# 148. Sort List

[Problem](https://leetcode.com/problems/sort-list/) · Medium · Linked List → Merge sort on list

LeetCode tags: linked-list, two-pointers, divide-and-conquer, sorting, merge-sort

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 15:38 IST · Accepted · C++

[submission 921778877](https://leetcode.com/submissions/detail/921778877/) · tests 30/30 · runtime 179 ms (beats 5.2%)

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
    ListNode * getMid(ListNode *head){
        ListNode *midPrev = nullptr;

        while(head && head->next){
            midPrev = (midPrev == nullptr) ? head : midPrev->next;
            head = head->next->next;
        }
        ListNode * mid = midPrev->next;
        midPrev->next = nullptr;
        return mid;
    }
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode * mid = getMid(head);
        ListNode * left = sortList(head);
        ListNode * right = sortList(mid); // as mid has converted 2 Linklists

        return merge(left, right);
    }

    ListNode *merge(ListNode* left, ListNode* right){
        ListNode dummyHead(0);
        ListNode *it = &dummyHead;

        while(left && right){
            if(left->val < right->val){
                it->next = left;
                left = left->next;
            }
            else{
                it->next = right;
                right = right->next;
            }
            it = it->next;
        }
        if(left){
            it->next = left;
        }
        else{
            it->next = right;
        }
        return dummyHead.next;
    }
};
```
