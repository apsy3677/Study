# P12: Design-a-Data-Structure / Systems Coding

> Practice files: `06-Practice/day2.cpp` (LRU), `06-Practice/day4.cpp` (ring buffer, smart pointers, pool allocator, vector, blocking queue)
> AMD reports: **LRU Cache** (★★★), **ring buffer + custom memory allocator** (TechPrep 2026), **how are smart pointers implemented internally** (AmbitionBox), **thread-safe queue** (Glassdoor), 2D matrix with raw pointers, implement stack/queue, **multi-level cache** design.

For every design question, use the **same opening**: *"Let me pin down the operations and their required complexity, the capacity/ownership rules, and whether it must be thread-safe."*

---

## D1. LRU Cache = hash map (find) + doubly linked list (order)
| | |
|---|---|
| **Hook** | The map answers **"where is it?"** in O(1). The list answers **"who's oldest?"** in O(1). Each map value is an **iterator** into the list. |
| **Ops** | `get`: find → splice to front → return. `put`: if present, update + splice; else if full, evict back (erase from the map too!), then emplace front + record the iterator. |
| **Traps** | Forgetting to erase the evicted key from the map. Capacity 0. Updating the value of an existing key without moving it to the front. |
| **Follow-ups** | **Thread-safe** → one mutex (simple) or sharded LRU (N shards by hash, each with its own lock) for scalability; `get` mutates the order, so even reads need the lock (or use approximate LRU / CLOCK). **LFU** → map key→(val,freq,iter) + map freq→list + minFreq. **TTL** → add an expiry time and a min-heap. **Multi-level cache** (AMD) → L1 small/fast, L2 larger; inclusive vs exclusive; write-through vs write-back; promotion on hit. |

## D2. Ring buffer (circular queue), fixed capacity
| | |
|---|---|
| **Hook** | An array plus two indices chasing each other around a circle. |
| **Full vs empty ambiguity** | `head == tail` could mean either. Fix: keep a `count` **or** waste one slot **or** use monotonically increasing 64-bit indices (`tail - head == cap` means full) with `idx % cap` (or `& (cap-1)` when cap is a power of 2). |
| **Ops** | `push`: if full → return false (or overwrite oldest, depending on policy); `buf[tail] = x; tail = (tail+1) % cap;`. `pop`: symmetric. |
| **Lead follow-ups** | SPSC lock-free ring: head written only by the consumer, tail only by the producer, as `std::atomic<size_t>` with **acquire/release**. Pad head and tail to separate cache lines (`alignas(64)`) to avoid **false sharing**. Used for logging, audio/DMA buffers, and producer/consumer pipelines. |

## D3. `unique_ptr` and `shared_ptr` from scratch
**unique_ptr** = raw pointer + deleter; **move-only**:
- copy ctor/assign `= delete`; move ctor steals and nulls the source; move assign = `reset(other.release())`.
- `~UniquePtr() { delete p; }`, `release()`, `reset(p)`, `get()`, `operator*`, `operator->`, `explicit operator bool`.
- Size = one pointer (with an empty deleter via EBO).

**shared_ptr** = pointer to the object **+ pointer to a control block** `{ atomic<long> strong; atomic<long> weak; deleter; (object storage if make_shared) }`:
- copy: `++strong` (atomic, `memory_order_relaxed` is enough for increment).
- destroy/reset: `if (--strong == 0) { destroy object; if (--weak == 0) delete control block; }` (decrement with **acq_rel** so the deleting thread sees all writes).
- `weak_ptr` holds the control block alive (the weak count) but not the object; `lock()` = CAS loop "increment strong if > 0".
- `make_shared`: **one allocation** (object + control block together), better locality. **But** the object's memory isn't freed until the last `weak_ptr` dies.
- **Thread safety:** the refcount is thread-safe; the pointee is **not**; the *same* `shared_ptr` instance being written by two threads is a race (use `atomic<shared_ptr<T>>` in C++20).
- Cycles leak → break with `weak_ptr` (parent owns child via shared, child→parent via weak).
- `enable_shared_from_this` holds a weak_ptr to self; calling `shared_from_this()` on an object not owned by a shared_ptr throws `bad_weak_ptr` (C++17).

