# Interview numbers: which sum, when, and what it decides

> Built on 20 Oct after Mock 1, where the 98% hit ratio had to be handed over. **The sums are easy; knowing which one to do is the skill.** Every section: the one-line formula → an example from our scenarios → **what it decides** → the sentence to say.
> Rule for all of them: **write the unit next to every number** (`/s`, `/day`, `s`). Every slip so far (2 billion, "5 billion per second", "trillions") happened when the unit fell off.

---

## 0. The only numbers to memorise

| Thing | Use this | (Real value, for the curious) |
|---|---|---|
| Seconds in a day | **10⁵** | 86,400: 15% less; nobody minds in an interview |
| So **1 /s** is about | **100k /day** | 86k |
| So **1,000 /s** is about | **100 million /day** | 86 M |
| Seconds in a month | **3 × 10⁶** | 2.6 M |
| A call inside the data centre | **~1 ms** | 0.5–1 ms |
| A DB commit | **~5–10 ms** | fsync of the log |
| A supplier / third-party HTTP call | **~100–500 ms** (p99 can be seconds) | |
| Cross-region call | **~100 ms** | 50–150 ms |

**Say it as:** "I'll round a day to 10⁵ seconds."

---

## 1. ★★★ "Can the supplier take our traffic?" (demand vs their limit)

**The sum that changed Mock 1.** Do it **right after clarifying**, every time there's a supplier limit or a per-call price.

```
calls we'd need  = our rate × miss ratio × suppliers asked
max miss ratio   = their limit ÷ our rate
hit ratio needed = 1 − (their limit ÷ our rate)
```
**Trick for the division:** turn it into "1 in N". 5 out of 300 = **1 in 60** ≈ 1.7% may miss → **98%+ must hit**.

| Scenario | Our rate | Their limit | May miss | Hit needed |
|---|---|---|---|---|
| Mock 1, Supplier A | 300 searches/s | 5 /s | 1 in 60 | **98%** |
| Same, but limit 50/s | 300 /s | 50 /s | 1 in 6 | 83% |
| Same, but 3 suppliers each 5/s | 300 /s | 5 /s each | 1 in 60 each | 98% (per supplier) |

**What it decides:**
| Hit ratio needed | Design |
|---|---|
| below ~80% | A cache on the request path is enough |
| ~80–95% | Cache + stale-while-revalidate + single-flight on a miss |
| **above ~95%, with long-tail keys** (location + time, route + date) | **Don't call the supplier on the request path.** Pull in the background into our own store; search reads only our store. Ask for more keys, a bulk or delta endpoint, or push (webhooks) |

**Say:** *"300 searches a second against A's 5 means 1 in 60 may miss, a 98% hit ratio. That's unrealistic for location plus time, so A can't sit on the search path; we pull A in the background and search reads our store."*

🔑 *Unki limit ÷ hamari speed = kitne miss chalenge. 95% se zyada hit chahiye? Toh request path se hatao.* (Their limit ÷ our rate = how many misses we can afford. Need more than 95% hits? Take the supplier off the request path.)

---

## 2. ★★★ The daily budget (how much background pulling can we do?)

```
calls per day = their limit × 10⁵
```
| Limit | Per day | Spend it like |
|---|---|---|
| 5 /s (Mock 1, A) | **500k /day** | 1,000 hot location-days × every 15 min (96/day) ≈ 100k; warm hourly; the rest on misses + booking re-checks |
| 10 /s (S4) | 1 M /day | a full 2M-hotel sync needs 20k pages ≈ 2% of it, so the limit isn't the bottleneck |
| 200 /s (S1-style) | 20 M /day | |

**Keep ~20% headroom** (use 8 of 10): a 429 or a ban costs more than the 20%.
**Reserve some for booking:** a booking must re-check availability live; never let the background job eat those tokens.

**Say:** *"5 a second is about 500k calls a day. I'd spend most on refreshing the hot keys, keep some for cache misses, and reserve some for booking re-checks."*

---

## 3. ★★★ Cost and look-to-book (does each booking pay for its searches?)

**Look-to-book** = searches per booking. 100:1 means 100 searches for every booking.

```
supplier cost per booking = look-to-book × calls per search × miss ratio × price per call
```
| Example | Cost per booking | vs ~$5 commission |
|---|---|---|
| 100:1 × 3 suppliers × 100% miss × $0.002 | 100 × 3 × 1 × 0.002 = **$0.60** | fine |
| 1,000:1 (bots, comparison sites) × same | **$6.00** | **we lose money on every booking** |
| 1,000:1 with a 90% hit cache | $0.60 | fine again |

