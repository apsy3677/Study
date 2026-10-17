# Micro-Labs Plan: learn connectivity by breaking things (before IV2)

> **IV2 Platform round: Wed 21 Oct 2026, 08:00.** Before IV2, this plan **replaces Tier 0** of [Prototype-Labs-Plan.md](Prototype-Labs-Plan.md). That heavier plan (Go, Docker, full services) resumes for IV3.
> The lab specs live in the WSL repo: `~/code/system-design-prototypes/micro-labs/README.md`. Coach rules for any Claude session: the repo's `CLAUDE.md` and §5 below.

## 1. Why micro-labs (diagnosis, 17 Oct)
- **Mechanism gap:** for things never built (timeouts, thread pools, breakers, bulkheads), there's no picture underneath the words, so answers turn into buzzwords. Where a mechanism exists (B+ tree → cursor pagination), answers are already Staff-level **without notes**.
- **Recall gap:** reading and rereading builds recognition, not recall. The 60-second answers were strong only straight after reading the doc.
- **Not the main problem:** English. Fillers and hesitation drop once the mechanism is solid.
- **So:** see each mechanism fail and fix it once (micro-lab), then retrieve it by being questioned. **No more reading-only sessions, and no new documents.**

## 2. Principles
1. **Build only the thing being learned; dummy everything else.** (Arpit's style: for SSE he used a file as the "database" and streamed it line by line.) The supplier is a 15-line `http.server` or a function with `sleep()`; the "DB" is a dict or SQLite; the "users" are a loop.
2. **Failure first:** watch it break, then fix it, then measure the difference.
3. **Python 3.12 standard library only** (`threading`, `concurrent.futures`, `http.server`, `urllib`, `sqlite3`, `hmac`, `random`, `time`). No Docker, no Go, no frameworks. Each file ≤ about 80 lines.
4. **Claude writes the dummies and the harness; Anuj writes the mechanism** (the timeout, the semaphore, the breaker, the retry loop, the key table).
5. **Question before reading:** predict what happens, second by second, *before* running anything.
6. **One formula carries §4–§10: Little's Law.** `threads busy = requests/s × seconds each request holds a thread`.

## 3. The labs (specs in the repo)
| # | Micro-lab | Real (you build it) | Dummy | Doc sections |
|---|---|---|---|---|
| 1 | **slow-supplier** | socket timeout, bulkhead (`Semaphore`), circuit breaker | supplier = `http.server` with `?delay=` / `?fail=`; "server" = a 10-thread pool; users = a loop | §4, §7 |
| 2 | **retry-storm** | naive retry → backoff + full jitter → retry budget | supplier = a capacity-100/s simulation with a 2 s blip; time-step loop, no network | §5 |
| 3 | **double-booking** | idempotency-key table (PRIMARY KEY + replay), conditional `UPDATE … WHERE available > 0` | "network loses the response" = raise after commit; SQLite file | §6 |
| 4 | **fan-out-search** | overall deadline + partial results, coalescing (in-flight map), token-bucket call budget | 3 suppliers = functions with random `sleep` / errors; cache = dict with expiry | §3, §8, §10 |
| 5 *(optional)* | webhook-verify | HMAC over `timestamp.body`, replay window, dedupe on `event_id` | the sender = a function that signs and resends | §14 |

## 4. Schedule to Wed 21 Oct 08:00
| Day | Time available | Plan |
|---|---|---|
| **Sat 17** (evening) | ~30 min | Optional: the "predict" questions for lab 1 only (no code) |
| **Sun 18** | full day | Morning: draw the chain from memory (10 min). **Lab 1** (90 min) → **Lab 2** (60 min) → **Lab 3** (60 min). Afternoon: 60 s aloud on §4, §5, §6, §7 (retake each once). Code review **CR-1…CR-3** from `04-Code-Review.md` (60 min) |
| **Mon 19** (office) | ~1.5 h evening | Commute: draw the chain. Evening: **Lab 4** (60 min) + §3 supplier-integration 60 s redo |
| **Tue 20** | mostly free | Questioning drills (no reading) on §8–§15: webhooks, auth, pagination, outbox (90 min). QA §1–6 by questioning (60 min). Scenario **S1** aloud (45 min). **Mock 1**, full 60 min + debrief (afternoon). Evening: `08-Recall-Day-Of.md`, sleep early |
| **Wed 21** | 06:30 | 10 min: draw the chain, read the recall sheet. **08:00 IV2** |

If a day slips, cut in this order: Lab 5 → Lab 4's token bucket → CR-3 → QA drill. **Never cut Mock 1.**

## 5. Coach protocol (for any Claude session, Windows or WSL)
- **Question first, one at a time.** Before each lab: 3–5 "what happens, second by second?" questions. Wait for the answer, push with "then what?", and don't reveal the answer early.
- **Show the lab design in ≤ 10 lines** (what's real, what's dummy, what we'll measure) and wait for OK.
- **Anuj writes the mechanism.** Give a stub, a check that currently fails, and hints. Show a solution only when he says "show me".
- **Teach with pictures first** (ASCII timelines, the Little's Law arithmetic), then **C++ analogies** (he's a C++ engineer: `future::wait_for`, `counting_semaphore`, watchdogs, master–worker). Short Hindi memory hooks are welcome; interview answers stay in English.
- **Explain frame:** Arpit's style: two opposite options → trade-offs → hybrid. Always end on the trade-off.
- **After each lab:** 60 s aloud → grade ✔ / partial / ✘ → corrections → one follow-up question → one line in both PROGRESS files.
- **Keep him focused:** anything not being learned stays a dummy. Don't drift into infra, frameworks or long documents.
- Never add AI attribution to commits. Commit only when asked. The WSL repo stays neutral: no company names, nothing about interviews.

## 6. Known weak spots (carry into every session)
From [PROGRESS.md](../Agoda-Staff-BE-Prep/02-Platform-Round/PROGRESS.md):
- Buzzwords where the mechanism is missing; length swings (20 s to 3 min); skipping the trade-off at the end.
- Fillers ("uh", "like"); says "matrices" for **metrics**; "item potency" for **idempotency**; says "avoid" for **void**.
- Debugging questions: guesses before data. Lead with "first I'd break the number down by …".
- Real stories to build: the Synopsys **master–worker** system (heartbeats, hung-worker reassignment, licence grace period) mapped to health checks, failover, leases and breakers.

## 7. Starting a new session
Claude sessions don't share chat history. Windows and WSL Claude Code don't share memory either. **These files are the handoff.**

**WSL (for labs):** `cd ~/code/system-design-prototypes && claude`, then paste:
> Read CLAUDE.md, micro-labs/README.md and "/mnt/d/Git/Study/System Design/Micro-Labs-Plan.md". Today is <day>. Start micro-lab <N> with the predict questions, one at a time.

**Windows desktop app (for drills and mocks):** open the Study folder, then:
> Read "System Design/Micro-Labs-Plan.md" and Agoda-Staff-BE-Prep/02-Platform-Round/CLAUDE.md. Coach mode: <drill / Mock 1 / Review CR-1>.
