# 354. Russian Doll Envelopes

[Problem](https://leetcode.com/problems/russian-doll-envelopes/) · Hard · DP: LIS Family → 2D LIS

LeetCode tags: array, binary-search, dynamic-programming, sorting, longest-increasing-subsequence

Attempts since Mar 2023: 6 · accepted: 3 · failed before first AC: 3

## Attempt 1 · 2023-03-23 17:00 IST · Compile Error · C++

[submission 920675714](https://leetcode.com/submissions/detail/920675714/)

Your output:

```text
{"compile_error": "Line 9: Char 5: error: non-void function does not return a value [-Werror,-Wreturn-type]\n    }\n    ^\n1 error generated."}
```

Compile error:

```text
Line 9: Char 5: error: non-void function does not return a value [-Werror,-Wreturn-type]
    }
    ^
1 error generated.
```

```cpp
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& arr) {
        
        sort(arr.begin(), arr.end());

        // find LIS

    }
};
```

## Attempt 2 · 2023-03-23 17:14 IST · Wrong Answer · C++

[submission 920681036](https://leetcode.com/submissions/detail/920681036/) · tests 44/87

Failing input:

```text
[[4,5],[4,6],[6,7],[2,3],[1,1]]
```

Expected:

```text
4
```

Your output:

```text
5
```

```cpp
class Solution {
public:
    static bool comp(const vector<int> &a, const vector<int> &b){
        return a[1] < b[1];
        // if(a[0] < b[0] ){
        //     return true;
        // }
        // else if(a[0] == b[0] && a[1] <b[1]){
        //     return true;
        // }
        // return false;
    }
    int maxEnvelopes(vector<vector<int>>& nums) {
        
        sort(nums.begin(), nums.end()) ;

        // find LIS
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i], comp
            );
            if(it==res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *it = nums[i];
            }
        }
        return res.size();

    }
};
```

## Attempt 3 · 2023-03-23 17:30 IST · Wrong Answer · C++

[submission 920687210](https://leetcode.com/submissions/detail/920687210/) · tests 14/87

Failing input:

```text
[[1,3],[3,5],[6,7],[6,8],[8,4],[9,5]]
```

Expected:

```text
3
```

Your output:

```text
5
```

```cpp
class Solution {
public:
    static bool comp(const vector<int> &a, const vector<int> &b){
        return a[1]<b[1];
    }
    static bool comp1(const vector<int> &a, const vector<int> &b){
        if(a[0] < b[0]) return true;
        if(a[0] == b[0] && a[1] > b[1]) return true;
        return false;
    }
    int maxEnvelopes(vector<vector<int>>& nums) {
        
        auto Cmp = [](const pair<int, int> &a, const pair<int, int> &b) { 
            if(a.first < b.first) return true;
            if(a.first == b.first && a.second > b.second) return true;
            return false;
        };
        auto Cmp2 = [](const pair<int, int> &a, const pair<int, int> &b) { 
            return a.second < b.second;
        };
        sort(nums.begin(), nums.end(),comp1) ;

        // find LIS
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
            if(it==res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *it = nums[i];
            }
        }
        return res.size();

    }
};
```

## Attempt 4 · 2023-03-23 17:43 IST · Accepted · C++

[submission 920692195](https://leetcode.com/submissions/detail/920692195/) · tests 87/87 · runtime 484 ms (beats 8.0%)

```cpp
class Solution {
public:
    static bool comp(const vector<int> &a, const vector<int> &b){
        return a[1]<b[1];
    }
    static bool comp1(const vector<int> &a, const vector<int> &b){
        if(a[0] < b[0]) return true;
        if(a[0] == b[0] && a[1] > b[1]) return true;
        return false;
    }
    int binarySearch(vector<vector<int>> &res, vector<int> x){
        if(res.size() == 0){
            return -1;
        }
        int low =0, high = res.size() -1, mid;
        int ans =-1;
        while(low <= high){
            mid = low +(high -low)/2;
            if(res[mid][0] > x[0] && res[mid][1] > x[1] ){
                high = mid -1;
            }
            else if(res[mid][0] < x[0] && res[mid][1] < x[1]){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return high;
    }
    int maxEnvelopes(vector<vector<int>>& nums) {
        
        auto Cmp = [](const pair<int, int> &a, const pair<int, int> &b) { 
            if(a.first < b.first) return true;
            if(a.first == b.first && a.second > b.second) return true;
            return false;
        };
        auto Cmp2 = [](const pair<int, int> &a, const pair<int, int> &b) { 
            return a.second < b.second;
        };
        sort(nums.begin(), nums.end(),comp1) ;

        // find LIS
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i],comp);
            if(it==res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *it = nums[i];
            }
        }
        return res.size();

    }
};
```

## Attempt 5 · 2023-03-23 18:10 IST · Accepted · C++

[submission 920702885](https://leetcode.com/submissions/detail/920702885/) · tests 87/87 · runtime 511 ms (beats 7.9%)

```cpp
class Solution {
public:
    static bool comp(const vector<int> &a, const vector<int> &b){
        if (a[1]<b[1] && a[0] <b[0])  return true;
        return a[1] < b[1];
    }
    static bool comp1(const vector<int> &a, const vector<int> &b){
        if(a[0] < b[0]) return true;
        if(a[0] == b[0] && a[1] > b[1]) return true;
        return false;
    }
    int binarySearch(vector<vector<int>> &res, vector<int> x){
        if(res.size() == 0){
            return -1;
        }
        int low =0, high = res.size() -1, mid;
        int ans =-1;
        while(low <= high){
            mid = low +(high -low)/2;
            if(res[mid][0] > x[0] && res[mid][1] > x[1] ){
                high = mid -1;
            }
            else if(res[mid][0] < x[0] && res[mid][1] < x[1]){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return high;
    }
    int maxEnvelopes(vector<vector<int>>& nums) {
        
        
        sort(nums.begin(), nums.end(),comp1) ;

        // find LIS
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i],comp);
            if(it==res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *it = nums[i];
            }
        }
        return res.size();

    }
};
```

## Attempt 6 · 2023-03-23 18:16 IST · Accepted · C++

[submission 920705425](https://leetcode.com/submissions/detail/920705425/) · tests 87/87 · runtime 456 ms (beats 8.0%)

```cpp
class Solution {
public:
    static bool comp(const vector<int> &a, const vector<int> &b){
        if (a[1]<b[1] && a[0] <b[0])  return true;
        return a[1] < b[1];
    }
    static bool comp1(const vector<int> &a, const vector<int> &b){
        if(a[0] < b[0]) return true;
        if(a[0] == b[0] && a[1] > b[1]) return true;
        return false;
    }
    int binarySearch(vector<vector<int>> &res, vector<int> x){
        if(res.size() == 0){
            return -1;
        }
        int low =0, high = res.size() -1, mid;
        int ans =-1;
        while(low <= high){
            mid = low +(high -low)/2;
            if(res[mid][0] > x[0] && res[mid][1] > x[1] ){
                high = mid -1;
            }
            else if(res[mid][0] < x[0] && res[mid][1] < x[1]){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return high;
    }
    int maxEnvelopes(vector<vector<int>>& nums) {
        
        
        sort(nums.begin(), nums.end(),comp1) ;

        // find LIS
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i],comp);
            if(it==res.end()) {
                res.push_back(nums[i]);
            }
            else {
                *it = nums[i];
            }
        }
        return res.size();

    }
};
```
