// REFERENCE SOLUTIONS for agoda_day1.cpp. Spoilers: open only after your version passes.
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

// ---------- S1/S2 shared: recursive descent over "group := (element|'(' group ')') count?" ----------
static long long readCount(const string& s, size_t& i) {
    if (i >= s.size() || !isdigit(static_cast<unsigned char>(s[i]))) return 1;  // no number means 1
    long long count = 0;
    while (i < s.size() && isdigit(static_cast<unsigned char>(s[i]))) count = count * 10 + (s[i++] - '0');
    return count;
}

static string readElement(const string& s, size_t& i) {
    size_t start = i++;  // the uppercase letter
    while (i < s.size() && islower(static_cast<unsigned char>(s[i]))) ++i;
    return s.substr(start, i - start);
}

// S1: O(n) time, O(depth) stack. long long: counts multiply through nesting.
static long long weightOfGroup(const string& s, size_t& i, const unordered_map<string, long long>& weight) {
    long long total = 0;
    while (i < s.size() && s[i] != ')') {
        long long unit = 0;
        if (s[i] == '(') {
            ++i;                                   // consume '('
            unit = weightOfGroup(s, i, weight);
            ++i;                                   // consume ')'
        } else {
            unit = weight.at(readElement(s, i));   // .at() throws on an unknown atom: ask the interviewer!
        }
        total += unit * readCount(s, i);
    }
    return total;
}

long long moleculeWeight(const string& formula, const unordered_map<string, long long>& weight) {
    size_t i = 0;
    return weightOfGroup(formula, i, weight);
}

// S2: same grammar, but each group returns a sorted map name -> count.
static map<string, long long> countsOfGroup(const string& s, size_t& i) {
    map<string, long long> counts;
    while (i < s.size() && s[i] != ')') {
        if (s[i] == '(') {
            ++i;
            map<string, long long> inner = countsOfGroup(s, i);
            ++i;
            long long multiplier = readCount(s, i);
            for (const auto& [name, c] : inner) counts[name] += c * multiplier;
        } else {
            string name = readElement(s, i);
            counts[name] += readCount(s, i);
        }
    }
    return counts;
}

string countOfAtoms(const string& formula) {
    size_t i = 0;
    string out;
    for (const auto& [name, c] : countsOfGroup(formula, i)) {
        out += name;
        if (c > 1) out += to_string(c);
    }
    return out;
}

// S3: stack of (text built before '[', repeat count). O(output) time.
string decodeString(const string& s) {
    stack<pair<string, int>> saved;
    string current;
    int number = 0;
    for (char ch : s) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            number = number * 10 + (ch - '0');
        } else if (ch == '[') {
            saved.push({current, number});
            current.clear();
            number = 0;
        } else if (ch == ']') {
            auto [before, times] = saved.top();
            saved.pop();
            string repeated;
            repeated.reserve(current.size() * times);
            for (int t = 0; t < times; ++t) repeated += current;
            current = before + repeated;
        } else {
            current += ch;
        }
    }
    return current;
}

// S4: O(n) "wormhole": pair up the parentheses, then walk; at a paren, jump to its partner and turn around.
string reverseParentheses(const string& s) {
    int n = static_cast<int>(s.size());
    vector<int> partner(n, -1);
    vector<int> open;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') open.push_back(i);
        else if (s[i] == ')') { partner[i] = open.back(); partner[open.back()] = i; open.pop_back(); }
    }
    string out;
    for (int i = 0, dir = 1; i < n; i += dir) {
        if (s[i] == '(' || s[i] == ')') { i = partner[i]; dir = -dir; }
        else out += s[i];
    }
    return out;
}

// S5: stack of (char, run length). Check the run AFTER pushing, so k == 1 also works. O(n).
string removeDuplicatesK(const string& s, int k) {
    vector<pair<char, int>> runs;
    for (char ch : s) {
        if (!runs.empty() && runs.back().first == ch) ++runs.back().second;
        else runs.push_back({ch, 1});
        if (runs.back().second == k) runs.pop_back();
    }
    string out;
    for (const auto& [ch, len] : runs) out.append(len, ch);
    return out;
}

