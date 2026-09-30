// cpp_toolkit.cpp: the interview C++ toolkit in ONE compilable file.
// Drill: retype this from memory (no autocomplete), then diff against this file.
// Build:  g++ -std=c++20 -O2 -Wall -Wextra -fsanitize=address,undefined cpp_toolkit.cpp && ./a.out
// Online: https://godbolt.org (x86-64 gcc, add -std=c++20) or https://www.onlinegdb.com (C++20)

#include <algorithm>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

// ---------- 1. Linked list ----------
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

ListNode* reverseList(ListNode* head) {          // invariant: prev = reversed prefix
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nxt = head->next;              // 1. save
        head->next = prev;                       // 2. cut & rewire
        prev = head;                             // 3. advance prev
        head = nxt;                              // 4. advance cur
    }
    return prev;
}

// ---------- 2. Tree ----------
struct TreeNode {
    int val;
    TreeNode *left = nullptr, *right = nullptr;
    TreeNode(int v) : val(v) {}
};

vector<int> inorderIterative(TreeNode* root) {
    vector<int> out; stack<TreeNode*> st; TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }   // go left as far as possible
        cur = st.top(); st.pop();
        out.push_back(cur->val);                         // visit
        cur = cur->right;                                // then right subtree
    }
    return out;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res; if (!root) return res;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = (int)q.size(); res.emplace_back();
        while (sz--) {
            auto* n = q.front(); q.pop();
            res.back().push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return res;
}

// ---------- 3. Grid BFS (number of islands) ----------
int numIslands(vector<string> grid) {
    const int DR[4] = {-1, 1, 0, 0}, DC[4] = {0, 0, -1, 1};
    int R = (int)grid.size(), C = R ? (int)grid[0].size() : 0, islands = 0;
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c) {
            if (grid[r][c] != '1') continue;
            ++islands;
            queue<pii> q; q.push({r, c}); grid[r][c] = '0';   // mark on push
            while (!q.empty()) {
                auto [cr, cc] = q.front(); q.pop();
                for (int k = 0; k < 4; ++k) {
                    int nr = cr + DR[k], nc = cc + DC[k];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] != '1') continue;
                    grid[nr][nc] = '0'; q.push({nr, nc});
                }
            }
        }
    return islands;
}

// ---------- 4. Topological sort (Kahn) ----------
vector<int> topoSort(int n, const vector<pii>& edges) {   // edge u -> v
    vector<vector<int>> adj(n); vector<int> indeg(n, 0);
    for (auto [u, v] : edges) { adj[u].push_back(v); ++indeg[v]; }
    queue<int> q; for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    if ((int)order.size() != n) return {};                   // cycle
    return order;
}

// ---------- 5. Dijkstra ----------
vector<ll> dijkstra(int n, const vector<vector<pii>>& adj, int src) { // adj[u] = {v, w}
    vector<ll> dist(n, LLONG_MAX); dist[src] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq; pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;                             // stale entry
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; pq.push({dist[v], v}); }
    }
    return dist;
}

// ---------- 6. Union-Find ----------
struct DSU {
    vector<int> parent, sz;
    explicit DSU(int n) : parent(n), sz(n, 1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a; sz[a] += sz[b];
        return true;
    }
};

// ---------- 7. Sliding window ----------
int longestUniqueSubstr(const string& s) {
    vector<int> last(256, -1); int best = 0, left = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char ch = s[right];
        if (last[ch] >= left) left = last[ch] + 1;          // shrink past the duplicate
        last[ch] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

// ---------- 8. Binary search on answer ----------
int shipWithinDays(const vector<int>& w, int days) {
    auto ok = [&](int cap) {
        int need = 1, cur = 0;
        for (int x : w) { if (cur + x > cap) { ++need; cur = 0; } cur += x; }
        return need <= days;
    };
    int lo = *max_element(w.begin(), w.end());
    int hi = accumulate(w.begin(), w.end(), 0);
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (ok(mid)) hi = mid; else lo = mid + 1; }
    return lo;
}

// ---------- 9. DP: coin change ----------
int coinChange(const vector<int>& coins, int amount) {
    const int INF = INT_MAX / 2;
    vector<int> dp(amount + 1, INF); dp[0] = 0;              // dp[a] = min coins for a
    for (int a = 1; a <= amount; ++a)
        for (int c : coins) if (c <= a) dp[a] = min(dp[a], dp[a - c] + 1);
    return dp[amount] >= INF ? -1 : dp[amount];
}

