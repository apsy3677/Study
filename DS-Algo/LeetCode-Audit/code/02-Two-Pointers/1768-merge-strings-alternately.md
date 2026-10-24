# 1768. Merge Strings Alternately

[Problem](https://leetcode.com/problems/merge-strings-alternately/) · Easy · Two Pointers → Interleave

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-08-17 23:52 IST · Accepted · C++

[submission 1024218483](https://leetcode.com/submissions/detail/1024218483/) · tests 108/108 · runtime 4 ms (beats 30.1%)

```cpp
class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int flag=0;
        int n=word1.length(), i=0;
        int m=word2.length(), j=0;
        string result = "";
        while(i<n && j<m) {
            if(flag%2 == 0) {
                result = result + word1[i];
                i++;
            } else {
                result = result + word2[j];
                j++;
            }
            flag = flag^1;
        }
        while(i<n) {
            result = result + word1[i];
                i++;
        }
        while(j<m) {
            result = result + word2[j];
                j++;
        }
        return result;
    }
};
```
