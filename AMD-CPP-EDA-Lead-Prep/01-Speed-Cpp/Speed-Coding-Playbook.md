# Speed-Coding Playbook (C++ for live interviews)

**Goal:** once you have the pseudocode, the C++ should flow out of your fingers with **zero container or API hesitation**.
The companion file [cpp_toolkit.cpp](cpp_toolkit.cpp) compiles and holds every snippet below. **Drill: retype it from memory until you can do it in under 25 minutes.**

---

## Part A: the 45-minute live-coding protocol

| Min | Step | What you say or do | Why it matters for a Lead |
|---|---|---|---|
| 0–3 | **Clarify** | Input size? Sorted? Duplicates? Negatives? Empty input? Return what on failure? In-place allowed? | Shows you size problems before building |
| 3–6 | **Examples** | Write one normal and one edge example *in the editor as comments* | Your test cases are ready for later |
| 6–12 | **Approach** | Brute force in one line + its complexity → the better idea → **state the invariant** → target complexity. **Ask "shall I code this?"** | Interviewers score this more than the code |
| 12–30 | **Code** | Top-down: write `main` logic first, helper signatures second, bodies last. Narrate lightly. | Avoids getting lost in details |
| 30–38 | **Test** | Dry-run your comment examples line by line. Then check the edge cases: empty, 1 element, all equal, negative, overflow | Catching your own bug = strong signal |
| 38–45 | **Extend** | Complexity recap, then say what changes for 100M items, multithreading, or streaming input | The lead-level follow-up is coming anyway, so get ahead of it |

**Rule of thumb from constraints → target complexity**

| n | Target | Typical technique |
|---|---|---|
| ≤ 12 | O(n!) | permutations |
| ≤ 25 | O(2ⁿ) | subsets / bitmask |
| ≤ 500 | O(n³) | interval DP, Floyd |
| ≤ 5·10³ | O(n²) | 2D DP, all pairs |
| ≤ 10⁶ | O(n log n) | sort, heap, binary search, map |
| ≤ 10⁸ | O(n) | two pointers, hashing, prefix, monotonic stack |
| huge | O(log n) / O(1) | math, binary search on answer |

---

## Part B: container decision table (memorize the left two columns)

| I need… | Use | Key ops & cost | Gotchas |
|---|---|---|---|
| dynamic array, random access | `vector<T>` | `push_back` amortized O(1), `[]` O(1), insert middle O(n) | growth invalidates iterators/refs; `reserve(n)` when size known |
| fast lookup by key, order irrelevant | `unordered_map<K,V>` / `unordered_set` | avg O(1), worst O(n) | `m[k]` **inserts** default; use `find`/`count`/`contains`(C++20); no hash for `pair` by default |
| sorted keys, floor/ceil, ordered iteration | `map<K,V>` / `set<T>` (RB-tree) | O(log n); `lower_bound`, `upper_bound`, `prev(it)` | use `s.lower_bound(x)`, **not** `std::lower_bound(s.begin(),…)` (that one is O(n)) |
| duplicates + sorted | `multiset<T>` | `erase(s.find(x))` removes ONE | `s.erase(x)` removes **all** copies of x |
| min/max repeatedly | `priority_queue<T>` (max-heap) | push/pop O(log n), top O(1) | min-heap: `priority_queue<T, vector<T>, greater<T>>`; no decrease-key → push duplicates + skip stale |
| FIFO / BFS | `queue<T>` | O(1) | `front()`, not `top()` |
| LIFO / DFS / monotonic stack | `stack<T>` or `vector<T>` | O(1) | vector lets you peek anywhere |
| both ends / sliding window max | `deque<T>` | O(1) both ends | store **indices**, not values |
| O(1) splice / LRU order | `list<T>` + `unordered_map<K, list<T>::iterator>` | splice O(1) | list iterators stay valid on insert/erase of *other* nodes |
| fixed bitset / masks | `bitset<N>`, `uint64_t` | O(N/64) ops | `__builtin_popcountll`, `std::popcount` (C++20) |
| string building | `string` + `+=` / `push_back` | amortized O(1) | `s = s + x` in a loop is O(n²) |
| non-owning view | `string_view`, `span<T>` (C++20) | O(1) | **dangling** if the source dies |

---

## Part C: muscle-memory snippets (type these daily until automatic)

### C1. Headers & aliases
```cpp
#include <bits/stdc++.h>          // GCC only (CoderPad/HackerRank = GCC). Otherwise:
// <vector> <string> <unordered_map> <unordered_set> <map> <set> <queue> <stack> <deque>
// <algorithm> <numeric> <functional> <climits> <iostream> <sstream> <list> <cstdint>
using namespace std;              // fine in interviews; say "I'd avoid this in headers"
using ll = long long;
using pii = pair<int,int>;
```

