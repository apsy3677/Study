# Flashcards (active recall)

> **How:** read the question, **answer out loud**, then open the answer. Mark misses in PROGRESS.md and re-test them the next morning.
> **Phone/Anki:** import `flashcards_anki.tsv` (File → Import; fields: Front, Back, Tags) for automatic spaced repetition.
> Generated from `flashcards_anki.tsv`, so edit that file and keep both in sync.

## C++ language (30)

1. **What does a virtual call compile to?**
   <details><summary>answer</summary>Load vptr from object → load function pointer from vtable slot → indirect call. Main cost: no inlining.</details>

2. **Virtual function called in a base constructor dispatches to…?**
   <details><summary>answer</summary>The base version (vptr = Base vtable during Base ctor). Pure virtual there = UB/abort.</details>

3. **Delete Derived via Base&#42; with non-virtual ~Base?**
   <details><summary>answer</summary>UB; typically only ~Base runs → derived resources leak. Fix: virtual ~Base (or protected non-virtual).</details>

4. **shared_ptr&lt;Base&gt;(new Derived) with non-virtual ~Base: ~Derived called?**
   <details><summary>answer</summary>Yes — the control block captures Derived's deleter. unique_ptr&lt;Base&gt; would NOT.</details>

5. **Default arguments on virtual functions are bound…?**
   <details><summary>answer</summary>Statically (by the static type) — body dynamic, default arg static. Never change defaults in overrides.</details>

6. **Object slicing?**
   <details><summary>answer</summary>Copying Derived into Base by value keeps only the Base subobject (Base vptr). Pass by reference/pointer.</details>

7. **sizeof(empty class)? sizeof(class with one virtual)?**
   <details><summary>answer</summary>1 (unique address); 8 on x86-64 (vptr).</details>

8. **Name hiding fix?**
   <details><summary>answer</summary>A derived f(double) hides all base f overloads → add `using Base::f;`.</details>

9. **What does std::move do?**
   <details><summary>answer</summary>static_cast to T&amp;&amp; — enables move overloads. Moves nothing itself. Moved-from = valid but unspecified.</details>

10. **std::move on a const object?**
   <details><summary>answer</summary>Yields const T&amp;&amp; → binds copy ctor → silent copy.</details>

11. **std::forward purpose?**
   <details><summary>answer</summary>Perfect forwarding: preserves the caller's value category for forwarding references (T&amp;&amp; in templates).</details>

12. **Rule of 0 / 3 / 5?**
   <details><summary>answer</summary>0: no custom special members (RAII members). 3: dtor+copy ctor+copy assign together. 5: plus move ctor/assign.</details>

13. **Declaring a destructor affects implicit moves how?**
   <details><summary>answer</summary>Suppresses implicit move ctor/assign → the class silently copies.</details>

14. **Why must move ctor be noexcept?**
   <details><summary>answer</summary>vector uses move_if_noexcept on reallocation; throwing move → it copies to keep the strong guarantee.</details>

15. **return std::move(local)?**
   <details><summary>answer</summary>Pessimization: blocks NRVO. Just `return local;`.</details>

16. **RAII in one line?**
   <details><summary>answer</summary>Resource lifetime bound to object scope: acquire in ctor, release in dtor → exception-safe, no leaks.</details>

17. **unique_ptr size and copyability?**
   <details><summary>answer</summary>One pointer (stateless deleter); move-only.</details>

18. **shared_ptr control block contains?**
   <details><summary>answer</summary>Strong count, weak count (atomic), deleter/allocator, and the object if make_shared.</details>

19. **make_shared pro and con?**
   <details><summary>answer</summary>One allocation + locality. Con: object memory held until last weak_ptr dies.</details>

20. **shared_ptr thread-safety?**
   <details><summary>answer</summary>Refcount atomic; pointee not synchronized; same instance written by 2 threads = race (use atomic&lt;shared_ptr&gt;).</details>

21. **weak_ptr::lock()?**
   <details><summary>answer</summary>Atomically increments strong count if &gt; 0 (CAS loop); returns empty if expired.</details>

