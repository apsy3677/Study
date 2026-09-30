# C3: Concurrency & the C++ Memory Model

> JD: "modern concurrent programming and threading APIs". AMD ★★★: mutex vs semaphore, **thread-safe queue**, multithreading rounds, race-condition debugging.
> Practice: `06-Practice/day4.cpp` (`BlockingQueue`, `printAlternately`, `parallelSum`). Your own old folder `..\MultiThreading-C++` has thread/condvar exercises too.

---

## 1. Vocabulary you must get exactly right ★★★
| Term | Precise meaning |
|---|---|
| **Data race** | Two threads access the same memory location, at least one writes, and there's no happens-before ordering (no lock/atomic) → **UB** in C++. |
| **Race condition** | The result depends on timing/interleaving. A logic bug; can exist **without** a data race (e.g. check-then-act with atomics). |
| **Mutex** | Mutual exclusion; has an **owner**; only the locker unlocks. Sleeps (futex) under contention. |
| **Semaphore** | A counter with wait (P, decrement or block) and signal (V, increment). **No owner**; any thread can signal. Counting semaphore limits N concurrent users (pool of N connections). Binary semaphore ≈ a signal, not a lock. C++20 `std::counting_semaphore`. |
| **Spinlock** | Busy-waits on an atomic flag. Good only for very short critical sections on multicore where you don't want the thread to sleep; bad with oversubscription. |
| **Condition variable** | Wait until a predicate becomes true; always used **with a mutex** and **a predicate loop** (spurious wakeups, lost wakeups). |
| **Deadlock** | Circular wait. The 4 Coffman conditions: mutual exclusion, hold-and-wait, no preemption, circular wait. Break any one (usually: a **global lock order** or `std::scoped_lock(a, b)`, which uses a deadlock-avoidance algorithm). |
| **Livelock / starvation** | Threads keep reacting without progress / a thread never gets the resource. |
| **Atomic** | An indivisible read-modify-write, plus ordering guarantees by memory order. |

**"Mutex vs semaphore" 30-sec answer:** "A mutex is about **ownership**: one thread enters the critical section and the same thread leaves it. A semaphore is about **counting/signalling**: it allows up to N holders, and any thread can post. I use a mutex to protect data, a counting semaphore to bound concurrency, and a condition variable (or semaphore) to signal events."

## 2. The standard toolkit
```cpp
std::thread t(fn, args...); t.join();          // must join or detach before destruction (else std::terminate)
std::jthread jt(fn);                           // C++20: joins in its destructor, supports stop_token
std::mutex m; std::lock_guard<std::mutex> g(m);                // scoped lock
std::unique_lock<std::mutex> ul(m);            // movable, unlockable; required by condition_variable
std::scoped_lock lk(m1, m2);                   // C++17: locks several without deadlock
std::shared_mutex rw; std::shared_lock r(rw); std::unique_lock w(rw);   // readers-writer
std::condition_variable cv; cv.wait(ul, [&]{ return ready; });          // ALWAYS with a predicate
std::atomic<int> cnt{0}; cnt.fetch_add(1, std::memory_order_relaxed);
std::once_flag f; std::call_once(f, init);     // or a function-local static (thread-safe since C++11)
auto fut = std::async(std::launch::async, work); fut.get();            // future/promise
std::latch, std::barrier (C++20)               // phase synchronization
```
`std::thread` args are **copied**; use `std::ref(x)` to pass by reference.

