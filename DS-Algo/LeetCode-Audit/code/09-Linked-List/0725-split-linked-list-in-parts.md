# 725. Split Linked List in Parts

[Problem](https://leetcode.com/problems/split-linked-list-in-parts/) · Medium · Linked List → Split by length

LeetCode tags: linked-list

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-03-25 14:59 IST · Wrong Answer · C++

[submission 921762395](https://leetcode.com/submissions/detail/921762395/)

_Code not returned by LeetCode._

## Attempt 2 · 2023-03-25 15:00 IST · Accepted · C++

[submission 921762544](https://leetcode.com/submissions/detail/921762544/) · tests 43/43 · runtime 8 ms (beats 0.1%)

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
    int len(ListNode* head){
        int len =0;
        while(head){head = head->next; len++;}
        return len;
    }
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> ans;
        int length = len(head);
        
        // if(!head || length == 0) return ans;
        
        int mod = length % k;
        int split = length/k ;
        ListNode * curr = head;
        while(k--){
            int count = split + (mod-- >0 ? 1: 0);
            ListNode * prev = curr;
            ans.push_back(curr); // add  splitting

            while(curr && count--){
                prev = curr;
                curr = curr->next;
            }
            if(prev)
                prev->next = NULL;
        }
        // int nul = k -ans.size();
        // if(nul){
        //     ans.push_back(NULL);
        // }
        return ans;
    }
};
```
