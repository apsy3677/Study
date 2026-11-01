#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
using namespace std;

#if defined(__SANITIZE_THREAD__)
extern "C" const char* __tsan_default_options() { return "halt_on_error=1"; }   // stop at the first race report
#endif

// Single-threaded LRU (same as lru_cache.cpp)
class LRUCache {
    int cap;
    list<pair<int,int>> dll;                                    // front = newest, back = LRU; node = {key, value}
    unordered_map<int, list<pair<int,int>>::iterator> pos;      // key -> its node
public:
    LRUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        dll.splice(dll.begin(), dll, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) { it->second->second = value; dll.splice(dll.begin(), dll, it->second); return; }
        if ((int)dll.size() == cap) { pos.erase(dll.back().first); dll.pop_back(); }
        dll.emplace_front(key, value);
        pos[key] = dll.begin();
    }
};

// T1 + T2: one mutex guards map + list together. Exclusive even for get(): get moves the node (it writes).
class ThreadSafeLRU {
    LRUCache c;
    mutex m;
public:
    ThreadSafeLRU(int cap) : c(cap) {}
    int  get(int k)        { lock_guard<mutex> lk(m); return c.get(k); }
    void put(int k, int v) { lock_guard<mutex> lk(m); c.put(k, v); }
};

// T3: sharding. S independent LRUs, each with its own lock; a key always goes to the same shard.
// Trade-off: LRU order is per shard (approximate overall), capacity is split cap / S.
class ShardedLRU {
    static const int S = 16;
    vector<unique_ptr<ThreadSafeLRU>> shards;                   // unique_ptr: a mutex can't be moved/copied
    ThreadSafeLRU& shard(int k) { return *shards[hash<int>{}(k) % S]; }
public:
    ShardedLRU(int cap) { for (int i = 0; i < S; i++) shards.push_back(make_unique<ThreadSafeLRU>(max(1, cap / S))); }
    int  get(int k)        { return shard(k).get(k); }
    void put(int k, int v) { shard(k).put(k, v); }
};

template<class C> void hammer(C& c) {                           // 8 threads x 20000 random get/put
    vector<thread> ts;
    for (int t = 0; t < 8; t++)
        ts.emplace_back([&c, t]{
            mt19937 rng(t);
            for (int i = 0; i < 20000; i++) {
                int k = rng() % 64;
                if (rng() % 2) c.put(k, i); else c.get(k);
            }
        });
    for (auto& th : ts) th.join();
}

int main(int argc, char** argv) {
    string mode = argc > 1 ? argv[1] : "safe";
    if (mode == "race") {                                       // ./x race : the unguarded cache, run under TSan
        LRUCache c(16);
        hammer(c);
        cout << "unguarded run finished without a report (luck, not safety)\n";
        return 0;
    }
    ThreadSafeLRU a(16); hammer(a);
    ShardedLRU b(64);    hammer(b);
    cout << "8 threads x 20000 ops on ThreadSafeLRU and ShardedLRU: done\n";
}
