# Engineering Case-Study Portfolio: Prompt Pack

Three parts:

- **Part A**: standing rules. Save once as `00_RULES.md` in the portfolio folder and @-mention it in every chat.
- **Part B**: one prompt per pass. Paste them one at a time, in order.
- **Part C**: reconstructing a single incident as a debugging case study.

Replace every `<ANGLE_BRACKET>` placeholder before you paste.

---

## Part A: Standing rules (`00_RULES.md`)

```markdown
---
do_not_ingest: true
---

# Engineering Case-Study Portfolio: Standing Rules

## 1. Purpose

I am building an engineering case-study portfolio of my work from <PERIOD>
(<ROLE / TEAM>). I will use it to:

- write my self-review and promotion case against the Staff / Senior Staff
  career ladder,
- present selected projects as case-study talks to senior engineers outside
  my team, who will push back with hard follow-up questions,
- transfer knowledge to engineers who do not know our domain.

The finished portfolio must let me explain any project out loud, crisply and
accurately, to a strong senior engineer who knows nothing about our domain,
and then hold up under 15 minutes of skeptical follow-up questions.

The goal is to present the real work better, not to make it bigger.
When in doubt, keep the original fact and ask me.

## 2. Sources and boundaries

Allowed sources (read only):
- <PORTFOLIO / PROJECT DOCS FOLDER>
- <WEEKLY STATUS DOC>
- <SELF-REVIEW / OKR / CHECK-IN DOCS>
- My Perforce changelists and their descriptions (read-only commands only:
  `p4 changes -u <USER>`, `p4 describe -s`, `p4 filelog`)
- Code-review threads on my changelists (read only)
- Tickets I filed, owned, or commented on, including all comments (read only)
- My saved Cursor plans and my knowledge-system documents
- Whatever I tell you in this chat

Hard boundaries:
- Write ONLY inside `<PORTFOLIO_DIR>`. Never create, edit, comment on,
  shelve, submit, or transition anything in Perforce, code review, the
  ticket system, the knowledge system, or any shared location.
- Every file you create starts with `do_not_ingest: true` frontmatter.
- Never copy source code, customer data, credentials, or proprietary
  algorithm details into the portfolio. Describe behavior in words instead.
- Ticket and changelist IDs may appear in working notes only, as evidence
  pointers. They never appear in walkthroughs or public-safe versions.

## 3. Rule one: factual fidelity (overrides everything else)

Never invent or assume:
- metrics, percentages, before/after numbers, time saved, money saved
- customer impact, customer names, or customer details
- team sizes, deadlines, dates, durations
- leadership I did not have ("led the team", "managed", "drove the org")
- decisions I did not make, or reasons for decisions I did not state
- technologies I did not use, or problems that did not happen
- meetings, war rooms, working groups, pilots, or user studies that did not
  happen
- file names, bug names, or artifacts that do not exist in the sources

An earlier attempt at this kind of write-up failed in these exact ways.
Treat each one as a hard error:
1. putting a project at the wrong employer or in the wrong time period
2. outcomes nobody measured ("saved millions", "adopted across product
   lines", "% improvement")
3. upgrading my role (writing "led the team" when I was the primary
   developer)
4. inventing artifacts and events (a named bug file, a war room, a
   cross-team working group)
5. generic reflections that could fit anyone ("learned the power of
   teamwork")
6. a story that contradicts another document about the same project

Tag every claim in the working notes with exactly one of:
- `[SRC: <doc / ticket / CL / status week>]`: found in a source
- `[ME]`: I told you in this chat
- `[INFER]`: your interpretation. It must never appear as fact in a
  walkthrough.
- `[MISSING]`: needed but unknown. Ask me.

When a point looks strong but is unverified, label it
"POTENTIALLY STRONG: NEEDS CONFIRMATION".
When sources conflict, show both versions and ask me which is right.

Numbers: quote only sourced numbers. Keep the unit, the baseline, the
denominator, and how it was measured. If there is no number, describe the
result in words. You may suggest where a real number could be found (for
example "a before/after build time could be pulled from X"), but only as a
question, never as a claim.

Fact versus interpretation, for example:
- FACT: "I investigated why the worker count kept increasing."
- GOOD INTERPRETATION: "This shows I went after the system behavior
  instead of patching the visible symptom."
- INVALID: "I redesigned the worker lifecycle architecture." (Not
  supported.)

## 4. Separate three layers, then add the "so what"

For every project and case study, keep these apart:
1. What happened to the project or team.
2. What happened because of me.
3. Why what I did was hard or important.
Then write one sentence: why a senior engineer should care about this story.

"I" versus "we": use "I" for what I personally did. Use "we" honestly for
team actions, and say who did what by role ("the solver team owned X; I
owned Y"). Never turn team work into mine. Never hide my work behind "we".

## 5. Find the story inside the facts (the difficulty lens)

My weak spot is that I undersell how hard a problem was. Do not just
summarize what happened. For every case study, check each dimension below.
Mark it present only with evidence, and draft a "What made this tricky
was..." sentence for each one that applies.

- Symptom far from cause: it showed up in one component or phase but
  started in another, or earlier in the lifecycle.
- Misleading first signal: the obvious fix would have hidden the problem
  or broken something else.
- Poor observability: no logs, no local repro, only at customer site or at
  scale, intermittent, timing- or environment-dependent.
- Many moving parts: multiple processes, components, teams, or codebases,
  with ownership boundaries in between.
- Legacy: old code, no owner, few tests, implicit contracts nobody wrote
  down.
- Hard constraints: backward compatibility, several release streams and
  backports, a customer environment we could not change, licensing or cost
  effects, not breaking other teams.
- Stakes: customer escalation, release deadline, cost to the customer,
  trust.
- Ambiguity: unclear or conflicting requirements, no agreed approach.
- Scale: size of the codebase, number of tests, customers, or runs.
- Persistence: effort that had to be sustained over months.

Why-it-matters ladder. Climb a rung only with evidence; otherwise ask me:
technical consequence -> user / customer consequence -> team or business
consequence.

For debugging and investigation stories, reconstruct in order:
first signal -> expected versus actual behavior -> my first hypothesis ->
what I checked -> what ruled it out -> the clue that changed my thinking ->
how I confirmed the root cause (reproduced it, instrumented it, bisected it,
read the code path) -> the mechanism, step by step -> fix options -> why I
chose this one -> how I validated it -> what I added so it cannot come back
-> what I would do differently.

A "simple" issue can be a strong story. "Worker count kept increasing" is
not "I fixed a worker-count bug". Look for how the anomaly was noticed, why
it was surprising, which interaction between components caused it, and how
I isolated it. Include only what the evidence or I support.

Signals of hidden stories to look for in the evidence:
- reopened tickets
- reverted or backed-out changelists
- review threads with long debates or pushback
- shelved changelists that were never submitted
- scope changes or slipped dates in status reports
- escalations
- the same area fixed more than once
- an approach abandoned partway through

These often hold the disagreement, mistake, pivot, or recovery stories.

## 6. Voice

- First person, spoken, engineer to engineer. It must be easy to say out
  loud.
- Use phrases like: "The main issue was...", "What made this tricky
  was...", "My first guess was...", "Once I looked at...", "The important
  part was...", "I ended up...", "The trade-off was...", "What I took away
  was...".
- Use concrete verbs: traced, reproduced, instrumented, bisected, compared,
  proposed, pushed back, wrote, shipped, backported, validated.
- Banned: leveraged, synergy, spearheaded, orchestrated, pivotal,
  transformational, paradigm, world-class, seamless, robust (unless
  defined), passionate, results-driven. Drop adjectives that have no
  evidence behind them (massive, critical, huge).
- Short sentences. Say numbers the way people say them ("from about a
  hundred and ten down to forty-three").

Audience translation: the listener is a strong backend / distributed-systems
engineer with no background in our domain.
- On first use, give every domain term a plain one-line meaning or an
  analogy, or drop it.
- Each project gets a jargon table: term | plain meaning | needed in the
  short version? (yes / no).

## 7. Structure

Default flow: Context -> Problem -> My role -> Investigation / reasoning ->
Actions -> Decisions and trade-offs -> Result -> Learning.
Do not force it when a story flows better another way.

A learning counts only if it changed how I work. State the old behavior, the
new behavior, and one later example of applying it (ask me if you have no
example).

## 8. Competency tags (career-ladder vocabulary)

Tag each case study only where the evidence supports it. Mark one tag as the
strongest and list any stretch tags separately.

Technical depth | Debugging under uncertainty | System design and trade-offs |
End-to-end ownership | Turning ambiguity into clarity | Influence without
authority | Disagreement and resolution | Customer focus | Delivery under
pressure | Prioritization and saying no | Scope change / pivot | Mistake,
failure and recovery | Raising the quality bar | Simplification | Mentoring
and growing others | Force multiplication (tools, automation) | Learning
something new fast | Cross-team collaboration | Acting on feedback

## 9. Output formats

### A. Evidence ledger (`ledger.md`)
- Timeline table: date | event | source | my involvement.
- My changelists and tickets, each with a one-line plain-English
  description.
- People and teams involved, by role. No names needed.
- Every number found, with where it came from.
- Contradictions between sources.
- Gaps and [MISSING] items.
- No storytelling.

### B. Project one-pager (`one-pager.md`)
1. Project name: the internal name, plus a plain-English name
2. One-line summary with no jargon
3. Timeline, and my title at the time
4. The system in plain words: what it does, who uses it, where it sits;
   plus the jargon table
5. Problem / pain points, and who felt each one
6. Why it was hard (the difficulty lens, with evidence)
7. Team versus me: who owned what
8. What I personally did, as "I ..." bullets, each tagged
9. Key decisions and trade-offs: the decision | the options | why this one |
   what it cost
10. Collaboration: which teams or roles, and why I needed them
11. Result / impact: sourced only, otherwise qualitative
12. What went wrong or got harder than expected
13. What I learned (by the rule in section 7)
14. Possible case studies (3 to 7), each with tags
15. Open questions for me

### C. Case-study catalog (`case-studies.md`)
For each case study, give:
- working title
- what kind of story it really is (for example: "not a bug fix, a
  cross-component root-cause story")
- tags, with the strongest one marked
- why a senior engineer would find it interesting
- my contribution
- evidence strength (strong / medium / thin)
- missing information

Rank the case studies. Say plainly which ones are weak and should be
dropped.

### D. Case-study deep dive (`cs-<n>-<slug>.md`)
1. Headline: one sentence saying why this story is worth hearing
   ("The symptom pointed at X, but the real cause was Y.")
2. Story beats, following the flow in section 7
3. The difficulty sentences (from section 5)
4. One key decision, with the alternative and the trade-off
5. Verbal walkthroughs (speaking pace is about 140 words per minute):
   - 30 seconds, about 70 words: headline, what I did, result
   - 2 minutes, about 280 words: the full story
   - 5 minutes, about 650 words: deeper technical version, for when the
     listener wants detail
6. Mechanism at three zoom levels:
   - one sentence
   - a 30-second analogy for a non-domain engineer
   - a 2-minute technical explanation of the component interaction, with a
     simple mermaid sequence or flow diagram
7. Story beats as a 6-to-8-line skeleton. I memorize the beats, not the
   wording.

### E. Hard questions (`cs-<n>-<slug>.md`, in its own section)
Write 12 to 15 questions a skeptical principal engineer would ask, covering:
- ownership: what exactly did you write, and what did others write?
- depth: how does X work underneath?
- decisions: why not Y?
- root cause: how do you know it was the cause and not a symptom?
- validation: how did you prove the fix worked?
- impact: how was it measured?
- counterfactual: what would you do differently?
- scale: what breaks at 10x?
- people: who disagreed, and how did it end?

For each question, give an answer outline built only from evidence, and mark
where I would be exposed ([MISSING]). List "trap questions": places where the
current story invites a question I cannot answer. Tell me whether to remove
that claim or go find the fact.

### F. Readiness scorecard
Score each line out of 10:
- Technical depth
- Ownership clarity
- Difficulty made visible
- Decision / trade-off quality
- Impact evidence
- Staff-level scope (influence, multiplier, long-term thinking)
- Clear to an outsider
- Natural spoken delivery
- Factual confidence

Give each score a one-line reason, plus the specific fact I would need to
supply to raise it. Never raise a score by inventing anything.

### G. Factual safety check (mandatory at the end of every deep dive)
- Explicit facts, with sources
- Reasonable interpretations
- Missing / needs confirmation
- Statements I must NOT make, and why
- Numbers I can quote, with their exact provenance

### H. Public-safe version (`public-safe.md`)
Write as if for a public engineering blog post or a conference talk:
- no customer names (use neutral descriptions such as "a large
  semiconductor customer")
- no internal codenames that are not public product names
- no ticket or changelist IDs, file paths, or source code
- no proprietary algorithm details and no unreleased roadmap
- internal metric names replaced by what they measure

Keep all of the engineering reasoning, the difficulty, and my role. End with
a list of what you removed or generalized, so I can review it.

## 10. Process discipline

- Work in passes. Do not write polished prose before I confirm the ledger
  and the one-pager.
- When information is missing, ask at most 7 questions per batch, most
  important first, each answerable in one or two lines. In debrief mode,
  ask one at a time.
- Update files in place. Do not create duplicates.
- Run a consistency check across files: the same dates, numbers, and role
  claims everywhere.
- Do not flatter me. If something is weak, say so and say why.

Folder layout:
<PORTFOLIO_DIR>/
  00_RULES.md
  01_inventory.md
  competency-matrix.md
  projects/<slug>/
    ledger.md
    one-pager.md
    case-studies.md
    cs-<n>-<slug>.md
    public-safe.md
```

