# Agoda IV1 Coding Round: 3-Day DSA Sprint (Fri 2 – Sun 4 Oct 2026)

Built for **Anuj** ([BE] Staff Software Engineer, Back End, Gurugram, [SHP] track). Recruiter screen passed on 1 Oct.
**IV1 = 60 minutes, live on HackerRank, 2 problems, LeetCode medium–hard, elimination round.** Agoda grades 4 areas: **understanding, coding efficiency, testing, communication**.

> **The bet behind this plan.** Your algorithmic ceiling (CodeChef 1974 / Codeforces 1693) isn't the risk. The risks are **rust, speed, test discipline and narration**, which are exactly what your Uber feedback flagged (*edge cases, readability, naming*). So the plan is:
> **(1)** drill the ~10 families Agoda actually asked in 2025–26, as compile-and-run problems with tests;
> **(2)** write *your own* tests before every problem;
> **(3)** run 7 timed mocks scored on Agoda's 4 areas.
> The evidence is in [00-Agoda-Coding-Intel.md](00-Agoda-Coding-Intel.md).

---

## 1. What's here and how it connects to the AMD prep

| File | What | When |
|---|---|---|
| [00-Agoda-Coding-Intel.md](00-Agoda-Coding-Intel.md) | 12 Agoda reports (2 from **Gurugram**, 1 from your exact [SHP] track), the LC tag, priorities, your own weak spots | Thu night / Fri 08:30 |
| [01-Live-Round-Playbook.md](01-Live-Round-Playbook.md) | The rubric decoded, the 25-min clock, scripts, **test matrix**, debug protocol, HackerRank tips, C++ idioms, **your pre-Run checklist** | Fri morning; §7–8 again on interview eve |
| [02-Pattern-Cards.md](02-Pattern-Cards.md) | 10 Agoda families (S M W B G I J P H R) as Hook / Triggers / Invariant / Skeleton / Traps / Follow-up | Before each block |
| [03-Problem-Bank.md](03-Problem-Bank.md) | All 54 problems: why, clarifying questions, hint ladders, **tests to justify**, follow-ups. Plus AMD warm-ups and an extra pool | While practising |
| [practice/agoda_day1.cpp](practice/agoda_day1.cpp) · [day2](practice/agoda_day2.cpp) · [day3](practice/agoda_day3.cpp) | **Single-file** stubs + 323 tests. Paste into HackerRank/godbolt as-is | The core work |
| [practice/solutions/](practice/solutions/) | Reference solutions: **323/323 checks pass on GCC 14 (C++17) and Clang 19 (C++20) under ASan + UBSan** | Only after passing |
| [04-Mock-Rounds.md](04-Mock-Rounds.md) | 7 mocks (2 unseen problems each) + scoring rubric | Evenings |
| [05-Recall-and-Day-Of.md](05-Recall-and-Day-Of.md) | One-page recall + interview-day checklist | Last night + morning of |
| [PROGRESS.md](PROGRESS.md) · [CLAUDE.md](CLAUDE.md) | Tracker, bug log · coach mode for Claude | Throughout |

