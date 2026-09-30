# Lead Signals, Behavioral & Project Deep-Dive (secondary priority, but R1 **will** open with your resume)

> Facts below come from your own notes (`Resumes/2026/profile-review-2026-09-v2.md`, `Resumes/EDA-Non-EDA.txt`). Anything marked **[confirm]** isn't verified yet. Don't say a number you can't defend under three "why?"s.
> Confidentiality: describe *mechanisms and outcomes*, not Synopsys internals or customer names.

---

## 1. What "Lead" means in this JD, and how you'll be judged
| JD phrase | Signal they look for | Your evidence |
|---|---|---|
| "Lead a team to improve performance of key applications/benchmarks" | You set measurable goals, split the work, and measured the result | Decoupling program (2–3 changes/sprint for 6+ months, ~75% coupling cut); licensing suite 38→9 tests; perf/scale work in DPV |
| "Drive sophisticated issues to resolution" | Ownership under ambiguity, customer escalations | Coverage subsystem: every release since 2023, escalations from 8 customer accounts, root cause → regression test → fix across release streams |
| "Communicate effectively, work across teams" | Cross-site/cross-team alignment | Agreed the coverage DB hierarchy with the Verdi team (Taiwan); customer summit talk; internal talk that got the pattern adopted |
| "Debuggers, profilers" | Hands-on depth | gdb/valgrind/perf stories (prepare one; see C4 §7) |

## 2. Your 90-second intro (tailor it and say it out loud 5 times)
> "I'm a Staff Engineer at Synopsys with about 11 years across Synopsys, Microsoft and Adobe, mostly large C++ systems.
> At Synopsys I work on VC Formal's datapath validation. I own the C++/RTL coverage subsystem end to end: design, every release since 2023, and escalations from our semiconductor customers.
> I also led a long-running decoupling effort in a 2M+ line C++ codebase. That incremental dependency-inversion work cut coupling by about 75% without a rewrite, and other engineers adopted the pattern.
> And I took our licensing through three models in two years without breaking existing customers.
> Before that I owned PowerPoint Recording Studio features at Microsoft, and worked on Photoshop Elements and AEM at Adobe.
> I'm excited about this role because it combines what I've been doing (performance and scale in EDA-grade C++, plus leading technical changes across teams) with building the toolchain for AMD's own silicon."

## 3. The project deep-dive template (7 layers: they'll drill until you run out)
1. **Context**: the product, the users, the scale (lines of code, design sizes, customers).
2. **Problem**: why it mattered (cost of not solving it).
3. **Constraints**: backward compatibility, release trains, team size, risk.
4. **Options considered**: at least 2, and why you rejected them. *This is the #1 lead signal.*
5. **What YOU did**: design, code, convincing people, the rollout.
6. **Result**: numbers + adoption + what it enabled.
7. **Retrospective**: what you'd do differently; what broke along the way.