### C2. Vectors
```cpp
vector<int> a(n, 0);                          // n zeros
vector<vector<int>> g(r, vector<int>(c, -1)); // r x c grid of -1
vector<int> idx(n); iota(idx.begin(), idx.end(), 0); // 0..n-1
sort(a.begin(), a.end());                     // ascending
sort(a.rbegin(), a.rend());                   // descending
sort(v.begin(), v.end(), [](const auto& x, const auto& y){ return x[1] < y[1]; }); // by field
a.erase(unique(a.begin(), a.end()), a.end()); // dedupe (after sort)
ll sum = accumulate(a.begin(), a.end(), 0LL); // 0LL! else int overflow
int mx = *max_element(a.begin(), a.end());
reverse(a.begin(), a.end());
auto it = lower_bound(a.begin(), a.end(), x); // first >= x
int pos = it - a.begin();                     // index
auto ub = upper_bound(a.begin(), a.end(), x); // first > x
int cnt = ub - it;                            // count of x in sorted a
a.back(); a.pop_back(); a.emplace_back(1);    // emplace_back(args...) constructs in place
```

### C3. Hash maps & sets
```cpp
unordered_map<int,int> freq;
for (int x : a) ++freq[x];                    // [] default-inits to 0, OK for counting
if (auto it = freq.find(k); it != freq.end()) use(it->second); // C++17 if-init
if (freq.count(k)) {...}                      // existence (C++20: freq.contains(k))
for (auto& [key, val] : freq) {...}           // structured bindings
unordered_set<int> seen(a.begin(), a.end());
seen.insert(x).second;                         // true if newly inserted
// pair key: use map<pair<int,int>,int> or a custom hash:
struct PairHash { size_t operator()(const pair<int,int>& p) const {
    return hash<long long>()(((long long)p.first << 32) ^ (unsigned)p.second); } };
unordered_map<pair<int,int>, int, PairHash> mp;
```

### C4. Ordered map / set (floor, ceil)
```cpp
map<int,int> m; set<int> s;
auto it = s.lower_bound(x);                   // ceil: first >= x
if (it != s.begin()) { auto fl = prev(it); }  // floor: last < x (use upper_bound for <=)
m.begin()->first;  m.rbegin()->first;         // min key, max key
for (auto it = m.begin(); it != m.end(); ) {  // erase while iterating
    if (bad(it->first)) it = m.erase(it); else ++it;
}
```

### C5. Heaps
```cpp
priority_queue<int> maxh;                                   // max-heap
priority_queue<int, vector<int>, greater<int>> minh;        // min-heap
priority_queue<pii, vector<pii>, greater<pii>> pq;          // min by first, then second
auto cmp = [](const Node& a, const Node& b){ return a.cost > b.cost; }; // ">" => min-heap
priority_queue<Node, vector<Node>, decltype(cmp)> pq2(cmp);
// Top-K largest: keep a MIN-heap of size k; pop when size > k.
```
> **Comparator mnemonic:** priority_queue's comparator says "a has *lower priority* than b". So `greater` puts small on top, and `a.cost > b.cost` means a min-heap by cost.

### C6. Strings
```cpp
s.substr(pos, len);                          // len, NOT end index!
s.find("ab") != string::npos;
to_string(42); stoi("42"); stoll("123456789012");
isdigit(c); isalpha(c); isalnum(c); tolower(c); toupper(c);
int d = c - '0'; char ch = 'a' + i;          // char arithmetic
vector<int> cnt(26); ++cnt[c - 'a'];         // letter frequency
stringstream ss(line); string w; while (ss >> w) words.push_back(w); // split on spaces
string t(n, '#');                             // n copies
reverse(s.begin(), s.end());
```

### C7. Linked list & tree scaffolding
```cpp
struct ListNode { int val; ListNode* next; ListNode(int v, ListNode* n=nullptr): val(v), next(n) {} };
ListNode dummy(0); ListNode* tail = &dummy;   // dummy head: no special-case for head
// ... tail->next = node; tail = tail->next; ...
return dummy.next;

struct TreeNode { int val; TreeNode *left=nullptr, *right=nullptr; TreeNode(int v): val(v) {} };
```

### C8. Grid BFS
```cpp
const int DR[4] = {-1, 1, 0, 0}, DC[4] = {0, 0, -1, 1};
queue<pii> q; q.push({sr, sc}); vis[sr][sc] = true;       // mark when PUSHING
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    for (int k = 0; k < 4; ++k) {
        int nr = r + DR[k], nc = c + DC[k];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C || vis[nr][nc] || grid[nr][nc] == '0') continue;
        vis[nr][nc] = true; q.push({nr, nc});
    }
}
```

### C9. Graph adjacency + recursive lambda DFS
```cpp
vector<vector<int>> adj(n);
for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
vector<int> vis(n, 0);
function<void(int)> dfs = [&](int u) {        // std::function: simple, slightly slower
    vis[u] = 1;
    for (int v : adj[u]) if (!vis[v]) dfs(v);
};
// C++14+ faster alternative: auto dfs = [&](auto&& self, int u) -> void { ... self(self, v); };
```

