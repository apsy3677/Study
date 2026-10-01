# Agoda: Recruiter Screen Prep ([BE] Staff Software Engineer - Back End, IND [SHP])

> Call: today (1 Oct 2026), 2:30 pm, with Eve Bovornrojwan (Agoda Talent Acquisition).
> Facts about you come from `Resumes/2026/profile-review-2026-09-v2.md` and `Resumes/2026/Build_resumes.md`.
> **[fill]** = a number only you know. **[confirm]** = say it only if it's true.
> Confidentiality: no Synopsys customer names, no internal tool names. Say "top semiconductor companies".

---

## 0. Keep this open during the call (cheat sheet)

| Item | Your answer |
|---|---|
| Total experience | ~11 years (Aug 2015 to now) |
| Current | Staff Engineer, Synopsys, Noida. Joined May 2023; Staff since Feb 2024 **[confirm against HR record; use the same dates everywhere]** |
| Before | Microsoft, Software Engineer II (May 2021 - May 2023); Adobe, MTS then SDE 2 (Aug 2015 - Apr 2021) |
| Education | B.Tech CSE, NIT Bhopal (MANIT), 2015 |
| Notice period | **[fill: 60 days per Naukri? early release or buyout possible?]** |
| Current CTC | **[fill: fixed + variable + stock, separately]** |
| Expected CTC | **[fill: a range, not one number]**, see section 5 |
| Location | Noida, so no relocation needed. Hybrid 3 days in the Gurugram office works. |
| Other processes | **[fill: e.g. "two other processes at mid stage"]**. Don't name companies unless asked. |
| Interview availability | **[fill: 3-4 slots over the next week]** |
| Which resume did you apply with? | **[check]** If it's a 2025 resume, it has the unsourced "40% setup time" claim and customer names. Don't repeat either on the call. |

Also check that the calendar invite says 2:30 pm **IST**. Eve is most likely in Bangkok (IST + 1:30).

---

## 1. What the Gurugram team handles (what's public, and what isn't)

**Public:**
- Agoda India has two offices: **Gurugram** (Tech, Product, Customer Experience) and **Mumbai**. Agoda calls India one of its fastest-growing markets.
- The Gurugram **Back End** postings (Staff Level 4, Lead Level 5, EM) all describe the same org: *high-scale, fault-tolerant distributed systems* owning **inventory, pricing, booking, payments, and customer/partner platforms**. These are high-availability, low-latency, zero-downtime systems.
- Stack: **Scala, Go, Java, Kotlin**, plus **Kafka** and **Aerospike**. Strong on CI/CD, automation and observability. Agoda historically also runs **C#/.NET** and its own **private cloud** rather than only AWS/GCP.
- Gurugram is also hiring Staff Backend-heavy Full Stack (BFF layer), a Staff Back End (AI) role, a Lead L5 (11+ years) and EMs. That means the hub is building whole teams, not just a few seats. A growing hub is a real reason a Staff engineer gets scope.
- Hybrid: 3 days in office, 2 from home. Relocation support is provided (not relevant for you).
- Level map: **Staff = Level 4 (8-12 yrs)**, Lead = Level 5 (11+ yrs). Your 11 years sit inside the L4 band. Don't push for L5 on this call.
- Company: part of **Booking Holdings** (NASDAQ: BKNG), 7,000+ people from 90+ countries, engineering-led, with a heavy **A/B experimentation** culture.

**Not public: which domain this req is in.** The "[SHP]" tag also appears on non-engineering Agoda postings: an HR Business Partner in Bangkok, a Market Manager (B2B supply) in Tokyo, an Account Manager for Japan Homes, and a Strategic Account Manager in Malaysia. So it's probably a hiring-program or requisition tag, not a team name. Several of those are supply-side, but don't assume. **Ask Eve** (section 7). It's a good question, and it shows you read the posting closely.

**How to use this on the call:** show you know the domains ("pricing, inventory, booking at marketplace scale") and ask which one this role sits in. Don't pretend to know the team.

---

## 2. What Eve is actually scoring (and the signal you want her to write down)

A recruiter screen isn't technical. She's filling a scorecard for the hiring manager. Make every box easy to tick:

