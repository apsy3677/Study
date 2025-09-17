# Atlassian Staff Engineer System Design Solutions

This document contains comprehensive system design solutions following industry best practices and the delivery framework, targeting staff-level engineering depth.

## Question 1: Cross-Product Tagging System for Atlassian Suite

### Requirements (~5 minutes)

#### Functional Requirements
1. **Tag Management**: Users should be able to create, update, and delete tags across Jira, Confluence, and Bitbucket
2. **Content Tagging**: Users should be able to attach multiple tags to content items (issues, pages, repositories)
3. **Tag Discovery**: Users should be able to search and discover existing tags with autocomplete
4. **Popular Tags Dashboard**: Administrators should be able to view trending tags across products with configurable time windows
5. **Cross-Product Tag Navigation**: Users should be able to find related content across products using shared tags

#### Non-Functional Requirements
1. **Scalability**: System must handle 100M+ content items across 50K+ organizations with 10M+ active users
2. **Availability**: 99.9% uptime with graceful degradation (core product functionality should not be blocked by tagging failures)
3. **Consistency**: Eventual consistency is acceptable for tag popularity metrics, but strong consistency required for tag-content associations
4. **Performance**: Tag autocomplete < 100ms, content retrieval by tags < 500ms
5. **Security**: Tag visibility must respect existing product permissions and organizational boundaries

#### Capacity Estimation
Let me do some targeted calculations that will influence our design:
- **Tag Operations**: ~1M tag operations/day across all products (heavy read:write ratio ~100:1)
- **Popular Tags Calculation**: Need to process ~100M daily interactions across 1M unique tags
- **Storage**: ~10GB for tag metadata, ~100GB for tag-content associations, ~1TB for popularity time-series data

### Core Entities (~2 minutes)
- **Tag**: Represents a label with metadata (name, description, creation context)
- **TaggedContent**: Association between tags and content across products
- **TagPopularityMetrics**: Time-series data for tag usage analytics
- **Organization**: Boundary for tag visibility and permissions

### API Design (~5 minutes)

**Protocol Choice**: REST for CRUD operations, with GraphQL for complex tag discovery queries to handle diverse client needs efficiently.

```
# Tag Management
POST /v1/tags
GET /v1/tags/search?q={query}&org_id={org}&limit=20
PUT /v1/tags/{tag_id}
DELETE /v1/tags/{tag_id}

# Content Tagging
POST /v1/content/{content_id}/tags
Body: {"tag_ids": ["tag1", "tag2"], "product": "jira"}

DELETE /v1/content/{content_id}/tags/{tag_id}

GET /v1/tags/{tag_id}/content?product={product}&org_id={org}

# Analytics & Discovery
GET /v1/analytics/tags/popular?timeframe=7d&org_id={org}&product={product}

# GraphQL for complex queries
query TagsWithContent($orgId: ID!, $filters: TagFilters!) {
  tags(orgId: $orgId, filters: $filters) {
    id
    name
    contentCount(product: $filters.product)
    relatedTags(limit: 5)
  }
}
```

### High Level Design (~10-15 minutes)

```
                    ┌─────────────────┐
                    │   API Gateway   │
                    │  (Rate Limiting)│
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │  Tag Service    │
                    │ (Business Logic)│
                    └─────────┬───────┘
                              │
           ┌──────────────────┼──────────────────┐
           │                  │                  │
     ┌─────▼─────┐     ┌─────▼─────┐     ┌─────▼─────┐
     │Tag Storage│     │Association│     │ Analytics │
     │(PostgreSQL│     │  Storage  │     │ Pipeline  │
     │   Primary)│     │(Cassandra)│     │ (Kafka +  │
     └───────────┘     └───────────┘     │Spark/Flink│
           │                  │          └───────────┘
     ┌─────▼─────┐     ┌─────▼─────┐            │
     │Tag Cache  │     │Search Index│     ┌─────▼─────┐
     │ (Redis)   │     │(Elasticsearch)│  │Time Series│
     └───────────┘     └───────────┘     │(InfluxDB) │
                                         └───────────┘
```

**Data Flow for Tag Creation**:
1. User creates tag → API Gateway → Tag Service validates & stores in PostgreSQL
2. Tag Service publishes event → Kafka → Search indexer updates Elasticsearch
3. Cache invalidation for affected queries

