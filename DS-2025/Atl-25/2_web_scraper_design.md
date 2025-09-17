# Distributed Web Scraper Service - Staff Engineer Design

## Problem Statement
Design a scalable web scraping service that can handle multiple concurrent jobs, extract content (images, links, metadata) from web pages, support recursive crawling with configurable depth, and provide real-time job monitoring.

## Requirements (~5 minutes)

### Functional Requirements
1. **Job Management**: Users should be able to submit scraping jobs with multiple seed URLs and configurable parameters (depth, delays, content types)
2. **Content Extraction**: System should extract images, links, text content, and metadata from web pages with configurable selectors
3. **Recursive Crawling**: System should follow links up to specified depth with intelligent cycle detection and domain filtering
4. **Job Monitoring**: Users should be able to track job progress in real-time, view statistics, pause/resume jobs, and retrieve results
5. **Result Storage & Export**: System should store extracted content with searchable metadata and support multiple export formats (JSON, CSV, XML)
6. **Politeness Controls**: Respect robots.txt, implement configurable delays, rate limiting, and domain-specific crawling policies

### Non-Functional Requirements
1. **Scalability**: Handle 10K+ concurrent scraping jobs processing 1M+ URLs per day across multiple regions
2. **Reliability**: 99.5% success rate for accessible URLs with comprehensive error handling and retry mechanisms
3. **Performance**: 
   - Process 1000+ URLs/hour per worker node
   - Job queue latency < 5 seconds
   - Result retrieval < 2 seconds for typical job sizes
4. **Politeness**: Configurable delays (100ms-30s), respect Crawl-Delay directives, implement exponential backoff
5. **Storage Efficiency**: Handle TB-scale extracted content with compression and intelligent deduplication
6. **Security**: Support authentication, proxy rotation, and protection against malicious content

### Capacity Estimation
**Critical calculations that drive architecture decisions**:
- **Peak Concurrent Jobs**: 10K jobs × 100 URLs average = 1M URLs in active processing
- **Worker Scaling**: Target 1K URLs/hour/worker → Need ~1K workers for 1M URLs/hour throughput
- **Storage Growth**: 50MB average content per job × 10K jobs/day = 500GB daily growth
- **Queue Depth**: During peak hours, expect 100K URLs queued across all jobs

## Core Entities (~2 minutes)
- **ScrapingJob**: Contains job configuration, status, progress tracking, and result metadata
- **UrlTask**: Individual URL processing unit with state, retry count, and extraction results
- **ExtractedContent**: Processed content including HTML, images, links, and structured metadata
- **CrawlPolicy**: Domain-specific rules for delays, allowed patterns, and extraction configuration
- **JobResult**: Aggregated and exportable results with filtering and search capabilities

## API Design (~5 minutes)

### Protocol Choice
**REST** for job management and configuration, **WebSocket** for real-time progress updates, **GraphQL** for complex result queries with flexible filtering.

```http
# Job Management
POST /v1/scraping/jobs
Body: {
  "name": "E-commerce Product Scraping",
  "urls": ["https://example-store.com/products"],
  "config": {
    "max_depth": 3,
    "max_pages": 5000,
    "respect_robots": true,
    "delay_ms": 1000,
    "timeout_ms": 30000,
    "user_agent": "MyBot/1.0",
    "content_types": ["images", "links", "text", "metadata"],
    "allowed_domains": ["example-store.com"],
    "extraction_rules": {
      "product_title": "h1.product-title",
      "price": ".price-current",
      "images": "img.product-image"
    }
  }
}
Response: {
  "job_id": "job_uuid_123",
  "status": "queued",
  "estimated_start": "2025-01-01T12:05:00Z"
}

# Job Control
GET /v1/scraping/jobs/{job_id}
PUT /v1/scraping/jobs/{job_id}/pause
PUT /v1/scraping/jobs/{job_id}/resume
DELETE /v1/scraping/jobs/{job_id}

# Results & Export
GET /v1/scraping/jobs/{job_id}/results?format=json&filter=status:success&page=1&limit=100
GET /v1/scraping/jobs/{job_id}/export?format=csv&include=images,metadata
GET /v1/scraping/jobs/{job_id}/stats

# Real-time Updates
WebSocket: /v1/scraping/jobs/{job_id}/stream
Messages: {
  "type": "progress_update",
  "data": {
    "processed": 1250,
    "total": 5000,
    "success_rate": 0.94,
    "current_url": "https://example.com/page/125",
    "eta": "2025-01-01T14:30:00Z"
  }
}

# GraphQL for Complex Queries
query JobResults($jobId: ID!, $filters: ResultFilters!) {
  scrapingJob(id: $jobId) {
    id
    status
    results(filters: $filters) {
      url
      extractedData {
        title
        images {
          src
          alt
          size
        }
        customFields
      }
      metadata {
        responseTime
        statusCode
        contentType
      }
    }
    analytics {
      domainDistribution
      errorsByType
      performanceMetrics
    }
  }
}
```

