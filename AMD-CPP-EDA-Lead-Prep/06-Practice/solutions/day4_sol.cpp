// SPOILERS: reference solutions for day4.cpp.
#include "../test.h"

// ===== P12-2 Ring buffer =====
template <class T>
class RingBuffer {
public:
    explicit RingBuffer(size_t capacity) : buf_(capacity) {}
    bool push(const T& v) {
        if (full()) return false;
        buf_[tail_] = v;
        tail_ = (tail_ + 1) % buf_.size();
        ++count_;
        return true;
    }
    bool pop(T& out) {
        if (empty()) return false;
        out = std::move(buf_[head_]);
        head_ = (head_ + 1) % buf_.size();
        --count_;
        return true;
    }
    size_t size() const { return count_; }
    size_t capacity() const { return buf_.size(); }
    bool empty() const { return count_ == 0; }
    bool full() const { return count_ == buf_.size(); }
private:
    vector<T> buf_;
    size_t head_ = 0, tail_ = 0, count_ = 0;   // count_ resolves the full/empty ambiguity
};

// ===== P12-3a UniquePtr =====
template <class T>
class UniquePtr {
public:
    UniquePtr() = default;
    explicit UniquePtr(T* p) : p_(p) {}
    ~UniquePtr() { delete p_; }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& o) noexcept : p_(std::exchange(o.p_, nullptr)) {}
    UniquePtr& operator=(UniquePtr&& o) noexcept {
        if (this != &o) reset(o.release());
        return *this;
    }
    T* get() const { return p_; }
    T* release() { return std::exchange(p_, nullptr); }
    void reset(T* p = nullptr) { T* old = std::exchange(p_, p); delete old; }   // set first, then delete (re-entrancy safe)
    T& operator*() const { return *p_; }
    T* operator->() const { return p_; }
    explicit operator bool() const { return p_ != nullptr; }
private:
    T* p_ = nullptr;
};

// ===== P12-3b SharedPtr =====
template <class T>
class SharedPtr {
    struct Ctrl { std::atomic<long> strong{1}; };
public:
    SharedPtr() = default;
    explicit SharedPtr(T* p) : p_(p), c_(p ? new Ctrl : nullptr) {}   // (production: if `new Ctrl` throws, delete p)
    SharedPtr(const SharedPtr& o) : p_(o.p_), c_(o.c_) {
        if (c_) c_->strong.fetch_add(1, std::memory_order_relaxed);      // increment needs no ordering
    }
    SharedPtr(SharedPtr&& o) noexcept : p_(std::exchange(o.p_, nullptr)), c_(std::exchange(o.c_, nullptr)) {}
    SharedPtr& operator=(SharedPtr o) noexcept { swap(o); return *this; } // copy-and-swap: copy, move and self-assign
    ~SharedPtr() { release(); }
    void swap(SharedPtr& o) noexcept { std::swap(p_, o.p_); std::swap(c_, o.c_); }
    T* get() const { return p_; }
    long use_count() const { return c_ ? c_->strong.load(std::memory_order_relaxed) : 0; }
    void reset() { release(); }
    T& operator*() const { return *p_; }
    T* operator->() const { return p_; }
    explicit operator bool() const { return p_ != nullptr; }
private:
    void release() {
        if (c_ && c_->strong.fetch_sub(1, std::memory_order_acq_rel) == 1) {  // last owner sees all prior writes
            delete p_;
            delete c_;
        }
        p_ = nullptr; c_ = nullptr;
    }
    T* p_ = nullptr;
    Ctrl* c_ = nullptr;
};

// ===== P12-4 FixedPool =====
class FixedPool {
    struct Slot { Slot* next; };
    static size_t roundUp(size_t n, size_t a) { return (n + a - 1) / a * a; }
public:
    FixedPool(size_t slotSize, size_t slotsPerBlock)
        : slotSize_(roundUp(std::max(slotSize, sizeof(Slot)), alignof(std::max_align_t))),
          perBlock_(std::max<size_t>(slotsPerBlock, 1)) {}
    ~FixedPool() { for (void* b : blocks_) ::operator delete(b); }
    FixedPool(const FixedPool&) = delete;
    FixedPool& operator=(const FixedPool&) = delete;
    void* allocate() {
        if (!free_) grow();
        Slot* s = free_;
        free_ = s->next;
        return s;
    }
    void deallocate(void* p) {
        if (!p) return;
        free_ = ::new (p) Slot{free_};                 // the free slot itself stores the link
    }
    size_t blockCount() const { return blocks_.size(); }
private:
    void grow() {
        void* block = ::operator new(slotSize_ * perBlock_);   // aligned to __STDCPP_DEFAULT_NEW_ALIGNMENT__
        blocks_.push_back(block);
        auto* base = static_cast<std::byte*>(block);
        for (size_t i = perBlock_; i-- > 0;)                    // push in reverse → allocation order is ascending
            free_ = ::new (base + i * slotSize_) Slot{free_};
    }
    size_t slotSize_, perBlock_;
    vector<void*> blocks_;
    Slot* free_ = nullptr;
};

