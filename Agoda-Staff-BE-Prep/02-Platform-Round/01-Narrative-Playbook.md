# Narrative Playbook: how to run the 40-minute scenario

The narrative is a **"spot what's wrong, fix it, justify it"** exercise, not a blank-page system design. The diagram is deliberately thin. The person who lists the gaps *systematically* and fixes the *important* ones first, with reasons, wins. Use this run-sheet every time you practise.

---

## 1. The run-sheet (memorise the 7 steps)

| # | Step | Time | What you say / do |
|---|---|---|---|
| 1 | **Restate** | 1 min | "So we have users searching X, a service that calls N suppliers and stores to one DB, and a booking step. Let me check what matters most." |
| 2 | **Clarify** | 3–4 min | Ask the **8 questions** (§2). Write the answers as a short list in the pane: they become your design constraints |
| 3 | **Gap hunt** | 4–5 min | Walk the diagram **left to right** with the **gap checklist** (§3). Write a numbered list of gaps *before* fixing anything. Say: "I'll list what I see, then fix the top ones in priority order." |
| 4 | **Prioritise** | 30 s | "The three that hurt most are A (correctness: double booking), B (supplier calls on the request path: latency + cost), C (no pagination: memory and payload). I'll fix those first." |
| 5 | **Redesign** | 8–10 min | Draw the improved diagram (§5). For each change: **mechanism + trade-off + failure mode** (§4 formula) |
| 6 | **Contract + connectivity** | 8–10 min | API: endpoints, pagination, idempotency, errors, auth, versioning. Supplier side: fetch strategy, limits, retries, breaker, timeouts, partial results |
| 7 | **Verify + operate** | 3–4 min | Test plan mapped to the failure modes. Observability: what you'd measure, the SLO, the alert. Rollout: flags, canary, migration |

Then the interviewer usually moves to the **code snippet** → [04-Code-Review.md](04-Code-Review.md).

---

## 2. The 8 clarifying questions (pick the 4–5 that matter)

1. **Scale:** searches/s and bookings/s? Read:write ratio? (Typical: search ≫ booking, 100:1 to 1000:1 "look-to-book".)
2. **Freshness:** how stale can a search result be? Is the price re-checked at booking? (The answer is almost always *search may be slightly stale, booking must be exact*.)
3. **Supplier constraints:** metered (cost per call)? Rate limits? Latency/p99? Push/webhook available, or poll only? Batch endpoints? Pagination?
4. **Correctness:** can we oversell? Who is the source of truth for inventory, us or the supplier?
5. **Duplicates:** can the same item come from several suppliers? Rule: cheapest? preferred supplier?
6. **Latency SLO** for search and for booking? (e.g. search p99 < 1 s, booking < 3 s.)
7. **Failure policy:** if one supplier is down, show partial results or fail?
8. **Clients:** who calls the API (our app, partners)? → auth model, versioning, rate limiting.

Staff touch: also ask **"what does success look like for the business: conversion, cost per search, or supplier spend?"** It shows you link design to impact.

---

## 3. The gap-hunt checklist (walk every box and arrow)

Read every **arrow** as "what happens when this is slow, down, duplicated, or overloaded?" and every **box** as "what if there are 10× more requests, or two of them?"

| Area | Gap to look for | Typical fix |
|---|---|---|
| **Request path** | Synchronous fan-out to external suppliers inside the user request | Pre-fetch/cache (pull model) + async refresh; on-demand fetch only on a miss, with a deadline |
| **Single points of failure** | One service instance, one DB, no LB | LB + stateless replicas + health checks; DB replica/failover |
| **Caching** | No cache for search; no invalidation/TTL strategy | Cache-aside with TTL by data volatility; request coalescing (avoid stampede) |
| **Timeouts** | No timeout on supplier/DB calls | Per-call timeouts under an overall deadline |
| **Retries** | None, or unbounded/immediate retries | Retry idempotent ops only, exponential backoff + jitter, retry budget, honour 429 `Retry-After` |
| **Isolation** | One slow supplier drains the thread pool | Bulkhead per supplier + circuit breaker |
| **Partial results** | All-or-nothing response | Return what arrived within the deadline, flag `partial: true` |
| **Rate / cost** | Unlimited calls to a metered or rate-limited API | Token bucket per supplier, call budget, batch endpoints, cache, conditional requests (ETag) |
| **Pagination** | List endpoint returns everything | Cursor (keyset) pagination, page-size cap |
| **Idempotency** | `POST /bookings` retried → double booking/charge | `Idempotency-Key` + unique constraint; supplier booking reference |
| **Concurrency** | Two users book the last room | Conditional update / row lock / supplier hold (reserve → confirm) |
| **Consistency** | DB write + event/notification not atomic | Transactional outbox → queue |
| **Async work** | Slow tasks (emails, supplier confirms) done inline | Queue + workers, DLQ for poison messages |
| **Backpressure** | Nothing stops overload | Bounded queues, load shedding (503 + `Retry-After`), rate limits at the edge |
| **Dedupe** | Same item from several suppliers shown twice | Canonical ID mapping (flight number+date, hotel mapping), pick cheapest/preferred |
| **API contract** | No versioning, no error model, no auth, verbs misused | `/v1`, RFC 7807 errors, OAuth2/JWT, correct verbs/status codes |
| **Security** | Secrets in code, no authZ, PII in logs | Vault/secret manager, scopes, field masking, TLS/mTLS |
| **Observability** | No metrics/tracing/logs | RED metrics per endpoint *and per supplier*, distributed tracing, structured logs with a correlation ID |
| **Data model** | Wrong store for the access pattern | Search store (ES / cache) vs transactional store (SQL) split |
| **Operations** | No SLOs, alerts, runbook, deploy safety | SLOs + burn-rate alerts, canary, feature flags |

