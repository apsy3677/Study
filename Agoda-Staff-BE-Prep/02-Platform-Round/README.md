# Agoda IV2 Platform Round: 2-Day Prep

Built for **Anuj** ([BE] Staff Software Engineer, Back End, Gurugram, [SHP] track). IV1 coding cleared. IV2 is roughly a week away (as of 15 Oct 2026).
**IV2 = 60 minutes on HackerRank: a narrative (a flawed design + API + code snippet) followed by generic questions.** Graded on **System analysis & design · Connectivity management · Quality assurance · Code review · Communication.**

> **The bet behind this plan.** The evidence ([00-Round-Intel](00-Round-Intel.md)) is unusually consistent: 4 of 5 detailed reports got **an aggregator pulling from external suppliers + a booking step**, then a **booking-service code review**. A Gurugram SSE on your track was **rejected for weak connectivity management**, and a Staff candidate was **down-levelled** after this round.
> So the plan is: **(1)** go deep on connectivity (the rejection reason), **(2)** drill the "find the gaps in this design" routine until it's automatic, **(3)** catch the fundamentals in code review *first* (SQLi, secrets, per-call init, pagination, races), **(4)** always justify tests by failure mode and cost, and **(5)** add a Staff layer to every answer: quantify, business metric, what you'd standardise.

---

## 1. Files

| File | What | When |
|---|---|---|
| [00-Round-Intel.md](00-Round-Intel.md) | Toolkit summary, recruiter hints, **7 candidate reports**, why people failed, the 60-min clock | Day 1 first |
| [01-Narrative-Playbook.md](01-Narrative-Playbook.md) | 7-step run-sheet, 8 clarifying questions, **gap-hunt checklist**, the answer formula, drawing tips, phrases | Day 1, then before every scenario |
| [02-Connectivity-APIs.md](02-Connectivity-APIs.md) | 19 topics: protocols, push/pull, **supplier integration**, timeouts, retries, idempotency, breakers, rate limits, backpressure, partial results, pagination, errors, auth, webhooks, outbox/saga, API checklist, versioning, observability, HTTP mechanics | Day 1 (the biggest block) |
| [02a-Connectivity-See-It.md](02a-Connectivity-See-It.md) | Pictures + the smallest code + a C++ analogy for the connectivity topics (so far §1 gRPC, §3 coalescing, §4 deadlines, §5 retries, §6 idempotency, §7 breaker/bulkhead) | With 02, when a term feels like an idiom |
| [03-QA-Testing.md](03-QA-Testing.md) | Pyramid vs honeycomb, each level's why/cost/tools, contract testing, NFRs, **failure-mode → test map**, template answer, shift-right, flaky tests, legacy-quality plan | Day 1 |
| [04-Code-Review.md](04-Code-Review.md) | Review order, comment labels, SOLID/patterns/smells, **12 planted-bug snippets** (Java, C#, Kotlin, Go, Python) with folded keys | Day 2 |
| [05-Scenarios.md](05-Scenarios.md) | **6 narratives** in Agoda's format (S1 = the flight aggregator actually asked in 2025 and 2026) with folded gap lists, redesigns, APIs, test plans | Days 1–2 |
| [06-Generic-Questions.md](06-Generic-Questions.md) | **50 generic questions** with 30–60 s model answers | Days 1–2 |
| [07-Mocks.md](07-Mocks.md) | 3 full 60-min mocks (new narratives) + the 5-attribute rubric | Day 2 + eve |
| [08-Recall-Day-Of.md](08-Recall-Day-Of.md) | One-page recall + day-of checklist | Eve + morning |
| [CLAUDE.md](CLAUDE.md) · [PROGRESS.md](PROGRESS.md) | Coach mode for Claude (interviewer persona) · tracker | Throughout |
| `Agoda_Technology_BE_IV2_Interview_Toolkit_2026.pdf` | Agoda's toolkit (local only, **git-ignored**: it's marked Internal and this repo is public) | Reference |

**Reused, don't redo:** [System Design Masterclass notes](../../System%20Design/Arpit-Masterclass/README.md): 01-02 (polling/WebSockets/SSE, queues vs streams, Kafka), 02-01 (locking, `SKIP LOCKED`), 03-01 (remote locks), 05-01 (caching, consistent hashing), 07-02 (flash sale). Stories for "tell me about a time…": [04-Projects-Behavioral](../04-Projects-Behavioral/README.md).

---

## 2. The 2-day plan

