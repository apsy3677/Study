# Problem Bank: 54 practice problems + warm-ups + extra pool

> **How to use one entry** (this is the interview, rehearsed):
> 1. Read the stub in `practice/agoda_dayN.cpp`. Ask yourself the **Clarify** questions out loud and decide the answers.
> 2. Say the approach + complexity. Open hints **one at a time**, and only after 3 minutes stuck.
> 3. **Write your own tests** as comments under the stub, then compare with **Tests to justify** below. Which did you miss?
> 4. Code → run → log the time and your bug in `PROGRESS.md`. Then say the **Follow-up** out loud (Agoda's "proactive" criterion).
>
> ★★★ = Agoda asked it (or its direct variant) in 2025–26 · ★★ = same family / Agoda LC tag · ★ = stretch.
> Sources for every ★★★ are in `00-Agoda-Coding-Intel.md` §3.

---

## Day 1 · S: stack parsing

### S1 · Molecule weight ★★★ · `moleculeWeight` · LC 726 variant
**Why:** Gurugram SSE [SHP] R1 (Oct 2025) and an Agoda R1 (Dec 2025). The Dec candidate failed hidden tests.
**Clarify:** Multi-letter elements (`Mg`)? Can a count follow `)`? Default count 1? Unknown atom: possible, and what then? Max count/nesting (overflow, recursion depth)? Validate parentheses?
**Target:** O(n) time, O(depth) space.
<details><summary>Hint 1</summary>When you reach a <code>)</code>, what do you need to know to continue?</details>
<details><summary>Hint 2</summary>Recursive descent with the index passed by reference, or a stack of partial sums.</details>
<details><summary>Hint 3</summary><code>parseGroup</code> sums units until <code>)</code> or the end. A unit is an element or a parenthesised group. After each unit, read an optional number (default 1) and multiply.</details>

**Tests to justify:** `H(CH4)2` group count · `Mg(OH)2` two-letter atom · `C12H22O11` multi-digit · `((CH)2O)3` nesting · `(H)` a `)` with no count · `""` empty · `C1000000000` overflows `int`.
**Follow-up:** error handling (`optional`/exception for an unknown atom or unbalanced input), an iterative stack for deep nesting, caching parsed formulas in a service.

### S2 · Number of Atoms ★ (hard) · `countOfAtoms` · LC 726
**Why:** The full version of S1. If S1 took under 15 minutes, do this.
**Clarify:** Output order (sorted by name)? Omit count 1?
<details><summary>Hint 1</summary>Same grammar as S1, but each group returns a map instead of a number.</details>
<details><summary>Hint 2</summary><code>map&lt;string,long long&gt;</code> keeps names sorted for free. Multiply the inner map by the group count and merge it into the parent.</details>

**Tests to justify:** `K4(ON(SO3)2)2` nested multiply · `Be32` two-letter + number · `((H))` empty multipliers.
**Follow-up:** complexity with deep nesting (re-multiplying maps): O(n · distinct · depth) worst case. Fix it with a stack of multipliers computed right to left.

### S3 · Decode String ★★ · `decodeString` · LC 394 (Agoda tag)
**Clarify:** Multi-digit counts? Nested? Letters outside brackets? Is the input always valid?
<details><summary>Hint 1</summary>On <code>[</code>, what do you need to remember to finish the outer string later?</details>
<details><summary>Hint 2</summary>A stack of (string so far, repeat count).</details>
<details><summary>Hint 3</summary>On <code>]</code>: pop (prev, k), then <code>current = prev + current × k</code>.</details>

**Tests:** `3[a2[c]]` nesting · `10[a]` multi-digit · `2[abc]3[cd]ef` trailing letters · `abc` no brackets · `""`.
**Follow-up:** Output size can explode (`9[9[9[a]]]`). Cap it, or stream it lazily.

