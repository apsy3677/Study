# Prototype Labs Plan (WSL): system design by building it

**Who this is for:** a Claude Code session running in WSL Ubuntu. Read this file fully before acting.
**Owner:** Anuj, about 11 years of backend/systems experience, mostly C++, some Java. New to Go, comfortable with Python.
**Why:** turn the System Design Masterclass exercises (notes: `/mnt/d/Git/Study/System Design/Arpit-Masterclass/`) into small running systems. The first three labs also act as hands-on practice for an upcoming backend "platform" interview round. That round grades system analysis, connectivity/API integration, QA/testing, code review and communication. Prep notes for it are in `/mnt/d/Git/Study/Agoda-Staff-BE-Prep/02-Platform-Round/`.

## Ground rules for the session
- **Never add AI attribution** to commits or PRs (no `Co-Authored-By`, no "Generated with", no session trailers). Commits belong to Anuj only.
- **Ask before creating the GitHub repo** and ask whether it's public or private. Proposed name: `sysdesign-labs`. Keep the name and README neutral (no company names).
- The repo lives in `~/code/sysdesign-labs` (Linux filesystem, not `/mnt/d`, for speed).
- Teach while building: Anuj is learning Go. Explain Go idioms the first time they appear (contexts, goroutines/channels, `errgroup`, interfaces, table-driven tests), with a C++ comparison where it helps.
- Don't claim something works unless the command actually ran. Show the test output.

## Stack
| Layer | Choice | Why |
|---|---|---|
| Services | **Go 1.23+** (`net/http`, `context`, `errgroup`, `log/slog`) | Concurrency, timeouts and deadlines are first-class. Small binaries |
| Fakes, load, scripts | **Python 3.12** with `uv`, FastAPI, Locust | Fast to write configurable fake vendors and load tests |
| Infra | Docker Compose: Postgres 16, Redis 7, **Redpanda** (Kafka API), **Toxiproxy**, Prometheus, Grafana, Jaeger (OTLP) | One `make up` brings everything up |
| Tests | Go `testing` + `httptest`, **testcontainers-go**, Toxiproxy for faults, Locust or k6 for load, pytest for Python | Covers every level of the test pyramid |
| CI | GitHub Actions: `golangci-lint`, unit, integration (testcontainers runs on the hosted runner) | Green badge per lab |

## Repo layout
```
sysdesign-labs/
  README.md                 # index of labs, how to run, what each one teaches
  Makefile                  # up/down/test/it/load across labs
  deploy/compose.yml        # shared infra stack
  deploy/grafana/, deploy/prometheus/
  pkg/                      # shared Go helpers (retry, breaker, otel setup) once they're needed twice
  labs/01-supplier-gateway/
  labs/02-idempotent-booking/
  labs/03-signed-webhooks/
  ...
  .github/workflows/ci.yml
```

## Every lab has the same shape
1. `README.md`: the problem (cite the Masterclass session) → requirements and SLOs → Mermaid diagram → design decisions with trade-offs → **failure modes table** (failure → detection → mitigation → which test proves it) → "How I'd explain this in 2 minutes".
2. Code (Go service + Python fakes where needed).
3. **Tests at every level:** unit (table-driven), integration (testcontainers), fault injection (Toxiproxy: latency, timeouts, resets), contract test where two services talk, load test with a stated target (for example "p99 < 300 ms at 200 RPS").
4. Observability: RED metrics (rate, errors, duration) on Prometheus, traces in Jaeger, structured logs with a trace id.
5. `REVIEW.md`: a deliberately flawed version of one key component (5–8 planted issues: security, reliability, performance, tests, readability). Anuj writes review comments, *then* opens the folded answer key. This is code-review practice.
6. `make test`, `make it` and `make load` work from the lab folder.

## Phase 1: before the interview (about 2 h/day, in this order)

### Lab 0: Skeleton (about 1 h)
- Install: Go, `uv` + Python 3.12, Docker (Docker Desktop with WSL integration, or Docker Engine in WSL), `golangci-lint`, k6 (optional).
- Create the repo, layout, `deploy/compose.yml`, Makefile, CI workflow, root README.
- Done when: `make up` starts the stack, Grafana/Jaeger UIs open, CI is green on an empty Go test.

