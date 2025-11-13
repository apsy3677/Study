# API Cost Optimizer - Visual Reference Diagrams

## 1. Complete System Architecture

```
┌────────────────────────────────────────────────────────────────────────────┐
│                          CLIENT APPLICATIONS                                │
│                    (Microservices, Web Apps, Mobile)                        │
└────────────────────────────┬───────────────────────────────────────────────┘
                             │
                             │ HTTP/gRPC Requests
                             ▼
┌────────────────────────────────────────────────────────────────────────────┐
│                     API COST OPTIMIZER LAYER                                │
│ ┌────────────────────────────────────────────────────────────────────────┐ │
│ │                      REQUEST INTERCEPTOR                               │ │
│ │  • Capture requests    • Generate ID    • Start timing                │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                      CONTEXT ENRICHER                                  │ │
│ │  • Customer ID    • Service ID    • SLA    • Budget    • Priority     │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                     STRATEGY SELECTOR                                  │ │
│ │  • Analyze request    • Select optimizations    • Create plan         │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│                              ├──────────────────────┐                       │
│                              │                      │                       │
│ ┌────────────────────────────▼─────┐  ┌────────────▼─────────────────┐    │
│ │      CACHE LAYER                 │  │   DEDUPLICATION ENGINE       │    │
│ │  ┌──────────────────────────┐    │  │  • In-flight tracking        │    │
│ │  │ L1: Local (100MB)        │    │  │  • Request coalescing        │    │
│ │  │  TTL: 1-60s              │    │  │  • Response broadcasting     │    │
│ │  └──────────┬───────────────┘    │  └──────────────────────────────┘    │
│ │             │                     │                                       │
│ │  ┌──────────▼───────────────┐    │                                       │
│ │  │ L2: Redis Cluster        │    │                                       │
│ │  │  TTL: 1-3600s            │    │                                       │
│ │  │  Hit Rate: ~70%          │    │                                       │
│ │  └──────────────────────────┘    │                                       │
│ └──────────────────────────────────┘                                       │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                      BATCH PROCESSOR                                   │ │
│ │  • Batch window: 20-200ms    • Max size: 100    • SLA enforcement     │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                      RATE LIMITER                                      │ │
│ │  • Token bucket    • Budget enforcement    • Priority queue           │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                      SMART ROUTER                                      │ │
│ │  • Provider selection    • Cost/latency/quality scoring               │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
│                              │                                              │
│ ┌────────────────────────────▼───────────────────────────────────────────┐ │
│ │                      API EXECUTOR                                      │ │
│ │  • Circuit breaker    • Retry logic    • Timeout handling             │ │
│ └────────────────────────────┬───────────────────────────────────────────┘ │
└──────────────────────────────┼────────────────────────────────────────────┘
                               │
                               ▼
┌────────────────────────────────────────────────────────────────────────────┐
│                         EXTERNAL API PROVIDERS                              │
│    ┌──────────────┐      ┌──────────────┐      ┌──────────────┐           │
│    │   AWS APIs   │      │   GCP APIs   │      │  Azure APIs  │           │
│    └──────────────┘      └──────────────┘      └──────────────┘           │
└────────────────────────────────────────────────────────────────────────────┘
                               │
                               │ Response
                               ▼
┌────────────────────────────────────────────────────────────────────────────┐
│                      COST TRACKING & ANALYTICS                              │
│  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐            │
│  │  PostgreSQL     │  │   ClickHouse    │  │   Prometheus    │            │
│  │  (Cost Records) │  │   (Analytics)   │  │   (Metrics)     │            │
│  └─────────────────┘  └─────────────────┘  └─────────────────┘            │
└────────────────────────────────────────────────────────────────────────────┘
```

---

## 2. Request Flow Diagram (Decision Tree)

