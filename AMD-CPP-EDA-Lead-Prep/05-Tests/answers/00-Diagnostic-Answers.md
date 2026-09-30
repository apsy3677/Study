# Diagnostic: Answer Key
Score 2 if you have the core fact; 3 if you also have the **(+lead)** point.

1. Load the vptr from the object → load the function pointer from the vtable slot → indirect call. **(+lead)** It blocks inlining; the cost is mostly the lost optimization and possible branch mispredicts, not the two loads. `final` and devirtualization help.
2. Deleting a derived object through a base pointer without a virtual dtor is **UB**; typically only `~Base` runs, so the derived members leak. **(+lead)** Alternative: a protected non-virtual dtor. `shared_ptr` created from `Derived*` still calls the right dtor.
3. An unconditional cast to an rvalue reference (`static_cast<T&&>`); it enables overload resolution to pick the move ops. The moved-from string is *valid but unspecified* (in practice empty). **(+lead)** `std::move` on a const object silently copies.
4. **0**: don't declare special members; use RAII members. **3**: if you need a custom dtor, copy ctor or copy assign, you need all three. **5**: plus the move ctor/assign. **(+lead)** Declaring a dtor/copy suppresses the implicit moves → silent copies.
5. `unique_ptr` = 1 pointer (stateless deleter). `shared_ptr` = 2 pointers. Plus a **control block** (strong + weak atomic counts, deleter), which `make_shared` allocates together with the object. **(+lead)** Atomic refcounting cost; pass by `const&`.
6. Copying a derived object into a base object by value copies only the base part: `void f(Base b); f(derived);`. Virtual calls on `b` use Base's versions.
7. On reallocation (size exceeds capacity) all iterators/refs are invalidated; insert/erase invalidate at or after the position. On reallocation, vector moves the elements only if the move ctor is `noexcept` (`move_if_noexcept`), otherwise it copies to keep the strong exception guarantee.
8. `map` = red-black tree, O(log n), ordered, stable iterators. `unordered_map` = hash table with chaining, O(1) average / O(n) worst, rehash invalidates iterators. Pick `map` for ordered iteration, floor/ceil, range queries, deterministic order, or worst-case guarantees. **(+lead)** Flat hash maps / sorted vectors for performance.
9. Tie a resource to an object's lifetime: acquire in the ctor, release in the dtor, so it's exception-safe. `unique_ptr`, `lock_guard`, `vector`, `fstream`, `jthread`.
10. `const int* p`: the pointee can't be modified through p (p can be reseated). `int* const p`: p can't be reseated. `const int& r`: can't modify through r, and it can bind temporaries (lifetime extension).
11. Signed overflow, out-of-bounds access, use-after-free, null deref, data race, uninitialized read, double delete, strict-aliasing violation, shifting by ≥ width, missing return.
12. Templates: zero-overhead, inlinable, compile-time dispatch. Virtual: runtime flexibility, heterogeneous containers, stable ABI/plugins, less code bloat.
13. A mutex has ownership (the locker unlocks) and gives mutual exclusion. A semaphore is a counter without ownership (any thread can signal) and is used to limit N concurrent holders or to signal.
14. Data race: unsynchronized concurrent access with ≥ 1 write, which is UB. Race condition: a timing-dependent logic bug; it can happen even with atomics (check-then-act).
15. Spurious wakeups, and lost/stolen wakeups (the condition changed before or after the notify). The predicate loop rechecks the real state under the lock.
16. Mutual exclusion, hold-and-wait, no preemption, circular wait. Prevent with a global lock ordering, or `std::scoped_lock` for multiple locks.
17. Separate vs shared address space; crash isolation; creation/switch cost; communication via IPC vs shared memory. (Linux: both are `clone()` tasks.)
18. 0 in the child, the child's PID in the parent, −1 on error. COW: pages are shared read-only and copied on the first write.
19. Different threads writing different variables that sit on the same cache line → the line bounces between cores → a big slowdown. Fix with padding/`alignas(64)` or local accumulation.
20. Via syscalls (`syscall` instruction), interrupts, or exceptions (e.g. a page fault). The CPU switches the privilege ring.
21. Prefix sum + hash map of prefix counts (seed {0:1}), O(n).
22. Sliding window with last-seen indices, O(n).
23. Binary search on the answer + a greedy feasibility check, O(n log range).
24. Monotonic (decreasing) stack of indices, O(n).
25. Min-heap of size k (top = k-th largest), O(log k) per element.
26. Sort by start + min-heap of end times (or a sweep with +1/−1 events), O(n log n).
27. `groupPrev`, `kth` (group end), `groupNext`, and prev/cur during the reversal. Use a dummy head.
28. Floyd: slow/fast meet; reset one to the head; step both by 1; they meet at the start.
29. Recursive: return the node if it matches a or b; if both the left and right results are non-null → the current node is the LCA. O(n).
30. Topological sort (Kahn); if the output count < n → a cycle, so it's impossible.
31. Coins outer, amount inner (ascending) → each combination is counted once. Amount outer → it counts permutations.
32. Hash map key→list iterator + a doubly linked list ordered by recency (`std::list` + `splice`).
33. Setup: data arrives early enough before the capture edge (a max-delay check). Hold: data doesn't change too soon after the capture edge (a min-delay check).
34. Topological order, `AT[v] = max(AT[u] + d)`. Longest path is only linear on a DAG; registers break the cycles, and combinational loops make timing ill-defined.
35. Half-perimeter wirelength: the net's bounding box width + height, a fast wirelength estimate.
36. Partitioning: FM / multilevel (hMETIS). Placement: simulated annealing / analytic (quadratic, ePlace). Routing: Lee/A* maze routing, PathFinder negotiated congestion.
37. L1 ~1 ns (4 cycles); DRAM ~80–100 ns.
38. When hot loops touch only a few fields of many objects: SoA streams just those fields → fewer cache misses, and SIMD-friendly.
39. ThreadSanitizer (race); ASan/LeakSanitizer or valgrind memcheck (leak); perf / VTune / AMD uProf (hotspot).
40. Half the memory of pointers, stable across reallocation, directly usable as array indices for side tables, and trivially serializable (checkpoints/mmap).
