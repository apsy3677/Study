# TDD Problem Solving Prompt for Atlassian Interview Questions

## Overview
This prompt guides you through solving complex data structure and system design problems using Test-Driven Development (TDD), following the patterns demonstrated in successful Atlassian interview solutions.

---

## TDD Problem-Solving Framework

### **Phase 1: Problem Analysis & Understanding (5-7 minutes)**

#### 1.1 Problem Decomposition
```
Given a problem statement, extract:
□ Core Requirements (what must the system do?)
□ Scale-up Requirements (what additional features?)
□ Performance Constraints (time/space complexity expectations?)
□ Edge Cases (empty inputs, duplicates, out-of-order data?)
□ Interface Requirements (specific method signatures?)
```

#### 1.2 Solution Approach Template
```cpp
/*
 * Atlassian Interview: [PROBLEM_NAME]
 * 
 * PROBLEM STATEMENT:
 * [Clearly restate the problem in your own words]
 * 
 * Requirements:
 * - [Basic requirement 1]
 * - [Basic requirement 2]
 * - [Scale-up requirement 1]
 * - [Scale-up requirement 2]
 * 
 * SOLUTION APPROACH:
 * 1. Data Structure Choice: [Why this structure?]
 * 2. Algorithm Strategy: [High-level approach]
 * 3. Optimization Strategy: [How to achieve required performance]
 * 4. Edge Case Handling: [Special scenarios]
 * 5. Scale-up Implementation: [How to extend for advanced features]
 * 
 * Time Complexity: O(?) for [operations]
 * Space Complexity: O(?)
 */
```

### **Phase 2: Test Case Design (5-8 minutes)**

#### 2.1 Test Categories Framework
Based on the solution patterns, design tests for:

```cpp
// 1. BASIC FUNCTIONALITY TESTS
void testBasicOperations() {
    // Test core functionality with simple inputs
    // Verify basic interface works as expected
}

// 2. EDGE CASE TESTS  
void testEdgeCases() {
    // Empty inputs, single elements, boundary conditions
    // Invalid inputs, error handling
}

// 3. SCALE-UP FEATURE TESTS
void testAdvancedFeatures() {
    // Test each scale-up requirement independently
    // Verify advanced features work correctly
}

// 4. PERFORMANCE & STRESS TESTS
void testPerformanceScenarios() {
    // Large datasets, worst-case scenarios
    // Time complexity validation
}

// 5. INTEGRATION TESTS
void testComplexScenarios() {
    // Multiple features working together
    // Real-world usage patterns
}
```

#### 2.2 Test Data Strategy
```cpp
// Pattern: Start simple, build complexity
vector<TestData> generateTestCases() {
    return {
        // Basic cases
        {"single_element", {1}, "expected_result"},
        {"two_elements", {1, 2}, "expected_result"},
        
        // Edge cases  
        {"empty_input", {}, "expected_result"},
        {"duplicate_elements", {1, 1, 1}, "expected_result"},
        
        // Complex cases
        {"large_dataset", generateLargeData(1000), "expected_result"},
        {"worst_case_scenario", generateWorstCase(), "expected_result"}
    };
}
```

### **Phase 3: Core Implementation (20-25 minutes)**

#### 3.1 Data Structure Selection Guide
```cpp
// SELECTION CRITERIA:
// □ Frequent lookups → unordered_map/unordered_set
// □ Ordered traversal → map/set  
// □ Range queries → map with lower_bound/upper_bound
// □ Efficient insertion/deletion at ends → deque
// □ Priority-based access → priority_queue
// □ Dynamic min/max tracking → set/multiset
// □ Fixed-size optimization → vector with custom logic

class SolutionClass {
private:
    // PRIMARY DATA STRUCTURES
    unordered_map<KeyType, ValueType> primaryIndex;  // O(1) lookup
    map<OrderedKeyType, DataType> orderedData;       // O(log n) ordered access
    set<ValueType> uniqueValues;                     // O(log n) sorted unique values
    
    // OPTIMIZATION STRUCTURES
    CachedValueType cachedResult;                    // O(1) frequent queries
    bool needsRecalculation;                         // Lazy evaluation flag
    
public:
    // INTERFACE METHODS (implement these first)
    void primaryOperation(InputType input);
    ResultType getResult();
    
    // SCALE-UP METHODS (implement after basic works)
    void advancedOperation(AdvancedInputType input);
    AdvancedResultType getAdvancedResult();
};
```

#### 3.2 Implementation Pattern
```cpp
// STEP 1: Basic operations that pass simple tests
void implementBasicVersion() {
    // Focus on correctness, not optimization
    // Use straightforward algorithms
    // Ensure all basic tests pass
}

// STEP 2: Add edge case handling
void addEdgeCaseHandling() {
    // Input validation
    // Empty container handling  
    // Boundary condition checks
    // Error state management
}

// STEP 3: Performance optimization
void optimizeForPerformance() {
    // Replace O(n) operations with O(log n) or O(1)
    // Add caching for frequently accessed data
    // Implement lazy evaluation where beneficial
}

// STEP 4: Scale-up features
void implementAdvancedFeatures() {
    // Add each scale-up requirement incrementally
    // Ensure backward compatibility
    // Test each feature independently
}
```

### **Phase 4: Optimization & Scale-up (15-20 minutes)**