**Data Flow for Popular Tags**:
1. User interactions → Event stream → Analytics pipeline
2. Spark job aggregates metrics → InfluxDB for time-series storage
3. Popular tags API reads from InfluxDB with Redis caching

### Deep Dives (~10 minutes)

#### Deep Dive 1: Storage Strategy Trade-offs

**PostgreSQL for Tag Metadata**:
- **Pros**: Strong consistency, ACID transactions, complex queries for tag relationships
- **Cons**: Vertical scaling limits, potential bottleneck for high write loads
- **Alternative**: Could use MongoDB for document flexibility, but loses transaction guarantees

**Cassandra for Tag-Content Associations**:
- **Pros**: Excellent write performance, natural partitioning by content_id, scales horizontally
- **Cons**: Eventually consistent, limited query flexibility
- **Design**: Partition by content_id, secondary index on tag_id with careful query patterns
- **Alternative**: Could use PostgreSQL with read replicas, but would hit scaling limits faster

#### Deep Dive 2: Tag Popularity at Scale

**Real-time vs Batch Processing Trade-off**:
- **Chosen**: Lambda architecture with both real-time (last hour) and batch (historical) processing
- **Real-time**: Kafka Streams for immediate updates, stored in Redis with TTL
- **Batch**: Spark jobs for accurate historical metrics, stored in InfluxDB
- **Why**: Balances accuracy with responsiveness; users expect recent changes to be visible quickly

**Popular Tags Algorithm**:
```
popularity_score = Σ(interaction_weight × time_decay_factor × user_authority_score)

Where:
- interaction_weight: view=1, create=3, share=5
- time_decay_factor: exponential decay (0.99^hours_since)
- user_authority_score: based on user's role and activity level
```

#### Deep Dive 3: Cross-Product Permission Model

**Challenge**: Different permission models across Jira (project-based), Confluence (space-based), Bitbucket (repository-based)

**Solution**: Tag visibility matrix approach
- Tags inherit strictest permissions from associated content
- Implement permission caching with invalidation on role changes
- Use async permission propagation to avoid blocking tag operations

**Trade-off**: Slight delay in permission updates vs system responsiveness

#### Deep Dive 4: Search and Discovery Optimization

**Elasticsearch Index Strategy**:
- Separate indices for tags and content to optimize query patterns
- Use multi-field mapping: exact match, ngram for autocomplete, stemmed for fuzzy search
- Implement result boosting based on user's organization and recent activity

**Autocomplete Performance**:
- Edge ngram tokenizer for prefix matching
- Redis cache for popular autocomplete queries
- Implement query-time boosting for user's frequently used tags

#### Deep Dive 5: Operational Considerations

**Monitoring & Alerting**:
- Tag operation latency percentiles (P50, P95, P99)
- Popular tags calculation lag time
- Cross-product consistency checks
- Cache hit rates and database connection pool utilization

**Data Consistency**:
- Implement saga pattern for cross-service tag operations
- Use distributed locks for critical tag operations (e.g., tag merging)
- Background reconciliation jobs to detect and fix inconsistencies

**Disaster Recovery**:
- PostgreSQL: Master-slave replication with automated failover
- Cassandra: Multi-datacenter replication with quorum reads/writes
- Analytics: Rebuild capability from event logs stored in S3

## Question 2: Distributed Web Scraper Service

### Requirements (~5 minutes)

#### Functional Requirements
1. **Job Management**: Users should be able to submit scraping jobs with multiple seed URLs and configurable depth
2. **Content Extraction**: System should extract images, links, and metadata from web pages
3. **Recursive Crawling**: System should follow links up to a specified depth with cycle detection
4. **Job Monitoring**: Users should be able to track job progress, view statistics, and retrieve results
5. **Result Storage**: System should store extracted content with searchable metadata and deduplication

#### Non-Functional Requirements
1. **Scalability**: Handle 10K+ concurrent scraping jobs with 1M+ URLs per day
2. **Reliability**: 99.5% success rate for accessible URLs with robust error handling
3. **Performance**: Process 100 URLs/second per worker node with configurable parallelism
4. **Politeness**: Respect robots.txt, implement rate limiting, and domain-specific delays
5. **Storage**: Efficiently store and serve TB-scale extracted content and metadata

#### Capacity Estimation
**Key calculations affecting design**:
- **Peak Load**: 10K jobs × 100 URLs average = 1M URLs in queue during peak
- **Worker Sizing**: Need ~100 worker nodes (1K URLs/hour/worker) for 100K URLs/hour target
- **Storage**: ~100MB average per job result → 10TB monthly storage growth

