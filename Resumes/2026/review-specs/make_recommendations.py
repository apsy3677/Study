import sys
sys.path.insert(0, "/home/apsy/.claude/skills/resume-docx/scripts")
from docxkit import new_document, h, p, bullet, numbered, table, callout, MUTED  # noqa: E402

OUT = sys.argv[1]
doc = new_document(page="A4")

h(doc, "Resume review against the Staff / Principal bar", 0)
p(doc, "Anuj Pratap Singh Yadav  ·  27 Sep 2026  ·  v2, updated with your answers  ·  reviewed: "
       "resume-faang-atlassian-2page.docx and resume-eda-2page.docx", size=9.5, color=MUTED, after=2)
p(doc, "Sources: memory notes, Build_resumes.md (July evidence audit), profile-review-2026-09-v2.md, career-ops cv.md, "
       "your answers of 27 Sep, and both files exported through your own Word 2010. Companion files: "
       "**resume_reviewed_faang.docx** and **resume_reviewed_eda.docx** (bullet-by-bullet comments plus tracked rewrites; "
       "no [confirm] placeholders left).", size=9.5, color=MUTED)

callout(doc,
        "**Bottom line.** The original resumes don't clear the Staff bar at a FAANG-tier company. Your answers changed the "
        "picture more than any rewording could. A shared layer serving 10-12 apps, a pattern another team (Low Power) "
        "adopted as a documented standard, work across the Common and CDC teams, design docs through architect and "
        "Distinguished Engineer review, interview panels, mentoring, and team adoption of your AI tooling are all Staff "
        "signals, and none were on the page.\n"
        "With the redlines accepted: **at the bar** for Cadence/Siemens Staff-Principal SWE and chip-company tools teams, "
        "**strong** for FAANG Senior, and **competitive for FAANG Staff resume screens** (about 7/10), where the interview "
        "loop decides. Principal is still out of range this cycle.")

# ---------------------------------------------------------------- 1
h(doc, "1. Verdict by track", 1)
table(doc, ["Track and level", "Verdict (after rewrite)", "Now", "After*", "What still limits it"], [
    ["**EDA:** Cadence / Siemens Staff, Lead, Principal SWE", "At bar", "6.0", "8.5",
     "Position for tool infrastructure, not formal-engine roles. Keep customer names off this version"],
    ["**Chip companies' CAD / tools / methodology teams** (Nvidia, AMD, Intel, Qualcomm)", "At bar", "6.0", "8.5",
     "Use a copy of the EDA version with customer names restored once: their formal teams are your customers"],
    ["**FAANG-tier Senior** (Google L5, Microsoft 63-64, Meta E5)", "Strong", "6.5", "8.5",
     "Nothing structural. Interview prep decides it"],
    ["**FAANG-tier Staff** (Google L6, Microsoft 65, Meta E6)", "Competitive for screens", "4.5", "7.0",
     "No measured org-level outcome (build time not benchmarked); you own a subsystem rather than lead engineers on it; no production distributed-systems depth"],
    ["**Principal / Senior Staff** (Google L7, Microsoft 66+, Meta E7)", "Out of range", "3.0", "4.5",
     "Needs multi-org technical direction as your primary job, not a project. Don't aim here this cycle"],
    ["**Cloud / backend Staff** (Atlassian, Salesforce, Amazon)", "Below bar, wrong shape", "4.0", "5.0",
     "Production distributed-systems evidence is one C# service you 'contributed to'"],
], [1.75, 0.95, 0.45, 0.55, 3.17])
p(doc, "*Now = the original files. After = redlines accepted. Scores are out of 10 against that track's bar, not a general "
       "quality score. Your 8-8.5 target is met for EDA, chip-company and FAANG-Senior. FAANG Staff at 7 means the resume "
       "gets you into Staff loops at some companies; the system-design and leadership rounds decide the level.",
       size=9, color=MUTED)
p(doc, "**How FAANG will level you.** Recruiters anchor on your last FAANG-tier title (Microsoft SWE II, 2021-23, at years "
       "6-8), then read the Synopsys section to see whether it justifies a jump. A Synopsys 'Staff' title doesn't transfer "
       "1:1; in most FAANG calibrations it sits closer to Senior. The rewritten Synopsys section now makes most of the "
       "Staff case on its own. Expect Senior-level offers as the base case at Google, Microsoft and Meta, with Staff "
       "possible where the loop goes well. Aim Staff applications first where Synopsys Staff maps directly: Cadence, "
       "Siemens, Adobe, and the chip companies' software and CAD teams.")

