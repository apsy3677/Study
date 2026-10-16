# My intro: Flex Array interview (C++ / EDA audience)

> **Sources only:** the Synopsys intro guide (Oct 2026) and `Agoda-Staff-BE-Prep/00-Recruiter-Screen.md`. Nothing else is assumed.
> **[fill]** = only you know it. **[confirm]** = say it only if it's true.
> Audience is EDA and C++ engineers, so EDA terms (RTL, FPV, coverage) are fine here. Internal project names, CL/JIRA counts and customer names are not.

**What changed from the two earlier intros**

- Agoda's version translated EDA away for a backend recruiter. This one leans *into* EDA and C++.
- The Synopsys guide was a theme list. This one adds the 11-year arc in one line, so an outside panel knows who you are before the depth starts.
- Numbers are reconciled: the decoupling result is **"about 73%, with Jerry"** (the Agoda file said "about 75%" and "drove". Don't use either).
- The spoken version is cut to about 200 words, so it really fits in 90 seconds.

---

## 0. Before the interview

| Item | Your answer |
|---|---|
| What Flex Array builds | **[fill: product, and where it sits in the flow]**. Don't guess this on the call |
| Role title / team | **[fill]** |
| Why Flex Array (one real reason) | **[fill]**. Goes in the last line of the intro |
| Total experience | About 11 years: Adobe (Aug 2015 - Apr 2021), Microsoft (May 2021 - May 2023), Synopsys (May 2023 - now) |
| Title | Staff Engineer, Synopsys, Noida **[confirm dates against HR record]** |

---

## A. 30-second version

> I'm Anuj, a Staff Engineer at Synopsys, with about 11 years writing production software across Adobe, Microsoft and Synopsys. For the last three years I've been in C++ on VC Formal DPV, the tool that proves a C++ model of a datapath and its RTL give the same answer.
> My core area is the question after the proof: **is it enough?** I own the DPV side of coverage and property density. Around that, I've reduced build coupling across VC Formal's C++ codebase and worked on the licensing layer every run depends on.

---

## B. 90-second version (use this one)

> I'm Anuj, a Staff Engineer at Synopsys in Noida. I have about 11 years in production software: six at Adobe, two at Microsoft, and the last three in C++ on VC Formal DPV. DPV proves that a C++ model of a datapath, like an adder, multiplier or floating-point unit, and its RTL give the same result.
>
> **My core is one question: how does a customer know a DPV proof is enough?** A green proof doesn't tell you what it exercised. I own the DPV side of that answer: C++ coverage, which shows what the model's code actually hit, and property density, which shows how much of the design the proof really checks. These are the features customers come back to us about.
>
> **Second, C++ codebase health.** The shared layer was including engine headers, so one small edit rebuilt half the product. I built a small callback hub so the shared code asks the engine questions without including it. With Jerry, we cut the dependency count by about 73%. Most of it was code I didn't own, so the real work was getting teams to agree.
>
> **Third, licensing.** When it breaks, nobody runs anything. I've worked on its architecture and on customer escalations.
>
> I start from the customer's symptom, work back to the real cause, and say plainly what isn't done yet. **[fill: one line on why Flex Array.]**

*About 210 words. Pause after "is it enough?"*

---

## C. C++ depth: one story per theme (say only when asked)

Each is 3-4 sentences. Use one, then stop and let them dig.

### 1. Coverage and density (lead with this)

> One idea I'm proud of: for RTL function coverage, if the call sites are covered, the function body is covered. FPV already gets that effect through the formal core, so I made DPV consistent with it. Customers cared because the old DPV answer didn't match what they saw in FPV.
>
> On the C++ side, I built the DPV bridge so coverage opens in the GUI. A colleague wrote the coverage database writer. I reviewed it and worked with him on saving and viewing it in Verdi.

- Don't claim the function-body behavior is on by default (unconfirmed).
- Say "AEs reported the hidden output-coverage check working at a customer." Never "used in sign-off."

### 2. Header coupling (the most "pure C++" story)

> The shared layer was including engine headers, so the include graph tied everything together and small edits caused huge rebuilds. I built a callback hub: the shared layer calls through it, the engine registers behind it, and the shared code no longer includes engine headers. Jerry had a cleaner plan for one part, so I dropped mine and used his.

- Follow-ups to expect: how the callbacks are registered, how you kept behavior unchanged, how you measured dependency count. Answer from what you actually did.
- If the May 2026 talk credited Jerry as architect: "I built and rolled out the hub; Jerry's review shaped it."

### 3. Licensing escalation

> A customer saw "license not found" on some servers only. The first signal was misleading: it looked like a missing license. I traced it to two license-library calls that gave inconsistent answers on some servers, and removed the flow that depended on them, behind a hidden setting that's on by default.

- Don't quote a CL number.
- Phase 1 of a new licensing model is checked in and on hold. Say "on hold" yourself, before anyone asks.

### 4. Bet: C++ program slicing (only if asked about what's next)

> A research prototype that slices C++ source to show what really drives an output. I measured two design variants, saw they weren't good enough, and reverted them. The open blocker is mapping signals to the right slicer criteria. Promising, not shipped.

### 5. How I started (only if asked)

> Commands, save-restore, tests. I learned the codebase by fixing things.

---

## D. If they ask X, lead with Y

| They ask | Lead with |
|---|---|
| "Strongest area?" | Coverage and density, the "is it enough?" question |
| "Hardest C++ problem?" | Header coupling and the callback hub |
| "Debugging under pressure?" | Licensing: "license not found" on some servers only |
| "Cross-team work?" | Decoupling: code I didn't own, agreement I had to get |
| "Something ambiguous?" | Slicer: a prototype with a named blocker |
| "Before Synopsys?" | One line each: Adobe (Photoshop Elements, AEM), Microsoft (OneDrive commerce backend, PowerPoint Recording Studio) |
| "Why Flex Array?" | **[fill]** |

---

## E. Never say

- "Led" or "sole" for the decoupling work, the coverage database writer or the slicer.
- The slicer as released, shipped or productized.
- "Used in sign-off" about output coverage.
- "Promoted" about the Staff title.
- Customer names, CL counts, JIRA counts, internal project names.
- "About 75%" or "drove" for decoupling (old Agoda wording).

---

## F. Settle before the interview

| Line | Risk | Fallback |
|---|---|---|
| "With Jerry, about 73%" | Jerry's share; 37 vs 43 (about 68%) | "we cut the dependency count a lot" |
| "I built a small callback hub" | May 2026 talk credits Jerry as architect | "I built and rolled out the hub; Jerry's review shaped it" |
| "I own the DPV side of coverage" | Boundary with Verdi, VCS and GUI teams | Already scoped to "DPV side" |
| Function-body coverage | Possibly gated by a setting | Don't claim it's on by default |
| Why Flex Array | Not written yet | Must be filled before the call |