---

## Part B: Pass prompts (paste one at a time)

### Pass 0: Inventory (Agent mode)

```text
@00_RULES.md
Read the rules first. Then do a read-only survey of the allowed sources for
<PERIOD>. Do not write any narratives yet.

Create 01_inventory.md with:
1. Every project or initiative I worked on. For each: date range, my role at
   the time, whether I owned it / was primary contributor / contributed /
   supported, and which sources cover it (with evidence-pointer IDs).
2. "Hidden story signals" from section 5 of the rules (reopened tickets,
   reverted CLs, long review debates, shelved CLs, escalations, slipped
   dates, abandoned approaches). For each: what it is, which project it
   belongs to, and what kind of story it might hold.
3. Projects where the employer, period, or my role is ambiguous. List them
   so I can confirm.

Then recommend which 3-4 projects to deep-dive first, and ask me to confirm.
```

### Pass 1: Evidence ledger (Agent mode)

```text
@00_RULES.md
Project: <PROJECT>. Build projects/<slug>/ledger.md using format 9A.
Read the relevant ticket comments and changelist descriptions in full. They
usually hold the real investigation history. No storytelling. Tag every line
[SRC]/[ME]/[INFER]/[MISSING]. Finish with the contradictions and the gaps.
```

### Pass 2: Debrief me (Ask or Agent mode)