# ---------------------------------------------------------------- 2
h(doc, "2. Format review and rating: 7 / 10", 1)
p(doc, "**Keep the format.** It's a clean, conventional, ATS-safe single-column layout, and Word 2010's PDF export preserves "
       "it. I verified this by exporting both files through your Word and extracting the PDF text layer. The problems are "
       "space allocation and a few small defects, not the design.")
table(doc, ["Dimension", "Score", "Evidence (Word render)", "Fix"], [
    ["ATS parsing", "9", "Single column, no tables or text boxes, headings are plain text, reading order intact in the PDF text layer, Calibri embedded", "None needed"],
    ["Typography and consistency", "8", "One family (Calibri); 16 / 11 / 10 / 9.5 pt hierarchy; blue #3C78D8 headings with a rule; right-aligned italic dates via a tab stop", "None"],
    ["Space allocation", "5", "Page 1 is a wall of 3-line bullets (median ~30 words, max 56). Page 2 is only 35-40% used. SKILLS takes the top third of page 1", "Redlined: every bullet 3 lines max. By hand: SKILLS below EXPERIENCE"],
    ["Header / contact", "5", "The link text reads 'LinkedIn', so the URL is invisible on paper and to text-only parsers such as Naukri's. No location. Icons include a Gmail logo", "Redlined: printed URL, 'Noida, India'. Icons optional"],
    ["Page-break control", "5", "The original FAANG file strands the Adobe header at the bottom of page 1. After the rewrite, the Microsoft header would have been stranded instead", "Redlined: 'Keep with next' on all role headers (tracked format change)"],
    ["Typographic polish", "6", "Bullets are typed '- ' with a manual hanging indent, not Word lists. ASCII '->' arrows. 'sev-2' and 'formal-verification' break across lines at the hyphen", "Rewrites drop the arrows. Keep '- ' if you like the look; non-breaking hyphen (Ctrl+Shift+-) in 'sev-2'"],
    ["Page size", "6", "US Letter. India prints A4, so printed copies scale down", "A4 for an India-only search"],
    ["File hygiene", "4", "The name 'resume-faang-atlassian-2page' tells Google it's a template aimed at someone else. Doc properties say creator 'python-docx'", "Always send 'Anuj_Pratap_Singh_Yadav_Resume.pdf'; set File > Properties"],
], [1.2, 0.5, 2.9, 2.27])
p(doc, "Length after the v2 rewrite: two pages, with page 2 about 40% full in both files. That's fine at 11 years. Don't "
       "pad it; the next additions should be numbers (section 8), not more text.", size=10)

# ---------------------------------------------------------------- 3
h(doc, "3. Top five systemic issues (in the original files)", 1)
numbered(doc, "**Bullets describe execution, not scope or judgment.** Of the 7 Synopsys bullets, 6 open with an execution verb. "
              "None states a trade-off you chose, and one mentions another engineer. The numbers that exist have no unit a "
              "reader can interpret (132 to 34 of what? 76% of what?). A Staff panel reads for decisions and why, other "
              "people's work changed by yours, and direction you set. The rewrite puts all three into the decoupling bullets.")
numbered(doc, "**Claims that break on the first follow-up question.** (a) The AI 'platform', written with no evidence of users. "
              "You do have team usage, so the fix is to say what's true. (b) Go 'runnable prototypes' and 'Go (study repo)': "
              "nothing is public. (c) 'Owned' Recording Studio and 'driving' 1.5M to 4.2M: by your own account it was team "
              "work. (d) 'Distributed systems, event-driven architectures' as a skill. (e) 'LLVM-adjacent', when you're "
              "actually building on LLVM. The Synopsys title was on this list in v1; your answer (a re-title, not a promotion) "
              "makes 'Staff, May 2023 - Present' fine.")
numbered(doc, "**The customer roster is overused, and for EDA it's a judgment flag.** The 8 names appear 3 times in each file, and "
              "the EDA save_covdb bullet adds per-customer fix detail. To Cadence and Siemens that reads as 'will share our "
              "customers too'. The rewrite names them once in the FAANG file and not at all in the EDA file.")