## High Level Design (~10-15 minutes)

```
                    ┌─────────────────┐
                    │   Load Balancer │
                    │   (nginx/HAProxy)│
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │   API Gateway   │
                    │ (Authentication,│
                    │ Rate Limiting,  │
                    │ Request Routing)│
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │  Job Scheduler  │
                    │   Service       │
                    └─────────┬───────┘
                              │
                    ┌─────────▼───────┐
                    │  Message Queue  │
                    │ (Apache Kafka)  │
                    │ ┌─────────────┐ │
                    │ │Priority     │ │
                    │ │Partitioning │ │
                    │ └─────────────┘ │
                    └─────────┬───────┘
                              │
         ┌────────────────────┼────────────────────┐
         │                    │                    │
   ┌─────▼─────┐        ┌─────▼─────┐        ┌─────▼─────┐
   │ Worker    │        │ Worker    │        │ Worker    │
   │ Pool 1    │        │ Pool 2    │        │ Pool N    │
   │┌─────────┐│        │┌─────────┐│        │┌─────────┐│
   ││Selenium ││        ││Headless ││        ││Mobile   ││
   ││Chrome   ││        ││Chromium ││        ││Emulator ││
   │└─────────┘│        │└─────────┘│        │└─────────┘│
   └─────┬─────┘        └─────┬─────┘        └─────┬─────┘
         │                    │                    │
         └────────────────────┼────────────────────┘
                              │
                    ┌─────────▼───────┐
                    │  Storage Layer  │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │ PostgreSQL  │ │ ← Job metadata,
                    │ │ (Primary)   │ │   configuration
                    │ └─────────────┘ │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │ Cassandra   │ │ ← URL tasks,
                    │ │ (Time-series│ │   crawl results
                    │ │  Optimized) │ │
                    │ └─────────────┘ │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │Object Store │ │ ← Extracted content,
                    │ │(S3/MinIO)   │ │   images, documents
                    │ └─────────────┘ │
                    │                 │
                    │ ┌─────────────┐ │
                    │ │Elasticsearch│ │ ← Search index,
                    │ │   + Redis   │ │   result caching
                    │ └─────────────┘ │
                    └─────────────────┘
```

### Data Flow Examples

**Job Submission Flow**:
1. User submits job → API Gateway (auth/validation) → Job Scheduler Service
2. Job Scheduler creates job record → PostgreSQL → Generates URL tasks
3. URL tasks published → Kafka (partitioned by domain) → Workers consume
4. Real-time job status → WebSocket connections for live updates

**URL Processing Flow**:
1. Worker receives URL task → Applies crawl policies → Fetches content
2. Content extraction using configured rules → Stores raw content (S3)
3. Structured data → Cassandra → Search index → Elasticsearch
4. Progress update → Kafka → Job status aggregation → WebSocket broadcast

**Result Retrieval Flow**:
1. User requests results → Check Redis cache → If miss, query Elasticsearch
2. Complex queries → PostgreSQL + Cassandra joins → Aggregate and cache
3. Export requests → Background job → Generate file → S3 → Download link

## Deep Dives (~10 minutes)

### Deep Dive 1: Scalable Queue Architecture

#### Message Queue Technology Selection
**Apache Kafka - Why Chosen**:
- **High Throughput**: Handle 1M+ messages/second across partitions
- **Durability**: Configurable replication and persistence for job reliability
- **Partitioning**: Natural load distribution by domain for politeness controls
- **Stream Processing**: Built-in support for real-time analytics and monitoring

**Alternative Analysis**:
- **RabbitMQ**: Better for complex routing but limited throughput scalability
- **Redis Streams**: Simpler deployment but lacks advanced partitioning
- **Amazon SQS**: Managed service but potential vendor lock-in and cost at scale

**Queue Design Pattern**:
```python
class ScrapingQueueManager:
    def __init__(self):
        self.priority_topics = {
            'urgent': 'scraping-urgent',    # < 100 URLs, SLA: 5 minutes
            'standard': 'scraping-standard', # 100-1000 URLs, SLA: 1 hour  
            'batch': 'scraping-batch'       # > 1000 URLs, SLA: 4 hours
        }
        
    def partition_by_domain(self, url):
        """Ensure same domain tasks go to same partition for politeness"""
        domain = extract_domain(url)
        return hash(domain) % self.num_partitions
        
    def publish_task(self, url_task):
        priority = self.determine_priority(url_task.job_config)
        partition = self.partition_by_domain(url_task.url)
        
        kafka_producer.send(
            topic=self.priority_topics[priority],
            value=url_task.serialize(),
            partition=partition,
            headers={'job_id': url_task.job_id}
        )
```

