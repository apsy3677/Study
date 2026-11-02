#include <iostream>
#include <list>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

// LC 460 LFU Cache. get/put O(1) average. Evict the lowest count; on a tie, the least recent in that count.
// byFreq:  count -> list of nodes used exactly that many times (front = most recent): the "reverse map"
// pos:     key -> iterator to its node (node stores {key, value, freq})
// minFreq: the lowest count present -> the bucket to evict from, no search
struct Node { int key, val, freq; };

class LFUCache {
    int cap, minFreq = 0;
    unordered_map<int, list<Node>> byFreq;
    unordered_map<int, list<Node>::iterator> pos;

    void touch(list<Node>::iterator it) {             // used once more: move the node from bucket f to f+1
        int f = it->freq;
        auto& from = byFreq[f];
        auto& to = byFreq[f + 1];                     // refs to unordered_map values survive a rehash
        to.splice(to.begin(), from, it);              // same node, other list, O(1); `it` stays valid
        it->freq++;
        if (from.empty()) {
            byFreq.erase(f);
            if (minFreq == f) minFreq = f + 1;        // the only way the minimum moves up
        }
    }
public:
    LFUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        touch(it->second);
        return it->second->val;
    }

    void put(int key, int value) {
        if (cap == 0) return;
        auto it = pos.find(key);
        if (it != pos.end()) {                        // 1. existing key: update + count++, NO eviction
            it->second->val = value;
            touch(it->second);
            return;
        }
        if ((int)pos.size() == cap) {                 // 2. full: evict the back of the lowest-count bucket
            auto& b = byFreq[minFreq];
            pos.erase(b.back().key);
            b.pop_back();
            if (b.empty()) byFreq.erase(minFreq);
        }
        byFreq[1].push_front({key, value, 1});        // 3. new key: count 1, and 1 is now the minimum
        pos[key] = byFreq[1].begin();
        minFreq = 1;
    }
};

// O(n) reference for the random test: evict the smallest (freq, last-used time)
struct Brute {
    struct E { int key, val, freq, last; };
    int cap, t = 0; vector<E> v;
    E* find(int k) { for (auto& e : v) if (e.key == k) return &e; return nullptr; }
    int get(int k) {
        E* e = find(k); if (!e) return -1;
        e->freq++; e->last = ++t; return e->val;
    }
    void put(int k, int val) {
        if (cap == 0) return;
        if (E* e = find(k)) { e->val = val; e->freq++; e->last = ++t; return; }
        if ((int)v.size() == cap) {
            int w = 0;
            for (int i = 1; i < (int)v.size(); i++)
                if (v[i].freq < v[w].freq || (v[i].freq == v[w].freq && v[i].last < v[w].last)) w = i;
            v.erase(v.begin() + w);
        }
        v.push_back({k, val, 1, ++t});
    }
};

int main() {
    // 1. the LeetCode example, capacity 2 -> expect 1 -1 3 -1 3 4
    LFUCache c(2);
    c.put(1, 1); c.put(2, 2);
    cout << c.get(1) << ' ';                           // key 1 count 2, key 2 count 1
    c.put(3, 3);                                       // evicts 2 (lowest count)
    cout << c.get(2) << ' ' << c.get(3) << ' ';        // key 3 count 2 -> tie with key 1
    c.put(4, 4);                                       // evicts 1 (count 2, least recent of the tie)
    cout << c.get(1) << ' ' << c.get(3) << ' ' << c.get(4) << '\n';

    // 2. 200000 random ops vs the O(n) reference (keys 0..9, capacity 3)
    LFUCache fast(3); Brute slow{3};
    mt19937 rng(42); int bad = 0;
    for (int i = 0; i < 200000; i++) {
        int k = rng() % 10;
        if (rng() % 2) { int v = rng() % 100; fast.put(k, v); slow.put(k, v); }
        else if (fast.get(k) != slow.get(k)) bad++;
    }
    cout << "random test mismatches: " << bad << '\n';
}
