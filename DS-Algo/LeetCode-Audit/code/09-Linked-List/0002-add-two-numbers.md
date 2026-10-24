# 2. Add Two Numbers

[Problem](https://leetcode.com/problems/add-two-numbers/) · Medium · Linked List → Digit addition

LeetCode tags: linked-list, math, recursion

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2024-02-11 00:53 IST · Runtime Error · C++

[submission 1171679926](https://leetcode.com/submissions/detail/1171679926/) · tests 32/1568

Failing input:

```text
[9]
[1,9,9,9,9,9,9,9,9,9]
```

Expected:

```text
[0,0,0,0,0,0,0,0,0,0,1]
```

Runtime error:

```text
Line 26: Char 45: runtime error: signed integer overflow: 9 * 1000000000 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:35:45
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
private:
    int power(int a, int n) {
        if(n==0) return 1;
        if(n%2 == 1) return power(a, n-1) * a;
        else return power(a*a, n/2);
    }

    int buildNumberFromLL(ListNode* l1) {
        ListNode *curr = l1;
        int number = 0;
        for(int i=0;curr!=NULL;i++) {
            if(i==0) {
                number = curr->val;
            } else {
                number = number + curr->val * power(10, i);
            }
            curr = curr->next;
        }
        return number;
    }

    ListNode* buildLLFromNumber(int number) {
        if(number == 0) return new ListNode();
        ListNode *curr = NULL, *head = NULL, *node = NULL;
        while(number !=0) {
            int remainder = number%10;
            number = number/10;
            if(head) {
                node = new ListNode(remainder);
                curr->next = node;
            } else {
                node = new ListNode(remainder);
                head = node;
            }
            curr = node;
        }
        return head;
    }

public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int n = buildNumberFromLL(l1);
        int m = buildNumberFromLL(l2);
        cout<<n<<" "<<m<<endl;
        return buildLLFromNumber(n+m);
    }
};
```

## Attempt 2 · 2024-02-11 01:03 IST · Accepted · C++

[submission 1171685978](https://leetcode.com/submissions/detail/1171685978/) · tests 1568/1568 · runtime 17 ms (beats 6.6%)

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
private:
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *currL1 = l1, *currL2 = l2, *head = NULL, *curr = NULL;
        int remainder, carry = 0 ;
        while(currL1 && currL2) {
            int number = currL1->val + currL2->val + carry;
            remainder = number%10;
            carry = number/10;
            if(head) {
                curr->next = new ListNode(remainder);
                curr = curr->next;
            } else {
                head = new ListNode(remainder);
                curr = head;
            }
            currL1 = currL1->next;
            currL2 = currL2->next;
        }

        while(currL1) {
            int number = currL1->val + carry;
            remainder = number%10;
            carry = number/10;
            if(head) {
                curr->next = new ListNode(remainder);
                curr = curr->next;
            } else {
                head = new ListNode(remainder);
                curr = head;
            }
            currL1 = currL1->next;
        }

        while(currL2) {
            int number = currL2->val + carry;
            remainder = number%10;
            carry = number/10;
            if(head) {
                curr->next = new ListNode(remainder);
                curr = curr->next;
            } else {
                head = new ListNode(remainder);
                curr = head;
            }
            currL2 = currL2->next;
        }
        if(carry != 0) {
            curr->next = new ListNode(carry);
        }
        return head;
    }
};
```