**Dead Letter Queue Strategy**:
- Failed tasks after 3 retries → DLQ for manual investigation
- Automated analysis of failure patterns → Dynamic blacklist updates
- Exponential backoff with jitter for temporary failures

### Deep Dive 2: Worker Node Architecture & Scaling

#### Worker Pool Design
**Multi-Browser Strategy**:
```python
class WorkerNodeManager:
    def __init__(self):
        self.browser_pools = {
            'headless_chrome': ChromePool(size=10),    # Fast, standard content
            'full_chrome': FullChromePool(size=3),     # JavaScript-heavy sites
            'mobile_chrome': MobileChromePool(size=2), # Mobile-specific content
            'requests_only': RequestsPool(size=20)     # Static content only
        }
    
    def select_browser_type(self, url_task):
        """Intelligent browser selection based on site characteristics"""
        if url_task.requires_javascript:
            return 'full_chrome'
        elif url_task.mobile_specific:
            return 'mobile_chrome'
        elif self.is_static_content(url_task.url):
            return 'requests_only'
        else:
            return 'headless_chrome'
```

**Auto-scaling Strategy**:
- **Horizontal Pod Autoscaler**: Scale based on Kafka consumer lag
- **Custom Metrics**: Queue depth per priority level, average processing time
- **Resource Limits**: CPU/memory limits with quality-of-service guarantees
- **Graceful Shutdown**: Complete current tasks before termination (max 5 minutes)

#### Politeness Implementation
**Domain-Level Rate Limiting**:
```python
class PolitenessController:
    def __init__(self):
        self.domain_limiters = {}  # Token bucket per domain
        self.robots_cache = RedisCache(ttl=3600)
        
    async def can_fetch_url(self, url):
        domain = extract_domain(url)
        
        # Check robots.txt compliance
        robots_rules = await self.get_robots_rules(domain)
        if not robots_rules.can_fetch(url, user_agent='*'):
            return False
            
        # Apply rate limiting
        limiter = self.get_domain_limiter(domain)
        return await limiter.acquire()
    
    def get_domain_limiter(self, domain):
        """Token bucket rate limiter per domain"""
        if domain not in self.domain_limiters:
            # Default: 1 request per second, burst of 5
            self.domain_limiters[domain] = TokenBucket(
                rate=1.0, 
                burst=5,
                redis_key=f"rate_limit:{domain}"
            )
        return self.domain_limiters[domain]
```

**Retry Strategy with Circuit Breaker**:
- Exponential backoff: 1s, 2s, 4s, 8s (max 3 retries)
- Circuit breaker per domain: Open after 10 consecutive failures
- Automatic recovery: Half-open state after 10 minutes

### Deep Dive 3: Content Storage & Processing Strategy

#### Multi-Tier Storage Architecture
**Storage Decision Matrix**:
```python
class StorageStrategy:
    def route_content(self, extracted_content):
        content_size = len(extracted_content.raw_html)
        content_type = extracted_content.content_type
        
        # Hot tier: Recent jobs, frequently accessed
        if self.is_recent_job(extracted_content.job_id):
            return self.store_hot_tier(extracted_content)
            
        # Warm tier: Completed jobs, occasional access
        elif content_size < 10_MB and content_type in ['text/html', 'application/json']:
            return self.store_warm_tier(extracted_content)
            
        # Cold tier: Large content, archive access
        else:
            return self.store_cold_tier(extracted_content)
```

**Storage Tier Implementation**:
1. **Hot Tier (Redis + SSD)**: Active job results, < 30 days
2. **Warm Tier (S3 Standard)**: Completed jobs, structured access
3. **Cold Tier (S3 Glacier)**: Historical data, archive retrieval

**Content Deduplication Strategy**:
```python
class ContentDeduplicator:
    def __init__(self):
        self.bloom_filter = BloomFilter(capacity=10_000_000, error_rate=0.001)
        self.content_hashes = RedisSet('content_hashes')
        
    def is_duplicate_content(self, content):
        # Fast bloom filter check (may have false positives)
        content_hash = sha256(content.text.encode()).hexdigest()
        
        if content_hash not in self.bloom_filter:
            self.bloom_filter.add(content_hash)
            return False
            
        # Exact check for potential duplicates
        return self.content_hashes.exists(content_hash)
        
    def store_unique_content(self, content):
        if not self.is_duplicate_content(content):
            content_hash = self.generate_content_hash(content)
            self.content_hashes.add(content_hash)
            return self.storage.save(content, hash=content_hash)
        else:
            return self.get_existing_content_reference(content)
```

