Build_resumes.py


LinkedIn Profile 2026
---
type: portfolio
author: Anuj Pratap Singh Yadav
role: Staff Engineer, VC Formal R&D (Synopsys)
status: complete
date: 2026-07-05
period: June 2023 - July 2026
do_not_ingest: true
sources:
  - P4 (260 changelists = 190 submitted + 70 shelved, Jun 2023 - Jun 2026)
  - /global/vcf01/anuyadav/vcf/docs/weekly-status/VC Formal Anuj Weekly Status.docx (Jun 2023 - May 2026)
  - /global/vcf01/anuyadav/vcf/docs/portfolio/ (INDEX + 8 project docs)
  - /global/vcf01/anuyadav/vcf/docs/performance-reviews/ (Feb 2026 check-in + Apr 2026 OKR + May-Jul 2026 OKR + Mar 2026 Swarm self-review)
  - Cursor / AI ecosystem: cursor-config (7 commands, 14 rules, 3 subagents, 79 plans), knowledge-system (532 docs indexed), 9 custom skills
---

# Engineering Profile 2026 -- Anuj Pratap Singh Yadav

**Staff Engineer | VC Formal R&D | Synopsys Inc.**
**Period at Synopsys: June 2023 -- July 2026 (~3.1 years)**
**Total industry experience: ~11 years (Adobe -> Microsoft -> Synopsys)**

This document is the project-level, IDs-free narrative of the current
Synopsys tenure. It is the source of truth for the resume, LinkedIn
Experience section, and interview stories. Do not ingest into the
knowledge system.

Authoring rules applied:
- No JIRA IDs, no CL numbers, no Swarm review numbers.
- Customer names and tool / feature names are OK.
- All quantitative claims are evidence-backed (see `sources` above).
- No fabricated numbers or ownership claims.

---

## 1. At a glance

| Signal | Number |
|---|---|
| Total industry experience | ~11 years (Adobe 2015-2021, Microsoft 2021-2023, Synopsys 2023-present) |
| Synopsys tenure | ~3.1 years, VC Formal R&D (Noida) |
| Role progression at Synopsys | R&D Engineer, Senior II (May 2023 - Jan 2024) -> Staff Engineer (Feb 2024 - Present) |
| Production changelists (Hector engine + VCF shell) | 190 submitted + 70 shelved = 260 total |
| Named customer accounts owned end-to-end | 8 (Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, Untether AI) |
| Release streams shipped | 5 (TD, X-2025.06, W-2024.09, V-2023.12, U-2023.03) |
| Code reviews authored | 50+ |
| Code reviews participated in | 70+ |
| Talks | Internal Tech Corner (One Percent Solution, May 2026); Nvidia internal formal-verification summit |
| Mentorship | 2 engineers picking up the CommonFormalOptions pattern |
| Prior tenures | Microsoft (2021-2023, PowerPoint / OneDrive / Excel), Adobe (2015-2021, Photoshop Elements / AEM Docx) |

---

## 2. Project portfolio (big-picture, no IDs)

### Project 1 -- Architectural decoupling: "One Percent Solution"

- **What it was:** Common code in VC Formal was transitively coupled to
  Formal / Banff / Hector internals via header dependencies; a single
  Common change forced rebuilds of 2000+ files. The pattern had accreted
  for a decade.
- **Why it mattered:** Every Common change slowed every Formal team's
  iteration. Attempts to modularize had stalled because there was no
  agreed-on decoupling pattern.
- **My scope:** Designed and drove the architectural pattern; sustained the
  burn-down cadence; owned the internal talk.
- **Technical approach:** CommonFormalOptions callback layer -- classic
  dependency inversion via std::function. Common code registers a getter
  for each option it needs; Formal code registers the actual answer at
  init time. Applied IWYU (Include What You Use) methodology to break
  transitive header chains.
- **Outcome:**
  - Internal orange-bubble dependency metric: 110 -> 43
  - Header-file dependencies for the touched files: 61 -> under 10
  - Sustained 2-3 CLs / sprint burn-down for 6+ months
  - Delivered internal Tech Corner talk with full pack (speaker notes,
    cheat sheet, Q&A bank, dry-run analysis)
  - Mentored two engineers now doing their own decoupling CLs
  - Pattern is now cited as go-to for similar problems

### Project 2 -- Property and Assertion Density reporting

- **What it was:** DPV had no equivalent to FPV's density analytics.
  Nvidia and AMD needed output-signal visibility for signoff.
- **Why it mattered:** Without density analytics, customers couldn't
  measure verification completeness on datapath designs.
- **My scope:** Full-stack feature owner across Hector engine, VCF TCL
  shell, dual-process XML IPC, and HTML reporting.
- **Technical approach:** Five sub-capabilities delivered in sequence:
  bit-level granularity, RTL2RTL flow, output-coverage check,
  consolidated reporting, NLDM-based design backend.
- **Outcome:** Shipped to TD + three service-pack streams. Foundation for
  future signoff automation.

### Project 3 -- DPV C++ Coverage infrastructure (save_covdb + Verdi integration)

- **What it was:** At join, DPV could not merge multiple proofs or save
  coverage into Verdi's VDB. Nvidia and Intel workflows were blocked.
- **Why it mattered:** Coverage-database write / merge / view was table
  stakes for enterprise customer signoff.
- **My scope:** Primary Hector-side developer; coordinated with the Verdi
  team in Taiwan on VDB hierarchy design.
- **Technical approach:** Built save_covdb from scratch on the proprietary
  UCAPI library. Proof-list union semantics for merging multiple proofs.
  Dual-design (-design) flow for handling reference / implementation
  design pairs. UNR-with-constraint annotations.
- **Outcome:** Largest sustained delivery to date (~2.5 years); several
  dozen child issues closed; 40+ regression tests. Presented at Nvidia
  internal formal-verification summit.

### Project 4 -- DPV C++ Coverage enhancements

- **What it was:** Production-hardening of the coverage subsystem across a
  year of customer feedback.
- **My scope:** Feature-by-feature owner; RCA lead on customer-reported
  issues.
- **Technical delivery:**
  - FOR-loop parent-block analysis (AMD)
  - Switch-case default handling (Intel)
  - Statement-level VDB depth
  - Call-depth column in HTML reports with sortable ASC / DESC / original
    (Nvidia)
  - Exclusive option groups
  - File-click highlight
- **Outcome:** Closed 8+ customer-reported issues; refreshed dozens of
  regression reflogs for the FOR-loop change.

### Project 5 -- DPV Licensing infrastructure (Token -> Cores -> Apex)

- **What it was:** Three-phase modernization of DPV licensing spanning two
  years.
- **Why it mattered:** Customers were hitting licensing friction at every
  scale point -- headless CI runs, multi-app runs, cores-per-license
  limits. Each phase unlocked a wave of customer productivity.
- **My scope:** Phase-owner across all three phases; validation harness
  builder.
- **Technical delivery:**
  - Phase 1: brought Token licensing to DPV end-to-end
  - Phase 2: raised cores-per-license to FPV parity (Base 1 -> 4, Elite
    4 -> 12)
  - Phase 3: implemented CoDa / FPV / SEQ Apex licensing with Elite-
    fallback hunt order
  - Built a T0..T6 license-probe validation harness (post-appmode,
    post-elaborate, post-sim_run, mid-solve, tail) that captures which
    FlexNet features check out at each phase. Used 4+ times during Q3
    2026 to triage probe regressions in ~2-day cycles instead of weeks.
- **Outcome:**
  - Licensing regression suite: 38 tests -> 9 (76% cut) with coverage
    preserved
  - Escalations resolved for Nvidia, Intel, AMD, ByteDance
  - Landed in TD; backports to 26.03 and 25.06-SP2 in flight

### Project 6 -- Save and Restore session extensions

