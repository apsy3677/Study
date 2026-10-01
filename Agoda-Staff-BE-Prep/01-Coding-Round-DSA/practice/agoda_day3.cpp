// AGODA DAY 3: Jump & stock DP (J), Palindromes & string DP (P), Hash + array design (H), Routes / graphs (R)
// Cards: ../02-Pattern-Cards.md   Hints + tests to say aloud: ../03-Problem-Bank.md
//
// HOW TO USE (the Agoda live round is: explain -> code -> RUN -> pass all tests)
//   1. Pick a stub. Timer on. Say: clarifying questions, brute force, better idea, complexity. (<= 4 min)
//   2. Before coding, write 3-5 of YOUR OWN test cases as comments under the stub (Agoda grades "testing").
//   3. Code it (target 12-18 min). No autocomplete, like HackerRank CodePair.
//   4. Build & run:  g++ -std=c++17 -O1 -g -fsanitize=address,undefined agoda_day3.cpp -o d3 && ./d3
//      One problem only:  ./d3 J1       (any substring of the test name)
//      No compiler? Paste the whole file into https://godbolt.org (x86-64 gcc, flags -std=c++17, enable "Execute")
//   5. Log time + bug in ../PROGRESS.md. Open solutions/agoda_day3_sol.cpp only after passing (or 10 min stuck after hints).
// ★★★ = asked by Agoda in 2025-26 (or its direct variant). ★★ = same family. ★ = stretch.
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
// YOUR CODE
// ============================================================================

// ★★★ J1  Jump Game (LC 55): a[i] = max jump length from i. Can you reach the last index from index 0?
//          (Agoda Staff Bangkok R2 2025 and SSE Bangkok R2 2026: "a DP one similar to Jump Game")
bool canJump(const VI& a) {
    return false;
}

// ★★★ J2  Jump Game II (LC 45): minimum number of jumps to reach the last index (always reachable).
int jumpMin(const VI& a) {
    return 0;
}

// ★★ J3  Jump Game III (LC 1306): from i you may go to i + a[i] or i - a[i]. Can you reach any index with value 0?
bool canReachZero(const VI& a, int start) {
    return false;
}

// ★★ J4  Jump Game VI (LC 1696): jump 1..k steps forward; score = sum of visited values. Max score at the end.
int maxResultJump(const VI& a, int k) {
    return 0;
}

// ★★★ J5  Best Time to Buy and Sell Stock II (LC 122): unlimited transactions, hold at most one share.
//          (Agoda Staff Bangkok R2 2025: "variation of stock buy/sell")
int maxProfitMulti(const VI& prices) {
    return 0;
}

// ★★ J6  Stock with Transaction Fee (LC 714): pay 'fee' per completed transaction.
int maxProfitFee(const VI& prices, int fee) {
    return 0;
}

// ★★ J7  Stock III (LC 123): at most TWO transactions.
int maxProfitTwo(const VI& prices) {
    return 0;
}

// ★★ J8  Triangle (LC 120): minimum path sum top to bottom (move to j or j+1 in the next row). Agoda LC tag.
int minimumTotal(const VVI& triangle) {
    return 0;
}

// ★★★ P1  Palindromic Substrings (LC 647): count palindromic substrings (by position).
//          (Agoda Staff Bangkok 2025: candidate passed with brute force but "could not optimize")
int countSubstrings(const string& s) {
    return 0;
}

// ★★ P2  Longest Palindromic Substring (LC 5). Any one if several have the max length.
string longestPalindrome(const string& s) {
    return "";
}

// ★★ P3  Decode Ways (LC 91): 'A'->"1" ... 'Z'->"26". Number of decodings; "" -> 0.
int numDecodings(const string& s) {
    return 0;
}

// ★★ P4  Word Break (LC 139): can s be split into dictionary words (reuse allowed)? "" -> true.
bool wordBreak(const string& s, const VS& dict) {
    return false;
}

// ★★ P5  Longest String Chain (LC 1048): a word is a predecessor if inserting ONE letter makes the next word.
//         Agoda LC tag.
int longestStrChain(VS words) {
    return 0;
}

// ★★ P6  Maximum Profit in Job Scheduling (LC 1235): non-overlapping jobs (one may start exactly when
//         another ends). Max total profit. Think "accept the most valuable set of bookings".
int jobScheduling(const VI& startTime, const VI& endTime, const VI& profit) {
    return 0;
}

// ★★ H1  Insert Delete GetRandom O(1) (LC 380). Agoda LC tag.
class RandomizedSet {
public:
    bool insert(int val) { return false; }
    bool remove(int val) { return false; }
    int getRandom() { return 0; }
};

// ★★ H2  Time Based Key-Value Store (LC 981): set(key, value, t) with strictly increasing t per key;
//         get(key, t) = value with the largest timestamp <= t, or "".  (think: price history of a hotel room)
class TimeMap {
public:
    void set(const string& key, const string& value, int timestamp) {}
    string get(const string& key, int timestamp) const { return ""; }
};

// ★★ R1  Cheapest Flights Within K Stops (LC 787): flights[i] = {from, to, price}. At most k stops
//         (k + 1 flights). -1 if impossible.
int findCheapestPrice(int n, const VVI& flights, int src, int dst, int k) {
    return 0;
}

// ★ R2  Evaluate Division (LC 399): equations a/b = value. Answer queries x/y, -1.0 if unknown.
//        (think: currency conversion rates)
vector<double> calcEquation(const vector<VS>& equations, const vector<double>& values, const vector<VS>& queries) {
    return {};
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
