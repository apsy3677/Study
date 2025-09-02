# Atlassian Interview Prep - Quick Reference Guide

## 📋 Overview
This folder contains comprehensive C++ solutions for all Atlassian DS interview questions, optimized for 60-minute interview format.

## 🗂️ File Structure

### Data Structure Questions (C++ Implementations)
1. **`1_closest_org_employees.cpp`** - Find closest common parent group for employees
2. **`2_tennis_club.cpp`** - Court booking assignment with maintenance scheduling
3. **`3_commodity_prices.cpp`** - Price tracking with out-of-order timestamps
4. **`4_popular_content.cpp`** - Content popularity tracking with real-time updates

### Code Design Questions (C++ Implementations)
5. **`5_customer_satisfaction.cpp`** - Agent rating system with multiple views
6. **`6_middleware_router.cpp`** - Web service router with wildcards and path params
7. **`7_snake_game.cpp`** - Classic Snake game implementation
8. **`8_cost_explorer.cpp`** - Subscription cost calculator with multiple plans

### System Design Solutions
9. **`9_system_design_solutions.md`** - High-level architectures for all system design questions

## ⚡ Quick Compile & Run

### Windows (PowerShell)
```powershell
# Compile any solution
g++ -std=c++17 -O2 1_closest_org_employees.cpp -o solution.exe

# Run
./solution.exe
```

### Key Features of Solutions

#### ✅ Time Complexities Optimized
- **Org Hierarchy**: O(n + m) for finding common groups
- **Tennis Courts**: O(n log n) for optimal court assignment
- **Commodity Prices**: O(1) for max price retrieval
- **Popular Content**: O(log n) for updates, O(1) for most popular

#### ✅ Thread-Safe Implementations
- Read-write locks for concurrent access
- Atomic operations where applicable
- Proper synchronization mechanisms

#### ✅ Scalable Designs
- Multiple solution approaches for each problem
- Extensible architectures
- Memory-efficient data structures

## 🎯 Interview Strategy (60 mins)

### Time Allocation
- **Problem Understanding**: 5-8 mins
- **Solution Design**: 10-15 mins
- **Implementation**: 25-30 mins
- **Testing & Edge Cases**: 8-10 mins
- **Optimization Discussion**: 5-7 mins

### Approach for Each Question Type

#### Data Structure Questions
1. **Clarify requirements** (input/output, constraints)
2. **Choose optimal data structure** (trees, graphs, heaps, hash maps)
3. **Implement core algorithm**
4. **Handle edge cases**
5. **Discuss time/space complexity**

#### Code Design Questions
1. **Define interfaces** (classes, methods)
2. **Identify key components**
3. **Implement step by step**
4. **Add extensibility features**
5. **Discuss design patterns used**

#### System Design Questions
1. **Gather requirements** (functional & non-functional)
2. **Estimate scale** (users, QPS, storage)
3. **High-level architecture**
4. **Deep dive into components**
5. **Discuss trade-offs**

## 🔧 Common Patterns Used

### Data Structures
- **Union-Find**: For hierarchical relationships
- **Interval Trees**: For time-based scheduling
- **Priority Queues**: For optimal resource allocation
- **Hash Maps + Sets**: For O(1) lookups
- **Tries**: For path-based routing

### Algorithms
- **DFS/BFS**: Tree/graph traversal
- **Greedy**: Optimal scheduling
- **Dynamic Programming**: Cost optimization
- **Two Pointers**: Conflict detection

### Design Patterns
- **Strategy Pattern**: Multiple algorithms
- **Observer Pattern**: Real-time updates
- **Factory Pattern**: Object creation
- **Template Method**: Extensible workflows

## 🧪 Testing Each Solution

### Run All Tests
```powershell
# Test data structure solutions
g++ -std=c++17 1_closest_org_employees.cpp -o test1.exe && ./test1.exe
g++ -std=c++17 2_tennis_club.cpp -o test2.exe && ./test2.exe
g++ -std=c++17 3_commodity_prices.cpp -o test3.exe && ./test3.exe
g++ -std=c++17 4_popular_content.cpp -o test4.exe && ./test4.exe

# Test code design solutions
g++ -std=c++17 5_customer_satisfaction.cpp -o test5.exe && ./test5.exe
g++ -std=c++17 6_middleware_router.cpp -o test6.exe && ./test6.exe
g++ -std=c++17 7_snake_game.cpp -o test7.exe && ./test7.exe
g++ -std=c++17 8_cost_explorer.cpp -o test8.exe && ./test8.exe
```

## 💡 Interview Tips

### Before Coding
- **Ask clarifying questions** about edge cases
- **Discuss multiple approaches** before implementing
- **Agree on the interface** with interviewer

### While Coding
- **Think out loud** - explain your reasoning
- **Start with simple version**, then optimize
- **Write clean, readable code** with proper naming

### After Coding
- **Walk through test cases** manually
- **Discuss optimizations** and alternative approaches
- **Explain trade-offs** made in your solution

### Common Follow-up Questions
- "How would you handle 10x more data?"
- "What if we need to support concurrent users?"
- "How would you monitor this system in production?"
- "What are the failure points and how to handle them?"

## 🎖️ Key Differentiators for Atlassian

### Technical Excellence
- **Clean, maintainable code**
- **Proper error handling**
- **Comprehensive testing**
- **Performance optimization**

### System Thinking
- **Scalability considerations**
- **Monitoring and observability**
- **Fault tolerance**
- **Security implications**

### Product Mindset
- **User experience focus**
- **Iterative development**
- **Metrics-driven decisions**
- **Cross-team collaboration**

## 📈 Practice Schedule

### Week 1-2: Data Structures
- Master tree/graph algorithms
- Practice time complexity analysis
- Implement from scratch

### Week 3: Code Design
- Design pattern practice
- API design principles
- Object-oriented concepts

### Week 4: System Design
- Architecture patterns
- Scalability techniques
- Real-world system examples

### Week 5: Mock Interviews
- Full 60-minute practice sessions
- Record and review performance
- Focus on communication skills

Good luck with your Atlassian interview! 🚀
