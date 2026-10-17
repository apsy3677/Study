# Connectivity: See It (pictures + the smallest code)

> Companion to [02-Connectivity-APIs.md](02-Connectivity-APIs.md). That file says **what to say**; this one shows **what it actually looks like**, so the words stop being idioms.
> Each topic: 🖼 **picture** → 💻 **pseudocode** (Python-style, at most about 10 lines, numbered comments = the story you tell aloud) → 🧩 **C++ analogy** (your home ground) → 🔎 **spot it in real code** (the Java / Python / Go keywords you'll see in an interviewer's snippet, and what a *missing* one means) → 🗣 **say it**.
>
> The pseudocode skips locks and error plumbing on purpose. Where that matters, a `# real code:` line says what's missing.

**You don't need production gRPC experience to speak about it.** A Staff interviewer grades whether you understand the mechanism and its trade-off. Honest framing works better than bluffing:
> "I haven't run gRPC in production; my services were C++ and REST. But mechanically it works like this: …, and the trade-off I'd watch is …"

Never bluff a tool's config flags. Explain the mechanism.

**Contents:** [§1 gRPC](#1-grpc-what-you-actually-write) · [§3 Coalescing](#3-request-coalescing-the-supplier-cost-saver) · [§4 Timeouts and deadline propagation](#4-timeouts-and-deadline-propagation) · [§5 Retries](#5-retries-backoff-jitter-budgets) · [§6 Idempotency](#6-idempotency) · [§7 Breaker and bulkhead](#7-circuit-breaker-and-bulkhead)

---

## §1 gRPC: what you actually write

🖼 **Picture**
```
REST:  your code ── builds URL + JSON by hand ──► HTTP/1.1 ──► server parses JSON ──► your handler
                    (the contract is a doc / OpenAPI file; nothing forces both sides to agree)

gRPC:  pricing.proto ──(protoc compiler)──┬──► client STUB        (has a GetPrice(...) method)
                                          └──► server BASE CLASS  (you override GetPrice)
       your code ── stub.GetPrice(req) ──► protobuf bytes over ONE HTTP/2 connection ──► your override
                    (looks like a local function call; the compiler forces both sides to agree)
```

💻 **Step 1: the contract** (`pricing.proto`). Both teams compile against this one file.
```proto
syntax = "proto3";
service Pricing {
  rpc GetPrice     (PriceRequest) returns (PriceReply);         // unary: 1 request, 1 reply
  rpc StreamPrices (PriceRequest) returns (stream PriceReply);  // server streaming: 1 request, many replies
}
message PriceRequest { int64 hotel_id = 1; string date = 2; }
message PriceReply   { int64 hotel_id = 1; string amount = 2; string currency = 3; }
```
The `= 1`, `= 2` are **field numbers**. Only the numbers go on the wire, never the names. That's why payloads are small, and why you must **never reuse a field number** (old clients would misread it).

💻 **Step 2: the server** overrides the generated base class:
```python
class PricingService(PricingServicer):            # PricingServicer was generated from "service Pricing"
    def GetPrice(self, request, context):         # same name as "rpc GetPrice"
        return PriceReply(hotel_id=request.hotel_id, amount="123.40", currency="USD")
```

💻 **Step 3: the client** calls the stub like a local function:
```python
channel = grpc.insecure_channel("pricing:50051")   # 1. ONE channel per app = one HTTP/2 connection, reused
stub    = PricingStub(channel)                     # 2. generated from "service Pricing"
reply   = stub.GetPrice(PriceRequest(hotel_id=42, date="2026-12-01"),
                        timeout=0.3)               # 3. deadline 300 ms, sent on the wire as  grpc-timeout: 300m
# after 300 ms → raises an error with status DEADLINE_EXCEEDED
# real code: TLS instead of "insecure", and round_robin load balancing across pods (the L4 trap)
```

🧩 **The same names in each language.** You never write these; `protoc` generates them from the `.proto`:
| In the `.proto` | Python | Java (what you saw earlier) | C++ |
|---|---|---|---|
| `service Pricing` (server) | `PricingServicer` | `PricingGrpc.PricingImplBase` | `Pricing::Service` |
| `service Pricing` (client) | `PricingStub(channel)` | `PricingGrpc.newBlockingStub(channel)` | `Pricing::NewStub(channel)` |
| `rpc GetPrice` | `GetPrice` | `getPrice` | `GetPrice` |
| `message PriceRequest`, `hotel_id` | `PriceRequest(hotel_id=42)` | `PriceRequest.newBuilder().setHotelId(42).build()` | `PriceRequest r; r.set_hotel_id(42);` |
| a 300 ms deadline | `timeout=0.3` | `.withDeadlineAfter(300, MILLISECONDS)` | `ctx.set_deadline(now + 300ms)` |

🖼 **What goes on the wire** (same data):
```
JSON:      {"hotelId":42,"date":"2026-12-01"}        → 34 bytes of text; names repeated in every message; must be parsed
protobuf:  [tag 1][42][tag 2][len 10][2026-12-01]    → about 14 bytes binary; no names; decoded by generated code
```

🧩 **C++ analogy:** the `.proto` is a **shared header file** both sides compile against. The stub is a **generated proxy class**: you call `stub->GetPrice()` as if it were local, and it serialises and sends the call. A breaking change to the proto is like changing a struct layout in a shared header: everyone must recompile, or old binaries misread the bytes.

🔎 **Spot it in real code**
- Files: `*.proto`; generated `*_pb2.py` / `*_pb2_grpc.py` (Python), `*Grpc.java` (Java), `*.pb.go` (Go), `*.grpc.pb.h` (C++).
- ⚠️ A stub call with **no `timeout=` / `withDeadlineAfter`** waits forever.
- ⚠️ A **new channel created per request** opens a new HTTP/2 connection every call; the channel should live as long as the app.

🗣 **Say it:** "With gRPC you write the contract once in a `.proto`, generate a client stub and a server base class, and the call looks like a local method. Payloads are binary with field numbers instead of names, over one multiplexed HTTP/2 connection, and every call can carry a deadline. That's why I'd use it for internal hot paths like search calling pricing."

🔑 *Proto = shared header; stub = proxy class.* · *Proto likho, naam compiler banata hai.* (You write the proto; the compiler makes the names.)

---

## §3 Request coalescing (the supplier-cost saver)

**The mental model: the first caller becomes the leader and makes the one real call; everyone else waits on the leader's result.**

🖼 **Picture**
```
WITHOUT coalescing: 100 users search BKK→SIN, 1 Dec. The cache entry just expired.
 req1   ─► cache miss ─► supplier call ┐
 req2   ─► cache miss ─► supplier call │  100 PAID calls for the same answer
 ...                                   │  + the supplier's rate limit trips → 429s for everyone
 req100 ─► cache miss ─► supplier call ┘  (this is a CACHE STAMPEDE)

WITH coalescing:
 req1      ─► miss ─► no call in flight → "I'm the leader" ─► ONE supplier call ─► fill cache ─┐
 req2..100 ─► miss ─► a call for this key is already in flight → wait on the SAME result ◄──────┘
                                                                     all 100 get the answer
```

💻 **Pseudocode**
```python
in_flight = {}                                         # key → the promise of the ONE real call

def search(key):                                       # key = "BKK-SIN-2026-12-01"
    if key in cache:      return cache[key]            # 1. cache hit: done
    if key in in_flight:  return in_flight[key].wait() # 2. someone is already asking: wait for them
    in_flight[key] = Promise()                         # 3. I'm the leader
    offers = supplier.fetch(key)                       #    the ONE paid call
    cache.set(key, offers, ttl=60)
    in_flight.pop(key).resolve(offers)                 # 4. wake every follower
    return offers
# real code: steps 2-3 under one lock; if the call fails, reject the promise so followers fail too
```
- This works **per process**. With 20 pods you can still make up to 20 calls (the "autoscaling doubled our spend" trap). Across pods: a short **Redis lock** (`SET lock:key 1 NX PX 2000`). The pod that gets it calls the supplier; the others briefly wait for the cache, or serve slightly stale data.
- A close cousin, **stale-while-revalidate**: when the TTL expires, keep serving the old value and let one background call refresh it. Users never wait.

🧩 **C++ analogy:** the leader creates a `std::promise`; every follower gets a copy of its `std::shared_future`. One producer, many waiters on the same result.

🔎 **Spot it in real code**
- Go: `singleflight.Group` → `g.Do(key, fn)`. That *is* coalescing, built in.
- Java: a `ConcurrentHashMap` of `CompletableFuture`s with `putIfAbsent` / `computeIfAbsent`; or Caffeine's `AsyncLoadingCache`, which coalesces loads per key for you.
- Redis: `SET … NX PX …`, a short lock so only one pod refreshes.
- ⚠️ `if key not in cache: result = supplier.call(...)` with no in-flight map = **stampede**. Classic review comment on a supplier client.

🗣 **Say it:** "When a popular cache entry expires, a hundred searches miss at the same moment and each would call the supplier. That's a cache stampede, and on a metered API it's real money and a tripped rate limit. With coalescing, the first request becomes the leader and makes the one call; the rest wait on its result. In-process that's a map of in-flight futures; across pods, a short Redis lock or stale-while-revalidate."

🔑 *Pehla leader, baaki intezaar.* (The first is the leader, the rest wait.) · *Sau log, ek call.* (A hundred users, one call.)

---

## §4 Timeouts and deadline propagation

**The mental model: a stopwatch that travels with the request.** The edge starts it once. Every service passes it along. Nobody starts a fresh one.

🖼 **Picture 1: what "children get what's left" means**
```
User search arrives. Budget 1000 ms → deadline = now + 1000 ms
t=0     Search service ─┐
t=0–300                 ├─ call Pricing ............ took 300 ms
t=300                   ├─ call Supplier: left = 1000 − 300 = 700 ms
                        │     give it min(own timeout 800, 700 − 50 margin) = 650 ms
t=950                   │     supplier still silent → CANCEL, use cached/partial data
t=1000  respond ◄───────┘  user gets an answer on time
```

🖼 **Picture 2: what happens WITHOUT timeouts (the cascade)**
```
Thread pool: 10 threads.   Supplier X hangs for 30 s.

T1  [waiting on supplier X ............................]
T2  [waiting on supplier X ............................]
...                                                         all 10 threads stuck
T10 [waiting on supplier X ............................]
New request (even one that never touches X) → no free thread → queued → times out → error
=> one slow supplier took down the WHOLE service. Then OUR callers' threads wait on US: the cascade.
```

💻 **Pseudocode 1: one call, two timeouts**
```python
session = requests.Session()                      # ONE per app: it keeps the connection pool
r = session.get("https://supplier.example/avail", params={"hotel": 42},
                timeout=(0.3, 0.8))               # (CONNECT 300 ms, READ 800 ms)
# CONNECT: can't even reach the host → fail fast.   READ: from the supplier's p99 (about p99 × 1.5)
# Leave timeout= out and this waits FOREVER.
```

💻 **Pseudocode 2: the stopwatch inside one service**
```python
deadline = now() + 1.000                          # 1. the edge starts ONE stopwatch (1 s for search)

def budget(own_timeout):                          # 2. before every downstream call: what's left?
    left = deadline - now() - 0.050               #    keep 50 ms to build the response
    if left <= 0: raise DeadlineExceeded          #    nothing left → don't even start the call
    return min(own_timeout, left)

prices = pricing.call(req,  timeout=budget(0.4))  # 3. early call: gets its full 400 ms
offers = supplier.call(req, timeout=budget(0.8))  # 4. later call: gets min(800 ms, what's left)
```

🖼 **Picture 3: propagation ACROSS services** (the "propagation" part)
```
Search ──(header: remaining 650 ms)──► Supplier-gateway ──(header: remaining 600 ms)──► Supplier
          the gateway reads the header, starts its own stopwatch from 650, and subtracts its own time
```
💻 **Pseudocode 3: passing the stopwatch over HTTP**
```python
# in Search, calling the gateway:
headers = {"X-Timeout-Ms": int(budget(0.8) * 1000)}               # send REMAINING time, not a clock time
# in the gateway, on receiving it:
deadline = now() + int(request.headers["X-Timeout-Ms"]) / 1000    # the same stopwatch, restarted locally
```
- Send the *remaining duration*, not a wall-clock time, because the two servers' clocks differ.
- **gRPC** carries it for you as the `grpc-timeout` header. In Java and Go, an outgoing call made while handling a request **inherits the incoming deadline automatically**: that is all "gRPC has native deadline propagation" means. In Python you pass it on yourself: `timeout=context.time_remaining()`.
- **Go** builds it into the language idiom: every function takes a `ctx`.
  ```go
  ctx, cancel := context.WithTimeout(r.Context(), 1*time.Second) // start the stopwatch once
  defer cancel()
  prices, err := pricing.Get(ctx, req)     // every call takes ctx ...
  offers, err := supplier.Search(ctx, req) // ... and automatically gets whatever is left
  ```

🧩 **C++ analogy:** instead of each function taking its own `timeout_ms`, you pass a `const std::chrono::steady_clock::time_point& deadline` down the whole call chain, and every blocking call does `wait_until(deadline)` instead of `wait_for(800ms)`. That one parameter is the whole idea.

🔎 **Spot it in real code**
- Python: ⚠️ `requests.get(url)` with **no `timeout=`** waits forever.
- Java: ⚠️ `HttpClient` / `HttpRequest` with no `.connectTimeout(...)` / `.timeout(...)` waits forever. `withDeadlineAfter` (gRPC), `orTimeout` (`CompletableFuture`) are the good signs.
- Go: `context.WithTimeout`, `ctx` as the first parameter. ⚠️ `http.Client{}` with no `Timeout`: the default client never times out.
- ⚠️ The same fixed `timeout=5` on every downstream call, ignoring what's left = **no deadline propagation**.

🗣 **Say it:** "Think of it as a stopwatch that travels with the request. The edge sets one deadline, say one second for search. Before each downstream call I compute what's left and give the call the smaller of its own timeout and the remaining budget. If nothing's left, I don't start the call at all. Across services the remaining time goes in a header; gRPC does that automatically. Without it, a hung supplier holds every thread and the whole service goes down with it."

🔑 *Stopwatch ek, request ke saath chalta hai.* (One stopwatch, travelling with the request.) · *Naya stopwatch mat shuru karo.* (Don't start a fresh stopwatch.)

---

## §5 Retries: backoff, jitter, budgets

**The mental model: before every retry, pass three gates. Is it safe? Is it temporary? Is there budget left?**

🖼 **Picture 1: why jitter**
```
A supplier blips at t=0 and 1,000 clients fail together.

Backoff WITHOUT jitter (everyone waits exactly 100 ms, then 200 ms, …):
 t=100  ██████████  1,000 retries in the same instant → the supplier falls over again
 t=300  ██████████  again …                            (a synchronised "thundering herd")

FULL jitter (each waits random(0, 100 × 2^attempt)):
 t=0…100  ▂▂▂▂▂▂▂▂▂▂  the same 1,000 retries spread out → the supplier recovers
```

🖼 **Picture 2: why retry at ONE layer**
```
App (3 tries) ──► Gateway (3 tries) ──► Booking svc (3 tries) ──► Supplier (down)
1 user click = 3 × 3 × 3 = 27 calls hitting a supplier that is already struggling
Fix: retry only at the layer closest to the failure; the others fail fast.
```

💻 **Pseudocode: the loop and its three gates**
```python
def call_with_retry(req, deadline):
    retry_budget.on_request()
    for attempt in range(3):                                          # at most 3 tries
        try:
            return supplier.call(req, timeout=deadline - now())       # 1. each try gets what's left (§4)
        except Exception as e:
            if not retryable(e) or attempt == 2 or not retry_budget.take():
                raise                                                 # 2. the gates: safe? temporary? budget?
            wait = random.uniform(0, min(2.0, 0.1 * 2**attempt))      # 3. FULL jitter: random(0, 100/200/400 ms)
            wait = max(wait, retry_after(e))                          #    a 429 says when: honour Retry-After
            if now() + wait >= deadline: raise                        # 4. can't wait past the deadline
            sleep(wait)

# retryable(e): YES → timeout, connection reset, 502 / 503 / 504, 429
#               NO  → 400, 401 / 403, 404, 409, 422 (retrying won't fix the request)
#               NO  → a POST without an Idempotency-Key (§6): a retry could book twice
```

💻 **Pseudocode: the retry budget** (retries stay under about 10% of traffic)
```python
class RetryBudget:
    tokens = 10
    def on_request(self): self.tokens = min(10, self.tokens + 0.1)   # every request earns 0.1 token
    def take(self):                                                  # every retry costs 1 token
        if self.tokens < 1: return False                             # budget gone → stop retrying
        self.tokens -= 1
        return True
```
When the supplier is healthy there are always tokens. When it fails 50% of calls, the tokens run out within seconds and retries stop. The supplier sees about **1.1×** its normal load instead of **3×**, so it can recover. Without a budget, the retries themselves keep it down: a **retry storm**.

🧩 **C++ analogy:** a spinlock with exponential backoff. Threads that lose a compare-and-swap don't all retry on the next cycle; each backs off a random, growing amount so they stop colliding. A retry storm is the distributed version of lock contention.

🔎 **Spot it in real code**
- Python: `tenacity` → `@retry(stop=stop_after_attempt(3), wait=wait_random_exponential(...))`.
- Java: Resilience4j `@Retry`, Spring `@Retryable`.
- Go / anywhere: a hand-written `for` loop with `sleep`.
- ⚠️ `for i in range(3): try: … except: pass` retries **everything** (400s and POSTs included) with no backoff and no jitter = a retry storm waiting to happen.
- ⚠️ A fixed `sleep(1)` between tries = no jitter. ⚠️ Retry on a `POST` with no idempotency key = double booking.

🗣 **Say it:** "Before retrying I ask three questions: is it safe, meaning idempotent; is it temporary, like a timeout, a 503 or a 429; and is there budget left. Then I back off exponentially with full jitter, so a thousand clients don't retry in the same millisecond, and I stop at the deadline. Only one layer retries, otherwise three layers of three tries turn one click into 27 calls. And a retry budget of about ten percent stops retries from keeping a struggling supplier down."

🔑 *Teen gate: safe hai? temporary hai? budget hai?* (Three gates: is it safe, is it temporary, is there budget?) · *Jitter = sab ek saath wapas na aayein.* (Jitter = don't let everyone come back at once.)

---

## §6 Idempotency

**The mental model: one click gets one key, and the key goes with every retry. The server remembers keys it has already done.**

🖼 **Picture 1: the problem**
```
Client ── POST /bookings ──► Server: books the room, charges the card ✔
Client ◄──── response LOST (Wi-Fi drop, timeout) ✘
Client: "did it work?" → retries POST → a SECOND booking and a SECOND charge ✘✘
```

🖼 **Picture 2: the fix**
```
The client creates key K (a UUID) once per click and resends the SAME K on every retry.

try 1: POST /bookings  Idempotency-Key: K → INSERT K succeeds (new) → do the work → save the response with K → 201 (lost)
try 2: POST /bookings  Idempotency-Key: K → INSERT K CONFLICTS (seen) → look up K → return the SAVED 201
                                                                        no second booking, no second charge
```

💻 **The table**: the primary key does the deduplication.
```sql
CREATE TABLE idempotency_keys (
  idem_key      VARCHAR(64) PRIMARY KEY,   -- a second INSERT with the same key fails: that IS the dedupe
  request_hash  CHAR(64)    NOT NULL,      -- same key + different body = a client bug → 422
  status        VARCHAR(16) NOT NULL,      -- IN_PROGRESS | DONE
  response_body TEXT,                      -- what we replay to the duplicate
  created_at    TIMESTAMP   NOT NULL       -- purge after 24 h – 7 days
);
```

💻 **Pseudocode: the handler**
```python
def create_booking(key, body):
    with db.transaction():
        if db.insert_if_absent(key=key, hash=sha256(body), status="IN_PROGRESS"):  # 1. INSERT … ON CONFLICT DO NOTHING
            booking = bookings.create(body)                       # 2. first time: do the real work
            db.update(key, status="DONE", response=booking)       #    saved in the SAME transaction
            return 201, booking
        row = db.get(key)                                         # 3. seen this key before
        if row.hash != sha256(body): return 422                   #    same key, different request = client bug
        if row.status == "DONE":     return 201, row.response     #    duplicate → replay the SAME answer
        return 409, {"Retry-After": 1}                            #    first try still running
```
(In the real flow the supplier and payment calls happen outside this DB transaction, as a saga (§15). The `IN_PROGRESS` row is what lets you detect and resume a crashed attempt.)

🖼 **Picture 3: the hardest case, an ambiguous supplier timeout**
```
We ── book(client_ref = AG-123) ──► Supplier      … 30 s, no answer
Did it book? UNKNOWN.
 ✘ retry blindly                      → maybe two rooms
 ✔ ask first, then retry only if it didn't happen
```
```python
try:
    supplier.book(offer, client_ref=booking_id)        # our ID doubles as their idempotency key
except Timeout:
    if not supplier.find(client_ref=booking_id):       # did it go through? ASK before retrying
        supplier.book(offer, client_ref=booking_id)
```

⚠️ Idempotency ≠ concurrency control. Idempotency stops **one user's retry** from booking twice. **Two users** wanting the last room is a race, fixed with a conditional update: `UPDATE … SET available = available − 1 WHERE … AND available > 0` (0 rows updated = sold out).

🧩 **C++ analogy:** `INSERT … ON CONFLICT DO NOTHING` is a **compare-and-swap on the key**: exactly one caller wins, and everyone else sees "already set". Like a `std::once_flag` per request: the work runs once, and every later call gets the stored result.

🔎 **Spot it in real code**
- The `Idempotency-Key` header; SQL `ON CONFLICT DO NOTHING` (Postgres), `INSERT IGNORE` / `ON DUPLICATE KEY` (MySQL); a `UNIQUE` constraint on a key or `event_id`; a `processed_events` table in a Kafka consumer.
- ⚠️ A `POST /bookings` handler with no key, plus a client that retries = **double booking**.
- ⚠️ Dedupe done as `SELECT` then `INSERT` with **no unique constraint** = a race: two requests both see "not found" and both book.

🗣 **Say it:** "Idempotency means the same request applied twice has the effect of once, and that's what makes retries safe. The client generates a key per click and resends it on every retry. The server inserts the key under a unique constraint. If the insert conflicts, it's a duplicate, and we replay the stored response instead of booking again. Toward suppliers, our booking ID is the key; if a call times out, we ask whether it went through before we retry."

🔑 *Ek click, ek key, kitni bhi retry.* (One click, one key, any number of retries.) · *Timeout aaya? Pehle poochho, phir retry.* (Timed out? Ask first, then retry.)

---

## §7 Circuit breaker and bulkhead

**The mental model: a timeout limits HOW LONG, a bulkhead limits HOW MANY, a breaker decides WHEN TO STOP.**

🖼 **Picture 1: the breaker's states** (like an electrical switch: closed = current flows)
```
                     > 50% errors over ≥ 20 calls
   ┌──────────┐ ──────────────────────────────────► ┌──────────┐
   │  CLOSED  │                                     │   OPEN   │  fail fast: 0 calls to the supplier,
   │calls flow│                                     │          │  return cached / partial data instead
   └──────────┘                                     └──────────┘
        ▲                                                │ after a 30 s cool-down
        │ trial calls succeed                            ▼
        │                                         ┌────────────┐
        └──────────────────────────────────────── │ HALF-OPEN  │  let a few trial calls through
                                                  └────────────┘
                                                         │ a trial call fails → back to OPEN
```

💻 **Pseudocode: a minimal breaker** (one per supplier)
```python
class Breaker:
    state, calls, failures, opened_at = "CLOSED", 0, 0, 0

    def allow(self):                                    # 1. ask before every call
        if self.state == "OPEN" and now() - self.opened_at > 30:
            self.state = "HALF_OPEN"                    #    cool-down over: let a trial call through
        return self.state != "OPEN"                     #    OPEN → fail fast, don't call at all

    def record(self, ok):                               # 2. report after every call
        self.calls += 1
        if not ok: self.failures += 1
        if self.state == "HALF_OPEN":                   #    the trial call decides
            if ok: self.state, self.calls, self.failures = "CLOSED", 0, 0
            else:  self.state, self.opened_at = "OPEN", now()
        elif self.calls >= 20 and self.failures / self.calls > 0.5:
            self.state, self.opened_at = "OPEN", now()  #    > 50% errors over ≥ 20 calls → trip
# real code: count over a rolling time window, and cap how many trial calls HALF_OPEN lets through
```
```python
def search_supplier_a(req):
    if not breaker_a.allow(): return partial("supplierA", "circuit_open")
    try:
        offers = supplier_a.search(req, timeout=budget(0.8))
        breaker_a.record(ok=True)
        return offers
    except Exception:
        breaker_a.record(ok=False)
        return partial("supplierA", "error")
```

🖼 **Picture 2: the bulkhead** (named after a ship's watertight compartments)
```
WITHOUT bulkheads: one shared pool of 50 threads
  supplier A hangs → A's calls take all 50 threads → calls to B, C and the DB wait → EVERYTHING is slow

WITH bulkheads: a separate, bounded pool (or semaphore) per dependency
  [ A: 20 slots ████████████████████ FULL → extra A calls rejected instantly ]
  [ B: 20 slots ████                 healthy ]
  [ C: 10 slots ██                   healthy ]
  A is sinking, but only A's compartment floods.
```

💻 **Pseudocode: a bulkhead is just a semaphore**
```python
slots_a = Semaphore(20)                                   # supplier A: at most 20 calls at once

def call_a(req):
    if not slots_a.acquire(blocking=False):               # all 20 busy → reject now, don't queue
        return partial("supplierA", "bulkhead_full")
    try:     return supplier_a.search(req, timeout=budget(0.8))
    finally: slots_a.release()                            # ALWAYS give the slot back
```

🖼 **How the three work together on one supplier call**
```
request ─► [bulkhead: a slot free?] ─► [breaker: closed?] ─► [timeout: done within budget?] ─► supplier
                  no → partial              no → partial            no → partial (+ breaker counts a failure)
```

🧩 **C++ analogy:** a bulkhead is a `std::counting_semaphore<20>` per resource. A breaker is a **watchdog** that disables a misbehaving device after N errors and probes it again after a cool-down.

🔎 **Spot it in real code**
- Java: Resilience4j `@CircuitBreaker(name = "supplierA", fallbackMethod = …)` and `@Bulkhead`; Hystrix (older, from Netflix). Python: `pybreaker`. Go: `gobreaker`.
- Bulkhead: a `Semaphore`, or a separate fixed-size thread pool (`ThreadPoolExecutor(max_workers=20)`) **per supplier**.
- ⚠️ One shared thread pool or HTTP connection pool for all suppliers, with no per-supplier limit = **no bulkhead**.
- ⚠️ One breaker shared by all suppliers: one bad supplier opens it for everyone.

🗣 **Say it:** "A circuit breaker stops calling a supplier that's clearly failing. Once errors pass a threshold it opens and we fail fast with cached or partial data, without even making the call. After a cool-down, half-open lets a few trial calls through to test recovery. A bulkhead is a bounded pool per supplier, in effect a semaphore, so when one supplier hangs it can only use its own slots and can't take the threads everyone else needs. Together with timeouts: the timeout limits how long, the bulkhead limits how many, the breaker decides when to stop."

🔑 *Timeout = kitni der, bulkhead = kitne log, breaker = kab band.* (Timeout = how long, bulkhead = how many, breaker = when to stop.)
