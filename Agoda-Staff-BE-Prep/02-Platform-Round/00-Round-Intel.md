# Agoda IV2 Platform Round: Intel (researched 15 Oct 2026)

> **Method:** (1) the Platform Interview Toolkit PDF from Agoda (kept locally in this folder, git-ignored because it's marked *Internal*; summarised here in my own words), (2) the recruiter's email, (3) candidate reports from 2024–26 read directly on LeetCode Discuss, plus TechPrep/Glassdoor/Blind summaries, (4) the recruiter-screen notes in [`../00-Recruiter-Screen.md`](../00-Recruiter-Screen.md).
> Every claim is tagged with its source so you can judge its weight.

---

## 1. Ground truth: Agoda's own description (Toolkit + email)

**Format.** 60 minutes on HackerRank (a whiteboard/diagram pane + code pane), **two parts**:
1. **Narrative** (most of the hour): Agoda shows you a feature or problem **with a diagram and code snippets**. The design *"often has intentional gaps or faults"*. You find them, fix them, and justify the fix.
2. **Generic questions**: short questions on the same 5 areas, **independent of the narrative** (e.g. "REST vs gRPC?", "how do you make a retry safe?", "what goes in your test pyramid?").

**The 5 graded attributes** (Toolkit, my wording):

| Attribute | What they want to see | Toolkit's pro tip, paraphrased |
|---|---|---|
| **System analysis & design** | Break down requirements, find bottlenecks and missing pieces, know scalability / integration / fault tolerance trade-offs (performance, cost, security) | Think aloud: say the pros and cons of every decision |
| **Connectivity management** | API design + "connectivity frameworks": protocol choice (REST, GraphQL, gRPC), error handling, authN/authZ, sync vs async, integration strategies, API contracts | Be specific about *why* you choose an approach, and name practices you've used in real projects |
| **Quality assurance** | Testing at design and code level: unit, integration, E2E, non-functional; test-pyramid trade-offs; how to raise coverage and reliability | Start with *why*: the value each test brings |
| **Code review** | Readability, maintainability, correctness; code smells, SOLID, basic design patterns; suggest fixes with reasons | Frame feedback positively and offer alternatives, not just criticism |
| **Communication** | Explain complex things simply, engage, take questions | Adapt to the audience (technical and non-technical) |

**Recruiter's extra hints** (these are, in effect, the answer key; they appear in the email because people miss them):
- Code review: **SQL injection, expensive DB initialisation per call, hardcoded vendor keys, missing pagination.** "Avoid superficial reviews."
- Connectivity: **webhooks, pub/sub, polling, REST vs gRPC, error handling, pagination, retry strategies**, partial responses, retries with backoff, observability (logs/metrics/tracing), **backpressure**.
- QA: justify each test type's **cost vs benefit**; cover **non-functional** (resilience, performance).
- Explain the **underlying mechanics** of the tech you pick, not just its name.
- **Manage the timebox**: don't get stuck in code minutiae; reach system-level concerns.
- Draw diagrams: component, sequence, deployment, test flow.

**Staff/Lead bar** (Toolkit p.2): drives architectural change, designs new systems, provides technical direction, *understands business impact*, raises team productivity, works across teams. → In every answer, add one line on **cost/business impact** or **what you'd standardise for the team** (a shared retry library, a contract-test gate in CI, a review checklist).

---

## 2. What candidates actually got (2024–26)

| When | Role, location | What the platform round was | Source |
|---|---|---|---|
| **May 2026** (posted Aug 2026) | **Staff SE, Bangkok** | **Flight aggregator pulling from 2 sources.** Diagram: `Client → Flight booking service → Source1, Source2, Database`, *no cache, no LB, no queue*. An incomplete API was given. Points expected: how to fetch from sources and keep data fresh · **cache the search API** · **pagination missing → cursor vs offset** · reduce downstream calls (**batch API**) · **double booking** · **dedupe provider responses** · **auth** and other API details. Then **fix a booking service's code**: no exception handling, non-standard structure. | [LC 8487700](https://leetcode.com/discuss/post/8487700/) |
| Sep 2026 | Staff Backend | Platform round = **"external supplier fetching booking data"**. Candidate was **down-levelled to Senior** after it. | [LC 8516551](https://leetcode.com/discuss/post/8516551/) |
| Feb 2026 | SSE Backend, Bangkok (offer) | (1) Problem statement + **partially completed design** → complete the HLD, say what's wrong, design the APIs. (2) **Code block to review**: *"checks how quickly you can understand the code and how you review it"*. | [LC 7565801](https://leetcode.com/discuss/post/7565801/) |
| Oct 2025 | **SSE Backend, Gurugram** (your [SHP] track) | **Flight inventory from multiple suppliers via metered (paid) APIs**, no push from suppliers. Users search by src/dest/dates, prices and seats change often, must show the latest data, the **same flight from several suppliers → show the cheapest**. HLD. **Rejected: "connectivity management area is not strong."** | [LC 7274226](https://leetcode.com/discuss/post/7274226/) |
| Jul–Aug 2025 | Staff SE, Bangkok | Covers system design, REST API design, code review, QA. Design: improve a **booking/data-fetching** design (LB, rate limiter, message queue…). Connectivity: improve the REST APIs, **types of authentication**, *"how you manage a robust, secure connectivity session"*. Code review: **booking API**, candidate proposed the **strategy pattern** + proper error/exception handling. | [LC 7082771](https://leetcode.com/discuss/post/7082771/) |
| Jul 2025 | Staff Backend, Bangkok | **Given a badly designed system → improve it.** Code review + DB/tech choices. *"Lots of how / what / why / why not grilling."* | [LC 7237792](https://leetcode.com/discuss/post/7237792/) |
| (Glassdoor) | Gurgaon | Code review: a **loop calling a DB client and an HTTP client** → refactor with the **strategy pattern** | [Glassdoor](https://www.glassdoor.com/Interview/Agoda-Interview-Questions-E461386.htm) (search summary only) |
| (Blind) | Senior Backend, Bangkok | Rewrote the supplied code with a **factory pattern + class hierarchy** | [Blind](https://www.teamblind.com/post/agoda-interview-experience-am-i-being-ghosted-gqhaqizi) (search summary only) |
| (TechPrep) | Backend | Code review of a **basic booking API**: find bugs, suggest patterns (strategy), improve error handling. Expect **concurrency + runtime** questions about your primary language (threading, immutability, async) | [TechPrep](https://www.techprep.app/blog/agoda-interview-process) |

### The pattern is strong: "aggregator over external suppliers, plus booking"
4 of the 5 detailed reports use **the same narrative shape**: a service that **pulls data from several external suppliers** (flights or hotels), serves **search**, and has a **booking** step. Then a **booking-service code review**. This matches Agoda's real business: supply comes from thousands of hotel chains, channel managers and flight consolidators via their APIs. This is literally what "connectivity" means at Agoda.

So expect, with high probability:
- A diagram with **one service calling suppliers synchronously from the request path**, writing to one DB. No cache, no queue, no LB, no rate limit, no retry, no idempotency.
- An **API without pagination, auth, versioning or error model**.
- **Booking code** in Java/C#/Scala-ish style with: no exception handling, a loop over suppliers with `if (supplier == "A") … else if …` (→ strategy/adapter + factory), clients created per call, hardcoded keys, string-built SQL, no transaction / double-booking race, no timeouts.

That exact narrative is [Scenario 1 in 05-Scenarios.md](05-Scenarios.md) and lab 1 of the WSL plan.

---

## 3. Why people failed or got down-levelled
1. **"Connectivity management not strong"** (Gurugram SSE, your track). The HLD alone isn't enough; they wanted depth on *how you talk to suppliers*: polling cadence vs cost, metered API budgets, caching with TTLs per field volatility, rate limits, retries/backoff, timeouts, partial results, circuit breakers, auth to suppliers, webhooks if available, pagination, batch APIs, change detection. → [02-Connectivity-APIs.md](02-Connectivity-APIs.md) is the biggest file for this reason.
2. **Down-levelled to Senior** after this round (Staff, Sep 2026). A Staff answer must go beyond fixing: trade-offs quantified, cost, operability (SLOs, alerts, runbooks), rollout/migration plan, what you'd standardise across teams.
3. **Superficial code review** (the recruiter warns about it explicitly). Naming nits while missing SQL injection or a double-booking race is a fail. → Review order in [04-Code-Review.md](04-Code-Review.md): correctness and security first.
4. **Getting stuck in detail and running out of time.** The recruiter warns about it. → Clock in §4.

---

## 4. The 60-minute clock (plan it, then say it)

| Min | Phase | Output |
|---|---|---|
| 0–3 | Intro (keep it short: 60 s) | One-line "who I am + a connectivity-heavy project" |
| 3–8 | **Clarify** the narrative | Functional reqs, scale, freshness SLA, supplier constraints (metered? rate limits? push available?), success metrics |
| 8–25 | **Gap hunt + redesign** | List gaps on the diagram first (a quick numbered list), then draw the improved version and justify the top 3–4 changes |
| 25–35 | **Connectivity + API** | Contract: endpoints, pagination, idempotency, errors, auth. Supplier integration: polling/caching/retry/limits |
| 35–48 | **Code review** | Top-down: correctness → security → reliability → performance → tests → readability. Then the refactor (strategy/adapter/factory) |
| 48–52 | **Test plan** | Pyramid mapped to the components and failure modes you just discussed |
| 52–60 | Generic questions + your questions | Crisp 30–60 s answers |

The interviewer drives the order. Follow them, but **if they haven't asked about testing by minute ~45, offer it** ("Shall I sketch how I'd test this?"): QA is graded either way.

---

## 5. Likely Agoda domains (from the recruiter screen)
Gurugram BE = inventory, pricing, booking, payments, customer/partner platforms. High-availability, low-latency, zero-downtime systems. Agoda's backend is JVM-heavy (Scala, Kotlin, Java) with some C#/.NET, Kafka, Couchbase/Redis, SQL Server/Postgres, Kubernetes, and a strong experimentation culture (A/B tests on almost everything). **For code review, expect Java/C#/Scala-looking code. Reviewing it needs no deep language expertise**: read for logic, resources, concurrency, security.

Your language for any code you write: say *"I'll sketch in Java"* (you've used it, and Agoda reads it natively) or Go/Python pseudocode. Avoid C++ for service code here: it reads as off-domain.

---

## Sources
- Agoda **Platform Interview Toolkit** PDF (local, git-ignored) and the recruiter email (15 Oct 2026)
- [LC Discuss 8487700: Staff SE Bangkok, May 2026: flight aggregator + booking code fix](https://leetcode.com/discuss/post/8487700/)
- [LC Discuss 8516551: Staff Backend, Sep 2026: external supplier fetching booking data, down-levelled](https://leetcode.com/discuss/post/8516551/)
- [LC Discuss 7565801: SSE Backend Bangkok, Feb 2026: partial design + code review](https://leetcode.com/discuss/post/7565801/)
- [LC Discuss 7274226: SSE Backend Gurugram, Oct 2025: metered flight supplier APIs; rejected on connectivity](https://leetcode.com/discuss/post/7274226/)
- [LC Discuss 7082771: Staff Bangkok, Jul–Aug 2025: design / REST / auth / code review / QA](https://leetcode.com/discuss/post/7082771/)
- [LC Discuss 7237792: Staff Backend, Jul 2025: badly designed system, code review, DB choices](https://leetcode.com/discuss/post/7237792/)
- [TechPrep: Agoda interview process](https://www.techprep.app/blog/agoda-interview-process) · [Glassdoor](https://www.glassdoor.com/Interview/Agoda-Interview-Questions-E461386.htm) · [Blind](https://www.teamblind.com/post/agoda-interview-experience-am-i-being-ghosted-gqhaqizi) (known from search summaries)
- Prep video: [Interview 2 Prep video, Agoda Backend Tech Team](https://www.youtube.com/watch?v=ok1Sa-ea7YY) (no transcript available: watch it on Day 1 and add notes in §6)

## 6. Notes from the prep video (fill in on Day 1)
- 