| She's checking | Signal to give | How |
|---|---|---|
| **Relevant experience** (backend, distributed systems, Java/Scala/Kotlin/Go) | "Owns systems end to end; has services and event-driven experience; will ramp on Scala fast" | Use JD words naturally: *ownership, distributed services, event-driven, concurrency, performance, reliability, backward compatibility, production RCA, mentoring* |
| **Seniority (Staff)** | "Drives cross-team technical changes, not just tickets" | Decoupling program, licensing across 3 models, customer escalations, 2 engineers mentored |
| **Motivation** | "Specifically wants Agoda and this hub, not just any job" | Section 4: why Agoda, why backend, why now |
| **Communication** | Clear, structured, no jargon | 60-90 second answers. Translate EDA terms (section 6) |
| **Logistics** | Notice, location, comp inside the band | Section 5. Have the numbers ready, no hesitation |
| **Risk flags** | None | No badmouthing, no over-claiming, no "just exploring" |

**The one concern she'll probably have:** *"His last 3 years are C++/EDA, not web backend in Java/Scala."* Handle it head-on (Q4 below) instead of hoping it doesn't come up.

---

## 3. Your intro

### 3a. Full version (~75 seconds). Say it out loud 3 times before the call.

> Hi Eve, thanks for setting this up.
>
> I'm Anuj, a Staff Engineer at Synopsys in Noida, with about 11 years across Adobe, Microsoft and Synopsys. The common thread is owning systems end to end, where performance, reliability and backward compatibility matter because real customers depend on them.
>
> At Synopsys I own a C++ subsystem in our verification product: the design, every release since 2023, and the production escalations from eight enterprise customers, from root cause to fix to regression test. I also drove a six-month effort that cut coupling in a 2-million-line codebase by about 75% without a rewrite, and two engineers now run that pattern on their own. And I took our licensing system, which is basically the entitlement service for what each customer can run, through three models in two years, with a fallback design so no existing customer broke.
>
> Before that, at Microsoft, I worked on OneDrive's commerce backend: an event-driven C# service on Azure Event Hubs that routes purchase and quota-entitlement events. I also designed catalog filtering that stopped unsupported SKUs from hitting the upgrade API, which had been causing sev-2 incidents. And I owned PowerPoint Recording Studio features. My first six years were at Adobe, on Photoshop Elements and AEM.
>
> Now I want to bring that ownership and systems depth back to high-scale consumer backend. That's why this role stood out: pricing, inventory and booking at marketplace scale are exactly those problems, and the Gurugram hub is growing, so a Staff engineer can help shape how it's built. It's also practical for me, since I'm in Noida.

### 3b. Short version (~30 seconds), if she says "briefly"

> I'm a Staff Engineer at Synopsys with 11 years across Adobe, Microsoft and Synopsys. I own a production C++ subsystem used by enterprise customers, I've led large cross-team refactoring and a backward-compatible licensing redesign, and at Microsoft I worked on OneDrive's event-driven commerce services. I'm looking to bring that ownership to high-scale backend, and Agoda's marketplace systems are exactly that.

**Delivery:** stop after the intro and let her steer. Don't monologue past 90 seconds.

---

## 4. Likely questions and how to answer

Keep each answer to 30-60 seconds: **headline, one proof point, tie back to Agoda.**

### Q1. Walk me through your background.
Section 3a.

### Q2. Why are you looking to move? Why now?
> Synopsys has been great for depth. I've owned a subsystem end to end and led long-running technical changes there. But EDA is a narrow domain. My Microsoft and Adobe years were at consumer scale, and I want to get back to systems where backend design choices directly affect millions of users, at Staff scope. The timing is right because I've built the ownership and leadership track record I wanted from this role.

Never criticize Synopsys, a manager or comp.

### Q3. Why Agoda? What do you know about us?
Pick 2-3:
> 1. **The problems:** pricing and availability across a huge inventory, in real time, with low latency. That's a genuinely hard distributed-systems problem, not CRUD.
> 2. **Engineering culture:** Agoda is known for being data-driven, with heavy A/B experimentation, so decisions get made on evidence. That's how I like to work.
> 3. **The Gurugram hub:** it's growing, with Staff, Lead and EM roles open, so there's room to help shape how the India teams own services, not just join a mature setup.
> 4. **Practical:** Booking Holdings backing, hybrid, and Gurugram is close to Noida.