22. **Lambda capturing [this] stored in async callback — risk?**
   <details><summary>answer</summary>Object may be destroyed before callback runs → dangling. Capture weak_ptr (shared_from_this).</details>

23. **volatile for threads?**
   <details><summary>answer</summary>No. volatile = don't elide accesses (MMIO). Not atomic, no ordering. Use std::atomic.</details>

24. **Static init order fiasco fix?**
   <details><summary>answer</summary>Construct on first use: function-local static (thread-safe since C++11).</details>

25. **new vs malloc?**
   <details><summary>answer</summary>new = allocate + construct, throws bad_alloc; malloc = raw bytes, NULL, no ctor. Never mix with free/delete.</details>

26. **Placement new?**
   <details><summary>answer</summary>Construct object in existing memory: new (buf) T(args); destroy with p-&gt;~T().</details>

27. **Throwing from a destructor?**
   <details><summary>answer</summary>Destructors are noexcept → std::terminate.</details>

28. **CRTP?**
   <details><summary>answer</summary>template&lt;class D&gt; struct Base { void f(){ static_cast&lt;D&#42;&gt;(this)-&gt;impl(); } }; static polymorphism, no vtable.</details>

29. **string_view risk?**
   <details><summary>answer</summary>Non-owning → dangling if source dies (e.g., bound to a temporary string).</details>

30. **Five UB examples?**
   <details><summary>answer</summary>Signed overflow, OOB, use-after-free, data race, uninitialized read (also: null deref, strict aliasing, shift ≥ width).</details>

## STL (9)

1. **vector growth factor and cost?**
   <details><summary>answer</summary>×2 (libstdc++) / ×1.5 (MSVC); amortized O(1) push_back; reallocation invalidates all iterators/refs.</details>

2. **unordered_map rehash invalidates…?**
   <details><summary>answer</summary>Iterators (not references/pointers to elements). reserve(n) avoids rehash.</details>

3. **map vs unordered_map?**
   <details><summary>answer</summary>RB-tree O(log n) ordered, floor/ceil, stable iterators vs hash O(1) avg / O(n) worst, unordered.</details>

4. **map[k] on a missing key?**
   <details><summary>answer</summary>Inserts a value-initialized element. Use find/count/contains for reads.</details>

5. **std::sort algorithm &amp; stability?**
   <details><summary>answer</summary>Introsort (quick + heap + insertion), not stable. stable_sort = merge sort.</details>

6. **std::lower_bound on std::set?**
   <details><summary>answer</summary>O(n) (bidirectional iterators). Use s.lower_bound(x): O(log n).</details>

7. **Min-heap declaration?**
   <details><summary>answer</summary>priority_queue&lt;int, vector&lt;int&gt;, greater&lt;int&gt;&gt;. Comparator(a,b)=true means a has LOWER priority.</details>

8. **Erase from vector/map while iterating?**
   <details><summary>answer</summary>it = c.erase(it); else ++it. Or std::erase_if (C++20).</details>

9. **deque iterator/reference validity on push_back?**
   <details><summary>answer</summary>References stay valid; iterators invalidated.</details>

## Concurrency (12)

1. **Data race vs race condition?**
   <details><summary>answer</summary>Data race: unsynchronized concurrent access with a write → UB. Race condition: timing-dependent logic bug (can exist with atomics).</details>

2. **Mutex vs semaphore?**
   <details><summary>answer</summary>Mutex: ownership, mutual exclusion. Semaphore: counter, no owner, limits N / signals.</details>

3. **Why predicate in cv.wait?**
   <details><summary>answer</summary>Spurious wakeups + state may change (stolen/lost wakeup). Re-check under lock.</details>

4. **Bounded blocking queue ingredients?**
   <details><summary>answer</summary>mutex, 2 condvars (notFull/notEmpty), deque, capacity, closed flag; pop returns optional.</details>

5. **Deadlock conditions &amp; prevention?**
   <details><summary>answer</summary>Mutual exclusion, hold-and-wait, no preemption, circular wait. Global lock order / std::scoped_lock.</details>

6. **acquire/release publish pattern?**
   <details><summary>answer</summary>Producer: write data; flag.store(true, release). Consumer: while(!flag.load(acquire)); read data safely.</details>

7. **shared_ptr refcount memory orders?**
   <details><summary>answer</summary>Increment relaxed; decrement acq_rel (the deleter must see all prior writes).</details>

8. **False sharing?**
   <details><summary>answer</summary>Threads write different vars on same 64B cache line → line ping-pong. Fix: alignas(64), local accumulation.</details>

9. **Amdahl's law?**
   <details><summary>answer</summary>Speedup ≤ 1/(s + (1−s)/N). 5% serial on 128 cores ≈ 17×.</details>

10. **ABA problem?**
   <details><summary>answer</summary>CAS sees A→B→A and wrongly succeeds (lock-free with memory reuse). Fix: tagged pointers, hazard pointers, epochs.</details>

11. **Tool to find data races?**
   <details><summary>answer</summary>ThreadSanitizer (-fsanitize=thread); also helgrind/DRD.</details>

12. **Sources of non-determinism in parallel EDA code?**
   <details><summary>answer</summary>Hash/pointer-order iteration, first-finisher-wins, FP reduction order, uninit memory, time seeds.</details>

## OS (9)

1. **Process vs thread?**
   <details><summary>answer</summary>Own vs shared address space; crash isolation; cost; IPC vs shared memory. Linux: both clone() tasks.</details>

2. **fork() return values &amp; COW?**
   <details><summary>answer</summary>0 in child, child PID in parent, −1 error. Pages shared read-only, copied on first write.</details>

3. **fork() in multithreaded program — danger?**
   <details><summary>answer</summary>Only calling thread survives; locks held by others stay locked → child deadlocks (e.g., malloc). exec ASAP / posix_spawn.</details>

4. **Zombie vs orphan?**
   <details><summary>answer</summary>Zombie: exited, not reaped by parent. Orphan: parent died → reparented to init which reaps it.</details>

5. **User → kernel mode entry?**
   <details><summary>answer</summary>Syscalls, interrupts, exceptions (page faults).</details>

6. **Process memory layout (low→high)?**
   <details><summary>answer</summary>text, rodata, data, bss, heap↑ … mmap … stack↓, kernel.</details>

7. **Minor vs major page fault?**
   <details><summary>answer</summary>Minor: page in memory (map it; first-touch/COW). Major: read from disk/swap.</details>

8. **TLB &amp; huge pages?**
   <details><summary>answer</summary>TLB caches translations; huge pages (2MB/1GB) cut TLB misses for big heaps.</details>

9. **MESI/MOESI?**
   <details><summary>answer</summary>Cache coherence states: Modified, (Owned), Exclusive, Shared, Invalid. AMD uses MOESI.</details>

## Performance & tooling (10)

1. **Cache line size &amp; DRAM latency?**
   <details><summary>answer</summary>64 bytes; ~80–100 ns (L1 ~1 ns).</details>

2. **Performance methodology?**
   <details><summary>answer</summary>Benchmark+metric → profile (where, why) → hypothesis/smallest change → measure A/B → guard in CI + communicate.</details>

3. **perf stat vs perf record?**
   <details><summary>answer</summary>stat: aggregate counters (IPC, misses). record: sampled stacks → report/flame graph.</details>

4. **AoS vs SoA?**
   <details><summary>answer</summary>SoA wins when hot loops touch few fields of many objects (less memory traffic, SIMD).</details>

5. **Why 32-bit ids instead of pointers in netlist DB?**
   <details><summary>answer</summary>Half size, stable on realloc, index side tables, serializable/mmap-able.</details>

6. **Crash only in release — likely causes?**
   <details><summary>answer</summary>UB exploited by optimizer, races, uninitialized vars, ODR/ABI mismatch. Build -g, sanitizers, core dump, bisect flags.</details>

7. **RSS grows but no leak reported?**
   <details><summary>answer</summary>Reachable growth (caches/containers) or fragmentation. Heaptrack/massif snapshots; compare live bytes vs RSS; try jemalloc.</details>

8. **NUMA on EPYC?**
   <details><summary>answer</summary>Remote memory slower; use first-touch by workers, interleave, pin threads, per-node pools.</details>

9. **PGO?**
   <details><summary>answer</summary>Profile-guided optimization: build instrumented, run training, rebuild with profile → better inlining/layout (5–15%).</details>

10. **Tool for heap growth over time?**
   <details><summary>answer</summary>heaptrack / valgrind massif.</details>

## DSA patterns (22)

1. **Prefix sum + hash map pattern?**
   <details><summary>answer</summary>Subarray sum = k (negatives OK): count[prefix − k]; seed {0:1}.</details>

2. **Sliding window works only if…?**
   <details><summary>answer</summary>Validity is monotone (shrinking valid stays valid). Negatives in sum break it.</details>

3. **Longest vs shortest window: where to record?**
   <details><summary>answer</summary>Longest: after shrinking-while-invalid. Shortest: inside while-valid, before shrinking.</details>

4. **Binary search first-true template?**
   <details><summary>answer</summary>while(lo&lt;hi){mid=lo+(hi−lo)/2; if(ok(mid)) hi=mid; else lo=mid+1;} return lo;</details>

5. **Binary search on answer — triggers?**
   <details><summary>answer</summary>"Minimum capacity/speed/time such that feasible", "minimize the max".</details>

6. **Rotated sorted array key insight?**
   <details><summary>answer</summary>One half is always sorted; check if target is inside it.</details>

7. **Monotonic stack invariant (next greater)?**
   <details><summary>answer</summary>Stack of indices with decreasing values = elements waiting for an answer. O(n).</details>

8. **Sliding window maximum?**
   <details><summary>answer</summary>Monotonic deque of indices, decreasing values; pop front if expired, pop back if ≤ new.</details>

9. **Top-K largest?**
   <details><summary>answer</summary>Min-heap of size k (O(n log k)) or nth_element O(n) avg.</details>

10. **Meeting rooms?**
   <details><summary>answer</summary>Sort by start + min-heap of ends (pop while top ≤ start) or sweep +1/−1 (ends before starts at ties).</details>

11. **Merge intervals?**
   <details><summary>answer</summary>Sort by start; if cur.start ≤ last.end → last.end = max(last.end, cur.end).</details>

12. **Reverse list loop body?**
   <details><summary>answer</summary>nxt=cur-&gt;next; cur-&gt;next=prev; prev=cur; cur=nxt; return prev.</details>

13. **Floyd cycle start?**
   <details><summary>answer</summary>After meet, reset one to head; move both 1 step; they meet at start (a = kL − b).</details>

14. **Palindrome list O(1) space?**
   <details><summary>answer</summary>Middle → reverse 2nd half → compare → restore.</details>

15. **LRU cache?**
   <details><summary>answer</summary>unordered_map&lt;key, list::iterator&gt; + list (front = recent); splice to front; evict back.</details>

16. **Tree recursion question?**
   <details><summary>answer</summary>What do I need from children (bottom-up) / what do I pass down (top-down)?</details>

17. **LCA recursion?**
   <details><summary>answer</summary>If node is a/b return it; recurse both; if both non-null → node; else the non-null one.</details>

18. **Validate BST?**
   <details><summary>answer</summary>Pass (lo, hi) bounds down; strict; use long long / pointers for bounds.</details>

19. **Balanced tree in O(n)?**
   <details><summary>answer</summary>Return −1 for unbalanced, else height; short-circuit.</details>

20. **Backtracking template?**
   <details><summary>answer</summary>choose → explore → un-choose; sort + skip dup at same depth.</details>

21. **x &amp; (x−1) and x &amp; −x?**
   <details><summary>answer</summary>Drop lowest set bit; isolate lowest set bit.</details>

22. **Fast power mod?**
   <details><summary>answer</summary>Square-and-multiply: while b: if b&amp;1 r=r&#42;a%m; a=a&#42;a%m; b&gt;&gt;=1. Reduce a%=m first.</details>

## Graphs (15)

1. **Frontier → algorithm?**
   <details><summary>answer</summary>FIFO=BFS, min-heap=Dijkstra, deque=0-1 BFS, indegree-0 queue=Kahn.</details>

2. **BFS visited marking?**
   <details><summary>answer</summary>Mark on push, not pop.</details>

3. **Bipartite check trap?**
   <details><summary>answer</summary>Disconnected graph — start BFS from every uncolored node. Failure = same-color edge (odd cycle).</details>

4. **Directed cycle detection?**
   <details><summary>answer</summary>3-color DFS (gray→gray = back edge) or Kahn count &lt; n.</details>

5. **Union-Find complexity?**
   <details><summary>answer</summary>Path compression + union by size → α(n) ≈ O(1).</details>

6. **Dijkstra stale entries?**
   <details><summary>answer</summary>No decrease-key: push duplicates; on pop skip if d != dist[u].</details>

7. **Kosaraju SCC?**
   <details><summary>answer</summary>Finish, Flip, Flood: DFS and record the finish order → reverse every edge → latest finisher first, DFS on the reversed graph; each flood = one SCC.</details>

8. **CSR graph?**
   <details><summary>answer</summary>offsets[n+1] + targets[E]: contiguous adjacency, cache-friendly, one allocation.</details>

9. **Why does Kosaraju flip the graph and start from the latest finisher?**
   <details><summary>answer</summary>The last finisher is in a top (source) SCC. Flipping keeps every SCC but turns the top into the bottom, so a DFS from it can't leak out of its own SCC.</details>

10. **Why does an upstream SCC finish later in a DFS?**
   <details><summary>answer</summary>Enter A first: A reaches all of B, so B finishes before A's first node returns. Enter B first: B can't reach A, so B is done before A starts.</details>

11. **Tarjan: when is u an SCC head, and which edges update low?**
   <details><summary>answer</summary>When low[u] == disc[u]. Tree edge: low[u] = min(low[u], low[v]). Any other edge: only if v is on the stack, low[u] = min(low[u], disc[v]).</details>

12. **Fewest edges to make a digraph strongly connected?**
   <details><summary>answer</summary>Condense the SCCs; answer max(#source SCCs, #sink SCCs), or 0 if there's only one SCC.</details>

13. **Bipartite ⇔ ?**
   <details><summary>answer</summary>No odd cycle. Two teams: every edge flips the team, so an odd cycle lands you on the wrong team.</details>

14. **Bipartite: how do you return an odd cycle as proof?**
   <details><summary>answer</summary>Keep the BFS parent. A same-color edge u–v joins two nodes in the same layer; walk both up until they meet. u…ancestor…v plus the edge v–u is a cycle of 2k+1 edges.</details>

15. **Where do bipartite graphs show up?**
   <details><summary>answer</summary>Splitting conflicts into two groups (LC 886, two exam slots, double-patterning masks in EDA), and two-kind graphs: matching (jobs ↔ machines, pin assignment), netlists as cells ↔ nets, users ↔ hotels.</details>

## Dynamic programming (5)

1. **DP 5 steps?**
   <details><summary>answer</summary>State (in words) → transition (last choice) → base → order → answer location.</details>

2. **Coin change combinations vs permutations?**
   <details><summary>answer</summary>Coins outer = combinations; amount outer = permutations.</details>

3. **0/1 knapsack 1D loop?**
   <details><summary>answer</summary>Items outer, capacity descending.</details>

4. **LIS n log n?**
   <details><summary>answer</summary>tails[k] = min tail of inc. subsequence of length k+1; lower_bound replace/append.</details>

5. **Edit distance recurrence?**
   <details><summary>answer</summary>Match: diag; else 1 + min(replace diag, delete up, insert left); base dp[i][0]=i, dp[0][j]=j.</details>

## EDA / FPGA / Vivado (18)

1. **Setup vs hold check?**
   <details><summary>answer</summary>Setup: data arrives before capture edge − setup (max delay). Hold: data stable after capture edge + hold (min delay).</details>

2. **Slack, WNS, TNS?**
   <details><summary>answer</summary>Slack = required − arrival. WNS = worst negative slack. TNS = sum of negative endpoint slacks.</details>

3. **STA propagation?**
   <details><summary>answer</summary>Forward topo: AT[v]=max(AT[u]+d). Backward: RT[u]=min(RT[v]−d). Slack = RT − AT.</details>

4. **Positive clock skew effect?**
   <details><summary>answer</summary>Helps setup, hurts hold.</details>

5. **Incremental STA?**
   <details><summary>answer</summary>Dirty arc → forward fanout cone in level order (bucket queue), early stop; backward fanin cone for required.</details>

6. **Levelization?**
   <details><summary>answer</summary>Kahn; level[v] = max(level[pred]) + 1. Loop → leftover nodes → SCC report.</details>

7. **HPWL?**
   <details><summary>answer</summary>Net bounding box width + height; standard wirelength estimate.</details>

8. **Partitioning algorithms?**
   <details><summary>answer</summary>KL (pair swaps), FM (single moves, gain buckets, O(pins)/pass), multilevel hMETIS (coarsen/partition/refine).</details>

9. **Placement algorithms?**
   <details><summary>answer</summary>Simulated annealing (VPR), analytic/quadratic (CG solve + spreading), ePlace/RePlAce (electrostatics+Nesterov), legalization, detailed.</details>

10. **Lee router?**
   <details><summary>answer</summary>BFS wavefront on grid from source to target + backtrace; optimal, O(grid). A&#42; adds Manhattan heuristic.</details>

11. **PathFinder cost?**
   <details><summary>answer</summary>(base + history) × present-congestion; rip-up &amp; reroute until no overuse; history prevents oscillation.</details>

12. **AIG + strash?**
   <details><summary>answer</summary>2-input AND + inverters; structural hashing = hash-cons (a,b) normalized to reuse identical nodes.</details>

13. **BDD vs SAT for multipliers?**
   <details><summary>answer</summary>BDDs blow up exponentially for multipliers in any order → SAT-based methods (with case splits).</details>

14. **K-feasible cut / tech mapping?**
   <details><summary>answer</summary>Set of ≤K nodes separating node from PIs → one K-LUT. Enumerate cuts bottom-up (priority cuts); FlowMap depth-optimal.</details>

15. **UltraScale+ CLB contents?**
   <details><summary>answer</summary>1 slice: 8 LUT6, 16 FFs, CARRY8, F7/F8/F9 muxes. SLICEM LUTs can be distributed RAM/SRL.</details>

16. **Vivado implementation flow?**
   <details><summary>answer</summary>synth_design → opt_design → place_design → phys_opt_design → route_design → write_bitstream (+ checkpoints .dcp).</details>

17. **SLR?**
   <details><summary>answer</summary>Super Logic Region: one die in stacked-silicon FPGAs; crossings via SLLs — a partitioning/placement cost.</details>

18. **Why determinism matters in EDA tools?**
   <details><summary>answer</summary>Customers &amp; developers need identical results for debug/regression regardless of threads/platform.</details>

## Lead & behavioral (4)

1. **STAR format?**
   <details><summary>answer</summary>Situation, Task, Action (what YOU did), Result (numbers) — plus what you learned.</details>

2. **Why AMD (3 points)?**
   <details><summary>answer</summary>Domain fit (EDA scale+formal+C++ perf ↔ Vivado QoR/runtime), closer to silicon (own FPGAs/adaptive SoCs), Lead scope for perf initiatives.</details>

3. **AI tools answer skeleton?**
   <details><summary>answer</summary>Concrete uses (code reading, test scaffolding, triage) + verification discipline + IP/confidentiality rules + measuring benefit + team enablement.</details>

4. **Two questions to ask the interviewer?**
   <details><summary>answer</summary>What are the top runtime/QoR bottlenecks the team is attacking this year? How is success for this Lead role measured in 6 months?</details>