// ---------- 10. LRU cache ----------
class LRUCache {
public:
    explicit LRUCache(int capacity) : cap_(capacity) {}
    int get(int key) {
        auto it = pos_.find(key);
        if (it == pos_.end()) return -1;
        order_.splice(order_.begin(), order_, it->second);   // move to front, O(1)
        return it->second->second;
    }
    void put(int key, int value) {
        if (auto it = pos_.find(key); it != pos_.end()) {
            it->second->second = value;
            order_.splice(order_.begin(), order_, it->second);
            return;
        }
        if ((int)order_.size() == cap_) {                    // evict LRU = back
            pos_.erase(order_.back().first);
            order_.pop_back();
        }
        order_.emplace_front(key, value);
        pos_[key] = order_.begin();
    }
private:
    int cap_;
    list<pair<int, int>> order_;                              // front = most recent
    unordered_map<int, list<pair<int, int>>::iterator> pos_;
};

// ---------- 11. Heap: top-k frequent ----------
vector<int> topKFrequent(const vector<int>& a, int k) {
    unordered_map<int, int> freq; for (int x : a) ++freq[x];
    priority_queue<pii, vector<pii>, greater<pii>> minh;     // {freq, value}
    for (auto& [v, f] : freq) { minh.push({f, v}); if ((int)minh.size() > k) minh.pop(); }
    vector<int> res; while (!minh.empty()) { res.push_back(minh.top().second); minh.pop(); }
    reverse(res.begin(), res.end());
    return res;
}

// ---------- 12. Strings ----------
vector<string> splitWords(const string& line) {
    stringstream ss(line); string w; vector<string> out;
    while (ss >> w) out.push_back(w);
    return out;
}

// ---------- 13. Ordered set floor/ceil ----------
pair<int, int> floorCeil(const set<int>& s, int x) {   // returns {floor<=x, ceil>=x}, INT_MIN/INT_MAX if none
    int fl = INT_MIN, ce = INT_MAX;
    auto it = s.lower_bound(x);
    if (it != s.end()) ce = *it;
    auto ub = s.upper_bound(x);
    if (ub != s.begin()) fl = *prev(ub);
    return {fl, ce};
}

// ---------- tiny self-check ----------
int main() {
    int ok = 0, fail = 0;
    auto check = [&](bool cond, const char* what) {
        if (cond) ++ok;
        else { ++fail; cout << "FAIL: " << what << "\n"; }
    };

    ListNode* l = new ListNode(1, new ListNode(2, new ListNode(3)));
    l = reverseList(l);
    check(l->val == 3 && l->next->val == 2 && l->next->next->val == 1, "reverseList");
    while (l) { auto* n = l->next; delete l; l = n; }

    TreeNode a(2), b(1), c(3); a.left = &b; a.right = &c;
    check(inorderIterative(&a) == vector<int>({1, 2, 3}), "inorder");
    check(levelOrder(&a) == vector<vector<int>>({{2}, {1, 3}}), "levelOrder");

    check(numIslands({"11000", "11000", "00100", "00011"}) == 3, "numIslands");
    check(topoSort(4, {{0, 1}, {1, 2}, {0, 3}, {3, 2}}).size() == 4, "topo ok");
    check(topoSort(2, {{0, 1}, {1, 0}}).empty(), "topo cycle");

    vector<vector<pii>> adj(3); adj[0] = {{1, 4}, {2, 1}}; adj[2] = {{1, 2}};
    check(dijkstra(3, adj, 0)[1] == 3, "dijkstra");

    DSU d(4); d.unite(0, 1); d.unite(2, 3);
    check(d.find(0) == d.find(1) && d.find(1) != d.find(2), "dsu");

    check(longestUniqueSubstr("abcabcbb") == 3 && longestUniqueSubstr("") == 0, "window");
    check(shipWithinDays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == 15, "ship");
    check(coinChange({1, 2, 5}, 11) == 3 && coinChange({2}, 3) == -1, "coin");

    LRUCache lru(2); lru.put(1, 1); lru.put(2, 2); lru.get(1); lru.put(3, 3);
    check(lru.get(2) == -1 && lru.get(1) == 1 && lru.get(3) == 3, "lru");

    auto tk = topKFrequent({1, 1, 1, 2, 2, 3}, 2);
    check(tk == vector<int>({1, 2}), "topk");
    check(splitWords("  hello   amd world ").size() == 3, "split");
    auto [fl, ce] = floorCeil({1, 5, 9}, 6);
    check(fl == 5 && ce == 9, "floorCeil");

    cout << "toolkit: " << ok << " passed, " << fail << " failed\n";
    return fail != 0;
}