- **What it was:** Enterprise customers needed the save_session /
  restore_session flow to work with UAL and case-split procs, SVA post-
  solveNB, report_assertion_density in restored sessions, and C++
  coverage proofs surviving restore.
- **My scope:** Owner across the session-persistence surface area.
- **Technical approach:** XML-based HecProblem persistence. Aligned
  -out_dir semantics across save / restore commands.
- **Outcome:** Filled the enterprise-blocker gaps. Now the assumed baseline
  for restored-session behavior.

### Project 7 -- RTL Coverage and solver configuration

- **What it was:** Two customer-driven RTL-side fixes.
- **My scope:** IC on both.
- **Technical delivery:** AMD RTL FOR-loop parent-block propagation for
  coverage accuracy; default Simon `-parMux` removal to align DPV/FPV
  proof behavior.
- **Outcome:** Validated against 200+ DPV regressions; shipped across
  three streams.

### Project 8 -- Customer escalation track record

Owned RCA -> regression test -> multi-stream ship pattern for:

- **Google:** AARCH64 Docker compose crash (urgent).
- **Nvidia:** -no_ui license-checkout path; output-bit visibility; CPP
  coverage HTML enhancements.
- **Apple:** Completeness check vs SVA assumption semantics.
- **Intel:** C++ coverage line-counting accuracy fix, RTL FOR-loop
  analysis.
- **AMD:** RTL coverage toggle analysis, DPV crash fixes.
- **ByteDance:** License checkout failure resolution.
- **Tenstorrent:** FuncCov / COI RCA.
- **Untether AI:** Miscellaneous coverage / licensing.

**Pattern:** own the RCA, build a regression test, ship across active
streams. Same playbook every time.

### Project 9 -- AI Engineering Productivity Platform (Cursor + Knowledge System)

- **What it was:** A VC-Formal-specific agent operating system built on
  top of Cursor.
- **My scope:** Sole builder; internal team demo delivered.
- **Technical delivery:**
  - 9 custom skills: JIRA, Swarm, P4 code review, build-check, VCF
    validation, license-validation matrix, reflog refresh, daily sprint,
    knowledge base
  - 7 persistent commands: `/implement-jira`, `/analyze-jira`, `/morning`,
    `/review-cl`, `/lint-fix`, and two more
  - 14 always-on `.mdc` rules
  - 3 subagents
  - 79 saved implementation plans
  - 532-document searchable knowledge index (self-healing auto-
    maintenance pipeline)
  - Jira Validation Compliance pipeline (daily cron, four strict rules)
- **Cited time savings:**
  - Regression triage: 1-2 hours -> 2-3 minutes
  - JIRA ramp-up: 3-4 hours -> 10-15 minutes
  - Test-case creation: 3 hours -> 30 minutes
- **Outcome:** Personally use it every day; demoed to the team in an
  internal skills session.

---

## 3. Technology and tech stack

**Languages:**
- C++ (primary, C++17/20; templates, RAII, std::function, callbacks,
  singleton patterns, multi-threaded worker queues)
- TCL (VCF command shell)
- Python (Cursor tooling, knowledge-system auto-maintenance, license
  validation harness)
- XML (Hector <-> VCF IPC protocol)

**Formal-verification domain:**
- DPV, FPV, SEQ
- NLDM, COI, save / restore, property / assertion density,
  fv_complexity
- C++ code coverage (statement / branch / condition)
- RTL coverage (line / toggle / branch / FOR-loop)
- Simon solver options

**Coverage stack:**
- save_covdb, UCAPI / libvcfucapi, Verdi (view_coverage, embed view),
  .vdb / .el files, LCOV

**Licensing stack:**
- FlexNet / SCL APIs, Token / Base / Elite / Apex tiers, Dynamic
  Orchestration worker licensing, T0..T6 probe harness

**Architecture patterns:**
- Callback / provider via std::function
- IWYU-driven decoupling
- Dual-process VCF <-> Hector XML IPC
- Adaptive-fallback licensing hunt order
- Dependency inversion

**Dev environment:**
- Perforce / P4 Swarm / vgp4lint
- Vim, GDB, VSCode SSH remote
- Synmake / vgbuild_grd
- LSF cluster

**AI / productivity:**
- Cursor Agent (skills, .mdc rules, commands, subagents, hooks)
- Cursor SDK
- Knowledge indexing pipeline
- JIRA / Swarm / P4 automation

**Customer engagement:**
- Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, Untether AI

---

## 4. LinkedIn "About" summary (3 paragraphs, paste-ready)

See `positioning-brief.md` section 4. The About block there is the current
canonical version.

---

## 5. LinkedIn "Experience" bullets for Synopsys (paste-ready)

```
Staff Engineer -- Synopsys Inc | Feb 2024 - Present
R&D Engineer, Senior II -- Synopsys Inc | May 2023 - Jan 2024
Noida, India

- Own the DPV C++ Coverage stack (save_covdb, UCAPI-based VDB generation,
  Verdi integration) shipped in every release since V-2023.12 and used by
  Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, and Untether
  AI. Presented at Nvidia's internal formal-verification summit.

- Architected and drove the "One Percent Solution" -- org-wide decoupling
  of Common code from the Formal engine in a 2M-line C++ codebase.
  Designed the CommonFormalOptions callback layer (dependency inversion
  via std::function); sustained a 2-3 CLs / sprint burn-down for 6+
  months; cut the internal orange-bubble dependency metric from 110 to 43;
  delivered an internal Tech Corner talk; mentored two engineers on the
  pattern.

- Delivered a three-phase DPV licensing modernization (Token -> per-app
  Cores lift Base 1 -> 4 and Elite 4 -> 12 -> Apex with CoDa/FPV/SEQ
  Elite fallback). Built a reusable T0..T6 license-probe validation
  harness. Cut the license regression suite from 38 tests to 9 while
  preserving coverage. Resolved escalations from Nvidia, Intel, AMD,
  ByteDance.

- Delivered full-stack Property & Assertion Density (report_assertion_
  density) across Hector engine, VCF TCL shell, dual-process XML IPC,
  and HTML reporting. Shipped 5 sub-capabilities (bit-level granularity,
  RTL2RTL flow, output-coverage check, consolidated reporting, NLDM-based
  design backend) across TD + three service-pack streams.

- Extended save_session / restore_session flow: UAL and case-split procs,
  SVA visibility after solveNB, density and grid-usage reports in restored
  sessions, C++ coverage proofs surviving restore. Designed XML-based
  HecProblem persistence.

- Resolved end-to-end customer escalations (RCA + regression test + multi-
  stream ship) for Google (AARCH64 Docker compose crash), Nvidia (-no_ui
  license-checkout path, output bit visibility), Apple (completeness check
  vs SVA assumption semantics), and Intel/AMD/ByteDance/Tenstorrent/
  Untether AI.

- Submitted 190 production changelists across the Hector engine and VCF
  shell over three years; authored 50+ code reviews.

- Built an internal Cursor-based engineering-productivity platform
  (9 custom skills, 79 saved plans, 14 rules, 3 subagents, 532-doc
  searchable knowledge index) that cut regression triage from 1-2 hours to
  2-3 minutes and JIRA ramp-up from 3-4 hours to 10-15 minutes. Delivered
  internal team demo.
```

---

## 6. Resume bullets -- tightest version

See `resume-eda-2page.docx` and `resume-faang-atlassian-2page.docx`.

---

## 7. Senior Staff / Principal positioning -- talking points

**Architectural ownership evidence:**
- CommonFormalOptions design + org-wide burn-down of a 2M-line C++
  codebase's Common <-> Formal dependency graph
- Three-phase Apex licensing hunt order (adaptive-fallback design)
- Bit-level Property / Assertion Density reporting design
- Dual-process VCF <-> Hector XML IPC (established during save_covdb)

