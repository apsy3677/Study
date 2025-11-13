# API Cost Optimizer - Real-World Scenarios & Advanced Patterns

## Table of Contents
1. [Common Usage Scenarios](#1-common-usage-scenarios)
2. [Edge Cases & Handling](#2-edge-cases--handling)
3. [Advanced Optimization Patterns](#3-advanced-optimization-patterns)
4. [Failure Scenarios & Recovery](#4-failure-scenarios--recovery)
5. [Performance Optimization Techniques](#5-performance-optimization-techniques)
6. [Security & Compliance Patterns](#6-security--compliance-patterns)

---

## 1. Common Usage Scenarios

### Scenario 1: E-Commerce Product Catalog

**Business Context:**
- Users browse product listings frequently
- Product data changes occasionally (price updates, stock changes)
- High read-to-write ratio (1000:1)
- SLA requirement: <100ms for product details

**Optimization Strategy:**

```go
// Product listing endpoint
GET /api/products?category=electronics&page=1

Optimization Plan:
├─> [1] Cache Strategy
│   ├─> TTL: 5 minutes (prices change infrequently)
│   ├─> Cache Key: hash(category, page, customer_tier)
│   ├─> Expected Hit Rate: 85%
│   └─> Savings: ~90% of requests served from cache
│
├─> [2] Invalidation Strategy
│   ├─> Event: "product.price_updated"
│   └─> Action: Invalidate specific product + list caches
│
└─> [3] Cache Warming
    ├─> Pre-fetch popular categories at peak hours
    └─> Prime cache before marketing campaigns
```

**Implementation:**

```go
type ProductCatalogOptimizer struct {
    cache         *CacheLayer
    eventStream   *EventStream
}

func (p *ProductCatalogOptimizer) GetProducts(req *Request) (*Response, error) {
    // Generate smart cache key
    cacheKey := p.generateProductCacheKey(req)
    
    // Try cache first
    if cached, found := p.cache.Get(cacheKey); found {
        return cached, nil
    }
    
    // Cache miss - fetch from API
    resp, err := p.fetchFromAPI(req)
    if err != nil {
        return nil, err
    }
    
    // Cache with dynamic TTL based on volatility
    ttl := p.calculateProductTTL(req.QueryParams["category"])
    p.cache.Set(cacheKey, resp, ttl)
    
    return resp, nil
}

func (p *ProductCatalogOptimizer) calculateProductTTL(category string) time.Duration {
    // Electronics prices change frequently
    if category == "electronics" {
        return 2 * time.Minute
    }
    
    // Books prices are stable
    if category == "books" {
        return 30 * time.Minute
    }
    
    // Default
    return 10 * time.Minute
}

// Event-based cache invalidation
func (p *ProductCatalogOptimizer) handlePriceUpdate(event *Event) {
    productID := event.Data["product_id"]
    
    // Invalidate specific product
    p.cache.Invalidate(fmt.Sprintf("product:%s", productID))
    
    // Invalidate list pages containing this product
    category := event.Data["category"]
    p.cache.InvalidatePattern(fmt.Sprintf("products:list:%s:*", category))
}
```

**Results:**
- Cost Reduction: 90% (cache hit rate)
- Latency: 2ms (cache) vs 45ms (API)
- Cache invalidation: <1 second after price update

---

### Scenario 2: Social Media Feed

**Business Context:**
- Personalized feeds for millions of users
- Real-time updates required
- Expensive feed generation algorithm
- Each API call costs $0.01

**Challenges:**
- Can't cache (personalized)
- Can't batch (user-specific)
- High volume (10M requests/day)

**Optimization Strategy:**

```go
Approach: Deduplication + Smart Pre-computation

Flow:
User requests feed
    │
    ├─> Check if recent feed exists (<30s old)
    │   └─> YES: Return existing feed (deduplication)
    │
    ├─> NO: Generate new feed
    │   ├─> Deduplicate with concurrent requests
    │   └─> Execute expensive feed algorithm
    │
    └─> Store feed with short TTL (30s)
        └─> Subsequent requests within 30s reuse
```

**Implementation:**

```go
type FeedOptimizer struct {
    deduplicator  *DeduplicationEngine
    feedCache     *TTLCache
    precomputer   *FeedPrecomputer
}

func (f *FeedOptimizer) GetFeed(userID string, req *Request) (*Response, error) {
    // [1] Check recent feed (short-lived cache)
    recentFeedKey := fmt.Sprintf("feed:recent:%s", userID)
    if feed, found := f.feedCache.Get(recentFeedKey); found {
        // Feed is fresh enough (< 30s)
        return feed, nil
    }
    
    // [2] Deduplicate concurrent requests for same user
    dedupKey := fmt.Sprintf("feed:gen:%s", userID)
    
    feed, err := f.deduplicator.Execute(dedupKey, func() (*Response, error) {
        // This expensive operation runs once even if
        // multiple requests come for same user
        return f.generateFeed(userID, req)
    })
    
    if err != nil {
        return nil, err
    }
    
    // [3] Cache for short duration
    f.feedCache.Set(recentFeedKey, feed, 30*time.Second)
    
    return feed, nil
}

// Background pre-computation for active users
func (f *FeedPrecomputer) PrecomputeFeeds() {
    // Identify users likely to check feed soon
    activeUsers := f.predictActiveUsers()
    
    for _, userID := range activeUsers {
        // Pre-generate feed
        feed := f.generateFeed(userID, nil)
        
        // Store in cache
        key := fmt.Sprintf("feed:recent:%s", userID)
        f.feedCache.Set(key, feed, 30*time.Second)
    }
}

func (f *FeedPrecomputer) predictActiveUsers() []string {
    // ML model to predict users likely to open app
    // Based on:
    // - Historical usage patterns
    // - Time of day
    // - Day of week
    // - Last activity time
    
    now := time.Now()
    hour := now.Hour()
    
    // Most users check feed in morning (7-9 AM)
    if hour >= 7 && hour <= 9 {
        return f.getHighActivityUsers(0.8) // 80% probability threshold
    }
    
    return f.getHighActivityUsers(0.95) // Higher threshold off-peak
}
```

**Results:**
- Cost Reduction: 60% (deduplication + pre-computation)
- Latency: 15ms (cached) vs 500ms (fresh generation)
- User Experience: Instant feed loads

---

### Scenario 3: Analytics Dashboard (Batch-Friendly)

**Business Context:**
- Dashboard shows metrics from multiple APIs
- Each widget queries different endpoint
- User loads dashboard → 20 API calls fired simultaneously
- SLA: Dashboard loads in <2 seconds

**Optimization Strategy:**

```go
Approach: Request Batching + Parallel Execution

Dashboard Load
    │
    ├─> Widget 1: GET /api/metrics/revenue
    ├─> Widget 2: GET /api/metrics/users
    ├─> Widget 3: GET /api/metrics/orders
    ├─> Widget 4: GET /api/metrics/traffic
    └─> ... (16 more)
    
Optimizer Action:
├─> Detect batch opportunity (all requests arrive within 50ms)
├─> Combine into single batch request
├─> Execute: POST /api/batch
│   {
│     "requests": [
│       {"id": "1", "url": "/metrics/revenue"},
│       {"id": "2", "url": "/metrics/users"},
│       ...
│     ]
│   }
└─> Distribute responses to widgets
```

**Implementation:**

```go
type DashboardOptimizer struct {
    batcher       *BatchProcessor
    cache         *CacheLayer
}

func (d *DashboardOptimizer) LoadDashboard(dashboardID string) (*Dashboard, error) {
    // Get dashboard configuration
    config := d.getConfig(dashboardID)
    
    // Create request batch
    batch := &RequestBatch{
        Requests: []BatchRequest{},
    }
    
    // Prepare all widget requests
    for _, widget := range config.Widgets {
        req := &BatchRequest{
            ID:       widget.ID,
            Method:   "GET",
            Endpoint: widget.DataSource,
        }
        batch.Requests = append(batch.Requests, req)
    }
    
    // Execute as single batched request
    responses, err := d.batcher.ExecuteBatch(batch)
    if err != nil {
        return nil, err
    }
    
    // Assemble dashboard
    dashboard := d.assembleDashboard(config, responses)
    
    return dashboard, nil
}

// Smart caching for dashboard data
func (d *DashboardOptimizer) GetWidgetData(widget *Widget) (*WidgetData, error) {
    // Different widgets have different data freshness requirements
    ttl := d.getWidgetTTL(widget)
    
    cacheKey := fmt.Sprintf("widget:%s:%s", widget.Type, widget.ID)
    
    // Try cache
    if cached, found := d.cache.Get(cacheKey); found {
        return cached, nil
    }
    
    // Fetch fresh data
    data, err := d.fetchWidgetData(widget)
    if err != nil {
        return nil, err
    }
    
    // Cache with appropriate TTL
    d.cache.Set(cacheKey, data, ttl)
    
    return data, nil
}

func (d *DashboardOptimizer) getWidgetTTL(widget *Widget) time.Duration {
    switch widget.Type {
    case "real_time_metrics":
        return 10 * time.Second  // Near real-time
        
    case "hourly_metrics":
        return 5 * time.Minute   // Refresh every 5 min
        
    case "daily_metrics":
        return 1 * time.Hour     // Refresh hourly
        
    case "historical_trends":
        return 24 * time.Hour    // Daily refresh
        
    default:
        return 1 * time.Minute
    }
}
```

**Results:**
- API Calls: 20 → 1 (95% reduction)
- Cost: $0.20 → $0.05 per dashboard load
- Latency: 800ms vs 2000ms (parallel vs sequential)

---

### Scenario 4: Background Job Processing

**Business Context:**
- Nightly batch job processes 1M records
- Each record requires API enrichment call
- Cost: $0.001 per API call = $1,000 per night
- No strict latency requirements

**Optimization Strategy:**

```go
Approach: Aggressive Batching + Rate Limiting + Caching

Batch Processing Flow:
├─> [1] Batch records into groups of 100
├─> [2] Check cache for each record
│   └─> Cache hit: Skip API call
├─> [3] For cache misses, batch API calls
├─> [4] Apply rate limiting (stay within budget)
└─> [5] Cache results for 24 hours
```

**Implementation:**

```go
type BatchJobOptimizer struct {
    cache         *CacheLayer
    batcher       *BatchProcessor
    rateLimiter   *RateLimiter
}

func (b *BatchJobOptimizer) ProcessRecords(records []*Record) error {
    // [1] Split into batches of 100
    batches := b.splitIntoBatches(records, 100)
    
    for _, batch := range batches {
        // [2] Filter out cached records
        uncached := b.filterCached(batch)
        
        if len(uncached) == 0 {
            // All cached, skip API call
            continue
        }
        
        // [3] Apply rate limiting
        if !b.rateLimiter.AllowBatch(len(uncached)) {
            // Wait before proceeding
            b.rateLimiter.WaitForCapacity(len(uncached))
        }
        
        // [4] Execute batch API call
        enrichedData, err := b.batcher.EnrichBatch(uncached)
        if err != nil {
            return err
        }
        
        // [5] Cache results
        for i, record := range uncached {
            cacheKey := fmt.Sprintf("enrich:%s", record.ID)
            b.cache.Set(cacheKey, enrichedData[i], 24*time.Hour)
        }
    }
    
    return nil
}

func (b *BatchJobOptimizer) filterCached(records []*Record) []*Record {
    var uncached []*Record
    
    for _, record := range records {
        cacheKey := fmt.Sprintf("enrich:%s", record.ID)
        
        if _, found := b.cache.Get(cacheKey); !found {
            uncached = append(uncached, record)
        } else {
            // Use cached data
            record.EnrichedData = b.cache.Get(cacheKey)
        }
    }
    
    return uncached
}

// Intelligent batch size selection
func (b *BatchJobOptimizer) selectOptimalBatchSize(recordCount int) int {
    // Factors to consider:
    // 1. API batch size limit
    // 2. Cost per request
    // 3. Failure blast radius
    // 4. Memory constraints
    
    maxBatchSize := 1000  // API limit
    
    // If many records, use larger batches for efficiency
    if recordCount > 100000 {
        return maxBatchSize
    }
    
    // For smaller jobs, use smaller batches for better failure handling
    if recordCount < 1000 {
        return 50
    }
    
    return 100  // Default
}
```

**Results:**
- Cache hit rate: 70% (recurring records)
- API calls: 1M → 300K (70% reduction)
- Cost: $1,000 → $300 per night
- Processing time: 8 hours → 2 hours (batching efficiency)

---

## 2. Edge Cases & Handling

### Edge Case 1: Cache Stampede

**Problem:**
```
Cache expires at T0
    │
    ├─> T0+1ms: Request 1 arrives → Cache miss → Query API
    ├─> T0+2ms: Request 2 arrives → Cache miss → Query API
    ├─> T0+3ms: Request 3 arrives → Cache miss → Query API
    └─> ... (1000 requests hit expired cache)
    
Result: 1000 simultaneous API calls (expensive!)
```

**Solution: Probabilistic Early Expiration**

```go
type CacheStampedeProtection struct {
    cache         *CacheLayer
    locks         sync.Map  // Request coalescing locks
}

func (c *CacheStampedeProtection) Get(key string) ([]byte, error) {
    // Get value and remaining TTL
    val, ttl, err := c.cache.GetWithTTL(key)
    
    if val == nil {
        // True cache miss - use locking to prevent stampede
        return c.getWithLock(key)
    }
    
    // Check if should trigger early refresh
    if c.shouldRefreshEarly(ttl) {
        // Trigger async refresh (non-blocking)
        go c.refreshCache(key)
    }
    
    // Return current value
    return val, nil
}

func (c *CacheStampedeProtection) shouldRefreshEarly(ttl time.Duration) bool {
    // Probabilistic early expiration
    // As TTL approaches 0, probability of refresh increases
    
    delta := 60 * time.Second  // Beta parameter
    xfetch := -math.Log(rand.Float64()) * float64(delta)
    
    return time.Duration(xfetch) > ttl
}

func (c *CacheStampedeProtection) getWithLock(key string) ([]byte, error) {
    // Try to acquire lock
    lock := &sync.Mutex{}
    actual, loaded := c.locks.LoadOrStore(key, lock)
    lock = actual.(*sync.Mutex)
    
    if loaded {
        // Another goroutine is fetching, wait for it
        lock.Lock()
        defer lock.Unlock()
        
        // Check cache again (should be populated now)
        val, _, _ := c.cache.GetWithTTL(key)
        return val, nil
    }
    
    // We acquired the lock, fetch data
    lock.Lock()
    defer func() {
        lock.Unlock()
        c.locks.Delete(key)
    }()
    
    // Fetch from API
    val, err := c.fetchFromAPI(key)
    if err != nil {
        return nil, err
    }
    
    // Store in cache
    c.cache.Set(key, val, 5*time.Minute)
    
    return val, nil
}
```

---

### Edge Case 2: Partial Batch Failure

**Problem:**
```
Batch Request: [Req1, Req2, Req3, Req4, Req5]
API Response:  [OK, OK, ERROR, OK, ERROR]

What to do with failed items?
- Fail entire batch?
- Return partial results?
- Retry failed items individually?
```

**Solution: Intelligent Failure Handling**

```go
type BatchFailureHandler struct {
    batcher       *BatchProcessor
    retryPolicy   *RetryPolicy
}

func (b *BatchFailureHandler) ExecuteBatch(requests []*Request) ([]*Response, error) {
    // Execute batch
    responses, err := b.batcher.Execute(requests)
    
    // Check for partial failures
    failed := b.extractFailures(responses)
    
    if len(failed) == 0 {
        // All succeeded
        return responses, nil
    }
    
    // Determine failure handling strategy
    if b.shouldRetryIndividually(failed) {
        // Retry failed items individually
        retriedResponses := b.retryIndividually(failed)
        
        // Merge with successful responses
        return b.mergeResponses(responses, retriedResponses), nil
    }
    
    // Fail fast for critical errors
    if b.hasCriticalError(failed) {
        return nil, fmt.Errorf("batch failed with critical error")
    }
    
    // Return partial results
    return b.filterSuccessful(responses), nil
}

func (b *BatchFailureHandler) shouldRetryIndividually(failed []*Response) bool {
    // Retry individually if:
    // 1. Few failures (<20% of batch)
    // 2. Failures are transient (5xx errors)
    // 3. SLA allows time for retry
    
    failureRate := float64(len(failed)) / float64(len(failed) + len(responses))
    
    if failureRate > 0.2 {
        return false  // Too many failures, don't retry
    }
    
    // Check if errors are retryable
    for _, resp := range failed {
        if !b.isRetryable(resp.Error) {
            return false
        }
    }
    
    return true
}

func (b *BatchFailureHandler) retryIndividually(failed []*Response) []*Response {
    var results []*Response
    
    for _, resp := range failed {
        // Retry with exponential backoff
        retried, err := b.retryPolicy.Retry(resp.Request)
        if err == nil {
            results = append(results, retried)
        }
    }
    
    return results
}
```

---

### Edge Case 3: Cache Invalidation Ordering

**Problem:**
```
T0: User updates profile → Event: "user.updated"
T1: Optimizer invalidates cache
T2: Old API response (in-flight) completes
T3: Old data written to cache
T4: User views profile → Sees stale data!

Problem: In-flight request repopulates cache with old data
```

**Solution: Version-Based Cache Invalidation**

```go
type VersionedCache struct {
    cache         *CacheLayer
    versions      sync.Map  // Track entity versions
}

func (v *VersionedCache) Set(key string, value []byte, entityID string) error {
    // Get current version for entity
    currentVersion := v.getVersion(entityID)
    
    // Store with version tag
    versionedKey := fmt.Sprintf("%s:v%d", key, currentVersion)
    return v.cache.Set(versionedKey, value, 5*time.Minute)
}

func (v *VersionedCache) Get(key string, entityID string) ([]byte, bool) {
    // Get current version
    currentVersion := v.getVersion(entityID)
    
    // Lookup versioned key
    versionedKey := fmt.Sprintf("%s:v%d", key, currentVersion)
    val, found := v.cache.Get(versionedKey)
    
    return val, found
}

func (v *VersionedCache) Invalidate(entityID string) {
    // Increment version (invalidates all keys with old version)
    v.versions.LoadOrStore(entityID, 0)
    v.versions.Store(entityID, v.getVersion(entityID)+1)
    
    // Old cached entries become unreachable
}

func (v *VersionedCache) getVersion(entityID string) int {
    ver, _ := v.versions.LoadOrStore(entityID, 0)
    return ver.(int)
}
```

---

### Edge Case 4: Deduplication Window Expiry

**Problem:**
```
T0: Request A arrives → Starts execution
T5: Request B arrives → Attaches to A (dedup)
T100: Request A completes
T105: Request C arrives → Dedup window expired
      → Starts new execution (duplicate work!)
```

**Solution: Soft Deduplication Window**

```go
type SoftDedupEngine struct {
    inFlight      sync.Map
    recentResults *LRUCache  // Cache recent results
}

func (s *SoftDedupEngine) Process(req *Request) (*Response, error) {
    dedupKey := s.generateKey(req)
    
    // [1] Check in-flight requests
    if group, exists := s.inFlight.Load(dedupKey); exists {
        return s.attachToInFlight(group, req)
    }
    
    // [2] Check recent results (soft dedup)
    if result, found := s.recentResults.Get(dedupKey); found {
        // Recent execution completed, reuse result
        return result.(*Response), nil
    }
    
    // [3] Execute new request
    return s.executeNew(req, dedupKey)
}

func (s *SoftDedupEngine) executeNew(req *Request, dedupKey string) (*Response, error) {
    // Create request group
    group := &RequestGroup{
        Leader: req,
    }
    s.inFlight.Store(dedupKey, group)
    
    // Execute
    resp, err := s.executeAPI(req)
    
    // Remove from in-flight
    s.inFlight.Delete(dedupKey)
    
    // Store in recent results (30 second window)
    s.recentResults.Set(dedupKey, resp, 30*time.Second)
    
    return resp, err
}
```

---

## 3. Advanced Optimization Patterns

### Pattern 1: Predictive Pre-fetching

**Concept:** Use ML to predict likely next requests and pre-fetch them.

```go
type PredictivePrefetcher struct {
    predictor     *MLPredictor
    cache         *CacheLayer
    prefetchQueue chan *PrefetchTask
}

type PrefetchTask struct {
    Request    *Request
    Confidence float64
    ExpectedAt time.Time
}

func (p *PredictivePrefetcher) OnRequest(req *Request) {
    // After serving a request, predict what's next
    predictions := p.predictor.PredictNextRequests(req)
    
    for _, pred := range predictions {
        if pred.Confidence > 0.7 {
            // High confidence - prefetch
            task := &PrefetchTask{
                Request:    pred.Request,
                Confidence: pred.Confidence,
                ExpectedAt: time.Now().Add(pred.ExpectedDelay),
            }
            
            p.prefetchQueue <- task
        }
    }
}

func (p *PredictivePrefetcher) processPrefetchQueue() {
    for task := range p.prefetchQueue {
        // Wait until just before expected request time
        time.Sleep(time.Until(task.ExpectedAt.Add(-5 * time.Second)))
        
        // Check if already cached
        cacheKey := p.generateKey(task.Request)
        if p.cache.Exists(cacheKey) {
            continue
        }
        
        // Prefetch
        resp, err := p.executeAPI(task.Request)
        if err != nil {
            continue
        }
        
        // Store in cache
        p.cache.Set(cacheKey, resp, 2*time.Minute)
    }
}

// Example: User browsing pattern prediction
type UserBehaviorPredictor struct {
    model *tensorflow.SavedModel
}

func (u *UserBehaviorPredictor) PredictNextRequests(currentReq *Request) []*Prediction {
    // Example: User viewing product page
    if currentReq.Endpoint == "/api/products/:id" {
        productID := currentReq.PathParams["id"]
        
        // Likely next actions:
        return []*Prediction{
            {
                Request:       createRequest("/api/products/" + productID + "/reviews"),
                Confidence:    0.8,   // 80% of users view reviews
                ExpectedDelay: 5 * time.Second,
            },
            {
                Request:       createRequest("/api/products/related?id=" + productID),
                Confidence:    0.65,  // 65% view related products
                ExpectedDelay: 10 * time.Second,
            },
            {
                Request:       createRequest("/api/cart"),
                Confidence:    0.45,  // 45% add to cart
                ExpectedDelay: 15 * time.Second,
            },
        }
    }
    
    // Use ML model for complex patterns
    features := u.extractFeatures(currentReq)
    predictions := u.model.Predict(features)
    
    return predictions
}
```

---

### Pattern 2: Tiered Caching Strategy

**Concept:** Different cache tiers for different data types and access patterns.

```go
type TieredCache struct {
    l1         *LocalCache      // Hot data (100MB, in-memory)
    l2         *RedisCache      // Warm data (distributed)
    l3         *CDNCache        // Cold data (edge locations)
}

func (t *TieredCache) Get(key string, req *Request) ([]byte, bool) {
    // Classify data tier
    tier := t.classifyDataTier(req)
    
    switch tier {
    case TierHot:
        // Check L1 (fastest)
        if val, found := t.l1.Get(key); found {
            return val, true
        }
        
        // Check L2
        if val, found := t.l2.Get(key); found {
            // Promote to L1
            t.l1.Set(key, val, 1*time.Minute)
            return val, true
        }
        
    case TierWarm:
        // Check L2 directly
        if val, found := t.l2.Get(key); found {
            return val, true
        }
        
    case TierCold:
        // Check L3 (CDN)
        if val, found := t.l3.Get(key); found {
            return val, true
        }
    }
    
    return nil, false
}

func (t *TieredCache) Set(key string, value []byte, req *Request) {
    tier := t.classifyDataTier(req)
    
    switch tier {
    case TierHot:
        // Store in all tiers
        t.l1.Set(key, value, 1*time.Minute)
        t.l2.Set(key, value, 10*time.Minute)
        
    case TierWarm:
        // Store in L2 only
        t.l2.Set(key, value, 30*time.Minute)
        
    case TierCold:
        // Store in CDN (long TTL)
        t.l3.Set(key, value, 24*time.Hour)
    }
}

func (t *TieredCache) classifyDataTier(req *Request) Tier {
    // Factors: access frequency, data size, customer tier
    
    accessFreq := t.getAccessFrequency(req.Endpoint)
    
    if accessFreq > 100 { // requests per second
        return TierHot
    } else if accessFreq > 10 {
        return TierWarm
    } else {
        return TierCold
    }
}
```

---

### Pattern 3: Cost-Aware Request Routing

**Concept:** Route requests to cheapest provider while maintaining quality.

```go
type CostAwareRouter struct {
    providers     []*APIProvider
    costTracker   *CostTracker
    qualityMonitor *QualityMonitor
}

type APIProvider struct {
    Name          string
    Endpoint      string
    CostModel     CostModel
    Latency       time.Duration
    Reliability   float64
    QualityScore  float64
}

type CostModel struct {
    FixedCost     float64  // Per request
    VariableCost  float64  // Per KB
}

func (r *CostAwareRouter) SelectProvider(req *Request) *APIProvider {
    // Calculate expected cost for each provider
    candidates := r.evaluateProviders(req)
    
    // Multi-objective optimization
    best := r.selectBestProvider(candidates, req)
    
    return best
}

func (r *CostAwareRouter) evaluateProviders(req *Request) []*ProviderScore {
    var scores []*ProviderScore
    
    for _, provider := range r.providers {
        score := &ProviderScore{
            Provider: provider,
        }
        
        // Calculate expected cost
        requestSize := float64(len(req.Body)) / 1024.0 // KB
        score.Cost = provider.CostModel.FixedCost +
                     (provider.CostModel.VariableCost * requestSize)
        
        // Latency score (normalized)
        score.Latency = provider.Latency
        
        // Quality score (success rate, data quality)
        score.Quality = provider.QualityScore
        
        // Reliability score
        score.Reliability = provider.Reliability
        
        scores = append(scores, score)
    }
    
    return scores
}

func (r *CostAwareRouter) selectBestProvider(
    candidates []*ProviderScore,
    req *Request,
) *APIProvider {
    // Weighted scoring based on request priority
    
    var weights struct {
        cost        float64
        latency     float64
        quality     float64
        reliability float64
    }
    
    switch req.Context.Priority {
    case PriorityHigh:
        // Prioritize latency and quality
        weights = struct{ cost, latency, quality, reliability float64 }{
            cost:        0.1,
            latency:     0.4,
            quality:     0.3,
            reliability: 0.2,
        }
        
    case PriorityLow:
        // Prioritize cost
        weights = struct{ cost, latency, quality, reliability float64 }{
            cost:        0.6,
            latency:     0.1,
            quality:     0.2,
            reliability: 0.1,
        }
        
    default:
        // Balanced
        weights = struct{ cost, latency, quality, reliability float64 }{
            cost:        0.3,
            latency:     0.3,
            quality:     0.2,
            reliability: 0.2,
        }
    }
    
    // Calculate weighted scores
    var best *APIProvider
    var bestScore float64
    
    for _, candidate := range candidates {
        // Normalize metrics to [0, 1]
        costScore := 1.0 - (candidate.Cost / r.maxCost())
        latencyScore := 1.0 - (float64(candidate.Latency) / float64(r.maxLatency()))
        qualityScore := candidate.Quality
        reliabilityScore := candidate.Reliability
        
        // Weighted sum
        score := (weights.cost * costScore) +
                 (weights.latency * latencyScore) +
                 (weights.quality * qualityScore) +
                 (weights.reliability * reliabilityScore)
        
        if score > bestScore {
            bestScore = score
            best = candidate.Provider
        }
    }
    
    return best
}
```

---

## 4. Failure Scenarios & Recovery

### Scenario 1: Redis Cluster Down

**Failure:** Redis cluster becomes unavailable.

**Detection:**
```go
type CacheHealthCheck struct {
    cache         *RedisCache
    status        atomic.Value  // CacheStatus
}

func (c *CacheHealthCheck) continuousHealthCheck() {
    ticker := time.NewTicker(5 * time.Second)
    
    for range ticker.C {
        err := c.cache.Ping()
        
        if err != nil {
            c.status.Store(CacheStatusDown)
            c.notifyDegraded()
        } else {
            c.status.Store(CacheStatusUp)
        }
    }
}
```

**Recovery:**
```go
func (o *Optimizer) handleCacheFailure(req *Request) (*Response, error) {
    // Graceful degradation: Bypass cache, go directly to API
    
    log.Warn("Cache unavailable, falling back to direct API call")
    
    resp, err := o.executeDirectly(req)
    if err != nil {
        return nil, err
    }
    
    // Track degraded mode cost impact
    o.metrics.RecordDegradedExecution(req)
    
    return resp, nil
}
```

---

### Scenario 2: Batch API Timeout

**Failure:** Batched API call times out, leaving requests hanging.

**Recovery:**
```go
type BatchTimeoutHandler struct {
    batcher       *BatchProcessor
    fallbackExecutor *DirectExecutor
}

func (b *BatchTimeoutHandler) ExecuteBatch(batch *RequestBatch) error {
    // Execute with timeout
    ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
    defer cancel()
    
    resultChan := make(chan *BatchResponse, 1)
    errorChan := make(chan error, 1)
    
    go func() {
        resp, err := b.batcher.Execute(batch)
        if err != nil {
            errorChan <- err
        } else {
            resultChan <- resp
        }
    }()
    
    select {
    case resp := <-resultChan:
        // Success
        b.distributeResponses(batch, resp)
        return nil
        
    case err := <-errorChan:
        // Error
        return b.handleBatchError(batch, err)
        
    case <-ctx.Done():
        // Timeout - fall back to individual execution
        log.Warn("Batch timeout, falling back to individual execution")
        return b.executeFallback(batch)
    }
}

func (b *BatchTimeoutHandler) executeFallback(batch *RequestBatch) error {
    // Execute requests individually
    for _, req := range batch.Requests {
        go func(r *Request) {
            resp, err := b.fallbackExecutor.Execute(r)
            // Send response to waiting goroutine
            r.ResponseChan <- resp
        }(req)
    }
    
    return nil
}
```

---

This document covers real-world scenarios, edge cases, advanced patterns, and failure handling strategies. Each scenario includes practical implementation examples that you can adapt to your specific use case!








