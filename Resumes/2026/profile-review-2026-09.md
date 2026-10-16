# Profile review: LinkedIn + Naukri (Sep 2026)

Review only. Nothing on either profile has been changed. You make the edits.

**Sources used:** LinkedIn "Save to PDF" export (`Profile.pdf`, 27 Sep 2026), Naukri page print
(`Naukri TopTier.pdf`, 27 Sep 2026), `cv.md` in job-scraper, `Build_resumes.md`, the two 2026 docx
resumes, and the recruiter-demand data from the 27 Sep LinkedIn draft.

**Rules I held to:** every number traces to `cv.md` or something you confirmed. Public profiles get the
redacted version (no customer names, internal metrics as percentages). Sample text follows `voice-dna.md`
(no em dashes, no AI filler words). The sample text is a starting point. Rewrite it in your own words.

---

## 0. The short version

Your raw material is strong. The profiles undersell it and, in two places, oversell it.

**Undersold:** the metrics that make you interesting (1.5M → 4.2M sessions, 2M-line codebase, ~75%
coupling cut, 2-3 h → 5-10 min triage) are on your resume but mostly missing from LinkedIn Experience
and entirely missing from Naukri. LinkedIn's top 3 skills are Concurrent Programming, IPC and TCL, and
Naukri's visible key skills don't include C++. Recruiter search runs on exactly these fields.

**Oversold / risky:**
1. The LinkedIn About claims a "companion repo … Runnable prototypes" of 9 systems. The code is on your
   office laptop and can't be shown. The first interviewer who asks "can I see it?" turns this from an
   asset into a credibility problem.
2. Titles and dates disagree across LinkedIn, Naukri and the resume (details in section 3). A
   background check compares these.

Fix those two first. Then do the keyword and metrics work.

---

## 1. Positioning

One sentence that everything else should support:

> C++ systems engineer who makes large codebases easier to change, with product-scale experience at
> Microsoft and Adobe, now going deeper into distributed systems and applied AI.

What recruiters are actually searching for (from your 294 LinkedIn alert jobs + 7 recruiter threads):
C++ (18 titles), AI (15), Cloud (14), Storage (7), Platform (6), Backend (5). Top companies in the alerts:
Microsoft, Google, NVIDIA, Qualcomm, Adobe, Cadence.

| Track | Lead with | Keywords to have somewhere on both profiles |
|---|---|---|
| C++ systems / platform (primary) | 2M-line decoupling, subsystem ownership, Office Win32 C++ | C++, C++17, Linux, multithreading, IPC, software architecture, performance, GDB |
| Backend / distributed (primary) | Microsoft services, system design training | distributed systems, microservices, system design, Azure, event-driven, Docker, REST |
| EDA (secondary) | coverage subsystem, licensing, customer escalations | formal verification, EDA, code coverage, TCL, RTL |
| Applied AI (open) | AI engineering setup at work, Applied AI Masterclass | LLM, RAG, AI agents, developer productivity |

LinkedIn should read as the first two tracks, with EDA and AI as proof of range. Don't make it an EDA
profile: that caps you at Cadence and Siemens.

---

## 2. LinkedIn, section by section

### 2.1 Headline

**Current:**
`Staff Engineer @ Synopsys - Formal Verification & High-Perf C++| Building EDA × AI | ex-Microsoft , ex-Adobe | Distributed Systems/ storage internals | Shipped desktop, web, cloud, and EDA-grade software`

| Works | Doesn't |
|---|---|
| Has Staff, Synopsys, ex-Microsoft, ex-Adobe, C++, Distributed Systems: the right search terms | 5 segments, ~200 chars. The eye gives up after the second pipe |
| "Building EDA × AI" is a real hook (you did build the AI tooling) | Spacing typos: `C++|`, `ex-Microsoft ,`, `Systems/ storage` |
| | "storage internals" rests on the office-laptop prototypes only. Remove it |
| | "EDA-grade software" means nothing to a non-EDA recruiter |

**Options (pick one):**

- **A (recommended):** `Staff Engineer at Synopsys | C++ systems and large-codebase architecture | ex-Microsoft, ex-Adobe | Distributed systems, applied AI`
- **B (search-heavy):** `Staff Engineer | C++ · Distributed Systems · Software Architecture · AI dev tooling | 11 yrs across Microsoft, Adobe, Synopsys`
- **C (EDA-leaning, only if you want Cadence/NVIDIA EDA calls):** `Staff Engineer, Synopsys VC Formal | High-performance C++ for formal verification | ex-Microsoft, ex-Adobe | Building AI tools for EDA engineers`

