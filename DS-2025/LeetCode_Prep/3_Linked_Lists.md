# Linked Lists Problems

## 1. Remove Nth Node From End of List (LC19)

**Problem**: Given a linked list, remove the n-th node from the end of the list and return its head.

**Approach**: Use two pointers with a gap of n nodes. When the first pointer reaches the end, the second pointer will be at the node before the one to be removed.

**Time Complexity**: O(L) where L is the length of the list - single pass.

**Space Complexity**: O(1) - constant extra space.

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // Create a dummy node to handle edge cases like removing the head
    ListNode dummy(0);
    dummy.next = head;
    
    ListNode* first = &dummy;
    ListNode* second = &dummy;
    
    // Move first pointer n+1 steps ahead
    for (int i = 0; i <= n; i++) {
        first = first->next;
    }
    
    // Move both pointers until first reaches the end
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    // Remove the nth node
    ListNode* toDelete = second->next;
    second->next = second->next->next;
    delete toDelete;
    
    return dummy.next;
}
```

## 2. Merge k Sorted Lists (LC23)

**Problem**: Merge k sorted linked lists into one sorted linked list.

**Approach**: Use a min-heap to select the next smallest element from all lists.

**Time Complexity**: O(N log k) where N is total nodes and k is number of lists.

**Space Complexity**: O(k) for the heap.

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    // Custom comparison for ListNode pointers
    auto compare = [](ListNode* a, ListNode* b) {
        return a->val > b->val;  // Min-heap
    };
    
    // Create min-heap of ListNode pointers
    priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);
    
    // Add the head of each list to the heap
    for (ListNode* list : lists) {
        if (list) minHeap.push(list);
    }
    
    // Dummy head for result list
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    // Process nodes in sorted order
    while (!minHeap.empty()) {
        // Get the smallest node
        ListNode* smallest = minHeap.top();
        minHeap.pop();
        
        // Add to result list
        tail->next = smallest;
        tail = tail->next;
        
        // Add next node from this list to heap
        if (smallest->next) {
            minHeap.push(smallest->next);
        }
    }
    
    return dummy.next;
}
```

## 3. Copy List with Random Pointer (LC138)

**Problem**: Create a deep copy of a linked list where each node contains a random pointer that could point to any node in the list or null.

**Approach**: Three-pass algorithm - create nodes, link random pointers, restore original list.

**Time Complexity**: O(n) - Three passes through the list.

**Space Complexity**: O(1) - No extra space except for the new list.

```cpp
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    
    // First pass: Create new nodes interleaved with original nodes
    Node* curr = head;
    while (curr) {
        Node* copy = new Node(curr->val);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }
    
    // Second pass: Assign random pointers for copied nodes
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }
    
    // Third pass: Separate original and copied lists
    curr = head;
    Node* copyHead = head->next;
    Node* copyCurr = copyHead;
    
    while (curr) {
        curr->next = curr->next->next;
        copyCurr->next = copyCurr->next ? copyCurr->next->next : nullptr;
        
        curr = curr->next;
        copyCurr = copyCurr->next;
    }
    
    return copyHead;
}
```

## 4. Merge Two Sorted Lists (LC21)

**Problem**: Merge two sorted linked lists into a single sorted linked list.

**Approach**: Compare the heads of both lists and build the result by taking the smaller one each time.

**Time Complexity**: O(n + m) where n and m are the lengths of the lists.

**Space Complexity**: O(1) - In-place merging.

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    // Handle empty list cases
    if (!l1) return l2;
    if (!l2) return l1;
    
    // Dummy head to simplify code
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    // Merge lists by selecting the smaller head each time
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    // Attach remaining nodes
    tail->next = l1 ? l1 : l2;
    
    return dummy.next;
}
```

## 5. Intersection of Two Linked Lists (LC160)

**Problem**: Find the node at which the intersection of two singly linked lists begins.

**Approach**: Use two pointers that switch to the head of the other list when reaching the end. They will meet at the intersection point.

**Time Complexity**: O(m + n) where m and n are the lengths of the two lists.

**Space Complexity**: O(1) - constant extra space.

```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    // When the pointers are at different positions or both null
    while (ptrA != ptrB) {
        // Move to next node or switch to the head of the other list
        ptrA = ptrA ? ptrA->next : headB;
        ptrB = ptrB ? ptrB->next : headA;
    }
    
    // Either found intersection node or both are null (no intersection)
    return ptrA;
}
```

## 6. Linked List Cycle Detection (LC141/142)

**Problem**: Determine if a linked list has a cycle and find the node where the cycle begins.

**Approach**: Use Floyd's Tortoise and Hare algorithm (slow/fast pointers).

**Time Complexity**: O(n) where n is the number of nodes.

**Space Complexity**: O(1) - constant extra space.

```cpp
// Detect if there's a cycle (LC141)
bool hasCycle(ListNode *head) {
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Fast pointer moves twice as fast as slow pointer
    while (fast && fast->next) {
        slow = slow->next;          // Move one step
        fast = fast->next->next;    // Move two steps
        
        // If they meet, there's a cycle
        if (slow == fast) return true;
    }
    
    // Fast pointer reached the end, no cycle
    return false;
}

// Find the start of the cycle (LC142)
ListNode *detectCycle(ListNode *head) {
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    bool hasCycle = false;
    
    // Phase 1: Detect cycle using slow/fast pointers
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            hasCycle = true;
            break;
        }
    }
    
    // No cycle found
    if (!hasCycle) return nullptr;
    
    // Phase 2: Find cycle start - reset slow to head and keep fast at meeting point
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;  // This is the start of the cycle
}
```

### Simple Explanation of Floyd's Cycle-Finding Algorithm:

Imagine two runners on a track - one running at normal speed (slow pointer) and one running at twice the speed (fast pointer). There are two scenarios:

1. **If there's no cycle**: The faster runner will reach the end of the track.

2. **If there's a cycle**: The faster runner will eventually lap the slower runner and they'll meet somewhere in the cycle.

When they meet, we know there's a cycle. To find where the cycle begins:
- Put the slow runner back at the start
- Keep the fast runner at the meeting point
- Have both runners move at the same speed (one step at a time)
- The point where they meet is the start of the cycle

**Why this works**: If the distance from the list head to the cycle start is 'x' and the meeting point is 'y' distance into the cycle, the math works out perfectly so that when they move at the same speed from their new starting positions, they'll meet exactly at the cycle's beginning.

The intuition behind this approach is elegant: if two linked lists intersect, then the last nodes must be the same. If we traverse both lists and switch to the other list when reaching the end, both pointers will travel the same distance before meeting at the intersection point or both becoming null (if there's no intersection).

## Key Patterns for Linked List Problems

1. **Two-Pointer Technique**:
   - Fast/slow pointers for cycle detection, middle finding
   - Leading/trailing pointers for nth operations from end
   - Dummy nodes to simplify edge cases (especially head operations)

2. **Iterative vs. Recursive**:
   - Iterative is usually better for space complexity
   - Recursive can be cleaner for some operations but watch the stack space

3. **In-Place Modification**:
   - Many linked list problems can be solved without extra space
   - Temporarily modify the structure, then restore if needed

4. **Common Operations**:
   - Reversing: Keep track of prev, curr, next pointers
   - Merging: Use dummy head and compare values
   - Detecting cycles: Floyd's tortoise and hare algorithm

5. **Edge Cases**:
   - Empty lists
   - Single node lists
   - Operations on head/tail nodes
   - Cycles or other irregular structures

When approaching a linked list problem in an interview, draw out the list and trace through your algorithm with pointers to visualize the changes and catch edge cases.