### Core Entities (~2 minutes)
- **ScrapingJob**: Contains job configuration, status, and metadata
- **UrlTask**: Individual URL to be processed with current state
- **ExtractedContent**: Processed content with images, links, and metadata
- **CrawlResult**: Final aggregated results per job

### API Design (~5 minutes)

**Protocol Choice**: REST for job management with WebSocket for real-time progress updates.

```
# Job Management
POST /v1/scraping/jobs
Body: {
  "urls": ["http://example.com"],
  "max_depth": 3,
  "max_pages": 1000,
  "respect_robots": true,
  "delay_ms": 1000,
  "content_types": ["images", "links", "text"]
}
Response: {"job_id": "uuid", "status": "queued"}

GET /v1/scraping/jobs/{job_id}
Response: {
  "job_id": "uuid",
  "status": "running",
  "progress": {
    "total_urls": 500,
    "processed": 150,
    "failed": 10,
    "estimated_completion": "2024-01-01T12:00:00Z"
  }
}

GET /v1/scraping/jobs/{job_id}/results?format=json|csv
DELETE /v1/scraping/jobs/{job_id}

# Real-time updates
WebSocket: /v1/scraping/jobs/{job_id}/stream
```

### High Level Design (~10-15 minutes)

```
                    ┌─────────────────┐
                    │   API Gateway   │
                    │ (Rate Limiting, │
                    │  Auth, Routing) │
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │  Job Service    │
                    │ (Job Management)│
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │  Message Queue  │
                    │ (Redis/RabbitMQ)│
                    └─────────┬───────┘
                              │
           ┌──────────────────┼──────────────────┐
           │                  │                  │
     ┌─────▼─────┐     ┌─────▼─────┐     ┌─────▼─────┐
     │ Worker    │     │ Worker    │     │ Worker    │
     │ Node 1    │     │ Node 2    │     │ Node N    │
     └─────┬─────┘     └─────┬─────┘     └─────┬─────┘
           │                 │                 │
           └─────────────────┼─────────────────┘
                             │
                    ┌────────▼────────┐
                    │  Storage Layer  │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │ PostgreSQL  │ │ ← Job metadata
                    │ │ (Metadata)  │ │
                    │ └─────────────┘ │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │   Object    │ │ ← Extracted content
                    │ │   Storage   │ │   (S3/MinIO)
                    │ │   (S3)      │ │
                    │ └─────────────┘ │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │   Search    │ │ ← Content indexing
                    │ │(Elasticsearch│ │
                    │ └─────────────┘ │
                    └─────────────────┘
```

**Data Flow**:
1. User submits job → Job Service validates and creates job record
2. Job Service breaks down URLs into tasks → Pushes to message queue
3. Workers pull tasks → Process URLs → Store results → Update progress
4. Job Service aggregates results → Marks job complete

### Deep Dives (~10 minutes)

#### Deep Dive 1: Queue Architecture Trade-offs

**Message Queue Selection**:
- **Redis with Streams**: Chosen for simplicity and persistence
  - **Pros**: Atomic operations, consumer groups, simple deployment
  - **Cons**: Single point of failure, memory limitations
- **Alternative - RabbitMQ**: Better for complex routing, clustering
  - **Pros**: Advanced routing, built-in HA, message persistence
  - **Cons**: More complex setup, operational overhead
- **Alternative - Apache Kafka**: For high-throughput scenarios
  - **Pros**: High throughput, partitioning, replay capability
  - **Cons**: Operational complexity, overkill for our scale

**Queue Design Pattern**:
```
Priority Queue Implementation:
- High Priority: Jobs with < 100 URLs
- Medium Priority: Jobs with 100-1000 URLs  
- Low Priority: Large jobs > 1000 URLs

Dead Letter Queue:
- Failed tasks after 3 retries
- Manual intervention queue for problematic domains
```

#### Deep Dive 2: Worker Node Architecture

**Worker Scalability Design**:
- **Auto-scaling**: Horizontal pod autoscaler based on queue depth
- **Resource Isolation**: CPU/memory limits per worker container
- **Graceful Shutdown**: Complete current tasks before termination

