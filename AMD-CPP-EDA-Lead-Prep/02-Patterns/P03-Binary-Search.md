# P03: Binary Search (on index **and** on answer)

> Practice file: `06-Practice/day1.cpp` · Striver: SDE Sheet (binary search day)
> AMD relevance: frequent "O(log n)" follow-ups; binary search on answer also shows up in EDA (min clock period feasible, min channel width that routes).

---

## Card: "find the boundary of a monotone predicate"
| | |
|---|---|
| **Hook** | Forget "find the target". Picture a row of `F F F F T T T` and find the **first T**. Every binary search is this. |
| **Triggers** | sorted / rotated / "O(log n)" / first or last occurrence / peak / "minimum X such that feasible" / "maximize the minimum" |
| **Invariant** | The answer is always inside `[lo, hi]`. `hi` is always a known-T candidate, and everything `< lo` is known-F. |
| **Termination** | `while (lo < hi)` with `mid = lo + (hi-lo)/2` and `hi = mid` / `lo = mid + 1` **always** terminates and never skips the answer. |
| **Traps** | `lo = mid` with floor-mid → infinite loop (use ceil-mid `lo + (hi-lo+1)/2` if you need "last T"). Overflow in `(lo+hi)/2`. Predicate not monotone → wrong. |

```cpp
// first index where pred is true, in [lo, hi]; hi must be a true-or-sentinel position
int lo = 0, hi = n;                     // n = "not found" sentinel
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (pred(mid)) hi = mid; else lo = mid + 1;
}
return lo;                              // == n if none

// last index where pred is true (pred is T T T F F):
while (lo < hi) { int mid = lo + (hi - lo + 1) / 2; if (pred(mid)) lo = mid; else hi = mid - 1; }
```

| Want | Predicate | STL |
|---|---|---|
| first `>= x` | `a[mid] >= x` | `lower_bound` |
| first `> x` | `a[mid] > x` | `upper_bound` |
| last `<= x` | first `> x`, then −1 | `prev(upper_bound)` |
| count of x | `upper − lower` | `equal_range` |

## Card: Binary search on the ANSWER
| | |
|---|---|
| **Hook** | "I can't compute the best X directly, but for a given X I can **check** feasibility greedily in O(n). Feasibility is monotone in X." |
| **Triggers** | "minimum capacity / speed / time / max-load such that…", "split into k parts minimizing the largest sum", "maximize the minimum distance" |
| **Recipe** | (1) Range `[lo, hi]` of possible answers. (2) `ok(x)` greedy check. (3) Confirm monotonicity aloud. (4) First-T template. |
| **EDA analogues** | Minimum feasible clock period; minimum routing channel width W for which the router succeeds (VPR does exactly this); smallest die size that fits utilization. |

## Rotated sorted array: the one idea
At any `mid`, **one half is sorted**. Check whether the target lies in the sorted half's range. If yes, go there; else go to the other half.
Min of rotated: compare `a[mid]` with `a[hi]`. If `a[mid] > a[hi]`, the min is right of mid; else it's at mid or left of it.

---

## Problems (hint ladders)

### P03-1 · First and Last Position (LC 34) ★★ · `searchRange`
<details><summary>Hint</summary>Two boundary searches with two different predicates.</details>
<details><summary>Approach check</summary>lower_bound(x) and upper_bound(x)−1; verify a[first]==x. O(log n).</details>

### P03-2 · Search in Rotated Sorted Array (LC 33) ★★★ · `searchRotated`
Distinct values.
<details><summary>Hint 1</summary>After choosing mid, which half is guaranteed sorted?</details>
<details><summary>Hint 2</summary>If a[lo] <= a[mid], the left half is sorted. Is the target inside [a[lo], a[mid])?</details>
<details><summary>Approach check</summary>Classic `while (lo <= hi)` exact-match search with the sorted-half test. O(log n). Follow-up: duplicates (LC 81) → when a[lo]==a[mid]==a[hi], shrink both ends, worst case O(n).</details>

### P03-3 · Find Peak Element (LC 162) ★
<details><summary>Hint</summary>If a[mid] < a[mid+1], a peak must exist to the right. Why?</details>

### P03-4 · Koko Eating Bananas (LC 875) ★★ · `minEatingSpeed`
Piles `p[i]`, `h` hours. Each hour she eats up to `k` from one pile. Find the min integer `k` that finishes in `h` hours.
<details><summary>Hint 1</summary>If speed k works, does k+1 work?</details>
<details><summary>Hint 2</summary>Hours needed at speed k = Σ ceil(p[i]/k). Range of k?</details>
<details><summary>Approach check</summary>lo=1, hi=max(p). Check in O(n) using `(p + k - 1) / k`, with the sum in long long. Total O(n log max). Same template: ship packages (LC 1011), split array largest sum (LC 410).</details>

### P03-5 · Median of Two Sorted Arrays (LC 4) ★ (hard, lead-level stretch)
<details><summary>Hint</summary>Binary search the partition in the smaller array so the left halves have (m+n+1)/2 elements total and maxLeft ≤ minRight on both sides.</details>

### P03-6 · Integer square root (LC 69) ★
<details><summary>Approach check</summary>Last k with k*k ≤ x; use `long long` or compare `k <= x / k`.</details>

---

## Recall check
1. Write the first-T template from memory. Why does `lo = mid` loop forever with floor-mid?
2. `std::lower_bound` on a `std::set`: why is it O(n), and what do you call instead?
3. Three problems that are "binary search on answer". State `ok(x)` for each.
4. Rotated array: the one-line insight.
