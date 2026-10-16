# Profile review v2: LinkedIn + Naukri (Sep 2026)

This version replaces `profile-review-2026-09.md` (v1). It re-runs the review with the career-narrative rubric:
conversion before distribution, the four Staff signals, no invented numbers. Nothing on either profile has been changed.

**Calibration:** Staff Engineer, ~11 YOE, targeting Senior Staff / Principal / Architect. Primary archetype is
system-design-heavy roles at FAANG-tier / top-tier product companies. Secondary is EDA-adjacent.
Public profiles use the redacted version (no customer names, internal metrics as percentages), as you decided.

---

## 0. Input check

| # | Required input | Status | Source |
|---|---|---|---|
| 1 | LinkedIn headline, About, last 2-3 roles (verbatim) | **Have it** | `Profile.pdf` (LinkedIn export, 27 Sep) |
| 2 | Naukri resume headline, summary, key skills (verbatim) | **Partial.** Summary: yes. Key skills: 4 of 21 visible. Resume headline: not shown in the TopTier view | `Naukri TopTier.pdf` |
| 3 | Target level + archetype | **Have it** (default calibration matches your stated goals) | job-search notes |
| 4 | 3-5 real achievements with numbers | **Have it**, with gaps listed in section 5 | `cv.md`, `Build_resumes.md`, your answers |

Because input 2 is partial, the **Naukri headline and key-skills rewrites are directional.** They're marked
`[PLACEHOLDER]` until you paste the current headline and all 21 skills. Everything else is a real rewrite. Any
number that still needs confirming shows as `[confirm: …]` rather than being filled in.

