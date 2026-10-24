# 187. Repeated DNA Sequences

[Problem](https://leetcode.com/problems/repeated-dna-sequences/) · Medium · Sliding Window → Fixed window + hashing

LeetCode tags: hash-table, string, bit-manipulation, sliding-window, rolling-hash, hash-function, z-algorithm, boyer-moore-string-search-algorithm

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-05-07 10:38 IST · Accepted · C++

[submission 945874530](https://leetcode.com/submissions/detail/945874530/) · tests 31/31 · runtime 130 ms (beats 98.3%)

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> out{};
        map<string, int> mp;
        int left = 0, right = 0, k=10;
        deque<char> dq;

        string dna;
        for(int i=0;i<k;i++){
            dq.push_back(s[i]);
            dna += s[i];
        }
        mp[dna]++;
        for(int i=k;i<s.size();i++){
            dna.erase(0, 1);
            dna += s[i];
            mp[dna]++;
        }
        for(auto it : mp){
            if(it.second > 1){
                out.push_back(it.first);
            }
        }
        return out;
    }
};
```

## Attempt 2 · 2023-05-07 10:43 IST · Accepted · C++

[submission 945876566](https://leetcode.com/submissions/detail/945876566/) · tests 31/31 · runtime 66 ms (beats 98.9%)

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // map<string, int> mp;
        unordered_set<string> seen, out;
        int left = 0, right = 0, k=10;

        string dna;
        for(int i=0;i<k;i++){
            dna += s[i];
        }
        seen.insert(dna);
        for(int i=k;i<s.size();i++){
            dna.erase(0, 1);
            dna += s[i];
            if(seen.find(dna) != seen.end()) out.insert(dna);
            seen.insert(dna);
        }
        // for(auto it : mp){
        //     if(it.second > 1){
        //         out.push_back(it.first);
        //     }
        // }
        return vector<string>(out.begin(), out.end());
    }
};
```

## Attempt 3 · 2023-05-07 10:44 IST · Accepted · C++

[submission 945876723](https://leetcode.com/submissions/detail/945876723/) · tests 31/31 · runtime 66 ms (beats 98.9%)

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // map<string, int> mp;
        unordered_set<string> seen, out;
        int k=10;

        string dna;
        for(int i=0;i<k;i++){
            dna += s[i];
        }
        seen.insert(dna);
        for(int i=k;i<s.size();i++){
            dna.erase(0, 1);
            dna += s[i];
            if(seen.find(dna) != seen.end()) out.insert(dna);
            seen.insert(dna);
        }

        return vector<string>(out.begin(), out.end());
    }
};
```
