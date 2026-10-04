# Visualizers: step-through pattern trainers

Open any `.html` file in a browser. Each one stands alone: no server, no other files needed.
Every trainer has **Step / Back / Play** (or the arrow keys) and a **Predict** mode that asks you to call the next move before it's revealed.

| Trainer | What you watch | Pairs with |
|---|---|---|
| `monotonic-stack-trainer.html` | the waiting room: who gets popped, and the two walls per pop | MM01, P05 |
| `kosaraju-trainer.html` | Finish, Flip, Flood; the two classic bugs leaking | MM04, P08 |
| `bipartite-trainer.html` | BFS layers as alternating teams; the odd cycle; the outer-loop bug | MM04 §10, P08 |
| `dp-trainer.html` | memoized recursion vs bottom-up loops filling **the same table**, 9 problems | MM05, P10 |
| `linked-list-trainer.html` | pointer surgery: reverse, k-group, Floyd's cycle start, LRU cache | P04, P12 |
| `sta-trainer.html` | levelize, arrival, required, slack, critical path; a combinational loop | E2, MM05 pattern 12 |
| `cv-queue-trainer.html` | you schedule the threads; the stolen-wakeup and lost-wakeup bugs | C3, day4 `BlockingQueue` |

## How the newer trainers are built (shared code, standalone pages)

```
_kit/trainer-kit.css    the shared look: layout, controls, narration, code panel, log
_kit/trainer-kit.js     the shared engine: Step/Back/Play/Reset, keys, live code, log, self-test
_src/<name>.src.html    one trainer's own algorithm, events and drawing (+ two @kit markers)
build.sh                inlines the kit into each source → <name>.html (standalone)
```
- **Edit** `_src/*.src.html` or `_kit/*`, then run `./build.sh` (Git Bash or WSL). Don't edit the generated `.html` directly; its second line says so.
- The DP, linked-list, static timing and condition-variable trainers use the kit. The first three (monotonic stack, Kosaraju, bipartite) were written before the kit and are self-contained files you edit directly.
- **Self-test:** open a kit trainer with `#selftest` at the end of its URL. It runs the page's own checks (algorithm results, every preset to the end, the predict flow) and shows the result at the top.
