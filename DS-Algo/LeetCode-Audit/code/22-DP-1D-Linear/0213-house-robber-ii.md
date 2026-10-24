# 213. House Robber II

[Problem](https://leetcode.com/problems/house-robber-ii/) · Medium · DP: 1D / Linear → Take/skip, circular

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-03-11 17:02 IST · Wrong Answer · C++

[submission 913184731](https://leetcode.com/submissions/detail/913184731/) · tests 68/75

Failing input:

```text
[1]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:

    int adjSum(vector<int>&arr ){
        int prev2 = 0;
        int prev1 = 0;
        int n= arr.size();
        if(n >=1){prev2 = arr[0];}
        if(n >=2){prev1 = max(arr[0],arr[1]);}
        for(int i=2;i<arr.size();i++){
            int curr = max(prev1, max(prev2 + arr[i], arr[i]));
            prev2= prev1;
            prev1 = curr;
        }
        return prev1;
    }

    int rob(vector<int>& arr) {
        vector<int> v = vector<int> (arr.begin(), arr.end()-1);
        int ans1 = adjSum(v);
        v = vector<int> (arr.begin()+1, arr.end());
        int ans2 = adjSum(v);
        return max(ans1, ans2);
    }
};
```

## Attempt 2 · 2023-03-11 17:03 IST · Wrong Answer · C++

[submission 913185027](https://leetcode.com/submissions/detail/913185027/) · tests 73/75

Failing input:

```text
[1]
```

Expected:

```text
1
```

Your output:

```text
0
```

```cpp
class Solution {
public:

    int adjSum(vector<int>&arr ){
        int prev2 = 0;
        int prev1 = 0;
        int n= arr.size();
        if(n >=1){prev2 = arr[0];prev1 = arr[0];}
        if(n >=2){prev1 = max(arr[0],arr[1]);}
        for(int i=2;i<arr.size();i++){
            int curr = max(prev1, max(prev2 + arr[i], arr[i]));
            prev2= prev1;
            prev1 = curr;
        }
        return prev1;
    }

    int rob(vector<int>& arr) {
        vector<int> v = vector<int> (arr.begin(), arr.end()-1);
        int ans1 = adjSum(v);
        v = vector<int> (arr.begin()+1, arr.end());
        int ans2 = adjSum(v);
        return max(ans1, ans2);
    }
};
```

## Attempt 3 · 2023-03-11 17:05 IST · Accepted · C++

[submission 913185817](https://leetcode.com/submissions/detail/913185817/) · tests 75/75 · runtime 3 ms (beats 6.5%)

```cpp
class Solution {
public:

    int adjSum(vector<int>&arr ){
        int prev2 = 0;
        int prev1 = 0;
        int n= arr.size();
        if(n >=1){prev2 = arr[0];prev1 = arr[0];}
        if(n >=2){prev1 = max(arr[0],arr[1]);}
        for(int i=2;i<arr.size();i++){
            int curr = max(prev1, max(prev2 + arr[i], arr[i]));
            prev2= prev1;
            prev1 = curr;
        }
        return prev1;
    }

    int rob(vector<int>& arr) {
        if(arr.size() ==1){
            return arr[0];
        }
        vector<int> v = vector<int> (arr.begin(), arr.end()-1);
        int ans1 = adjSum(v);
        v = vector<int> (arr.begin()+1, arr.end());
        int ans2 = adjSum(v);
        return max(ans1, ans2);
    }
};
```