**Daily rule:** everything **out loud**. Reading isn't practice. For each topic, close the file and explain it in 60 s as if to the interviewer, including one trade-off and one failure mode.

### Day 1: "Find the gaps, own the connectivity"
| Time | Block | What |
|---|---|---|
| 08:30–09:00 | MUST | [00-Round-Intel](00-Round-Intel.md) + watch the [prep video](https://www.youtube.com/watch?v=ok1Sa-ea7YY); write notes in Intel §6 |
| 09:00–09:45 | MUST | [01-Narrative-Playbook](01-Narrative-Playbook.md): memorise the 7 steps + gap checklist |
| 09:45–12:15 | **MUST** | [02-Connectivity](02-Connectivity-APIs.md) §1–§11 (protocols → pagination). After each section: 60 s aloud |
| 12:15–13:15 | Break | |
| 13:15–14:15 | **MUST** | [02-Connectivity](02-Connectivity-APIs.md) §12–§19 (errors → HTTP mechanics) |
| 14:15–15:45 | **MUST** | [03-QA-Testing](03-QA-Testing.md), especially §3, §7 (draw the map from memory), §8 (say the template answer) |
| 15:45–16:00 | Break | |
| 16:00–17:30 | **MUST** | **Scenario S1** (40 min, timed, aloud, write the gap list + diagram) → open the key → score. **Scenario S2** (30 min) → score |
| 17:30–18:00 | SHOULD | Generic questions A1–A12 |
| 19:30–20:15 | SHOULD | Generic questions B1–B16 (the connectivity set) |
| 20:15–20:30 | MUST | Log weak spots in [PROGRESS](PROGRESS.md) |

### Day 2: "Review like a Staff engineer, then mock"
| Time | Block | What |
|---|---|---|
| 08:30–09:00 | MUST | Spaced review: re-explain your 3 weakest Day-1 topics aloud |
| 09:00–09:30 | **MUST** | [04-Code-Review](04-Code-Review.md) §1–§3 (order, labels, SOLID/patterns) |
| 09:30–11:15 | **MUST** | **CR-1** (8 min) then CR-2…CR-12 (4 min each), timed, aloud, self-scored with §5 |
| 11:15–12:45 | **MUST** | Scenarios **S3–S6** (20 min each: clarify + gap list + top-3 fixes + test plan) |
| 12:45–13:45 | Break | |
| 13:45–14:15 | SHOULD | Generic C1–C12, D1–D6, E1–E4 |
| 14:15–15:15 | **MUST** | **Mock 1** with the coach (*"Run Mock 1"*) or solo + recording |
| 15:15–16:00 | MUST | Fix the top 3 issues from Mock 1: re-read those sections, re-answer aloud |
| 16:00–16:30 | MUST | Prepare 2 stories: an integration that failed in prod (E4) and a review comment that changed a design (D6) |
| 17:00–18:00 | **MUST** | **Mock 2** |
| 18:00–18:30 | MUST | Log scores + weak spots |

### Days 3 → interview eve (about 2 h/day)
- **Hands-on reinforcement** in WSL: **Tier 0 (P0–P7)** of the [Prototype Labs Plan](../../System%20Design/Prototype-Labs-Plan.md), the cohort exercises in Agoda-priority order: booking with no double booking + idempotency (W2#1) → bounded pool as a bulkhead (W1#1) → **supplier gateway capstone** (deadline, retries, breaker, partial results, cache, rate limit) → cursor pagination (W8#2) → signed webhooks (W7#9) → JWT/HMAC auth → outbox queue (W7#8). Short on time? Do P0 → P1 → P3 → P4 only. Building them makes every connectivity answer concrete ("when I built this, the breaker…").
- 20 min/day: 10 random generic questions (*"Generic drill"*) + 1 CR snippet.
- **Eve:** **Mock 3** in the morning, the [Recall page](08-Recall-Day-Of.md) in the evening. **Nothing new after 6 pm.**

---

## 3. Three ways to practise
| Mode | How |
|---|---|
| **Solo** | Prompts + folded keys in 04/05/06/07. Answer aloud *before* opening a key. Record mocks. |
| **Coach (Claude)** | Open this folder in Claude Code: *"Run Mock 2"*, *"Scenario S1"*, *"Review CR-4"*, *"Generic drill"*, *"Gap drill"*, *"Explain to a PM: idempotency"*. [CLAUDE.md](CLAUDE.md) keeps Claude in interviewer mode with the faults hidden. |
| **Hands-on** | The WSL labs: the same concepts, running and tested. |
