# 1153. String Transforms Into Another String

[Problem](https://leetcode.com/problems/string-transforms-into-another-string/) · Hard · Graph: General BFS/DFS → Mapping graph cycles

LeetCode tags: hash-table, string, graph

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-05-21 18:08 IST · Wrong Answer · C++

[submission 954499981](https://leetcode.com/submissions/detail/954499981/) · tests 32/40

Failing input:

```text
"abcdefghijklmnopqrstuvwxyz"
"bcadefghijklmnopqrstuvwxzz"
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
public:
    bool canConvert(string str1, string str2) {
        set<vector<int>> set1, set2;

        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str1.size();i++){
                if( str1[i] == ch){
                    occurences.push_back(i);
                }
            }
            set1.insert(occurences);
        }

        for(auto ch = 'a'; ch<='z'; ch++){
            vector<int> occurences;
            for(int i=0;i<str2.size();i++){
                if( str2[i] == ch){
                    occurences.push_back(i);
                }
            }
            set2.insert(occurences);
        }

        return set1 == set2 ? true : false;
        
    }
};
```

## Attempt 2 · 2023-05-23 14:13 IST · Wrong Answer · C++

[submission 955668873](https://leetcode.com/submissions/detail/955668873/) · tests 32/40

Failing input:

```text
"abcdefghijklmnopqrstuvwxyz"
"bcadefghijklmnopqrstuvwxzz"
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
public:
    bool isIsomorphic1(string s, string t) {
        if(s.size() != t.size()) return false;
        unordered_map<char, char> mp, mp2;
        for (int i=0; i<s.length(); ++i) {
            if (mp[s[i]] && mp[s[i]]!=t[i]) return false;
            if (mp2[t[i]] && mp2[t[i]]!=s[i]) return false;
            mp[s[i]]=t[i];
            mp2[t[i]]=s[i];
        }
        return true;
    }
    bool canConvert(string str1, string str2) {
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

## Attempt 3 · 2023-05-23 14:22 IST · Accepted · C++

[submission 955672846](https://leetcode.com/submissions/detail/955672846/) · tests 40/40 · runtime 3 ms (beats 89.2%)

```cpp
class Solution {
public:
    bool isIsomorphic1(string s, string t) {
        if(s.size() != t.size()) return false;
        if(s == t) return true;
        unordered_map<char, char> mp, mp2;
        for (int i=0; i<s.length(); ++i) {
            if (mp[s[i]] && mp[s[i]]!=t[i]) return false;
            // if (mp2[t[i]] && mp2[t[i]]!=s[i]) return false;
            mp[s[i]]=t[i];
            // mp2[t[i]]=s[i];
        }
        return unordered_set(t.begin(), t.end()).size() < 26;
    }
    bool canConvert(string str1, string str2) {
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
