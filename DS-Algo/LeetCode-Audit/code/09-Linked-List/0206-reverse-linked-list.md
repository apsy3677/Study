# 206. Reverse Linked List

[Problem](https://leetcode.com/problems/reverse-linked-list/) · Easy · Linked List → Reverse

LeetCode tags: linked-list, recursion

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-20 18:10 IST · Accepted · C++

[submission 953894557](https://leetcode.com/submissions/detail/953894557/) · tests 28/28 · runtime 5 ms (beats 0.8%)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * curr= head, *prev = NULL, *next;

        while(curr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr= next;
        }
        return prev;
    }
};
```
