# 127. Word Ladder

[Problem](https://leetcode.com/problems/word-ladder/) · Hard · Graph: General BFS/DFS → BFS on implicit graph

LeetCode tags: hash-table, string, breadth-first-search, bidirectional-search

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-22 18:37 IST · Accepted · C++

[submission 920118983](https://leetcode.com/submissions/detail/920118983/) · tests 50/50 · runtime 592 ms (beats 13.5%)

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<string> qu;
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                if(curr == endWord){
                    return level;
                }
                vector<string> neigh = findNeighbours(curr);
                for(auto x: neigh){
                    if(words.find(x) != words.end()){
                        qu.push(x);
                        words.erase(words.find(x));
                    }
                }
            }
        }
        return 0;
    }

    vector<string> findNeighbours(string curr){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                // if(curr[i] == c) 
                //     continue;
                curr[i] = c;
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

};
```

## Attempt 2 · 2023-03-22 18:56 IST · Accepted · C++

[submission 920128078](https://leetcode.com/submissions/detail/920128078/) · tests 50/50 · runtime 587 ms (beats 13.6%)

```cpp
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<string> qu;
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                if(curr == endWord){
                    return level;
                }
                vector<string> neigh = findNeighbours(curr);
                for(auto x: neigh){
                    if(words.find(x) != words.end()){
                        qu.push(x);
                        words.erase(words.find(x));
                    }
                }
            }
        }
        return 0;
    }

    vector<string> findNeighbours(string curr){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                if(temp == c) 
                    continue;
                curr[i] = c;
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

};
```

## Attempt 3 · 2023-04-29 17:09 IST · Accepted · C++

[submission 941514736](https://leetcode.com/submissions/detail/941514736/) · tests 50/50 · runtime 84 ms (beats 36.3%)

```cpp
class Solution {
public:
    int ladderLength(string startWord, string targetWord, vector<string>& words) {
    // int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(words.begin(), words.end()); // like not seen so far
        queue<string> qu;
        qu.push(startWord);
        if(st.find(startWord) != st.end())
            st.erase(st.find(startWord));
        int level = 1;
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                string node = qu.front(); qu.pop();
                
                if(node == targetWord) return level;
                
                for(int i=0;i<node.size();i++){
                    char ch = node[i];
                    for(char c = 'a'; c<='z';c++){
                        node[i] = c;
                        if(st.find(node) != st.end()){
                            st.erase(st.find(node));
                            qu.push(node);
                        }
                    }
                    node[i]=ch;
                }
            }
            level++;
            
        }
        return 0;
        
        // queue<string> qu;
        // set<string> words(wordList.begin(), wordList.end());
        // int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        // qu.push(beginWord);

        // int level =0;

        // while(!qu.empty()){
        //     int sz = qu.size();
        //     level++;
        //     for(int i=0;i<sz;i++){
        //         string curr = qu.front();
        //         qu.pop();
        //         if(curr == endWord){
        //             return level;
        //         }
        //         vector<string> neigh = findNeighbours(curr);
        //         for(auto x: neigh){
        //             if(words.find(x) != words.end()){
        //                 qu.push(x);
        //                 words.erase(words.find(x));
        //             }
        //         }
        //     }
        // }
        // return 0;
    }

    vector<string> findNeighbours(string curr){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                if(temp == c) 
                    continue;
                curr[i] = c;
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

};
```

## Attempt 4 · 2023-10-14 08:28 IST · Accepted · C++

[submission 1074673446](https://leetcode.com/submissions/detail/1074673446/) · tests 51/51 · runtime 62 ms (beats 47.9%)

```cpp
class Solution {
public:
    int ladderLength(string startWord, string targetWord, vector<string>& words) {
    // int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> st(words.begin(), words.end()); // like not seen so far
        queue<string> qu;
        qu.push(startWord);
        if(st.find(startWord) != st.end())
            st.erase(st.find(startWord));
        int level = 1;
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                string node = qu.front(); qu.pop();
                
                if(node == targetWord) return level;
                
                for(int i=0;i<node.size();i++){
                    char ch = node[i];
                    for(char c = 'a'; c<='z';c++){
                        node[i] = c;
                        if(st.find(node) != st.end()){
                            st.erase(st.find(node));
                            qu.push(node);
                        }
                    }
                    node[i]=ch;
                }
            }
            level++;
            
        }
        return 0;
        
        // queue<string> qu;
        // set<string> words(wordList.begin(), wordList.end());
        // int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        // qu.push(beginWord);

        // int level =0;

        // while(!qu.empty()){
        //     int sz = qu.size();
        //     level++;
        //     for(int i=0;i<sz;i++){
        //         string curr = qu.front();
        //         qu.pop();
        //         if(curr == endWord){
        //             return level;
        //         }
        //         vector<string> neigh = findNeighbours(curr);
        //         for(auto x: neigh){
        //             if(words.find(x) != words.end()){
        //                 qu.push(x);
        //                 words.erase(words.find(x));
        //             }
        //         }
        //     }
        // }
        // return 0;
    }

    vector<string> findNeighbours(string curr){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                if(temp == c) 
                    continue;
                curr[i] = c;
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

};
```

## Attempt 5 · 2023-10-14 08:33 IST · Accepted · C++

[submission 1074675001](https://leetcode.com/submissions/detail/1074675001/) · tests 51/51 · runtime 69 ms (beats 43.1%)

```cpp
class Solution {
public:
    int ladderLength(string startWord, string targetWord, vector<string>& wordList) {
    // int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // unordered_set<string> st(words.begin(), words.end()); // like not seen so far
        // queue<string> qu;
        // qu.push(startWord);
        // if(st.find(startWord) != st.end())
        //     st.erase(st.find(startWord));
        // int level = 1;
        // while(!qu.empty()){
        //     int sz = qu.size();
        //     while(sz--){
        //         string node = qu.front(); qu.pop();
                
        //         if(node == targetWord) return level;
                
        //         for(int i=0;i<node.size();i++){
        //             char ch = node[i];
        //             for(char c = 'a'; c<='z';c++){
        //                 node[i] = c;
        //                 if(st.find(node) != st.end()){
        //                     st.erase(st.find(node));
        //                     qu.push(node);
        //                 }
        //             }
        //             node[i]=ch;
        //         }
        //     }
        //     level++;
            
        // }
        // return 0;
        
        queue<string> qu;
        unordered_set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        if(words.find(startWord) != words.end())
            words.erase(words.find(startWord));
        qu.push(startWord);

        int level =0;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                if(curr == targetWord){
                    return level;
                }
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    qu.push(x);
                    words.erase(words.find(x));
                }
            }
        }
        return 0;
    }

    vector<string> findNeighbours(string curr, unordered_set<string> &words){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                if(temp == c) 
                    continue;
                curr[i] = c;
                if (words.count(curr))
                    res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

};
```
