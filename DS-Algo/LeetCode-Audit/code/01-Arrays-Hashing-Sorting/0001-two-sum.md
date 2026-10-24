# 1. Two Sum

[Problem](https://leetcode.com/problems/two-sum/) · Easy · Arrays, Hashing & Sorting → Complement map

LeetCode tags: array, hash-table

Attempts since Mar 2023: 7 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-03-06 21:52 IST · Accepted · C++

[submission 910266383](https://leetcode.com/submissions/detail/910266383/) · tests 57/57 · runtime 9 ms (beats 40.6%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        vector<int> ans(2);
        map<int,int> mp;
        for(int i=0;i< nums.size();i++){
            if(mp.find(target - nums[i]) != mp.end()){
                ans[0] = i;
                ans[1] = mp[target - nums[i]];
                return ans;
            }
            mp[nums[i]] =i;
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-06 21:55 IST · Accepted · C++

[submission 910268202](https://leetcode.com/submissions/detail/910268202/) · tests 57/57 · runtime 14 ms (beats 39.3%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        vector<int> ans(2);
        map<int,int> mp;
        for(int i=0;i< nums.size();i++){
            if(mp.find(target - nums[i]) != mp.end()){
                ans[0] = i;
                ans[1] = mp[target - nums[i]];
                return ans;
            }
            mp[nums[i]] =i;
        }
        return vector<int>();
    }
};
```

## Attempt 3 · 2023-03-07 00:37 IST · Accepted · C++

[submission 910366686](https://leetcode.com/submissions/detail/910366686/) · tests 57/57 · runtime 18 ms (beats 39.2%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        vector<int> ans(2);
        map<int,int> mp;
        for(int i=0;i< nums.size();i++){
            if(mp.find(target - nums[i]) != mp.end()){
                ans[0] = i;
                ans[1] = mp[target - nums[i]];
                return ans;
            }
            mp[nums[i]] =i;
        }
        return vector<int>();
    }
};
```

## Attempt 4 · 2023-03-22 21:06 IST · Accepted · C++

[submission 920196208](https://leetcode.com/submissions/detail/920196208/) · tests 57/57 · runtime 15 ms (beats 39.3%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        map<int,int> mp;
        for(int i=0;i< nums.size();i++){
            if(mp.find(target - nums[i]) != mp.end()){
                ans[0] = i;
                ans[1] = mp[target - nums[i]];
                return ans;
            }
            mp[nums[i]] =i;
        }
        return vector<int>();
    }
};
```

## Attempt 5 · 2023-05-19 11:38 IST · Accepted · C++

[submission 953164303](https://leetcode.com/submissions/detail/953164303/) · tests 57/57 · runtime 10 ms (beats 40.3%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        unordered_map<int, int> exist;
        int i=0;
        for(auto x : nums){
            int req = target - x;
            if(exist.find(req) != exist.end()){
                return {exist[req], i};
            }
            exist[x] = i;
            i++;
        }
        return {};
    }
};
```

## Attempt 6 · 2023-05-20 13:46 IST · Accepted · C++

[submission 953787124](https://leetcode.com/submissions/detail/953787124/) · tests 57/57 · runtime 13 ms (beats 39.4%)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        unordered_map<int, int> exist;
        int i=0;
        for(auto x : nums){
            int req = target - x;
            if(exist.find(req) != exist.end()){
                return {exist[req], i};
            }
            exist[x] = i;
            i++;
        }
        return {};
    }
};
```

## Attempt 7 · 2023-10-19 20:36 IST · Accepted · C++

[submission 1079247546](https://leetcode.com/submissions/detail/1079247546/) · tests 60/60 · runtime 14 ms (beats 39.3%)

```cpp
class Solution {
private:

    static bool compareValue(pair<int, int> x, pair<int, int> y) {
        return x.first < y.first;
    } 

public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int,int>> x;
        for (int i=0;i< nums.size(); i++) {
            x.push_back({nums[i], i});
        }

        sort(x.begin(), x.end(), compareValue);
        int i=0, j=nums.size()-1;
        vector<int> ans;
        while(i<j) {
            if(target == x[i].first + x[j].first) {
                ans.push_back(x[i].second);
                ans.push_back(x[j].second);
                return ans;
            } else if (target > x[i].first + x[j].first) {
                i++;
            } else {
                j--;
            }
        }
        return ans;
    }
};
```
