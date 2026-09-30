# C5: OS & Systems Fundamentals (fast pass)

> AMD ★★★ (uProf-team senior round): mutex, semaphore, **child process / fork**, **kernel vs user mode**, **process states**, threading, caches.
> AMD C++ Developer R3: scheduling, memory, threads, plus **networks** (protocols, layers).

---

## 1. Process vs thread ★★★
| | Process | Thread |
|---|---|---|
| Address space | own (isolated) | shared with the other threads of the process |
| Owns | page tables, fds, signal handlers, PID | stack, registers, TLS, TID |
| Create cost | higher (`fork` + `exec`) | lower (`clone` with shared VM) |
| Crash isolation | yes | one thread's segfault kills the whole process |
| Communication | IPC (pipes, sockets, shared memory, message queues) | shared memory (needs synchronization) |
Linux: both are **tasks** created by `clone()`, with different sharing flags.

## 2. `fork` / `exec` / `wait` ★★★
- `fork()` returns **0 in the child** and the **child's PID in the parent** (−1 on error). The child is a copy: same code, a **copy-on-write** snapshot of memory, and duplicated fds (sharing file offsets).
- **COW**: pages are shared read-only until either side writes → then the kernel copies that page (page fault).
- `exec*()` replaces the process image (the PID stays the same). `fork`+`exec` = how shells launch programs. `posix_spawn`/`vfork` avoid copying page tables for huge parents (relevant for **EDA tools with 100 GB of RSS launching subprocesses!**).
- `wait`/`waitpid` reaps the child. **Zombie** = exited but not reaped (the process-table entry remains). **Orphan** = the parent died → re-parented to init/systemd, which reaps it.
- **fork in a multithreaded program**: only the calling thread exists in the child. Mutexes held by other threads stay **locked forever** → only call async-signal-safe functions before `exec`.
- Puzzle: `for (i=0;i<3;i++) fork();` → **8** processes (2³); `printf` buffering can print duplicates if not flushed before the fork.

## 3. User mode vs kernel mode ★★★
- The CPU privilege rings: user (ring 3) cannot execute privileged instructions or touch kernel memory. The kernel (ring 0) has full access.
- Transitions: **system calls** (`syscall` instruction), **interrupts** (hardware), **exceptions** (page fault, divide by zero).
- A syscall costs ~100 ns–1 µs (mode switch, plus Spectre/Meltdown mitigations). Batching and `mmap` avoid syscalls; vDSO for `gettimeofday`.

## 4. Process states ★★
`New → Ready ⇄ Running → Terminated`, with `Running → Waiting/Blocked (I/O, lock) → Ready`. Linux letters: R (running/runnable), S (interruptible sleep), D (uninterruptible, usually I/O), T (stopped), Z (zombie).

## 5. Scheduling ★
FCFS (convoy effect) · SJF/SRTF (optimal average wait, needs the burst lengths, can starve) · Round Robin (time quantum, good response time) · Priority (+ aging to prevent starvation) · Multilevel feedback queue. Linux: **CFS** (vruntime in a red-black tree; being replaced by EEVDF since 6.6), real-time classes SCHED_FIFO/RR. Context switch = save/restore registers + possibly switch page tables (TLB flush without PCID) → cache pollution is the real cost.

