# 139. Word Break

[Problem](https://leetcode.com/problems/word-break/) · Medium · DP: 1D / Linear → Word segmentation

LeetCode tags: array, hash-table, string, dynamic-programming, trie, memoization, brute-force-search

Attempts since Mar 2023: 16 · accepted: 15 · failed before first AC: 0

## Attempt 1 · 2023-03-23 13:38 IST · Accepted · C++

[submission 920595604](https://leetcode.com/submissions/detail/920595604/) · tests 45/45 · runtime 8 ms (beats 53.6%)

```cpp
class Solution {
public:

    bool rec(int n, int w, string &s, vector<string>& words, vector<vector<int>>& dp){

        // Base cases
        if(n<0 ) return true;

        if(n>=0 && w<0){
            // s is remaining but words finished
            return 0;
        }

        // s (0-n-1) exists in Dict return true
        // if(isPresent()){

        // }

        // recurrence Relation
        // s[n] contains words[w] if suffix of string s contains this string w
        // rec(n-words[n].length, w-1) || rec(n, w-1)
        // rec
        // n, w makes words in s, 
        // n matched with word w so 2 chices
        // rec(n-len, w) || rec(n, w-1)

        // if it doesn't match
        //rec(n, w-1)

        // if(s contains )

        return false;
    }

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        WB(s, wordDict, dp);
        return dp[s];
    }
};
```

## Attempt 2 · 2023-03-23 13:40 IST · Accepted · C++

[submission 920596266](https://leetcode.com/submissions/detail/920596266/) · tests 45/45 · runtime 8 ms (beats 53.6%)

```cpp
class Solution {
public:

    bool rec(int n, int w, string &s, vector<string>& words, vector<vector<int>>& dp){

        // Base cases
        if(n<0 ) return true;

        if(n>=0 && w<0){
            // s is remaining but words finished
            return 0;
        }

        // s (0-n-1) exists in Dict return true
        // if(isPresent()){

        // }

        // recurrence Relation
        // s[n] contains words[w] if suffix of string s contains this string w
        // rec(n-words[n].length, w-1) || rec(n, w-1)
        // rec
        // n, w makes words in s, 
        // n matched with word w so 2 chices
        // rec(n-len, w) || rec(n, w-1)

        // if it doesn't match
        //rec(n, w-1)

        // if(s contains )

        return false;
    }

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        return WB(s, wordDict, dp);
        // return dp[s];
    }
};
```

## Attempt 3 · 2023-03-23 14:37 IST · Accepted · C++

[submission 920618340](https://leetcode.com/submissions/detail/920618340/) · tests 45/45 · runtime 8 ms (beats 53.6%)

```cpp
class Solution {
public:

    bool rec(int n, int w, string &s, vector<string>& words, vector<vector<int>>& dp){

        // Base cases
        if(n<0 ) return true;

        if(n>=0 && w<0){
            // s is remaining but words finished
            return 0;
        }

        // s (0-n-1) exists in Dict return true
        // if(isPresent()){

        // }

        // recurrence Relation
        // s[n] contains words[w] if suffix of string s contains this string w
        // rec(n-words[n].length, w-1) || rec(n, w-1)
        // rec
        // n, w makes words in s, 
        // n matched with word w so 2 chices
        // rec(n-len, w) || rec(n, w-1)

        // if it doesn't match
        //rec(n, w-1)

        // if(s contains )

        return false;
    }

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        return WB(s, wordDict, dp);
        // return dp[s];
    }
};
```

## Attempt 4 · 2023-05-19 19:20 IST · Accepted · C++

[submission 953369177](https://leetcode.com/submissions/detail/953369177/) · tests 46/46 · runtime 28 ms (beats 6.8%)

```cpp
class Solution {
public:

    bool rec(int n, int w, string &s, vector<string>& words, vector<vector<int>>& dp){

        // Base cases
        if(n<0 ) return true;

        if(n>=0 && w<0){
            // s is remaining but words finished
            return 0;
        }

        // s (0-n-1) exists in Dict return true
        // if(isPresent()){

        // }

        // recurrence Relation
        // s[n] contains words[w] if suffix of string s contains this string w
        // rec(n-words[n].length, w-1) || rec(n, w-1)
        // rec
        // n, w makes words in s, 
        // n matched with word w so 2 chices
        // rec(n-len, w) || rec(n, w-1)

        // if it doesn't match
        //rec(n, w-1)

        // if(s contains )

        return false;
    }

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        // return WB(s, wordDict, dp);
        // return dp[s];

        return wordBreak1(s, wordDict);
    }
    unordered_set<string> dict;

bool f(int index, string &s, vector<int> &dp){
    if(index == s.size()) return dp[s.size()] =  1;

    if(dp[index] != -1) return dp[index];

    for(int i=index; i<s.size(); i++){
        string sub = s.substr(index, i-index+1);
        if(dict.find(sub) != dict.end()){
            if(f(i+1, s, dp)){
                return dp[index] = dp[i] = 1;
            }
        }
    }
    return dp[index] = 0;
}

bool wordBreak1(string s, vector<string>& wordDict){
    vector<int> dp(s.size() +5, -1);
    for(auto w : wordDict) dict.insert(w);
    return f(0, s, dp);
}
};
```

## Attempt 5 · 2023-05-19 19:22 IST · Accepted · C++

[submission 953370129](https://leetcode.com/submissions/detail/953370129/) · tests 46/46 · runtime 24 ms (beats 9.6%)

```cpp
class Solution {
public:

    bool rec(int n, int w, string &s, vector<string>& words, vector<vector<int>>& dp){

        // Base cases
        if(n<0 ) return true;

        if(n>=0 && w<0){
            // s is remaining but words finished
            return 0;
        }

        // s (0-n-1) exists in Dict return true
        // if(isPresent()){

        // }

        // recurrence Relation
        // s[n] contains words[w] if suffix of string s contains this string w
        // rec(n-words[n].length, w-1) || rec(n, w-1)
        // rec
        // n, w makes words in s, 
        // n matched with word w so 2 chices
        // rec(n-len, w) || rec(n, w-1)

        // if it doesn't match
        //rec(n, w-1)

        // if(s contains )

        return false;
    }

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        // return WB(s, wordDict, dp);
        // return dp[s];

        return wordBreak1(s, wordDict);
    }
    unordered_set<string> dict;

bool f(int index, string &s, vector<int> &dp){
    if(index == s.size()) return dp[s.size()] =  1;

    if(dp[index] != -1) return dp[index];

    for(int i=index; i<s.size(); i++){
        string sub = s.substr(index, i-index+1);
        if(dict.find(sub) != dict.end()){
            if(f(i+1, s, dp)){
                return dp[i] = 1;
            }
        }
    }
    return dp[index] = 0;
}

bool wordBreak1(string s, vector<string>& wordDict){
    vector<int> dp(s.size() +5, -1);
    for(auto w : wordDict) dict.insert(w);
    f(0, s, dp);
    return dp[0];
}
};
```

## Attempt 6 · 2023-05-19 19:24 IST · Accepted · C++

[submission 953370759](https://leetcode.com/submissions/detail/953370759/) · tests 46/46 · runtime 28 ms (beats 6.8%)

```cpp
class Solution {
public:

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        // return WB(s, wordDict, dp);
        // return dp[s];

        return wordBreak1(s, wordDict);
    }
    
bool f(int index, string &s, vector<int> &dp, unordered_set<string>& dict){
    if(index == s.size()) return dp[s.size()] =  1;

    if(dp[index] != -1) return dp[index];

    for(int i=index; i<s.size(); i++){
        string sub = s.substr(index, i-index+1);
        if(dict.find(sub) != dict.end()){
            if(f(i+1, s, dp, dict)){
                return dp[i] = 1;
            }
        }
    }
    return dp[index] = 0;
}

bool wordBreak1(string s, vector<string>& wordDict){
    vector<int> dp(s.size() +5, -1);
    unordered_set<string> dict;
    for(auto w : wordDict) dict.insert(w);
    f(0, s, dp, dict);
    return dp[0];
}
};
```

## Attempt 7 · 2023-05-20 13:52 IST · Accepted · C++

[submission 953789290](https://leetcode.com/submissions/detail/953789290/) · tests 46/46 · runtime 28 ms (beats 6.8%)

```cpp
class Solution {
public:

    bool WB(string s, vector<string>& wordDict, map<string, bool>& dp){
        if (s.empty()) {
            // String is empty, return true 
            return true;
        }
        
        // Check if this subproblem is evaluated
        if (dp.count(s) == 1) {
            // The subproblem is already evaluated, returning previous
            // calculated solution
            return dp[s];
        }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word && WB(s.substr(word.size()), wordDict, dp)) {
                return dp[s] = true;
            }
        }
        return dp[s] = false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // vector<int> dp(s.size(), -1);
        map<string, bool> dp;
        // for(int i=0;i<dp.size();i++) cout<<dp[i]<<" ";
        // return WB(s, wordDict, dp);
        // return dp[s];

        return wordBreak1(s, wordDict);
    }
    
bool f(int index, string &s, vector<int> &dp, unordered_set<string>& dict){
    if(index == s.size()) return dp[s.size()] =  1;

    if(dp[index] != -1) return dp[index];

    for(int i=index; i<s.size(); i++){
        string sub = s.substr(index, i-index+1);
        if(dict.find(sub) != dict.end()){
            if(f(i+1, s, dp, dict)){
                return dp[i] = 1;
            }
        }
    }
    return dp[index] = 0;
}

bool wordBreak1(string s, vector<string>& wordDict){
    vector<int> dp(s.size() +5, -1);
    unordered_set<string> dict;
    for(auto w : wordDict) dict.insert(w);
    f(0, s, dp, dict);
    return dp[0];
}
};
```

## Attempt 8 · 2023-11-29 20:17 IST · Time Limit Exceeded · Python3

[submission 1108934824](https://leetcode.com/submissions/detail/1108934824/) · tests 35/46

Failing input:

```text
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
```

Expected:

```text
false
```

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        def dfs(i):
            if i>len(s)-1:
                return True

            for first in range(i+1, len(s)+1):
                if s[i:first] in wordDict:
                    #print(s[i:first])
                    if dfs(first):
                        return True

        return dfs(0)
```

## Attempt 9 · 2023-11-29 20:24 IST · Accepted · Python3

[submission 1108938735](https://leetcode.com/submissions/detail/1108938735/) · tests 46/46 · runtime 42 ms (beats 5.2%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        memo = {}
        def dfs(i):
            if i>len(s)-1:
                return True
            if i in memo:
                return memo[i]

            for first in range(i+1, len(s)+1):
                if s[i:first] in wordDict:
                    #print(s[i:first])
                    memo[first] = dfs(first)
                    if memo[first]:
                        return True
            memo[i]=False
            return memo[i]

        return dfs(0)
```

## Attempt 10 · 2024-01-02 23:33 IST · Accepted · Python3

[submission 1134878882](https://leetcode.com/submissions/detail/1134878882/) · tests 46/46 · runtime 92 ms (beats 5.2%)

```python
class Solution:
    def wordBreak1(self, s: str, wordDict: List[str]) -> bool:
        memo = {}
        def dfs(i):
            if i>len(s)-1:
                return True
            if i in memo:
                print(i)
                return memo[i]

            for first in range(i+1, len(s)+1):
                if s[i:first] in wordDict:
                    print(s[i:first])
                    memo[first] = dfs(first)
                    if memo[first]:
                        return True
            memo[i]=False
            return memo[i]

        return dfs(0)

    def wordBreak3(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        def dfs(start):
            if start >= len(s):
                return True

            for i in range(start+1, len(s)+1):
                print(s[start:i])
                if s[start: i] in words: 
                    print('found', s[start:i], 'calling for', s[i:])
                    if dfs(i):
                        return True
                
            return False
        return dfs(0)


    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        
        queue = deque([0])

        while queue:
            idx = queue.popleft()
            print('processing', idx)
            if idx >= len(s):
                return True
            for word in wordDict:
                end = idx+ len(word)
                if word == s[idx:end]:
                    print('found', 'now calling for', end)
                    queue.append(end)
        return False
                

    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of subsets = O(n^2)
        for each subset - check m choices
        substring operation - n
        n^2 * m * n + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 3  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)
```

## Attempt 11 · 2024-01-02 23:36 IST · Accepted · Python3

[submission 1134881936](https://leetcode.com/submissions/detail/1134881936/) · tests 46/46 · runtime 53 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of subsets = O(n^2)
        for each subset - check m choices
        substring operation - n
        n^2 * m * n + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 3  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)
```

## Attempt 12 · 2024-01-02 23:37 IST · Accepted · Python3

[submission 1134882352](https://leetcode.com/submissions/detail/1134882352/) · tests 46/46 · runtime 103 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of subsets = O(n^2)
        for each subset - check m choices
        substring operation - n
        n^2 * m * n + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 4  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)
```

## Attempt 13 · 2024-01-25 23:58 IST · Accepted · Python3

[submission 1156737925](https://leetcode.com/submissions/detail/1156737925/) · tests 46/46 · runtime 37 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of substrings = O(n^2)
        for each subset - check m choices
        substring operation - n
        n * m * k + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 4  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)

    # bfs solution with 
    #O(n^3) - n^2 subsets with work of n
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        # keep track of start position for substring checks
        # check all substrings starting from this position
        queue = deque([0]) 
        visited = set()

        while queue:
            start = queue.popleft()
            if start == len(s):
                return True

            for end in range(start+1, len(s) +1):
                if s[start:end] in words and end not in visited:
                    queue.append(end)
                    visited.add(end)
        return False




    
    # from collections import deque

    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        queue = deque([(0, trie)])
        visited = set([0])  # Start index is initially visited

        while queue:
            start, node = queue.popleft()

            for end in range(start, len(s)):
                if s[end] not in node:
                    break  # No further match in the trie

                node = node[s[end]]

                # If end of a word is found in the trie
                if '$' in node:
                    next_index = end + 1
                    if next_index == len(s):  # Check if we reached the end of the string
                        return True
                    if next_index not in visited:
                        queue.append((next_index, trie))  # Enqueue the next index with the root of trie
                        visited.add(next_index)  # Mark the new index as visited

        return False
```

## Attempt 14 · 2024-01-25 23:58 IST · Accepted · Python3

[submission 1156737982](https://leetcode.com/submissions/detail/1156737982/) · tests 46/46 · runtime 33 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of substrings = O(n^2)
        for each subset - check m choices
        substring operation - n
        n * m * k + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 4  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)

    # bfs solution with 
    #O(n^3) - n^2 subsets with work of n
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        # keep track of start position for substring checks
        # check all substrings starting from this position
        queue = deque([0]) 
        visited = set()

        while queue:
            start = queue.popleft()
            if start == len(s):
                return True

            for end in range(start+1, len(s) +1):
                if s[start:end] in words and end not in visited:
                    queue.append(end)
                    visited.add(end)
        return False




    
    # from collections import deque

    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        queue = deque([(0, trie)])
        visited = set([0])  # Start index is initially visited

        while queue:
            start, node = queue.popleft()

            for end in range(start, len(s)):
                if s[end] not in node:
                    break  # No further match in the trie

                node = node[s[end]]

                # If end of a word is found in the trie
                if '$' in node:
                    next_index = end + 1
                    if next_index == len(s):  # Check if we reached the end of the string
                        return True
                    if next_index not in visited:
                        queue.append((next_index, trie))  # Enqueue the next index with the root of trie
                        visited.add(next_index)  # Mark the new index as visited

        return False
```

## Attempt 15 · 2024-01-26 00:23 IST · Accepted · Python3

[submission 1156758926](https://leetcode.com/submissions/detail/1156758926/) · tests 46/46 · runtime 50 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of substrings = O(n^2)
        for each subset - check m choices
        substring operation - n
        n * m * k + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 4  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)

    # bfs solution with 
    #O(n^3) - n^2 subsets with work of n
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        # keep track of start position for substring checks
        # check all substrings starting from this position
        queue = deque([0]) 
        visited = set()

        while queue:
            start = queue.popleft()
            if start == len(s):
                return True

            for end in range(start+1, len(s) +1):
                if s[start:end] in words and end not in visited:
                    queue.append(end)
                    visited.add(end)
        return False




    
    # from collections import deque

    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        queue = deque([(0, trie)])
        visited = set([0])  # Start index is initially visited

        while queue:
            start, node = queue.popleft()

            for end in range(start, len(s)):
                if s[end] not in node:
                    break  # No further match in the trie

                node = node[s[end]]

                # If end of a word is found in the trie
                if '$' in node:
                    next_index = end + 1
                    if next_index == len(s):  # Check if we reached the end of the string
                        return True
                    if next_index not in visited:
                        queue.append((next_index, trie))  # Enqueue the next index with the root of trie
                        visited.add(next_index)  # Mark the new index as visited

        return False

    # dfs recursion
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        def can_break(start):
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in words and can_break(end):
                    return True

            return False

        return can_break(0)

    # with memoization and trie
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        memo = {}
        def can_break(start):
            if start == len(s):
                return True

            if start in memo:
                return False

            # result = False
            node = trie
            for end in range(start, len(s)):
                char = s[end]
                if char in node:
                    node = node[char]
                    if '$' in node and can_break(end+1):
                        memo[start] =True
                        return True
                else:
                    break
            memo[start] = False
            return memo[start]

            return False

        return can_break(0)
```

## Attempt 16 · 2024-02-09 19:34 IST · Accepted · Python3

[submission 1170645773](https://leetcode.com/submissions/detail/1170645773/) · tests 46/46 · runtime 38 ms (beats 5.2%)

```python
class Solution:
    # ver 1 
    # recursive solution
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        for each substring check if that subset exists in the dictionary
        if it, recursively call function with remaining string
        if not try other 

        number of recursive calls - for each position of string there 
        are m choices to be checked - for both substring call or for dfs call for remainign string
        so time complexity is 
        n^m * n + mk
        another n for substring operation
        another mk to build set from m string of average length k
        space - O(n) length of string decides depth of stack
        '''
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    return True
            return False

        return can_break(0)

    # ver 2
    ## top down dp solution
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        memoization reduces time complexity from exponential to 
        quadratic 
        number of substrings = O(n^2)
        for each subset - check m choices
        substring operation - n
        n * m * k + mk

        space - n - memoization hashmap - for each position in string s
        '''
        memo = {}  # create memoization map
        word_set = set(wordDict)
        def can_break(start):
            '''
            top down recursion for get all possible substrings
            for end in (start+1, len(s)+1)
            and when start reaches len(s) return no substrings left
            '''
            if start == len(s):
                return True

            if start in memo:
                return memo[start] # return already calcuated result

            for end in range(start+1, len(s)+1):
                if s[start:end] in word_set and can_break(end):
                    memo[start] = True # assign
                    return True
            
            memo[start] = False
            return False
        
        res =  can_break(0)
        # print(memo)
        return res

    # ver 3
    ## use BFS and visited set (to avoid calculating again)
    ## use recursion with memoization
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        you put position in the queue 
        you each substring check if it in words - 
        if then - put new position for remaingin string in the queue
        if you hve already put htis position in teh queue - next time dont process it
        which reduces the overlap calculation and keeps time complexity 
        same as above solution

        O(n^2* n+m⋅k)
        space - O(n+mk)
        '''
        queue = deque([0])
        seen = set()
        while queue:
            # queue holds the start position from which you need to check 
            # all substrings
            start = queue.popleft()

            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if end in seen:
                    continue
                if s[start:end] in words:
                    queue.append(end)
                    seen.add(end)

        return False

    # ver 4  - handle large word dictionary
    # you check each substring with all the words in the dictionary 
    # though lookup is O(1) you still check all m options
    # use trie to do lookup - it can reduce the lookup from m to k the average length of string instead of number of strings
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        '''
        build trie from wordDict
        use trie for substring lookups

        time complexity 
        you still have same subsets O(n^2)
        but instead of checking all m words each time, you can easily match the fix 
        of any word using trie making it O(n^2) instead of O(n^2 *m)

        still it takes O(mk) to build trie
        O(n^2 + mk)

        trie storage + memoization + call stack = O(mk + n + n)
        '''
        trie = {} # end of word - $
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True

        print(trie)
        memo = {}

        def can_break(start, node):
            if start == len(s):
                return True
            
            if start in memo:
                return memo[start]

            temp_node = node
            for end in range(start, len(s)):
                # for each character
                char = s[end]

                # check in trie
                if char in temp_node:
                    temp_node = temp_node[char]
                    if '$' in temp_node and can_break(end+1, trie):
                        memo[start] =True
                        return True
                else:
                    break

            memo[start] = False
            return False

        return can_break(0, trie)

    # bfs solution with 
    #O(n^3) - n^2 subsets with work of n
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        # keep track of start position for substring checks
        # check all substrings starting from this position
        queue = deque([0]) 
        visited = set()

        while queue:
            start = queue.popleft()
            if start == len(s):
                return True

            for end in range(start+1, len(s) +1):
                if s[start:end] in words and end not in visited:
                    queue.append(end)
                    visited.add(end)
        return False




    
    # from collections import deque
    # n^2 
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        queue = deque([(0, trie)])
        visited = set([0])  # Start index is initially visited

        while queue:
            start, node = queue.popleft()

            for end in range(start, len(s)):
                if s[end] not in node:
                    break  # No further match in the trie

                node = node[s[end]]

                # If end of a word is found in the trie
                if '$' in node:
                    next_index = end + 1
                    if next_index == len(s):  # Check if we reached the end of the string
                        return True
                    if next_index not in visited:
                        queue.append((next_index, trie))  # Enqueue the next index with the root of trie
                        visited.add(next_index)  # Mark the new index as visited

        return False

    # dfs recursion
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        def can_break(start):
            if start == len(s):
                return True

            for end in range(start+1, len(s)+1):
                if s[start:end] in words and can_break(end):
                    return True

            return False

        return can_break(0)

    # with memoization and trie
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True  # Mark end of word

        memo = {}
        def can_break(start):
            if start == len(s):
                return True

            if start in memo:
                return memo[start]

            # result = False
            # because reuse words, start checking from start node
            node = trie
            for end in range(start, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]

                if '$' in node and can_break(end+1):
                    memo[start] =True
                    return True

            memo[start] = False
            return memo[start]

            return False

        return can_break(0)
```