// S6: O(1) space: walk both strings from the end, skipping characters erased by '#'.
bool backspaceCompare(const string& s, const string& t) {
    auto nextKept = [](const string& str, int idx) {
        int skip = 0;
        while (idx >= 0) {
            if (str[idx] == '#') { ++skip; --idx; }
            else if (skip > 0) { --skip; --idx; }
            else break;
        }
        return idx;  // index of the next surviving char, or -1
    };
    int i = static_cast<int>(s.size()) - 1, j = static_cast<int>(t.size()) - 1;
    while (true) {
        i = nextKept(s, i);
        j = nextKept(t, j);
        if (i < 0 || j < 0) return i < 0 && j < 0;
        if (s[i] != t[j]) return false;
        --i;
        --j;
    }
}

// S7: keep "committed" sum + the last term (so * and / bind tighter). O(n), O(1).
int calculate(const string& s) {
    long long committed = 0, lastTerm = 0, number = 0;
    char op = '+';
    for (size_t i = 0; i <= s.size(); ++i) {
        char ch = i < s.size() ? s[i] : '\0';     // '\0' flushes the final number
        if (isdigit(static_cast<unsigned char>(ch))) { number = number * 10 + (ch - '0'); continue; }
        if (ch == ' ') continue;
        if (op == '+') { committed += lastTerm; lastTerm = number; }
        else if (op == '-') { committed += lastTerm; lastTerm = -number; }
        else if (op == '*') lastTerm *= number;
        else lastTerm /= number;                  // C++ truncates toward zero, as required
        op = ch;
        number = 0;
    }
    return static_cast<int>(committed + lastTerm);
}

// M1: scan twice (index k % n); stack holds indices still waiting for a greater value. O(n).
VI nextGreaterCircular(const VI& a) {
    int n = static_cast<int>(a.size());
    VI answer(n, -1);
    vector<int> waiting;
    for (int k = 0; k < 2 * n; ++k) {
        int value = a[k % n];
        while (!waiting.empty() && a[waiting.back()] < value) {
            answer[waiting.back()] = value;
            waiting.pop_back();
        }
        if (k < n) waiting.push_back(k);
    }
    return answer;
}

// M2: increasing stack of values; anything >= x can never be "nearest smaller" for later elements. O(n).
VI nearestSmallerToLeft(const VI& a) {
    VI answer;
    answer.reserve(a.size());
    vector<int> increasing;
    for (int x : a) {
        while (!increasing.empty() && increasing.back() >= x) increasing.pop_back();
        answer.push_back(increasing.empty() ? -1 : increasing.back());
        increasing.push_back(x);
    }
    return answer;
}

// M3: prefix max (left of i) < a[i] < suffix min (right of i). long long sentinels so INT_MAX/INT_MIN still work.
VI pivotElements(const VI& a) {
    int n = static_cast<int>(a.size());
    vector<long long> suffixMin(n + 1, LLONG_MAX);
    for (int i = n - 1; i >= 0; --i) suffixMin[i] = min<long long>(a[i], suffixMin[i + 1]);
    VI pivots;
    long long prefixMax = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        if (a[i] > prefixMax && a[i] < suffixMin[i + 1]) pivots.push_back(a[i]);
        prefixMax = max<long long>(prefixMax, a[i]);
    }
    return pivots;
}

// M4: a[i] is the min of left[i] * right[i] subarrays. Ties: strict on one side, non-strict on the other.
int sumSubarrayMins(const VI& a) {
    const long long MOD = 1'000'000'007;
    int n = static_cast<int>(a.size());
    vector<int> left(n), right(n), st;
    for (int i = 0; i < n; ++i) {                          // previous strictly smaller
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        left[i] = st.empty() ? i + 1 : i - st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; --i) {                     // next smaller-or-equal
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        right[i] = st.empty() ? n - i : st.back() - i;
        st.push_back(i);
    }
    long long sum = 0;
    for (int i = 0; i < n; ++i) sum = (sum + static_cast<long long>(a[i]) * left[i] % MOD * right[i]) % MOD;
    return static_cast<int>(sum);
}

