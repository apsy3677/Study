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
