# 833. Find And Replace in String

[Problem](https://leetcode.com/problems/find-and-replace-in-string/) · Medium · Strings & Simulation → Index replacement

LeetCode tags: array, hash-table, string, sorting

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-05-21 17:48 IST · Accepted · C++

[submission 954491200](https://leetcode.com/submissions/detail/954491200/) · tests 53/53 · runtime 7 ms (beats 5.1%)

```cpp
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        
        map<int, pair<string, string>> hash;
        string ans = "";
        int k = indices.size();

        for(int idx = 0; idx < k ; idx++){
            int index = indices[idx];
            string source = sources[idx];
            string target = targets[idx];
            
            if(s.substr( index, source.size() ) == source){
                hash[index] = {source, target};
            }
        }
        for(auto &[id, p] : hash) 
            cout<<id<<" "<<p.first<<" "<<p.second<<"::";
        int index = 0;
        while( index < s.size() ){
            if(hash.find(index) != hash.end()){
                ans += hash[index].second;
                index += hash[index].first.size();
            }
            else{
                ans += s[index];
                index++;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-21 17:48 IST · Accepted · C++

[submission 954491357](https://leetcode.com/submissions/detail/954491357/) · tests 53/53 · runtime 11 ms (beats 5.1%)

```cpp
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        
        map<int, pair<string, string>> hash;
        string ans = "";
        int k = indices.size();

        for(int idx = 0; idx < k ; idx++){
            int index = indices[idx];
            string source = sources[idx];
            string target = targets[idx];
            
            if(s.substr( index, source.size() ) == source){
                hash[index] = {source, target};
            }
        }
        // for(auto &[id, p] : hash) 
        //     cout<<id<<" "<<p.first<<" "<<p.second<<"::";
        int index = 0;
        while( index < s.size() ){
            if(hash.find(index) != hash.end()){
                ans += hash[index].second;
                index += hash[index].first.size();
            }
            else{
                ans += s[index];
                index++;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-21 17:49 IST · Accepted · C++

[submission 954491647](https://leetcode.com/submissions/detail/954491647/) · tests 53/53 · runtime 3 ms (beats 20.7%)

```cpp
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        
        map<int, pair<string, string>> hash;
        string ans = "";
        int k = indices.size();

        for(int idx = 0; idx < k ; idx++){
            int index = indices[idx];
            string source = sources[idx];
            string target = targets[idx];
            
            if(s.substr( index, source.size() ) == source){
                hash[index] = {source, target};
            }
        }
        // for(auto &[id, p] : hash) 
        //     cout<<id<<" "<<p.first<<" "<<p.second<<"::";
        int index = 0;
        while( index < s.size() ){
            if(hash.find(index) != hash.end()){
                ans += hash[index].second;
                index += hash[index].first.size();
            }
            else{
                ans += s[index];
                index++;
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-21 17:50 IST · Accepted · C++

[submission 954492404](https://leetcode.com/submissions/detail/954492404/) · tests 53/53 · runtime 3 ms (beats 20.7%)

```cpp
class Solution {
public:
    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        
        map<int, pair<int, string>> hash;
        string ans = "";
        int k = indices.size();

        for(int idx = 0; idx < k ; idx++){
            int index = indices[idx];
            string source = sources[idx];
            string target = targets[idx];
            
            if(s.substr( index, source.size() ) == source){
                hash[index] = {source.size(), target};
            }
        }
        // for(auto &[id, p] : hash) 
        //     cout<<id<<" "<<p.first<<" "<<p.second<<"::";
        int index = 0;
        while( index < s.size() ){
            if(hash.find(index) != hash.end()){
                ans += hash[index].second;
                index += hash[index].first;
            }
            else{
                ans += s[index];
                index++;
            }
        }
        return ans;
    }
};
```