I also read the 2025 resumes in `Resumes\` (`…Staff_Engineer2025.pdf`, `…Staff_Engineer_Snps_2025.pdf`). One of
them is almost certainly the file on Naukri (uploaded 20/08/2025, name starts `Resume_AnujPratapSinghYadav_Staff_`).
That matters a lot. See 1.8.

---

## 1. Diagnostics

### Positioning axis: does "deep systems ownership + engineering-productivity leverage" hold up?

I tested it against your evidence. **Half of it holds.**

- **Deep systems ownership: yes, strongly.** Two things are genuinely Staff-grade. First, a 2M+ line C++ decoupling with a
  before/after number, a pattern others adopted, and a talk. Second, a subsystem you own end to end *with external
  customers*. Most Staff candidates can't show either.
- **Engineering-productivity leverage: not yet.** Your own notes say the Cursor platform has one builder and
  one daily user (you), plus a team demo. Leverage means other people's work got faster. Right now the evidence
  is "my triage got faster". That's a good personal-tooling story, not a Staff leverage story. It becomes one the
  day you can say "N engineers use it" `[confirm: does anyone besides you use it?]`.

**Recommended axis:** *C++ systems architect who owns customer-facing subsystems and fixes large codebases without
rewrites.* The AI tooling is a supporting differentiator, not the headline, until adoption exists.

**The honest ceiling for FAANG system-design roles:** your production distributed-systems evidence is thin. It's a
Microsoft microservice you "worked on" plus training. No wording fixes that, and wording that tries to will
fail the first system-design follow-up. The profile should convert well for **C++ infra/platform** roles (Microsoft,
Google, Adobe, Nvidia, Qualcomm, AMD, Intel software) and should *not* pose as a distributed-backend profile. The
system-design interview is where you prove the distributed skill.

### Corrections to my own v1

v1 had three problems the rubric catches:

1. **Scope inflation in the AI tooling.** v1's sample said "AI tooling for my team" and "took regression triage from 2-3 hours to
   5-10 minutes" as if it were team-wide. Your evidence supports *your* triage only.
2. **Unqualified causation at Microsoft.** v1 said "while monthly recording sessions grew", which is better than the resumes'
   "driving… from 1.5M to 4.2M". But the underlying metric is itself ambiguous (see 1.6).
3. **Over-weighting skills and endorsements.** At Staff level they barely move search. v1 spent a section on them. That effort
   belongs on recommendations and Experience bullets.

### 1.1 LinkedIn headline

| Current (verbatim) | What's wrong | Why it fails at Staff | Evidence needed |
|---|---|---|---|
| `Staff Engineer @ Synopsys - Formal Verification & High-Perf C++\| Building EDA × AI \| ex-Microsoft , ex-Adobe \| Distributed Systems/ storage internals \| Shipped desktop, web, cloud, and EDA-grade software` (~200 chars) | 5 themes. The visible first ~65 chars are "Staff Engineer @ Synopsys - Formal Verification & High-Perf C++", which pitches you as an EDA specialist to every non-EDA recruiter. "storage internals" has no production evidence (only office-laptop prototypes). "EDA-grade" is jargon. Spacing typos | A Staff headline needs role + specialization + one differentiator in the first 65 chars. This one spends them on a domain that narrows your market, and one of its 5 claims wouldn't survive "tell me about your storage work" | None new. The differentiator (2M-line decoupling, customer-facing ownership) already exists; it just isn't here |

### 1.2 LinkedIn About

**Current (verbatim, as exported):**
> Staff Engineer, 11 years across Adobe, Microsoft, and Synopsys. I have shipped software at every layer of the stack — desktop binaries (Photoshop Elements), enterprise web (AEM Docx), cloud SaaS used by millions (OneDrive, Stream 2.0, PowerPoint Cameo: ~1.2M of 4.2M monthly recording sessions), and now high-performance C++ inside the formal-verification tools every major chipmaker (Nvidia, Intel, Apple etc) runs.C++, Java, Go, C# / TS / Python / ReactAlongside the day job, I create prototypes for personal study — I've been building a companion repo: Bitcask, LSM, B+ trees, WAL, Redis, consistent hashing, Bloom filters, Kafka offsets, idempotent webhooks. Runnable prototypes.

| Problem | Type | Interview risk |
|---|---|---|
| First ~250 chars (the only part most people read) = years + "every layer of the stack" + product list. No Staff signal, no judgment, no outcome of yours | Task list as pitch | Reader concludes "generalist senior". The best material is below the fold or missing |
| "companion repo … Runnable prototypes" of 9 systems | **Unverifiable claim** | High. The code is on your Synopsys laptop. "Can you share the repo?" has no good answer, and it can make every other claim look padded |
| "every major chipmaker" | Vague superlative | Medium. "Which ones? Qualcomm? Broadcom?" You have 8 accounts, which is strong enough on its own |
| Names Nvidia, Intel, Apple | Confidentiality | You decided to redact. It's also a target-employer overlap |
| "cloud SaaS used by millions" credited next to your name | Borrowed scale | Medium. The users belong to the product. What did *you* move? |
| Go in the stack line | Unsupported | Rests only on the prototypes |
| Nothing on decoupling, customer ownership, licensing, AI tooling | Underrepresentation | You're leaving your 3 strongest stories out |

### 1.3 LinkedIn: Synopsys (last role)

**Current (verbatim):**
Staff Engineer (Feb 2024 - Present):
- "Architected and led the multi-quarter "One Percent Solution" to decouple VC Formal's Common layer from Formal-only headers."
- "Designed the NLDM-based propert density for DPV, enhancing reporting capabilities."
- "Modernized DPV licensing."

R&D Engineer, Senior II (May 2023 - Jan 2024):
- "Designed and implemented save/restore flow extensions using XML-based persistence."
- "Enhanced preservation of UAL/case-split procedures and SVA cover/assume/assert post-solve."
- "Developed C++ coverage proof containers to improve save/restore functionality at Synopsys Inc."

| Bullet | Staff signals present (Scope / Judgment / Leverage / Number / External) | What's wrong | Evidence needed |
|---|---|---|---|
| One Percent Solution | Scope only | No number, no mechanism, no adoption. The internal name means nothing outside. "led" invites "how many people?" (Answer: you drove it, and 2 engineers adopted the pattern. Say that) | Have it: ~75% (132→34), 6+ months, 2 adopters, talk. Missing: build-time delta |
| NLDM density | none | Jargon + typo + "enhancing capabilities" (adjective, no outcome). Mid-level bullet | Adoption / which customers asked for it `[confirm]`. Otherwise merge or cut |
| "Modernized DPV licensing." | none | 3 words for a 2-year, 3-phase program with the best judgment story you have | Have it: 3 phases, fallback design, 38→9 tests, ~2-day triage vs weeks |
| save/restore ×3 | Scope (thin) | Domain jargon (UAL, SVA, solveNB). No outcome. "at Synopsys Inc." inside a Synopsys entry | Outcome: what customer flow did it unblock `[confirm]` |
| *(missing)* coverage subsystem ownership | would be Scope + External | Your clearest Staff signal isn't on the profile at all | Have it: every release since V-2023.12, 8 accounts, escalations, customer summit talk |
| *(missing)* AI tooling | would be Number (personal) | Absent | Adoption `[confirm]` |

**Verdict:** the current Synopsys entry reads mid-level. 6 bullets, 0 numbers, 0 external signals, 0 judgment.

### 1.4 LinkedIn: Microsoft (second-last role)

**Current (verbatim, condensed):** four "Worked on…" items. Catalog Filtering ("Tech Used: C#, Ramping Framework"), Purchase
Commerce EventHandler ("manages the events for purchase and other quota Entitlements and pass them on to SPO client"),
Stream 2.0 in Excel ("Created standalone component to support plackback of Online Videos"), Recording Studio ("Worked
on Camera Feature and Blurring background of user. Worked on Zone Lockout Issues as well for the team.").

| Problem | Staff signal gap | Evidence needed |
|---|---|---|
| "Worked on" ×8: participation, not ownership | Scope | You *owned* Recording Studio features (your own resumes say so). State it |
| No numbers here; 1.5M→4.2M lives only in About/Projects | Number | Metric definition `[confirm: MAU or monthly sessions?]` and your share of it |
| SKU filtering: the *why* (sev-2s, 2-3 week fixes) is missing | Judgment | Have it: sev-2s on the upsell path took 2-3 weeks to fix. Missing: incidents after `[confirm]` |
| EventHandler: accurate that you "worked on" it | none (fine) | Keep as a supporting line. Don't upgrade it to "built" |
| Typos: plackback, Powerpoint win 32, Stream2.0 | n/a | none |

### 1.5 LinkedIn: Adobe and internship (older)

Adobe has 8 "Worked on" items across 5.7 years. Per the rubric, older roles get compressed, not rewritten line by line.
Keep the two numbers (~50% install time, ~60% load time) and the Spot Award. Remove the 2013 internship. Check:
"Updater Workflow of Photoshop Elements 2019" sits under the MTS title (2015-17), but PSE 2019 shipped in late 2018.

### 1.6 Metric integrity (cross-source)

Where the same claim appears in different sources with different numbers or wording:

| Claim | Sources disagree how | Risk | Action |
|---|---|---|---|
| Recording Studio growth | 2025 resume: "recording sessions **MAU** from 1.5M to 4.2M"; 2026 resume: "**monthly recording sessions**"; Cameo: "MAU is 1.2M out of 4.2M recording **sessions** started" | Users and sessions are different metrics. An ex-Microsoft interviewer will ask | `[confirm: which metric]`. Say "during the release window", not "drove" |
| Save/restore "reduced verification setup time by **40%**" | Appears in both 2025 resumes only. Not in `cv.md`, the portfolio, OKRs, or the 2026 resumes | **No source I can find.** If it can't be sourced, it's a fabricated number, and it's on the resume Naukri recruiters are downloading | Remove it unless you have a source |
| Dependency metric | 132→34 (confirmed) vs 110→43 (July notes) | Low, now settled | Update `Build_resumes.md` |
| AI triage time | 2-3h→5-10min (confirmed) vs 1-2h→2-3min (July notes) | Low, now settled | Same |
| "Header deps 61 → under 10", "2000+ files rebuilt per Common change" | July notes only, and those notes had stale numbers elsewhere | Medium | `[confirm]` before using either |
| Synopsys title | LinkedIn: Sr II May 2023 → Staff Feb 2024. Naukri + all resumes: Staff from May 2023 | **High.** Background checks compare titles and dates | Use your HR record everywhere |
| Adobe title | LinkedIn: MTS → SDE 2 (Jan 2017). 2025 resume: "SDE 2, 08/2015-04/2021". Snps resume: "Member Of Technical Staff 2" | Medium | Match LinkedIn (or HR) |

### 1.7 Naukri: headline, summary, key skills, filters

| Section | Current (verbatim) | What's wrong | Why it fails at Staff | Evidence needed |
|---|---|---|---|---|
| Resume headline | Not visible in the TopTier view. Header shows only "Staff Engineer @ Synopsys, Noida". "Profile highlights" is empty | The most-searched text field is empty or unknown | Recruiters search this field directly. Empty means you only surface on key skills | Paste the current headline if your view has one |
| Profile summary | "Versatile Software Engineer with 10 years of experience in software development, cloud integration, and system design at Microsoft, Adobe, and Synopsys. Proven expertise in building scalable, reliable systems and enhancing user experience through innovative solutions." | "Versatile", "Proven expertise", "scalable", "innovative solutions" are template tells. Says 10 years. No number. Title is "Software Engineer" | The rubric requires one number you can defend live. This has zero, and it reads as mid-level | Have it |
| Key skills | "Backend Development, Distributed Systems, Microservices, Azure DevOps" + 17 hidden | C++ isn't in the visible 4. "Backend Development" is a category, not a term recruiters type. Azure DevOps has no evidence in `cv.md` | Search weight goes to terms you'd struggle to defend, not your strongest | The 17 hidden skills |
| Tech skills (years) | IntelliJ 1y6m, Visual Studio 8y, XCode 3y, Objective C++ 0 yr | IDEs + a 0-year language | Reads stale and careless | Honest years per language, filled by you |
| Hard filters | Experience **10 yrs**; notice 2 months; min expected CTC **₹0**; resume from Aug 2025 | 10 yrs understates you (11y1m). ₹0 may read as unset. Last-active date unknown | These filter you out before any text is read | Your call on CTC. I won't ask for figures |
| Dept / role | "Research & Development, R&D - Other" | Software recruiters rarely filter on this | Discoverability | None |

### 1.8 Naukri resume file (the biggest hidden risk)

Both 2025 resumes, one of which is likely the Naukri upload, contain:

- **Customer names *plus what each one designs*:** "Nvidia (GPU architectures), Intel (CPU designs), Apple (custom silicon), and
  ByteDance (ML accelerators)". That's more exposure than a name list. Any recruiter can download it, including those at
  Synopsys competitors.
- **The unsourced 40% claim** (1.6).
- "Staff Engineer 05/2023" (title/date conflict), "Proven track record", "seamless" ×2, "Curser" typo, Objective C/C++, jQuery.

This file does more damage than anything on the profile page. Take it down or replace it before you edit anything else on Naukri.

Naukri reportedly blocks your current employer from seeing your profile by default (their FAQ says so, according to search
results; the page itself returned 403 to me, so I couldn't read it). Check **Settings → Blocked Companies** anyway and add Synopsys by name.
It won't stop a recruiter at another firm from downloading the file.

---

## 2. Rewrites

Rules applied: every number traces to `cv.md` or your confirmation; `[confirm: …]` marks what's still open; no em dashes; no
template words; "I" voice on LinkedIn; bullets vary in length.

### 2.1 LinkedIn headline (220 max; ~65 visible in search and on mobile)

| # | Text | Chars | First ~65 (what search shows) |
|---|---|---|---|
| **A (recommended)** | `Staff Engineer, C++ systems & large-codebase architecture \| Synopsys, ex-Microsoft, ex-Adobe \| Owns a customer-facing verification subsystem \| System design, applied AI` | 168 | "Staff Engineer, C++ systems & large-codebase architecture \| Synop…" |
| B (number-led) | `Staff Engineer (C++ systems) at Synopsys \| Cut coupling ~75% in a 2M-line C++ codebase, no rewrite \| ex-Microsoft (PowerPoint, OneDrive), ex-Adobe \| System design, applied AI` | 174 | "Staff Engineer (C++ systems) at Synopsys \| Cut coupling ~75% in a…" |
| C (EDA track only) | `Staff Engineer, Synopsys VC Formal \| C++ coverage & licensing subsystems for chip-design customers \| ex-Microsoft, ex-Adobe \| AI tooling for engineers` | 150 | "Staff Engineer, Synopsys VC Formal \| C++ coverage & licensing sub…" |

Why A: the visible part says role + specialization in words a Google, Microsoft or Nvidia recruiter types. "Customer-facing" is
the Staff differentiator most profiles can't claim. B is stronger if you're comfortable with a number in the headline.
The ~75% is already redacted, so it's safe. C is for an EDA-only push; it narrows you everywhere else.

### 2.2 LinkedIn About (2,600 max; ~250 visible before "See more")

```text
I work on large C++ systems that need to change without breaking. At Synopsys I own a subsystem that chip-design customers depend on, and I cut coupling by about 75% in a 2M+ line codebase without a rewrite. Before that: Office at Microsoft, Photoshop Elements and AEM at Adobe.

