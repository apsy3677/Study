# Code review triggers: "I see this shape → I suspect that bug"

> One page for the day before. Pattern-match, don't analyse from scratch. Built on 19 Oct from Anuj's own list (CR-1…CR-3), with the gaps filled in.
> Method: **silent read** → only question the **boundary lines** (input, network, DB, shared state, money/maths): *"what if this fails, is slow, or runs twice?"* → speak **Kya → Kitne → Kaunse → Kaise**.

## The three phrases (remember only these 9 words)
| Tier | Phrase | Each word asks |
|---|---|---|
| 🔴 RED | ***Galat, Leak, Do Baar*** (wrong, leaked, twice) | **Galat:** is the result or number wrong (money, sort, units, dies halfway)? **Leak:** can an outsider get in or out (injection, IDOR, secrets, PII)? **Do baar:** what if it runs twice, or twice at once (retry, race)? |
| 🟡 YELLOW | ***Dheema, Toota, Mehenga*** (slow, broken, expensive) | **Dheema:** the other side is slow (timeout, deadline, sequential loop)? **Toota:** a part fails (all-or-nothing, silent catch, no status check)? **Mehenga:** what costs on every call or grows (new client per call, N+1, no limit, no cache)? |
| 🔵 BLUE | ***Jodo, Jaancho, Samjho*** (add, test, understand) | **Jodo:** adding one more supplier means editing here? **Jaancho:** testable without the network or clock? **Samjho:** one job per method, clear names? |

## The generic one-liners (the long form of the 9 words; the tables below are examples)
Ask each question of the boundary lines. A "yes / don't know" is a finding.

**RED: is anything wrong, leaked or done twice? (block the merge)**
1. **Who controls this value?** If the caller does: injection, IDOR, tampered price/quantity. Never trust it; validate or take it from the server/token.
2. **Where does this secret or personal data end up?** Code, logs, URLs, error messages, responses: all leaks.
3. **What if two requests run this at the same time?** Read-then-write on shared data = a race; make it one atomic step.
4. **What if this runs twice?** A retry or replay on a write = double booking/charge; needs an idempotency key or dedupe.
5. **What if it dies halfway?** Two writes in two systems = orphans; status + compensation, or an outbox.
6. **Is the number right?** Money type, rounding, units, currency, timezone, off-by-one, comparisons.

**YELLOW: does it survive production? (fix before it ships)**
1. **What if the other side is slow?** Every remote call needs a timeout inside one overall deadline.
2. **What if one part fails?** Does it fail everything, or degrade (partial results, fallback)?
3. **How does it grow?** Loops of remote calls, N+1, no limit/pagination, everything loaded in memory.
4. **What is created on every call?** Clients, connections, parsers, config reads: build once, inject, close.
5. **If it fails, would anyone know?** Swallowed errors, `None`/null returns, no status check, no log/metric.
6. **What does it cost when repeated?** Paid calls with no cache, retries with no backoff/budget.

**BLUE: will the team cope with it? (follow-ups)**
1. **What do I edit to add one more X?** If-chains → strategy/registry.
2. **Can I test it without the network or the clock?** `new` inside, statics, time → inject.
3. **How many jobs does this method do?** More than one → split.
4. **Would a new teammate read it right?** Names, magic numbers, comments: labelled nits.

🔑 *RED: kaun, kahan, saath, dobara, beech mein, number. YELLOW: slow, fail, badhna, har baar, pata, kharcha. BLUE: naya X, test, kaam, padhna.* (RED: who, where, together, twice, halfway, number. YELLOW: slow, fail, growth, every call, would we know, cost. BLUE: one more X, test, jobs, reading.)

---

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
