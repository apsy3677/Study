# P06: Heaps, Intervals, Sweep Line, Greedy (+ rectilinear geometry)

> Practice file: `06-Practice/day2.cpp` · Striver: SDE Sheet (heap, greedy days)
> AMD/EDA reports: **Merge Intervals**, **Top K Frequent**, **meeting rooms (your Cadence R1)**, **rectilinear segment intersection (your Cadence R1)**, segment tree (TechPrep), merge k sorted.

---

## Card A: Heap = "the bouncer who only knows the top"
| | |
|---|---|
| **Hook** | A heap answers exactly one question fast: *"who is the best right now?"* Push/pop O(log n), peek O(1). It does **not** support search or arbitrary delete. |
| **Triggers** | k-th largest/smallest, top-k, merge k sorted, running median, schedule the "earliest finishing", Dijkstra, "repeatedly take the min/max" |
| **Top-K largest** | **min**-heap of size k; the top is the k-th largest. O(n log k). (Quickselect `nth_element` gives O(n) average when you don't need a stream.) |
| **Running median** | max-heap for the lower half, min-heap for the upper half; keep sizes balanced (lower may have +1). |
| **Traps** | Comparator direction (see the Speed playbook C5). No decrease-key → push the new entry and skip stale ones on pop. `priority_queue` has no iteration. |

## Card B: Intervals = "sort by start, then decide on the last one"
| | |
|---|---|
| **Merge** | sort by start; if `cur.start <= last.end` → `last.end = max(last.end, cur.end)`, else push. |
| **Insert interval** | copy all ending before new.start; merge all overlapping; copy the rest. |
| **Min removals to make non-overlapping** | greedy by **end** time (activity selection): keep the interval that ends earliest. |
| **Traps** | Touching intervals `[1,2],[2,3]`: overlapping or not? **Ask!** (It changes `<` vs `<=`.) Merging needs `max` on end (containment). |

## Card C: Sweep line = "sort events, walk through time, maintain the active set"
| | |
|---|---|
| **Hook** | Turn each interval into two events, `(start, +1)` and `(end, −1)`. Sort. Walk. The running sum = how many are active right now. |
| **Meeting rooms II** | max running sum. Tie-break: process `−1` before `+1` at equal time if `[s,e)` is half-open. Heap version: min-heap of end times; pop while `top <= start`. |
| **EDA use** | Overlapping rectangles/shapes (DRC), counting wire overlaps, max congestion along a channel, interval/segment trees for spatial queries. |
| **Active set type** | a counter (rooms) · a `multiset` (sky-line heights) · a Fenwick/segment tree over y (count H/V crossings, rectangle union area). |

## Card D: Rectilinear geometry (EDA flavour, from your Cadence round)
- **Rect overlap:** `A.x1 < B.x2 && B.x1 < A.x2 && A.y1 < B.y2 && B.y1 < A.y2` (strict = positive area; `<=` if touching counts).
- **Overlap area:** `max(0, min(x2s) − max(x1s)) * max(0, min(y2s) − max(y1s))`.
- **Axis-parallel segments intersect:** normalize so `x1<=x2`, `y1<=y2`.
  - H vs V: `V.x ∈ [H.x1, H.x2]` **and** `H.y ∈ [V.y1, V.y2]`.
  - H vs H: same y **and** the x-ranges overlap (`max(x1s) <= min(x2s)`). V vs V is symmetric.
- **Count all H–V crossings** among n segments in O(n log n): sweep x. Events: H-start (add y), V (query the count of active y in `[y1,y2]` with a Fenwick tree over compressed y), H-end (remove y). Order at equal x: add, query, remove (if touching counts).
- **General segments:** orientation test `cross(b−a, c−a)`; proper intersection when the orientations differ on both sides, plus collinear-overlap special cases.

## Card E: Greedy = "make the locally safe choice and prove it with an exchange argument"
Triggers: activity selection, jump game, gas station, assign cookies, minimum platforms, Huffman.
Always **say** why it's safe: *"If an optimal solution didn't pick the earliest-ending interval, swap it in. It ends no later, so nothing breaks."*

---

## Problems (hint ladders)

### P06-1 · Merge Intervals (LC 56) ★★★ · `mergeIntervals`
<details><summary>Hint</summary>After sorting by start, when does the current interval overlap the last merged one?</details>
<details><summary>Approach check</summary>Sort by start; compare with `res.back()`; extend with max. O(n log n). Ask about the touching intervals convention.</details>

### P06-2 · Meeting Rooms II / Min Platforms (LC 253) ★★★ · `minMeetingRooms`
<details><summary>Hint 1</summary>At any instant, how many meetings are running?</details>
<details><summary>Hint 2</summary>When a new meeting starts, which room could it reuse?</details>
<details><summary>Approach check</summary>Sort by start + min-heap of end times (pop while top ≤ start) → max heap size. Or two sorted arrays (starts, ends) with two pointers. O(n log n).</details>

### P06-3 · K-th Largest Element (LC 215) ★★ · `findKthLargest`
<details><summary>Approach check</summary>Min-heap of size k (O(n log k)), or `nth_element` / quickselect O(n) average, O(n²) worst (randomize the pivot). Discuss which you'd use for a stream vs a static array.</details>

### P06-4 · Merge k Sorted Lists (LC 23) ★★ · `mergeKLists`
<details><summary>Approach check</summary>Min-heap of (val, node) seeded with each head; pop, append, push next. O(N log k). Alternative: pairwise divide & conquer merging.</details>

### P06-5 · Find Median from Data Stream (LC 295) ★★ · `MedianFinder`
<details><summary>Hint</summary>Split the numbers into a lower half and an upper half. Which heap type for each?</details>
<details><summary>Approach check</summary>Max-heap `lo`, min-heap `hi`. Push to lo, move lo.top to hi, and if hi is bigger move one back. Median = lo.top or the average. O(log n) add, O(1) query.</details>

### P06-6 · Top K Frequent Elements (LC 347) ★★★ · (already in `cpp_toolkit.cpp`: re-derive, don't copy)
<details><summary>Approach check</summary>Count map + min-heap of size k (O(n log k)), or **bucket sort** by frequency (O(n)). Mention both.</details>

### P06-7 · Do two axis-parallel segments intersect? ★★ (EDA / Cadence) · `segmentsIntersect`
Each segment is horizontal or vertical, given by endpoints in any order. Touching counts as intersecting.
<details><summary>Hint 1</summary>Normalize the endpoints first. How many type combinations are there?</details>
<details><summary>Hint 2</summary>For H vs V, write the two containment conditions. For parallel ones, what must be equal?</details>
<details><summary>Approach check</summary>Normalize; 3 cases (HV, HH, VV); closed-interval overlap `max(lo) <= min(hi)`. Degenerate point segments (both H and V) should still work if you treat a point as H. O(1).</details>

### P06-8 · Rectangle overlap area & union area ★ (EDA) · `rectOverlapArea`, `rectUnionArea`
Union area of n axis-aligned rectangles (n ≤ 200).
<details><summary>Hint 1</summary>Coordinate-compress the x and y edges. The plane becomes a grid of cells.</details>
<details><summary>Hint 2</summary>Mark the cells covered by any rectangle; sum the covered cell areas.</details>
<details><summary>Approach check</summary>O(n³) with compression is fine for n ≤ 200. At scale: sweep over x with a segment tree over y storing (cover count, covered length) → O(n log n). A lead should say that second part.</details>

### P06-9 · Non-overlapping Intervals (LC 435) ★
<details><summary>Approach check</summary>Sort by end; greedily keep the non-overlapping ones; the answer = n − kept.</details>

---

## Recall check
1. Top-k largest uses which heap and why? 2. Two ways to solve meeting rooms. 3. Event ordering at equal timestamps. Why does it matter?
4. H–V segment intersection condition. 5. How do you count all crossings among 10⁶ H/V wires fast? (Sweep + Fenwick.)