```
                        ┌─────────────────┐
                        │ Request Arrives │
                        └────────┬────────┘
                                 │
                        ┌────────▼────────┐
                        │ Intercept &     │
                        │ Enrich Context  │
                        └────────┬────────┘
                                 │
                                 │
                        ┌────────▼────────┐
                        │ Select Strategy │
                        │ Plan            │
                        └────────┬────────┘
                                 │
                                 │
                    ┌────────────▼────────────┐
                    │  Check Cache (L1/L2)    │
                    └──┬──────────────────┬───┘
                       │                  │
                   [Hit]                [Miss]
                       │                  │
         ┌─────────────▼──────┐           │
         │ Return Cached Data │           │
         │   💰 90% Savings   │           │
         │   ⚡ 2ms latency   │           │
         └────────────────────┘           │
                                          │
                              ┌───────────▼──────────┐
                              │ Check Deduplication  │
                              │ (In-flight requests) │
                              └──┬───────────────┬───┘
                                 │               │
                          [Duplicate]      [Unique]
                                 │               │
                    ┌────────────▼────────┐      │
                    │ Attach to Existing  │      │
                    │   💰 100% Savings   │      │
                    │   ⚡ 0ms API call   │      │
                    └─────────────────────┘      │
                                                 │
                                     ┌───────────▼──────────┐
                                     │  Batchable?          │
                                     └──┬───────────────┬───┘
                                        │               │
                                      [Yes]           [No]
                                        │               │
                          ┌─────────────▼────────┐      │
                          │ Add to Batch Queue   │      │
                          │ Wait for:            │      │
                          │ • Window expires OR  │      │
                          │ • Batch full         │      │
                          │   💰 50% Savings     │      │
                          │   ⏱️ +50ms latency   │      │
                          └──────────────────────┘      │
                                                        │
                                            ┌───────────▼──────────┐
                                            │  Check Rate Limit    │
                                            │  & Budget            │
                                            └──┬───────────────┬───┘
                                               │               │
                                           [Over]          [Under]
                                               │               │
                                 ┌─────────────▼────────┐      │
                                 │ Priority?            │      │
                                 │ • High: Allow + Warn │      │
                                 │ • Med:  Queue        │      │
                                 │ • Low:  Reject       │      │
                                 └──────────────────────┘      │
                                                               │
                                                   ┌───────────▼──────────┐
                                                   │  Smart Routing       │
                                                   │  Score providers by: │
                                                   │  • Cost              │
                                                   │  • Latency           │
                                                   │  • Quality           │
                                                   │  • Reliability       │
                                                   │    💰 30% Savings    │
                                                   └───────────┬──────────┘
                                                               │
                                                   ┌───────────▼──────────┐
                                                   │  Execute API Call    │
                                                   │  • Circuit breaker   │
                                                   │  • Retry on failure  │
                                                   │  • Timeout handling  │
                                                   └───────────┬──────────┘
                                                               │
                                                   ┌───────────▼──────────┐
                                                   │  Update Cache        │
                                                   │  Track Cost          │
                                                   │  Return Response     │
                                                   └──────────────────────┘
```

---

## 3. Component Interaction Diagram

```
┌───────────────────────────────────────────────────────────────────────────┐
│                            Request Flow                                    │
└───────────────────────────────────────────────────────────────────────────┘

Interceptor          Context         Strategy        Cache          Executor
    │                Enricher        Selector        Layer             │
    │                   │                │             │               │
    │─────req──────────▶│                │             │               │
    │                   │                │             │               │
    │                   │───enriched────▶│             │               │
    │                   │     req        │             │               │
    │                   │                │             │               │
    │                   │                │─cache_key──▶│               │
    │                   │                │             │               │
    │                   │                │◀──miss──────│               │
    │                   │                │             │               │
    │                   │                │─────────────────req────────▶│
    │                   │                │             │               │
    │                   │                │             │       Execute API
    │                   │                │             │               │
    │                   │                │             │◀──response────│
    │                   │                │             │               │
    │                   │                │──cache─────▶│               │
    │                   │                │  response   │               │
    │                   │                │             │               │
    │◀──────────────────────response─────│             │               │
    │                   │                │             │               │
    ▼                   ▼                ▼             ▼               ▼

                            [Cost Tracker]
                                  │
                    ┌─────────────┼─────────────┐
                    │             │             │
                    ▼             ▼             ▼
              PostgreSQL    ClickHouse    Prometheus
              (Records)     (Analytics)    (Metrics)
```

---

## 4. Optimization Strategy Decision Matrix