### Prepared stories (fill the gaps before the interview)
| # | Story | Best for questions like | Key facts | Gaps to fill |
|---|---|---|---|---|
| S1 | **Decoupling shared code from engine internals** (2M+ LOC) | "Hardest technical problem", "led change across teams", "handled tech debt", "influence without authority" | Prior attempts stalled; chose incremental dependency inversion (callback-based options layer) over a big-bang split; 2–3 changes/sprint for 6+ months; ~75% coupling reduction (132→34); talk; 2 engineers adopted it | **Build-time delta** [confirm]; how you measured coupling; one pushback you handled |
| S2 | **Licensing through 3 models in 2 years** | "Ambiguity", "tough trade-off", "customer impact", "testing strategy" | Token → per-app cores → tiered with fallback (existing customers kept working); 7-checkpoint probe harness: triage weeks → ~2 days; suite 38 → 9 tests without losing coverage | Who decided the fallback, and what the risk was; one incident |
| S3 | **Coverage subsystem ownership** | "Ownership", "customer escalation", "cross-site collaboration", "quality" | Built the coverage DB writer from scratch; agreed the hierarchy with the Verdi team (Taiwan); every release since 2023; 8 customer accounts; customer summit talk | One concrete escalation: symptom → root cause → fix → prevention |
| S4 | **Performance/scale for huge designs** (partitioning + multiprocessing) | "Biggest perf win" (**the JD's core question**) | From your 2024–25 resume: partitioning and multi-processing support for massive designs | **Numbers** (runtime/memory before→after), processes vs threads rationale, load balancing, determinism. If you can't defend it, lead with S1 or the Adobe lazy load (−60% load time) |
| S5 | **Save/restore persistence** | "Designing for backward compatibility", "serialization" | Extended save/restore so enterprise flows (case-splits, SVA results, coverage proofs) survive a restored session; XML-based persistence | Which customer flow it unblocked [confirm]; XML vs binary trade-off (maps to Vivado DCP!) |
| S6 | **AI tooling for your own workflow** | "How do you use AI tools?" (**AMD asks this in 2025–26**) | 9 agent skills, 500+ doc index; your triage went from 2–3 h to 5–10 min; demoed to the team | Adoption by others [confirm]. Say "my workflow", not "the team's" |
| S7 | **Microsoft Recording Studio / Cameo** | "Shipping to millions", "working with PMs/designers" | Owned camera/background-blur features; Cameo camera overlays | Your specific contribution vs the product metrics |

## 4. Behavioral bank (STAR, "I" not "we", end with a number or lesson)
| Competency | Likely question | Story |
|---|---|---|
| Technical leadership | "Tell me about a technical change you drove across teams." | S1 |
| Ambiguity | "A project with unclear requirements?" | S2 |
| Ownership / customer | "A critical customer issue you resolved?" | S3 |
| Conflict | "You disagreed with a senior engineer/architect/manager." | S1 (pushback on incremental vs big-bang) or S2 (the fallback design) |
| Failure | "Something that didn't go well?" | Pick a real one: a missed estimate, a regression you shipped, what you changed after |
| Mentoring | "How do you grow engineers?" | Review checklists, pairing on debugging, delegating owned sub-areas, the talk that got S1 adopted |
| Prioritization | "Tech debt vs features?" | S1: incremental delivery alongside features, a measurable debt metric |
| Quality | "How do you ensure quality in a large C++ codebase?" | S2's probe harness, regression discipline, sanitizers, code review |
| Influence | "Convinced people without authority?" | S1 (talk + a working pattern + small safe PRs) |
| AI fluency | "How do you use AI tools day to day?" | S6 + verification discipline + confidentiality rules |

## 5. Tricky questions: prepared answers
- **Why leave Synopsys?** Positive framing only: *"I want to build EDA software for the silicon my company designs, in a Lead scope focused on performance. Vivado's scale and QoR problems are exactly where I want to grow."* Never criticize your employer.
- **Why AMD?** (a) domain fit (EDA scale + formal + C++ perf), (b) closer to silicon (Vivado/Versal), (c) the Lead scope. Mention one thing you actually read about Vivado or Versal.
- **You haven't done synthesis/place/route.** *"Right, my EDA depth is in formal/datapath verification. The transferable parts are large-scale C++ on netlist-like graphs, performance under memory pressure, SAT-based reasoning, and customer-grade quality. I've been reading up on the implementation side (PathFinder, analytic placement, incremental STA), and I ramp fast."*
- **Compensation / notice period:** defer to the recruiter; know your notice period and your number.
- **Competitor/NDA:** *"I'm happy to talk about the approach and results; I'll keep product internals general."*

## 6. Questions to ask them (pick 2–3)
1. What are the top runtime/QoR bottlenecks the team is attacking this year?
2. How is performance tracked: benchmark suites, per-commit gates?
3. What would success look like for this Lead role at 6 months?
4. How is the team split (synthesis / place / route / timing), and where does this role sit?
5. How much of the work is new algorithms vs scaling and hardening existing ones?

## 7. Before the interview: 60-minute project prep checklist
- [ ] Fill the **Gaps** column for S1–S4 (numbers you can defend).
- [ ] Draw the architecture of S1 and S3 on paper (boxes and arrows) in under 2 minutes each.
- [ ] Prepare "options considered" for S1, S2 and S4.
- [ ] One failure story, told honestly.
- [ ] Record the 90-second intro and listen to it once.
