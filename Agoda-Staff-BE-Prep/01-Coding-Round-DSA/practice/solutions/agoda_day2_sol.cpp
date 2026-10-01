// REFERENCE SOLUTIONS for agoda_day2.cpp. Spoilers: open only after your version passes.
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

// B1: answer is monotone (bigger capacity never needs more days) -> first capacity that works.
//     lo = heaviest package (must fit), hi = everything in one day. O(n log(sum)).
static bool canShipWithin(const VI& weights, int days, long long capacity) {
    int daysUsed = 1;
    long long load = 0;
    for (int w : weights) {
        if (load + w > capacity) { ++daysUsed; load = 0; }
        load += w;
    }
    return daysUsed <= days;
}

int shipWithinDays(const VI& weights, int days) {
    long long lo = *max_element(weights.begin(), weights.end());
    long long hi = accumulate(weights.begin(), weights.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canShipWithin(weights, days, mid)) hi = mid;
        else lo = mid + 1;
    }
    return static_cast<int>(lo);
}

// B2: same "first value that works" template; ceil division without floating point.
int smallestDivisor(const VI& a, int threshold) {
    auto total = [&](int d) {
        long long sum = 0;
        for (int x : a) sum += (x + d - 1) / d;
        return sum;
    };
    int lo = 1, hi = *max_element(a.begin(), a.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (total(mid) <= threshold) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// B3: "maximize the minimum" -> LAST gap that works. Upper-mid avoids the infinite loop. O(n log n + n log range).
int maxMinDistance(VI positions, int m) {
    sort(positions.begin(), positions.end());
    auto canPlace = [&](int gap) {
        int placed = 1, last = positions[0];
        for (size_t i = 1; i < positions.size(); ++i)
            if (positions[i] - last >= gap) { ++placed; last = positions[i]; }
        return placed >= m;
    };
    int lo = 1, hi = positions.back() - positions.front();
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;   // upper mid: lo = mid must make progress
        if (canPlace(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// B4: sort + prefix sums; for each q split at lower_bound. O((n + Q) log n).
vector<ll> minOperationsQueries(VI a, const VI& queries) {
    sort(a.begin(), a.end());
    int n = static_cast<int>(a.size());
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i];
    vector<ll> answer;
    answer.reserve(queries.size());
    for (int q : queries) {
        int below = static_cast<int>(lower_bound(a.begin(), a.end(), q) - a.begin());  // a[0..below) < q
        ll raise = static_cast<ll>(q) * below - prefix[below];
        ll lower = (prefix[n] - prefix[below]) - static_cast<ll>(q) * (n - below);
        answer.push_back(raise + lower);
    }
    return answer;
}

// G1: shoot in order of arrival. The plane shot at minute i must arrive strictly after i.
//     arrival = ceil(dist / speed) in integers (no doubles). O(n log n); O(n) with counting (arrival > n never matters).
int eliminateMaximum(const VI& dist, const VI& speed) {
    int n = static_cast<int>(dist.size());
    vector<long long> arrival(n);
    for (int i = 0; i < n; ++i) arrival[i] = (static_cast<long long>(dist[i]) + speed[i] - 1) / speed[i];
    sort(arrival.begin(), arrival.end());
    for (int minute = 0; minute < n; ++minute)
        if (arrival[minute] <= minute) return minute;
    return n;
}

// G2: after sorting, the closest pair is always adjacent. One pass, reset the list on a new minimum.
VVI minimumAbsDifference(VI a) {
    sort(a.begin(), a.end());
    long long best = LLONG_MAX;
    VVI pairs;
    for (size_t i = 1; i < a.size(); ++i) {
        long long diff = static_cast<long long>(a[i]) - a[i - 1];
        if (diff < best) { best = diff; pairs.clear(); }
        if (diff == best) pairs.push_back({a[i - 1], a[i]});
    }
    return pairs;
}

// G3: count map; k == 0 needs a duplicate, else check x + k exists. Use count(), never operator[]
//     while iterating the same map (it inserts, can rehash, and invalidates the loop).
int findPairsKDiff(const VI& a, int k) {
    unordered_map<int, int> freq;
    for (int x : a) ++freq[x];
    int pairs = 0;
    for (const auto& [x, f] : freq) {
        if (k == 0) pairs += f > 1;
        else pairs += freq.count(x + k) > 0;
    }
    return pairs;
}

// G4: sort + unique gives the distinct values in order; rank = position + 1. O(n log n).
VI arrayRankTransform(const VI& a) {
    VI distinct = a;
    sort(distinct.begin(), distinct.end());
    distinct.erase(unique(distinct.begin(), distinct.end()), distinct.end());
    VI rank(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        rank[i] = static_cast<int>(lower_bound(distinct.begin(), distinct.end(), a[i]) - distinct.begin()) + 1;
    return rank;
}

// G5: custom comparator (a strict weak ordering!). O(n log n).
VI frequencySort(VI a) {
    unordered_map<int, int> freq;
    for (int x : a) ++freq[x];
    sort(a.begin(), a.end(), [&](int x, int y) {
        int fx = freq.at(x), fy = freq.at(y);
        return fx != fy ? fx < fy : x > y;
    });
    return a;
}

// G6: halving x saves ceil(x/2), which grows with x -> always halve the current most expensive item.
//     Stop early when the max is 0 (m can be huge). O((n + min(m, 31n)) log n).
long long minCostWithCoupons(const VI& price, int m) {
    priority_queue<int> maxHeap(price.begin(), price.end());
    while (m-- > 0 && !maxHeap.empty() && maxHeap.top() > 0) {
        int top = maxHeap.top();
        maxHeap.pop();
        maxHeap.push(top / 2);
    }
    long long total = 0;
    while (!maxHeap.empty()) { total += maxHeap.top(); maxHeap.pop(); }
    return total;
}

// G7: '1' and '3' can never pass each other; '2' can move anywhere. So keep the 1/3 order and put
//     every '2' right before the first '3' (after the leading 1s). O(n).
string smallestTaskQueue(const string& s) {
    size_t twos = count(s.begin(), s.end(), '2');
    string rest;
    rest.reserve(s.size());
    for (char c : s) if (c != '2') rest += c;
    size_t firstThree = rest.find('3');
    if (firstThree == string::npos) firstThree = rest.size();
    return rest.substr(0, firstThree) + string(twos, '2') + rest.substr(firstThree);
}

// G8: frame formula: (maxFreq - 1) blocks of (n + 1) slots, plus one slot per task tied at maxFreq.
//     Never less than the number of tasks. Guard empty input (the formula breaks there).
int leastInterval(const vector<char>& tasks, int n) {
    if (tasks.empty()) return 0;
    array<int, 26> freq{};
    for (char t : tasks) ++freq[t - 'A'];
    int maxFreq = *max_element(freq.begin(), freq.end());
    int tiedAtMax = static_cast<int>(count(freq.begin(), freq.end(), maxFreq));
    int frame = (maxFreq - 1) * (n + 1) + tiedAtMax;
    return max(frame, static_cast<int>(tasks.size()));
}

// G9: possible iff maxFreq <= (n + 1) / 2. Fill even slots with the most frequent letter first, then the rest,
//     wrapping to odd slots. O(n).
string reorganizeString(const string& s) {
    array<int, 26> freq{};
    for (char c : s) ++freq[c - 'a'];
    int n = static_cast<int>(s.size());
    int top = static_cast<int>(max_element(freq.begin(), freq.end()) - freq.begin());
    if (freq[top] > (n + 1) / 2) return "";
    string out(n, ' ');
    int slot = 0;
    auto place = [&](int letter) {
        while (freq[letter] > 0) {
            if (slot >= n) slot = 1;            // even slots are full: continue on odd slots
            out[slot] = static_cast<char>('a' + letter);
            slot += 2;
            --freq[letter];
        }
    };
    place(top);
    for (int letter = 0; letter < 26; ++letter) place(letter);
    return out;
}

// I1: for each centre i, members = n - (#intervals ending before start[i]) - (#starting after end[i]).
//     Two sorted arrays + binary search. O(n log n).
int maxTeamSize(const VI& start, const VI& end) {
    int n = static_cast<int>(start.size());
    VI starts = start, ends = end;
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int best = 0;
    for (int i = 0; i < n; ++i) {
        int endBefore = static_cast<int>(lower_bound(ends.begin(), ends.end(), start[i]) - ends.begin());
        int startAfter = static_cast<int>(starts.end() - upper_bound(starts.begin(), starts.end(), end[i]));
        best = max(best, n - endBefore - startAfter);
    }
    return best;
}

// I2: difference map sorted by location; drop-off and pick-up at the same stop net out. O(n log n).
bool carPooling(const VVI& trips, int capacity) {
    map<int, int> change;
    for (const auto& t : trips) { change[t[1]] += t[0]; change[t[2]] -= t[0]; }
    int onboard = 0;
    for (const auto& [stop, delta] : change) {
        onboard += delta;
        if (onboard > capacity) return false;
    }
    return true;
}

// I3: difference array + prefix sum. O(n + bookings).
VI corpFlightBookings(const VVI& bookings, int n) {
    VI diff(n + 1, 0);
    for (const auto& b : bookings) { diff[b[0] - 1] += b[2]; diff[b[1]] -= b[2]; }
    VI seats(n);
    partial_sum(diff.begin(), diff.end() - 1, seats.begin());
    return seats;
}

// I4: tentatively add the booking to a sweep map; if any point reaches 3, roll it back. O(n) per booking.
class MyCalendarTwo {
    map<int, int> change_;
public:
    bool book(int start, int end) {
        ++change_[start];
        --change_[end];
        int active = 0;
        for (const auto& [time, delta] : change_) {
            active += delta;
            if (active >= 3) {
                if (--change_[start] == 0) change_.erase(start);   // roll back, then stop iterating
                if (++change_[end] == 0) change_.erase(end);
                return false;
            }
            if (time >= end) break;                               // later points are unaffected
        }
        return true;
    }
};

// I5: two min-heaps: free rooms (by index) and busy rooms (by end time, then index).
//     Delayed meetings keep their duration. long long: end times grow with delays. O(m log m + m log n).
int mostBooked(int n, VVI meetings) {
    sort(meetings.begin(), meetings.end());
    priority_queue<int, vector<int>, greater<int>> freeRooms;
    for (int room = 0; room < n; ++room) freeRooms.push(room);
    using EndAndRoom = pair<long long, int>;
    priority_queue<EndAndRoom, vector<EndAndRoom>, greater<EndAndRoom>> busy;
    vector<int> uses(n, 0);
    for (const auto& meeting : meetings) {
        long long start = meeting[0], duration = meeting[1] - meeting[0];
        while (!busy.empty() && busy.top().first <= start) {
            freeRooms.push(busy.top().second);
            busy.pop();
        }
        int room;
        long long finish;
        if (!freeRooms.empty()) {
            room = freeRooms.top();
            freeRooms.pop();
            finish = start + duration;
        } else {
            auto [freeAt, earliestRoom] = busy.top();
            busy.pop();
            room = earliestRoom;
            finish = freeAt + duration;
        }
        busy.push({finish, room});
        ++uses[room];
    }
    return static_cast<int>(max_element(uses.begin(), uses.end()) - uses.begin());   // first max = lowest index
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
