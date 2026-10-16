# Prototype Labs Plan (WSL): cohort exercises, in Agoda-priority order

**Who this is for:** a Claude Code session running in WSL Ubuntu. Read this whole file before acting.
**Owner:** Anuj, about 11 years of backend/systems experience, mostly C++, some Java. New to Go, comfortable with Python.
**Source of exercises:** `/mnt/d/Git/Study/System Design/Cohort exercises-Weeks 01–08.md`, the 76 exercises from the Feb 2025 system-design cohort (concept, gotchas, verify, stretch). Theory notes: `/mnt/d/Git/Study/System Design/Arpit-Masterclass/` (one `slide-notes.md` per session).
**Goal:** build the cohort exercises **in the order that best prepares the Agoda Staff Backend loop**, with an "Agoda twist" on each, so that if time runs out (it will), the most interview-relevant ones are done.

## The interviews this plan serves

| Round | When | What it tests | Evidence |
|---|---|---|---|
| **IV2 Platform** | ~1 week from 15 Oct 2026 | A flawed design (an **aggregator over external suppliers + booking**) to fix; API design; **connectivity** (retries, idempotency, rate limits, pagination, auth, webhooks); QA strategy; **booking-service code review** | `/mnt/d/Git/Study/Agoda-Staff-BE-Prep/02-Platform-Round/00-Round-Intel.md` |
| **IV3 Architecture** | After IV2 | LLD + HLD. Reported prompts: **hotel search/booking with proximity search**, **concert booking (flash sale)**, **payment gateway at 10M DAU** (Stripe-like provider, transactions, reconciliation), Booking.com-style search + booking. "Lots of metrics and telemetry." | same folder, §2 |
| IV4 Overall + culture | Last | Past projects and judgement; hands-on depth helps here too | |

**Rule of thumb for priority:** an exercise ranks higher if (a) it shows up directly in a reported Agoda question, (b) it gives you a *"when I built this, I measured…"* story for connectivity/booking/payments, and (c) it's cheap to build.

---

## Priority list

Hours are estimates for a Go beginner pairing with Claude. **Tier 0 is the must-do before IV2.** If you're behind, do just the ★ items in order.

### Tier 0: before IV2 (Platform round), about 14 h