#### 4.1 Performance Optimization Checklist
```cpp
// COMMON OPTIMIZATION PATTERNS FROM SOLUTIONS:

// 1. CACHING PATTERN (Popular Content, Commodity Prices)
class CachedSolution {
private:
    mutable CacheType cache;
    mutable bool cacheValid;
    
    void invalidateCache() { cacheValid = false; }
    void updateCache() const {
        if (!cacheValid) {
            cache = computeExpensiveResult();
            cacheValid = true;
        }
    }
};

// 2. DUAL DATA STRUCTURE PATTERN (Customer Satisfaction)
class DualIndexSolution {
private:
    unordered_map<ID, Data> primaryIndex;     // Fast ID lookup
    map<Priority, set<ID>> priorityIndex;     // Fast priority-based queries
    
    void updateBothIndexes(ID id, Data oldData, Data newData);
};

// 3. HIERARCHICAL ORGANIZATION (Snake Game, Router)
class HierarchicalSolution {
private:
    struct Node {
        unordered_map<Key, Node*> children;
        optional<Value> value;
        Node* wildcardChild;
        Node* parameterChild;
    };
};
```

#### 4.2 Scale-up Implementation Strategy
```cpp
// INCREMENTAL FEATURE ADDITION:

// Level 0: Basic functionality
class BasicSolution {
    // Core features only
};

// Level 1: Add first scale-up
class Level1Solution : public BasicSolution {
    // Add feature 1 with minimal changes to base
};

// Level 2: Add second scale-up  
class Level2Solution : public Level1Solution {
    // Add feature 2, ensure compatibility with Level 1
};

// Advanced: Full-featured solution
class AdvancedSolution {
    // All features integrated optimally
    // May require refactoring for best performance
};
```

### **Phase 5: Testing & Validation (8-10 minutes)**

#### 5.1 Comprehensive Testing Pattern
```cpp
int main() {
    // RUN TESTS IN ORDER OF COMPLEXITY
    cout << "=== BASIC FUNCTIONALITY TESTS ===" << endl;
    testBasicOperations();
    
    cout << "=== EDGE CASE TESTS ===" << endl;
    testEdgeCases();
    
    cout << "=== SCALE-UP FEATURE TESTS ===" << endl;
    testScaleUpFeatures();
    
    cout << "=== PERFORMANCE TESTS ===" << endl;
    testPerformanceScenarios();
    
    cout << "=== INTEGRATION TESTS ===" << endl;
    testComplexScenarios();
    
    cout << "=== ALL TESTS PASSED ===" << endl;
    return 0;
}
```

#### 5.2 Test Validation Checklist
```cpp
// VERIFY EACH TEST:
□ Does it test exactly one concept?
□ Does it have clear expected output?
□ Does it cover both positive and negative cases?
□ Does it validate performance requirements?
□ Does it test error handling?
□ Does it verify scale-up features work independently?
```

---

## Problem-Specific Application Examples

### **Example 1: Stream Processing Problem**
```cpp
// Given: Stream of data with operations
// Apply Framework:
// 1. Identify: Need real-time updates + queries
// 2. Data Structure: unordered_map + multiset for dual indexing
// 3. Tests: empty stream, single item, duplicates, large stream
// 4. Optimization: Cache most frequent query result
// 5. Scale-up: Add categories, time windows, statistics
```

### **Example 2: Routing/Matching Problem**  
```cpp
// Given: Path matching with wildcards/parameters
// Apply Framework:
// 1. Identify: Prefix matching + parameter extraction
// 2. Data Structure: Trie with special nodes for wildcards/params
// 3. Tests: exact match, wildcards, parameters, conflicts
// 4. Optimization: Ordered checking, priority rules
// 5. Scale-up: Middleware, advanced patterns, performance
```

### **Example 3: Tracking/Analytics Problem**
```cpp
// Given: Track entities with rankings/statistics  
// Apply Framework:
// 1. Identify: Updates + ranked queries + time-based analysis
// 2. Data Structure: maps for tracking + sets for ranking
// 3. Tests: single entity, ties, time periods, exports
// 4. Optimization: Smart ranking updates, cached calculations
// 5. Scale-up: Multiple metrics, export formats, categories
```

---

## Time Management Strategy

| Phase | Time Allocation | Focus |
|-------|----------------|-------|
| Problem Analysis | 5-7 minutes | Understand completely before coding |
| Test Design | 5-8 minutes | Design comprehensive test cases |
| Core Implementation | 20-25 minutes | Basic functionality + edge cases |
| Optimization & Scale-up | 15-20 minutes | Performance + advanced features |
| Testing & Validation | 8-10 minutes | Verify all requirements met |
| **Total** | **53-70 minutes** | **Allows buffer for discussion** |

---

## Key Success Patterns

### **1. Progressive Complexity**
- Start with simplest possible solution that works
- Add one feature at a time
- Test each addition before moving forward
- Always maintain working code

### **2. Performance-First Thinking**
- Choose data structures based on query patterns
- Optimize the most frequent operations
- Use caching for expensive computations
- Consider space-time tradeoffs

### **3. Comprehensive Edge Case Handling**
- Empty inputs and boundary conditions
- Invalid inputs and error states
- Duplicate data and ordering issues
- Scale limits and performance degradation

### **4. Clean Code Practices**
- Clear variable and function names
- Logical code organization
- Comprehensive comments explaining approach
- Consistent coding style throughout

This framework transforms complex problems into manageable steps while ensuring all requirements are met with optimal solutions.