Why A: it keeps both FAANG-tier logos, puts C++ and architecture where a search hits them, and says
"distributed systems" as a direction rather than a claim.

### 2.2 About

**Current (as exported):** opens "Staff Engineer, 11 years across Adobe, Microsoft, and Synopsys. I have
shipped software at every layer of the stack…", names "(Nvidia, Intel, Apple etc)", runs into
"runs.C++, Java, Go, C# / TS / Python / ReactAlongside the day job…", and closes with the prototype list
"Bitcask, LSM, B+ trees, WAL, Redis, consistent hashing, Bloom filters, Kafka offsets, idempotent webhooks.
Runnable prototypes."

| Works | Doesn't |
|---|---|
| Opening line is clear and gets the 11 years + 3 names in early | Customer names on a public page (you chose to redact) |
| "Every layer of the stack" is a genuine differentiator | Prototype list is unverifiable and on an employer's machine (see 0 and 6) |
| The Cameo 1.2M / 4.2M number is here | Line breaks lost ("runs.C++", "ReactAlongside"). Check the live page; it may just be the PDF export |
| | Nothing about the thing you're best at: the 2M-line decoupling |
| | Nothing about the AI tooling you built, or the Applied AI course |
| | "Go" in the stack line only rests on the prototypes |

**Sample to adapt (~1,500 chars):**

```text
I've spent 11 years shipping software at Adobe, Microsoft and Synopsys, and I've ended up most useful in one spot: big, old codebases that need to change without breaking.

Right now I'm a Staff Engineer on VC Formal at Synopsys, a formal-verification tool used by major semiconductor companies. I own a C++ coverage subsystem end to end, from design to customer escalations, and it has shipped in every release since 2023.

I also drove an org-wide cleanup of a 2M+ line C++ codebase. Shared code had been tangled up with engine internals for about a decade. I designed a callback-based options layer (plain dependency inversion), kept chipping at it for 6+ months, cut the coupling by about 75%, and then gave an internal talk so others could carry it on.

Before that, Microsoft. I owned PowerPoint Recording Studio features (camera modes, background blur, Cameo) while monthly recording sessions grew from 1.5M to 4.2M. I also built video playback for Excel and worked on OneDrive commerce services on Azure EventHubs.

And before that, almost 6 years at Adobe on Photoshop Elements and AEM. I moved the Elements installers to a new CI/CD system, which cut install time roughly in half, and made the AEM web editor ~60% faster on large files.

Lately I've been building AI tooling for engineers. At work: custom agent skills plus a searchable index of 500+ internal docs, which took regression triage from 2-3 hours to 5-10 minutes. On my own: Arpit Bhayani's System Design and Applied AI masterclasses.

Mostly C++. Also Python, Java, C#, TypeScript. Based in Noida.
```

Deliberately left out: "open to" / "looking for" (your manager can read this; that signal goes through
Open to Work, recruiters only). Add Go back once a public repo exists.

### 2.3 Experience: Synopsys

**Current:** two positions (Staff, Feb 2024 - Present; R&D Engineer Senior II, May 2023 - Jan 2024).
Staff has 3 bullets: One Percent Solution, "NLDM-based propert density", "Modernized DPV licensing."
Sr II has 3 bullets on save/restore.

| Works | Doesn't |
|---|---|
| Shows the promotion. Keep this; it's the only place that does | Your strongest items are missing: subsystem ownership, the ~75% result, the 76% suite cut, the AI tooling |
| Split positions under one company group is the right format | Typo "propert density" |
| | "Modernized DPV licensing." with no detail reads like filler |
| | "at Synopsys Inc." inside a Synopsys bullet is redundant |
| | "One Percent Solution" is an internal name that means nothing outside |

**Sample, Staff Engineer (Feb 2024 - Present):**