## 3. Thread-safe bounded blocking queue ★★★ (write this blind in 8 minutes)
```cpp
template <class T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t cap) : cap_(cap) {}
    bool push(T v) {                                             // false if closed
        std::unique_lock lk(m_);
        notFull_.wait(lk, [&]{ return q_.size() < cap_ || closed_; });
        if (closed_) return false;
        q_.push_back(std::move(v));
        lk.unlock();                                             // optional: notify without holding the lock
        notEmpty_.notify_one();
        return true;
    }
    std::optional<T> pop() {                                     // nullopt when closed AND drained
        std::unique_lock lk(m_);
        notEmpty_.wait(lk, [&]{ return !q_.empty() || closed_; });
        if (q_.empty()) return std::nullopt;
        T v = std::move(q_.front()); q_.pop_front();
        lk.unlock();
        notFull_.notify_one();
        return v;
    }
    void close() {
        { std::lock_guard lk(m_); closed_ = true; }
        notEmpty_.notify_all(); notFull_.notify_all();
    }
private:
    std::mutex m_;
    std::condition_variable notEmpty_, notFull_;
    std::deque<T> q_;
    size_t cap_;
    bool closed_ = false;
};
```
**Talking points:** why the predicate (spurious and stolen wakeups) · why two condvars (producers vs consumers) · shutdown semantics (`close` + drain) · `pop` returns `optional` rather than `T&` (can't return a reference to a popped element; `front()`+`pop()` as separate calls is a race) · exception safety of `T`'s move · for high throughput: batching, lock-free SPSC ring (P12-D2), or MPMC (e.g. moodycamel).

## 4. Classic coding exercises
- **Print odd/even alternately with 2 threads** (or ping-pong, or 3 threads printing in turn): one mutex + one condvar + a shared `turn` variable; each thread waits for `turn == me`, prints, flips the turn, `notify_all`.
- **Parallel sum**: split into chunks → `std::async` or threads writing to `partial[i]` → reduce. Beware **false sharing** if the `partial[i]` are adjacent `long long`s updated in the loop (accumulate in a local, write once).
- **Thread pool**: a vector of workers looping on `BlockingQueue<std::function<void()>>`; `submit` returns a `std::future` via `std::packaged_task`; the destructor closes the queue and joins.
- **Reader-writer cache**: `shared_mutex` + double-checked lookup (shared lock → miss → unique lock → re-check → insert).
- **Spinlock:**
```cpp
class SpinLock { std::atomic_flag f = ATOMIC_FLAG_INIT;
public: void lock() { while (f.test_and_set(std::memory_order_acquire)) { /* _mm_pause(); */ } }
        void unlock() { f.clear(std::memory_order_release); } };
```

## 5. Memory model & atomics ★★ (lead-level depth)
- Compilers and CPUs **reorder** memory operations. Atomics and locks create **happens-before** edges.
- `memory_order_seq_cst` (default): a single total order, the easiest to reason about, and on x86 it costs a fence on stores (`xchg`/`mfence`).
- **acquire/release:** a release store "publishes" all earlier writes; an acquire load that reads that value "sees" them. The classic pattern: producer writes data, then `ready.store(true, release)`; consumer does `while(!ready.load(acquire));` then reads the data safely.
- `relaxed`: atomicity only, no ordering. Fine for counters/statistics.
- `acq_rel` for RMW (refcount decrement in `shared_ptr`).
- **x86-64 is TSO** (strong): only store→load reordering is visible, so acquire/release are almost free there. ARM/POWER are weak. Code must be correct by the **C++ model**, not the CPU.
- **CAS loop:** `while (!a.compare_exchange_weak(expected, desired)) {}` (weak can fail spuriously, so loop). **ABA problem** in lock-free stacks → tagged pointers / hazard pointers / epoch reclamation.
- `volatile` ≠ atomic (see C1).
- **Double-checked locking** is correct only with atomics (acquire/release) or `call_once`/function-local statics.

## 6. Performance of concurrent code ★★ (the JD is about perf)
| Issue | Symptom | Fix |
|---|---|---|
| **False sharing** | threads write different variables on the **same 64-byte cache line** → the line ping-pongs between cores (MESI invalidations); scaling collapses | `alignas(64)` / `std::hardware_destructive_interference_size`, per-thread local accumulation |
| Lock contention | throughput flat as threads grow; high `futex` time in `perf` | shrink critical sections, shard the locks (striped locking), RW locks, lock-free for hot paths, batch work |
| Oversubscription | more runnable threads than cores → context switching | a thread pool sized to the cores; work stealing (TBB) |
| Load imbalance | some threads idle while one finishes | dynamic scheduling / smaller chunks / work stealing |
| Amdahl's law | speedup ≤ 1 / (s + (1−s)/N) | measure the serial fraction s. If 10% is serial, the max speedup is 10× regardless of cores |
| NUMA (AMD EPYC chiplets!) | remote memory access is slower | first-touch allocation by the worker thread, pin threads (`numactl`, affinity), per-NUMA pools |
| Memory allocator contention | `malloc` lock in hot loops | per-thread arenas (tcmalloc/jemalloc/mimalloc), pools |

## 7. Parallelism in EDA tools ★★ (your differentiator)
- **Determinism is a requirement:** the same input must give the same QoR regardless of thread count or scheduling (customers file bugs otherwise, and it's needed for debug and regression). Sources of non-determinism: iteration over `unordered_map` (hash order), pointer-address ordering (`set<Obj*>`), race-dependent "first finisher wins", **floating-point reduction order**, uninitialized memory.
  Fixes: sort by stable IDs, deterministic partitioning, per-thread results merged in a fixed order, fixed-order reductions, deterministic task graphs.
- **Common patterns:** partition the design (your DPV partitioning + multiprocessing work!) · level-by-level parallel propagation in timing (the nodes in a level are independent) · parallel net routing with conflict detection (nets in disjoint bounding boxes in parallel; conflicts get serialized or rip-up) · multi-start placement · processes vs threads (processes give isolation and a separate address space, which scales past one host's memory; threads share memory, which is cheaper to communicate).
- Frameworks: `std::thread` + pools, **Intel oneTBB** (task graphs, `parallel_for`, concurrent containers), **OpenMP** (`#pragma omp parallel for reduction(+:x)`), Taskflow.

## 8. Debugging concurrency
- **ThreadSanitizer** (`-fsanitize=thread`) finds data races (5–15× slowdown). Helgrind/DRD (valgrind).
- Deadlock: `gdb -p <pid>` → `thread apply all bt` → look for two threads each waiting on a mutex held by the other. Prevent it with lock ordering plus lock-order checking in debug builds.
- Heisenbugs: add stress tests (many threads, random sleeps/yields), run under `rr` (record & replay), and use TSan in CI.

---

## Self-test
1. Data race vs race condition, with an example of a race condition with no data race.
2. Why must `cv.wait` use a predicate? Name two wakeup problems.
3. Write the `BlockingQueue` from memory. Why two condvars? How does shutdown work?
4. acquire/release: explain the "publish data with a flag" pattern.
5. What is false sharing; how do you detect it (`perf c2c`!) and fix it?
6. Amdahl: with 20% serial code, what's the max speedup on 64 cores?
7. Three sources of non-determinism in a parallel EDA algorithm and a fix for each.
8. Mutex vs spinlock vs semaphore: when do you use each?
