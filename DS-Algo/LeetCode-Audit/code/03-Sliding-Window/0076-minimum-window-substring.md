# 76. Minimum Window Substring

[Problem](https://leetcode.com/problems/minimum-window-substring/) · Hard · Sliding Window → Variable window, min cover

LeetCode tags: hash-table, string, sliding-window

Attempts since Mar 2023: 19 · accepted: 11 · failed before first AC: 3

## Attempt 1 · 2023-03-21 11:58 IST · Time Limit Exceeded · C++

[submission 919296391](https://leetcode.com/submissions/detail/919296391/) · tests 266/267

Failing input:

```text
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ... [47030 more chars]
```

Expected:

```text
"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
```

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";
        for(;right<n;right++){
            char ch = s[right];
            s_map[ch]++;
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 2 · 2023-03-21 12:17 IST · Wrong Answer · C++

[submission 919305715](https://leetcode.com/submissions/detail/919305715/) · tests 87/267

Failing input:

```text
"ADOBECODEBANC"
"ABC"
```

Expected:

```text
"BANC"
```

Your output:

```text
"C"
```

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        // for(;right<n;right++){
        //     char ch = s[right];

        //     if(t_map.find(ch) != t_map.end()){
        //         s_map[ch]++;
        //         if(s_map[ch] <= t_map[ch]){
        //             countChar++;
        //         }
        //     }
        // }


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 3 · 2023-03-21 12:17 IST · Time Limit Exceeded · C++

[submission 919306129](https://leetcode.com/submissions/detail/919306129/) · tests 266/267

Failing input:

```text
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ... [47030 more chars]
```

Expected:

```text
"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"
```

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        // for(;right<n;right++){
        //     char ch = s[right];

        //     if(t_map.find(ch) != t_map.end()){
        //         s_map[ch]++;
        //         if(s_map[ch] <= t_map[ch]){
        //             countChar++;
        //         }
        //     }
        // }


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            // s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 4 · 2023-03-21 12:21 IST · Accepted · C++

[submission 919307944](https://leetcode.com/submissions/detail/919307944/) · tests 267/267 · runtime 55 ms (beats 11.7%)

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        for(;right<n;right++){
            char ch = s[right];

            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }

            if(countChar >= m){

                while(t_map.find(s[left]) == t_map.end() || s_map[s[left]] > t_map[s[left]]){
                    s_map[s[left]]--;
                    left++;
                }

                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
            }
        }
        return mwSub;


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            // s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 5 · 2023-03-21 12:25 IST · Accepted · C++

[submission 919309991](https://leetcode.com/submissions/detail/919309991/) · tests 267/267 · runtime 58 ms (beats 11.6%)

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        for(;right<n;right++){
            char ch = s[right];

            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }

            if(countChar == m){

                while(t_map.find(s[left]) == t_map.end() || s_map[s[left]] > t_map[s[left]]){
                    s_map[s[left]]--;
                    left++;
                }

                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
            }
        }
        return mwSub;


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            // s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 6 · 2023-03-22 21:06 IST · Accepted · C++

[submission 920196602](https://leetcode.com/submissions/detail/920196602/) · tests 267/267 · runtime 59 ms (beats 11.6%)

```cpp
class Solution {
public:

    bool contains(map<char,int> &s_map, map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        for(;right<n;right++){
            char ch = s[right];

            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }

            if(countChar == m){

                while(t_map.find(s[left]) == t_map.end() || s_map[s[left]] > t_map[s[left]]){
                    s_map[s[left]]--;
                    left++;
                }

                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
            }
        }
        return mwSub;


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            // s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 7 · 2023-05-08 08:38 IST · Accepted · C++

[submission 946373397](https://leetcode.com/submissions/detail/946373397/) · tests 267/267 · runtime 50 ms (beats 11.9%)

```cpp
class Solution {
public:

    bool contains(unordered_map<char,int> &s_map, unordered_map<char,int> &t_map){
        for(auto x : t_map){
            char ch = x.first;
            int count = x.second;

            if(s_map.find(ch) == s_map.end()){
                return false;
            }
            if(s_map[ch] < count){
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size(), m = t.size();
        unordered_map<char,int> t_map, s_map;

        if(m>n){
            return "";
        }
        for(int i=0;i<m;i++){
            t_map[t[i]]++;
        }

        int left =0, right=0;
        int ans = INT_MAX;
        string mwSub = "";

        int countChar =0;

        for(;right<n;right++){
            char ch = s[right];

            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }

            if(countChar == m){

                while(t_map.find(s[left]) == t_map.end() || s_map[s[left]] > t_map[s[left]]){
                    s_map[s[left]]--;
                    left++;
                }

                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
            }
        }
        return mwSub;


        // 2nd Solution
        right = left = 0;
        for(;right<n;right++){
            char ch = s[right];
            // s_map[ch]++;
            if(t_map.find(ch) != t_map.end()){
                s_map[ch]++;
                if(s_map[ch] <= t_map[ch]){
                    countChar++;
                }
            }
            // if(contains(s_map, t_map)){
            //     if(right -left +1 < ans){
            //         mwSub = s.substr(left, right-left+1);
            //         ans = right -left +1;
            //     }
            // }
            while(left <= right && contains(s_map, t_map)){
                if(right -left +1 < ans){
                    mwSub = s.substr(left, right-left+1);
                    ans = right -left +1;
                }
                char lc = s[left];

                s_map[lc]--;
                left++;
            }
        }

        return mwSub;
    }
};
```

## Attempt 8 · 2023-11-18 20:07 IST · Time Limit Exceeded · Python3

[submission 1101446851](https://leetcode.com/submissions/detail/1101446851/) · tests 265/267

Failing input:

```text
"kgfidhktkjhlkbgjkylgdracfzjduycghkomrbfbkoowqwgaurizliesjnveoxmvjdjaepdqftmvsuyoogobrutahogxnvuxyezevfuaaiyufwjtezuxtpycfgasburzytdvazwakuxpsiiyhewctwgycgsgdkhdfnzfmvhwrellmvjvzfzsdgqgolorxvxciwjxtqvmxhxlcijeqiytqrzfcpyzlvbvrksmcoybxxpbgyfwgepzvrezgcytabptnjgpxgtweiykgfiolxniqthzwfswihpvtxlseepkopwuueiidyquratphnnqxflqcyiiezssoomlsxtyxlsolngtctjzywrbvajbzeuqsiblhwlehfvtubmwuxyvvpwsrhutlojgwktegek ... [109605 more chars]
```

Expected:

```text
"sehoeyslmrsxseyxdkpnanapjjfophmhnwxswpdijxhbbiyhspwudwlofsewztdprchnsmxbkhenpcujuqdxoqntjspkluzcxirrvouhvyukcptwhytwpjrybjiofksesjvnzpuvnrhqidmpbinsrhsusbixlccflztmppjegruoujgxrvqkckgulquysyefxzrmqbrxunnqwtnprfbtqhqdxmerkkwjloybrraleobdjquayywqfovfazymlvvwlvacmaptoswaksciqyyymwfmvdajywflrfpggezwyvyjpbrgzsgoolclodupzcasjqyruxovuoempvurpahfljtbmpqnrtibjgsfgiaczeqqckjtkqzxauzojrcdkkgtsabajbfkivakikf ... [10344 more chars]
```

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        char_count = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                char_count[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(char_count[ch] >= required_count[ch] for ch in t):             
                # print('here', r-l)
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                char_count[s[l]] -=1
                l +=1
                print(char_count, required_count)
            r+=1
        return result
```

## Attempt 9 · 2023-11-18 20:17 IST · Accepted · Python3

[submission 1101451534](https://leetcode.com/submissions/detail/1101451534/) · tests 267/267 · runtime 155 ms (beats 19.9%)

```python
class Solution:
    def minWindow1(self, s: str, t: str) -> str:
        

        l, r = 0,0
        char_count = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                char_count[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(char_count[ch] >= required_count[ch] for ch in t):             
                # print('here', r-l)
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                char_count[s[l]] -=1
                l +=1
                print(char_count, required_count)
            r+=1
        return result


    def minWindow(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString
```

## Attempt 10 · 2023-11-29 09:14 IST · Runtime Error · Python3

[submission 1108604004](https://leetcode.com/submissions/detail/1108604004/) · tests 0/267

Failing input:

```text
"ADOBECODEBANC"
"ABC"
```

Expected:

```text
"BANC"
```

Runtime error:

```text
SyntaxError: invalid syntax
    ^^^
    and window_count[s[l]] == required_count[s[l]]:
Line 85  (Solution.py)
```

```python
class Solution:
    def minWindow1(self, s: str, t: str) -> str:
        

        l, r = 0,0
        char_count = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                char_count[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(char_count[ch] >= required_count[ch] for ch in t):             
                # print('here', r-l)
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                char_count[s[l]] -=1
                l +=1
                print(char_count, required_count)
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                     and window_count[s[l]] == required_count[s[l]]:
                    formed -=1
                    window_count[s[l]] -=1
                l+=1

            r+=1
        return result
```

## Attempt 11 · 2023-12-03 22:57 IST · Time Limit Exceeded · Python3

[submission 1111621511](https://leetcode.com/submissions/detail/1111621511/) · tests 265/267

Failing input:

```text
"kgfidhktkjhlkbgjkylgdracfzjduycghkomrbfbkoowqwgaurizliesjnveoxmvjdjaepdqftmvsuyoogobrutahogxnvuxyezevfuaaiyufwjtezuxtpycfgasburzytdvazwakuxpsiiyhewctwgycgsgdkhdfnzfmvhwrellmvjvzfzsdgqgolorxvxciwjxtqvmxhxlcijeqiytqrzfcpyzlvbvrksmcoybxxpbgyfwgepzvrezgcytabptnjgpxgtweiykgfiolxniqthzwfswihpvtxlseepkopwuueiidyquratphnnqxflqcyiiezssoomlsxtyxlsolngtctjzywrbvajbzeuqsiblhwlehfvtubmwuxyvvpwsrhutlojgwktegek ... [109605 more chars]
```

Expected:

```text
"sehoeyslmrsxseyxdkpnanapjjfophmhnwxswpdijxhbbiyhspwudwlofsewztdprchnsmxbkhenpcujuqdxoqntjspkluzcxirrvouhvyukcptwhytwpjrybjiofksesjvnzpuvnrhqidmpbinsrhsusbixlccflztmppjegruoujgxrvqkckgulquysyefxzrmqbrxunnqwtnprfbtqhqdxmerkkwjloybrraleobdjquayywqfovfazymlvvwlvacmaptoswaksciqyyymwfmvdajywflrfpggezwyvyjpbrgzsgoolclodupzcasjqyruxovuoempvurpahfljtbmpqnrtibjgsfgiaczeqqckjtkqzxauzojrcdkkgtsabajbfkivakikf ... [10344 more chars]
```

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in t):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
                
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow2(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 12 · 2023-12-03 22:58 IST · Time Limit Exceeded · Python3

[submission 1111622130](https://leetcode.com/submissions/detail/1111622130/) · tests 265/267

Failing input:

```text
"kgfidhktkjhlkbgjkylgdracfzjduycghkomrbfbkoowqwgaurizliesjnveoxmvjdjaepdqftmvsuyoogobrutahogxnvuxyezevfuaaiyufwjtezuxtpycfgasburzytdvazwakuxpsiiyhewctwgycgsgdkhdfnzfmvhwrellmvjvzfzsdgqgolorxvxciwjxtqvmxhxlcijeqiytqrzfcpyzlvbvrksmcoybxxpbgyfwgepzvrezgcytabptnjgpxgtweiykgfiolxniqthzwfswihpvtxlseepkopwuueiidyquratphnnqxflqcyiiezssoomlsxtyxlsolngtctjzywrbvajbzeuqsiblhwlehfvtubmwuxyvvpwsrhutlojgwktegek ... [109605 more chars]
```

Expected:

```text
"sehoeyslmrsxseyxdkpnanapjjfophmhnwxswpdijxhbbiyhspwudwlofsewztdprchnsmxbkhenpcujuqdxoqntjspkluzcxirrvouhvyukcptwhytwpjrybjiofksesjvnzpuvnrhqidmpbinsrhsusbixlccflztmppjegruoujgxrvqkckgulquysyefxzrmqbrxunnqwtnprfbtqhqdxmerkkwjloybrraleobdjquayywqfovfazymlvvwlvacmaptoswaksciqyyymwfmvdajywflrfpggezwyvyjpbrgzsgoolclodupzcasjqyruxovuoempvurpahfljtbmpqnrtibjgsfgiaczeqqckjtkqzxauzojrcdkkgtsabajbfkivakikf ... [10344 more chars]
```

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in t):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow2(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 13 · 2023-12-03 22:59 IST · Accepted · Python3

[submission 1111622888](https://leetcode.com/submissions/detail/1111622888/) · tests 267/267 · runtime 794 ms (beats 5.0%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow2(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 14 · 2023-12-29 05:00 IST · Accepted · Python3

[submission 1130947759](https://leetcode.com/submissions/detail/1130947759/) · tests 267/267 · runtime 769 ms (beats 5.0%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow2(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 15 · 2023-12-29 05:03 IST · Accepted · Python3

[submission 1130949292](https://leetcode.com/submissions/detail/1130949292/) · tests 267/267 · runtime 755 ms (beats 5.0%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow2(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        time complexity  T + S
        space - T + S

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 16 · 2023-12-29 05:04 IST · Accepted · Python3

[submission 1130949492](https://leetcode.com/submissions/detail/1130949492/) · tests 267/267 · runtime 265 ms (beats 15.2%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        time complexity  T + S
        space - T + S

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 17 · 2023-12-29 05:04 IST · Accepted · Python3

[submission 1130949566](https://leetcode.com/submissions/detail/1130949566/) · tests 267/267 · runtime 146 ms (beats 21.7%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        time complexity  T + S
        space - T + S

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result
```

## Attempt 18 · 2024-02-10 20:16 IST · Wrong Answer · Python3

[submission 1171473713](https://leetcode.com/submissions/detail/1171473713/) · tests 158/267

Failing input:

```text
"aa"
"aa"
```

Expected:

```text
"aa"
```

Your output:

```text
"a"
```

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        time complexity  T + S
        space - T + S

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result

    def minWindow(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        required_chars = len(required_count)
        found_chars = 0

        result = ""

        l = r = 0
        min_len = float('inf')
        while r<len(s):
            # include in window
            if s[r] in required_count:
                window_count[s[r]] +=1
                if window_count[s[r]] == required_count[s[r]]:
                    found_chars +=1
            
            # contract window
            while l<=r and found_chars == required_chars:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        found_chars -=1

                l+=1
            r+=1
        return result

    
    def minWindow(self, s: str, t: str) -> str:
        required_counter = Counter(t)
        window_counter = Counter()

        found_chars,required_chars = 0, len(required_counter)
        left, right = 0,0

        min_window = float('inf')
        result = ''
        while right < len(s):
            # expand window
            if s[right] in required_counter:
                window_counter[s[right]] += 1
                if window_counter[s[right]] == required_counter[s[right]]:
                    found_chars +=1

            # contract
            while left <= right and found_chars == required_chars:
                # valid window
                if right - left -1 < min_window:
                    min_window = right-left-1
                    result = s[left:right+1]

                if s[left] in window_counter:
                    window_counter[s[left]] -=1
                    if window_counter[s[left]] < required_counter[s[left]]:
                        found_chars -=1
                left+=1

            
            right +=1
        return result

    def minWindow(self, s: str, t: str) -> str:
        target_count = Counter(t)
        window_count = Counter()

        l, r = 0,0
        formed = 0
        required = len(target_count)
        min_length = float('inf')
        min_string = ''
        # print('dfd')
        while r< len(s):
            letter = s[r] 
            if letter in target_count:
                window_count[letter] +=1
                if window_count[letter] == target_count[letter]:
                    formed +=1
            
            # contract
            while l<= r and formed == required:
                # valid window
                if r-l+1 < min_length:
                    min_length = r-l+1
                    min_string = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] == 0:
                        formed -=1
                l +=1
            r+=1
        return min_string
```

## Attempt 19 · 2024-02-10 20:17 IST · Accepted · Python3

[submission 1171474048](https://leetcode.com/submissions/detail/1171474048/) · tests 267/267 · runtime 152 ms (beats 20.3%)

```python
class Solution:
    def minWindow(self, s: str, t: str) -> str:
        

        l, r = 0,0
        window = Counter()
        required_count = Counter(t)
        count = math.inf
        result = ''
        while r < len(s):
            
            if s[r] in required_count:
                window[s[r]] +=1
            # print(r,s[r], char_count, required_count)

            while all(window[ch] >= required_count[ch] for ch in required_count):           
                # get minimum
                if r-l < count:
                    count = r-l
                    result = s[l:r+1]
                
                # reduce the window
                if s[l] in window:
                    window[s[l]] -=1
                l +=1
            print(len(window), len(required_count))
            # move the window
            r+=1
        return result


    def minWindow3(self, s: str, t: str) -> str:
        window = Counter()
        
        required_t = Counter(t)
        required = len(required_t)
        formed = 0
        
        minLength=math.inf 
        minString=''
        
        l = 0
        r = 0
        
        while r<len(s):
            if s[r] in required_t:
                window[s[r]]+=1
                if window[s[r]] == required_t[s[r]]:
                    formed +=1
                    
            while formed == required:
                if r-l< minLength:
                    # print(r-l+1)
                    minLength = r-l
                    minString = s[l:r+1]
                        
                if s[l] in window:
                    window[s[l]] -=1
                    if window[s[l]] < required_t[s[l]]:
                        formed-=1
                l+=1
            r+=1
        return minString

    def minWindow(self, s: str, t: str) -> str:
        '''
        you have a variable window which will expand on each iteration
        and will collapse once you have valid window to find minimum

        how do you check if the window has all the character with correct count
        - use required_counter and window counter

        for optimization I can use required_chars - which will tell me once the window is valid 
        or when it becomes invalid

        time complexity  T + S
        space - T + S

        '''
        required_count = Counter(t)
        window_count = Counter()

        l = 0
        r = 0
        
        required_chars = len(required_count)

        formed =0
        min_len = math.inf
        result = ''
        while r < len(s):

            # check if character is part of required count 
            # update count of char and increase formed to later check against required_chars
            if s[r] in required_count:
                window_count[s[r]] += 1
                if required_count[s[r]] == window_count[s[r]]:
                    formed +=1
            
            # contract the window if valid 
            while formed == required_chars and l<=r:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                # remove left from the window when contracting the window
                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        formed -=1
                l+=1

            r+=1
        return result

    def minWindow(self, s: str, t: str) -> str:
        required_count = Counter(t)
        window_count = Counter()

        required_chars = len(required_count)
        found_chars = 0

        result = ""

        l = r = 0
        min_len = float('inf')
        while r<len(s):
            # include in window
            if s[r] in required_count:
                window_count[s[r]] +=1
                if window_count[s[r]] == required_count[s[r]]:
                    found_chars +=1
            
            # contract window
            while l<=r and found_chars == required_chars:
                if r-l+1 < min_len:
                    min_len = r-l+1
                    result = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < required_count[s[l]]:
                        found_chars -=1

                l+=1
            r+=1
        return result

    
    def minWindow(self, s: str, t: str) -> str:
        required_counter = Counter(t)
        window_counter = Counter()

        found_chars,required_chars = 0, len(required_counter)
        left, right = 0,0

        min_window = float('inf')
        result = ''
        while right < len(s):
            # expand window
            if s[right] in required_counter:
                window_counter[s[right]] += 1
                if window_counter[s[right]] == required_counter[s[right]]:
                    found_chars +=1

            # contract
            while left <= right and found_chars == required_chars:
                # valid window
                if right - left -1 < min_window:
                    min_window = right-left-1
                    result = s[left:right+1]

                if s[left] in window_counter:
                    window_counter[s[left]] -=1
                    if window_counter[s[left]] < required_counter[s[left]]:
                        found_chars -=1
                left+=1

            
            right +=1
        return result

    def minWindow(self, s: str, t: str) -> str:
        target_count = Counter(t)
        window_count = Counter()

        l, r = 0,0
        formed = 0
        required = len(target_count)
        min_length = float('inf')
        min_string = ''
        # print('dfd')
        while r< len(s):
            letter = s[r] 
            if letter in target_count:
                window_count[letter] +=1
                if window_count[letter] == target_count[letter]:
                    formed +=1
            
            # contract
            while l<= r and formed == required:
                # valid window
                if r-l+1 < min_length:
                    min_length = r-l+1
                    min_string = s[l:r+1]

                if s[l] in window_count:
                    window_count[s[l]] -=1
                    if window_count[s[l]] < target_count[s[l]]:
                        formed -=1
                l +=1
            r+=1
        return min_string
```