```text
C++ systems work on VC Formal, Synopsys' formal-verification tool.

• Own the C++/RTL coverage subsystem end to end: design, releases, customer escalations. Shipped in every release since 2023.
• Led an org-wide decoupling of shared code from engine internals in a 2M+ line C++ codebase. Designed a callback-based options framework, kept a steady cadence for 6+ months, cut coupling by ~75%, and gave an internal talk on the pattern.
• Ran a three-phase licensing modernization for the DPV product line. Built a license-probe test harness and cut the licensing regression suite by 76% without losing coverage.
• Built Property & Assertion Density reporting across the engine, the TCL shell, a two-process XML IPC layer and HTML reports.
• Built an AI-assisted engineering setup on Cursor (9 custom agent skills, 500+ doc searchable index). Regression triage went from 2-3 hours to 5-10 minutes.
• Handle customer escalations from root cause to regression test to a fix shipped across release streams.
```

**Sample, R&D Engineer, Senior II (May 2023 - Jan 2024):**

```text
• Started the C++ coverage database work: writing coverage into Verdi's database and merging results across proofs, working with the Verdi team in Taiwan.
• Extended save/restore sessions so enterprise flows (case-split procs, SVA results, coverage proofs) survive a restore, using XML-based persistence.
```

Check the dates on the save_covdb work before you use that first bullet. It ran ~2.5 years, so it may
belong to the company-level description instead.

### 2.4 Experience: Microsoft (SWE II, May 2021 - May 2023)

**Current:** 4 items, each starting "Worked on…", with "Tech Used:" lines. Typos: "plackback",
"Powerpoint win 32", "Stream2.0". No outcomes. The 1.5M → 4.2M and Cameo numbers only appear in About.

| Works | Doesn't |
|---|---|
| Good spread: Win32 C++, TypeScript, C# microservice, Azure EventHubs | "Worked on" ×8 reads as participation, not ownership |
| Tech Used lines are search-friendly | Zero metrics, though you have two good ones |
| | "Zone Lockout Issues" means nothing outside the team |

**Sample:**

```text
• Owned PowerPoint Recording Studio features in the Win32 app: camera modes, background blur, the Cameo camera object, export. Monthly recording sessions went from 1.5M to 4.2M over that stretch, and Cameo was in ~1.2M of them.
• Built the video playback component for Stream 2.0 in Excel Win32 (C++, TypeScript), playing SharePoint, OneDrive and online video.
• Built catalog SKU filtering for OneDrive upgrade plans (C#) so new SKUs couldn't break the upsell path. That class of bug used to be a sev-2 that took 2-3 weeks to fix.
• Worked on the OneDrive Consumer purchase-events microservice (C#, Docker, Azure EventHubs).
• Led test automation for Explainer Videos v1 and added telemetry for Recording and Export.
```

### 2.5 Experience: Adobe (SDE 2 Jan 2017 - Apr 2021; MTS Aug 2015 - Jan 2017)

**Current:** 8 "Worked on" items. The ~60% load-time and ~50% install-time numbers are missing.
"AEM Dox" here vs "AEM Docx" on the resume.

| Works | Doesn't |
|---|---|
| Shows breadth: C++ desktop and Java/React web | Too long for work that's 5-11 years old. Recruiters skim this |
| Title progression is visible | Best two results have no numbers |
| | "Updater Workflow of Photoshop Elements 2019" sits under MTS (2015-2017), but PSE 2019 shipped in late 2018. Check which title it belongs under |
| | Product name inconsistent (Dox / Docx). Use Adobe's official name for the product |

**Sample, SDE 2:**

```text
• Designed lazy loading for large files in the AEM web editor; load time dropped ~60% on the files customers were complaining about.
• Added MathML (SVG) support to the web editor and built a content-filtering library and snippet APIs (Java, React, TypeScript).
• Built the ColorPop effect in Photoshop Elements 2020 (C++) and shipped Photoshop Elements 2019 on the Windows App Store.
```

**Sample, MTS:**

```text
• Moved Photoshop Elements and Premiere Elements from RIBS to Hyperdrive. Parallelized install bundles cut install time ~50%. Spot Award.
• Added licensing deactivation on uninstall.
```

### 2.6 Internship (Trivenifashions.com, Dec 2013 - Jan 2014)

Remove it. At 11 years it only adds noise. It's probably also where the stray "Greater Surat Area"
location on your public page comes from.

### 2.7 Skills

**Current top 3 (shown on the export):** Concurrent Programming, IPC, TCL.
The full list isn't in the PDF. The July notes say it had 100+ entries, including noise like
"options trading", "camera operation" and "app store optimization".

| Works | Doesn't |
|---|---|
| Nothing false in the top 3 | These are the 3 LinkedIn shows first and weights most, and nobody searches for them. C++ isn't there |

