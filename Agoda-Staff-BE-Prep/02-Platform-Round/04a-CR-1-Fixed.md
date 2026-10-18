# CR-1 fixed: the booking service after the review

> Companion to [04-Code-Review.md](04-Code-Review.md) CR-1. Same service, with the **important** issues fixed (correctness, DB, security, reliability, design), in **Python, Java and Go**. Sketches, not production code: helper types (`Offer`, `BookingRequest`, `Result`…) are assumed.
> **Case B** (we own the inventory). For **Case A** (the supplier owns it), delete the inventory `UPDATE` from T1; `reserve()` becomes the real hold.

## What changed (the review → the fix)
| Review finding | Fix in the code below |
|---|---|
| SQL built by string concatenation (injection) | Parameters everywhere (`%s` / `?` / `$1`) |
| Check-then-act race → double booking | One conditional `UPDATE … AND available >= qty` over all nights + **row count == nights** |
| Supplier booked before we save; no transaction | **The sandwich:** T1 (key + hold nights + PENDING) → payment + supplier, no transaction → T2 (CONFIRMED + outbox + stored reply); compensate on failure |
| No idempotency (client retries book twice) | `INSERT … ON CONFLICT (key) DO NOTHING` on `idempotency_keys`; a duplicate replays the stored reply |
| Client sends `price` as `double` | Price comes from `pricing.revalidate(offer_id)` on the server, as a decimal |
| Card number in logs; raw card in the service | Only a **payment token** from the PSP; logs carry the booking ID, never card data |
| Hardcoded API key and DB `root/root`; key in the URL | Injected config/secrets; the key goes in a header inside each supplier client |
| New DB connection and HTTP client per call; never closed | An injected **pool** and a shared HTTP client; `with` / try-with-resources / `defer` |
| No timeouts | Every supplier call gets a deadline (`timeout=` / `Duration` / `context.WithTimeout`) |
| if/else per supplier | `SupplierClient` interface + a `{name: client}` map (strategy), injected |
| Swallowed exceptions, `return null` | Specific errors: SoldOut, UnknownSupplier, PaymentDeclined; a supplier timeout → PENDING |
| `getBookings(userId)`: IDOR, unbounded | The user comes from the **auth token**; cursor pagination with a capped limit; explicit columns |

---

