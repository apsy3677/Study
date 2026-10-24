# 237. Delete Node in a Linked List

[Problem](https://leetcode.com/problems/delete-node-in-a-linked-list/) · Medium · Linked List → Copy next node

LeetCode tags: linked-list

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-19 17:41 IST · Accepted · C++

[submission 953326026](https://leetcode.com/submissions/detail/953326026/) · tests 41/41 · runtime 9 ms (beats 36.2%)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(!node) return;

        ListNode *curr = node->next, *prev = node;

        while(curr->next != NULL){
            prev->val = curr->val;

            prev = curr;
            curr= curr->next;
        }
        prev->val = curr->val;
        prev->next = NULL;
    }
};
```

## Attempt 2 · 2023-05-19 17:43 IST · Accepted · C++

[submission 953326937](https://leetcode.com/submissions/detail/953326937/) · tests 41/41 · runtime 7 ms (beats 56.3%)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(!node) return;

        ListNode *curr = node->next, *prev = node;
        prev->val = curr->val;
        prev->next = curr->next;
    }
};
```

## Attempt 3 · 2023-05-20 13:48 IST · Accepted · C++

[submission 953787543](https://leetcode.com/submissions/detail/953787543/) · tests 41/41 · runtime 7 ms (beats 56.3%)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if(!node) return;

        ListNode *curr = node->next, *prev = node;
        prev->val = curr->val;
        prev->next = curr->next;
    }
};
```
