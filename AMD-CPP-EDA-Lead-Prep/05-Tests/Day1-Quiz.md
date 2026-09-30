# Day 1 Quiz: C++ core, STL, arrays/strings/binary search (20 min)
Answer from memory. Grade 0–3 using [answers/Day1-Answers.md](answers/Day1-Answers.md). Max 60.
Questions marked **(transfer)** are *new* problems. Name the pattern and the invariant, then sketch the approach.

1. Draw the object layout of `struct B { virtual void f(); int x; }; struct D : B { void f() override; double y; };` on x86-64 and give `sizeof(D)`.
2. You call a virtual function inside a base-class constructor. What runs, and why?
3. Write the signatures of all five special members for a class `Buf`, and mark which should be `noexcept`.
4. Why is `return std::move(local);` usually wrong?
5. `std::forward` vs `std::move`: when do you use each?
6. Explain the lifetime issue: `std::string_view name() { std::string s = "abc"; return s; }`.
7. A `std::unordered_map<std::pair<int,int>, int>` fails to compile. Why? Two fixes.
8. Why is `std::lower_bound(set.begin(), set.end(), x)` slow, and what should you call instead?
9. Priority queue: write the declaration of a min-heap of `pair<int,int>` and a heap of `Node` ordered by the smallest `cost` using a lambda.
10. Given constraints n ≤ 2·10⁵, what complexity do you target? n ≤ 20?
11. Prefix sums: why must the map start as `{0: 1}`? What changes to find the *longest* subarray with sum k?
12. Sliding window: state the invariant for "longest substring with at most K distinct characters".
13. Why does sliding window fail for "subarray sum = k" with negative numbers?
14. Trapping rain water with two pointers: why can you finalize the side with the smaller running max?
15. Binary search: write the "first true" template. What is the loop condition and how do you update?
16. Rotated sorted array: the one observation that makes O(log n) possible.
17. **(transfer)** Given an array of positive integers and S, find the minimum-length contiguous subarray with sum ≥ S.
18. **(transfer)** Given n packages with weights and D days, find the least ship capacity to ship them in order within D days.
19. **(transfer)** Find the minimum element in a rotated sorted array (distinct values) in O(log n).
20. **(transfer)** Given a matrix where each row and column is sorted, check if the target exists. Target O(m + n).
