// Tests for day3. Included at the end of day3.cpp (and solutions/day3_sol.cpp).
#pragma once
#include "../test.h"

// ---------- P08 ----------
static void t_orangesRotting() {
    CHECK_EQ(orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}), 4);
    CHECK_EQ(orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}), -1);
    CHECK_EQ(orangesRotting({{0, 2}}), 0);
    CHECK_EQ(orangesRotting({{0}}), 0);
    CHECK_EQ(orangesRotting({{1}}), -1);
    CHECK_EQ(orangesRotting({{2, 1, 1, 1, 2}}), 2);
}
static void t_isBipartite() {
    CHECK(!isBipartite({{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}}));
    CHECK(isBipartite({{1, 3}, {0, 2}, {1, 3}, {0, 2}}));
    CHECK(!isBipartite({{1}, {0}, {3, 4}, {2, 4}, {2, 3}}));   // odd cycle in the 2nd component
    CHECK(isBipartite({{}, {2}, {1}}));
    CHECK(isBipartite({}));
}
static bool validOrder(int n, const vector<PII>& pre, const VI& order) {
    if ((int)order.size() != n) return false;
    VI pos(n, -1);
    for (int i = 0; i < n; ++i) {
        if (order[i] < 0 || order[i] >= n || pos[order[i]] != -1) return false;
        pos[order[i]] = i;
    }
    for (auto [a, b] : pre) if (pos[b] > pos[a]) return false;
    return true;
}
static void t_findOrder() {
    vector<PII> p1{{1, 0}};
    CHECK(validOrder(2, p1, findOrder(2, p1)));
    vector<PII> p2{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    CHECK(validOrder(4, p2, findOrder(4, p2)));
    vector<PII> p3{{1, 0}, {0, 1}};
    CHECK_EQ(findOrder(2, p3), (VI{}));
    CHECK(validOrder(3, {}, findOrder(3, {})));
    vector<PII> p4{{0, 1}, {1, 2}, {2, 3}, {3, 1}};
    CHECK_EQ(findOrder(4, p4), (VI{}));
}
static void t_networkDelayTime() {
    CHECK_EQ(networkDelayTime({{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2), 2);
    CHECK_EQ(networkDelayTime({{1, 2, 1}}, 2, 1), 1);
    CHECK_EQ(networkDelayTime({{1, 2, 1}}, 2, 2), -1);
    CHECK_EQ(networkDelayTime({{1, 2, 5}, {1, 3, 1}, {3, 2, 1}}, 3, 1), 2);
}
static void t_countComponents() {
    CHECK_EQ(countComponents(5, {{0, 1}, {1, 2}, {3, 4}}), 2);
    CHECK_EQ(countComponents(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}), 1);
    CHECK_EQ(countComponents(3, {}), 3);
    CHECK_EQ(countComponents(4, {{0, 1}, {1, 0}, {2, 3}, {3, 2}}), 2);
}
static void t_findRedundantConnection() {
    CHECK_EQ(findRedundantConnection({{1, 2}, {1, 3}, {2, 3}}), (PII{2, 3}));
    CHECK_EQ(findRedundantConnection({{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}), (PII{1, 4}));
}
static void t_hasCycleDirected() {
    CHECK(hasCycleDirected(3, {{0, 1}, {1, 2}, {2, 0}}));
    CHECK(!hasCycleDirected(3, {{0, 1}, {1, 2}, {0, 2}}));      // diamond: NOT a cycle
    CHECK(hasCycleDirected(1, {{0, 0}}));                        // self-loop
    CHECK(hasCycleDirected(4, {{0, 1}, {2, 3}, {3, 2}}));
    CHECK(!hasCycleDirected(4, {}));
}
static void t_countSCC() {
    CHECK_EQ(countSCC(5, {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}}), 3);
    CHECK_EQ(countSCC(3, {}), 3);
    CHECK_EQ(countSCC(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}), 1);
    CHECK_EQ(countSCC(6, {{0, 1}, {1, 0}, {2, 3}, {3, 4}, {4, 2}, {1, 2}, {4, 5}}), 3);
}

// ---------- MM04 ----------
static vector<vector<bool>> reachAll(int n, const vector<PII>& edges) {   // reach[s][t]: path s → t
    VVI adj(n);
    for (auto [u, v] : edges) adj[u].push_back(v);
    vector<vector<bool>> reach(n, vector<bool>(n, false));
    for (int s = 0; s < n; ++s) {
        VI st{s}; reach[s][s] = true;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : adj[u]) if (!reach[s][v]) { reach[s][v] = true; st.push_back(v); }
        }
    }
    return reach;
}
// ids 0..k-1 all used; same id ⇔ mutually reachable; every edge u→v has comp[u] <= comp[v]
static bool validTopoScc(int n, const vector<PII>& edges, const VI& comp) {
    if ((int)comp.size() != n) return false;
    int k = 0;
    for (int c : comp) { if (c < 0 || c >= n) return false; k = max(k, c + 1); }
    vector<bool> used(k, false);
    for (int c : comp) used[c] = true;
    for (bool b : used) if (!b) return false;
    auto reach = reachAll(n, edges);
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            if ((comp[u] == comp[v]) != (reach[u][v] && reach[v][u])) return false;
    for (auto [u, v] : edges) if (comp[u] > comp[v]) return false;
    return true;
}
static vector<PII> randomDigraph(uint32_t& seed, int& n) {
    auto rnd = [&](int m) { seed = seed * 1103515245u + 12345u; return (int)((seed >> 8) % (uint32_t)m); };
    n = 1 + rnd(9);
    vector<PII> e(rnd(2 * n + 1));
    for (auto& [u, v] : e) { u = rnd(n); v = rnd(n); }
    return e;
}
static const vector<PII> kSccEx = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 3}, {4, 0}, {5, 3}};      // MM04 running example
static const vector<PII> kSccP1 = {{0, 1}, {1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 4}, {6, 0}};  // MM04 practice 1
static void checkSccLabeler(VI (*label)(int, const vector<PII>&)) {
    CHECK_EQ(label(6, kSccEx), (VI{2, 2, 2, 1, 1, 0}));       // a chain [5] → [3 4] → [0 1 2]: unique labels
    CHECK_EQ(label(7, kSccP1), (VI{1, 2, 2, 2, 3, 3, 0}));    // [6] → [0] → [1 2 3] → [4 5]
    CHECK_EQ(label(2, {{0, 1}}), (VI{0, 1}));
    CHECK_EQ(label(1, {{0, 0}}), (VI{0}));
    CHECK_EQ(label(0, {}), (VI{}));
    vector<PII> diamond{{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}, {4, 3}};
    CHECK(validTopoScc(5, diamond, label(5, diamond)));
    CHECK(validTopoScc(3, {}, label(3, {})));
    uint32_t seed = 4242;
    bool allOk = true;
    for (int iter = 0; iter < 300 && allOk; ++iter) {
        int n;
        auto e = randomDigraph(seed, n);
        allOk = validTopoScc(n, e, label(n, e));
    }
    CHECK(allOk);
}
static void t_sccLabels() { checkSccLabeler(sccLabels); }
static void t_sccLabelsTarjan() { checkSccLabeler(sccLabelsTarjan); }
static void t_loopNodes() {
    CHECK_EQ(loopNodes(6, kSccEx), (VI{0, 1, 2, 3, 4}));
    CHECK_EQ(loopNodes(7, kSccP1), (VI{1, 2, 3, 4, 5}));
    CHECK_EQ(loopNodes(3, {{0, 1}, {1, 1}, {1, 2}}), (VI{1}));             // a self-loop is a loop
    CHECK_EQ(loopNodes(4, {{0, 1}, {0, 2}, {1, 3}, {2, 3}}), (VI{}));     // diamond: no loop
    CHECK_EQ(loopNodes(2, {{0, 1}, {1, 0}, {0, 1}}), (VI{0, 1}));          // duplicate edge
    CHECK_EQ(loopNodes(3, {}), (VI{}));
    uint32_t seed = 777;
    bool allOk = true;
    for (int iter = 0; iter < 300 && allOk; ++iter) {
        int n;
        auto e = randomDigraph(seed, n);
        auto reach = reachAll(n, e);
        VI want;
        for (int u = 0; u < n; ++u) {
            bool onCycle = false;
            for (auto [a, b] : e) if (a == u && reach[b][u]) onCycle = true;   // u → b, and b gets back to u
            if (onCycle) want.push_back(u);
        }
        allOk = loopNodes(n, e) == want;
    }
    CHECK(allOk);
}
static void t_minEdgesToStronglyConnect() {
    CHECK_EQ(minEdgesToStronglyConnect(1, {}), 0);
    CHECK_EQ(minEdgesToStronglyConnect(3, {}), 3);
    CHECK_EQ(minEdgesToStronglyConnect(3, {{0, 1}, {1, 2}}), 1);
    CHECK_EQ(minEdgesToStronglyConnect(3, {{0, 1}, {0, 2}}), 2);
    CHECK_EQ(minEdgesToStronglyConnect(4, {{0, 1}, {1, 2}, {2, 3}, {3, 0}}), 0);
    CHECK_EQ(minEdgesToStronglyConnect(4, {{0, 1}, {1, 0}, {2, 3}, {3, 2}}), 2);
    CHECK_EQ(minEdgesToStronglyConnect(6, kSccEx), 1);
    CHECK_EQ(minEdgesToStronglyConnect(5, {{0, 1}, {2, 1}, {3, 4}}), 3);
}
static void t_possibleBipartition() {
    CHECK(possibleBipartition(4, {{1, 2}, {1, 3}, {2, 4}}));
    CHECK(!possibleBipartition(3, {{1, 2}, {1, 3}, {2, 3}}));
    CHECK(!possibleBipartition(5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}}));
    CHECK(possibleBipartition(1, {}));
    CHECK(possibleBipartition(6, {{1, 2}, {3, 4}, {5, 6}, {2, 3}}));
    CHECK(!possibleBipartition(6, {{1, 2}, {4, 5}, {5, 6}, {4, 6}}));   // the odd cycle is in a later component
}
static bool validOddCycle(const VVI& adj, const VI& cyc) {
    int k = (int)cyc.size();
    if (k % 2 == 0) return false;
    if ((int)set<int>(cyc.begin(), cyc.end()).size() != k) return false;
    for (int i = 0; i < k; ++i) {
        int a = cyc[i], b = cyc[(i + 1) % k];
        if (a < 0 || a >= (int)adj.size()) return false;
        if (find(adj[a].begin(), adj[a].end(), b) == adj[a].end()) return false;
    }
    return true;
}
static bool bruteBipartite(const VVI& adj) {
    int n = (int)adj.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool ok = true;
        for (int u = 0; u < n && ok; ++u)
            for (int v : adj[u]) if (((mask >> u) & 1) == ((mask >> v) & 1)) { ok = false; break; }
        if (ok) return true;
    }
    return false;
}
static void t_oddCycle() {
    VVI tri{{1, 2}, {0, 2}, {0, 1}};
    CHECK(validOddCycle(tri, oddCycle(tri)));
    VVI square{{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    CHECK_EQ(oddCycle(square), (VI{}));
    VVI hub(7);                                       // hexagon 0..5 + hub 6 on 0 and 3: odd cycle of 5
    auto link = [&](int a, int b) { hub[a].push_back(b); hub[b].push_back(a); };
    for (int i = 0; i < 6; ++i) link(i, (i + 1) % 6);
    link(6, 0); link(6, 3);
    CHECK(validOddCycle(hub, oddCycle(hub)));
    VVI twoComp{{1}, {0}, {3, 4}, {2, 4}, {2, 3}};     // the odd cycle is in the 2nd component
    CHECK(validOddCycle(twoComp, oddCycle(twoComp)));
    VVI selfLoop{{0}};
    CHECK(validOddCycle(selfLoop, oddCycle(selfLoop)));
    CHECK_EQ(oddCycle(VVI{}), (VI{}));
    uint32_t seed = 2026;
    auto rnd = [&](int m) { seed = seed * 1103515245u + 12345u; return (int)((seed >> 8) % (uint32_t)m); };
    bool allOk = true;
    for (int iter = 0; iter < 300 && allOk; ++iter) {
        int n = 1 + rnd(9);
        VVI g(n);
        for (int e = rnd(2 * n + 1); e > 0; --e) { int a = rnd(n), b = rnd(n); g[a].push_back(b); if (a != b) g[b].push_back(a); }
        VI cyc = oddCycle(g);
        allOk = bruteBipartite(g) ? cyc.empty() : validOddCycle(g, cyc);
    }
    CHECK(allOk);
}

// ---------- EDA ----------
static void t_levelize() {
    CHECK_EQ(levelize(5, {{0, 2}, {1, 2}, {2, 3}, {3, 4}, {1, 4}}), (VI{0, 0, 1, 2, 3}));
    CHECK_EQ(levelize(3, {{0, 1}, {1, 2}, {2, 1}}), (VI{}));
    CHECK_EQ(levelize(3, {}), (VI{0, 0, 0}));
    CHECK_EQ(levelize(4, {{3, 2}, {2, 1}, {1, 0}}), (VI{3, 2, 1, 0}));
}
static const vector<Edge3> kDag = {{0, 2, 3}, {1, 2, 1}, {2, 3, 4}, {2, 4, 2}, {1, 4, 6}, {3, 5, 2}, {4, 5, 1}};
static void t_worstSlack() {
    CHECK_EQ(worstSlack(6, kDag, 10), 1);
    CHECK_EQ(worstSlack(6, kDag, 8), -1);
    vector<Edge3> two{{0, 1, 5}, {0, 2, 2}, {2, 3, 1}};                 // two primary outputs: 1 and 3
    CHECK_EQ(worstSlack(4, two, 4), -1);
    CHECK_EQ(worstSlack(1, vector<Edge3>{}, 5), 5);
}
static void t_criticalPath() {
    CHECK_EQ(criticalPath(6, kDag), (VI{0, 2, 3, 5}));
    vector<Edge3> two{{0, 1, 5}, {0, 2, 2}, {2, 3, 1}};
    CHECK_EQ(criticalPath(4, two), (VI{0, 1}));
    CHECK_EQ(criticalPath(1, vector<Edge3>{}), (VI{0}));
}
static int gridDist(const VS& g) { return leeRoute(g); }
static bool validLeePath(const VS& g, const vector<PII>& p, int dist) {
    if ((int)p.size() != dist + 1) return false;
    for (size_t i = 0; i < p.size(); ++i) {
        auto [r, c] = p[i];
        if (r < 0 || r >= (int)g.size() || c < 0 || c >= (int)g[0].size() || g[r][c] == '#') return false;
        if (i && abs(r - p[i - 1].first) + abs(c - p[i - 1].second) != 1) return false;
    }
    return g[p.front().first][p.front().second] == 'S' && g[p.back().first][p.back().second] == 'T';
}
static void t_leeRoute() {
    VS g1{"S.#.", "..#T", "...."};
    CHECK_EQ(gridDist(g1), 6);
    CHECK_EQ(gridDist(VS{"S#T"}), -1);
    CHECK_EQ(gridDist(VS{"ST"}), 1);
    VS g2{"S...", "###.", "T...", "...."};
    CHECK_EQ(gridDist(g2), 8);
}
static void t_leeRoutePath() {
    VS g1{"S.#.", "..#T", "...."};
    CHECK(validLeePath(g1, leeRoutePath(g1), 6));
    VS g2{"S...", "###.", "T...", "...."};
    CHECK(validLeePath(g2, leeRoutePath(g2), 8));
    CHECK_EQ(leeRoutePath(VS{"S#T"}), (vector<PII>{}));
}
static ll bruteHpwl(const vector<PII>& pos, const VVI& nets) {
    ll total = 0;
    for (auto& net : nets) {
        if (net.empty()) continue;
        int x0 = INT_MAX, x1 = INT_MIN, y0 = INT_MAX, y1 = INT_MIN;
        for (int c : net) { x0 = min(x0, pos[c].first); x1 = max(x1, pos[c].first); y0 = min(y0, pos[c].second); y1 = max(y1, pos[c].second); }
        total += (ll)(x1 - x0) + (y1 - y0);
    }
    return total;
}
static void t_hpwl() {
    vector<PII> pos{{0, 0}, {2, 3}, {5, 1}, {1, 1}};
    VVI nets{{0, 1}, {1, 2, 3}, {0, 3}};
    CHECK_EQ(hpwl(pos, nets), 13LL);
    CHECK_EQ(hpwl(pos, VVI{{2}}), 0LL);
    CHECK_EQ(hpwl(pos, VVI{}), 0LL);
}
static void t_hpwlAfterSwap() {
    vector<PII> pos{{0, 0}, {2, 3}, {5, 1}, {1, 1}};
    VVI nets{{0, 1}, {1, 2, 3}, {0, 3}};
    CHECK_EQ(hpwlAfterSwap(pos, nets, 13, 0, 2), 14LL);
    // randomized cross-check against brute force (deterministic seed)
    uint32_t seed = 12345;
    auto rnd = [&](int m) { seed = seed * 1103515245u + 12345u; return (int)((seed >> 8) % (uint32_t)m); };
    bool allOk = true;
    for (int iter = 0; iter < 200 && allOk; ++iter) {
        int n = 2 + rnd(20);
        vector<PII> p(n);
        for (auto& q : p) q = {rnd(100), rnd(100)};
        VVI ns(1 + rnd(15));
        for (auto& net : ns) { int k = 1 + rnd(5); for (int j = 0; j < k; ++j) net.push_back(rnd(n)); }
        int a = rnd(n), b = rnd(n);
        ll cur = bruteHpwl(p, ns);
        auto q = p; swap(q[a], q[b]);
        if (hpwlAfterSwap(p, ns, cur, a, b) != bruteHpwl(q, ns)) allOk = false;
    }
    CHECK(allOk);
}

// ---------- P10 ----------
static void t_rob() {
    CHECK_EQ(rob({1, 2, 3, 1}), 4);
    CHECK_EQ(rob({2, 7, 9, 3, 1}), 12);
    CHECK_EQ(rob({}), 0);
    CHECK_EQ(rob({5}), 5);
    CHECK_EQ(rob({2, 1, 1, 2}), 4);
}
static void t_coinChangeWays() {
    CHECK_EQ(coinChangeWays({1, 2, 5}, 5), 4LL);
    CHECK_EQ(coinChangeWays({2}, 3), 0LL);
    CHECK_EQ(coinChangeWays({10}, 10), 1LL);
    CHECK_EQ(coinChangeWays({1, 2, 5}, 0), 1LL);
    CHECK_EQ(coinChangeWays({1, 5, 10, 25}, 100), 242LL);
}
static void t_lengthOfLIS() {
    CHECK_EQ(lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}), 4);
    CHECK_EQ(lengthOfLIS({0, 1, 0, 3, 2, 3}), 4);
    CHECK_EQ(lengthOfLIS({7, 7, 7}), 1);
    CHECK_EQ(lengthOfLIS({}), 0);
}
static void t_lcs() {
    CHECK_EQ(lcs("abcde", "ace"), 3);
    CHECK_EQ(lcs("abc", "def"), 0);
    CHECK_EQ(lcs("", "a"), 0);
    CHECK_EQ(lcs("AGGTAB", "GXTXAYB"), 4);
}
static void t_editDistance() {
    CHECK_EQ(editDistance("horse", "ros"), 3);
    CHECK_EQ(editDistance("intention", "execution"), 5);
    CHECK_EQ(editDistance("", "abc"), 3);
    CHECK_EQ(editDistance("same", "same"), 0);
}
static void t_knapsack01() {
    CHECK_EQ(knapsack01({1, 3, 4, 5}, {1, 4, 5, 7}, 7), 9);
    CHECK_EQ(knapsack01({10, 20, 30}, {60, 100, 120}, 50), 220);
    CHECK_EQ(knapsack01({5}, {10}, 0), 0);
    CHECK_EQ(knapsack01({2}, {3}, 5), 3);               // one copy only: not 6
}
static void t_canPartition() {
    CHECK(canPartition({1, 5, 11, 5}));
    CHECK(!canPartition({1, 2, 3, 5}));
    CHECK(canPartition({2, 2}));
    CHECK(!canPartition({1}));
}
static void t_uniquePathsWithObstacles() {
    CHECK_EQ(uniquePathsWithObstacles({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}), 2);
    CHECK_EQ(uniquePathsWithObstacles({{0, 1}, {0, 0}}), 1);
    CHECK_EQ(uniquePathsWithObstacles({{1}}), 0);
    CHECK_EQ(uniquePathsWithObstacles({{0}}), 1);
    CHECK_EQ(uniquePathsWithObstacles({{0, 0}, {1, 1}, {0, 0}}), 0);
}

