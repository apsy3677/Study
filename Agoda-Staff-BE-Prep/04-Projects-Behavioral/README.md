# Projects & Behavioral: Strategy

Goal: be able to explain any project clearly. That means getting across how hard it was and what *you* did, and then holding up under follow-up questions. Every claim has to be true.

| File | Where it's used | What it is |
|---|---|---|
| [Work-Prompt-Pack.md](Work-Prompt-Pack.md) | **Work laptop (Cursor)** | Rules plus prompts for each pass. It never mentions interviews, so it's safe to paste. |
| [Worker-Count-Story.md](Worker-Count-Story.md) | Home | Brain-dump questions, the story skeleton and likely follow-ups for the worker-count issue |
| This README | **Home only** | The strategy and the decoder. Never copy it to the work laptop. |

---

## 1. The plan

```text
 WORK LAPTOP (Cursor)                        HOME (Claude / ChatGPT)
 ─────────────────────                       ───────────────────────
 sources -> evidence ledger                  brain-dump from memory  (do this FIRST)
        -> debrief (Cursor asks, you answer)          │
        -> one-pager                                  │
        -> case-study discovery                       ▼
        -> deep dive + 30s/2m/5m walkthroughs  ──►  retell it from memory
        -> public-safe version                 ──►  skeptical review + follow-ups
                                                     mock rounds, out loud
```

- **Work laptop is for evidence only.** That means anything that needs the tickets, CLs, status docs or review threads: the dates, the mechanisms, the real sequence of events.
- **Home is for performance.** Rehearsal, review and mock drills don't need any work material, so they shouldn't spend work-laptop time.
- **Your memory comes first for debugging stories.** Do the brain-dump before reading the tickets. Tickets record *what* happened. Your memory holds *what you thought and tried*, and that is the part that makes the story strong.

## 2. Which Cursor mode and model, for each pass

| Pass | Mode | Model | Why |
|---|---|---|---|
| 0 Inventory, 1 Ledger, Part C steps 1–2 | Agent | Opus | Needs judgment while reading long ticket threads |
| 2 Debrief, 6 Review drill | Ask | Opus | The quality of the follow-up questions is the whole value |
| 3 One-pager, 4 Discovery, 5 Deep dive, 9 Matrix | Agent | Opus | "What is actually interesting here?" is a reasoning task |
| 7 Public-safe, 8 Batch, 10 Consistency | Agent | Sonnet | Formatting and checking. No need to spend Opus on it. |

Cursor setup:

- **Open the portfolio folder as its own Cursor window.** Don't open it inside your main workspace. That keeps your 14 always-on work rules and your knowledge-system automation out of it, and keeps its rules out of your daily work.
- **Name the folder neutrally**, e.g. `eng-portfolio/`. Never use a name like `interview-prep/`.
- **Keep it outside the paths your knowledge system indexes.** The rules also add `do_not_ingest: true` to every file, which matches the convention you already use.
- **@-mention `00_RULES.md` in every chat.** That's the simplest option. You can also save it as `.cursor/rules/portfolio.mdc` with `alwaysApply: true` inside that folder only.
- **Turn off auto-run for terminal commands.** Approve only read-only `p4` commands (`changes`, `describe -s`, `filelog`).

## 3. How much to use the work laptop

Budget about **8–10 hours in total, spread over 1–2 weeks**, not one long session.

| Work | Time |
|---|---|
| Pass 0 inventory | ~45 min |
| Top 3–4 projects × (ledger 20 min + debrief 20 min + one-pager/discovery 20 min + 1–2 deep dives 30 min) | ~5–6 h |
| Worker-count reconstruction (Part C) | ~1 h |
| Competency matrix + consistency check | ~45 min |
| Remaining projects in a Sonnet batch | ~30 min |

What to keep in mind on that machine:

- **Keep each agent run scoped to one project.** Opus agent runs over hundreds of tickets cost real money and show up in team usage dashboards. Don't let it crawl everything.
- **Assume an admin could read any prompt and output.** The pack passes that test. Its stated purposes (self-review, promotion case, case-study talk, knowledge transfer) are all genuine uses of the output, and you could show it to your manager without awkwardness.
- **The pack hides the keyword, not the activity.** Never type a target company's name, never paste a job description, and never bring this README or the decoder onto that machine.
- **Your real exposure is moving files off the laptop, not prompt wording.** Emailing, uploading or syncing work files to personal accounts is what DLP tools flag, and it's usually where policy actually draws the line. Check your company's AI and data-use policy.
- **The safest bridge home is your head.** Read the public-safe version at work, then retell it from memory to Claude at home. That doubles as your first rehearsal.

## 4. Decoder: what the pack's neutral terms mean

