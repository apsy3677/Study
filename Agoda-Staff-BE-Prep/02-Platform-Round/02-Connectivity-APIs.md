# Connectivity Management & API Integration

> The round's most important area. A Gurugram SSE on your track was rejected specifically because *"connectivity management area is not strong"* ([00-Round-Intel §3](00-Round-Intel.md#3-why-people-failed-or-got-down-levelled)).
> At Agoda, "connectivity" means **talking to external suppliers** (hotel chains, channel managers, flight consolidators, payment providers) and to **partners** who call you. It covers **how data moves (protocol, push/pull), how it fails (timeouts, retries, limits), and how it stays secure (auth, signing)**.

Each topic: 🧠 **anchor** (one line to remember) → ⚙️ **mechanics** (how it works underneath, which the recruiter explicitly wants) → 🏗 **Agoda example** → ⭐ **Staff line** (trade-off, cost, or what you'd standardise).
Masterclass cross-links (`SD/…` = [System Design/Arpit-Masterclass](../../System%20Design/Arpit-Masterclass/README.md)): polling/WebSockets/SSE and queues vs streams → `SD/01-02`; locks → `SD/02-01`, `SD/03-01`; caching → `SD/05-01`.

**Contents:** [1 Protocols](#1-protocols-rest-vs-grpc-vs-graphql) · [2 Sync vs async](#2-sync-vs-async-and-the-4-ways-to-get-data-from-someone-else) · [3 Supplier integration](#3-integrating-with-external-suppliers-the-core-agoda-problem) · [4 Timeouts](#4-timeouts-and-deadline-propagation) · [5 Retries](#5-retries-backoff-jitter-budgets) · [6 Idempotency](#6-idempotency) · [7 Breaker/bulkhead](#7-circuit-breaker-and-bulkhead) · [8 Rate limits](#8-rate-limiting-and-quotas) · [9 Backpressure](#9-backpressure-and-load-shedding) · [10 Partial responses](#10-partial-responses-in-fan-out) · [11 Pagination](#11-pagination) · [12 Errors](#12-error-model) · [13 Auth](#13-authentication-and-authorisation) · [14 Webhooks](#14-webhooks-done-right) · [15 Outbox/saga](#15-outbox-and-saga-reliable-multi-step-flows) · [16 API design checklist](#16-api-contract-checklist) · [17 Versioning](#17-versioning-and-evolution) · [18 Observability](#18-observability-for-connectivity) · [19 HTTP mechanics](#19-http-mechanics-worth-knowing-cold)

---

## 1. Protocols: REST vs gRPC vs GraphQL

🧠 **REST for public/partner APIs, gRPC for internal service-to-service, GraphQL for client-driven aggregation (BFF).**

| | REST (JSON/HTTP) | gRPC (Protobuf/HTTP/2) | GraphQL |
|---|---|---|---|
| ⚙️ How | Resources + verbs, text JSON, usually HTTP/1.1 (or 2) | IDL (`.proto`) → generated stubs, binary protobuf, **HTTP/2 multiplexed streams**, deadlines built in, 4 modes (unary, server/client/bidi streaming) | Single endpoint, client sends a query naming fields; server resolves each field via resolvers |
| Strengths | Universal, cacheable (HTTP caching, CDN), easy to debug, browser-friendly | Fast (smaller payloads, no JSON parsing), strict contract, streaming, deadline propagation | No over/under-fetching, one round trip for nested data, schema introspection |
| Weaknesses | Over/under-fetching, loose contracts unless OpenAPI | Not browser-native (needs gRPC-Web), harder to debug, L7 LB needed (long-lived HTTP/2 connections defeat L4 balancing) | **N+1 resolver problem** (fix: DataLoader batching), hard to cache over HTTP, query cost attacks (need depth/complexity limits) |
| Use at Agoda | Partner/supplier APIs, public APIs | Search → pricing → availability internal calls | Mobile/web BFF composing property + price + reviews |

⭐ *"Internally I'd standardise on gRPC with deadlines for the hot path, REST + OpenAPI at the edge for partners. Partners can't be forced onto gRPC, and HTTP caching matters there."* Mention **contract-first** (OpenAPI/proto in a repo, generated clients, breaking-change checks in CI: `buf breaking`, `openapi-diff`).

## 2. Sync vs async, and the 4 ways to get data from someone else

🧠 **Sync when the caller needs the answer now; async when it only needs to know it'll happen.**

| Pattern | ⚙️ Mechanism | Use when | Watch out |
|---|---|---|---|
| **Short polling** | Client asks every N s | Supplier has no push; changes are moderately frequent | Wasted calls (cost on metered APIs), latency up to N |
| **Long polling** | Server holds the request until data or timeout | Near-real-time without WebSockets | Connection held per client |
| **Webhooks** | Provider POSTs to your URL on change | Provider supports it, events are sparse | Must verify signature, dedupe, handle out-of-order, endpoint must be up (they retry) |
| **Pub/Sub / streams** (Kafka, SNS/SQS) | Producer publishes, many consumers subscribe | Internal fan-out, decoupling, replay (Kafka) | At-least-once → idempotent consumers; ordering only per partition |
| SSE / WebSockets | Server pushes over a held connection | Pushing to *browsers* (price alerts) | Sticky connections, reconnect storms |

Queue vs stream (`SD/01-02`): a **queue** (SQS, RabbitMQ) deletes on ack, one consumer per message, good for work distribution. A **stream** (Kafka) is a retained log, consumer groups track offsets, replayable, ordered per partition, good for event fan-out and rebuilding state.

⭐ *"Sync calls couple availability: if A calls B calls C synchronously, A's availability is roughly the product. I'd keep the user path short and synchronous, and move everything else (supplier confirmation, emails, analytics) behind a queue."*

## 3. Integrating with external suppliers: the core Agoda problem

🧠 **Never put an expensive, slow, unreliable third party directly on your hot path. Cache what you can, fetch on schedule, re-validate at booking.**

This is the exact shape of the Gurugram and Bangkok narratives (metered flight APIs, no push).

⚙️ **Design:**
1. **Supplier adapter per supplier** (strategy/adapter pattern): each translates its API (REST/SOAP/XML, auth, pagination, error codes) into one canonical model. Adding a supplier = adding an adapter, not editing a switch statement.
2. **Pull model with smart scheduling** (no push available):
   - Refresh **popular** routes/hotels/dates often, the long tail rarely or on demand (**popularity-weighted polling**: search logs drive the schedule).
   - **TTL by field volatility**: static content (hotel name, photos, flight schedule) for days; availability/price for seconds to minutes.
   - **On-demand fetch** on a cache miss for a real user search, under a deadline, with **request coalescing** (100 users searching BKK→SIN for 1 Dec trigger *one* supplier call).
   - Prefer **batch / delta endpoints** ("changes since T") and **conditional requests** (`ETag`/`If-None-Match` → 304 costs less, or nothing) when the supplier offers them.
3. **Budget**: per-supplier call budget (calls/day ≈ money). Enforce with a token bucket. Measure **cost per search** and **look-to-book ratio per supplier**. Suppliers often contractually cap it.
4. **Normalise + dedupe**: map to canonical IDs (flight = carrier + number + date; hotel = mapping table, since supplier IDs differ). If the same item comes from several suppliers, keep all offers and **show the cheapest** (or rank by price + reliability).
5. **Look vs book**: search reads the cache (may be stale). **Booking re-checks price/availability live with that supplier**, then holds/reserves, then confirms. If the price changed, tell the user before charging.
6. **Resilience** on every supplier call: timeout, retry (idempotent only), circuit breaker, bulkhead, partial results (§4–§10).
7. **Webhooks if the supplier offers them**, polling as a safety net (webhooks get lost; reconcile periodically).

🏗 Hotel version: thousands of hotels via channel managers. ARI (availability, rates, inventory) updates often arrive as **push** from channel managers (they call *your* API), so here Agoda is the receiver: authenticate the partner, validate, idempotent upsert, ack fast, process async.

⭐ *"The trade-off is freshness vs supplier cost vs latency. I'd make it explicit with two metrics: 'price changed at booking' rate (staleness hurting users) and cost per 1,000 searches. Then tune TTLs per route tier with an experiment, not by guessing."*

## 4. Timeouts and deadline propagation

🧠 **Every remote call has a timeout; every request has a deadline; children get what's left.**

⚙️
- Separate **connect timeout** (short, ~100–500 ms) and **read/response timeout** (based on the dependency's p99, e.g. p99 × 1.5).
- **Deadline propagation**: the incoming request has a budget (search = 1 s). Each downstream call gets `min(own timeout, remaining budget − safety margin)`. gRPC does this natively (`grpc-timeout` header); in HTTP pass it in a header, or use Go's `context.WithTimeout` / Java `CompletableFuture.orTimeout`.
- Without timeouts, a slow dependency holds threads/connections until the pool is exhausted → **cascading failure**.
- The default timeout in many HTTP clients is **infinite** (Java's old `HttpURLConnection`, Python `requests` with no `timeout=`). A classic review catch.

⭐ *"Timeouts are a product decision: 'after 800 ms we show what we have'. I'd set them from measured p99s and alert when the timeout rate rises."*

## 5. Retries, backoff, jitter, budgets

🧠 **Retry only what's safe (idempotent) and only what's transient; back off exponentially with jitter; cap the total.**

⚙️
- **Retryable:** connection errors, timeouts, 502/503/504, **429 (honour `Retry-After`)**. **Not retryable:** 400, 401/403, 404, 409, 422 (retrying won't fix them).
- **Exponential backoff with full jitter:** `sleep = random(0, min(cap, base × 2^attempt))`. Jitter avoids synchronised retry waves (thundering herd) after an outage.
- **Max attempts** (2–3) and stay **within the deadline**.
- **Retry budget**: retries ≤ ~10% of requests (e.g. Finagle/Envoy budgets). Otherwise a dependency at 50% errors gets 3× load and never recovers: a **retry storm**.
- **Retry at one layer only.** If client, gateway and service all retry 3×, one failure becomes 27 calls (retry amplification).
- **Non-idempotent operations** (`POST /book`, `charge`) are retried only with an **idempotency key** (§6).
- **Hedged requests** (tail-latency trick): after p95 elapses, send a duplicate to another replica and take the first answer. Only for idempotent reads, at a budget.

```go
// Go sketch: exponential backoff with full jitter, bounded by ctx deadline
for attempt := 0; attempt < maxAttempts; attempt++ {
    resp, err := call(ctx)
    if err == nil || !retryable(err) { return resp, err }
    backoff := time.Duration(rand.Int63n(int64(min(capDelay, base<<attempt))))
    select {
    case <-time.After(backoff):
    case <-ctx.Done(): return nil, ctx.Err() // deadline wins
    }
}
```

⭐ *"I'd put retry policy in a shared client library with budgets and metrics, so teams don't hand-roll `for i < 3` loops that turn into retry storms."*

## 6. Idempotency

🧠 **Same request applied twice = applied once. It makes retries safe.**

⚙️
- Naturally idempotent: `GET`, `PUT` (full replace), `DELETE`. Not idempotent: `POST`, `PATCH` (generally).
- **Idempotency-Key pattern** (Stripe-style) for `POST /bookings`:
  1. Client generates a UUID per *logical* operation and sends `Idempotency-Key`.
  2. Server inserts `(key, request_hash, status=IN_PROGRESS)` with a **unique constraint**. If the insert conflicts → it's a duplicate:
     - same hash + completed → **return the stored response**;
     - same hash + in progress → `409` / retry-after;
     - different hash → `422` (key reuse with a different body).
  3. Do the work. Store the response with the key **in the same transaction** as the booking.
  4. TTL keys (e.g. 24 h–7 d).
- **Consumers** of at-least-once queues dedupe by **event ID** (processed-events table, unique constraint) or make the operation an upsert.
- **Downstream to suppliers**: pass *your* booking reference as their idempotency key/client reference if they support it. If not, before retrying a booking call that timed out, **query by reference** first ("did it go through?"). The ambiguous timeout is the hardest case.

🏗 Double booking ≠ double charge: idempotency protects against *the same user retrying*. Concurrency control (conditional update, row lock, supplier hold) protects against *two users wanting the last room* (`SD/02-01`).

```sql
-- concurrency: no oversell, no explicit lock needed
UPDATE inventory SET available = available - 1
WHERE room_type_id = ? AND date = ? AND available > 0;   -- 0 rows updated => sold out
```

⭐ *"Idempotency should be a platform feature, middleware that every write endpoint gets, not something each team remembers."*

## 7. Circuit breaker and bulkhead

🧠 **Breaker: stop calling what's broken. Bulkhead: one broken thing can't sink the ship.**

⚙️
- **Circuit breaker** states: **Closed** (calls flow; count failures in a rolling window) → if the error rate > threshold (e.g. 50% over ≥20 calls) → **Open** (fail fast, return fallback/partial, no calls) → after a cool-down → **Half-open** (let a few trial calls through; success → Closed, failure → Open). Libraries: Resilience4j (JVM), Polly (.NET), gobreaker / sony (Go).
- **Bulkhead**: a separate bounded pool/semaphore **per dependency**, so supplier A hanging can use at most its 20 slots and can't eat the threads serving supplier B or the DB.
- **Fallbacks**: cached/stale data (mark it as such), default, or omit with `partial: true`.

⭐ *"Breakers per supplier and per endpoint, not global. A breaker opening is an incident signal: page on breaker-open duration for top suppliers."*

## 8. Rate limiting and quotas

🧠 **Protect yourself (inbound) and respect others (outbound).**

⚙️ Algorithms:
- **Token bucket**: bucket of capacity B refills at R tokens/s; a request takes a token or is rejected. Allows bursts up to B. The most common choice.
- **Leaky bucket**: a queue drained at a fixed rate; smooths output (good for *outbound* to a strict supplier).
- **Fixed window** (simple, boundary bursts) / **sliding window log/counter** (accurate, more memory).
- **Distributed**: a counter in Redis with an atomic Lua script (`INCR` + `EXPIRE`, or the token-bucket state) keyed by `client_id`/`supplier`. Or local limits ≈ global/N per instance (cheaper, approximate).
- **Inbound** response: `429 Too Many Requests` + `Retry-After` + `X-RateLimit-Limit/Remaining/Reset` headers. Limit per API key / partner / IP; tiered quotas.
- **Outbound**: shape calls to each supplier under *their* limit (and your cost budget). Queue excess or serve from cache.

⭐ *"Outbound rate limiting is really cost control on metered APIs. I'd tie the limiter's budget to the supplier contract and finance's monthly spend, and alert at 80% of the monthly quota."*

## 9. Backpressure and load shedding

🧠 **When you can't keep up, push back early instead of falling over late.**

⚙️
- **Bounded everything**: queues, thread pools, connection pools, in-flight requests. An unbounded queue just converts overload into latency, then into OOM.
- **Signals upstream**: `429`/`503 + Retry-After`, gRPC `RESOURCE_EXHAUSTED`, TCP flow control/HTTP/2 window, Kafka consumer lag (consumers pull at their own pace, which is natural backpressure), reactive streams `request(n)`.
- **Load shedding**: reject the lowest-priority work first (prefetch/refresh jobs before user searches, search before booking). Adaptive concurrency limits (Netflix `concurrency-limits`, Envoy adaptive concurrency) use latency as the signal.
- **Consumer side**: pause/slow consumption when the downstream (DB, supplier) is slow; don't keep pulling into memory.

🏗 Supplier refresh workers read from a queue. If supplier A rate-limits, the workers for A slow down (token bucket blocks). Lag grows on A's partition only, and user searches still serve cached data.

## 10. Partial responses in fan-out

🧠 **Return what you have by the deadline; say what's missing.**

⚙️ Fan out concurrently (Go `errgroup` with context, Java `CompletableFuture.allOf` with `orTimeout`), collect results until the deadline, cancel stragglers:
```json
{ "results": [ ... ], "partial": true,
  "sources": { "supplierA": "ok", "supplierB": "timeout", "supplierC": "circuit_open" } }
```
HTTP 200 (with the flag), **not 500**, and not 206 (that's for byte ranges). Optionally the client polls/streams for late results (progressive loading, as flight metasearch sites do).

⭐ *"Partial results trade completeness for latency. That's right for search, wrong for booking. I'd make the policy explicit per endpoint and track the partial-response rate per supplier as an SLI."*

## 11. Pagination

🧠 **Never return unbounded lists. Offset is simple but slow and unstable; cursor is fast and stable.**

| | Offset/limit (`?page=5&size=50`) | Cursor/keyset (`?after=eyJpZCI6...&limit=50`) |
|---|---|---|
| ⚙️ DB | `OFFSET 10000 LIMIT 50` scans and discards 10,000 rows: O(offset) | `WHERE (price, id) > (?, ?) ORDER BY price, id LIMIT 50` uses the index: O(limit) |
| Concurrent inserts/deletes | Items skipped or duplicated between pages | Stable |
| Jump to page N | Yes | No (next/prev only) |
| Use | Small admin lists | Feeds, search results, sync/export APIs, supplier pulls |

- The cursor is **opaque** (base64 of the last sort key + id, optionally signed) so clients can't build it and you can change it later.
- Always **cap `limit`** server-side (e.g. max 100) and set a default.
- Return `next_cursor` (null at the end); total counts are expensive, so make them optional/approximate.
- **Consuming** a paginated supplier API: follow cursors with a page cap and checkpointing (resume after a crash), respect rate limits between pages.

## 12. Error model

🧠 **Right status code, machine-readable body, a clear retryable-or-not signal.**

⚙️
- **4xx = client's fault, don't retry as-is:** 400 validation, 401 unauthenticated, 403 forbidden, 404, 409 conflict (e.g. sold out, version mismatch), 412 precondition failed (ETag), 422 semantic error, 429 rate limited.
- **5xx = server's fault, maybe retry:** 500, 502 bad gateway (upstream bad), 503 unavailable (+`Retry-After`), 504 upstream timeout.
- Body: **RFC 7807 / 9457 Problem Details**: `{"type": "https://…/sold-out", "title": "Room sold out", "status": 409, "detail": "...", "instance": "/bookings/123", "traceId": "…"}`. Stable `type`/`code` for clients to branch on; never stack traces or SQL errors (information leak).
- Map **supplier errors into your own model** in the adapter (their `ERR_7731` → your `SUPPLIER_UNAVAILABLE`, retryable).
- gRPC: use canonical codes (`UNAVAILABLE` retryable, `INVALID_ARGUMENT`, `DEADLINE_EXCEEDED`, `RESOURCE_EXHAUSTED`).

## 13. Authentication and authorisation

🧠 **AuthN = who are you; AuthZ = what may you do. Different mechanisms for users, services, partners.**

| Caller | Mechanism | ⚙️ Notes |
|---|---|---|
| End users (app/web) | **OAuth2 / OIDC**, short-lived **JWT access token** + refresh token | JWT is signed (RS256/ES256), verified locally with the issuer's public key (JWKS) → no DB call. Downside: hard to revoke before expiry → keep it short (5–15 min) + a denylist for emergencies |
| Partners / suppliers calling us | **OAuth2 client-credentials** (scoped tokens) or **API key + HMAC request signing**; **mTLS** for high-trust partners | Keys per partner, rotatable, scoped; IP allow-lists as extra |
| Us calling suppliers | Whatever they offer (API key, OAuth2 CC, basic auth over TLS) | **Secrets in a vault/secret manager**, injected at runtime, rotated. Never in code or logs. Cache OAuth tokens until shortly before expiry (don't fetch a token per call) |
| Service-to-service (internal) | **mTLS** via service mesh (SPIFFE IDs) + JWT for end-user context propagation | Zero-trust: don't rely on "it's inside the VPC" |
| Webhooks we receive | HMAC signature + timestamp | §14 |

- **AuthZ**: scopes/roles (RBAC), resource ownership checks ("can user X read booking Y?": the classic **IDOR** bug in code review), ABAC for complex policies.
- "**Robust, secure connectivity session**" (asked in a Bangkok report): TLS 1.2+ everywhere; token lifecycle (expiry, refresh, rotation, revocation); connection pooling + keep-alive to suppliers (reuse TLS sessions, avoid the handshake per call); retries on token expiry (`401` → refresh once → retry); clock-skew tolerance; audit logging.

## 14. Webhooks done right

🧠 **Sign, timestamp, dedupe, ack fast, process async, retry with backoff, and let them replay.**

**Sending** (we notify partners):
- Payload + `X-Event-Id` + `X-Timestamp` + `X-Signature: HMAC-SHA256(secret, timestamp + "." + body)`.
- Delivery via queue + workers; retry on non-2xx/timeouts with exponential backoff over hours; **DLQ** after N attempts; a **replay** endpoint/UI; per-partner concurrency limits (one slow partner shouldn't block others); disable endpoints that fail for days and notify the partner.
- Events are **at-least-once and may arrive out of order** → include a version/sequence or `occurred_at`; consider "thin" events (ID only, partner fetches the latest state).

**Receiving** (supplier notifies us):
- Verify the signature with a **constant-time compare**; reject if the timestamp is older than ~5 min (**replay protection**).
- Dedupe by event ID; ack `2xx` fast, then enqueue (don't do slow work in the handler, or the sender times out and retries).
- Don't trust order: compare versions and ignore older updates.
- Keep a **reconciliation poll** as the safety net (webhooks get lost).

## 15. Outbox and saga: reliable multi-step flows

🧠 **You can't atomically write your DB and publish to Kafka, so write the event to your DB and publish it later.**

⚙️
- **Dual-write problem**: `db.save(booking); kafka.send(event)`. A crash between them gives a booking without an event, and the reverse order gives an event without a booking.
- **Transactional outbox**: in one DB transaction insert the booking **and** an `outbox` row. A relay (poller or CDC via Debezium) publishes outbox rows to Kafka, marks them sent. At-least-once → consumers dedupe by event ID.
- **Saga** for a multi-service booking (no distributed 2PC across suppliers/payments): steps with **compensations**: reserve room → charge card → confirm supplier. If confirm fails → refund + release.
  - **Orchestration** (a booking orchestrator/state machine drives the steps: easier to reason about and observe) vs **choreography** (services react to events: looser coupling, harder to follow).
  - Persist saga state; every step and compensation idempotent; timeouts for stuck steps; a **reconciliation job** for ambiguous states ("payment captured but supplier unknown").

⭐ *"For money flows I prefer orchestration with an explicit state machine and a daily reconciliation against the payment provider and suppliers. Reconciliation is what catches the bugs the design didn't."*

## 16. API contract checklist

When asked to "design/improve the API", walk this list:
1. **Resources and verbs**: nouns, plural (`/v1/bookings`), correct verbs (`GET` safe, `POST` create, `PUT` replace, `PATCH` partial, `DELETE`), and correct codes (`201 Created` + `Location`, `202 Accepted` for async).
2. **Pagination** (cursor) + filtering + sorting, with a max page size.
3. **Idempotency-Key** on non-idempotent writes.
4. **Error model** (RFC 7807) with stable codes.
5. **AuthN/Z**: scheme, scopes per endpoint, ownership checks.
6. **Versioning** (`/v1`, or a header) + deprecation policy.
7. **Validation**: types, ranges (check-in < check-out, ≤ 30 nights), and size limits.
8. **Rate limits** + headers.
9. **Caching**: `Cache-Control`, `ETag` for GETs; **optimistic concurrency** via `If-Match` for updates.
10. **Async operations**: `202` + status resource (`/v1/bookings/123/status`) or a webhook.
11. **Batch endpoints** to cut chattiness (`POST /v1/availability:batchGet` with up to 50 IDs).
12. **Documentation**: OpenAPI spec, examples, SDKs; contract tests.
13. **Observability**: `traceparent` / correlation-ID header in and out.

Example improved search + booking contract:
```
GET  /v1/flights/search?from=BKK&to=SIN&date=2026-12-01&pax=2&cursor=…&limit=50
  200 { results:[{offerId, flightKey, price:{amount:"123.40",currency:"USD"}, supplier, expiresAt}],
        partial:false, nextCursor:"…" }
POST /v1/bookings          Idempotency-Key: 6f1c…   Authorization: Bearer …
  body { offerId, passengers:[…], paymentToken }
  201 { bookingId, status:"CONFIRMED" }  | 202 { bookingId, status:"PENDING" }
  409 problem+json { type:".../price-changed", newPrice:{…} } | 409 sold-out
GET  /v1/bookings/{id}     (owner-only)
```
Note `amount` as a **string/decimal** (never float), `expiresAt` on offers (the price is valid for N minutes), and `offerId` instead of re-sending the price (so the client can't tamper with it).

## 17. Versioning and evolution
- **Additive changes are non-breaking** (new optional fields, new endpoints). Clients must **ignore unknown fields** (tolerant reader). Removing/renaming fields, changing types or semantics, or adding required fields is breaking.
- URI versioning (`/v2`) is simple and visible; header/media-type versioning is cleaner but harder to test. Protobuf: never reuse field numbers, use `reserved`.
- Deprecation: announce, a `Sunset` header, usage metrics per version, then remove.
- ⭐ Breaking-change detection in CI + **consumer-driven contract tests** (Pact) so a provider can't break a consumer silently ([03-QA-Testing §4](03-QA-Testing.md)).

## 18. Observability for connectivity

🧠 **Per dependency, measure rate, errors, duration; trace across hops; log with a correlation ID.**

- **RED** per endpoint *and per supplier*: request rate, error rate (by class: timeout, 5xx, 429), latency p50/p95/p99. Also breaker state, retry count, cache hit ratio, queue lag, supplier spend/quota used.
- **Distributed tracing** (OpenTelemetry; W3C `traceparent` header propagated through HTTP, gRPC, Kafka headers): shows which supplier made the search slow.
- **Structured logs** (JSON) with trace ID, supplier, booking ID. **No PII/secrets/card data** (mask them).
- **SLOs**: e.g. search availability 99.9%, p99 < 1 s; booking success 99.95%. **Burn-rate alerts** instead of alerting on every spike.
- **Synthetic probes** against each supplier (and sandbox bookings) to catch breakage before users do.

## 19. HTTP mechanics worth knowing cold
- **Connection reuse**: TCP + TLS handshakes cost ~1–3 RTTs. Use a **pooled, long-lived client** (one `HttpClient` per app, not per request). Per-request clients cause socket exhaustion (`TIME_WAIT`) and latency: the "expensive initialisation per call" bug.
- **HTTP/1.1** keep-alive, one request at a time per connection (head-of-line blocking) · **HTTP/2** multiplexed streams over one connection, header compression (HPACK) · **HTTP/3** over QUIC/UDP, no TCP head-of-line blocking.
- **Caching headers**: `Cache-Control: max-age, no-store, private`, `ETag` + `If-None-Match` → 304, `Vary`.
- **Idempotent/safe methods** per the RFC (GET/HEAD/OPTIONS safe; PUT/DELETE idempotent).
- **Compression** (gzip/br) for big JSON; **keep payloads small** (field filtering, `fields=` param).
- **Plain HTTP client basics** (the OA in some loops tested it): build the URL with query encoding, set headers, set timeouts, check the status before parsing, parse JSON, handle pagination, and close/release the response body.

```python
# Python: the correct-by-default supplier call
session = requests.Session()                       # one per process: connection pooling
session.mount("https://", HTTPAdapter(pool_maxsize=50))
def fetch(url, params, token):
    r = session.get(url, params=params, timeout=(0.3, 1.5),   # connect, read
                    headers={"Authorization": f"Bearer {token}"})
    if r.status_code == 429: raise Retryable(retry_after=r.headers.get("Retry-After"))
    if r.status_code >= 500: raise Retryable()
    r.raise_for_status()                           # 4xx: not retryable
    return r.json()
```
