// AGODA DAY 2: Binary search on the answer (B), Greedy / sorting / heaps (G), Intervals & sweep (I)
// Cards: ../02-Pattern-Cards.md   Hints + tests to say aloud: ../03-Problem-Bank.md
//
// HOW TO USE (the Agoda live round is: explain -> code -> RUN -> pass all tests)
//   1. Pick a stub. Timer on. Say: clarifying questions, brute force, better idea, complexity. (<= 4 min)
//   2. Before coding, write 3-5 of YOUR OWN test cases as comments under the stub (Agoda grades "testing").
//   3. Code it (target 12-18 min). No autocomplete, like HackerRank CodePair.
//   4. Build & run:  g++ -std=c++17 -O1 -g -fsanitize=address,undefined agoda_day2.cpp -o d2 && ./d2
//      One problem only:  ./d2 G1       (any substring of the test name)
//      No compiler? Paste the whole file into https://godbolt.org (x86-64 gcc, flags -std=c++17, enable "Execute")
//   5. Log time + bug in ../PROGRESS.md. Open solutions/agoda_day2_sol.cpp only after passing (or 10 min stuck after hints).
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

// ★★★ B1  Capacity To Ship Packages Within D Days (LC 1011). Packages ship in the given order.
int shipWithinDays(const VI& weights, int days) {
    return 0;
}

// ★★ B2  Find the Smallest Divisor Given a Threshold (LC 1283): sum of ceil(a[i]/d) <= threshold.
int smallestDivisor(const VI& a, int threshold) {
    return 0;
}

// ★★★ B3  Magnetic Force Between Two Balls (LC 1552) = "aggressive cows": place m balls at the given
//          positions to MAXIMIZE the MINIMUM gap. (Agoda SSE OA: "binary search to find maximum of minimum")
int maxMinDistance(VI positions, int m) {
    return 0;
}

// ★★ B4  Minimum Operations to Make All Array Elements Equal (LC 2602). For each query q, the cost
//         to make every a[i] equal to q with +1/-1 steps. (Agoda Staff OA, Nov 2025)
vector<ll> minOperationsQueries(VI a, const VI& queries) {
    return {};
}

// ★★★ G1  Eliminate Maximum Number of Monsters (LC 1921) = Agoda's "airplanes": plane i is dist[i] away
//          at speed[i]. You shoot one plane per minute, starting at minute 0. If a plane lands at the
//          same moment you're ready to shoot, you lose. How many can you shoot before any lands?
//          (Agoda Gurugram SSE [SHP] R1 Oct 2025; Glassdoor Agoda Staff India)
int eliminateMaximum(const VI& dist, const VI& speed) {
    return 0;
}

// ★★★ G2  Minimum Absolute Difference (LC 1200): all pairs [a, b] (a < b) with the minimum difference,
//          in ascending order. Distinct integers. (Agoda Staff R1 2025; Agoda LC tag)
VVI minimumAbsDifference(VI a) {
    return {};
}

// ★★ G3  K-diff Pairs in an Array (LC 532): number of UNIQUE pairs (x, y) with |x - y| == k, k >= 0.
int findPairsKDiff(const VI& a, int k) {
    return 0;
}

// ★★★ G4  Rank Transform of an Array (LC 1331): rank 1 = smallest; equal values share a rank; ranks are
//          consecutive. (Agoda Staff R1 2026: "give ranks of every element in priorities")
VI arrayRankTransform(const VI& a) {
    return {};
}

// ★★ G5  Sort Array by Increasing Frequency (LC 1636): ties broken by DECREASING value.
VI frequencySort(VI a) {
    return {};
}

// ★★ G6  Discount coupons (Agoda OA 2025): applying one coupon to an item sets its price to
//         floor(price / 2). Several coupons may go on the same item. Minimum total with at most m coupons.
long long minCostWithCoupons(const VI& price, int m) {
    return 0;
}