| Pack term | What it is for you |
|---|---|
| 30-second walkthrough | Project one-liner for "walk me through your background" and for openers |
| 2-minute walkthrough | The standard behavioral answer |
| 5-minute walkthrough + mechanism explanation | The deep-dive project discussion (Agoda IV4, "overall technical") |
| Hard questions bank | The interviewer's follow-ups |
| Skeptical review drill (Pass 6) | A mock behavioral round |
| Readiness scorecard | Story quality bar |
| Public-safe version | What you can say in the room, and what you bring home |
| Competency matrix (Pass 9) | Which question families you can and can't answer yet |

Competency tag → the questions it answers:

| Tag | Typical questions |
|---|---|
| Debugging under uncertainty | Hardest bug · solved without all the information · production issue |
| Technical depth | Most technically complex project |
| System design and trade-offs | A design decision you made · a trade-off you'd revisit |
| End-to-end ownership | Owned something beyond your role · saw it through |
| Turning ambiguity into clarity | Little direction · vague requirements |
| Influence without authority | Convinced others · drove change you didn't own |
| Disagreement and resolution | Disagreed with a peer or manager · were wrong and changed your mind |
| Customer focus | Customer-impacting issue · went beyond for a customer |
| Delivery under pressure | Tight deadline · escalation |
| Prioritization and saying no | Competing priorities · pushed back on scope |
| Scope change / pivot | Changed direction mid-project |
| Mistake, failure and recovery | A failure · a mistake you made |
| Raising the quality bar | Improved engineering practices · reviews and tests |
| Simplification | Reduced complexity or tech debt |
| Mentoring and growing others | Helped someone grow |
| Force multiplication | Improved the team's productivity |
| Learning something new fast | Ramped up on something unfamiliar |
| Cross-team collaboration | Worked across teams or time zones |
| Acting on feedback | Received critical feedback |

Aim for at least one **strong** story for each row. One story can cover 2–3 tags, but don't stretch a story to cover a tag it doesn't really fit.

## 5. Why the old Cursor stories can't be used

[`DS-2025/Behavioral/Meta_Behavioral_Staff_Stories.md`](../../DS-2025/Behavioral/Meta_Behavioral_Staff_Stories.md) has factual errors an interviewer would catch:

| Story | What it says | What your evidence-backed profile says |
|---|---|---|
| #1, #11, #18 | DPV Code Coverage "at Adobe" | Synopsys |
| #4, #14 | RIBS → Hyperdrive "at Synopsys" | Adobe |
| #5, #17 | Save/Restore "at Adobe" | Synopsys |
| #2 | Stream 2.0 into PowerPoint Recording Studio | Excel Win32 |
| #3 | SKU filtering as a live outage with a "war room", "contained within hours" | Preventive filtering against sev-2s that had taken 2–3 weeks to fix |
| #16 | A critical bug in `delivery_truck_interview.cpp` | That's a practice-problem file, not a work bug |
| #18 | "Led the DPV Code Coverage team", "saving millions" | Primary Hector-side developer; no cost figure exists |

[`DS-2025/Competency_Stories_Part1.md`](../../DS-2025/Competency_Stories_Part1.md) Story 1 has the same problem. The token-allocation conflict, the tiered token numbers and the "25–30% license utilization" don't appear anywhere in [`Build_resumes.md`](../../Resumes/2026/Build_resumes.md). Verify them through the pack before using any of it.

**Treat both files as retired.** One wrong employer or one invented number found in the room makes every other story suspect. Section 3 of the pack's rules bans each of these failure modes by name.

## 6. Turning a write-up into something you can say

- **Memorize the beats, not the script.** Each deep dive ends with a 6–8 line skeleton. Practice from that.
- **Open with the headline**, i.e. why the story is worth hearing: "The symptom pointed at X, but the cause was Y."
- **Keep context to about 20 seconds.** Spend the time on *why it was tricky* and *what you decided*.
- **Include exactly one trade-off, one number (or concrete outcome), and a one-line learning.**
- **Say "I" for your actions and "we" only for the team's.** Name who did the other parts.
- **Record yourself.** If a 2-minute answer runs past 2:30, cut context, not difficulty.
- **Translate the domain.** Agoda interviewers won't know DPV, Hector or VDB. Each project's jargon table tells you which terms to drop from the short version.

## 7. Order of work, given that IV1 coding is next

1. **Now, 20 min at home:** answer the [worker-count brain-dump](Worker-Count-Story.md#step-1-brain-dump-answer-in-13-rough-lines-each) in chat with Claude.
2. **This week, at work, ~2 h:** Pass 0 inventory, then Part C (worker count).
3. **After IV1:** Passes 1–5 on the top 3–4 projects, then Pass 9 to find the gaps.
4. **Before IV4:** mock rounds at home from the public-safe versions.
