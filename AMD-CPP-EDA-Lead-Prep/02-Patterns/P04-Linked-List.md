# P04: Linked Lists (AMD asks these a LOT)

> Practice file: `06-Practice/day2.cpp` · Striver: SDE Sheet days 5–6 (linked list)
> AMD reports: **reverse in K-groups**, **rotate by k**, **merge two sorted without extra space**, middle, remove duplicates (sorted), remove element, palindrome LL, add two numbers, LL using stack.
> **See it move:** [the linked-list trainer](../07-Revision/visualizers/linked-list-trainer.html) steps through reverse, reverse in k-groups, Floyd's cycle start and the LRU cache one pointer write at a time. Turn on Predict to call each rewiring.

---

## Card A: Pointer surgery = "save, cut, rewire, advance"
| | |
|---|---|
| **Hook** | Draw three boxes, **prev · cur · next**. You may only cut `cur->next` **after** saving `next`. |
| **Triggers** | reverse, reorder, rotate, remove, insert, k-group |
| **Invariant (reverse)** | `prev` is the head of the already-reversed prefix; `cur` is the head of the untouched suffix. |
| **Traps** | Losing the rest of the list (not saving next). Returning the old head. Not connecting the reversed segment back (k-group). Recursion depth on 10⁵ nodes. |

```cpp
ListNode* prev = nullptr, *cur = head;
while (cur) { ListNode* nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
return prev;
```

## Card B: Dummy head = "never special-case the head"
Any time the head might change (remove, merge, insert, partition), start with `ListNode dummy(0, head);` and return `dummy.next`.
Use a **stack-allocated** dummy (no leak), and say *"dummy avoids head special-cases"* out loud.

## Card C: Slow/fast pointers = "the tortoise and the hare"
| Use | Rule |
|---|---|
| **Middle** | fast moves 2, slow moves 1; when fast hits the end, slow is at the middle (for even n, pick first/second middle by the loop condition: `while (fast && fast->next)` → second middle). |
| **Cycle detect** | if they meet, there's a cycle. |
| **Cycle start** | after meeting, reset one pointer to head and move both 1 step; they meet at the cycle start. *(Why: distance head→start = distance meet→start mod cycle length.)* |
| **n-th from end** | move `fast` n steps first, then move both; slow stops before the target (start both at a dummy). |

## Card D: Merge = "zipper with a tail pointer"
```cpp
ListNode dummy(0); ListNode* t = &dummy;
while (a && b) { if (a->val <= b->val) { t->next = a; a = a->next; } else { t->next = b; b = b->next; } t = t->next; }
t->next = a ? a : b;
return dummy.next;
```
"**Without extra space**" = relink existing nodes (as above), O(1) extra; don't allocate new nodes.
**Sort a list:** merge sort (find middle, split, sort halves, merge). O(n log n), O(log n) recursion stack. Bottom-up merge sort gives true O(1) space.

## Card E: Compose the primitives
Most "hard" list problems = **middle + reverse + merge**:
- Palindrome LL = middle → reverse the 2nd half → compare → (restore).
- Reorder list L0→Ln→L1→Ln−1… = middle → reverse 2nd half → alternate merge.
- Rotate right by k = length + make it circular + break at `len − k % len`.
- Reverse k-group = count k → reverse that segment → connect → recurse or iterate.

---

## Problems (hint ladders)

### P04-1 · Reverse Linked List (LC 206) ★★★ · warm-up (also do it recursively)
<details><summary>Recursive hint</summary>`newHead = reverse(head->next); head->next->next = head; head->next = nullptr; return newHead;`. Mention the O(n) stack depth.</details>

### P04-2 · Reverse Nodes in k-Group (LC 25) ★★★ · `reverseKGroup`
Leftover < k nodes stay as they are.
<details><summary>Hint 1</summary>Before reversing, how do you know you HAVE k nodes?</details>
<details><summary>Hint 2</summary>Keep `groupPrev` (the node before the group). After reversing, what must groupPrev->next point to, and what does the old group head become?</details>
<details><summary>Hint 3</summary>Reverse the k nodes with prev initialized to `groupNext` (the node after the group). Then the tail auto-connects.</details>
<details><summary>Approach check</summary>Iterative with a dummy: find kth from groupPrev; if null, stop. Reverse [groupPrev->next .. kth] with prev = kth->next; then `tmp = groupPrev->next; groupPrev->next = kth; groupPrev = tmp;`. O(n) time, O(1) space.</details>