### S4 · Reverse Substrings Between Parentheses ★★ · `reverseParentheses` · LC 1190 (Agoda tag)
<details><summary>Hint 1</summary>The simple way: a stack of strings, reverse the inner one at each <code>)</code>. What's the complexity?</details>
<details><summary>Hint 2</summary>That's O(n²). For O(n): pair each paren with its partner first.</details>
<details><summary>Hint 3</summary>Walk the string. At a paren, jump to its partner and flip direction. Collect letters as you go.</details>

**Tests:** `(u(love)i)` two levels · `(ed(et(oc))el)` three levels · `()ab` empty pair · `""`.
**Follow-up:** Explain why the "wormhole" walk visits each char once.

### S5 · Remove All Adjacent Duplicates II ★★★ · `removeDuplicatesK` · LC 1209 (Agoda tag, recent)
<details><summary>Hint 1</summary>After removing a run, the neighbours touch. What must you remember about the left side?</details>
<details><summary>Hint 2</summary>A stack of (char, run length).</details>
<details><summary>Hint 3</summary>Bump the top run or push a new one, <b>then</b> pop if the run equals k.</details>

**Tests:** `deeedbbcccbdaa`,3 → `aa` cascading removals · `abcd`,2 nothing removed · `aaa`,3 → `""` · `abc`,1 degenerate k.
**Follow-up:** k = 2 is LC 1047. A streaming version keeps only the stack.

### S6 · Backspace String Compare ★★ · `backspaceCompare` · LC 844
**Why:** Asked live (Agoda SSE 2025, "easy" slot). Agoda tag.
<details><summary>Hint 1</summary>Building both strings is O(n) space. Can you compare from the end?</details>
<details><summary>Hint 2</summary>Walk backwards with a skip counter.</details>

**Tests:** `a##c` vs `#a#c` (`#` on empty) · `ab##` vs `c#d#` both empty · `abc` vs `abcd#d` · `""` vs `#`.
**Follow-up:** O(1) extra space. The interviewer *will* ask for it after the stack version.

### S7 · Basic Calculator II ★★ · `calculate` · LC 227
<details><summary>Hint 1</summary>Precedence: <code>*</code> and <code>/</code> bind to the last term only.</details>
<details><summary>Hint 2</summary>Keep a committed sum plus the last term. Apply the <i>previous</i> operator when you meet a new one (or the end).</details>

**Tests:** `14-3/2` = 13 (truncation) · `1-1-1` = −1 (left associativity) · spaces · a single number.
**Follow-up:** Parentheses and unary minus = LC 224 (Mock 6).

## Day 1 · M: monotonic stack

### M1 · Next Greater Element II (circular) ★★★ · `nextGreaterCircular` · LC 503
**Why:** Gurugram Staff R1 (Feb 2026), "variant of the largest greater number on the right side". Agoda SSE 2025 also asked a next-greater variant. Variants to know: **LC 496** (with a map), **LC 739** (distance, AMD P05-3), **LC 1299** (greatest to the right = suffix max).
**Clarify:** Values or indices? Strictly greater? Circular? What if none?
<details><summary>Hint 1</summary>Which elements are still "waiting" for their answer?</details>
<details><summary>Hint 2</summary>A stack of indices with decreasing values. Pop while the current value is greater.</details>
<details><summary>Hint 3</summary>Circular: loop k from 0 to 2n−1 using <code>a[k % n]</code>, and push only when k &lt; n.</details>

**Tests:** `[5,5,5]` equal is not greater · `[3,8,4,1,2]` wrap-around · `[]`.
**Follow-up:** "Largest greater on the right" (not the next one) is a suffix max, O(n), no stack. Say both.

### M2 · Nearest smaller to the left ★★★ · `nearestSmallerToLeft`
**Why:** Agoda Staff R1 2026 (selected candidate).
<details><summary>Hint 1</summary>If <code>a[j] ≥ a[i]</code> and j &lt; i, can <code>a[j]</code> ever be the answer for anything after i?</details>
<details><summary>Hint 2</summary>No, so keep an increasing stack. Pop while top ≥ x. Then the top is the answer.</details>