// M5: greedy: a bigger digit before a smaller one should go first. Increasing stack of digits. O(n).
string removeKdigits(const string& num, int k) {
    string kept;
    for (char d : num) {
        while (k > 0 && !kept.empty() && kept.back() > d) { kept.pop_back(); --k; }
        kept.push_back(d);
    }
    kept.resize(kept.size() - min<size_t>(k, kept.size()));   // still k left: drop from the end
    size_t firstNonZero = kept.find_first_not_of('0');
    return firstNonZero == string::npos ? "0" : kept.substr(firstNonZero);
}

// W1: window [left, right] has no repeats; last[c] = last index of c. O(n), O(alphabet).
string longestDistinctSubstring(const string& s) {
    array<int, 256> last;
    last.fill(-1);
    int left = 0, bestStart = 0, bestLen = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        unsigned char c = s[right];
        if (last[c] >= left) left = last[c] + 1;      // jump past the previous copy
        last[c] = right;
        if (right - left + 1 > bestLen) { bestLen = right - left + 1; bestStart = left; }
    }
    return s.substr(bestStart, bestLen);
}

// W2: grow right; shrink left while more than k distinct. O(n).
int longestAtMostKDistinct(const string& s, int k) {
    unordered_map<char, int> freq;
    int left = 0, best = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        ++freq[s[right]];
        while (static_cast<int>(freq.size()) > k) {
            if (--freq[s[left]] == 0) freq.erase(s[left]);
            ++left;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

// W3: window is valid while (length - count of its most frequent letter) <= k. O(n).
int characterReplacement(const string& s, int k) {
    array<int, 26> freq{};
    int left = 0, maxFreq = 0, best = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        maxFreq = max(maxFreq, ++freq[s[right] - 'A']);
        while (right - left + 1 - maxFreq > k) { --freq[s[left] - 'A']; ++left; }
        best = max(best, right - left + 1);
    }
    return best;
}

// W4: every window ending at right with product < k adds (right - left + 1) subarrays. O(n).
int numSubarrayProductLessThanK(const VI& a, int k) {
    if (k <= 1) return 0;                 // positive ints: product >= 1 can never be < 1
    long long product = 1;
    int left = 0, count = 0;
    for (int right = 0; right < static_cast<int>(a.size()); ++right) {
        product *= a[right];
        while (product >= k) product /= a[left++];
        count += right - left + 1;
    }
    return count;
}

// W5: fixed-size window of |p|; compare 26-letter counts. O(26 * |s|).
bool checkInclusion(const string& p, const string& s) {
    if (p.size() > s.size()) return false;
    array<int, 26> need{}, have{};
    for (char c : p) ++need[c - 'a'];
    for (size_t i = 0; i < s.size(); ++i) {
        ++have[s[i] - 'a'];
        if (i >= p.size()) --have[s[i - p.size()] - 'a'];
        if (have == need) return true;
    }
    return p.empty();
}

// W6: exactly(k) = atMost(k) - atMost(k - 1). O(n).
static long long countAtMostKDistinct(const VI& a, int k) {
    unordered_map<int, int> freq;
    long long count = 0;
    int left = 0;
    for (int right = 0; right < static_cast<int>(a.size()); ++right) {
        ++freq[a[right]];
        while (static_cast<int>(freq.size()) > k) {
            if (--freq[a[left]] == 0) freq.erase(a[left]);
            ++left;
        }
        count += right - left + 1;
    }
    return count;
}

int subarraysWithKDistinct(const VI& a, int k) {
    return static_cast<int>(countAtMostKDistinct(a, k) - countAtMostKDistinct(a, k - 1));
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
static const unordered_map<string, long long> W{{"C", 12}, {"H", 1}, {"O", 8}, {"N", 14}, {"S", 32}, {"K", 39}, {"Mg", 24}};

static void t_S1_moleculeWeight() {
    CHECK_EQ(moleculeWeight("CH4", W), 16LL);
    CHECK_EQ(moleculeWeight("H(CH4)2", W), 33LL);
    CHECK_EQ(moleculeWeight("H2O", W), 10LL);
    CHECK_EQ(moleculeWeight("Mg(OH)2", W), 42LL);               // two-letter element
    CHECK_EQ(moleculeWeight("C12H22O11", W), 254LL);            // multi-digit counts
    CHECK_EQ(moleculeWeight("((CH)2O)3", W), 102LL);            // nested groups
    CHECK_EQ(moleculeWeight("K4(ON(SO3)2)2", W), 424LL);
    CHECK_EQ(moleculeWeight("(H)", W), 1LL);                    // group without a count
    CHECK_EQ(moleculeWeight("", W), 0LL);
    CHECK_EQ(moleculeWeight("C1000000000", W), 12000000000LL);  // overflows int
}
static void t_S2_countOfAtoms() {
    CHECK_EQ(countOfAtoms("H2O"), string("H2O"));
    CHECK_EQ(countOfAtoms("Mg(OH)2"), string("H2MgO2"));
    CHECK_EQ(countOfAtoms("K4(ON(SO3)2)2"), string("K4N2O14S4"));
    CHECK_EQ(countOfAtoms("Be32"), string("Be32"));
    CHECK_EQ(countOfAtoms("((H))"), string("H"));
}
static void t_S3_decodeString() {
    CHECK_EQ(decodeString("3[a]2[bc]"), string("aaabcbc"));
    CHECK_EQ(decodeString("3[a2[c]]"), string("accaccacc"));
    CHECK_EQ(decodeString("2[abc]3[cd]ef"), string("abcabccdcdcdef"));
    CHECK_EQ(decodeString("10[a]"), string("aaaaaaaaaa"));
    CHECK_EQ(decodeString("abc"), string("abc"));
    CHECK_EQ(decodeString(""), string(""));
}
static void t_S4_reverseParentheses() {
    CHECK_EQ(reverseParentheses("(abcd)"), string("dcba"));
    CHECK_EQ(reverseParentheses("(u(love)i)"), string("iloveu"));
    CHECK_EQ(reverseParentheses("(ed(et(oc))el)"), string("leetcode"));
    CHECK_EQ(reverseParentheses("a(bcdefghijkl(mno)p)q"), string("apmnolkjihgfedcbq"));
    CHECK_EQ(reverseParentheses("()ab"), string("ab"));
    CHECK_EQ(reverseParentheses(""), string(""));
}
static void t_S5_removeDuplicatesK() {
    CHECK_EQ(removeDuplicatesK("abcd", 2), string("abcd"));
    CHECK_EQ(removeDuplicatesK("deeedbbcccbdaa", 3), string("aa"));
    CHECK_EQ(removeDuplicatesK("pbbcggttciiippooaais", 2), string("ps"));
    CHECK_EQ(removeDuplicatesK("aaa", 3), string(""));
    CHECK_EQ(removeDuplicatesK("abc", 1), string(""));          // degenerate k
    CHECK_EQ(removeDuplicatesK("", 2), string(""));
}
static void t_S6_backspaceCompare() {
    CHECK_EQ(backspaceCompare("ab#c", "ad#c"), true);
    CHECK_EQ(backspaceCompare("ab##", "c#d#"), true);
    CHECK_EQ(backspaceCompare("a#c", "b"), false);
    CHECK_EQ(backspaceCompare("a##c", "#a#c"), true);            // '#' on empty text
    CHECK_EQ(backspaceCompare("", "#"), true);
    CHECK_EQ(backspaceCompare("bxj##tw", "bxo#j##tw"), true);
    CHECK_EQ(backspaceCompare("y#fo##f", "y#f#o##f"), true);
    CHECK_EQ(backspaceCompare("abc", "abcd#d"), false);
}
static void t_S7_calculate() {
    CHECK_EQ(calculate("3+2*2"), 7);
    CHECK_EQ(calculate(" 3/2 "), 1);
    CHECK_EQ(calculate(" 3+5 / 2 "), 5);
    CHECK_EQ(calculate("14-3/2"), 13);
    CHECK_EQ(calculate("2*3-4/2+10"), 14);
    CHECK_EQ(calculate("0"), 0);
    CHECK_EQ(calculate("1-1-1"), -1);                           // left to right
}
static void t_M1_nextGreaterCircular() {
    CHECK_EQ(nextGreaterCircular({1, 2, 1}), (VI{2, -1, 2}));
    CHECK_EQ(nextGreaterCircular({1, 2, 3, 4, 3}), (VI{2, 3, 4, -1, 4}));
    CHECK_EQ(nextGreaterCircular({5, 5, 5}), (VI{-1, -1, -1}));  // equal is not greater
    CHECK_EQ(nextGreaterCircular({}), (VI{}));
    CHECK_EQ(nextGreaterCircular({3, 8, 4, 1, 2}), (VI{8, -1, 8, 2, 3}));
}
static void t_M2_nearestSmallerToLeft() {
    CHECK_EQ(nearestSmallerToLeft({4, 5, 2, 10, 8}), (VI{-1, 4, -1, 2, 2}));
    CHECK_EQ(nearestSmallerToLeft({1, 3, 0, 2, 5}), (VI{-1, 1, -1, 0, 2}));
    CHECK_EQ(nearestSmallerToLeft({3, 2, 1}), (VI{-1, -1, -1}));
    CHECK_EQ(nearestSmallerToLeft({2, 2, 3}), (VI{-1, -1, 2}));   // strictly smaller
    CHECK_EQ(nearestSmallerToLeft({}), (VI{}));
}
static void t_M3_pivotElements() {
    CHECK_EQ(pivotElements({5, 1, 4, 3, 6, 8, 10, 7, 9}), (VI{6}));
    CHECK_EQ(pivotElements({1, 2, 3}), (VI{1, 2, 3}));
    CHECK_EQ(pivotElements({3, 2, 1}), (VI{}));
    CHECK_EQ(pivotElements({1, 1, 2}), (VI{2}));                // strict on both sides
    CHECK_EQ(pivotElements({7}), (VI{7}));
    CHECK_EQ(pivotElements({}), (VI{}));
    CHECK_EQ(pivotElements({1, INT_MAX}), (VI{1, INT_MAX}));    // sentinel trap
}
static void t_M4_sumSubarrayMins() {
    CHECK_EQ(sumSubarrayMins({3, 1, 2, 4}), 17);
    CHECK_EQ(sumSubarrayMins({11, 81, 94, 43, 3}), 444);
    CHECK_EQ(sumSubarrayMins({2, 2, 2}), 12);                   // duplicates counted once
    CHECK_EQ(sumSubarrayMins({}), 0);
    CHECK_EQ(sumSubarrayMins(VI(30000, 30000)), 449905500);     // 30000 * n(n+1)/2 mod 1e9+7: overflow + modulo
}
static void t_M5_removeKdigits() {
    CHECK_EQ(removeKdigits("1432219", 3), string("1219"));
    CHECK_EQ(removeKdigits("10200", 1), string("200"));
    CHECK_EQ(removeKdigits("10", 2), string("0"));
    CHECK_EQ(removeKdigits("112", 1), string("11"));
    CHECK_EQ(removeKdigits("9", 1), string("0"));
    CHECK_EQ(removeKdigits("1234567890", 9), string("0"));
    CHECK_EQ(removeKdigits("12345", 0), string("12345"));
}
static void t_W1_longestDistinctSubstring() {
    CHECK_EQ(longestDistinctSubstring("abcabcbb"), string("abc"));
    CHECK_EQ(longestDistinctSubstring("bbbbb"), string("b"));
    CHECK_EQ(longestDistinctSubstring("pwwkew"), string("wke"));
    CHECK_EQ(longestDistinctSubstring("dvdf"), string("vdf"));
    CHECK_EQ(longestDistinctSubstring("abba"), string("ab"));   // stale last-seen index trap
    CHECK_EQ(longestDistinctSubstring("a b!a"), string("a b!"));
    CHECK_EQ(longestDistinctSubstring(""), string(""));
}
static void t_W2_longestAtMostKDistinct() {
    CHECK_EQ(longestAtMostKDistinct("eceba", 2), 3);
    CHECK_EQ(longestAtMostKDistinct("aa", 1), 2);
    CHECK_EQ(longestAtMostKDistinct("abaccc", 2), 4);
    CHECK_EQ(longestAtMostKDistinct("a", 0), 0);
    CHECK_EQ(longestAtMostKDistinct("", 2), 0);
    CHECK_EQ(longestAtMostKDistinct("abc", 5), 3);
}
static void t_W3_characterReplacement() {
    CHECK_EQ(characterReplacement("ABAB", 2), 4);
    CHECK_EQ(characterReplacement("AABABBA", 1), 4);
    CHECK_EQ(characterReplacement("AAAA", 0), 4);
    CHECK_EQ(characterReplacement("ABCDE", 1), 2);
    CHECK_EQ(characterReplacement("", 1), 0);
}
static void t_W4_numSubarrayProductLessThanK() {
    CHECK_EQ(numSubarrayProductLessThanK({10, 5, 2, 6}, 100), 8);
    CHECK_EQ(numSubarrayProductLessThanK({1, 2, 3}, 0), 0);
    CHECK_EQ(numSubarrayProductLessThanK({1, 1, 1}, 2), 6);
    CHECK_EQ(numSubarrayProductLessThanK({1, 1, 1}, 1), 0);
    CHECK_EQ(numSubarrayProductLessThanK({}, 10), 0);
}
static void t_W5_checkInclusion() {
    CHECK_EQ(checkInclusion("ab", "eidbaooo"), true);
    CHECK_EQ(checkInclusion("ab", "eidboaoo"), false);
    CHECK_EQ(checkInclusion("adc", "dcda"), true);
    CHECK_EQ(checkInclusion("a", ""), false);
    CHECK_EQ(checkInclusion("", "abc"), true);
    CHECK_EQ(checkInclusion("abc", "ab"), false);
}
static void t_W6_subarraysWithKDistinct() {
    CHECK_EQ(subarraysWithKDistinct({1, 2, 1, 2, 3}, 2), 7);
    CHECK_EQ(subarraysWithKDistinct({1, 2, 1, 3, 4}, 3), 3);
    CHECK_EQ(subarraysWithKDistinct({1, 1, 1}, 1), 6);
    CHECK_EQ(subarraysWithKDistinct({1, 2}, 3), 0);
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_S1_moleculeWeight);
    SECTION(t_S2_countOfAtoms);
    SECTION(t_S3_decodeString);
    SECTION(t_S4_reverseParentheses);
    SECTION(t_S5_removeDuplicatesK);
    SECTION(t_S6_backspaceCompare);
    SECTION(t_S7_calculate);
    SECTION(t_M1_nextGreaterCircular);
    SECTION(t_M2_nearestSmallerToLeft);
    SECTION(t_M3_pivotElements);
    SECTION(t_M4_sumSubarrayMins);
    SECTION(t_M5_removeKdigits);
    SECTION(t_W1_longestDistinctSubstring);
    SECTION(t_W2_longestAtMostKDistinct);
    SECTION(t_W3_characterReplacement);
    SECTION(t_W4_numSubarrayProductLessThanK);
    SECTION(t_W5_checkInclusion);
    SECTION(t_W6_subarraysWithKDistinct);
    return tst::summary("agoda_day1");
}
