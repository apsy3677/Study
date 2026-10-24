# 21. Merge Two Sorted Lists

[Problem](https://leetcode.com/problems/merge-two-sorted-lists/) · Easy · Linked List → Merge

LeetCode tags: linked-list, recursion

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-23 10:14 IST · Accepted · C++

[submission 955548288](https://leetcode.com/submissions/detail/955548288/) · tests 208/208 · runtime 20 ms (beats 0.5%)

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
    ListNode * mergeTwoLinkedList(ListNode *l1, ListNode *l2){
        ListNode *head = NULL, *curr = NULL;

        while(l1 && l2){
            if(l1->val <= l2->val ){
                if(!head) head = l1, curr = l1;
                else{
                    curr->next = l1;
                    curr = curr->next;
                }
                cout<<l1->val<<" ";
                l1 = l1->next;
            }
            else{
                if(!head) head = l2, curr = l2;
                else{
                    curr->next = l2;
                    curr = curr->next;
                }
                cout<<l2->val<<" ";
                l2 = l2->next;

            }
        }
        while(l1 ){ if(!curr) return l1;
            curr->next = l1; curr = curr->next; l1 = l1->next;
        }
        while(l2 ){if(!curr) return l2;
        curr->next = l2; curr = curr->next; l2 = l2->next;}

        return head;
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        return mergeTwoLinkedList(list1, list2);
    }
};
```

## Attempt 2 · 2023-05-23 10:19 IST · Accepted · C++

[submission 955550808](https://leetcode.com/submissions/detail/955550808/) · tests 208/208 · runtime 12 ms (beats 0.5%)

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
    ListNode * mergeTwoLinkedList(ListNode *l1, ListNode *l2){
        ListNode *head = NULL, *curr = NULL;

        while(l1 && l2){
            if(l1->val <= l2->val ){
                if(!head) head = l1, curr = l1;
                else{
                    curr->next = l1;
                    curr = curr->next;
                }
                cout<<l1->val<<" ";
                l1 = l1->next;
            }
            else{
                if(!head) head = l2, curr = l2;
                else{
                    curr->next = l2;
                    curr = curr->next;
                }
                cout<<l2->val<<" ";
                l2 = l2->next;

            }
        }
        while(l1 ){ if(!curr) return l1;
            curr->next = l1; curr = curr->next; l1 = l1->next;
        }
        while(l2 ){if(!curr) return l2;
        curr->next = l2; curr = curr->next; l2 = l2->next;}

        return head;
    }

    ListNode * mergeTwoLinkedListUsingDummyNode(ListNode *l1, ListNode *l2){
        ListNode *head = new ListNode(INT_MIN);
        ListNode *curr = head;

        while(l1 && l2){
            if(l1->val <= l2->val ){
                curr->next = l1;
                l1 = l1->next;
            }
            else{
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;

        }
        
        curr->next = l1 ? l1 :l2;

        return head->next;
    }

    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        return mergeTwoLinkedListUsingDummyNode(list1, list2);
        // return mergeTwoLinkedList(list1, list2);
    }
};
```

## Attempt 3 · 2025-03-23 16:38 IST · Accepted · C++

[submission 1583232564](https://leetcode.com/submissions/detail/1583232564/) · tests 208/208 · runtime 0 ms (beats 100%)

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode * dummy = new ListNode(-1), *head;
        head = dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                dummy->next = list1;
                list1 = list1->next;
            } else {
                dummy->next = list2;
                list2 = list2->next;
            }
            dummy = dummy->next;
        }
        dummy->next = list1 ? list1 : list2;

        return head->next;
    }
};
```
