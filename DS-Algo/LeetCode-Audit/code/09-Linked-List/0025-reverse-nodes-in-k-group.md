# 25. Reverse Nodes in k-Group

[Problem](https://leetcode.com/problems/reverse-nodes-in-k-group/) · Hard · Linked List → Reverse in groups

LeetCode tags: linked-list, recursion

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-20 16:59 IST · Accepted · C++

[submission 918719901](https://leetcode.com/submissions/detail/918719901/) · tests 62/62 · runtime 3 ms (beats 2.3%)

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
    int length(ListNode *curr){
        int len =0;
            
            if(curr == NULL){
                return 0;
            }
            
            while(curr){
                curr = curr->next;
                len++;
            }
            return len;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode * curr = head;

            ListNode * prev = NULL, *next;
            int len = length(head);
            
            if(len < k){
                return head;
            }
            // 1->2->3->4->5->6->7 k =2
            // curr = 2
            // next = 2
            // prev = 1
            // head 1 <-2 
            // head 2->1 ->4->3 ->6->5 ->7
            
            for(int i=0;i<k;i++){
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head->next = reverseKGroup(curr,k);
            return prev;

            int reverse = len/k;
            curr = head;
            bool flag = false;
            ListNode * tail, *prevhead, *ans = head;
            while(reverse --){
                // lasthead = curr;
                // prev = NULL;
                for(int i=0;i<k;i++){
                    next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                if(!flag){
                    ans = prev;
                    flag = true;
                }
                cout<<prev->val<<":"<<curr->val<<"::";
                prev->next = head;
                // head->next = curr;
                head = curr;
                cout<<prev->val<<":"<<curr->val<<"::";
                // prevHead = 
                tail = curr;
            }
            return ans;
    }
};
```

## Attempt 2 · 2025-03-23 18:52 IST · Accepted · C++

[submission 1583325959](https://leetcode.com/submissions/detail/1583325959/) · tests 62/62 · runtime 0 ms (beats 100%)

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) return head;
        ListNode *curr = head, *prev = NULL;
        int count = 0;
        
        while (curr && count < k ) curr = curr->next, count++;
        if (count < k) return head;

        curr = head;
        prev = NULL;
        count = k;
        while (count--) {
            ListNode * next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        } 
        head->next = reverseKGroup(curr, k);
        return prev;
    }
};
```
