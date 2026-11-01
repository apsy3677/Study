# Concurrency one-pager (C++ threads, for interview practice)

Code next to this file: `blocking_queue.cpp`, `foobar.cpp`, `foobar_semaphore.cpp`, `dining_philosophers.cpp`.

## 1. The one mental model: 1 board + 1 waiting room
- **Board** = the shared state (queue size, `turn`, token count). **Waiting room** = where a thread sleeps until the board says "go".
- **4 K's** (say them out loud first, ~30 s): **Kya baanta** (what is shared + what guards it) → **Kab ruke** (exact wait
  condition) → **Kaun jagaaye** (who changes the board and wakes whom) → **Kaise khatam** (how it stops).
- **Kya baanta test:** local variable = not shared · member/global that nobody writes = shared but safe · one writes,
  another reads/writes = **shared, needs the lock**.
- **5-line skeleton:** `lock → wait until <my condition> → do my work → change the board → notify`.
  *Hook: Lock → Ruko → Kaam → Board badlo → Jagao.*

## 2. Two places a thread can wait
| Place | What gets you out | Without it |
|---|---|---|
| CV waiting room (asleep in `wait`) | only a `notify` | sleeps forever (spurious wake-ups are rare, never relied on) |
| Mutex line (wants the lock) | the holder's `unlock` | nothing needed, unlock always hands it over |
- `wait(lk, pred)`: checks pred first (no sleep if already true) → sleeps **and releases the lock** → on wake **re-takes the
  lock and re-checks pred**. Woken ≠ your turn.
- **The board must change under the lock.** `notify` may be inside or after unlock (after = one fewer wasted wake-up).
- **notify forgets, a semaphore token remembers.** A notify with nobody waiting is lost → that's why CV needs board + predicate.

## 3. The tools
| Tool | Plain words | Use it for |
|---|---|---|
| `mutex` | one key, has an owner (who locks, unlocks) | **protect data**; RAII `lock_guard` / `unique_lock` / `scoped_lock` |
| `condition_variable` | waiting room, always with a mutex | wait until a condition on shared data is true |
| semaphore | jar of tokens, **no owner**: `acquire` takes (sleeps if empty), `release` adds | hand-off order, or "at most N at once" |
| `atomic` | one indivisible step + visibility/ordering | counters, flags, CAS loops |
- Semaphores: `binary_semaphore s{0}` (= `counting_semaphore<1>`), `counting_semaphore<10> pool{4}` (max, start), POSIX `sem_t`.
- Speed: mutex and semaphore are about the same (atomic when uncontended, futex sleep when contended). **Pick by fit, not speed.**
- **Interview default: mutex + CV.** Semaphore for pure order (LC 1114–1116) with one line of why.
  *Hook: Mutex = chaabi (data bachao), semaphore = token (gino/saunpo), CV = waiting room (shart pe ruko).*

## 4. Three patterns behind the LeetCode concurrency set
| Pattern | Tool | Problems |
|---|---|---|
| Baton: fixed order | one jar per thread, **one token**, pass it to the next | 1114, 1115, 1116 (zero chooses odd/even jar) |
| Permits: at most N | one counting semaphore of N | 1226 room of 4, 1117 H2O, DB pool |
| Decide by the board | mutex + CV + predicate (+ `notify_all` if > 2 kinds of waiter) | 1195 FizzBuzz, blocking queue with close |

## 5. Problems done
- **Blocking queue:** deque + mutex + 2 CVs (`not_full`, `not_empty`); predicate waits; notify on **every** push/pop
  (notify only on full→not-full = lost wake-up). Shutdown (close / poison pill) in one sentence unless asked.
- **FooBar (CV):** `bool turn`; foo waits for `turn`, bar for `!turn`; **print → flip → notify, under the lock**. 1 CV is
  enough with 2 threads (only one other waiter).
- **3 threads, 1 CV:** `notify_one` can wake the wrong waiter → it sleeps again → everyone asleep → hang. Fix `notify_all`
  or one CV each. *Hook: galat bande ko jagaya, sab soye.*
- **FooBar (semaphores):** `fooJar{1}, barJar{0}`; acquire mine → print → release the **other's** jar. One baton in total.
  3 threads = 3 jars in a ring, release exactly one (the next).
- **Spinning** (`while (!turn) {}` on an atomic): burns a core; fine only for µs waits on a spare core, never on one core;
  plain `bool` may loop forever (read once into a register). Real mutexes spin briefly, then sleep.

## 6. Bug catalogue: answer every "find the bug" with 3 N's (Naam → Nazara → Nuskha)
| Bug (Naam) | Nazara (what happens) | Nuskha (fix) |
|---|---|---|
| Lost update (`hits++` unguarded) | read 5 / read 5 / write 6 / write 6 → one +1 lost; result ≤ expected; data race = UB | `atomic<int>` / mutex; better: count locally, add once |
| Check-then-act | `if (used < 10) used++` → both see 9 → 11 | mutex around check **and** act, or a CAS loop |
| `volatile` flag | compiler/CPU moves `data = 42` after `ready = true` → reader prints 0 | `atomic<bool>`: store release / load acquire (publish point) |
| Deadlock (two locks) | T1 holds A wants B, T2 holds B wants A | global lock order (lower id first) or `scoped_lock`; check `&a == &b` |
| Self-deadlock (callback under lock) | same thread locks `m` twice → hang; + iterator invalidation | copy under the lock, call out unlocked |
| Lost wake-up | notify before the wait, or notify only on a transition, or `notify_one` to the wrong waiter | change board under lock + predicate wait; notify every change; `notify_all` |
- **Deadlock needs all 4:** only one holder · hold and wait · no snatching · **circular wait**. Break one.
  Lock order breaks the circle; room of 4 breaks it (pigeonhole: 4 people, 5 forks); `scoped_lock` breaks hold-and-wait.
  Release order never matters, only the order you wait. *Hook: chaar shartein, ek todo.*
- Atomic makes **one** step indivisible, not a check + act. *Hook: atomic ek kadam bachata hai, kahani nahi.*

## 7. Tools to find them
- ThreadSanitizer: `g++ -std=c++20 -g -O1 -pthread -fsanitize=thread x.cpp -o x_tsan` then `setarch x86_64 -R ./x_tsan`
  (WSL kernel needs `setarch -R`). Also reports lock-order inversion.
- Hang in production: `gdb -p <pid>` → `thread apply all bt` → every thread parked in a lock = the circle.
- An online judge can't prove there's no race: local stress test + TSan.