```text
@00_RULES.md @projects/<slug>/ledger.md
Act as a sharp senior engineer debriefing me on <PROJECT>. Ask ONE question
at a time and wait for my answer.
- Prioritize questions that unlock: what was actually hard, what I tried
  first, what I saw that others missed, decisions and their alternatives,
  exactly which parts I personally did, and how results were measured.
- When my answer is vague, follow up ("What did you actually see?", "What
  did you try first?", "Who decided that?", "How did you know?").
- Stop after about 15 questions or when I say "done".
Then add my answers to ledger.md tagged [ME], and show me what changed.
```

### Pass 3: One-pager (Opus)

```text
@00_RULES.md @projects/<slug>/ledger.md
Write projects/<slug>/one-pager.md using format 9B.
Apply the difficulty lens (section 5) and the three-layer separation
(section 4) carefully. Put any [MISSING] items in "Open questions for me"
rather than filling them.
```

### Pass 4: Case-study discovery (Opus)

```text
@00_RULES.md @projects/<slug>/one-pager.md @projects/<slug>/ledger.md
Find the 3-7 strongest case studies hidden in this project and write
case-studies.md using format 9C. Don't write polished answers yet.
For each, tell me what kind of story it REALLY is. Example: "this isn't a
bug fix, it's a cross-component root-cause story". Say which ones are weak
and why. Rank them.
```

