# Detailed Database Schema Design for Jira-like System

## Core Tables and Their Design Rationale

### 1. Issues Table
```sql
CREATE TABLE issues (
    id BIGSERIAL PRIMARY KEY,
    key VARCHAR(255) NOT NULL,              -- Project-specific identifier (e.g., PROJ-123)
    project_id BIGINT REFERENCES projects(id),
    type VARCHAR(50),                       -- Story, Bug, Task, Epic
    status VARCHAR(50),                     -- Open, In Progress, Done
    priority VARCHAR(20),                   -- P0, P1, P2, P3
    summary TEXT NOT NULL,
    description TEXT,
    reporter_id BIGINT REFERENCES users(id),
    assignee_id BIGINT REFERENCES users(id),
    epic_id BIGINT REFERENCES issues(id),   -- For hierarchy
    sprint_id BIGINT REFERENCES sprints(id),
    story_points DECIMAL(5,2),              -- For agile estimation
    original_estimate_minutes INTEGER,
    remaining_estimate_minutes INTEGER,
    labels TEXT[],                          -- Array of labels for flexible categorization
    custom_fields JSONB,                    -- Extensible fields storage
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    resolution_date TIMESTAMP WITH TIME ZONE,
    due_date TIMESTAMP WITH TIME ZONE,
    environment TEXT,                       -- For bug reports
    version_affected VARCHAR(100)[],        -- Array of affected versions
    version_fixed VARCHAR(100)[],           -- Array of versions where fix is available
    UNIQUE(project_id, key)
);

-- Reasoning for key decisions:
-- 1. BIGSERIAL for id: Supports large number of issues (billions)
-- 2. JSONB for custom_fields: Flexible schema evolution without migrations
-- 3. Array types for labels/versions: Efficient querying of multiple values
-- 4. Timestamps with timezone: Global team support
-- 5. Separate estimate fields: Track original vs remaining work

CREATE INDEX idx_issues_project_status ON issues(project_id, status);
CREATE INDEX idx_issues_assignee ON issues(assignee_id);
CREATE INDEX idx_issues_sprint ON issues(sprint_id);
CREATE INDEX idx_issues_created_at ON issues(created_at);
CREATE INDEX idx_issues_labels ON issues USING gin(labels);
CREATE INDEX idx_issues_custom_fields ON issues USING gin(custom_fields);
```

### 2. Projects Table
```sql
CREATE TABLE projects (
    id BIGSERIAL PRIMARY KEY,
    key VARCHAR(10) NOT NULL UNIQUE,        -- Short identifier like 'PROJ'
    name VARCHAR(255) NOT NULL,
    description TEXT,
    lead_id BIGINT REFERENCES users(id),
    category_id BIGINT REFERENCES project_categories(id),
    workflow_scheme_id BIGINT REFERENCES workflow_schemes(id),
    permission_scheme_id BIGINT REFERENCES permission_schemes(id),
    issue_type_scheme_id BIGINT REFERENCES issue_type_schemes(id),
    default_assignee_id BIGINT REFERENCES users(id),
    is_private BOOLEAN DEFAULT false,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    archived_at TIMESTAMP WITH TIME ZONE,
    settings JSONB,                         -- Project-specific settings
    CONSTRAINT valid_key CHECK (key ~ '^[A-Z][A-Z0-9]+$')
);

-- Reasoning:
-- 1. Separate scheme IDs: Enables flexible workflow/permission management
-- 2. JSONB settings: Allows project-specific configurations
-- 3. Key constraint: Ensures valid project keys
```

### 3. Workflows Table
```sql
CREATE TABLE workflows (
    id BIGSERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    status_config JSONB NOT NULL,           -- Available statuses and their properties
    transitions JSONB NOT NULL,             -- State machine definition
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    version INTEGER DEFAULT 1,              -- For workflow versioning
    is_draft BOOLEAN DEFAULT false,         -- Support draft workflows
    published_at TIMESTAMP WITH TIME ZONE,
    UNIQUE(name, version)
);

-- Reasoning:
-- 1. JSONB for flexible workflow definitions
-- 2. Version tracking for workflow evolution
-- 3. Draft support for workflow testing
```

