# Mock Rounds: 3 full 60-minute platform interviews

**How to run:** best with the coach (open this folder in Claude Code and say *"Run Mock 1"*; [CLAUDE.md](CLAUDE.md) keeps the interviewer persona and hides the faults). Solo: read only the prompt + diagram + code, set a 60-minute timer, answer aloud (record yourself), then open the interviewer notes and score.
Each mock = **narrative (~40 min, including a code snippet)** + **5 generic questions (~12 min)** + your questions (~3 min).
The narratives are **new** (not S1–S6), so they test transfer, not recall.

---

## Rubric

Score 1–4 per attribute (4 = Strong Hire at Staff level).

| Attribute | 1 | 2 | 3 | 4 (Staff) |
|---|---|---|---|---|
| **System analysis & design** | Fixes random things; misses correctness gaps | Finds obvious gaps; fixes lack trade-offs | Systematic gap list, prioritised; sound fixes with trade-offs | + quantifies (QPS, cost), names failure modes and how to detect them, rollout/migration plan |
| **Connectivity** | Names patterns without mechanics | Knows retries/timeouts but misses idempotency/limits/partial results | Correct protocol choice, error model, auth, retries, idempotency, pagination | + supplier economics (cost/quota), backpressure, reconciliation, standardised client library |
| **QA** | "Write unit tests" | Lists levels without the why | Maps tests to failure modes; justifies cost vs benefit; covers NFRs | + shift-right (canary, flags, synthetic), contract strategy for externals, quality metrics |
| **Code review** | Style nits; misses security | Finds some real bugs, unprioritised | Catches security/integrity/reliability issues, prioritised, with fixes | + refactor shape (strategy/DI), tone, how to prevent recurrence (lint rules, libraries) |
| **Communication** | Rambling or silent; needs prompting | Understandable but unstructured | Signposted, concise, checks in, adapts to questions | + crisp summaries, handles pushback gracefully, explains to non-technical listeners |

**Pass bar for Staff:** ≥ 3 in every attribute and at least two 4s. Log scores in [PROGRESS.md](PROGRESS.md).

---

## Mock 1: Car-rental availability aggregator

**Narrative prompt:**
> We're adding car rentals. We integrate 3 rental suppliers. Users search by pickup location and time; we show cars from all suppliers, then book. Supplier A has a REST API with 5 req/s per API key. Supplier B uses SOAP and is slow (p99 4 s). Supplier C offers webhooks for availability changes. Here's our first version.

```mermaid
flowchart LR
    W[Web/App] -->|GET /cars?loc&time| CS[Car service]
    CS -->|for each supplier| A[Supplier A REST]
    CS --> B[Supplier B SOAP]
    CS --> Cc[Supplier C REST]
    Cc -.->|webhook POST /hook| CS
    CS --> DB[(Postgres)]
```
**Code snippet (shown at ~minute 25):**
```java
@PostMapping("/hook")
public void hook(@RequestBody String body) {
    JsonNode n = new ObjectMapper().readTree(body);
    jdbc.update("UPDATE cars SET available=" + n.get("available") + " WHERE id='" + n.get("carId").asText() + "'");
}

@GetMapping("/cars")
public List<Car> cars(String loc, String time) {
    List<Car> all = new ArrayList<>();
    all.addAll(supplierA.search(loc, time));
    all.addAll(supplierB.search(loc, time));
    all.addAll(supplierC.search(loc, time));
    return all;
}
```
**Generic questions:** (1) REST vs gRPC for internal pricing calls? (2) How do you test a circuit breaker? (3) JWT vs sessions? (4) What do you block a PR for? (5) Explain backpressure to a PM.

<details><summary>Interviewer notes (open after the mock)</summary>

Expected: sequential fan-out → parallel with a deadline + partial results; **B is slow** → its own bulkhead + timeout, or async/progressive results, plus a cache; **A's 5 req/s limit** → a shared token bucket across instances (one key = global limit), caching, maybe more keys by contract; **C webhooks** → verify the signature, timestamp, dedupe, ordering (version), ack fast + queue, a reconciliation poll; the webhook code has **SQL injection**, no auth/signature, an `ObjectMapper` per call, no validation (null `available`), no error handling, synchronous DB write (fine if fast, but enqueue at scale); `/cars` has no pagination, no dedupe, no timeouts, sequential calls, verbs are fine but no versioning; car availability for a *time range* (a model issue); booking: hold → confirm with the supplier, idempotency. Tests: Toxiproxy on B, limiter test for A, webhook replay/order tests, contract fixtures for SOAP.
</details>

---

## Mock 2: Multi-currency price display service

