# Cross-Product Tagging System - Staff Engineer Design

## Problem Statement
Design a tagging system that works across Atlassian's product suite (Jira, Confluence, Bitbucket) allowing users to tag content, discover related items, and view popular tags analytics.

## Requirements (~5 minutes)

### Functional Requirements
1. **Tag Management**: Users should be able to create, update, and delete tags across Jira, Confluence, and Bitbucket
2. **Content Tagging**: Users should be able to attach multiple tags to content items (issues, pages, repositories, pull requests)
3. **Tag Discovery**: Users should be able to search and discover existing tags with autocomplete functionality
4. **Popular Tags Dashboard**: Administrators should be able to view trending tags across products with configurable time windows (1d, 7d, 30d)
5. **Cross-Product Tag Navigation**: Users should be able to find related content across products using shared tags
6. **Tag Suggestions**: System should suggest relevant tags based on content analysis and user behavior

### Non-Functional Requirements
1. **Scalability**: System must handle 100M+ content items across 50K+ organizations with 10M+ daily active users
2. **Availability**: 99.9% uptime with graceful degradation (core product functionality should not be blocked by tagging failures)
3. **Consistency**: Eventual consistency is acceptable for tag popularity metrics, but strong consistency required for tag-content associations
4. **Performance**: 
   - Tag autocomplete < 100ms (P95)
   - Content retrieval by tags < 500ms (P95)
   - Popular tags dashboard < 2s (P95)
5. **Security**: Tag visibility must respect existing product permissions and organizational boundaries
6. **Storage**: Efficient storage for ~1B tag-content associations with 10M unique tags

### Capacity Estimation
**Key calculations that influence our design**:
- **Tag Operations**: ~10M tag operations/day across all products (read:write ratio ~50:1)
- **Popular Tags Calculation**: Process ~500M daily interactions across 10M unique tags
- **Storage Requirements**: 
  - Tag metadata: ~100GB (10M tags × 10KB average)
  - Tag-content associations: ~1TB (1B associations × 1KB each)
  - Popularity time-series: ~10TB (10M tags × 365 days × 3KB per day)

## Core Entities (~2 minutes)
- **Tag**: Represents a label with metadata (name, description, creation context, organization scope)
- **TaggedContent**: Association between tags and content across products with timestamps
- **TagPopularityMetrics**: Time-series data for tag usage analytics and trending calculations
- **Organization**: Boundary for tag visibility, permissions, and analytics scope
- **TagSuggestion**: ML-generated tag recommendations based on content and user patterns

## API Design (~5 minutes)

### Protocol Choice
**REST** for CRUD operations with **GraphQL** for complex tag discovery queries to handle diverse client needs efficiently. **WebSocket** for real-time tag suggestions during content creation.

```http
# Tag Management
POST /v1/tags
Body: {
  "name": "backend-performance",
  "description": "Issues related to backend performance optimization",
  "color": "#FF5733",
  "organization_id": "org_123"
}

GET /v1/tags/search?q={query}&org_id={org}&limit=20&products=jira,confluence
PUT /v1/tags/{tag_id}
DELETE /v1/tags/{tag_id}

# Content Tagging
POST /v1/content/{content_id}/tags
Body: {
  "tag_ids": ["tag_123", "tag_456"],
  "product": "jira",
  "content_type": "issue"
}

DELETE /v1/content/{content_id}/tags/{tag_id}
GET /v1/tags/{tag_id}/content?product={product}&org_id={org}&page=1&limit=50

# Analytics & Discovery
GET /v1/analytics/tags/popular?timeframe=7d&org_id={org}&product={product}
GET /v1/analytics/tags/{tag_id}/trends?timeframe=30d

# Tag Suggestions
GET /v1/tags/suggestions?content_type=issue&title={title}&description={description}
WebSocket: /v1/tags/suggestions/stream (real-time suggestions during typing)

# GraphQL for complex queries
query TagsWithRelatedContent($orgId: ID!, $filters: TagFilters!) {
  tags(orgId: $orgId, filters: $filters) {
    id
    name
    contentCount(product: $filters.product)
    relatedTags(limit: 5) {
      id
      name
      commonContentCount
    }
    trending {
      rank
      changePercent
    }
  }
}
```

## High Level Design (~10-15 minutes)

```
                        ┌─────────────────┐
                        │   CDN/CloudFlare│
                        │  (Static Assets)│
                        └─────────┬───────┘
                                  │
                        ┌─────────▼───────┐
                        │   API Gateway   │
                        │ (Rate Limiting, │
                        │ Auth, Routing)  │
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
         │ + Replicas)│     │(Cassandra)│     │ (Kafka +  │
         └─────┬─────┘     └─────┬─────┘     │Spark/Flink│
               │                 │           └─────┬─────┘
         ┌─────▼─────┐     ┌─────▼─────┐           │
         │Tag Cache  │     │Search Index│    ┌─────▼─────┐
         │ (Redis    │     │(Elasticsearch)│ │Time Series│
         │ Cluster)  │     │   + Cache    │  │(InfluxDB) │
         └───────────┘     └──────────────┘  └───────────┘
                                  │
                           ┌─────▼─────┐
                           │ML Pipeline│
                           │(Tag Suggest│
                           │ + Content │
                           │ Analysis) │
                           └───────────┘
```

