# 205. Isomorphic Strings

[Problem](https://leetcode.com/problems/isomorphic-strings/) · Easy · Arrays, Hashing & Sorting → Two-way map

LeetCode tags: hash-table, string

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-05-23 14:08 IST · Wrong Answer · C++

[submission 955666814](https://leetcode.com/submissions/detail/955666814/) · tests 41/44

Failing input:

```text
"32767"
"65535"
```

Expected:

```text
false
```

Your output:

```text
true
```

```cpp
class Solution {
public:
    bool isIsomorphic(string str1, string str2) {
        set<vector<int>> set1, set2;
        vector<vector<int>> set3;
        auto print = [](set<vector<int>> &s){
            for(auto vec : s){
                for(auto x : vec){
                    cout<<x<<":";
                }
                cout<<"|";
            }
        };
        for(int ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str1.size();i++){
                if( str1[i] == ch){
                    occurences.push_back(i);
                }
            }
            set1.insert(occurences);
        }
        cout<<"Set1 ";
        print(set1);
        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str2.size();i++){
                if( str2[i] == ch){
                    occurences.push_back(i);
                }
            }
            set2.insert(occurences);
        }
        cout<<"Set2 ";
        print(set2);
        int unique1 = set1.size();
        int unique2 = set2.size();
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(set3));
        
        if(set1 == set2 ) return true;
        cout<<" unique set size "<<unique1 <<" "<< unique2 <<" " <<" inter " <<set3.size() <<" set2 " << set2.size()<<" set1 "<<set1.size()<<" ";
        if(unique1 > unique2 && set3.size() == set2.size()){
            return 2;
        }
        return false;
    }
};
```

## Attempt 2 · 2023-05-23 14:12 IST · Accepted · C++

[submission 955668181](https://leetcode.com/submissions/detail/955668181/) · tests 44/44 · runtime 12 ms (beats 6.3%)

```cpp
class Solution {
public:
    bool isIsomorphic1(string s, string t) {
         unordered_map<char, char> mp, mp2;
        for (int i=0; i<s.length(); ++i) {
            if (mp[s[i]] && mp[s[i]]!=t[i]) return false;
            if (mp2[t[i]] && mp2[t[i]]!=s[i]) return false;
            mp[s[i]]=t[i];
            mp2[t[i]]=s[i];
        }
        return true;
    }
    bool isIsomorphic(string str1, string str2) {
        return isIsomorphic1(str1, str2);
        set<vector<int>> set1, set2;
        vector<vector<int>> set3;
        auto print = [](set<vector<int>> &s){
            for(auto vec : s){
                for(auto x : vec){
                    cout<<x<<":";
                }
                cout<<"|";
            }
        };
        for(int ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str1.size();i++){
                if( str1[i] == ch){
                    occurences.push_back(i);
                }
            }
            set1.insert(occurences);
        }
        cout<<"Set1 ";
        print(set1);
        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str2.size();i++){
                if( str2[i] == ch){
                    occurences.push_back(i);
                }
            }
            set2.insert(occurences);
        }
        cout<<"Set2 ";
        print(set2);
        int unique1 = set1.size();
        int unique2 = set2.size();
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(set3));
        
        if(set1 == set2 ) return true;
        cout<<" unique set size "<<unique1 <<" "<< unique2 <<" " <<" inter " <<set3.size() <<" set2 " << set2.size()<<" set1 "<<set1.size()<<" ";
        if(unique1 > unique2 && set3.size() == set2.size()){
            return 2;
        }
        return false;
    }
};
```

## Attempt 3 · 2023-05-23 15:09 IST · Accepted · C++

[submission 955695727](https://leetcode.com/submissions/detail/955695727/) · tests 44/44 · runtime 12 ms (beats 6.3%)

```cpp
class Solution {
public:
    bool isIsomorphic1(string s, string t) {
         unordered_map<char, char> mp, mp2;
        for (int i=0; i<s.length(); ++i) {
            if (mp[s[i]] && mp[s[i]]!=t[i]) return false;
            if (mp2[t[i]] && mp2[t[i]]!=s[i]) return false;
            mp[s[i]]=t[i];
            mp2[t[i]]=s[i];
        }
        return true;
    }
    bool isIsomorphic(string str1, string str2) {
        return isIsomorphic1(str1, str2);
    }
};
```