The ownership part: I own the C++/RTL coverage subsystem in VC Formal end to end. That means the design, every release since 2023, and the escalations when one of our 8 semiconductor customer accounts hits a problem. The pattern is always the same: find the root cause, write the regression test, ship the fix across every active release stream. I've also presented the work at a customer's internal verification summit.

The decoupling: shared code had been tangled with engine internals for about a decade, and earlier attempts to modularize had stalled without an agreed pattern. Instead of a big-bang split, I introduced a small callback-based options layer (plain dependency inversion) so shared code could stop including engine headers, then shipped 2-3 changes a sprint for 6+ months. Coupling went down ~75%. I gave an internal talk, and two engineers now use the pattern on their own.

I also took the product line's licensing through three models in two years: token, per-app cores, then a tiered scheme that falls back to older licenses so existing customers kept working. Along the way I cut its regression suite by 76% without losing coverage.

At Microsoft I owned PowerPoint Recording Studio features (camera modes, background blur, Cameo, export) during a stretch when monthly recording [confirm: users or sessions] went from 1.5M to 4.2M. I also worked on OneDrive's purchase-events service on Azure Event Hubs. At Adobe I cut Photoshop Elements install time ~50% and AEM web-editor load time ~60% on large files.

Lately I've been building AI tooling for my own engineering work: 9 Cursor agent skills and a searchable index of 500+ internal docs. My regression triage went from 2-3 hours to 5-10 minutes. [confirm: if teammates use it, say how many.] I finished Arpit Bhayani's System Design and Applied AI masterclasses.