| P | Cohort exercise | Agoda twist (what to actually build) | Why it ranks here | Est. |
|---|---|---|---|---|
| **0** | Setup | Repo, Go/uv/Docker, `deploy/compose.yml` (Postgres, MySQL, Redis, Toxiproxy, Prometheus, Grafana, Jaeger), Makefile, CI | Everything else needs it | 1.5 h |
| **1 ★** | **W2#1 Airline check-in** (`airline-checkin/`) | **Room/seat booking API**: compare naive vs `FOR UPDATE` vs optimistic version vs **conditional `UPDATE … WHERE available > 0`**. Add an **`Idempotency-Key`** on `POST /bookings`. Stretch from the cohort: **a 5-min hold with TTL** (reserve → confirm), crash mid-hold | "Double booking" and idempotency were asked in the May 2026 Staff IV2. It's also the core of IV3's concert/flash-sale and hotel-booking prompts | 2.5 h |
| **2 ★** | **W1#1 Bounded pool** (`bounded-blocking-pool/`) | Generic pool → reuse as a **per-supplier bulkhead** (acquire timeout, `defer release`, metrics for in-use/wait time) | The building block of the gateway in P3. "Expensive DB init per call" is a recruiter-flagged code-review catch | 1 h |
| **3 ★** | **Capstone A: supplier gateway** (new; composes **W1#6 polling + ETag**, **W4#1 toy CDN** cache logic, **W8#3 Redis EVAL rate limiter**) | `fake-supplier` (Python/FastAPI: latency, errors, 429 + `Retry-After`, cursor pages, metered call counter). `gateway` (Go): parallel fan-out with an **overall deadline**, **retries with backoff + jitter** (idempotent only), **circuit breaker**, bulkhead (P2), **partial results**, **dedupe → cheapest offer**, **cache-aside + single-flight + stale-while-revalidate**, a **Redis Lua token bucket** per supplier (call budget). Toxiproxy chaos test | **This is the IV2 narrative** (the flight aggregator over metered APIs, asked in 2025 and 2026). The Gurugram rejection was for weak connectivity. Building it makes every answer concrete | 5 h |
| **4 ★** | **W8#2 Cursor pagination** (`cursor-pagination/`) + W3#10 benchmark | Paginate the gateway's search results and a `GET /bookings` listing. Measure OFFSET vs `(created_at, id)` keyset p99 at depths 1…10K | "Pagination missing → cursor vs offset" was an explicit point in the 2026 IV2 | 1 h |
| **5 ★** | **W7#9 Payment webhooks** (`payment-webhooks/`) | Build a **fake PSP** that signs (HMAC of `timestamp.body`) and **retries with backoff**. Receiver: raw-body verify with `hmac.Equal`, a replay window, `INSERT … ON CONFLICT DO NOTHING` on `event_id`, **enqueue then 200**, an async worker. Optionally run Razorpay test mode + ngrok as the cohort suggests | Webhooks are in the recruiter's list; it's also IV3's payment-gateway prompt | 1.5 h |
| **6** | **W4#6 JWT auth** (guidance) | Add auth to the booking API: RS256, pinned alg, short expiry + refresh, `jti` denylist. Plus partner **API key + HMAC** request signing for the supplier-facing side | "Types of authentication, a secure connectivity session" (Bangkok Staff IV2) | 1 h |
| **7** | **W7#8 Brokers, flavour 1: SQS on SQL** (`brokers-three-flavours/`) | SQS-style queue on Postgres/MySQL (visibility timeout, ack, DLQ, `SKIP LOCKED`), used as the **transactional outbox relay** for P1's `BookingConfirmed` events, with an idempotent consumer | Outbox + DLQ is the standard "dual write" fix in the booking review | 1.5 h |

**Before IV2, stop here.** Then reread `08-Recall-Day-Of.md`. Each lab's "2-minute interview story" (see Lab shape) is what you'll actually use.

### Tier 1: before IV3 (Architecture: LLD + HLD), about 16 h

| P | Cohort exercise | Agoda twist | Why | Est. |
|---|---|---|---|---|
| **8 ★** | **W2#6 2PC** (`distributed-2pc/`) + stretch: **saga** | Payment flow: authorise → supplier confirm → capture, as **2PC first** (see it block when the coordinator dies), then an **orchestrated saga** with compensations + a **reconciliation job** | The IV3 payment-gateway prompt ("transactions, external provider, reconciliation") | 2.5 h |
| **9 ★** | **W8#1 GeoHash** (`geohash-nearby/`) | "Hotels near me": encode/decode, 8 neighbours, Haversine refine, compare with Redis `GEOSEARCH`, measure boundary misses without neighbours | IV3 report: hotel search *"with an emphasis on proximity-based search"* | 2 h |
| **10 ★** | **W4#2 Hashtag counter, 5 approaches** (`hashtag-counter/`) | **Hot-key counters**: "rooms left" / "N people viewing this hotel" during a flash sale. Naive vs batched vs map-swap vs Kafka-partitioned; measure DB writes and drift | IV3 concert flash sale; the canonical hot-key answer | 2 h |
| **11** | **W7#6 Task scheduler** (`task-scheduler/`) + W7#7 CH rebalance | Scheduled **supplier refresh jobs** (popular routes every 5 min): `SKIP LOCKED` pullers, heartbeat leases, missed-run policy, worker death recovery | The cohort's own capstone; it's also the refresh scheduler in the IV2 aggregator design | 3 h |
| **12** | **W5#1–3 Consistent hashing + vnodes** (`consistent-hashing/`) + **W1#2 sharding router** | Shard bookings by `user_id` vs `hotel_id`; measure remaps `% N` vs ring; skew vs vnodes | Scale-out vocabulary every HLD needs ("how do you shard bookings?") | 2 h |
| **13** | **W1#8 Kafka demo** (`kafka-demo/`) + **W1#7 RabbitMQ** | Booking events on Kafka (key = `bookingId`), consumer groups, rebalance, replay; compare work-queue semantics in RabbitMQ (prefetch, DLQ) | Queue vs log is a guaranteed follow-up | 1.5 h |
| **14** | **W3#2 Snowflake** (`id-snowflake-api/`) + **W3#8 UUID vs bigint** | Booking IDs: Snowflake with clock-rollback handling; UUIDv4 vs v7 vs BIGINT insert cost | "How are booking IDs generated across regions?" | 1.5 h |
| **15** | **W1#3 Read replica** + **W2#5 read-your-own-writes** | "I just booked, why isn't it in My Trips?" Replica lag + a primary-read window / LSN token | Classic consistency follow-up | 1.5 h |

### Tier 2: after the interviews, the Masterclass deep dive (ordered by learning value)
W1#9 realtime chat → W2#9 Redis PubSub star → W1#5 SSE (price-alert push) · W5#9 sequential vs random IO → W5#8 **Bitcask** → W6#2 Bloom FPR → W6#1 **LSM** (Go or C++) · W8#5 HyperLogLog · W6#6 1 GB streaming upload + W4#14 presigned upload · W7#3 contact fuzzy search · W2#2 deadlock · W2#3–4 KV on MySQL → sharded · W3#1 atomic counter · W4#10–12 Redis cluster/replication/Sentinel · W8#3 EVAL vs EVAL_RO replica routing · W4#3 denormalisation · W2#7–8 Neo4j/Mongo · W1#4 fairness · W8#6 hot-reload sidecar.

### Tier 3: read or paper only (skip building unless curious)
W3#3–7, W3#9, W3#11, W3#12 (duplicate of W2#6), W4#4–5, W4#7–8, W4#13, W4#15, W5#4–7 (fold #6–7 into Bitcask), W6#3–5, W6#7, W7#1–2, W7#4–5, W8#4 (covered by W3#8).

### If you only have 6 hours before IV2
**P0 → P1 (with idempotency) → P3 (fan-out + deadline + retries + breaker + partial results; skip the cache) → P4.** That alone covers the 2026 IV2 checklist: freshness, cache, pagination, double booking, dedupe, auth (talk only).

---

## Repo

**Ask before creating it on GitHub, and ask about visibility.** Proposed name: **`system-design-prototypes`** (alternative: `sysdesign-labs`). It's specifically for system design prototypes. Keep the name, README and commits **neutral**: no company names, nothing about interviews.

```
system-design-prototypes/
  README.md                 # index: exercise → folder → status → what it proves (table)
  Makefile                  # up/down/test/it/load/bench
  deploy/compose.yml        # shared infra: postgres, mysql, redis, toxiproxy, prometheus, grafana, jaeger (+ kafka/rabbitmq added when needed)
  pkg/                      # shared Go helpers, only once something is needed twice (retry, breaker, otel, httpx)
  labs/
    01-airline-checkin/     # use the cohort's prototype folder names after the number
    02-bounded-blocking-pool/
    03-supplier-gateway/
    04-cursor-pagination/
    05-payment-webhooks/
    ...
  PROGRESS.md               # one line per session: lab, what was done, numbers measured
  .github/workflows/ci.yml
```

**Stack:** Go 1.23+ (`net/http`, `context`, `errgroup`, `log/slog`, `pgx`, `go-redis`), Python 3.12 via `uv` (FastAPI fakes, Locust), Docker Compose, testcontainers-go, Toxiproxy, k6 or Locust, OpenTelemetry → Jaeger, Prometheus/Grafana. CI: `golangci-lint`, unit, integration.

## Lab shape (every lab)
1. **README.md**: the cohort exercise (week/number) → the Agoda twist → requirements → a Mermaid diagram → decisions and trade-offs → a **failure-modes table** (failure → detection → mitigation → test that proves it) → **the measured numbers** (the cohort's "Verify" list) → **"2-minute interview story"** (how I'd explain this in a design round, with one number I measured).
2. Code: a Go service, plus Python fakes where useful.
3. Tests: unit (table-driven) · integration (testcontainers) · fault injection (Toxiproxy) where there's a network hop · a load/bench test with a stated target.
4. Observability: RED metrics, traces, structured logs with a trace ID.
5. **REVIEW.md**: a deliberately flawed version of the key component (5–8 planted issues: SQL injection, per-call client/DB init, hardcoded key, missing pagination, race, swallowed errors, no timeout). I review it *before* opening the folded key. This is code-review practice for IV2.
6. Work through the cohort's **Gotchas** and **Verify** bullets explicitly. Do the **Stretch** only if the tier's time allows.

## Ground rules for the session
- **Never add AI attribution** to commits or PRs. Commit only when I ask.
- Repo in `~/code/system-design-prototypes` (Linux filesystem, not `/mnt/d`).
- **Show the design for each lab and wait for my OK before coding.** Go one lab at a time, in the priority order above, unless I say otherwise.
- **Teach Go as you go**: explain each idiom the first time (context, goroutines/channels, `errgroup`, interfaces, table-driven tests, `defer`) with a C++ comparison.
- Let me write parts myself when I ask ("my turn": give me the stub and tests, and hints only).
- Never claim something works without running it. Show the real test and benchmark output.
- At the end of each session, append a line to `PROGRESS.md`, and tell me the next lab in priority order.
