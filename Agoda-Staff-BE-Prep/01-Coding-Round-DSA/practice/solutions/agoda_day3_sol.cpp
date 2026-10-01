// REFERENCE SOLUTIONS for agoda_day3.cpp. Spoilers: open only after your version passes.
// ============================================================================
// Includes + aliases. Single file on purpose: paste the whole file
// into HackerRank / godbolt / onlinegdb, or build locally with g++.
// ============================================================================
#include <algorithm>
#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using VS = vector<string>;

// ============================================================================
// REFERENCE SOLUTIONS (spoilers). Read for idioms and edge-case handling.
// ============================================================================

// J1: greedy "farthest reachable". If i is beyond it, we're stuck. O(n), O(1).
//     (The DP version dp[i] = any reachable j with j + a[j] >= i is O(n^2): say it, then improve.)
bool canJump(const VI& a) {
    int farthest = 0;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        if (i > farthest) return false;
        farthest = max(farthest, i + a[i]);
    }
    return true;
}

// J2: BFS by levels without a queue: [levelStart, levelEnd] is everything reachable with 'jumps' jumps.
int jumpMin(const VI& a) {
    int jumps = 0, levelEnd = 0, farthest = 0;
    for (int i = 0; i + 1 < static_cast<int>(a.size()); ++i) {   // never jump FROM the last index
        farthest = max(farthest, i + a[i]);
        if (i == levelEnd) { ++jumps; levelEnd = farthest; }
    }
    return jumps;
}

// J3: plain BFS over indices. O(n).
bool canReachZero(const VI& a, int start) {
    int n = static_cast<int>(a.size());
    vector<bool> seen(n, false);
    queue<int> frontier;
    frontier.push(start);
    seen[start] = true;
    while (!frontier.empty()) {
        int i = frontier.front();
        frontier.pop();
        if (a[i] == 0) return true;
        for (int next : {i + a[i], i - a[i]})
            if (next >= 0 && next < n && !seen[next]) { seen[next] = true; frontier.push(next); }
    }
    return false;
}

// J4: best[i] = a[i] + max(best[i-k .. i-1]). Sliding-window max with a deque of indices (best decreasing).
//     O(n) instead of O(nk).
int maxResultJump(const VI& a, int k) {
    int n = static_cast<int>(a.size());
    vector<long long> best(n);
    deque<int> window;
    best[0] = a[0];
    window.push_back(0);
    for (int i = 1; i < n; ++i) {
        while (window.front() < i - k) window.pop_front();          // fell out of reach
        best[i] = best[window.front()] + a[i];
        while (!window.empty() && best[window.back()] <= best[i]) window.pop_back();
        window.push_back(i);
    }
    return static_cast<int>(best[n - 1]);
}

// J5: collect every upward step (equivalent to buying at each valley, selling at each peak). O(n).
int maxProfitMulti(const VI& prices) {
    int profit = 0;
    for (size_t i = 1; i < prices.size(); ++i) profit += max(0, prices[i] - prices[i - 1]);
    return profit;
}

// J6: two states per day: cash (no share) and hold (one share). O(n), O(1).
int maxProfitFee(const VI& prices, int fee) {
    if (prices.empty()) return 0;
    long long cash = 0, hold = -prices[0];
    for (size_t i = 1; i < prices.size(); ++i) {
        cash = max(cash, hold + prices[i] - fee);   // sell today
        hold = max(hold, cash - prices[i]);         // buy today
    }
    return static_cast<int>(cash);
}

// J7: four states in order: after 1st buy, 1st sell, 2nd buy, 2nd sell. O(n), O(1).
int maxProfitTwo(const VI& prices) {
    int buy1 = INT_MIN, sell1 = 0, buy2 = INT_MIN, sell2 = 0;
    for (int p : prices) {
        buy1 = max(buy1, -p);
        sell1 = max(sell1, buy1 + p);
        buy2 = max(buy2, sell1 - p);
        sell2 = max(sell2, buy2 + p);
    }
    return sell2;
}

// J8: bottom-up, one row of state. O(n^2) time, O(n) space; doesn't modify the input.
int minimumTotal(const VVI& triangle) {
    if (triangle.empty()) return 0;
    VI best = triangle.back();
    for (int row = static_cast<int>(triangle.size()) - 2; row >= 0; --row)
        for (int j = 0; j <= row; ++j)
            best[j] = triangle[row][j] + min(best[j], best[j + 1]);
    return best[0];
}

