# 61. Rotate List

[Problem](https://leetcode.com/problems/rotate-list/) · Medium · Linked List → Rotate by k

LeetCode tags: linked-list, two-pointers

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 3

## Attempt 1 · 2023-03-25 15:14 IST · Runtime Error · C++

[submission 921768791](https://leetcode.com/submissions/detail/921768791/) · tests 2/231

Failing input:

```text
[]
0
```

Expected:

```text
[]
```

Runtime error:

```text
Line 30: Char 15: runtime error: member access within null pointer of type 'ListNode' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:39:15
```

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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* curr = head;
        // int n = length(head);
        int n =0;
        ListNode *prev = curr, *last = curr;

        while(curr){last = curr; curr=curr->next; n++;};
        
        // rotate list by k 
        // move elements after n-k, n-k+1, n-k+2...n to front
        if(k>n) k = k%n;
        int kth = n-k ;
        prev = curr = head;
        while(kth--){
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        if(curr){
            last->next = head;
            head = curr;
        }
        return head;
    }
};
```

## Attempt 2 · 2023-03-25 15:15 IST · Runtime Error · C++

[submission 921769122](https://leetcode.com/submissions/detail/921769122/) · tests 3/231

Failing input:

```text
[]
1
```

Expected:

```text
[]
```

Runtime error:

```text
Line 23: Char 22: runtime error: division by zero (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:32:22
```

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
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* curr = head;
        // int n = length(head);
        int n =0;
        ListNode *prev = curr, *last = curr;

        while(curr){last = curr; curr=curr->next; n++;};
        
        // rotate list by k 
        // move elements after n-k, n-k+1, n-k+2...n to front
        if(k>n) k = k%n;
        int kth = n-k ;
        prev = curr = head;
        while(kth--){
            prev = curr;
            curr = curr->next;
        }
        if(prev)
            prev->next = NULL;
        if(curr){
            last->next = head;
            head = curr;
        }
        return head;
    }
};
```

## Attempt 3 · 2023-03-25 15:16 IST · Runtime Error · C++

[submission 921769552](https://leetcode.com/submissions/detail/921769552/) · tests 5/231

Failing input:

```text
[1]
1
```

Expected:

```text
[1]
```

Runtime error:

```text
=================================================================
==31==ERROR: AddressSanitizer: heap-use-after-free on address 0x6020000003d8 at pc 0x000000370fcd bp 0x7ffd2a7b3d60 sp 0x7ffd2a7b3d58
READ of size 8 at 0x6020000003d8 thread T0
    #2 0x7f0fd3ae90b2  (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
0x6020000003d8 is located 8 bytes inside of 16-byte region [0x6020000003d0,0x6020000003e0)
f ... [1627 more chars]
```

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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || k==0 ) return head;
        ListNode* curr = head;
        // int n = length(head);
        int n =0;
        ListNode *prev = curr, *last = curr;

        while(curr){last = curr; curr=curr->next; n++;};
        
        // rotate list by k 
        // move elements after n-k, n-k+1, n-k+2...n to front
        if(k>n) k = k%n;
        int kth = n-k ;
        prev = curr = head;
        while(kth--){
            prev = curr;
            curr = curr->next;
        }
        if(prev)
            prev->next = NULL;
        if(curr){
            last->next = head;
            head = curr;
        }
        return head;
    }
};
```

## Attempt 4 · 2023-03-25 15:18 IST · Accepted · C++

[submission 921770509](https://leetcode.com/submissions/detail/921770509/) · tests 231/231 · runtime 11 ms (beats 0.7%)

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
    ListNode* rotateRight(ListNode* head, int k) {
        
        ListNode* curr = head;
        // int n = length(head);
        int n =0;
        ListNode *prev = curr, *last = curr;

        while(curr){last = curr; curr=curr->next; n++;};

        if(!head || k%n==0 ) return head;
        
        // rotate list by k 
        // move elements after n-k, n-k+1, n-k+2...n to front
        if(k>n) k = k%n;
        int kth = n-k ;
        prev = curr = head;
        while(kth--){
            prev = curr;
            curr = curr->next;
        }
        if(prev)
            prev->next = NULL;
        if(curr){
            last->next = head;
            head = curr;
        }
        return head;
    }
};
```