**Tests:** `[2,2,3]` strict · `[3,2,1]` all −1 · `[]`.
**Follow-up:** Previous/next smaller on both sides → largest rectangle in a histogram (AMD P05-4).

### M3 · Pivot elements ★★★ · `pivotElements`
**Why:** Glassdoor, Agoda Staff India: "find all possible pivot elements in an unsorted array".
**Clarify:** Strict on both sides? Return values or indices? First/last elements?
<details><summary>Hint 1</summary>"Everything left is smaller" means larger than the max of the left part.</details>
<details><summary>Hint 2</summary>Prefix max from the left, suffix min from the right. Two passes.</details>

**Tests:** `[1,1,2]` strictness · `[1, INT_MAX]` sentinel trap (use `long long` sentinels) · single element · sorted (all qualify) · reverse sorted (none).
**Follow-up:** One pass with a stack is possible (keep candidates; pop those ≥ the current). O(1) extra space isn't, beyond the output.

### M4 · Sum of Subarray Minimums ★★ · `sumSubarrayMins` · LC 907
<details><summary>Hint 1</summary>Flip it: for each element, in how many subarrays is it the minimum?</details>
<details><summary>Hint 2</summary>left[i] = distance to the previous smaller, right[i] = distance to the next smaller. The contribution is a[i]·left·right.</details>
<details><summary>Hint 3</summary>Duplicates: strict on one side, non-strict on the other.</details>

**Tests:** `[2,2,2]` = 12 (double counting) · 30000 × 30000 (modulo + overflow) · `[]`.
**Follow-up:** Sum of subarray ranges (LC 2104) = sum of maxes − sum of mins.

### M5 · Remove K Digits ★★ · `removeKdigits` · LC 402
<details><summary>Hint 1</summary>Which single digit should you remove to make the number smallest?</details>
<details><summary>Hint 2</summary>The first digit that's larger than the one after it. Repeat with a stack: an increasing stack of digits.</details>

**Tests:** `10200`,1 → `200` leading zeros · `10`,2 → `0` everything removed · `112`,1 increasing (remove from the end) · k = 0.

## Day 1 · W: sliding window

### W1 · Longest substring with distinct chars (return it) ★★★ · `longestDistinctSubstring` · LC 3 variant
**Why:** Gurugram Staff R1 (Feb 2026). LC 3 is AMD P02-5, but here you return the substring.
**Clarify:** Charset (ASCII vs Unicode)? Ties: first or last? Empty input?
<details><summary>Hint 1</summary>Keep the last index of each char.</details>
<details><summary>Hint 2</summary>On a repeat, jump left to <code>last[c] + 1</code>, but only if that index is inside the window.</details>

**Tests:** `abba` (stale index: the answer is `ab`, not `ba` or `aba`) · `a b!a` spaces/symbols · `""` · `bbbbb`.
**Follow-up:** Unicode → `unordered_map<char32_t,int>`. For a stream, keep only the window.

### W2 · At most k distinct ★★ · `longestAtMostKDistinct` · LC 340 / LC 904
**Tests:** k = 0 · k ≥ distinct count · `""`.
<details><summary>Hint</summary>A count map. Shrink while <code>map.size() &gt; k</code>, erasing keys that hit 0.</details>

### W3 · Longest Repeating Character Replacement ★★ · `characterReplacement` · LC 424
<details><summary>Hint 1</summary>A window is fixable if (length − count of its most frequent letter) ≤ k.</details>
<details><summary>Hint 2</summary>maxFreq never needs to decrease (it can only make the window "look" valid, never yield a longer wrong answer).</details>

**Tests:** `AABABBA`,1 · k = 0 · `ABCDE`,1 · `""`.
**Follow-up:** Explain why the stale <code>maxFreq</code> is safe. Interviewers love asking this.

### W4 · Subarray Product Less Than K ★★ · `numSubarrayProductLessThanK` · LC 713 (Agoda tag)
<details><summary>Hint</summary>All values are positive, so the product is monotone in the window. Each right end adds <code>right − left + 1</code> subarrays.</details>