// P1: expand around 2n - 1 centres (odd and even). O(n^2) time, O(1) space. (Manacher: O(n), mention only.)
int countSubstrings(const string& s) {
    int n = static_cast<int>(s.size()), count = 0;
    auto expand = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) { ++count; --left; ++right; }
    };
    for (int centre = 0; centre < n; ++centre) {
        expand(centre, centre);       // odd length
        expand(centre, centre + 1);   // even length
    }
    return count;
}

// P2: same expansion, remember the best window.
string longestPalindrome(const string& s) {
    int n = static_cast<int>(s.size()), bestStart = 0, bestLen = n > 0 ? 1 : 0;
    auto expand = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) { --left; ++right; }
        int len = right - left - 1;
        if (len > bestLen) { bestLen = len; bestStart = left + 1; }
    };
    for (int centre = 0; centre < n; ++centre) {
        expand(centre, centre);
        expand(centre, centre + 1);
    }
    return s.substr(bestStart, bestLen);
}

// P3: ways(i) = ways(i-1) if s[i] != '0'  +  ways(i-2) if s[i-1..i] is 10..26. Two rolling variables.
int numDecodings(const string& s) {
    if (s.empty()) return 0;
    int twoBack = 1, oneBack = s[0] != '0';
    for (size_t i = 1; i < s.size(); ++i) {
        int current = 0;
        if (s[i] != '0') current += oneBack;
        int pair = (s[i - 1] - '0') * 10 + (s[i] - '0');
        if (s[i - 1] != '0' && pair <= 26) current += twoBack;
        twoBack = oneBack;
        oneBack = current;
    }
    return oneBack;
}

// P4: ok[end] = some word ends at 'end' and ok[end - len]. Only try lengths up to the longest word.
bool wordBreak(const string& s, const VS& dict) {
    unordered_set<string> words(dict.begin(), dict.end());
    size_t longest = 0;
    for (const auto& w : dict) longest = max(longest, w.size());
    vector<bool> ok(s.size() + 1, false);
    ok[0] = true;
    for (size_t end = 1; end <= s.size(); ++end)
        for (size_t len = 1; len <= min(longest, end) && !ok[end]; ++len)
            ok[end] = ok[end - len] && words.count(s.substr(end - len, len)) > 0;
    return ok[s.size()];
}

// P5: sort by length; chain[w] = 1 + max chain of any word obtained by deleting one letter. O(n * L^2).
int longestStrChain(VS words) {
    sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.size() < b.size(); });
    unordered_map<string, int> chain;
    int best = 0;
    for (const string& w : words) {
        int length = 1;
        for (size_t i = 0; i < w.size(); ++i) {
            auto it = chain.find(w.substr(0, i) + w.substr(i + 1));
            if (it != chain.end()) length = max(length, it->second + 1);
        }
        chain[w] = length;
        best = max(best, length);
    }
    return best;
}

// P6: sort jobs by end; best[j] = max(skip job j, take job j + best of jobs ending <= its start).
//     Binary search for "ending <= start". O(n log n).
int jobScheduling(const VI& startTime, const VI& endTime, const VI& profit) {
    int n = static_cast<int>(startTime.size());
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return endTime[a] < endTime[b]; });
    vector<int> ends;
    vector<long long> best;   // best[j]: max profit using the first j+1 jobs by end time
    ends.reserve(n);
    best.reserve(n);
    for (int job : order) {
        int compatible = static_cast<int>(upper_bound(ends.begin(), ends.end(), startTime[job]) - ends.begin());
        long long take = profit[job] + (compatible > 0 ? best[compatible - 1] : 0);
        long long skip = best.empty() ? 0 : best.back();
        ends.push_back(endTime[job]);
        best.push_back(max(take, skip));
    }
    return best.empty() ? 0 : static_cast<int>(best.back());
}