// ★★ G7  Task queue (Agoda OA 2025): string of '1','2','3'. You may swap ADJACENT '1'<->'2' and
//         '2'<->'3' any number of times. Return the lexicographically smallest string.
string smallestTaskQueue(const string& s) {
    return "";
}

// ★★ G8  Task Scheduler (LC 621): same task needs n idle slots between runs. Minimum total slots.
//         (Agoda Gurgaon backend 2021)
int leastInterval(const vector<char>& tasks, int n) {
    return 0;
}

// ★★ G9  Reorganize String (LC 767): no two adjacent chars equal; "" if impossible. Any valid answer.
string reorganizeString(const string& s) {
    return "";
}

// ★★★ I1  Maximum Team Size with Overlapping Intervals (LC 3893; Agoda LC tag, recent): employee i works
//          [start[i], end[i]] (closed). A team is valid if ONE member overlaps every other member.
int maxTeamSize(const VI& start, const VI& end) {
    return 0;
}

// ★★ I2  Car Pooling (LC 1094): trips[i] = {passengers, from, to}. Passengers leave at 'to'.
bool carPooling(const VVI& trips, int capacity) {
    return false;
}

// ★★ I3  Corporate Flight Bookings (LC 1109): bookings[i] = {first, last, seats} (1-indexed, inclusive).
VI corpFlightBookings(const VVI& bookings, int n) {
    return {};
}

// ★★ I4  My Calendar II (LC 731): book [start, end) unless it would cause a TRIPLE booking.
class MyCalendarTwo {
public:
    bool book(int start, int end) {
        return false;
    }
};

