# 60. Permutation Sequence

[Problem](https://leetcode.com/problems/permutation-sequence/) · Hard · Math & Bit Manipulation → Factorial number system

LeetCode tags: math, recursion

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 3

## Attempt 1 · 2023-04-28 15:34 IST · Time Limit Exceeded · C++

[submission 941038951](https://leetcode.com/submissions/detail/941038951/) · tests 109/200

Failing input:

```text
9
62716
```

Expected:

```text
"265183794"
```

```cpp
class Solution {
    vector<string> ans;
    void rec(int idx, string &perm){
        if(idx == perm.size()){
            ans.push_back(perm);
            return;
        }

        for(int i=idx;i<perm.size();i++){
            swap(perm[idx], perm[i]);
            rec(idx+1, perm);
            swap(perm[idx], perm[i]);

        }
    }
public:
    string getPermutation(int n, int k) {
        string perm="";

        for(int i=1;i<=n;i++){
            perm += to_string(i);
        }
        rec(0, perm);
        sort(ans.begin(), ans.end());

        return ans[k-1];
    }
};
```

## Attempt 2 · 2023-04-28 15:34 IST · Time Limit Exceeded · C++

[submission 941039153](https://leetcode.com/submissions/detail/941039153/) · tests 109/200

Failing input:

```text
9
62716
```

Expected:

```text
"265183794"
```

```cpp
class Solution {
    vector<string> ans;
    void rec(int idx, string &perm){
        if(idx == perm.size()){
            ans.push_back(perm);
            return;
        }

        for(int i=idx;i<perm.size();i++){
            swap(perm[idx], perm[i]);
            rec(idx+1, perm);
            swap(perm[idx], perm[i]);
        }
    }
public:
    string getPermutation(int n, int k) {
        string perm="";

        for(int i=1;i<=n;i++){
            perm += to_string(i);
        }
        rec(0, perm);
        sort(ans.begin(), ans.end());

        return ans[k-1];
    }
};
```

## Attempt 3 · 2023-04-28 15:48 IST · Compile Error · C++

[submission 941043418](https://leetcode.com/submissions/detail/941043418/)

Your output:

```text
{"compile_error": "Line 21: Char 13: error: use of undeclared identifier 'perm'\n            perm += to_string(i);\n            ^"}
```

Compile error:

```text
Line 21: Char 13: error: use of undeclared identifier 'perm'
            perm += to_string(i);
            ^
```

```cpp
class Solution {
    vector<string> ans;
    // TC : O(n! *n)
    void rec(int idx, string &perm){
        if(idx == perm.size()){
            ans.push_back(perm);
            return;
        }

        for(int i=idx;i<perm.size();i++){
            swap(perm[idx], perm[i]);
            rec(idx+1, perm);
            swap(perm[idx], perm[i]);
        }
    }
public:
    string getPermutation(int n, int k) {
        // string perm="";
        long long fact = 1;
        for(int i=1;i<=n;i++){
            perm += to_string(i);
            fact *= i;
        }
        k--; // we are finding in 0 based indexing
        string res = "";
        while(true){
            res += perm[k/fact];
            perm.erase(perm.begin() + k/fact);
            if(perm.size() == 0){
                break;
            }
            k = k%fact;
            fact = fact/perm.size();
        }

        return res;

        // TC: O(n!*n)
        // rec(0, perm);
        // sort(ans.begin(), ans.end());

        // return ans[k-1];
    }
};
```

## Attempt 4 · 2023-04-28 15:54 IST · Accepted · C++

[submission 941045258](https://leetcode.com/submissions/detail/941045258/) · tests 200/200 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    vector<string> ans;
    // TC : O(n! *n)
    void rec(int idx, string &perm){
        if(idx == perm.size()){
            ans.push_back(perm);
            return;
        }

        for(int i=idx;i<perm.size();i++){
            swap(perm[idx], perm[i]);
            rec(idx+1, perm);
            swap(perm[idx], perm[i]);
        }
    }
public:
    string getPermutation(int n, int k) {
        // string perm="";
        vector<int> perm;
        long long fact = 1;
        for(int i=1;i<n;i++){
            // perm += to_string(i);
            perm.push_back(i);
            fact *= i;
        }
        perm.push_back(n);
        k--; // we are finding in 0 based indexing
        string res = "";
        while(true){
            res += to_string(perm[k/fact]);
            perm.erase(perm.begin() + k/fact);
            if(perm.size() == 0){
                break;
            }
            k = k%fact;
            fact = fact/perm.size();
        }

        return res;

        // TC: O(n!*n)
        // rec(0, perm);
        // sort(ans.begin(), ans.end());

        // return ans[k-1];
    }
};
```