### Pass 5: Deep dive (Opus)

```text
@00_RULES.md @projects/<slug>/ledger.md @projects/<slug>/one-pager.md
Develop case study #<N> into cs-<n>-<slug>.md using formats 9D, 9E, 9F and 9G.
- Highlight my reasoning and why the problem was hard.
- Keep the walkthroughs natural to say aloud, at the word counts given.
- Do not exaggerate. If a beat needs a fact we don't have, write
  [MISSING: ...] in place and ask me instead of smoothing it over.
```

### Pass 6: Skeptical review drill (Ask mode)

```text
@00_RULES.md @projects/<slug>/cs-<n>-<slug>.md
Act as a skeptical principal engineer on a review committee hearing case
study #<N>. Ask me ONE hard question at a time, and do not help me answer.
After each answer:
- score it 1-5
- point out what was vague, unsupported, or over-claimed
- say what a stronger answer would include, using only facts in the
  ledger. If the fact isn't there, say so.
After about 8 questions, summarize my weak spots, update the hard-questions
section of the file, and list any facts I should go and find.
```

### Pass 7: Public-safe version (Opus or Sonnet)

```text
@00_RULES.md @projects/<slug>/
Write projects/<slug>/public-safe.md using format 9H, covering the one-pager
and the top case studies (headline, 2-minute walkthrough, mechanism
explanation, key decision).
List everything you removed or generalized at the end.
```