## Python
```python
class SupplierClient(Protocol):                       # strategy: one implementation per supplier
    def reserve(self, offer, client_ref: str, timeout_s: float) -> str: ...   # returns the supplier's booking ref

class SupplierAClient:
    def __init__(self, http, base_url, api_key):      # shared requests.Session (pooled); key from a secret store
        self.http, self.base_url, self.api_key = http, base_url, api_key
    def reserve(self, offer, client_ref, timeout_s):
        r = self.http.post(f"{self.base_url}/book", json={"hotel": offer.hotel_id, "ref": client_ref},
                           headers={"X-Api-Key": self.api_key}, timeout=(0.3, timeout_s))  # connect, read
        if r.status_code == 409: raise SupplierSoldOut()
        r.raise_for_status()
        return r.json()["confirmation_id"]

class BookingService:
    def __init__(self, db, suppliers: dict, pricing, payments):      # everything injected → testable with fakes
        self.db, self.suppliers, self.pricing, self.payments = db, suppliers, pricing, payments

    def book(self, user_id, req, idem_key):            # user_id comes from the auth token, not the request
        offer = self.pricing.revalidate(req.offer_id)  # server-side price; the client never sends one
        supplier = self.suppliers.get(offer.supplier)
        if supplier is None: raise UnknownSupplier(offer.supplier)
        nights = (req.check_out - req.check_in).days

        # ── T1: milliseconds ────────────────────────────────────────────────
        with self.db.transaction() as tx:              # any exception inside → ROLLBACK
            claimed = tx.execute("INSERT INTO idempotency_keys(key, req_hash, status) VALUES (%s, %s, 'IN_PROGRESS') "
                                 "ON CONFLICT (key) DO NOTHING", (idem_key, req.hash())).rowcount
            if not claimed:
                return self.replay(idem_key, req)      # duplicate: stored reply, 409 if still running, 422 if the body differs
            held = tx.execute("UPDATE inventory SET available = available - %s "
                              "WHERE hotel_id = %s AND room_type = %s AND date >= %s AND date < %s AND available >= %s",
                              (req.qty, offer.hotel_id, offer.room_type, req.check_in, req.check_out, req.qty)).rowcount
            if held != nights: raise SoldOut()         # some night is full → ROLLBACK undoes everything
            booking_id = tx.insert_booking(user_id, offer, req, status="PENDING")
            tx.execute("UPDATE idempotency_keys SET booking_id = %s WHERE key = %s", (booking_id, idem_key))

        # ── remote calls: no transaction open ─────────────────────────────────
        auth = None
        try:
            auth = self.payments.authorise(req.payment_token, offer.price)   # a PSP token, never a raw card
            supplier_ref = supplier.reserve(offer, client_ref=str(booking_id), timeout_s=0.8)
        except SupplierTimeout:
            return Result(booking_id, "PENDING")       # outcome unknown: don't compensate; the reconciler finishes it
        except (PaymentDeclined, SupplierSoldOut) as e:
            self.compensate(booking_id, req, offer, auth, reason=str(e))      # nights back, void auth, FAILED
            raise

        # ── T2: milliseconds ────────────────────────────────────────────────
        reply = {"booking_id": booking_id, "status": "CONFIRMED"}
        with self.db.transaction() as tx:
            tx.execute("UPDATE bookings SET status = 'CONFIRMED', supplier_ref = %s WHERE id = %s", (supplier_ref, booking_id))
            tx.execute("INSERT INTO outbox(event, booking_id) VALUES ('BookingConfirmed', %s)", (booking_id,))
            tx.execute("UPDATE idempotency_keys SET status = 'DONE', response = %s WHERE key = %s", (json.dumps(reply), idem_key))
        self.payments.capture(auth)
        log.info("booking confirmed", extra={"booking_id": booking_id, "supplier": offer.supplier})   # no card data
        return Result(booking_id, "CONFIRMED", supplier_ref)

    def get_bookings(self, user_id, after_id=0, limit=50):   # user_id from the token → no IDOR
        limit = min(limit, 100)                               # cap the page size
        rows = self.db.query("SELECT id, hotel_id, check_in, check_out, status FROM bookings "
                             "WHERE user_id = %s AND id > %s ORDER BY id LIMIT %s", (user_id, after_id, limit))
        next_cursor = rows[-1].id if len(rows) == limit else None
        return rows, next_cursor
```

