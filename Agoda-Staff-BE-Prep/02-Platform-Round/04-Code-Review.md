# Code Review: checklist, comment style, 12 practice snippets

> Reports: the snippet is usually a **booking service / booking API**. Candidates were asked to fix exception handling and code structure, and proposed the **strategy** or **factory** pattern for a **loop calling a DB client and an HTTP client per supplier**.
> Recruiter: *"Avoid superficial code reviews. Catch fundamentals like **SQL injection, expensive DB initialisation per call, hardcoded vendor keys, and missing pagination**."*
> Toolkit: readability, maintainability, correctness, **code smells, SOLID, basic design patterns**. *"Frame feedback positively and offer alternatives."*

---

## 1. The review order (top-down: the most expensive bugs first)

Read the whole snippet once for **intent** (30 s, and say it aloud: "this books a room by checking each supplier, then saving and charging"). Then sweep in this order:

| # | Lens | Questions |
|---|---|---|
| 1 | **Correctness** | Does it do what it claims? Edge cases (null/empty, zero, date ranges, time zones), off-by-one, wrong comparison, missing `return`/`break`, error paths |
| 2 | **Security** | Injection (SQL, command, log), **hardcoded secrets**, authZ/ownership checks (IDOR), input validation, **PII/card data in logs**, error messages leaking internals |
| 3 | **Concurrency & data integrity** | Check-then-act races (double booking), shared mutable state, non-thread-safe collections/singletons, missing transaction, non-atomic multi-step writes (dual write), idempotency on retries |
| 4 | **Reliability / connectivity** | Timeouts, retries (safe? bounded?), swallowed exceptions, resource leaks (connections/streams not closed), partial-failure handling, fallbacks |
| 5 | **Performance & scalability** | Expensive object per call (DB connection, HTTP client, ObjectMapper, regex), **N+1 queries**, unbounded queries (**no pagination**), sync calls in loops (sequential fan-out), blocking in async code, loading everything into memory |
| 6 | **Design / maintainability** | SRP (god method), OCP (`if supplier == "A"` chains → strategy), DIP (`new` concrete clients inside → inject interfaces), magic numbers/strings, duplication, naming, layering (controller doing SQL) |
| 7 | **Testability & tests** | Can it be unit-tested (static calls, `new` inside, `System.currentTimeMillis()`)? Are there tests for failure paths? |
| 8 | **Observability** | Logging at the right level with context (correlation ID), metrics for supplier calls, no `printStackTrace` |
| 9 | **Readability nits** | Naming, formatting, comments: **last, and labelled as nits** |

**Prioritise out loud:** *"I see about 10 issues. Let me start with the three that can lose money or data: …, then the reliability ones, then design."*
**Fix, don't just flag:** for the top 2–3, show the corrected code or the refactored shape (interface + implementations). That's where the strategy/factory discussion goes.

## 2. Comment style (the Toolkit grades the tone)

Use labels so severity is obvious (Conventional Comments style):

| Label | Example |
|---|---|
| **blocking / issue** | "**issue (blocking):** this builds SQL by concatenating `userId`, which allows SQL injection (`' OR '1'='1`). Could we use a `PreparedStatement` with `?` parameters? Same pattern on line 31." |
| **suggestion** | "**suggestion:** the `if/else` per supplier will grow with every new supplier. A `SupplierClient` interface with one implementation per supplier, picked from a map, keeps this method closed for modification. Happy to pair on it." |
| **question** | "**question:** is `bookRoom` ever retried by the client? If so, we'd create two bookings. Should we accept an idempotency key?" |
| **nit** | "**nit:** `d` → `checkInDate` would read better." |
| **praise** | "**praise:** nice use of a value object for `Money`, this removes a whole class of rounding bugs." |

Rules: comment on the **code, not the person** ("this method", not "you"); give the **why** (impact) and an **alternative**; ask questions when unsure of intent; group repeated issues ("same on lines 31, 48"); one **praise** if something is genuinely good; and say what you'd **approve with** vs **block on**.
⭐ Staff angle: *"Recurring issues mean the team needs a linter rule, a shared library or a checklist, not more review comments. I'd add Semgrep rules for SQL concatenation and secret patterns so humans review design, not formatting."*

## 3. SOLID and the patterns that come up

