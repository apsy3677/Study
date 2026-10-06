# The worker-count story

> **This repo is public.** Don't write real details (customer names, ticket IDs, internal mechanism specifics) into this file. Answer the questions in chat with Claude, or keep a private copy outside the repo.

## Why this story is worth building

A worker count that keeps growing sounds like a small bug, and if you tell it as "I fixed a worker-count bug" it will land like one. Told properly, it is usually a strong story. It shows debugging under uncertainty and how well you understand the system. In practice that means:

- a symptom that showed up far from its cause
- nothing obviously failing, so nothing caught it
- an obvious fix that would have hidden the problem
- you working out how two parts of the system interact

That is the debugging story every round asks for: hardest bug, a problem you solved without all the information, a customer-impacting issue.

The plan has two tracks, and the order matters:

1. **At home first: brain-dump from memory** (step 1 below, about 20 minutes). If you read the tickets first, your memory gets anchored to what was written down, and the written record rarely says what you thought or what you tried that didn't work.
2. **Then at work: pull the evidence** with Part C of the [Work-Prompt-Pack](Work-Prompt-Pack.md#part-c-incident-reconstruction-the-worker-count-issue). That fixes the dates, the mechanism and the release streams, and fills the gaps.

Then merge the two tracks and rehearse.

## Step 1: brain-dump (answer in 1–3 rough lines each)

**Setting**

1. Which product, flow or mode was this in, and roughly when (year, quarter, release)?
2. What is a "worker" here, in one plain sentence? Is it a process or a thread, local or on the grid? Who starts workers, and who is supposed to stop them?
3. How many workers did you expect, and how many did you see? What was the pattern over time: growing per run, per restore, per proof, or never coming down?

**Detection**

4. Who noticed, and how? A customer report, a regression, grid or license usage, CI, or your own testing?
5. Why was it surprising? What should have stopped it from happening?

**Investigation**

6. What was your first guess, and what made you drop it?
7. What did you look at? Logs, `ps`/`top`, `bjobs`, license server usage, a debugger, reading the code, added prints?
8. What was the clue that changed your thinking?
9. Could you reproduce it locally? If not, what did you do instead?

**Root cause**

10. In 2–3 steps, what caused what? Which two components or phases were interacting?
11. Why hadn't anyone caught it before? A rarely used path, a new feature, a recent change, only with certain settings?

**Fix**

12. What did you change? What was the *obvious* fix, and why didn't you do that?
13. How did you validate the fix? Did you add a test or a harness check?
14. Which release streams did it ship to?

**Stakes and you**

15. What did the extra workers cost: grid slots, licenses, memory, runtime, the customer's money? Only include what you actually know.
16. Which part was only you? What did you figure out that others hadn't?
17. Who else was involved, and what did they do?
18. What do you do differently now because of this?

## Things to check: my guesses from your profile, not facts

Your notes mention several areas that *might* be connected. I don't know which, if any, apply. Use them only to jog your memory:

- **Dynamic Orchestration worker licensing**, which is in your licensing-stack list.
- **The cores-per-license lift** (Base 1→4, Elite 4→12). If worker count and license checkout are tied together, a change here could change how many workers start or how many licenses each one holds.
- **DPV's worker model.** An older, unverified note mentions "DPV with its 4 workers".
- **Save/restore and `report_grid_usage` in restored sessions.** Did restore re-launch workers without reclaiming the old ones?
- **The T0..T6 license-probe harness.** Did it help you see this, or did this issue help motivate building it?
- **Multi-threaded worker queues** in the C++ code, if this was a thread pool rather than processes.

## Step 2: the shape of the finished story

Fill the blanks only with true things. Memorize the beats, not the wording.

| Beat | Sentence shape |
|---|---|
| Headline | "This was a debugging problem where the symptom was ___, but the actual cause was ___ in ___. The hard part was ___." |
| Context (2 sentences, plain words) | "[Product] splits a run across worker [processes] on the customer's [grid]. Each worker [holds a license / takes a grid slot / uses ___]." |
| Symptom | "We were seeing ___ workers where we expected ___, and it got worse whenever ___." |
| Why it was tricky (choose the 2 that are true) | "Nothing failed. The results were correct, so no test caught it. The only sign was ___." / "The count showed up in ___, but it was decided in ___, which is a different [process / phase]." / "It only happened when ___, so I couldn't reproduce it with ___." / "The obvious fix was to cap the count at ___, but that would have hidden ___." |
| Investigation | "My first guess was ___. I checked ___, and that ruled it out because ___. What changed my thinking was ___." |
| Root cause | "It turned out that ___ led to ___, which led to ___." |
| Fix and trade-off | "I changed ___. The alternative was ___. I didn't go that way because ___." |
| Validation and prevention | "I verified it by ___, and I added ___ so this gets caught automatically now." |
| Result | "___" (a number, or a concrete outcome such as "the customer's runs went back to N workers") |
| Learning | "Since then, whenever I see ___, the first thing I check is ___." |

A 2-minute version is about 280 spoken words. Keep the context to about 20 seconds. Spend most of the time on "why it was tricky" and "what changed my thinking", because that is where the signal is.

## Step 3: follow-up questions to prepare

- How did you know it was the root cause and not another symptom?
- Why didn't the existing tests catch it?
- What exactly is a worker: a process or a thread? Who owns its lifecycle?
- Why not just cap the worker count?
- How did you reproduce it?
- What was the impact on the customer, and how did you put a number on it?
- What did you do to make sure this *class* of bug can't come back?
- What would you do differently?
- At 10× the scale, what else would break?
- Which part of this did you do yourself, and which part did others do?

## Step 4: next

Paste your step-1 answers into chat, rough is fine. Claude will draft the 30-second, 2-minute and 5-minute versions, flag the weak spots, and then question you on it.
