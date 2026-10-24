# 2381. Shifting Letters II

[Problem](https://leetcode.com/problems/shifting-letters-ii/) · Medium · Prefix Sum & Difference Array → Difference array

LeetCode tags: array, string, prefix-sum

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2025-04-16 21:35 IST · Wrong Answer · C++

[submission 1608687673](https://leetcode.com/submissions/detail/1608687673/) · tests 9/39

Failing input:

```text
"xuwdbdqik"
[[4,8,0],[4,4,0],[2,4,0],[2,4,0],[6,7,1],[2,2,1],[0,2,1],[8,8,0],[1,3,1]]
```

Expected:

```text
"ywxcxcqii"
```

Your output:

```text
"ywxc^cqii"
```

```cpp
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        map <int, int> active;

        for(auto shift : shifts) {
            int l = shift[0];
            int r = shift[1];
            int d = shift[2];

            active[l] += d==1 ? 1 : -1 ;
            active[r+1] += d==1 ? -1 : 1 ;
        }
        int l = 0, curr = 0;
        bool flag = true;
        for (auto &[x, count] : active) {
            // shift chars from 
            if (flag) {
                l = x; // first index;
                flag = false;
            } else {
                // l to x-1 
                for (int i= l ; i<x ; i++) {
                    int shift = curr;
                    s[i] = 'a' + (s[i] - 'a' + shift)%26;
                }
                l = x ;
            }
            
            curr += count; // no of times char needs to be shifted
        }
        if (l <= s.size()-1) {
            for (int i= l ; i < s.size();i++) {
                int shift = curr;
                s[i] = 'a' + (s[i] - 'a' + shift)%26;
            }
        }

        return s;
    }
};
```

## Attempt 2 · 2025-04-16 21:39 IST · Accepted · C++

[submission 1608691058](https://leetcode.com/submissions/detail/1608691058/) · tests 39/39 · runtime 144 ms (beats 5.0%)

```cpp
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        map <int, int> active;

        for(auto shift : shifts) {
            int l = shift[0];
            int r = shift[1];
            int d = shift[2];

            active[l] += d==1 ? 1 : -1 ;
            active[r+1] += d==1 ? -1 : 1 ;
        }
        int l = 0, curr = 0;
        bool flag = true;
        for (auto &[x, count] : active) {
            // shift chars from 
            if (flag) {
                l = x; // first index;
                flag = false;
            } else {
                // l to x-1 
                for (int i= l ; i<x ; i++) {
                    int shift = curr;
                    s[i] = 'a' + ((s[i] - 'a' + shift) % 26 + 26) % 26; // Fix for negative shifts
                }
                l = x ;
            }
            
            curr += count; // no of times char needs to be shifted
        }
        if (l <= s.size()-1) {
            for (int i= l ; i < s.size();i++) {
                int shift = curr;
                s[i] = 'a' + ((s[i] - 'a' + shift) % 26 + 26) % 26; // Fix for negative shifts
            }
        }

        return s;
    }
};
```

## Attempt 3 · 2025-04-16 21:44 IST · Accepted · C++

[submission 1608696090](https://leetcode.com/submissions/detail/1608696090/) · tests 39/39 · runtime 146 ms (beats 5.0%)

```cpp
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        map <int, int> active;

        for(auto shift : shifts) {
            int l = shift[0];
            int r = shift[1];
            int d = shift[2];

            active[l] += d==1 ? 1 : -1 ;
            active[r+1] += d==1 ? -1 : 1 ;
        }

        int currShift = 0; // Tracks the cumulative shift
        int prevIndex = 0; // Tracks the start of the current range

        // Apply shifts to the string
        for (const auto &[index, shiftChange] : active) {
            // Apply the cumulative shift to the range [prevIndex, index - 1]
            for (int i = prevIndex; i < index; i++) {
                s[i] = 'a' + ((s[i] - 'a' + currShift) % 26 + 26) % 26; // Handle negative shifts
            }

            // Update the cumulative shift and move to the next range
            currShift += shiftChange;
            prevIndex = index;
        }

        // Apply the remaining shift to the rest of the string
        for (int i = prevIndex; i < s.size(); i++) {
            s[i] = 'a' + ((s[i] - 'a' + currShift) % 26 + 26) % 26; // Handle negative shifts
        }

        return s;
    }
};
```
