# Connectivity Management & API Integration

> The round's most important area. A Gurugram SSE on your track was rejected specifically because *"connectivity management area is not strong"* ([00-Round-Intel §3](00-Round-Intel.md#3-why-people-failed-or-got-down-levelled)).
> At Agoda, "connectivity" means **talking to external suppliers** (hotel chains, channel managers, flight consolidators, payment providers) and to **partners** who call you. It covers **how data moves (protocol, push/pull), how it fails (timeouts, retries, limits), and how it stays secure (auth, signing)**.

Each topic: 🧠 **anchor** (one line to remember) → ⚙️ **mechanics** (how it works underneath, which the recruiter explicitly wants) → 🏗 **Agoda example** → ⭐ **Staff line** (trade-off, cost, or what you'd standardise).
Masterclass cross-links (`SD/…` = [System Design/Arpit-Masterclass](../../System%20Design/Arpit-Masterclass/README.md)): polling/WebSockets/SSE and queues vs streams → `SD/01-02`; locks → `SD/02-01`, `SD/03-01`; caching → `SD/05-01`.

**Contents:** [0 How to speak 60 s](#0-how-to-speak-for-60-seconds-use-this-on-every-section) · [1 Protocols](#1-protocols-rest-vs-grpc-vs-graphql) · [2 Sync vs async](#2-sync-vs-async-and-the-4-ways-to-get-data-from-someone-else) · [3 Supplier integration](#3-integrating-with-external-suppliers-the-core-agoda-problem) · [4 Timeouts](#4-timeouts-and-deadline-propagation) · [5 Retries](#5-retries-backoff-jitter-budgets) · [6 Idempotency](#6-idempotency) · [7 Breaker/bulkhead](#7-circuit-breaker-and-bulkhead) · [8 Rate limits](#8-rate-limiting-and-quotas) · [9 Backpressure](#9-backpressure-and-load-shedding) · [10 Partial responses](#10-partial-responses-in-fan-out) · [11 Pagination](#11-pagination) · [12 Errors](#12-error-model) · [13 Auth](#13-authentication-and-authorisation) · [14 Webhooks](#14-webhooks-done-right) · [15 Outbox/saga](#15-outbox-and-saga-reliable-multi-step-flows) · [16 API design checklist](#16-api-contract-checklist) · [17 Versioning](#17-versioning-and-evolution) · [18 Observability](#18-observability-for-connectivity) · [19 HTTP mechanics](#19-http-mechanics-worth-knowing-cold)

---



## 0. How to speak for 60 seconds (use this on every section)

🔑 **Char K: Kya → Kaise → Kahan → Keemat.** (What → How → Where at Agoda → Cost/trade-off.) Roughly 10 s + 25 s + 10 s + 15 s.


| Beat              | Opening phrase to say out loud                                                                                                                                        | Fill with                                        |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------ |
| **Kya** (what)    | "In one line, …" / "The core idea is …"                                                                                                                               | the 🧠 anchor                                    |
| **Kaise** (how)   | "Underneath, what actually happens is …" / "Mechanically, …"                                                                                                          | 2–3 ⚙️ points, not all of them                   |
| **Kahan** (where) | "Concretely, at Agoda this shows up when …"                                                                                                                           | the 🏗 example (hotel search, booking, supplier) |
| **Keemat** (cost) | "The trade-off is X versus Y." → "I'd know it's working by watching …" → "At platform level I'd make it a default in the shared client, so teams don't hand-roll it." | the ⭐ line: trade-off + metric + standardise     |


**Phrases for when your mind goes blank** (they buy 3 seconds and keep you structured):

- "Let me structure this in three parts." · "Two things matter here: … and …"
- "Where this breaks is …" · "The failure mode to watch is …"
- "This buys us X at the cost of Y."
- "Let me step back: the key point is …" (recovering after a tangent)
- "That's right for search, but wrong for booking." (shows you think per endpoint)

Each section below ends with 🗣 **Say it** (the English core of your 60 s) and 🔑 **Yaad rakho** (a short Hindi hook for your own memory; never say it in the interview).

## 1. Protocols: REST vs gRPC vs GraphQL

🧠 **REST for public/partner APIs, gRPC for internal service-to-service, GraphQL for client-driven aggregation (BFF).**


|              | REST (JSON/HTTP)                                                          | gRPC (Protobuf/HTTP/2)                                                                                                                               | GraphQL                                                                                                                         |
| ------------ | ------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| ⚙️ How       | Resources + verbs, text JSON, usually HTTP/1.1 (or 2)                     | IDL (`.proto`) → generated stubs, binary protobuf, **HTTP/2 multiplexed streams**, deadlines built in, 4 modes (unary, server/client/bidi streaming) | Single endpoint, client sends a query naming fields; server resolves each field via resolvers                                   |
| Strengths    | Universal, cacheable (HTTP caching, CDN), easy to debug, browser-friendly | Fast (smaller payloads, no JSON parsing), strict contract, streaming, deadline propagation                                                           | No over/under-fetching, one round trip for nested data, schema introspection                                                    |
| Weaknesses   | Over/under-fetching, loose contracts unless OpenAPI                       | Not browser-native (needs gRPC-Web), harder to debug, L7 LB needed (long-lived HTTP/2 connections defeat L4 balancing)                               | **N+1 resolver problem** (fix: DataLoader batching), hard to cache over HTTP, query cost attacks (need depth/complexity limits) |
| Use at Agoda | Partner/supplier APIs, public APIs                                        | Search → pricing → availability internal calls                                                                                                       | Mobile/web BFF composing property + price + reviews                                                                             |


⭐ *"Internally I'd standardise on gRPC with deadlines for the hot path, REST + OpenAPI at the edge for partners. Partn*If I have to choose from protocols, we have different protocols, mainly REST versus gRPC versus GraphQL. REST is generally used for public or partner APIs. gRPC is used for internal service-to-service communication, and GraphQL is generally used for client-driven aggregations, which we can call BFF (backend for frontend). How all of these work:

- REST works with resources, which are generally verbs and text, plus a JSON reply. For insertion, or for sending data, we can use the JSON format, and it usually uses the HTTP protocol.
- gRPC uses an interface definition language, which actually uses protobufs. They are generating stubs, and we are transferring data using those binary formats, which are called protobufs. We are using the HTTP protocol again, but HTTP/2, and there are multiple streams. There are multiple modes in gRPC.
- GraphQL has single endpoints. The client sends a query with named fields, and the server resolves each field using resolvers and sends the data back.

 If we talk about the strengths of each:

- REST is universal. It has been used for a long time. We can cache the results, use HTTP caching, and use CDNs (content delivery networks). They're easy to manage, browser-friendly, and easily debuggable as well.
- gRPC is usually fast because of smaller payloads. We don't send the overhead data that is sent in REST, so that's why they are faster. We don't have to parse JSON and everything. We have a strict contract between services, and propagation is faster.
- In GraphQL, there is no over- or under-fetching. One round trip will only fetch the nested data that it requires, so the schema is important over here.

 If we talk about the cons or weaknesses:

- With REST, we can over- or under-fetch some things, depending upon the contracts between the APIs that we have.
- gRPCs are not browser-native. They need gRPC Web. They are harder to debug, and they need long-lived connections.

 We would require L7 load balancers, which can actually look into the presentation layer as well and look into what the payload actually contains from the headers and everything. People generally use them at partner or supplier APIs or for public APIs. This is for REST. For gRPCs, we can use these for internal service-to-service calling, for example, search services calling the pricing API and these kinds of calls. For GraphQL, these would be helpful in mobile or web BFF, composing property, price, reviews, etc.*ers can't be forced onto gRPC, and HTTP caching matters there."* Mention **contract-first** (OpenAPI/proto in a repo, generated clients, breaking-change checks in CI: `buf breaking`, `openapi-diff`).

> 🗣 **Say it:** "REST at the edge for partners, gRPC inside for speed and built-in deadlines, GraphQL only as a BFF for the apps. Contracts live in a repo, and CI fails on a breaking change."
>
> 👀 **See it in code:** [02a §1 gRPC](02a-Connectivity-See-It.md#1-grpc-what-you-actually-write)
>
> 🔑 **Yaad rakho:** *Bahar REST, andar gRPC, app ke liye GraphQL.* · *Contract pehle, code baad mein.*



## 2. Sync vs async, and the 4 ways to get data from someone else

🧠 **Sync when the caller needs the answer now; async when it only needs to know it'll happen.**


| Pattern                                | ⚙️ Mechanism                                   | Use when                                              | Watch out                                                                            |
| -------------------------------------- | ---------------------------------------------- | ----------------------------------------------------- | ------------------------------------------------------------------------------------ |
| **Short polling**                      | Client asks every N s                          | Supplier has no push; changes are moderately frequent | Wasted calls (cost on metered APIs), latency up to N                                 |
| **Long polling**                       | Server holds the request until data or timeout | Near-real-time without WebSockets                     | Connection held per client                                                           |
| **Webhooks**                           | Provider POSTs to your URL on change           | Provider supports it, events are sparse               | Must verify signature, dedupe, handle out-of-order, endpoint must be up (they retry) |
| **Pub/Sub / streams** (Kafka, SNS/SQS) | Producer publishes, many consumers subscribe   | Internal fan-out, decoupling, replay (Kafka)          | At-least-once → idempotent consumers; ordering only per partition                    |
| SSE / WebSockets                       | Server pushes over a held connection           | Pushing to *browsers* (price alerts)                  | Sticky connections, reconnect storms                                                 |


Queue vs stream (`SD/01-02`): a **queue** (SQS, RabbitMQ) deletes on ack, one consumer per message, good for work distribution. A **stream** (Kafka) is a retained log, consumer groups track offsets, replayable, ordered per partition, good for event fan-out and rebuilding state.

⭐ *"Sync calls couple availability: if A calls B calls C synchronously, A's availability is roughly the product. I'd keep the user path short and synchronous, and move everything else (supplier confirmation, emails, analytics) behind a queue."*

> 🗣 **Say it:** "If the caller needs the answer now, call synchronously; if it only needs to know it will happen, put it on a queue. Every synchronous hop multiplies the failure chance, so I keep the user path short."
>
> 🔑 **Yaad rakho:** *Abhi chahiye toh sync, baad mein chalega toh queue.* · *Har sync hop = availability ka guna.* · 4 tareeke: *poochte raho (poll), ruk ke poochho (long poll), woh batayega (webhook), sabko batao (pub/sub).*



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

> 🗣 **Say it:** "A slow, metered, unreliable supplier never sits on the hot path. One adapter per supplier into a canonical model; cache with TTL by volatility; refresh popular items more often; coalesce duplicate calls; and re-check the price live at booking. The trade-off is freshness versus supplier cost versus latency."
>
> 👀 **See it in code:** [02a §3 coalescing](02a-Connectivity-See-It.md#3-request-coalescing-the-supplier-cost-saver)
>
> 🔑 **Yaad rakho:** *Dekhna cache se, khareedna live se.* · *Jo zyada dikhta hai, woh zyada refresh.* · *Sau log, ek call (coalescing).*



## 4. Timeouts and deadline propagation

🧠 **Every remote call has a timeout; every request has a deadline; children get what's left.**

⚙️

- Separate **connect timeout** (short, ~100–500 ms) and **read/response timeout** (based on the dependency's p99, e.g. p99 × 1.5).
- **Deadline propagation**: the incoming request has a budget (search = 1 s). Each downstream call gets `min(own timeout, remaining budget − safety margin)`. gRPC does this natively (`grpc-timeout` header); in HTTP pass it in a header, or use Go's `context.WithTimeout` / Java `CompletableFuture.orTimeout`.
- Without timeouts, a slow dependency holds threads/connections until the pool is exhausted → **cascading failure**.
- The default timeout in many HTTP clients is **infinite** (Java's old `HttpURLConnection`, Python `requests` with no `timeout=`). A classic review catch.

⭐ *"Timeouts are a product decision: 'after 800 ms we show what we have'. I'd set them from measured p99s and alert when the timeout rate rises."*

> 🗣 **Say it:** "Every remote call has a timeout, every request has a deadline, and each child call gets only what's left. Without that, one slow dependency holds threads until the pool is empty, and the failure cascades."
>
> 👀 **See it in code:** [02a §4 deadlines](02a-Connectivity-See-It.md#4-timeouts-and-deadline-propagation)
>
> 🔑 **Yaad rakho:** *Bachcha utna hi lega jitna bacha hai.* · *Bina timeout ka call = khula nal.*



## 5. Retries, backoff, jitter, budgets

🧠 **Retry only what's safe (idempotent) and only what's transient; back off exponentially with jitter; cap the total.**

⚙️

- **Retryable:** connection errors, timeouts, 502/503/504, **429 (honour** `Retry-After`**)**. **Not retryable:** 400, 401/403, 404, 409, 422 (retrying won't fix them).
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

⭐ *"I'd put retry policy in a shared client library with budgets and metrics, so teams don't hand-roll* `for i < 3` *loops that turn into retry storms."*

> 🗣 **Say it:** "Retry only transient errors, and only on idempotent calls: exponential backoff with full jitter, two or three attempts inside the deadline, at one layer only, under a retry budget of about ten percent."
>
> 👀 **See it in code:** [02a §5 retries](02a-Connectivity-See-It.md#5-retries-backoff-jitter-budgets)
>
> 🔑 **Yaad rakho:** *Retry tabhi jab safe ho aur galti temporary ho.* · *Teen layer × teen retry = sattais call.* · *Jitter = sab ek saath wapas na aayein.*



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

> 🗣 **Say it:** "Same request twice has the effect of once, which is what makes retries safe. For POST bookings the client sends an Idempotency-Key; the server stores it under a unique constraint in the same transaction as the booking, and a duplicate gets the stored response. If a supplier call times out, I query by my reference before retrying."
>
> 👀 **See it in code:** [02a §6 idempotency](02a-Connectivity-See-It.md#6-idempotency)
>
> 🔑 **Yaad rakho:** *Do baar bhejo, ek baar ho.* · *Timeout aaya? Pehle poochho "hua ya nahi", phir retry.* · *Idempotency = ek user ka retry; locking = do user, ek kamra.*



## 7. Circuit breaker and bulkhead

🧠 **Breaker: stop calling what's broken. Bulkhead: one broken thing can't sink the ship.**

⚙️

- **Circuit breaker** states: **Closed** (calls flow; count failures in a rolling window) → if the error rate > threshold (e.g. 50% over ≥20 calls) → **Open** (fail fast, return fallback/partial, no calls) → after a cool-down → **Half-open** (let a few trial calls through; success → Closed, failure → Open). Libraries: Resilience4j (JVM), Polly (.NET), gobreaker / sony (Go).
- **Bulkhead**: a separate bounded pool/semaphore **per dependency**, so supplier A hanging can use at most its 20 slots and can't eat the threads serving supplier B or the DB.
- **Fallbacks**: cached/stale data (mark it as such), default, or omit with `partial: true`.

⭐ *"Breakers per supplier and per endpoint, not global. A breaker opening is an incident signal: page on breaker-open duration for top suppliers."*

> 🗣 **Say it:** "A circuit breaker stops calling a dependency that's failing and fails fast with a fallback; after a cool-down, half-open lets a few trial calls through. A bulkhead gives each supplier its own bounded pool, so one hanging supplier can't eat everyone's threads."
>
> 👀 **See it in code:** [02a §7 breaker/bulkhead](02a-Connectivity-See-It.md#7-circuit-breaker-and-bulkhead)
>
> 🔑 **Yaad rakho:** *Breaker: tooti cheez ko baar baar mat chhedo.* · *Bulkhead: ek kamre mein paani, poora jahaaz nahi doobega.* · *Switch jaisa: closed = bijli chalu (calls flow), open = kat gayi.*



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

> 🗣 **Say it:** "Inbound, I rate-limit to protect us: a token bucket per API key, 429 with Retry-After. Outbound, I shape calls under each supplier's limit, and on metered APIs that's really cost control, tied to the contract and the monthly budget."
>
> 🔑 **Yaad rakho:** *Andar aane walon se bachao, bahar jaane mein izzat karo.* · *Token bucket: tokens bharte rehte, burst tak chalega.*



## 9. Backpressure and load shedding

🧠 **When you can't keep up, push back early instead of falling over late.**

⚙️

- **Bounded everything**: queues, thread pools, connection pools, in-flight requests. An unbounded queue just converts overload into latency, then into OOM.
- **Signals upstream**: `429`/`503 + Retry-After`, gRPC `RESOURCE_EXHAUSTED`, TCP flow control/HTTP/2 window, Kafka consumer lag (consumers pull at their own pace, which is natural backpressure), reactive streams `request(n)`.
- **Load shedding**: reject the lowest-priority work first (prefetch/refresh jobs before user searches, search before booking). Adaptive concurrency limits (Netflix `concurrency-limits`, Envoy adaptive concurrency) use latency as the signal.
- **Consumer side**: pause/slow consumption when the downstream (DB, supplier) is slow; don't keep pulling into memory.

🏗 Supplier refresh workers read from a queue. If supplier A rate-limits, the workers for A slow down (token bucket blocks). Lag grows on A's partition only, and user searches still serve cached data.

> 🗣 **Say it:** "When we can't keep up, we push back early instead of falling over late: bounded queues and pools, 429 or 503 to the caller, and shed the lowest-priority work first, so background refresh goes before user search, and search goes before booking."
>
> 🔑 **Yaad rakho:** *Jaldi mana karo, der se girne se behtar.* · *Unbounded queue = pehle latency, phir OOM.*



## 10. Partial responses in fan-out

🧠 **Return what you have by the deadline; say what's missing.**

⚙️ Fan out concurrently (Go `errgroup` with context, Java `CompletableFuture.allOf` with `orTimeout`), collect results until the deadline, cancel stragglers:

```json
{ "results": [ ... ], "partial": true,
  "sources": { "supplierA": "ok", "supplierB": "timeout", "supplierC": "circuit_open" } }
```

HTTP 200 (with the flag), **not 500**, and not 206 (that's for byte ranges). Optionally the client polls/streams for late results (progressive loading, as flight metasearch sites do).

⭐ *"Partial results trade completeness for latency. That's right for search, wrong for booking. I'd make the policy explicit per endpoint and track the partial-response rate per supplier as an SLI."*

> 🗣 **Say it:** "In a fan-out I return what I have by the deadline and say what's missing: 200 with partial: true and a status per supplier, never a 500. That's right for search, wrong for booking, and I track the partial rate per supplier."
>
> 🔑 **Yaad rakho:** *Jo mila woh do, jo nahi mila woh batao.* · *Search mein adhoora chalega, booking mein nahi.*



## 11. Pagination

🧠 **Never return unbounded lists. Offset is simple but slow and unstable; cursor is fast and stable.**


|                            | Offset/limit (`?page=5&size=50`)                                  | Cursor/keyset (`?after=eyJpZCI6...&limit=50`)                                     |
| -------------------------- | ----------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| ⚙️ DB                      | `OFFSET 10000 LIMIT 50` scans and discards 10,000 rows: O(offset) | `WHERE (price, id) > (?, ?) ORDER BY price, id LIMIT 50` uses the index: O(limit) |
| Concurrent inserts/deletes | Items skipped or duplicated between pages                         | Stable                                                                            |
| Jump to page N             | Yes                                                               | No (next/prev only)                                                               |
| Use                        | Small admin lists                                                 | Feeds, search results, sync/export APIs, supplier pulls                           |


- The cursor is **opaque** (base64 of the last sort key + id, optionally signed) so clients can't build it and you can change it later.
- Always **cap** `limit` server-side (e.g. max 100) and set a default.
- Return `next_cursor` (null at the end); total counts are expensive, so make them optional/approximate.
- **Consuming** a paginated supplier API: follow cursors with a page cap and checkpointing (resume after a crash), respect rate limits between pages.

> 🗣 **Say it:** "Never return an unbounded list. Offset scans and throws away rows and shifts when data changes; a cursor seeks through the index and stays stable. The cursor is opaque, and the server caps the limit."
>
> 🔑 **Yaad rakho:** *Offset = gin gin ke chhodo; cursor = jahan ruke, wahin se shuru.*



## 12. Error model

🧠 **Right status code, machine-readable body, a clear retryable-or-not signal.**

⚙️

- **4xx = client's fault, don't retry as-is:** 400 validation, 401 unauthenticated, 403 forbidden, 404, 409 conflict (e.g. sold out, version mismatch), 412 precondition failed (ETag), 422 semantic error, 429 rate limited.
- **5xx = server's fault, maybe retry:** 500, 502 bad gateway (upstream bad), 503 unavailable (+`Retry-After`), 504 upstream timeout.
- Body: **RFC 7807 / 9457 Problem Details**: `{"type": "https://…/sold-out", "title": "Room sold out", "status": 409, "detail": "...", "instance": "/bookings/123", "traceId": "…"}`. Stable `type`/`code` for clients to branch on; never stack traces or SQL errors (information leak).
- Map **supplier errors into your own model** in the adapter (their `ERR_7731` → your `SUPPLIER_UNAVAILABLE`, retryable).
- gRPC: use canonical codes (`UNAVAILABLE` retryable, `INVALID_ARGUMENT`, `DEADLINE_EXCEEDED`, `RESOURCE_EXHAUSTED`).

> 🗣 **Say it:** "Right status code, a machine-readable Problem Details body with a stable code, and a clear retryable-or-not signal. 4xx means don't retry as-is; 5xx and 429 maybe. Supplier error codes get mapped to ours inside the adapter."
>
> 🔑 **Yaad rakho:** *4xx = teri galti, 5xx = meri galti, 429 = thoda ruko.*



## 13. Authentication and authorisation

🧠 **AuthN = who are you; AuthZ = what may you do. Different mechanisms for users, services, partners.**


| Caller                          | Mechanism                                                                                                             | ⚙️ Notes                                                                                                                                                                                       |
| ------------------------------- | --------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| End users (app/web)             | **OAuth2 / OIDC**, short-lived **JWT access token** + refresh token                                                   | JWT is signed (RS256/ES256), verified locally with the issuer's public key (JWKS) → no DB call. Downside: hard to revoke before expiry → keep it short (5–15 min) + a denylist for emergencies |
| Partners / suppliers calling us | **OAuth2 client-credentials** (scoped tokens) or **API key + HMAC request signing**; **mTLS** for high-trust partners | Keys per partner, rotatable, scoped; IP allow-lists as extra                                                                                                                                   |
| Us calling suppliers            | Whatever they offer (API key, OAuth2 CC, basic auth over TLS)                                                         | **Secrets in a vault/secret manager**, injected at runtime, rotated. Never in code or logs. Cache OAuth tokens until shortly before expiry (don't fetch a token per call)                      |
| Service-to-service (internal)   | **mTLS** via service mesh (SPIFFE IDs) + JWT for end-user context propagation                                         | Zero-trust: don't rely on "it's inside the VPC"                                                                                                                                                |
| Webhooks we receive             | HMAC signature + timestamp                                                                                            | §14                                                                                                                                                                                            |


- **AuthZ**: scopes/roles (RBAC), resource ownership checks ("can user X read booking Y?": the classic **IDOR** bug in code review), ABAC for complex policies.
- "**Robust, secure connectivity session**" (asked in a Bangkok report): TLS 1.2+ everywhere; token lifecycle (expiry, refresh, rotation, revocation); connection pooling + keep-alive to suppliers (reuse TLS sessions, avoid the handshake per call); retries on token expiry (`401` → refresh once → retry); clock-skew tolerance; audit logging.

> 🗣 **Say it:** "AuthN is who you are, AuthZ is what you may do. Users get short-lived JWTs through OAuth2, partners get client-credentials or HMAC-signed keys, internal services use mTLS. Secrets live in a vault, and every read checks ownership, which prevents IDOR."
>
> 🔑 **Yaad rakho:** *Kaun ho? (AuthN) → Kya kar sakte ho? (AuthZ).* · *Token ki umar chhoti.* · *Secret code mein nahi, vault mein.*



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

> 🗣 **Say it:** "Sign it, timestamp it, dedupe by event ID, ack fast and process async, retry with backoff, allow replay. And I keep a reconciliation poll, because webhooks get lost."
>
> 🔑 **Yaad rakho:** *Webhook pe bharosa, par poll se tasdeek.* · *Pehle "mil gaya" bolo, kaam baad mein.*



## 15. Outbox and saga: reliable multi-step flows

🧠 **You can't atomically write your DB and publish to Kafka, so write the event to your DB and publish it later.**

⚙️

- **Dual-write problem**: `db.save(booking); kafka.send(event)`. A crash between them gives a booking without an event, and the reverse order gives an event without a booking.
- **Transactional outbox**: in one DB transaction insert the booking **and** an `outbox` row. A relay (poller or CDC via Debezium) publishes outbox rows to Kafka, marks them sent. At-least-once → consumers dedupe by event ID.
- **Saga** for a multi-service booking (no distributed 2PC across suppliers/payments): steps with **compensations**: reserve room → charge card → confirm supplier. If confirm fails → refund + release.
  - **Orchestration** (a booking orchestrator/state machine drives the steps: easier to reason about and observe) vs **choreography** (services react to events: looser coupling, harder to follow).
  - Persist saga state; every step and compensation idempotent; timeouts for stuck steps; a **reconciliation job** for ambiguous states ("payment captured but supplier unknown").

⭐ *"For money flows I prefer orchestration with an explicit state machine and a daily reconciliation against the payment provider and suppliers. Reconciliation is what catches the bugs the design didn't."*

> 🗣 **Say it:** "I can't atomically write the DB and publish to Kafka, so I write the event to an outbox table in the same transaction and a relay publishes it later. For a multi-step booking I use a saga: every step has a compensation, an orchestrator drives it, and a daily reconciliation catches what the design missed."
>
> 🔑 **Yaad rakho:** *Do jagah ek saath likhna = jhagda; ek jagah likho, baad mein bhejo.* · *Saga: har kadam ka ulta kadam tayyar.*



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

> 🗣 **Say it:** "When I review an API I walk a checklist: resources and verbs, pagination, idempotency key, error model, auth, versioning, validation, rate limits, caching, async, batch, docs, tracing."
>
> 🔑 **Yaad rakho:** *Pehle naam aur verb, phir page, key, error, auth, version.*



## 17. Versioning and evolution

- **Additive changes are non-breaking** (new optional fields, new endpoints). Clients must **ignore unknown fields** (tolerant reader). Removing/renaming fields, changing types or semantics, or adding required fields is breaking.
- URI versioning (`/v2`) is simple and visible; header/media-type versioning is cleaner but harder to test. Protobuf: never reuse field numbers, use `reserved`.
- Deprecation: announce, a `Sunset` header, usage metrics per version, then remove.
- ⭐ Breaking-change detection in CI + **consumer-driven contract tests** (Pact) so a provider can't break a consumer silently ([03-QA-Testing §4](03-QA-Testing.md)).

> 🗣 **Say it:** "Adding is safe, removing or changing is breaking. Clients ignore unknown fields, CI blocks breaking changes, and consumer contract tests stop a provider breaking a consumer silently."
>
> 🔑 **Yaad rakho:** *Jodna safe, hatana ya badalna breaking.*



## 18. Observability for connectivity

🧠 **Per dependency, measure rate, errors, duration; trace across hops; log with a correlation ID.**

- **RED** per endpoint *and per supplier*: request rate, error rate (by class: timeout, 5xx, 429), latency p50/p95/p99. Also breaker state, retry count, cache hit ratio, queue lag, supplier spend/quota used.
- **Distributed tracing** (OpenTelemetry; W3C `traceparent` header propagated through HTTP, gRPC, Kafka headers): shows which supplier made the search slow.
- **Structured logs** (JSON) with trace ID, supplier, booking ID. **No PII/secrets/card data** (mask them).
- **SLOs**: e.g. search availability 99.9%, p99 < 1 s; booking success 99.95%. **Burn-rate alerts** instead of alerting on every spike.
- **Synthetic probes** against each supplier (and sandbox bookings) to catch breakage before users do.

> 🗣 **Say it:** "Per dependency I measure rate, errors and duration; I trace across hops; I log with a correlation ID; and I alert on SLO burn rate, not on every spike."
>
> 🔑 **Yaad rakho:** *Har supplier ka RED, har hop ka trace.*



## 19. HTTP mechanics worth knowing cold

- **Connection reuse**: TCP + TLS handshakes cost ~1–3 RTTs. Use a **pooled, long-lived client** (one `HttpClient` per app, not per request). Per-request clients cause socket exhaustion (`TIME_WAIT`) and latency: the "expensive initialisation per call" bug.
- **HTTP/1.1** keep-alive, one request at a time per connection (head-of-line blocking) · **HTTP/2** multiplexed streams over one connection, header compression (HPACK) · **HTTP/3** over QUIC/UDP, no TCP head-of-line blocking.
- **Caching headers**: `Cache-Control: max-age, no-store, private`, `ETag` + `If-None-Match` → 304, `Vary`.
- **Idempotent/safe methods** per the RFC (GET/HEAD/OPTIONS safe; PUT/DELETE idempotent).
- **Compression** (gzip/br) for big JSON; **keep payloads small** (field filtering, `fields=` param).
- **L4 vs L7 load balancing** (the reason gRPC "needs L7"):
  - **L4** (transport: IP + port; AWS NLB, kube-proxy / a plain Kubernetes `Service`) sees only TCP connections, so it picks a backend **once per connection** and then just forwards bytes. It's fast and cheap and works for any protocol (DBs, Kafka, TLS passthrough).
  - **L7** (application: HTTP; Envoy, NGINX, AWS ALB, Istio) terminates the connection, reads each request (path, headers, cookies) and picks a backend **per request**. It can route `/search` and `/book` separately and handle retries, auth, rate limits and canaries. It costs more CPU and has to terminate TLS.
  - **gRPC trap**: a client opens one HTTP/2 connection and multiplexes every call over it for hours. Behind L4, all of that client's calls land on one pod, and pods added on scale-up get nothing. Fix: L7 proxy/mesh, **client-side load balancing** (headless DNS + `round_robin`), or a server `MaxConnectionAge` so connections are recycled periodically.
  - **Sticky sessions** (affinity: a cookie at L7, a source-IP hash at L4) deliberately send the same client to the same server, because that server holds in-memory state. The cost is uneven load and lost state if the server dies. Prefer stateless servers with state in Redis/DB.
  - **Long-lived connections** (WebSocket/SSE) are sticky by nature. They need an L7 balancer that allows `Upgrade` and long idle timeouts, plus pub/sub (Redis/Kafka) so any server can reach the server holding a user's socket, and **jittered client reconnects** to avoid a reconnect storm when a server dies.

  > 🔑 **Yaad rakho:** *L4 lifafa dekhta hai, L7 chitthi padhta hai.* (L4 looks at the envelope, L7 reads the letter.) · *Ek connection, ek pod: gRPC ka jaal.* (One connection, one pod: the gRPC trap.)
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

> 🗣 **Say it:** "One pooled, long-lived HTTP client per app, never one per request, because each new TCP and TLS handshake costs round trips and per-request clients exhaust sockets."
>
> 🔑 **Yaad rakho:** *Ek client, poori app ke liye.*