### Data Flow Examples

**Tag Creation Flow**:
1. User creates tag → API Gateway (auth/rate limit) → Tag Service
2. Tag Service validates uniqueness → Stores in PostgreSQL → Returns tag_id
3. Async: Publishes event → Kafka → Search indexer updates Elasticsearch
4. Cache warming for popular tag queries

**Content Tagging Flow**:
1. User tags content → Tag Service validates permissions → Stores association in Cassandra
2. Async: Updates tag popularity counters → Analytics pipeline → InfluxDB
3. Invalidates relevant caches (content tags, tag content counts)

**Popular Tags Dashboard Flow**:
1. Request → Cache check (Redis) → If miss, query InfluxDB
2. Aggregate across time windows → Cache result with 5-min TTL
3. Return trending data with confidence intervals

## Deep Dives (~10 minutes)

### Deep Dive 1: Storage Architecture Trade-offs

#### PostgreSQL for Tag Metadata
**Why Chosen**:
- Strong consistency for tag definitions and permissions
- Complex queries for tag relationships and hierarchies
- ACID transactions for tag management operations

**Schema Design**:
```sql
CREATE TABLE tags (
    tag_id UUID PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    color VARCHAR(7),
    organization_id UUID NOT NULL,
    created_by UUID NOT NULL,
    created_at TIMESTAMP DEFAULT NOW(),
    updated_at TIMESTAMP DEFAULT NOW(),
    is_system_tag BOOLEAN DEFAULT FALSE,
    UNIQUE(organization_id, name),
    INDEX(organization_id, created_at),
    INDEX(name) -- For autocomplete queries
);

CREATE TABLE tag_hierarchies (
    parent_tag_id UUID REFERENCES tags(tag_id),
    child_tag_id UUID REFERENCES tags(tag_id),
    PRIMARY KEY(parent_tag_id, child_tag_id)
);
```

**Scaling Strategy**:
- Read replicas for tag discovery queries
- Horizontal partitioning by organization_id for large deployments
- Connection pooling with PgBouncer

#### Cassandra for Tag-Content Associations
**Why Chosen Over Alternatives**:
- **vs PostgreSQL**: Better write performance for high-volume tagging operations
- **vs MongoDB**: Better for time-series access patterns and horizontal scaling
- **vs DynamoDB**: More cost-effective for predictable access patterns

**Schema Design**:
```cql
-- Primary access pattern: Get tags for content
CREATE TABLE content_tags (
    content_id UUID,
    product TEXT,
    tag_id UUID,
    tag_name TEXT, -- Denormalized for performance
    tagged_by UUID,
    tagged_at TIMESTAMP,
    PRIMARY KEY (content_id, tag_id)
);

-- Secondary access pattern: Get content for tag
CREATE TABLE tag_contents (
    tag_id UUID,
    organization_id UUID,
    product TEXT,
    content_id UUID,
    content_title TEXT, -- Denormalized
    tagged_at TIMESTAMP,
    PRIMARY KEY ((tag_id, organization_id), product, tagged_at, content_id)
) WITH CLUSTERING ORDER BY (product ASC, tagged_at DESC, content_id ASC);
```

**Trade-offs**:
- **Pros**: Excellent write performance, natural partitioning, linear scalability
- **Cons**: Data duplication, eventual consistency, complex query patterns
- **Mitigation**: Async reconciliation jobs, careful data modeling

### Deep Dive 2: Tag Discovery and Search Optimization

#### Elasticsearch Strategy
**Index Design**:
```json
{
  "tags_index": {
    "mappings": {
      "properties": {
        "name": {
          "type": "text",
          "fields": {
            "exact": {"type": "keyword"},
            "autocomplete": {
              "type": "text",
              "analyzer": "autocomplete_analyzer"
            }
          }
        },
        "description": {"type": "text"},
        "organization_id": {"type": "keyword"},
        "popularity_score": {"type": "integer"},
        "usage_trend": {"type": "float"},
        "content_count": {"type": "integer"},
        "recent_usage": {"type": "date"}
      }
    }
  }
}
```

**Autocomplete Performance**:
- Edge n-gram tokenizer for prefix matching
- Boosting based on popularity and user's organization
- Redis cache for top 1000 autocomplete queries per organization

**Search Ranking Algorithm**:
```
final_score = (
    text_relevance_score * 0.4 +
    popularity_score * 0.3 +
    user_affinity_score * 0.2 +
    recency_score * 0.1
) * organization_boost
```

### Deep Dive 3: Popular Tags Analytics at Scale

#### Real-time vs Batch Processing Architecture
**Lambda Architecture Approach**:
- **Speed Layer**: Kafka Streams for real-time trending (last 1 hour)
- **Batch Layer**: Spark jobs for historical analysis and ML training
- **Serving Layer**: InfluxDB for time-series queries with Redis caching

