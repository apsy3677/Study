# Mock Rounds: 7 timed Agoda-style IV1 simulations

> Each mock = **2 problems in 50 minutes**, like the real round. They use problems that are **not** in the practice files, so they test *transfer* (Agoda gives "variants").
> The interviewer notes are folded. **Don't open them until the mock is over.**

## How to run a mock

**With Claude (best):** open this folder in Claude Code and say *"Run Mock 2"*. Claude plays the Agoda interviewer (`CLAUDE.md`), answers only what you ask, keeps time, and scores you.

**Solo:**
1. Plain editor or the HackerRank playground (no autocomplete). Start a **50-minute timer** and **record your voice** on your phone.
2. Read only problem A. Talk as if someone is listening: clarify → approach → code → test.
3. At **25:00**, move to problem B no matter what.
4. Afterwards, **submit both on LeetCode** (the links) to run the hidden tests. Listen to 5 minutes of your recording and count silences longer than 30 s.
5. Score yourself with the rubric below. Log the scores and the bug in `PROGRESS.md`.

## Rubric (Agoda's 4 areas + result), 1–4 each

| Area | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| **Understanding** | Started coding immediately | Some questions, no example | Key questions + worked example | + brute → optimal with complexity, got agreement |
| **Coding** | Didn't run | Ran after many fixes | Clean, ran with 1–2 fixes | Clean, idiomatic, helpers, ran first or second time |
| **Testing** | Only the sample | A few cases, no reasons | Edge cases with reasons | Matrix-driven, found its own bug, justified |
| **Communication** | Long silences | Needed prompting | Steady narration | + proactive follow-up (scale, stream, service) |
| **Result** | Neither passes | One passes | Both pass | Both pass, ≤ 22 min each |

**Target by Mock 5:** ≥ 16/20 with both problems passing.

---

## Mock 0: calibration (Day 1, 09:00, cold)