### Lab 1: Supplier connectivity gateway ★ most interview-relevant
**Story:** a hotel search needs availability + price from N external suppliers. Each supplier is slow, flaky or rate-limited in its own way.
- `fake-supplier` (Python/FastAPI): env-configurable latency distribution, error rate, 429 with `Retry-After`, cursor-paginated results, an API-key check.
- `gateway` (Go): `GET /availability?hotel=…&checkin=…` fans out to suppliers concurrently.
  - **Deadline propagation:** the request context carries an overall budget (for example 800 ms). Each supplier call gets `min(remaining, per-supplier timeout)`.
  - **Retries:** only idempotent calls and only retryable errors (timeouts, 502/503, 429 honouring `Retry-After`). Exponential backoff + full jitter, max attempts, retry budget.
  - **Circuit breaker** per supplier (closed/open/half-open). **Bulkhead:** a bounded concurrency semaphore per supplier.
  - **Partial responses:** return what arrived within the deadline with `{"partial": true, "missing": ["supplierB"], …}`, not a 500.
  - **Pagination:** follow cursors with a page cap. Never load unbounded pages.
  - **Rate limiting** toward each supplier: a token bucket in Redis (a Lua script for atomicity).
  - **Backpressure:** a bounded in-flight request queue. Shed load with 503 + `Retry-After` when it's full.
  - Secrets from env/secret file, never hardcoded. HTTP client created once and reused (connection pooling).
- Tests: unit (backoff math, breaker state machine, merge logic), `httptest` suppliers, Toxiproxy chaos (one supplier at +2 s latency → response is still within the deadline and marked partial), load test showing load shedding.
- Masterclass link: 01-02 (communication, queues), 03-01 (remote locks / Redis atomics).

### Lab 2: Idempotent booking + transactional outbox
**Story:** "Book" must never double-charge or oversell, even when clients retry and consumers redeliver.
- Go API + Postgres: `POST /bookings` with an `Idempotency-Key` header. Store key → request hash → response. Same key + same body → same response. Same key + different body → 422. Handle concurrent duplicates with a unique constraint.
- Inventory: compare `SELECT … FOR UPDATE` vs `SKIP LOCKED` vs a conditional `UPDATE … WHERE available > 0`. Benchmark them under contention.
- **Transactional outbox:** the booking row + outbox row in one transaction. A relay publishes to Redpanda. The consumer dedupes by event id and sends poison messages to a DLQ after N attempts.
- A payment-step saga with a compensating action (cancel booking when the fake payment fails).
- Tests: concurrency test (100 parallel bookings for 10 rooms → exactly 10 succeed), duplicate-retry test, kill-the-relay-mid-way test, consumer redelivery test.
- Masterclass link: 02-01 (pessimistic locking, SKIP LOCKED), 07-02 (flash sale, per-unit inventory).

### Lab 3: Signed webhooks + delivery worker
**Story:** notify partners of booking/price changes over webhooks, reliably and safely.
- Producer: signs payloads with HMAC-SHA256 (`timestamp.body`), sends `X-Signature` + `X-Timestamp` + an event id.
- Delivery worker: retry schedule (1 m, 5 m, 30 m … compressed to seconds in tests), per-partner concurrency limit, a DLQ, and a replay endpoint.
- Receiver (Python): verifies the signature with a constant-time compare, rejects stale timestamps (replay window), dedupes by event id, returns 2xx fast and processes async.
- Contract test between producer and receiver (a schema/Pact-style JSON contract checked in CI).
- Compare in the README: webhooks vs polling vs pub/sub vs SSE for partner integration.
- Masterclass link: 01-02 (short/long polling, queues vs streams).

## Phase 2: after the interview (Masterclass deep dive)
| # | Lab | Session | Core idea to prove |
|---|---|---|---|
| 4 | Task scheduler | 07-02 | Pullers with `SKIP LOCKED`, cron expansion, at-least-once execution, autoscaled executors |
| 5 | Distributed cache | 05-01 | Consistent hashing + virtual nodes. Rebalancing cost measured. LRU/TTL sampling |
| 6 | ID generator | 03-02 | Snowflake layout, clock-skew handling, ticket-server comparison |
| 7 | Remote locks | 03-01 | SETNX+TTL, fencing tokens, why Redlock is debated (demo a GC-pause failure) |
| 8 | Realtime fan-out | 02-02 | WebSocket edge servers + Redis Pub/Sub, connection registry, reconnect storms |
| 9 | Bitcask KV + WAL | 05-02 | Append-only log, in-memory keydir, merge/compaction, crash recovery (Go or **C++**) |
| 10 | LSM tree | 06-01 | Memtable → SSTables, Bloom filters, compaction, read/write amplification (Go or **C++**) |
| 11 | Impressions counter | 08-01 | HyperLogLog (PFADD/PFMERGE/PFCOUNT), tiered storage |
| 12 | Geo-proximity | 08-02 | GeoHash, nearby-driver search, Redis GEO |
| 13 | Online/offline indicator | 01-01 | Heartbeats, TTL keys, Redis vs DynamoDB-style trade-off |

## How to start the WSL session
```bash
mkdir -p ~/code && cd ~/code && claude
```
Then say: *"Read /mnt/d/Git/Study/System Design/Prototype-Labs-Plan.md and start Lab 0. Ask me about the repo name and visibility first."*
