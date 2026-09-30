# P05: Stack, Monotonic Stack & Monotonic Deque

> Practice file: `06-Practice/day2.cpp` · Striver: SDE Sheet (stack & queue days)
> AMD reports: implement stack/queue, LL using stack, valid parentheses (classic screen), trapping rain water (stack version), sliding window max.

---

## Card A: Plain stack = "most recent unfinished thing"
Triggers: matching brackets, undo, expression evaluation, DFS without recursion, "backspace string", nested structures.
```cpp
stack<char> st;
for (char c : s) {
    if (c == '(' || c == '[' || c == '{') st.push(c);
    else { if (st.empty() || st.top() != match(c)) return false; st.pop(); }
}
return st.empty();
```

## Card B: Monotonic stack = "the waiting room"
| | |
|---|---|
| **Hook** | Elements wait in a room until someone **bigger** arrives. The newcomer "resolves" everyone smaller, who leave and record the newcomer as their answer. The room is therefore always **decreasing** from bottom to top. |
| **Triggers** | next/previous greater or smaller, daily temperatures, stock span, largest rectangle in histogram, trapping rain water (stack version), remove k digits |
| **Invariant** | The stack holds indices of elements whose "next greater" hasn't been found yet, in **decreasing** value order. |
| **Complexity** | Each index is pushed and popped once, so **O(n)** total even with a nested while. |
| **Traps** | Store **indices**, not values (you need distances/widths). Strict vs non-strict comparison decides duplicate handling. Leftover elements have no answer (−1). Circular array → iterate 2n with `i % n`. |

```cpp
vector<int> nge(n, -1); stack<int> st;               // indices
for (int i = 0; i < n; ++i) {
    while (!st.empty() && a[st.top()] < a[i]) { nge[st.top()] = a[i]; st.pop(); }
    st.push(i);
}
```

| Want | Stack order | Pop when |
|---|---|---|
| next greater | decreasing | `a[top] < a[i]` |
| next smaller | increasing | `a[top] > a[i]` |
| previous greater | decreasing | the answer for `i` is the top **after** popping |

## Card C: Largest Rectangle in Histogram = "each bar asks how far it can stretch"
For bar i: width = (next smaller index) − (previous smaller index) − 1. One pass with an increasing stack. When you pop `h`, the new top is its left limit and `i` is its right limit. Push a sentinel `0` at the end to flush.
Maximal rectangle in a binary matrix = histogram per row (heights accumulate).

## Card D: Monotonic deque = "sliding window max"
| | |
|---|---|
| **Hook** | Keep a queue of "candidates that could still be the max". A new element evicts all smaller ones from the **back** (they can never win again). The front expires when it leaves the window. |
| **Invariant** | Deque holds indices in the window with **decreasing** values; the front is the window max. |

```cpp
deque<int> dq; vector<int> res;
for (int i = 0; i < n; ++i) {
    if (!dq.empty() && dq.front() <= i - k) dq.pop_front();          // expire
    while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();        // evict losers
    dq.push_back(i);
    if (i >= k - 1) res.push_back(a[dq.front()]);
}
```

## Card E: Design with stacks
- **Min stack:** push pairs `(val, minSoFar)`. Or a second stack of mins.
- **Queue with two stacks:** `in` for push; `out` for pop/peek; move all of in→out only when out is empty. Amortized O(1).
- **Stack with queues:** push then rotate the queue n−1 times (push O(n)).

---

## Problems (hint ladders)

### P05-1 · Valid Parentheses (LC 20) ★★ · `isValidParens`
<details><summary>Approach check</summary>Stack of openers; on a closer check the match; at the end the stack must be empty. Edge cases: "(", ")", "([)]".</details>

### P05-2 · Min Stack (LC 155) ★★ · `MinStack`
All ops O(1).
<details><summary>Hint</summary>What if each stack entry remembered the minimum at the time it was pushed?</details>

### P05-3 · Next Greater Element / Daily Temperatures (LC 739) ★★★ · `nextGreater`
Return, for each index, the next greater **value** (or −1).
<details><summary>Hint 1</summary>Brute force is O(n²). Which elements are still "waiting" for an answer?</details>
<details><summary>Approach check</summary>Decreasing stack of indices; when you pop, record. O(n). Daily temperatures = record `i − top` instead of the value.</details>

### P05-4 · Largest Rectangle in Histogram (LC 84) ★★ · `largestRectangle`
<details><summary>Hint 1</summary>For each bar as the SHORTEST bar of the rectangle, how wide can it go?</details>
<details><summary>Hint 2</summary>Its width is bounded by the previous smaller and the next smaller bars.</details>
<details><summary>Approach check</summary>Increasing stack. On pop of index j at i: height h[j], width = st.empty() ? i : i − st.top() − 1. Append a 0 sentinel. O(n).</details>

### P05-5 · Sliding Window Maximum (LC 239) ★★ · `maxSlidingWindow`
<details><summary>Hint</summary>Could a smaller element that arrived earlier ever be the max again once a bigger one arrives?</details>
<details><summary>Approach check</summary>Monotonic deque of indices, O(n). Alternatives: multiset O(n log k), heap with lazy deletion.</details>

### P05-6 · Implement Queue using Stacks (LC 232) ★★
<details><summary>Approach check</summary>Two stacks, transfer lazily. Explain the amortized analysis: each element moves at most twice.</details>

### P05-7 · Evaluate Reverse Polish Notation (LC 150) ★
<details><summary>Approach check</summary>Stack of operands; on an operator pop b, then a; push a op b. Careful with operand order for − and /.</details>

---

## Recall check
1. The monotonic stack invariant for "next greater", and why it's O(n).
2. Histogram: when you pop bar j at index i, what's the width?
3. Sliding max: two reasons an index leaves the deque.
4. Queue from two stacks: when do you transfer?
