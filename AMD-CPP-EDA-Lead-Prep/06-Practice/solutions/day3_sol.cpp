// SPOILERS: reference solutions for day3.cpp.
#include "../test.h"
using Edge3 = array<int, 3>;

// ===== P08 =====
int orangesRotting(VVI g) {
    int R = (int)g.size(), C = R ? (int)g[0].size() : 0, fresh = 0;
    queue<PII> q;
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c) {
            if (g[r][c] == 2) q.push({r, c});
            else if (g[r][c] == 1) ++fresh;
        }
    const int DR[4] = {-1, 1, 0, 0}, DC[4] = {0, 0, -1, 1};
    int minutes = 0;
    while (!q.empty() && fresh > 0) {
        for (int sz = (int)q.size(); sz > 0; --sz) {           // one BFS level = one minute
            auto [r, c] = q.front(); q.pop();
            for (int k = 0; k < 4; ++k) {
                int nr = r + DR[k], nc = c + DC[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C || g[nr][nc] != 1) continue;
                g[nr][nc] = 2; --fresh; q.push({nr, nc});
            }
        }
        ++minutes;
    }
    return fresh == 0 ? minutes : -1;
}

bool isBipartite(const VVI& adj) {
    int n = (int)adj.size();
    VI color(n, -1);
    for (int s = 0; s < n; ++s) {
        if (color[s] != -1) continue;                           // every component
        queue<int> q; q.push(s); color[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) { color[v] = color[u] ^ 1; q.push(v); }
                else if (color[v] == color[u]) return false;   // odd cycle
            }
        }
    }
    return true;
}

VI findOrder(int n, const vector<PII>& prereq) {
    VVI adj(n); VI indeg(n, 0);
    for (auto [a, b] : prereq) { adj[b].push_back(a); ++indeg[a]; }
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    VI order;
    while (!q.empty()) {
        int u = q.front(); q.pop(); order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return (int)order.size() == n ? order : VI{};
}

int networkDelayTime(const VVI& times, int n, int k) {
    vector<vector<PII>> adj(n + 1);
    for (auto& t : times) adj[t[0]].push_back({t[1], t[2]});
    VI dist(n + 1, INT_MAX); dist[k] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq; pq.push({0, k});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;                             // stale
        for (auto [v, w] : adj[u])
            if (d + w < dist[v]) { dist[v] = d + w; pq.push({dist[v], v}); }
    }
    int best = *max_element(dist.begin() + 1, dist.end());
    return best == INT_MAX ? -1 : best;
}

struct DSU {
    VI p, sz;
    explicit DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; } return x; }   // path halving
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

int countComponents(int n, const vector<PII>& edges) {
    DSU d(n); int comps = n;
    for (auto [u, v] : edges) if (d.unite(u, v)) --comps;
    return comps;
}

PII findRedundantConnection(const vector<PII>& edges) {
    DSU d((int)edges.size() + 1);
    for (auto [u, v] : edges) if (!d.unite(u, v)) return {u, v};
    return {0, 0};
}

bool hasCycleDirected(int n, const vector<PII>& edges) {
    VVI adj(n);
    for (auto [u, v] : edges) adj[u].push_back(v);
    VI color(n, 0);                                             // 0 white, 1 gray (on stack), 2 black
    for (int s = 0; s < n; ++s) {
        if (color[s]) continue;
        vector<PII> st{{s, 0}}; color[s] = 1;                   // iterative DFS: {node, next edge index}
        while (!st.empty()) {
            auto& [u, i] = st.back();
            if (i < (int)adj[u].size()) {
                int v = adj[u][i++];
                if (color[v] == 1) return true;                 // back edge
                if (color[v] == 0) { color[v] = 1; st.push_back({v, 0}); }
            } else { color[u] = 2; st.pop_back(); }
        }
    }
    return false;
}

int countSCC(int n, const vector<PII>& edges) {                 // Kosaraju, iterative
    VVI adj(n), radj(n);
    for (auto [u, v] : edges) { adj[u].push_back(v); radj[v].push_back(u); }
    VI order; vector<char> seen(n, 0);
    for (int s = 0; s < n; ++s) {
        if (seen[s]) continue;
        vector<PII> st{{s, 0}}; seen[s] = 1;
        while (!st.empty()) {
            auto& [u, i] = st.back();
            if (i < (int)adj[u].size()) { int v = adj[u][i++]; if (!seen[v]) { seen[v] = 1; st.push_back({v, 0}); } }
            else { order.push_back(u); st.pop_back(); }        // finish time
        }
    }
    fill(seen.begin(), seen.end(), 0);
    int comps = 0;
    for (int k = n - 1; k >= 0; --k) {
        int s = order[k];
        if (seen[s]) continue;
        ++comps;
        vector<int> st{s}; seen[s] = 1;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : radj[u]) if (!seen[v]) { seen[v] = 1; st.push_back(v); }
        }
    }
    return comps;
}