// H1: vector for O(1) random pick + map value -> index. Remove = move the last element into the hole.
class RandomizedSet {
    vector<int> values_;
    unordered_map<int, int> indexOf_;
    mt19937 rng_{12345};
public:
    bool insert(int val) {
        if (indexOf_.count(val)) return false;
        indexOf_[val] = static_cast<int>(values_.size());
        values_.push_back(val);
        return true;
    }
    bool remove(int val) {
        auto it = indexOf_.find(val);
        if (it == indexOf_.end()) return false;
        int hole = it->second, lastValue = values_.back();
        values_[hole] = lastValue;
        indexOf_[lastValue] = hole;
        values_.pop_back();
        indexOf_.erase(val);          // erase AFTER the update: handles val == lastValue
        return true;
    }
    int getRandom() {
        uniform_int_distribution<int> pick(0, static_cast<int>(values_.size()) - 1);
        return values_[pick(rng_)];
    }
};

// H2: per key, timestamps arrive increasing -> each history is sorted; get = upper_bound - 1. O(log n).
class TimeMap {
    unordered_map<string, vector<pair<int, string>>> history_;
public:
    void set(const string& key, const string& value, int timestamp) { history_[key].emplace_back(timestamp, value); }
    string get(const string& key, int timestamp) const {
        auto it = history_.find(key);
        if (it == history_.end()) return "";
        const auto& h = it->second;
        auto after = upper_bound(h.begin(), h.end(), timestamp,
                                 [](int t, const pair<int, string>& entry) { return t < entry.first; });
        return after == h.begin() ? "" : prev(after)->second;
    }
};

// R1: Bellman-Ford limited to k+1 rounds. Copy the array each round so one round = one more flight.
//     O(k * E). (Dijkstra on (node, stops) also works; plain Dijkstra on node alone is WRONG here.)
int findCheapestPrice(int n, const VVI& flights, int src, int dst, int k) {
    const long long INF = LLONG_MAX / 4;
    vector<long long> cost(n, INF);
    cost[src] = 0;
    for (int round = 0; round <= k; ++round) {
        vector<long long> next = cost;
        for (const auto& f : flights)
            if (cost[f[0]] != INF) next[f[1]] = min(next[f[1]], cost[f[0]] + f[2]);
        cost = move(next);
    }
    return cost[dst] == INF ? -1 : static_cast<int>(cost[dst]);
}

// R2: weighted graph a->b (value), b->a (1/value). Each query = BFS multiplying weights. O(Q * (V + E)).
vector<double> calcEquation(const vector<VS>& equations, const vector<double>& values, const vector<VS>& queries) {
    unordered_map<string, vector<pair<string, double>>> graph;
    for (size_t i = 0; i < equations.size(); ++i) {
        const string& a = equations[i][0];
        const string& b = equations[i][1];
        graph[a].push_back({b, values[i]});
        graph[b].push_back({a, 1.0 / values[i]});
    }
    vector<double> answers;
    for (const auto& q : queries) {
        const string& from = q[0];
        const string& to = q[1];
        if (!graph.count(from) || !graph.count(to)) { answers.push_back(-1.0); continue; }
        unordered_map<string, double> ratio{{from, 1.0}};   // ratio[x] = from / x
        queue<string> frontier;
        frontier.push(from);
        while (!frontier.empty() && !ratio.count(to)) {
            string node = frontier.front();
            frontier.pop();
            double here = ratio[node];
            for (const auto& [next, weight] : graph[node])
                if (!ratio.count(next)) { ratio[next] = here * weight; frontier.push(next); }
        }
        answers.push_back(ratio.count(to) ? ratio[to] : -1.0);
    }
    return answers;
}

// ============================================================================
// Tiny test harness (don't edit)
// ============================================================================

namespace tst {
inline int passed = 0, failed = 0;
inline string filter;  // run only the sections whose name contains this

template <class T> string show(const T& v);
template <class A, class B> string show(const pair<A, B>& p);
template <class T> string show(const vector<T>& v);
inline string show(const string& s) { return "\"" + s + "\""; }
inline string show(const char* s) { return show(string(s)); }
inline string show(bool b) { return b ? "true" : "false"; }
inline string show(char c) { return string("'") + c + "'"; }
template <class T> string show(const T& v) { ostringstream os; os << v; return os.str(); }
template <class A, class B> string show(const pair<A, B>& p) { return "(" + show(p.first) + ", " + show(p.second) + ")"; }
template <class T> string show(const vector<T>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) { if (i) s += ", "; s += show(v[i]); if (i >= 40) { s += ", ..."; break; } }
    return s + "]";
}

