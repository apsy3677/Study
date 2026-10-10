# System Design Masterclass (Arpit Bhayani): study notes

My own study notes from the 16 session PDFs of the System Design Masterclass (Feb–Apr 2025 cohort).
The source PDFs are view-only on Google Drive, so these are **notes in my own words** that follow each session's
structure, numbers and diagrams. They're not a copy of the slides.

- **Offline book:** `System-Design-Masterclass-Notes.pdf` (all notes + flashcards)
- **Flashcards:** [flashcards.md](flashcards.md) (192 cards) · Anki import: `flashcards.csv` (tab-separated: front, back, tag)

Each notes file has: a session map, per-topic 🧠 anchor → ⚙️ mechanics → 🏗 so-what → 🔁 recall questions,
a "What these notes add" section (corrections and extra context), and a one-page memory card.

| # | Session | Topics |
|---|---|---|
| 01-01 | [Foundations](01-01/slide-notes.md) | Design approach · online/offline indicator (heartbeats, TTL, Redis vs DynamoDB, connection pools) · blogging: soft delete, caching, stampede |
| 01-02 | [Scaling, delegation, communication](01-02/slide-notes.md) | Vertical/horizontal · DB scaling + ProxySQL · queues vs streams · Kafka essentials · short/long poll, WebSockets, SSE |
| 02-01 | [Databases: locking](02-01/slide-notes.md) | Pessimistic locks · FOR UPDATE / SKIP LOCKED / NOWAIT · airline check-in · KV store on SQL |
| 02-02 | [NoSQL + Slack realtime](02-02/slide-notes.md) | Document/KV/column/wide-column/graph · Slack schema · WebSocket edges · Redis Pub/Sub fan-out |
| 03-01 | [Load balancer + locks](03-01/slide-notes.md) | LB config sync · orchestrator · DNS + VIP/VRRP · remote locks (SETNX + TTL) · Redlock |
| 03-02 | [ID generation](03-02/slide-notes.md) | Counters · monotonicity & clock skew · Amazon batches · Flickr ticket servers · Snowflake · Instagram IDs |
| 04-01 | [CDN, uploads, Gravatar](04-01/slide-notes.md) | How a CDN works · signed-URL uploads · private photos + JWT · CDN resizing · Gravatar |
| 04-02 | [Hashtags + unread indicator](04-02/slide-notes.md) | Pre-computed hashtag docs · read/write paths · batching · Kafka re-partition adapter · unread-senders badge |
| 05-01 | [Distributed cache](05-01/slide-notes.md) | Redis/DiceDB internals · eviction · TTL sampling · shared-nothing · consistent hashing · virtual nodes |
| 05-02 | [Dictionary, Bitcask, WAL](05-02/slide-notes.md) | Indexed files on S3 · O(n) merge · versioned switch-over · log-structured KV (Bitcask) · log recovery |
| 06-01 | [LSM, tiered storage, ingestion](06-01/slide-notes.md) | Memtable + SSTables + Bloom filters · Amazon order tiering · event ingestion |
| 06-02 | [Live streaming + S3](06-02/slide-notes.md) | HLS/m3u8 · SSAI vs CSAI · CDN token auth · storage stamps · front-end/partition/stream layers |
| 07-01 | [Information retrieval](07-01/slide-notes.md) | Recent searches · Cricbuzz commentary · Elasticsearch in production · tenant routing keys |
| 07-02 | [Task scheduler + flash sale](07-02/slide-notes.md) | Pullers + SKIP LOCKED · cron expansion · autoscaled executors · per-unit inventory |
| 08-01 | [Impressions + Dropbox](08-01/slide-notes.md) | HyperLogLog (PFADD/PFMERGE/PFCOUNT) · tiered HLL storage · block hashing · version-id sync |
| 08-02 | [Geo-proximity + follow graph](08-02/slide-notes.md) | GeoHash · Gojek driver matching (EVAL_RO) · follow graph on SQL (FlockDB) |