**Narrative prompt:**
> Every price on Agoda is shown in the user's currency. A Currency service fetches exchange rates from an external FX provider and converts prices for the search, property and checkout pages. During last month's provider outage, **checkout was down for 40 minutes**, and finance reports **small mismatches** between charged and displayed amounts.

```mermaid
flowchart LR
    SP[Search page svc] -->|convert each price| CUR[Currency service]
    PP[Property page svc] --> CUR
    CO[Checkout svc] --> CUR
    CUR -->|GET /rates on every call| FX[External FX provider]
```
**Code snippet:**
```python
class CurrencyService:
    def convert(self, amount: float, frm: str, to: str) -> float:
        rates = requests.get(f"https://fx.example.com/latest?key=ABC123&base={frm}").json()["rates"]
        return round(amount * rates[to], 2)
```
**Generic questions:** (1) Design a retry policy. (2) Offset vs cursor pagination. (3) How do you test a DB migration? (4) Contract testing: what and why? (5) How would you drive adoption of a shared library across teams?

<details><summary>Interviewer notes</summary>

Expected: **an external call per conversion** (every search result price!) → a rates cache refreshed on a schedule (every minute), served from memory, **last-known-good** fallback with a staleness limit + alert → the outage no longer takes down checkout. Chatty API → a batch convert API, or ship rates to callers (a client library with a local cache). **Mismatches**: float maths and rounding at different steps/places; display rates vs charge rates differ in time → use decimals/minor units, a single rounding policy (banker's?), **lock the rate at checkout** (a quote with an ID + expiry, used at charge time), store the rate used with the booking (audit). Second FX provider for redundancy, compared to detect bad data (a sanity bound on rate jumps). Code: hardcoded key in the URL, no timeout, no status check, a new connection per call, a KeyError on an unknown currency, float. Tests: property-based rounding tests, provider-down chaos test (checkout still works on cached rates), rate-quote expiry tests, reconciliation report charged vs displayed.
</details>

---

## Mock 3: Payment routing across multiple PSPs

**Narrative prompt:**
> We charge customers through two payment providers (PSP-1 and PSP-2) to get better acceptance rates and redundancy. The routing service picks a PSP per transaction. Customers report **double charges after "payment failed" messages**, and when PSP-1 degraded last week, **all traffic still went to it**.

```mermaid
flowchart LR
    CO[Checkout] -->|POST /pay| R[Payment router]
    R -->|70%| P1[PSP-1]
    R -->|30%| P2[PSP-2]
    P1 -.->|webhook result| R
    P2 -.->|webhook result| R
    R --> DB[(payments)]
```
**Code snippet:**
```go
func (r *Router) Pay(ctx context.Context, req PayReq) (string, error) {
    psp := r.p1
    if rand.Intn(100) >= 70 { psp = r.p2 }
    res, err := psp.Charge(context.Background(), req.CardToken, req.Amount)
    if err != nil {
        other := r.p2
        if psp == r.p2 { other = r.p1 }
        res, err = other.Charge(context.Background(), req.CardToken, req.Amount)
    }
    if err != nil { return "", errors.New("payment failed") }
    return res.ID, nil
}
```
**Generic questions:** (1) How does a circuit breaker work? (2) Saga: orchestration vs choreography? (3) What non-functional tests before a campaign? (4) Code review on a senior's PR who disagrees? (5) Strong vs eventual consistency with travel examples.

<details><summary>Interviewer notes</summary>

Expected: **failover after an ambiguous error = double charge**. A timeout from PSP-1 doesn't mean it failed; retrying on PSP-2 charges twice → only fail over on *definitive* failures (connection refused before send, explicit declines that are retryable elsewhere); on timeouts, **query PSP-1 by idempotency key/reference** first. **No idempotency keys** to the PSPs (each supports them) → use the payment attempt ID. `context.Background()` drops the request deadline/cancellation → pass `ctx`, with per-call timeouts. **Static 70/30 routing** → health-aware routing: per-PSP breaker, success-rate/latency-based weights, BIN/currency/cost-based rules, manual kill switch. A payment state machine persisted *before* calling (PENDING → AUTHORIZED/FAILED/UNKNOWN), webhook results reconcile states (verify signatures, dedupe, ordering), a reconciler for UNKNOWN, daily settlement reconciliation. The error message loses detail (decline vs technical) → typed errors for UX ("card declined" vs "try again"). Tests: timeout-then-success on PSP-1 must not charge PSP-2; webhook-before-response race; breaker opens on degradation and traffic shifts; load at peak; PSP sandbox contract tests. Metrics: auth rate per PSP, latency, unknown-state count, double-charge detector.
</details>