**Tests:** k = 0 and k = 1 (no subarray) · all ones · `[]`.
**Follow-up:** With zeros or negatives the window breaks. Use logs/prefix products or a different approach.

### W5 · Permutation in String ★ · `checkInclusion` · LC 567
**Tests:** `p` longer than `s` · empty `p` · `adc` in `dcda` (wrap-like case).
<details><summary>Hint</summary>A fixed window of |p|. Compare <code>array&lt;int,26&gt;</code> counts (or track a "matches" counter for O(1) per step).</details>

### W6 · Subarrays with exactly K distinct ★ (hard) · `subarraysWithKDistinct` · LC 992
<details><summary>Hint</summary>Exactly(k) = AtMost(k) − AtMost(k−1).</details>

**Tests:** k bigger than the distinct count → 0 · all equal.

---

## Day 2 · B: binary search on the answer

### B1 · Capacity To Ship Within D Days ★★★ · `shipWithinDays` · LC 1011
**Why:** Agoda tag (recent). The Aug 2025 Staff R1 had "very similar to Koko". AMD P03-4 Koko is the warm-up.
**Clarify:** Order fixed? Days ≥ 1? Weight and n limits (sum fits in int?)
<details><summary>Hint 1</summary>If capacity C works, does C+1 work?</details>
<details><summary>Hint 2</summary>Yes, monotone, so binary search C in [max weight, sum]. Check greedily, day by day.</details>