### Q4. (The important one) This role needs strong backend and distributed systems in Java/Scala/Kotlin/Go. Your recent work is C++/EDA. How much backend experience do you have?
Be precise. Over-claiming gets exposed in round 2.
> Fair question. All 11 years have been on the systems side, but I'll be precise. My services work is Microsoft: OneDrive's commerce backend, an event-driven C# service on Azure Event Hubs, which is the same model as Kafka, plus the catalog-filtering work on the upgrade path. At Adobe I worked in Java on AEM **[confirm: server-side?]**. At Synopsys it's large-scale C++ systems: multiprocessing and partitioning for very large inputs, IPC between processes, the licensing and entitlement system, and backward-compatible persistence. Different domain, same core problems: performance, concurrency, reliability, and owning production issues for enterprise customers. The system design round is where I'd want to show the distributed-systems depth.

### Q5. Are you comfortable with Scala, Kotlin or Go?
> Yes. I've written C++, C#, Java and TypeScript professionally, so switching languages is routine. I've also been writing Go on my own, building distributed-systems primitives (a write-ahead log, LSM storage, consistent hashing, Kafka-style consumer offsets) as study projects. Scala's functional style is the biggest shift, and I'd expect to be productive in the first few weeks. The harder part of this job is design and ownership, and that transfers directly.