```
┌─────────────────────────────────────────────────────────────────────────┐
│                    Optimization Strategy Selector                        │
└─────────────────────────────────────────────────────────────────────────┘

Request Characteristics:
┌──────────────┬──────────┬───────────┬───────────┬──────────┬──────────┐
│ Characteristic│  Cache  │  Dedupe   │  Batch    │Rate Limit│ Routing  │
├──────────────┼──────────┼───────────┼───────────┼──────────┼──────────┤
│ GET request  │    ✅    │    ✅     │    ❌     │    ✅    │    ✅    │
│ POST/PUT     │    ❌    │    ⚠️     │    ✅     │    ✅    │    ✅    │
│ Idempotent   │    ✅    │    ✅     │    ⚠️     │    ✅    │    ✅    │
│ Real-time    │    ❌    │    ✅     │    ❌     │    ⚠️    │    ✅    │
│ Batch job    │    ✅    │    ❌     │    ✅     │    ⚠️    │    ✅    │
│ High traffic │    ✅    │    ✅     │    ✅     │    ✅    │    ✅    │
│ Low traffic  │    ⚠️    │    ❌     │    ❌     │    ❌    │    ✅    │
│ Budget tight │    ✅    │    ✅     │    ✅     │    ✅    │    ✅    │
│ Low priority │    ✅    │    ✅     │    ✅     │    ✅    │    ✅    │
│ High priority│    ⚠️    │    ⚠️     │    ❌     │    ⚠️    │    ⚠️    │
└──────────────┴──────────┴───────────┴───────────┴──────────┴──────────┘

Legend:
✅ = Highly Recommended
⚠️  = Use with Caution
❌ = Not Recommended
```

---

## 5. Cache Strategy Visualization

```
┌────────────────────────────────────────────────────────────────────────┐
│                        Cache Hierarchy                                  │
└────────────────────────────────────────────────────────────────────────┘

        Request
           │
           ▼
    ┌─────────────────┐
    │  L1: Local      │ ◄─── 100MB per instance
    │  In-Memory      │      TTL: 1-60 seconds
    │  LRU Cache      │      Hit Rate: ~20%
    └────────┬────────┘      Latency: 0.1ms
             │
         [Miss]
             │
             ▼
    ┌─────────────────┐
    │  L2: Redis      │ ◄─── Distributed cluster
    │  Cluster        │      TTL: 1-3600 seconds
    │  (Sharded)      │      Hit Rate: ~50%
    └────────┬────────┘      Latency: 1-2ms
             │
         [Miss]
             │
             ▼
    ┌─────────────────┐
    │  Execute API    │ ◄─── External API call
    │  Call           │      Cost: $0.001-0.01
    └────────┬────────┘      Latency: 50-500ms
             │
             ▼
         Response
             │
             ├────────────────▶ Store in L2 (Redis)
             └────────────────▶ Store in L1 (Local)


Cache Key Generation:
┌────────────────────────────────────────────────────────────────────────┐
│  cache:v1:{customer_id}:{endpoint}:{method}:{params_hash}              │
│                                                                         │
│  Example:                                                               │
│  cache:v1:cust_123:/api/products:GET:a3f7b2c9                          │
└────────────────────────────────────────────────────────────────────────┘

TTL Calculation:
┌────────────────────────────────────────────────────────────────────────┐
│                                                                         │
│  Base TTL: 5 minutes                                                   │
│     │                                                                   │
│     ├─ Data volatility: High  → TTL / 2 = 2.5 min                     │
│     │                   Medium → TTL     = 5 min                       │
│     │                   Low    → TTL * 2 = 10 min                      │
│     │                                                                   │
│     └─ Access frequency: High (>100/s) → Keep TTL                     │
│                          Low  (<10/s)  → Reduce TTL                   │
│                                                                         │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 6. Batch Processing Timeline

```
┌────────────────────────────────────────────────────────────────────────┐
│                    Batch Window Visualization                           │
└────────────────────────────────────────────────────────────────────────┘