**Cross-team influence evidence:**
- Mentorship (2 engineers picking up the CommonFormalOptions pattern)
- BU-level priority citations in weekly status reports
- Nvidia internal formal-verification summit presentation
- Internal Tech Corner talk to org

**Force-multiplier evidence:**
- 9-skill AI agent stack, used by self and demoed to team
- 532-doc knowledge base auto-maintained
- Weekly-status .docx pipeline (May 22 2026)
- Cited time savings: regression triage 1-2h -> 2-3 min; JIRA ramp-up
  3-4h -> 10-15 min; test-case creation 3h -> 30 min

**Customer fluency evidence:**
- 8 named accounts owned end-to-end across DPV and licensing
- Same customer-response playbook (RCA -> regression test -> multi-
  stream ship) applied repeatedly

---

## 8. Out of scope

- No knowledge-system ingestion (this file has `do_not_ingest: true`
  frontmatter).
- No P4 changes, no JIRA edits, no Swarm posts.
- No edits to existing portfolio / performance-review / status docs.
- No JIRA IDs or CL numbers in this document.

positioning-breif.md
---
type: positioning-brief
topic: resume-refresh-2026-07-05
status: complete
date: 2026-07-05
do_not_ingest: true
---

# Positioning Brief -- Anuj Pratap Singh Yadav

Purpose: the narrative that stitches your resume, LinkedIn, and interviews
together. If you can tell three stories -- crisply, from memory -- the
resume/LinkedIn become supporting evidence, not the pitch. This doc gives you
those stories plus copy-paste LinkedIn refresh text.

Do NOT ingest into the knowledge base.

---

## 1. Core narrative (1 paragraph, memorize this)

> "Eleven years of shipping software at every layer of the stack. I started
> at Adobe on desktop -- Photoshop Elements, AEM Docx -- moved to Microsoft
> on cloud SaaS at product-scale (PowerPoint Cameo shipped to ~1.2M of 4.2M
> monthly recording sessions, plus a purchase-events microservice for
> OneDrive), and now at Synopsys own the C++ coverage stack in the
> formal-verification tool every major chipmaker runs. Along the way I've
> gotten better at one thing in particular: taking a hard, entrenched
> architectural problem and quietly reshaping the codebase around it without
> breaking anyone -- most recently a decade-old header entanglement across a
> 2M-line C++ codebase that I decoupled through a callback-based options
> layer, delivered as an internal Tech Corner talk and mentored two
> engineers on the pattern."

Everything else in interviews is a variation of this paragraph.

---

## 2. The three stories you should be able to tell without notes

These are your "top of stack" interview stories. Practice each until you can
tell it in 3-4 minutes with metrics.

### Story 1 -- Architectural: The One Percent Solution

**Hook:** "We had a header in Synopsys VC Formal that, when touched, rebuilt
2000+ files. It had been that way for a decade. I broke it, one header at a
time, over six months, without shipping a regression."

**Setup:** VC Formal is Synopsys's flagship formal-verification product. The
Common code (utilities used by every app team -- FPV, DPV, SEQ) had grown
transitive dependencies on Formal / Banff / Hector internals. Every Common
change triggered a mega-rebuild. The team accepted it as fixed.

**What I did:** Designed the CommonFormalOptions callback layer -- classic
dependency inversion via std::function -- so Common code could ask "what's
your option value?" without knowing anything about who was answering.
Sustained a 2-3 CLs per sprint burn-down for 6+ months. Merge-conflict
resolutions on integration branches were treated as P0 interrupts to keep
cadence intact.

**Result:** Internal orange-bubble dependency metric went from 110 to 43.
Header-file dependencies dropped from 61 to under 10. Delivered internal
Tech Corner talk (full presentation pack -- speaker notes, cheat sheet, Q&A
bank, dry runs). Mentored two engineers who are now doing their own
decoupling CLs. The pattern is now cited as the go-to approach for similar
problems.

**Why it matters (the "so what"):** This is what Staff / Principal
engineering looks like: not "I shipped a feature" but "I removed a decade-
old drag on the entire team's velocity, and I did it without breaking
anyone."

**Interview signal:** Architectural ownership + patience + team leverage.

---

### Story 2 -- Product-scale ownership: PowerPoint Cameo + Recording Studio

**Hook:** "I owned a PowerPoint feature that shipped to 1.2 million of 4.2
million monthly recording sessions. Before the work, it was 1.5 million
sessions total. So we roughly tripled recording engagement and made Cameo --
the little customizable camera object on top of your slides -- the default
recording experience for a third of that."

**Setup:** PowerPoint Recording Studio in the Win32 app was serviceable but
uninspiring; explainer-video creation was declining. The team wanted to
renovate it.

**What I did:** New camera modes, live-feed background blur, video export,
and the Cameo customizable-camera object (shape / size / layout controls to
optimize slide + camera composition). C++ in the Oasysnet platform.
Instrumented telemetry across Recording and Export events for feature-
health monitoring. Led the automation crew for v1 of the Explainer Videos
release.

**Result:** Recording-sessions MAU 1.5M -> 4.2M. Cameo in ~1.2M of the 4.2M.
Feature stayed healthy in production through my ownership window.

**Why it matters:** Concrete product-scale numbers. Shows you can ship into
a codebase used by hundreds of millions and move real metrics.

**Interview signal:** Product judgment + working at enterprise scale.

---

### Story 3 -- Customer + systems: Three-phase Licensing Modernization

**Hook:** "I moved a licensing subsystem through three architectures in two
years -- Token, then per-app Cores, then Apex with an adaptive Elite
fallback -- while cutting the regression suite from 38 tests to 9 without
losing coverage. Nvidia, Intel, AMD, and ByteDance escalations dropped out
along the way."

**Setup:** DPV (data-path verification) needed licensing parity with FPV.
Each customer had a different pain point -- Nvidia on headless-mode
checkout, ByteDance on suite runtime, Intel and AMD on core allocation
under multi-app runs.

**What I did:** Sequenced three phases. Phase 1: brought Token licensing to
DPV end-to-end. Phase 2: raised cores-per-license to FPV parity -- Base 1 to
4, Elite 4 to 12. Phase 3: implemented CoDa / FPV / SEQ Apex licensing with
Elite-fallback hunt order. In parallel built a T0..T6 license-probe
validation harness -- a reusable test that runs `vcf` and captures which
FlexNet features check out at each phase (post-appmode, post-elaborate,
post-sim_run, mid-solve, tail). Used it to triage probe regressions in ~2-
day cycles instead of weeks.

**Result:** Licensing regression suite from 38 -> 9 tests (76% reduction),
coverage preserved. All named-customer licensing escalations resolved.
Feature landed in TD, backports to 26.03 and 25.06-SP2 in flight.

**Why it matters:** Long-arc systems ownership across two years, three
architectures, four customers. Shows you can sequence a multi-quarter
program without dropping bugs.

**Interview signal:** Sustained ownership + test infrastructure thinking +
customer fluency.

---

## 3. How the resume threads these three stories

- **Resume Positioning line** -- opens with "own the DPV C++ Coverage stack
  used by 8 named marquee customers... led an org-wide architectural
  decoupling." Threads Story 1 + customer roster.

- **Synopsys bullet 1 (E-S1 / F-S1)** -- customer ownership + Nvidia summit
  talk -> sets up Story 3 (customer fluency) and provides talk credibility.

- **Synopsys bullet 2 (E-S2 / F-S2)** -- One Percent Solution -> Story 1
  fully written down.

- **Synopsys bullet 5 (E-S5 / F-S4)** -- Three-phase licensing + 38 -> 9
  test cut -> Story 3.

- **Microsoft bullet 1 (M1)** -- Recording Studio + Cameo 1.2M/4.2M ->
  Story 2 fully written down.

