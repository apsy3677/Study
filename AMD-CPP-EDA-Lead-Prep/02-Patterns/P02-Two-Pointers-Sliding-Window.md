# P02: Two Pointers & Sliding Window

> Practice file: `06-Practice/day1.cpp` · Striver: SDE Sheet (two pointers, strings)
> AMD reports: 3Sum, **Trapping Rain Water**, Move Zeroes, Merge Sorted Array, Longest Substring without Repeating, Container With Most Water.

---

## Card A: Opposite-end pointers = "each step discards a loser"
| | |
|---|---|
| **Hook** | Two people walking toward each other on a **sorted** line. Each step, one of them can prove its current position can never be part of a better answer, so it moves. |
| **Triggers** | sorted input (or sortable), pair/triplet sums, palindrome check, container/area, "in place" |
| **Invariant** | Every pair outside `[l, r]` has already been considered or proven useless. |
| **Traps** | Duplicates in 3Sum (skip equal neighbours **after** a match). Forgetting to sort. `l < r`, not `l <= r`, for pairs. |

```cpp
sort(a.begin(), a.end());
int l = 0, r = n - 1;
while (l < r) {
    int s = a[l] + a[r];
    if (s == target) { /* record */ ++l; --r; }
    else if (s < target) ++l;          // a[l] is too small with ANY remaining r
    else --r;                          // a[r] is too big with ANY remaining l
}
```

## Card B: Same-direction pointers (read/write) = "compaction"
| | |
|---|---|
| **Hook** | `write` is the end of the "good" prefix; `read` scans ahead. |
| **Use** | move zeroes, remove duplicates from sorted array, remove element, partition |
| **Invariant** | `a[0..write-1]` contains exactly the kept elements, in order. |

```cpp
int w = 0;
for (int r = 0; r < n; ++r) if (keep(a[r])) a[w++] = a[r];   // (swap(a[w++], a[r]) to preserve the rest)
```

**Merge Sorted Array into `a` (space for `m+n`):** fill from the **back**, so you never overwrite unread data.

**Dutch National Flag (0/1/2):** `low`, `mid`, `high`. Invariant: `[0,low)`=0, `[low,mid)`=1, `(high,n-1]`=2. On a 2, swap with high and **don't** advance mid.

## Card C: Sliding window = "the caterpillar"
| | |
|---|---|
| **Hook** | The head (`right`) always moves forward. The tail (`left`) moves only to **repair** the window when it breaks the rule. Record the answer when the window is valid. |
| **Triggers** | "longest/shortest **contiguous** subarray/substring such that …", "at most k distinct", "all positive numbers, sum ≥ target", anagram/permutation in string |
| **Invariant** | After the inner `while`, `s[left..right]` is the longest valid window ending at `right`. |
| **Only works if** | the validity is **monotone**: shrinking a valid window keeps it valid, and growing an invalid one keeps it invalid. Negatives in a sum problem break this, so use P01 prefix sums. |

```cpp
// LONGEST valid window
int left = 0, best = 0;
for (int right = 0; right < n; ++right) {
    add(s[right]);
    while (!valid()) remove(s[left++]);          // repair
    best = max(best, right - left + 1);           // record at valid state
}

// SHORTEST valid window (e.g., min window substring, min subarray sum >= target)
for (int right = 0; right < n; ++right) {
    add(s[right]);
    while (valid()) { best = min(best, right - left + 1); remove(s[left++]); }  // record, THEN shrink
}
```
**"Exactly k"** = `atMost(k) − atMost(k−1)`.

## Card D: Trapping Rain Water = "the lower wall decides"
| | |
|---|---|
| **Hook** | Water above bar i = `min(maxLeft, maxRight) − h[i]`. With two pointers, whichever side has the **smaller** max is the bottleneck, so you can finalize that side now. |
| **Invariant** | If `leftMax <= rightMax`, the water at `l` is exactly `leftMax − h[l]`: some wall on the right is at least `rightMax >= leftMax`. |
| **Alternatives** | Prefix max arrays O(n) space · monotonic stack (fills "layers", good follow-up). |

---

## Problems (hint ladders)

### P02-1 · 3Sum (LC 15) ★★★ · `threeSum`
All unique triplets summing to 0.
<details><summary>Hint 1</summary>Fix one element. What's left is a problem you already know.</details>
<details><summary>Hint 2</summary>How do you avoid duplicate triplets without a set?</details>
<details><summary>Approach check</summary>Sort. For each i (skip if a[i]==a[i-1]), two pointers on (i+1, n-1). After a match, move both and skip equal values. O(n²), O(1) extra (ignoring output). Early break if a[i] > 0.</details>

### P02-2 · Move Zeroes (LC 283) ★★ · `moveZeroes`
Keep the relative order of non-zeros, in place.
<details><summary>Approach check</summary>Read/write pointers; swap `a[w++]` with `a[r]` when a[r] ≠ 0. O(n), minimal writes.</details>

### P02-3 · Trapping Rain Water (LC 42) ★★★ · `trap`
<details><summary>Hint 1</summary>For a single bar, what determines the water above it?</details>
<details><summary>Hint 2</summary>Can you compute that without knowing BOTH maxima exactly?</details>
<details><summary>Hint 3</summary>Move the pointer on the side whose running max is smaller.</details>
<details><summary>Approach check</summary>Two pointers with leftMax and rightMax. O(n)/O(1). Be ready for the stack version and the "2D (Trapping Rain Water II) → min-heap from the border" follow-up.</details>

### P02-4 · Merge Sorted Array (LC 88) ★★ · `mergeSorted`
<details><summary>Approach check</summary>Three pointers from the back: i=m-1, j=n-1, k=m+n-1. Loop while j ≥ 0 (leftover a[i] is already in place).</details>

### P02-5 · Longest Substring Without Repeating Characters (LC 3) ★★★ · `lengthOfLongestSubstring`
<details><summary>Hint 1</summary>When the window gets a duplicate, where must `left` jump to?</details>
<details><summary>Approach check</summary>last-seen index array[256]; `left = max(left, last[c]+1)`. O(n)/O(Σ). Classic bug: letting `left` move backwards (that's why you need the max, or check `last[c] >= left`).</details>

### P02-6 · Minimum Window Substring (LC 76) ★★ · `minWindow`
Smallest window of s containing all chars of t (with multiplicity).
<details><summary>Hint 1</summary>Is this the "longest" or the "shortest" window template?</details>
<details><summary>Hint 2</summary>How do you know in O(1) that the window covers t?</details>
<details><summary>Approach check</summary>need[128] counts + a `missing` counter (the number of chars still needed). Expand right; when missing==0, record, then shrink left while it stays valid. O(|s|+|t|).</details>

### P02-7 · Container With Most Water (LC 11) ★★
<details><summary>Hint</summary>Why is it always safe to move the shorter line?</details>
<details><summary>Approach check</summary>The area is limited by the shorter line; moving the taller one can't increase the height and definitely reduces the width. O(n).</details>

### P02-8 · Sort Colors / Dutch Flag (LC 75) ★
<details><summary>Approach check</summary>low/mid/high pointers, one pass. When you swap with high, don't advance mid (the swapped-in value is unexamined).</details>

---

## Recall check
1. What property must hold for sliding window to work? Give a problem where it fails.
2. The "longest" vs "shortest" window template: where do you record the answer?
3. Trapping rain water: why is it OK to finalize the side with the smaller max?
4. How do you turn "exactly k distinct" into sliding windows?
5. Why merge from the back in LC 88?