// ===== EDA =====
VI levelize(int n, const vector<PII>& edges) {
    VVI adj(n); VI indeg(n, 0), level(n, 0);
    for (auto [u, v] : edges) { adj[u].push_back(v); ++indeg[v]; }
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    int done = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop(); ++done;
        for (int v : adj[u]) {
            level[v] = max(level[v], level[u] + 1);
            if (--indeg[v] == 0) q.push(v);
        }
    }
    return done == n ? level : VI{};
}

// shared: topological order of a DAG
static VI topoOrder(int n, const vector<Edge3>& edges) {
    VVI adj(n); VI indeg(n, 0), order;
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); ++indeg[e[1]]; }
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
    while (!q.empty()) { int u = q.front(); q.pop(); order.push_back(u); for (int v : adj[u]) if (--indeg[v] == 0) q.push(v); }
    return order;
}

int worstSlack(int n, const vector<Edge3>& edges, int T) {
    vector<vector<PII>> out(n);                                 // {v, delay}
    for (auto& e : edges) out[e[0]].push_back({e[1], e[2]});
    VI order = topoOrder(n, edges);
    const int NEG = INT_MIN / 2, POS = INT_MAX / 2;
    VI indeg(n, 0);
    for (auto& e : edges) ++indeg[e[1]];
    VI at(n, NEG);
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) at[i] = 0;   // primary inputs
    for (int u : order) for (auto [v, d] : out[u]) at[v] = max(at[v], at[u] + d);    // forward: max
    VI rt(n, POS);
    for (int k = n - 1; k >= 0; --k) {                          // backward: min
        int u = order[k];
        if (out[u].empty()) rt[u] = T;                          // primary output
        for (auto [v, d] : out[u]) rt[u] = min(rt[u], rt[v] - d);
    }
    int worst = INT_MAX;
    for (int i = 0; i < n; ++i) worst = min(worst, rt[i] - at[i]);
    return worst;
}

VI criticalPath(int n, const vector<Edge3>& edges) {
    VI order = topoOrder(n, edges);
    VI indeg(n, 0);
    vector<vector<PII>> out(n);
    for (auto& e : edges) { out[e[0]].push_back({e[1], e[2]}); ++indeg[e[1]]; }
    const int NEG = INT_MIN / 2;
    VI at(n, NEG), pred(n, -1);
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) at[i] = 0;
    for (int u : order)
        for (auto [v, d] : out[u])
            if (at[u] + d > at[v]) { at[v] = at[u] + d; pred[v] = u; }
    int end = -1;
    for (int i = 0; i < n; ++i) if (out[i].empty() && (end == -1 || at[i] > at[end])) end = i;
    VI path;
    for (int v = end; v != -1; v = pred[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

static bool findChar(const VS& g, char ch, int& r, int& c) {
    for (r = 0; r < (int)g.size(); ++r)
        for (c = 0; c < (int)g[r].size(); ++c)
            if (g[r][c] == ch) return true;
    return false;
}

vector<PII> leeRoutePath(const VS& grid) {
    int sr, sc, tr, tc;
    if (!findChar(grid, 'S', sr, sc) || !findChar(grid, 'T', tr, tc)) return {};
    int R = (int)grid.size(), C = (int)grid[0].size();
    vector<VI> parent(R, VI(C, -2));                            // -2 unvisited, -1 source, else r*C+c
    queue<PII> q; q.push({sr, sc}); parent[sr][sc] = -1;
    const int DR[4] = {-1, 1, 0, 0}, DC[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == tr && c == tc) break;
        for (int k = 0; k < 4; ++k) {
            int nr = r + DR[k], nc = c + DC[k];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] == '#' || parent[nr][nc] != -2) continue;
            parent[nr][nc] = r * C + c;
            q.push({nr, nc});
        }
    }
    if (parent[tr][tc] == -2) return {};
    vector<PII> path;
    for (int cur = tr * C + tc; cur != -1; cur = parent[cur / C][cur % C]) path.push_back({cur / C, cur % C});
    reverse(path.begin(), path.end());                          // backtrace
    return path;
}

int leeRoute(const VS& grid) {
    auto p = leeRoutePath(grid);
    return p.empty() ? -1 : (int)p.size() - 1;
}

static ll netHpwl(const vector<PII>& pos, const VI& net) {
    if (net.empty()) return 0;
    int x0 = INT_MAX, x1 = INT_MIN, y0 = INT_MAX, y1 = INT_MIN;
    for (int c : net) {
        x0 = min(x0, pos[c].first); x1 = max(x1, pos[c].first);
        y0 = min(y0, pos[c].second); y1 = max(y1, pos[c].second);
    }
    return (ll)(x1 - x0) + (y1 - y0);
}