- **Microsoft bullet 3 (M3)** -- Purchase Commerce EventHandler (C#, Docker,
  Azure EventHubs, SharePoint) -> distributed-systems evidence, supports
  FAANG variant's "Systems" skill claim.

- **Adobe bullet 3 (A3)** -- PSE/PRE licensing deactivation on uninstall
  via LEID -> makes the licensing thread longitudinal (2015 - present, 10
  years of licensing exposure).

- **Personal Projects (FAANG only)** -- Go distributed-systems primitives
  -> reinforces distributed-systems narrative for FAANG interviewers.

---

## 4. LinkedIn refresh -- copy-paste ready

### Headline (current on LI: "Staff Engineer at Synopsys | Ex-Microsoft | Ex-Adobe | NIT Bhopal")

Recommendation: keep the current headline. It's concise and correctly
positions you. Only alternatives worth considering:

**Alternative A (positioning-forward):**
> Staff Engineer, Synopsys VC Formal | Ex-Microsoft, Ex-Adobe | C++
> systems, formal verification, distributed systems

**Alternative B (target-forward, use if actively interviewing):**
> Staff Engineer -- C++ Systems, Formal Verification, Distributed Systems |
> Open to Staff / Senior Staff / Principal roles

Pick the current one if you're passive, Alternative B if you want to signal
availability.

---

### About (replace current)

Replace the entire current About with this:

```
I turn a decade of shipping software at every layer of the stack -- desktop
binaries, enterprise web, cloud SaaS with millions of monthly users, and
now high-performance C++ formal-verification tools used by every major
chipmaker -- into architectural leverage: refactoring flagship codebases
without breaking them, owning customer systems end-to-end, and building the
tooling that lets a team ship faster.

At Synopsys VC Formal (2023 - present), I own the DPV C++ Coverage stack
used by Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, and
Untether AI. Across three years and 190 production changelists on the
Hector engine and VCF shell, I've delivered a three-phase licensing
modernization (Token -> Cores -> Apex) that cut its regression suite from
38 tests to 9 while preserving coverage, and drove an org-wide
architectural decoupling initiative that broke a decade-old header
entanglement across a 2M-line C++ codebase -- delivered as an internal
Tech Corner talk, mentored two engineers on the pattern.

Before Synopsys, at Microsoft (2021 - 2023) I worked on OneDrive, Excel,
and PowerPoint Recording Studio. The Cameo feature I owned shipped in ~1.2M
of 4.2M monthly recording sessions. Before that, at Adobe (2015 - 2021), I
shipped across AEM Docx Web Editor and Photoshop Elements, including a
RIBS -> Hyperdrive CI/CD migration that cut install time ~50% and licensing
deactivation flows via LEID.

Stack: C++ (primary), Java, C#, TypeScript, Python. Formal verification,
licensing, distributed systems, LLVM-adjacent tooling, coverage
infrastructure. Alongside the day job I build distributed-systems
primitives in Go -- Bitcask, LSM/SSTable, WAL, consistent hashing, Bloom
filters, Kafka-style offsets -- as runnable prototypes in a personal study
repo (currently private; publishing selectively).
```

**Why this beats the current About:**
1. Opens with positioning ("I turn X into architectural leverage") instead
   of a descriptive header.
2. Threads all three interview stories.
3. Every metric is verifiable.
4. The Go prototype line is honest about scope (private, publishing
   selectively) -- no credibility landmine.
5. Named customer roster is complete (8 accounts).

---

### Skills (LinkedIn cleanup)

