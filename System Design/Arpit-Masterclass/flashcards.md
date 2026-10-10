# Flashcards: System Design Masterclass (Arpit Bhayani)

Cards test the ideas, not trivia. `flashcards.csv` (Anki import) is generated from these tables.

## 01-01 · Foundational topics

| # | Question | Answer |
|---|---|---|
| 1 | What is the "Framework of the Opposites"? | For every decision, consider the exact opposite (push vs pull, store vs don't store, build vs offload), evaluate all paths, then choose. |
| 2 | Why does a presence system use client heartbeats instead of the server polling clients? | Without a persistent connection the server cannot reach the client, so the client must push a periodic pulse. |
| 3 | What should the presence table store: a boolean or a timestamp? | The last heartbeat time (epoch). Online = now − last_hb is below a threshold (e.g. 30 s). |
| 4 | Storage for 1B users at 8 bytes per row? | About 8 GB (4 B user_id + 4 B last_hb). |
| 5 | How does "absence == offline" shrink the presence store? | Keep rows only for active users and expire them by TTL. 100k active × 8 B ≈ 800 KB instead of 8 GB. |
| 6 | Two ways to delete expired presence rows? Which is better? | A CRON job you run, or offloading to a datastore with native TTL (Redis/DynamoDB). Offloading is simpler. |
| 7 | Redis vs DynamoDB for presence: what decides? | Context: Redis is fast in-memory but costly and self-run; DynamoDB is durable, managed, multi-region, cheaper, with AWS lock-in. |
| 8 | Heartbeat every 10 s with 1M active users: DB write rate? | 6M writes per minute (100k per second). |
| 9 | Why does connection pooling matter for tiny DB updates? | TCP setup/teardown per request dominates; reusing pre-established connections removes it. |
| 10 | What data structure implements a connection pool? | A bounded blocking queue (often a circular array) of connection objects; borrowers wait when it's empty. |
| 11 | Reasons for soft delete? | Recoverability, archival, audit, and no B+ tree rebalancing that a real DELETE can cause. |
| 12 | What is a cache stampede and the fix? | Many concurrent misses on one key all hit the DB. Request coalescing (single-flight): one request fetches, the rest wait for its result. |

## 01-02 · Scaling, Delegation, Communication

| # | Question | Answer |
|---|---|---|
| 13 | Vertical vs horizontal scaling: what does horizontal add? | Near-linear capacity increase and fault tolerance (vertical just makes one box bigger). |
| 14 | Why scale bottom-up? | Stateful layers (DB, cache) must handle the concurrent load from all API servers; scale them first. |
| 15 | Three ways to scale a relational DB? | Vertical scaling, read replicas, sharding (plus a proxy to route). |
| 16 | What does a DB proxy like ProxySQL do? | Knows the topology; routes queries via rules (e.g. SELECT → replica hostgroup), pools connections, can cache. |
| 17 | The performance mantra for delegation? | What doesn't need to be done in realtime shouldn't be done in realtime. |
| 18 | Which tasks should be delegated to async workers? | Long-running tasks, heavy computation, batch writes, anything eventually consistent. |
| 19 | Message queue vs message stream? | Queue (SQS, RabbitMQ): each message goes to one consumer. Stream (Kafka, Kinesis): each consumer group reads every message. |
| 20 | Why use Kafka instead of one worker that counts and indexes? | Separation of concerns: separate consumer groups (counter, search) each process the same event. |
| 21 | Kafka's ordering guarantee? | Only within a partition; none across partitions. |
| 22 | Two Kafka partition limitations? | You can't reduce partitions; consumers in a group beyond the partition count sit idle. |
| 23 | Short polling vs long polling? | Short: server responds immediately, client repeats. Long: server holds the request until data is ready or timeout. |
| 24 | WebSockets vs SSE? | WebSockets: bidirectional persistent channel. SSE: server-to-client one-way stream over HTTP. |
| 25 | Typical load sequence for a realtime app? | Load UI → fetch initial state via REST → subscribe to live updates. |

## 02-01 · Databases: locking, check-in, KV on SQL

| # | Question | Answer |
|---|---|---|
| 26 | Pessimistic locking flow? | Acquire lock → read/update → release (on commit or rollback). |
| 27 | Why do databases need locks? | To protect data consistency and integrity under concurrent updates. |
| 28 | FOR UPDATE vs SKIP LOCKED vs NOWAIT on a locked row? | Wait · skip it and return other rows · fail immediately with an error. |
| 29 | Why use SKIP LOCKED for airline seat selection? | Users need any free seat; concurrent transactions each grab a different unlocked seat without queueing or double booking. |
| 30 | Name systems with "fixed inventory + contention". | Airline check-in, CoWIN slots, IRCTC, BookMyShow, flash sales. |
| 31 | How do you avoid an is_deleted column in the KV store? | Use a sentinel: expired_at = -1 marks a deleted row. |
| 32 | How is PUT implemented in the KV store? | An upsert (MySQL REPLACE INTO / ON DUPLICATE KEY UPDATE; Postgres ON CONFLICT DO UPDATE), not GET-then-INSERT/UPDATE. |
| 33 | How does GET respect TTL? | WHERE key = k AND expired_at > NOW(). Expired rows are filtered at read time. |
| 34 | Why add LIMIT 1000 to the cleanup DELETE? | Avoid huge transactions that hold many locks, bloat logs, lag replicas and stall live traffic. |
| 35 | When are read replicas appropriate? | Read-heavy load where slightly stale reads are fine; send consistent reads to the master. |
| 36 | Master can't handle writes: what next? | Scale vertically first; then shard (range or hash) so each master owns an exclusive slice of keys. |
| 37 | Do FOR UPDATE locks block a plain SELECT in InnoDB/Postgres? | No. Plain reads use MVCC snapshots; only locking reads wait. |

## 02-02 · NoSQL + Slack realtime

| # | Question | Answer |
|---|---|---|
| 38 | What do most NoSQL DBs trade for scalability and availability? | Consistency (most are eventually consistent). |
| 39 | Does "NoSQL scales" imply "SQL doesn't"? | No. Anything you can shard scales, relational DBs included. |
| 40 | Document vs key-value store? | Document: JSON, complex queries, partial updates (MongoDB). KV: key-wise access, heavily partitioned, no complex queries (Redis, DynamoDB). |
| 41 | Why are column stores used for analytics? | They read only the columns a query touches, not whole rows. |
| 42 | Wide-column store in one line? | Columns grouped into column families stored together on disk across rows (Cassandra). |
| 43 | Slack insight 1? | A DM is just a channel with two members. |
| 44 | How are Slack messages sharded and why? | By workspace, so all of a workspace's history is on one shard (no cross-shard scrolling). |
| 45 | What does membership.checkpoint store and why? | Last message id read; the client fetches anything newer, which recovers missed realtime messages. |
| 46 | Persistence-first vs realtime-first chat examples? | Slack persists first; WhatsApp delivers realtime with async persistence; Zoom chat has no persistence. |
| 47 | Why multiplex everything over one WebSocket per user? | WebSockets are expensive persistent TCP connections and browsers limit them. |
| 48 | How do edge servers deliver across servers? | Each subscribes to Redis Pub/Sub channels (one per Slack channel) for its users; publishes fan out to every subscribed edge. |
| 49 | What does a TCP connection's identity consist of? | Source IP, source port, destination IP, destination port, protocol. |

## 03-01 · Load balancer, remote & distributed locks

| # | Question | Answer |
|---|---|---|
| 50 | Why do LB servers keep config in memory? | A config-DB call per request would wreck latency; the in-memory copy is kept in sync. |
| 51 | How does config reach LB servers quickly, and what if that path fails? | Config DB → CDC → Redis Pub/Sub push; if Pub/Sub is down, LBs poll. |
| 52 | What does the LB orchestrator do? | Health-checks backends and LB servers, updates the backend list, scales LB servers using metrics from Prometheus. |
| 53 | How is the orchestrator itself kept alive? | Leader election: a master assigns exclusive work to workers; a new master is elected on failure. |
| 54 | How do you scale the LB tier itself? | Weighted DNS (e.g. CoreDNS) resolving one name to many LB server IPs. |
| 55 | How do two DNS servers provide HA without client changes? | They share a Virtual IP via VRRP; the secondary takes over the VIP (ARP) when the primary fails. |
| 56 | How do threads, processes and machines synchronise? | Mutex/semaphore; disk (lock files); remote lock manager. |
| 57 | Two requirements for a remote lock manager? | Atomic acquire and automatic expiry (TTL). |
| 58 | Redis command to acquire a lock with expiry? | SET key owner NX EX ttl (set-if-not-exists with TTL). |
| 59 | Why release a Redis lock via a Lua script? | Owner check + delete must be atomic so you never delete someone else's re-acquired lock. |
| 60 | How does Redlock acquire a lock? | SETNX on N independent Redis masters; success if a majority (e.g. 3 of 5) is acquired, else release all. |
| 61 | What does Redlock buy you and what does it cost? | No single point of failure and better correctness; lower throughput (consensus is slow). |
| 62 | Why do TTL-based locks need fencing tokens? | A paused holder can outlive its TTL while another client acquires the lock; monotonically increasing tokens let the resource reject stale writers. |

## 03-02 · ID generation

| # | Question | Answer |
|---|---|---|
| 63 | Why can't sharded DBs rely on auto-increment IDs? | Each independent shard's auto-increment collides with the others; the app must supply globally unique IDs. |
| 64 | Why does epoch_ms alone fail as an ID? | Two machines (or two calls) in the same millisecond produce the same value. |
| 65 | How do you persist an ID counter cheaply and recover safely? | Flush every N increments; on restart begin at last_flushed + N (+1), skipping but never reusing IDs. |
| 66 | Why do ID schemes put time in the most significant bits? | Numeric order matches time order (sortable); lower bits only break ties. |
| 67 | What breaks monotonicity across machines? | Clock skew between machines. |
| 68 | Core lesson about distributed ID generation? | You can't distribute it and guarantee strict monotonicity, so real systems relax a constraint. |
| 69 | Amazon-style central ID service optimisation? | Hand out ID batches (ranges) per call; servers re-ask when exhausted. |
| 70 | Why avoid UUIDs as primary keys at scale? | 128-bit random keys bloat indexes and scatter inserts; indexes stop fitting in memory. |
| 71 | How do Flickr ticket servers work and avoid SPOF? | MySQL auto-increment table bumped via upsert; two servers issue odd and even IDs. |
| 72 | INSERT … ON DUPLICATE KEY UPDATE vs REPLACE INTO? | ODKU updates in place; REPLACE deletes then inserts (much slower). Both atomic. |
| 73 | Snowflake bit layout? | 41 bits epoch ms, 10 bits machine id, 12 bits per-machine sequence (plus a 0 sign bit). |
| 74 | Instagram's ID layout and where it's generated? | 41 bits ms since 2011, 13 bits logical shard, 10 bits sequence; a Postgres function at INSERT. |
| 75 | Why is since_id pagination efficient? | It seeks straight into the index (WHERE id > x LIMIT k) instead of skipping OFFSET rows. |

## 04-01 · CDN, photo uploads, Gravatar

| # | Question | Answer |
|---|---|---|
| 76 | How does a CDN serve a request? | Its domain maps to your origin; on a miss it fetches from the origin, caches the response and returns it. |
| 77 | Why shouldn't photo uploads go through the API server? | It doubles bandwidth and wastes API resources just relaying bytes. |
| 78 | How does a client upload to S3 without your servers relaying? | The service creates a pre-signed URL for an exact path; the client PUTs directly to S3. |
| 79 | Why store image_id instead of the full image URL on a post? | The S3 path is computable from user_id + image_id; saves space and lets the service validate ownership. |
| 80 | How are Instagram's private photos protected? | Short-lived signed CDN URLs; the CDN rejects invalid or expired signatures. |
| 81 | Why can a service verify a JWT without the auth service? | It checks the signature with the issuer's public key (asymmetric, e.g. RS256). |
| 82 | When should you reach for public-key cryptography? | When system A must trust system B's statement without calling B. |
| 83 | How do you avoid sending huge photos to every device? | CDN on-the-fly transformation (e.g. ?w=360), with cached variants. |
| 84 | What is the Gravatar URL keyed by? | A hash of the user's email. |
| 85 | Two ways to model "one active photo per user"? | is_active flag flipped in one transaction (with a unique partial index), or active_photo_id denormalised on users. |

## 04-02 · Hashtag service + unread indicator

| # | Question | Answer |
|---|---|---|
| 86 | How does the hashtag page achieve super-fast reads? | One pre-computed document per tag (count + top posts), served by key from a partitioned DB, cache and CDN. |
| 87 | Post ids vs full post details in the hashtag doc? | Ids: small but N+1 enrichment on read. Full details: one fast read, more storage, risk of staleness. |
| 88 | What's the value of splitting read and write paths? | Each can be optimised independently: cache + thin API on reads; Kafka + batching on writes. |
| 89 | How do hashtag workers count efficiently? | Aggregate counts in memory and flush every N events or time window with one increment per tag. |
| 90 | How do you minimise stop-the-world during a flush? | Swap the active map under the lock (O(1)) and write the old map to the DB outside the lock. |
| 91 | Why add a hashtag-extraction adapter? | POST_PUBLISH is keyed by post; re-emitting per-hashtag events keyed by tag lets one consumer own each tag's counts. |
| 92 | What does the newly-unread badge count? | The number of distinct people with unread messages, not the number of messages. |
| 93 | Best index for counting distinct unread senders? | Covering composite (to, ts, from): equality, then range, then the read column. |
| 94 | Day-N design for the unread indicator? | ON_MSG_UNSENT events → workers SADD(dest, src) into a per-user Redis set; the badge is the set size; clear on read. |
| 95 | How is "unread" detected in the pre-computed approach? | The messaging service knows via WebSocket presence that delivery failed and emits ON_MSG_UNSENT. |

## 05-01 · Distributed cache

| # | Question | Answer |
|---|---|---|
| 96 | Core data structure of a cache server? | A hash table mapping key → typed object (type decides allowed operations). |
| 97 | HTTP vs raw TCP (RESP) for a cache? | HTTP: easy tooling but heavy per-request overhead. RESP over TCP: minimal overhead, needs custom clients. |
| 98 | How does a cache know it's full? | Cap on key count, or track total bytes via an allocation wrapper (zmalloc/zfree). |
| 99 | LRU vs LFU: typical workloads? | LRU for recency-driven traffic (news, CDN); LFU for stable popularity (Wikipedia). |
| 100 | Why does Redis approximate LRU? | An exact doubly linked list costs memory and CPU; sampling keys into a small eviction pool is close enough. |
| 101 | Three ways to expire TTL keys? | Priority queue by expiry; lazy deletion on access; random sampling (Redis: 20 keys, repeat if > 25% expired). |
| 102 | How does single-threaded Redis run background work? | Time events in its event loop (serverCron, activeExpireCycle) interleaved with I/O. |
| 103 | How do multi-threaded caches (DiceDB) avoid lock contention? | Shared-nothing: one hash-table shard per core owned by a pinned data thread; I/O threads route by hash. |
| 104 | Problem with hash(key) % N routing? | Changing N remaps most keys (≈ N/(N+1) of them). |
| 105 | How does consistent hashing assign keys? | Nodes and keys hash onto a ring; each key goes to the next node clockwise. |
| 106 | Steps to add a cache node with minimal transfer? | Snapshot the neighbour, load, replicate until lag ≈ 0, brief pause, update ring, resume, delete moved data. |
| 107 | What problem do virtual nodes solve? | Skewed ring arcs: many positions per node spread load evenly. |

## 05-02 · Dictionary without DB, Bitcask, WAL recovery

| # | Question | Answer |
|---|---|---|
| 108 | How do you look up a word in a 1 TB file quickly without a DB? | Load a small word → (offset, length) index into memory and read only that byte range from S3. |
| 109 | Rough size of the dictionary index? | About 171k entries × ~16 B ≈ 2.7 MB (more with 8-byte offsets, still tiny). |
| 110 | How is the weekly changelog applied efficiently? | Both are sorted, so merge them in O(n) like merge sort, then rebuild the index. |
| 111 | How do you switch dictionary versions without garbage reads? | Upload to a new versioned path and flip a meta.json pointer; never overwrite files in place. |
| 112 | How do you store index and data in one portable file? | A fixed-length header holding the index and data offsets (plus metadata), followed by the index, then the data. |
| 113 | Why are log-structured stores fast for writes? | Append-only sequential writes avoid disk seeks. |
| 114 | How does an append-only store delete a key? | Append a tombstone (e.g. PUT(k, -1)); compaction removes it later. |
| 115 | Layout of a Bitcask entry? | CRC, timestamp, key size, value size, key, value. |
| 116 | How does Bitcask achieve O(1) GET? | An in-memory hash index maps key → (file id, value position, size); one seek reads the value. |
| 117 | Bitcask's main limitation? | All keys must fit in memory. |
| 118 | What does merge/compaction do in Bitcask? | Rewrites immutable files keeping only each key's latest live value and updates the index atomically. |
| 119 | How do databases recover a torn write at the end of the log? | Scan entries verifying CRCs and truncate at the first mismatch. |

## 06-01 · LSM trees, tiered storage, event ingestion

| # | Question | Answer |
|---|---|---|
| 120 | Core idea of an LSM tree over Bitcask? | Buffer writes in an in-memory memtable (plus a WAL), flush periodically to immutable sorted files, so keys needn't fit in RAM. |
| 121 | What is an SSTable? | An immutable file of key-sorted entries with an index of key → offset. |
| 122 | Order of lookup for GET in an LSM? | Memtable, then SSTables newest to oldest; first hit wins. |
| 123 | Why flush the memtable to a new file each time? | Faster, one-shot sequential writes; avoids rewriting a large existing file. |
| 124 | How do Bloom filters speed up LSM reads? | Each SSTable's filter says "definitely not here" so the file is skipped; "maybe" means check it. |
| 125 | Bloom filter error types? | False positives possible, false negatives impossible. |
| 126 | Purpose of the WAL in an LSM? | Durability for memtable contents; replayed on restart and truncated after each flush. |
| 127 | B+ tree vs LSM workload fit? | B+ trees for read-heavy; LSM for write-heavy. |
| 128 | Name LSM-based storage engines. | RocksDB, LevelDB, BadgerDB (also Cassandra). |
| 129 | Idea behind multi-tiered order storage? | Move orders to cheaper tiers by age (hot MySQL → S3) while keeping them queryable via indexes. |
| 130 | How is cold data on S3 kept queryable? | Indexed file layout (index + data) served by index servers or Athena/Hive-style engines. |
| 131 | How do you ingest huge event volumes cheaply? | Write to rotating local log files and ship them as batches to Kafka/S3, not one sync write per event. |
| 132 | Why avoid video_id as the Kafka partition key for impressions? | A viral video would create a hot partition; spread events evenly. |

## 06-02 · Live streaming + Designing S3

| # | Question | Answer |
|---|---|---|
| 133 | Master vs playlist m3u8? | Master lists renditions (bandwidth/resolution → playlist) and doesn't change; a playlist lists .ts segments and grows by appends during live. |
| 134 | How does a player follow a live HLS stream? | It periodically re-fetches the playlist and plays newly appended segments. |
| 135 | SSAI vs CSAI? | SSAI stitches ad segments into the manifest server-side (seamless, hard to block); CSAI plays ads in the client on cues (glitchy, blockable). |
| 136 | Components of SSAI? | Origin with SCTE-35 markers, a manifest manipulator, an ad decision server (VAST), and the CDN. |
| 137 | How are private live streams protected at the CDN? | Signed tokens/certificates validated by the CDN per request. |
| 138 | Why use multiple CDNs? | Backup and performance: continuously measure and shift traffic in real time. |
| 139 | S3's four design goals? | Strong consistency, global namespace, multi-tenancy, cost efficiency. |
| 140 | What is a storage stamp? | A cluster of 10–20 racks (~30–50 PB) run at ≤ 70% utilisation, with headroom for rack failures. |
| 141 | What does the location service do? | Maps accounts/namespaces to stamps (via DNS) and manages cross-stamp replication. |
| 142 | Three layers inside a stamp? | Front-end (auth + routing + streaming), Partition (range ownership, throttling), Stream (replicated append-only DFS). |
| 143 | Why range partitioning in S3? | Keeps object locality and tenant isolation, and lets hot ranges be split. |
| 144 | Partition ownership rule? | Each partition is owned by exactly one partition server; a server can own many partitions. |
| 145 | How does S3-style storage get durability? | Sync replicas within the stamp, async replicas across data centres and regions. |

## 07-01 · Recent searches, Cricbuzz, ES in production

| # | Question | Answer |
|---|---|---|
| 146 | Which user behaviours shape the recent-searches design? | 50% tap the search bar within 5 s (read-heavy, must be preloaded); 30% of searches come from recent searches (write-heavy). |
| 147 | How are recent searches stored for fast reads? | A pre-computed list of the last 10 queries per user in Redis, written synchronously. |
| 148 | Where does the full search history go? | Async via Kafka into a partitioned NoSQL DB (search logs), archived to S3 after ~6 months. |
| 149 | How do you avoid a slow first load when a user's Redis entry was evicted? | Pre-warm recent searches into Redis when the app opens. |
| 150 | Why short polling instead of WebSockets for Cricbuzz commentary? | About one update per minute and identical data for everyone; cached polling is cheaper than millions of idle sockets. |
| 151 | How is the latest commentary served cheaply? | Redis holds the latest per match, or a CDN with max-age ≈ 5 s and prefreshing near expiry. |
| 152 | How is commentary stored? | Ball-wise rows (match_id, innings, ball, text), upserted per ball. |
| 153 | Pain points of Day-0 Elasticsearch? | Painful recovery, limits on scale and experimentation, hard debugging, no auto replication or latency routing, costly big tenants, no throttling. |
| 154 | Key pieces of the revamped search platform? | Indexers to primary + backup-region ES, a search gateway, identity (JWT) and relevance re-ranking, multi-region failover. |
| 155 | ES routing strategy by tenant size? | Small tenant → one shard (tenant_id % shards); large tenant → spread over N shards (tenant_id + doc_id % N). |
| 156 | What problem does tenant-aware routing solve? | Hot shards and noisy neighbours from uneven tenant sizes. |

## 07-02 · Task scheduler + flash sale

| # | Question | Answer |
|---|---|---|
| 157 | Requirements of the distributed task scheduler? | One-off or cron tasks executed (as HTTP calls) within a 30 s SLA, minute granularity, multi-tenant, ~2B tasks/day. |
| 158 | Why must every scheduler component be horizontally scalable and fault tolerant? | The strict SLA at extreme scale leaves no room for bottlenecks or single points of failure. |
| 159 | How is the task store partitioned? | By tenant (customer or microservice). |
| 160 | What do task pullers do and how are they coordinated? | Pull due tasks and enqueue them; each owns a tenant range assigned via ZooKeeper, reassigned if it dies. |
| 161 | SQL used to pull due tasks concurrently? | WHERE scheduled_at <= now AND picked_at IS NULL ORDER BY scheduled_at LIMIT n FOR UPDATE SKIP LOCKED, then mark picked. |
| 162 | How are executors organised and scaled? | Separate queues/fleets by priority and task type; an orchestrator autoscales on queue length. |
| 163 | How are recurring (cron) tasks handled? | Expand the cron into the next N absolute run times inserted as jobs (idempotently), topping up on each pick. |
| 164 | Why model flash-sale stock as one row per unit? | So concurrent buyers lock different rows (SKIP LOCKED) instead of all contending on one qty row. |
| 165 | What happens on payment failure in the flash sale? | The unit is released: picked_at and picked_by are reset to NULL. |
| 166 | How are abandoned carts handled? | A CRON job releases units picked more than ~12 min ago and not purchased. |
| 167 | Why can't add-to-cart and payment be one transaction? | They span services and time; there's no distributed transaction, so use steps with compensation. |

## 08-01 · Impression counting + Dropbox sync

| # | Question | Answer |
|---|---|---|
| 168 | Why can't per-minute unique counts be summed? | Users repeat across minutes; you need a set union, not a sum. |
| 169 | Why are exact hash sets impractical for impression counting at scale? | Each ad-minute can take MBs; hourly unions across thousands of customers run into TBs of processing. |
| 170 | What data structure estimates unique counts cheaply? | HyperLogLog (~12 KB per key, mergeable, approximate). |
| 171 | Redis HLL commands? | PFADD (add, O(1)), PFCOUNT (cardinality), PFMERGE (union of N HLLs). |
| 172 | Main limitation of HLL besides approximation? | You can't delete elements. |
| 173 | How do you answer unique viewers for an arbitrary range? | PFMERGE the per-minute HLLs for that range into a temp key, then PFCOUNT. |
| 174 | How does the impressions design keep Redis small? | Recent HLLs stay in Redis; bytes are copied periodically to DynamoDB and reloaded on demand. |
| 175 | Why archive raw view events to S3? | Replayability: if filter rules had a bug, events can be reprocessed. |
| 176 | How does Dropbox represent a file? | As a blocklist: hashes of 4 MB blocks, with blocks stored content-addressed. |
| 177 | Dropbox upload protocol? | Commit blocklist → metaserver replies with missing hashes → client uploads them to the block server → re-commit. |
| 178 | How do clients learn about changes? | A per-namespace incrementing version id; clients fetch everything after their last version, like a Kafka offset. |
| 179 | How does multi-versioning fall out of the design? | Old metadata rows keep old blocklists; the blocks still exist, so any version can be rebuilt. |

## 08-02 · Geo-proximity, ride hailing, follow graph

| # | Question | Answer |
|---|---|---|
| 180 | Why is geo-proximity hard with plain (x, y)? | It needs a 2D range query (intersecting two 1D ranges), O(n) naively; 1D ranges are easy. |
| 181 | How does GeoHash encode a location? | Repeatedly halve the longitude and latitude ranges into bits, interleave them, and encode in base 32. |
| 182 | What does a shared GeoHash prefix mean? | The points fall in the same cell, so they're likely near each other (longer prefix = smaller cell). |
| 183 | GeoHash boundary edge case and fix? | Nearby points across a cell edge get different prefixes; also search the 8 neighbouring cells. |
| 184 | Why Redis for ride-hailing driver locations? | In-memory speed, built-in geo queries, multi-master multi-replica sharding. |
| 185 | Why did Gojek need EVAL_RO? | Redis rejects EVAL on replicas (scripts could write); a read-only variant lets filtering scripts run on replicas. |
| 186 | How does the matcher keep latency low? | Split the area into smaller GEOSEARCH queries run in parallel; return partial results if the SLA is breached. |
| 187 | How were hot shards avoided for driver locations? | Manually mix peak and low-traffic regions on each master (Redis sharding has no business context). |
| 188 | Why not a graph DB for follow/following? | No advanced graph algorithms needed; costly, hard to operate, and pagination is tricky. |
| 189 | Problem with sharding an edges(src, dest) table by src? | "Followers of B" filters on dest, so it must fan out across all shards. |
| 190 | How do you serve both follower and following queries from one shard? | Store two rows per follow, (A, B, FOLLOWS) and (B, A, FOLLOWED_BY), and shard by src. |
| 191 | FlockDB primary key and unique index? | PK (source_id, state, position); unique (source_id, destination_id, state). |
| 192 | How does FlockDB paginate efficiently? | Cursor on position (WHERE position > last ORDER BY position LIMIT k), not OFFSET. |
