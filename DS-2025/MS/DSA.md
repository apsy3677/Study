## Microsoft DSA Interview Solutions

Concise, interview-ready solutions with time/space notes and clean code. Use these to drive discussion, complexity analysis, and edge cases.
Language: C++ (use Java only if explicitly noted).

### Canonical File Path Simplification
Approach: Split by '/', use a stack to resolve '.' and '..'.

Complexity: O(n) time, O(n) space.

```cpp
#include <string>
#include <vector>
using namespace std;

string simplifyPath(const string& path) {
    vector<string> st;
    string token;
    for (size_t i = 0; i <= path.size(); ++i) {
        if (i == path.size() || path[i] == '/') {
            if (!token.empty()) {
                if (token == "..") {
                    if (!st.empty()) st.pop_back();
                } else if (token != ".") {
                    st.push_back(token);
                }
                token.clear();
            }
        } else {
            token.push_back(path[i]);
        }
    }
    string res = "/";
    for (size_t i = 0; i < st.size(); ++i) {
        res += st[i];
        if (i + 1 < st.size()) res += "/";
    }
    return res;
}
```

### Capacity To Ship Packages Within D Days
Approach: Binary search on capacity; feasibility by greedy day packing.

Complexity: O(n log S), where S is sum(weights) - max(weights).

```cpp
#include <vector>
using namespace std;

bool canShipWithinDays(const vector<int>& weights, int days, long long cap) {
    int d = 1; long long load = 0;
    for (int w : weights) {
        if (load + w > cap) { ++d; load = 0; }
        load += w;
    }
    return d <= days;
}

int shipWithinDays(vector<int>& weights, int days) {
    int left = 0; long long right = 0;
    for (int w : weights) { if (w > left) left = w; right += w; }
    while (left < right) {
        long long mid = (left + right) / 2;
        if (canShipWithinDays(weights, days, mid)) right = mid; else left = (int)mid + 1;
    }
    return left;
}
```

### Next Closest Time Using Available Digits
Approach: Increment minutes and check digit set subset.

Complexity: O(1440) worst-case, constant.

```cpp
#include <string>
#include <unordered_set>
using namespace std;

string nextClosestTime(string time) {
    unordered_set<char> allowed;
    for (char c : time) if (c != ':') allowed.insert(c);
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    for (int i = 1; i <= 24 * 60; ++i) {
        int total = (h * 60 + m + i) % (24 * 60);
        int hh = total / 60, mm = total % 60;
        string cand;
        cand += (hh < 10 ? "0" : "") + to_string(hh);
        cand += ":";
        cand += (mm < 10 ? "0" : "") + to_string(mm);
        bool ok = true;
        for (char c : cand) {
            if (c != ':' && !allowed.count(c)) { ok = false; break; }
        }
        if (ok) return cand;
    }
    return time;
}
```

### Gas Station
Approach: Single pass; track total surplus and current tank. Reset start when tank < 0.

Complexity: O(n) time, O(1) space.

```cpp
#include <vector>
using namespace std;

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, tank = 0, start = 0;
    for (int i = 0; i < (int)gas.size(); ++i) {
        int diff = gas[i] - cost[i];
        total += diff; tank += diff;
        if (tank < 0) { start = i + 1; tank = 0; }
    }
    return total >= 0 ? start : -1;
}
```

### Substring with Concatenation of All Words
Approach: Sliding window with step = wordLength across wordLength offsets.

Complexity: O(n) with constant factor of wordLength.

```cpp
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    if (s.empty() || words.empty()) return res;
    int wl = (int)words[0].size(), k = (int)words.size(), n = (int)s.size();
    unordered_map<string,int> need;
    for (auto& w : words) need[w]++;
    for (int offset = 0; offset < wl; ++offset) {
        int left = offset, right = offset, count = 0;
        unordered_map<string,int> window;
        while (right + wl <= n) {
            string w = s.substr(right, wl);
            right += wl;
            if (need.count(w)) {
                window[w]++; count++;
                while (window[w] > need[w]) {
                    string w2 = s.substr(left, wl);
                    window[w2]--; left += wl; count--;
                }
                if (count == k) {
                    res.push_back(left);
                    string w2 = s.substr(left, wl);
                    window[w2]--; left += wl; count--;
                }
            } else {
                window.clear(); count = 0; left = right;
            }
        }
    }
    return res;
}
```

### LRU Cache
Approach: Custom doubly linked list + hashmap for O(1) get/put with LRU eviction.

Complexity: O(1) average operations.

```cpp
#include <unordered_map>
using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> pos;
    Node* head; // dummy head
    Node* tail; // dummy tail

    void remove(Node* n) {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void insertToFront(Node* n) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }
public:
    explicit LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail; tail->prev = head;
    }
    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        Node* n = it->second;
        remove(n);
        insertToFront(n);
        return n->value;
    }
    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {
            Node* n = it->second;
            n->value = value;
            remove(n);
            insertToFront(n);
        } else {
            Node* n = new Node(key, value);
            pos[key] = n;
            insertToFront(n);
            if ((int)pos.size() > capacity) {
                Node* lru = tail->prev;
                remove(lru);
                pos.erase(lru->key);
                delete lru;
            }
        }
    }
    ~LRUCache() {
        Node* cur = head;
        while (cur) { Node* nxt = cur->next; delete cur; cur = nxt; }
    }
};
```

### Core Templates

```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> bfs(int start, const vector<vector<int>>& adj) {
    vector<int> order;
    queue<int> q;
    vector<char> seen(adj.size(), false);
    q.push(start); seen[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (!seen[v]) { seen[v] = true; q.push(v); }
    }
    return order;
}

void dfs(int u, const vector<vector<int>>& adj, vector<char>& seen) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : adj[u]) dfs(v, adj, seen);
}

int maxWindowSum(const vector<int>& a, int k) {
    if (k <= 0 || k > (int)a.size()) return 0;
    long long sum = 0, best;
    for (int i = 0; i < k; ++i) sum += a[i];
    best = sum;
    for (int i = k; i < (int)a.size(); ++i) {
        sum += a[i] - a[i-k];
        if (sum > best) best = sum;
    }
    return (int)best;
}
```


