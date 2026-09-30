# P10: Dynamic Programming

> Practice file: `06-Practice/day3.cpp` · Striver: `DP-Problems.pdf`
> AMD reports: **Coin Change** (C++ Developer R1, TechPrep), Climbing Stairs, "HLD + LLD + 2 DP questions" (senior loop), stock problems.

---

## Card: "recursion + memory; the state is the minimum info that makes the future independent of the past"
| | |
|---|---|
| **Hook** | Write the brute-force recursion as **"what's my last (or first) choice?"** Notice that the same subproblem repeats, then cache it. Bottom-up is just the same table filled in dependency order. |
| **Triggers** | "number of ways", "min/max cost", "can we reach/make", "longest … subsequence", choices at each step with overlapping subproblems |
| **5-step recipe** | 1. **State**: `dp[i]` / `dp[i][j]` means … (say it in English!) · 2. **Transition**: last choice · 3. **Base cases** · 4. **Order**: fill so the dependencies are ready · 5. **Answer** location |
| **Traps** | An undefined state meaning (the #1 cause of wrong DP). Off-by-one with a 1-based `dp` over prefixes. Overflow in counting → `long long`/mod. **Loop order in knapsack variants** (see below). INF + 1 overflow → use `INT_MAX/2`. |

## The families (80% of interview DP)

| Family | State | Transition | Examples |
|---|---|---|---|
| **1D linear** | `dp[i]` = answer for prefix/position i | from i−1, i−2… | climbing stairs, house robber, decode ways, max product subarray |
| **Unbounded knapsack / coin** | `dp[a]` = best for amount a | `dp[a] = min(dp[a], dp[a−c]+1)` | coin change (min), coin change II (#ways), rod cutting |
| **0/1 knapsack** | `dp[w]` = best value with capacity w | iterate items; **w descending** | subset sum, partition equal subset, target sum |
| **LIS** | `dp[i]` = LIS ending at i, or the tails array | O(n²) or O(n log n) with `lower_bound` | LIS, Russian dolls, longest chain |
| **Two strings** | `dp[i][j]` = answer for prefixes `s[0..i)`, `t[0..j)` | match → diag + 1; else max/min of neighbours | LCS, edit distance, distinct subsequences, wildcard/regex |
| **Grid** | `dp[r][c]` = paths/cost to reach (r,c) | from top/left | unique paths, min path sum, obstacles |
| **Interval** | `dp[l][r]` = answer for the segment | split point k in (l,r) | matrix chain, burst balloons, palindrome partitioning |
| **State machine** | `dp[i][state]` | transitions between states | stocks with cooldown/fee/k transactions |
| **Tree DP** | return a pair (take, skip) from children | postorder | house robber III, max independent set |
| **Bitmask** | `dp[mask]` or `dp[mask][i]` | add one element | TSP (n ≤ 16), assignment |

### The loop-order rule (memorize)
```cpp
// COMBINATIONS (order doesn't matter), unbounded:   coins OUTER, amount INNER (ascending)
for (int c : coins) for (int a = c; a <= A; ++a) ways[a] += ways[a - c];
// PERMUTATIONS (order matters, e.g. 1+2 != 2+1):    amount OUTER, coins INNER
for (int a = 1; a <= A; ++a) for (int c : coins) if (c <= a) ways[a] += ways[a - c];
// 0/1 knapsack (each item once):                    items OUTER, capacity DESCENDING
for (auto [w, v] : items) for (int cap = W; cap >= w; --cap) dp[cap] = max(dp[cap], dp[cap - w] + v);
```

### LIS in O(n log n): "patience sorting"
`tails[k]` = the smallest possible tail of an increasing subsequence of length k+1. For each x: `*lower_bound(tails, x) = x`, or push_back if x is the largest. The answer = `tails.size()`. (Use `upper_bound` for non-decreasing.)

### Edit distance (say the 3 operations)
`dp[i][j]` = min ops to turn `s[0..i)` into `t[0..j)`. If `s[i-1]==t[j-1]`: `dp[i-1][j-1]`; else `1 + min(replace dp[i-1][j-1], delete dp[i-1][j], insert dp[i][j-1])`. Base: `dp[i][0]=i`, `dp[0][j]=j`.
*(EDA relevance: diffing netlists/ECO, sequence alignment.)*

### Space optimization
2D → two rows (or one row with care about the direction). Say this as the follow-up after coding the clear 2D version.

---

## Problems (hint ladders)

### P10-1 · House Robber (LC 198) ★★ · `rob`
<details><summary>Hint</summary>At house i, you either rob it (then skip i−1) or you don't.</details>
<details><summary>Approach check</summary>dp[i] = max(dp[i−1], dp[i−2] + a[i]); two variables. Circular version (LC 213): run twice, excluding the first or the last.</details>

### P10-2 · Coin Change: min coins (LC 322) ★★★ and number of combinations (LC 518) ★★★ · `coinChangeWays` (min version is in the toolkit)
<details><summary>Hint 1</summary>Greedy (largest coin first) fails for coins {1,3,4}, amount 6. Why?</details>
<details><summary>Hint 2</summary>For #ways, why can the loop order double-count?</details>
<details><summary>Approach check</summary>Min: dp over amounts, O(A·C). Ways: coins outer, amount inner → combinations. Explain the permutation vs combination difference; the interviewer WILL ask.</details>

### P10-3 · Longest Increasing Subsequence (LC 300) ★★ · `lengthOfLIS`
<details><summary>Approach check</summary>O(n²) dp first (say it), then O(n log n) tails. Be ready for "reconstruct the sequence" → keep parent indices.</details>

### P10-4 · Longest Common Subsequence (LC 1143) ★★ · `lcs`
<details><summary>Approach check</summary>dp[i][j] over prefixes; match → 1 + diag, else max(up, left). O(mn), 1-row optimization possible.</details>

### P10-5 · Edit Distance (LC 72) ★★ · `editDistance`
<details><summary>Approach check</summary>See above. Common bug: base row/column.</details>

### P10-6 · 0/1 Knapsack ★★ · `knapsack01`
<details><summary>Hint</summary>If you iterate capacity ascending with a 1D array, what goes wrong?</details>
<details><summary>Approach check</summary>Descending capacity so each item is used at most once. O(nW).</details>

### P10-7 · Partition Equal Subset Sum (LC 416) ★★ · `canPartition`
<details><summary>Approach check</summary>Odd total → false; subset-sum to total/2 with a bool dp (descending) or `bitset<>` shifts: `bs |= bs << x`.</details>

### P10-8 · Unique Paths with Obstacles (LC 63) ★ · `uniquePathsWithObstacles`
<details><summary>Approach check</summary>dp[c] += dp[c−1] row by row; an obstacle sets 0. Watch the first row/column.</details>

### P10-9 · Best Time to Buy and Sell Stock with Cooldown (LC 309) ★ (state machine)
<details><summary>Approach check</summary>States hold/sold/rest; transitions per day.</details>

### P10-10 · Matrix Chain Multiplication ★ (interval DP, Striver MCM)
<details><summary>Approach check</summary>dp[i][j] = min over k of dp[i][k] + dp[k+1][j] + p[i−1]·p[k]·p[j]. Fill by increasing length. O(n³).</details>

---

## Recall check
1. The 5-step recipe. 2. Combinations vs permutations loop order. 3. Why descending capacity in 0/1 knapsack?
4. LIS tails: what does `tails[k]` mean? 5. The edit distance recurrence with base cases.
