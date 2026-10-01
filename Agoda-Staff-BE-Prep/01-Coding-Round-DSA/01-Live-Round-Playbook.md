# The Agoda Live Coding Round: Playbook

> Read §0–§4 and §7 on Day 1 morning. Re-read §7 and §8 the night before the interview.
> Agoda grades **4 areas**: understanding, coding efficiency, testing, communication. The algorithm is maybe 40% of the score. The rest is *how* you get there, and that part is fully trainable in 3 days.

---

## 0. The rubric → behaviours an interviewer can actually observe

| Agoda's words | What they write down | What you do (visibly) |
|---|---|---|
| "Clarify requirements, discuss possible solutions, choose the most efficient one" | Asked the right questions? Considered alternatives? Picked optimal? | 3–5 targeted questions. Restate with an example. **Brute force in one sentence → better idea → complexity → get a nod.** |
| "Clean and working code confidently" | Readable? Structured? Hesitant? | Small helper functions, names that say what they hold, no dead code. Steady pace: narrate *blocks*, not keystrokes. |
| "Advanced features and syntax of the selected language" | Idiomatic C++ or "C with classes"? | Structured bindings, lambdas, `priority_queue<…, greater<>>`, STL algorithms, `const&`, `long long` where needed (§6). |
| "Efficient in debugging" | Random prints, or a hypothesis? | §5 protocol: read the failing case → predict → one targeted print → fix → re-run **all** tests. |
| "Thoroughness… wide range of conditions… justify your choice of test scenarios" | Tested only the sample? Said *why*? | §4 matrix. **Write tests before coding.** Say the reason for each one ("this hits the tie branch"). |
| "Explain clearly and concisely… minimal prompting" | Did I have to drag it out of them? | Think aloud in summaries: "Plan: X. Invariant: Y. Now coding the shrink step." No silent stretches longer than 30 s. |
| "Proactive in introducing new topics or ideas" | Senior signal | After passing, volunteer a follow-up: streaming input, scale, a service version, concurrency, a better complexity (§3F). |

---

## 1. The 60-minute clock (2 problems)

```
00–05  Hello + short intro (technical, 45 s). If they open a resume chat, keep answers to 60 s each.
05–30  Problem 1   (25 min budget)
30–55  Problem 2   (25 min budget)
55–60  Your questions (have 2 ready: "what does your team own?", "how do you test in production at Agoda's scale?")
```

**Per problem (25 min):**

| Phase | Minutes | Output |
|---|---|---|
| A. Understand | 0–4 | Restated problem, answers to clarifying questions, one example worked by hand |
| B. Approach | 4–8 | Brute force (1 sentence) → optimal idea → invariant → complexity → interviewer agrees |
| C. Code | 8–20 | Compiles early, helpers extracted, narrated at block level |
| D. Test | 20–24 | Sample + your edge cases, each with a reason; all pass |
| E. Follow-up | 24–25 | You raise one: optimization, scale, stream, service |

**Clock rules**
- At **18 min** with no code running on problem 1, say: *"I'll get this version passing first, then discuss the optimization."* Ship something that runs.
- **Never** let problem 1 eat more than 32 min. A complete problem 2 matters more than a perfect follow-up on problem 1.
- If problem 2 is easy, finish it fully *and* test it well. Agoda's "Strong Hire" reports finished early and chatted.

---

## 2. Phase scripts (say these, adapted)

### A. Understand (≤ 4 min)
> "Let me restate it: given ___, return ___. Before I solve it, a few questions."

Pick the ones that matter. Each one changes your code:

| Question | What it decides |
|---|---|
| "How large can n be? What's the value range? Negatives?" | O(n log n) vs O(n²). `int` vs `long long`. Sentinels. |
| "Can the input be empty, or a single element?" | Guard clauses, `front()`/`back()` safety |
| "Duplicates? Ties: which answer should I return?" | `<` vs `<=`, stable ordering, first vs last |
| "Is it sorted? May I modify the input?" | Sorting a copy vs in place |
| "Output: indices or values? Order? Any valid answer?" | The return format, and how tests compare |
| "Is the input guaranteed valid? (balanced parentheses, known atoms)" | Validation code vs a stated assumption |
| **Edge semantics of the story**: "If a plane lands exactly when I'm ready to shoot, is that a loss?" | The exact comparison in the core loop |

Then: *"Let me run your example by hand… and one of mine: ___."*