**Do this:**
- Pin as top 3: **C++**, **Software Architecture**, **Distributed Systems**.
- Keep roughly 30-40 skills you can defend, in this rough order: System Design, Microservices, Python,
  Java, C#, TypeScript, Multithreading, IPC, Linux, Design Patterns, Performance Engineering, Microsoft
  Azure, Docker, REST APIs, Event-Driven Architecture, CI/CD, Git, Perforce, GDB, TCL, Formal Verification,
  EDA, Code Coverage, Large Language Models (LLM), Retrieval-Augmented Generation (RAG), AI Agents, React.
- Delete anything you couldn't talk about for 5 minutes in an interview.
- Attach skills to each Experience entry (LinkedIn lets you tag up to 5 per role). That ties the skill to
  evidence.

### 2.8 Licenses, certifications, courses

**Current:** only "Machine Learning Foundations: A Case Study Approach" (Coursera, Nov 2018).

- Add **Applied AI Masterclass**, issuer as printed on the certificate, Sep 2026, with the credential URL
  if the certificate has one. Tag LLM, RAG, AI Agents.
- Add **System Design Masterclass (Arpit Bhayani)** under Courses (or Certifications if you have a certificate).
- Keep the Coursera one below them. It's old but harmless.
- Optional: put the Applied AI certificate in Featured.

### 2.9 Projects and Featured

**Current (from the public page, not in the export):** a "Distributed Message Queue" project linked to
GitHub, plus OneDrive / Stream 2.0 / Explainer Videos / Recording Studio projects.

- **Hide or delete "Distributed Message Queue"** until the repo is more than a skeleton. A hiring manager
  who clicks it sees weak code with your name on it.
