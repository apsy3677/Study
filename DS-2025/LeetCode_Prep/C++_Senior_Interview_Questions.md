# Senior C++ Developer Interview Questions (7-10 Years Experience)

## 1. Rule of Three/Five/Zero

**Question**: Explain the Rule of Three, Rule of Five, and Rule of Zero. When and why do you need to implement each?

**What it tests**: 
- Deep understanding of RAII and resource management
- Knowledge of move semantics and modern C++
- Understanding of when compiler-generated functions are sufficient

**Intuition and Approach**:
- Rule of Three: If you need one of destructor/copy constructor/copy assignment, you likely need all three
- Rule of Five: Adds move constructor and move assignment for performance
- Rule of Zero: Prefer using standard library containers to avoid manual resource management

**Standard C++ Code for Interviews**:

```cpp
// Rule of Three Example
class LegacyResource {
private:
    char* data;
    size_t size;

public:
    // Constructor
    LegacyResource(size_t n) : size(n), data(new char[n]) {}
    
    // Destructor
    ~LegacyResource() { delete[] data; }
    
    // Copy Constructor
    LegacyResource(const LegacyResource& other) 
        : size(other.size), data(new char[size]) {
        std::copy(other.data, other.data + size, data);
    }
    
    // Copy Assignment
    LegacyResource& operator=(const LegacyResource& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new char[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
};

// Rule of Five Example (adds move semantics)
class ModernResource {
private:
    std::unique_ptr<char[]> data;
    size_t size;

public:
    ModernResource(size_t n) : size(n), data(std::make_unique<char[]>(n)) {}
    
    // Move Constructor
    ModernResource(ModernResource&& other) noexcept 
        : data(std::move(other.data)), size(other.size) {
        other.size = 0;
    }
    
    // Move Assignment
    ModernResource& operator=(ModernResource&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }
    
    // Copy operations (Rule of Three still applies)
    ModernResource(const ModernResource& other);
    ModernResource& operator=(const ModernResource& other);
    ~ModernResource() = default; // unique_ptr handles cleanup
};

// Rule of Zero Example (preferred)
class BestPractice {
private:
    std::vector<char> data; // Handles all resource management
    std::string name;       // Handles all string operations
    
public:
    BestPractice(size_t n, const std::string& n) : data(n), name(n) {}
    // Compiler generates all special functions correctly!
};
```

## 2. Virtual Function Table (vtable) and Virtual Inheritance

**Question**: Explain how virtual function dispatch works. What are the performance implications? What is virtual inheritance and when do you use it?

**What it tests**:
- Understanding of polymorphism implementation
- Knowledge of performance trade-offs
- Advanced inheritance concepts

**Intuition and Approach**:
- vtable is a lookup table of function pointers for each class with virtual functions
- Virtual inheritance solves diamond problem but adds overhead
- Performance cost: one extra indirection per virtual call

**Standard C++ Code for Interviews**:

```cpp
// Virtual Function Table Example
class Base {
public:
    virtual void func1() { std::cout << "Base::func1\n"; }
    virtual void func2() { std::cout << "Base::func2\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void func1() override { std::cout << "Derived::func1\n"; }
    void func3() { std::cout << "Derived::func3\n"; }
};

// Diamond Problem and Virtual Inheritance
class Animal {
public:
    virtual void speak() = 0;
    int age;
};

class Mammal : public virtual Animal {
public:
    void breathe() { std::cout << "Breathing\n"; }
};

class Bird : public virtual Animal {
public:
    void fly() { std::cout << "Flying\n"; }
};

class Bat : public Mammal, public Bird {
public:
    void speak() override { std::cout << "Screech\n"; }
    // Only one copy of Animal::age due to virtual inheritance
};

// Performance demonstration
void demonstrateVirtualCallOverhead() {
    Base* obj = new Derived();
    
    // Virtual call: obj->vtable->func1()
    obj->func1(); // Two pointer dereferences
    
    // Direct call: no vtable lookup
    Derived d;
    d.func3(); // Direct function call
    
    delete obj;
}
```

## 3. RAII and Exception Safety

**Question**: Explain RAII. What are the different levels of exception safety? How do you implement strong exception safety?

**What it tests**:
- Resource management philosophy
- Understanding of exception handling best practices
- Ability to write robust code

**Intuition and Approach**:
- RAII: Resource Acquisition Is Initialization - resources tied to object lifetime
- Exception safety levels: No-throw, Strong, Basic, No guarantee
- Strong safety: Either complete success or no change to program state

**Standard C++ Code for Interviews**:

