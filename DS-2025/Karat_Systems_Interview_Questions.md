# Karat Systems Interview Questions & Answers

## Table of Contents
- [Q1: Photo Storage Sharding](#q1-photo-storage-sharding)
- [Q2: Music Streaming Consistent Hashing](#q2-music-streaming-consistent-hashing)
- [Q3: Crossword App Hints Implementation](#q3-crossword-app-hints-implementation)
- [Q4: Large XML Processing](#q4-large-xml-processing)
- [Q5: Sports News Service Budget Planning](#q5-sports-news-service-budget-planning)
- [Q6: Social App International Release](#q6-social-app-international-release)
- [Q7: Go Game Analysis Architecture](#q7-go-game-analysis-architecture)
- [Q8: Vending Machine Infrastructure](#q8-vending-machine-infrastructure)
- [Q9: Missing Data Analysis in Distributed Systems](#q9-missing-data-analysis-in-distributed-systems)
- [Q10: Photo Storage Capacity Planning](#q10-photo-storage-capacity-planning)
- [Q11: Social Media Friend Count Feature](#q11-social-media-friend-count-feature)
- [Q12: Subtitle Generation Service Reliability](#q12-subtitle-generation-service-reliability)

---

## Q1: Photo Storage Sharding
**Tags:** `sharding` `data-distribution` `photo-storage` `scalability`

**Question:** 
We are running a simple photo storage and sharing service. People upload their photos to our servers and then give links to other users who can then view them.

We're trying to figure out how to split the photos and associated data evenly onto multiple machines, especially as we get new users. We've decided to shard the photos evenly alphabetically by username. For example, if we had 26 servers, all the usernames starting with 'a' would be on server 1, usernames starting with 'b' would be on server 2, and so on. We have created a scheme like this that will work for any number of servers.

Are there any problems with this design?

**Answer:**
**Main Issue:** Alphabetical sharding creates uneven load distribution and fundamental scaling problems.

**Critical Problems:**

**Load Distribution Issues:**
- **Uneven User Distribution:** Names starting with common letters (A, B, C, J, M, S) significantly outnumber rare letters (Q, X, Z)
- **Hot Spots:** Servers handling popular letters become overloaded while others remain underutilized
- **Geographic Bias:** Different cultures have varying name distribution patterns, creating regional imbalances
- **Temporal Variations:** User activity patterns differ by letter groups, causing time-based load spikes

**Scalability Challenges:**
- **Resharding Nightmare:** Adding new servers requires complete data migration and redistribution
- **No Graceful Growth:** Cannot easily accommodate organic user growth without major infrastructure changes
- **Maintenance Complexity:** Rebalancing requires coordinating across multiple servers simultaneously
- **Downtime Risk:** Data migration periods create service availability issues

**Performance & Reliability:**
- **Query Hotspots:** Popular username prefixes create database query bottlenecks
- **Storage Imbalance:** Some servers run out of space while others have excess capacity
- **Network Congestion:** High-traffic servers experience bandwidth saturation
- **Backup Complexity:** Uneven data distribution complicates backup and recovery strategies

**Better Solutions:**

**Hash-Based Sharding:**
- **Consistent Hashing:** Use hash(user_id) % server_count for uniform distribution
- **Virtual Nodes:** Implement multiple virtual nodes per physical server for better load balancing
- **Deterministic Routing:** Ensure same user always routes to same server for consistency

**Advanced Approaches:**
- **Range-Based Sharding:** Partition by user_id ranges with dynamic rebalancing
- **Directory-Based:** Use lookup service to map users to servers with real-time optimization
- **Hybrid Strategy:** Combine multiple sharding techniques based on access patterns

**Implementation Best Practices:**
- **Monitor Load Metrics:** Track CPU, memory, storage, and network usage per server
- **Auto-scaling:** Implement automatic server provisioning based on load thresholds
- **Data Replication:** Maintain multiple copies for high availability and disaster recovery
- **Gradual Migration:** Use blue-green deployment for seamless data redistribution

**Key Success Factor:** Choose sharding strategy that distributes both data and load evenly while supporting seamless horizontal scaling.

---

## Q2: Music Streaming Consistent Hashing
**Tags:** `consistent-hashing` `load-balancing` `music-streaming` `distribution`

**Question:** 
We are developing an indie music streaming service, where bands can upload songs and users can stream them.

Our central load balancing server distributes the songs onto a series of physical servers using consistent hashing, so every server has the same number of songs.

Do you have any concerns about this system?

**Answer:**
**Main Issue:** Equal song distribution ≠ equal load due to popularity differences and potential data hotspots.

**Critical Concerns:**

**Load Distribution Problems:**
- **Popular Song Hotspots:** Consistent hashing doesn't account for song popularity, creating uneven server loads
- **Data Hotspots:** Small number of servers may host disproportionate amount of traffic
- **Limited Scalability:** Popular songs can overwhelm specific servers, requiring manual rebalancing

**System Reliability Issues:**
- **Fault Tolerance Gaps:** Consistent hashing alone insufficient for large-scale failures or network partitions
- **Single Points of Failure:** Popular content concentrated on few servers increases failure impact
- **Management Overhead:** Complex configuration, monitoring, and troubleshooting requirements

**Performance Bottlenecks:**
- **Uneven Resource Utilization:** Some servers heavily loaded while others underutilized
- **Increased Latency:** Users experience delays when accessing content on overloaded servers
- **Limited Traffic Handling:** System cannot efficiently handle viral content spikes

**Comprehensive Solutions:**

**Load Management:**
- **Dynamic Rebalancing:** Implement real-time monitoring and automatic song redistribution
- **Popularity-Based Distribution:** Use weighted consistent hashing considering song access patterns
- **CDN Integration:** Cache popular content at edge locations to reduce origin server load

**Reliability & Scalability:**
- **Data Replication:** Replicate popular songs across multiple servers for redundancy
- **Auto-scaling:** Dynamically add servers during traffic spikes
- **Circuit Breakers:** Prevent cascade failures during server overload

**Performance Optimization:**
- **Caching Layers:** Multi-tier caching (memory, SSD, CDN) for frequently accessed content
- **Load Monitoring:** Real-time metrics tracking and alerting for proactive intervention
- **Geographic Distribution:** Regional servers to reduce latency for global users

**Key Success Factor:** Implement hybrid approach combining consistent hashing with popularity-aware distribution and comprehensive caching strategy.

---

## Q3: Crossword App Hints Implementation
**Tags:** `mobile-app` `content-delivery` `caching` `offline-support` `detailed-analysis`

**Question:** 
We've developed a crossword puzzle mobile app. The app can give hints which include a synonym for the answer, a picture, or a short video clip.

We are debating two options for how to implement these hints:
- Access hints from the server.
- Preloaded hints into the app.

What are some advantages and disadvantages of each option?

**Answer:**

**Access Hints from the Server:**

*Advantages:*
- **Dynamic Content:** Hints can be updated without app releases, allowing flexibility for new content
- **Lower Initial App Size:** Smaller download size as hints are fetched on-demand
- **Customization:** Personalized hints based on user preferences and progress
- **Analytics:** Track user interactions for insights on hint effectiveness and engagement

*Disadvantages:*
- **Network Dependency:** Requires stable internet; poor connectivity affects hint retrieval
- **Server Load:** High user volume can strain servers, causing performance issues during peak usage
- **Privacy Concerns:** May require sending user data/progress to server for hint customization

**Preloaded Hints into the App:**

*Advantages:*
- **Offline Access:** Uninterrupted gameplay without internet dependency
- **Faster Retrieval:** No network latency or server response time delays
- **Reduced Server Load:** Offloads hint delivery from server infrastructure
- **Improved Privacy:** Local storage reduces privacy concerns about data transmission

*Disadvantages:*
- **Limited Updates:** Cannot modify hints without app releases, reducing content flexibility
- **Increased App Size:** Larger download may deter users with storage or bandwidth constraints
- **Less Customization:** Reduced ability to provide personalized, dynamic user experiences

**Conclusion:** Choice depends on priorities: dynamic content vs offline reliability, privacy vs personalization, and infrastructure vs app size constraints.

---

## Q4: Large XML Processing
**Tags:** `big-data` `memory-management` `xml-processing` `streaming`

**Question:** 
We are building a business analytics application that analyzes large XML files containing sales data in chronological order.

Due to the sensitive nature of the data, we want to keep all processing on our local machine. However, the files are sometimes larger than the available RAM on our computer.

What are some techniques which we could use to process this data?

**Answer:**
**Main Solution:** Stream processing with memory-efficient techniques for large dataset analysis.

**Core Streaming Techniques:**

**Parser Selection:**
- **SAX Parser:** Event-driven XML parsing that processes elements sequentially without loading entire document
- **StAX Parser:** Pull-based parsing allowing precise control over processing flow and memory usage
- **Avoid DOM Parser:** Never use DOM as it loads complete XML structure into memory

**Memory Management Strategies:**
- **Chunked Processing:** Read and process XML in configurable buffer sizes (e.g., 1MB chunks)
- **Sliding Window:** For chronological data, maintain rolling window of recent records for analysis
- **Memory Mapping:** Use OS-level memory mapping to let kernel optimize file access patterns
- **Garbage Collection Tuning:** Configure JVM/runtime GC for large file processing workloads

**Advanced Processing Patterns:**

**Pipeline Architecture:**
- **Producer-Consumer:** Separate reading, parsing, analysis, and output into distinct pipeline stages
- **Buffered Queues:** Use bounded queues between pipeline stages to prevent memory overflow
- **Backpressure Handling:** Implement flow control to slow down producers when consumers lag

**Incremental Analysis:**
- **State Machines:** Process XML elements using finite state machines to track context efficiently
- **Accumulator Pattern:** Maintain running calculations without storing historical data
- **Checkpoint Recovery:** Save processing state periodically to resume from failures

**Storage Optimization:**

**Temporary Files:**
- **Intermediate Results:** Store partial analysis results in compressed temporary files
- **Sorted Merging:** Process data in sorted order to enable efficient merge operations
- **Index Creation:** Build lightweight indexes for quick data lookup during analysis

**Compression Techniques:**
- **On-the-fly Compression:** Compress intermediate results using gzip/lz4 to reduce storage needs
- **Binary Formats:** Convert XML to efficient binary formats (Avro, Parquet) for faster processing
- **Schema Evolution:** Design flexible schemas that can handle varying XML structures

**Performance Optimization:**

**I/O Efficiency:**
- **Sequential Access:** Process data sequentially to optimize disk read patterns
- **Buffer Management:** Use large I/O buffers to minimize system call overhead
- **Async Processing:** Overlap I/O operations with computation using async programming

**Parallel Processing:**
- **Multi-threading:** Process independent data chunks in parallel threads
- **Work Stealing:** Implement dynamic load balancing across worker threads
- **NUMA Awareness:** Optimize memory access patterns for multi-socket servers

**Implementation Example:**
```python
# Streaming XML processor with memory constraints
def process_large_xml(file_path, chunk_size=1024*1024):
    parser = ET.iterparse(file_path, events=('start', 'end'))
    current_record = {}
    
    for event, elem in parser:
        if event == 'start' and elem.tag == 'record':
            current_record = process_record(elem)
        elif event == 'end':
            elem.clear()  # Free memory immediately
            
    return analysis_results
```

**Key Success Factor:** Design processing pipeline that minimizes memory footprint while maintaining data integrity and analysis accuracy through streaming and incremental techniques.

---

## Q5: Sports News Service Budget Planning
**Tags:** `capacity-planning` `machine-learning` `budget-estimation` `resource-planning`

**Question:** 
We run a sports news classification service, where users can provide a link to a sports article and our service downloads the article, uses machine learning to detect and report any bias towards a specific team.

We want to plan our budget for the next six months. What information do we need to estimate the resources needed?

**Answer:**
**Main Need:** Comprehensive data analysis combining historical usage patterns with predictive modeling for accurate resource estimation.

**Critical Data Requirements:**

**Usage Analytics & Traffic Patterns:**
- **Current Metrics:** Daily/monthly article submissions, processing time per article, concurrent user peaks
- **Seasonal Variations:** Sports calendar impact (playoffs, championships, off-season fluctuations)
- **Peak Load Analysis:** Traffic spikes during major sporting events, breaking news, controversial games
- **Geographic Distribution:** Regional sports preferences and time zone usage patterns
- **User Behavior:** Article submission frequency, retry patterns, premium vs free tier usage

**Technical Resource Mapping:**

**ML Infrastructure Costs:**
- **Model Inference:** GPU/CPU requirements per article, inference time, model complexity
- **Training Overhead:** Periodic model retraining costs, A/B testing infrastructure
- **Feature Engineering:** Text preprocessing, sentiment analysis, entity extraction compute needs
- **Model Storage:** Version control, model artifacts, experiment tracking storage

**Data Processing Pipeline:**
- **Web Scraping:** Bandwidth costs, rate limiting compliance, proxy services, anti-bot measures
- **Content Storage:** Article caching, processed data retention, backup storage requirements
- **Real-time Processing:** Stream processing infrastructure, message queue throughput
- **Batch Processing:** Offline analysis jobs, report generation, data warehouse costs

**Infrastructure Scaling:**

**Compute Resources:**
- **Auto-scaling Metrics:** CPU/memory thresholds, queue length triggers, response time SLAs
- **Reserved vs On-demand:** Cost optimization for predictable baseline vs spike traffic
- **Multi-region Deployment:** Global latency requirements, data sovereignty compliance
- **Container Orchestration:** Kubernetes cluster costs, load balancer expenses

**Monitoring & Observability:**
- **Performance Monitoring:** APM tools, log aggregation, metrics storage, alerting systems
- **Security Infrastructure:** WAF services, DDoS protection, compliance auditing tools
- **Disaster Recovery:** Backup systems, cross-region replication, business continuity planning

**Cost Modeling Framework:**

**Financial Projections:**
- **Growth Scenarios:** Conservative, expected, aggressive growth with corresponding resource needs
- **Pricing Models:** Tiered service offerings impact on infrastructure requirements
- **Operational Overhead:** DevOps team costs, 24/7 support, incident response capabilities
- **Vendor Dependencies:** Third-party API costs (news sources, ML services), license fees

**Budget Optimization:**
- **Cost Per Article:** Calculate unit economics including all infrastructure and operational costs
- **Resource Utilization:** Optimize for 70-80% average utilization with burst capacity
- **Commitment Discounts:** Reserved instance savings, enterprise contracts, volume pricing
- **Cost Allocation:** Accurate cost tracking per feature, customer segment, geographic region

**Risk Assessment:**
- **Capacity Planning Buffer:** 25-30% overhead for unexpected growth or technical issues
- **Vendor Lock-in Costs:** Migration expenses, multi-cloud strategy, exit planning
- **Regulatory Compliance:** GDPR, regional data laws, content moderation requirements
- **Technology Refresh:** Hardware/software lifecycle, security updates, performance improvements

**Implementation Strategy:**
```
Budget Formula:
Total Cost = (Base Infrastructure + Variable Processing + Storage + Monitoring + 
             Security + Compliance + Operational Overhead) × Growth Factor × Risk Buffer

Monthly Breakdown:
- Compute: 40-50% (ML inference, web scraping, API processing)
- Storage: 15-20% (articles, models, logs, backups)
- Network: 10-15% (CDN, bandwidth, inter-region transfers)
- Operations: 15-20% (monitoring, security, support)
- Contingency: 10-15% (unexpected growth, incidents)
```

**Key Success Factor:** Build dynamic cost model that adapts to actual usage patterns with automated alerting when costs deviate from projections, enabling proactive resource optimization.

---

## Q6: Social App International Release
**Tags:** `internationalization` `global-deployment` `backend-architecture` `scalability`

**Question:** 
We run a social networking mobile app for university students. The app allows students to express interests in study groups or hobbies and find students with similar interests. It has been really successful in the United States so we've decided to release it worldwide.

The translations and front-end have been updated. What updates would you make to the backend to ensure a smooth international release?

**Answer:**
**Main Focus:** Regional infrastructure deployment and comprehensive localization requirements.

**Critical Infrastructure Updates:**
- **Global Scalability:** Deploy regional data centers (US, EU, APAC) with CDN for reduced latency
- **Load Balancing:** Implement geographic routing and auto-scaling for increased worldwide traffic
- **Performance Monitoring:** Track KPIs (response times, error rates) across all regions

**Localization & Data Management:**
- **Backend Localization:** Support multiple languages, date/time formats, and local currencies
- **Data Model Updates:** Ensure database schema supports multilingual content (profiles, groups, interests)
- **Content Recommendations:** Customize algorithms based on language preferences and geographic location

**Compliance & Security:**
- **Data Privacy:** Implement GDPR (Europe), CCPA (California), and other regional privacy regulations
- **Data Residency:** Partition user data by region to comply with local data storage laws
- **User Consent:** Provide transparent privacy controls and consent mechanisms

**Payment & Business Logic:**
- **International Payments:** Integrate payment gateways supporting global currencies and methods
- **Regional Configuration:** Handle different business rules and regulations per country
- **Multi-timezone Support:** Ensure proper timestamp handling across time zones

**Key Success Factors:** Comprehensive testing in target regions, local compliance review, and gradual rollout strategy.

---

## Q7: Go Game Analysis Architecture
**Tags:** `mobile-app` `computational-analysis` `client-server` `performance` `game-analysis`

**Question:** 
We are working on a mobile app for the board game Go. We'd like to add a feature where the computer will analyze a complete game. The analysis looks at each position from the game and provides suggested moves to help improve our users' play. We've found a library we can use to do this analysis. It takes an average of a minute on a modern desktop computer to analyze entire game. An average game consists of about 200 moves.

We are considering two approaches: 1) running this analysis on the phone itself, and 2) sending the game to a server farm for analysis that will be returned to the user.

What are some advantages or disadvantages of each approach?

**Answer:**
**Main Trade-off:** Local processing power vs network dependency for computationally intensive analysis.

**Running Analysis on the Phone:**

*Advantages:*
- **Offline Capability:** Users can perform analysis without internet connection, enhancing accessibility
- **Privacy Protection:** Analysis done locally eliminates privacy concerns about sending game data externally
- **Zero Latency:** Immediate results without network delays or server response times

*Disadvantages:*
- **Resource Intensive:** Significant computational load may impact device performance and battery life
- **Limited Processing Power:** Mobile devices slower than desktop/server hardware, potentially affecting analysis quality
- **Inconsistent Performance:** Analysis speed varies greatly across different device capabilities

**Sending Game to Server Farm:**

*Advantages:*
- **Superior Performance:** High-performance hardware and parallel processing enable faster, more accurate analysis
- **Device Efficiency:** Offloads computational burden, preserving battery life and device performance
- **Continuous Improvement:** Server-side algorithms can be updated without requiring app updates
- **Scalability:** Can handle simultaneous requests from multiple users efficiently

*Disadvantages:*
- **Internet Dependency:** Requires stable connection, limiting accessibility in poor connectivity areas
- **Privacy Concerns:** Sending game data to external servers raises data security and privacy issues
- **Network Latency:** Analysis results subject to network delays, potentially longer wait times than local processing

**Recommendation:** Hybrid approach - offer both options with server-side as default (faster, better analysis) and local processing as fallback for offline scenarios or privacy-conscious users.

---

## Q8: Vending Machine Infrastructure
**Tags:** `iot` `scalability` `distributed-systems` `load-balancing` `reliability`

**Question:** 
You're working on infrastructure for internet-connected vending machines. The plan is to install around 188,888 of these vending machines in the coming year, in major cities around the world. These machines will connect to the internet through cellular network.

Each machine will connect to a central server at midnight to report remaining stock and any maintenance issues like coin jams or stuck items. These machine status updates will be stored in a database, and a batch job will run at 1 AM to schedule the restocking and maintenance of machines. 

Are there any problems with the above design? How to solve these problems?

**Answer:**
**Main Issues:** Thundering herd problem and single point of failure at massive scale.

**Critical Problems:**
- **Scalability Crisis:** 188,888 machines connecting simultaneously at midnight will overwhelm server infrastructure
- **Concurrency Bottleneck:** Resource contention and potential system crashes during peak load
- **Network Reliability:** Cellular connectivity issues could cause data loss and missed updates

**Solutions:**

**Infrastructure Scaling:**
- **Distributed Architecture:** Deploy multiple servers/cloud instances across regions to distribute load
- **Load Balancing:** Use load balancers to distribute requests evenly across server fleet
- **Auto-scaling:** Implement dynamic scaling to handle peak midnight traffic

**Connection Management:**
- **Staggered Connectivity:** Spread connections over 30-60 minute window instead of exact midnight
- **Randomized Timing:** Each machine connects at random time within designated window
- **Geographic Distribution:** Route machines to nearest regional data centers

**Reliability & Resilience:**
- **Retry Mechanisms:** Implement exponential backoff for failed connections
- **Offline Storage:** Local buffering on machines for temporary connectivity issues
- **Circuit Breakers:** Prevent cascade failures when servers are overloaded
- **Monitoring & Alerting:** Real-time detection of performance issues and network outages

**Data Management:**
- **Asynchronous Processing:** Use message queues to decouple data ingestion from processing
- **Database Sharding:** Partition data by geographic region or machine ID ranges
- **Caching Layer:** Implement caching for frequently accessed data

**Key Success Factor:** Design for 10x current scale (1.8M machines) to handle future growth gracefully.

---

## Q9: Missing Data Analysis in Distributed Systems
**Tags:** `debugging` `log-analysis` `data-integrity` `distributed-systems` `troubleshooting`

**Question:** 
There was a bug on an application, and you ended up having a lot of failed requests. You have a database that stores all IDs that are there, and you also have large log files from about 500 different production servers that log the IDs of the successful requests. 

How would you come up with a solution to find the IDs that were missing?

**Answer:**
**Main Strategy:** Systematic data reconciliation between database records and distributed log files.

**Step-by-Step Solution:**

**1. Scope Definition:**
- **Identify Timeframe:** Determine exact period when bug occurred using error logs/monitoring
- **Define Success Criteria:** Establish what constitutes a "successful" vs "failed" request
- **Baseline Database State:** Capture current database IDs for comparison

**2. Log Data Extraction:**
- **Automated Parsing:** Use scripts (Python/bash) to extract successful request IDs from 500 servers
- **Parallel Processing:** Process log files concurrently to handle large data volumes efficiently
- **Data Validation:** Ensure log format consistency and handle parsing errors gracefully

**3. Data Reconciliation:**
- **Set Operations:** Compare successful IDs from logs against database IDs using set difference
- **Batch Processing:** Handle large datasets using streaming or chunked comparison
- **Deduplication:** Remove duplicate IDs from aggregated log data across servers

**4. Missing ID Identification:**
- **Gap Analysis:** Generate list of IDs present in logs but missing from database
- **Categorization:** Group missing IDs by server, timestamp, or request type for pattern analysis
- **Impact Assessment:** Quantify data loss and prioritize recovery efforts

**5. Root Cause Investigation:**
- **Error Log Analysis:** Correlate missing IDs with error patterns and system metrics
- **Timeline Reconstruction:** Map failures to specific system events or deployments
- **Performance Analysis:** Check if failures correlate with high load or resource constraints

**6. Prevention & Recovery:**
- **Implement Retry Logic:** Add exponential backoff for transient failures
- **Data Recovery:** Replay/reprocess identified missing requests if possible
- **Monitoring Enhancement:** Add alerts for request success rate anomalies
- **Circuit Breakers:** Prevent cascade failures during high error rates

**Technical Implementation:** Use tools like ELK stack for log aggregation, database comparison utilities, and automated reconciliation scripts for ongoing monitoring.

---

## Q10: Photo Storage Capacity Planning
**Tags:** `capacity-planning` `cost-estimation` `photo-storage` `infrastructure` `scalability`

**Question:** 
We are running a simple photo storage and sharing service. People upload their photos to our servers and then give links to other users who can then view them. Instead of using a cloud service, we have our own server farms. You've been tasked with creating an estimate of the storage required over the coming year and the cost of that storage.

What information would you need and what factors would you consider as you generate this estimate?

**Answer:**
**Main Focus:** Comprehensive data-driven capacity planning with growth projections and cost modeling.

**Critical Data Requirements:**

**Usage Analytics:**
- **Current Storage Metrics:** Total photos stored, storage utilization trends, user count
- **Growth Patterns:** Historical user growth rate, photos per user per month, seasonal variations
- **Photo Characteristics:** Average file size, format distribution (JPEG, PNG, RAW), resolution trends

**Business Projections:**
- **User Growth:** Expected new user acquisition, retention rates, user engagement patterns
- **Feature Impact:** New features that might increase storage (video, higher resolution, editing history)
- **Retention Policy:** Photo lifecycle management, auto-deletion policies, user behavior patterns

**Technical Factors:**

**Storage Optimization:**
- **Compression:** Potential savings from image optimization and format conversion
- **Deduplication:** Duplicate photo detection and storage efficiency gains
- **Metadata Overhead:** Storage for indexing, thumbnails, search data, and user permissions

**Infrastructure Requirements:**
- **Redundancy Strategy:** Replication factor (3x for safety), backup storage, disaster recovery
- **Performance Needs:** SSD vs HDD mix based on access patterns, caching requirements
- **Geographic Distribution:** Multi-region storage for global user base

**Cost Modeling:**

**Hardware Costs:**
- **Storage Hardware:** Cost per TB including servers, drives, networking equipment
- **Infrastructure:** Data center space, power, cooling, network bandwidth
- **Replacement Cycle:** Hardware depreciation and refresh schedules

**Operational Expenses:**
- **Personnel:** System administration, monitoring, maintenance staff
- **Utilities:** Power consumption, cooling costs, internet connectivity
- **Scalability Buffer:** 20-30% capacity overhead for unexpected growth

**Calculation Framework:**
```
Total Storage = (Users × Photos/User × Avg_Size × Growth_Factor × Replication_Factor) + Metadata_Overhead
Annual Cost = Hardware_Cost + Operational_Cost + Scaling_Buffer
```

**Key Success Factor:** Build 25-30% buffer capacity and implement automated monitoring for proactive scaling decisions.

---

## Q11: Social Media Friend Count Feature
**Tags:** `database-design` `denormalization` `caching` `social-media` `scalability` `performance`

**Question:** 
We are working on a clone of Facebook. We want to add a numeric count to every post showing how many friends the post's author has at the time of viewing the post.

Database Schema:
```
USER
 'user_id' (primary key)
 'name' 
 'created_date' 

USER_RELATIONSHIP 
 'friendship_id' (primary key, unique to each relationship)
 'user_id' (indexed)
 'user2_id' (indexed)
 'start_date'
```

Focusing on the database, how would you implement the friend-count feature? Note we will soon be more popular than Facebook, so the solution needs to scale.

**Answer:**
**Main Strategy:** Denormalization with caching and incremental updates for optimal read performance at scale.

**Core Implementation Approach:**

**1. Denormalization Strategy:**
- **Add Friend Count Column:** Extend USER table with `friend_count` field for O(1) read access
- **Real-time Updates:** Increment/decrement count when friendships are added/removed
- **Consistency Guarantees:** Use database transactions to ensure count accuracy during updates

**2. Caching Architecture:**
- **Multi-tier Caching:** Redis/Memcached for friend counts with TTL-based expiration
- **Cache-aside Pattern:** Check cache first, fallback to database, update cache on miss
- **Cache Warming:** Preload popular users' friend counts during low-traffic periods

**3. Incremental Update System:**
- **Event-driven Updates:** Update only affected users when friendship changes occur
- **Atomic Operations:** Use database triggers or application-level transactions
- **Avoid Full Recalculation:** Never recalculate entire friend counts from scratch

**Scalability Solutions:**

**4. Batch Processing:**
- **Scheduled Reconciliation:** Daily batch jobs to verify count accuracy and fix inconsistencies
- **Bulk Updates:** Process friendship changes in batches during peak traffic periods
- **Asynchronous Processing:** Use message queues for non-critical count updates

**5. Database Optimization:**
- **Proper Indexing:** Composite indexes on (user_id, user2_id) for efficient friendship queries
- **Read Replicas:** Separate read/write traffic to reduce load on primary database
- **Connection Pooling:** Optimize database connection management for high concurrency

**6. Horizontal Scaling:**
- **Database Sharding:** Partition users across multiple database servers by user_id ranges
- **Distributed Caching:** Redis Cluster for cache scalability across multiple nodes
- **Load Balancing:** Distribute read requests across multiple database replicas

**Advanced Considerations:**

**7. Performance Monitoring:**
- **Query Performance:** Monitor friend count query latency and optimize slow queries
- **Cache Hit Rates:** Track cache effectiveness and adjust TTL values accordingly
- **Database Metrics:** Monitor connection pools, query throughput, and replication lag

**8. Consistency Models:**
- **Eventually Consistent:** Accept slight delays in count updates for better performance
- **Reconciliation Jobs:** Periodic verification of denormalized counts against source data
- **Graceful Degradation:** Fallback to approximate counts during high load periods

**Technical Implementation:**
```sql
-- Add denormalized column
ALTER TABLE USER ADD COLUMN friend_count INT DEFAULT 0;

-- Efficient friend count query
SELECT friend_count FROM USER WHERE user_id = ?;

-- Update on friendship creation
UPDATE USER SET friend_count = friend_count + 1 WHERE user_id IN (?, ?);
```

**Key Success Factor:** Implement comprehensive monitoring and automated reconciliation to maintain data consistency while achieving sub-millisecond read performance at Facebook scale.

---

## Q12: Subtitle Generation Service Reliability
**Tags:** `concurrency` `resource-management` `system-reliability` `threading` `workarounds`

**Question:** 
We are working on a service that generates subtitles for users' videos. This process starts a new thread for every video and is processor-intensive. Currently, this service runs as a single process on a machine.

We've run into a bug where if the service is processing more than 10 videos at the same time, the service crashes the server, losing all requests currently being processed and affecting other processes on the machine.

It may take a long time to find and fix this bug. What workarounds could we implement to continue running the service while we do so?

**Answer:**
**Main Strategy:** Implement immediate protective measures to prevent crashes while maintaining service availability.

**Immediate Workarounds:**

**1. Request Limiting & Throttling:**
- **Concurrent Processing Limit:** Hard cap at 8-9 concurrent videos (below crash threshold)
- **Queue Management:** Implement request queue for videos exceeding limit
- **Rate Limiting:** Control incoming request rate to prevent queue overflow
- **Circuit Breaker:** Stop accepting new requests when approaching resource limits

**2. Resource Isolation:**
- **Process Isolation:** Run subtitle service in separate container/VM to protect other processes
- **Resource Limits:** Use cgroups/containers to limit CPU and memory usage
- **Dedicated Hardware:** Move service to dedicated machines to eliminate impact on other services

**3. Graceful Degradation:**
- **Health Monitoring:** Continuously monitor system resources (CPU, memory, thread count)
- **Automatic Restart:** Implement service restart on crash with exponential backoff
- **State Persistence:** Save processing state to recover interrupted jobs after restart

**Operational Improvements:**

**4. Enhanced Monitoring:**
- **Real-time Metrics:** Track concurrent processing count, resource usage, queue length
- **Alerting:** Set up alerts at 7-8 concurrent videos to prevent reaching crash point
- **Logging:** Detailed logging before crashes to help identify root cause

**5. Processing Architecture:**
- **Worker Pool Pattern:** Replace unlimited threading with fixed-size worker pool
- **Load Balancing:** Distribute video processing across multiple service instances
- **Asynchronous Processing:** Decouple request acceptance from processing using message queues

**6. Failure Recovery:**
- **Checkpointing:** Save intermediate progress to resume interrupted video processing
- **Job Retry Logic:** Automatically retry failed jobs with exponential backoff
- **Dead Letter Queue:** Handle permanently failed jobs separately

**Advanced Solutions:**

**7. Horizontal Scaling:**
- **Multiple Instances:** Deploy service across multiple machines with load balancer
- **Auto-scaling:** Automatically add instances based on queue length or processing load
- **Sticky Sessions:** Route video processing to specific instances for consistency

**8. Resource Management:**
- **Memory Monitoring:** Track memory usage per video to detect memory leaks
- **Thread Pool Management:** Replace per-video threads with managed thread pool
- **Garbage Collection Tuning:** Optimize GC settings for processor-intensive workloads

**Implementation Priority:**
1. **Immediate:** Concurrent processing limit (< 10 videos)
2. **Short-term:** Process isolation and monitoring
3. **Medium-term:** Worker pool pattern and horizontal scaling
4. **Long-term:** Complete architecture redesign with proper resource management

**Key Success Factor:** Implement layered protection - request limiting + resource isolation + monitoring - to prevent crashes while maintaining service availability during bug investigation.

---

## Search Tags Index
- **Sharding & Distribution:** Q1, Q2, Q8, Q11
- **Mobile Apps:** Q3, Q7
- **Data Processing:** Q4, Q9
- **Capacity Planning:** Q5, Q10
- **Global Scale:** Q6, Q8
- **Performance:** Q2, Q3, Q6, Q7, Q8, Q11
- **Cost Optimization:** Q3, Q5, Q10
- **Compliance:** Q4, Q6
- **Detailed Analysis:** Q3
- **Client-Server Architecture:** Q7
- **Computational Analysis:** Q7
- **IoT Systems:** Q8
- **Load Balancing:** Q8
- **Reliability:** Q8, Q9, Q12
- **Debugging & Troubleshooting:** Q9
- **Data Integrity:** Q9
- **Log Analysis:** Q9
- **Photo Storage:** Q1, Q10
- **Infrastructure Planning:** Q10
- **Cost Estimation:** Q10
- **Database Design:** Q11
- **Denormalization:** Q11
- **Caching:** Q11
- **Social Media:** Q11
- **Concurrency:** Q12
- **Resource Management:** Q12
- **System Reliability:** Q12
- **Threading:** Q12

---

*Last Updated: August 24, 2025*
*Total Questions: 12*
