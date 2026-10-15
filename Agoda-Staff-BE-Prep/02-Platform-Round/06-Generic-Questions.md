# Generic Questions Bank (part 2 of the round)

The second part of the round is **generic questions independent of the narrative**. Answer each in **30–60 seconds**: the point → the mechanism → a trade-off → (Staff add-on: experience, standardisation, or business impact).
Drill: read the question, answer aloud, *then* open the key. Mark the ones you fumbled in [PROGRESS.md](PROGRESS.md).

---

## A. System analysis & design (12)

**A1. How do you approach a design you've been handed that "has problems"?**
<details><summary>Answer</summary>
Clarify goals and SLOs → walk every component and arrow asking "what if this is slow, down, duplicated, 10× loaded" → list gaps → prioritise by correctness > availability > latency/cost > scale > operability → fix the top few with trade-offs → define how we'd verify (tests, metrics). <b>Staff:</b> also ask what changed recently (traffic, new supplier), since problems usually follow change.
</details>

**A2. Monolith vs microservices: when would you split?**
<details><summary>Answer</summary>
Split when parts need <b>independent scaling, deployment cadence, or ownership</b> (team boundaries: Conway), or have different reliability needs (search vs booking). Costs: network failures, distributed data, observability, ops overhead. Start with a modular monolith with clear boundaries; extract along the seams that hurt. <b>Staff:</b> the deciding factor is usually org/team autonomy, not tech.
</details>

**A3. What is event-driven architecture and when is it a bad idea?**
<details><summary>Answer</summary>
Services communicate by publishing facts ("BookingConfirmed") that others react to: loose coupling, easy fan-out, replay (Kafka), absorbs bursts. Bad when you need an immediate answer, strict cross-service consistency, or the flow is hard to follow (choreography spaghetti, debugging across hops). Needs idempotent consumers, schema governance, DLQs, tracing.
</details>

**A4. How do you make a service horizontally scalable?**
<details><summary>Answer</summary>
Make it <b>stateless</b> (sessions in a token or Redis), put it behind an LB with health checks, externalise state to a scalable store, avoid local caches that need consistency (or accept the staleness), partition the data (sharding by key), make background work queue-based, and autoscale on the right signal (CPU, RPS, queue lag). Watch the shared bottlenecks: the DB, a hot key, a downstream rate limit.
</details>

**A5. SQL or NoSQL for X?**
<details><summary>Answer</summary>
Decide by <b>access patterns, consistency, and scale</b>. Bookings/payments: SQL (transactions, constraints, joins, auditing). Search/offers: a document store/Elasticsearch/cache (denormalised, read-heavy, flexible schema). Time-series/events: Cassandra/Kafka/ClickHouse. KV at huge scale with simple lookups: DynamoDB/Couchbase/Redis. Polyglot persistence is fine, but each store adds ops cost. (Masterclass 02-02 covers the NoSQL families.)
</details>

