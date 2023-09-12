LRU
Least Recently Used (LRU) is a common caching strategy. It defines the policy to evict elements from the cache to make room for new elements when the cache is full, meaning it discards the least recently used items first.

LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4


get(key)

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