Mostly C++. Also Python, C#, Java, TypeScript. Noida.
```

Length: ~2,175 chars. The first ~250 carry role, specialization, one external signal and one number. Everything after is
depth for someone who clicked. Not included on purpose: customer names, Go, "open to" language.

### 2.3 LinkedIn Experience: Synopsys (rewritten)

Each bullet is tagged with the Staff signals it carries. Group entry: *Synopsys Inc · Noida · 3 yrs 5 mos*.

**Staff Engineer · Feb 2024 - Present**

```text
• Own the C++/RTL coverage subsystem of VC Formal end to end: design, every release since 2023, and escalations from 8 semiconductor customer accounts, from root cause to a regression test to a fix shipped across active release streams. Presented it at a customer's internal formal-verification summit.
• Drove the decoupling of shared code from engine internals in a 2M+ line C++ codebase. Chose an incremental path over a big-bang module split: a callback-based options layer (dependency inversion) plus header cleanup, 2-3 changes per sprint for 6+ months. Coupling down ~75% [confirm: build-time effect]. Gave an internal talk; two engineers now run their own decoupling changes with the pattern.
• Took DPV licensing through three models in two years (token, per-app cores, tiered licensing with fallback so existing customers weren't locked out). Built a 7-checkpoint license-probe harness that turned probe-regression triage from weeks into about 2 days, and cut the licensing regression suite from 38 tests to 9 without losing coverage.
• Built Property & Assertion Density reporting across the engine, the TCL shell, a two-process XML IPC layer and HTML reports. [confirm: which customer need or adoption, or merge this into bullet 1]
• Built AI tooling for my own workflow on Cursor (9 agent skills, 500+ doc searchable index). My regression triage went from 2-3 hours to 5-10 minutes; demoed to the team. [confirm: adoption]
```

Signals: bullet 1 = Scope + External. Bullet 2 = Judgment + Number + Leverage. Bullet 3 = Judgment + Number + External (the customers
behind the fallback). Bullet 4 = Scope only, which is why it's flagged as merge or cut. Bullet 5 = Number (personal), and Leverage once adoption is confirmed.

"38 tests to 9" is a test count, not a business metric, so I think it's fine publicly. If you'd rather not, use "by 76%".

**R&D Engineer, Senior II · May 2023 - Jan 2024**

```text
• Built the C++ coverage database writer (save_covdb) from scratch: writing coverage into Verdi's database and merging results across proofs. Agreed the database hierarchy with the Verdi team in Taiwan, who own the viewer side. This became the base of the subsystem I own now.
• Extended save/restore so enterprise flows (case-split procs, SVA results, coverage proofs) survive a restored session, using XML-based persistence. [confirm: which customer flow it unblocked]
```

Check: save_covdb ran ~2.5 years, so it spans both titles. Putting it here shows where it started. Move it if HR dates say otherwise.

### 2.4 LinkedIn Experience: Microsoft (rewritten)

**Software Engineer II · May 2021 - May 2023 · Noida**

```text
• Owned Recording Studio features in PowerPoint Win32 (C++): camera modes, live background blur, video export, and Cameo, a camera object you can reshape and place on the slide. Monthly recording [confirm: users or sessions] went from 1.5M to 4.2M over those releases, and Cameo was used in ~1.2M. Also led test automation for v1 and wired telemetry for Recording and Export.
• New commerce SKUs kept breaking OneDrive's upgrade path, as sev-2s that took 2-3 weeks to fix in production. I designed catalog filtering plus an allowlist (C#) so unsupported SKUs never reached the upgrade API. [confirm: incidents after]
• Built the standalone video playback component for Stream 2.0 in Excel Win32 (C++, TypeScript), for SharePoint, OneDrive and online video.
• Worked on OneDrive Consumer's purchase-events microservice (C#, Docker, Azure Event Hubs), which routes purchase and quota-entitlement events to SharePoint.
```

Signals: bullet 1 = Scope + Number (with the attribution caveat). Bullet 2 = Judgment (problem → mechanism). Bullets 3-4 are honest
supporting lines. Bullet 4 stays "worked on" because that's what your notes say.

### 2.5 Adobe (compressed)

**SDE 2 · Jan 2017 - Apr 2021** and **Member of Technical Staff · Aug 2015 - Jan 2017** (keep both titles)

```text
• Moved Photoshop Elements and Premiere Elements from RIBS to Hyperdrive; parallelized install bundles cut install time ~50%. Spot Award.
• Designed lazy loading for large files in the AEM web editor; load time down ~60% on the files customers had reported as freezing.
• Also: MathML (SVG) support in the web editor, ColorPop in Photoshop Elements 2020, licensing deactivation on uninstall. (C++, Java, React, TypeScript)
```

### 2.6 LinkedIn: the other sections (ranked by what they're worth at Staff)

1. **Recommendations: highest value.** Ask for 2: a Microsoft manager or senior peer (Recording Studio) and someone who saw the decoupling
   work. Suggest a focus ("the SKU filtering design", "how the decoupling got adopted") so they write specifics, not adjectives.
2. **Certifications:** add Applied AI Masterclass (Sep 2026) and System Design Masterclass. Keep the 2018 Coursera one below them.
3. **Projects:** hide "Distributed Message Queue" (a skeleton repo). Keep the Microsoft project entries.
4. **Featured:** nothing until something public exists (see gap G1).
5. **Skills:** 5 minutes. Pin C++, Software Architecture, System Design, and delete anything you couldn't defend. Don't spend more
   than that.
6. **Open to Work:** recruiters only.
7. **Remove** the 2013 internship.

### 2.7 Naukri resume headline (250 max; ~120 show in search) `[PLACEHOLDER until current headline is pasted]`

| # | Text | Chars |
|---|---|---|
| **N1 (recommended)** | `Staff Software Engineer, 11 yrs \| C++ systems, system design, distributed systems \| C#, Azure, Docker, Python \| Synopsys, Microsoft, Adobe \| NIT Bhopal` | 151 |
| N2 (denser) | `Staff Engineer, 11 yrs \| C++, Linux, software architecture, large-codebase refactoring \| Microservices: C#, Azure Event Hubs, Docker \| Python, TCL \| EDA, formal verification \| Synopsys, ex-Microsoft, ex-Adobe` | 208 |

N1 fits entirely in the ~120-char search view up to the company names. N2 catches more EDA searches but pushes the company names
out of the visible part. Neither has an adjective. "Distributed systems" in N1 is defensible as training plus Microsoft services,
but only just. Keep it only if you're ready for a distributed-systems screening call.

### 2.8 Naukri profile summary (3-5 lines, one defensible number)

```text
Staff Engineer at Synopsys, 11 years across Synopsys, Microsoft and Adobe. I own a C++ coverage subsystem in VC Formal end to end, including customer escalations, and cut coupling ~75% in a 2M+ line C++ codebase without a rewrite. At Microsoft I owned PowerPoint Recording Studio features and worked on OneDrive commerce services on Azure. Looking at Staff / Principal roles in C++ systems and platform engineering.
```

Defensible live: ~75% (you can explain the metric and the mechanism). The "Looking at" line is fine on Naukri, since you're already marked
"Actively exploring".

### 2.9 Naukri key skills `[PLACEHOLDER until the 17 hidden skills are pasted]`

Exact terms recruiters type, strongest first:

`C++` · `C++17` · `Linux` · `Multithreading` · `Software Architecture` · `System Design` · `Distributed Systems` · `Microservices` ·
`Python` · `C#` · `Java` · `TypeScript` · `Azure` · `Azure Event Hubs` · `Docker` · `REST API` · `GDB` · `Git` · `Perforce` · `CI/CD` ·
`TCL` · `Formal Verification` · `EDA` · `LLM` · `RAG`

Remove: `Backend Development` (a category, not a search term), `Azure DevOps` (keep only if you really used ADO pipelines at Microsoft),
`OOPS`, `Regression`. Tech-skills table: C++, Python, C#, Java, TypeScript, TCL with **honest** years you fill in. Delete the IDEs and Objective C++.

### 2.10 Naukri filters and hygiene

- Experience → 11 yrs 1 mo. Split Synopsys into Sr II + Staff to match LinkedIn/HR.
- Dept/role → Engineering - Software department, closest Staff/Principal/Architect role in the dropdown.
- Min expected CTC ₹0 → your call. Just know it may be read as "not set".
- Replace the resume file (1.8). Until the new variant exists, deleting the old one beats leaving it up.
- Fill Profile highlights with 3 one-liners from 2.3 (bullets 1-3, shortened).
- A small real update every 3-5 days while you're actively looking. Recruiters sort by last-active.

---

## 3. Rubric scores (1-5)

| Dimension | LinkedIn now | LinkedIn after rewrite | Naukri now | Naukri after rewrite |
|---|---|---|---|---|
| Impact clarity | 2 | 4 | 1 | 3 |
| Technical specificity | 3 | 4 | 1 | 4 |
| Scope / seniority signal | 2 | 4 | 1 | 3 |
| Search discoverability | 3 | 4 | 2 | 4 |
| Narrative coherence | 2 | 4 | 2 | 3 |
| Evidence / proof density | 1 | 3 | 1 | 3 |

"After" assumes the `[confirm]` items are resolved honestly (including "no number exists" answers). Roughly 4/5 lines up with your
8-8.5/10 target. None of them should reach 5.

**The actual bottlenecks:**
- **LinkedIn: scope/seniority signal in Experience.** Your Staff role currently reads as 3 tasks. The rewrite fixes this with
  material you already have. Evidence density stays at 3 until gaps G1-G3 close. That's the next ceiling, and wording can't lift it.
- **Naukri: discoverability and hard filters,** plus the resume file. Nobody reads the summary if the 10-year filter,
  the empty headline and a 13-month-old file keep you out of results, and the file itself is the biggest risk (1.8).

---

## 4. What to do, in order

1. **Naukri resume file**: take it down or replace it (customer detail + unsourced 40%).
2. **Title/date consistency**: HR record → LinkedIn, Naukri, resumes.
3. **LinkedIn About**: remove the prototypes line and customer names today, even before the full rewrite.
4. **LinkedIn Synopsys + Microsoft entries** (2.3, 2.4). This fixes the LinkedIn bottleneck.
5. **LinkedIn headline + About** (2.1, 2.2).
6. **Naukri headline, summary, key skills, filters** (2.7-2.10), after you paste the hidden parts.
7. **Recommendations**: send the 2 asks.
8. Adobe compression, certifications, internship removal, Projects cleanup.

---

## 5. Open gaps (claims that still need a number or a defensible example)

| # | Claim | What's missing | Interview risk if left vague | How to get it |
|---|---|---|---|---|
| G1 | AI tooling as leverage | Anyone besides you using it? How many? | High, if framed as team impact | Count users, or keep it framed as personal |
| G2 | Decoupling impact | Build-time before/after (FAANG readers care about dev velocity, not an internal metric) | Medium: "what did ~75% buy the team?" | IWYU/build reports in `docs/1percent/IWYU/` |
| G3 | Public proof of systems/distributed work | Nothing public to click | Medium-high for FAANG | Rebuild 2-3 prototypes at home and publish them; clean up `apsy3677/applied-ai` |
| G4 | Recording Studio metric | Users vs sessions; your share of the growth | Medium, especially at Microsoft | Old Microsoft notes, the LinkedIn project entry |
| G5 | Coverage subsystem adoption | Designs / runs / customers actively using save_covdb | Low (ownership alone is strong) | Usage reports, if accessible |
| G6 | SKU filtering outcome | Incidents after vs before | Low | Memory / old notes. "No number" is an acceptable answer |
| G7 | Density reporting | Who needed it, what it enabled | Low, but it's a filler bullet without it | Merge into the coverage bullet if there's no answer |
| G8 | Save/restore | Which customer flow was unblocked | Low | Same |
| G9 | "40% setup time" (2025 resumes) | Any source at all | **High**: it looks invented | Remove unless you can source it |
| G10 | "2000+ files" / "61 → <10 headers" | Re-confirmation (from notes that were stale elsewhere) | Medium | Same IWYU reports as G2 |
| G11 | Go prototypes | Public code | High, if claimed | Don't claim them until G3 is done. Mention them in interviews as study work |

---

## 6. What I still need from you

1. Naukri: the current resume headline (if your view has one) and all 21 key skills, verbatim.
2. Answers to the `[confirm]` items. "There's no number" is a valid answer, and the bullet gets reworded around it.
3. Your HR record for the Synopsys and Adobe title dates.

Sources on Naukri mechanics: [Naukri FAQ on blocking your current employer](https://www.naukri.com/faq/job-seeker-search-i-do-not-want-my-current-employer-to-have-access-to-my-profile.-how-can-i-block-a-recruiter)
(403 when fetched; summarized from search results), [HR Cabin: blocking companies on Naukri](https://www.hrcabin.com/how-to-block-particular-companies-in-naukri-portal/),
[GoodSpace: Naukri visibility guide 2026](https://goodspace.ai/blogs/855452/how-to-make-your-naukri-profile-visible-to-recruiters-and-actually-get-calls-2026-guide),
[GoodSpace: Naukri headline examples](https://goodspace.ai/blogs/630401/naukri-profile-headline-50-examples-for-freshers-experienced-2026).
LinkedIn limits (220 / 2,600, truncation points) are from the rubric you supplied.
