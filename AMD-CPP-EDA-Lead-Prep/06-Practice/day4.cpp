// DAY 4: Systems coding: the "implement it from scratch" questions AMD reports.
// Theory: 02-Patterns/P12 (design DS) and 03-Cpp-Deep/C3 (concurrency).
// Build (note -pthread):
//   g++ -std=c++20 -O1 -g -pthread -fsanitize=address,undefined day4.cpp -o day4 && ./day4 [filter]
//   Race check for the threaded ones:  g++ -std=c++20 -O1 -g -pthread -fsanitize=thread day4.cpp -o day4t && ./day4t Queue
// Notes:
//   * The stubs compile but leak or fail on purpose. A LeakSanitizer report at exit is expected until you implement them.
//   * If a threaded test HANGS, you have a lost wakeup or a missing notify/close. That's a good bug to find.
// ★ = most likely to be asked.
#include "test.h"

// ★ P12-2  Fixed-capacity circular buffer. push fails when full; pop fails when empty.
template <class T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity) {}
    bool push(const T& v) { return false; }
    bool pop(T& out) { return false; }
    size_t size() const { return 0; }
    size_t capacity() const { return 0; }
    bool empty() const { return true; }
    bool full() const { return false; }
};

// ★ P12-3a  unique_ptr: exclusive ownership, MOVE-ONLY, size of one raw pointer.
template <class T>
class UniquePtr {
public:
    UniquePtr() = default;
    explicit UniquePtr(T* p) {}
    // TODO: destructor, deleted copy ctor/assign, move ctor/assign (noexcept)
    T* get() const { return nullptr; }
    T* release() { return nullptr; }                 // give up ownership, return the raw pointer
    void reset(T* p = nullptr) {}                     // delete the current object, own p
    T& operator*() const { return *get(); }
    T* operator->() const { return get(); }
    explicit operator bool() const { return get() != nullptr; }
};

// ★ P12-3b  shared_ptr: control block with an ATOMIC strong count. (weak_ptr not required.)
template <class T>
class SharedPtr {
public:
    SharedPtr() = default;
    explicit SharedPtr(T* p) {}
    // TODO: copy ctor/assign, move ctor/assign, destructor. Self-assignment must be safe.
    T* get() const { return nullptr; }
    long use_count() const { return 0; }
    void reset() {}                                   // release ownership (may delete the object)
    T& operator*() const { return *get(); }
    T* operator->() const { return get(); }
    explicit operator bool() const { return get() != nullptr; }
};

// ★ P12-4  Fixed-size pool allocator. O(1) allocate/deallocate via an intrusive free list.
//   Every slot must be aligned to alignof(std::max_align_t). Grow by whole blocks of slotsPerBlock.
//   The destructor releases all blocks.
class FixedPool {
public:
    FixedPool(size_t slotSize, size_t slotsPerBlock) {}
    ~FixedPool() {}
    FixedPool(const FixedPool&) = delete;
    FixedPool& operator=(const FixedPool&) = delete;
    void* allocate() { return nullptr; }
    void deallocate(void* p) {}
    size_t blockCount() const { return 0; }
};

// P12-5  A minimal vector. Separate allocation from construction (operator new + placement new).
//   Growth must be geometric. Reallocation must MOVE elements whose move ctor is noexcept.
//   Trap: v.push_back(v[0]) when a reallocation is needed.
template <class T>
class MyVector {
public:
    MyVector() = default;
    ~MyVector() {}
    MyVector(const MyVector&) = delete;              // (kept out of scope for this drill)
    MyVector& operator=(const MyVector&) = delete;
    void push_back(const T& v) {}
    void push_back(T&& v) {}
    void pop_back() {}
    void reserve(size_t n) {}
    size_t size() const { return 0; }
    size_t capacity() const { return 0; }
    T& operator[](size_t i) { return data_[i]; }
private:
    T* data_ = nullptr;                               // you may change the members
};

// ★ C3  Bounded blocking queue. push blocks while full; pop blocks while empty.
//   After close(): push returns false; pop drains the remaining items, then returns nullopt.
template <class T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity) {}
    bool push(T v) { return false; }
    std::optional<T> pop() { return std::nullopt; }
    void close() {}
};

// ★ C3  Two threads (one prints odd numbers, one even) build "1 2 3 ... n" strictly alternating.
std::string printAlternately(int n) {
    return "";
}

// C3  Sum using `threads` worker threads (split into chunks; avoid false sharing).
ll parallelSum(const VI& a, int threads) {
    return 0;
}

// C3 (stretch)  Fixed-size thread pool. submit() returns a future. The destructor finishes all queued tasks, then joins.
class ThreadPool {
public:
    explicit ThreadPool(size_t n) {}
    ~ThreadPool() {}
    std::future<int> submit(std::function<int()> task) { return {}; }
};

// P12-D7  r x c int matrix, zero-initialized, usable as m[i][j], with ONE contiguous data block.
int** allocMatrix(int r, int c) {
    return nullptr;
}
void freeMatrix(int** m) {
}

#include "tests/day4_tests.h"
