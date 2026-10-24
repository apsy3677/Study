# 126. Word Ladder II

[Problem](https://leetcode.com/problems/word-ladder-ii/) · Hard · Graph: General BFS/DFS → BFS layers + path backtrack

LeetCode tags: hash-table, string, backtracking, breadth-first-search, bidirectional-search

Attempts since Mar 2023: 10 · accepted: 6 · failed before first AC: 1

## Attempt 1 · 2023-03-22 19:55 IST · Time Limit Exceeded · C++

[submission 920159508](https://leetcode.com/submissions/detail/920159508/) · tests 0/36

Failing input:

```text
"hit"
"cog"
["hot","dot","dog","lot","log","cog"]
```

Expected:

```text
[["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
```

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        map<string,int> isVis;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
};
```

## Attempt 2 · 2023-03-22 19:59 IST · Accepted · C++

[submission 920161455](https://leetcode.com/submissions/detail/920161455/) · tests 36/36 · runtime 64 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
};
```

## Attempt 3 · 2023-03-22 20:00 IST · Accepted · C++

[submission 920162321](https://leetcode.com/submissions/detail/920162321/) · tests 36/36 · runtime 63 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
};
```

## Attempt 4 · 2023-03-22 22:10 IST · Accepted · C++

[submission 920230156](https://leetcode.com/submissions/detail/920230156/) · tests 36/36 · runtime 67 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level =0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
};
```

## Attempt 5 · 2023-04-30 09:24 IST · Compile Error · C++

[submission 941913351](https://leetcode.com/submissions/detail/941913351/)

Your output:

```text
{"compile_error": "Line 87: Char 5: error: expected member name or ';' after declaration specifiers\n    {\n    ^\n1 error generated."}
```

Compile error:

```text
Line 87: Char 5: error: expected member name or ';' after declaration specifiers
    {
    ^
1 error generated.
```

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<string> qu;
        qu.push(beginWord);
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back();
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-04-30 09:27 IST · Time Limit Exceeded · C++

[submission 941915375](https://leetcode.com/submissions/detail/941915375/) · tests 32/36

Failing input:

```text
"aaaaa"
"ggggg"
["aaaaa","caaaa","cbaaa","daaaa","dbaaa","eaaaa","ebaaa","faaaa","fbaaa","gaaaa","gbaaa","haaaa","hbaaa","iaaaa","ibaaa","jaaaa","jbaaa","kaaaa","kbaaa","laaaa","lbaaa","maaaa","mbaaa","naaaa","nbaaa","oaaaa","obaaa","paaaa","pbaaa","bbaaa","bbcaa","bbcba","bbdaa","bbdba","bbeaa","bbeba","bbfaa","bbfba","bbgaa","bbgba","bbhaa","bbhba","bbiaa","bbiba","bbjaa","bbjba","bbkaa","bbkba" ... [3529 more chars]
```

Expected:

```text
[["aaaaa","aaaaz","aaawz","aavwz","avvwz","vvvwz","vvvww","wvvww","wwvww","wwwww","ywwww","yywww","yyyww","yyyyw","yyyyy","xyyyy","xxyyy","xxxyy","xxxxy","xxxxx","gxxxx","ggxxx","gggxx","ggggx","ggggg"]]
```

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        return findLaddersUtil(beginWord, endWord, wordList);

        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    vector<vector<string>> findLaddersUtil(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> qu;
        qu.push({beginWord});
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back(word);
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```

## Attempt 7 · 2023-10-14 08:45 IST · Memory Limit Exceeded · C++

[submission 1074679202](https://leetcode.com/submissions/detail/1074679202/) · tests 32/36

Failing input:

```text
"aaaaa"
"ggggg"
["aaaaa","caaaa","cbaaa","daaaa","dbaaa","eaaaa","ebaaa","faaaa","fbaaa","gaaaa","gbaaa","haaaa","hbaaa","iaaaa","ibaaa","jaaaa","jbaaa","kaaaa","kbaaa","laaaa","lbaaa","maaaa","mbaaa","naaaa","nbaaa","oaaaa","obaaa","paaaa","pbaaa","bbaaa","bbcaa","bbcba","bbdaa","bbdba","bbeaa","bbeba","bbfaa","bbfba","bbgaa","bbgba","bbhaa","bbhba","bbiaa","bbiba","bbjaa","bbjba","bbkaa","bbkba" ... [3529 more chars]
```

Expected:

```text
[["aaaaa","aaaaz","aaawz","aavwz","avvwz","vvvwz","vvvww","wvvww","wwvww","wwwww","ywwww","yywww","yyyww","yyyyw","yyyyy","xyyyy","xxyyy","xxxyy","xxxxy","xxxxx","gxxxx","ggxxx","gggxx","ggggx","ggggg"]]
```

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        return findLaddersUtil(beginWord, endWord, wordList);

        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    vector<vector<string>> findLaddersUtil(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> qu;
        qu.push({beginWord});
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back(word);
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```

## Attempt 8 · 2023-10-14 08:55 IST · Accepted · C++

[submission 1074682758](https://leetcode.com/submissions/detail/1074682758/) · tests 36/36 · runtime 54 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    // if not visited
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // return findLaddersUtil(beginWord, endWord, wordList);

        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    vector<vector<string>> findLaddersUtil(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> qu;
        qu.push({beginWord});
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back(word);
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```

## Attempt 9 · 2023-10-14 08:56 IST · Accepted · C++

[submission 1074683017](https://leetcode.com/submissions/detail/1074683017/) · tests 36/36 · runtime 46 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    // if not visited
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
            visited.clear();
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (int i = 0; i < graph[source].size(); i++) {
            currPath.push_back(graph[source][i]);
            backtrack(graph[source][i], destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // return findLaddersUtil(beginWord, endWord, wordList);

        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    vector<vector<string>> findLaddersUtil(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> qu;
        qu.push({beginWord});
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back(word);
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```

## Attempt 10 · 2023-10-14 08:59 IST · Accepted · C++

[submission 1074684278](https://leetcode.com/submissions/detail/1074684278/) · tests 36/36 · runtime 45 ms (beats 5.0%)

```cpp
class Solution {
    map<string, vector<string>> graph;
    vector<string> currPath;
    vector<vector<string>> shortestPaths;

public:
    vector<string> findNeighbours(string &curr, set<string> &wordList){
        vector<string> res;
        for(int i=0;i<curr.size();i++){
            char temp = curr[i];
            for(char c= 'a'; c<='z'; c++){
                curr[i] = c;
                if(temp == c || !wordList.count(curr)) 
                    continue;
                
                res.push_back(curr) ;
            }
            curr[i] = temp;
        }
        return res;
    }

    void bfs(string& beginWord, string& endWord, set<string>& words){
        queue<string> qu;
        if(words.find(beginWord) != words.end())
            words.erase(words.find(beginWord));
        qu.push(beginWord);

        int level = 0;

        map<string,int> isVis;
        vector<string> visited;

        while(!qu.empty()){
            int sz = qu.size();
            level++;
            for(int i=0;i<sz;i++){
                string curr = qu.front();
                qu.pop();
                
                vector<string> neigh = findNeighbours(curr, words);
                for(auto x: neigh){
                    visited.push_back(x);
                    graph[x].push_back(curr);
                    
                    // if not visited
                    if(isVis.find(x) == isVis.end()){
                        qu.push(x);
                        isVis[x]=1;
                    }
                }
            }

            for(int i=0;i<visited.size();i++){
                if(words.find(visited[i]) != words.end()){
                    words.erase(words.find(visited[i]));
                }
            }
            visited.clear();
        }
    }

    void backtrack(string &source, string &destination) {
        // store the path if we reached the endWord
        if (source == destination) {
            shortestPaths.push_back(vector<string>(currPath.rbegin(), currPath.rend()));
        }
        for (auto node : graph[source]) {
            currPath.push_back(node);
            backtrack(node, destination);
            currPath.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // return findLaddersUtil(beginWord, endWord, wordList);

        set<string> words(wordList.begin(), wordList.end());
        int ans =0;
        // if(words.find(beginWord) != words.end())
        //     words.erase(words.find(beginWord));
        
        // builds graph
        bfs(beginWord, endWord, words);
        currPath = {endWord};
        backtrack(endWord, beginWord);

        return shortestPaths;
    }
    vector<vector<string>> findLaddersUtil(string beginWord, string endWord, vector<string>& wordList)
    {
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<vector<string>> qu;
        qu.push({beginWord});
        
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;
        
        while(!qu.empty()){
            // new level
            int sz = qu.size();
            for(auto it : usedOnLevel){
                st.erase(it);
            }
            usedOnLevel.clear();
            while(sz--){
                vector<string> seq = qu.front(); qu.pop();
                
                string word = seq.back();
                if(word == endWord){
                    if(ans.size()==0){
                        ans.push_back(seq);
                    }
                    else if(ans[0].size() == seq.size()){
                        ans.push_back(seq);
                    }
                }
                for(int i=0;i<word.size();i++){
                    char ch = word[i];
                    for(char c = 'a'; c<='z'; c++){
                        word[i]=c;
                        if(st.count(word) >0){
                            usedOnLevel.push_back(word);
                            seq.push_back(word);
                            qu.push(seq);
                            seq.pop_back();
                        }
                    }
                    word[i]=ch;
                }
            }
        }
        return ans;
    }
};
```