numbered(doc, "**The two variants differ in vocabulary, not positioning.** About 70% of the text is identical. The FAANG file "
              "opens with 'full-stack', which a FAANG screener reads as web, and it's named for Atlassian, a Java / cloud-SaaS "
              "shop where this profile is weakest. See section 4.")
numbered(doc, "**The strongest leadership evidence wasn't on the page at all.** Your answers surfaced:\n"
              "• a shared layer serving 10-12 apps;\n"
              "• cross-team work with the Common and CDC teams;\n"
              "• a documented standard that the Low Power team adopted;\n"
              "• design docs through architect and Distinguished Engineer review;\n"
              "• interview panels;\n"
              "• 50+ code reviews across teams;\n"
              "• 2 + 2 engineers mentored, and knowledge transfer to a new app;\n"
              "• AI tooling you introduced and shared, plus a tool your manager asked for.\n"
              "Add the summit talk from your notes. That's the gap between 'strong Senior' and 'Staff', and it was a writing "
              "gap, not an experience gap.")

# ---------------------------------------------------------------- 4
h(doc, "4. One resume per track", 1)
table(doc, ["Variant", "Send to", "Positioning", "What changes"], [
    ["**A. EDA, competitor-safe**", "Cadence, Siemens EDA, other EDA vendors",
     "C++ infrastructure engineer for verification tools: coverage databases, licensing, IPC, codebase architecture",
     "No customer names ('8 accounts'). Domain vocabulary in. Target platform / infrastructure roles, not formal-engine roles. = resume_reviewed_eda.docx"],
    ["**B. Chip-company tools**", "Nvidia, AMD, Intel, Qualcomm CAD, formal and methodology teams",
     "A, plus direct experience supporting their formal-verification teams",
     "Copy of A with the customer names restored once and the Nvidia summit named (and CoDa, if it's public)"],
    ["**C. C++ systems / platform**", "Google, Microsoft, Adobe, Apple, Meta infra, chip-company software teams",
     "11 years in large, long-lived C++ codebases (Photoshop Elements, Office Win32, VC Formal); a customer-facing subsystem; a cross-team standard",
     "= resume_reviewed_faang.docx. No distributed-systems claims. Rename the file"],
    ["**D. Cloud / backend**", "Atlassian, Salesforce, Amazon",
     "Don't build this one yet",
     "Production distributed evidence is one C# service. Apply with C at Senior level and let the system-design round prove the rest. Revisit after 2-3 public prototypes"],
], [1.3, 1.45, 2.0, 2.12])
p(doc, "Whatever the variant, the PDF you send is named **Anuj_Pratap_Singh_Yadav_Resume.pdf**.", size=10)

# ---------------------------------------------------------------- 5
h(doc, "5. Prioritized rewrite list", 1)
callout(doc, "**Before any of this:** the resume file on Naukri is still the 2025 version, with customer names plus what each "
             "customer designs, and the unsourced '40% setup time' claim (profile review v2, section 1.8). Every recruiter who "
             "downloads your profile gets that file, including recruiters at Synopsys competitors. Replace it, or take it down, first.",
        fill="FDECEA", border="D9534F")