Timeline:
│
├─ T0: Req1 arrives ────┐
│                       │ Start batch
│                       │ Start timer (50ms)
│                       │
├─ T10: Req2 arrives ───┤ Add to batch (2 requests)
│                       │
├─ T15: Req3 arrives ───┤ Add to batch (3 requests)
│                       │
├─ T25: Req4 arrives ───┤ Add to batch (4 requests)
│                       │
├─ T30: Req5 arrives ───┤ Add to batch (5 requests)
│                       │
├─ T50: Timer expires ──┘ FLUSH BATCH
│       │
│       ▼
│   ┌───────────────────────────┐
│   │ Execute batched API call  │
│   │ [Req1, Req2, Req3,        │
│   │  Req4, Req5]              │
│   └───────────┬───────────────┘
│               │
│               ▼ (100ms)
│   ┌───────────────────────────┐
│   │ Response received         │
│   │ [Res1, Res2, Res3,        │
│   │  Res4, Res5]              │
│   └───────────┬───────────────┘
│               │
│               ├──────────────▶ Req1.ResponseChan ← Res1
│               ├──────────────▶ Req2.ResponseChan ← Res2
│               ├──────────────▶ Req3.ResponseChan ← Res3
│               ├──────────────▶ Req4.ResponseChan ← Res4
│               └──────────────▶ Req5.ResponseChan ← Res5
│
▼

Cost Analysis:
┌────────────────────────────────────────────────────────────────────────┐
│  Without Batching:                                                      │
│    5 requests × $0.01 = $0.05                                          │
│                                                                         │
│  With Batching:                                                         │
│    1 batch request × $0.01 = $0.01                                     │
│                                                                         │
│  Savings: $0.04 (80%)                                                  │
│                                                                         │
│  Latency:                                                              │
│    Individual: 0ms wait + 100ms API = 100ms                           │
│    Batched:    50ms wait + 100ms API = 150ms                          │
│    Overhead:   +50ms (acceptable if SLA > 200ms)                      │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 7. Deduplication Pattern

```
┌────────────────────────────────────────────────────────────────────────┐
│                    Deduplication Visualization                          │
└────────────────────────────────────────────────────────────────────────┘

Scenario: Multiple concurrent identical requests

Time    Request A          Request B          Request C
│       (Leader)           (Follower)         (Follower)
│
├─ T0   Arrives ─────────┐
│       Generate key:    │
│       "dedup:abc123"   │
│       Create group     │
│       Execute API ───┐ │
│                      │ │
├─ T5                  │ │ Arrives ─────────┐
│                      │ │ Generate key:    │
│                      │ │ "dedup:abc123"   │
│                      │ │ Found existing!  │
│                      │ │ Attach to group  │
│                      │ │ Wait for leader──┼─┐
│                      │ │                  │ │
├─ T10                 │ │                  │ │ Arrives ─────────┐
│                      │ │                  │ │ Generate key:    │
│                      │ │                  │ │ "dedup:abc123"   │
│                      │ │                  │ │ Found existing!  │
│                      │ │                  │ │ Attach to group  │
│                      │ │                  │ │ Wait for leader──┼─┐
│                      │ │                  │ │                  │ │
├─ T50  API Response ◀─┘ │                  │ │                  │ │
│       Received         │                  │ │                  │ │
│                        │                  │ │                  │ │
│       Broadcast ───────┼──────────────────┼─┼──────────────────┼─┘
│       to all           │                  │ │                  │
│                        │                  │ │                  │
├─ T51  Response A ◀─────┘ Response B ◀─────┘ │ Response C ◀─────┘
│                                              │
▼

In-Flight Map:
┌─────────────────────────────────────────────────────────────────────┐
│  Key: "dedup:abc123"                                                 │
│  Value: RequestGroup {                                               │
│    Leader: Request A                                                 │
│    Followers: [Request B, Request C]                                 │
│    ResponseChans: [Chan A, Chan B, Chan C]                          │
│    StartTime: T0                                                     │
│  }                                                                   │
└─────────────────────────────────────────────────────────────────────┘

Cost Analysis:
┌─────────────────────────────────────────────────────────────────────┐
│  Without Deduplication:                                              │
│    3 requests × $0.01 = $0.03                                       │
│                                                                      │
│  With Deduplication:                                                 │
│    1 request × $0.01 = $0.01                                        │
│                                                                      │
│  Savings: $0.02 (67%)                                               │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 8. Cost Breakdown Visualization

```
┌────────────────────────────────────────────────────────────────────────┐
│                 Daily Cost Breakdown (1M requests)                      │
└────────────────────────────────────────────────────────────────────────┘

Before Optimization: $1,000/day
█████████████████████████████████████████████████████████████████ $1,000
(1M requests × $0.001)

After Optimization: $200/day
█████████████ $200