- **S**ingle responsibility: a method that validates, calls suppliers, saves, charges and emails has 5 reasons to change → split into collaborators.
- **O**pen/closed: adding supplier C shouldn't mean editing `BookingService` → **Strategy** (interface `SupplierClient`, one class per supplier) + **Factory/registry** (`Map<SupplierId, SupplierClient>` built by DI).
- **L**iskov: subclasses mustn't strengthen preconditions or throw unexpected exceptions (e.g. `ReadOnlySupplier.book()` throwing `UnsupportedOperationException` → wrong hierarchy).
- **I**nterface segregation: don't force every supplier to implement `cancel()`, `modify()` and `getReviews()` if some can't → smaller interfaces.
- **D**ependency inversion: depend on `BookingRepository` / `PaymentGateway` interfaces injected via constructor, not `new MySqlConnection()` inside → testable, swappable.

Other patterns: **Adapter** (wrap each supplier API into the canonical model), **Decorator** (add retry/metrics/caching around a `SupplierClient` without touching it), **Template method** (common booking flow, supplier-specific steps), **Builder** (complex request objects), **Circuit breaker** / **Retry** (resilience decorators), **Repository** (data access), **Value object** (`Money`, `DateRange`).

**Code smells:** long method, god class, long parameter list, primitive obsession (`double price`, `String currency`), switch/if-chains on type, duplicated code, feature envy, shotgun surgery, dead code, magic numbers, comments explaining bad code, exceptions used for control flow, catch-all `catch (Exception e) {}`.

---

## 4. Practice snippets (4 minutes each, aloud: list, prioritise, fix the top 2)

Answer keys are folded. Don't open them until you've written your own review.

### CR-1 ★★★ The booking service (the most likely shape), Java
```java
public class BookingService {
    private static final String API_KEY = "sk_live_9f8a7b6c5d";          // supplier key
    private List<Booking> cache = new ArrayList<>();

    public Booking book(String userId, String hotelId, String supplier,
                        String checkIn, String checkOut, double price, String cardNo) {
        Connection conn = DriverManager.getConnection("jdbc:mysql://db:3306/agoda", "root", "root");
        try {
            Statement st = conn.createStatement();
            ResultSet rs = st.executeQuery("SELECT available FROM rooms WHERE hotel_id = '" + hotelId + "'");
            rs.next();
            if (rs.getInt("available") > 0) {
                boolean ok = false;
                if (supplier.equals("SupplierA")) {
                    HttpClient client = HttpClient.newHttpClient();
                    HttpRequest req = HttpRequest.newBuilder(URI.create("https://a.example.com/book?key=" + API_KEY
                            + "&hotel=" + hotelId)).POST(HttpRequest.BodyPublishers.noBody()).build();
                    ok = client.send(req, HttpResponse.BodyHandlers.ofString()).statusCode() == 200;
                } else if (supplier.equals("SupplierB")) {
                    HttpClient client = HttpClient.newHttpClient();
                    HttpRequest req = HttpRequest.newBuilder(URI.create("https://b.example.com/v2/reserve"))
                            .header("X-Api-Key", API_KEY).POST(HttpRequest.BodyPublishers.ofString(hotelId)).build();
                    ok = client.send(req, HttpResponse.BodyHandlers.ofString()).statusCode() == 201;
                }
                if (ok) {
                    st.executeUpdate("UPDATE rooms SET available = available - 1 WHERE hotel_id = '" + hotelId + "'");
                    st.executeUpdate("INSERT INTO bookings VALUES ('" + userId + "','" + hotelId + "'," + price + ")");
                    System.out.println("Booked for card " + cardNo);
                    Booking b = new Booking(userId, hotelId, price);
                    cache.add(b);
                    return b;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public List<Booking> getBookings(String userId) throws SQLException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://db:3306/agoda", "root", "root");
        ResultSet rs = conn.createStatement().executeQuery("SELECT * FROM bookings WHERE user_id = '" + userId + "'");
        List<Booking> all = new ArrayList<>();
        while (rs.next()) all.add(map(rs));
        return all;
    }
}
```
<details><summary>Answer key (aim for ≥ 12 of these, top 4 first)</summary>

