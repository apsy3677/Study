# Agoda Pattern Cards (10 families)

> Same 5-part card format as the AMD prep: **Hook · Triggers · Invariant · Skeleton · Traps**, plus a **Follow-up to volunteer** (Agoda's "proactive" criterion).
> These cards cover what's *new or Agoda-specific*. For the basics, the AMD cards are still the reference: window/two pointers `AMD/02-Patterns/P02`, binary search `P03`, monotonic stack `P05`, heaps/intervals `P06`, DP `P10`, design `P12`.
> Read a card **before** its block of practice problems, and close it while coding.

---

## S. Stack parsing / recursive descent: "every `(` opens a new world; every `)` folds it back into its parent"

**Triggers (Agoda dressing):** chemical formula / molecule weight (asked twice) · `k[...]` decode · reverse inside parentheses · calculator · backspace `#` · "remove k adjacent equal".

**Invariant:** the top of the stack (or the current recursion frame) is *the group I'm building now*. Everything below is waiting for its `)`.

**Two implementations. Pick by the shape of the grammar:**
- **Recursive descent with an index by reference.** The cleanest for formulas: one function per grammar rule.
- **Explicit stack of (partial result, multiplier).** Avoids recursion depth (say this as the follow-up).

```cpp
// group := ( element | '(' group ')' ) count?   ...repeated until ')' or end
long long parseGroup(const string& s, size_t& i) {
    long long total = 0;
    while (i < s.size() && s[i] != ')') {
        long long unit;
        if (s[i] == '(') { ++i; unit = parseGroup(s, i); ++i; }   // consume '(' and ')'
        else unit = weight.at(readElement(s, i));                 // Uppercase + lowercase*
        total += unit * readCount(s, i);                          // digits*, default 1
    }
    return total;
}
```
Stack-of-runs (S5): `vector<pair<char,int>>`. Bump or push, **then** pop when the run reaches k.

**Traps:** multi-digit counts · default count 1 · two-letter atoms (`Mg`) · a `)` with no count · consume `)` exactly once · `long long` (counts multiply through nesting) · `isdigit((unsigned char)c)` · `k == 1` in S5 · `'\0'` sentinel to flush the last number (S7).

**Follow-up to volunteer:** "Invalid input: unbalanced parens or an unknown atom. I'd return `optional`/an error code, or throw `invalid_argument`. For 10⁵-deep nesting, an iterative stack avoids stack overflow. As a service: cache by formula string."

---

## M. Monotonic stack variants: "the waiting room" (AMD P05 card A/B)

**Triggers:** next/previous greater/smaller · "largest greater on the right" · span · nearest smaller · "contribution of each element as the minimum" · "smallest number after removing k digits".

**Decide two things before coding:**
1. **Who gets answered on a pop?** *Next* greater → the **popped** element gets the current as its answer. *Previous* smaller → the **current** element's answer is the top **after** popping.
2. **Ties:** `<` vs `<=` when popping decides whether equal values block each other.

```cpp
// Next greater (indices waiting for an answer, values decreasing)
for (int k = 0; k < 2 * n; ++k) {                  // 2n + k % n only if circular
    int x = a[k % n];
    while (!st.empty() && a[st.back()] < x) { ans[st.back()] = x; st.pop_back(); }
    if (k < n) st.push_back(k);
}
// Previous smaller (values increasing)
for (int x : a) {
    while (!st.empty() && st.back() >= x) st.pop_back();
    ans.push_back(st.empty() ? -1 : st.back());
    st.push_back(x);
}
```
**Contribution trick (M4):** `a[i]` is the minimum of `left[i] * right[i]` subarrays. Use **strictly smaller** on one side and **smaller-or-equal** on the other, so duplicates are counted once.
**Pivot (M3)** isn't a stack, but it's the same "all left smaller / all right greater" question: `prefixMax < a[i] < suffixMin`.

**Traps:** values vs indices in the stack · circular double push · equal elements · elements never popped keep the default `-1` · sentinels: use `LLONG_MIN/MAX` if `INT_MAX` can be in the input.

**Follow-up:** "Each index is pushed and popped once, so O(n) amortized. For a stream (stock span), keep (price, span) pairs: O(1) amortized per update."

---

## W. Sliding-window variants: "the caterpillar" (AMD P02 card C)

| Ask | Window rule | Record |
|---|---|---|
| Longest valid | grow right; **while invalid** shrink left | `best = max(best, right-left+1)` after shrinking |
| Return the substring | same | store `bestStart, bestLen`; `substr` at the end |
| Count subarrays (product < k, at most k distinct) | same | `count += right - left + 1` |
| Exactly k | `atMost(k) - atMost(k-1)` | — |
| Fixed length (anagram/permutation) | add right, remove `right - len` | compare `array<int,26>` |
| "Replace ≤ k chars" | valid while `len - maxFreq ≤ k` | max length |

```cpp
array<int,256> last; last.fill(-1);
for (int right = 0, left = 0; right < n; ++right) {
    unsigned char c = s[right];
    if (last[c] >= left) left = last[c] + 1;   // >= left: ignore stale indices ("abba")
    last[c] = right;
    // record window [left, right]
}
```
**Traps:** stale last-seen index (`abba`) · `k == 0` · product window with `k ≤ 1` · erase the map key at zero when counting distinct · return the substring vs the length · first vs last on ties.

**Follow-up:** "O(n): each pointer moves n times. For Unicode, use a hash map instead of `array<256>`. For a stream, the window state is the only memory needed."

---

## B. Binary search on the answer: "guess the answer, check it greedily"

**Triggers:** minimum capacity/speed/days/divisor such that… · **maximize the minimum** gap (asked) · minimize the maximum load · "Koko-like" (asked) · many queries over a sorted array (prefix sums + `lower_bound`).

**Invariant:** `feasible(x)` is monotone. Find the boundary.

```cpp
// FIRST x that works (minimize):          // LAST x that works (maximize the minimum):
while (lo < hi) {                          while (lo < hi) {
    auto mid = lo + (hi - lo) / 2;             auto mid = lo + (hi - lo + 1) / 2;   // upper mid!
    if (feasible(mid)) hi = mid;               if (feasible(mid)) lo = mid;
    else lo = mid + 1;                         else hi = mid - 1;
}                                          }
```
**Bounds:** capacity → `lo = max element`, `hi = sum`. Divisor/speed → `lo = 1`, `hi = max`. Gap → `lo = 1`, `hi = max - min`.
**Queries variant (B4):** sort + prefix sums; split each query at `lower_bound`; cost = `q*cntBelow - sumBelow + sumAbove - q*cntAbove`.

**Traps:** an infinite loop when maximizing with a lower mid · `long long` sums · ceil without floats: `(x + d - 1) / d` · `hi` too small (the answer must be inside `[lo, hi]`) · non-monotone check (re-verify!).

**Follow-up:** "O(n log range). If the check were expensive, I'd narrow the range first using an averages bound, e.g. `lo = ceil(sum/days)`."

---

## G. Greedy with sorting and heaps: "sort by whatever runs out first"

| Story | Greedy | Proof in one sentence |
|---|---|---|
| Airplanes/monsters arriving (G1) | sort arrival times; minute `i` kills the i-th earliest; fail if `arrival[i] ≤ i` | "Any order that shoots a later plane first can swap with an earlier one without hurting" (exchange argument) |
| Closest pairs (G2) | sort; the closest pair is adjacent | sorted order: a non-adjacent pair has a smaller gap inside it |
| Ranks (G4) | sort + `unique` + `lower_bound` | rank = position among distinct values |
| Coupons halving (G6) | always halve the current max (max-heap) | the saving `ceil(x/2)` grows with x |
| Cooldown scheduling (G8) | frame formula `(maxF-1)*(n+1)+ties` | the most frequent task forces the frame |
| No two adjacent equal (G9) | most frequent letter on even slots first | possible iff `maxF ≤ (n+1)/2` |
| Order constraints (G7) | find which items can move freely | `1` and `3` never cross; `2` floats |

**Traps:** floating-point times (use integer ceil or cross-multiplication) · the comparator must be a **strict** weak ordering (never `<=`) · formulas need empty-input guards (G8 says 23 for empty!) · a heap loop over `m` with no early exit when nothing improves · tie-break rules from the statement.

**Follow-up:** "O(n log n). With bounded keys, counting sort gives O(n): G1 only cares about arrivals ≤ n."

---

## I. Intervals, sweep and difference arrays: "+1 at start, −1 at end, walk through time" (the booking domain)

| Need | Tool |
|---|---|
| Max simultaneous / rooms needed | sort starts + min-heap of ends, or a `+1/-1` sweep |
| Capacity check at every moment (car pooling) | `map<int,int> delta`, prefix-walk |
| Many range additions (flight bookings) | difference array `diff[l] += v; diff[r+1] -= v;` + `partial_sum` |
| Reject a booking that causes a k-overlap (calendar) | tentatively add to the sweep map; **roll back** if it breaks |
| How many intervals overlap interval i | sorted starts and ends + binary search: `n - endsBefore(l) - startsAfter(r)` |
| Assign rooms with delays (Meeting Rooms III) | two heaps: free rooms by index, busy rooms by (end, index) |

**Traps:** closed vs half-open (`[1,2]` and `[2,3]`: overlap or not? **ask**) · same-time drop-off/pick-up (a sweep map nets them) · `long long` end times when meetings get delayed · heap ties: (end, index) · rejected bookings must not linger.

**Follow-up:** "For a hotel with millions of bookings: a segment tree with lazy propagation answers max overlap per range in O(log n). Concurrent bookings need a lock or optimistic versioning per room/date."

---

## J. Jump and stock DP as state machines: "what's the best I can have at step i in each state?"

```cpp
// J1 reachability: greedy farthest            // J2 min jumps: BFS levels without a queue
int far = 0;                                    for (int i = 0; i + 1 < n; ++i) {
for (int i = 0; i < n; ++i) {                       far = max(far, i + a[i]);
    if (i > far) return false;                      if (i == levelEnd) { ++jumps; levelEnd = far; }
    far = max(far, i + a[i]);                   }
}
// Stock with fee (J6): two states            // At most 2 transactions (J7): four states, in order
cash = max(cash, hold + p - fee);               buy1 = max(buy1, -p);        sell1 = max(sell1, buy1 + p);
hold = max(hold, cash - p);                     buy2 = max(buy2, sell1 - p); sell2 = max(sell2, buy2 + p);
```
**J4 (jump 1..k, max score):** `best[i] = a[i] + max(best[i-k..i-1])` → sliding-window max with a deque (AMD P05 card D).
**Say the DP first, then the greedy:** "dp[i] = reachable if some j < i with j + a[j] ≥ i is reachable: O(n²). The greedy keeps only the farthest reach: O(n)."

**Traps:** J2 loop must stop at `n-2` · J4 deque must drop indices `< i-k` · `INT_MIN + p` overflow (update `buy` first) · state update order · unlimited transactions = sum of positive deltas (J5).

**Follow-up:** "Generalize to k transactions: `buy[j], sell[j]` arrays, O(nk). If k ≥ n/2, it's the unlimited case."

---

## P. Palindromes and string DP

| Problem | Core |
|---|---|
| Count / longest palindromic substring (P1, P2) | **expand around 2n−1 centres** (odd and even): O(n²) time, O(1) space. Manacher O(n) is a mention-only follow-up |
| Decode ways (P3) | `ways[i] = ways[i-1] (if s[i] != '0') + ways[i-2] (if 10 ≤ s[i-1..i] ≤ 26)` |
| Word break (P4) | `ok[end] = ok[end - len] && dict has s.substr(end-len, len)` for len ≤ longest word |
| String chain (P5) | sort by length; `chain[w] = 1 + max(chain[w minus one char])` |
| Weighted interval scheduling (P6) | sort by end; `best[j] = max(skip, profit + best[last compatible])`, compatible via `upper_bound` |

**Traps:** forgetting even centres (`abba`) · `"0"`, `"06"`, `"100"` in decode ways · `substr` inside a hot loop (fine at these sizes, mention it) · `upper_bound` vs `lower_bound` when "end == next start" is allowed.

**Follow-up:** "The brute force is O(n³) (each substring × check). Centres make it O(n²). Manacher makes it O(n) by reusing mirror radii."

---

## H. Hash + array design: "an array for order/randomness, a map for O(1) lookup"

- **O(1) insert/delete/random (H1):** `vector<int> values` + `unordered_map<int,int> indexOf`. Delete = move the last element into the hole, **update its index, then erase**. Handles `val == last`.
- **Versioned values (H2):** per key a `vector<pair<time, value>>` (times increase) → `upper_bound` → `prev`.
- **LRU (AMD P12-1):** map + doubly linked list. Re-type it once on Day 3 as a warm-up.

**Traps:** erase before updating the moved index · `upper_bound` with a custom comparator takes `(value, element)` · `getRandom` on an empty set.

**Follow-up:** "Thread safety: one mutex, or sharding by key. For H2 at Agoda's scale: a time-series store; old versions compacted or TTL'd."

---

## R. Routes and graphs (travel flavour): "state, transition, frontier order" (AMD P08 card A)

| Story | Algorithm | Trap |
|---|---|---|
| Cheapest flight within k stops (R1) | **Bellman-Ford, k+1 rounds, copying the array each round** (or BFS by levels) | in-place relaxation chains several flights in one round. Plain Dijkstra on the node alone is **wrong** |
| Conversion rates / ratios (R2) | weighted graph a→b (v), b→a (1/v); BFS multiplying | unknown node → −1, even for `x/x` |
| Fewest buses (LC 815) | BFS over **routes**, not stops | `source == target` → 0 |
| Itinerary using every ticket (LC 332) | Hierholzer with a min-heap per airport | stuck at a dead end → append on the way back |

**Follow-up:** "With many queries on static ratios, union-find with weights answers each in near O(1)."