Breakdown by Strategy:
┌──────────────────────────────────────────────────────────────────────┐
│                                                                       │
│  Cache (70% hit rate):                                               │
│  █████████████████████████████████████████████ $0 (700K requests)    │
│  Savings: $700                                                       │
│                                                                       │
│  Deduplication (15%):                                                │
│  ██████████ $0 (150K requests)                                       │
│  Savings: $150                                                       │
│                                                                       │
│  Batching (10% → 1%):                                                │
│  █████ $10 (100K → 10K batches)                                      │
│  Savings: $90                                                        │
│                                                                       │
│  Direct (5%):                                                         │
│  ███ $50 (50K requests)                                              │
│  Savings: $0 (baseline)                                              │
│                                                                       │
│  Smart Routing (avg 20% savings on direct):                          │
│  █ -$10 (saved on routing)                                           │
│  Savings: $10                                                        │
│                                                                       │
└──────────────────────────────────────────────────────────────────────┘

Total Savings: $800/day = $292K/year (80% reduction)

Monthly Cost Trend:
┌──────────────────────────────────────────────────────────────────────┐
│  $30K ┤                                                               │
│       │  ●                                                            │
│  $25K ┤  │ Before                                                     │
│       │  │                                                            │
│  $20K ┤  ●                                                            │
│       │  │                                                            │
│  $15K ┤  │                                                            │
│       │  │                                                            │
│  $10K ┤  │                        ■───■───■ After (stabilized)       │
│       │  │                    ■───                                    │
│   $5K ┤  │                ■───                                        │
│       │  │            ■───                                            │
│   $0  ┤  └────────────                                                │
│       └──┬────┬────┬────┬────┬────┬────┬────┬────┬────              │
│          W1   W2   W3   W4   W5   W6   W7   W8   W9                 │
│                                                                       │
│          Rollout Timeline                                            │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 9. Failure Scenarios & Recovery Paths