**Total per day:** `calls/s × 10⁵ × price`. S1: 3,000 searches/s × 2 suppliers = 6,000 calls/s × 10⁵ = 6 × 10⁸/day × $0.001 = **$600k/day**.

**What it decides:** cache aggressively, **rate-limit bots and scrapers at the gateway**, and track **cost per booking** as the business metric.

**Say:** *"At 100 looks per book, each booking carries about 60 cents of supplier calls; if bots push it to 1,000:1, we pay more than we earn, so the cache and bot limits are a business requirement."*

---

## 4. ★★★ Little's Law: threads, connections, workers, bulkheads

**One formula covers all of them:**
```
things in flight (L) = arrival rate (λ) × time each one is held (W)
```
"In flight" = threads blocked, connections busy, requests waiting. **W is how long each one is held: the latency, capped by your timeout.**

**You never simulate second by second. One multiplication:**
| Question | λ × W | Answer |
|---|---|---|
| Threads stuck on slow Supplier B at p99 | 300 /s × 4 s | **1,200 threads** |
| Same, with a **0.8 s timeout** | 300 /s × 0.8 s | **240 at most** (the timeout caps W) |
| Workers to reach 8 req/s when a call takes 0.3 s (S4) | 8 /s × 0.3 s | 2.4 → **3 workers** |
| DB connections: 2,000 queries/s × 5 ms | 2,000 × 0.005 | **10 connections** |
| Search requests waiting at a cache stampede (S5) | 5,000 /s × 0.8 s | **4,000 waiting** |

**The timeout trick for any timeout:** the worst case is `rate × timeout`. A 0.8 s timeout means "at most 0.8 s × rate are ever waiting". Nothing more to compute.

### The bulkhead as a number
A **bulkhead** = a hard cap of **N slots** for calls to one supplier. Slot taken → call; no slot free → **fail fast** (skip that supplier, partial results). No queue grows, because nothing waits for a slot.

```
max rate a bulkhead can serve = N ÷ W
```
| Supplier B | N | W | Serves at most | Our rate | Result |
|---|---|---|---|---|---|
| healthy (p50) | 100 | 1.2 s | 100 ÷ 1.2 ≈ **83 /s** | 300 /s | ~217/s skip B → partial results, A and C still fast |
| slow, timeout 0.8 s | 100 | 0.8 s | **125 /s** | 300 /s | 175/s skip B |
| no bulkhead | ∞ | 4 s | — | 300 /s | **1,200 threads on B** → the pool shared with A and C is gone → **everything** is slow |

**When does a queue grow?** Only when **arrivals > what the slots can serve**, i.e. `λ > N ÷ W`. Then it grows by `λ − N/W` **every second, forever**, until memory or timeouts kill it.
**So the rule:** a queue in front of a slow dependency must be **bounded** (small) or **absent** (fail fast). Never unbounded.

**Say:** *"300 a second times 4 seconds is 1,200 threads stuck on B, which would starve A and C. I cap B at 100 slots; at 1.2 seconds that serves about 80 a second, and the rest skip B and get partial results."*

**C++ analogy:** the bulkhead is a `std::counting_semaphore<100>` with `try_acquire()` (not `acquire()`): if no permit, return "B skipped" immediately instead of blocking.

🔑 *Andar kitne = rate × time. Timeout = time ki chhat. Bulkhead = N kursi, kursi nahi toh skip.* (How many inside = rate × time. The timeout is the ceiling on time. Bulkhead = N chairs; no chair, skip.)

---

## 5. ★★ Stampede (how bad is a TTL expiry?)

```
jobs at expiry ≈ rate × time to refill   vs   capacity
```
S5: 5,000 searches/s × 0.8 s = **4,000 pricing jobs** vs capacity **50 /s** → **80× overload**, every TTL.
**What it decides:** single-flight, stale-while-revalidate, TTL jitter. **Say the multiple** ("80 times what pricing can take").

---

## 6. ★★ Batch jobs (how long, and where does the time go?)

```
time = items ÷ rate                      (the floor the supplier allows)
cost per item = observed time ÷ items    (work backwards from the symptom)
```
S4: 20,000 pages ÷ 10/s = 2,000 s ≈ **33 min** floor. Observed 9 h ≈ 3 × 10⁴ s ÷ 2 × 10⁶ inserts ≈ **15 ms each** → per-row commits are the bottleneck → batch per page.
**What it decides:** whether the slowness is theirs (the limit) or ours (our writes, our loops).

