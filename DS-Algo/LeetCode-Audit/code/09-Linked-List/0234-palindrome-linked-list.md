# 234. Palindrome Linked List

[Problem](https://leetcode.com/problems/palindrome-linked-list/) · Easy · Linked List → Middle + reverse

LeetCode tags: linked-list, two-pointers, stack, recursion

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2026-10-04 10:16 IST · Accepted · C++

[submission 2161729892](https://leetcode.com/submissions/detail/2161729892/) · tests 93/93 · runtime 4 ms (beats 48.9%)

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
    ListNode * reverse(ListNode * head) {
        ListNode *prev = nullptr, *curr = head, *next = nullptr;

        while(curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr= next;
        }
        return prev;
    }
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;

        ListNode *s = head, *f = head;

        while(f && f->next) {
            s = s->next; f = f->next->next;
        }

        ListNode * nh = reverse(s);
        bool ok = true;
        for (auto p=head, q = nh; q ; p=p->next, q=q->next ){
            if (p->val != q->val) {
                ok = false;
                break;
            }
        }
        s = reverse(nh);
        return ok;
    }
};
```