ll hpwl(const vector<PII>& pos, const VVI& nets) {
    ll total = 0;
    for (auto& net : nets) total += netHpwl(pos, net);
    return total;
}

ll hpwlAfterSwap(const vector<PII>& pos, const VVI& nets, ll currentTotal, int a, int b) {
    if (a == b) return currentTotal;
    // In a real placer, cellToNets is built once; here we build it for the two cells only.
    VI affected;
    for (int i = 0; i < (int)nets.size(); ++i)
        for (int c : nets[i]) if (c == a || c == b) { affected.push_back(i); break; }
    ll before = 0, after = 0;
    for (int i : affected) before += netHpwl(pos, nets[i]);
    vector<PII> p2 = pos;                                       // (a placer would swap in place, then undo if rejected)
    swap(p2[a], p2[b]);
    for (int i : affected) after += netHpwl(p2, nets[i]);
    return currentTotal - before + after;
}

// ===== P10 =====
int rob(const VI& a) {
    int take = 0, skip = 0;                                     // best ending with/without robbing the previous
    for (int x : a) { int t = skip + x; skip = max(skip, take); take = t; }
    return max(take, skip);
}

ll coinChangeWays(const VI& coins, int amount) {
    vector<ll> ways(amount + 1, 0); ways[0] = 1;
    for (int c : coins)                                         // coins OUTER → combinations
        for (int a = c; a <= amount; ++a) ways[a] += ways[a - c];
    return ways[amount];
}

int lengthOfLIS(const VI& a) {
    VI tails;                                                   // tails[k] = min tail of an inc. subseq of length k+1
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x); else *it = x;
    }
    return (int)tails.size();
}

int lcs(const string& a, const string& b) {
    int m = (int)a.size(), n = (int)b.size();
    VVI dp(m + 1, VI(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[m][n];
}

int editDistance(const string& a, const string& b) {
    int m = (int)a.size(), n = (int)b.size();
    VVI dp(m + 1, VI(n + 1));
    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1]
                                            : 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
    return dp[m][n];
}

int knapsack01(const VI& wt, const VI& val, int W) {
    VI dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); ++i)
        for (int cap = W; cap >= wt[i]; --cap)                  // DESCENDING → each item once
            dp[cap] = max(dp[cap], dp[cap - wt[i]] + val[i]);
    return dp[W];
}

bool canPartition(const VI& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total % 2) return false;
    bitset<10001> bs; bs[0] = 1;                                // reachable subset sums
    for (int x : a) bs |= bs << x;
    return bs[total / 2];
}

int uniquePathsWithObstacles(const VVI& g) {
    int C = (int)g[0].size();
    VI dp(C, 0); dp[0] = 1;
    for (auto& row : g)
        for (int c = 0; c < C; ++c) {
            if (row[c] == 1) dp[c] = 0;
            else if (c > 0) dp[c] += dp[c - 1];
        }
    return dp[C - 1];
}

// ===== P11 =====
class Trie {
    struct Node { int next[26]; bool isWord = false; Node() { std::fill(std::begin(next), std::end(next), -1); } };
    vector<Node> pool_{Node()};                                 // node 0 = root; indices, not pointers
    int walk(const string& s) const {
        int cur = 0;
        for (char ch : s) { cur = pool_[cur].next[ch - 'a']; if (cur == -1) return -1; }
        return cur;
    }
public:
    void insert(const string& w) {
        int cur = 0;
        for (char ch : w) {
            int c = ch - 'a';
            if (pool_[cur].next[c] == -1) { int id = (int)pool_.size(); pool_.emplace_back(); pool_[cur].next[c] = id; }
            cur = pool_[cur].next[c];
        }
        pool_[cur].isWord = true;
    }
    bool search(const string& w) const { int n = walk(w); return n != -1 && pool_[n].isWord; }
    bool startsWith(const string& p) const { return walk(p) != -1; }
};

VI countBitsUpTo(int n) {
    VI bits(n + 1, 0);
    for (int i = 1; i <= n; ++i) bits[i] = bits[i >> 1] + (i & 1);
    return bits;
}

int singleNumber(const VI& a) {
    int x = 0;
    for (int v : a) x ^= v;
    return x;
}

uint32_t reverseBits(uint32_t x) {
    uint32_t r = 0;
    for (int i = 0; i < 32; ++i) { r = (r << 1) | (x & 1u); x >>= 1; }
    return r;
}

ll powMod(ll a, ll b, ll m) {
    ll r = 1 % m;
    a %= m; if (a < 0) a += m;
    while (b > 0) {
        if (b & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        b >>= 1;
    }
    return r;
}

#include "../tests/day3_tests.h"
