# 1657. Determine if Two Strings Are Close

[Problem](https://leetcode.com/problems/determine-if-two-strings-are-close/) · Medium · Arrays, Hashing & Sorting → Frequency multisets

LeetCode tags: hash-table, string, sorting, counting

Attempts since Mar 2023: 7 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-04-01 13:38 IST · Wrong Answer · C++

[submission 925782591](https://leetcode.com/submissions/detail/925782591/) · tests 131/153

Failing input:

```text
"uau"
"ssx"
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
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size()) return false;

        map<char, int> w1,w2;
        for(auto ch : word1){
            w1[ch]++;
        }
        for(auto ch : word2){
            w2[ch]++;
        }
        if(w1.size() != w2.size()) return false;
        vector<int> v1,v2;
        for(auto [_, val] : w1){
            v1.push_back(val);
        }
        for(auto [_, val] : w2){
            v2.push_back(val);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        for(int i=0;i< min(v1.size(), v2.size() ) ; i++){
            if(v1[i] != v2[i]) return false;
        }
        return true;
    }
};
```

## Attempt 2 · 2023-04-01 13:40 IST · Accepted · C++

[submission 925783650](https://leetcode.com/submissions/detail/925783650/) · tests 153/153 · runtime 144 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size()) return false;

        map<char, int> w1,w2;
        for(auto ch : word1){
            w1[ch]++;
        }
        for(auto ch : word2){
            w2[ch]++;
        }
        if(w1.size() != w2.size()) return false;
        vector<int> v1,v2;
        vector<char> c1,c2;
        for(auto [ch, val] : w1){
            v1.push_back(val);
            c1.push_back(ch);
        }
        for(auto [ch, val] : w2){
            v2.push_back(val);
            c2.push_back(ch);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());

        for(int i=0;i< min(c1.size(), c2.size() ) ; i++){
            if(c1[i] != c2[i]) return false;
        }
        for(int i=0;i< min(v1.size(), v2.size() ) ; i++){
            if(v1[i] != v2[i]) return false;
        }
        return true;
    }
};
```

## Attempt 3 · 2023-04-01 13:43 IST · Accepted · C++

[submission 925784827](https://leetcode.com/submissions/detail/925784827/) · tests 153/153 · runtime 148 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size()) return false;

        map<char, int> w1,w2;
        for(auto ch : word1){
            w1[ch]++;
        }
        for(auto ch : word2){
            w2[ch]++;
        }
        if(w1.size() != w2.size()) return false;
        vector<int> v1,v2;
        vector<char> c1,c2;
        for(auto [ch, val] : w1){
            v1.push_back(val);
            c1.push_back(ch);
        }
        for(auto [ch, val] : w2){
            v2.push_back(val);
            c2.push_back(ch);
        }
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        sort(c1.begin(), c1.end());
        sort(c2.begin(), c2.end());

        if(c1 != c2) return false;

        if(v1 != v2) return false;

        // for(int i=0;i< min(c1.size(), c2.size() ) ; i++){
        //     if(c1[i] != c2[i]) return false;
        // }
        // for(int i=0;i< min(v1.size(), v2.size() ) ; i++){
        //     if(v1[i] != v2[i]) return false;
        // }
        return true;
    }
};
```

## Attempt 4 · 2023-09-08 23:40 IST · Wrong Answer · C++

[submission 1044132167](https://leetcode.com/submissions/detail/1044132167/) · tests 131/153

Failing input:

```text
"uau"
"ssx"
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
    bool closeStrings(string word1, string word2) {
        map<char, int> c1, c2;
        map<char, int>::iterator it, it1, it2;
        for(int i=0;i<word1.size();i++) {
            it = c1.find(word1[i]);
            if (it == c1.end()) {
                c1.insert(pair<int,int> (word1[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        for(int i=0;i<word2.size();i++) {
            it = c2.find(word2[i]);
            if (it == c2.end()) {
                c2.insert(pair<int,int> (word2[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        if(c1.size() != c2.size()) {
            return false;
        } 
        it1 = c1.begin();
        it2 = c2.begin();
        vector<int> r1,r2;
        while(it1 != c1.end()) {
            r1.push_back(it1->second);
            r2.push_back(it2->second);
            it1++;it2++;
        }
        std::sort(r1.begin(), r1.end());
        std::sort(r2.begin(), r2.end());
        for(int i=0;i<r1.size();i++) {
            if(r1[i]!=r2[i]) {
                return false;
            }
        }
        return true;
    }
};
```

## Attempt 5 · 2023-09-08 23:54 IST · Wrong Answer · C++

[submission 1044144179](https://leetcode.com/submissions/detail/1044144179/) · tests 62/153

Failing input:

```text
"abc"
"bca"
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
    bool closeStrings(string word1, string word2) {
        map<char, int> c1, c2;
        map<char, int>::iterator it, it1, it2;
        for(int i=0;i<word1.size();i++) {
            it = c1.find(word1[i]);
            if (it == c1.end()) {
                c1.insert(pair<int,int> (word1[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        for(int i=0;i<word2.size();i++) {
            it = c2.find(word2[i]);
            if (it == c2.end()) {
                c2.insert(pair<int,int> (word2[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        if(c1.size() != c2.size()) {
            return false;
        } 
        it1 = c1.begin();
        it2 = c2.begin();
        vector<int> r1,r2;
        set<char> s1, s2;
        set<char>::iterator sit1, sit2;
        while(it1 != c1.end()) {
            cout<<it2->first<<" "<<it2->second<<endl;
            r1.push_back(it1->second);
            s1.insert(it1->first);
            r2.push_back(it2->second);
            s1.insert(it2->first);
            it1++;it2++;
        }
        sit1 = s1.begin();
        sit2 = s2.begin();
        while(sit1 != s1.end()) {
            cout<<*sit1<<" "<<*sit2<<endl;
            if(sit1 != sit2) {
                return false;
            }
            sit1++;
            sit2++;
        }
        std::sort(r1.begin(), r1.end());
        std::sort(r2.begin(), r2.end());
        for(int i=0;i<r1.size();i++) {
            if(r1[i]!=r2[i]) {
                return false;
            }
        }
        return true;
    }
};
```

## Attempt 6 · 2023-09-08 23:57 IST · Accepted · C++

[submission 1044146339](https://leetcode.com/submissions/detail/1044146339/) · tests 153/153 · runtime 111 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        map<char, int> c1, c2;
        map<char, int>::iterator it, it1, it2;
        for(int i=0;i<word1.size();i++) {
            it = c1.find(word1[i]);
            if (it == c1.end()) {
                c1.insert(pair<int,int> (word1[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        for(int i=0;i<word2.size();i++) {
            it = c2.find(word2[i]);
            if (it == c2.end()) {
                c2.insert(pair<int,int> (word2[i], 1));
            } else {
                it->second = it->second +1;
            }
        }

        if(c1.size() != c2.size()) {
            return false;
        } 
        it1 = c1.begin();
        it2 = c2.begin();
        vector<int> r1,r2;
        set<char> s1, s2;
        set<char>::iterator sit1, sit2;
        while(it1 != c1.end()) {
            r1.push_back(it1->second);
            s1.insert(it1->first);
            r2.push_back(it2->second);
            s2.insert(it2->first);
            it1++;it2++;
        }
        sit1 = s1.begin();
        sit2 = s2.begin();
        while(sit1 != s1.end()) {
            cout<<*sit1<<" "<<*sit2<<endl;
            if(*sit1 != *sit2) {
                return false;
            }
            sit1++;
            sit2++;
        }
        std::sort(r1.begin(), r1.end());
        std::sort(r2.begin(), r2.end());
        for(int i=0;i<r1.size();i++) {
            if(r1[i]!=r2[i]) {
                return false;
            }
        }
        return true;
    }
};
```

## Attempt 7 · 2023-09-09 00:05 IST · Accepted · C++

[submission 1044153250](https://leetcode.com/submissions/detail/1044153250/) · tests 153/153 · runtime 115 ms (beats 5.0%)

```cpp
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        map<char, int> c1, c2;
        for(auto i:word1) {
            c1[i]++;
        }
        for(auto i:word2) {
            c2[i]++;
        }

        if(c1.size() != c2.size()) {
            return false;
        } 
        vector<int> r1,r2;
        set<char> s1, s2;
        for(auto [k,v]:c1) { 
            r1.push_back(v);
            s1.insert(k);
        }
        for(auto [k,v]:c2) { 
            r2.push_back(v);
            s2.insert(k);
        }
        std::sort(r1.begin(), r1.end());
        std::sort(r2.begin(), r2.end());
        if(s1 != s2) return false;
        if(r1 != r2) return false;
        return true;
    }
};
```
