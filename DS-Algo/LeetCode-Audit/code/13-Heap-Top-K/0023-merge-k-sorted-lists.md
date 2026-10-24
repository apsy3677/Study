# 23. Merge k Sorted Lists

[Problem](https://leetcode.com/problems/merge-k-sorted-lists/) · Hard · Heap / Top-K → K-way merge

LeetCode tags: linked-list, divide-and-conquer, heap-priority-queue, merge-sort, tournament-sort

Attempts since Mar 2023: 10 · accepted: 8 · failed before first AC: 0

## Attempt 1 · 2023-03-22 03:11 IST · Accepted · C++

[submission 919769431](https://leetcode.com/submissions/detail/919769431/) · tests 133/133 · runtime 32 ms (beats 18.6%)

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
    typedef  pair<int,int> PII;
public:
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int k= arr.size();
        ListNode * head=NULL , *last=NULL; // return this headlist
        // make_heap of first element of each linklist // making a map instead
        set< PII> heap;
        for(int i=0;i<k;i++){
            if(arr[i] == NULL)
                continue;
            PII pii = {arr[i]->val,i};
            heap.insert(pii);
        }
        while(!heap.empty()){
            // bool finish=true;
            // for(int i=0;i<n;i++){
            //     if(arr[i]!=NULL){
            //         finish=false;
            //         break;
            //     }
            // }
            // if(finish){
            //     break;
            // }
            auto it = heap.begin();
            PII min_pii= (*it);
            int idx= (*it).second;
            int min_val=(*it).first;
            if(!head){
                head= arr[idx];
                arr[idx]=arr[idx]->next;
                head->next=NULL;
                last=head;
            }
            else{
                last->next=arr[idx];
                arr[idx]=arr[idx]->next;
                last=last->next;
                last->next=NULL;
            }
            
            heap.erase(heap.begin());
            // insert new element into heap
            if(arr[idx]!=NULL){
                heap.insert( {arr[idx]->val, idx} );
            }
        }
        return head;
    }
};
```

## Attempt 2 · 2023-03-22 22:02 IST · Accepted · C++

[submission 920225535](https://leetcode.com/submissions/detail/920225535/) · tests 133/133 · runtime 28 ms (beats 18.7%)

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
    typedef  pair<int,int> PII;
public:
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int k= arr.size();
        ListNode * head=NULL , *last=NULL; // return this headlist
        // make_heap of first element of each linklist // making a map instead
        set< PII> heap;
        for(int i=0;i<k;i++){
            if(arr[i] == NULL)
                continue;
            PII pii = {arr[i]->val,i};
            heap.insert(pii);
        }
        while(!heap.empty()){
            // bool finish=true;
            // for(int i=0;i<n;i++){
            //     if(arr[i]!=NULL){
            //         finish=false;
            //         break;
            //     }
            // }
            // if(finish){
            //     break;
            // }
            auto it = heap.begin();
            PII min_pii= (*it);
            int idx= (*it).second;
            int min_val=(*it).first;
            if(!head){
                head= arr[idx];
                arr[idx]=arr[idx]->next;
                head->next=NULL;
                last=head;
            }
            else{
                last->next=arr[idx];
                arr[idx]=arr[idx]->next;
                last=last->next;
                last->next=NULL;
            }
            
            heap.erase(heap.begin());
            // insert new element into heap
            if(arr[idx]!=NULL){
                heap.insert( {arr[idx]->val, idx} );
            }
        }
        return head;
    }
};
```

## Attempt 3 · 2023-05-23 10:31 IST · Accepted · C++