inline void section(const char* name, void (*fn)()) {
    if (!filter.empty() && string(name).find(filter) == string::npos) return;
    cout << "-- " << name << "\n";
    int p0 = passed, f0 = failed;
    fn();
    int p = passed - p0, f = failed - f0;
    cout << (f == 0 ? "   [PASS] " : "   [FAIL] ") << name << "  " << p << "/" << (p + f) << endl;
}
inline int summary(const char* file) {
    cout << "\n==== " << file << ": " << passed << " passed, " << failed << " failed ====" << endl;
    return failed == 0 ? 0 : 1;
}
inline bool approxEqual(const vector<double>& a, const vector<double>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) if (fabs(a[i] - b[i]) > 1e-6) return false;
    return true;
}
}  // namespace tst

#define CHECK(cond)                                                                        \
    do {                                                                                   \
        if (cond) ++tst::passed;                                                           \
        else { ++tst::failed; std::cout << "   FAIL line " << __LINE__ << ": " #cond "\n"; } \
    } while (0)

#define CHECK_EQ(actual, expected)                                                         \
    do {                                                                                   \
        auto&& a_ = (actual);                                                              \
        auto&& e_ = (expected);                                                            \
        if (a_ == e_) ++tst::passed;                                                       \
        else {                                                                             \
            ++tst::failed;                                                                 \
            std::cout << "   FAIL line " << __LINE__ << ": " #actual "\n"                  \
                      << "        got:      " << tst::show(a_) << "\n"                     \
                      << "        expected: " << tst::show(e_) << "\n";                   \
        }                                                                                  \
    } while (0)

#define SECTION(fn) tst::section(#fn, fn)

// ============================================================================
// TESTS (don't edit). Read them AFTER writing your own: which of yours did they miss, and why?
// ============================================================================
static void t_J1_canJump() {
    CHECK_EQ(canJump({2, 3, 1, 1, 4}), true);
    CHECK_EQ(canJump({3, 2, 1, 0, 4}), false);
    CHECK_EQ(canJump({0}), true);                                  // already at the end
    CHECK_EQ(canJump({1, 0, 1}), false);
    CHECK_EQ(canJump({2, 0, 0}), true);
    CHECK_EQ(canJump({0, 1}), false);
}
static void t_J2_jumpMin() {
    CHECK_EQ(jumpMin({2, 3, 1, 1, 4}), 2);
    CHECK_EQ(jumpMin({2, 3, 0, 1, 4}), 2);
    CHECK_EQ(jumpMin({0}), 0);
    CHECK_EQ(jumpMin({1, 2, 3}), 2);
    CHECK_EQ(jumpMin({1, 1, 1, 1}), 3);
    CHECK_EQ(jumpMin({5, 1, 1, 1, 1}), 1);
}
static void t_J3_canReachZero() {
    CHECK_EQ(canReachZero({4, 2, 3, 0, 3, 1, 2}, 5), true);
    CHECK_EQ(canReachZero({4, 2, 3, 0, 3, 1, 2}, 0), true);
    CHECK_EQ(canReachZero({3, 0, 2, 1, 2}, 2), false);             // cycles: needs a visited set
    CHECK_EQ(canReachZero({0}, 0), true);
}
static void t_J4_maxResultJump() {
    CHECK_EQ(maxResultJump({1, -1, -2, 4, -7, 3}, 2), 7);
    CHECK_EQ(maxResultJump({10, -5, -2, 4, 0, 3}, 3), 17);
    CHECK_EQ(maxResultJump({1, -5, -20, 4, -1, 3, -6, -3}, 2), 0);
    CHECK_EQ(maxResultJump({5}, 3), 5);
    CHECK_EQ(maxResultJump({-1, -2, -3}, 1), -6);                  // forced path, all negative
}
static void t_J5_maxProfitMulti() {
    CHECK_EQ(maxProfitMulti({7, 1, 5, 3, 6, 4}), 7);
    CHECK_EQ(maxProfitMulti({1, 2, 3, 4, 5}), 4);
    CHECK_EQ(maxProfitMulti({7, 6, 4, 3, 1}), 0);
    CHECK_EQ(maxProfitMulti({}), 0);
}
static void t_J6_maxProfitFee() {
    CHECK_EQ(maxProfitFee({1, 3, 2, 8, 4, 9}, 2), 8);
    CHECK_EQ(maxProfitFee({1, 3, 7, 5, 10, 3}, 3), 6);
    CHECK_EQ(maxProfitFee({1, 2}, 5), 0);                          // fee eats the profit
    CHECK_EQ(maxProfitFee({5}, 1), 0);
    CHECK_EQ(maxProfitFee({}, 1), 0);
}
static void t_J7_maxProfitTwo() {
    CHECK_EQ(maxProfitTwo({3, 3, 5, 0, 0, 3, 1, 4}), 6);
    CHECK_EQ(maxProfitTwo({1, 2, 3, 4, 5}), 4);
    CHECK_EQ(maxProfitTwo({7, 6, 4, 3, 1}), 0);
    CHECK_EQ(maxProfitTwo({1, 2, 4, 2, 5, 7, 2, 4, 9, 0}), 13);
    CHECK_EQ(maxProfitTwo({1}), 0);
    CHECK_EQ(maxProfitTwo({}), 0);
}
static void t_J8_minimumTotal() {
    CHECK_EQ(minimumTotal({{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}), 11);
    CHECK_EQ(minimumTotal({{-10}}), -10);
    CHECK_EQ(minimumTotal({{1}, {2, 3}}), 3);
    CHECK_EQ(minimumTotal({}), 0);
}
static void t_P1_countSubstrings() {
    CHECK_EQ(countSubstrings("abc"), 3);
    CHECK_EQ(countSubstrings("aaa"), 6);
    CHECK_EQ(countSubstrings("abba"), 6);                          // even-length centre
    CHECK_EQ(countSubstrings("a"), 1);
    CHECK_EQ(countSubstrings(""), 0);
}
static bool isPalindromeOfLength(const string& source, const string& p, size_t len) {
    return p.size() == len && source.find(p) != string::npos && equal(p.begin(), p.end(), p.rbegin());
}
static void t_P2_longestPalindrome() {
    CHECK(isPalindromeOfLength("babad", longestPalindrome("babad"), 3));
    CHECK_EQ(longestPalindrome("cbbd"), string("bb"));
    CHECK_EQ(longestPalindrome("a"), string("a"));
    CHECK_EQ(longestPalindrome("forgeeksskeegfor"), string("geeksskeeg"));
    CHECK(isPalindromeOfLength("ac", longestPalindrome("ac"), 1));
    CHECK_EQ(longestPalindrome(""), string(""));
}
static void t_P3_numDecodings() {
    CHECK_EQ(numDecodings("12"), 2);
    CHECK_EQ(numDecodings("226"), 3);
    CHECK_EQ(numDecodings("06"), 0);                               // leading zero
    CHECK_EQ(numDecodings("10"), 1);
    CHECK_EQ(numDecodings("2101"), 1);
    CHECK_EQ(numDecodings("11106"), 2);
    CHECK_EQ(numDecodings("27"), 1);                               // 27 > 26
    CHECK_EQ(numDecodings("100"), 0);                              // "00" can't decode
    CHECK_EQ(numDecodings("0"), 0);
    CHECK_EQ(numDecodings(""), 0);
}
static void t_P4_wordBreak() {
    CHECK_EQ(wordBreak("leetcode", {"leet", "code"}), true);
    CHECK_EQ(wordBreak("applepenapple", {"apple", "pen"}), true);   // reuse
    CHECK_EQ(wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}), false);
    CHECK_EQ(wordBreak("aaaaaaa", {"aaaa", "aaa"}), true);
    CHECK_EQ(wordBreak("", {"a"}), true);
    CHECK_EQ(wordBreak("a", {}), false);
}
static void t_P5_longestStrChain() {
    CHECK_EQ(longestStrChain({"a", "b", "ba", "bca", "bda", "bdca"}), 4);
    CHECK_EQ(longestStrChain({"xbc", "pcxbcf", "xb", "cxbc", "pcxbc"}), 5);
    CHECK_EQ(longestStrChain({"abcd", "dbqca"}), 1);               // same letters, not a chain
    CHECK_EQ(longestStrChain({}), 0);
}
static void t_P6_jobScheduling() {
    CHECK_EQ(jobScheduling({1, 2, 3, 3}, {3, 4, 5, 6}, {50, 10, 40, 70}), 120);
    CHECK_EQ(jobScheduling({1, 2, 3, 4, 6}, {3, 5, 10, 6, 9}, {20, 20, 100, 70, 60}), 150);
    CHECK_EQ(jobScheduling({1, 1, 1}, {2, 3, 4}, {5, 6, 4}), 6);
    CHECK_EQ(jobScheduling({1, 2}, {2, 3}, {5, 6}), 11);           // end == next start is allowed
    CHECK_EQ(jobScheduling({}, {}, {}), 0);
}
static void t_H1_RandomizedSet() {
    RandomizedSet set;
    CHECK_EQ(set.insert(1), true);
    CHECK_EQ(set.remove(2), false);
    CHECK_EQ(set.insert(2), true);
    int r = set.getRandom();
    CHECK(r == 1 || r == 2);
    CHECK_EQ(set.remove(1), true);
    CHECK_EQ(set.insert(2), false);
    CHECK_EQ(set.getRandom(), 2);
    CHECK_EQ(set.insert(3), true);
    CHECK_EQ(set.remove(3), true);                                 // removing the LAST element
    CHECK_EQ(set.remove(2), true);
    CHECK_EQ(set.insert(4), true);
    CHECK_EQ(set.getRandom(), 4);
}
static void t_H2_TimeMap() {
    TimeMap prices;
    prices.set("room101", "100USD", 1);
    CHECK_EQ(prices.get("room101", 1), string("100USD"));
    CHECK_EQ(prices.get("room101", 3), string("100USD"));
    prices.set("room101", "120USD", 4);
    CHECK_EQ(prices.get("room101", 4), string("120USD"));
    CHECK_EQ(prices.get("room101", 5), string("120USD"));
    CHECK_EQ(prices.get("room101", 3), string("100USD"));
    CHECK_EQ(prices.get("room101", 0), string(""));                // before the first timestamp
    CHECK_EQ(prices.get("room999", 9), string(""));                // unknown key
}
static void t_R1_findCheapestPrice() {
    CHECK_EQ(findCheapestPrice(4, {{0, 1, 100}, {1, 2, 100}, {2, 0, 100}, {1, 3, 600}, {2, 3, 200}}, 0, 3, 1), 700);
    CHECK_EQ(findCheapestPrice(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1), 200);
    CHECK_EQ(findCheapestPrice(3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0), 500);
    CHECK_EQ(findCheapestPrice(3, {{0, 1, 1}, {1, 2, 1}, {0, 2, 5}}, 0, 2, 0), 5);   // in-place update would say 2
    CHECK_EQ(findCheapestPrice(3, {{0, 1, 100}}, 0, 2, 1), -1);
    CHECK_EQ(findCheapestPrice(2, {{0, 1, 5}}, 0, 0, 0), 0);
}
static void t_R2_calcEquation() {
    vector<double> got = calcEquation({{"a", "b"}, {"b", "c"}}, {2.0, 3.0},
                                      {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}});
    CHECK(tst::approxEqual(got, {6.0, 0.5, -1.0, 1.0, -1.0}));
    vector<double> got2 = calcEquation({{"USD", "THB"}, {"INR", "THB"}}, {36.0, 0.4}, {{"USD", "INR"}});
    CHECK(tst::approxEqual(got2, {90.0}));
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_J1_canJump);
    SECTION(t_J2_jumpMin);
    SECTION(t_J3_canReachZero);
    SECTION(t_J4_maxResultJump);
    SECTION(t_J5_maxProfitMulti);
    SECTION(t_J6_maxProfitFee);
    SECTION(t_J7_maxProfitTwo);
    SECTION(t_J8_minimumTotal);
    SECTION(t_P1_countSubstrings);
    SECTION(t_P2_longestPalindrome);
    SECTION(t_P3_numDecodings);
    SECTION(t_P4_wordBreak);
    SECTION(t_P5_longestStrChain);
    SECTION(t_P6_jobScheduling);
    SECTION(t_H1_RandomizedSet);
    SECTION(t_H2_TimeMap);
    SECTION(t_R1_findCheapestPrice);
    SECTION(t_R2_calcEquation);
    return tst::summary("agoda_day3");
}
