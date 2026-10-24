# LeetCode code audit (Mar 2023 – Oct 2026)

Based on 1,620 submissions and their code: 277 problems on your list plus 118 other problems on the account.
Every number here comes from `LeetCode-History.xlsx` and the `code/` folder.
The same data is in `data/*.csv` for other tools and agents: problems, submissions, pattern scorecard, re-do queue and monthly activity.

Two terms used throughout:
- **First-try**: the first submission on that problem was Accepted.
- **Cold revisit**: you came back to a problem 7 or more days after last solving it. Did the first submission of that session pass?
  This measures what you *remember*, not what you just watched in a video.

Caveat: much of the list follows a video-course order (DP, graphs), so a first-try pass right after watching the explanation proves little.
The cold-revisit column is the honest one. Rows with fewer than 4 revisits are only a hint.

---

## 1. Scorecard

```
                         first-try   cold revisit (n)     verdict
Grid BFS/DFS                92%        77%  (13)          STRONG
Intervals & sweep line      64%        89%  (18)          STRONG (learned from your mistakes)
Linked list                 83%        86%  (7)           STRONG
Binary search (classic)     76%        81%  (31)          STRONG, your most-practised pattern
Monotonic stack / deque     71%        83%  (6)           STRONG
Design (LRU, hit counter)   73%       100%  (11)          STRONG
Binary tree DFS             91%        75%  (12)          GOOD
Backtracking                69%        74%  (23)          GOOD
DP knapsack / stocks       100%        50%  (4)           GOOD state design, recall untested
--------------------------------------------------------------------------------------
Heap / Top-K                50%        62%  (21)          WEAK: ties and heap direction
DP grid / 2D                45%        62%  (8)           WEAK: base cases, 1x1 grid
Binary search on answer     60%        60%  (5)           WEAK: bounds and 64-bit
DP strings (LCS/edit/match) 40%        33%  (3)           WEAK
Topological sort           100%        38%  (8)           DECAYS: knew it, forgot it
DP on trees                100%        33%  (3)           DECAYS
Trie                        75%         0%  (4)           DECAYS (Word Search II, 0 of 4)
Bitmask DP                   0%        50%  (4)           GAP: Parallel Courses II never accepted
```

The overall shape: **you learn patterns fast and solve well right after learning them. Retention is the problem.**
Of 302 cold revisits, 71% passed on the first submission. The misses cluster in patterns you only studied in one burst.

> Hindi hook: *Seekhna fast hai, yaad rakhna kamzor. Revisit hi asli test hai.*

---

## 2. Six failure types, with your own code

### 2.1 Debugging through the judge (the biggest lever)

- 60% of your resubmits after a failure come within 3 minutes.
- The median change between a failed attempt and the next one is 4 lines.
- The same failing input was resubmitted up to 5 times: Alien Dictionary ×5, Basic Calculator III ×5, Minimum Time to Complete Trips ×4.

One real night, Closest BST Value, 17 Nov 2023:

```
03:14  WA   if target < root.left        <- comparing a float with a node object
03:14  WA   (same input, branch swapped)
03:19  WA
03:21  WA   + print(closest)
03:21  WA   now compares root.val; tie case 4.5 -> expected 4, got 5
03:22  RE   key=(lambda x: ..., x)       <- typo in the fix
03:23  AC   key=lambda x: (abs(target-x), x)
-- 7 days later --
04:06  WA   same kind of tie: 3.5 -> got 4, expected 3
04:08  WA   4.5 -> got 5 again
```

Each fix was one comparator flip, made without tracing the failing input by hand. Two other patterns:
- About 24% of all your submissions land between midnight and 5 am. Acceptance then is 62%, against 67% overall.
- When stuck, you sometimes paste in a reference solution. Examples: Wildcard Matching attempt 2, Minimum Time attempt 6, and the first C++ Basic Calculator II. The style changes completely between attempts.
  That's fine for learning, but count those problems as *seen*, not *solved*, until you pass a cold revisit.

**The 90-second rule:** after any Wrong Answer, copy the failing input and trace it on paper (or in a comment) until you can say which line produced the wrong value. Only then resubmit.
C++ analogy: treat the judge like a CI run, not a REPL. You don't push a 4-line guess to CI five times; you reproduce the failure locally first.

> Hindi hook: *Judge debugger nahi hai. Pehle haath se trace, phir submit.*