table(doc, ["#", "Change", "Files", "Severity", "Effort", "Why"], [
    ["1", "Delete Personal Projects and 'Go (study repo)'", "FAANG, cv.md", "CRITICAL", "2 min", "Unverifiable, and it invites a cold deep dive"],
    ["2", "Decoupling as two bullets: scope (10-12 apps), the incremental choice, Common/CDC teams, then the documented standard and Low Power adoption", "Both", "HIGH", "Done", "Your strongest Staff evidence; multi-team influence"],
    ["3", "'Also' line: interview panels, 50+ cross-team reviews, mentoring 2 engineers, knowledge transfer to the new C++/RTL app", "Both", "HIGH", "Done", "Leadership evidence that was nowhere on the page"],
    ["4", "Coverage ownership: design docs through architect/DE review, escalations, summit talk", "Both", "HIGH", "Done", "Your clearest external signal, now with design authority"],
    ["5", "AI tooling: 'introduced to the team, built and shared', plus the manager-requested notifier", "Both, cv.md", "HIGH", "Done", "Team leverage stated as it is, instead of an unsupported 'platform'"],
    ["6", "Customers named once (C, B) or not at all (A); no per-customer issue detail", "Both", "HIGH", "Done", "Judgment flag for EDA; frees 2-3 lines"],
    ["7", "Recording Studio: team work, 'with the team', growth as context", "Both", "HIGH", "Done", "Matches what you told me; an ex-Microsoft interviewer will check it"],
    ["8", "Licensing: fallback judgment, weeks to ~2 days, verified core limits", "Both", "HIGH", "Done", "Your best number wasn't on the page"],
    ["9", "Skills lines: no distributed/event-driven claims (FAANG); formal terms you can defend (EDA); program slicer instead of 'LLVM-adjacent'", "Both", "HIGH", "Done", "Skills lines set the interview agenda"],
    ["10", "Summary: 11 years, C++ large-codebase throughline, 10-12 apps, cross-team standard", "Both", "HIGH", "Done", "The first 3 lines decide whether the rest gets read"],
    ["11", "Outcomes: density 'used by most customers'; save/restore 'a flow many customers rely on'; coverage DB before/after", "Both", "MED", "Done", "Activity logs read as mid-level"],
    ["12", "Remove Awards; fold the Adobe Spot Award into its bullet", "Both", "MED", "Done", "The Synopsys spot award reads as trivia"],
    ["13", "Format: keep-with-next (done), URL + location (done), SKILLS below EXPERIENCE (by hand), A4, file name", "Both", "MED", "15 min", "Cheap and visible"],
    ["14", "Titles: Synopsys stays 'Staff Engineer, May 2023 - Present' (re-title); Adobe becomes 'Member of Technical Staff 2'; change LinkedIn's Adobe 'SDE 2' to match", "Both, LinkedIn", "LOW", "5 min", "Resume matches the HR record; LinkedIn history stays as is"],
    ["15", "Sync cv.md (career-ops) once you sign off", "cv.md", "HIGH", "10 min", "career-ops tailors every application from cv.md, so the old claims propagate into everything it generates"],
], [0.3, 2.35, 0.9, 0.75, 0.55, 2.02])
p(doc, "'Done' means drafted as a tracked change in the reviewed files: accept or reject it in Word.", size=9.5, color=MUTED)

# ---------------------------------------------------------------- 6
h(doc, "6. Before and after: the three weakest bullets", 1)


def ba(title, before, wrong, after, note):
    h(doc, title, 3)
    table(doc, None, [
        ["**Before**", before],
        ["**What was wrong**", wrong],
        ["**After (v2)**", after],
        ["**Next step**", note],
    ], [1.2, 5.67], col_fills={0: "EAF0FA"}, zebra=None, size=9.5)


ba("6.1  AI tooling (both files)",
   "Built an internal Cursor-based engineering-productivity platform (9 custom skills, saved plans, 500+ doc searchable "
   "knowledge index) that cut regression triage from 2-3 hours to 5-10 minutes and JIRA ramp-up from 3-4 hours to 10-15 minutes.",
   "'Internal platform' plus team-sounding savings, with nothing on the page showing anyone else used it. The mid-level tell: "
   "it lists the tool's parts (skills, plans, index) instead of what it changed for the team. Your answer turned out better "
   "than the bullet: you introduced AI tooling to the team, the skills are shared, and your manager asked you for a tool.",
   "Introduced LLM agent tooling to my team: built and shared Cursor skills for regression validation, code review and "
   "license checks, backed by a searchable index of 500+ internal docs; regression triage dropped from 2-3 hours to 5-10 "
   "minutes. Also built the daily Jira-compliance notifier my manager asked for.",
   "Get one count: how many teammates use the skills weekly. 'Used by N of the team' makes this an unambiguous Staff "
   "leverage line.")

ba("6.2  Property & Assertion Density (FAANG file)",
   "Delivered Property & Assertion Density across native engine, TCL command shell, dual-process XML IPC, and HTML reporting; "
   "shipped 5 sub-capabilities across multiple releases.",
   "An activity log: the layers you touched plus a count of sub-features. No user, no problem, no result. 'Delivered' is a "
   "project-manager verb.",
   "Built property and assertion density reporting end to end (engine, TCL shell, two-process XML IPC, HTML report) so "
   "customers could measure verification completeness on datapath designs, closing a gap with the sister product; now used "
   "by most of the product's customers.",
   "None needed. 'Most customers' came from you; be ready to say how you know (usage data, support cases, AE feedback).")