```cpp
// RAII Example
class FileHandler {
private:
    std::FILE* file;
    
public:
    FileHandler(const char* filename) {
        file = std::fopen(filename, "r");
        if (!file) throw std::runtime_error("Failed to open file");
    }
    
    ~FileHandler() {
        if (file) std::fclose(file); // Automatic cleanup
    }
    
    // Prevent copying (or implement proper copy semantics)
    FileHandler(const FileHandler&) = delete;
    FileHandler& operator=(const FileHandler&) = delete;
    
    std::FILE* get() const { return file; }
};

// Exception Safety Levels
class ExceptionSafeVector {
private:
    std::unique_ptr<int[]> data;
    size_t size;
    size_t capacity;
    
public:
    // Strong Exception Safety
    void push_back(int value) {
        if (size >= capacity) {
            // Allocate new memory first (might throw)
            size_t new_capacity = capacity ? capacity * 2 : 1;
            auto new_data = std::make_unique<int[]>(new_capacity);
            
            // Copy existing elements (might throw)
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            
            // Only commit changes after everything succeeds (no-throw operations)
            data = std::move(new_data);
            capacity = new_capacity;
        }
        
        data[size++] = value; // No-throw operation
    }
    
    // No-throw guarantee
    size_t getSize() const noexcept { return size; }
    
    // Basic exception safety
    void risky_operation() {
        try {
            some_operation_that_might_throw();
        } catch (...) {
            // Cleanup and maintain invariants
            // Object remains in valid (but possibly changed) state
            throw;
        }
    }
};

// RAII for multiple resources
class DatabaseConnection {
private:
    struct Impl; // Pimpl idiom
    std::unique_ptr<Impl> pImpl;
    
public:
    DatabaseConnection(const std::string& connectionString);
    ~DatabaseConnection(); // Defined in .cpp file
    
    // Move-only semantics
    DatabaseConnection(DatabaseConnection&&) = default;
    DatabaseConnection& operator=(DatabaseConnection&&) = default;
    
    void execute(const std::string& query);
    void beginTransaction();
    void commit();
    void rollback();
};
```

## 4. Template Metaprogramming and SFINAE

**Question**: What is SFINAE? How do you use enable_if and concepts? Explain template specialization vs overloading.

**What it tests**:
- Advanced template knowledge
- Modern C++ features (concepts, if constexpr)
- Ability to write generic, efficient code

**Intuition and Approach**:
- SFINAE: Substitution Failure Is Not An Error - allows conditional compilation
- enable_if creates overloads based on type traits
- Concepts (C++20) provide cleaner syntax for template constraints

**Standard C++ Code for Interviews**:

```cpp
#include <type_traits>
#include <iostream>
#include <vector>

// SFINAE with enable_if
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
process(T value) {
    std::cout << "Processing integral: " << value << std::endl;
    return value * 2;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
process(T value) {
    std::cout << "Processing floating point: " << value << std::endl;
    return value * 1.5;
}

// Modern C++17 with if constexpr
template<typename T>
auto modern_process(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Processing integral: " << value << std::endl;
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Processing floating point: " << value << std::endl;
        return value * 1.5;
    } else {
        std::cout << "Processing other type" << std::endl;
        return value;
    }
}

// C++20 Concepts (if available)
#if __cpp_concepts >= 201907L
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T concept_process(T value) {
    return value * 2;
}
#endif

// Template Specialization
template<typename T>
class Container {
    std::vector<T> data;
public:
    void add(const T& item) { data.push_back(item); }
    size_t size() const { return data.size(); }
};

// Specialization for bool (space optimization)
template<>
class Container<bool> {
    std::vector<bool> data; // Uses bit packing
public:
    void add(bool item) { data.push_back(item); }
    size_t size() const { return data.size(); }
    void optimize() { data.shrink_to_fit(); }
};

// Partial specialization for pointers
template<typename T>
class Container<T*> {
    std::vector<T*> data;
public:
    void add(T* item) { 
        if (item) data.push_back(item); 
    }
    size_t size() const { return data.size(); }
    void cleanup() {
        for (auto* ptr : data) delete ptr;
        data.clear();
    }
};

// Type traits implementation
template<typename T>
struct is_container : std::false_type {};

template<typename T, typename Alloc>
struct is_container<std::vector<T, Alloc>> : std::true_type {};

template<typename T>
constexpr bool is_container_v = is_container<T>::value;
```

## 5. Memory Management and Smart Pointers

**Question**: Compare unique_ptr, shared_ptr, and weak_ptr. When do you use each? What are the performance implications? How do you avoid circular references?

**What it tests**:
- Modern C++ memory management
- Understanding of reference counting overhead
- Knowledge of common pitfalls

**Intuition and Approach**:
- unique_ptr: Exclusive ownership, zero overhead
- shared_ptr: Shared ownership, reference counting overhead
- weak_ptr: Non-owning reference, breaks cycles