**A6. CAP / PACELC in one minute.**
<details><summary>Answer</summary>
During a network partition you choose consistency or availability (CAP). Even without partitions you trade latency vs consistency (PACELC). Booking inventory: favour consistency (don't oversell). Search results: favour availability/latency (stale is OK). Choose per operation, not per system.
</details>

**A7. How do you avoid a single point of failure?**
<details><summary>Answer</summary>
Redundancy at every layer: multiple instances across AZs behind LBs, DB primary + replicas with automatic failover, multi-broker Kafka with a replication factor of 3, no single cron box (leader election or a scheduler service), redundant suppliers/PSPs where possible. Then <b>test the failover</b> (game days), because untested redundancy is a hope, not a design.
</details>

**A8. Caching strategies and their pitfalls?**
<details><summary>Answer</summary>
Cache-aside (most common), read-through, write-through (consistent, slower writes), write-behind (fast, risk of loss). Pitfalls: stampede (single-flight, jittered TTL, stale-while-revalidate), invalidation (TTL + event-driven), hot keys (local cache, replication), coarse keys (wrong data), caching errors, memory eviction policy (LRU/LFU). Measure the hit ratio and staleness impact.
</details>

**A9. How would you handle a flash sale (huge spike on few items)?**
<details><summary>Answer</summary>
Protect the core: a waiting room/queue at the edge, rate limits, pre-warmed capacity. Inventory: atomic decrement (Redis `DECR` or a conditional SQL update), per-unit tokens, short holds with expiry. Async order processing via a queue. Degrade non-critical features. Load-test beforehand. (Masterclass 07-02.)
</details>

**A10. Strong vs eventual consistency: give a real example of each in travel.**
<details><summary>Answer</summary>
Strong: the room allotment decrement and the payment state (money and oversell). Eventual: search results, review counts, the "X people are looking" badge, analytics, partner notifications. The art is putting the boundary in the right place: re-validate at the step where it matters (booking).
</details>

**A11. How do you estimate capacity quickly?**
<details><summary>Answer</summary>
DAU × actions/day ÷ 86,400 × peak factor (3–10×) = peak QPS. × payload = bandwidth. × retention = storage. Then per-instance throughput → instance count + headroom (N+2, AZ loss). Example: 10M searches/day ≈ 115/s avg, ~1k/s peak. At 1:1000 look-to-book that's ~10k bookings/day.
</details>

**A12. What makes a design "operable"?**
<details><summary>Answer</summary>
SLOs and alerts on symptoms (not causes), dashboards per dependency, distributed tracing, runbooks, feature flags/kill switches, safe deploys (canary, rollback), graceful degradation paths, capacity headroom, and clear ownership. <b>Staff:</b> operability is a design requirement written into the design doc, not a post-launch task.
</details>

## B. Connectivity & APIs (16)

**B1. REST vs gRPC: which would you use between search and pricing, and why?**
<details><summary>Answer</summary>
gRPC: internal, latency-sensitive, high-QPS. Protobuf is compact and fast to parse, HTTP/2 multiplexing, a strict generated contract, deadlines propagate natively, streaming if needed. Costs: needs an L7 LB (long-lived connections), harder to debug, not browser-native. REST stays at the public/partner edge.
</details>

**B2. When would you choose GraphQL?**
<details><summary>Answer</summary>
For client-facing aggregation (BFF) where different clients need different shapes (mobile vs web property page) and you want to avoid many round trips. Watch for N+1 resolvers (DataLoader), caching (no HTTP cache by default; use persisted queries), and query cost limits. Not for service-to-service or partner integrations.
</details>

**B3. Webhooks vs polling vs pub/sub for receiving supplier updates?**
<details><summary>Answer</summary>
Webhooks: near-real-time and efficient, but you must verify signatures, dedupe, handle ordering, and stay up. Polling: simple and under your control, but costs calls (metered!) and adds latency. Pub/sub: great internally, rarely offered by external suppliers. In practice: <b>webhooks when offered + periodic polling to reconcile</b>, polling with popularity-weighted schedules otherwise.
</details>

**B4. What makes an operation idempotent, and how do you make POST idempotent?**
<details><summary>Answer</summary>
Applying it N times has the same effect as once. GET/PUT/DELETE are by definition; POST isn't. Add an <code>Idempotency-Key</code>: store key + request hash + response under a unique constraint, return the stored response on a duplicate, 422 on a different body for the same key, expire keys after a TTL. Consumers dedupe by event ID.
</details>

**B5. Design a retry policy.**
<details><summary>Answer</summary>
Retry only transient errors (timeouts, 502/503/504, 429 with Retry-After) on idempotent operations; exponential backoff with full jitter; 2–3 attempts; within the request deadline; a retry budget (~10%); retry at a single layer; log/metric each attempt. Pair it with a circuit breaker so you stop retrying a dead dependency.
</details>

**B6. How does a circuit breaker work?**
<details><summary>Answer</summary>
Closed: count failures in a rolling window. Over the threshold → Open: fail fast with a fallback for a cool-down. Then Half-open: allow a few trial calls; success → Closed, failure → Open. Per dependency/endpoint. Protects the caller's resources and gives the dependency room to recover.
</details>

**B7. How do you handle a downstream that's slow but not failing?**
<details><summary>Answer</summary>
Timeouts from p99, a bulkhead (bounded concurrency) so it can't exhaust threads, a breaker on slow calls (Resilience4j has a slow-call rate threshold), hedged requests for idempotent reads, partial results/fallbacks, and an alert on latency SLO burn. Then talk to the owning team/supplier with the data.
</details>

**B8. Offset vs cursor pagination?**
<details><summary>Answer</summary>
Offset is simple and allows jump-to-page, but is O(offset) in the DB and skips/duplicates rows when data changes. Cursor/keyset (<code>WHERE (sort_key, id) &gt; last</code>) is O(limit) with an index and stable under writes, but next/prev only. Use cursors for feeds, search and sync APIs; make the cursor opaque; cap the page size.
</details>

**B9. How do you secure a public partner API?**
<details><summary>Answer</summary>
TLS everywhere; per-partner credentials (OAuth2 client-credentials with scopes, or HMAC-signed requests; mTLS for high-trust partners); authZ on every resource (partner X → only its hotels); input validation + size limits; per-partner rate limits/quotas; a WAF; audit logs; secret rotation; no sensitive data in URLs; versioning and deprecation policy.
</details>

**B10. JWT vs opaque session tokens?**
<details><summary>Answer</summary>
JWT: self-contained, verified locally via the public key (no lookup, scales), but hard to revoke → short expiry + refresh tokens + an emergency denylist; don't put secrets in it (it's only base64, signed but not encrypted). Opaque: a lookup on every request (Redis), easy revocation. Common hybrid: an opaque refresh token, a short-lived JWT access token.
</details>