---

## 7. ★★ Async and reconciliation load

```
stuck items per minute = rate × failure % × 60
```
S2: 50 bookings/s × 1% timeouts = 0.5/s ≈ **30 PENDING a minute** → the reconciler checks every 30 s, easily done long before a 7-day auth hold expires.
**What it decides:** that the reconciler is small and the PENDING state is safe.

---

## 8. ★★ Availability across synchronous hops

```
availability of a chain = product of each hop
```
3 sync hops at 99.9% each = 99.9³ ≈ **99.7%** (3× the downtime). 5 suppliers in a row at 99% = **95%**.
**What it decides:** fan out in parallel with partial results, or go async, instead of chaining.

---

## 9. ★ Storage and bandwidth (rarely decides anything; do it last, if asked)

```
bytes per day = items/day × size
```
30 M searches/day × 1 KB log = **30 GB/day** ≈ 1 TB/month. Usually the answer is "fine, retention + cheap storage".

---

## 10. Which sum to reach for (read the prompt for these signals)

| The prompt says… | Do this sum first | Section |
|---|---|---|
| "supplier allows N req/s", "per API key" | demand vs limit → hit ratio | §1, §2 |
| "metered", "we pay per call", "costs went up" | cost/day, cost per booking | §3 |
| "look-to-book", "bots", "scrapers" | cost per booking at 100:1 vs 1,000:1 | §3 |
| "slow supplier", "p99 = 4 s", "timeouts", "threads" | rate × time held; bulkhead N ÷ W | §4 |
| "spikes every few minutes", "CPU 100% periodically" | stampede: rate × refill time vs capacity | §5 |
| "nightly job takes 9 hours", "doesn't finish" | items ÷ rate; observed ÷ items | §6 |
| "ambiguous timeout", "PENDING", "reconciler" | rate × failure % | §7 |
| "calls A, then B, then C" | availability product; latency sum | §8 |

**The order in the interview:** clarify → **one sum from this table, aloud, with units** → the design consequence in one sentence → then the boxes.

---

## 11. Practice (answer aloud, then open)

1. 2,000 searches/s, each calls 4 suppliers; supplier X allows 20 req/s. Hit ratio needed for X?
2. Same supplier X: calls per day available?
3. Look-to-book 200:1, 4 suppliers, 50% hit ratio, $0.001 per call. Supplier cost per booking?
4. 500 req/s to a supplier with p99 2 s and no timeout. Threads stuck at p99? With a 0.5 s timeout?
5. A bulkhead of 50 slots, calls take 0.25 s. Max rate it serves? At 300 /s, how many skip?
6. A TTL expires on a key with 2,000 hits/s; a refill takes 1 s; the backend handles 20/s. Overload multiple?

<details><summary>Answers</summary>

1. 20 ÷ 2,000 = 1 in 100 may miss → **99%** hit → off the request path; background pull.
2. 20 × 10⁵ = **2 M calls/day**.
3. 200 × 4 × 0.5 × $0.001 = **$0.40** per booking.
4. 500 × 2 = **1,000** threads; with the timeout 500 × 0.5 = **250**.
5. 50 ÷ 0.25 = **200 /s**; at 300 /s, **100/s skip** (partial results).
6. 2,000 × 1 = 2,000 jobs vs 20/s → **100×**.
</details>

---

## 12. HTTP/2 multiplexing (why gRPC sends many calls on one connection)

**First, one fix to the mental model:** a TCP connection is **already two-way** (full duplex): one socket carries bytes in both directions. There aren't two channels to manage. Multiplexing is about something else: **how many requests can share that one connection at the same time.**

**HTTP/1.1: one request at a time per connection.**
```
connection 1:  [req A ──────── resp A][req B ── resp B][req C ─ resp C]
               B and C wait behind A (head-of-line blocking)
→ browsers open ~6 connections per site to get parallelism
```
**HTTP/2: chop every message into small frames, each tagged with a stream ID, and interleave them.**
```
one connection, client → server:  [A:1][B:1][C:1][A:2][B:2] ...
one connection, server → client:  [C:1][A:1][C:2]                  ← replies in any order
receiver: frames with stream 3 → request C, stream 5 → request A …  (reassemble by ID)
```
So 100 gRPC calls in flight can share **one** TCP connection; a slow reply doesn't block a fast one.