Current LI Skills section has 100+ endorsements, most of them noise
("adept", "well", "options trading", "camera operation", "trial
management", "app store optimization", etc.). Delete all and re-add only
the following ~25 skills (keeps recruiter algorithm signal clean):

**Primary:**
- C++
- Java
- C#
- TypeScript
- Python
- Go

**Systems:**
- Distributed systems
- Microservices
- Multi-process IPC
- Message queues
- Formal verification
- Code coverage
- Architecture
- Dependency management

**Backend / cloud:**
- Microsoft Azure
- Docker
- REST APIs
- Telemetry

**Frontend / desktop:**
- React
- Win32 development

**Tools:**
- Perforce
- Git
- CI/CD
- LLVM

Everything else -- delete.

---

## 5. What to do if you get *one* additional half-day to invest

Ranked ROI:

1. **Push 3 clean Go prototypes to a public GitHub repo** (Bitcask, Bloom
   filter, consistent hashing). Then update the FAANG resume's Personal
   Projects line with the repo URL. Biggest single upgrade to your FAANG
   candidacy.
2. **Clean up LinkedIn Skills** (delete + re-add 25 items per above).
3. **Rewrite LinkedIn About** using the block above.
4. **Ask your Synopsys manager for one measurable metric on the One Percent
   Solution** (e.g., specific file where incremental build went from X min
   to Y min). Adds a hard number to your strongest bullet.

---

## 6. What NOT to say in interviews

Anti-patterns to avoid:
- "I helped..." -- use "I owned / led / drove / architected / delivered."
- "We shipped..." -- specify what *you* shipped, then credit the team.
- "It was really hard..." -- describe the constraint concretely.
- "I use Cursor / Copilot for productivity" -- you *built* the Cursor
  platform, you didn't consume it. Different signal.
- Any adjective without a concrete example ("passionate", "results-
  driven"). Assume the interviewer is a senior engineer allergic to filler.

---

## 7. Elevator pitches (choose by audience)

**30 seconds (recruiter first call):**
> Staff Engineer with 11 years at Synopsys, Microsoft, and Adobe. At
> Synopsys I own the C++ coverage subsystem used by all major chipmakers
> and drove a large architectural refactor of a 2M-line codebase. At
> Microsoft I owned the PowerPoint Cameo feature that shipped to 1.2M of
> 4.2M monthly recording sessions.

**60 seconds (hiring manager screen):**
> I'm a Staff Engineer at Synopsys VC Formal where I've submitted 190
> production changelists across the Hector engine and VCF shell over three
> years. My biggest work has three threads: I own the C++ coverage stack
> that ships in every release and is used by 8 named customers including
> Nvidia, Intel, Apple, and Google. I drove an org-wide architectural
> decoupling of a decade-old header entanglement in a 2M-line C++ codebase,
> delivered as an internal talk and mentored two engineers on the pattern.
> And I sequenced a three-phase licensing modernization -- Token to Cores
> to Apex -- that cut the regression suite from 38 tests to 9 while
> preserving coverage. Before Synopsys, I owned PowerPoint Cameo at
> Microsoft (1.2M of 4.2M monthly recording sessions) and did the AEM Docx
> lazy-loading and RIBS-to-Hyperdrive migrations at Adobe.

**3 minutes (any deep behavioral):** Use Story 1, 2, or 3 above depending
on what the interviewer asks.

---

Done. Print this doc, keep it open during interview prep.

ResumeChangelog.md
---
type: audit-trail
topic: resume-refresh-2026-07-05
status: complete
date: 2026-07-05
do_not_ingest: true
---

# Resume Changelog -- 2026-07-05

Line-by-line delta between the previous resumes and the two new variants
produced today. For every bullet in the new resumes, this document names the
source doc / verified evidence it maps to, and explains what changed and why.

**Source files audited:**
- `/remote/us01home51/anuyadav/Downloads/Anuj/Anuj Resume March 2024-25-EDA.docx`
- `/remote/us01home51/anuyadav/Downloads/Anuj/Anuj Resume March 2024-25-Non-EDA.docx`
- `/remote/us01home51/anuyadav/Downloads/Anuj/Resume_AnujPratapSinghYadav_Staff_Engineer2025.pdf`

**New resumes produced:**
- `resume-eda-2page.docx`
- `resume-faang-atlassian-2page.docx`

**Ground-truth sources cited below:**
- **PLAN** = `/u/anuyadav/.cursor/plans/linkedin_profile_deep_dive_02b3c7da.plan.md`
- **PORT** = `/global/vcf01/anuyadav/vcf/docs/portfolio/00_INDEX.md` + 8 project docs
- **OKR** = `/global/vcf01/anuyadav/vcf/docs/performance-reviews/OKR_Progress_May_Jul_2026.md`
- **PERF** = `/global/vcf01/anuyadav/vcf/docs/performance-reviews/Performance_Check_In_Feb_2026_*.md`
- **STATUS** = `/global/vcf01/anuyadav/vcf/docs/weekly-status/VC Formal Anuj Weekly Status.docx`
- **LI** = LinkedIn profile fetched 2026-07-05
- **RES-OLD** = old resume files listed above

---

## 1. Global changes (both variants)

| # | Change | Rationale | Source |
|---|---|---|---|
| G1 | Positioning statement added (2-3 lines) at top | Old resume had generic "Software Engineer with a decade of experience". Staff+ resumes need a positioning claim in the first pass. | Plan file architecture, PORT, PLAN |
| G2 | Skills section restructured from 3-line list to 5 labeled sub-groups | Improves ATS keyword matching and shows depth by category. | ATS best practice; segment benchmark |
| G3 | Synopsys title progression added (R&D Sr II -> Staff) | Old resume elided the promotion. Showing progression tells a growth story. | LI (Feb 2024 promotion date) |
| G4 | Adobe title progression added (MTS -> SDE 2) | Same reason. | LI (Jan 2017 promotion date) |
| G5 | Adobe compressed from ~5 bullets to 3 bullets + merged tail | Staff+ at 11y allocates <15% to > 6-year-old roles. | Segment benchmark |
| G6 | 10th/12th CBSE percentages removed | Dropped in all staff+ resumes globally except India-fresher formats. | User approved Q7 |
| G7 | Hobbies section removed | Dropped at 11y+. | User approved Q7 |
| G8 | Competitive programming ratings removed | FAANG/EDA staff+ almost universally drop CP by year 8. | Segment benchmark; user approved |
| G9 | "Curser" (typo) not carried over; not listed as tool | Cursor stack listed as *built* tooling platform, not "tool user". | User approved Q7 |
| G10 | Location updated from "Noida, INDIA" to "Noida, India" for consistency | Cosmetic. | -- |
| G11 | Phone reformatted to +91-97523-73677 | International calling format for global targets. | RES-OLD (raw digits) |
| G12 | LinkedIn URL added to contact line | Standard staff+ practice. | LI |
| G13 | GitHub handle added to contact line | User has an active study repo; adding for FAANG credibility. | LI mentions GitHub |
| G14 | CL count updated: portfolio said "80+", now "190" | Plan file verified from P4 directly (190 submitted + 70 shelved as of Jun 2026). | PLAN |
| G15 | 5 release streams called out (TD + 4 SP streams) | New numeric evidence. | PLAN, PORT |
| G16 | Customer roster expanded from 4 (Nvidia, Intel, Apple, ByteDance) to 8 (add AMD, Google, Tenstorrent, Untether AI) | PLAN and PORT list 8. AMD is a recurring customer (RTL FOR-loop parent block, CPP crash). Google (AARCH64 Docker crash). Tenstorrent + Untether AI in the plan file. | PLAN, PORT, OKR |
| G17 | Section "Awards" retained but shrunk to a single relevant line | Kept only the Spot Award tied to a resume-listed project. | User approved Q7 |
| G18 | Removed: MathML standalone bullet, snippets, filtering library, checked-out delete, WAS PSE 2019 CrashReporter | All Adobe minor items. | User approved Adobe compression |

---

## 2. Positioning statement -- both variants

### EDA variant

**New (this doc):**
> Staff Engineer, 11 years shipping C++ systems and cloud services across Synopsys, Microsoft, and Adobe. At Synopsys, own the DPV C++ Coverage stack used by 8 named marquee customers (Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, Untether AI) and led an org-wide architectural decoupling of a 2M-line C++ codebase.

**Sources:** PLAN (customer roster + One Percent Solution context); PORT (executive summary and impact section).

### FAANG / Atlassian variant

**New (this doc):**
> Staff Engineer with a decade of full-stack shipping - desktop binaries, enterprise web, and cloud SaaS at Microsoft (Cameo shipped to ~1.2M of 4.2M monthly PowerPoint recording sessions) - now working on high-performance C++ inside the formal-verification tools that every major chipmaker runs. Currently owning the DPV C++ coverage stack at Synopsys across 8 named semiconductor customers, and drove an org-wide architectural decoupling of a 2M-line C++ codebase.

**Sources:** LI (Cameo 1.2M/4.2M), PLAN (customer roster + 2M-line codebase), PORT.

**Old (what we replaced):**
> "Software Engineer with a decade of experience building impactful systems across enterprise applications, cloud services, and formal verification tools..."
Generic; no positioning claim; no metric hooks; adjective-heavy.

---

## 3. Skills section -- both variants

### EDA variant Skills

| Row | Content | Source justification |
|---|---|---|
| Languages | C++ (primary, C++17/20), Python, TCL, Java, C#, TypeScript | RES-OLD (all listed except C++17/20); Python evidence via Cursor auto_maintain.py; TCL evidence via DPV commands; Java at Adobe AEM; C# at MS OneDrive; TypeScript at Adobe AEM + MS Excel. Dropped JavaScript, jQuery, Node, Objective C/C++, Bash (either weak evidence or noise). |
| Formal verification | DPV, FPV, SEQ, C++ code coverage (statement/branch/condition), RTL coverage, COI, property/assertion density, save/restore session flow | PORT/03/04/05/06/07; PLAN section 2 |
| Tools and infra | VC Formal, Hector engine, UCAPI/libvcfucapi, Verdi VDB, FlexNet/SCL, LCOV, Perforce/P4 Swarm, vgbuild/synmake, LSF, GDB | PLAN section 3 (technology and tech stack) |
| Architecture patterns | Callback via std::function, IWYU-driven header decoupling, dual-process XML IPC (VCF <-> Hector), dependency inversion, adaptive-fallback licensing hunt order | PLAN section 3; PORT/01 (CommonFormalOptions callback pattern); PORT/02 (dual-process IPC) |
| Engineering platform | Cursor SDK (custom skills, MDC rules, subagents), knowledge indexing pipeline, JIRA/Swarm/P4 automation, license-validation harness | OKR KR1a/b/c; PLAN section 3 |

### FAANG variant Skills

| Row | Content | Source justification |
|---|---|---|
| Languages | C++, Java, C#, TypeScript/JavaScript, Python, Go (study repo) | Same as EDA plus TypeScript/JavaScript grouped (Adobe AEM + MS Excel evidence). Go added as "study repo" -- honest scope, code not yet public. |
| Systems | Distributed systems, microservices, multi-process IPC, message queues, event-driven, callback-based decoupling, dependency inversion | LI (Microsoft Purchase Commerce EventHandler microservice); PORT/01 (callback-based decoupling); Personal projects (message queue in maven/); dual-process IPC in Synopsys |
| Backend / Cloud | Azure (EventHubs, SharePoint), Docker, REST APIs, telemetry, SDX; multi-service integration | LI Microsoft; RES-OLD (Azure listed); telemetry work called out on old resume |
| Frontend / Desktop | React, TypeScript, HTML/CSS; C++ Win32 desktop (PowerPoint, Excel, PSE) | LI Adobe AEM; LI Microsoft; LI Adobe PSE |
| Tooling and AI | Cursor SDK (built platform), Perforce/Git, CI/CD (RIBS/Hyperdrive, vgbuild/synmake), LLVM-adjacent | OKR KR1a/b/c; LI Adobe RIBS/Hyperdrive; docs/cpp-output-coverage/cpp-design-complexity-2026-06/03_CPP_Construct_Catalog_via_LLVM.md |

---

## 4. Synopsys bullets -- EDA variant

Each bullet cites its source. Numbers cited are only those that appear in a source doc (never invented).

### E-S1: DPV C++ Coverage ownership + Nvidia summit

**Bullet:** "Own the DPV C++ Coverage stack (save_covdb, UCAPI-based VDB generation, Verdi integration) shipped in every release since V-2023.12 and used by Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, and Untether AI; presented at Nvidia's internal formal-verification summit."

**Sources:**
- PORT/03: save_covdb primary developer, UCAPI, Verdi integration, Nvidia summit talk
- PLAN section 2 project 3: same, plus "presented at Nvidia internal formal verification summit"
- PORT/00 Executive Summary: 5 release streams listed as TD, X-2025.06, W-2024.09, V-2023.12, U-2023.03 (V-2023.12 = earliest post-join)
- PLAN section 1: 8 named customer accounts (Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, Untether AI)

**Old resume said:** "Designed and implemented comprehensive code coverage analysis for C++ designs..." -- generic; no ownership signal, no customer roster, no talks.

### E-S2: One Percent Solution

**Bullet:** "Architected and drove 'One Percent Solution' -- an org-wide decoupling of Common code from the Formal engine in a 2M-line C++ codebase; designed the CommonFormalOptions callback layer (dependency inversion via std::function), sustained a 2-3 CLs/sprint burn-down for 6+ months, cut the internal orange-bubble dependency metric from 110 to 43; delivered an internal Tech Corner talk on the pattern; mentored two engineers picking it up."

**Sources:**
- PORT/01 (One Percent Solution -- Architectural Decoupling)
- OKR KR4a: "Maintained the steady 2-3-CL-per-sprint cadence on P10237313-42413... orange-bubble dependency metric 110 -> 43 across the period"
- OKR KR4c: May 2026 org-talk delivered, mentored two engineers
- PLAN section 2 project 1: same claims

**Old resume said:** *nothing about this project.*

### E-S3: save_covdb 2.5-year delivery

**Bullet:** "Led 2.5-year save_covdb delivery: proof-list union semantics, dual-design (-design) flow, UNR-with-constraint annotations, HTML report with sortable call-depth column; coordinated with the Verdi GUI team (Taiwan) on VDB hierarchy; closed 8+ customer issues across FOR-loop parent-block (AMD), switch-case default handling (Intel), statement-level VDB depth (Nvidia)."

**Sources:**
- PORT/03: 2.5-year sustained delivery, proof-list merge, dual-design flow, UNR
- PORT/05 (CPP Coverage Enhancements): FOR-loop parent block (AMD), switch-case default (Intel), statement-level VDB depth, call-depth column, exclusive option groups
- OKR KR3b: P10237313-37090 call-depth column shipped
- PLAN section 2 project 3: coordination with Verdi Taiwan team
- OKR KR3b: "closed 8+ customer-reported issues"

### E-S4: Property and Assertion Density

**Bullet:** "Delivered full-stack Property and Assertion Density (report_assertion_density) across the Hector engine, VCF TCL shell, dual-process XML IPC, and HTML reporting; shipped 5 sub-capabilities (bit-level granularity, RTL2RTL flow, output-coverage check, consolidated reporting, NLDM-based design backend) across TD + three service-pack streams."

**Sources:**
- PORT/02 (Property Density & Assertion Density Reporting)
- PLAN section 2 project 2: 5 sub-capabilities enumerated

### E-S5: Three-phase Licensing Modernization

**Bullet:** "Delivered three-phase DPV licensing modernization (Token -> per-app Cores lift Base 1->4 and Elite 4->12 -> Apex with CoDa/FPV/SEQ Elite fallback); built a reusable T0..T6 license-probe validation harness; cut the license regression suite from 38 tests to 9 (76%) while preserving coverage; resolved escalations from Nvidia, Intel, AMD, ByteDance."

**Sources:**
- PORT/04 (DPV Licensing Infrastructure)
- PLAN section 2 project 5: 3-phase enumeration (Token/Cores/Apex); Base 1->4 and Elite 4->12; T0..T6 harness; regression suite 38 -> 9 (76%)
- OKR KR1a: T0..T6 license-probe harness productized
- OKR KR2a: Apex Licensing landed in TD

### E-S6: save/restore session extensions

**Bullet:** "Extended save_session / restore_session flow to unblock enterprise customers: UAL and case-split procs, SVA visibility after solveNB, report_assertion_density and report_grid_usage in restored sessions, C++ coverage proofs surviving restore; designed XML-based HecProblem persistence; aligned -out_dir semantics across save/restore."

**Sources:**
- PLAN section 2 project 6: exactly this enumeration
- PORT/07 (Command Infrastructure & Usability): save/restore flow references
- docs/analysis/SaveRestore_Proofs_DeepDive.md

### E-S7: Customer escalations track record

**Bullet:** "Resolved customer escalations end-to-end (RCA + regression test + multi-stream ship) for Google (AARCH64 Docker compose crash), Nvidia (-no_ui license-checkout path, output bit visibility), Apple (completeness check vs SVA assumption semantics), and Intel/AMD/ByteDance/Tenstorrent/Untether AI."

**Sources:**
- PLAN section 2 project 8: exactly this list with same phrasing
- PORT/00: 8 customer escalations, matching list
- OKR various KRs across the year

### E-S8: 190 CLs + 50+ reviews + Cursor platform

**Bullet:** "Submitted 190 production changelists (Hector engine + VCF shell) across 5 release streams; authored 50+ code reviews; built an internal Cursor-based engineering platform (9 custom skills, 79 saved plans, 532-doc searchable knowledge index) that cut regression triage from 1-2 hours to 2-3 minutes and JIRA ramp-up from 3-4 hours to 10-15 minutes."

**Sources:**
- PLAN "Source ground-truth": 260 CLs (190 submitted, 70 shelved) Jun 2023 -- Jun 2026
- PORT/00: 50+ code reviews authored
- PLAN "Source ground-truth": 9 custom skills, 79 plans, 532-doc knowledge index
- PLAN section 2 project 9: regression triage 1-2h -> 2-3 min, JIRA ramp 3-4h -> 10-15 min
- OKR KR1a/b/c

---

## 5. Synopsys bullets -- FAANG variant

Same source-of-truth as EDA variant. Differences from EDA are tonal only:

| # | EDA phrasing | FAANG phrasing | Reason |
|---|---|---|---|
| F-S1 | "DPV C++ Coverage stack (save_covdb, UCAPI-based VDB generation, Verdi integration)" | "C++ coverage-analysis subsystem in Synopsys' flagship verification tool" | Soften EDA jargon; retain scale signal |
| F-S1 | "presented at Nvidia's internal formal-verification summit" | "presented internally at Nvidia" | Same fact, less domain-specific |
| F-S2 | "decoupling of Common code from the Formal engine" | "decoupling initiative" | Same fact, less domain-specific |
| F-S3 | "on UCAPI, proof-list union semantics" | "on top of a proprietary coverage API, append-only VDB generation" | Vendor-neutral phrasing |
| F-S4 | "Token -> per-app Cores lift Base 1->4 and Elite 4->12 -> Apex with CoDa/FPV/SEQ Elite fallback" | "token licensing -> per-app cores lift -> adaptive-fallback licensing across CoDa/FPV/SEQ tiers" | Same fact, less domain jargon |
| F-S5 | Same as EDA (full-stack framing already works) | Same | -- |
| F-S6 | Same as EDA | "Nvidia (license-checkout path in headless mode, output-bit visibility)" instead of "-no_ui license-checkout path" | Non-EDA readers won't know -no_ui |
| F-S7 | Combined with S8 | Kept separate | -- |
| F-S8 | Combined with S7 | Separate bullet for internal Cursor platform | Better ATS keyword weight for "engineering-productivity platform" |

---

## 6. Microsoft bullets (both variants)

Both variants use the same 4 bullets. Sources:

### M1: Recording Studio + Cameo

**Bullet:** "Owned PowerPoint Recording Studio enhancements (camera modes, background blur, Cameo customizable-camera object, video export) driving monthly recording sessions from 1.5M to 4.2M; Cameo shipped to ~1.2M of the 4.2M sessions."

**Sources:** LI project "Explainer Videos in PowerPoint" (Jun 2021 - Nov 2021, MAU 1.5M -> 4.2M); LI project "Cameo in Recording Studio" (Jan 2022 - Apr 2022, 1.2M of 4.2M); RES-OLD confirms same numbers. Merged from two bullets into one because both are Recording Studio work.

### M2: Stream 2.0 in Excel

**Bullet:** "Built the Stream 2.0 video insertion and playback module for Excel Win32 (C++/JavaScript/TypeScript/SDX), integrating SharePoint/OneDrive video with multi-service playback for M365 enterprise users."

**Sources:** LI project "Stream 2.0 Office Integration" (Sep 2022 - Dec 2022, Excel + SharePoint + OneDrive + M365); LI Experience block confirms Tech Used: C++, JavaScript, TypeScript, SDX; RES-OLD has same claim.

### M3: Purchase Commerce EventHandler (**new, from LinkedIn only, not on old resume**)

**Bullet:** "Built a Purchase Commerce EventHandler microservice for OneDrive Consumer (C#, Docker, Azure EventHubs, SharePoint) that manages purchase and quota-entitlement events for downstream processing."

**Sources:** LI Experience block only ("Worked on Microservice Purchase Commerce EventHandler for OneDrive Consumer... Tech Used: C#, Docker, Azure EventHubs, SharePoint"). Added because it's the strongest distributed-systems evidence in the Microsoft stint.

### M4: OneDrive SKU filtering + telemetry

**Bullet:** "Delivered OneDrive Catalog SKU filtering and whitelisting to shield the upsell path from new SKU releases, preventing sev-2 incidents that historically took 2-3 weeks to fix in production; led automation for v1 of PowerPoint Explainer Videos and instrumented telemetry across Recording and Export events."

**Sources:** LI project "Catalog Filtering for Upgradable Plans in OneDrive" (Jan-Feb 2023); RES-OLD OneDrive SKU + Explainer Videos automation + telemetry -- merged three bullets into one for compactness.

---

## 7. Adobe bullets (both variants, compressed per user direction)

### A1: RIBS -> Hyperdrive migration

**Bullet:** "Migrated Photoshop Elements and Premiere Elements from RIBS to Hyperdrive: redesigned CI/CD pipelines with parallelized independent bundles; cut product install time by ~50% on average."

**Sources:** LI Experience "Migrated Elements from RIBS to Hyperdrive"; RES-OLD "Elements Product Installation time on system significantly reduced by 50% on average". Number preserved as ~50%.

### A2: AEM Docx lazy loading

**Bullet:** "Designed and implemented lazy loading for large files in AEM Docx Web Editor, cutting overall load time by ~60% for customer-reported freeze / slowness cases."

**Sources:** LI Experience + RES-OLD "60% reduction in overall loading time".

### A3: PSE/PRE licensing + tail (MathML + ColorPop merged)

**Bullet:** "Implemented PSE / PRE licensing deactivation on uninstall via payload code and LEID; also delivered MathML support in AEM Docx Web Editor (SVG rendering) and the ColorPop feature in Photoshop Elements 2020 (object masking + background auto-creation workflow)."

**Sources:**
- LI Experience "licensing deactivation of Photoshop Elements and Premiere Elements... payload code and LEID" -- **new addition**, not on RES-OLD; enables 10-year licensing narrative
- LI Experience "MathML support" + RES-OLD MathML bullet
- LI Experience "ColorPop feature in PSE 2020" + RES-OLD ColorPop bullet

**Dropped from old resume:** Filtering Library, checked-out delete + Lucene, snippets APIs, CSS templates, WAS PSE 2019 with CrashReporter, Updater workflow.

---

## 8. Personal Projects section -- FAANG variant only

### P1: Distributed systems primitives in Go

**Bullet:** "Distributed systems primitives in Go - Bitcask (append-only KV + WAL), LSM/SSTable, consistent hashing with virtual nodes, Bloom filters, Kafka-style offset tracking. Runnable prototypes in a personal study repo (currently private; publishing selectively)."

**Sources:** User statement 2026-07-05 "I have built them in Go using cursor, but have not published them yet. They are curently at local place for now, in my windows machine WSL ubuntu."

**Caveat:** The claim is that the code exists locally. It is not currently verifiable via public GitHub. Recommendation: push 2-3 clean prototypes within 2 weeks and then upgrade the resume line to name the public repo. See `resume-open-questions.md` for the follow-up.

**Dropped from public GitHub repo (apsy3677/Study):** old academic projects (NLP concept mapping, CUDA Boruvka's MST), Maven Message-Queue (skeleton only). None strong enough to feature.

---

## 9. Awards -- both variants

**Kept:** "Spot Award, Adobe -- recognized for delivery of the RIBS -> Hyperdrive migration in Photoshop Elements."

**Rationale:** This is the only award tied to a project on the current resume. Keeping it validates A1 above.

**Dropped:** "Ranked 1st in Knight Coders in TechnoSearch (2012), Ranked 3rd in Code Pokers TechnoSearch (2012), Max Rated 1974 on Codechef, Max Rated 1693 on Codeforces."

**Rationale:** Competitive programming ratings and college-era rankings are dropped at Staff+ globally. See segment benchmark in Phase 2.

---

## 10. Education

**Kept:** "B.Tech, Computer Science -- Maulana Azad National Institute of Technology (NIT Bhopal) | 2011 - 2015 | GPA 8.27/10"

**Dropped:** 10th CBSE (85.6%), 12th CBSE (78%) rows and their school details.

**Rationale:** Staff+ resumes never carry K-12 percentages outside of India-fresher formats. User approved Q7.

---

## 11. Sections dropped entirely

| Section | Rationale |
|---|---|
| Hobbies and Interests (Cricket, Football, Chess, Competitive programming) | Not carried at 11y+ |
| Objective statement | Not used; Summary/Positioning covers this |
| References available on request | Not a 2026 practice |

---

## 12. What's *not* on this resume but exists in your record

Deliberate exclusions -- available for later if a specific role calls for them:

| Item | Why excluded |
|---|---|
| Program slicer work (`docs/program-slicer-2026-07/`) | In-flight (Jul 2026), too early to cite as delivered |
| CPP COI briefing pack (`docs/cpp-output-coverage/cpp-coi-fspec-2026-06/`) | Strategic disposition doc, not shipped code |
| 27+ inline replies on peer's CL review (Ankit's CoDa CppCovDB) | Included implicitly in "50+ code reviews" |
| Nvidia formal-verification summit talk audience size | Number unknown; excluded per no-invention rule |
| Hector license-key deprecation (P10237313-45876) | Self-filed Jun 15 2026; audit + roadmap shared but no CL landed yet |
| Weekly-status .docx pipeline, sprint automation .docx generator | Rolled into Cursor engineering-platform bullet |
| Regression non-determinism sweep (Jun 18-26 2026) | Investigation-heavy; hard to reduce to one bullet at Staff+ |
| Individual named JIRAs / CL numbers | Not resume-appropriate; kept in the LinkedIn_Profile doc without IDs |
| One Percent Solution presentation pack (V11 speaker notes, cheat sheet, Q&A bank) | Covered by the "delivered internal Tech Corner talk" phrase |

---

## 13. Verification

- All quantitative claims have at least one source above.
- No fabricated metrics.
- No fabricated tech stack items (Go marked as "study repo").
- No fabricated customer relationships.
- No fabricated talks.

If any claim above is inaccurate, mark it and I will regenerate.


ResumeOpen-Questions.md
---
type: audit-followup
topic: resume-refresh-2026-07-05
status: open
date: 2026-07-05
do_not_ingest: true
---

# Open Questions / Verification Asks

Numbers I could not verify from any source doc. Per your directive
(2026-07-05: "if I don't have, do not frame them. Keep the originality of
what I had"), I did **not** fabricate any of the below in the resume. The
resume ships with qualitative language where a number would go. Fill any of
these in when convenient and I can regenerate the `.docx` file with the
number inserted.

Nothing here is blocking. The resume is shippable today as-is.

---

## Category A -- Numbers that would strengthen bullets if you have them

### A1. Adobe RIBS -> Hyperdrive install-time baseline

- **Resume says:** "cut product install time by ~50% on average"
- **What would strengthen:** Baseline in raw seconds, e.g. "cut install time from 45s to 22s" or "from 4m 30s to 2m 15s".
- **Where you might find it:** old Adobe Confluence RCAs; Elements installer telemetry.

### A2. Adobe Web Editor lazy loading baseline

- **Resume says:** "cutting overall load time by ~60% for customer-reported freeze / slowness cases"
- **What would strengthen:** File-size threshold that triggered the slowness + before/after load times, e.g. "for docs > 5 MB, first-open time dropped from 12s to 5s".
- **Where you might find it:** AEM Docx issue tracker; old customer support tickets.

### A3. Microsoft OneDrive SKU filtering

- **Resume says:** "preventing sev-2 incidents that historically took 2-3 weeks to fix in production"
- **What would strengthen:** Count of incidents avoided per quarter/year; or dollar value of upsell path protected.
- **Where you might find it:** OneDrive DRI dashboards; old bridge notes.

### A4. Microsoft Purchase Commerce EventHandler scale

- **Resume says:** "manages purchase and quota-entitlement events for downstream processing"
- **What would strengthen:** Event volume (events/sec, events/day) or number of downstream consumers.
- **Where you might find it:** OneDrive Consumer service Grafana / Azure metrics.

### A5. Microsoft Stream 2.0 in Excel adoption

- **Resume says:** "for M365 enterprise users"
- **What would strengthen:** Adoption metric (# tenants using the feature, # videos inserted per week).
- **Where you might find it:** Stream 2.0 telemetry dashboards.

### A6. Synopsys DPV C++ Coverage customer designs

- **Resume says:** "used by 8 named marquee customers"
- **What would strengthen:** Number of customer designs currently running save_covdb; or number of VDB files generated per month across the customer base.
- **Where you might find it:** Synopsys customer telemetry; DPV usage reports.

### A7. Nvidia internal formal-verification summit audience

- **Resume says:** "presented at Nvidia's internal formal-verification summit"
- **What would strengthen:** Approximate audience size (e.g. "~50 Nvidia formal engineers") and whether it was recorded.
- **Where you might find it:** Your calendar / email around the date of the summit.

### A8. One Percent Solution -- 3x incremental build speedup

- **Plan file says:** "~3x faster incremental builds for the most-touched files"
- **Not on resume yet** because I couldn't tie it to a specific baseline.
- **What would strengthen:** Which files? What baseline (e.g. "for BanffMgr.h, incremental rebuild dropped from 45 min to 15 min") -- would add a clear metric to the E-S2 bullet.
- **Where you might find it:** IWYU dependency reduction reports at `docs/1percent/IWYU/`.

### A9. Cursor engineering platform -- knowledge index freshness

- **Resume says:** "532-doc searchable knowledge index"
- **What would strengthen:** Confirm the current count as of the day you send the resume (was 532 in Jun 28 plan file; 430 in the May-Jul OKR doc; 360 at end of April). If you round to "500+" that's safe for now.
- **Where you might find it:** `python3 /global/vcf01/anuyadav/knowledge-system/scripts/auto_maintain.py status`.

### A10. Personal Go repo status

- **Resume says:** "Runnable prototypes in a personal study repo (currently private; publishing selectively)."
- **What would upgrade this to a stronger claim:** Push 2-3 clean prototypes to a public repo (recommended order: Bitcask, Bloom filter, consistent hashing). Then the bullet can name the repo URL and add "runnable, benchmarked" -- much stronger for FAANG.

---

## Category B -- Claims to double-check before you ship the resume

### B1. Customer roster completeness

Verify none of these are under NDA that prevents naming: Nvidia, Intel, AMD, Apple, ByteDance, Google, Tenstorrent, Untether AI. Standard practice at Synopsys is to name these publicly since they're referenced in Synopsys marketing / press releases -- but if HR or your manager has flagged any as internally-only-name, remove from resume.

### B2. R&D Sr II -> Staff promotion date

Resume states: "Staff Engineer (Feb 2024 - Present); R&D Engineer, Senior II (May 2023 - Jan 2024)". Confirmed via LinkedIn. Cross-check against your official Synopsys HR record if you want the exact promotion month.

### B3. Adobe title dates

Resume states: "SDE 2 (Jan 2017 - Apr 2021); Member of Technical Staff (Aug 2015 - Jan 2017)". Confirmed via LinkedIn. Cross-check if you want the exact promotion month.

### B4. "org-wide Tech Corner talk" attribution

Resume says: "delivered an internal Tech Corner talk on the pattern". Confirmed via `docs/1percent/presentation/2026-05-org-talk/` package. If the talk was under a different program name at Synopsys (e.g. "Formal Team Talk", "Common Team Talk"), adjust the label before shipping. "Tech Corner" is a common Synopsys-internal name -- please verify it's the correct program at your BU.

### B5. Release-streams count

Resume says "5 release streams". Portfolio lists TD, X-2025.06, W-2024.09, V-2023.12, U-2023.03 = 5. Confirmed.

### B6. Cameo denominator

Resume says "1.2M of the 4.2M sessions". Both figures come from LinkedIn project descriptions. Confirmed.

### B7. Cores lift numbers

Resume says "Base 1->4 and Elite 4->12". This is from the plan file. Confirm against your Apex Licensing implementation docs if you want to be precise about the "before" state.

---

## Category C -- Explicit non-inclusions (kept off resume by design)

To make it easy to reconsider later:

- **Program slicer** (`docs/program-slicer-2026-07/`) -- in flight, no delivery yet.
- **CPP COI FSpec briefing pack** (`docs/cpp-output-coverage/cpp-coi-fspec-2026-06/`) -- strategic disposition; not shipped code.
- **Hector license-key deprecation** (P10237313-45876) -- audit shared, no CL landed yet.
- **Weekly-status .docx pipeline / sprint automation** -- rolled into the "Cursor engineering platform" bullet.
- **Regression non-determinism sweep (Jun 18-26 2026)** -- investigation-heavy; hard to reduce to a single bullet.
- **Individual JIRA/CL IDs** -- deliberately kept off (matches the plan-file rules).

---

## Category D -- Action items for the next 2 weeks (to strengthen next iteration)

Ranked by ROI:

1. **Push Bitcask + Bloom filter + consistent hashing to public GitHub.** Then upgrade FAANG resume's Personal Projects bullet with a repo URL and "runnable, benchmarked" language. Biggest single lift.
2. **Grab the 3x build-speedup baseline from `docs/1percent/IWYU/`.** Adds a hard metric to your strongest architectural bullet.
3. **Confirm Nvidia summit audience count.** If it's > 30, add it; if smaller, leave off.
4. **LinkedIn cleanup:** trim the 100+ endorsed skills down to ~20; rewrite the About using `positioning-brief.md`. This is where recruiters land first.
5. **Update knowledge-index count on the day you send the resume** -- run `auto_maintain.py status` and use the current number (or "500+" if you prefer a round number).