**Standard C++ Code for Interviews**:

```cpp
#include <memory>
#include <vector>
#include <iostream>

// unique_ptr - Exclusive ownership
class ResourceManager {
private:
    std::unique_ptr<int[]> buffer;
    size_t size;

public:
    ResourceManager(size_t n) : buffer(std::make_unique<int[]>(n)), size(n) {}
    
    // Move semantics (unique_ptr is move-only)
    ResourceManager(ResourceManager&&) = default;
    ResourceManager& operator=(ResourceManager&&) = default;
    
    // Factory function
    static std::unique_ptr<ResourceManager> create(size_t n) {
        return std::make_unique<ResourceManager>(n);
    }
    
    int& operator[](size_t i) { return buffer[i]; }
};

// shared_ptr - Shared ownership
class Node {
public:
    int data;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> parent; // Avoid circular reference
    
    Node(int val) : data(val) {}
    
    void addChild(std::shared_ptr<Node> child) {
        child->parent = shared_from_this(); // Requires std::enable_shared_from_this
        next = child;
    }
};

class TreeNode : public std::enable_shared_from_this<TreeNode> {
public:
    int value;
    std::vector<std::shared_ptr<TreeNode>> children;
    std::weak_ptr<TreeNode> parent;
    
    TreeNode(int val) : value(val) {}
    
    void addChild(int val) {
        auto child = std::make_shared<TreeNode>(val);
        child->parent = shared_from_this();
        children.push_back(child);
    }
    
    std::shared_ptr<TreeNode> getParent() {
        return parent.lock(); // Returns nullptr if parent is destroyed
    }
};

// Custom deleter with unique_ptr
class FileDescriptor {
private:
    int fd;
    
public:
    FileDescriptor(const char* filename);
    
    // Custom deleter
    struct FileDeleter {
        void operator()(FileDescriptor* ptr) {
            if (ptr) {
                close(ptr->fd);
                delete ptr;
            }
        }
    };
    
    using UniqueFilePtr = std::unique_ptr<FileDescriptor, FileDeleter>;
    
    static UniqueFilePtr open(const char* filename) {
        return UniqueFilePtr(new FileDescriptor(filename));
    }
};

// Performance comparison
void demonstratePerformance() {
    // unique_ptr - Zero overhead
    auto unique = std::make_unique<int>(42);
    // Direct pointer access, no reference counting
    
    // shared_ptr - Reference counting overhead
    auto shared1 = std::make_shared<int>(42);
    auto shared2 = shared1; // Atomic increment of reference count
    // shared2.reset(); // Atomic decrement
    
    // weak_ptr - No ownership, must lock to access
    std::weak_ptr<int> weak = shared1;
    if (auto locked = weak.lock()) {
        // Safe access to the object
        std::cout << *locked << std::endl;
    }
}

// Breaking circular references
class Parent {
public:
    std::vector<std::shared_ptr<class Child>> children;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

class Child {
public:
    std::weak_ptr<Parent> parent; // Weak reference breaks cycle
    ~Child() { std::cout << "Child destroyed\n"; }
};

void avoidCircularReference() {
    auto parent = std::make_shared<Parent>();
    auto child = std::make_shared<Child>();
    
    parent->children.push_back(child);
    child->parent = parent; // weak_ptr assignment
    
    // When parent goes out of scope, both objects are properly destroyed
}
```

## 6. Move Semantics and Perfect Forwarding

**Question**: Explain move semantics. What is perfect forwarding? When do you use std::forward vs std::move?

**What it tests**:
- Modern C++ performance optimization
- Understanding of value categories (lvalue, rvalue, xvalue)
- Template forwarding knowledge

**Intuition and Approach**:
- Move semantics: Transfer ownership instead of copying
- Perfect forwarding: Preserve value category in template functions
- std::move: Cast to rvalue, std::forward: Conditional cast based on template parameter

**Standard C++ Code for Interviews**:

```cpp
#include <utility>
#include <vector>
#include <string>
#include <iostream>

// Move semantics example
class MoveableResource {
private:
    std::vector<int> data;
    std::string name;

public:
    // Constructor
    MoveableResource(const std::string& n) : name(n) {
        data.resize(1000000); // Large resource
        std::cout << "Constructed: " << name << std::endl;
    }
    
    // Copy constructor (expensive)
    MoveableResource(const MoveableResource& other) 
        : data(other.data), name(other.name + "_copy") {
        std::cout << "Copied: " << name << std::endl;
    }
    
    // Move constructor (cheap)
    MoveableResource(MoveableResource&& other) noexcept
        : data(std::move(other.data)), name(std::move(other.name)) {
        other.name = "moved_from";
        std::cout << "Moved: " << name << std::endl;
    }
    
    // Copy assignment
    MoveableResource& operator=(const MoveableResource& other) {
        if (this != &other) {
            data = other.data;
            name = other.name + "_assigned";
            std::cout << "Copy assigned: " << name << std::endl;
        }
        return *this;
    }
    
    // Move assignment
    MoveableResource& operator=(MoveableResource&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            name = std::move(other.name);
            other.name = "moved_from";
            std::cout << "Move assigned: " << name << std::endl;
        }
        return *this;
    }
    
    const std::string& getName() const { return name; }
};

// Perfect forwarding
template<typename T>
void process_value(T&& value) {
    // Perfect forwarding preserves value category
    helper(std::forward<T>(value));
}

void helper(const MoveableResource& res) {
    std::cout << "Helper called with lvalue: " << res.getName() << std::endl;
}

void helper(MoveableResource&& res) {
    std::cout << "Helper called with rvalue: " << res.getName() << std::endl;
}

// Factory function with perfect forwarding
template<typename T, typename... Args>
std::unique_ptr<T> make_unique_perfect(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Universal reference vs rvalue reference
template<typename T>
void universal_ref(T&& param) {  // Universal reference (can bind to lvalue or rvalue)
    // T&& is universal reference only in template parameter deduction context
    process_value(std::forward<T>(param));
}

void rvalue_ref(MoveableResource&& param) {  // Rvalue reference (only rvalues)
    // param is always rvalue reference, no template deduction
    helper(std::move(param));
}

// Demonstration of move semantics benefits
void demonstrateMoveSemantics() {
    std::vector<MoveableResource> vec;
    
    // Without move semantics (expensive copies)
    MoveableResource res1("resource1");
    vec.push_back(res1); // Copy
    
    // With move semantics (cheap moves)
    vec.push_back(MoveableResource("resource2")); // Move from temporary
    vec.push_back(std::move(res1)); // Explicit move
    
    // Perfect forwarding
    MoveableResource res3("resource3");
    process_value(res3);                    // Calls helper(const MoveableResource&)
    process_value(std::move(res3));         // Calls helper(MoveableResource&&)
    process_value(MoveableResource("temp")); // Calls helper(MoveableResource&&)
}

// Return value optimization (RVO) vs move
MoveableResource createResource() {
    MoveableResource local("local");
    // RVO: no copy/move, object constructed directly in return location
    return local;
}

MoveableResource createResourceConditional(bool condition) {
    MoveableResource res1("res1");
    MoveableResource res2("res2");
    
    if (condition) {
        return res1; // NRVO may not apply, move used
    } else {
        return res2; // NRVO may not apply, move used
    }
}
```

## 7. Concurrency and Thread Safety

**Question**: How do you ensure thread safety? Compare mutex, atomic, and lock-free programming. What are memory barriers?

**What it tests**:
- Multithreading knowledge
- Understanding of memory models
- Performance implications of synchronization

**Intuition and Approach**:
- Mutex: Blocking synchronization, heavyweight
- Atomic: Lock-free for simple operations, lightweight
- Memory barriers: Control memory reordering

**Standard C++ Code for Interviews**:

```cpp
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <memory>

// Thread-safe singleton (Meyers' singleton)
class ThreadSafeSingleton {
private:
    ThreadSafeSingleton() = default;
    
public:
    static ThreadSafeSingleton& getInstance() {
        static ThreadSafeSingleton instance; // Thread-safe in C++11+
        return instance;
    }
    
    // Prevent copying
    ThreadSafeSingleton(const ThreadSafeSingleton&) = delete;
    ThreadSafeSingleton& operator=(const ThreadSafeSingleton&) = delete;
    
    void doSomething() {
        std::cout << "Doing something thread-safely\n";
    }
};

// Thread-safe queue using mutex
template<typename T>
class ThreadSafeQueue {
private:
    mutable std::mutex mtx;
    std::queue<T> data;
    std::condition_variable cv;

public:
    void push(T item) {
        std::lock_guard<std::mutex> lock(mtx);
        data.push(item);
        cv.notify_one();
    }
    
    bool try_pop(T& item) {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) return false;
        
        item = data.front();
        data.pop();
        return true;
    }
    
    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.empty()) return std::shared_ptr<T>();
        
        auto result = std::make_shared<T>(data.front());
        data.pop();
        return result;
    }
    
    void wait_and_pop(T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !data.empty(); });
        
        item = data.front();
        data.pop();
    }
    
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }
};

// Atomic operations and memory ordering
class AtomicCounter {
private:
    std::atomic<int> count{0};
    std::atomic<bool> flag{false};

public:
    void increment() {
        count.fetch_add(1, std::memory_order_relaxed); // Relaxed ordering for counter
    }
    
    int get() const {
        return count.load(std::memory_order_acquire); // Acquire semantics for reading
    }
    
    void setFlag() {
        flag.store(true, std::memory_order_release); // Release semantics for flag
    }
    
    bool checkFlag() const {
        return flag.load(std::memory_order_acquire); // Acquire semantics for reading
    }
    
    // Compare and swap
    bool compareAndSwap(int expected, int desired) {
        return count.compare_exchange_weak(expected, desired, 
                                         std::memory_order_acq_rel);
    }
};

// Lock-free stack (simplified)
template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };
    
    std::atomic<Node*> head{nullptr};

public:
    void push(const T& data) {
        Node* new_node = new Node(data);
        new_node->next = head.load();
        
        // Compare-and-swap loop
        while (!head.compare_exchange_weak(new_node->next, new_node)) {
            // If CAS fails, new_node->next is updated with current head value
            // Loop until successful
        }
    }
    
    bool pop(T& result) {
        Node* old_head = head.load();
        
        while (old_head && 
               !head.compare_exchange_weak(old_head, old_head->next)) {
            // Loop until successful or empty
        }
        
        if (old_head) {
            result = old_head->data;
            delete old_head; // Potential ABA problem - need hazard pointers in production
            return true;
        }
        return false;
    }
    
    ~LockFreeStack() {
        while (Node* old_head = head.load()) {
            head = old_head->next;
            delete old_head;
        }
    }
};

// RAII lock management
class BankAccount {
private:
    mutable std::mutex mtx;
    double balance;

public:
    BankAccount(double initial_balance) : balance(initial_balance) {}
    
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
    }
    
    bool withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
    
    double getBalance() const {
        std::lock_guard<std::mutex> lock(mtx);
        return balance;
    }
    
    // Deadlock-free transfer using std::lock
    friend void transfer(BankAccount& from, BankAccount& to, double amount) {
        std::lock(from.mtx, to.mtx); // Acquire both locks atomically
        std::lock_guard<std::mutex> lock1(from.mtx, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(to.mtx, std::adopt_lock);
        
        if (from.balance >= amount) {
            from.balance -= amount;
            to.balance += amount;
        }
    }
};

// Producer-consumer pattern
void producerConsumerDemo() {
    ThreadSafeQueue<int> queue;
    
    // Producer thread
    std::thread producer([&queue] {
        for (int i = 0; i < 10; ++i) {
            queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    
    // Consumer thread
    std::thread consumer([&queue] {
        int item;
        for (int i = 0; i < 10; ++i) {
            queue.wait_and_pop(item);
            std::cout << "Consumed: " << item << std::endl;
        }
    });
    
    producer.join();
    consumer.join();
}
```

## Key Interview Tips

1. **Always explain trade-offs**: Performance vs safety, memory vs speed
2. **Mention modern alternatives**: std::string over char*, smart pointers over raw pointers
3. **Discuss exception safety**: Show understanding of robust code design
4. **Know the standard library**: STL containers, algorithms, utilities
5. **Understand undefined behavior**: Dangling pointers, buffer overflows, data races
6. **Be prepared for follow-ups**: "How would you optimize this?", "What if memory is limited?"

## Common Follow-up Questions

- How do you debug memory leaks?
- What tools do you use for profiling?
- How do you ensure code quality in large C++ projects?
- What's your approach to handling legacy C++ code?
- How do you stay updated with modern C++ standards?

---

# LeetCode Problem Analysis

## 1. Robot Room Cleaner (489) - Variant

**Problem Statement**:
You control a robot in a room. The robot can move forward, turn left, or turn right. The robot cannot see the entire room layout but can detect obstacles directly in front. Your task is to clean the entire room using the robot's limited interface.

**Robot Interface**:
```cpp
class Robot {
public:
    bool move();        // Move forward, returns true if successful
    void turnLeft();    // Turn 90 degrees left
    void turnRight();   // Turn 90 degrees right
    void clean();       // Clean current cell
};
```

**Key Insights**:
- **Backtracking with State Management**: Since we can't see the full room, we need to explore systematically
- **Direction Tracking**: Keep track of robot's orientation to navigate properly
- **Visited Set**: Use coordinates relative to starting position to avoid cleaning same cell twice
- **Spiral Pattern**: Use right-hand rule (always try to go right first) for systematic exploration

**Approach**:
1. Use DFS with backtracking to explore all reachable cells
2. Maintain robot's current direction (0=North, 1=East, 2=South, 3=West)
3. For each cell: clean it, mark as visited, explore all 4 directions
4. After exploring a direction, backtrack by moving back and restoring orientation