## Java
```java
public interface SupplierClient {                       // strategy: one implementation per supplier
    String reserve(Offer offer, String clientRef, Duration timeout)
            throws SupplierSoldOutException, SupplierTimeoutException;   // returns the supplier's booking ref
}

public final class BookingService {
    private final DataSource db;                          // a pool (e.g. HikariCP), injected
    private final Map<String, SupplierClient> suppliers;  // strategy registry, injected
    private final PricingService pricing;
    private final PaymentGateway payments;

    public BookingService(DataSource db, Map<String, SupplierClient> suppliers,
                          PricingService pricing, PaymentGateway payments) {
        this.db = db; this.suppliers = suppliers; this.pricing = pricing; this.payments = payments;
    }

    public BookingResult book(String userId, BookingRequest req, String idemKey) throws Exception {  // userId from the token
        Offer offer = pricing.revalidate(req.offerId());                  // server-side price (BigDecimal)
        SupplierClient supplier = Optional.ofNullable(suppliers.get(offer.supplier()))
                .orElseThrow(() -> new UnknownSupplierException(offer.supplier()));
        long nights = ChronoUnit.DAYS.between(req.checkIn(), req.checkOut());

        // ── T1: milliseconds ──
        Long bookingId = inTx(conn -> {
            if (update(conn, "INSERT INTO idempotency_keys(key, req_hash, status) VALUES (?, ?, 'IN_PROGRESS') "
                           + "ON CONFLICT (key) DO NOTHING", idemKey, req.hash()) == 0) return null;   // duplicate
            int held = update(conn, "UPDATE inventory SET available = available - ? WHERE hotel_id = ? AND room_type = ? "
                           + "AND date >= ? AND date < ? AND available >= ?",
                           req.qty(), offer.hotelId(), offer.roomType(), req.checkIn(), req.checkOut(), req.qty());
            if (held != nights) throw new SoldOutException();             // → rollback
            long id = insertBooking(conn, userId, offer, req, "PENDING");
            update(conn, "UPDATE idempotency_keys SET booking_id = ? WHERE key = ?", id, idemKey);
            return id;
        });
        if (bookingId == null) return replay(idemKey, req);

        // ── remote calls: no transaction open ──
        PaymentAuth auth = null;
        final String supplierRef;
        try {
            auth = payments.authorise(req.paymentToken(), offer.price()); // a PSP token, never a raw card
            supplierRef = supplier.reserve(offer, bookingId.toString(), Duration.ofMillis(800));
        } catch (SupplierTimeoutException e) {
            return BookingResult.pending(bookingId);                      // unknown → the reconciler finishes it
        } catch (PaymentDeclinedException | SupplierSoldOutException e) {
            compensate(bookingId, req, offer, auth, e.getMessage());     // nights back, void auth, FAILED
            throw e;
        }

        // ── T2: milliseconds ──
        BookingResult result = BookingResult.confirmed(bookingId, supplierRef);
        inTx(conn -> {
            update(conn, "UPDATE bookings SET status = 'CONFIRMED', supplier_ref = ? WHERE id = ?", supplierRef, bookingId);
            update(conn, "INSERT INTO outbox(event, booking_id) VALUES ('BookingConfirmed', ?)", bookingId);
            update(conn, "UPDATE idempotency_keys SET status = 'DONE', response = ? WHERE key = ?", toJson(result), idemKey);
            return null;
        });
        payments.capture(auth);
        log.info("booking confirmed bookingId={} supplier={}", bookingId, offer.supplier());   // no card data
        return result;
    }

    public Page<BookingSummary> getBookings(String userId, long afterId, int limit) throws SQLException {  // userId from the token
        int size = Math.min(limit, 100);
        try (Connection c = db.getConnection();
             PreparedStatement ps = c.prepareStatement("SELECT id, hotel_id, check_in, check_out, status FROM bookings "
                                                     + "WHERE user_id = ? AND id > ? ORDER BY id LIMIT ?")) {
            ps.setString(1, userId); ps.setLong(2, afterId); ps.setInt(3, size);
            return Page.of(mapAll(ps.executeQuery()), size);              // next cursor = last id if the page is full
        }
    }

    // helpers: every connection returns to the pool; every SQL statement uses parameters
    private <T> T inTx(SqlWork<T> work) throws Exception {
        try (Connection conn = db.getConnection()) {
            conn.setAutoCommit(false);
            try { T out = work.run(conn); conn.commit(); return out; }
            catch (Exception e) { conn.rollback(); throw e; }
        }
    }
    private static int update(Connection c, String sql, Object... args) throws SQLException {
        try (PreparedStatement ps = c.prepareStatement(sql)) {
            for (int i = 0; i < args.length; i++) ps.setObject(i + 1, args[i]);
            return ps.executeUpdate();                                    // = the row count
        }
    }
}
```