### P04-3 · Linked List Cycle II (LC 142) ★★ · `detectCycle`
Return the node where the cycle begins, or nullptr.
<details><summary>Hint</summary>After slow and fast meet, what happens if you restart one of them from head at speed 1?</details>
<details><summary>Approach check</summary>Floyd. Proof sketch: 2(a+b) = a+b+kL → a = kL − b, so walking a steps from the meet point lands on the start. O(n)/O(1).</details>

### P04-4 · Merge Two Sorted Lists (LC 21), "without extra space" ★★★ · `mergeTwoLists`
<details><summary>Approach check</summary>Dummy + tail relinking. Use `<=` for stability. Follow-up: merge k lists → min-heap (P06) or divide & conquer, O(N log k).</details>

### P04-5 · Palindrome Linked List (LC 234) ★★ · `isPalindromeList`
O(n) time, O(1) space.
<details><summary>Hint</summary>Combine two primitives from Card E.</details>
<details><summary>Approach check</summary>Middle → reverse the second half → compare → restore (a lead should mention restoring the input!).</details>

### P04-6 · Rotate List (LC 61) ★★ · `rotateRight`
<details><summary>Hint 1</summary>k can be larger than the length.</details>
<details><summary>Hint 2</summary>Make the list circular, then decide where to break it.</details>
<details><summary>Approach check</summary>len + tail; k %= len; if 0 return; tail->next = head; walk len−k−1 steps from head to the new tail; newHead = newTail->next; newTail->next = nullptr.</details>

### P04-7 · Remove N-th Node From End (LC 19) ★★ · `removeNthFromEnd`
<details><summary>Approach check</summary>Dummy; fast moves n+1 ahead of slow (both from the dummy); move together; `slow->next = slow->next->next` (and `delete` the node in real C++!).</details>

### P04-8 · Add Two Numbers (LC 2) ★★ · `addTwoNumbers`
Digits stored in reverse order.
<details><summary>Approach check</summary>Loop while (a || b || carry); dummy + tail. Follow-up (LC 445: digits in forward order) → reverse both, or use stacks.</details>

### P04-9 · Remove Duplicates from Sorted List (LC 83) ★★ · `deleteDuplicates`
<details><summary>Approach check</summary>While `cur && cur->next`: if equal, unlink next (delete it); else advance. Variant LC 82 (remove ALL duplicated values) → dummy + prev pointer.</details>

### P04-10 · Sort List (LC 148) ★ · `sortList`
<details><summary>Approach check</summary>Merge sort. Split with slow/fast where fast starts at head->next (so a 2-node list splits correctly).</details>

### P04-11 · Copy List with Random Pointer (LC 138) ★
<details><summary>Approach check</summary>Hash map old→new (O(n) space), or interleave copies A→A'→B→B' and fix random = old->random->next, then unweave (O(1) space).</details>

### P04-12 · Intersection of Two Lists (LC 160) ★
<details><summary>Approach check</summary>Two pointers that switch to the other head at the end; they meet at the intersection or at nullptr after ≤ m+n steps.</details>

---

## Lead-level talking points
- **Why do linked lists lose in practice?** Pointer chasing means a cache miss per node (~100 ns from DRAM) vs a contiguous vector. EDA netlists with 100M objects avoid per-node allocation. Use `std::list` only for **stable iterators + O(1) splice** (LRU).
- **Ownership in C++:** raw `ListNode*` in interviews, but in production use `unique_ptr<Node> next` (and beware: its recursive destructor can overflow the stack on long lists, so write an iterative destructor).
- **Memory:** interviewers like "I'd `delete` removed nodes / who owns them?"

## Recall check
1. Reverse the invariant in one sentence. 2. Why does cycle-start work? 3. Which three primitives solve palindrome and reorder?
4. How do you avoid the head special case? 5. Why can `unique_ptr`-linked lists crash in the destructor?