**Popularity Algorithm**:
```python
def calculate_tag_popularity(tag_events, time_window):
    score = 0
    current_time = now()
    
    for event in tag_events:
        # Time decay factor (exponential)
        time_diff_hours = (current_time - event.timestamp).hours
        time_decay = exp(-time_diff_hours / 24)  # 24-hour half-life
        
        # Event weights
        weights = {
            'tag_created': 5,
            'tag_applied': 3,
            'content_viewed': 1,
            'tag_shared': 8
        }
        
        # User authority (based on role and activity)
        user_authority = get_user_authority_score(event.user_id)
        
        score += weights[event.type] * time_decay * user_authority
    
    return score
```

**Trending Detection**:
- Compare current window vs previous window popularity
- Statistical significance testing to avoid noise
- Confidence intervals for trending indicators

### Deep Dive 4: Cross-Product Permission Model

#### Challenge Analysis
Different permission models across products:
- **Jira**: Project-based permissions with role hierarchies
- **Confluence**: Space-based permissions with inheritance
- **Bitbucket**: Repository-based permissions with team access

#### Solution: Permission Intersection Model
```python
class TagPermissionResolver:
    def can_user_see_tag(self, user_id, tag_id, context):
        # Get all content associated with this tag
        tagged_content = get_tagged_content(tag_id)
        
        # User can see tag if they can see ANY associated content
        for content in tagged_content:
            if self.can_user_access_content(user_id, content):
                return True
        
        return False
    
    def can_user_apply_tag(self, user_id, tag_id, content_id):
        # Must have write access to content AND tag visibility
        return (
            self.can_user_modify_content(user_id, content_id) and
            self.can_user_see_tag(user_id, tag_id, content_id)
        )
```

**Permission Caching Strategy**:
- Redis cache with hierarchical keys: `perm:{user_id}:{tag_id}:{product}`
- TTL of 15 minutes with cache invalidation on role changes
- Async background refresh for frequently accessed permissions

**Trade-offs**:
- **Consistency vs Performance**: 15-minute eventual consistency vs immediate permission updates
- **Storage vs Computation**: Pre-computed permission cache vs real-time calculation
- **Security vs Usability**: Strict inheritance vs flexible tag sharing

### Deep Dive 5: Tag Suggestion and ML Pipeline

#### Content Analysis Pipeline
```python
class TagSuggestionEngine:
    def suggest_tags(self, content):
        suggestions = []
        
        # 1. Keyword extraction using TF-IDF
        keywords = extract_keywords(content.text)
        keyword_tags = self.match_keywords_to_tags(keywords)
        
        # 2. Similar content analysis
        similar_content = self.find_similar_content(content)
        collaborative_tags = self.get_tags_from_similar_content(similar_content)
        
        # 3. User behavior patterns
        user_patterns = self.get_user_tagging_patterns(content.author_id)
        pattern_tags = self.predict_from_patterns(user_patterns, content)
        
        # 4. Ensemble scoring
        suggestions = self.ensemble_score([
            (keyword_tags, 0.4),
            (collaborative_tags, 0.35),
            (pattern_tags, 0.25)
        ])
        
        return sorted(suggestions, key=lambda x: x.confidence)[:10]
```

**ML Model Architecture**:
- **Feature Engineering**: Content embeddings (BERT), user behavior vectors, tag co-occurrence matrices
- **Model**: Gradient boosting with online learning for real-time adaptation
- **Training**: Daily batch training with streaming updates for popular tags

### Deep Dive 6: Operational Excellence

#### Monitoring and Alerting
**Key Metrics**:
```yaml
SLIs:
  - tag_operation_latency_p95 < 200ms
  - tag_search_latency_p95 < 100ms
  - popular_tags_api_latency_p95 < 2000ms
  - tag_suggestion_accuracy > 0.75

SLOs:
  - availability: 99.9%
  - data_consistency: 99.99%
  - cache_hit_rate: > 85%

Alerts:
  - Error rate > 1% (immediate)
  - Latency degradation > 50% (5 minutes)
  - Cache hit rate < 70% (immediate)
  - Data lag > 10 minutes (immediate)
```

#### Disaster Recovery Strategy
1. **Multi-region Setup**: Active-passive with 15-minute RTO
2. **Data Backup**: 
   - PostgreSQL: Continuous WAL archiving + daily snapshots
   - Cassandra: Incremental backups with cross-region replication
   - InfluxDB: Automated backup to object storage
3. **Failover Automation**: Health checks with automatic DNS switching
4. **Data Consistency**: Cross-region data validation jobs

#### Capacity Planning
- **Growth Projections**: 100% YoY growth in tag operations
- **Resource Scaling**: Auto-scaling based on queue depth and CPU utilization
- **Cost Optimization**: Spot instances for analytics workloads, reserved instances for core services

This design demonstrates staff-level thinking through comprehensive trade-off analysis, detailed technical decisions, and operational considerations that reflect 9-10 years of distributed systems experience.