**A. Online stock span** ([LC 901](https://leetcode.com/problems/online-stock-span/))
Design `StockSpanner` with `int next(int price)`: return how many consecutive days, **ending today**, had a price ≤ today's price.
Example: prices 100, 80, 60, 70, 60, 75, 85 → 1, 1, 1, 2, 1, 4, 6.

**B. Minimum speed to arrive on time** ([LC 1870](https://leetcode.com/problems/minimum-speed-to-arrive-on-time/))
You take n trains in order; `dist[i]` is train i's distance. Every train departs only at an **integer hour**, so you may wait. Given `hour` (a real number, at most 2 decimals), return the minimum **positive integer** speed (≤ 10⁷) that gets you there within `hour`, or −1.
Example: `[1,3,2]`, 6 → 1 · `[1,3,2]`, 2.7 → 3 · `[1,3,2]`, 1.9 → −1.

<details><summary>Interviewer notes</summary>

- **A:** a stack of (price, span). Pop while top price ≤ price and add its span. O(1) amortized. Good clarifying question: "equal prices count?" (yes). Follow-up: "what if we need the span for an arbitrary past day?" → store the spans.
- **B:** binary search the speed in [1, 10⁷]. Check: sum of `ceil(d/s)` for all but the last train, plus `d_last/s` exact. **Traps:** the last train isn't rounded up · floating comparisons (multiply by 100 and use integers, or add 1e-9) · `hour ≤ n−1` → −1 immediately · overflow in the sum. Tests to expect: hour < n−1, hour exactly an integer, the last train fractional.
</details>

## Mock 1: after Day 1 (Fri, 19:30)

**A. Score of parentheses** ([LC 856](https://leetcode.com/problems/score-of-parentheses/))
Balanced string: `()` = 1, `AB` = A + B, `(A)` = 2·A. Return the score.
Examples: `()` → 1 · `(())` → 2 · `()()` → 2 · `(()(()))` → 6.

**B. Frequency of the most frequent element** ([LC 1838](https://leetcode.com/problems/frequency-of-the-most-frequent-element/))
In one operation you may add 1 to any element. With at most k operations, maximize the frequency of some value.
Examples: `[1,2,4]`, k=5 → 3 · `[1,4,8,13]`, k=5 → 2 · `[3,9,6]`, k=2 → 1.

<details><summary>Interviewer notes</summary>

- **A:** a stack of scores (push 0 on `(`, on `)` pop v and add `max(2v, 1)` to the new top), or O(1) space: every `()` contributes `1 << depth`. Expect the candidate to give the stack version, then mention the O(1) idea.
- **B:** sort, then a sliding window where the cost to raise everything to `nums[r]` = `nums[r]*len − windowSum ≤ k`. **`long long`** (10⁵ × 10⁵). Clarify: only increments? (yes). Tests: k = 0, all equal, a large k.
</details>

## Mock 2: after Day 2 (Sat, 19:00)

**A. Minimum days to make m bouquets** ([LC 1482](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/))
`bloomDay[i]` is when flower i blooms. A bouquet needs k **adjacent** bloomed flowers. Minimum days to make m bouquets, or −1.
Examples: `[1,10,3,10,2]`, m=3, k=1 → 3 · same, m=3, k=2 → −1 · `[7,7,7,7,12,7,7]`, m=2, k=3 → 12.

**B. Divide intervals into the minimum number of groups** ([LC 2406](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/))
Closed intervals `[l, r]`. Split them into groups so no two intervals in a group intersect. Minimum groups?
Examples: `[[5,10],[6,8],[1,5],[2,3],[1,10]]` → 3 · `[[1,3],[5,6],[8,10],[11,13]]` → 1.

<details><summary>Interviewer notes</summary>

- **A:** binary search the day in [min, max]. Greedy count of adjacent runs. **Early −1 when `(long long)m*k > n`** (an overflow trap). Tests: impossible, k = 1, all the same day.
- **B:** answer = maximum overlap. Sort by start + a min-heap of ends; pop while `top < start` (**strict**, because the intervals are closed: `[1,5]` and `[5,10]` intersect). Or a sweep with `+1 at l, −1 at r+1`. Follow-up: "return the actual grouping" → assign the group id of the popped interval.
</details>

## Mock 3: after Day 2 (Sat, 20:15). Do it in the **HackerRank editor**

**A. Minimum operations to halve the array sum** ([LC 2208](https://leetcode.com/problems/minimum-operations-to-halve-array-sum/))
In one operation, choose any number and replace it with **exactly half** (a real number). Minimum operations to reduce the total by at least half.
Examples: `[5,19,8,1]` → 3 · `[3,8,20]` → 3.

**B. Insert interval** ([LC 57](https://leetcode.com/problems/insert-interval/))
Sorted, non-overlapping intervals plus one new interval: insert it and merge.
Examples: `[[1,3],[6,9]]` + `[2,5]` → `[[1,5],[6,9]]` · `[[1,2],[3,5],[6,7],[8,10],[12,16]]` + `[4,8]` → `[[1,2],[3,10],[12,16]]`.

<details><summary>Interviewer notes</summary>

- **A:** a max-heap of doubles; halve the top until the reduction ≥ sum/2. Sibling of G6 (coupons). Ask: "real halves, not floor?" Proof: the biggest number gives the biggest reduction.
- **B:** three phases: before (end < newStart), merge (start ≤ newEnd), after. **Tests:** empty list · new at the front/back · touching `[1,5]` + `[5,7]` → merge (clarify!) · new covers everything. Common bug: forgetting to push the merged interval when the loop ends.
</details>

## Mock 4: Day 3 (Sun, 16:00)

**A. Jump Game VII** ([LC 1871](https://leetcode.com/problems/jump-game-vii/))
Binary string s (`s[0] = '0'`). From i you may jump to j with `i + minJump ≤ j ≤ min(i + maxJump, n−1)` and `s[j] = '0'`. Can you reach the last index?
Examples: `"011010"`, 2, 3 → true · `"01101110"`, 2, 3 → false.

**B. Longest palindromic subsequence** ([LC 516](https://leetcode.com/problems/longest-palindromic-subsequence/))
Examples: `"bbbab"` → 4 · `"cbbd"` → 2.

<details><summary>Interviewer notes</summary>

- **A:** naive BFS is O(n·maxJump). O(n): `reach[j]` is true if some reachable i is in `[j − maxJump, j − minJump]`. Keep a running count of reachable indices in that window (prefix sums or a counter). This is the J4 deque idea, but simpler.
- **B:** `dp[i][j] = s[i]==s[j] ? dp[i+1][j−1] + 2 : max(dp[i+1][j], dp[i][j−1])`. Loop i downward. O(n²) time, O(n) space possible. Mention LPS = LCS(s, reverse(s)). Contrast with substring (P2): a subsequence can skip characters.
</details>

## Mock 5: Day 3 (Sun, 17:30). Use the **HackerRank editor** again

**A. Stock price fluctuation** ([LC 2034](https://leetcode.com/problems/stock-price-fluctuation/))
A stream of `update(timestamp, price)`. A later update for the same timestamp **corrects** the earlier one. Support `current()` (the price at the latest timestamp), `maximum()` and `minimum()` over the current prices.

**B. Bus routes** ([LC 815](https://leetcode.com/problems/bus-routes/), hard)
`routes[i]` lists the stops of bus i (it loops forever). Fewest buses from `source` to `target`, or −1.
Examples: `[[1,2,7],[3,6,7]]`, 1 → 6 = 2 · `[[7,12],[4,5,15],[6],[15,19],[9,12,13]]`, 15 → 12 = −1.

<details><summary>Interviewer notes</summary>

- **A:** `map<int,int>` timestamp → price, plus a `multiset<int>` of prices (erase **one** instance on a correction: `prices.erase(prices.find(old))`). Alternative: two heaps with lazy deletion. Follow-up: thread safety, and a sliding-window max over the last 24 h (monotonic deque).
- **B:** BFS where the nodes are **buses**. Map stop → buses. Mark the buses *and* the stops you've visited. `source == target` → 0 (clarify!). Bad answer: BFS over stops with an adjacency list of every stop pair (O(stops²) edges). Agoda angle: the flight/route search domain.
</details>

## Mock 6: interview eve or extra day (morning, fresh)

**A. Basic calculator** ([LC 224](https://leetcode.com/problems/basic-calculator/), hard)
`+`, `-`, parentheses, spaces, unary minus. Examples: `"1 + 1"` → 2 · `" 2-1 + 2 "` → 3 · `"(1+(4+5+2)-3)+(6+8)"` → 23 · `"-(2+3)"` → −5.

**B. Maximum number of events that can be attended** ([LC 1353](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/))
`events[i] = [start, end]` (inclusive). You can attend one event per day, on any day within its range. Maximum events?
Examples: `[[1,2],[2,3],[3,4]]` → 3 · `[[1,2],[2,3],[3,4],[1,2]]` → 4.

<details><summary>Interviewer notes</summary>

- **A:** `result`, `sign`, and a stack of (result, sign) pushed at `(`. At `)`: `result = saved + savedSign * result`. Or recursive descent (card S). Tests: unary minus at the start and after `(`, nested parens, multi-digit numbers, spaces.
- **B:** sort by start. Walk the days: push the ends of events starting today into a min-heap, pop expired ones (`end < day`), attend the earliest-ending one. O(n log n + D log n). Explain why the earliest deadline is optimal (exchange argument). Ties with G1 (airplanes): same "earliest deadline first" idea.
</details>