**C++ analogy:** one socket; every message has a header `{stream_id, length}`; a reader thread puts each frame in `std::unordered_map<stream_id, std::promise<Reply>>`, and each caller waits on its own `future`. That's all multiplexing is.

**Why it matters in the interview:**
- **Load balancing:** an L4 balancer picks a server **per connection**. With one long-lived HTTP/2 connection, all calls go to **one server**. gRPC needs **L7 (per-request) balancing** or client-side balancing.
- **One catch:** it's still one TCP stream underneath. A lost packet stalls **all** streams until it's resent (TCP head-of-line). HTTP/3 (QUIC, over UDP) fixes that.
- **gRPC vs REST in one breath:** gRPC = HTTP/2 multiplexing + binary protobuf + streaming + deadlines carried across calls + generated clients; **trade-offs:** browsers can't call it directly, it's harder to debug with curl, and it needs L7 balancing.

🔑 *Ek pipe, bahut saare chhote dabbe, har dabbe pe number.* (One pipe, many small boxes, a number on each box.)

---

## 13. Backpressure, the production version

**Who is under pressure, and who says what to whom:**
- **Downstream** = the one doing the work (slower). **Upstream** = the one sending work.
- **Backpressure = the downstream telling its upstream "slow down"**, and that signal travelling **back up, hop by hop**, to whoever started the work.
- Without it, the downstream doesn't say anything; work just piles up somewhere unbounded until something crashes.

### A real failure (S3's pipeline)
```
Channel managers ──► Ingest API ──► Kafka ──► Writers (consumers) ──► MySQL
                                                                     index rebuild:
                                                                     10 ms → 200 ms per write
```
**Without backpressure:**
1. MySQL slows to 200 ms per write.
2. Writers keep spawning threads and connections to keep up → MySQL connections maxed → MySQL slows further.
3. Kafka lag grows: 1 min → 20 min → 2 h. Partners see "my price takes 20 minutes".
4. The Ingest API keeps answering `202` happily, so partners keep sending at full speed. Nobody upstream knows.

**With backpressure (each hop pushes back on the one before it):**
| Hop | The signal | What happens |
|---|---|---|
| MySQL → Writers | slow commits | Writers use a **fixed pool** (Little's Law: e.g. 20 connections). They don't add more; they just consume more slowly. |
| Writers → Kafka | Kafka is **pull**-based: consumers only fetch what they can handle | The backlog waits **in Kafka** (durable, bounded by retention). **Lag** is the measurable pressure. |
| Kafka → Ingest API | the Ingest API checks consumer lag | Lag > 5 min → the API returns **`429` + `Retry-After: 30`** (or `503`) instead of `202` |
| Ingest API → Channel managers | the 429 | Their client backs off and resends later. **The pressure reached the source.** Nothing is lost; it's delayed and controlled. |

### The three things a full downstream can do (only these three)
1. **Buffer**, but **bounded**: a queue with a max size, or Kafka with retention and a lag alert.
2. **Shed / drop**: reject now (`429`/`503`, partial results, skip a supplier). Fail fast.
3. **Slow the sender**: block or refuse to accept until there's room.

**What it looks like in real tech:**
| Tech | Backpressure mechanism |
|---|---|
| HTTP APIs | `429` / `503` + `Retry-After`; the caller backs off with jitter |
| Thread pools / bulkheads | bounded queue → reject when full (Java `ThreadPoolExecutor` with a bounded queue, `try_acquire`) |
| Kafka consumer | pull only what you can process; lag is the gauge |
| Kafka producer | broker quotas; when the producer's buffer is full, `send()` blocks (`max.block.ms`) |
| HTTP/2 / gRPC / TCP | **flow-control windows**: the receiver stops granting window, so the sender physically can't send more bytes |
| Reactive streams | the consumer calls `request(n)`: "send me n more" |

**PM version (production, 30 s):** *"When our database falls behind, instead of letting work pile up until everything crashes, each service slows the one before it, all the way back to the partner, who gets 'try again in 30 seconds'. Nothing is lost; updates arrive a bit later, and the system stays up."*

**Interview version:** *"Backpressure is the slow consumer signalling upstream: bounded queues, Kafka lag, 429 with Retry-After at the edge, and flow-control windows in gRPC. The rule is never an unbounded buffer: buffer a bounded amount, shed, or slow the sender."*

🔑 *Neeche wala dheema hai → upar wale ko bolta hai "ruk" → woh apne upar wale ko → partner tak 429.* (The one below is slow → tells the one above "wait" → which tells the one above it → all the way to the partner as a 429.)