## D4. Pool / arena allocator
| | |
|---|---|
| **Why** | `malloc` per small object costs ~20–100 ns, has headers (8–16 B), fragments the heap and scatters objects in memory. EDA tools allocate **millions of identical small objects** (pins, nets, timing arcs). |
| **Fixed-size pool** | carve a big block into equal slots; keep a **free list threaded through the free slots themselves** (the first bytes of a free slot store the next pointer). alloc = pop the free list; free = push. O(1), no per-object header. |
| **Arena / bump allocator** | pointer += size (aligned); free everything at once (per-phase lifetimes: parse → build → discard). |
| **Care** | alignment (`alignof(T)`, `std::align`), slot size ≥ `sizeof(void*)`, construct with **placement new** and destroy with an explicit `p->~T()`, thread-safety (per-thread pools), debug mode poisoning. C++17 `std::pmr::monotonic_buffer_resource` / `unsynchronized_pool_resource` are the standard versions. |

```cpp
class FixedPool {                       // sketch; day4.cpp has the full exercise
    struct Slot { Slot* next; };
    vector<unique_ptr<std::byte[]>> blocks_; Slot* free_ = nullptr; size_t slotSize_, perBlock_;
public:
    FixedPool(size_t sz, size_t perBlock) : slotSize_(max(sz, sizeof(Slot))), perBlock_(perBlock) {}
    void* allocate();                   // if (!free_) grow(); pop free_
    void deallocate(void* p);           // push p onto free_
};
```

## D5. `vector` from scratch (a favourite follow-up to "how does vector work?")
- Members: `T* data_; size_t size_, cap_;`
- `push_back`: if full → allocate `max(1, 2*cap)` **raw** memory (`operator new(n*sizeof(T))`), **move-construct** the elements if `T`'s move ctor is `noexcept` (else copy; this is **why noexcept matters**), destroy the old ones, free the old memory, then placement-new the new element.
- Growth factor: 2 (libstdc++) or 1.5 (MSVC). Amortized O(1) by the doubling argument (total copies ≤ 2n).
- Iterator invalidation: any reallocation invalidates **all** iterators, pointers and references.

## D6. Thread-safe blocking queue (see C3 for the full treatment)
`mutex` + `condition_variable notEmpty, notFull` + `deque<T>`. `push` waits on notFull; `pop` waits on notEmpty with a **predicate** (spurious wakeups). Add a `close()` / shutdown flag so the consumers exit. Notify **after** the state change (outside the lock is fine and slightly faster).

## D7. 2D matrix with raw pointers (AmbitionBox)
Two ways: (a) `int** m = new int*[r]; for each row new int[c]` → r+1 allocations, rows scattered; (b) **one contiguous block** `new int[r*c]` + row pointers into it, or just index `i*c + j`. Always prefer (b): locality, one delete, simpler exception safety. In real code, `vector<int>(r*c)` + an accessor.

## D8. External sort ("implement file sorting in C++" / sort a 100 GB file with 4 GB RAM)
1. Read chunks that fit in memory → sort each (`std::sort`) → write sorted **runs**.
2. **k-way merge** the runs with a min-heap of (value, runIndex), using buffered reads/writes.
3. If there are too many runs for the open-file limit → multi-pass merge.
Talk about I/O being the bottleneck (sequential reads, large buffers), parallel run sorting, and replacement selection (runs of 2× memory).

---

## Problems (hint ladders)
### P12-1 · LRU Cache (LC 146) ★★★ · `LRUCache` in day2.cpp (the toolkit has a reference: write it blind first)
<details><summary>Hint</summary>What must the map's value be so that you can move a node in O(1)?</details>

### P12-2 · Ring buffer ★★ · `RingBuffer<T>` in day4.cpp
<details><summary>Hint</summary>Decide how you'll distinguish full from empty before writing any code.</details>

### P12-3 · UniquePtr / SharedPtr ★★ · day4.cpp
<details><summary>Hint (shared)</summary>What lives in the control block, and when is each thing (object, block) destroyed?</details>

### P12-4 · Fixed-size pool allocator ★★ · `FixedPool` in day4.cpp
<details><summary>Hint</summary>Where can you store the free-list "next" pointer without extra memory?</details>

### P12-5 · MyVector push_back/reserve ★ · day4.cpp
<details><summary>Hint</summary>Separate allocation from construction (operator new + placement new).</details>

### P12-6 · LFU Cache (LC 460) ★ (stretch)
<details><summary>Approach check</summary>key→{val, freq, iterator}; freq→list of keys; track minFreq; on access move the key from list f to f+1; evict the back of list[minFreq]. All O(1).</details>

---

## Recall check
1. LRU: the two structures and why each. 2. The three ways to tell a full ring buffer from an empty one. 3. What's inside a `shared_ptr` control block? Which ops are atomic?
4. Why does `vector` growth care about `noexcept`? 5. Where does a pool allocator store its free list? 6. External sort in 3 steps.
