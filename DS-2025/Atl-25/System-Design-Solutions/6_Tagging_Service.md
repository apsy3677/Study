# Tagging Service Design for Atlassian Content

## Table of Contents
1. [Requirements Analysis](#1-requirements-analysis)
2. [System Architecture](#2-system-architecture)
3. [Data Models](#3-data-models)
4. [Core Components](#4-core-components)
5. [API Design](#5-api-design)
6. [Scaling Strategy](#6-scaling-strategy)
7. [Performance Optimization](#7-performance-optimization)
8. [Monitoring & Analytics](#8-monitoring--analytics)
9. [Security Considerations](#9-security-considerations)
10. [Future Improvements](#10-future-improvements)

## 1. Requirements Analysis

### Functional Requirements
- Tag creation and management
- Tag assignment to content
- Tag hierarchies and relationships
- Tag search and suggestions
- Bulk tagging operations
- Tag analytics and trends
- Tag synonyms and aliases
- Tag governance and moderation

### Non-Functional Requirements
- Low latency tag operations (< 100ms)
- High availability (99.99%)
- Eventually consistent tag counts
- Scalable to billions of tagged items
- Cross-service compatibility
- Real-time tag updates

## 2. System Architecture

```plaintext
[Client Apps] --> [Load Balancer] --> [Tag Service API]
                                          |
    [Tag Manager] <--> [Tag Store] <--> [Search Index]
         |                |
    [Tag Rules]    [Analytics Store]
```

## 3. Data Models

### PostgreSQL Schema
```sql
CREATE TABLE tags (
    id UUID PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    normalized_name VARCHAR(255) NOT NULL,
    description TEXT,
    created_by UUID REFERENCES users(id),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    parent_id UUID REFERENCES tags(id),
    metadata JSONB,
    status VARCHAR(50) DEFAULT 'ACTIVE',
    workspace_id UUID,
    UNIQUE(workspace_id, normalized_name)
);

CREATE TABLE tag_relationships (
    id UUID PRIMARY KEY,
    source_tag_id UUID REFERENCES tags(id),
    target_tag_id UUID REFERENCES tags(id),
    relationship_type VARCHAR(50),  -- parent, related, synonym
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    metadata JSONB,
    UNIQUE(source_tag_id, target_tag_id, relationship_type)
);

CREATE TABLE tagged_items (
    id UUID PRIMARY KEY,
    tag_id UUID REFERENCES tags(id),
    item_type VARCHAR(50) NOT NULL,  -- jira_issue, confluence_page, etc.
    item_id VARCHAR(255) NOT NULL,
    tagged_by UUID REFERENCES users(id),
    tagged_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    workspace_id UUID,
    metadata JSONB,
    UNIQUE(tag_id, item_type, item_id)
);

CREATE TABLE tag_suggestions (
    id UUID PRIMARY KEY,
    content_snippet TEXT,
    suggested_tags JSONB,
    confidence_scores JSONB,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    item_type VARCHAR(50),
    item_id VARCHAR(255),
    metadata JSONB
);

CREATE TABLE tag_rules (
    id UUID PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    conditions JSONB,  -- Rule conditions
    actions JSONB,     -- Actions to take
    priority INTEGER,
    status VARCHAR(50) DEFAULT 'ACTIVE',
    created_by UUID REFERENCES users(id),
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE tag_analytics (
    id UUID PRIMARY KEY,
    tag_id UUID REFERENCES tags(id),
    timestamp TIMESTAMP WITH TIME ZONE,
    metric_type VARCHAR(50),  -- usage_count, search_count, etc.
    metric_value INTEGER,
    dimensions JSONB,
    workspace_id UUID
);
```

## 4. Core Components

### Tag Manager
```python
class TagManager:
    async def create_tag(self, tag_data):
        # Validate tag data
        normalized_name = self.normalize_tag_name(tag_data['name'])
        
        # Check for duplicates
        existing = await self.find_by_normalized_name(normalized_name)
        if existing:
            raise DuplicateTagError()
            
        # Create tag
        tag = await self.tag_store.create({
            'name': tag_data['name'],
            'normalized_name': normalized_name,
            'description': tag_data.get('description'),
            'metadata': tag_data.get('metadata', {})
        })
        
        # Index for search
        await self.search_index.index_tag(tag)
        
        return tag
```

### Tag Rules Engine
```python
class TagRulesEngine:
    async def evaluate_rules(self, content, metadata):
        applicable_rules = await self.find_applicable_rules(content)
        
        suggestions = []
        for rule in applicable_rules:
            if await self.evaluate_conditions(rule, content, metadata):
                suggestions.extend(await self.apply_actions(rule))
                
        return suggestions
```

## 5. API Design

### REST API Endpoints
```python
@router.post("/tags")
async def create_tag(tag: TagCreate):
    return await tag_service.create_tag(tag)

@router.post("/items/{item_id}/tags")
async def tag_item(item_id: str, tags: List[str]):
    return await tag_service.tag_item(item_id, tags)

@router.get("/tags/suggest")
async def suggest_tags(content: str, context: dict):
    return await tag_service.suggest_tags(content, context)

@router.get("/tags/trending")
async def get_trending_tags(workspace_id: str):
    return await analytics_service.get_trending_tags(workspace_id)
```

## 6. Scaling Strategy

### Data Partitioning
```sql
-- Partition tagged_items by workspace
CREATE TABLE tagged_items_partition OF tagged_items
PARTITION BY HASH (workspace_id);

-- Time-based partitioning for analytics
CREATE TABLE tag_analytics_partition OF tag_analytics
PARTITION BY RANGE (timestamp);
```

### Caching Strategy
```python
class TagCache:
    def __init__(self):
        self.tag_cache = Redis()
        self.count_cache = Redis()
        self.suggestion_cache = Redis()
        
    async def get_tag_counts(self, tag_ids):
        # Try cache first
        cached_counts = await self.count_cache.mget(tag_ids)
        
        # Get missing counts from DB
        missing = self.get_missing_ids(tag_ids, cached_counts)
        if missing:
            db_counts = await self.fetch_from_db(missing)
            await self.count_cache.mset(db_counts)
            
        return self.merge_counts(cached_counts, db_counts)
```

## 7. Performance Optimization

### Batch Operations
```python
class BatchProcessor:
    async def batch_tag_items(self, items, tags):
        # Group by workspace for efficient processing
        by_workspace = self.group_by_workspace(items)
        
        # Process each workspace batch
        results = []
        for workspace_id, workspace_items in by_workspace.items():
            batch = await self.create_batch_operation(workspace_items, tags)
            results.extend(await self.execute_batch(batch))
            
        return results
```

### Search Optimization
```python
class TagSearch:
    def build_search_query(self, term, filters):
        return {
            "query": {
                "bool": {
                    "must": [
                        {"multi_match": {
                            "query": term,
                            "fields": ["name^3", "description"],
                            "fuzziness": "AUTO"
                        }}
                    ],
                    "filter": self.build_filters(filters)
                }
            },
            "aggs": {
                "related_tags": {
                    "terms": {"field": "related_tags"}
                }
            }
        }
```

## 8. Monitoring & Analytics

### Metrics Collection
```sql
CREATE TABLE tag_service_metrics (
    id UUID PRIMARY KEY,
    timestamp TIMESTAMP WITH TIME ZONE,
    metric_name VARCHAR(100),
    metric_value FLOAT,
    dimensions JSONB
);

CREATE TABLE tag_usage_patterns (
    id UUID PRIMARY KEY,
    analysis_period VARCHAR(50),
    pattern_type VARCHAR(100),
    pattern_data JSONB,
    confidence FLOAT,
    created_at TIMESTAMP WITH TIME ZONE
);
```

### Analytics Queries
```sql
-- Tag usage trends
SELECT 
    date_trunc('day', timestamp) as day,
    tag_id,
    COUNT(*) as usage_count
FROM tag_analytics
WHERE metric_type = 'usage'
GROUP BY day, tag_id
ORDER BY day DESC;

-- Co-occurrence analysis
SELECT 
    t1.tag_id as tag1,
    t2.tag_id as tag2,
    COUNT(*) as co_occurrences
FROM tagged_items t1
JOIN tagged_items t2 ON t1.item_id = t2.item_id
WHERE t1.tag_id < t2.tag_id
GROUP BY t1.tag_id, t2.tag_id
HAVING COUNT(*) > 10;
```

## 9. Security Considerations

### Access Control
```python
class TagPermissionManager:
    async def check_permission(self, user_id, tag_id, action):
        # Get tag details
        tag = await self.tag_store.get(tag_id)
        
        # Check workspace access
        if not await self.workspace_access.can_access(user_id, tag.workspace_id):
            return False
            
        # Check specific permission
        return await self.permission_store.has_permission(
            user_id, tag.workspace_id, f"tag.{action}"
        )
```

### Validation Rules
```python
class TagValidator:
    def validate_tag(self, tag_data):
        rules = [
            self.validate_name_length,
            self.validate_name_format,
            self.validate_description,
            self.validate_metadata
        ]
        
        for rule in rules:
            rule(tag_data)
```

## 10. Future Improvements

### 1. Advanced Features
- ML-based tag suggestions
- Automated tag cleanup
- Tag governance workflows
- Advanced analytics

### 2. Performance Enhancements
- Predictive caching
- Enhanced batch processing
- Search optimization
- Real-time analytics

### 3. Integration Capabilities
- Webhook support
- Custom rules engine
- External system integration
- Bulk import/export

### 4. Analytics and Insights
- Tag effectiveness metrics
- Usage pattern analysis
- Recommendation engine
- Trend detection