### 4. Comments Table
```sql
CREATE TABLE comments (
    id BIGSERIAL PRIMARY KEY,
    issue_id BIGINT REFERENCES issues(id),
    author_id BIGINT REFERENCES users(id),
    content TEXT NOT NULL,
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    parent_id BIGINT REFERENCES comments(id),  -- For threaded comments
    is_internal BOOLEAN DEFAULT false,         -- For internal notes
    attachment_ids BIGINT[],                   -- Related attachments
    mentioned_users BIGINT[],                  -- For @mentions
    reactions JSONB                            -- Store emoji reactions
);

CREATE INDEX idx_comments_issue ON comments(issue_id);
CREATE INDEX idx_comments_created ON comments(created_at);
```

### 5. Attachments Table
```sql
CREATE TABLE attachments (
    id BIGSERIAL PRIMARY KEY,
    issue_id BIGINT REFERENCES issues(id),
    uploader_id BIGINT REFERENCES users(id),
    filename VARCHAR(255) NOT NULL,
    file_size BIGINT NOT NULL,
    content_type VARCHAR(255),
    storage_path TEXT NOT NULL,             -- S3 or similar storage path
    thumbnail_path TEXT,                    -- For image previews
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    deleted_at TIMESTAMP WITH TIME ZONE,    -- Soft delete support
    metadata JSONB                          -- For extra file information
);

CREATE INDEX idx_attachments_issue ON attachments(issue_id);
```

### 6. Issue History Table
```sql
CREATE TABLE issue_history (
    id BIGSERIAL PRIMARY KEY,
    issue_id BIGINT REFERENCES issues(id),
    author_id BIGINT REFERENCES users(id),
    field_name VARCHAR(255) NOT NULL,       -- What changed
    old_value TEXT,                         -- Previous value
    new_value TEXT,                         -- New value
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    change_type VARCHAR(50) NOT NULL,       -- Type of change (update, workflow, etc.)
    additional_context JSONB                -- Extra change context
);

CREATE INDEX idx_history_issue ON issue_history(issue_id);
CREATE INDEX idx_history_created ON issue_history(created_at);
```

### 7. Sprint Table
```sql
CREATE TABLE sprints (
    id BIGSERIAL PRIMARY KEY,
    project_id BIGINT REFERENCES projects(id),
    name VARCHAR(255) NOT NULL,
    goal TEXT,
    start_date TIMESTAMP WITH TIME ZONE,
    end_date TIMESTAMP WITH TIME ZONE,
    completed_date TIMESTAMP WITH TIME ZONE,
    status VARCHAR(50) DEFAULT 'PENDING',   -- PENDING, ACTIVE, COMPLETED
    created_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP,
    metrics JSONB                          -- Sprint metrics/velocity
);
```

## Performance Optimization Strategies

### 1. Partitioning
```sql
-- Partition issues by project_id
CREATE TABLE issues_partition OF issues
PARTITION BY HASH (project_id);

-- Time-based partitioning for history
CREATE TABLE issue_history_partition OF issue_history
PARTITION BY RANGE (created_at);
```

### 2. Materialized Views
```sql
-- For project statistics
CREATE MATERIALIZED VIEW project_stats AS
SELECT 
    project_id,
    COUNT(*) as total_issues,
    COUNT(CASE WHEN status = 'OPEN' THEN 1 END) as open_issues,
    AVG(EXTRACT(EPOCH FROM (resolution_date - created_at))) as avg_resolution_time
FROM issues
GROUP BY project_id;
```

### 3. Caching Considerations
- Cache issue counts by status
- Cache recent comments
- Cache user permissions
- Cache project metadata

## Key Design Decisions

1. **Use of JSONB**
   - Pros: Schema flexibility, queryable
   - Cons: Less structured, potential for mess
   - Used for: Custom fields, workflow definitions, metadata

2. **Timestamp with Time Zone**
   - Reasoning: Global teams, accurate timing
   - Impact: Consistent time handling

3. **Soft Deletes**
   - Why: Data recovery, audit trails
   - How: deleted_at timestamp

4. **Array Types**
   - Use: Labels, versions, attachments
   - Benefit: Efficient querying, reduced joins

5. **Indexing Strategy**
   - Composite indexes for common queries
   - GIN indexes for array/JSONB fields
   - Partial indexes for active records