- The Microsoft project entries are fine. They repeat Experience, but they hold the dates and numbers
  (they're the source for 1.5M → 4.2M and 1.2M). Keep them.
- Featured is empty as far as I can tell. The best candidates once they exist: the public `applied-ai`
  repo (if it's clean), the Applied AI certificate, and one post you've written (see 2.12).

### 2.10 Education

MANIT: add the field of study properly (the public page shows no degree) and optionally the 8.27 GPA.
KV Shivpuri is fine to keep or drop; it carries no weight either way.

### 2.11 Photo, banner, URL, Open to Work

- **Photo:** use the same recent, professional photo on LinkedIn and Naukri. The Naukri one looks old and
  casual.
- **Banner:** plain is fine. Don't use a text-heavy banner.
- **URL** `linkedin.com/in/yadavaps77`: keep it. It's on every resume you've sent.
- **Open to Work:** Recruiters only (never the green frame). Titles: Staff Software Engineer, Senior Staff
  Software Engineer, Principal Engineer, Software Architect, Lead Software Engineer. Locations: Noida,
  Gurugram, Delhi, Bengaluru, Hyderabad, remote India.

### 2.12 Recommendations and activity (not in the export, so I can't check them)

- Recommendations: get 2, one from a Microsoft or Adobe manager/peer and one from a Synopsys peer who has
  already left Synopsys. A line about "the person who untangled X" from someone who worked with you is worth more than any
  headline.
- Activity: 2-3 posts over the next 2 months beats 0. You have real material that doesn't leak
  anything: "what I learned building agent skills for a C++ team", "dependency inversion in a 2M-line
  codebase without a big-bang rewrite". Keep them generic. No product internals.

---

## 3. Consistency matrix

| Item | LinkedIn | Naukri | Resume (docx) / cv.md | Fix |
|---|---|---|---|---|
| Synopsys title/date | Sr II May 2023 → Staff Feb 2024 | Staff Engineer, May 2023 - Present | Staff Engineer, May 2023 - Present | Match your official HR record everywhere. If LinkedIn is right, fix Naukri and both resumes |
| Total experience | (derived) 11 yrs | **10 yrs** | 11 years | Naukri → 11 yrs 1 mo |
| Adobe product | "AEM Dox" | (not visible) | "AEM Docx" | Use the official product name everywhere |
| Adobe titles | MTS → SDE 2 (Jan 2017) | (not visible) | "SDE 2 / Member of Technical Staff" | Fine. Keep the order oldest-last on the resume |
| Dependency metric | not mentioned | not mentioned | 132 → 34 | Public: "~75%". Resume: your call per company |
| Triage time | not mentioned | not mentioned | 2-3 h → 5-10 min | Use this everywhere. `Build_resumes.md` still says 1-2 h → 2-3 min: update it |
| Go / prototypes | "Runnable prototypes" | not mentioned | "Runnable prototypes" (FAANG docx, cv.md) | Reword everywhere (section 6) |
| Customers | Nvidia, Intel, Apple named | not visible | 8 named | Remove from public profiles |
| Courses | none | none | cv.md only | Add to both profiles and the resume |

---

## 4. Naukri, section by section

Naukri recruiters mostly find you through Resdex keyword search, filtered by experience, location,
notice period and CTC, and sorted in part by how recently you updated your profile. So on this site
**key skills, headline and freshness matter more than prose.**

### 4.1 Profile highlights / resume headline

**Current:** Profile highlights is empty ("Add key highlights of your career…"). The header shows only
"Staff Engineer @ Synopsys, Noida".

This is the most-seen empty space on your profile. If your view also has a **Resume headline** field
(250 chars), fill that too.

Sample headline:
```text
Staff Engineer, 11 yrs | C++ systems, software architecture, distributed systems | Synopsys, ex-Microsoft, ex-Adobe | Azure microservices, AI dev tooling | NIT Bhopal
```

Sample highlights (short, one line each):
```text
• Own a C++ coverage subsystem in Synopsys VC Formal, shipped every release since 2023, used by major semiconductor companies
• Led an org-wide decoupling of a 2M+ line C++ codebase, cutting coupling by ~75%
• Microsoft: owned PowerPoint Recording Studio features while monthly sessions grew from 1.5M to 4.2M
• Built AI tooling for my team that took regression triage from 2-3 hours to 5-10 minutes
```

### 4.2 Profile summary

**Current:** "Versatile Software Engineer with 10 years of experience in software development, cloud
integration, and system design at Microsoft, Adobe, and Synopsys. Proven expertise in building scalable,
reliable systems and enhancing user experience through innovative solutions."

| Works | Doesn't |
|---|---|
| Three company names | Says 10 years |
| | "Versatile", "Proven expertise", "scalable", "innovative solutions": every Naukri profile says this, so readers skip it |
| | No product, no number, no C++ |

Sample (~750 chars):
```text
Staff Engineer at Synopsys with 11 years across Adobe, Microsoft and Synopsys.

At Synopsys I own a C++ coverage subsystem in VC Formal end to end and led an org-wide decoupling of a 2M+ line C++ codebase (coupling down ~75%). I also built AI tooling for my team: custom agent skills plus a 500+ doc knowledge index that cut regression triage from 2-3 hours to 5-10 minutes.

At Microsoft I owned PowerPoint Recording Studio features (monthly sessions 1.5M to 4.2M), built video playback for Excel, and worked on OneDrive commerce microservices on Azure. At Adobe I worked on Photoshop Elements and AEM, cutting install time ~50% and large-file load time ~60%.

C++, Python, Java, C#, TypeScript. Looking at Staff / Principal roles in C++ systems, backend and distributed systems.
```
(The "looking at" line is fine on Naukri: the profile already says Actively exploring. It isn't fine on LinkedIn.)

### 4.3 Key skills

**Current visible:** Backend Development, Distributed Systems, Microservices, Azure DevOps, +17 hidden.

| Works | Doesn't |
|---|---|
| Distributed Systems and Microservices are good search terms | **C++ isn't in the first 4**, and it's your strongest skill |
| | Azure DevOps: keep only if you really used ADO boards/pipelines at Microsoft |
| | The 17 hidden ones aren't in the export (see section 8) |

Suggested order (first ones matter most): **C++, Software Architecture, System Design, Distributed
Systems, Microservices**, Python, Java, C#, TypeScript, Multithreading, Linux, Design Patterns,
Performance Engineering, Azure, Docker, REST API, Event-Driven Architecture, Formal Verification, EDA,
TCL, CI/CD, Git, LLM, RAG, AI Agents.

### 4.4 Tech skills (the table with years)

**Current:** IntelliJ Idea 1 yr 6 mos, Visual Studio 8 yrs, XCode 3 yrs, **Objective C++ 0 yr**.

These are IDEs plus a language you list at zero years. It reads as stale and a bit careless. Replace it
with your real stack and **honest** years that you fill in yourself: C++, Python, Java, C#, TypeScript,
TCL, Linux, Git/Perforce, Docker, Azure. Don't round up. A recruiter who asks "8 years of C++?" will
check it against your roles.

### 4.5 Employment

**Current:** Synopsys, "Staff Engineer, May 2023 - Present", description "Working in DPV, a formal
verification tool that verifies the correct implementation of data path elements…" (truncated), tags
C++, Formal Verification, TCL, Linux, OOPS, Design Patterns, Regression. Microsoft and Adobe are behind "+2 more".

- Split Synopsys into R&D Engineer Sr II (May 2023 - Jan 2024) and Staff Engineer (Feb 2024 - Present), or
  whatever your HR record says, so it matches LinkedIn.
- The description opens by explaining what DPV is. Open with what *you* own instead, and reuse the
  LinkedIn bullets from 2.3 (Naukri's field is shorter, so take the top 3-4).
- Tags: swap "OOPS" and "Regression" for Software Architecture and Performance Engineering.
- Microsoft/Adobe: send me the full text and I'll review them (section 8).

### 4.6 Projects

**Current:** "Catalog Filtering for Upgradable Plans in OneDrive" (Feb 2023, 1 month) leads, with "+2 more"
behind it.

A 1-month project is your first impression. Reorder so the big ones lead:
1. C++ coverage subsystem, Synopsys (2023 - present)
2. Large-codebase decoupling, Synopsys (use the real start/end dates)
3. PowerPoint Recording Studio + Cameo, Microsoft (Jun 2021 - Apr 2022, per LinkedIn projects)
4. OneDrive catalog filtering (keep, but last)

### 4.7 Professional details and career preferences

| Field | Current | Suggestion |
|---|---|---|
| Total experience | 10 yrs | 11 yrs (1 mo) |
| Department, Role | Research & Development, R&D - Other | Move to the Engineering - Software department and pick the closest Staff / Principal / Architect-type role in Naukri's dropdown. "R&D - Other" is a filter most software recruiters never select |
| Industry | Software Product | Fine |
| Current salary | shown to recruiters | Your call. Just know that recruiters see it and anchor on it |
| Minimum expected salary | ₹0 | Reads as "not filled". Leave it blank or set it yourself, whichever you prefer. Your call |
| Roles wanted | Staff / Senior Staff / Principal | Add Software Architect / Technical Architect |
| Companies, Tech stacks, Level, Work mode, Industries | all empty ("+") | Fill Tech stacks (C++, Distributed Systems), Level (Staff / Principal), Industries (Software Product, Semiconductors, Internet). Naukri uses these for matching |
| Location | Bengaluru, Delhi/NCR, Hyderabad, Noida, +1 | Fine |
| Notice period | 2 months | Fine |

### 4.8 Resume file

**Current:** `Resume_AnujPratapSinghYadav_Staff_…`, uploaded 20/08/2025.

It's 13 months old, predates the 2026 refresh, and is probably the unredacted version. Any recruiter can
download it, including Synopsys and competitor recruiters. Replace it with the redacted Naukri variant
we'll build in the next phase.

### 4.9 Online profiles, certifications, education

- Online profiles: LinkedIn is there. Add GitHub once a public repo is worth clicking.
- Certifications: empty. Add Applied AI Masterclass and the System Design course.
- Education: shows "0 - 2015". Set the start year to 2011.

### 4.10 Privacy and hygiene

- You're "Actively exploring" on a public profile while employed. Use Naukri's privacy setting that
  blocks specific companies from viewing your profile, and add Synopsys.
- Freshness: Naukri is widely reported to rank recently-updated profiles higher. A small real edit every
  few days (reorder a skill, tweak a line) is enough. Don't churn it for the sake of it.
- Photo: same one as LinkedIn (2.11).

---

## 5. Confidentiality pass

| Item | Public profiles (LinkedIn, Naukri, Naukri resume) | Targeted resume |
|---|---|---|
| Customer names (8) | Remove. "major semiconductor companies" | Keep, except for Cadence/Siemens and roles at the customers themselves (redacted variant) |
| 132 → 34 dependency metric | "~75%" | Your call per company |
| Internal project names (One Percent Solution, CommonFormalOptions) | Drop | Fine on EDA resumes; drop for non-EDA (it means nothing to them) |
| "2M+ line codebase" | Fine (a size, not a result) | Fine |
| Product names (VC Formal, DPV) | Fine, they're public products | Fine |
| Why you're leaving | Never | Never |

---

## 6. The prototypes question

The code for the Go prototypes lives on your Synopsys laptop. Three consequences:

1. **Don't claim a repo you can't show.** Remove "companion repo … Runnable prototypes" from LinkedIn About,
   the FAANG resume and `cv.md`.
2. **IP risk.** Code written on a company laptop is often covered by the employment agreement, even if it's
   personal study. Don't copy it off, and don't describe it as your personal repo. (Not legal advice; check
   your agreement.)
3. **Honest wording that still gets credit:** in Courses/Training, e.g. "System Design Masterclass. Hands-on:
   implemented a key-value store, consistent hashing and Bloom filters in Go." List only the ones you
   actually built. In interviews you can talk through them; you just can't link them.

The real fix is below (gap #1).

---

## 7. Gaps you can close honestly (ranked by ROI)

| # | Gap | Why it matters | Effort |
|---|---|---|---|
| 1 | No public code | Distributed systems and AI claims have nothing to click. Rebuild 2-3 prototypes at home (Bitcask, consistent hashing, Bloom filter) and clean up `apsy3677/applied-ai` | 2-3 weekends |
| 2 | Zero recommendations (unverified) | Cheapest trust signal on LinkedIn | 2 messages |
| 3 | No posts | Recruiters check activity. 2-3 posts from real work | 1 hr each |
| 4 | Networking / data plane (2 recruiter threads, 5 alerts) | Recruiters already match you here. Only chase it if you want those roles; a small packet-processing prototype would make it real | Optional |
| 5 | Storage / Rust (7 alerts, 1 thread) | Covered by #1 if the KV store is public. Rust only if you want storage roles | Optional |
| 6 | Kubernetes | Shows up in backend/platform JDs. Deploy one course prototype on it; only claim what you ran | Optional |

---

## 8. What I still need to finish the review

The exports cut these off. Paste them into a text file, or expand everything and print again, and I'll fill in
those rows:

- **Naukri:** the 17 hidden key skills; full Synopsys description ("read more"); Microsoft and Adobe
  employment entries ("+2 more"); the other 2 projects; the other 2 education entries; the "+1 more" location;
  whether a Resume headline field exists in your view.
- **LinkedIn:** full Skills list (Skills → Show all), Projects, Featured, Recommendations (received and given),
  your current photo/banner, and Open to Work settings.

---

## 9. Priority checklist

**30 minutes (do first)**
- [ ] Decide the true Synopsys title dates; fix Naukri (and note it for the resumes)
- [ ] Naukri total experience → 11 yrs
- [ ] Remove "Runnable prototypes" / companion repo line from LinkedIn About
- [ ] Remove customer names from LinkedIn About
- [ ] LinkedIn: pin C++, Software Architecture, Distributed Systems as top skills
- [ ] Naukri: put C++ first in key skills; delete Objective C++ 0 yr / XCode / IntelliJ
- [ ] Naukri: block Synopsys in privacy settings
- [ ] Hide the "Distributed Message Queue" project on LinkedIn

**Half a day**
- [ ] New LinkedIn headline + About (sections 2.1, 2.2)
- [ ] Rewrite LinkedIn Experience for all three companies (2.3 to 2.5), fix typos, remove internship
- [ ] Naukri headline, highlights, summary, projects order, dept/role, career prefs (4.1 to 4.7)
- [ ] Add Applied AI + System Design courses to both
- [ ] Same professional photo on both
- [ ] Open to Work → recruiters only

**Next 2 weeks**
- [ ] Ask for 2 recommendations
- [ ] Write 1 LinkedIn post
- [ ] Start the public repo (gap #1)
- [ ] Replace the Naukri resume with the redacted 2026 variant (next phase)

---

## Next phase (after you sign off on this)

Resume variants from one corrected master: C++ Systems/Platform, Backend/Distributed, EDA (plus a redacted
copy for Cadence/Siemens and customer companies), and the Naukri general redacted version. Each ships with
a "changed vs source" list, ATS-safe formatting (single column, city in the header, plain-text URLs, `Mon YYYY`
dates) and a deliberately human, ~8-8.5/10 finish.

Quick read on the current resumes, so it's on record: ~8/10 for EDA readers, ~7.5 for non-EDA. The
Synopsys section is 7-8 dense, semicolon-chained bullets full of jargon (UAL, solveNB, HecProblem,
-out_dir, NLDM). That density is the thing that makes a resume look machine-assembled.
