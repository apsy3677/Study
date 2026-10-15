# One-Page Recall + Day-Of Checklist

## The round
60 min · HackerRank · **Narrative** (a flawed diagram + API + code snippet, usually *aggregator over external suppliers + booking*) → **generic questions**. Graded: **Design · Connectivity · QA · Code review · Communication**. A Gurugram SSE on this track was rejected for **weak connectivity**; a Staff candidate was down-levelled after this round.

## Run-sheet (say it, then do it)
**Restate → 4–5 clarifying Qs → numbered gap list → "top 3 are…" → redesign (what · how · trade-off · failure & metric) → API + connectivity → test plan → summary.**

Clarify: scale & read:write · freshness SLA · supplier constraints (metered? limits? push? batch?) · oversell rules · dedupe rule · latency SLO · partial-failure policy · who the clients are.

## Gap hunt: walk every arrow
Sync external call on the hot path · SPOF/no LB · no cache / bad key / stampede · **no timeouts** · unsafe retries · no breaker/bulkhead · all-or-nothing results · no rate limit/budget (metered!) · **no pagination** · **no idempotency** · **double booking race** · dual write (→ outbox) · slow work inline (→ queue) · no backpressure · no dedupe · API: verbs/versioning/errors/**auth** · secrets in code · PII in logs · no observability · no SLO/canary.
**Fix order:** money/data correctness → availability → latency/cost → scale → operability.

## Connectivity formulas
- **Timeout:** connect ~300 ms, read ≈ p99 × 1.5, child deadline = min(own, remaining − margin).
- **Retry:** transient only (timeout, 502/503/504, 429 + Retry-After) · idempotent only · `sleep = rand(0, min(cap, base·2^n))` · ≤ 3 attempts · within the deadline · budget ≤ 10% · one layer.
- **Idempotency-Key:** unique (key, hash) → same → stored response · in progress → 409 · different body → 422 · TTL. Consumers dedupe by event ID. Ambiguous supplier timeout → **query by our ref before retrying**.
- **Concurrency:** `UPDATE … SET n = n-1 WHERE … AND n > 0` → check row count.
- **Breaker:** closed → (error % over a window) → open (fail fast) → half-open trial. **Bulkhead:** a bounded pool per dependency.
- **Partial:** 200 + `partial: true` + per-source status. Search yes, booking never.
- **Pagination:** cursor `WHERE (k, id) > last ORDER BY k, id LIMIT n`, opaque cursor, capped limit.
- **Errors:** 4xx don't retry · 5xx maybe · 429/503 + Retry-After · RFC 7807 body + traceId.
- **Auth:** users OAuth2/OIDC + short JWT · partners OAuth2 client-credentials / HMAC / mTLS · internal mTLS · secrets in a vault, rotated · **authZ ownership (IDOR)**.
- **Webhooks:** HMAC(timestamp.body), constant-time compare, 5-min window, dedupe by event ID, ack fast + queue, version for ordering, reconcile by polling.
- **Outbox:** row + event in one tx → relay → Kafka → idempotent consumers. **Saga:** orchestrated state machine + compensations + reconciler.
- **Protocols:** REST at the edge · gRPC internal (HTTP/2, protobuf, deadlines, L7 LB) · GraphQL for BFF (N+1 → DataLoader).
- **Supplier economics:** cache + popularity-weighted refresh + single-flight + batch/delta + ETag · **look vs book** (re-validate at booking) · metrics: price-changed-at-booking %, cost per 1k searches.

## Code review order
Intent → **correctness → security (SQLi, secrets, authZ, PII) → integrity (race, tx, idempotency) → reliability (timeouts, swallowed exceptions, leaks) → performance (client/DB per call, N+1, unbounded) → design (SRP/OCP → strategy + factory, DIP) → tests → nits.**
Labels: *issue (blocking) / suggestion / question / nit / praise*. Fix the top 2 in code. Say how you'd prevent a recurrence (lint rule, library).

## Test map (draw it)
Unit = logic (dedupe, pricing, backoff) · Component = service + stubs (500/429/slow → partial, no storm) · Integration = real DB/Kafka (idempotency, double booking, outbox) · Contract = Pact internal; fixtures + nightly sandbox for suppliers · E2E = 1–2 journeys · NFR = load 2× peak, spike, soak, chaos (Toxiproxy) · Prod = canary, flags, dark launch, synthetic, SLO burn alerts. **Always say why + cost.**

## Staff add-ons (one per answer)
Quantify (QPS, cost) · the business metric that validates the trade-off · what I'd standardise (shared client lib, idempotency middleware, contract gate, lint rules) · rollout/migration plan · ownership/on-call/runbook.

## Openers / closers
- Open: *"Let me restate, ask a few questions, list the gaps I see, then fix them in priority order."*
- Check in: *"Should I go deeper on the supplier side or move to the API?"*
- Time check (~45 min): *"I'd like to cover testing. Shall I sketch the test plan?"*
- Close: *"To summarise: the three biggest risks were X, Y, Z; I fixed them with A, B, C; I'd verify with these tests and these metrics; next I'd look at…"*

---

## Day-of checklist
- [ ] Night before: this page + [01-Narrative-Playbook §3](01-Narrative-Playbook.md) + CR-1 answer key. **Nothing new after 6 pm.**
- [ ] HackerRank link tested; quiet room; second monitor off; water.
- [ ] Have a 60 s intro + one connectivity-heavy project story ready (an integration with an external system: what failed, what you built).
- [ ] Decide your sketch language: **Java** (or Go/Python pseudocode). Not C++.
- [ ] Prepare 2 questions for them: *"How do supplier integrations get built today: a shared connectivity framework or per team?"* · *"What does the platform team measure for integration quality: supplier SLOs, cost per search?"*
- [ ] During: narrate, number your gaps, watch the clock at 25 / 45 / 52 min.