**Politeness Implementation**:
```
Domain Rate Limiter:
- Token bucket per domain (configurable rate)
- Distributed coordination via Redis
- Exponential backoff for 429/503 responses
- Respect Crawl-Delay from robots.txt

Circuit Breaker Pattern:
- Fail fast for consistently failing domains
- Automatic recovery attempts with exponential backoff
```

#### Deep Dive 3: Content Storage Strategy

**Storage Tier Strategy**:
1. **Hot Storage (Recent 30 days)**: Redis for job results, PostgreSQL for metadata
2. **Warm Storage (30-365 days)**: S3 Standard for content, compressed JSON
3. **Cold Storage (>1 year)**: S3 Glacier for archived jobs

**Data Partitioning**:
- **PostgreSQL**: Partition jobs by creation_date (monthly partitions)
- **Object Storage**: Partition by job_id prefix for even distribution
- **Elasticsearch**: Time-based indices with automated rollover

**Trade-off Analysis**:
- **Cost vs Access Speed**: Tiered storage reduces costs by 70% with acceptable access times
- **Consistency vs Performance**: Eventual consistency for search index vs immediate consistency for job status

#### Deep Dive 4: Content Deduplication and Processing

**URL Deduplication Strategy**:
```
Multi-level Deduplication:
1. Bloom Filter (1% false positive rate): Quick rejection of seen URLs
2. Redis Set: Exact URL tracking per job
3. Content Hash: SHA-256 for duplicate content detection

URL Canonicalization:
- Remove tracking parameters
- Normalize case and encoding
- Handle redirects consistently
```

**Content Processing Pipeline**:
- **Image Extraction**: Parse HTML, extract src attributes, validate image URLs
- **Link Extraction**: Extract all <a> tags, validate against domain whitelist
- **Metadata Extraction**: Title, description, keywords using HTML parsing
- **Content Cleaning**: Remove scripts, styles, normalize whitespace

#### Deep Dive 5: Monitoring and Reliability

**Circuit Breaker Implementation**:
- Per-domain failure tracking with Redis counters
- Automatic domain blacklisting after consecutive failures
- Health check endpoints for worker liveness probes

**Observability Stack**:
```
Metrics (Prometheus):
- Queue depth by priority
- Worker utilization and success rates
- Domain-specific performance metrics
- Storage utilization trends

Logging (ELK Stack):
- Structured JSON logs with correlation IDs
- Error categorization and alerting
- Performance bottleneck identification

Distributed Tracing (Jaeger):
- End-to-end job processing traces
- Worker performance analysis
- Dependency mapping
```

**Failure Recovery Patterns**:
- **Job Recovery**: Restart failed jobs from last checkpoint
- **Worker Recovery**: Reassign tasks from failed workers
- **Data Recovery**: Multiple replica strategy for critical metadata

## Question 3: Hierarchical Data Storage System

### API Design
```cpp
class HierarchicalDataSystem {
public:
    string addChildNode(string parentId, NodeData data);
    vector<NodeInfo> getChildren(string nodeId);
    vector<string> getAncestors(string nodeId);
    bool reorderNodes(string parentId, vector<string> childOrder);
    bool hasPermission(string userId, string nodeId, Permission perm);
};

struct NodeInfo {
    string nodeId;
    NodeData data;
    bool hasChildren;
    int childCount;
    Permission userPermission;
};
```

### Data Model (Adjacency List + Materialized Path)
```sql
CREATE TABLE nodes (
    node_id UUID PRIMARY KEY,
    parent_id UUID,
    node_path VARCHAR(4000), -- /root/child1/child2
    level INT,
    order_index INT,
    data JSONB,
    created_at TIMESTAMP,
    INDEX(parent_id),
    INDEX(node_path)
);

CREATE TABLE node_permissions (
    node_id UUID,
    user_id UUID,
    permission_type ENUM('read', 'write', 'admin'),
    inherited BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (node_id, user_id, permission_type)
);
```

### Scale-up Implementations
- **Caching**: Cache frequently accessed subtrees
- **Bulk Operations**: Batch operations for moving/copying subtrees
- **Permission Inheritance**: Efficient permission checking with path-based queries

## Question 4: Confluence Popular Feed

### API Design
```cpp
class PopularFeedService {
public:
    vector<ContentItem> getPopularFeed(string userId, int page, int limit);
    void recordInteraction(string userId, string contentId, InteractionType type);
    vector<ContentItem> getPersonalizedFeed(string userId);
    vector<ContentItem> getTrendingContent(TimeFrame timeframe);
};
```