**B11. How do you call an external API that requires OAuth2 efficiently?**
<details><summary>Answer</summary>
Client-credentials flow; cache the access token until shortly before expiry (shared across threads, refreshed once, single-flight); on 401, refresh once and retry; keep client secrets in a vault; pooled HTTP connections; timeouts on the token endpoint too (it's a dependency).
</details>

**B12. What is backpressure? Give two mechanisms.**
<details><summary>Answer</summary>
Signalling a producer to slow down when the consumer can't keep up, instead of buffering until collapse. Mechanisms: bounded queues + rejecting/blocking when full; 429/503 with Retry-After; pull-based consumption (Kafka consumers pull at their own pace); TCP/HTTP/2 flow-control windows; reactive streams <code>request(n)</code>; adaptive concurrency limits.
</details>

**B13. How do you return results when 1 of 5 suppliers fails?**
<details><summary>Answer</summary>
Fan out in parallel with an overall deadline; return what arrived with <code>partial: true</code> and per-source status (HTTP 200); maybe fall back to cached data for the missing supplier, labelled stale. Partial is fine for search, never for booking. Track the partial rate per supplier.
</details>

**B14. How do you design error responses?**
<details><summary>Answer</summary>
Correct HTTP status (4xx client, 5xx server), an RFC 7807 Problem Details body with a stable machine-readable <code>type</code>/code, a human message, and a trace ID; never stack traces. Indicate retryability (status + Retry-After). Map supplier errors into your own taxonomy in the adapter.
</details>

**B15. How do you version an API without breaking clients?**
<details><summary>Answer</summary>
Make additive changes by default and have tolerant readers. For breaking changes, a new version (<code>/v2</code> or a header), run both, measure usage per version, announce deprecation with a Sunset header, migrate the big consumers proactively, then remove. CI checks for breaking changes (openapi-diff, buf breaking) + consumer contract tests.
</details>

**B16. Sync vs async: how do you decide for a given call?**
<details><summary>Answer</summary>
Does the caller need the result to continue/respond? If yes: sync with a timeout. If it only needs a guarantee that it'll happen: async via a queue (an outbox if it follows a DB write). Async improves availability and absorbs spikes, but adds eventual consistency, ordering and duplicate handling, plus observability needs.
</details>

## C. Quality assurance (12)

**C1. Explain the test pyramid and when you'd deviate.**
<details><summary>Answer</summary>
Many fast unit tests, fewer integration tests, very few E2E: cheap, fast feedback and precise failure location. Deviate for integration-heavy microservices (honeycomb/trophy: mostly component tests against real infra in containers) because bugs live at boundaries. Choose the shape by where the bugs come from.
</details>

**C2. Unit vs integration vs E2E: the value and cost of each?**
<details><summary>Answer</summary>
Unit: logic correctness, ms, stable, but can't catch wiring/infra issues. Integration: real DB/Kafka behaviour (SQL, transactions, serialisation), seconds, needs Docker. E2E: the whole journey incl. config/deploy, highest confidence per test, but slow, flaky, costly to maintain → only for critical journeys.
</details>

**C3. What's contract testing and why would you use it?**
<details><summary>Answer</summary>
Verifying that the provider meets the consumer's expectations without deploying both. Consumer-driven (Pact): consumer tests generate a pact; provider CI verifies it; <code>can-i-deploy</code> gates releases. Gives independent deployability and catches breaking API changes early. For external suppliers: recorded fixtures + schema checks + nightly sandbox runs.
</details>

**C4. How do you test resilience features like retries and circuit breakers?**
<details><summary>Answer</summary>
Fault injection: stub servers returning 500/429/slow responses, Toxiproxy for latency/resets, assert behaviour (attempt counts, backoff timing with a fake clock, breaker state transitions, partial results within the deadline, metrics emitted). In staging/prod: chaos experiments and game days.
</details>

**C5. What non-functional tests would you run before a big campaign?**
<details><summary>Answer</summary>
A load test at forecast peak × 2 with a realistic mix, a spike test, a soak test for leaks, failover tests (lose an AZ/node), dependency-degradation tests (slow supplier/PSP), and verifying autoscaling and alerting fire. Plus a capacity review of downstream limits (supplier quotas, DB connections).
</details>

**C6. Mocks vs fakes vs stubs: when to use which?**
<details><summary>Answer</summary>
Stub: canned responses for state-based tests. Fake: a working lightweight implementation (in-memory repo, fake supplier server), great for component tests. Mock: verifies interactions; use sparingly (overuse couples tests to implementation). Don't mock types you don't own: wrap them in your own interface.
</details>

**C7. How do you deal with flaky tests?**
<details><summary>Answer</summary>
Track flake rates, quarantine with an owner and a ticket (don't ignore or delete), fix the root causes (time, randomness, ordering, shared state, real network, sleeps → polling waits), and keep CI trustworthy. Make it a team metric.
</details>

**C8. How do you test a database migration?**
<details><summary>Answer</summary>
Expand → migrate → contract (backward-compatible steps, so old and new code both work), run against a prod-sized snapshot to time it and check locks, test rollback, verify with data checks (row counts, checksums), deploy behind flags, and monitor.
</details>

**C9. How do you ensure quality in production (shift-right)?**
<details><summary>Answer</summary>
Canary with automated analysis and rollback, feature flags/kill switches, dark launches/shadow traffic, A/B experiments, synthetic monitoring, SLOs with burn-rate alerts, error tracking, and fast rollback paths.
</details>

**C10. What would your test strategy be for a payment integration?**
<details><summary>Answer</summary>
Unit (amount/currency/rounding, state machine), component tests with a PSP stub (declines, timeouts, duplicates, webhooks out of order), PSP sandbox contract tests, idempotency + reconciliation tests, security tests (no PAN in logs, tokenisation), load at peak, and production reconciliation reports as the final safety net.
</details>

**C11. Is 100% coverage a good goal?**
<details><summary>Answer</summary>
No. Coverage shows what's executed, not what's verified. Use diff coverage on changed code as a gate, focus on critical paths and failure paths, and check test quality with mutation testing on core modules. Measure escaped defects and change failure rate instead.
</details>

**C12. How do you test an async, event-driven flow end to end?**
<details><summary>Answer</summary>
Component tests per service with embedded/containerised Kafka (publish an input, assert the output event/DB state with polling waits), contract tests on event schemas (a schema registry with compatibility rules), idempotency tests (redeliver the same event), DLQ tests (poison message), and a few E2E flows in staging with trace-based assertions.
</details>

## D. Code review (6)

**D1. What do you look for first in a code review?**
<details><summary>Answer</summary>
Intent, then correctness and security (injection, secrets, authZ, PII), data integrity (races, transactions, idempotency), reliability (timeouts, error handling, resource leaks), performance (per-call initialisation, N+1, unbounded queries), design (SRP/OCP/DIP), tests, and only then style nits. Labelled by severity.
</details>

**D2. How do you give feedback to a senior engineer who disagrees?**
<details><summary>Answer</summary>
Separate facts from preferences; explain the impact with evidence (a failing test, a benchmark, an incident); ask about their reasoning (they may know something I don't); offer alternatives; if it's a preference, let it go; if it's a real risk, escalate to a quick sync or a design review rather than a comment war. Document the decision.
</details>

**D3. How do you keep reviews fast on a busy team?**
<details><summary>Answer</summary>
Small PRs (&lt; 400 lines), clear descriptions, automation for style/lint/security (formatters, Semgrep, SAST) so humans review logic, review SLAs (e.g. first response within 4 working hours), rotating reviewers, and pairing for complex changes.
</details>

**D4. Which SOLID principle is most often violated in service code, and how do you fix it?**
<details><summary>Answer</summary>
SRP and OCP: god services with <code>if/else</code> per supplier/type. Fix: extract interfaces (Strategy/Adapter per supplier), a registry/factory, constructor injection (DIP) → testable and extensible. Cross-cutting concerns (retry, metrics, cache) go in decorators.
</details>

**D5. What's a code smell you'd block a PR for?**
<details><summary>Answer</summary>
I block on <i>risks</i>, not smells: SQL injection, hardcoded secrets, swallowed exceptions on money paths, missing transactions/idempotency on writes, no timeout on external calls, PII in logs, unbounded queries. Pure smells (long method, naming) get suggestions unless they hide a bug.
</details>

**D6. Walk me through a review comment you've given that changed a design.**
<details><summary>Answer</summary>
Prepare one real story from your work, STAR-style: the PR, what you spotted (e.g. a race or a missing idempotency), how you raised it (a question first, then data), the outcome, and what you standardised afterwards (a lint rule, a library, a checklist). Prepare it in <a href="../04-Projects-Behavioral/README.md">04-Projects-Behavioral</a>.
</details>

## E. Communication / Staff-level (4)

**E1. Explain idempotency to a product manager.**
<details><summary>Answer</summary>
"If a customer's phone loses signal and the app sends 'book' twice, we make sure they get one booking and one charge, never two. Every booking attempt carries a unique ticket number, and we ignore repeats of the same ticket."
</details>

**E2. How do you drive a cross-team change like "all supplier integrations must use the shared resilience library"?**
<details><summary>Answer</summary>
Data first (incidents caused by missing timeouts/retries), an RFC with alternatives, a pilot with one team, make the right way the easy way (templates, a library, docs, migration help), track adoption, add guardrails (lint/CI checks), and celebrate the early adopters. Influence without authority.
</details>

**E3. How do you balance tech debt against feature work?**
<details><summary>Answer</summary>
Make the debt visible with impact (incidents, lead time, on-call load), tie fixes to business outcomes, reserve capacity (e.g. 20%), and bundle debt work with related features. Prioritise debt that blocks scaling or causes incidents.
</details>

**E4. Tell me about a time an integration failed in production.**
<details><summary>Answer</summary>
Prepare your own story: detection (alert or customer), mitigation (feature flag, fallback), root cause (missing timeout, schema change), the blameless postmortem, and the systemic fixes (contract tests, synthetic checks, a library). Draw it from your Synopsys/Microsoft/Adobe work in <a href="../04-Projects-Behavioral/README.md">04-Projects-Behavioral</a>.
</details>