## Go
```go
type SupplierClient interface { // strategy: one implementation per supplier
	Reserve(ctx context.Context, offer Offer, clientRef string) (supplierRef string, err error)
}

type BookingService struct {
	db        *sql.DB                   // a pool: one per app, injected
	suppliers map[string]SupplierClient // strategy registry, injected
	pricing   Pricing
	payments  Payments
}

func (s *BookingService) Book(ctx context.Context, userID string, req BookingRequest, idemKey string) (Result, error) {
	offer, err := s.pricing.Revalidate(ctx, req.OfferID) // server-side price
	if err != nil {
		return Result{}, err
	}
	supplier, ok := s.suppliers[offer.Supplier]
	if !ok {
		return Result{}, ErrUnknownSupplier
	}
	nights := int64(req.CheckOut.Sub(req.CheckIn).Hours() / 24)

	// ── T1: milliseconds ──
	var bookingID int64
	err = s.inTx(ctx, func(tx *sql.Tx) error {
		res, err := tx.ExecContext(ctx, `INSERT INTO idempotency_keys(key, req_hash, status)
			VALUES ($1, $2, 'IN_PROGRESS') ON CONFLICT (key) DO NOTHING`, idemKey, req.Hash())
		if err != nil {
			return err
		}
		if n, _ := res.RowsAffected(); n == 0 {
			return errDuplicate
		}
		res, err = tx.ExecContext(ctx, `UPDATE inventory SET available = available - $1
			WHERE hotel_id = $2 AND room_type = $3 AND date >= $4 AND date < $5 AND available >= $1`,
			req.Qty, offer.HotelID, offer.RoomType, req.CheckIn, req.CheckOut)
		if err != nil {
			return err
		}
		if n, _ := res.RowsAffected(); n != nights {
			return ErrSoldOut // → rollback
		}
		if err := tx.QueryRowContext(ctx, `INSERT INTO bookings(user_id, offer_id, check_in, check_out, qty, status)
			VALUES ($1, $2, $3, $4, $5, 'PENDING') RETURNING id`,
			userID, offer.ID, req.CheckIn, req.CheckOut, req.Qty).Scan(&bookingID); err != nil {
			return err
		}
		_, err = tx.ExecContext(ctx, `UPDATE idempotency_keys SET booking_id = $1 WHERE key = $2`, bookingID, idemKey)
		return err
	})
	if errors.Is(err, errDuplicate) {
		return s.replay(ctx, idemKey, req)
	}
	if err != nil {
		return Result{}, err
	}

	// ── remote calls: no transaction open ──
	auth, err := s.payments.Authorise(ctx, req.PaymentToken, offer.Price) // a PSP token, never a raw card
	if err != nil {
		s.compensate(ctx, bookingID, req, offer, nil, err)
		return Result{}, err
	}
	callCtx, cancel := context.WithTimeout(ctx, 800*time.Millisecond) // the supplier's deadline
	defer cancel()
	supplierRef, err := supplier.Reserve(callCtx, offer, strconv.FormatInt(bookingID, 10))
	switch {
	case errors.Is(err, context.DeadlineExceeded):
		return Result{BookingID: bookingID, Status: "PENDING"}, nil // unknown → the reconciler finishes it
	case err != nil:
		s.compensate(ctx, bookingID, req, offer, auth, err) // nights back, void auth, FAILED
		return Result{}, err
	}

	// ── T2: milliseconds ──
	result := Result{BookingID: bookingID, Status: "CONFIRMED", SupplierRef: supplierRef}
	err = s.inTx(ctx, func(tx *sql.Tx) error {
		if _, err := tx.ExecContext(ctx, `UPDATE bookings SET status = 'CONFIRMED', supplier_ref = $1 WHERE id = $2`,
			supplierRef, bookingID); err != nil {
			return err
		}
		if _, err := tx.ExecContext(ctx, `INSERT INTO outbox(event, booking_id) VALUES ('BookingConfirmed', $1)`,
			bookingID); err != nil {
			return err
		}
		_, err := tx.ExecContext(ctx, `UPDATE idempotency_keys SET status = 'DONE', response = $1 WHERE key = $2`,
			result.JSON(), idemKey)
		return err
	})
	if err != nil {
		return Result{}, err // the reconciler will see a PENDING booking with a supplier ref and finish it
	}
	s.payments.Capture(ctx, auth)
	slog.Info("booking confirmed", "booking_id", bookingID, "supplier", offer.Supplier) // no card data
	return result, nil
}

// inTx: COMMIT if fn succeeds; any early return rolls back (Rollback after Commit is a no-op)
func (s *BookingService) inTx(ctx context.Context, fn func(*sql.Tx) error) error {
	tx, err := s.db.BeginTx(ctx, nil)
	if err != nil {
		return err
	}
	defer tx.Rollback()
	if err := fn(tx); err != nil {
		return err
	}
	return tx.Commit()
}
```

## Which language to use in the interview
- **Read Java fluently enough.** Agoda's snippets are JVM-style (Java, Kotlin, Scala, C#), so you need to *recognise* `PreparedStatement`, try-with-resources, `@Transactional`, `Optional`.
- **Write fixes as Python-style pseudocode.** It's the shortest to write, and the structure (T1 → remote calls → T2) is the most visible. Say: *"I'm a C++ engineer; I'll sketch the fix in Python-style pseudocode."*
- **Go** is closest to C: explicit errors, and `context` carries the deadline. It's good to recognise, but verbose to write on a whiteboard.
