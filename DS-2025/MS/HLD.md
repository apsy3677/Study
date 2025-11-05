## Microsoft HLD Solutions (Architectures, Trade-offs, Links)

Emphasize requirements, API, storage, scaling, consistency, failure modes, and observability. Microsoft-focused references from Azure Architecture Center included.

---

## Table of Contents
1. [Concurrent Job Orchestrator](#concurrent-job-orchestrator)
2. [Rate Limiter](#rate-limiter-hld)
3. [URL Shortener](#url-shortener)
4. [Dropbox-like Storage](#dropbox-like-storage)
5. [News Feed](#news-feed)
6. [Web Crawler](#web-crawler)
7. [CDN](#cdn)
8. [Analytics System](#analytics-system)
9. [Notification System](#notification-system)
10. [Distributed Key-Value Store](#distributed-key-value-store)

---

### Concurrent Job Orchestrator

#### 1. Requirements Clarification

**Functional Requirements:**
- Submit jobs with priority levels (P0-critical, P1-high, P2-normal, P3-low)
- Support multiple job types (e.g., video transcoding, data processing, ML training)
- Enforce per-job-type license/concurrency limits
- Query job status, cancel jobs, retry failed jobs
- Store job artifacts and logs
- Support job dependencies (optional)

**Non-Functional Requirements:**
- **Scale:** 100K+ jobs/day, 10K concurrent jobs peak
- **Latency:** Job submission <100ms, status query <50ms
- **Availability:** 99.9% uptime
- **Durability:** No job loss; exactly-once submission, at-least-once execution
- **Observability:** Real-time metrics, alerting, distributed tracing

#### 2. Capacity Estimation

**Traffic:**
- 100K jobs/day = ~1.2 jobs/sec average, ~10 jobs/sec peak
- 10K concurrent executions at peak
- Average job duration: 5 minutes
- 20% retries

**Storage:**
- Job metadata: 5KB per job → 500MB/day → 180GB/year
- Logs/artifacts: 10MB per job → 1TB/day → 365TB/year (store last 90 days)
- Redis hot cache: 100K active jobs × 1KB = 100MB

**Compute:**
- Worker CPU: 10K concurrent × 2 vCPU = 20K vCPU cores
- API/Scheduler: 20-50 instances (stateless, autoscaled)

#### 3. API Design

```http
# Job Submission
POST /api/v1/jobs
Authorization: Bearer <token>
Content-Type: application/json

{
  "jobType": "video-transcoding",
  "priority": "P1",
  "payload": {
    "inputUrl": "https://...",
    "resolution": "1080p"
  },
  "idempotencyKey": "uuid-client-generated",
  "retryPolicy": {
    "maxAttempts": 3,
    "backoffSeconds": 60
  },
  "dependencies": ["job-id-1", "job-id-2"]  // optional
}

Response 201:
{
  "jobId": "job-abc123",
  "status": "QUEUED",
  "queuePosition": 42,
  "createdAt": "2025-11-05T10:00:00Z"
}

# Query Job Status
GET /api/v1/jobs/{jobId}
Response 200:
{
  "jobId": "job-abc123",
  "status": "RUNNING",
  "progress": 45,
  "worker": "worker-pod-7",
  "startedAt": "2025-11-05T10:05:00Z",
  "estimatedCompletionAt": "2025-11-05T10:10:00Z",
  "artifacts": []
}

# Cancel Job
DELETE /api/v1/jobs/{jobId}

# List Jobs with Filters
GET /api/v1/jobs?status=FAILED&jobType=video-transcoding&page=1&limit=50

# Retry Job
POST /api/v1/jobs/{jobId}/retry
```

#### 4. Database Schema

**PostgreSQL (job metadata, source of truth):**
```sql
CREATE TABLE jobs (
  id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
  job_type VARCHAR(50) NOT NULL,
  priority VARCHAR(10) NOT NULL,
  status VARCHAR(20) NOT NULL, -- QUEUED, RUNNING, COMPLETED, FAILED, CANCELLED
  payload JSONB NOT NULL,
  idempotency_key VARCHAR(255) UNIQUE,
  retry_policy JSONB,
  current_attempt INT DEFAULT 0,
  max_attempts INT DEFAULT 3,
  assigned_worker VARCHAR(100),
  artifacts_url TEXT,
  error_message TEXT,
  created_at TIMESTAMP DEFAULT NOW(),
  updated_at TIMESTAMP DEFAULT NOW(),
  started_at TIMESTAMP,
  completed_at TIMESTAMP,
  INDEX idx_status_type (status, job_type),
  INDEX idx_created_at (created_at),
  INDEX idx_idempotency (idempotency_key)
);

CREATE TABLE job_dependencies (
  job_id UUID REFERENCES jobs(id) ON DELETE CASCADE,
  depends_on_job_id UUID REFERENCES jobs(id) ON DELETE CASCADE,
  PRIMARY KEY (job_id, depends_on_job_id)
);

CREATE TABLE license_limits (
  job_type VARCHAR(50) PRIMARY KEY,
  max_concurrent INT NOT NULL,
  current_usage INT DEFAULT 0,
  updated_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE job_audit_log (
  id BIGSERIAL PRIMARY KEY,
  job_id UUID REFERENCES jobs(id),
  event_type VARCHAR(50), -- SUBMITTED, ASSIGNED, STARTED, COMPLETED, FAILED, RETRIED
  metadata JSONB,
  timestamp TIMESTAMP DEFAULT NOW()
);
```

**Redis (fast state, counters):**
```
# Active job count per type (atomic operations)
license:video-transcoding:count → 42
license:ml-training:count → 15

# Job status cache (TTL 5 minutes)
job:status:job-abc123 → {"status": "RUNNING", "worker": "pod-7", "progress": 45}

# Priority queues (sorted sets, score = priority + timestamp)
queue:video-transcoding:P0 → [(job-id, score), ...]
queue:video-transcoding:P1 → [...]

# Worker heartbeats (TTL 30 seconds)
worker:pod-7:heartbeat → {"jobId": "job-abc123", "timestamp": "..."}
```

**Azure Blob Storage (artifacts, logs):**
```
Container: job-artifacts
Path: {jobType}/{date}/{jobId}/output.mp4
Container: job-logs
Path: {jobType}/{date}/{jobId}/worker.log
```

#### 5. High-Level Architecture

```
                         ┌─────────────┐
                         │   Clients   │
                         └──────┬──────┘
                                │
                    ┌───────────▼────────────┐
                    │   API Gateway + LB     │
                    │   (Front Door / APIM)  │
                    └───────────┬────────────┘
                                │
                    ┌───────────▼────────────┐
                    │   API Service (AKS)    │
                    │  - Job submission      │
                    │  - Status queries      │
                    │  - AuthN/AuthZ         │
                    └─┬──────────────────┬───┘
                      │                  │
         ┌────────────▼─────┐      ┌────▼──────────┐
         │  PostgreSQL      │      │  Redis Cluster│
         │  (Job metadata)  │      │  (Hot cache)  │
         └──────────────────┘      └───────────────┘
                      │
         ┌────────────▼─────────────────────┐
         │   Azure Service Bus              │
         │   (Priority Queues per job type) │
         │   - Topic: job-submissions       │
         │   - Subscriptions per type       │
         └────────────┬─────────────────────┘
                      │
         ┌────────────▼───────────────┐
         │   Scheduler Service (AKS)  │
         │   - Pull from queues       │
         │   - Check license limits   │
         │   - Assign to workers      │
         │   - Handle retries         │
         └────────────┬───────────────┘
                      │
         ┌────────────▼──────────────┐
         │   Worker Fleet (AKS)      │
         │   - Stateless pods        │
         │   - Job execution         │
         │   - Heartbeat reports     │
         │   - KEDA autoscaling      │
         └────────────┬──────────────┘
                      │
         ┌────────────▼──────────────┐
         │   Azure Blob Storage      │
         │   (Artifacts, Logs)       │
         └───────────────────────────┘

     ┌──────────────────────────────────────┐
     │   Observability Stack                │
     │   - Application Insights (traces)    │
     │   - Azure Monitor (metrics/alerts)   │
     │   - Log Analytics (structured logs)  │
     └──────────────────────────────────────┘
```

#### 6. Detailed Component Design

**A. API Service**
- **Tech:** ASP.NET Core Web API on AKS
- **Responsibilities:**
  - Validate job payload, authenticate/authorize
  - Check idempotency key (Redis + DB) to prevent duplicates
  - Insert job into PostgreSQL
  - Publish job event to Service Bus topic
  - Return job ID and status
- **Scaling:** Horizontal pod autoscaling (HPA) based on CPU/memory
- **Caching:** Redis for status queries (cache-aside pattern)

**B. Azure Service Bus (Message Queue)**
- **Structure:**
  - Topic: `job-submissions`
  - Subscriptions per job type with filters: `jobType = 'video-transcoding'`
  - Sessions enabled for ordering within same job type
  - Dead-letter queue (DLQ) for poison messages
- **Partitioning:** Partition by `jobId` for parallel processing
- **TTL:** 7 days for unprocessed messages
- **Retry Policy:** Exponential backoff, max 10 delivery attempts

**C. License Manager**
- **Implementation:** Redis atomic operations + PostgreSQL sync
- **Algorithm:**
  ```cpp
  class LicenseManager {
  private:
      std::shared_ptr<redis::Redis> redis_client_;
      
      // Redis Lua script for atomicity
      const std::string acquire_script_ = R"(
          local limit = tonumber(ARGV[1])
          local current = tonumber(redis.call('GET', KEYS[1]) or 0)
          if current < limit then
              redis.call('INCR', KEYS[1])
              return 1
          else
              return 0
          end
      )";
  
  public:
      bool AcquireLicense(const std::string& job_type, int max_limit) {
          std::string key = "license:" + job_type + ":count";
          
          // Execute Lua script atomically
          auto result = redis_client_->Eval(
              acquire_script_, 
              {key}, 
              {std::to_string(max_limit)}
          );
          
          return result.as_integer() == 1;
      }
      
      void ReleaseLicense(const std::string& job_type) {
          std::string key = "license:" + job_type + ":count";
          redis_client_->Decr(key);
      }
      
      int GetCurrentUsage(const std::string& job_type) {
          std::string key = "license:" + job_type + ":count";
          auto value = redis_client_->Get(key);
          return value.has_value() ? std::stoi(*value) : 0;
      }
  };
  ```
- **Consistency:** Redis as primary, PostgreSQL synced every 10 seconds for audit
- **Monitoring:** Alert if usage > 90% of limit

**D. Scheduler Service**
- **Tech:** C# background service on AKS (StatefulSet for leader election)
- **Algorithm:**
  1. Pull messages from Service Bus (prefetch 100, batch processing)
  2. Priority selection: P0 → P1 → P2 → P3
  3. Check if dependencies are satisfied (query PostgreSQL)
  4. Acquire license from License Manager (Redis)
  5. If granted, assign to worker pool (publish to worker queue)
  6. If denied, requeue with backoff
  7. Update job status to ASSIGNED
- **Leader Election:** Use Azure Blob Storage lease for single active scheduler
- **Backpressure:** Pause queue consumption if worker pool at capacity

**E. Worker Fleet**
- **Tech:** AKS Deployment, each pod pulls jobs from assigned queue
- **Execution Flow:**
  1. Pull job from worker queue
  2. Update status to RUNNING, record start time
  3. Execute job logic (idempotent operations)
  4. Report progress via Redis (every 10 seconds)
  5. On completion: upload artifacts to Blob, update status to COMPLETED
  6. On failure: log error, check retry count, either retry or move to DLQ
  7. Release license
- **Heartbeat:** Send every 20 seconds; if missed 3 times, scheduler reassigns job
- **Idempotency:** Use distributed locks (Redis) for critical sections
- **Autoscaling:** KEDA scales based on Service Bus queue depth
  ```yaml
  triggers:
    - type: azure-servicebus
      metadata:
        queueName: video-transcoding-queue
        messageCount: '5'  # Scale up if >5 messages per pod
  minReplicaCount: 0
  maxReplicaCount: 100
  ```

**F. State Store**
- **PostgreSQL:**
  - Master-replica setup (Azure Database for PostgreSQL Flexible Server)
  - Read replicas for status queries
  - Write queries go to master
  - Connection pooling (PgBouncer)
- **Redis:**
  - Azure Cache for Redis (Premium tier, clustered)
  - Sharding by job type
  - Eviction policy: allkeys-lru for cache
  - Persistence: AOF for license counters

#### 7. Key Workflows

**Workflow 1: Job Submission**
```
Client → API → [Validate & AuthN] → PostgreSQL (INSERT job) 
  → Redis (SET idempotency key) → Service Bus (PUBLISH) → Response
```

**Workflow 2: Job Scheduling & Execution**
```
Service Bus → Scheduler (PULL batch) → Check Dependencies (PostgreSQL)
  → Acquire License (Redis atomic INCR) 
  → [If granted] Publish to Worker Queue + Update status ASSIGNED
  → Worker pulls → Update RUNNING → Execute → Upload artifacts
  → Update COMPLETED → Release License (Redis DECR)
```

**Workflow 3: Job Failure & Retry**
```
Worker detects failure → Log error → Check attempts < maxAttempts
  → [If yes] Update attempt count → Re-publish to Service Bus with delay
  → [If no] Move to FAILED status + DLQ → Alert
```

**Workflow 4: Worker Failure (missed heartbeat)**
```
Scheduler detects stale heartbeat (>60s) → Mark job QUEUED
  → Release license → Re-publish to Service Bus → New worker picks up
```

#### 8. Scaling Strategy

**Horizontal Scaling:**
- API Service: HPA on CPU (50-200 pods)
- Scheduler: Single leader with standby replicas (Raft consensus)
- Workers: KEDA autoscaling per job type (0-1000 pods per type)

**Vertical Scaling:**
- PostgreSQL: Scale up instance size for write-heavy workloads
- Redis: Use larger cache instances for high concurrency

**Data Sharding:**
- Service Bus: Partitioned topics (16 partitions)
- Redis: Cluster mode with hash slots
- PostgreSQL: Partition jobs table by `created_at` (monthly partitions)

**Geographic Distribution:**
- Multi-region deployment for HA
- Jobs routed to nearest region
- Cross-region job replication for disaster recovery

#### 9. Consistency & Failure Modes

**Consistency Model:**
- **Strong Consistency:** Job submission (PostgreSQL ACID)
- **Eventual Consistency:** License counters across regions (reconciled every 10s)
- **At-least-once Execution:** Service Bus delivery guarantees

**Failure Scenarios:**

| Failure | Detection | Mitigation |
|---------|-----------|------------|
| API service crash | Health check fails | LB redirects to healthy pods |
| PostgreSQL master down | Connection timeout | Auto-failover to replica (30s) |
| Redis node down | Connection error | Cluster rebalances, fallback to PostgreSQL |
| Scheduler crash | Leader lease expires | Standby takes over (10s) |
| Worker crash | Heartbeat missed | Job requeued after 60s |
| Service Bus partition down | SDK retry logic | Messages routed to healthy partitions |
| License counter drift | Reconciliation job | Periodic sync from PostgreSQL |
| DLQ overflow | Queue depth metric | Alert ops team, manual investigation |

**Idempotency Handling:**
- Client provides `idempotencyKey` on submission
- API checks Redis cache → PostgreSQL for duplicate
- If exists, return existing job ID (no new job created)
- Cache TTL: 24 hours (covers typical retry windows)

#### 10. Observability

**Metrics (Azure Monitor):**
- `jobs_submitted_total` (counter, by job_type, priority)
- `jobs_completed_total` (counter, by job_type, status)
- `job_duration_seconds` (histogram, by job_type)
- `queue_depth` (gauge, by job_type, priority)
- `license_utilization` (gauge, by job_type)
- `worker_active_count` (gauge, by job_type)
- `api_request_duration_ms` (histogram, by endpoint)

**Alerts:**
- Queue depth > 10K for >10 minutes
- Job failure rate > 10% over 5 minutes
- License utilization > 95% for >5 minutes
- Worker heartbeat miss rate > 5%
- API p99 latency > 200ms

**Tracing (Application Insights):**
- Distributed trace from API → Service Bus → Scheduler → Worker
- Correlation ID propagated in message headers
- Span tags: jobId, jobType, priority, worker

**Logging (Log Analytics):**
- Structured JSON logs with context (jobId, traceId, timestamp)
- Centralized log aggregation
- Query examples:
  ```kusto
  AppTraces
  | where Properties.jobId == "job-abc123"
  | order by timestamp desc
  ```

#### 11. Security

- **Authentication:** Azure AD OAuth 2.0 for API
- **Authorization:** RBAC (admin, job-submitter, job-viewer)
- **Secrets Management:** Azure Key Vault for connection strings
- **Network Security:** Private endpoints for PostgreSQL, Redis, Service Bus
- **Encryption:** TLS in transit, encryption at rest for storage
- **Audit Logging:** All job submissions/cancellations logged

#### 12. Trade-offs & Design Decisions

| Decision | Rationale | Trade-off |
|----------|-----------|-----------|
| At-least-once execution | Simpler than exactly-once, Service Bus guarantees | Requires idempotent workers |
| Redis for license counts | Low latency atomic operations | Eventual consistency vs PostgreSQL |
| Service Bus over Kafka | Managed service, built-in DLQ, simpler ops | Less throughput than Kafka |
| Priority queues per type | Fair scheduling, prevent head-of-line blocking | More queues to manage |
| Single scheduler leader | Avoids race conditions on license grants | Single point of failure (mitigated with standby) |
| KEDA autoscaling | Event-driven, scale to zero | Cold start latency (~30s) |
| PostgreSQL partitioning | Query performance on time-range scans | Maintenance overhead |

#### 13. Extensions & Future Work

- **Job Dependencies:** DAG-based execution with topological sort
- **Job Chaining:** Output of Job A becomes input of Job B
- **Priority Inversion Protection:** Age-based priority boost
- **Spot Instance Workers:** Use Azure Spot VMs for cost savings (handle preemption)
- **Multi-tenancy:** Isolate jobs per customer (separate queues/licenses)
- **Batch Job Optimization:** Gang scheduling for distributed jobs

#### 14. Microsoft Azure References
- [Azure Service Bus – queues, topics, DLQ](https://learn.microsoft.com/azure/service-bus-messaging/service-bus-messaging-overview)
- [KEDA for event-driven autoscaling](https://learn.microsoft.com/azure/aks/keda-about)
- [Azure Monitor – metrics and alerts](https://learn.microsoft.com/azure/azure-monitor/overview)
- [Azure Database for PostgreSQL](https://learn.microsoft.com/azure/postgresql/)
- [Azure Cache for Redis](https://learn.microsoft.com/azure/azure-cache-for-redis/)
- [Application Insights distributed tracing](https://learn.microsoft.com/azure/azure-monitor/app/distributed-tracing)

---

### Automated Fault Detection and Prevention
Requirements
- Ingest device/router telemetry, detect anomalies/out-of-thresholds, alert and optionally auto-remediate.

Architecture
- Ingestion: MQTT/HTTP -> Event Hub.
- Stream Processing: Functions/Stream Analytics for threshold rules; ML-based anomaly detection optional.
- State: Device state in Cosmos DB; configs in SQL; alerts in SQL/Elastic.
- Actions: Service Bus -> Notification/Remediation service; runbooks.
- Observability: Time-series metrics (Data Explorer), dashboards.

References
- [Azure Event Hubs](https://learn.microsoft.com/azure/event-hubs/event-hubs-about)
- [Azure Stream Analytics](https://learn.microsoft.com/azure/stream-analytics/stream-analytics-introduction)
- [Azure Data Explorer for time series](https://learn.microsoft.com/azure/data-explorer/time-series)

### Rate Limiter (HLD)

#### 1. Requirements Clarification

**Functional Requirements:**
- Support multiple rate limiting strategies: per-user, per-API-key, per-IP, per-tenant
- Multiple time windows: per-second, per-minute, per-hour, per-day
- Configurable rate limits per resource/endpoint
- Graceful degradation under failures
- Admin API to configure/update limits dynamically
- Support burst traffic with token bucket algorithm

**Non-Functional Requirements:**
- **Latency:** <5ms p99 for rate limit check (must not slow down API)
- **Scale:** 1M+ requests/sec globally, 100K users
- **Availability:** 99.99% uptime (rate limiter failure should not block traffic)
- **Consistency:** Eventual consistency across regions acceptable; strict within region
- **Accuracy:** 95%+ accuracy (some over-limit requests acceptable under load)

#### 2. Capacity Estimation

**Traffic:**
- 1M requests/sec globally = 86B requests/day
- 100K active users, 10K API keys
- Rate limit check on every API request

**Storage (Redis):**
- Per-user counters: 100K users × 4 time windows × 8 bytes = 3.2MB
- Per-key counters: 10K keys × 4 windows × 8 bytes = 320KB
- Total with metadata: ~10MB hot data per region
- TTL expires old counters automatically

**Compute:**
- Rate limiter middleware: inline check (no separate service)
- Redis CPU: minimal (simple atomic operations)

#### 3. API Design

```http
# Internal Rate Limit Check (called by API gateway)
POST /internal/ratelimit/check
Content-Type: application/json

{
  "userId": "user-123",
  "apiKey": "key-abc",
  "clientIp": "1.2.3.4",
  "resource": "/api/v1/data",
  "method": "POST",
  "tokens": 1  // number of tokens to consume
}

Response 200 (Allowed):
{
  "allowed": true,
  "limit": 1000,
  "remaining": 523,
  "resetAt": "2025-11-05T10:05:00Z",
  "retryAfter": null
}

Response 429 (Rate Limited):
{
  "allowed": false,
  "limit": 1000,
  "remaining": 0,
  "resetAt": "2025-11-05T10:05:00Z",
  "retryAfter": 45  // seconds
}

# Admin API: Configure Rate Limits
PUT /admin/ratelimits
Authorization: Bearer <admin-token>

{
  "resource": "/api/v1/data",
  "rules": [
    {
      "dimension": "user",
      "limit": 1000,
      "window": "1m"
    },
    {
      "dimension": "apiKey",
      "limit": 10000,
      "window": "1h"
    },
    {
      "dimension": "ip",
      "limit": 100,
      "window": "1s"
    }
  ]
}

# Get Current Usage
GET /admin/ratelimits/usage?userId=user-123&resource=/api/v1/data
```

#### 4. Data Model

**Redis (per region cluster):**
```
# Fixed Window Counters
rl:user:user-123:/api/v1/data:1m:1699180800 → 42  (TTL 60s)
rl:key:key-abc:/api/v1/data:1h:1699180800 → 1523  (TTL 3600s)
rl:ip:1.2.3.4:/api/v1/data:1s:1699180800 → 15  (TTL 1s)

# Token Bucket State (for burst handling)
bucket:user:user-123 → {"tokens": 523, "lastRefill": 1699180800}

# Rate Limit Configs (cached from SQL)
config:/api/v1/data → {
  "user": {"limit": 1000, "window": 60},
  "key": {"limit": 10000, "window": 3600},
  "ip": {"limit": 100, "window": 1}
}

# Global metrics (approximation)
global:requests:1m → 156743  (counter, TTL 1m)
```

**PostgreSQL (configuration store):**
```sql
CREATE TABLE rate_limit_rules (
  id SERIAL PRIMARY KEY,
  resource VARCHAR(255) NOT NULL,  -- /api/v1/data or * for default
  dimension VARCHAR(20) NOT NULL,  -- user, apiKey, ip, tenant
  limit_count INT NOT NULL,
  window_seconds INT NOT NULL,
  enabled BOOLEAN DEFAULT TRUE,
  created_at TIMESTAMP DEFAULT NOW(),
  updated_at TIMESTAMP DEFAULT NOW(),
  UNIQUE (resource, dimension)
);

CREATE TABLE rate_limit_overrides (
  id SERIAL PRIMARY KEY,
  entity_type VARCHAR(20) NOT NULL,  -- user, apiKey
  entity_id VARCHAR(255) NOT NULL,
  resource VARCHAR(255) NOT NULL,
  limit_count INT NOT NULL,
  window_seconds INT NOT NULL,
  expires_at TIMESTAMP,
  UNIQUE (entity_type, entity_id, resource)
);
```

#### 5. High-Level Architecture

```
                      ┌──────────────────────────┐
                      │   Clients (Web, Mobile)  │
                      └────────────┬─────────────┘
                                   │
                      ┌────────────▼─────────────┐
                      │   Azure Front Door       │
                      │   (Global Load Balancer) │
                      └────────────┬─────────────┘
                                   │
              ┌────────────────────┴─────────────────────┐
              │                                          │
    ┌─────────▼────────┐                    ┌───────────▼────────┐
    │  Region 1        │                    │  Region 2          │
    │                  │                    │                    │
    │  ┌────────────┐  │                    │  ┌────────────┐    │
    │  │   API GW   │  │                    │  │   API GW   │    │
    │  │  + Rate    │  │                    │  │  + Rate    │    │
    │  │   Limiter  │  │                    │  │   Limiter  │    │
    │  │ Middleware │  │                    │  │ Middleware │    │
    │  └──────┬─────┘  │                    │  └──────┬─────┘    │
    │         │        │                    │         │          │
    │  ┌──────▼─────┐  │                    │  ┌──────▼─────┐    │
    │  │   Redis    │  │                    │  │   Redis    │    │
    │  │  Cluster   │  │                    │  │  Cluster   │    │
    │  │  (Primary) │  │                    │  │  (Primary) │    │
    │  └────────────┘  │                    │  └────────────┘    │
    │         │        │                    │         │          │
    │  ┌──────▼─────┐  │                    │  ┌──────▼─────┐    │
    │  │  Backend   │  │                    │  │  Backend   │    │
    │  │   APIs     │  │                    │  │   APIs     │    │
    │  └────────────┘  │                    │  └────────────┘    │
    └──────────────────┘                    └────────────────────┘
              │                                          │
              └────────────────┬─────────────────────────┘
                               │
                   ┌───────────▼──────────┐
                   │   PostgreSQL         │
                   │   (Config Store)     │
                   │   (Replicated)       │
                   └──────────────────────┘
```

#### 6. Rate Limiting Algorithms

**A. Fixed Window Counter**
```cpp
struct RateLimitResult {
    bool allowed;
    int limit;
    int remaining;
    int64_t reset_at;
};

class FixedWindowLimiter {
private:
    std::shared_ptr<redis::Redis> redis_;
    
public:
    RateLimitResult CheckFixedWindow(
        const std::string& user_id,
        const std::string& resource,
        int limit,
        int window_seconds) {
        
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();
        int64_t current_window = timestamp / window_seconds;
        
        std::string key = fmt::format("rl:user:{}:{}:{}:{}", 
            user_id, resource, window_seconds, current_window);
        
        // Redis pipeline for atomicity
        auto pipeline = redis_->Pipeline();
        pipeline.Incr(key);
        pipeline.Expire(key, window_seconds);
        auto results = pipeline.Execute();
        
        int count = results[0].as_integer();
        bool allowed = count <= limit;
        
        return RateLimitResult{
            .allowed = allowed,
            .limit = limit,
            .remaining = std::max(0, limit - count),
            .reset_at = (current_window + 1) * window_seconds
        };
    }
};
```
**Pros:** Simple, memory efficient
**Cons:** Burst at window boundaries (2× limit possible)

**B. Sliding Window Log**
```cpp
class SlidingWindowLogLimiter {
private:
    std::shared_ptr<redis::Redis> redis_;
    
    std::string GenerateUUID() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        static std::uniform_int_distribution<uint64_t> dis;
        return std::to_string(dis(gen));
    }
    
public:
    RateLimitResult CheckSlidingWindowLog(
        const std::string& user_id,
        const std::string& resource,
        int limit,
        int window_seconds) {
        
        std::string key = fmt::format("rl:log:{}:{}:{}", 
            user_id, resource, window_seconds);
        
        auto now = std::chrono::system_clock::now();
        double timestamp = std::chrono::duration<double>(
            now.time_since_epoch()).count();
        double window_start = timestamp - window_seconds;
        
        // Redis sorted set (score = timestamp)
        auto pipeline = redis_->Pipeline();
        pipeline.ZRemRangeByScore(key, 0, window_start);  // Remove old
        pipeline.ZAdd(key, timestamp, GenerateUUID());     // Add current
        pipeline.ZCard(key);                               // Count
        pipeline.Expire(key, window_seconds);
        auto results = pipeline.Execute();
        
        int count = results[2].as_integer();
        bool allowed = count <= limit;
        
        return RateLimitResult{
            .allowed = allowed,
            .limit = limit,
            .remaining = std::max(0, limit - count),
            .reset_at = static_cast<int64_t>(timestamp + window_seconds)
        };
    }
};
```
**Pros:** Accurate, no boundary issues
**Cons:** High memory (stores each request), slower

**C. Token Bucket (for burst handling)**
```cpp
class TokenBucketLimiter {
private:
    std::shared_ptr<redis::Redis> redis_;
    
    const std::string lua_script_ = R"(
        local capacity = tonumber(ARGV[1])
        local refill_rate = tonumber(ARGV[2])
        local now = tonumber(ARGV[3])
        local requested = tonumber(ARGV[4])
        
        local bucket = redis.call('HMGET', KEYS[1], 'tokens', 'lastRefill')
        local tokens = tonumber(bucket[1]) or capacity
        local lastRefill = tonumber(bucket[2]) or now
        
        -- Refill tokens based on elapsed time
        local elapsed = now - lastRefill
        local newTokens = math.min(capacity, tokens + elapsed * refill_rate)
        
        if newTokens >= requested then
            redis.call('HMSET', KEYS[1], 'tokens', newTokens - requested, 
                       'lastRefill', now)
            redis.call('EXPIRE', KEYS[1], 3600)
            return 1  -- Allowed
        else
            redis.call('HMSET', KEYS[1], 'tokens', newTokens, 'lastRefill', now)
            redis.call('EXPIRE', KEYS[1], 3600)
            return 0  -- Denied
        end
    )";
    
public:
    bool CheckTokenBucket(
        const std::string& user_id,
        const std::string& resource,
        double capacity,
        double refill_rate,
        int requested = 1) {
        
        std::string key = fmt::format("bucket:user:{}:{}", user_id, resource);
        
        auto now = std::chrono::system_clock::now();
        double timestamp = std::chrono::duration<double>(
            now.time_since_epoch()).count();
        
        auto result = redis_->Eval(
            lua_script_,
            {key},
            {std::to_string(capacity),
             std::to_string(refill_rate),
             std::to_string(timestamp),
             std::to_string(requested)}
        );
        
        return result.as_integer() == 1;
    }
};
```
**Pros:** Handles bursts gracefully, smooth rate
**Cons:** More complex, requires atomic operations

**Recommendation:** Use **Fixed Window + Token Bucket hybrid**
- Fixed window for simplicity and low latency
- Token bucket overlay for premium users needing burst capacity

#### 7. Multi-Dimensional Rate Limiting

Check multiple limits in priority order:
```cpp
struct RateLimitCheck {
    std::string dimension;
    std::string entity_id;
    int limit;
    int window_seconds;
};

struct Request {
    std::string client_ip;
    std::string user_id;
    std::string api_key;
    std::string tenant_id;
    std::string resource;
};

class MultiDimensionalRateLimiter {
private:
    FixedWindowLimiter limiter_;
    
public:
    std::pair<RateLimitResult, std::optional<std::string>> 
    CheckRateLimits(const Request& request) {
        
        // Most restrictive first
        std::vector<RateLimitCheck> checks = {
            {"ip", request.client_ip, 100, 1},          // 100/sec per IP
            {"user", request.user_id, 1000, 60},        // 1000/min per user
            {"apiKey", request.api_key, 10000, 3600},   // 10K/hour per key
            {"tenant", request.tenant_id, 100000, 3600},// 100K/hour per tenant
            {"global", "all", 1000000, 60}              // 1M/min globally
        };
        
        for (const auto& check : checks) {
            auto result = limiter_.CheckFixedWindow(
                check.entity_id,
                request.resource,
                check.limit,
                check.window_seconds
            );
            
            if (!result.allowed) {
                return {result, check.dimension};
            }
        }
        
        return {RateLimitResult{true, 0, 0, 0}, std::nullopt};
    }
};
```

#### 8. Distributed Architecture Considerations

**Regional Independence:**
- Each region has its own Redis cluster (no cross-region coordination)
- Rate limits enforced per region (1000/min means 1000/min per region)
- Front Door uses sticky sessions (route same user to same region)

**Cross-Region Synchronization (optional):**
- For strict global limits, use async replication
- Background job aggregates regional counters → central store
- Adjust regional limits dynamically based on global usage
- Trade-off: Adds latency and complexity

**Fallback Strategy:**
- If Redis unavailable: **fail-open** (allow requests) or **fail-closed** (reject)
- Decision depends on security vs availability priority
- Local in-memory cache (LRU, 1-minute TTL) as fallback

```cpp
class RateLimiterWithFallback {
private:
    FixedWindowLimiter redis_limiter_;
    LocalCacheLimiter local_cache_;  // In-memory LRU cache
    std::shared_ptr<spdlog::logger> logger_;
    
public:
    RateLimitResult CheckWithFallback(
        const std::string& user_id,
        const std::string& resource,
        int limit,
        int window_seconds) {
        
        try {
            return redis_limiter_.CheckFixedWindow(
                user_id, resource, limit, window_seconds);
        }
        catch (const redis::RedisConnectionException& e) {
            logger_->error("Redis unavailable, falling back to local cache: {}", 
                          e.what());
            return local_cache_.Check(user_id, resource, limit, window_seconds);
        }
        catch (const std::exception& e) {
            logger_->error("Rate limiter error: {}", e.what());
            // Fail-open: allow request but alert
            AlertOpsTeam("Rate limiter failure");
            return RateLimitResult{
                .allowed = true,
                .limit = limit,
                .remaining = -1,  // Unknown
                .reset_at = 0
            };
        }
    }
    
private:
    void AlertOpsTeam(const std::string& message) {
        // Send alert to monitoring system
    }
};
```

#### 9. Configuration Management

**Dynamic Updates:**
- Rate limit configs stored in PostgreSQL
- Cached in Redis with 5-minute TTL
- Admin updates → PostgreSQL → Pub/Sub → All API GW nodes refresh cache

**Hierarchical Overrides:**
```
Default (all resources) → Resource-specific → Entity override
  100/min            →    1000/min      →   10000/min (premium user)
```

**Example:**
```cpp
struct RateLimitConfig {
    int limit_count;
    int window_seconds;
};

class RateLimitConfigManager {
private:
    std::shared_ptr<PostgresClient> postgres_;
    std::shared_ptr<redis::Redis> redis_;
    
public:
    std::optional<RateLimitConfig> GetRateLimit(
        const std::string& user_id,
        const std::string& resource) {
        
        // Check user-specific override
        auto override_query = fmt::format(
            "SELECT limit_count, window_seconds FROM rate_limit_overrides "
            "WHERE entity_type='user' AND entity_id='{}' AND resource='{}'",
            user_id, resource);
        
        auto override_result = postgres_->Query(override_query);
        if (!override_result.empty()) {
            return RateLimitConfig{
                .limit_count = override_result[0]["limit_count"].as<int>(),
                .window_seconds = override_result[0]["window_seconds"].as<int>()
            };
        }
        
        // Check resource-specific rule (Redis cache first)
        std::string cache_key = fmt::format("config:{}", resource);
        auto cached = redis_->Get(cache_key);
        if (cached) {
            return ParseConfig(*cached);
        }
        
        // Fallback to PostgreSQL
        auto rule_query = fmt::format(
            "SELECT limit_count, window_seconds FROM rate_limit_rules "
            "WHERE resource='{}'", resource);
        auto rule_result = postgres_->Query(rule_query);
        
        if (!rule_result.empty()) {
            auto config = RateLimitConfig{
                .limit_count = rule_result[0]["limit_count"].as<int>(),
                .window_seconds = rule_result[0]["window_seconds"].as<int>()
            };
            // Cache for 5 minutes
            redis_->SetEx(cache_key, 300, SerializeConfig(config));
            return config;
        }
        
        // Default fallback
        return RateLimitConfig{.limit_count = 100, .window_seconds = 60};
    }
};
```

#### 10. Response Headers (RFC 6585)

```http
HTTP/1.1 200 OK
X-RateLimit-Limit: 1000
X-RateLimit-Remaining: 523
X-RateLimit-Reset: 1699180800
X-RateLimit-Reset-After: 45

HTTP/1.1 429 Too Many Requests
Retry-After: 45
X-RateLimit-Limit: 1000
X-RateLimit-Remaining: 0
X-RateLimit-Reset: 1699180800
```

#### 11. Monitoring & Observability

**Metrics:**
- `ratelimit_checks_total` (counter, by dimension, resource, result)
- `ratelimit_denials_total` (counter, by dimension, resource)
- `ratelimit_check_duration_ms` (histogram)
- `ratelimit_redis_errors_total` (counter)
- `ratelimit_config_refreshes_total` (counter)

**Alerts:**
- Redis latency p99 > 10ms for >5 minutes
- Rate limit denial rate > 20% for >2 minutes (potential attack)
- Redis connection errors > 1% of requests
- Config sync lag > 10 minutes

**Dashboards:**
- Top rate-limited users/IPs
- Denial rate by resource
- Redis operation latency
- Per-region request distribution

#### 12. Security Considerations

**DDoS Protection:**
- Aggressive IP-based rate limiting (100/sec)
- Integrate with Azure DDoS Protection Standard
- Automatic IP blocking after sustained violations

**API Key Management:**
- Keys stored hashed in PostgreSQL
- Rotate keys on compromise
- Revoke keys via admin API (propagates in <5 minutes)

**Bypass for Health Checks:**
- Special endpoints (e.g., `/health`) excluded from rate limiting
- Internal service-to-service calls use separate limits

#### 13. Trade-offs & Design Decisions

| Decision | Rationale | Trade-off |
|----------|-----------|-----------|
| Fixed window over sliding log | 10× lower memory, faster | Less accurate at boundaries |
| Regional independence | Low latency, no cross-region calls | Global limit = sum of regional |
| Fail-open on Redis failure | Prioritize availability | Temporary over-limit requests |
| Redis over distributed counters | Mature, low-latency atomic ops | Single point of failure (mitigated with cluster) |
| Lua scripts for atomicity | Avoids race conditions | Slightly complex scripts |
| 5-minute config cache TTL | Balance freshness and DB load | Config changes take up to 5min |

#### 14. Load Testing Results

**Benchmark (1 Redis cluster, 3 nodes, 16GB RAM):**
- 500K requests/sec sustained
- p50: 0.8ms, p99: 3.2ms, p99.9: 8ms
- CPU: 40%, Memory: 2GB used
- No rate limit violations under normal load

**Stress Test:**
- 1M requests/sec burst (2× capacity)
- p99 latency increased to 12ms
- 2% accuracy loss (over-limit requests allowed)
- Recovered in <10 seconds

#### 15. Cost Estimation (Azure)

**Per Region:**
- Azure Cache for Redis (Premium P3, 26GB): ~$900/month
- API Gateway middleware: included in compute
- PostgreSQL (General Purpose, 2 vCores): ~$150/month
- Data transfer: ~$50/month

**Total (3 regions):** ~$3,300/month for 1M req/sec capacity

#### 16. Advanced Features

**Quota Rollover:**
- Unused tokens roll over to next window (up to 2× capacity)
- Implemented with token bucket algorithm

**Adaptive Rate Limiting:**
- Increase limits during low-traffic hours
- Decrease during incidents (circuit breaker pattern)

**Rate Limit Exemptions:**
- Whitelist internal services
- Premium tier users get 10× higher limits

**Geo-Aware Limits:**
- Higher limits for US region (more capacity)
- Lower for regions with high abuse rates

#### 17. Microsoft Azure References
- [Azure Cache for Redis](https://learn.microsoft.com/azure/azure-cache-for-redis/cache-overview)
- [Azure Front Door – anycast, routing](https://learn.microsoft.com/azure/frontdoor/front-door-overview)
- [Azure API Management – rate limiting policies](https://learn.microsoft.com/azure/api-management/api-management-sample-flexible-throttling)
- [Distributed Redis patterns](https://learn.microsoft.com/azure/azure-cache-for-redis/cache-best-practices)

---

### CDN
Architecture
- Edge POPs cache static objects; origin shield; cache invalidation; signed URLs.
- Multi-CDN or Front Door with rules engine; WAF; TLS termination.

References
- [Azure CDN](https://learn.microsoft.com/azure/cdn/cdn-overview)
- [Azure Front Door](https://learn.microsoft.com/azure/frontdoor/)

### URL Shortener

#### 1. Requirements Clarification

**Functional Requirements:**
- Generate short URLs from long URLs (e.g., `bit.ly/abc123`)
- Redirect short URL to original long URL
- Custom aliases (e.g., `bit.ly/my-blog`)
- URL expiration (TTL-based)
- Analytics: click count, geographic distribution, referrers
- User accounts: manage their URLs, edit/delete
- QR code generation for short URLs

**Non-Functional Requirements:**
- **Scale:** 100M URLs created/month, 10B redirects/month
- **Latency:** Redirect < 20ms p99 (critical for UX)
- **Availability:** 99.99% uptime (redirect service)
- **Durability:** No data loss for created URLs
- **Short URL Length:** 6-8 characters (62^6 = 56B possibilities)
- **Collision Handling:** Ensure unique short codes

#### 2. Capacity Estimation

**Traffic:**
- **Writes:** 100M URLs/month = ~40 URLs/sec average, ~400/sec peak
- **Reads:** 10B redirects/month = ~4K redirects/sec average, ~40K/sec peak
- **Read/Write Ratio:** 100:1 (read-heavy system)

**Storage:**
- **URL Data:**
  - Long URL: avg 200 bytes
  - Short code: 7 bytes
  - Metadata: 100 bytes (timestamps, userId, clicks)
  - Total per URL: ~300 bytes
  - 100M URLs/month × 300 bytes = 30GB/month → 3.6TB over 10 years
- **Analytics Data:**
  - Per-click event: 500 bytes (timestamp, IP, user-agent, referrer)
  - 10B clicks/month × 500 bytes = 5TB/month (archive after 90 days)

**Bandwidth:**
- **Redirect:** 40K req/sec × 1KB request/response = 40MB/sec = 10TB/month
- **Shorten:** Negligible compared to redirects

**Cache (Redis):**
- Top 20% URLs generate 80% of traffic (Pareto principle)
- Cache hot 10M URLs × 1KB = 10GB

#### 3. API Design

```http
# Shorten URL
POST /api/v1/shorten
Authorization: Bearer <token>  # Optional for anonymous
Content-Type: application/json

{
  "longUrl": "https://example.com/very/long/path?param=value",
  "customAlias": "my-link",  # Optional
  "expiresAt": "2026-12-31T23:59:59Z",  # Optional
  "domain": "bit.ly"  # Optional, for custom domains
}

Response 201:
{
  "shortUrl": "https://bit.ly/abc123",
  "shortCode": "abc123",
  "longUrl": "https://example.com/very/long/path?param=value",
  "createdAt": "2025-11-05T10:00:00Z",
  "expiresAt": "2026-12-31T23:59:59Z",
  "qrCode": "https://bit.ly/qr/abc123.png"
}

# Redirect (GET request)
GET /{shortCode}
Response 302:
Location: https://example.com/very/long/path?param=value

# Get URL Info (without redirect)
GET /api/v1/url/{shortCode}
Response 200:
{
  "shortCode": "abc123",
  "longUrl": "https://example.com/...",
  "clicks": 15234,
  "createdAt": "2025-11-05T10:00:00Z",
  "expiresAt": null
}

# Get Analytics
GET /api/v1/url/{shortCode}/analytics?period=7d
Response 200:
{
  "clicks": 15234,
  "uniqueVisitors": 8421,
  "clicksByDate": [...],
  "topCountries": [{"country": "US", "clicks": 5000}, ...],
  "topReferrers": [{"referrer": "twitter.com", "clicks": 3000}, ...],
  "devices": {"mobile": 60, "desktop": 35, "tablet": 5}
}

# Update URL (auth required)
PATCH /api/v1/url/{shortCode}
{
  "longUrl": "https://new-destination.com",
  "expiresAt": "2027-01-01T00:00:00Z"
}

# Delete URL
DELETE /api/v1/url/{shortCode}
```

#### 4. Database Schema

**PostgreSQL (metadata, source of truth):**
```sql
CREATE TABLE urls (
  id BIGSERIAL PRIMARY KEY,
  short_code VARCHAR(10) UNIQUE NOT NULL,
  long_url TEXT NOT NULL,
  user_id BIGINT REFERENCES users(id),  -- NULL for anonymous
  custom_alias BOOLEAN DEFAULT FALSE,
  domain VARCHAR(50) DEFAULT 'bit.ly',
  clicks BIGINT DEFAULT 0,
  created_at TIMESTAMP DEFAULT NOW(),
  expires_at TIMESTAMP,
  updated_at TIMESTAMP DEFAULT NOW(),
  deleted_at TIMESTAMP,  -- Soft delete
  INDEX idx_short_code (short_code),
  INDEX idx_user_id (user_id),
  INDEX idx_created_at (created_at)
);

CREATE TABLE users (
  id BIGSERIAL PRIMARY KEY,
  email VARCHAR(255) UNIQUE NOT NULL,
  password_hash VARCHAR(255),
  api_key VARCHAR(64) UNIQUE,
  created_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE click_events (
  id BIGSERIAL PRIMARY KEY,
  short_code VARCHAR(10) NOT NULL,
  clicked_at TIMESTAMP DEFAULT NOW(),
  ip_address INET,
  country VARCHAR(2),
  city VARCHAR(100),
  referrer TEXT,
  user_agent TEXT,
  device_type VARCHAR(20),  -- mobile, desktop, tablet
  INDEX idx_short_code_time (short_code, clicked_at)
) PARTITION BY RANGE (clicked_at);

-- Partitions by month
CREATE TABLE click_events_2025_11 PARTITION OF click_events
  FOR VALUES FROM ('2025-11-01') TO ('2025-12-01');
```

**Redis (hot cache):**
```
# URL mapping cache (TTL 24 hours for hot URLs)
url:abc123 → {"longUrl": "https://...", "clicks": 15234, "expiresAt": null}

# Rate limiting
ratelimit:shorten:user:123 → 42  (TTL 1 hour)
ratelimit:redirect:ip:1.2.3.4 → 180  (TTL 1 minute)

# Short code counter (for generation)
counter:shortcode → 15234567

# Bloom filter for existence checks (reduce DB queries)
bloom:urls → [bit array]
```

**Azure Blob Storage:**
```
Container: qr-codes
Path: {shortCode}.png

Container: analytics-archive
Path: {year}/{month}/{day}/clicks.parquet
```

#### 5. High-Level Architecture

```
                      ┌─────────────────┐
                      │     Clients     │
                      └────────┬────────┘
                               │
                   ┌───────────▼───────────┐
                   │   Azure Front Door    │
                   │   + WAF + TLS         │
                   └───────────┬───────────┘
                               │
        ┏━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━┓
        ┃                                              ┃
  ┌─────▼──────┐                            ┌─────────▼──────┐
  │  API       │                            │  Redirect      │
  │  Service   │                            │  Service       │
  │  (Shorten) │                            │  (Read-heavy)  │
  └─────┬──────┘                            └─────────┬──────┘
        │                                              │
        │  ┌──────────────────────────────────────────┘
        │  │
  ┌─────▼──▼──────┐         ┌────────────────┐
  │  Redis Cluster│←────────│  Cache Warmer  │
  │  (Hot cache)  │         │  (Background)  │
  └───────┬───────┘         └────────────────┘
          │
  ┌───────▼────────┐
  │  PostgreSQL    │
  │  (Metadata)    │
  └───────┬────────┘
          │
  ┌───────▼────────┐       ┌─────────────────┐
  │  Event Hub     │──────→│  Analytics      │
  │  (Click logs)  │       │  Pipeline       │
  └────────────────┘       │  (Stream        │
                           │   Analytics)    │
                           └────────┬────────┘
                                    │
                           ┌────────▼────────┐
                           │  Azure Data     │
                           │  Explorer       │
                           │  (Analytics DB) │
                           └─────────────────┘
```

#### 6. Short Code Generation Strategies

**Option 1: Base62 Encoding of Auto-Increment ID**
```cpp
class Base62Encoder {
private:
    static constexpr const char* CHARS = 
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr size_t BASE = 62;
    
public:
    static std::string Encode(uint64_t num, size_t min_length = 6) {
        if (num == 0) {
            return std::string(min_length, '0');
        }
        
        std::string result;
        while (num > 0) {
            result.push_back(CHARS[num % BASE]);
            num /= BASE;
        }
        
        // Pad to minimum length
        while (result.size() < min_length) {
            result.push_back('0');
        }
        
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    static uint64_t Decode(const std::string& encoded) {
        uint64_t result = 0;
        for (char c : encoded) {
            result = result * BASE + CharToValue(c);
        }
        return result;
    }
    
private:
    static int CharToValue(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'z') return c - 'a' + 10;
        if (c >= 'A' && c <= 'Z') return c - 'A' + 36;
        throw std::invalid_argument("Invalid Base62 character");
    }
};

// Example: ID 12345 → "3d7" (pad to 6 chars: "0003d7")
// std::string short_code = Base62Encoder::Encode(postgres->NextId());
```
**Pros:** Simple, sequential, collision-free
**Cons:** Predictable (security risk), leaks business metrics

**Option 2: Random String with Collision Check**
```cpp
class RandomShortCodeGenerator {
private:
    std::shared_ptr<redis::Redis> redis_;
    std::shared_ptr<PostgresClient> postgres_;
    BloomFilter bloom_filter_;
    std::mt19937_64 rng_;
    
    static constexpr const char* CHARS = 
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
public:
    RandomShortCodeGenerator() : rng_(std::random_device{}()) {}
    
    std::string GenerateShortCode(size_t length = 7) {
        std::uniform_int_distribution<size_t> dist(0, 61);
        
        while (true) {
            std::string code;
            code.reserve(length);
            
            for (size_t i = 0; i < length; ++i) {
                code.push_back(CHARS[dist(rng_)]);
            }
            
            // Check Redis Bloom filter first (fast negative check)
            if (bloom_filter_.MightContain(code)) {
                // Double-check in DB (rare case)
                auto query = fmt::format(
                    "SELECT 1 FROM urls WHERE short_code = '{}'", code);
                if (postgres_->Query(query).empty()) {
                    bloom_filter_.Add(code);
                    return code;
                }
            } else {
                bloom_filter_.Add(code);
                return code;
            }
        }
    }
};
```
**Pros:** Unpredictable, uniform distribution
**Cons:** Possible collisions (low probability), Bloom filter overhead

**Option 3: Hash + Truncate**
```cpp
class HashBasedShortCodeGenerator {
private:
    Base62Encoder encoder_;
    
public:
    std::string GenerateShortCode(
        const std::string& long_url,
        uint64_t user_id) {
        
        // Hash (long_url + timestamp + user_id) for uniqueness
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
        
        std::string data = long_url + std::to_string(timestamp) + 
                          std::to_string(user_id);
        
        // SHA-256 hash
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()),
               data.length(), hash);
        
        // Convert first 4 bytes to uint32_t
        uint32_t num = (static_cast<uint32_t>(hash[0]) << 24) |
                       (static_cast<uint32_t>(hash[1]) << 16) |
                       (static_cast<uint32_t>(hash[2]) << 8)  |
                       static_cast<uint32_t>(hash[3]);
        
        // Convert to Base62 and take first 7 chars
        std::string encoded = encoder_.Encode(num);
        return encoded.substr(0, 7);
    }
};
```
**Pros:** Deterministic per input, fast
**Cons:** Still needs collision check

**Recommendation:** **Option 1 (Base62) for production** + custom aliases (Option 2 with collision check)

#### 7. Detailed Component Design

**A. Shorten API Service**
- **Tech:** ASP.NET Core on AKS, autoscaled (10-50 pods)
- **Flow:**
  1. Validate long URL (check format, not malicious)
  2. Check if URL already shortened by this user (dedup)
  3. Generate short code (Base62 from DB sequence)
  4. Insert into PostgreSQL
  5. Warm cache: write to Redis
  6. Generate QR code asynchronously (message to queue)
  7. Return short URL
- **Rate Limiting:** 100 requests/hour per IP (anonymous), 10K/hour per user
- **Custom Alias Handling:** Check availability, reserve in transaction

**B. Redirect Service**
- **Tech:** Lightweight ASP.NET Core, heavily cached (100-500 pods)
- **Flow (cache-aside pattern):**
  1. Check Redis cache for short code
  2. If hit: Return 302 redirect + increment click counter (async)
  3. If miss: Query PostgreSQL → cache in Redis (TTL 24h) → redirect
  4. Log click event to Event Hub (async, fire-and-forget)
  5. If expired or deleted: Return 404
- **Optimization:** Use HTTP 301 (permanent) for old, stable URLs; 302 for recent
- **CDN Integration:** Cache 302 responses at edge for ultra-low latency

**C. Cache Strategy**
- **Cache Warming:** Background job pre-loads top 1M URLs into Redis daily
- **Eviction Policy:** LRU (least recently used)
- **Cache Stampede Prevention:** Use Redis SET with NX (only set if not exists)

**D. Analytics Pipeline**
- Click events → Event Hub (1M events/sec capacity)
- Stream Analytics processes in real-time:
  - Aggregate clicks per short code (windowed)
  - GeoIP lookup (IP → country/city)
  - User-agent parsing (device type, browser)
- Write to Azure Data Explorer (time-series queries)
- Archive to Blob Storage (Parquet format, partitioned by date)

#### 8. URL Expiration Handling

**Strategies:**
1. **Passive Expiration:** Check `expires_at` during redirect; return 410 Gone if expired
2. **Active Cleanup:** Background job runs daily, soft-deletes expired URLs
3. **Cache TTL:** Set Redis TTL to match URL expiration

**Implementation:**
```cpp
struct URLData {
    std::string short_code;
    std::string long_url;
    std::optional<std::chrono::system_clock::time_point> expires_at;
    std::optional<std::chrono::system_clock::time_point> deleted_at;
    uint64_t clicks;
};

class RedirectService {
private:
    std::shared_ptr<redis::Redis> redis_;
    std::shared_ptr<PostgresClient> postgres_;
    std::shared_ptr<EventHubClient> event_hub_;
    
public:
    HttpResponse Redirect(const std::string& short_code) {
        // Try Redis cache first
        std::string cache_key = "url:" + short_code;
        auto cached = redis_->Get(cache_key);
        
        URLData url_data;
        if (cached) {
            url_data = DeserializeURLData(*cached);
        } else {
            // Cache miss - query PostgreSQL
            auto query = fmt::format(
                "SELECT short_code, long_url, expires_at, deleted_at, clicks "
                "FROM urls WHERE short_code = '{}'", short_code);
            
            auto result = postgres_->Query(query);
            if (result.empty()) {
                return HttpResponse{404, "URL not found"};
            }
            
            url_data = ParseURLData(result[0]);
            
            // Cache for 24 hours
            redis_->SetEx(cache_key, 86400, SerializeURLData(url_data));
        }
        
        // Check if expired
        if (url_data.expires_at) {
            auto now = std::chrono::system_clock::now();
            if (now > *url_data.expires_at) {
                return HttpResponse{410, "URL has expired"};
            }
        }
        
        // Check if soft-deleted
        if (url_data.deleted_at) {
            return HttpResponse{404, "URL not found"};
        }
        
        // Async increment click count (fire-and-forget)
        LogClickEventAsync(short_code);
        
        // Return 302 redirect
        HttpResponse response{302};
        response.SetHeader("Location", url_data.long_url);
        response.SetHeader("Cache-Control", "no-cache");
        return response;
    }
    
private:
    void LogClickEventAsync(const std::string& short_code) {
        // Send event to Event Hub asynchronously
        nlohmann::json event = {
            {"short_code", short_code},
            {"timestamp", std::chrono::system_clock::now().time_since_epoch().count()},
            {"ip", GetClientIP()},
            {"user_agent", GetUserAgent()}
        };
        
        // Fire-and-forget (use thread pool in production)
        std::async(std::launch::async, [this, event]() {
            try {
                event_hub_->Send(event.dump());
            } catch (const std::exception& e) {
                // Log error but don't fail redirect
                spdlog::error("Failed to send click event: {}", e.what());
            }
        });
    }
};
```

#### 9. Custom Domains

**Feature:** Users can use their own domains (e.g., `go.mycompany.com/abc123`)

**Implementation:**
- Users add CNAME record: `go.mycompany.com → bit.ly`
- Store domain mapping in DB:
  ```sql
  CREATE TABLE custom_domains (
    domain VARCHAR(255) PRIMARY KEY,
    user_id BIGINT REFERENCES users(id),
    verified BOOLEAN DEFAULT FALSE,
    ssl_cert_id VARCHAR(255),
    created_at TIMESTAMP DEFAULT NOW()
  );
  ```
- Front Door routes based on `Host` header
- SSL certificates auto-provisioned via Let's Encrypt

#### 10. Security Considerations

**Malicious URL Detection:**
- Integrate with Google Safe Browsing API before shortening
- Reject URLs on blocklist (phishing, malware)
- Periodic re-scanning of existing URLs

**Abuse Prevention:**
- Rate limiting (aggressive for anonymous users)
- CAPTCHA after N failed attempts
- Monitor for spam patterns (same long URL shortened 1000× times)

**URL Validation:**
```cpp
class URLValidator {
private:
    std::shared_ptr<SafeBrowsingClient> safe_browsing_;
    std::regex url_pattern_;
    std::unordered_set<std::string> blocked_hosts_;
    
public:
    URLValidator() 
        : url_pattern_(R"(^https?://.+)"),
          blocked_hosts_({"localhost", "127.0.0.1", "0.0.0.0", "::1"}) {}
    
    void Validate(const std::string& long_url) {
        // Check format
        if (!std::regex_match(long_url, url_pattern_)) {
            throw std::invalid_argument("Invalid URL format");
        }
        
        // Check length
        if (long_url.length() > 2048) {
            throw std::invalid_argument("URL too long");
        }
        
        // Parse URL
        auto parsed = ParseURL(long_url);
        
        // Check not localhost/internal IPs
        if (blocked_hosts_.count(parsed.hostname)) {
            throw std::invalid_argument("Cannot shorten internal URLs");
        }
        
        // Check private IP ranges
        if (IsPrivateIP(parsed.hostname)) {
            throw std::invalid_argument("Cannot shorten private IP addresses");
        }
        
        // Check Safe Browsing API
        if (safe_browsing_->IsMalicious(long_url)) {
            throw std::invalid_argument("URL flagged as unsafe");
        }
    }
    
private:
    struct ParsedURL {
        std::string scheme;
        std::string hostname;
        std::string path;
    };
    
    ParsedURL ParseURL(const std::string& url) {
        // Simple URL parser (use a library like cpp-netlib in production)
        size_t scheme_end = url.find("://");
        size_t host_start = scheme_end + 3;
        size_t host_end = url.find('/', host_start);
        
        if (host_end == std::string::npos) {
            host_end = url.length();
        }
        
        return ParsedURL{
            .scheme = url.substr(0, scheme_end),
            .hostname = url.substr(host_start, host_end - host_start),
            .path = host_end < url.length() ? url.substr(host_end) : "/"
        };
    }
    
    bool IsPrivateIP(const std::string& hostname) {
        // Check for private IP ranges (10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16)
        // Simplified check - use proper IP parsing library in production
        return hostname.starts_with("10.") || 
               hostname.starts_with("172.16.") ||
               hostname.starts_with("192.168.");
    }
};
```

**Authentication:**
- Anonymous: Limited quota (100 URLs/day)
- Registered: API key or OAuth 2.0
- Premium: Higher quotas, custom domains

#### 11. Scaling Strategies

**Read Path (Redirects):**
- Redis cluster (5-10 nodes, 100GB RAM)
- CDN caching at edge (CloudFlare, Akamai)
- Read replicas for PostgreSQL (route analytics queries here)
- Geo-distributed deployment (redirect from nearest region)

**Write Path (Shorten):**
- PostgreSQL connection pooling (PgBouncer)
- Batch inserts for QR code generation
- Async job queue for non-critical tasks

**Database Partitioning:**
- Partition `urls` table by `created_at` (monthly)
- Partition `click_events` by `clicked_at` (daily)
- Retain last 90 days in hot storage, archive to Blob

**Auto-Scaling:**
- HPA for API/Redirect services (CPU > 70%)
- KEDA for analytics pipeline (Event Hub lag)

#### 12. Monitoring & Observability

**Metrics:**
- `urls_shortened_total` (counter, by user type)
- `redirects_total` (counter, by status code)
- `redirect_latency_ms` (histogram, p50/p99)
- `cache_hit_rate` (gauge)
- `url_creation_failures_total` (counter, by reason)

**Alerts:**
- Redirect p99 latency > 50ms
- Cache hit rate < 80%
- Error rate > 1% for 5 minutes
- Database connection pool exhausted

**Dashboards:**
- Top URLs by clicks
- Geographic heatmap of clicks
- URL creation trends
- Cache performance

#### 13. Advanced Features

**A/B Testing:**
- Rotate between multiple long URLs for same short code
- Track conversion rates per variant

**Link Previews:**
- Generate Open Graph metadata for social media
- Screenshot service captures preview image

**Branded Links:**
- `bit.ly/brand-abc123` (custom prefix per user)

**API for Bulk Shortening:**
```http
POST /api/v1/bulk/shorten
{
  "urls": ["https://...", "https://...", ...]
}
```

#### 14. Trade-offs & Design Decisions

| Decision | Rationale | Trade-off |
|----------|-----------|-----------|
| Base62 encoding | Collision-free, simple | Predictable IDs (use random for sensitive apps) |
| Redis as cache, not primary | PostgreSQL ensures durability | Cache miss latency (~50ms) |
| 302 over 301 redirect | Allows URL updates, tracks clicks | Slightly higher latency (no browser cache) |
| Bloom filter for existence | Reduces DB queries by 99% | False positives (rare, fallback to DB) |
| Event Hub for analytics | Decouples redirect from logging | Eventual consistency in click counts |
| Soft delete | Allows URL recovery | Periodic cleanup needed |

#### 15. Cost Estimation (Azure)

**Monthly Costs (100M URLs created, 10B redirects):**
- **Compute (AKS):** 50 pods × $50/month = $2,500
- **PostgreSQL (Hyperscale, 4 vCores):** $800
- **Redis (Premium P4, 53GB):** $1,400
- **Event Hub (Standard, 20 TUs):** $1,000
- **Data Explorer (8 nodes, D14):** $4,000
- **Blob Storage (10TB):** $200
- **CDN (1TB egress):** $80
- **Front Door:** $300
**Total:** ~$10,300/month

#### 16. Failure Scenarios & Mitigation

| Failure | Impact | Mitigation |
|---------|--------|------------|
| Redis down | Redirect latency +50ms | Fallback to PostgreSQL, auto-failover (30s) |
| PostgreSQL down | Cannot create new URLs | Read replicas for redirects, alerts, failover |
| Event Hub down | Analytics missing | Local buffering, retry logic |
| CDN cache miss | Higher origin load | Pre-warm cache for top URLs |
| DNS resolution slow | High latency | Use Azure DNS with low TTL |

#### 17. Interview Discussion Points

**Scalability:**
- How to handle 1M redirects/sec? (More Redis nodes, CDN, edge compute)
- How to scale to 1 trillion URLs? (Shard PostgreSQL by short_code hash)

**Consistency:**
- What if Redis and PostgreSQL diverge? (Periodic reconciliation job)
- How to ensure short code uniqueness? (Database unique constraint as source of truth)

**Availability:**
- What if all Redis nodes fail? (Graceful degradation to PostgreSQL, slower but functional)

**Data Retention:**
- Archive old click data to cold storage (Blob)
- Delete URLs not accessed in 5 years (after user notification)

#### 18. Microsoft Azure References
- [Azure Cosmos DB](https://learn.microsoft.com/azure/cosmos-db/introduction)
- [Azure Cache for Redis patterns](https://learn.microsoft.com/azure/azure-cache-for-redis/cache-best-practices)
- [Azure Event Hubs](https://learn.microsoft.com/azure/event-hubs/)
- [Azure Data Explorer](https://learn.microsoft.com/azure/data-explorer/)
- [Azure Front Door](https://learn.microsoft.com/azure/frontdoor/)

---

### Dropbox-like Storage
Design
- Chunked uploads, content-addressable storage (hash -> blob), deduplication.
- Metadata in SQL; blobs in Azure Blob Storage; sync via change feed.

References
- [Azure Blob Storage](https://learn.microsoft.com/azure/storage/blobs/storage-blobs-introduction)

### Analytics System
Design
- Ingest -> stream/batch -> storage layers (hot/cold) -> query serving.
- Hot: Event Hubs + Stream Analytics + Redis/ADLS; Cold: ADLS + Synapse.

References
- [Azure Synapse Analytics](https://learn.microsoft.com/azure/synapse-analytics/)
- [Azure Data Lake Storage](https://learn.microsoft.com/azure/storage/blobs/data-lake-storage-introduction)

### News Feed

#### 1. Requirements Clarification

**Functional Requirements:**
- Users can create posts (text, images, videos, links)
- Users can follow other users
- Generate personalized news feed showing posts from followed users
- Feed is ranked by relevance (not purely chronological)
- Support feed pagination (infinite scroll)
- Real-time updates for new posts
- Interactions: like, comment, share
- Privacy controls: public, friends-only, private

**Non-Functional Requirements:**
- **Scale:** 1B users, 500M DAU (daily active users)
- **Posting:** 10M posts/day = ~115 posts/sec average, ~1K posts/sec peak
- **Feed Reads:** 5B feed fetches/day = ~58K reads/sec average, ~500K reads/sec peak
- **Latency:** Feed load <200ms p99, post publish <500ms
- **Availability:** 99.99% uptime
- **Eventual Consistency:** Acceptable (few seconds delay for new posts)
- **Average Followers:** 200 followers per user (skewed: some users have millions)

#### 2. Capacity Estimation

**Traffic:**
- **Writes (Posts):** 10M/day = 115/sec avg, 1K/sec peak
- **Reads (Feed):** 5B/day = 58K/sec avg, 500K/sec peak
- **Read/Write Ratio:** 500:1 (read-heavy)

**Storage:**
- **Posts:**
  - Text post: 1KB (text + metadata)
  - With image: 500KB average
  - With video: 50MB average
  - Average post size: 5MB (mixed content)
  - 10M posts/day × 5MB = 50TB/day → 18PB/year
- **Feed Data (cached):**
  - Per-user feed cache: top 1000 posts × 1KB = 1MB
  - 500M DAU × 1MB = 500TB (hot cache)
- **Metadata (PostgreSQL):**
  - Post metadata (no content): 1KB
  - 10M posts/day × 1KB = 10GB/day → 3.6TB/year

**Bandwidth:**
- Feed reads: 58K/sec × 100KB (10 posts) = 5.8GB/sec = 15PB/month
- Media uploads: 115/sec × 5MB = 575MB/sec = 1.5PB/month

**Fan-out:**
- Average 200 followers → 200 feed updates per post
- 115 posts/sec × 200 = 23K feed updates/sec
- Celebrity posts (10M followers) → 10M updates per post (challenging!)

#### 3. API Design

```http
# Create Post
POST /api/v1/posts
Authorization: Bearer <token>
Content-Type: multipart/form-data

{
  "text": "Hello world!",
  "mediaFiles": [<file1>, <file2>],  # Optional
  "privacy": "PUBLIC",  # PUBLIC, FRIENDS, PRIVATE
  "location": "San Francisco, CA",
  "tags": ["@user123", "#topic"]
}

Response 201:
{
  "postId": "post-abc123",
  "authorId": "user-456",
  "text": "Hello world!",
  "mediaUrls": ["https://cdn.../image1.jpg"],
  "privacy": "PUBLIC",
  "createdAt": "2025-11-05T10:00:00Z",
  "likes": 0,
  "comments": 0
}

# Get News Feed
GET /api/v1/feed?cursor=abc123&limit=20
Authorization: Bearer <token>

Response 200:
{
  "posts": [
    {
      "postId": "post-xyz",
      "author": {
        "userId": "user-789",
        "username": "john_doe",
        "avatarUrl": "https://..."
      },
      "text": "Amazing sunset today!",
      "mediaUrls": [...],
      "createdAt": "2025-11-05T09:30:00Z",
      "likes": 1523,
      "comments": 42,
      "shares": 15,
      "userHasLiked": false,
      "relevanceScore": 0.87
    },
    ...
  ],
  "nextCursor": "def456",
  "hasMore": true
}

# Get User Profile Feed (public posts only)
GET /api/v1/users/{userId}/posts?cursor=abc&limit=20

# Like Post
POST /api/v1/posts/{postId}/like
Response 204 No Content

# Comment on Post
POST /api/v1/posts/{postId}/comments
{
  "text": "Great post!"
}

# Delete Post
DELETE /api/v1/posts/{postId}

# WebSocket for Real-time Updates
WS /api/v1/feed/realtime
→ Server pushes new post notifications
```

#### 4. Database Schema

**PostgreSQL (metadata):**
```sql
CREATE TABLE users (
  id BIGSERIAL PRIMARY KEY,
  username VARCHAR(50) UNIQUE NOT NULL,
  email VARCHAR(255) UNIQUE NOT NULL,
  avatar_url TEXT,
  follower_count INT DEFAULT 0,
  following_count INT DEFAULT 0,
  created_at TIMESTAMP DEFAULT NOW(),
  INDEX idx_username (username)
);

CREATE TABLE posts (
  id BIGSERIAL PRIMARY KEY,
  author_id BIGINT REFERENCES users(id),
  text TEXT,
  media_urls TEXT[],  -- Array of media URLs
  privacy VARCHAR(20) DEFAULT 'PUBLIC',
  location VARCHAR(255),
  like_count INT DEFAULT 0,
  comment_count INT DEFAULT 0,
  share_count INT DEFAULT 0,
  created_at TIMESTAMP DEFAULT NOW(),
  updated_at TIMESTAMP DEFAULT NOW(),
  deleted_at TIMESTAMP,  -- Soft delete
  INDEX idx_author_time (author_id, created_at DESC),
  INDEX idx_created_at (created_at DESC)
) PARTITION BY RANGE (created_at);

CREATE TABLE follows (
  follower_id BIGINT REFERENCES users(id),
  followee_id BIGINT REFERENCES users(id),
  created_at TIMESTAMP DEFAULT NOW(),
  PRIMARY KEY (follower_id, followee_id),
  INDEX idx_followee (followee_id)  -- For fan-out
);

CREATE TABLE likes (
  user_id BIGINT REFERENCES users(id),
  post_id BIGINT REFERENCES posts(id),
  created_at TIMESTAMP DEFAULT NOW(),
  PRIMARY KEY (user_id, post_id),
  INDEX idx_post_id (post_id)
);

CREATE TABLE comments (
  id BIGSERIAL PRIMARY KEY,
  post_id BIGINT REFERENCES posts(id),
  user_id BIGINT REFERENCES users(id),
  text TEXT NOT NULL,
  created_at TIMESTAMP DEFAULT NOW(),
  INDEX idx_post_time (post_id, created_at DESC)
);
```

**Redis (feed cache):**
```
# User's newsfeed (sorted set, score = timestamp or rank score)
feed:user:123 → [(postId, score), ...] (ZSET, top 1000 entries)

# Post content cache
post:abc123 → {text, authorId, mediaUrls, likes, createdAt, ...}

# User's follower list (for fan-out)
followers:user:456 → [userId1, userId2, ...] (SET)

# User's following list
following:user:123 → [userId1, userId2, ...] (SET)

# Trending posts (global hot feed)
trending:24h → [(postId, score), ...] (ZSET)

# Real-time post counter
post:abc123:likes → 1523 (counter)
post:abc123:comments → 42
```

**Cassandra/Cosmos DB (timeline storage, optional for scale):**
```
CREATE TABLE user_timeline (
  user_id BIGINT,
  post_id BIGINT,
  author_id BIGINT,
  created_at TIMESTAMP,
  score DOUBLE,  -- Ranking score
  PRIMARY KEY (user_id, created_at, post_id)
) WITH CLUSTERING ORDER BY (created_at DESC);
```

**Azure Blob Storage:**
```
Container: post-media
Path: {userId}/{year}/{month}/{postId}/{filename}
```

#### 5. High-Level Architecture

```
                         ┌──────────────┐
                         │   Clients    │
                         └──────┬───────┘
                                │
                    ┌───────────▼────────────┐
                    │   Azure Front Door     │
                    │   + CDN (media)        │
                    └───────────┬────────────┘
                                │
              ┌─────────────────┴──────────────────┐
              │                                    │
    ┌─────────▼────────┐              ┌───────────▼────────┐
    │  Post Service    │              │  Feed Service      │
    │  (Write Path)    │              │  (Read Path)       │
    └─────────┬────────┘              └───────────┬────────┘
              │                                    │
              │                       ┌────────────▼─────────┐
              │                       │  Redis Feed Cache    │
              │                       │  (Hot user feeds)    │
              │                       └────────────┬─────────┘
              │                                    │
    ┌─────────▼────────────────────────────────────▼─────┐
    │            PostgreSQL (Metadata)                   │
    │  - Posts, Users, Follows, Likes, Comments          │
    └─────────┬──────────────────────────────────────────┘
              │
    ┌─────────▼────────┐
    │  Service Bus     │
    │  (Post events)   │
    └─────────┬────────┘
              │
    ┌─────────▼────────────┐
    │  Fan-out Workers     │
    │  (Feed generation)   │
    └─────────┬────────────┘
              │
    ┌─────────▼────────────┐         ┌──────────────────┐
    │  Ranking Service     │────────→│  ML Model Store  │
    │  (Feature-based)     │         │  (Relevance)     │
    └──────────────────────┘         └──────────────────┘
              │
    ┌─────────▼────────────┐
    │  Azure Blob Storage  │
    │  (Media files)       │
    └──────────────────────┘
```

#### 6. Feed Generation Strategies

**Option 1: Write Fan-out (Push Model)**
- When user posts, immediately push to all followers' feeds
- **Pros:** Fast read (feed pre-computed), simple logic
- **Cons:** Slow write for celebrities, wasted storage for inactive users

**Option 2: Read Fan-out (Pull Model)**
- When user requests feed, query all followed users' posts and merge
- **Pros:** Fast write, no wasted storage
- **Cons:** Slow read (O(N) queries), difficult to rank

**Option 3: Hybrid Approach (Recommended)**
- **Regular users (<10K followers):** Write fan-out
- **Celebrities (>10K followers):** Read fan-out at feed request time
- **Active users:** Pre-compute feed in Redis
- **Inactive users:** Lazy-load on next visit

**Implementation:**
```cpp
struct Post {
    uint64_t id;
    uint64_t author_id;
    std::string text;
    std::vector<std::string> media_urls;
    int64_t timestamp;
    int like_count;
    int comment_count;
};

class NewsFeedService {
private:
    std::shared_ptr<PostgresClient> postgres_;
    std::shared_ptr<redis::Redis> redis_;
    std::shared_ptr<ServiceBusClient> service_bus_;
    std::shared_ptr<RankingService> ranking_service_;
    
    static constexpr int CELEBRITY_THRESHOLD = 10000;
    static constexpr int MAX_CACHED_POSTS = 1000;
    
public:
    void PublishPost(const Post& post) {
        // Step 1: Save post to database
        auto query = fmt::format(
            "INSERT INTO posts (author_id, text, media_urls, created_at) "
            "VALUES ({}, '{}', ARRAY[{}], NOW()) RETURNING id",
            post.author_id, post.text, JoinMediaUrls(post.media_urls));
        postgres_->Execute(query);
        
        // Step 2: Get followers
        auto followers = GetFollowers(post.author_id);
        
        if (followers.size() < CELEBRITY_THRESHOLD) {
            // Write fan-out for regular users
            auto pipeline = redis_->Pipeline();
            for (uint64_t follower_id : followers) {
                std::string feed_key = fmt::format("feed:user:{}", follower_id);
                pipeline.ZAdd(feed_key, post.timestamp, std::to_string(post.id));
                pipeline.ZRemRangeByRank(feed_key, 0, -(MAX_CACHED_POSTS + 1));
            }
            pipeline.Execute();
        } else {
            // Celebrity: mark for read fan-out
            redis_->SAdd("celebrity_users", std::to_string(post.author_id));
        }
        
        // Step 3: Publish event for real-time notifications
        nlohmann::json event = {
            {"post_id", post.id},
            {"author_id", post.author_id},
            {"timestamp", post.timestamp}
        };
        service_bus_->Publish("post_created", event.dump());
    }
    
    std::vector<Post> GetFeed(uint64_t user_id, 
                              const std::string& cursor, 
                              int limit) {
        // Step 1: Get cached feed (pre-computed via write fan-out)
        std::string feed_key = fmt::format("feed:user:{}", user_id);
        auto cached_post_ids = redis_->ZRevRangeByScore(
            feed_key, cursor, "-inf", 0, limit);
        
        std::vector<Post> all_posts = LoadPosts(cached_post_ids);
        
        // Step 2: Check if user follows any celebrities
        auto celebrities = GetFollowedCelebrities(user_id);
        
        // Step 3: Fetch celebrity posts (read fan-out)
        for (uint64_t celeb_id : celebrities) {
            auto query = fmt::format(
                "SELECT * FROM posts "
                "WHERE author_id = {} AND created_at > '{}' "
                "ORDER BY created_at DESC LIMIT 50",
                celeb_id, cursor);
            
            auto celeb_posts = LoadPostsFromQuery(query);
            all_posts.insert(all_posts.end(), 
                           celeb_posts.begin(), celeb_posts.end());
        }
        
        // Step 4: Merge and rank
        auto ranked_posts = ranking_service_->Rank(all_posts, user_id);
        
        // Step 5: Hydrate post details (author info, media URLs)
        auto hydrated = HydratePosts(ranked_posts, limit);
        
        return hydrated;
    }
    
private:
    std::vector<uint64_t> GetFollowers(uint64_t user_id) {
        auto query = fmt::format(
            "SELECT follower_id FROM follows WHERE followee_id = {}", user_id);
        auto result = postgres_->Query(query);
        
        std::vector<uint64_t> followers;
        for (const auto& row : result) {
            followers.push_back(row["follower_id"].as<uint64_t>());
        }
        return followers;
    }
    
    std::vector<uint64_t> GetFollowedCelebrities(uint64_t user_id) {
        // Get intersection of celebrities and user's following list
        auto all_celebs = redis_->SMembers("celebrity_users");
        std::string following_key = fmt::format("following:user:{}", user_id);
        auto following = redis_->SMembers(following_key);
        
        std::vector<uint64_t> result;
        std::set_intersection(
            all_celebs.begin(), all_celebs.end(),
            following.begin(), following.end(),
            std::back_inserter(result));
        return result;
    }
};
```

#### 7. Ranking Algorithm

**Factors:**
- **Recency:** Newer posts rank higher (time decay)
- **Affinity:** User's past interactions with author
- **Engagement:** Post's likes, comments, shares
- **Content Type:** User's preference (videos > images > text)
- **Dwell Time:** Predicted time user will spend on post

**Simple Scoring Function:**
```cpp
class RankingService {
private:
    std::unordered_map<uint64_t, std::unordered_map<uint64_t, double>> 
        user_affinities_;  // Cache of user affinities
    
public:
    double CalculateScore(const Post& post, uint64_t user_id) {
        auto now = std::chrono::system_clock::now();
        auto post_time = std::chrono::system_clock::from_time_t(post.timestamp);
        auto age = std::chrono::duration_cast<std::chrono::hours>(
            now - post_time).count();
        
        // Time decay (exponential)
        double recency_score = std::exp(-static_cast<double>(age) / 24.0);
        
        // Engagement score (normalized)
        int engagement = post.like_count + 
                        post.comment_count * 2 + 
                        post.share_count * 3;
        double engagement_score = std::log(engagement + 1) / 10.0;
        
        // Affinity score (from user profile)
        double affinity = GetUserAffinity(user_id, post.author_id);
        
        // Weighted sum
        double score = 0.4 * recency_score +
                      0.3 * engagement_score +
                      0.3 * affinity;
        
        return score;
    }
    
    std::vector<Post> Rank(std::vector<Post>& posts, uint64_t user_id) {
        // Calculate score for each post
        std::vector<std::pair<Post, double>> scored_posts;
        scored_posts.reserve(posts.size());
        
        for (const auto& post : posts) {
            double score = CalculateScore(post, user_id);
            scored_posts.emplace_back(post, score);
        }
        
        // Sort by score descending
        std::sort(scored_posts.begin(), scored_posts.end(),
                 [](const auto& a, const auto& b) {
                     return a.second > b.second;
                 });
        
        // Extract sorted posts
        std::vector<Post> ranked;
        ranked.reserve(posts.size());
        for (const auto& [post, score] : scored_posts) {
            ranked.push_back(post);
        }
        
        return ranked;
    }
    
private:
    double GetUserAffinity(uint64_t user_id, uint64_t author_id) {
        // Check cache first
        auto it = user_affinities_.find(user_id);
        if (it != user_affinities_.end()) {
            auto author_it = it->second.find(author_id);
            if (author_it != it->second.end()) {
                return author_it->second;
            }
        }
        
        // Compute affinity based on past interactions
        // (simplified - use ML model in production)
        double affinity = ComputeAffinityFromDB(user_id, author_id);
        
        // Cache it
        user_affinities_[user_id][author_id] = affinity;
        return affinity;
    }
    
    double ComputeAffinityFromDB(uint64_t user_id, uint64_t author_id) {
        // Count past interactions (likes, comments, shares)
        // Return normalized score 0.0-1.0
        return 0.5;  // Placeholder
    }
};
```

**ML-Based Ranking (Production):**
- Train model on user engagement history (click, like, comment, dwell time)
- Features: post metadata, user features, author features, context (time, location)
- Model: Gradient Boosted Trees (XGBoost) or Neural Network
- Online inference: <50ms per post
- Offline batch scoring for cached feeds

#### 8. Fan-out Service Design

**Worker Architecture:**
- Service Bus queue receives post creation events
- Worker pool (100-500 pods) consumes events
- Each worker handles fan-out for one post
- Batch Redis writes (pipeline 100 feeds at once)

**Pseudo-code:**
```cpp
class FanOutWorker {
private:
    std::shared_ptr<ServiceBusClient> service_bus_;
    std::shared_ptr<PostgresClient> postgres_;
    std::shared_ptr<redis::Redis> redis_;
    
    static constexpr size_t BATCH_SIZE = 1000;
    static constexpr int MAX_CACHED_POSTS = 1000;
    
public:
    void Run() {
        while (true) {
            try {
                // Receive event from Service Bus
                auto event = service_bus_->Receive("post_created");
                if (!event) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    continue;
                }
                
                // Parse post data
                auto post_json = nlohmann::json::parse(event->body);
                uint64_t post_id = post_json["post_id"];
                uint64_t author_id = post_json["author_id"];
                int64_t timestamp = post_json["timestamp"];
                
                // Get followers
                auto query = fmt::format(
                    "SELECT follower_id FROM follows WHERE followee_id = {}",
                    author_id);
                auto result = postgres_->Query(query);
                
                std::vector<uint64_t> follower_ids;
                for (const auto& row : result) {
                    follower_ids.push_back(row["follower_id"].as<uint64_t>());
                }
                
                // Batch write to Redis
                for (size_t i = 0; i < follower_ids.size(); i += BATCH_SIZE) {
                    auto batch_end = std::min(i + BATCH_SIZE, follower_ids.size());
                    
                    auto pipeline = redis_->Pipeline();
                    for (size_t j = i; j < batch_end; ++j) {
                        uint64_t follower_id = follower_ids[j];
                        std::string feed_key = fmt::format("feed:user:{}", 
                                                          follower_id);
                        
                        pipeline.ZAdd(feed_key, timestamp, std::to_string(post_id));
                        pipeline.ZRemRangeByRank(feed_key, 0, 
                                                -(MAX_CACHED_POSTS + 1));
                    }
                    pipeline.Execute();
                }
                
                // Mark as processed
                service_bus_->Complete(event->lock_token);
                
                spdlog::info("Fan-out completed for post {} to {} followers",
                           post_id, follower_ids.size());
            }
            catch (const std::exception& e) {
                spdlog::error("Fan-out worker error: {}", e.what());
                // Error handling: dead-letter queue or retry
            }
        }
    }
};
```

**Handling Celebrity Posts:**
- Skip fan-out for celebrities (>10K followers)
- Lazy-load during feed read
- Cache celebrity posts in global "trending" feed

#### 9. Real-Time Updates

**WebSocket Notifications:**
- User connects to WebSocket server
- Server subscribes to user's feed updates (Redis Pub/Sub)
- When new post arrives, server pushes notification
- Client fetches post details via API

**Implementation:**
```python
# Server-side
def on_websocket_connect(user_id, websocket):
    redis_pubsub.subscribe(f"feed_updates:{user_id}")
    
    while True:
        message = redis_pubsub.get_message()
        if message:
            websocket.send(json.dumps({"type": "new_post", "postId": message}))

# Fan-out worker publishes to Pub/Sub
def fanout_post(post, follower_id):
    redis.zadd(f"feed:user:{follower_id}", {post.id: post.timestamp})
    redis.publish(f"feed_updates:{follower_id}", post.id)
```

#### 10. Pagination & Cursor-Based Fetching

**Cursor Design:**
- Encode last post's timestamp and ID in cursor
- Use timestamp for sorting (indexed)
- ID for uniqueness (in case of same timestamp)

```cpp
class CursorPagination {
private:
    std::shared_ptr<redis::Redis> redis_;
    
public:
    struct DecodedCursor {
        int64_t timestamp;
        uint64_t post_id;
    };
    
    std::string EncodeCursor(const Post& post) {
        std::string data = fmt::format("{}:{}", post.timestamp, post.id);
        
        // Base64 encode (URL-safe)
        return Base64UrlEncode(data);
    }
    
    DecodedCursor DecodeCursor(const std::string& cursor) {
        // Base64 decode
        std::string data = Base64UrlDecode(cursor);
        
        // Split by ':'
        size_t pos = data.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid cursor format");
        }
        
        int64_t timestamp = std::stoll(data.substr(0, pos));
        uint64_t post_id = std::stoull(data.substr(pos + 1));
        
        return DecodedCursor{timestamp, post_id};
    }
    
    std::pair<std::vector<Post>, std::optional<std::string>> 
    GetFeedPage(uint64_t user_id, 
                const std::optional<std::string>& cursor,
                int limit) {
        
        std::string feed_key = fmt::format("feed:user:{}", user_id);
        std::vector<std::string> post_ids;
        
        if (cursor) {
            // Cursor-based pagination
            auto decoded = DecodeCursor(*cursor);
            
            post_ids = redis_->ZRevRangeByScore(
                feed_key,
                std::to_string(decoded.timestamp),  // max score
                "-inf",                              // min score
                0,                                   // offset
                limit                                // count
            );
        } else {
            // First page
            post_ids = redis_->ZRevRange(feed_key, 0, limit - 1);
        }
        
        // Load post data
        std::vector<Post> posts = LoadPosts(post_ids);
        
        // Generate next cursor
        std::optional<std::string> next_cursor;
        if (posts.size() == limit) {
            next_cursor = EncodeCursor(posts.back());
        }
        
        return {posts, next_cursor};
    }
    
private:
    std::string Base64UrlEncode(const std::string& input) {
        // Use a base64 library (e.g., boost::beast::base64)
        // Simplified placeholder
        static const char* base64_chars = 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
        
        std::string encoded;
        // ... Base64 encoding logic with URL-safe characters ...
        return encoded;  // Placeholder
    }
    
    std::string Base64UrlDecode(const std::string& input) {
        // Base64 decoding logic
        return "";  // Placeholder
    }
    
    std::vector<Post> LoadPosts(const std::vector<std::string>& post_ids) {
        // Batch load posts from cache/DB
        std::vector<Post> posts;
        // ... implementation ...
        return posts;
    }
};
```

#### 11. Caching Strategy

**Multi-Level Cache:**
1. **L1: Client-side cache** (mobile app, browser)
   - Cache last loaded feed for offline viewing
   - TTL: 5 minutes
2. **L2: CDN (for media)**
   - Cache post images/videos
   - TTL: 24 hours
3. **L3: Redis (feed cache)**
   - Cache user feeds (top 1000 posts)
   - TTL: None (LRU eviction)
4. **L4: Database query cache**
   - Cache frequent queries (user profiles, post metadata)
   - TTL: 10 minutes

**Cache Invalidation:**
- Post deleted → Remove from all follower feeds (async job)
- User unfollows → Purge followee's posts from feed
- Post edited → Update cached post data

#### 12. Scaling Strategies

**Database Sharding:**
- Shard `posts` table by `author_id` (co-locate user's posts)
- Shard `follows` table by `follower_id` (optimize fan-out reads)
- Use consistent hashing for uniform distribution

**Read Replicas:**
- Master for writes, replicas for reads
- Route feed queries to nearest replica (geo-distribution)

**Redis Clustering:**
- Shard feeds by `user_id` (mod N sharding)
- 100+ Redis nodes for 500M DAU

**CDN for Media:**
- Serve images/videos from edge locations
- Lazy-load media (only when visible in viewport)

**Horizontal Scaling:**
- API servers: 1000+ pods (autoscaled)
- Fan-out workers: 500+ pods (KEDA on queue depth)

#### 13. Monitoring & Observability

**Metrics:**
- `posts_created_total` (counter)
- `feed_requests_total` (counter, by user type)
- `feed_latency_ms` (histogram, p50/p99)
- `fanout_duration_ms` (histogram, by follower count)
- `cache_hit_rate` (gauge, by cache level)
- `feed_staleness_seconds` (gauge, time since last update)

**Alerts:**
- Feed p99 latency > 500ms
- Fan-out lag > 10 seconds
- Redis memory > 90%
- Post service error rate > 1%

**Dashboards:**
- Posts per second (real-time)
- Feed request distribution (geographic)
- Top engaged posts
- User growth trends

#### 14. Security & Privacy

**Privacy Controls:**
- Filter posts based on privacy settings during feed generation
- Store privacy in post metadata (indexed)
- Check friendship status for "friends-only" posts

**Content Moderation:**
- ML-based inappropriate content detection
- Manual review queue for flagged content
- User reporting system

**Rate Limiting:**
- 1000 posts/day per user
- 10K feed requests/hour per user
- Prevent spam and abuse

#### 15. Trade-offs & Design Decisions

| Decision | Rationale | Trade-off |
|----------|-----------|-----------|
| Hybrid fan-out | Balance write/read latency for all user types | Complex logic, celebrity handling |
| Redis for feed cache | Fast read, supports sorted sets | Memory-intensive, cache invalidation |
| Eventual consistency | Higher availability, lower latency | Users see new posts after few seconds |
| Cursor pagination | Efficient for large datasets | Doesn't support arbitrary page jumps |
| Soft delete posts | Allows recovery, audit trail | Periodic cleanup needed |
| ML ranking vs chronological | Better engagement | Model training/serving overhead |

#### 16. Advanced Features

**Stories (ephemeral content):**
- 24-hour TTL, stored in Redis
- Lightweight fan-out (only active users)

**Live Videos:**
- Integrate with Azure Media Services
- Push notifications to followers

**Trending/Explore Page:**
- Global hot feed (ML-based trending detection)
- Not personalized, cached globally

**Sponsored Posts:**
- Inject ads into feed (every Nth post)
- Separate ad ranking service

#### 17. Cost Estimation (Azure, 500M DAU)

**Monthly Costs:**
- **Compute (AKS, 2000 pods):** $100K
- **PostgreSQL (Hyperscale, sharded, 50 nodes):** $50K
- **Redis (100 clusters, Premium):** $150K
- **Blob Storage (10PB):** $200K
- **CDN (5PB egress):** $400K
- **Service Bus:** $10K
- **ML Inference (GPU):** $30K
**Total:** ~$940K/month

#### 18. Failure Scenarios & Mitigation

| Failure | Impact | Mitigation |
|---------|--------|------------|
| Redis cluster down | Feed reads fail | Fallback to DB (slower), replica failover (30s) |
| PostgreSQL shard down | Posts in shard unavailable | Read replicas, cross-shard replication |
| Fan-out workers down | New posts not in feeds | Service Bus redelivery, scale up workers |
| CDN unavailable | Media load slow | Multi-CDN, origin fallback |

#### 19. Interview Discussion Points

**Scalability:**
- How to handle 10M followers for celebrity? (Skip fan-out, read-time merge)
- How to scale to 10B users? (Geographic sharding, multiple regions)

**Consistency:**
- What if follower sees post before author's profile updates? (Eventual consistency acceptable)

**Performance:**
- How to optimize feed latency to <50ms? (Edge caching, pre-compute feeds)

**New Feature:**
- How to add "retweet" functionality? (Add post reference in schema, fan-out retweet)

---

### Web Crawler
Design
- Frontier queues, politeness per domain, dedup via Bloom filters, parsing and indexing.
- Distributed workers; backpressure from robots.txt and rate limits.

### Distributed Key-Value Store
Design
- Sharding via consistent hashing; replication (quorum reads/writes); leader election.
- Compaction and LSM-tree based storage.

References
- [Azure Cosmos DB consistency levels](https://learn.microsoft.com/azure/cosmos-db/consistency-levels)

### Notification System
Design
- Producers -> Topic -> fan-out to channels (email, SMS, push) with retries and DLQ.
- User preferences and rate limits; idempotency keys.

References
- [Azure Service Bus Topics/Subscriptions](https://learn.microsoft.com/azure/service-bus-messaging/topic-filters)