[submission 955556653](https://leetcode.com/submissions/detail/955556653/) · tests 133/133 · runtime 27 ms (beats 18.8%)

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
    typedef  pair<int,int> PII;
public:
    ListNode * mergeTwoLinkedListUsingDummyNode(ListNode *l1, ListNode *l2){
        ListNode *dummYHead = new ListNode(INT_MIN); // reduces code size
        ListNode *curr = dummYHead;

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

        return dummYHead->next;
    }
    ListNode * mergeLists(vector<ListNode*>& arr, int low, int high){
        if(low == high) return arr[low];
        int mid = (low + high)/2;

        ListNode * left = mergeLists(arr, low, mid);
        ListNode * right= mergeLists(arr, mid+1, high);

        return mergeTwoLinkedListUsingDummyNode(left, right);
    }
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int k= arr.size();
        if(k==0) return NULL;
        // Using Divide and Conquer
        return mergeLists(arr, 0, k-1);

        ListNode * head=NULL , *last=NULL; // return this headlist
        // make_heap of first element of each linklist // making a map instead
        set< PII> heap;
        for(int i=0;i<k;i++){
            if(arr[i] == NULL)
                continue;
            PII pii = {arr[i]->val,i};
            heap.insert(pii);
        }
        while(!heap.empty()){
            // bool finish=true;
            // for(int i=0;i<n;i++){
            //     if(arr[i]!=NULL){
            //         finish=false;
            //         break;
            //     }
            // }
            // if(finish){
            //     break;
            // }
            auto it = heap.begin();
            PII min_pii= (*it);
            int idx= (*it).second;
            int min_val=(*it).first;
            if(!head){
                head= arr[idx];
                arr[idx]=arr[idx]->next;
                head->next=NULL;
                last=head;
            }
            else{
                last->next=arr[idx];
                arr[idx]=arr[idx]->next;
                last=last->next;
                last->next=NULL;
            }
            
            heap.erase(heap.begin());
            // insert new element into heap
            if(arr[idx]!=NULL){
                heap.insert( {arr[idx]->val, idx} );
            }
        }
        return head;
    }
};
```

## Attempt 4 · 2023-05-23 10:39 IST · Accepted · C++

[submission 955560290](https://leetcode.com/submissions/detail/955560290/) · tests 133/133 · runtime 34 ms (beats 18.6%)

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
    typedef  pair<int,int> PII;
public:
    ListNode * mergeTwoLinkedListUsingDummyNode(ListNode *l1, ListNode *l2){
        ListNode *dummYHead = new ListNode(INT_MIN); // reduces code size
        ListNode *curr = dummYHead;

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

        return dummYHead->next;
    }
    ListNode * mergeLists(vector<ListNode*>& arr, int low, int high){
        if(low == high) return arr[low];
        int mid = (low + high)/2;

        ListNode * left = mergeLists(arr, low, mid);
        ListNode * right= mergeLists(arr, mid+1, high);

        return mergeTwoLinkedListUsingDummyNode(left, right);
    }
    
    ListNode* mergeKLists(vector<ListNode*>& arr) {
        int k= arr.size();
        if(k==0) return NULL;
        // Using Divide and Conquer
        // return mergeLists(arr, 0, k-1);

        priority_queue<ListNode*, vector<ListNode*>, CustomCompare> pq;
        ListNode* dummy = new ListNode(INT_MIN);
        ListNode* result = dummy;
        
        for(int i=0;i<arr.size();i++) {
            if(arr[i] != NULL) {
                pq.push(arr[i]);
            }
        }
        
        while(!pq.empty()) {
            
            ListNode* val = pq.top();
            pq.pop();
            
            if(val->next != NULL) {
                pq.push(val->next);
            }
            
            dummy->next = val;
            dummy = dummy->next;
        }
        
        return result->next;
    }
    struct CustomCompare {
        bool operator()( ListNode* lhs,  ListNode* rhs) {
            return lhs->val > rhs->val;
        }
    };
};
```

## Attempt 5 · 2023-11-16 23:26 IST · Accepted · Python