### 2.2 Tiny inputs break you

Real failing inputs, all with 1 element or near-empty:

```
house-robber-ii      [1]            got 0, expected 1
minimum-path-sum     [[1]]          got 2, expected 1
binary-search        [5], 5         got -1
word-search          [["a"]], "a"   got false
longest-pal-substr   "a"            got ""
max-path-sum         [-3]           got 0      (best initialised to 0, not -inf)
course-schedule      1, []          got false
meeting-rooms-ii     [[2,7]]        got 0
first-missing-pos    [1]            got 1, expected 2
basic-calculator-ii  "42"           got 6
```

**Pre-submit checklist (30 seconds, every time):**
1. Empty or 1 element.
2. All values equal / all duplicates.
3. Extremes: INT_MIN, INT_MAX, 1e9 values, all negative.
4. Ties: does the problem say which one wins?
5. Unsorted input when your mental picture was sorted.

> Hindi hook: *Chhota input pehle, bada baad mein.*

### 2.3 Integer range (15 overflow runtime errors across 11 problems)

The clearest example is Minimum Time to Complete Trips, 16 Mar 2023. Five wrong answers in 10 minutes, all on the same input:

```cpp
long long tripsInTime(int t, vector<int>& arr)   // t is int
...
long long mid = low + (high - low) / 2;          // mid is up to ~1e14
long long trips = tripsInTime(mid, time);        // mid silently narrowed to int
```

You flipped `<` and `<=` and `mid` and `mid-1` four times. The search template was fine; the bug was the `int t` parameter.
Others from your code:
- Arrows: `INT_MIN - 5`.
- Path Sum III: `2e9 + 1e9`.
- Maximum Width of Binary Tree: `2 * idx`.
- Cherry Pickup: adding two INT_MIN "minus infinity" sentinels together.

Fixes:
- Any value that is a *count × size* or a *sum of up to 1e9 values* is `long long` from the first line.
- Sentinels should be `-1e9` (or `LLONG_MIN / 4`), never INT_MIN when you add to them.
- Compile locally with `-Wconversion`: it flags exactly the `int t` narrowing.

> Hindi hook: *long long ko int mein mat thoonso.*

### 2.4 Duplicates and tie-breaking

- 3Sum `[0,0,0,0]` returned `[[0,0,0],[0,0,0]]`.
- Subsets II, Permutations II and Combination Sum II all failed on duplicates.
- K Closest Points, Find K Closest Elements and Vertical Order Traversal failed on equal distances or columns.
- Closest BST Value failed on an exact half (4.5).
- Accounts Merge put the name after the email.

The rule is always written in the problem statement. You read it, but you didn't encode it.
**Habit:** before coding, write the comparator tuple as a comment, e.g. `# order by (dist, value)` or `# column, row, value`. In C++ that is a `std::tie(a.d, a.v) < std::tie(b.d, b.v)` comparator. Write it before the algorithm.

> Hindi hook: *Barabari ho to kaun jeetega, pehle likh lo.*

### 2.5 Recall decay on patterns studied once

- **Alien Dictionary.** Correct on 25 Mar 2023. The same evening you "optimised" it, dropped the `break` after the first differing character, and got a wrong answer. Then it failed on cold revisits in Apr, Oct and Nov 2023 (7 failed attempts in total), including the prefix rule `["abc","ab"] -> ""`.
- **Binary Tree Maximum Path Sum.** Clean in C++ in Oct 2023. In Python in Jan 2024 you had 6 failed attempts in 4 minutes, because you no longer remembered the one key line:

```python
best = -inf                          # 1. not 0: a tree like [-3]
def gain(node):                      # 2. best downward path from node
    if not node: return 0
    l = max(0, gain(node.left))      # 3. the line you forgot: drop a negative branch
    r = max(0, gain(node.right))
    best = max(best, node.val + l + r)   # 4. path that bends at this node
    return node.val + max(l, r)      # 5. a parent can extend only one side
```

- **Word Search II.** Failed on all 4 cold revisits. The same word was reported twice (`["oa","oa","oaa"]`), and `"oa"` was missed when it was a prefix of `"oaa"`.

The fix is spaced re-solving: give each pattern a 2–3 line *invariant card* (like lines 3–5 above), and re-solve from the card after 3, 7 and 21 days.

