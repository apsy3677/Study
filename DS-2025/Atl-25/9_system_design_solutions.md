# Atlassian Interview Solutions - System Design Questions

This document contains high-level solutions for the system design questions in the Atlassian interview preparation.

## Question 1: Tagging System

### Part 1: API Design
```
POST /tags
- Create a new tag

GET /tags
- List all tags with popularity metrics

POST /content/{content-id}/tags
- Add tags to content
Body: {"tags": ["tag1", "tag2"]}

DELETE /content/{content-id}/tags/{tag-id}
- Remove tag from content

GET /tags/{tag-id}/content
- Get all content associated with a tag
- Support pagination: ?page=1&limit=20

GET /tags/popular
- Get dashboard of popular tags
- Support time ranges: ?timeframe=7d|30d|90d
```

### Part 2: Data Modeling
```sql
-- Core tables
CREATE TABLE tags (
    tag_id BIGINT PRIMARY KEY,
    tag_name VARCHAR(255) UNIQUE,
    created_at TIMESTAMP,
    popularity_score INT DEFAULT 0
);

CREATE TABLE content (
    content_id BIGINT PRIMARY KEY,
    product_type ENUM('jira', 'confluence', 'bitbucket'),
    content_type VARCHAR(50), -- issue, page, pull_request
    created_at TIMESTAMP
);

CREATE TABLE content_tags (
    content_id BIGINT,
    tag_id BIGINT,
    created_at TIMESTAMP,
    created_by BIGINT,
    PRIMARY KEY (content_id, tag_id)
);

-- For popular tags dashboard
CREATE TABLE tag_popularity_daily (
    tag_id BIGINT,
    date DATE,
    usage_count INT,
    PRIMARY KEY (tag_id, date)
);
```

### Part 3: Scaling Popular Tags API
- **Caching Strategy**: Redis cache for popular tags with TTL
- **Pre-computation**: Daily batch jobs to calculate popularity metrics
- **CDN**: Cache popular tags response at edge locations
- **Read Replicas**: Separate read replicas for analytics queries

### Part 4: Scaling Remaining APIs
- **Horizontal Sharding**: Shard by content_id or product_type
- **Microservices**: Separate tag service from content services
- **Event-driven Architecture**: Use message queues for tag updates
- **Database Optimization**: Proper indexing on content_tags table

### Part 5: Introducing Permissions
```sql
-- Add permission tables
CREATE TABLE permissions (
    permission_id BIGINT PRIMARY KEY,
    content_id BIGINT,
    user_id BIGINT,
    permission_type ENUM('read', 'write', 'admin'),
    granted_by BIGINT,
    granted_at TIMESTAMP
);

-- Modify API to check permissions before tag operations
-- Implement permission inheritance from product-level permissions
```

## Question 2: Web Scraper Service

### Architecture Overview
```
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│   Load      │    │   Job Queue  │    │  Worker     │
│  Balancer   │────│   (Redis)    │────│  Nodes      │
└─────────────┘    └──────────────┘    └─────────────┘
       │                   │                   │
       │                   │                   │
       ▼                   ▼                   ▼
┌─────────────┐    ┌──────────────┐    ┌─────────────┐
│  API Gateway│    │  PostgreSQL  │    │  S3 Storage │
│             │    │  (Metadata)  │    │  (Results)  │
└─────────────┘    └──────────────┘    └─────────────┘
```

### Data Model
```sql
CREATE TABLE scraping_jobs (
    job_id UUID PRIMARY KEY,
    status ENUM('pending', 'running', 'completed', 'failed'),
    created_at TIMESTAMP,
    completed_at TIMESTAMP,
    total_urls INT,
    processed_urls INT
);

CREATE TABLE job_urls (
    job_id UUID,
    url VARCHAR(2048),
    status ENUM('pending', 'processing', 'completed', 'failed'),
    depth INT DEFAULT 0,
    parent_url VARCHAR(2048),
    PRIMARY KEY (job_id, url)
);
```

### API Implementation
```cpp
// Job Management
class ScrapingJobManager {
    string createJob(vector<string> urls);
    JobStatus getJobStatus(string jobId);
    map<string, vector<string>> getJobResults(string jobId);
    
private:
    void processUrlsRecursively(string jobId, vector<string> urls, int depth);
    vector<string> extractImages(string htmlContent);
    vector<string> extractLinks(string htmlContent);
};
```

### Scaling Considerations
- **Worker Pools**: Multiple worker nodes for parallel processing
- **Rate Limiting**: Respect robots.txt and implement backoff
- **Deduplication**: Use bloom filters to avoid processing same URLs
- **Fault Tolerance**: Retry mechanisms with exponential backoff

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
