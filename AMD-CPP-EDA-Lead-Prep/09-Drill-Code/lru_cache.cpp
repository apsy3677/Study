#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

// LC 146 LRU Cache. Hash map + doubly linked list, get/put O(1) average.
// dll:  front = most recently used, back = least recently used; each node stores {key, value}
// pos:  key -> iterator to its node (std::list iterators stay valid across splice / other inserts / erases)
class LRUCache {
    int cap;
    list<pair<int,int>> dll;
    unordered_map<int, list<pair<int,int>>::iterator> pos;
public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        dll.splice(dll.begin(), dll, it->second);     // move the node to the front, O(1), no copy
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {                        // 1. existing key: update + move to front, NO eviction
            it->second->second = value;
            dll.splice(dll.begin(), dll, it->second);
            return;
        }
        if ((int)dll.size() == cap) {                 // 2. full: evict the back (LRU)
            pos.erase(dll.back().first);              //    node keeps the key -> we can erase it from the map
            dll.pop_back();
        }
        dll.emplace_front(key, value);                // 3. new key = most recent
        pos[key] = dll.begin();
    }
};

// O(n) reference for the random test: vector, front = most recent
struct Brute {
    int cap; vector<pair<int,int>> v;
    int get(int k) {
        auto it = find_if(v.begin(), v.end(), [&](auto& p){ return p.first == k; });
        if (it == v.end()) return -1;
        auto p = *it; v.erase(it); v.insert(v.begin(), p);
        return p.second;
    }
    void put(int k, int val) {
        auto it = find_if(v.begin(), v.end(), [&](auto& p){ return p.first == k; });
        if (it != v.end()) v.erase(it);
        else if ((int)v.size() == cap) v.pop_back();
        v.insert(v.begin(), {k, val});
    }
};

int main() {
    // 1. the LeetCode example, capacity 2 -> expect 1 -1 -1 3 4
    LRUCache c(2);
    c.put(1, 1); c.put(2, 2);
    cout << c.get(1) << ' ';
    c.put(3, 3);                                       // evicts 2
    cout << c.get(2) << ' ';
    c.put(4, 4);                                       // evicts 1
    cout << c.get(1) << ' ' << c.get(3) << ' ' << c.get(4) << '\n';

    // 2. 200000 random ops vs the O(n) reference (keys 0..9, capacity 3)
    LRUCache fast(3); Brute slow{3, {}};
    mt19937 rng(42); int bad = 0;
    for (int i = 0; i < 200000; i++) {
        int k = rng() % 10;
        if (rng() % 2) { int v = rng() % 100; fast.put(k, v); slow.put(k, v); }
        else if (fast.get(k) != slow.get(k)) bad++;
    }
    cout << "random test mismatches: " << bad << '\n';
}