// ---------- P11 ----------
static void t_Trie() {
    Trie t;
    t.insert("apple");
    CHECK(t.search("apple"));
    CHECK(!t.search("app"));
    CHECK(t.startsWith("app"));
    t.insert("app");
    CHECK(t.search("app"));
    CHECK(!t.startsWith("b"));
    CHECK(!t.search("apples"));
}
static void t_countBitsUpTo() {
    CHECK_EQ(countBitsUpTo(5), (VI{0, 1, 1, 2, 1, 2}));
    CHECK_EQ(countBitsUpTo(0), (VI{0}));
    auto cb = countBitsUpTo(8);
    CHECK(cb.size() == 9 && cb.back() == 1);
}
static void t_singleNumber() {
    CHECK_EQ(singleNumber({4, 1, 2, 1, 2}), 4);
    CHECK_EQ(singleNumber({1}), 1);
    CHECK_EQ(singleNumber({-3, 7, 7}), -3);
}
static void t_reverseBits() {
    CHECK_EQ(reverseBits(43261596u), 964176192u);
    CHECK_EQ(reverseBits(1u), 2147483648u);
    CHECK_EQ(reverseBits(0u), 0u);
}
static void t_powMod() {
    CHECK_EQ(powMod(2, 10, 1000), 24LL);
    CHECK_EQ(powMod(3, 0, 7), 1LL);
    CHECK_EQ(powMod(7, 13, 1), 0LL);
    CHECK_EQ(powMod(5, 3, 13), 8LL);
    CHECK_EQ(powMod(123456789, 1000000006, 1000000007), 1LL);   // Fermat
    CHECK_EQ(powMod(1000000000000LL, 1000000006, 1000000007), 1LL);  // needs a %= m first
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_orangesRotting);
    SECTION(t_isBipartite);
    SECTION(t_findOrder);
    SECTION(t_networkDelayTime);
    SECTION(t_countComponents);
    SECTION(t_findRedundantConnection);
    SECTION(t_hasCycleDirected);
    SECTION(t_countSCC);
    SECTION(t_sccLabels);
    SECTION(t_loopNodes);
    SECTION(t_minEdgesToStronglyConnect);
    SECTION(t_sccLabelsTarjan);
    SECTION(t_possibleBipartition);
    SECTION(t_oddCycle);
    SECTION(t_levelize);
    SECTION(t_worstSlack);
    SECTION(t_criticalPath);
    SECTION(t_leeRoute);
    SECTION(t_leeRoutePath);
    SECTION(t_hpwl);
    SECTION(t_hpwlAfterSwap);
    SECTION(t_rob);
    SECTION(t_coinChangeWays);
    SECTION(t_lengthOfLIS);
    SECTION(t_lcs);
    SECTION(t_editDistance);
    SECTION(t_knapsack01);
    SECTION(t_canPartition);
    SECTION(t_uniquePathsWithObstacles);
    SECTION(t_Trie);
    SECTION(t_countBitsUpTo);
    SECTION(t_singleNumber);
    SECTION(t_reverseBits);
    SECTION(t_powMod);
    return tst::summary("day3");
}
