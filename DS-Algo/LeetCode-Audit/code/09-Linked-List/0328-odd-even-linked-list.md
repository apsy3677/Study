# 328. Odd Even Linked List

[Problem](https://leetcode.com/problems/odd-even-linked-list/) · Medium · Linked List → Re-linking

LeetCode tags: linked-list

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 14:30 IST · Accepted · C++

[submission 921750222](https://leetcode.com/submissions/detail/921750222/) · tests 70/70 · runtime 18 ms (beats 0.7%)

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
    ListNode* oddEvenList(ListNode* head) {
        // odd pointing to odd element, even pointing to even elements
        if(!head) return head;
        ListNode *odd = head, *even = head->next, *evenHead = even;
        // given order as odd->even->odd->even
        while(even !=NULL && even->next !=NULL){
            // if(even->val % 2 == 0){
            //     // remove from linklist and add to even list
            //     odd->next = even->next;
            //     odd = odd->next;
            // }
            odd->next = even->next;
            odd = odd->next;
            even->next = even->next->next;
            even = even->next;
            

        } 
        odd->next = evenHead;
        return head;
    }
};
```