> Hindi hook: *Ek baar samjha, teen baar dohraya, tab yaad hua.*

### 2.6 C++ hygiene (costs you TLEs and noise)

- **Passing `string` by value into recursive helpers**, in about 20 of your C++ solutions. LCS hit TLE at 46/47 tests *with* memoization, because `lcs(int, int, string s1, string s2, ...)` copies both strings on every call.
  Use `const string&`. C++ analogy: it is the same as passing a `std::vector` by value into a hot loop.
- **Memo not stored on one branch.** In Wildcard Matching, the `*` branch did `return f(...) || f(...)` without assigning `dp[i][j]`, so it ran in exponential time and timed out.
  Rule: every `return` in a memoized function goes through `dp[...] =`.
- **Member state not reset.** In 3Sum Closest, `closestDiff` was a class member carried across calls and combined with `max()`, which is the wrong aggregate for "closest".
- **Noise:** `cout` left in 17 accepted solutions, and 5 or more lines of commented-out code in 46. In an interview, delete dead code before you say "done".

---

## 3. What you're good at (keep doing this)

- **Graph traversal on grids and BFS layering.** 92% first try and almost no failed attempts.
- **DP state design.** Stocks IV shows the full ladder (recursion → memo → tabulation → space-optimized), with a comment on every choice. That is exactly what interviewers want to hear.
- **Intervals.** After early mistakes on touching intervals (`>` vs `>=`), you now pass 89% of cold revisits. The mistakes turned into knowledge.
- **You already revisit problems:** 95 of 277 were re-solved at least 7 days later. The habit exists; it just needs a schedule aimed at the weak rows.
- **You write comments that explain *why*.** That's in 66% of C++ solutions and almost all Python ones.

---

## 4. What to practise first

Priority order. Each item names the exact problems from your own history.

1. **Submit discipline (all patterns, starts today).** The 90-second rule from 2.1 and the 5-input checklist from 2.2. Measure it: resubmits under 3 minutes should drop from 60% to under 20%.
2. **Recall drills on the decaying patterns.** Cold re-solve, 25-minute limit, no video first:
   - Topological sort: Alien Dictionary, Course Schedule II, Parallel Courses III.
   - Trie: Word Search II, Design Add and Search Words.
   - DP on trees: Binary Tree Maximum Path Sum, House Robber III, Diameter of Binary Tree.
   - Heap with ties: K Closest Points to Origin, Top K Frequent Words, Find K Closest Elements.
3. **Binary search on answer with 64-bit:** Minimum Time to Complete Trips, Koko Eating Bananas, Split Array Largest Sum, Capacity to Ship Packages. Use one template:

```python
lo, hi = 1, min(time) * total_trips  # 1. hi must already be feasible
while lo < hi:                       # 2. invariant: answer is in [lo, hi]
    mid = lo + (hi - lo) // 2        # 3. long long in C++
    if ok(mid): hi = mid             # 4. mid might be the answer
    else:       lo = mid + 1         # 5. mid is definitely not
return lo
```

   C++ analogy: this is `std::partition_point` over the range `[lo, hi)` with predicate `!ok`.
4. **DP strings, written bottom-up:** Wildcard Matching, Regular Expression Matching, Distinct Subsequences, Edit Distance. Start with the table's first row and column; that's where your base-case bugs were.
5. **Close the gap:** solve Parallel Courses II (bitmask DP). It's the only list problem you never got accepted.

Suggested 4-week loop. Each day: 2 cold re-solves from section 4, then 1 new problem in the same pattern.

```
Week 1  Topological sort + Trie
Week 2  Tree DP + heap ties
Week 3  Binary search on answer + overflow
Week 4  DP strings + bitmask, then one mixed 45-min mock
```

---

## 5. Check yourself (try these before reading any answer)

1. `alienOrder(["abc","ab"])`: what must it return, and which single check in your code handles it?
2. On the tree `[2,-1]`, what does your Jan-2024 Python max-path-sum return, and which one line fixes it?
3. Minimum Time to Complete Trips, `time=[88690,69213]`, `totalTrips=90165`: why could no change to `<` or `<=` fix your 16 Mar 2023 code?
4. Closest BST Value with target 4.5 and nodes 4 and 5: write the `min(..., key=...)` that returns 4.
5. Your LCS had memoization and still timed out at 46/47 tests. What was being copied on every call?