**Reused from `../../AMD-CPP-EDA-Lead-Prep/` (don't redo, just use):**
- `01-Speed-Cpp/` (speed playbook + `cpp_toolkit.cpp`): the Fri 08:30 warm-up.
- `02-Patterns/00-Pattern-Map.md` (the decision tree) and cards P02/P03/P05/P06/P10 for basics.
- **Agoda-tagged problems already in AMD's practice files** become 8-minute warm-ups (list in [03-Problem-Bank.md](03-Problem-Bank.md#warm-ups-already-in-the-amd-prep-agoda-tagged-8-minutes-each-from-a-blank-file)).
- **Skip for Agoda:** linked lists (P04), EDA, concurrency, C++ internals. No Agoda coding report asked them.

---

## 2. Setup (Thursday night, 15 minutes)

You have no compiler on Windows right now, and WSL Ubuntu has no `g++`. Pick one:

**A. WSL (recommended: the same GCC as HackerRank):**
```bash
wsl sudo apt update
```
```bash
wsl sudo apt install -y g++
```
Then build from this folder. Run `wsl`, `cd "/mnt/d/Git/Study/Agoda-Staff-BE-Prep/01-Coding-Round-DSA/practice"`, and:
```bash
g++ -std=c++17 -O1 -g -fsanitize=address,undefined agoda_day1.cpp -o d1 && ./d1 S1
```
(`./d1 S1` runs only the tests whose name contains "S1". `./d1` runs everything.)

**B. No install:** paste the whole `agoda_dayN.cpp` into [godbolt.org](https://godbolt.org) (x86-64 gcc 14, flags `-std=c++17`, add the "Execute" pane). Each practice file is a single file on purpose.

You should see `[FAIL]` everywhere at first. That means the setup works.

---

## 3. The plan

**Daily rules (every problem):** timer on → clarifying questions + approach + complexity out loud (≤ 4 min) → **your own 3–5 tests written as comments** → code (target 12–18 min) → run → log time + bug in [PROGRESS.md](PROGRESS.md) → say the follow-up out loud.
★★★ = Agoda asked it in 2025–26. Do those first if a block runs late. Items in (brackets) are SHOULD, not MUST.

### Thursday 1 Oct, evening (optional, 45 min)
- 15 min: setup (§2).
- 30 min: read the [Intel](00-Agoda-Coding-Intel.md) §1–3 and §7, and [Playbook](01-Live-Round-Playbook.md) §0–2.

### Day 1, Friday 2 Oct: "Parse it, stack it, slide it"
| Time | Block | What |
|---|---|---|
| 08:30–09:00 | Warm-up | Type AMD `01-Speed-Cpp/cpp_toolkit.cpp` from memory once (syntax reload: heaps, comparators, maps) |
| 09:00–10:00 | **MUST** | **Mock 0 (cold calibration)** from [04](04-Mock-Rounds.md). Score it. Your weakest area decides what to watch all weekend |
| 10:00–10:30 | **MUST** | [Playbook](01-Live-Round-Playbook.md) §2–4 and §7 (phase scripts, test matrix, checklist) |
| 10:30–10:45 | **MUST** | Cards **S** and **M** |
| 10:45–13:00 | **MUST** | **S1★★★** · S3 · S4 · **S5★★★** · S6 · S7 · (S2) |
| 13:00–14:00 | Break | Walk, no screens |
| 14:00–15:45 | **MUST** | **M1★★★** · **M2★★★** · **M3★★★** · M4 · M5 |
| 15:45–16:00 | **MUST** | Card **W** |
| 16:00–17:30 | **MUST** | **W1★★★** · W2 · W3 · W4 · (W5 · W6) |
| 17:30–18:00 | SHOULD | AMD warm-ups: LC 739 · 239 · 20 (8 min each, blank file) |
| 18:00–19:30 | Break | |
| 19:30–20:30 | **MUST** | **Mock 1** (record yourself) |
| 20:30–21:00 | **MUST** | Bug log → PROGRESS.md. Read your Mock 0 vs Mock 1 scores |

### Day 2, Saturday 3 Oct: "Guess the answer, sort the world, sweep the bookings"
| Time | Block | What |
|---|---|---|
| 08:30–09:00 | **MUST** | Spaced review: your 2 worst Day-1 problems. Approach + invariant aloud, code only the core loop |
| 09:00–09:15 | **MUST** | Card **B** |
| 09:15–10:45 | **MUST** | **B1★★★** · B2 · **B3★★★** · B4 |
| 10:45–11:00 | **MUST** | Card **G** |
| 11:00–13:15 | **MUST** | **G1★★★** (your most likely question) · **G2★★★** · G3 · **G4★★★** · G5 · G6 · G7 |
| 13:15–14:15 | Break | |
| 14:15–15:00 | **MUST** | G8 · G9 |
| 15:00–15:15 | **MUST** | Card **I** |
| 15:15–17:15 | **MUST** | **I1★★★** · I2 · I3 · I4 · **I5 (your Google 2023 rematch)** |
| 17:15–17:45 | SHOULD | AMD warm-ups: LC 875 · 56 · 253 |
| 17:45–19:00 | Break | |
| 19:00–20:00 | **MUST** | **Mock 2** |
| 20:15–21:15 | SHOULD | **Mock 3 in the HackerRank editor** (or move it to Sun 08:00 if tired) |
| 21:15–21:30 | **MUST** | Bug log |

### Day 3, Sunday 4 Oct: "States, centres, routes", then mocks
| Time | Block | What |
|---|---|---|
| 08:30–09:00 | **MUST** | Spaced review: worst 2 from Days 1–2 |
| 09:00–09:15 | **MUST** | Card **J** |
| 09:15–11:00 | **MUST** | **J1★★★** · **J2★★★** · J3 · J4 · **J5★★★** · J6 · J7 · J8 |
| 11:00–11:15 | **MUST** | Card **P** |
| 11:15–13:00 | **MUST** | **P1★★★** (say O(n³) → O(n²) aloud) · P2 · P3 · P4 · P5 · P6 |
| 13:00–14:00 | Break | |
| 14:00–14:40 | **MUST** | Card **H** + H1 · H2 |
| 14:40–15:30 | SHOULD | Card **R** + R1 · (R2) |
| 15:30–16:00 | SHOULD | AMD warm-ups: LC 322 · 300 |
| 16:00–17:00 | **MUST** | **Mock 4** |
| 17:30–18:30 | **MUST** | **Mock 5 in the HackerRank editor** |
| 19:30–20:30 | **MUST** | **Re-solve your 3 worst problems from the bug log**, from a blank file, timed |
| 20:30–21:00 | **MUST** | [05-Recall](05-Recall-and-Day-Of.md). Sleep early |

### Day 4 / interview eve (whenever the date lands)
Morning: **Mock 6** (fresh). Afternoon: re-solve 2 bug-log items + the ★★★ list as "approach only". Evening: Playbook §7–8 and the [Recall](05-Recall-and-Day-Of.md). **Nothing new after 6 pm.**

**If the interview is more than 1 week away:** keep a 90-minute daily rhythm (1 mock from the extra pool in [03](03-Problem-Bank.md#extra-pool-after-the-plan-or-for-daily-practice-until-the-interview) + a 6-item spaced review), and move on to Platform-round prep. Then do Day 4 on the eve.

---

## 4. Three ways to practise (same as the AMD course)

| Mode | How |
|---|---|
| **Solo** | Stubs + tests in `practice/`. Hints are folded in [03](03-Problem-Bank.md), one level at a time. Solutions only after passing. |
| **Coach (Claude)** | Open this folder in Claude Code and say: *"S1: my approach is…"*, *"Review my G1, interviewer style"*, *"Run Mock 2"*, *"Pattern drill"*, *"Test drill on B3"*. [CLAUDE.md](CLAUDE.md) keeps Claude in hint-only interviewer mode, scoring on Agoda's rubric. |
| **Real editor** | Mocks 3 and 5 in HackerRank's own editor (hackerrank.com → Prepare → C++), to feel the CodePair environment. |

---

## 5. How this was built (the same method as the AMD session)

The AMD prep session (29–30 Sep) did four things: researched company-specific reports (LeetCode Discuss, AmbitionBox, Glassdoor, TechPrep, CodeJeet), mined your own notes (`I-2025/Cadence-R1.txt`), ranked topics ★★★/★★/★, and turned them into pattern cards + hint ladders + compile-and-run tests, verified on Compiler Explorer with GCC 14 and Clang 19.
This sprint repeats that for Agoda:
1. Your recruiter's IV1 rubric.
2. **12 Agoda candidate reports**, read directly on LeetCode Discuss (2 from Gurugram, one of them on the same [SHP] backend track).
3. The LeetCode **Agoda tag** with recency (DSAPrep, CodingKaro).
4. Your feedback history (Uber, Google, Cadence).

Every reference solution was compiled and run: **323/323 checks pass** on GCC 14 (C++17) and Clang 19 (C++20), under AddressSanitizer + UBSan. The stub files compile and fail cleanly until you implement them.