**Tests:** days = n → max weight · days = 1 → sum · a single package · `[7,2,5,10,8]`,2 = 18 (it's also LC 410).
**Follow-up:** LC 410 split array, LC 1482 bouquets (Mock 2) and LC 875 Koko are the same template. Name them.

### B2 · Smallest Divisor ★★ · `smallestDivisor` · LC 1283 (Agoda tag)
**Tests:** a huge threshold → 1 · threshold = n → max element · ceil without floats `(x + d - 1) / d`.

### B3 · Maximize the minimum gap ★★★ · `maxMinDistance` · LC 1552 ("aggressive cows")
**Why:** Agoda SSE OA: "binary search pattern to find maximum of minimum".
<details><summary>Hint 1</summary>If you can place m balls with min gap g, can you with g−1?</details>
<details><summary>Hint 2</summary>Sort, then binary-search the LAST g that works. Greedy placement from the left.</details>
<details><summary>Hint 3</summary>Use an upper mid <code>lo + (hi − lo + 1) / 2</code>, or the loop never ends.</details>

**Tests:** unsorted input · m = n (min adjacent gap) · m = 2 (max − min).
**Follow-up:** O(n log n + n log range). Why the greedy check is optimal (placing earlier never hurts).

### B4 · Min operations per query ★★ · `minOperationsQueries` · LC 2602
**Why:** Agoda Staff OA (Nov 2025), per the CodingKaro summary.
<details><summary>Hint 1</summary>Per query, brute force is O(n). With 10⁵ queries, too slow.</details>
<details><summary>Hint 2</summary>Sort + prefix sums. Split at <code>lower_bound(q)</code>: below needs raising, above needs lowering.</details>

**Tests:** q below all, above all, equal to an element · empty array · 2·10⁹ total (`long long`).

## Day 2 · G: greedy, sorting, heaps

### G1 · Airplanes / Eliminate Maximum Monsters ★★★ · `eliminateMaximum` · LC 1921
**Why:** Gurugram SSE [SHP] R1 (Oct 2025), plus Glassdoor Staff India. **Your most likely question.**
**Clarify:** Shoot at minute 0? "Lands exactly when I'm ready to shoot": is that a loss? Can distances/speeds be 0? Integer or real times?
<details><summary>Hint 1</summary>Which plane must you shoot first?</details>
<details><summary>Hint 2</summary>The one landing earliest. Sort arrival times.</details>
<details><summary>Hint 3</summary>The plane shot at minute i must arrive after i. With integers: <code>arrival = ceil(d/s)</code>, fail when <code>arrival ≤ i</code>.</details>

**Tests:** `[3,5,7,4,5]/[2,3,6,3,2]` fractional times = 2 · `[1,1]/[1,1]` tie at the shooting minute = 1 · all reachable = n · `[]`.
**Follow-up:** O(n) with counting (arrivals > n never matter). Explain why doubles are risky (`3/2` vs `1.5000001`).

### G2 · Minimum Absolute Difference pairs ★★★ · `minimumAbsDifference` · LC 1200
**Why:** Aug 2025 Staff R1 ("pairs with min absolute difference"). Agoda tag (6 months).
**Tests:** several pairs tie · one element → none · `±2·10⁹` (difference overflows `int`).
**Follow-up:** without sorting? Bucket/radix ideas for bounded values.

### G3 · K-diff pairs ★★ · `findPairsKDiff` · LC 532
**Why:** The other reading of "pairs with min absolute difference = K". Ask which one they mean!
<details><summary>Hint</summary>A count map. k = 0 needs a duplicate. Otherwise check x + k. Don't use <code>map[x+k]</code> while iterating: it inserts.</details>

**Tests:** k = 0 with duplicates · duplicates with k > 0 counted once · `[]`.

### G4 · Rank transform ★★★ · `arrayRankTransform` · LC 1331
**Why:** Staff R1 2026 (selected): "ranks of every element in priorities".
**Clarify:** Ties share a rank? Dense ranks (1,2,2,3) or competition ranks (1,2,2,4)? Highest = rank 1 or n?
**Tests:** all equal · negatives · `[]`.
**Follow-up:** Competition ranking and "highest first" are one-line changes. Show you can switch.

### G5 · Sort by increasing frequency ★★ · `frequencySort` · LC 1636 (Agoda tag)
**Tests:** frequency ties → decreasing value · negatives.
**Follow-up:** Why the comparator must be a strict weak ordering (never `<=`).

### G6 · Discount coupons ★★ · `minCostWithCoupons` (Agoda OA)
**Clarify:** Can several coupons go on one item? Floor? Can m exceed what's useful?
<details><summary>Hint 1</summary>Halving x saves ceil(x/2). Which item gives the biggest saving?</details>
<details><summary>Hint 2</summary>A max-heap. Halve the top m times. Stop early when the top is 0.</details>

**Tests:** all coupons on one item (`[8]`,3 → 1) · m = 0 · m huge · a total > `INT_MAX`.
**Follow-up:** The proof (the saving is monotone in price) and the m ≫ n optimization (≤ 31 useful halvings per item).

### G7 · Task queue lexicographic ★★ · `smallestTaskQueue` (Agoda OA)
<details><summary>Hint 1</summary>Which pairs can never change their relative order?</details>
<details><summary>Hint 2</summary><code>1</code> and <code>3</code> can't cross. <code>2</code> moves anywhere. Where do all the 2s go?</details>

**Tests:** no 3s (2s go at the end) · no 2s · `3312` → `2331` · `""`.

### G8 · Task Scheduler ★★ · `leastInterval` · LC 621
**Why:** Agoda Gurgaon backend.
**Tests:** n = 0 → the task count · many tasks tied at max frequency · the empty list (the formula alone gives 23!).
**Follow-up:** Return the actual schedule (simulate with a max-heap + cooldown queue).

### G9 · Reorganize String ★★ · `reorganizeString` · LC 767 (Agoda tag)
**Tests:** impossible (`aaab`) · a single char · `""`. **Tests must check properties** (no adjacent equal + same letters), not one exact string. Say this to the interviewer.

## Day 2 · I: intervals and bookings

### I1 · Max team size with overlapping intervals ★★★ · `maxTeamSize` · LC 3893 (Agoda tag, recent)
**Clarify:** Closed intervals (does touching count)? Must the "centre" overlap everyone?
<details><summary>Hint 1</summary>Fix the centre i. Who can be on its team?</details>
<details><summary>Hint 2</summary>Everyone overlapping [lᵢ, rᵢ] = n − (ends &lt; lᵢ) − (starts &gt; rᵢ).</details>

**Tests:** touching `[1,2]`,`[2,3]` · disjoint · nested.

### I2 · Car Pooling ★★ · `carPooling` · LC 1094
**Tests:** drop-off and pick-up at the same stop · capacity 0 with no trips.
**Follow-up:** With locations ≤ 1000, a difference array instead of a map gives O(n + L).

### I3 · Corporate Flight Bookings ★★ · `corpFlightBookings` · LC 1109
**Tests:** single-flight ranges · no bookings.
**Follow-up:** Range add plus range query online → Fenwick/segment tree.

### I4 · My Calendar II ★★ · `MyCalendarTwo` · LC 731
**Clarify:** Half-open `[start, end)`?
**Tests:** back-to-back bookings · a rejected booking must not linger (a later unrelated booking still succeeds).
**Follow-up:** k-booking (LC 732), segment tree for 10⁵ bookings, concurrency (lock per room/date).

### I5 · Meeting Rooms III ★★ · `mostBooked` · LC 2402 (your Google R2 rematch)
<details><summary>Hint</summary>Two min-heaps: free rooms by index; busy rooms by (end, index). A delayed meeting keeps its duration.</details>

**Tests:** delays · count ties → lowest index · end times > `INT_MAX`.
**Follow-up:** Compare with your 2023 code. Name the 3 bugs you would catch now.

---

## Day 3 · J: jump and stock DP

### J1 · Jump Game ★★★ · `canJump` · LC 55
**Why:** Jul 2025 Staff R2 and Feb 2026 SSE R2 ("a DP similar to Jump Game"). Agoda tag.
**Say:** The DP first (O(n²)), then the greedy farthest-reach (O(n)).
**Tests:** `[0]` already there · a zero you can't pass · a zero you can jump over.

### J2 · Jump Game II ★★★ · `jumpMin` · LC 45
<details><summary>Hint</summary>BFS by levels. [levelStart, levelEnd] are the indices reachable in exactly "jumps" jumps.</details>

**Tests:** n = 1 → 0 · the first jump reaches the end · all ones.

### J3 · Jump Game III ★★ · `canReachZero` · LC 1306
**Tests:** cycles (a visited set is needed) · start already on 0.

### J4 · Jump Game VI ★★ · `maxResultJump` · LC 1696
<details><summary>Hint</summary><code>best[i] = a[i] + max(best[i−k..i−1])</code>. The window max comes from a monotonic deque (AMD P05 card D).</details>

**Tests:** all negative · k ≥ n · n = 1.

### J5 · Stock II (unlimited) ★★★ · `maxProfitMulti` · LC 122
**Why:** Jul 2025 Staff R2 "variation of Stock Buy/Sell". AMD has LC 121 (P01-7) and cooldown (P10-9).
**Follow-up:** Prove that summing positive deltas is optimal.

### J6 · Stock with fee ★★ · `maxProfitFee` · LC 714
**Tests:** a fee larger than any gain · one day.

### J7 · Stock III (two transactions) ★★ · `maxProfitTwo` · LC 123
**Tests:** a monotone increasing series (one transaction is best) · a decreasing series → 0.
**Follow-up:** k transactions (LC 188).

### J8 · Triangle ★★ · `minimumTotal` · LC 120 (Agoda tag)
**Follow-up:** Bottom-up in O(n) extra space, without modifying the input.

## Day 3 · P: palindromes and string DP

### P1 · Count Palindromic Substrings ★★★ · `countSubstrings` · LC 647
**Why:** Aug 2025 Staff: "passed all test cases but could not optimize". **Say O(n³) → O(n²) out loud.**
**Tests:** `abba` even centre · `aaa` overlapping · `""`.
**Follow-up:** Manacher O(n) (explain the mirror idea; don't code it unless asked).

### P2 · Longest Palindromic Substring ★★ · `longestPalindrome` · LC 5
**Tests:** several answers of the same length (say "any one"; the tests check the property).

### P3 · Decode Ways ★★ · `numDecodings` · LC 91
**Tests:** `06`, `100`, `27`, `10`, `2101`. Zeros are the whole problem.

### P4 · Word Break ★★ · `wordBreak` · LC 139
**Tests:** word reuse · a dead-end prefix (`catsandog`) · empty string.
**Follow-up:** Return all sentences (LC 140): memoized DFS.

### P5 · Longest String Chain ★★ · `longestStrChain` · LC 1048 (Agoda tag)
**Tests:** same letters but not a chain (`abcd`, `dbqca`).

### P6 · Max Profit in Job Scheduling ★★ · `jobScheduling` · LC 1235
**Why:** Weighted interval scheduling is the "accept the most valuable bookings" problem. It fits the domain.
**Tests:** end == next start is allowed (`upper_bound`).

## Day 3 · H: design · R: routes

### H1 · RandomizedSet ★★ · LC 380 (Agoda tag)
**Tests:** remove the last element · remove then re-insert.

### H2 · TimeMap ★★ · LC 981
**Tests:** a query before the first timestamp · an unknown key.
**Follow-up:** Timestamps not increasing → `map<int,string>` per key.

### R1 · Cheapest Flights Within K Stops ★★ · LC 787
**Tests:** the in-place relaxation trap (`[[0,1,1],[1,2,1],[0,2,5]]`, k = 0 → 5) · unreachable · src = dst.

### R2 · Evaluate Division ★ · LC 399
**Tests:** an unknown variable · `x/x` with x unknown → −1.

---

## Warm-ups already in the AMD prep (Agoda-tagged): 8 minutes each, from a blank file

| Day | Problem → where to practise it in `AMD-CPP-EDA-Lead-Prep/` |
|---|---|
| 1 | Daily Temperatures LC 739 (P05-3, `06-Practice/day2.cpp` `nextGreater`) · Sliding Window Max LC 239 (P05-5, day2 `maxSlidingWindow`) · Valid Parentheses LC 20 (P05-1, day2 `isValidParens`) |
| 2 | Koko LC 875 (P03-4, day1 `minEatingSpeed`) · Merge Intervals LC 56 (P06-1, day2 `mergeIntervals`) · Meeting Rooms II LC 253 (P06-2, day2 `minMeetingRooms`) · 3Sum LC 15 (P02-1, day1 `threeSum`) · Top K LC 347 (P06-6: re-derive, reference in `01-Speed-Cpp/cpp_toolkit.cpp`) · Sort Colors LC 75 (P02-8: on LeetCode, no stub) |
| 3 | Coin Change LC 322 (P10-2, day3 `coinChange`) · LIS LC 300 (P10-3, day3 `lengthOfLIS`) · House Robber LC 198 (P10-1, day3 `rob`) · Stock I LC 121 (P01-7, day1 `maxProfit`) · LRU LC 146 (P12-1, day2 `LRUCache`) |

## Extra pool (after the plan, or for daily practice until the interview)

| Family | Problems (LeetCode) |
|---|---|
| S | 1249 · 856 · 224 (hard) · 726 (full) · 1047 · 71 |
| M | 901 · 84 · 85 (hard) · 456 · 2104 · 1475 |
| W | 1004 · 904 · 1838 · 2958 · 438 · 76 (hard) |
| B | 1482 · 1870 · 410 · 1231 · 2064 · 1760 |
| G | 2208 · 1353 · 452 · 435 · 134 · 763 · 846 · 2551 |
| I | 57 · 2406 · 759 (hard) · 1288 · 986 · 732 |
| J | 1871 · 309 · 188 (hard) · 2289 |
| P | 516 · 131 · 1143 · 132 (hard) |
| H | 2034 · 146 · 460 (hard) · 1396 (travel: underground system) |
| R | 815 (hard) · 332 (hard) · 127 · 1584 · 743 |