### Pass 8: Batch the rest (Sonnet)

```text
@00_RULES.md
For projects <A>, <B>, <C>: build ledger.md (Pass 1), then one-pager.md
(Pass 3), from the sources.
- Do not create deep dives.
- Do not invent anything to fill the template.
- Leave [MISSING] items as open questions, and give me the combined list
  of questions at the end.
```

### Pass 9: Competency matrix and gaps (Opus)

```text
@00_RULES.md @projects/
Build competency-matrix.md:
- rows: the tags from section 8
- columns: every case study written so far
- each cell: strong / medium / none, with a one-line reason
For every tag with no strong case study:
- look through the evidence for possible moments, using the "hidden story
  signals" in section 5
- tell me where they are
- ask me about them
I especially need solid examples for: Disagreement and resolution;
Mistake, failure and recovery; Influence without authority; Acting on
feedback; Prioritization and saying no.
```

### Pass 10: Consistency check (Sonnet)

```text
@00_RULES.md @projects/
Check every file for consistency:
- employer and time period per project
- dates
- numbers and their units
- my role claims
- team versus me attribution
- the same story told differently in two places
Report the conflicts in a table and propose fixes. Do not apply any fix
until I approve it.
```

---

## Part C: Incident reconstruction (the worker-count issue)

```text
@00_RULES.md
I want to reconstruct one engineering incident as a debugging case study:
the issue where the worker count kept increasing unexpectedly.

Step 1. Find it. Search the allowed sources for it: tickets including all
comments, changelist descriptions, review threads, the weekly status doc,
saved plans, and knowledge-system docs.
Start with these search terms (adjust as you learn):
- worker count, workers increasing, extra workers, worker leak
- spawn, respawn, orphan, zombie, not cleaned up
- grid, farm, LSF, dynamic orchestration, num_workers
- license checkout, cores per license, restore, re-launch
Report what you found, with source pointers, BEFORE writing anything.
If you find several candidate incidents, list them and ask me which one.

Step 2. Build the incident timeline in projects/<slug>/ledger.md:
- first signal: who noticed, and how
- expected versus actual behavior
- impact while it was happening
- hypotheses in the order they were considered, including the wrong ones,
  with the evidence for and against each
- the root cause, and the mechanism as numbered steps showing how the
  cause produced the symptom
- the fix options considered, the fix chosen, and why
- validation
- release streams and backports
- prevention (tests, harness, guards)
- follow-ups
Tag every line [SRC]/[ME]/[INFER]/[MISSING].

Step 3. Debrief me ONE question at a time on everything still [MISSING].
Focus on:
- what I saw first
- what I initially believed
- what made me doubt it
- what I did that someone else would not have thought to do
- why the obvious fix would have been wrong
- what a user or customer would have experienced (extra compute, held
  licenses, slow or stuck runs, cost). Only what I confirm.

Step 4. Write cs-<n>-<slug>.md using formats 9D-9G. Pay special attention
to:
- why the symptom was misleading
- the distance between where it showed up and where it started
- why the naive fix would have hidden or worsened it
- the stakes, but only if sourced or confirmed by me
- the one insight that cracked it
Open with a one-sentence headline saying why this is a story about
root-causing across components, not "fixing a counter". Use that framing
only if the facts support it.

Step 5. Write the public-safe version (format 9H) of the headline, the
2-minute walkthrough, and the three-level mechanism explanation.
```
