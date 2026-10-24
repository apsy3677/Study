# 146. LRU Cache

[Problem](https://leetcode.com/problems/lru-cache/) · Medium · Design → Hash map + doubly linked list

LeetCode tags: hash-table, linked-list, design, doubly-linked-list

Attempts since Mar 2023: 6 · accepted: 5 · failed before first AC: 1

## Attempt 1 · 2023-03-20 17:40 IST · Wrong Answer · C++

[submission 918738327](https://leetcode.com/submissions/detail/918738327/) · tests 12/22

Failing input:

```text
["LRUCache","put","put","get","put","put","get"]
[[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
```

Expected:

```text
[null,null,null,2,null,null,-1]
```

Your output:

```text
[null,null,null,1,null,null,-1]
```

```cpp
class LRUCache {

private:
    typedef pair<int,int> PII;
    int capacity;
    list< pair<int,int> > dq;
    map<int, list< pair<int,int> >::iterator > lru_map;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            int val = it->second;
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,val});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            return val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            int val = it->second;
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,val});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            
        }
        else{
            if(lru_map.size() >= capacity){
                auto it = dq.back();
                dq.pop_back();
                lru_map.erase(it.first);

            }
            dq.push_front({key, value});
            lru_map[key] = dq.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

## Attempt 2 · 2023-03-20 17:41 IST · Accepted · C++

[submission 918739058](https://leetcode.com/submissions/detail/918739058/) · tests 22/22 · runtime 593 ms (beats 5.0%)

```cpp
class LRUCache {

private:
    typedef pair<int,int> PII;
    int capacity;
    list< pair<int,int> > dq;
    map<int, list< pair<int,int> >::iterator > lru_map;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            int val = it->second;
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,val});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            return val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,value});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            
        }
        else{
            if(lru_map.size() >= capacity){
                auto it = dq.back();
                dq.pop_back();
                lru_map.erase(it.first);

            }
            dq.push_front({key, value});
            lru_map[key] = dq.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

## Attempt 3 · 2023-04-25 17:49 IST · Accepted · C++

[submission 939483920](https://leetcode.com/submissions/detail/939483920/) · tests 22/22 · runtime 634 ms (beats 5.0%)

```cpp
class LRUCache {

private:
    typedef pair<int,int> PII;
    int capacity;
    list< pair<int,int> > dq;
    map<int, list< pair<int,int> >::iterator > lru_map;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            int val = it->second;
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,val});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            return val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(lru_map.find(key) != lru_map.end()){
            auto it = lru_map[key];
            
            
            // make it recently visited
            dq.erase(it);
            dq.push_front({key,value});
            lru_map.erase(key);
            lru_map[key] = dq.begin();
            
        }
        else{
            if(lru_map.size() >= capacity){
                auto it = dq.back();
                dq.pop_back();
                lru_map.erase(it.first);

            }
            dq.push_front({key, value});
            lru_map[key] = dq.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

## Attempt 4 · 2023-05-20 15:22 IST · Accepted · C++

[submission 953826407](https://leetcode.com/submissions/detail/953826407/) · tests 22/22 · runtime 470 ms (beats 5.0%)

```cpp
class LRUCache {
    typedef pair<int, int> PII;
private:
    int capacity;
    list<PII> LL;
    unordered_map<int, list<PII>::iterator> keyNode;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(keyNode.find(key) == keyNode.end()) return -1;

        int val = keyNode[key]->second;
        // move Node to front
        // delete it and insert again in front (from both LL & Map) OR
        // Move it using 
        //splice (movement-iterator, from which list, transfer-iterator)
        LL.splice(LL.begin(), LL, keyNode[key]);
        return val;
    }
    
    void put(int key, int value) {
        if(keyNode.find(key) != keyNode.end()){
            keyNode[key]->second = value;
            // move Node to front
            // delete it and insert again in front (from both LL & Map)
            LL.splice(LL.begin(), LL, keyNode[key]);
            return;
        }
        // evict a key
        if(keyNode.size() >= this->capacity){
            // <!-- delete last element from LL -->
            auto key = LL.back().first;
            LL.pop_back(); keyNode.erase(key);
        }
        // <!-- insertInto LL & Map --> in front
        LL.push_front({key, value});
        keyNode[key] = LL.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// class LRUCache {

// private:
//     typedef pair<int,int> PII;
//     int capacity;
//     list< pair<int,int> > dq;
//     map<int, list< pair<int,int> >::iterator > lru_map;

// public:
//     LRUCache(int capacity) {
//         this->capacity = capacity;
//     }
    
//     int get(int key) {
//         if(lru_map.find(key) != lru_map.end()){
//             auto it = lru_map[key];
//             int val = it->second;
            
//             // make it recently visited
//             dq.erase(it);
//             dq.push_front({key,val});
//             lru_map.erase(key);
//             lru_map[key] = dq.begin();
//             return val;
//         }
//         return -1;
//     }
    
//     void put(int key, int value) {
//         if(lru_map.find(key) != lru_map.end()){
//             auto it = lru_map[key];
            
            
//             // make it recently visited
//             dq.erase(it);
//             dq.push_front({key,value});
//             lru_map.erase(key);
//             lru_map[key] = dq.begin();
            
//         }
//         else{
//             if(lru_map.size() >= capacity){
//                 auto it = dq.back();
//                 dq.pop_back();
//                 lru_map.erase(it.first);

//             }
//             dq.push_front({key, value});
//             lru_map[key] = dq.begin();
//         }
//     }
// };

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

## Attempt 5 · 2023-11-27 08:00 IST · Accepted · Python3

[submission 1107134933](https://leetcode.com/submissions/detail/1107134933/) · tests 22/22 · runtime 700 ms (beats 5.0%)

```python

# 1. define DLNode
class DLinkedNode:
    def __init__(self, key, value):
        self.key = key
        self.val= value
        self.next = None
        self.prev = None

class LRUCache:
    def __init__(self, capacity):
        self.capacity = capacity

        # 2. declare cache to hold dlinkD and create dummy head and tail nodes  
        self.cache = {} # 

        self.head  = DLinkedNode(0,0)
        self.tail = DLinkedNode(0,0)
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _add(self,node):
        # add item to the head of doubly linked list
        # you have a dummy head pointer

        #3. add node to the head
        # point head prev and next to correct 
        prev, nxt = self.head, self.head.next
        prev.next = nxt.prev = node
        node.next, node.prev = nxt, prev

    def _remove(self, node):
        # remove any node - could be inbetween or could be head
        #3. point node next and prev
        nxt, prev = node.next, node.prev
        prev.next, nxt.prev = nxt, prev

    def get(self, key):
        #4. if key in cache, remove and add to end
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val
        return -1

    def put(self, key, val):
        #5. if key in cache, remove, update and add
        if key in self.cache:
            self._remove(self.cache[key])

        self.cache[key] = DLinkedNode(key, val)
        self._add(self.cache[key])

        if self.capacity < len(self.cache):
            # find least recently used 
            # from the tail

            #6. delete lru node in DList and element in cache
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]
```

## Attempt 6 · 2024-02-11 07:54 IST · Accepted · Python3

[submission 1171863682](https://leetcode.com/submissions/detail/1171863682/) · tests 22/22 · runtime 584 ms (beats 5.0%)

```python

# 1. define DLNode
class DLinkedNode:
    def __init__(self, key, value):
        self.key = key
        self.val= value
        self.next = None
        self.prev = None

class LRUCache1:
    def __init__(self, capacity):
        self.capacity = capacity

        # 2. declare cache to hold dlinkD and create dummy head and tail nodes  
        self.cache = {} # 

        self.head  = DLinkedNode(0,0)
        self.tail = DLinkedNode(0,0)
        self.head.next = self.tail
        self.tail.prev = self.head
    
    def _add(self,node):
        # add item to the head of doubly linked list
        # you have a dummy head pointer

        #3. add node to the head
        # point head prev and next to correct 
        prev, nxt = self.head, self.head.next
        prev.next = nxt.prev = node
        node.next, node.prev = nxt, prev

    def _remove(self, node):
        # remove any node - could be inbetween or could be head
        #3. point node next and prev
        nxt, prev = node.next, node.prev
        prev.next, nxt.prev = nxt, prev

    def get(self, key):
        #4. if key in cache, remove and add to end
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val
        return -1

    def put(self, key, val):
        #5. if key in cache, remove, update and add
        if key in self.cache:
            self._remove(self.cache[key])

        self.cache[key] = DLinkedNode(key, val)
        self._add(self.cache[key])

        if self.capacity < len(self.cache):
            # find least recently used 
            # from the tail

            #6. delete lru node in DList and element in cache
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]
        
           
class LRUCache(OrderedDict):
    def __init__(self, capacity):
        self.capacity = capacity

    def get(self, key):
        if key in self:
            # move item to end
            # end has recently used items
            self.move_to_end(key)
            return self[key]
        return -1

    def put(self, key, value):
        if key in self:
            self.move_to_end(key)
        self[key] = value
        if len(self) > self.capacity:
            # pop item from beginning
            # start has lru
            self.popitem(last=False)

class LRUCache:
    def __init__(self, capacity): 
        self.cache= {}
        self.capacity = capacity
        self.size = 0
        self.head = DlinkedNode(0)
        self.tail = DlinkedNode(0)

        # tail is lru
        # head is recently used
        self.head.next = self.tail
        self.tail.prev = self.head

    def get(self, key):
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val
        return -1
            
    def put(self, key, value):
        if key in self.cache:
            self._remove(self.cache[key])
        
        self.cache[key] = DlinkedNode(value)
        self._add(self.cache[key])
    
        if len(self.cache) > self.capacity:
            # find lru item
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]

class DlinkedNode:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.next = None
        self.prev = None

class LRUCache:
    def __init__(self, capacity): 
        # head will be recently used item and tail is lru
        self.capacity = capacity
        self.cache = {} # cache holds the key and DlinkedNode
        self.head = DlinkedNode(0,0)
        self.tail = DlinkedNode(0,0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _add(self,node):
        # add node to head
        prev, nxt = self.head, self.head.next
        prev.next = nxt.prev = node
        node.next, node.prev = nxt, prev
        
    
    def _remove(self,node):
        # remove node from anywhere
        prev, nxt = node.prev, node.next
        prev.next, nxt.prev = nxt, prev

    def get(self, key):
        if key in self.cache:
            node =self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val

        return -1
            
    def put(self, key, value):
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)

        self.cache[key] = DlinkedNode(key, value)
        self._add(self.cache[key])

        if self.capacity < len(self.cache):
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]

class DlinkedNode:
    def __init__(self, key, val):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity): 
        self.cache = {}
        self.capacity = capacity
        self.head = DlinkedNode(0,0) # ru
        self.tail = DlinkedNode(0,0) # lru
        self.head.next = self.tail
        self.tail.prev = self.head

    def get(self, key):
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
            self._add(node)
            return node.val
        return -1

    def _add(self,node):
        # add to head
        prev, nxt = self.head, self.head.next
        node.prev, node.next = prev, nxt
        prev.next =  nxt.prev = node
        

    def _remove(self, node):
        prev, nxt = node.prev, node.next
        prev.next, nxt.prev = nxt, prev

        
        
    def put(self,key,val):
        if key in self.cache:
            node = self.cache[key]
            self._remove(node)
        self.cache[key]= DlinkedNode(key, val)
        self._add(self.cache[key])
        
        if len(self.cache) > self.capacity:
            lru = self.tail.prev
            self._remove(lru)
            del self.cache[lru.key]
```
