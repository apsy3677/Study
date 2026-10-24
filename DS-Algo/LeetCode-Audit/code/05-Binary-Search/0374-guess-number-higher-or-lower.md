# 374. Guess Number Higher or Lower

[Problem](https://leetcode.com/problems/guess-number-higher-or-lower/) · Easy · Binary Search → Classic search

LeetCode tags: binary-search, interactive

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-24 12:58 IST · Accepted · C++

[submission 1212385330](https://leetcode.com/submissions/detail/1212385330/) · tests 25/25 · runtime 0 ms (beats 100%)

```cpp
/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        int num = 1;
        while(left <= right) {
            int picked = left + (right-left)/2;
            num = picked;
            int ret = guess(picked);
            if(ret == 0 ) return picked;
            else if (ret == 1) left = picked +1;
            else if (ret == -1) right = picked -1;
        }
        return num;
    }
};
```
