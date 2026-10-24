# 92. Reverse Linked List II

[Problem](https://leetcode.com/problems/reverse-linked-list-ii/) · Medium · Linked List → Reverse a sublist

LeetCode tags: linked-list

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-20 18:17 IST · Accepted · C++

[submission 953897121](https://leetcode.com/submissions/detail/953897121/) · tests 44/44 · runtime 6 ms (beats 0.1%)

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(!head) return head;
        ListNode * curr= head, *prev = NULL, *next;

        while(curr && left > 1){
            prev = curr;
            curr= curr->next;
            left--;
            right--;
            // next = curr->next;
            // curr->next = prev;
            // prev = curr;
            // curr= next;
        }
        ListNode *temp = NULL, *tail = curr, *con = prev;
        while(right > 0){
            temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
            right--;
        }
        if(con){
            con->next = prev;
        }
        else{
            head = prev;
        }
        tail->next = curr;
        return head;
    }
};
```