## 6. Memory management ★★
- **Virtual memory:** each process sees its own address space; the MMU translates via **page tables** (x86-64: 4-level, 48-bit; 5-level on newer parts). **TLB** caches translations → huge pages reduce TLB misses (big EDA heaps benefit from **THP**).
- **Page fault**: minor (the page is in memory, just map it, e.g. COW or first touch) vs major (read from disk/swap).
- **Demand paging**: `malloc` of 10 GB returns fast; the pages are only materialized on first touch (Linux overcommit → the OOM killer).
- **Replacement**: FIFO (Bélády's anomaly), **LRU** (exact is costly), **Clock / second chance** (the practical approximation), LFU.
- **Thrashing**: the working set exceeds RAM → constant paging.
- **Process memory layout** (low → high): text (code) · rodata · data (initialized globals) · **bss** (zero-initialized globals) · heap (grows up, `brk`/`mmap`) · … mmap region (shared libs, large mallocs ≥128 KB via `mmap`) … · **stack** (grows down, 8 MB default on the main thread) · kernel.
- **Stack vs heap:** the stack is automatic, fast (a pointer bump), limited in size, and per thread. The heap is dynamic, needs an allocator, is shared, and fragments.
- Fragmentation: external (free space split into holes) vs internal (slack within blocks).

## 7. Caches & coherence ★★ (hardware-adjacent, which AMD likes)
- L1d/L1i (per core), L2 (per core), L3 (shared per **CCX/CCD** on Zen); inclusive vs exclusive/victim caches (Zen L3 is mostly a victim cache of L2).
- **Cache line 64 B**; mapping: direct-mapped / set-associative / fully associative. Misses: compulsory, capacity, conflict (+ coherence).
- **MESI** (AMD uses **MOESI**): Modified, Owned, Exclusive, Shared, Invalid. A write needs exclusive ownership → invalidates other copies → **false sharing** cost.
- Write-back vs write-through; write-allocate.
- Prefetchers love sequential access → arrays win.
- **Designing a multi-level cache (AMD design question):** levels with increasing size and latency; lookup L1 → L2 → memory; fill policy (inclusive: the line is in all levels; exclusive: in exactly one); replacement (LRU/pseudo-LRU); write policy; coherence across cores. In software: an in-memory LRU L1 + a larger L2 (SSD/remote) with async promotion. Think of `get` latency, hit-rate metrics and consistency.

## 8. Synchronization & deadlock (see C3)
Coffman conditions; prevention (lock ordering), avoidance (**Banker's algorithm**), detection (a wait-for graph cycle → **DFS cycle detection**, P08!), recovery. Priority inversion (the Mars Pathfinder story) → priority inheritance.

## 9. IPC ★
Pipes (anonymous, parent-child) · FIFOs (named) · message queues · **shared memory** (fastest; needs a sync such as a process-shared mutex or semaphore) · sockets (UNIX domain for local, TCP for remote) · signals (async notification; only async-signal-safe functions in handlers) · `mmap` of a file.

## 10. Files & I/O ★
File descriptors (per-process table → open file table → inode). Blocking vs non-blocking I/O · `select`/`poll`/**`epoll`** (event-driven servers) · `io_uring` · buffered (`FILE*`, page cache) vs direct I/O · `fsync` durability.

## 11. Networking in 60 seconds ★ (asked once for a C++ role)
- OSI 7 layers: Physical, Data link, Network (IP), Transport (TCP/UDP), Session, Presentation, Application. TCP/IP model: Link, Internet, Transport, Application.
- **TCP**: connection-oriented (3-way handshake SYN, SYN-ACK, ACK), reliable, ordered, flow control (window), congestion control. **UDP**: connectionless, no guarantees, low latency (DNS, video, games).
- A socket = IP + port. `TIME_WAIT`. Nagle's algorithm (`TCP_NODELAY`).
- "What happens when you type a URL" → DNS → TCP (+TLS) → HTTP request → response → render.

## 12. "What happens when you run `./a.out`?" ★
The shell `fork`s → the child `execve`s → the kernel parses the ELF, maps segments, sets up the stack (argv, envp, auxv) → the **dynamic loader** (`ld-linux.so`) maps the shared libs and resolves symbols (PLT/GOT, lazy binding) → runs static initializers (`.init_array`, global constructors) → `main` → `exit` runs the `atexit` handlers and static destructors → the kernel frees resources → the parent `wait`s.

---

## Self-test
1. Process vs thread: 4 differences. How does Linux implement both?
2. `fork` return values; what is COW; why is fork in a multithreaded process dangerous?
3. Zombie vs orphan. 4. User → kernel transitions: 3 kinds.
5. Where do globals, zero-initialized globals, locals, and `new`'d objects live?
6. TLB and huge pages: why do big EDA runs care?
7. MESI states and how false sharing arises.
8. `for(i=0;i<3;i++) fork();` how many processes?