// ★★ I5  Meeting Rooms III (LC 2402): rooms 0..n-1; meeting goes to the lowest free room; if none is free,
//         it waits for the earliest-free room (ties: lowest index) and keeps its duration. Return the room
//         that held the most meetings (ties: lowest index). Your Google R2 question (2023): rematch!
int mostBooked(int n, VVI meetings) {
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
static void t_B1_shipWithinDays() {
    CHECK_EQ(shipWithinDays({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5), 15);
    CHECK_EQ(shipWithinDays({3, 2, 2, 4, 1, 4}, 3), 6);
    CHECK_EQ(shipWithinDays({1, 2, 3, 1, 1}, 4), 3);
    CHECK_EQ(shipWithinDays({10}, 1), 10);
    CHECK_EQ(shipWithinDays({1, 1, 1, 1}, 4), 1);
    CHECK_EQ(shipWithinDays({7, 2, 5, 10, 8}, 2), 18);           // = LC 410 split array largest sum
}
static void t_B2_smallestDivisor() {
    CHECK_EQ(smallestDivisor({1, 2, 5, 9}, 6), 5);
    CHECK_EQ(smallestDivisor({44, 22, 33, 11, 1}, 5), 44);
    CHECK_EQ(smallestDivisor({21212, 10101, 12121}, 1000000), 1);
    CHECK_EQ(smallestDivisor({2, 3, 5, 7, 11}, 11), 3);
    CHECK_EQ(smallestDivisor({19}, 5), 4);
}
static void t_B3_maxMinDistance() {
    CHECK_EQ(maxMinDistance({1, 2, 3, 4, 7}, 3), 3);
    CHECK_EQ(maxMinDistance({5, 4, 3, 2, 1, 1000000000}, 2), 999999999);
    CHECK_EQ(maxMinDistance({1, 2, 3}, 3), 1);
    CHECK_EQ(maxMinDistance({1, 100}, 2), 99);
    CHECK_EQ(maxMinDistance({79, 74, 57, 22}, 4), 5);             // unsorted input
}
static void t_B4_minOperationsQueries() {
    CHECK_EQ(minOperationsQueries({3, 1, 6, 8}, {1, 5}), (vector<ll>{14, 10}));
    CHECK_EQ(minOperationsQueries({2, 9, 6, 3}, {10}), (vector<ll>{20}));
    CHECK_EQ(minOperationsQueries({5}, {5, 0, 10}), (vector<ll>{0, 5, 5}));
    CHECK_EQ(minOperationsQueries({}, {7}), (vector<ll>{0}));
    CHECK_EQ(minOperationsQueries({1000000000, 1000000000}, {0}), (vector<ll>{2000000000}));  // > INT_MAX
}
static void t_G1_eliminateMaximum() {
    CHECK_EQ(eliminateMaximum({1, 3, 4}, {1, 1, 1}), 3);
    CHECK_EQ(eliminateMaximum({1, 1, 2, 3}, {1, 1, 1, 1}), 1);
    CHECK_EQ(eliminateMaximum({3, 2, 4}, {5, 3, 2}), 1);
    CHECK_EQ(eliminateMaximum({4, 2, 3}, {2, 1, 1}), 3);
    CHECK_EQ(eliminateMaximum({3, 5, 7, 4, 5}, {2, 3, 6, 3, 2}), 2);   // fractional arrival times
    CHECK_EQ(eliminateMaximum({1, 1}, {1, 1}), 1);                     // tie at the shooting moment = loss
    CHECK_EQ(eliminateMaximum({5}, {10}), 1);
    CHECK_EQ(eliminateMaximum({}, {}), 0);
}
static void t_G2_minimumAbsDifference() {
    CHECK_EQ(minimumAbsDifference({4, 2, 1, 3}), (VVI{{1, 2}, {2, 3}, {3, 4}}));
    CHECK_EQ(minimumAbsDifference({1, 3, 6, 10, 15}), (VVI{{1, 3}}));
    CHECK_EQ(minimumAbsDifference({3, 8, -10, 23, 19, -4, -14, 27}), (VVI{{-14, -10}, {19, 23}, {23, 27}}));
    CHECK_EQ(minimumAbsDifference({5}), (VVI{}));
    CHECK_EQ(minimumAbsDifference({-2000000000, 2000000000}), (VVI{{-2000000000, 2000000000}}));  // diff > INT_MAX
}
static void t_G3_findPairsKDiff() {
    CHECK_EQ(findPairsKDiff({3, 1, 4, 1, 5}, 2), 2);
    CHECK_EQ(findPairsKDiff({1, 2, 3, 4, 5}, 1), 4);
    CHECK_EQ(findPairsKDiff({1, 3, 1, 5, 4}, 0), 1);
    CHECK_EQ(findPairsKDiff({1, 1, 1, 1}, 0), 1);
    CHECK_EQ(findPairsKDiff({1, 2, 4, 4, 3, 3, 0, 9, 2, 3}, 3), 2);
    CHECK_EQ(findPairsKDiff({}, 1), 0);
}
static void t_G4_arrayRankTransform() {
    CHECK_EQ(arrayRankTransform({40, 10, 20, 30}), (VI{4, 1, 2, 3}));
    CHECK_EQ(arrayRankTransform({100, 100, 100}), (VI{1, 1, 1}));
    CHECK_EQ(arrayRankTransform({37, 12, 28, 9, 100, 56, 80, 5, 12}), (VI{5, 3, 4, 2, 8, 6, 7, 1, 3}));
    CHECK_EQ(arrayRankTransform({-5, 0, -5}), (VI{1, 2, 1}));
    CHECK_EQ(arrayRankTransform({}), (VI{}));
}
static void t_G5_frequencySort() {
    CHECK_EQ(frequencySort({1, 1, 2, 2, 2, 3}), (VI{3, 1, 1, 2, 2, 2}));
    CHECK_EQ(frequencySort({2, 3, 1, 3, 2}), (VI{1, 3, 3, 2, 2}));
    CHECK_EQ(frequencySort({-1, 1, -6, 4, 5, -6, 1, 4, 1}), (VI{5, -1, 4, 4, -6, -6, 1, 1, 1}));
    CHECK_EQ(frequencySort({}), (VI{}));
}
static void t_G6_minCostWithCoupons() {
    CHECK_EQ(minCostWithCoupons({2, 4}, 2), 3LL);
    CHECK_EQ(minCostWithCoupons({1, 2, 3}, 0), 6LL);
    CHECK_EQ(minCostWithCoupons({8}, 3), 1LL);                     // several coupons on one item
    CHECK_EQ(minCostWithCoupons({5, 5}, 1), 7LL);
    CHECK_EQ(minCostWithCoupons({7, 3}, 2), 4LL);
    CHECK_EQ(minCostWithCoupons({}, 3), 0LL);
    CHECK_EQ(minCostWithCoupons({1000000000, 1}, 100), 0LL);       // more coupons than useful
    CHECK_EQ(minCostWithCoupons({1000000000, 1000000000, 1000000000}, 0), 3000000000LL);
}
static void t_G7_smallestTaskQueue() {
    CHECK_EQ(smallestTaskQueue("3121"), string("2311"));
    CHECK_EQ(smallestTaskQueue("123"), string("123"));
    CHECK_EQ(smallestTaskQueue("321"), string("231"));
    CHECK_EQ(smallestTaskQueue("33221"), string("22331"));
    CHECK_EQ(smallestTaskQueue("1312"), string("1231"));
    CHECK_EQ(smallestTaskQueue("3312"), string("2331"));
    CHECK_EQ(smallestTaskQueue("2222"), string("2222"));
    CHECK_EQ(smallestTaskQueue(""), string(""));
}
static void t_G8_leastInterval() {
    CHECK_EQ(leastInterval({'A', 'A', 'A', 'B', 'B', 'B'}, 2), 8);
    CHECK_EQ(leastInterval({'A', 'C', 'A', 'B', 'D', 'B'}, 1), 6);
    CHECK_EQ(leastInterval({'A', 'A', 'A', 'B', 'B', 'B'}, 3), 10);
    CHECK_EQ(leastInterval({'A', 'A', 'A', 'A', 'A', 'A', 'B', 'C', 'D', 'E', 'F', 'G'}, 2), 16);
    CHECK_EQ(leastInterval({'A', 'A', 'A'}, 0), 3);
    CHECK_EQ(leastInterval({}, 2), 0);                             // the formula alone says 23 here
}
static bool isValidReorganization(const string& input, const string& output) {
    if (output.size() != input.size()) return false;
    string a = input, b = output;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a != b) return false;
    for (size_t i = 1; i < output.size(); ++i) if (output[i] == output[i - 1]) return false;
    return true;
}
static void t_G9_reorganizeString() {
    for (string s : {"aab", "vvvlo", "a", "aaabbbccc", "aabb", "abcdefg", "baaba"})
        CHECK(isValidReorganization(s, reorganizeString(s)));
    CHECK_EQ(reorganizeString("aaab"), string(""));
    CHECK_EQ(reorganizeString("zzzzy"), string(""));
    CHECK_EQ(reorganizeString(""), string(""));
}
static void t_I1_maxTeamSize() {
    CHECK_EQ(maxTeamSize({1, 2, 3}, {4, 5, 6}), 3);
    CHECK_EQ(maxTeamSize({2, 5, 8}, {3, 7, 9}), 1);
    CHECK_EQ(maxTeamSize({3, 4, 6}, {8, 5, 7}), 3);
    CHECK_EQ(maxTeamSize({1, 2}, {2, 3}), 2);                     // closed intervals: touching overlaps
    CHECK_EQ(maxTeamSize({1, 10}, {2, 11}), 1);
    CHECK_EQ(maxTeamSize({1, 2, 3, 10}, {10, 2, 3, 11}), 4);
    CHECK_EQ(maxTeamSize({}, {}), 0);
}
static void t_I2_carPooling() {
    CHECK_EQ(carPooling({{2, 1, 5}, {3, 3, 7}}, 4), false);
    CHECK_EQ(carPooling({{2, 1, 5}, {3, 3, 7}}, 5), true);
    CHECK_EQ(carPooling({{2, 1, 5}, {3, 5, 7}}, 3), true);         // drop-off before pick-up at stop 5
    CHECK_EQ(carPooling({{3, 2, 7}, {3, 7, 9}, {8, 3, 9}}, 11), true);
    CHECK_EQ(carPooling({{9, 0, 1}}, 8), false);
    CHECK_EQ(carPooling({}, 0), true);
}
static void t_I3_corpFlightBookings() {
    CHECK_EQ(corpFlightBookings({{1, 2, 10}, {2, 3, 20}, {2, 5, 25}}, 5), (VI{10, 55, 45, 25, 25}));
    CHECK_EQ(corpFlightBookings({{1, 2, 10}, {2, 2, 15}}, 2), (VI{10, 25}));
    CHECK_EQ(corpFlightBookings({}, 3), (VI{0, 0, 0}));
    CHECK_EQ(corpFlightBookings({{1, 1, 5}, {3, 3, 7}}, 3), (VI{5, 0, 7}));
}
static void t_I4_MyCalendarTwo() {
    MyCalendarTwo cal;
    VI got;
    for (auto [s, e] : vector<pair<int, int>>{{10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}})
        got.push_back(cal.book(s, e));
    CHECK_EQ(got, (VI{1, 1, 1, 0, 1, 1}));
    MyCalendarTwo cal2;
    CHECK_EQ(cal2.book(1, 2), true);
    CHECK_EQ(cal2.book(1, 2), true);
    CHECK_EQ(cal2.book(1, 2), false);
    CHECK_EQ(cal2.book(2, 3), true);                               // half-open: [1,2) and [2,3) don't overlap
    CHECK_EQ(cal2.book(5, 6), true);                               // fails if the rejected booking was not rolled back
    CHECK_EQ(cal2.book(0, 5), false);                              // overlaps the double-booked [1,2)
}
static void t_I5_mostBooked() {
    CHECK_EQ(mostBooked(2, {{0, 10}, {1, 5}, {2, 7}, {3, 4}}), 0);
    CHECK_EQ(mostBooked(3, {{1, 20}, {2, 10}, {3, 5}, {4, 9}, {6, 8}}), 1);
    CHECK_EQ(mostBooked(2, {{0, 10}, {1, 2}, {12, 14}, {13, 15}}), 0);   // tie -> lowest index
    CHECK_EQ(mostBooked(2, {{0, 10}, {1, 11}, {2, 3}}), 0);              // delayed meeting keeps its duration
    CHECK_EQ(mostBooked(1, {{0, 1000000000}, {1, 1000000001}, {2, 1000000002}}), 0);  // end times > INT_MAX
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_B1_shipWithinDays);
    SECTION(t_B2_smallestDivisor);
    SECTION(t_B3_maxMinDistance);
    SECTION(t_B4_minOperationsQueries);
    SECTION(t_G1_eliminateMaximum);
    SECTION(t_G2_minimumAbsDifference);
    SECTION(t_G3_findPairsKDiff);
    SECTION(t_G4_arrayRankTransform);
    SECTION(t_G5_frequencySort);
    SECTION(t_G6_minCostWithCoupons);
    SECTION(t_G7_smallestTaskQueue);
    SECTION(t_G8_leastInterval);
    SECTION(t_G9_reorganizeString);
    SECTION(t_I1_maxTeamSize);
    SECTION(t_I2_carPooling);
    SECTION(t_I3_corpFlightBookings);
    SECTION(t_I4_MyCalendarTwo);
    SECTION(t_I5_mostBooked);
    return tst::summary("agoda_day2");
}
