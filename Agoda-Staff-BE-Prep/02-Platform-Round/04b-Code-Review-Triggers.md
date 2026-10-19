# Code review triggers: "I see this shape → I suspect that bug"

> One page for the day before. Pattern-match, don't analyse from scratch. Built on 19 Oct from Anuj's own list (CR-1…CR-3), with the gaps filled in.
> Method: **silent read** → only question the **boundary lines** (input, network, DB, shared state, money/maths): *"what if this fails, is slow, or runs twice?"* → speak **Kya → Kitne → Kaunse → Kaise**.

## RED: money, data, security (block the merge)
| You see (Java / Python) | Bug | Fix in one line |
|---|---|---|
| `"... WHERE id = '" + id + "'"` / `f"... {id}"` / `String.format("%s", id)` / `"%s" % id` | SQL injection. **Any** text building (concat, format, f-string) is the same bug | Parameters: `ps.setString(1, id)` / `cur.execute("... = %s", (id,))` |
| `API_KEY = "sk-..."`, `"root"/"root"`, the key in a URL | Hardcoded secret, leaks via git and logs | Secret store, injected; key in a header |
| `log.info("..." + req)` / `logger.info(f"{req.dict()}")` | Card, CVV or PII in logs | Log IDs only; take a PSP token, never a raw card |
| `getBookings(userId)` with `userId` from the request | IDOR: anyone reads anyone's data | The user comes from the auth token |
| `price` taken from the request body | Price tampering | Revalidate the price on the server from `offer_id` |
| `if (available > 0) { ... available-- }` (two steps) | Check-then-act race → double booking | One conditional `UPDATE ... WHERE available >= n` + check the row count |
| `HashMap` / `dict` field in a singleton service, written per request | Data race on shared mutable state | Immutable snapshot + atomic swap, or a concurrent map |
| A POST (book, pay) inside a retry loop | Retry books or charges twice | An Idempotency-Key the other side honours |
| `double price`, `(int)(a - b)` in a comparator | Money rounding; a wrong "cheapest" | `BigDecimal` / integer minor units; `Comparator.comparing` |
| Prices from several sources compared raw | Mixed currencies / taxes → wrong order | Normalise to one currency first |
| Supplier booked, then `save()` with no status | Orphan booking if the save fails | PENDING row first, then the call, then CONFIRMED |

## YELLOW: production (resilience + performance; fix before production)
| You see | Bug | Fix |
|---|---|---|
| `for (s : suppliers) s.call()` | Sequential fan-out: latency = the sum | Parallel on a bounded pool, **one overall deadline** |
| `requests.post(url)` / `HttpClient` call with no timeout | Waits forever; threads pile up | Connect + read timeout = `min(own, time left)` |
| `catch (Exception e) { return emptyList(); }` | One failure wipes everything | Partial results + a status per source |
| `catch (Exception) {}` / `except: pass` / `return None` | Silent failure; "no data" looks like "failed" | Specific exceptions; log + metric; raise a typed error |
| `return r.json()` with no status check | A 500 error body treated as success | Check the status first (`r.ok`, `raise_for_status`) |
| `time.sleep(1)` in a retry loop; retries everything | Retry storm; retries 400/401 and bugs | Retry only temporary errors; backoff + jitter; honour `Retry-After` |
| `new SupplierApi(...)`, `new HttpClient()`, `connect()`, `requests.post` (no Session) inside the method | A new connection per call | Inject a pooled client / Session / DB pool, built once |
| A stream, connection or file never closed | Resource leak → pool exhaustion | try-with-resources / `with` / `defer` |
| A query or list with no `LIMIT` / cursor | Unbounded response, memory blow-up | Cursor (keyset) pagination, capped page size |
| A DB or HTTP call inside a loop over rows | N+1 queries | Batch: `findAllById(ids)`, one `GROUP BY` |
| `Thread.sleep` or blocking JDBC in async code | Starves the event loop / small pool | Move to an IO pool, or use async drivers |
| Every request calls the paid API, no cache | Cost + rate limit | Cache with a TTL; single-flight on a miss |

## BLUE: design and team (follow-ups, suggest kindly)
| You see | Smell | Suggest |
|---|---|---|
| `if (supplier == "A") ... else if ("B")` | Open/closed: edit for every new supplier | Strategy interface + a `{name: client}` map |
| Supplier's response format used directly | Coupling to their model | Adapter → our `Offer` |
| Retry, metrics, cache code inside the business method | Mixed concerns | Decorator / gateway, written once |
| `new` concrete class, `System.currentTimeMillis()` inside | Hard to test | Inject interfaces and a `Clock` |
| One method validates, calls, saves, charges, emails | God method (SRP) | Split into collaborators |
| Magic numbers (`5`, `1000`), unclear names | Readability | Named config; labelled **nit** |

🔑 *Bahar ki har line pe ek sawaal: fail, slow, ya do baar?* (On every line that touches the outside, one question: fails, slow, or twice?)
