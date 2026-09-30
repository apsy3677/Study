# P01: Arrays, Hashing, Prefix Sums, Matrix Simulation

> Practice file: `06-Practice/day1.cpp` · Striver: SDE Sheet days 1–4 (arrays, hashing)
> AMD reports: Two Sum, Subarray Sum = K, Spiral Matrix, Rotate Image, stock "sell first then buy", Top-K, Roman numerals, atoi, reverse words.

---

## Card A: Hash map = "memory of the past"
| | |
|---|---|
| **Hook** | Walking left to right, at each index ask: *"Have I already seen the thing that completes me?"* |
| **Triggers** | pair with target, "seen before", duplicates, frequency, anagram, first unique, complement |
| **Invariant** | Before processing `a[i]`, the map holds exactly the information about `a[0..i-1]` I need. |
| **Traps** | Insert **after** the lookup (so you don't pair an element with itself). `m[k]` inserts on read. Hash for `pair` isn't built in. |

```cpp
unordered_map<int,int> idx;                 // value -> index
for (int i = 0; i < n; ++i) {
    if (auto it = idx.find(target - a[i]); it != idx.end()) return {it->second, i};
    idx[a[i]] = i;                           // insert AFTER the check
}
```

## Card B: Prefix sum = "turn a subarray question into a pair question"
| | |
|---|---|
| **Hook** | `sum(i..j) = P[j+1] − P[i]`. "Subarray sums to k" becomes "two prefix values differ by k", which is Two Sum on prefixes. |
| **Triggers** | subarray sum equals / divisible by k, **negatives allowed** (a sliding window fails with negatives), range-sum queries, equal 0s and 1s |
| **Invariant** | `count[s]` = how many prefixes seen so far have sum `s`. Seed `count[0] = 1` (the empty prefix). |
| **Traps** | Forgetting `count[0] = 1`. Overflow → `long long`. For "divisible by k", normalize the negative mod: `((s % k) + k) % k`. |

```cpp
unordered_map<long long,int> cnt{{0, 1}};
long long s = 0; int ans = 0;
for (int x : a) { s += x; if (auto it = cnt.find(s - k); it != cnt.end()) ans += it->second; ++cnt[s]; }
```
**2D prefix:** `P[i+1][j+1] = a[i][j] + P[i][j+1] + P[i+1][j] − P[i][j]`; rectangle sum by inclusion-exclusion. (EDA: density maps, congestion grids.)

## Card C: Kadane = "drop a negative past"
| | |
|---|---|
| **Hook** | Carry the best sum ending here. If the carried sum goes negative it only hurts, so **restart**. |
| **Invariant** | `cur` = max subarray sum **ending at i**; `best` = max over all `cur`. |
| **Variant** | Stock buy-sell once = Kadane on differences, or simply "track min so far". |

```cpp
int cur = a[0], best = a[0];
for (int i = 1; i < n; ++i) { cur = max(a[i], cur + a[i]); best = max(best, cur); }
```

## Card D: Matrix simulation = "shrinking boundaries"
| | |
|---|---|
| **Hook** | Spiral: four walls `top, bottom, left, right` that move inward after each side is walked. |
| **Rotate 90° clockwise in place** | **transpose** (swap `a[i][j]` with `a[j][i]` for `j > i`), then **reverse each row**. (Counter-clockwise: transpose, then reverse each column.) |
| **Traps** | Spiral on non-square matrices: after walking top and right, re-check `top <= bottom` and `left <= right` before walking bottom and left. |

## Card E: In-place tricks (when "O(1) extra space" is demanded)
- **Index marking:** for values in `1..n`, mark "seen" by negating `a[v-1]` (find duplicates or missing).
- **Boyer–Moore majority:** keep a candidate and a count; the count goes up if equal, down otherwise, and you switch the candidate at 0.
- **Dutch flag (0/1/2):** `low, mid, high` pointers (see P02).
- **Cyclic sort** for `0..n-1` permutations.

---

## Problems (hint ladders). Say the approach **before** opening hints.

### P01-1 · Two Sum (LC 1) ★★★ · `twoSum`
Return indices of two numbers adding to `target`. Exactly one answer exists.
- Say it first: brute force? Then the one-pass idea?
<details><summary>Hint 1</summary>For each element, what exact value would complete it?</details>
<details><summary>Hint 2</summary>Where can you look that value up in O(1)?</details>
<details><summary>Approach check</summary>One pass with a value→index map; look up before inserting. O(n) time, O(n) space. If sorted, use two pointers for O(1) space.</details>

### P01-2 · Subarray Sum Equals K (LC 560) ★★★ · `subarraySumK`
Count contiguous subarrays summing to k. Values may be **negative**.
<details><summary>Hint 1</summary>Why does a sliding window fail here?</details>
<details><summary>Hint 2</summary>Express the sum of a[i..j] with two prefix sums.</details>
<details><summary>Hint 3</summary>At index j you need the number of earlier prefixes equal to P − k.</details>
<details><summary>Approach check</summary>Map of prefix-sum counts seeded with {0:1}. O(n)/O(n). Follow-up: "longest subarray with sum k" → store the FIRST index of each prefix instead of a count.</details>

### P01-3 · Longest Consecutive Sequence (LC 128) ★★ · `longestConsecutive`
Unsorted array; find the length of the longest run of consecutive integers, in O(n).
<details><summary>Hint 1</summary>Sorting is O(n log n). What set lookup avoids it?</details>
<details><summary>Hint 2</summary>Only start counting from numbers that are the *start* of a run.</details>
<details><summary>Approach check</summary>`unordered_set`. Start from x only if x−1 is absent, then walk x+1, x+2, … Each element is visited at most twice, so O(n).</details>

### P01-4 · Maximum Subarray (LC 53) ★★ · `maxSubArray`
<details><summary>Hint</summary>What's the best sum of a subarray that must END at i?</details>
<details><summary>Approach check</summary>Kadane, O(n)/O(1). All-negative input → answer is the max element (a correct Kadane handles this if initialized with a[0]). Follow-up: return the indices, so track the start when you restart.</details>

### P01-5 · Spiral Matrix (LC 54) ★★★ · `spiralOrder`
<details><summary>Hint 1</summary>Keep 4 boundaries. What do you do after walking the top row?</details>
<details><summary>Hint 2</summary>Single row or single column left: which walks must be skipped?</details>
<details><summary>Approach check</summary>top/bottom/left/right; walk top (→) then top++, right (↓) then right--, if top ≤ bottom walk bottom (←) then bottom--, if left ≤ right walk left (↑) then left++. O(mn).</details>

### P01-6 · Rotate Image in place (LC 48) ★★★ · `rotateImage`
<details><summary>Hint</summary>Which two simple in-place operations compose to a 90° rotation?</details>
<details><summary>Approach check</summary>Transpose + reverse each row (clockwise). O(n²) time, O(1) space. Alternative: rotate 4 cells at a time, layer by layer.</details>

### P01-7 · Stock: buy-then-sell once (LC 121) and the AMD variant "sell first, then buy" ★★★ · `maxProfit`, `maxShortProfit`
`maxProfit`: max of `a[j] − a[i]` for `i < j` (0 if none). `maxShortProfit`: max of `a[i] − a[j]` for `i < j` (sell high first, buy back lower later; 0 if none).
<details><summary>Hint 1</summary>For each day as the *second* action, what's the best *first* action seen so far?</details>
<details><summary>Approach check</summary>Track the running min (for buy-then-sell) or running max (for sell-then-buy). O(n)/O(1). Follow-ups: unlimited transactions → sum all positive diffs. k transactions → DP.</details>

### P01-8 · Product of Array Except Self (LC 238) ★★ · `productExceptSelf`
No division, O(n).
<details><summary>Hint</summary>The answer at i = (product of everything left of i) × (product of everything right of i).</details>
<details><summary>Approach check</summary>Left-prefix pass into the output, then a right pass with a running suffix. O(1) extra space besides the output.</details>

### P01-9 · String to Integer atoi (LC 8) + Roman to Integer (LC 13) ★★ · `myAtoi`, `romanToInt`
atoi: skip leading spaces, optional sign, digits until a non-digit, clamp to the int range.
<details><summary>Hint (atoi)</summary>Detect overflow *before* it happens: compare `res` with `(INT_MAX − d) / 10`, or accumulate in `long long` and clamp.</details>
<details><summary>Hint (roman)</summary>If a symbol is smaller than the next one, subtract it; otherwise add it.</details>
<details><summary>Approach check</summary>Both O(n). The interviewer checks edge cases: "", "   ", "+-12", "-91283472332", "00012", "words 123".</details>

### P01-10 · Reverse Words in a String (LC 151) ★★ · `reverseWords`
Trim and collapse multiple spaces.
<details><summary>Hint</summary>Easy version: stringstream split + reverse the vector. For O(1) extra space, say it aloud: reverse the whole string, then reverse each word, then compact the spaces.</details>

---

## Recall check (close the file, answer aloud)
1. Why does the prefix-sum map need `{0:1}`?
2. Rotate clockwise = ? + ?
3. The Kadane invariant in one sentence.
4. What changes in "longest subarray with sum k" vs "count subarrays with sum k"?
5. `unordered_map` worst case, and when it happens? (Answer: all keys collide → O(n) per op. Adversarial inputs; mitigate with a custom hash or a `reserve`.)
