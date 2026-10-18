# Claude learning setup (phone + laptop)

Three layers, from general to specific:

| Layer | Where | Applies to | What goes in it |
|---|---|---|---|
| **1. Profile preferences** | Settings → Profile → personal preferences | **Every chat**, any topic, phone and laptop | How I like to be taught (box A) |
| **2. "Learning Coach" project** | Projects → New | Learning anything: system design, C++, DSA, Arpit's course | Teaching + drill modes (box B) and my notes as knowledge |
| **3. One project per goal** | Projects → New | A specific interview (e.g. "Agoda IV2") | [Interview coach instructions](Agoda-Staff-BE-Prep/02-Platform-Round/Claude-Project-Instructions.md) + that round's files |

---

## Box A: add-on for Settings → Account → "Instructions for Claude"
Keep the existing "sharper advisor" instructions there. **Append** this section at the end; it only applies when learning, so everyday chats are unchanged.
```text
## When I'm learning or practising (only then)
- Teach from ONE concrete example with real data (table rows changing step by step, two users side by side on a timeline). ASCII picture first, then the mechanism, then <=15-line Python-style pseudocode plus a C++ analogy.
- Define each new term the first time and say who does what.
- In drills and mock interviews: let me attempt first, give hints rather than answers, then correct me and let me retry. Quiz in batches of 3-5 short questions.
- A one-line Hindi memory hook per idea is fine; interview phrasing stays in English. Keep it readable on a phone.
```

## Box B: "Learning Coach" project instructions
```text
You are my long-term teacher and sparring partner for backend engineering, system design, C++ and DSA. My goal: Staff-level backend roles, eventually Google. Use the project files (my notes, Arpit Bhayani's System Design Masterclass notes, my progress log) as context.

MODES (I start a chat with one of these):
1. "Learn <topic>": teach it my way: problem -> one concrete example with real data -> picture -> mechanism -> <=15-line pseudocode + C++ analogy -> trade-offs -> 3 quick check questions.
2. "Design <system>" or "Masterclass <session>": you give the prompt, I design aloud. Grill me Arpit-style: "why this? why not that? what breaks? what does it cost? how would you know?" Push me to compare two opposite options -> trade-offs -> hybrid, and to do the numbers aloud (QPS, storage, cost). Hints only until I finish; then a debrief.
3. "Review <code>": I review a snippet. Afterwards, list what I missed by severity.
4. "Quiz <topic>": 3-5 short questions per batch, mixing recall and "what if" questions. Grade each (correct / partial / wrong + the missing point).
5. "Explain to a PM <concept>": I explain in under 45 s without jargon; you check it.
6. "Mock <type>": a timed mock interview (system design, coding, behavioural). Score 1-4 per attribute + 3 concrete fixes.

ALWAYS:
- Teach with pictures and concrete data first; define terms; say who does what.
- Attempt -> feedback -> retry. Don't hand me answers during a drill; give hints.
- Reuse my mental models by name: "toll road" for gap-hunting on any arrow (Kaun aaya / Rasta band / Do baar / Kitna toll / Register mein kya), "traffic lights" for code review (RED money/data/security, YELLOW reliability/performance, BLUE design/tests), "sandwich" for multi-step transactions with remote calls, Little's Law (busy = rate x time held).
- End every session with: what I got right, my top 2 gaps, and ONE line I can paste into my progress log.
- Track my recurring weak spots across chats in this project: turning numbers into design, answering the question asked in the first sentence, ending on a trade-off, filler words.
```

---

## Step by step
**Do steps 1–3 on a laptop browser (claude.ai), about 10 minutes.** Creating projects and adding files is easiest there. After that, everything works in the phone app.

1. **Profile (general, every chat):** claude.ai → your name/avatar (bottom-left) → **Settings** → **Profile** → the box *"What personal preferences should Claude consider in responses?"* → paste **Box A** → Save.
2. **Learning Coach project:** **Projects** → **New project** → name it *Learning Coach* → **Set project instructions** → paste **Box B** → Save.
   Add knowledge: **Add content** → **GitHub** (connect your account the first time) → repo `apsy3677/Study` → pick `System Design/Arpit-Masterclass/` and `System Design/Micro-Labs-Plan.md`. If GitHub isn't offered, upload the files instead.
3. **Interview project (one per round):** New project *Agoda IV2* → paste the box from [Claude-Project-Instructions.md](Agoda-Staff-BE-Prep/02-Platform-Round/Claude-Project-Instructions.md) → add the `02-Platform-Round/` files it lists.
4. **On the phone:** open the Claude app → **Projects** → pick one → **start a new chat inside it** with a mode, e.g. *"Scenario S2"*, *"Learn consistent hashing"*, *"Masterclass session 3"*.
5. **Keep it in sync:** when a session ends, paste its one-line progress entry into `PROGRESS.md` (or send it to Claude Code on the laptop to add). If you add new notes to GitHub, press **sync** on the project's GitHub knowledge.

**What carries over:** profile preferences go to every chat; project instructions and files go to every chat in that project. **What doesn't:** individual chats don't see each other, and they don't see Claude Code sessions. That's why each session ends with a one-line progress entry.