[submission 1100251601](https://leetcode.com/submissions/detail/1100251601/) · tests 133/133 · runtime 66 ms (beats 10.4%)

```python
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def mergeKLists1(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        point = head = ListNode(0)
        nodes = []
        for l in lists:
            while l:
                nodes.append(l.val)
                l = l.next
        
        nodes = sorted(nodes)

        for x in nodes:
            point.next = ListNode(x)
            point = point.next

        return head.next

    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        heap = []
        for i, list_node in enumerate(lists):
            if list_node:
                heapq.heappush(heap, (list_node.val, list_node))
            
        dummy = ListNode(0)
        current = dummy
        while heap:
            _, list_node = heapq.heappop(heap)
            current.next = list_node
            current = current.next
            if list_node.next:
                heapq.heappush(heap, (list_node.next.val, list_node.next))
        
        return dummy.next
```

## Attempt 6 · 2023-11-25 03:47 IST · Accepted · Python3

[submission 1105714758](https://leetcode.com/submissions/detail/1105714758/) · tests 133/133 · runtime 94 ms (beats 12.6%)

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# This is necessary for the heapq to compare ListNode objects
    # def __lt__(self, other):
    #     return self.val < other.val


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        def mergeTwoLists(l1, l2):
            head = dummy = ListNode(0)
            while l1 and l2:
                if l1.val <= l2.val:
                    dummy.next = l1
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next
                dummy = dummy.next

            dummy.next = l1 or l2
            return head.next


        n = len(lists)

        interval = 1

        while interval < n:
            for i in range(0, n - interval, interval*2):
                lists[i] = mergeTwoLists(lists[i], lists[i+interval])
            interval *=2

        return lists[0] if n>0 else None
```

## Attempt 7 · 2023-12-05 06:32 IST · Runtime Error · Python3

[submission 1112533366](https://leetcode.com/submissions/detail/1112533366/) · tests 0/133

Failing input:

```text
[[1,4,5],[1,3,4],[2,6]]
```

Expected:

```text
[1,1,2,3,4,4,5,6]
```

Runtime error:

```text
TypeError: '<' not supported between instances of 'ListNode' and 'ListNode'
    heapq.heappush(heap, node)
Line 103 in mergeKLists (Solution.py)
    ret = Solution().mergeKLists(param_1)
Line 136 in _driver (Solution.py)
    _driver()
Line 147 in <module> (Solution.py)
```

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# This is necessary for the heapq to compare ListNode objects
    # def __lt__(self, other):
    #     return self.val < other.val


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, other):
        return self.val < other.val

class Solution:
    '''
    approach 1 - put all in one list - put all valies in the array and then sort and create a final linked list O(NlogN) and O(N)

    approach2 - use min heap  O(NlogK) O(n)+O(k)
    1. put all nodes of the lists on to min_heap 

    2. while heap:
      take out node put it on the new list and then put another node from that onto list

    approach 3 - merge two lists at a time
    can be done without extra space 
    run loop from 0 to n-interval and skip 2*interval each time
    start with interval 1 and then do list[i] and list[i+interval]
    at last return list[0] or none


    '''
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        # merge two linked lists
        # l1 and l2 are nodes
        def mergeTwoLists(l1, l2):
            head = dummy = ListNode(0)
            
            # while both
            while l1 and l2:
                if l1.val <= l2.val:
                    dummy.next = l1
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next
                dummy = dummy.next

            # remaining list
            dummy.next = l1 or l2
            return head.next


        n = len(lists)

        # merge 0 1, 2,3 4,5
        # then 0 2,  4 6
        # then 0 4 
        interval = 1

        # if cann't be partitioned further
        while interval < n:

            # n-interval will be last range and every time skip twice the lists

            for i in range(0, n - interval, interval*2):
                lists[i] = mergeTwoLists(lists[i], lists[i+interval])
            interval *=2

        return lists[0] if n>0 else None

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # for each node in this list
        # add it to list of values
        # and sort it and then. create a linked list
        # O(Nlog N) and O(N)
        head = dummy = ListNode(0)
        nodes = []
        for list_node in lists:
          while list_node:
            nodes.append(list_node.val)  
            list_node = list_node.next
        
        # print(nodes)
        for x in sorted(nodes):
          # print(x)
          dummy.next = ListNode(x)
          dummy = dummy.next

        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        head = dummy = ListNode(0)
        for node in lists:
          if node:
            heapq.heappush(heap, node)

        while heap:
          node = heapq.heappop(heap)
          dummy.next = node
          dummy = dummy.next
          node = node.next
          if node:
            heapq.heappush(heap, node)

        return head.next
```

## Attempt 8 · 2024-01-02 02:42 IST · Wrong Answer · Python3

[submission 1134069625](https://leetcode.com/submissions/detail/1134069625/) · tests 24/133

Failing input:

```text
[[1,4,5],[1,3,4],[2,6]]
```

Expected:

```text
[1,1,2,3,4,4,5,6]
```

Your output:

```text
[6]
```

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# This is necessary for the heapq to compare ListNode objects
    # def __lt__(self, other):
    #     return self.val < other.val


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, other):
        return self.val < other.val

class Solution:
    '''
    approach 1 - put all in one list - put all valies in the array and then sort and create a final linked list O(NlogN) and O(N)

    approach2 - use min heap  O(NlogK) O(n)+O(k)
    1. put all nodes of the lists on to min_heap 

    2. while heap:
      take out node put it on the new list and then put another node from that onto list

    approach 3 - merge two lists at a time
    can be done without extra space 
    run loop from 0 to n-interval and skip 2*interval each time
    start with interval 1 and then do list[i] and list[i+interval]
    at last return list[0] or none


    '''
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        # merge two linked lists
        # l1 and l2 are nodes
        def mergeTwoLists(l1, l2):
            head = dummy = ListNode(0)
            
            # while both
            while l1 and l2:
                if l1.val <= l2.val:
                    dummy.next = l1
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next
                dummy = dummy.next

            # remaining list
            dummy.next = l1 or l2
            return head.next


        n = len(lists)

        # merge 0 1, 2,3 4,5
        # then 0 2,  4 6
        # then 0 4 
        interval = 1

        # if cann't be partitioned further
        while interval < n:

            # n-interval will be last range and every time skip twice the lists

            for i in range(0, n - interval, interval*2):
                lists[i] = mergeTwoLists(lists[i], lists[i+interval])
            interval *=2

        return lists[0] if n>0 else None

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # for each node in this list
        # add it to list of values
        # and sort it and then. create a linked list
        # O(Nlog N) and O(N)
        head = dummy = ListNode(0)
        nodes = []
        for list_node in lists:
          while list_node:
            nodes.append(list_node.val)  
            list_node = list_node.next
        
        # print(nodes)
        for x in sorted(nodes):
          # print(x)
          dummy.next = ListNode(x)
          dummy = dummy.next

        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        head = dummy = ListNode(0)
        for node in lists:
          if node:
            heapq.heappush(heap, node)

        while heap:
          node = heapq.heappop(heap)
          dummy.next = node
          dummy = dummy.next
          node = node.next
          if node:
            heapq.heappush(heap, node)

        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = [] # min heap

        for node in lists:
            heapq.heappush(heap, node)    

        head = dummy = ListNode(0)
        while heap:
            node = heapq.heappop(heap)
            dummy.next = node 
            dummy = dummy.next
            node = node.next

            if node:
                heapq.heappush(node)
        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        # merge two lists at a time
        def mergeLists(list1, list2):
            dummy = head = ListNode(0)
            while list1 and list2:
                if list1.val < list2.val:
                    dummy.next = list1
                    list1 = list1.next
                else:
                    dummy.next = list2
                    list2 = list2.next

            dummy.next = list1 or list2
            return head.next

        interval = 1
        n = len(lists)
        
        # as long as there are two lists to merge

        while interval < n:
            # for this interval merge all lists
            for i in range(0, n - interval, interval*2):
                lists[i] = mergeLists(lists[i], lists[i+interval])
                
            interval *= 2
        return lists[0] if n>0 else None
```

## Attempt 9 · 2024-01-20 21:07 IST · Accepted · Python3

[submission 1151716207](https://leetcode.com/submissions/detail/1151716207/) · tests 133/133 · runtime 79 ms (beats 12.7%)

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# This is necessary for the heapq to compare ListNode objects
    # def __lt__(self, other):
    #     return self.val < other.val


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, other):
        return self.val < other.val

class Solution:
    '''
    approach 1 - put all in one list - put all valies in the array and then sort and create a final linked list O(NlogN) and O(N)

    approach2 - use min heap  O(NlogK) O(n)+O(k)
    1. put all nodes of the lists on to min_heap 

    2. while heap:
      take out node put it on the new list and then put another node from that onto list

    approach 3 - merge two lists at a time
    can be done without extra space 
    run loop from 0 to n-interval and skip 2*interval each time
    start with interval 1 and then do list[i] and list[i+interval]
    at last return list[0] or none


    '''
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        # merge two linked lists
        # l1 and l2 are nodes
        def mergeTwoLists(l1, l2):
            head = dummy = ListNode(0)
            
            # while both
            while l1 and l2:
                if l1.val <= l2.val:
                    dummy.next = l1 
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next
                dummy = dummy.next

            # remaining list
            dummy.next = l1 or l2
            return head.next


        n = len(lists)

        # merge 0 1, 2,3 4,5
        # then 0 2,  4 6
        # then 0 4 
        interval = 1

        # if cann't be partitioned further
        while interval < n:

            # n-interval will be last range and every time skip twice the lists

            for i in range(0, n - interval, interval*2):
                lists[i] = mergeTwoLists(lists[i], lists[i+interval])
            interval *=2

        return lists[0] if n>0 else None

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # for each node in this list
        # add it to list of values
        # and sort it and then. create a linked list
        # O(Nlog N) and O(N)
        head = dummy = ListNode(0)
        nodes = []
        for list_node in lists:
          while list_node:
            nodes.append(list_node.val)  
            list_node = list_node.next
        
        # print(nodes)
        for x in sorted(nodes):
          # print(x)
          dummy.next = ListNode(x)
          dummy = dummy.next

        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = []
        head = dummy = ListNode(0)
        for node in lists:
          if node:
            heapq.heappush(heap, node)

        while heap:
          node = heapq.heappop(heap)
          dummy.next = node
          dummy = dummy.next
          node = node.next
          if node:
            heapq.heappush(heap, node)

        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        heap = [] # min heap

        for node in lists:
            heapq.heappush(heap, node)    

        head = dummy = ListNode(0)
        while heap:
            node = heapq.heappop(heap)
            dummy.next = node 
            dummy = dummy.next
            node = node.next

            if node:
                heapq.heappush(node)
        return head.next

    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        # merge two lists at a time
        def mergeTwoLists(l1, l2):
            head = dummy = ListNode(0)
            
            # while both
            while l1 and l2:
                if l1.val <= l2.val:
                    dummy.next = l1
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next
                dummy = dummy.next

            # remaining list
            dummy.next = l1 or l2
            return head.next

        interval = 1
        n = len(lists)
        
        # as long as there are two lists to merge

        while interval < n:
            # for this interval merge all lists
            for i in range(0, n - interval, interval*2):
                # 0 2 4 -> new list first time
                # 0 4 -> new list second time
                lists[i] = mergeTwoLists(lists[i], lists[i+interval])
            interval *= 2
        return lists[0] if n>0 else None


class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        def merge2lists(l1, l2):
            head = dummy = ListNode(0)

            while l1 and  l2:
                if l1.val <= l2.val:
                    dummy.next = l1
                    l1 = l1.next
                else:
                    dummy.next = l2
                    l2 = l2.next

                dummy = dummy.next
            
            dummy.next = l1 or l2
            return head.next
        
        interval = 1
        n = len(lists)
        while interval < n:
            for i in range(0, n - interval , interval*2):
                # 0 2 4 -> new list first time
                # 0 4 -> new list second time
                lists[i] = merge2lists(lists[i], lists[i+interval])
            interval *=2
        return lists[0] if n > 0 else None

    ## def __lt__(self, other):
        # return self.val < other.val
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:

        '''
        using heap - heap of size k - logk operation for each element
        Nlog k
        '''

        heap = []
        for l in lists:
            if l:
                heapq.heappush(heap, (l.val, id(l), l))

        dummy = head = ListNode(0)

        while heap:
            val, _, node = heapq.heappop(heap)
            dummy.next = node
            dummy = dummy.next
            if node.next:
                node = node.next
                heapq.heappush(heap, (node.val, id(node), node))
        return head.next
```

## Attempt 10 · 2025-03-26 09:53 IST · Accepted · C++

[submission 1586434062](https://leetcode.com/submissions/detail/1586434062/) · tests 134/134 · runtime 2 ms (beats 70.2%)

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
    typedef pair<int, int> pii;
    typedef pair <pii, ListNode *> piin;
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // priority_queue<pii, vector<pii>, greater<pii> > pq;
        priority_queue<piin, vector<piin>, greater<piin> > pq;

        int n = lists.size();

        for(int i=0; i<n;i++) {
            int listIdx = i;
            if (lists[listIdx]) {
                pq.push( {{lists[listIdx]->val, listIdx}, lists[listIdx]});
            }
        }

        // Merge all the lists.
        ListNode *dummy = new ListNode(INT_MIN);
        ListNode *head = dummy;
        while(!pq.empty()) {
            auto node = pq.top(); pq.pop();
            int listIdx = node.first.second;
            int val = node.first.first;
            auto nextNode = node.second->next;

            // push next item in PQ if present;
            if (nextNode) {
                pq.push({{nextNode->val, listIdx}, nextNode});
            }
            dummy->next = node.second;
            dummy = dummy->next;
        }
        return head->next;
    }
};
```