### B. Approach (≤ 4 min)
> "Brute force: try every ___, that's O(___). The repeated work is ___. With a **[pattern]** I can do it in O(___). The invariant is: ___. Space O(___). Shall I code that?"

- If two approaches are close, name the trade-off ("heap is O(n log n) and simple; counting is O(n) with more code"), choose one, and say why.
- **Wait for the nod.** Coding the wrong idea for 10 minutes is the most expensive mistake there is.

### C. Code (10–14 min)
1. Write the **signature + helper stubs** first, then **Run once** (HackerRank compiles). This kills typos while they're cheap.
2. Fill in the helpers. Narrate at block level: *"This helper answers: can we ship with this capacity in `days` days? It's greedy: fill each day until the next package doesn't fit."*
3. Names: `left/right`, `windowStart`, `arrival`, `freeRooms`, `canShip`. Not `a1`, `tmp`, `ff`. (Your Uber feedback.)
4. Keep functions short. Extract `canShip(capacity)`, `readCount(i)`, `expand(l, r)`.
5. Before pressing Run: the **60-second checklist** in §7.

### D. Test (4–5 min). Agoda scores this separately
> "I'll test the given example, then the edge cases I listed earlier, and say why for each."

**The test matrix.** Cover one case per relevant row and **say the reason**:

| Category | Why it catches bugs | Example |
|---|---|---|
| Empty / minimal | Loop bounds, `back()` on empty, `size() - 1` underflow | `[]`, `""`, one element |
| Duplicates / ties | Strict vs non-strict comparisons | `[2,2,2]`, two meetings ending together |
| Exact boundary of the rule | The edge semantics you clarified | a plane arriving at minute `i`; drop-off at a pick-up stop |
| Extremes | `int` overflow, `INT_MAX` sentinels | values of 1e9, sums > 2³¹, `INT_MAX` in input |
| Shape | Nesting, all-same, sorted, reverse-sorted | `((CH)2O)3`, `[5,4,3,2,1]` |
| Invalid (if in scope) | Robustness discussion | unbalanced `(`, unknown atom |

**Writing tests fast on HackerRank.** If you get a blank editor or a custom `main`:

```cpp
int main() {
    struct Case { string formula; long long expected; };
    const vector<Case> cases = {
        {"CH4", 16}, {"H(CH4)2", 33},  // given
        {"Mg(OH)2", 42},               // two-letter atom + group count
        {"((CH)2O)3", 102},            // nesting
        {"", 0},                       // empty
    };
    for (const auto& [formula, expected] : cases) {
        long long got = moleculeWeight(formula, weights);
        cout << (got == expected ? "PASS " : "FAIL ") << formula << " -> " << got << " (want " << expected << ")\n";
    }
}
```
A table of cases with a comment per row *is* the "justify your test scenarios" evidence, and it's written down.

### E. Follow-up (proactive: the senior signal)
After all tests pass, **you** raise one or two:
- **Complexity:** "This is O(n²); with ___ it becomes O(n log n)." (or "this is optimal because each element is pushed and popped once")
- **Scale / streaming:** "If the prices come as a stream, I'd keep ___ incrementally."
- **Service view (Agoda is a backend shop):** "As an API, I'd cache parsed formulas, validate input, return 400 on unbalanced parentheses."
- **Concurrency:** "If many threads book rooms, the map needs a lock, or I'd partition by hotel."

Per-pattern follow-ups are listed in `02-Pattern-Cards.md`.

---

## 3. Stuck protocol (the 3-minute rule)

1. **Re-read the input and ask.** Run the decision tree in AMD `02-Patterns/00-Pattern-Map.md` (input shape → ask → pattern).
2. **Solve a tiny instance by hand** and watch what *you* do. That's usually the algorithm.
3. **Say the brute force and offer to code it** if more than 10 minutes remain. A working O(n²) plus a clearly explained O(n log n) beats a broken optimal. (The Aug 2025 candidate passed brute-force palindromes and still got "strong coding skills".)
4. **Take hints well:** *"Good point. So if I keep a stack of the open groups, a ')' multiplies the top… let me adjust."* A hint isn't fatal. Silence is.

---

## 4. HackerRank CodePair: the environment

- **Language:** pick **C++** (C++17 or C++20 if listed; every solution here compiles as C++17).
- You'll see a shared editor with syntax highlighting, **little or no autocomplete**, a **Run** button and custom input. The interviewer watches you type live.
- The problem may arrive as a **function stub with prepared I/O and hidden tests**, or as a **blank editor**. Be ready for both:
  ```cpp
  int n; cin >> n; vector<int> a(n); for (auto& x : a) cin >> x;   // array
  string line; getline(cin, line);                                    // whole line
  ```