### Data Model
```sql
CREATE TABLE content_interactions (
    user_id BIGINT,
    content_id BIGINT,
    interaction_type ENUM('view', 'like', 'comment', 'share'),
    timestamp TIMESTAMP,
    INDEX(content_id, timestamp),
    INDEX(user_id, timestamp)
);

CREATE TABLE content_popularity_scores (
    content_id BIGINT PRIMARY KEY,
    hourly_score FLOAT,
    daily_score FLOAT,
    weekly_score FLOAT,
    monthly_score FLOAT,
    last_updated TIMESTAMP
);
```

### Algorithm
```cpp
class PopularityCalculator {
private:
    double calculateScore(ContentInteractions interactions) {
        double score = 0.0;
        double timeDecay = 1.0;
        
        for (auto& interaction : interactions) {
            double weight = getInteractionWeight(interaction.type);
            double recency = calculateRecencyScore(interaction.timestamp);
            score += weight * recency * timeDecay;
            timeDecay *= 0.95; // Decay factor
        }
        
        return score;
    }
    
    double getInteractionWeight(InteractionType type) {
        switch(type) {
            case VIEW: return 1.0;
            case LIKE: return 3.0;
            case COMMENT: return 5.0;
            case SHARE: return 8.0;
        }
    }
};
```

## Question 5: Color Picker Web Application

### Architecture (1-day implementation)
```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   React Frontend│────│   Node.js API   │────│   PostgreSQL    │
│   (Color Picker)│    │   (Express)     │    │   (User Colors) │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### API Design
```javascript
// REST API endpoints
POST /api/colors - Save a color
GET /api/colors/:userId - Get user's saved colors
PUT /api/colors/:colorId - Update a color
DELETE /api/colors/:colorId - Delete a color
POST /api/colors/:colorId/share - Share color with users
GET /api/colors/public - Get public colors
```

### Database Schema
```sql
CREATE TABLE users (
    user_id SERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE,
    email VARCHAR(255) UNIQUE,
    created_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE saved_colors (
    color_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES users(user_id),
    color_hex VARCHAR(7), -- #RRGGBB
    color_name VARCHAR(100),
    is_public BOOLEAN DEFAULT FALSE,
    created_at TIMESTAMP DEFAULT NOW()
);

CREATE TABLE color_shares (
    share_id SERIAL PRIMARY KEY,
    color_id INT REFERENCES saved_colors(color_id),
    shared_with_user_id INT REFERENCES users(user_id),
    shared_by_user_id INT REFERENCES users(user_id),
    created_at TIMESTAMP DEFAULT NOW()
);
```

### Frontend Implementation (React)
```jsx
const ColorPicker = () => {
    const [selectedColor, setSelectedColor] = useState('#FF0000');
    const [savedColors, setSavedColors] = useState([]);
    
    const saveColor = async () => {
        const response = await fetch('/api/colors', {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({
                color_hex: selectedColor,
                color_name: colorName,
                is_public: isPublic
            })
        });
        // Handle response
    };
    
    return (
        <div>
            <input 
                type="color" 
                value={selectedColor} 
                onChange={(e) => setSelectedColor(e.target.value)} 
            />
            <ColorPalette colors={savedColors} />
            <SharePanel colorId={selectedColorId} />
        </div>
    );
};
```

### Scaling Considerations
- **CDN**: Cache color palettes and public colors
- **Caching**: Redis for frequently accessed color combinations
- **Database Sharding**: Shard by user_id for large user base
- **Image Generation**: Generate color palette images and cache them
- **Rate Limiting**: Prevent spam color creation
- **Search**: Elasticsearch for color search by name/hex/RGB values

### Deployment (1-day scope)
```dockerfile
# Simple Docker deployment
FROM node:16
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
EXPOSE 3000
CMD ["npm", "start"]
```

### Monitoring and Analytics
- Track popular colors
- User engagement metrics
- Color usage patterns
- Performance monitoring with basic health checks

---

## Interview Tips for System Design

1. **Start with Requirements**: Clarify functional and non-functional requirements
2. **Estimate Scale**: Ask about expected users, requests per second, data size
3. **High-level Design**: Draw basic architecture first
4. **Deep Dive**: Focus on one component and discuss in detail
5. **Scale Gradually**: Start simple, then add complexity
6. **Trade-offs**: Discuss pros/cons of different approaches
7. **Real-world Considerations**: Mention monitoring, security, testing