**Order the fixes by:** correctness (money, double booking) → availability (SPOF, cascades) → latency/cost → scalability → operability → nice-to-have.

---

## 4. The answer formula for every change (say all 4 parts)

> **What** I add → **how it works** underneath → **trade-off** I'm accepting → **how it fails, and how I'd know** (metric/test).

Example (cache for search):
> "I'd put a Redis cache in front of search, keyed by `route+date`, **cache-aside**. On a miss we read from our availability store, not the supplier. TTL depends on volatility: about 5 min for schedules, about 60 s for price. **Trade-off**: users may see a price that's up to 60 s stale, so the booking flow **re-validates the price with the supplier** before charging. That's the standard look vs book split. **Failure**: a hot key expiring causes a stampede, so I'd use request coalescing (single-flight) and jittered TTLs. I'd watch the hit ratio and the 'price changed at booking' rate, which is my real staleness metric."

That last metric is the Staff touch: **a business-visible signal that tells you if the trade-off is right.**

---

## 5. How to draw (on HackerRank's whiteboard, or as text if it's clumsy)

Use **3 views**, only as much as needed:
- **Component** (always): boxes and arrows, **sync arrows solid, async dashed**, number the arrows so you can refer to them ("on arrow 3 I'd add a timeout").
- **Sequence** (for booking or any multi-step flow): actor → service → DB → supplier, with the failure branch.
- **Deployment** (only if asked): regions, LB, replicas, DB primary/replica.

If drawing is slow, type a text diagram. It's faster and the interviewer can read it:
```
Client ─▶ API GW (auth, rate limit) ─▶ Search Svc ─▶ Redis (cache) ─▶ Availability DB
                                        │ miss+stale
                                        └─▶ Supplier Gateway ─▶ Supplier A/B (timeouts, breaker, budget)
Scheduler ─▶ Refresh queue ─▶ Fetch workers ─▶ Supplier Gateway ─▶ normalize+dedupe ─▶ Availability DB
Client ─▶ Booking Svc ─▶ (idempotency) ─▶ SQL tx {booking + outbox} ─▶ Kafka ─▶ Supplier confirm worker
```

---

## 6. Phrases that score (communication is graded)

- **Signposting:** "I'll do three things: list the gaps, fix the top three, then the API." Then do them in that order.
- **Prioritising out loud:** "This is a nice-to-have; I'll park it and come back if we have time."
- **Checking in:** "Does that match what you had in mind, or should I go deeper on the supplier side?" (once every 8–10 min, not every sentence).
- **Trade-off:** "I'm choosing X over Y because of Z; if Z changes, say suppliers start offering webhooks, I'd switch to push."
- **Not knowing:** "I haven't used GraphQL federation in production. Here's how I'd reason about it…" (honest + reasoning beats bluffing).
- **Staff framing:** "If I were leading this, I'd also make the supplier client a shared library with retries, timeouts and metrics built in, so every new supplier integration gets them by default."
- **Non-technical version** (the Toolkit asks for audience awareness): "For a product manager: we'll show results from the suppliers that answer within a second, and confirm the exact price before payment, so customers never get charged a wrong price."

## 7. Anti-patterns that lose points
- Jumping into fixes before listing gaps (looks unsystematic).
- Buzzword lists ("add Kafka, Redis, K8s") without mechanism or reason.
- Fixing 15 small things and never reaching booking correctness.
- Redesigning from scratch and ignoring the given diagram (they wanted analysis of *their* system).
- 3 minutes on one naming nit in the code review.
- Silence while thinking: narrate ("I'm checking what happens if this supplier times out…").
