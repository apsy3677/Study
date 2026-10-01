// AGODA DAY 1: Stack parsing (S), Monotonic stack (M), Sliding window (W)
// Cards: ../02-Pattern-Cards.md   Hints + tests to say aloud: ../03-Problem-Bank.md
//
// HOW TO USE (the Agoda live round is: explain -> code -> RUN -> pass all tests)
//   1. Pick a stub. Timer on. Say: clarifying questions, brute force, better idea, complexity. (<= 4 min)
//   2. Before coding, write 3-5 of YOUR OWN test cases as comments under the stub (Agoda grades "testing").
//   3. Code it (target 12-18 min). No autocomplete, like HackerRank CodePair.
//   4. Build & run:  g++ -std=c++17 -O1 -g -fsanitize=address,undefined agoda_day1.cpp -o d1 && ./d1
//      One problem only:  ./d1 molecule      (any substring of the test name)
//      No compiler? Paste the whole file into https://godbolt.org (x86-64 gcc, flags -std=c++17, enable "Execute")
//   5. Log time + bug in ../PROGRESS.md. Open solutions/agoda_day1_sol.cpp only after passing (or 10 min stuck after hints).
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

// ★★★ S1  Molecule weight (Agoda Gurugram R1 Oct 2025; Agoda R1 Dec 2025; LC 726 variant)
// Atom weights are given (e.g. C=12, H=1, O=8). Element = uppercase letter + optional lowercase letters.
// A count may follow an element or a ')'. Parentheses nest. "CH4" -> 16, "H(CH4)2" -> 33.
long long moleculeWeight(const string& formula, const unordered_map<string, long long>& weight) {
    return 0;
}

// ★ S2  Number of Atoms (LC 726, hard). Return counts as "H2MgO2": names sorted, count omitted when 1.
string countOfAtoms(const string& formula) {
    return "";
}

// ★★ S3  Decode String (LC 394). "3[a2[c]]" -> "accaccacc". Counts can be multi-digit.
string decodeString(const string& s) {
    return "";
}

// ★★ S4  Reverse Substrings Between Each Pair of Parentheses (LC 1190). "(u(love)i)" -> "iloveu".
string reverseParentheses(const string& s) {
    return "";
}

// ★★★ S5  Remove All Adjacent Duplicates in String II (LC 1209): repeatedly delete k adjacent equal chars.
string removeDuplicatesK(const string& s, int k) {
    return "";
}

// ★★ S6  Backspace String Compare (LC 844). '#' deletes the previous char. Follow-up: O(1) extra space.
bool backspaceCompare(const string& s, const string& t) {
    return false;
}

// ★★ S7  Basic Calculator II (LC 227): + - * / on non-negative ints, spaces allowed, '/' truncates toward 0.
int calculate(const string& s) {
    return 0;
}

// ★★★ M1  Next Greater Element II (LC 503): circular array; -1 when none.
//          (Agoda Gurugram Staff R1 Feb 2026: "variant of the largest greater number on the right side")
VI nextGreaterCircular(const VI& a) {
    return {};
}

// ★★★ M2  Nearest smaller element to the LEFT (strictly smaller value), -1 if none. Values are >= 0.
//          (Agoda Staff R1 2026: "monotonic stack problem involving nearest smaller element")
VI nearestSmallerToLeft(const VI& a) {
    return {};
}

// ★★★ M3  Pivot elements: values whose every left element is strictly smaller and every right element
//          strictly greater. Return them in order. (Glassdoor, Agoda Staff India)
VI pivotElements(const VI& a) {
    return {};
}

// ★★ M4  Sum of Subarray Minimums (LC 907), modulo 1e9+7.
int sumSubarrayMins(const VI& a) {
    return 0;
}

// ★★ M5  Remove K Digits (LC 402): smallest number after removing k digits. No leading zeros; "0" if empty.
string removeKdigits(const string& num, int k) {
    return "";
}

// ★★★ W1  Longest substring with all distinct characters: return the SUBSTRING (first one on ties).
//          (Agoda Gurugram Staff R1 Feb 2026; LC 3 returns only the length)
string longestDistinctSubstring(const string& s) {
    return "";
}

// ★★ W2  Longest substring with at most k distinct characters (LC 340 / LC 904 "fruit into baskets").
int longestAtMostKDistinct(const string& s, int k) {
    return 0;
}

// ★★ W3  Longest Repeating Character Replacement (LC 424). Uppercase A-Z.
int characterReplacement(const string& s, int k) {
    return 0;
}

// ★★ W4  Subarray Product Less Than K (LC 713). Positive integers.
int numSubarrayProductLessThanK(const VI& a, int k) {
    return 0;
}

// ★ W5  Permutation in String (LC 567): does s contain a permutation of p? Lowercase a-z.
bool checkInclusion(const string& p, const string& s) {
    return false;
}

// ★ W6  Subarrays with K Different Integers (LC 992, hard): count subarrays with EXACTLY k distinct.
int subarraysWithKDistinct(const VI& a, int k) {
    return 0;
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