```
┌────────────────────────────────────────────────────────────────────────┐
│                    Failure Handling Decision Tree                       │
└────────────────────────────────────────────────────────────────────────┘

                            Request
                               │
                               ▼
                      ┌────────────────┐
                      │ Optimization   │
                      │ Attempt        │
                      └───────┬────────┘
                              │
                              ├───────────────────────┐
                              │                       │
                          [Success]               [Failure]
                              │                       │
                    ┌─────────▼────────┐              │
                    │ Return Optimized │              │
                    │ Response         │              │
                    └──────────────────┘              │
                                                      │
                                          ┌───────────▼──────────┐
                                          │ Determine Failure    │
                                          │ Type                 │
                                          └───────────┬──────────┘
                                                      │
                    ┌─────────────────────────────────┼──────────────────┐
                    │                                 │                  │
                    ▼                                 ▼                  ▼
         ┌──────────────────┐          ┌──────────────────┐  ┌──────────────────┐
         │ Cache Unavailable│          │ Batch Timeout    │  │ Rate Limit Hit   │
         └────────┬─────────┘          └────────┬─────────┘  └────────┬─────────┘
                  │                              │                     │
                  ▼                              ▼                     ▼
         ┌──────────────────┐          ┌──────────────────┐  ┌──────────────────┐
         │ Bypass Cache     │          │ Execute          │  │ Check Priority   │
         │ Go Direct        │          │ Individually     │  │                  │
         └────────┬─────────┘          └────────┬─────────┘  └────────┬─────────┘
                  │                              │                     │
                  ▼                              ▼                     ├─[High]──▶Allow
         ┌──────────────────┐          ┌──────────────────┐           ├─[Med]───▶Queue
         │ Execute API      │          │ Execute API      │           └─[Low]───▶Reject
         │ (Direct)         │          │ (Fallback)       │
         └────────┬─────────┘          └────────┬─────────┘
                  │                              │
                  └──────────────┬───────────────┘
                                 │
                                 ▼
                        ┌────────────────┐
                        │ Track Degraded │
                        │ Execution      │
                        └────────┬───────┘
                                 │
                                 ▼
                        ┌────────────────┐
                        │ Emit Metrics   │
                        │ & Alerts       │
                        └────────────────┘

Circuit Breaker States:
┌────────────────────────────────────────────────────────────────────────┐
│                                                                         │
│   CLOSED                    OPEN                    HALF-OPEN          │
│   (Normal)                  (Failing)               (Testing)          │
│      │                         │                         │             │
│      │ Error rate > 50%        │ Timeout expired         │             │
│      ├────────────────────────▶│                         │             │
│      │                         │                         │             │
│      │                         ├────────────────────────▶│             │
│      │                         │                         │             │
│      │                         │         Success         │             │
│      │◀────────────────────────┴─────────────────────────┘             │
│      │                                                                  │
│      │                         Failure                                 │
│      │◀────────────────────────────────────────────────────────────────┘
│                                                                         │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 10. Performance Metrics Dashboard Layout

```
┌────────────────────────────────────────────────────────────────────────┐
│                     Cost Optimizer Dashboard                            │
├────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────────────────────────────────────────────────────┐  │
│  │  COST OVERVIEW                                      [Last 24h] │  │
│  ├─────────────────────────────────────────────────────────────────┤  │
│  │  Total Spend:        $60      (-80% vs baseline)               │  │
│  │  Total Savings:      $240                                       │  │
│  │  Optimized Requests: 950K     (95% of total)                   │  │
│  └─────────────────────────────────────────────────────────────────┘  │
│                                                                         │
│  ┌──────────────────────┐  ┌──────────────────────┐                   │
│  │  CACHE METRICS       │  │  BATCH METRICS       │                   │
│  ├──────────────────────┤  ├──────────────────────┤                   │
│  │  Hit Rate: 72%       │  │  Avg Batch Size: 5.2 │                   │
│  │  L1 Hits:  18%       │  │  Batches: 12,500     │                   │
│  │  L2 Hits:  54%       │  │  Savings: $45        │                   │
│  │  Savings:  $210      │  │  Avg Wait: 42ms      │                   │
│  └──────────────────────┘  └──────────────────────┘                   │
│                                                                         │
│  ┌──────────────────────┐  ┌──────────────────────┐                   │
│  │  DEDUP METRICS       │  │  ROUTING METRICS     │                   │
│  ├──────────────────────┤  ├──────────────────────┤                   │
│  │  Dedup Rate: 12%     │  │  Provider A: 45%     │                   │
│  │  Requests: 120K      │  │  Provider B: 35%     │                   │
│  │  Savings: $36        │  │  Provider C: 20%     │                   │
│  │  Avg Wait: 15ms      │  │  Savings: $12        │                   │
│  └──────────────────────┘  └──────────────────────┘                   │
│                                                                         │
│  ┌─────────────────────────────────────────────────────────────────┐  │
│  │  PERFORMANCE METRICS                                            │  │
│  ├─────────────────────────────────────────────────────────────────┤  │
│  │  p50 Latency: 3ms    │  p95 Latency: 8ms   │  p99 Latency: 15ms│  │
│  │  SLA Violations: 0.02% (Target: < 0.1%)                        │  │
│  │  Availability: 99.998%                                           │  │
│  └─────────────────────────────────────────────────────────────────┘  │
│                                                                         │
│  ┌─────────────────────────────────────────────────────────────────┐  │
│  │  TOP COST CONSUMERS                                             │  │
│  ├─────────────────────────────────────────────────────────────────┤  │
│  │  1. order-service    $18.50   ████████████████░░░░░░░  62%     │  │
│  │  2. user-service     $12.30   ██████████░░░░░░░░░░░░░  41%     │  │
│  │  3. product-service  $8.70    ██████░░░░░░░░░░░░░░░░░  29%     │  │
│  │  4. analytics-svc    $6.20    ████░░░░░░░░░░░░░░░░░░░  21%     │  │
│  │  5. payment-service  $4.30    ███░░░░░░░░░░░░░░░░░░░░  14%     │  │
│  └─────────────────────────────────────────────────────────────────┘  │
│                                                                         │
│  ┌─────────────────────────────────────────────────────────────────┐  │
│  │  ALERTS                                                         │  │
│  ├─────────────────────────────────────────────────────────────────┤  │
│  │  ⚠️  order-service approaching daily budget (95% used)          │  │
│  │  ✓  All SLAs within target                                      │  │
│  │  ✓  Cache hit rate healthy (> 70%)                              │  │
│  └─────────────────────────────────────────────────────────────────┘  │
│                                                                         │
└────────────────────────────────────────────────────────────────────────┘
```

---

These visual references provide a quick way to understand the system's architecture, flow, and decision-making processes! 📊








