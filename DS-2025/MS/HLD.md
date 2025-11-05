## Microsoft HLD Solutions (Architectures, Trade-offs, Links)

Emphasize requirements, API, storage, scaling, consistency, failure modes, and observability. Microsoft-focused references from Azure Architecture Center included.

### Concurrent Job Orchestrator
Requirements
- High concurrency execution with priorities, per-job-type license limits, autoscaling workers.
- Reliable scheduling, retries, idempotency, observability, and resilience.

High-level Architecture
- API Service: enqueue jobs, query status; authN/Z.
- Priority Queues per job type: backed by durable broker (Service Bus/Kafka) with DLQ.
- License Manager: tracks active counts per job type; enforces max concurrency per license.
- Scheduler: pulls from priority queues, checks license capacity, dispatches to workers.
- Worker Fleet: stateless pods (AKS) pulling tasks; idempotent execution; heartbeats.
- State Store: job metadata (PostgreSQL/SQL), fast counters (Redis), artifacts (Blob Storage).
- Autoscaling: HPA/KEDA based on queue depth and CPU; scale to zero per job type when idle.
- Observability: tracing, metrics (queue depth, success/fail rates), structured logs.

Key Flows
- Submit: API -> enqueue (topic per type, partition by jobId) -> Scheduler.
- Dispatch: Scheduler checks License Manager (Redis atomic counters) -> grant -> assign.
- Complete: Worker updates status; counters decremented; DLQ on permanent failure.

Data Model (simplified)
- Job(id, type, priority, payloadRef, status, attempts, createdAt, updatedAt)
- LicenseLimit(type, maxConcurrent)

Trade-offs
- Exactly-once vs at-least-once: prefer at-least-once with idempotent workers.
- Global ordering vs throughput: shard by type and priority.

Microsoft References
- [Azure Service Bus – queues, topics, DLQ](https://learn.microsoft.com/azure/service-bus-messaging/service-bus-messaging-overview)
- [KEDA for event-driven autoscaling](https://learn.microsoft.com/azure/aks/keda-about)
- [Azure Monitor – metrics and alerts](https://learn.microsoft.com/azure/azure-monitor/overview)

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
Requirements
- Global, distributed rate limiting; per-user/key quotas; low latency; burst handling.

Design
- Local fast-path limiter in each region (Token Bucket in-memory) + centralized counters in Redis cluster per region.
- Cross-region consistency: eventual; periodic reconciliation; sticky routing by user to region.
- Use Redis Lua scripts for atomic increments and TTL-based windows.

References
- [Azure Cache for Redis](https://learn.microsoft.com/azure/azure-cache-for-redis/cache-overview)
- [Azure Front Door – anycast, routing](https://learn.microsoft.com/azure/frontdoor/front-door-overview)

### CDN
Architecture
- Edge POPs cache static objects; origin shield; cache invalidation; signed URLs.
- Multi-CDN or Front Door with rules engine; WAF; TLS termination.

References
- [Azure CDN](https://learn.microsoft.com/azure/cdn/cdn-overview)
- [Azure Front Door](https://learn.microsoft.com/azure/frontdoor/)

### URL Shortener
Design
- API: POST /shorten, GET /{code} (302 redirect)
- Storage: Hot path in Redis; durable store in Cosmos DB/SQL; code generation with collision checks.
- Analytics: event logs to Event Hub -> aggregation.

References
- [Azure Cosmos DB](https://learn.microsoft.com/azure/cosmos-db/introduction)

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
Design
- Write fan-out vs read fan-out; hybrid with per-user timelines in Redis.
- Ranking via offline features + online re-rank; pagination and backfill jobs.

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