**Solution**:
```cpp
class Solution {
private:
    // Directions: North, East, South, West
    vector<vector<int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    set<pair<int,int>> visited;
    
public:
    void cleanRoom(Robot& robot) {
        dfs(robot, 0, 0, 0); // Start at (0,0) facing North
    }
    
private:
    void dfs(Robot& robot, int x, int y, int direction) {
        // Clean current cell and mark as visited
        robot.clean();
        visited.insert({x, y});
        
        // Try all 4 directions (right-hand rule)
        for (int i = 0; i < 4; i++) {
            int newDir = (direction + i) % 4;
            int newX = x + directions[newDir][0];
            int newY = y + directions[newDir][1];
            
            // If not visited and can move
            if (visited.find({newX, newY}) == visited.end() && robot.move()) {
                dfs(robot, newX, newY, newDir);
                
                // Backtrack: return to previous position and orientation
                goBack(robot);
            }
            
            // Turn right for next direction
            robot.turnRight();
            direction = (direction + 1) % 4;
        }
    }
    
    void goBack(Robot& robot) {
        robot.turnRight();
        robot.turnRight();
        robot.move();
        robot.turnRight();
        robot.turnRight();
    }
};
```

**Time Complexity**: O(N) where N is number of reachable cells
- **Each cell visited exactly once**: Due to visited set, we never revisit a cell
- **4 direction attempts per cell**: At each cell, we try at most 4 directions
- **Backtracking operations**: After exploring each successful move, we backtrack (5 robot operations)
- **Total**: O(N × 4 × 5) = O(N) - linear, not exponential

**Space Complexity**: O(N) where N is number of reachable cells
- **Visited Set**: O(N) to store coordinates of all visited cells
- **Recursion Stack**: O(N) in worst case for deep paths (e.g., long corridor)

**Why NOT O(4^N)?**
The visited set is the key! Even though we try 4 directions at each cell, we never actually explore the same cell twice. The exponential behavior is **prevented** by the visited check.

**Detailed Breakdown**:
- **Cell visits**: Each of N cells visited exactly once → O(N)
- **Direction attempts**: 4 attempts per cell → O(4N) = O(N)  
- **Successful moves**: At most N-1 successful moves (to visit N cells)
- **Backtracking**: At most N-1 backtracks → O(N)
- **Robot operations**: Each backtrack = 5 operations → O(5N) = O(N)

---

## 2. Diagonal Traverse II (1424) - Variant

**Problem Statement**:
Given a 2D array where each row can have different lengths, return all elements in diagonal order. Elements in the same diagonal have the same sum of indices (i + j).

**Example**:
```
Input: [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,7,2,5,8,3,6,9]

Diagonals:
- Diagonal 0: (0,0) -> [1]
- Diagonal 1: (1,0), (0,1) -> [4,2] 
- Diagonal 2: (2,0), (1,1), (0,2) -> [7,5,3]
- etc.
```

**Key Insights**:
- **Diagonal Property**: Elements at (i,j) belong to diagonal (i+j)
- **Jagged Array**: Handle variable row lengths carefully
- **BFS vs Map Approach**: Two main approaches - BFS traversal or map by diagonal index

**Approach 1: Map by Diagonal Index**:
1. Group elements by their diagonal index (i + j)
2. For each diagonal, elements appear in order of increasing row index
3. Concatenate all diagonals in order

**Solution 1**:
```cpp
vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
    map<int, vector<int>> diagonals;
    
    // Group by diagonal index
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums[i].size(); j++) {
            diagonals[i + j].push_back(nums[i][j]);
        }
    }
    
    vector<int> result;
    for (auto& [diag, elements] : diagonals) {
        for (int val : elements) {
            result.push_back(val);
        }
    }
    return result;
}
```

**Approach 2: BFS Traversal**:
1. Start from (0,0), use BFS to visit diagonally
2. For each cell, add right and down neighbors to queue
3. Use set to avoid visiting same cell twice

**Solution 2**:
```cpp
vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
    vector<int> result;
    queue<pair<int,int>> q;
    set<pair<int,int>> visited;
    
    q.push({0, 0});
    visited.insert({0, 0});
    
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        
        result.push_back(nums[i][j]);
        
        // Add down neighbor
        if (i + 1 < nums.size() && j < nums[i + 1].size() && 
            visited.find({i + 1, j}) == visited.end()) {
            q.push({i + 1, j});
            visited.insert({i + 1, j});
        }
        
        // Add right neighbor  
        if (j + 1 < nums[i].size() && 
            visited.find({i, j + 1}) == visited.end()) {
            q.push({i, j + 1});
            visited.insert({i, j + 1});
        }
    }
    
    return result;
}
```