(Call the Go work "study projects", not production. Per your profile review, the code isn't public yet.)

### Q6. Tell me about the biggest or most complex system you've owned.
Lead with **licensing**. It's the most backend-like story (an entitlement service plus backward compatibility):
> Over two years I took our licensing through three models: token-based, then per-app cores, then a tiered scheme. The hard part was that existing customers couldn't break, so I designed a fallback that honored older licenses. I also built a 7-checkpoint probe harness that cut regression triage from weeks to about 2 days, and shrank the licensing test suite from 38 tests to 9 without losing coverage.

Backup: the **decoupling** story (2M+ lines, ~75% coupling cut, incremental instead of big-bang, 2-3 changes per sprint for 6+ months).

### Q7. What scale have you worked at?
> At Microsoft it was user scale: OneDrive consumer and PowerPoint, used by millions. At Synopsys it's code and data scale: a 2M+ line codebase and very large chip designs that need partitioning and multiprocessing to run at all. In both, the job was the same: performance, reliability, and not breaking existing users.

(Don't claim the OneDrive user count as your personal impact. The product had the users.)

### Q8. Leadership and mentoring?
> I lead through technical direction rather than people management. On the decoupling work, earlier attempts had stalled, so I proposed an incremental pattern, proved it with small safe changes, gave an internal talk, and two engineers now drive their own changes with it. I also review across teams and agreed a data format with a team in Taiwan for the coverage database.

### Q9. A production issue you handled?
> I own escalations for my subsystem from eight enterprise accounts. The pattern is root cause, then a regression test, then a fix shipped across every active release stream. At Microsoft, new commerce SKUs kept breaking OneDrive's upgrade path as sev-2s that took 2-3 weeks to fix, so I designed catalog filtering plus an allowlist so unsupported SKUs never reached the upgrade API.

### Q10. What's your current role and team?
> Staff Engineer on **[fill: team, size N]**, reporting to **[fill: manager's title]**. I own the coverage subsystem and drive cross-team technical work like the decoupling and licensing changes.

### Q11. What are you looking for in your next role?
> Staff IC scope on high-scale backend: owning a domain's services, setting technical direction for the team, mentoring, and being close to production. I'm deliberately staying on the IC track.

### Q12. Notice period?
> **[fill]** days. **[confirm: "I'll check whether early release is possible."]**

Agoda will ask this early. Saying it without hesitation is itself a good signal.

### Q13. Location and hybrid?
> I'm in Noida, so Gurugram works without relocation, and 3 days a week in the office is fine.

### Q14. Other interviews or offers?
> Yes, a couple of other processes at **[fill: stage]**. Agoda is high on my list because of the domain and the hub, so I'm happy to move quickly on scheduling.

This gives her a reason to move fast. Don't bluff an offer you don't have.

### Q15. Have you interviewed with Agoda before?
Answer truthfully.

### Q16. When can you do the next rounds?
Give 3-4 concrete slots in the next 7 days. Fast availability is a positive signal.

---

## 5. Compensation (Indian recruiters usually ask current and expected CTC)

- **Try to get her range first:** "Before I share a number, could you tell me the budgeted range for Level 4 in Gurugram? I want to make sure we're aligned."
- **If she insists on current CTC:** give it broken down, honestly (fixed / variable / stock). Don't inflate it. Offer letters and payslips get checked.
- **Expected:** give a **range**, anchored on the total package, and say you're flexible on the mix. "For a Staff role, I'm looking at **[fill: X-Y]** total, depending on the structure of fixed, bonus and stock."
- **Data point (single, unverified):** one Blind commenter put Agoda India Staff at roughly ₹70 LPA fixed. Treat it as a hint, not a benchmark. Look up Level 4 on levels.fyi before the call if you have 5 minutes.
- Don't negotiate on this call. The goal is just "within band, proceed".

---

## 6. Translate EDA jargon (she isn't technical; the hiring manager reads her notes)

| Don't say | Say instead |
|---|---|
| VC Formal / DPV / formal verification tool | "A product top chip companies use to prove their chip designs are correct before manufacturing" |
| Coverage subsystem (internal command names) | "The component that measures and stores how thoroughly a design was checked" |
| DPV licensing (internal model names) | "The licensing and entitlement system that decides what each customer can run" |
| Decoupling program (internal project/class/metric names) | "A decoupling program in a 2M-line codebase, using dependency inversion" |
| RTL, SVA, case-split, UAL | (skip entirely) |
| Any customer name | "Top semiconductor companies" |

---

## 7. Questions to ask Eve (pick 3-4; always ask the first and the last)

1. **"Which domain does this role sit in: inventory, pricing, booking, payments or partner platforms? And what does [SHP] in the title refer to?"**
2. "How big is the Gurugram backend org today, and do the India teams own services end to end, or work alongside Bangkok-owned services?"
3. "What separates Level 4 Staff from Level 5 Lead at Agoda, in terms of scope?"
4. "What does the interview loop look like: rounds, format, and which languages are allowed for coding? Is there a system design round?"
5. "Is Scala expected from day one, or is ramp-up time expected for someone strong in other languages?"
6. **"Is there anything in my background you'd want me to clarify for the hiring manager?"** This surfaces the backend/C++ concern while you can still answer it.
7. "What are the next steps and the timeline?"

---

## 8. Closing the call (30 seconds)

> Thanks, Eve. This sounds like a strong fit, especially **[the domain she named]**. I'm very interested and can make myself available for the next rounds this week. What's the best way to send you my slots?

Then send a short thank-you email the same day with your availability.

---

## 9. Don'ts

- Don't ramble past 90 seconds on any answer.
- Don't over-claim "8+ years of distributed systems". Be precise (Q4).
- Don't quote numbers you can't source: no "40% setup time", and check whether the Recording Studio 1.5M to 4.2M figure is users or sessions before using it.
- Don't name Synopsys customers or internal tools.
- Don't say "just exploring", and don't badmouth any employer.
- Don't anchor comp low just to get through.

---

## 10. After the call: what the next rounds probably look like (confirm with Eve)

Public reports, not verified for this req: a coding round (DSA, LeetCode medium-hard; past Agoda India Staff questions included queue/tree problems and finding pivot elements in an unsorted array), then a virtual loop with **coding + system design + hiring manager / behavioral**.

For this role, system design should be travel-marketplace-flavored: **hotel search and availability, pricing cache (Aerospike-style KV), booking with idempotency and payments, Kafka-based event pipelines, rate limiting, and multi-region consistency for inventory.**

Sources: [Agoda India offices blog](https://careersatagoda.com/blog/agoda-india-gurugram-mumbai/), [Staff BE L4 JD (Greenhouse)](https://job-boards.greenhouse.io/agoda/jobs/8035213), [Staff BE L4 JD (freehire mirror)](https://freehire.me/jobs/staff-software-engineer-backend-level-4-gurugram-ind-agoda-yd4eptvn), [Lead SE L5 Gurugram](https://careersatagoda.com/job/8036127-lead-software-engineer-level-5-backend-gurugram-based/), [[SHP] on a non-engineering posting](https://builtin.com/job/principal-hr-business-partner-commercial-bangkok-based-shp/8046947), [Blind: Agoda India Staff](https://www.teamblind.com/post/agoda-india-staff-software-engineer-interview-nqovghon), [Prepfully: Agoda SE guide](https://prepfully.com/interview-guides/agoda-software-engineer).