- `#include <bits/stdc++.h>` works on HackerRank (GCC). Use it to save time. That's fine.
- **Practise in the real editor at least twice** (Mock 3 and Mock 5): hackerrank.com → Prepare → any medium problem → C++.
- Setup check the evening before: camera, mic, a stable connection, a charger, water. Close Slack and email (screen sharing may be on).

---

## 5. Debug protocol (efficient, visible, calm)

1. **Read the failing case** and **predict** the correct intermediate state at the first suspicious step.
2. Add **one** print at the invariant (window bounds, stack contents, `lo/hi/mid`). Not ten.
3. Say it: *"Hypothesis: I shrink one step late because I check before incrementing."*
4. Fix → **re-run all tests**, not just the failing one → remove the print.

The bugs you *will* make under pressure (from your history and these patterns):
`<` vs `<=` · `size_t` underflow in `n - 1` · `int` overflow · a `}` closing the wrong block · copy-paste symmetric code (`left` twice) · `mid` infinite loop · popping an empty stack · inserting into a `map` with `operator[]` while iterating it.

---

## 6. C++ features worth showing (naturally, never forced)

| Feature | Natural use in these problems |
|---|---|
| `auto` + structured bindings | `for (const auto& [name, count] : counts)` · `auto [freeAt, room] = busy.top();` |
| Lambdas as helpers and comparators | `auto canShip = [&](long long cap) {…};` · `sort(v.begin(), v.end(), [&](int x, int y) {…});` |
| Heaps with a comparator | `priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> busy;` |
| STL algorithms | `accumulate(…, 0LL)` · `max_element` · `count` · `lower_bound`/`upper_bound` · `partial_sum` · `iota` · `unique` + `erase` · `nth_element` |
| `std::array<int, 26> freq{}` | Value-initialized counters; `have == need` compares whole arrays (W5) |
| String tools | `substr`, `find_first_not_of`, `append(n, ch)`, `to_string`, `reserve` |
| Correctness hygiene | `const&` parameters, `static_cast`, `long long` sums, `isdigit(static_cast<unsigned char>(c))` |
| Mention when relevant | `std::optional` for "maybe" results · `std::string_view` for zero-copy parsing · C++20: `map.contains`, `std::ranges::sort` |

**Avoid at Staff level:** macros (`#define int long long`, `rep(i,n)`), global arrays, one-letter names beyond loop indices, `using ll = long long` *everywhere* (fine once). These are competitive-programming habits, and they hurt the "clean code" score.

**Why C++ (not Java) for this round:** it's your fastest language, the AMD toolkit is in C++, and Agoda grades the idioms of *your chosen* language. Say once at the start: *"I'll use C++, it's my daily language."* (Agoda's backend is JVM. That fits the Platform round, not this one.)

---

## 7. Your 60-second pre-Run checklist (from your own interview history)

- [ ] **Names** say what they hold (no `a1`, `tmp2`, `ff`)
- [ ] **Symmetric code:** left/right and i/j copies. Did I paste `left` twice? *(Cadence R1 bug)*
- [ ] **Loops:** start, end, step. `i + 1 < n` (not `i < n - 1` with `size_t`)
- [ ] **Empty input** returns the right thing without touching `[0]` or `back()`
- [ ] **Overflow:** sums, products, end times, `x * k` → `long long`
- [ ] **Strict vs non-strict** comparisons match the clarified semantics
- [ ] **Containers:** `top()`/`back()` only when non-empty. No `map[]` insertion while iterating that map.
- [ ] **Every path returns** a value. Typos: `priority_queue`, `greater`, `return` *(Google R2 / Cadence)*

---

## 8. Phrases that keep the conversation smooth (minimal prompting)

- **Start:** "Let me make sure I have the input and the edge semantics right first."
- **Before coding:** "I'm confident in O(n log n). I'll code it, then test the edge cases I listed."
- **While coding:** "This helper checks feasibility for one capacity. The outer loop binary-searches the capacity."
- **Spotting a bug:** "Wait, this breaks when the window is empty. Fixing that before I run."
- **After passing:** "All pass. Time O(…), space O(…). If this were a stream / a service / multi-threaded, I'd…"
- **Behind on time:** "To be efficient: I'll code the O(n²) version that I know is correct, and explain the O(n) improvement."
- **When given a hint:** "That helps. Then the invariant becomes… let me update the loop."
