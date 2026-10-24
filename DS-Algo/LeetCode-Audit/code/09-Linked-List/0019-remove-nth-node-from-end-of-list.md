# 19. Remove Nth Node From End of List

[Problem](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) · Medium · Linked List → Two pointers with gap

LeetCode tags: linked-list, two-pointers

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2025-03-23 18:13 IST · Accepted · C++

[submission 1583297279](https://leetcode.com/submissions/detail/1583297279/) · tests 208/208 · runtime 0 ms (beats 100%)

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
    // ListNode* removeNthFromEnd(ListNode* head, int n) {
    //     ListNode * curr = head, *prev = head;

    //     while (n--) {
    //         curr = curr->next;
    //     }
    //     while (curr->next) {
    //         curr = curr->next;
    //         head = head->next;
    //     }
    //     auto delNode = head->next;
    //     head->next = head->next->next;
    // }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
    // Create a dummy node to handle edge cases (e.g., removing the head)
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;

    ListNode* curr = dummy;
    ListNode* prev = dummy;

    // Move `curr` n steps ahead
    while (n--) {
        curr = curr->next;
    }

    // Move both `curr` and `prev` until `curr` reaches the end
    while (curr->next) {
        curr = curr->next;
        prev = prev->next;
    }

    // Remove the nth node from the end
    ListNode* delNode = prev->next;
    prev->next = prev->next->next;

    // Free the memory of the deleted node
    delete delNode;

    // Return the updated head of the list
    ListNode* newHead = dummy->next;
    delete dummy; // Free the dummy node
    return newHead;
}
};
```