**Time Complexity**: O(N) where N is total number of elements
**Space Complexity**: O(N) for storage

---

## 3. Count Nodes Equal to Average of Subtree (2265) - Exactly

**Problem Statement**:
Given a binary tree, count the number of nodes where the node's value equals the average of all values in its subtree (including the node itself). The average should be the floor of the true average.

**Example**:
```
     4
   /   \
  8     5
 / \     \
0   1     6

Node 4: subtree values [4,8,5,0,1,6], average = 24/6 = 4 ✓
Node 5: subtree values [5,6], average = 11/2 = 5.5 → floor(5.5) = 5 ✓
```

**Key Insights**:
- **Post-order Traversal**: Need subtree info before processing current node
- **Return Multiple Values**: Need both sum and count from each subtree
- **Floor Division**: Use integer division for average calculation

**Approach**:
1. Use post-order DFS to get sum and count of each subtree
2. For each node, check if its value equals floor(subtree_sum / subtree_count)
3. Return updated sum and count to parent

**Solution**:
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int count = 0;
    
public:
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return count;
    }
    
private:
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {0, 0};
        
        // Get sum and count from left and right subtrees
        auto [leftSum, leftCount] = dfs(node->left);
        auto [rightSum, rightCount] = dfs(node->right);
        
        // Calculate current subtree sum and count
        int totalSum = leftSum + rightSum + node->val;
        int totalCount = leftCount + rightCount + 1;
        
        // Check if current node value equals average (floor division)
        if (node->val == totalSum / totalCount) {
            count++;
        }
        
        return {totalSum, totalCount};
    }
};
```

**Time Complexity**: O(N) - visit each node once
**Space Complexity**: O(H) where H is tree height (recursion stack)

---

## 4. Insert into a Sorted Circular Linked List (708) - Almost Exactly

**Problem Statement**:
Insert a value into a sorted circular linked list. Return any node in the resulting list. Handle edge cases where the list is empty or has only one node.

**Key Insights**:
- **Three Insertion Cases**:
  1. Normal case: value fits between two consecutive nodes
  2. Boundary case: value is smaller than min or larger than max
  3. All same values: can insert anywhere
- **Circular Traversal**: Use do-while to handle single-node case
- **Edge Cases**: Empty list requires creating new node

**Approach**:
1. Handle empty list case first
2. Find insertion point by traversing the circular list
3. Insert at the appropriate position based on the three cases

**Solution**:
```cpp
class Node {
public:
    int val;
    Node* next;
    
    Node() {}
    Node(int _val) {
        val = _val;
        next = NULL;
    }
    
    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* newNode = new Node(insertVal);
        
        // Case 1: Empty list
        if (!head) {
            newNode->next = newNode;
            return newNode;
        }
        
        // Case 2: Single node or find insertion point
        Node* prev = head;
        Node* curr = head->next;
        
        bool toInsert = false;
        
        do {
            if (prev->val <= insertVal && insertVal <= curr->val) {
                // Case 2a: Normal insertion between prev and curr
                toInsert = true;
            } else if (prev->val > curr->val) {
                // Case 2b: At the boundary (max -> min transition)
                if (insertVal >= prev->val || insertVal <= curr->val) {
                    toInsert = true;
                }
            }
            
            if (toInsert) {
                prev->next = newNode;
                newNode->next = curr;
                return head;
            }
            
            prev = curr;
            curr = curr->next;
        } while (prev != head);
        
        // Case 3: All nodes have same value, insert anywhere
        prev->next = newNode;
        newNode->next = curr;
        return head;
    }
};
```

**Alternative Cleaner Solution**:
```cpp
Node* insert(Node* head, int insertVal) {
    Node* newNode = new Node(insertVal);
    
    if (!head) {
        newNode->next = newNode;
        return newNode;
    }
    
    Node* prev = head;
    Node* curr = head->next;
    
    do {
        // Case 1: insertVal fits between prev and curr
        if ((prev->val <= insertVal && insertVal <= curr->val) ||
            // Case 2: at boundary and insertVal is extreme value
            (prev->val > curr->val && (insertVal >= prev->val || insertVal <= curr->val))) {
            
            prev->next = newNode;
            newNode->next = curr;
            return head;
        }
        
        prev = curr;
        curr = curr->next;
    } while (prev != head);
    
    // Case 3: all values are same, insert anywhere
    prev->next = newNode;
    newNode->next = curr;
    return head;
}
```

**Time Complexity**: O(N) - might need to traverse entire list
**Space Complexity**: O(1) - only creating one new node

**Key Edge Cases**:
1. Empty list
2. Single node list  
3. All nodes have same value
4. Insert minimum value
5. Insert maximum value
6. Insert in normal sorted position

---

## **Case 3 Detailed Example: All Nodes Have Same Value**

**Scenario**: Insert `insertVal = 5` into circular list where all nodes have value `3`

**Initial List**: `3 -> 3 -> 3 -> (back to first 3)`
```
     3
   /   \
  3     3
   \   /
    \ /
