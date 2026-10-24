# 143. Reorder List

[Problem](https://leetcode.com/problems/reorder-list/) · Medium · Linked List → Middle + reverse + merge

LeetCode tags: linked-list, two-pointers, stack, recursion

Attempts since Mar 2023: 6 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2025-03-23 17:10 IST · Accepted · C++

[submission 1583254762](https://leetcode.com/submissions/detail/1583254762/) · tests 12/12 · runtime 0 ms (beats 100%)

```cpp
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (!head) return;
//         ListNode *l1 = head, *slow = head, *fast = head, *mid = head;

//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         mid = slow;

//         // reverse from mid
//         ListNode *prev = NULL, *next, *curr = mid;
//         while (cur) {
//             next = cuur->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         mid = prev;

//         // Now reorder from list1 and list 2

//         while (mid->next) {
//             next = l1->next;
//             l1->next = mid;

//             ListNode *nextMid = mid->next;
//             mid->next = next;

//             l1 = next;
//             mid = nextMid;
//         }
//     }
// };

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return; // Handle edge cases

        // Step 1: Find the middle of the list
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* mid = slow;

        // Step 2: Reverse the second half of the list
        ListNode *prev = nullptr, *curr = mid, *next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        ListNode* secondHalf = prev; // The head of the reversed second half

        // Step 3: Merge the two halves
        ListNode *firstHalf = head;
        while (secondHalf->next) { // Stop when the second half is fully merged
            ListNode* temp1 = firstHalf->next;
            ListNode* temp2 = secondHalf->next;

            firstHalf->next = secondHalf;
            secondHalf->next = temp1;

            firstHalf = temp1;
            secondHalf = temp2;
        }
    }
};
```

## Attempt 2 · 2025-03-23 17:13 IST · Accepted · C++

[submission 1583256839](https://leetcode.com/submissions/detail/1583256839/) · tests 12/12 · runtime 0 ms (beats 100%)

```cpp
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        ListNode *l1 = head, *slow = head, *fast = head, *mid = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        mid = slow;

        // reverse from mid
        ListNode *prev = NULL, *next, *curr = mid;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        mid = prev;

        // Now reorder from list1 and list 2

        while (mid->next) {
            next = l1->next;
            l1->next = mid;

            ListNode *nextMid = mid->next;
            mid->next = next;

            l1 = next;
            mid = nextMid;
        }
    }
};

// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (!head || !head->next || !head->next->next) return; // Handle edge cases

//         // Step 1: Find the middle of the list
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         ListNode* mid = slow;

//         // Step 2: Reverse the second half of the list
//         ListNode *prev = nullptr, *curr = mid, *next = nullptr;
//         while (curr) {
//             next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         ListNode* secondHalf = prev; // The head of the reversed second half

//         // Step 3: Merge the two halves
//         ListNode *firstHalf = head;
//         while (secondHalf->next) { // Stop when the second half is fully merged
//             ListNode* temp1 = firstHalf->next;
//             ListNode* temp2 = secondHalf->next;

//             firstHalf->next = secondHalf;
//             secondHalf->next = temp1;

//             firstHalf = temp1;
//             secondHalf = temp2;
//         }
//     }
// };
```

## Attempt 3 · 2025-03-23 17:38 IST · Accepted · C++

[submission 1583273041](https://leetcode.com/submissions/detail/1583273041/) · tests 12/12 · runtime 0 ms (beats 100%)

```cpp
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head) return;
        ListNode *l1 = head, *slow = head, *fast = head, *mid = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        mid = slow;

        // reverse from mid
        ListNode *prev = NULL, *next, *curr = mid;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        mid = prev;

        // Now reorder from list1 and list 2
        while (l1 && mid->next) {
            next = l1->next;
            l1->next = mid;

            ListNode *nextMid = mid->next;
            mid->next = next;

            l1 = next;
            mid = nextMid;
        }
    }
};

// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (!head || !head->next || !head->next->next) return; // Handle edge cases

//         // Step 1: Find the middle of the list
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         ListNode* mid = slow;

//         // Step 2: Reverse the second half of the list
//         ListNode *prev = nullptr, *curr = mid, *next = nullptr;
//         while (curr) {
//             next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         ListNode* secondHalf = prev; // The head of the reversed second half

//         // Step 3: Merge the two halves
//         ListNode *firstHalf = head;
//         while (secondHalf->next) { // Stop when the second half is fully merged
//             ListNode* temp1 = firstHalf->next;
//             ListNode* temp2 = secondHalf->next;

//             firstHalf->next = secondHalf;
//             secondHalf->next = temp1;

//             firstHalf = temp1;
//             secondHalf = temp2;
//         }
//     }
// };
```

## Attempt 4 · 2025-03-23 17:53 IST · Accepted · C++

[submission 1583283239](https://leetcode.com/submissions/detail/1583283239/) · runtime 179 ms

_Code not returned by LeetCode._

## Attempt 5 · 2025-03-23 17:55 IST · Accepted · C++

[submission 1583284814](https://leetcode.com/submissions/detail/1583284814/) · tests 12/12 · runtime 175 ms (beats 5.0%)

```cpp
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next ) return;
        ListNode *l1 = head, *slow = head, *fast = head, *mid = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        mid = slow;

        // reverse from mid
        ListNode *prev = NULL, *next, *curr = mid;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        mid = prev;

        // Now reorder from list1 and list 2
        int i = 1;
        while (l1 && mid->next) {
            std::cout << "Iteration : " << i << ", " << l1->val << " || " 
                        << mid->val << "::: ";
            next = l1->next;
            l1->next = mid;
            ListNode *nextMid = mid->next;
            mid->next = next;

            l1 = next;
            mid = nextMid;
        }
        if (l1 && l1->next) l1->next->next = NULL;
    }
};

// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (!head || !head->next || !head->next->next) return; // Handle edge cases

//         // Step 1: Find the middle of the list
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         ListNode* mid = slow;

//         // Step 2: Reverse the second half of the list
//         ListNode *prev = nullptr, *curr = mid, *next = nullptr;
//         while (curr) {
//             next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         ListNode* secondHalf = prev; // The head of the reversed second half

//         // Step 3: Merge the two halves
//         ListNode *firstHalf = head;
//         while (secondHalf->next) { // Stop when the second half is fully merged
//             ListNode* temp1 = firstHalf->next;
//             ListNode* temp2 = secondHalf->next;

//             firstHalf->next = secondHalf;
//             secondHalf->next = temp1;

//             firstHalf = temp1;
//             secondHalf = temp2;
//         }
//     }
// };
```

## Attempt 6 · 2025-03-23 18:24 IST · Accepted · C++

[submission 1583304906](https://leetcode.com/submissions/detail/1583304906/) · tests 12/12 · runtime 0 ms (beats 100%)

```cpp
// /**
//  * Definition for singly-linked list.
//  * struct ListNode {
//  *     int val;
//  *     ListNode *next;
//  *     ListNode() : val(0), next(nullptr) {}
//  *     ListNode(int x) : val(x), next(nullptr) {}
//  *     ListNode(int x, ListNode *next) : val(x), next(next) {}
//  * };
//  */
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next ) return;
        ListNode *l1 = head, *slow = head, *fast = head, *mid = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Splitted into two lists.
        mid = slow->next;
        slow->next = nullptr;
        // reverse from mid
        ListNode *prev = NULL, *next, *curr = mid;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        mid = prev;

        // Now reorder from list1 and list 2
        int i = 1;
        while (mid) {
            // std::cout << "Iteration : " << i << ", " << l1->val << " || " 
                        // << mid->val << "::: ";
            next = l1->next;
            l1->next = mid;
            ListNode *nextMid = mid->next;
            mid->next = next;

            l1 = next;
            mid = nextMid;
        }
        // if (l1 && l1->next) l1->next->next = NULL;
    }
};

// class Solution {
// public:
//     void reorderList(ListNode* head) {
//         if (!head || !head->next || !head->next->next) return; // Handle edge cases

//         // Step 1: Find the middle of the list
//         ListNode *slow = head, *fast = head;
//         while (fast && fast->next) {
//             slow = slow->next;
//             fast = fast->next->next;
//         }
//         ListNode* mid = slow;

//         // Step 2: Reverse the second half of the list
//         ListNode *prev = nullptr, *curr = mid, *next = nullptr;
//         while (curr) {
//             next = curr->next;
//             curr->next = prev;
//             prev = curr;
//             curr = next;
//         }
//         ListNode* secondHalf = prev; // The head of the reversed second half

//         // Step 3: Merge the two halves
//         ListNode *firstHalf = head;
//         while (secondHalf->next) { // Stop when the second half is fully merged
//             ListNode* temp1 = firstHalf->next;
//             ListNode* temp2 = secondHalf->next;

//             firstHalf->next = secondHalf;
//             secondHalf->next = temp1;

//             firstHalf = temp1;
//             secondHalf = temp2;
//         }
//     }
// };
```
