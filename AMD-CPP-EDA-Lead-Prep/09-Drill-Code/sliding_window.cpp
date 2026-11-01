#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Sliding window, one template, two flavours.
//   for r: add s[r]  ->  LONGEST: while BAD shrink, then record   |   SHORTEST: while GOOD record, then shrink
// Works only when "bad" is monotonic: a bad window stays bad if you grow it (true for repeats, false for sums with negatives).

// LC 3, template version (LONGEST): bad = s[r] now appears twice
int lengthOfLongestSubstring(string s) {
    int cnt[128] = {}, l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        cnt[s[r]]++;                               // 1. head eats s[r]
        while (cnt[s[r]] > 1) cnt[s[l++]]--;       // 2. bad -> tail catches up
        best = max(best, r - l + 1);               // 3. window valid -> record
    }
    return best;
}

// LC 3, jump version: l leaps past the previous copy, but only forward (max) -> "abba"
int lengthOfLongestSubstringJump(string s) {
    vector<int> last(128, -1);
    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        l = max(l, last[s[r]] + 1);                // stale copy outside the window must not pull l back
        last[s[r]] = r;
        best = max(best, r - l + 1);
    }
    return best;
}

// LC 76, template version (SHORTEST): good = nothing from t is missing
string minWindow(string s, string t) {
    int need[128] = {}, missing = t.size(), l = 0, bestL = 0, bestLen = INT_MAX;
    for (char c : t) need[c]++;
    for (int r = 0; r < (int)s.size(); r++) {
        if (need[s[r]]-- > 0) missing--;           // 1. add; negative need = surplus copy
        while (missing == 0) {                     // 2. good -> record, then shrink
            if (r - l + 1 < bestLen) { bestLen = r - l + 1; bestL = l; }
            if (++need[s[l++]] > 0) missing++;     //    dropping s[l] makes us need it again
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

// LC 76, "formed" version (LeetCode's official one): count DISTINCT letters that are complete
// need = the recipe, win = my basket, formed = recipe lines ticked off, required = lines on the recipe
string minWindowFormed(string s, string t) {
    int need[128] = {}, win[128] = {}, required = 0, formed = 0, l = 0, bestL = 0, bestLen = INT_MAX;
    for (char c : t) if (need[c]++ == 0) required++;                        // distinct letters in t
    for (int r = 0; r < (int)s.size(); r++) {
        char c = s[r];
        if (need[c] > 0 && ++win[c] == need[c]) formed++;                    // this letter JUST became complete
        while (formed == required) {
            if (r - l + 1 < bestLen) { bestLen = r - l + 1; bestL = l; }
            char d = s[l++];
            if (need[d] > 0 && win[d]-- == need[d]) formed--;                // it WAS exactly complete -> now short
        }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
}

int main() {
    for (string s : {"abcabcbb", "pwwkew", "abba", "", " ", "bbbbb"})
        cout << '"' << s << "\" -> " << lengthOfLongestSubstring(s) << ' ' << lengthOfLongestSubstringJump(s) << '\n';
    cout << minWindow("ADOBECODEBANC", "ABC") << " | " << minWindow("a", "aa") << "(empty) | " << minWindow("a", "a") << '\n';
    cout << minWindowFormed("ADOBECODEBANC", "ABC") << " | " << minWindowFormed("a", "aa") << "(empty) | "
         << minWindowFormed("a", "a") << " | " << minWindowFormed("AAB", "AB") << " | " << minWindowFormed("XAAYB", "AAB") << '\n';
}
