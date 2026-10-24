# 17. Letter Combinations of a Phone Number

[Problem](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) · Medium · Backtracking → Cartesian product

LeetCode tags: hash-table, string, backtracking

Attempts since Mar 2023: 9 · accepted: 9 · failed before first AC: 0

## Attempt 1 · 2023-03-22 11:56 IST · Accepted · C++

[submission 919952195](https://leetcode.com/submissions/detail/919952195/) · tests 25/25 · runtime 4 ms (beats 1.1%)

```cpp
class Solution {
public:
    vector<string> mp;
    void dfs(int n, string path, string digits, vector<string> &ans){

        if(n<0){
            ans.push_back(path);
            return;
        }
        int num = digits[n] - '0';
        for(int i=0;i<mp[num].size();i++){
            char ch = mp[num][i];
            dfs(n-1, ch+path, digits, ans);
        }

    }
    vector<string> letterCombinations(string digits) {
        mp.resize(10);
        vector<string> ans;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";

        int n = digits.size();
        if(n==0){
            return ans;
        }
        string path ="";
        dfs(n-1, path, digits, ans);

        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 12:02 IST · Accepted · C++

[submission 919954817](https://leetcode.com/submissions/detail/919954817/) · tests 25/25 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<string> mp;
    void dfs(int n, string &path, string digits, vector<string> &ans){

        if(n<0){
            ans.push_back(path);
            return;
        }
        int num = digits[n] - '0';
        for(int i=0;i<mp[num].size();i++){
            char ch = mp[num][i];
            path = ch + path;
            dfs(n-1, path, digits, ans);
            path = path.substr(1);
        }

    }
    vector<string> letterCombinations(string digits) {
        mp.resize(10);
        vector<string> ans;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";

        int n = digits.size();
        if(n==0){
            return ans;
        }
        string path ="";
        dfs(n-1, path, digits, ans);

        return ans;
    }
};
```

## Attempt 3 · 2023-03-22 12:03 IST · Accepted · C++

[submission 919955350](https://leetcode.com/submissions/detail/919955350/) · tests 25/25 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<string> mp;
    void dfs(int n, string &path, string digits, vector<string> &ans){

        if(n<0){
            ans.push_back(path);
            return;
        }
        int num = digits[n] - '0';
        for(int i=0;i<mp[num].size();i++){
            char ch = mp[num][i];
            path = ch + path;
            dfs(n-1, path, digits, ans);
            path.erase(0,1);
        }

    }
    vector<string> letterCombinations(string digits) {
        mp.resize(10);
        vector<string> ans;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";

        int n = digits.size();
        if(n==0){
            return ans;
        }
        string path ="";
        dfs(n-1, path, digits, ans);

        return ans;
    }
};
```

## Attempt 4 · 2023-03-22 12:03 IST · Accepted · C++

[submission 919955559](https://leetcode.com/submissions/detail/919955559/) · tests 25/25 · runtime 4 ms (beats 1.1%)

```cpp
class Solution {
public:
    vector<string> mp;
    void dfs(int n, string &path, string digits, vector<string> &ans){

        if(n<0){
            ans.push_back(path);
            return;
        }
        int num = digits[n] - '0';
        for(int i=0;i<mp[num].size();i++){
            char ch = mp[num][i];
            path = ch + path;
            dfs(n-1, path, digits, ans);
            path.erase(path.begin());
        }

    }
    vector<string> letterCombinations(string digits) {
        mp.resize(10);
        vector<string> ans;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";

        int n = digits.size();
        if(n==0){
            return ans;
        }
        string path ="";
        dfs(n-1, path, digits, ans);

        return ans;
    }
};
```

## Attempt 5 · 2023-03-22 22:09 IST · Accepted · C++

[submission 920229842](https://leetcode.com/submissions/detail/920229842/) · tests 25/25 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<string> mp;
    void dfs(int n, string &path, string digits, vector<string> &ans){

        if(n<0){
            ans.push_back(path);
            return;
        }
        int num = digits[n] - '0';
        for(int i=0;i<mp[num].size();i++){
            char ch = mp[num][i];
            path = ch + path;
            dfs(n-1, path, digits, ans);
            path.erase(path.begin());
        }

    }
    vector<string> letterCombinations(string digits) {
        mp.resize(10);
        vector<string> ans;
        mp[2] = "abc";
        mp[3] = "def";
        mp[4] = "ghi";
        mp[5] = "jkl";
        mp[6] = "mno";
        mp[7] = "pqrs";
        mp[8] = "tuv";
        mp[9] = "wxyz";

        int n = digits.size();
        if(n==0){
            return ans;
        }
        string path ="";
        dfs(n-1, path, digits, ans);

        return ans;
    }
};
```

## Attempt 6 · 2023-11-16 04:40 IST · Accepted · Python

[submission 1099689974](https://leetcode.com/submissions/detail/1099689974/) · tests 25/25 · runtime 10 ms (beats 0.7%)

```python
class Solution(object):
    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        letters = {'2':'abc','3':'def','4':'ghi','5':'jkl','6':'mno','7':'pqrs','8':'tuv','9':'wxyz'}

        combinations = []
        if not digits:
            return combinations

        def backtrack(index, path):
            if len(path) == len(digits):
                combinations.append(''.join(path))
                return 
            
            possible_letters = letters[digits[index]]
            for letter in possible_letters:
                path.append(letter)
                backtrack(index + 1,path)
                path.pop()

        backtrack(0,[])
        return combinations
```

## Attempt 7 · 2023-11-29 01:51 IST · Accepted · Python3

[submission 1108418188](https://leetcode.com/submissions/detail/1108418188/) · tests 25/25 · runtime 42 ms (beats 0.1%)

```python
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) ==0:
            return []
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        
        result = []
        def backtrack(i, comb):
            nonlocal result
            if len(comb) == len(digits):
                result.append(''.join(comb))
                return

            for ch in digit_map[digits[i]]:
                comb.append(ch)
                backtrack(i+1, comb)
                comb.pop()

        backtrack(0,[])
        return result
```

## Attempt 8 · 2023-12-05 07:09 IST · Accepted · Python3

[submission 1112548089](https://leetcode.com/submissions/detail/1112548089/) · tests 25/25 · runtime 37 ms (beats 0.1%)

```python
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        '''
        backtrack solution to explore all possibilitie
        at each turn you have 4(max) choices 4^N N being digits
        and preparing substring comb O(N)

        '''
        if len(digits) ==0:
            return []
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        
        result = []
        def backtrack(i, comb):
            nonlocal result

            # success case
            if len(comb) == len(digits):
                result.append(''.join(comb))
                return

            # for each char for this index. add it to comb
            for ch in digit_map[digits[i]]:
                comb.append(ch)
                backtrack(i+1, comb)
                comb.pop()

        backtrack(0,[])
        return result
```

## Attempt 9 · 2024-01-27 10:53 IST · Accepted · Python3

[submission 1157970096](https://leetcode.com/submissions/detail/1157970096/) · tests 25/25 · runtime 28 ms (beats 0.1%)

```python
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        '''
        backtrack solution to explore all possibilitie
        at each turn you have 4(max) choices 4^N N being digits
        and preparing substring comb O(N)

        '''
        if len(digits) ==0:
            return []
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        
        result = []
        def backtrack(i, comb):
            nonlocal result

            # success case
            if len(comb) == len(digits):
                result.append(''.join(comb))
                return

            # for each char for this index. add it to comb
            for ch in digit_map[digits[i]]:
                comb.append(ch)
                backtrack(i+1, comb)
                comb.pop()

        backtrack(0,[])
        return result

class Solution1:
    def letterCombinations(self, digits: str) -> List[str]:
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        result = []
        def backtrack(idx, comb):
            # base condition 
            # reached end of string or built string
            if idx == len(digits):
                result.append(''.join(comb))
                return

            for ch in digit_map[digits[idx]]:
                comb.append(ch)
                backtrack(idx+1, comb)
                comb.pop()

        backtrack(0,[])
        return result

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        result = []
        if len(digits) ==0:
            return []

        def backtrack(indx, comb):
            # reached end of the string
            if indx == len(digits):
                result.append(''.join(comb))
                return 

            # for each choices
            # build choices at a time 
            for letter in digit_map[digits[indx]]:
                comb.append(letter)
                backtrack(indx+1, comb)
                comb.pop()

        backtrack(0, [])
        return result

    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) ==0:
            return []
        digit_map =  {"2": "abc", "3": "def", "4": "ghi", "5": "jkl", 
                   "6": "mno", "7": "pqrs", "8": "tuv", "9": "wxyz"}
        results = []
        def backtrack(indx, comb):
            if indx == len(digits):
                results.append(''.join(comb[:]))
                return 

            for ch in digit_map[digits[indx]]:
                comb.append(ch)
                backtrack(indx+1, comb)
                comb.pop()

        backtrack(0,[])
        return results
```
