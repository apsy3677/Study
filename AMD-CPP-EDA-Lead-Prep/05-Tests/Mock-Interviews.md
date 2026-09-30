# Mock Interviews (run with Claude, a friend, or solo with a timer + voice recorder)

**With Claude:** *"Run Mock 1. You are the interviewer. Keep strictly to time, one question at a time, and score me with the rubric at the end."*
**Solo:** set a timer, answer **out loud** (record it on your phone), write code in a plain editor, then self-score with the rubric. Listening to yourself is uncomfortable, and it's the single highest-return exercise.

---

## Rubric (score 1–4 each, max 24)
| Dimension | 1 | 4 |
|---|---|---|
| **Problem solving** | jumps to code, no approach | clarifies, brute force → optimal, states the invariant and complexity first |
| **C++ fluency** | fights the syntax, wrong containers | idiomatic STL, RAII, const-correct, fast |
| **Communication** | silent or rambling | narrates the decisions crisply, checks in with the interviewer |
| **Testing** | "I think it works" | dry-runs, edge cases, finds their own bug |
| **Depth** | surface answers | internals + trade-offs + "what breaks at scale" |
| **Lead signal** | "I did the task" | ownership, measurable impact, influence, mentoring, judgment |

---

## Mock 1: "Round 1 screen" (60 min). **The most likely format.**
**Persona:** Senior MTS on the Vivado implementation team + a second engineer. Friendly, fast, drills whatever you mention.

| Time | Segment | Script (interviewer) |
|---|---|---|
| 0–10 | Intro | "Walk me through your background and your current role." → pick the **one** project you mention most and ask: "What was the hardest technical problem? What did *you* do? How did you measure success?" |
| 10–25 | C++ rapid-fire (pick 6–8) | vtable/vptr · virtual dtor · smart pointer internals ("how would you implement shared_ptr?") · move semantics/Rule of 5 · `map` vs `unordered_map` · a snippet from C6 to debug · "what's RAII and where did you use it?" · mutex vs semaphore · process vs thread |
| 25–55 | Coding (choose one medium, one follow-up) | **Option A:** "Reverse a linked list in groups of k." Follow-up: "Do it recursively; what's the space cost?" **Option B:** "Given meeting intervals, find the min rooms." Follow-up: "Now 10⁸ meetings streaming in: what changes?" **Option C:** "Design an LRU cache." Follow-up: "Make it thread-safe. How does it scale to 32 threads?" |
| 55–60 | Your questions | You ask 2 sharp questions (see 08-Lead) |

## Mock 2: "C++ / systems deep dive + coding" (60 min)
**Persona:** Principal engineer, perf-obsessed, skeptical. Asks "why?" three levels deep.

| Time | Segment | Script |
|---|---|---|
| 0–15 | Perf story | "Tell me about the biggest performance improvement you've delivered." Drill: baseline? profiler? what was hot? why? alternatives considered? how did you verify the correctness didn't change? what did you guard in CI? |
| 15–30 | Concurrency | "Implement a bounded blocking queue." (write it) → "Why the predicate?" → "Why two condvars?" → "How do consumers shut down?" → "Where's false sharing possible?" → "How would you make it lock-free for a single producer and single consumer?" |
| 30–50 | Coding | "Implement `shared_ptr` (no weak_ptr)." Follow-ups: thread-safety of the refcount, memory orders, `make_shared` benefits, cycles. **or** "Implement a fixed-size pool allocator" → alignment, free list, thread-safety |
| 50–60 | Debug | Show 3 snippets from C6 (#14, #16, #21) and ask for the bug/output + fix |

## Mock 3: "EDA + design + lead" (60 min)
**Persona:** Hiring manager (Lead/Director level) of the synthesis/implementation team.

| Time | Segment | Script |
|---|---|---|
| 0–10 | Motivation | "Why AMD? Why leave Synopsys? What do you know about Vivado?" |
| 10–30 | Design | "Design the in-memory netlist database for a 100M-instance design. Our engines (timing, placement) need fast traversal and incremental updates." Drill: memory estimate, ids vs pointers, hierarchy, ECO edits, observers, checkpointing, thread-safety |
| 30–45 | EDA algorithms | "How does timing analysis work on the netlist graph?" → "What happens incrementally after a placement move?" → "How would you find the top 100 critical paths?" → "How would you detect combinational loops and report them?" |
| 45–55 | Leadership | "Tell me about a time you led a technical change across teams." · "A senior engineer on your team disagrees with your design in a review. What do you do?" · "How do you prioritize tech debt vs features?" · "How do you use AI tools?" |
| 55–60 | Your questions | |

---

## Mock log (fill after each)
| Date | Mock | Score /24 | Top 3 fixes |
|---|---|---|---|
| | | | |