// ===== P12-5 MyVector =====
template <class T>
class MyVector {
public:
    MyVector() = default;
    ~MyVector() { clearAndFree(); }
    MyVector(const MyVector&) = delete;
    MyVector& operator=(const MyVector&) = delete;
    void push_back(const T& v) { emplace(v); }
    void push_back(T&& v) { emplace(std::move(v)); }
    void pop_back() { data_[--size_].~T(); }
    void reserve(size_t n) { if (n > cap_) reallocate(n); }
    size_t size() const { return size_; }
    size_t capacity() const { return cap_; }
    T& operator[](size_t i) { return data_[i]; }
private:
    template <class... Args>
    void emplace(Args&&... args) {
        if (size_ < cap_) { ::new (data_ + size_) T(std::forward<Args>(args)...); ++size_; return; }
        size_t newCap = cap_ ? cap_ * 2 : 1;
        T* nd = static_cast<T*>(::operator new(newCap * sizeof(T)));
        try {
            ::new (nd + size_) T(std::forward<Args>(args)...);    // construct FIRST: args may alias old storage
        } catch (...) { ::operator delete(nd); throw; }
        moveInto(nd);
        data_ = nd; cap_ = newCap; ++size_;
    }
    void reallocate(size_t newCap) {
        T* nd = static_cast<T*>(::operator new(newCap * sizeof(T)));
        moveInto(nd);
        data_ = nd; cap_ = newCap;
    }
    void moveInto(T* nd) {                                        // relocate old elements, free old buffer
        for (size_t i = 0; i < size_; ++i) {
            ::new (nd + i) T(std::move_if_noexcept(data_[i]));   // copy if move could throw (strong guarantee)
            data_[i].~T();
        }
        ::operator delete(data_);
    }
    void clearAndFree() {
        for (size_t i = 0; i < size_; ++i) data_[i].~T();
        ::operator delete(data_);
        data_ = nullptr; size_ = cap_ = 0;
    }
    T* data_ = nullptr;
    size_t size_ = 0, cap_ = 0;
};

// ===== C3 BlockingQueue =====
template <class T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity) : cap_(capacity) {}
    bool push(T v) {
        std::unique_lock lk(m_);
        notFull_.wait(lk, [&] { return q_.size() < cap_ || closed_; });
        if (closed_) return false;
        q_.push_back(std::move(v));
        lk.unlock();
        notEmpty_.notify_one();
        return true;
    }
    std::optional<T> pop() {
        std::unique_lock lk(m_);
        notEmpty_.wait(lk, [&] { return !q_.empty() || closed_; });
        if (q_.empty()) return std::nullopt;                      // closed and drained
        T v = std::move(q_.front());
        q_.pop_front();
        lk.unlock();
        notFull_.notify_one();
        return v;
    }
    void close() {
        { std::lock_guard lk(m_); closed_ = true; }
        notEmpty_.notify_all();
        notFull_.notify_all();
    }
private:
    std::mutex m_;
    std::condition_variable notEmpty_, notFull_;
    std::deque<T> q_;
    size_t cap_;
    bool closed_ = false;
};

// ===== C3 printAlternately =====
std::string printAlternately(int n) {
    std::string out;
    std::mutex m;
    std::condition_variable cv;
    int next = 1;
    auto worker = [&](int parity) {
        while (true) {
            std::unique_lock lk(m);
            cv.wait(lk, [&] { return next > n || next % 2 == parity; });
            if (next > n) return;
            if (!out.empty()) out += ' ';
            out += std::to_string(next++);
            cv.notify_all();
        }
    };
    std::thread odd(worker, 1), even(worker, 0);
    odd.join(); even.join();
    return out;
}

// ===== C3 parallelSum =====
ll parallelSum(const VI& a, int threads) {
    threads = std::max(1, threads);
    size_t n = a.size(), chunk = (n + threads - 1) / threads;
    vector<ll> partial(threads, 0);                               // each thread writes ONCE → no false sharing in the loop
    vector<std::thread> ts;
    for (int t = 0; t < threads; ++t) {
        size_t lo = std::min(n, t * chunk), hi = std::min(n, lo + chunk);
        ts.emplace_back([&, t, lo, hi] {
            ll local = 0;
            for (size_t i = lo; i < hi; ++i) local += a[i];
            partial[t] = local;
        });
    }
    for (auto& th : ts) th.join();
    return std::accumulate(partial.begin(), partial.end(), 0LL);  // fixed-order reduction → deterministic
}

// ===== C3 ThreadPool =====
class ThreadPool {
public:
    explicit ThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) workers_.emplace_back([this] { loop(); });
    }
    ~ThreadPool() {
        { std::lock_guard lk(m_); stop_ = true; }
        cv_.notify_all();
        for (auto& t : workers_) t.join();
    }
    std::future<int> submit(std::function<int()> task) {
        std::packaged_task<int()> pt(std::move(task));
        auto f = pt.get_future();
        { std::lock_guard lk(m_); q_.push_back(std::move(pt)); }
        cv_.notify_one();
        return f;
    }
private:
    void loop() {
        while (true) {
            std::packaged_task<int()> task;
            {
                std::unique_lock lk(m_);
                cv_.wait(lk, [&] { return stop_ || !q_.empty(); });
                if (q_.empty()) return;                           // stop requested and drained
                task = std::move(q_.front());
                q_.pop_front();
            }
            task();                                               // run outside the lock
        }
    }
    vector<std::thread> workers_;
    std::deque<std::packaged_task<int()>> q_;
    std::mutex m_;
    std::condition_variable cv_;
    bool stop_ = false;
};

// ===== P12-D7 matrix =====
int** allocMatrix(int r, int c) {
    int** rows = new int*[r];
    int* block = new int[(size_t)r * c]();                        // one zero-initialized block
    for (int i = 0; i < r; ++i) rows[i] = block + (size_t)i * c;
    return rows;
}
void freeMatrix(int** m) {
    if (!m) return;
    delete[] m[0];                                                // the data block (assumes r >= 1)
    delete[] m;
}

#include "../tests/day4_tests.h"