ba("6.3  Recording Studio (both files)",
   "Owned PowerPoint Recording Studio enhancements (camera modes, background blur, Cameo customizable-camera object, video "
   "export) driving monthly recording sessions from 1.5M to 4.2M; Cameo shipped to ~1.2M of the 4.2M sessions.",
   "'Owned' and 'driving' claim a 2.8x product metric as your result. You confirmed it was team work. It also happened "
   "during 2021 remote-work growth, in your first months at Microsoft.",
   "Built PowerPoint Recording Studio features (C++) with the team: camera modes, live background blur, video export and "
   "Cameo, a camera object placed on the slide. Monthly recording sessions grew from 1.5M to 4.2M over those releases "
   "(Cameo: ~1.2M). Led v1 test automation and Recording/Export telemetry.",
   "This is the honest ceiling for this bullet. In an interview, say 'the team's number' before anyone asks.")

# ---------------------------------------------------------------- 7
h(doc, "7. What you'd done that the resume undersold, and where it went", 1)
table(doc, ["Evidence", "Source", "Now in the rewrite"], [
    ["Shared layer serves 10-12 VC Formal apps; worked with the Common and CDC teams", "Your answer", "Decoupling bullet + summary"],
    ["Options-layer pattern documented as a standard, presented to a wide forum, adopted by the Low Power team", "Your answer", "New bullet after decoupling + summary"],
    ["Two engineers you mentored now run their own decoupling changes", "OKR, May-Jul 2026", "Same new bullet"],
    ["Design docs for your features, reviewed by senior architects and a Distinguished Engineer", "Your answer", "Coverage-ownership bullet"],
    ["Nvidia internal formal-verification summit talk", "Portfolio, project 3", "Coverage bullet (named in C, redacted in A)"],
    ["Interview panels; 50+ code reviews across DPV and neighbouring teams", "Your answer", "'Also' line"],
    ["Mentored 2 engineers on the coverage stack; knowledge transfer that brought it into a new C++/RTL app (CoDa)", "Your answer", "'Also' line (app kept generic)"],
    ["AI tooling introduced to the team, skills shared; Jira-compliance notifier requested by your manager", "Your answer", "AI bullet"],
    ["Program slicer: first phase computes the cone of influence of the signals in a design's assertions", "Your answer", "New bullet + skills line"],
    ["Probe harness: licensing triage from weeks to ~2 days", "Portfolio, project 5", "Licensing bullet"],
    ["Fallback order designed so existing customers weren't locked out; core limits Base 1 to 4, Elite 4 to 12 (verified)", "Portfolio + your answer", "Licensing bullet (3-4x in FAANG)"],
    ["Density reporting used by most customers", "Your answer", "Density bullet"],
    ["save_covdb: 40+ regression tests; cross-site VDB design agreed with the Taiwan team", "Portfolio", "Coverage DB bullet"],
    ["10-year licensing thread (Adobe deactivation, then the Synopsys three-phase program)", "Resumes", "Kept in both; use it in EDA interviews"],
], [3.2, 1.35, 2.32])

# ---------------------------------------------------------------- 8
h(doc, "8. What wording can't fix", 1)
p(doc, "**Measured org-level outcome.** Your best Staff story has scope and adoption but no business number. Build time wasn't "
       "benchmarked, and you can still measure it: take one widely-included Common header, touch it on a pre-decoupling "
       "changelist and on today's code, and record files rebuilt and wall-clock rebuild time. One afternoon, and it turns "
       "'~75% fewer dependencies' into 'a shared-header change now rebuilds X files instead of Y'. This is the single "
       "highest-value addition left.")
p(doc, "**Leading people versus owning a system.** You own the coverage subsystem mostly alone, with mentoring and knowledge "
       "transfer around it. FAANG L6 panels often probe 'who executed your designs?'. The decoupling and Low Power adoption "
       "answer part of that. Leading a small feature team, formally or through a multi-person design, is the next step, "
       "and the program slicer is the natural candidate.")
