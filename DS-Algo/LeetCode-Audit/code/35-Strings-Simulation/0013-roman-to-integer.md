# 13. Roman to Integer

[Problem](https://leetcode.com/problems/roman-to-integer/) · Easy · Strings & Simulation → Parsing

LeetCode tags: hash-table, math, string

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-06 22:32 IST · Accepted · C++

[submission 910290507](https://leetcode.com/submissions/detail/910290507/) · tests 3999/3999 · runtime 17 ms (beats 5.1%)

```cpp
class Solution {
public:
    
    map<char, int> valMap;

    vector<char> symbols = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    vector<int> values = {1,5,10,50,100,500,1000};

    bool charIslessthenNext(char prev, char next){
        bool ans = false;
        if(valMap[next] > valMap[prev]){
            return true;
        }
        return ans;
    }
    
    int romanToInt(string s) {
        
        for(int i=0; i<symbols.size();i++){
            valMap[symbols[i]] = values[i];
        }
        
        int ans =0;
        for(int i=0;i<s.size();i++){
            if( (i+1 < s.size() && charIslessthenNext(s[i], s[i+1]) ) ){
                
                    ans += valMap[s[i+1]] - valMap[s[i]];
                    i++;
                
                
                
            }
            else{
                ans+= valMap[s[i]];
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-07 00:38 IST · Accepted · C++

[submission 910366895](https://leetcode.com/submissions/detail/910366895/) · tests 3999/3999 · runtime 11 ms (beats 26.4%)

```cpp
class Solution {
public:
    
    map<char, int> valMap;

    vector<char> symbols = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    vector<int> values = {1,5,10,50,100,500,1000};

    bool charIslessthenNext(char prev, char next){
        bool ans = false;
        if(valMap[next] > valMap[prev]){
            return true;
        }
        return ans;
    }
    
    int romanToInt(string s) {
        
        for(int i=0; i<symbols.size();i++){
            valMap[symbols[i]] = values[i];
        }
        
        int ans =0;
        for(int i=0;i<s.size();i++){
            if( (i+1 < s.size() && charIslessthenNext(s[i], s[i+1]) ) ){
                
                    ans += valMap[s[i+1]] - valMap[s[i]];
                    i++;
                
                
                
            }
            else{
                ans+= valMap[s[i]];
            }
        }
        return ans;
    }
};
```
