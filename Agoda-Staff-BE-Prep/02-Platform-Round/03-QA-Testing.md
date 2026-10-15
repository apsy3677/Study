# Quality Assurance & Testing Strategy

> Toolkit: *"Start with **why**: explain the value each test brings."* Recruiter: *"justify which test types you'd use, their **cost vs benefit**, and how you cover **non-functional** requirements (resilience, performance)."*
> So never list test types. For each one say: **what risk it removes, what it costs, and where it sits in the pipeline.**

**Contents:** [1 Mental model](#1-the-mental-model-risk--cost) · [2 Pyramid vs trophy](#2-pyramid-vs-trophy-vs-honeycomb) · [3 Each level](#3-each-test-level-what-why-cost-tools) · [4 Contract testing](#4-contract-testing-the-connectivity-teams-best-friend) · [5 Non-functional](#5-non-functional-testing) · [6 Test doubles](#6-test-doubles-pick-the-right-one) · [7 Failure-mode map](#7-failure-mode--test-type-map-the-table-to-draw-in-the-interview) · [8 Template answer](#8-template-answer-test-plan-for-a-new-supplier-integration) · [9 Shift-right](#9-shift-right-testing-in-production-safely) · [10 Flaky tests](#10-flaky-tests-policy) · [11 Legacy service](#11-staff-question-how-would-you-improve-quality-on-a-legacy-service-with-low-coverage) · [12 Metrics](#12-quality-metrics-worth-naming)

---

## 1. The mental model: risk × cost
- Every test **buys confidence against a specific risk** and **costs**: writing time, run time, flakiness, maintenance, and how late it gives feedback.
- **Push each check to the lowest, cheapest level that can catch it.** Business-rule bugs go in unit tests. "Does our SQL work against real Postgres" goes in integration tests. "Does our JSON match what the supplier really sends" goes in contract tests. "Does the whole booking journey work" gets a handful of E2E tests.
- **Fast feedback wins**: a unit suite of 3 minutes on every commit catches more bugs in practice than a perfect E2E suite that runs nightly and is red half the time.

## 2. Pyramid vs trophy vs honeycomb
```
        /\        E2E (few, slow, brittle, highest confidence per test)
       /  \       ── service/component + contract
      /----\      integration (real DB, real Kafka via containers)
     /------\     unit (many, ms each, precise failure location)
```
- **Test pyramid** (Cohn/Fowler): many unit, fewer integration, very few E2E. Good default for logic-heavy services (pricing rules, availability calculation).
- **Testing trophy** (Kent C. Dodds) / **honeycomb** (Spotify, for microservices): the bulk is **integration/component tests** of one service with real infra in containers and mocked *external* dependencies. Microservices have little logic per service and lots of integration surface, so that's where bugs live.
- ⭐ What to say: *"I don't treat the shape as dogma. I look at where this service's bugs come from. A pricing engine is pyramid-shaped; a supplier gateway is honeycomb-shaped: most risk is in the integration, so most tests are component tests against containerised infra plus contract tests per supplier."*

## 3. Each test level: what, why, cost, tools

| Level | Scope | Catches (why) | Cost | Tools (JVM / Go / Python) |
|---|---|---|---|---|
| **Unit** | One class/function, no I/O | Logic errors: price calculation, dedupe/cheapest selection, date ranges, retry/backoff maths, breaker state machine, mappers | ms, cheap, very stable | JUnit5 + AssertJ + Mockito / `testing` table-driven / pytest. Property-based: jqwik, `rapid`, Hypothesis |
| **Integration** | Your code + one real dependency | SQL correctness, transactions, locking/unique constraints, Kafka serialisation, Redis Lua scripts, ORM mappings | seconds; needs Docker | **Testcontainers** (Java, Go, Python), embedded Kafka, LocalStack |
| **Component / service** | One deployable service, real infra in containers, **externals stubbed** | The service works as a black box through its API: routing, validation, error mapping, timeouts/retries against slow or failing stubs | 10s of s | WireMock / MockServer / `httptest` / Toxiproxy for faults |
| **Contract** | The API agreement between consumer and provider | Breaking changes between services or with a supplier (field renamed, type changed, enum value added) *without* deploying both | cheap once set up | **Pact** (consumer-driven), Spring Cloud Contract, OpenAPI schema validation |
| **End-to-end** | The deployed system, user journey | Wiring/config/deploy issues no lower level sees (wrong URL, missing permission, broken auth between real services) | minutes, flaky, costly to maintain | Playwright/Cypress (UI), REST-assured/k6 scripts (API) in staging |
| **Exploratory / manual** | Humans probing | UX and "nobody thought of that" cases | people time | Session-based testing, bug bashes before big launches |

⭐ **E2E budget**: *"a handful of critical-journey E2E tests (search → book → cancel), run on every deploy to staging and as synthetic checks in production. Everything else lower down."*

## 4. Contract testing: the connectivity team's best friend
🧠 **Integration tests without deploying everything together.**
- **Consumer-driven contracts (Pact)**: the consumer's tests record the requests it makes and the responses it relies on → a **pact file** → published to a **Pact Broker** → the provider's CI replays them against the real provider → `can-i-deploy` gates the release.
- Why at Agoda: dozens of internal services + hundreds of supplier integrations; full E2E environments are slow and flaky. Contracts give **independent deployability**.
- **External suppliers won't run your Pact tests.** So: (1) record real supplier responses (sanitised) as **fixtures**, (2) validate their schema/OpenAPI in CI, (3) run a **scheduled sandbox check** against the supplier's test environment to detect *their* breaking changes, (4) strict-but-tolerant parsing (ignore unknown fields, alert on missing required ones).

## 5. Non-functional testing

| Type | Question it answers | How | When |
|---|---|---|---|
| **Load** | Do we meet the SLO at expected peak (e.g. 5k searches/s, p99 < 1 s)? | k6 / Gatling / Locust against a prod-like env, realistic traffic mix (search:book ≈ 100:1) | Before launch, and in CI nightly on the critical path |
| **Stress** | Where does it break, and *how* (graceful shedding or a collapse)? | Ramp past the limit; watch for 503s vs timeouts vs OOM | Capacity planning |
| **Spike** | Flash sale / campaign burst | Sudden 10× ramp | Before campaigns |
| **Soak / endurance** | Leaks over hours (memory, connections, file handles) | Moderate load for 8–24 h | Before major releases |
| **Resilience / chaos** | Do timeouts, retries, breakers, fallbacks actually work? | **Fault injection**: Toxiproxy (latency, resets, bandwidth), kill pods, block a supplier, fill a disk. Chaos Monkey / Litmus / Gremlin in staging, then game days in prod | Every resilience feature gets a fault test |
| **Security** | Injection, auth bypass, IDOR, secrets | SAST (Semgrep, SonarQube), dependency scanning (Dependabot, Snyk), DAST (OWASP ZAP), secret scanning (gitleaks), pen tests | SAST/deps on every PR; DAST nightly |
| **Performance regression** | Did this PR make the hot path slower? | Microbenchmarks (JMH, `go test -bench`) + a perf gate on key endpoints | CI on the hot path |
| **Compatibility** | Old clients still work with the new API | Contract tests + version matrix | Every API change |
| **Data/migration** | Schema migration is safe and reversible | Migrate a prod-sized snapshot, time it, test rollback; expand → migrate → contract | Before risky migrations |

⭐ Resilience features you design (timeout, retry, breaker, partial response, idempotency) are **untested promises** until there's a fault-injection test for each. Say so in the interview.

## 6. Test doubles: pick the right one
- **Dummy** (unused filler) · **Stub** (canned answers) · **Spy** (records calls) · **Mock** (pre-programmed expectations, verifies interactions) · **Fake** (working lightweight implementation: in-memory repo, fake supplier server).
- Prefer **fakes and stubs over mocks** for most tests. Over-mocking couples tests to implementation (refactors break tests even though behaviour didn't change).
- **Don't mock what you don't own** (wrap the supplier SDK in your adapter interface, mock *that*, and test the adapter itself against a stub HTTP server with recorded responses).
- A **configurable fake supplier** (latency, error rate, 429s, pagination, malformed payloads) is gold for component and chaos tests (lab 1 in the WSL plan builds exactly this).

## 7. Failure-mode → test-type map (the table to draw in the interview)

For the supplier-aggregator narrative:

| Failure mode | Test that proves we handle it | Level |
|---|---|---|
| Wrong cheapest-offer selection / dedupe bug | Table-driven tests: same flight from 3 suppliers, ties, currency conversion, missing fields | Unit |
| Supplier returns 500 / times out | Stub returns 500 / delays 3 s → we retry within budget, then return `partial: true` within the deadline | Component |
| Supplier rate-limits (429 + Retry-After) | Stub returns 429 → we back off for `Retry-After`, no retry storm (assert call count) | Component |
| Supplier changes the response schema | Recorded-fixture parsing test + nightly sandbox schema check | Contract / scheduled |
| Supplier slow for a long time | Toxiproxy latency → breaker opens, other suppliers unaffected (bulkhead), breaker metric emitted | Resilience |
| Double booking under concurrency | 100 parallel bookings for 10 rooms against real Postgres → exactly 10 succeed | Integration |
| Client retries POST /bookings | Same `Idempotency-Key` twice → one booking, same response; different body → 422 | Component |
| Crash between DB write and event publish | Kill the outbox relay mid-batch → events still published exactly once to consumers (dedupe) | Integration |
| Cache stampede on a hot route | Concurrent misses → single supplier call (single-flight) | Integration |
| Stale price shown at booking | Price changed at supplier → booking returns 409 `price-changed`, no charge | Component / E2E |
| SQL injection / IDOR | Malicious inputs; user A reading B's booking → 403/404 | Unit + DAST |
| Peak traffic | Load test at 2× forecast peak, p99 < SLO, error rate < 0.1% | Load |
| Memory/connection leak | 12 h soak, flat memory and pool usage | Soak |
| Bad deploy | Canary with automated rollback on error-rate/latency regression | Production |

## 8. Template answer: "test plan for a new supplier integration"
> *"I'd test it in layers, starting with why:*
> 1. *Unit tests for the adapter's mapping and error translation. That's where most supplier bugs are: odd fields, time zones, currencies. They're fast and run on every commit.*
> 2. *Component tests of the gateway with a stub supplier built from recorded real responses, including the ugly ones: 500s, 429s, slow responses, malformed JSON, empty pages. These prove retries, timeouts and partial results.*
> 3. *A contract/schema check against the supplier's spec, plus a nightly job against their sandbox, so we notice when they change something before customers do.*
> 4. *Integration tests with Testcontainers for our own DB/Kafka paths: idempotency and the outbox.*
> 5. *A load test sized to the supplier's rate limit and our peak, and a chaos test where the supplier goes slow.*
> 6. *In production: a dark launch (call the supplier, don't show its results, compare), then a percentage rollout behind a feature flag, synthetic sandbox bookings, and per-supplier SLO dashboards.*
> *I'd stop at one or two E2E journeys in staging. More than that costs more in flakiness than it buys."*

## 9. Shift-right: testing in production, safely
- **Feature flags** (decouple deploy from release; kill switch per supplier).
- **Canary releases**: 1% → 10% → 50% → 100% with automated analysis (error rate, latency, business metrics like conversion) and auto-rollback.
- **Dark launch / shadow traffic**: mirror real requests to the new path, compare results, discard the output.
- **A/B experiments** (very Agoda: experimentation is core to their culture): ship behind an experiment, measure conversion/revenue impact.
- **Synthetic monitoring**: scripted probes (search + sandbox booking) every minute from several regions.
- **Observability as testing**: SLOs + burn-rate alerts are the final safety net.

## 10. Flaky tests policy
- A flaky test is worse than no test: it trains people to ignore red builds.
- Detect: rerun-on-failure stats, track flake rate per test. **Quarantine** (move it out of the blocking suite, with a ticket and an owner) instead of deleting or ignoring it.
- Root causes: time (use an injectable clock), randomness (seeded), ordering, shared state between tests, real network calls, `sleep()`-based waits (use polling with a timeout, e.g. Awaitility), port collisions.
- ⭐ *"I'd publish a flaky-test dashboard and make fixing quarantined tests part of the team's definition of done. Leads have to protect trust in CI."*

## 11. Staff question: "How would you improve quality on a legacy service with low coverage?"
1. **Measure first**: where do incidents and bugs come from (incident postmortems, bug tracker), which code changes most (churn × complexity hotspots)?
2. **Characterisation tests** (golden master) around the riskiest flows before touching code. Capture current behaviour, even if it's weird.
3. **Coverage on new/changed code** as the CI gate (e.g. ≥ 80% diff coverage), not a global % target (a global target creates useless tests).
4. Add **contract tests** at the service boundaries and **component tests** for critical journeys.
5. Refactor behind the tests (strangler fig for big pieces).
6. **Mutation testing** (PIT for the JVM) on core modules to check the tests actually assert something.
7. Make it cultural: a review checklist item ("tests for the failure path?"), and pairing on the first few.
8. Track outcomes: change failure rate, escaped defects, MTTR (the DORA metrics), not coverage alone.

## 12. Quality metrics worth naming
- **DORA**: deployment frequency, lead time for changes, **change failure rate**, **MTTR**.
- Escaped defects (found in prod vs before), flake rate, CI duration, diff coverage, mutation score on core modules.
- SLO attainment and error-budget burn.