p(doc, "**Distributed systems.** There's no production ownership at scale. The system-design round carries this, and "
       "articulating your own work under pressure is the weak spot you've already named. Prepare the three stories "
       "(decoupling, licensing, coverage ownership) in the problem, choice, result, adoption shape the rewrites use. "
       "Publish 2-3 prototypes with benchmarks before you claim Go or a GitHub link.")

# ---------------------------------------------------------------- 9
h(doc, "9. Your answers, and what I did with them", 1)
table(doc, ["#", "Your answer (short)", "What changed"], [
    ["1", "Synopsys title changed mid-way, not a promotion. Adobe was MTS2, 'SDE 2' possible; I decide",
     "Synopsys: keep 'Staff Engineer, May 2023 - Present', no promotion line. Current title across the tenure is standard, and background checks verify last designation plus dates. Adobe: **Member of Technical Staff 2**, your HR title, and Adobe (a target) reads its own levels exactly. Align LinkedIn's Adobe entry"],
    ["2", "Mostly me; a Distinguished Engineer approved design docs and joined feature discussions. Worried it reduces my credit",
     "'Own ... end to end: design docs (reviewed by senior architects and a Distinguished Engineer)'. It doesn't reduce credit: authoring designs that pass DE review is a Staff signal, and the wording keeps authorship yours"],
    ["3", "No build-time benchmark. Shared layer used across orgs: Common teams and all VC Formal, ~10-12 apps",
     "No build claim. Scope 'serves 10-12 apps' added to the bullet and summary. Section 8 shows how to get the number"],
    ["4", "Others use it: first in the team to present AI tooling; skills shared; manager-requested Jira notifier",
     "Rewritten as team adoption you introduced. 'Platform' dropped; the notifier added"],
    ["5", "Recording Studio was team work, not only my features", "'Built ... with the team'; growth kept as the team's context; 'Owned' and 'driving' removed"],
    ["6", "SKU sev-2 figure may not be exact; keep it", "Kept as '2-3 weeks' (a range); the 'incidents after' request dropped"],
    ["7", "Most customers adopted density reporting", "'Now used by most ... customers'"],
    ["8", "Many customers use save/restore; unsure about names", "EDA: 'a flow many enterprise customers rely on'. No names"],
    ["9", "Program slicer WIP; first part done (COI from a design plus assertion signals)", "New bullet 'in progress' plus the skills line. Generic in FAANG, 'DG/LLVM ... in DPV' in EDA"],
    ["10", "Reviewed changes from DPV and a few other teams", "'50+ code reviews across my team and neighbouring teams'"],
    ["11", "Core limits verified; licensing belongs under the Staff title", "EDA keeps Base 1 to 4 / Elite 4 to 12; FAANG says '3-4x'. All Synopsys work sits under the single Staff entry"],
    ["12", "Design docs: yes. Contributors: none, mentored 2. Interviews: yes, plus coverage KT for CoDa. Standard: yes, Low Power adopted. Cross-team: Common and CDC",
     "All added: coverage bullet, new standard bullet, 'Also' line, decoupling bullet"],
], [0.3, 2.5, 4.07])
p(doc, "**Still open (optional, none block sending):**")
bullet(doc, "The count of teammates who use your AI skills (section 6.1).")
bullet(doc, "Rebuild files and time for one Common header, before and after (section 8).")
bullet(doc, "Whether CoDa is public. If yes, name it in the chip-company copy.")
bullet(doc, "That the Feb 2024 title change kept the same level. If it was a level change, show the split dates instead of "
            "'Staff, May 2023 - Present'.")

# ---------------------------------------------------------------- 10
h(doc, "10. Files", 1)
bullet(doc, "**resume_reviewed_faang.docx** and **resume_reviewed_eda.docx**: open in Word and use Review > Reviewing Pane "
            "to read the full comments. Accept or reject per bullet; Accept All produces the rewrite (2 pages each, checked "
            "in Word).")
bullet(doc, "**resume_recommendations.docx**: this file.")
bullet(doc, "**review-specs/**: the specs that generate the reviewed files, rerun with "
            "`redline.py <original> spec-<variant>.json <out>` from the `resume-docx` skill (~/.claude/skills/resume-docx).")

doc.core_properties.title = "Resume review: Staff / Principal bar (v2)"
doc.core_properties.author = "Anuj Pratap Singh Yadav"
doc.save(OUT)
print("wrote", OUT)
