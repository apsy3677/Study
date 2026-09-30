// SPOILERS: reference solutions for day1.cpp. Open only after your version passes,
// or after all hints plus 10 minutes stuck. Compare idioms, not just correctness.
#include "../test.h"

VI twoSum(const VI& a, int target) {
    unordered_map<int, int> idx;                              // value -> index
    for (int i = 0; i < (int)a.size(); ++i) {
        if (auto it = idx.find(target - a[i]); it != idx.end()) return {it->second, i};
        idx[a[i]] = i;                                        // insert AFTER lookup
    }
    return {};
}

int subarraySumK(const VI& a, int k) {
    unordered_map<ll, int> cnt{{0, 1}};                       // empty prefix
    ll s = 0; int ans = 0;
    for (int x : a) {
        s += x;
        if (auto it = cnt.find(s - k); it != cnt.end()) ans += it->second;
        ++cnt[s];
    }
    return ans;
}

int longestConsecutive(const VI& a) {
    unordered_set<int> s(a.begin(), a.end());
    int best = 0;
    for (int x : s) {
        if (s.count(x - 1)) continue;                         // only start at run heads
        int len = 1;
        while (s.count(x + len)) ++len;
        best = max(best, len);
    }
    return best;
}

int maxSubArray(const VI& a) {
    int cur = a[0], best = a[0];
    for (size_t i = 1; i < a.size(); ++i) { cur = max(a[i], cur + a[i]); best = max(best, cur); }
    return best;
}

VI spiralOrder(const VVI& m) {
    VI out;
    if (m.empty()) return out;
    int top = 0, bottom = (int)m.size() - 1, left = 0, right = (int)m[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; ++c) out.push_back(m[top][c]);
        ++top;
        for (int r = top; r <= bottom; ++r) out.push_back(m[r][right]);
        --right;
        if (top <= bottom) { for (int c = right; c >= left; --c) out.push_back(m[bottom][c]); --bottom; }
        if (left <= right) { for (int r = bottom; r >= top; --r) out.push_back(m[r][left]); ++left; }
    }
    return out;
}

void rotateImage(VVI& m) {
    int n = (int)m.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) swap(m[i][j], m[j][i]);   // transpose
    for (auto& row : m) reverse(row.begin(), row.end());          // mirror
}

int maxProfit(const VI& p) {
    int best = 0, lo = INT_MAX;
    for (int x : p) { lo = min(lo, x); best = max(best, x - lo); }
    return best;
}

int maxShortProfit(const VI& p) {
    int best = 0, hi = INT_MIN;
    for (int x : p) { hi = max(hi, x); best = max(best, hi - x); }  // sell at running max, buy now
    return best;
}

VI productExceptSelf(const VI& a) {
    int n = (int)a.size();
    VI out(n, 1);
    for (int i = 1; i < n; ++i) out[i] = out[i - 1] * a[i - 1];    // prefix products
    int suffix = 1;
    for (int i = n - 1; i >= 0; --i) { out[i] *= suffix; suffix *= a[i]; }
    return out;
}

int myAtoi(const string& s) {
    size_t i = 0, n = s.size();
    while (i < n && s[i] == ' ') ++i;
    int sign = 1;
    if (i < n && (s[i] == '+' || s[i] == '-')) sign = (s[i++] == '-') ? -1 : 1;
    ll res = 0;
    while (i < n && isdigit((unsigned char)s[i])) {
        res = res * 10 + (s[i++] - '0');
        if (sign * res > INT_MAX) return INT_MAX;
        if (sign * res < INT_MIN) return INT_MIN;
    }
    return (int)(sign * res);
}

int romanToInt(const string& s) {
    auto val = [](char c) {
        switch (c) { case 'I': return 1; case 'V': return 5; case 'X': return 10; case 'L': return 50;
                     case 'C': return 100; case 'D': return 500; case 'M': return 1000; }
        return 0;
    };
    int total = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        int v = val(s[i]);
        if (i + 1 < s.size() && v < val(s[i + 1])) total -= v; else total += v;
    }
    return total;
}

string reverseWords(const string& s) {
    stringstream ss(s); string w; VS words;
    while (ss >> w) words.push_back(w);
    string out;
    for (int i = (int)words.size() - 1; i >= 0; --i) { out += words[i]; if (i) out += ' '; }
    return out;
}

VVI threeSum(VI a) {
    sort(a.begin(), a.end());
    VVI res; int n = (int)a.size();
    for (int i = 0; i < n - 2; ++i) {
        if (a[i] > 0) break;
        if (i > 0 && a[i] == a[i - 1]) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
            int s = a[i] + a[l] + a[r];
            if (s < 0) ++l;
            else if (s > 0) --r;
            else {
                res.push_back({a[i], a[l], a[r]});
                ++l; --r;
                while (l < r && a[l] == a[l - 1]) ++l;
                while (l < r && a[r] == a[r + 1]) --r;
            }
        }
    }
    return res;
}

void moveZeroes(VI& a) {
    int w = 0;
    for (int r = 0; r < (int)a.size(); ++r) if (a[r] != 0) swap(a[w++], a[r]);
}

int trap(const VI& h) {
    int l = 0, r = (int)h.size() - 1, leftMax = 0, rightMax = 0, water = 0;
    while (l < r) {
        leftMax = max(leftMax, h[l]);
        rightMax = max(rightMax, h[r]);
        if (leftMax <= rightMax) water += leftMax - h[l++];   // left side is the bottleneck
        else water += rightMax - h[r--];
    }
    return water;
}

void mergeSorted(VI& a, int m, const VI& b, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (j >= 0) a[k--] = (i >= 0 && a[i] > b[j]) ? a[i--] : b[j--];
}

int lengthOfLongestSubstring(const string& s) {
    array<int, 256> last; last.fill(-1);
    int best = 0, left = 0;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char c = s[right];
        if (last[c] >= left) left = last[c] + 1;
        last[c] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

string minWindow(const string& s, const string& t) {
    array<int, 128> need{};
    for (char c : t) ++need[(unsigned char)c];
    int missing = (int)t.size(), left = 0, bestL = 0, bestLen = INT_MAX;
    for (int right = 0; right < (int)s.size(); ++right) {
        if (need[(unsigned char)s[right]]-- > 0) --missing;
        while (missing == 0) {
            if (right - left + 1 < bestLen) { bestLen = right - left + 1; bestL = left; }
            if (++need[(unsigned char)s[left++]] > 0) ++missing;
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

VI searchRange(const VI& a, int x) {
    auto lo = lower_bound(a.begin(), a.end(), x);
    if (lo == a.end() || *lo != x) return {-1, -1};
    auto hi = upper_bound(a.begin(), a.end(), x);
    return {(int)(lo - a.begin()), (int)(hi - a.begin()) - 1};
}

int searchRotated(const VI& a, int x) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == x) return mid;
        if (a[lo] <= a[mid]) {                                  // left half sorted
            if (a[lo] <= x && x < a[mid]) hi = mid - 1; else lo = mid + 1;
        } else {                                                // right half sorted
            if (a[mid] < x && x <= a[hi]) lo = mid + 1; else hi = mid - 1;
        }
    }
    return -1;
}

int minEatingSpeed(const VI& piles, int h) {
    auto ok = [&](int k) {
        ll hours = 0;
        for (int p : piles) hours += (p + (ll)k - 1) / k;
        return hours <= h;
    };
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (ok(mid)) hi = mid; else lo = mid + 1; }
    return lo;
}

#include "../tests/day1_tests.h"