### C10. Limits, bits, math
```cpp
INT_MAX, INT_MIN, LLONG_MAX; numeric_limits<int>::max();
const int INF = 1e9; const ll LINF = 4e18;
(x >> k) & 1;  x | (1 << k);  x & ~(1 << k);  x ^ (1 << k);   // test/set/clear/toggle
x & (x - 1);   // drop lowest set bit;  x & -x  → lowest set bit;  power of 2: x && !(x & (x-1))
__builtin_popcount(x); __builtin_popcountll(y); __builtin_ctz(x) /* x != 0 */;
1LL << 40;     // NOT 1 << 40 (int overflow)
gcd(a, b); lcm(a, b);                          // <numeric>, C++17
int mid = lo + (hi - lo) / 2;                  // no overflow
```

### C11. Binary search on answer (the only template you need)
```cpp
// find smallest x in [lo, hi] with ok(x) == true, where ok is F F F T T T
int lo = LOW, hi = HIGH;                       // hi must be a known-true value
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (ok(mid)) hi = mid; else lo = mid + 1;
}
return lo;
```

### C12. Class skeleton for design questions (LRU, etc.)
```cpp
class LRUCache {
public:
    explicit LRUCache(int capacity) : cap_(capacity) {}
    int get(int key);
    void put(int key, int value);
private:
    int cap_;
    list<pair<int,int>> order_;                                  // front = most recent
    unordered_map<int, list<pair<int,int>>::iterator> pos_;
};
```

---

## Part D: the 15 bugs you'll make under pressure (scan before you say "done")

1. `int` overflow: sums and products → `long long`; `accumulate(…, 0LL)`; `1LL << k`.
2. `size_t` underflow: `for (size_t i = 0; i < v.size() - 1; ++i)` with an empty v runs forever. Cast `(int)v.size()`.
3. `map[key]` inside a *read* **inserts**. Use `find`/`count`.
4. Modifying a `vector` while holding an iterator or reference (`push_back` may reallocate).
5. `erase` inside a range-for → use `it = c.erase(it)`.
6. The priority_queue comparator is reversed from your intuition.
7. The sort comparator must be a **strict weak ordering**: use `<`, never `<=` (UB, may crash).
8. BFS: mark visited on **push**, not pop (else you get duplicates and TLE).
9. Off-by-one on `substr(pos, len)` and on binary search bounds.
10. Recursion depth: 10⁵ deep can overflow the stack, so go iterative for linked lists or skewed trees.
11. Returning a reference or pointer to a local.
12. `string_view` or `auto&` bound to a temporary.
13. `vector<bool>` isn't a real container (proxy refs, not thread-safe per element).
14. `x & 1 == 0` parses as `x & (1 == 0)` → **parenthesize bit ops**.
15. `abs(INT_MIN)` and `-INT_MIN` are UB. Mid-point is `lo + (hi-lo)/2`.

---

## Part E: speed drills (tick off when under target)

| # | Drill (from blank editor, no reference) | Target |
|---|---|---|
| 1 | Type C1–C12 from memory | 25 min |
| 2 | Reverse a linked list (iterative) + reverse in k-groups | 6 min |
| 3 | LRU cache (get/put) | 8 min |
| 4 | BFS on grid (number of islands) | 6 min |
| 5 | Topological sort (Kahn) returning order or empty-on-cycle | 5 min |
| 6 | Dijkstra with min-heap + stale-skip | 6 min |
| 7 | Union-Find with path compression + union by size | 4 min |
| 8 | Sliding window "longest substring without repeat" | 5 min |
| 9 | Binary search on answer (ship packages in D days) | 6 min |
| 10 | Coin change (min coins) bottom-up | 4 min |
| 11 | Thread-safe blocking queue (mutex + condvar) | 8 min |
| 12 | `unique_ptr`-like class (move-only, Rule of 5) | 8 min |
| 13 | Merge intervals | 4 min |
| 14 | Inorder traversal iterative (stack) | 4 min |
| 15 | Trie insert/search/startsWith | 5 min |

> How: set a timer, write it in a plain editor (no autocomplete, since CoderPad has none worth relying on), compile on godbolt or g++, fix, and log the time in PROGRESS.md.

---

## Part F: lead-level code hygiene (interviewers notice)
- Name things by **meaning** (`windowStart`, `bestLen`), not `i2`, `tmp`.
- Pass big inputs by `const&`; return by value (RVO/move make it cheap).
- One small helper beats a 60-line function; say *"I'll extract this"*.
- State complexity **unprompted** at the end: time **and** space.
- Mention the production-grade version briefly: *"In production I'd add bounds checks / use `std::span` / make it a template / add unit tests for X."*