### Deep Dive 4: Content Extraction & Processing Pipeline

#### Intelligent Content Extraction
**Multi-Strategy Extraction**:
```python
class ContentExtractor:
    def __init__(self):
        self.extractors = [
            StructuredDataExtractor(),  # JSON-LD, microdata
            XPathExtractor(),          # Custom XPath rules
            ReadabilityExtractor(),    # Main content extraction
            GenericExtractor()         # Fallback extraction
        ]
        
    def extract_content(self, html, extraction_rules):
        results = {}
        
        for field_name, selector in extraction_rules.items():
            for extractor in self.extractors:
                try:
                    value = extractor.extract(html, selector)
                    if value and self.validate_extraction(value, field_name):
                        results[field_name] = value
                        break
                except ExtractionError:
                    continue
                    
        return results
        
    def validate_extraction(self, value, field_name):
        """Validate extracted content based on field type"""
        validators = {
            'price': self.validate_price,
            'email': self.validate_email,
            'date': self.validate_date,
            'url': self.validate_url
        }
        
        validator = validators.get(field_name, lambda x: True)
        return validator(value)
```

**Image Processing Pipeline**:
- Download optimization: WebP conversion, size optimization
- Metadata extraction: EXIF data, dimensions, file size
- Duplicate detection: Perceptual hashing (pHash) for near-duplicates
- Storage: CDN integration for fast image serving

### Deep Dive 5: Real-time Monitoring & Analytics

#### Comprehensive Observability Stack
**Metrics Collection**:
```python
class ScrapingMetrics:
    def __init__(self):
        self.metrics = {
            # Performance metrics
            'urls_processed_per_second': Counter(),
            'extraction_latency': Histogram(buckets=[0.1, 0.5, 1, 2, 5, 10]),
            'queue_depth': Gauge(),
            
            # Quality metrics  
            'success_rate_by_domain': Counter(),
            'content_extraction_accuracy': Histogram(),
            'duplicate_detection_rate': Counter(),
            
            # Resource metrics
            'worker_cpu_utilization': Gauge(),
            'memory_usage_by_job': Histogram(),
            'storage_growth_rate': Counter()
        }
        
    def record_url_processed(self, url, processing_time, success):
        domain = extract_domain(url)
        self.metrics['urls_processed_per_second'].inc()
        self.metrics['extraction_latency'].observe(processing_time)
        self.metrics['success_rate_by_domain'].labels(domain=domain, status='success' if success else 'failure').inc()
```

**Alerting Strategy**:
```yaml
Critical Alerts (Immediate Response):
  - success_rate < 80% for 5 minutes
  - queue_depth > 100,000 URLs
  - worker_failure_rate > 10%
  - storage_service_unavailable

Warning Alerts (15-minute Response):
  - avg_processing_time > 30 seconds
  - duplicate_rate > 50%
  - memory_usage > 80%
  - robots_txt_violation_rate > 5%
```

**Real-time Dashboard Components**:
- Live job progress with ETA calculations
- Worker health and resource utilization
- Domain-specific performance metrics
- Content quality and extraction accuracy
- Cost analysis and resource optimization insights

### Deep Dive 6: Security & Compliance

#### Security Architecture
**Content Sanitization**:
```python
class SecurityLayer:
    def __init__(self):
        self.content_scanner = MalwareScanner()
        self.data_classifier = DataClassifier()
        
    def sanitize_content(self, raw_content):
        # Malware scanning
        if self.content_scanner.is_malicious(raw_content):
            raise SecurityException("Malicious content detected")
            
        # PII detection and redaction
        classified_content = self.data_classifier.classify(raw_content)
        if classified_content.contains_pii:
            raw_content = self.redact_pii(raw_content)
            
        # HTML sanitization
        clean_html = bleach.clean(raw_content.html, tags=ALLOWED_TAGS)
        
        return clean_html
```

**Proxy Rotation & IP Management**:
- Rotating proxy pools with health monitoring
- Geographic distribution for region-specific content
- IP reputation monitoring and automatic rotation
- Rate limiting enforcement across proxy pools

**Compliance Framework**:
- GDPR compliance for EU-based content
- Robots.txt respect with override capabilities for authorized testing
- Copyright-aware content handling with metadata preservation
- Data retention policies with automated cleanup

This design demonstrates staff-level engineering thinking through comprehensive trade-off analysis, detailed scalability considerations, and production-ready operational practices.