```

**Code Dry Run**:
```cpp
Node* insert(Node* head, int insertVal = 5) {
    Node* newNode = new Node(5);
    
    // head points to first node with value 3
    Node* prev = head;        // prev points to node with value 3
    Node* curr = head->next;  // curr points to second node with value 3
    
    do {
        // Iteration 1: prev=3, curr=3, insertVal=5
        if (prev->val <= insertVal && insertVal <= curr->val) {
            // 3 <= 5 && 5 <= 3  →  true && false  →  false
        } else if (prev->val > curr->val) {
            // 3 > 3  →  false (no boundary transition since all same)
        }
        // toInsert remains false, continue
        
        prev = curr;          // prev moves to second node (3)
        curr = curr->next;    // curr moves to third node (3)
        
        // Iteration 2: prev=3, curr=3, insertVal=5
        // Same logic: both conditions false
        
        prev = curr;          // prev moves to third node (3)
        curr = curr->next;    // curr moves back to first node (3)
        
        // Iteration 3: prev=3, curr=3, insertVal=5
        // Same logic: both conditions false
        
        prev = curr;          // prev moves back to first node (3)
        curr = curr->next;    // curr moves to second node (3)
        
    } while (prev != head);   // prev == head, so exit loop
    
    // Case 3: All nodes have same value, insert anywhere
    prev->next = newNode;     // Insert between prev and curr
    newNode->next = curr;
    return head;
}
```

**Step-by-Step Execution**:

**Initial State**:
- `head` → Node(3) → Node(3) → Node(3) → back to first Node(3)
- `insertVal = 5`
- `prev = head` (first 3)
- `curr = head->next` (second 3)

**Loop Iterations**:
1. **Iteration 1**: `prev=3, curr=3`
   - `3 <= 5 && 5 <= 3` → `true && false` → **false**
   - `3 > 3` → **false**
   - Move: `prev` → second 3, `curr` → third 3

2. **Iteration 2**: `prev=3, curr=3`
   - Same conditions, same results → **false**
   - Move: `prev` → third 3, `curr` → first 3

3. **Iteration 3**: `prev=3, curr=3`
   - Same conditions, same results → **false**
   - Move: `prev` → first 3, `curr` → second 3
   - Now `prev == head`, so exit loop

**Final Result**:
```cpp
// Case 3 executes:
prev->next = newNode;    // first 3 → new 5
newNode->next = curr;    // new 5 → second 3
```

**Final List**: `3 -> 5 -> 3 -> 3 -> (back to first 3)`

**Why Case 3 Occurs**:
- **No normal insertion point**: `5` doesn't fit between any `3` and `3`
- **No boundary transition**: Since all values are same (`3 > 3` is false), there's no max→min transition
- **Loop completes**: We traverse the entire circle without finding insertion point
- **Default insertion**: Insert anywhere (between `prev` and `curr` at loop exit)

**Case 3 with Same Value**: Insert `insertVal = 3` into `[3,3,3]`

**Code Execution**:
```cpp
Node* insert(Node* head, int insertVal = 3) {
    Node* newNode = new Node(3);
    
    Node* prev = head;        // prev points to first 3
    Node* curr = head->next;  // curr points to second 3
    
    do {
        // Iteration 1: prev=3, curr=3, insertVal=3
        if (prev->val <= insertVal && insertVal <= curr->val) {
            // 3 <= 3 && 3 <= 3  →  true && true  →  **TRUE**
            prev->next = newNode;
            newNode->next = curr;
            return head;  // ✓ INSERTION SUCCESSFUL
        }
        // This condition succeeds, so we never reach the boundary check
        
    } while (prev != head);
}
```

**Key Difference**: 
- When `insertVal = 5`: `3 <= 5 && 5 <= 3` → `true && false` → **false** (continue loop)
- When `insertVal = 3`: `3 <= 3 && 3 <= 3` → `true && true` → **TRUE** (insert immediately)

**Result**: Inserts at **first valid position** rather than falling through to Case 3

**Final List**: `3 -> 3 -> 3 -> 3 -> (back to first 3)`

---

**Another Example**: Insert `1` into `[5,5,5,5]`
- `1` is smaller than all values
- No boundary (all same), so Case 2b doesn't trigger
- Falls through to Case 3, inserts anywhere