**Blocking (money/data/security):**
1. **SQL injection**: string-concatenated SQL everywhere (`hotelId`, `userId`). → `PreparedStatement` with `?` parameters.
2. **Double booking race (check-then-act)**: `SELECT available` then later `UPDATE`. Two requests both see 1 and both book. → An atomic conditional update `UPDATE … SET available = available - 1 WHERE hotel_id = ? AND date = ? AND available > 0` and check the row count (or `SELECT … FOR UPDATE` inside a transaction). Also, availability should be per **date range**, but the dates are ignored entirely.
3. **No transaction**: the inventory decrement and the booking insert aren't atomic; a crash between them corrupts inventory. And the supplier call happens *before* our write: the supplier is booked but we fail to save → an orphan booking at the supplier. → Transaction for local writes; saga: create a PENDING booking → call the supplier with our booking ref → CONFIRM, compensate on failure; reconciliation job.
4. **Hardcoded secrets**: the `sk_live_` supplier key and DB `root/root` in source. One key shared by both suppliers. Key in the **URL query string** (ends up in logs and proxies). → Secret manager/env, per-supplier keys, send in a header.
5. **Card number logged** (`System.out.println(cardNo)`) → a PCI violation. The service shouldn't even receive the raw PAN: use a payment token from the PSP. Never log PII.
6. **No idempotency**: a client retry after a timeout books twice. → `Idempotency-Key`.
7. **Price from the client** as `double`: (a) the client can tamper with the price; re-price server-side from an `offerId`; (b) `double` for money → rounding errors → `BigDecimal`/minor units + currency.
8. **No authZ** on `getBookings(userId)`: any caller passing any `userId` reads others' bookings (IDOR) → derive the user from the auth token.

