# Day 1 Quiz: Answers

1. `D`: [vptr 8][x 4][pad 4][y 8] = **24 bytes**. There's one vptr, shared by the B subobject and D (single inheritance). The vtable of D has `&D::f` in f's slot (plus offset-to-top and RTTI before it).
2. The **Base** version (or UB/abort if it's pure virtual). During Base's constructor the vptr points to Base's vtable; the Derived part isn't constructed yet, so dispatching to it would touch uninitialized members.
3. `~Buf() noexcept` (implicit) · `Buf(const Buf&)` · `Buf& operator=(const Buf&)` · `Buf(Buf&&) noexcept` · `Buf& operator=(Buf&&) noexcept`. The move ops **must** be noexcept so `vector` moves them on reallocation.
4. It disables NRVO (the returned expression is no longer just the name of a local). `return local;` is elided or implicitly moved anyway. GCC warns with `-Wpessimizing-move`.
5. `std::move` when you *know* you're done with an object and want to allow moving. `std::forward<T>` inside templates taking a forwarding reference `T&&`, to pass the argument on with its original value category (perfect forwarding).
6. The view points into `s`'s buffer; `s` is destroyed on return → a **dangling** view → UB. Return `std::string` instead.
7. No `std::hash<std::pair<int,int>>` exists. Fixes: provide a custom hasher (`struct PairHash`), use `std::map` (ordered), or encode the key as one `long long` (`(long long)a << 32 | (unsigned)b`).
8. Set iterators are bidirectional, so `std::lower_bound` does O(log n) comparisons but **O(n) iterator steps**. Use the member `s.lower_bound(x)`: O(log n).
9. `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;` and `auto cmp = [](const Node& a, const Node& b){ return a.cost > b.cost; }; priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);`
10. n ≤ 2·10⁵ → O(n log n) or O(n). n ≤ 20 → O(2ⁿ · n) (subsets / bitmask) is fine.
11. `{0:1}` represents the empty prefix, so subarrays starting at index 0 are counted. For the **longest**: store the **first index** at which each prefix sum occurs (`firstIdx[0] = -1`), and the length = `i − firstIdx[s − k]`. Never overwrite the first index.
12. After shrinking, the window `s[left..right]` has ≤ K distinct characters (tracked by a count map + a distinct counter), and it's the longest valid window ending at `right`.
13. With negatives, validity isn't monotone: extending the window can decrease the sum, and shrinking can increase it. You can't decide when to move `left`. Use prefix sums + a hash map.
14. If `leftMax <= rightMax`, there's a wall of height ≥ `leftMax` somewhere on the right (namely the one giving `rightMax`), so the water at `l` is bounded exactly by `leftMax`: `leftMax − h[l]`. The unknown part of the right side can only be higher.
15. `while (lo < hi) { mid = lo + (hi-lo)/2; if (pred(mid)) hi = mid; else lo = mid + 1; } return lo;` with `hi` set to a known-true value or a sentinel.
16. At any mid, **at least one half is sorted**. Check whether the target lies in that sorted half's range to decide the direction.
17. Sliding window, the shortest-window template (positives → monotone): expand right; `while (sum >= S)` record the length, then shrink from the left. O(n). (Negatives → prefix sums + a monotonic deque.)
18. Binary search on the answer: lo = max weight, hi = total. `ok(cap)` greedily counts the days needed. First capacity with ok = true. O(n log Σ).
19. Compare `a[mid]` with `a[hi]`: if `a[mid] > a[hi]` the min is in `(mid, hi]` → `lo = mid+1`; else it's in `[lo, mid]` → `hi = mid`. Loop `while (lo < hi)`.
20. Staircase search: start at the top-right. If the value > target, go left; if < target, go down. Each step eliminates a row or a column → O(m+n).