**Reliability/performance:**
9. **New DB connection per call** (`DriverManager.getConnection`) and **never closed** → slow (TCP + auth handshake every time) and a connection leak → pool exhaustion. → Injected `DataSource` with a pool (HikariCP), try-with-resources for `Connection/Statement/ResultSet`.
10. **New `HttpClient` per call** → no connection reuse (a TLS handshake every booking). → One shared, injected client.
11. **No timeouts** on supplier HTTP calls (Java `HttpClient` defaults to none) → threads hang. → `connectTimeout` + per-request `.timeout()`.
12. **Swallowed exceptions**: `catch (Exception e) { e.printStackTrace(); } return null;` hides failures, and the caller gets `null` (NPE later) with no reason. → Specific exceptions mapped to domain errors (`SoldOut`, `SupplierUnavailable`, `PaymentFailed`), logged with context, propagated or translated to HTTP codes.
13. **`rs.next()` result ignored**: if the hotel doesn't exist, `getInt` throws.
14. **Unknown supplier** silently returns `null` (no `else`).
15. **Supplier status checks differ** (200 vs 201) and ignore the response body (no supplier booking reference stored → you can't cancel or reconcile later).
16. **`getBookings` has no pagination** → unbounded result set; `SELECT *` is fragile. → Cursor pagination + explicit columns.
17. **`cache` is an unbounded, non-thread-safe `ArrayList`** on a (probably singleton) service → memory leak + race conditions; it's also never read. → Remove it, or use a proper cache.
18. **INSERT without a column list**: breaks when the schema changes.

**Design:**
19. **God method / SRP**: validation, inventory, supplier calls, persistence and logging in one method. **OCP**: an `if/else` per supplier. → `SupplierClient` interface (`reserve(BookingRequest): SupplierBookingRef`) with `SupplierAClient` and `SupplierBClient` (Strategy/Adapter), resolved via a registry/factory `Map<String, SupplierClient>`; `BookingRepository`; `PaymentGateway`; all injected (DIP) → unit-testable with fakes.
20. **Primitive obsession**: dates as `String`, `double price` → `LocalDate`/`DateRange`, `Money` value objects; a long parameter list → a `BookingRequest` object. Validate `checkIn < checkOut`.
21. `System.out`/`printStackTrace` → structured logger with booking ID and trace ID; metrics per supplier.
22. Tests: none possible as written (static `DriverManager`, `new HttpClient` inside).

**Refactored shape to sketch:**
```java
public interface SupplierClient { SupplierRef reserve(ReserveRequest r) throws SupplierException; }

public final class BookingService {
    private final Map<SupplierId, SupplierClient> suppliers;   // injected (factory/registry)
    private final BookingRepository repo; private final IdempotencyStore idem;

    public BookingResult book(UserId user, BookingRequest req, String idemKey) {
        return idem.execute(idemKey, req, () -> {
            Offer offer = pricing.revalidate(req.offerId());                 // server-side price
            Booking pending = repo.createPendingIfAvailable(user, offer);    // tx + conditional update
            SupplierClient client = Optional.ofNullable(suppliers.get(offer.supplier()))
                    .orElseThrow(() -> new UnknownSupplierException(offer.supplier()));
            try {
                SupplierRef ref = client.reserve(ReserveRequest.from(pending));  // timeout+retry inside
                return repo.confirm(pending.id(), ref);                       // + outbox event, same tx
            } catch (SupplierException e) {
                repo.fail(pending.id(), e.reason());                          // compensation
                throw new BookingFailedException(e);
            }
        });
    }
}
```
</details>

### CR-2 ★★★ Supplier search fan-out, Java
```java
public List<Offer> search(SearchRequest req) {
    List<Offer> offers = new ArrayList<>();
    for (String supplier : config.getSuppliers()) {               // 12 suppliers
        SupplierApi api = new SupplierApi(supplier, config.getKey(supplier));
        try {
            offers.addAll(api.search(req));
        } catch (Exception e) {
            return Collections.emptyList();
        }
    }
    offers.sort((a, b) -> (int) (a.getPrice() - b.getPrice()));
    return offers;
}
```
<details><summary>Answer key</summary>

1. **Sequential fan-out**: latency = the *sum* of 12 supplier latencies. → Parallel calls (`CompletableFuture.supplyAsync` on a **bounded** executor, `allOf` + `orTimeout`), overall deadline.
2. **One failing supplier wipes all results** (`return emptyList()`) → partial results with per-source status.
3. **Client constructed per call per supplier** → reuse injected clients.
4. **No timeouts / breaker / bulkhead** → one slow supplier stalls the request.
5. **Comparator bug**: `(int)(a - b)` truncates: prices 10.3 and 10.7 compare equal (`(int) -0.4 = 0`), and large differences can overflow. → `Comparator.comparing(Offer::getPrice)` with `BigDecimal`.
6. **No dedupe**: the same hotel/flight from several suppliers appears multiple times → group by canonical key, keep the cheapest.
7. **No pagination/limit** on the merged list.
8. `catch (Exception)` with no logging/metrics → invisible failures.
9. No caching: every search hits 12 metered APIs (cost!).
10. Currency: comparing prices in different currencies without normalisation.
</details>

### CR-3 ★★ Retry helper, Python
```python
import requests, time

def call_supplier(url, payload):
    for i in range(5):
        try:
            r = requests.post(url, json=payload)
            return r.json()
        except Exception:
            time.sleep(1)
    return None
```
<details><summary>Answer key</summary>

1. **No timeout** on `requests.post` (default: wait forever).
2. **Retries a POST** (non-idempotent: may book 5 times) → only retry if idempotent or with an idempotency key.
3. **Status code never checked**: a 500 or 400 returns `r.json()` of an error body as if it were success; `r.json()` may raise on HTML error pages.
4. **Retries everything**, including non-retryable errors (400/401), and bugs (`TypeError`).
5. **Fixed 1 s sleep, no jitter, no backoff** → synchronised retry storms; ignores `Retry-After` on 429.
6. 5 attempts × unbounded time: no overall deadline.
7. **Returns `None` silently** → the caller can't tell "no data" from "failed"; raise a typed exception.
8. **A new connection per call** (module-level `requests.post`) → use a `Session` for pooling.
9. No logging/metrics of attempts.
</details>

### CR-4 ★★★ Paginated listing endpoint, C# (.NET)
```csharp
[HttpGet("api/hotels/{cityId}/reviews")]
public IActionResult GetReviews(int cityId, int page)
{
    var db = new SqlConnection(_config["ConnStr"]);
    db.Open();
    var reviews = db.Query<Review>("SELECT * FROM Reviews WHERE CityId = " + cityId).ToList();
    var result = reviews.Skip(page * 20).Take(20);
    return Ok(result);
}
```
<details><summary>Answer key</summary>

1. **Pagination done in memory**: loads *all* reviews for a city (maybe millions) and then skips → memory/latency blow-up. → Paginate in SQL with **keyset**: `SELECT TOP (@pageSize) … WHERE CityId = @cityId AND (CreatedAt < @lastCreatedAt OR (CreatedAt = @lastCreatedAt AND Id < @lastId)) ORDER BY CreatedAt DESC, Id DESC` (T-SQL has no row-value `(a, b) < (x, y)`; Postgres does), backed by an index on `(CityId, CreatedAt DESC, Id DESC)`; return `nextCursor`.
2. **Connection never disposed** → pool leak. → `using var db = …` or (better) injected via DI; open per operation (ADO.NET pools underneath).
3. **SQL concatenation**: `cityId` is an `int`, so it isn't exploitable *here*, but it's a bad habit that gets copied with strings → parameters (`@cityId`).
4. `page` unvalidated (negative values), no page-size cap, no stable `ORDER BY` (pages are non-deterministic).
5. `SELECT *` returns columns you don't need (and maybe PII such as reviewer emails).
6. Synchronous I/O in ASP.NET → `QueryAsync` + `async Task<IActionResult>` (thread-pool starvation under load).
7. No caching for a read-heavy, rarely-changing resource (`Cache-Control`, `ETag`).
</details>

### CR-5 ★★ Webhook receiver, Go
```go
func handleSupplierWebhook(w http.ResponseWriter, r *http.Request) {
    body, _ := io.ReadAll(r.Body)
    sig := r.Header.Get("X-Signature")
    mac := hmac.New(sha256.New, []byte("whsec_123"))
    mac.Write(body)
    if hex.EncodeToString(mac.Sum(nil)) != sig {
        http.Error(w, "bad sig", 401)
        return
    }
    var ev RateUpdate
    json.Unmarshal(body, &ev)
    db.Exec("UPDATE rates SET price=$1 WHERE hotel_id=$2", ev.Price, ev.HotelID)
    notifyAllSubscribers(ev)   // calls ~200 partner endpoints
    w.WriteHeader(200)
}
```
<details><summary>Answer key</summary>

1. **Non-constant-time comparison** (`!=` on strings) → timing attack. → `hmac.Equal`.
2. **Hardcoded secret**; a single secret for all suppliers → per-supplier secrets from a secret store, with rotation support (accept 2 active secrets).
3. **No timestamp/replay protection**: a captured request can be replayed forever → sign `timestamp.body`, reject if older than 5 min.
4. **No dedupe** by event ID → retries apply twice (harmless here, harmful for non-idempotent events).
5. **No ordering protection**: an older update arriving late overwrites a newer price → compare a version/`updated_at` (`WHERE hotel_id=$2 AND version < $3`).
6. **Errors ignored**: `io.ReadAll`, `json.Unmarshal`, `db.Exec` → a malformed payload writes zero values (price 0!). Validate it.
7. **No body size limit** → `http.MaxBytesReader`.
8. **Slow synchronous fan-out to 200 partners inside the handler** → the sender times out and retries → duplicates + storms. → Persist/enqueue, return 2xx fast, process async with workers.
9. Status 401 for a bad signature is fine; also log/metric it (an attack signal).
</details>

### CR-6 ★★ N+1 and the ORM, Java/JPA
```java
@GetMapping("/users/{id}/trips")
public List<TripDto> trips(@PathVariable long id) {
    List<Booking> bookings = bookingRepo.findByUserId(id);
    List<TripDto> out = new ArrayList<>();
    for (Booking b : bookings) {
        Hotel h = hotelRepo.findById(b.getHotelId()).get();
        List<Review> reviews = reviewRepo.findByHotelId(h.getId());
        out.add(new TripDto(b, h, reviews.size()));
    }
    return out;
}
```
<details><summary>Answer key</summary>

1. **N+1 (actually 2N+1) queries**: one per booking for the hotel, one per booking for the reviews. → Batch: `hotelRepo.findAllById(ids)` → map; a review count via `GROUP BY hotel_id` in one query (or a join fetch / `@EntityGraph`).
2. **Loads all reviews just to count them** → `COUNT(*)` query, or a denormalised `review_count` column.
3. `.get()` on an `Optional` → `NoSuchElementException` if the hotel was deleted → handle it.
4. **No authZ**: any user can read any user's trips (IDOR) → the user comes from the token, or check ownership.
5. **No pagination** on bookings.
6. Entities leaking into DTO construction is okay, but watch lazy loading outside a transaction (`LazyInitializationException`) / open-session-in-view.
</details>

### CR-7 ★★ Thread-safety and the singleton, Java
```java
@Service
public class ExchangeRateService {
    private Map<String, Double> rates = new HashMap<>();
    private long lastRefresh = 0;
    private SimpleDateFormat fmt = new SimpleDateFormat("yyyy-MM-dd");

    public double convert(double amount, String from, String to) {
        if (System.currentTimeMillis() - lastRefresh > 60_000) {
            rates = fetchRatesFromProvider();       // HTTP call ~300ms
            lastRefresh = System.currentTimeMillis();
        }
        return amount * rates.get(to) / rates.get(from);
    }
}
```
<details><summary>Answer key</summary>

1. **Spring `@Service` is a singleton shared by all request threads**: `HashMap`, `lastRefresh`, `SimpleDateFormat` are shared mutable state without synchronisation (data races; `SimpleDateFormat` is not thread-safe, so use `DateTimeFormatter`).
2. **Refresh stampede**: when the TTL expires, every concurrent request calls the provider at once. → A single background refresh (`@Scheduled`) or single-flight; publish via `volatile` reference to an immutable map (`Map.copyOf`).
3. **Refresh on the request path** adds 300 ms latency to the unlucky request, and if the provider is down every request fails → serve the last-known rates (with a staleness limit + alert).
4. **`rates.get()` → NPE** for an unknown currency; `lastRefresh` isn't updated on failure (or is, depending) → define it.
5. **`double` for money** → `BigDecimal` with explicit rounding (`HALF_EVEN`), rates as `BigDecimal`.
6. `System.currentTimeMillis()` hardcoded → inject a `Clock` for testability.
7. No timeout on the provider call.
</details>

### CR-8 ★★ Async code that blocks, Kotlin
```kotlin
suspend fun getHotelPage(id: Long): HotelPage = coroutineScope {
    val hotel = async { hotelClient.get(id) }
    val price = async { pricingClient.price(id) }        // blocking JDBC inside
    val reviews = async { reviewsClient.top(id).also { Thread.sleep(50) } }
    HotelPage(hotel.await(), price.await(), reviews.await())
}
```
<details><summary>Answer key</summary>

1. **Blocking calls on the coroutine dispatcher** (blocking JDBC, `Thread.sleep`) → starve the limited `Default` pool, so throughput collapses under load. → `withContext(Dispatchers.IO)` for blocking work, `delay()` instead of `Thread.sleep` (and why sleep at all?).
2. **No timeouts** → `withTimeout(…)` per call, or an overall timeout.
3. **All-or-nothing**: if reviews fail, `coroutineScope` cancels everything and the page fails → reviews are optional: `supervisorScope` / `runCatching` → render the page without reviews (graceful degradation).
4. Price is critical, reviews aren't: say the **criticality split** explicitly.
</details>

### CR-9 ★ Logging and errors, Python (FastAPI)
```python
@app.post("/payments")
def pay(req: PaymentRequest):
    logger.info(f"payment request {req.dict()}")
    try:
        result = psp.charge(req.card_number, req.cvv, req.amount)
    except Exception as e:
        return {"status": "error", "message": str(e)}
    return {"status": "ok", "id": result.id}
```
<details><summary>Answer key</summary>

1. **Logs the full card number and CVV** (`req.dict()`) → a PCI-DSS violation. CVV must never be stored or logged. → Tokenise on the client (PSP hosted fields); log only a masked last-4 + payment ID.
2. **Errors returned with HTTP 200** + the raw exception message (may leak internals) → proper status codes (402/409/502) + Problem Details, generic message, details only in logs.
3. **No idempotency key** → a retry double-charges. PSPs support an idempotency key: pass it through.
4. `float` amount? (check the model) → integer minor units + currency.
5. **Sync PSP call without a timeout**; the ambiguous timeout (charged or not?) → query by idempotency key/reference before retrying.
6. `def` in FastAPI runs in a threadpool: fine, but say it if asked about async.
</details>

### CR-10 ★★ Cache-aside with a stampede, Go
```go
func (s *Search) Get(ctx context.Context, route string) ([]Flight, error) {
    if v, err := s.redis.Get(ctx, route).Result(); err == nil {
        var f []Flight
        json.Unmarshal([]byte(v), &f)
        return f, nil
    }
    flights, err := s.suppliers.FetchAll(ctx, route)   // ~1.5 s, metered
    if err != nil {
        return nil, err
    }
    b, _ := json.Marshal(flights)
    s.redis.Set(ctx, route, b, 0)
    return flights, nil
}
```
<details><summary>Answer key</summary>

1. **TTL 0 = never expires** → stale prices forever. → A TTL by volatility (e.g. 60 s price) + jitter.
2. **Cache stampede**: on a miss for a hot route, 1,000 concurrent requests all call the metered suppliers. → `singleflight.Group` (in-process) and/or a Redis lock / "stale-while-revalidate" (serve stale, refresh async once).
3. **Redis errors are treated as a miss** (any `err`, including Redis down) → every request hits suppliers → cost/rate-limit blow-up exactly when Redis is down. → Distinguish `redis.Nil` from errors; a circuit breaker around the supplier fallback.
4. Ignored errors (`Unmarshal`, `Marshal`, `Set`) → a corrupted cache value returns an empty list silently.
5. Caches *errors*? No, and that's good. But consider **negative caching** of "no flights" for a short TTL.
6. Key design: `route` alone ignores date/pax/currency → wrong results across dates. Normalise and version the key (`v1:BKK:SIN:2026-12-01:2A`).
</details>

### CR-11 ★ Config and resource handling, Java
```java
public class SupplierGateway {
    public String fetch(String hotelId) throws IOException {
        ObjectMapper mapper = new ObjectMapper();
        Properties p = new Properties();
        p.load(new FileInputStream("/etc/app/supplier.properties"));
        URL url = new URL(p.getProperty("endpoint") + "/hotels/" + hotelId);
        HttpURLConnection c = (HttpURLConnection) url.openConnection();
        InputStream in = c.getInputStream();
        return mapper.readTree(in).get("rates").toString();
    }
}
```
<details><summary>Answer key</summary>

1. **Expensive initialisation per call**: a new `ObjectMapper` (costly, thread-safe once configured) and **reading a properties file from disk on every call** → load config once at startup (inject it), share the `ObjectMapper`.
2. **Resource leaks**: the `FileInputStream`, `InputStream` and connection are never closed → try-with-resources; `disconnect`.
3. **No timeouts** (`HttpURLConnection` defaults to infinite) → `setConnectTimeout`/`setReadTimeout`, or the modern `HttpClient`.
4. **No status check**: a 4xx/5xx throws `IOException` from `getInputStream` with no context; no retry policy.
5. **`hotelId` unencoded in the path** → path injection (`../admin`) → URL-encode/validate the format.
6. `.get("rates")` → NPE if the field is missing → validate the schema.
7. No auth to the supplier at all? (likely missing).
</details>

### CR-12 ★★ The "strategy" refactor prompt, Python
> *"This works. How would you change it so adding suppliers is easier, and what else would you change?"*
```python
def get_price(supplier, hotel_id, dates):
    if supplier == "expedia_like":
        conn = psycopg2.connect(DSN)
        cur = conn.cursor()
        cur.execute(f"select price from cache where hotel='{hotel_id}'")
        row = cur.fetchone()
        if row: return row[0]
        return requests.get(f"https://x.example/api?h={hotel_id}&k=KEY123").json()["p"]
    elif supplier == "chain_direct":
        return requests.post("https://chain.example/rates", json={"hotel": hotel_id, "d": dates},
                             headers={"auth": "KEY456"}).json()["rate"]["amount"]
    elif supplier == "channel_mgr":
        ...  # 60 more lines
```
<details><summary>Answer key</summary>

- **Strategy/Adapter**: `class PriceProvider(Protocol): def get_price(self, hotel_id: str, dates: DateRange) -> Money`, one class per supplier, holding its own client, auth and mapping. A **registry/factory** `PROVIDERS: dict[str, PriceProvider]` built at startup from config (DI). The caller does `PROVIDERS[supplier].get_price(...)` (with an `UnknownSupplier` error). Adding a supplier = a new class + registration; existing code is untouched (OCP).
- **Decorators** for cross-cutting concerns: `CachedProvider(RetryingProvider(TimedProvider(ChainDirect())))`: caching, retries, metrics and timeouts written once.
- Then the fundamentals: SQL injection (f-string SQL), a DB connection per call, hardcoded keys, no timeouts, no status checks, `["p"]` KeyErrors, money as a float, mixed responsibilities (cache lookup inside a supplier branch). The cache belongs in front of all providers, not inside one.
- Tests: each provider tested against a stub HTTP server with recorded responses; the registry tested for unknown suppliers.
</details>

---

## 5. Self-score after each snippet
| Did I… | ✔ |
|---|---|
| State the intent in one sentence first? | |
| Catch every **security** and **data-integrity** issue? | |
| Prioritise aloud (blocking vs suggestion vs nit)? | |
| Propose a concrete fix/refactor for the top 2? | |
| Mention how I'd **test** the fix? | |
| Use positive, labelled comment phrasing? | |
| Finish within 4 minutes (8 for CR-1)? | |
