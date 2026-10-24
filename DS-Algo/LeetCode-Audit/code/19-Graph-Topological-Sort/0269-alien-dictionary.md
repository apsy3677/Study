# 269. Alien Dictionary

[Problem](https://leetcode.com/problems/alien-dictionary/) · Hard · Graph: Topological Sort → Order from word pairs

LeetCode tags: array, string, depth-first-search, breadth-first-search, graph, topological-sort, directed-acyclic-graph

Attempts since Mar 2023: 20 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-03-25 19:26 IST · Accepted · C++

[submission 921872538](https://leetcode.com/submissions/detail/921872538/) · tests 127/127 · runtime 8 ms (beats 6.3%)

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char, vector<char>> graph;
        map<char, int> inDegree;

        for(auto word : words){
            for(auto ch : word){
                inDegree[ch]=0;
            }
        }

        // Build Graph
        for(int i=1;i<words.size();i++){
            string pre = words[i-1];
            string curr = words[i];
            int j = 0;

            while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
                j++;
            }
            if(j<pre.size() && j==curr.size()) return "";
            if(j<curr.size() && j<pre.size()){
                graph[pre[j]].push_back(curr[j]);
                inDegree[curr[j]]++;
                // if(inDegree.count(pre[j]) == 0){
                //     inDegree[pre[j]]=0;
                // }
            }
        }

        // Do Topological Sorting
        queue<char> qu;
        cout<<" push in Queue ";
        for(auto d: inDegree){
            cout<<d.first <<" "<<d.second<<" ";
            if(d.second == 0){
                qu.push(d.first);
                
            }
        }
        cout<<qu.size()<<" queue size ";

        string ans = "";
        while(!qu.empty()){
            int sz = qu.size();
            for(int i=0;i<sz;i++){
                char ch = qu.front(); qu.pop();
                ans += ch;
                for(auto end : graph[ch]){
                    inDegree[end]--;
                    if(inDegree[end] == 0){
                        qu.push(end);
                    }
                }
            }
        }

        if(ans.size() == inDegree.size()){
            return ans;
        }
        return "";

    }
};
```

## Attempt 2 · 2023-03-25 19:34 IST · Wrong Answer · C++

[submission 921875962](https://leetcode.com/submissions/detail/921875962/) · tests 104/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char, vector<char>> graph;
        map<char, int> inDegree;

        for(auto word : words){
            for(auto ch : word){
                inDegree[ch]=0;
            }
        }

        // Build Graph
        for(int i=1;i<words.size();i++){
            string pre = words[i-1];
            string curr = words[i];
            int j = 0;

            // OPTIMIZE this 

            if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
                return "";
            }
            for(int j=0;j< min(pre.size(), curr.size()) ; j++){
                if(pre[j] != curr[j]){
                    graph[pre[j]].push_back(curr[j]);
                    inDegree[curr[j]]++;
                }
            }

            // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
            //     j++;
            // }
            // if(j<pre.size() && j==curr.size()) return "";
            // if(j<curr.size() && j<pre.size()){
            //     graph[pre[j]].push_back(curr[j]);
            //     inDegree[curr[j]]++;
            //     // if(inDegree.count(pre[j]) == 0){
            //     //     inDegree[pre[j]]=0;
            //     // }
            // }
        }

        // Do Topological Sorting
        queue<char> qu;
        cout<<" push in Queue ";
        for(auto d: inDegree){
            cout<<d.first <<" "<<d.second<<" ";
            if(d.second == 0){
                qu.push(d.first);
                
            }
        }
        cout<<qu.size()<<" queue size ";

        string ans = "";
        while(!qu.empty()){
            int sz = qu.size();
            for(int i=0;i<sz;i++){
                char ch = qu.front(); qu.pop();
                ans += ch;
                for(auto end : graph[ch]){
                    inDegree[end]--;
                    if(inDegree[end] == 0){
                        qu.push(end);
                    }
                }
            }
        }

        if(ans.size() == inDegree.size()){
            return ans;
        }
        return "";

    }
};
```

## Attempt 3 · 2023-03-25 20:21 IST · Accepted · C++

[submission 921897939](https://leetcode.com/submissions/detail/921897939/) · tests 127/127 · runtime 4 ms (beats 18.8%)

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char, vector<char>> graph;
        map<char, int> inDegree;

        for(auto word : words){
            for(auto ch : word){
                inDegree[ch]=0;
            }
        }

        // Build Graph
        for(int i=1;i<words.size();i++){
            string pre = words[i-1];
            string curr = words[i];
            int j = 0;

            // OPTIMIZE this 

            if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
                return "";
            }
            for(int j=0;j< min(pre.size(), curr.size()) ; j++){
                if(pre[j] != curr[j]){
                    graph[pre[j]].push_back(curr[j]);
                    inDegree[curr[j]]++;
                    break;
                }
            }

            // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
            //     j++;
            // }
            // if(j<pre.size() && j==curr.size()) return "";
            // if(j<curr.size() && j<pre.size()){
            //     graph[pre[j]].push_back(curr[j]);
            //     inDegree[curr[j]]++;
            //     // if(inDegree.count(pre[j]) == 0){
            //     //     inDegree[pre[j]]=0;
            //     // }
            // }
        }

        // Do Topological Sorting
        queue<char> qu;
        cout<<" push in Queue ";
        for(auto d: inDegree){
            cout<<d.first <<" "<<d.second<<" ";
            if(d.second == 0){
                qu.push(d.first);
                
            }
        }
        cout<<qu.size()<<" queue size ";

        string ans = "";
        while(!qu.empty()){
            int sz = qu.size();
            for(int i=0;i<sz;i++){
                char ch = qu.front(); qu.pop();
                ans += ch;
                for(auto end : graph[ch]){
                    inDegree[end]--;
                    if(inDegree[end] == 0){
                        qu.push(end);
                    }
                }
            }
        }

        if(ans.size() == inDegree.size()){
            return ans;
        }
        return "";

    }
};
```

## Attempt 4 · 2023-04-29 15:19 IST · Wrong Answer · C++

[submission 941479595](https://leetcode.com/submissions/detail/941479595/) · tests 124/127

Failing input:

```text
["abc","ab"]
```

Expected:

```text
""
```

Your output:

```text
"cba"
```

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {

        unordered_map<char, int> indegree;
        for(auto word : words){
            for(auto ch : word)
                indegree[ch] =0;
        }
        unordered_map<char, vector<char>> adj;
        // create a graph between chars
        for(int i=1;i<words.size();i++){
            // compare dict[i-] & dict[i]
            string s1 = words[i-1], s2 = words[i];
            int len = min(s1.size(),s2.size());
            for(int j=0;j<len;j++){
                // build graph
                // store indegrees
                if(s1[j] != s2[j]){
                    adj[s1[j]].push_back(s2[j]);
                    indegree[s2[j]]++;
                    break;
                }
            }
        }
        queue<char> qu;
        // fill initial nodes with indegree 0
        for(auto &it : indegree){
            if(it.second == 0)
                qu.push(it.first);
        }
        // apply toposort
        string ans="";
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                char node = qu.front(); qu.pop();
                ans += node;
                for(auto &it: adj[node]){
                    indegree[it]--;
                    if(indegree[it]==0) qu.push(it);
                }
            }
        }
        if(ans.size() != indegree.size())
            return "";
        return ans;

        // map<char, vector<char>> graph;
        // map<char, int> inDegree;

        // for(auto word : words){
        //     for(auto ch : word){
        //         inDegree[ch]=0;
        //     }
        // }

        // // Build Graph
        // for(int i=1;i<words.size();i++){
        //     string pre = words[i-1];
        //     string curr = words[i];
        //     int j = 0;

        //     // OPTIMIZE this 

        //     if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
        //         return "";
        //     }
        //     for(int j=0;j< min(pre.size(), curr.size()) ; j++){
        //         if(pre[j] != curr[j]){
        //             graph[pre[j]].push_back(curr[j]);
        //             inDegree[curr[j]]++;
        //             break;
        //         }
        //     }

        //     // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
        //     //     j++;
        //     // }
        //     // if(j<pre.size() && j==curr.size()) return "";
        //     // if(j<curr.size() && j<pre.size()){
        //     //     graph[pre[j]].push_back(curr[j]);
        //     //     inDegree[curr[j]]++;
        //     //     // if(inDegree.count(pre[j]) == 0){
        //     //     //     inDegree[pre[j]]=0;
        //     //     // }
        //     // }
        // }

        // // Do Topological Sorting
        // queue<char> qu;
        // cout<<" push in Queue ";
        // for(auto d: inDegree){
        //     cout<<d.first <<" "<<d.second<<" ";
        //     if(d.second == 0){
        //         qu.push(d.first);
                
        //     }
        // }
        // cout<<qu.size()<<" queue size ";

        // string ans = "";
        // while(!qu.empty()){
        //     int sz = qu.size();
        //     for(int i=0;i<sz;i++){
        //         char ch = qu.front(); qu.pop();
        //         ans += ch;
        //         for(auto end : graph[ch]){
        //             inDegree[end]--;
        //             if(inDegree[end] == 0){
        //                 qu.push(end);
        //             }
        //         }
        //     }
        // }

        // if(ans.size() == inDegree.size()){
        //     return ans;
        // }
        // return "";

    }
};
```

## Attempt 5 · 2023-04-29 15:22 IST · Wrong Answer · C++

[submission 941480449](https://leetcode.com/submissions/detail/941480449/) · tests 124/127

Failing input:

```text
["z","z"]
```

Expected:

```text
"z"
```

Your output:

```text
""
```

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {

        unordered_map<char, int> indegree;
        for(auto word : words){
            for(auto ch : word)
                indegree[ch] =0;
        }
        unordered_map<char, vector<char>> adj;
        // create a graph between chars
        for(int i=1;i<words.size();i++){
            // compare dict[i-] & dict[i]
            string s1 = words[i-1], s2 = words[i];
            int len = min(s1.size(),s2.size());
            bool flag = false;
            for(int j=0;j<len;j++){
                // build graph
                // store indegrees
                if(s1[j] != s2[j]){
                    adj[s1[j]].push_back(s2[j]);
                    indegree[s2[j]]++;
                    flag=true;
                    break;
                }
            }
            if(!flag){
                return "";
            }
        }
        queue<char> qu;
        // fill initial nodes with indegree 0
        for(auto &it : indegree){
            if(it.second == 0)
                qu.push(it.first);
        }
        // apply toposort
        string ans="";
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                char node = qu.front(); qu.pop();
                ans += node;
                for(auto &it: adj[node]){
                    indegree[it]--;
                    if(indegree[it]==0) qu.push(it);
                }
            }
        }
        if(ans.size() != indegree.size())
            return "";
        return ans;

        // map<char, vector<char>> graph;
        // map<char, int> inDegree;

        // for(auto word : words){
        //     for(auto ch : word){
        //         inDegree[ch]=0;
        //     }
        // }

        // // Build Graph
        // for(int i=1;i<words.size();i++){
        //     string pre = words[i-1];
        //     string curr = words[i];
        //     int j = 0;

        //     // OPTIMIZE this 

        //     if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
        //         return "";
        //     }
        //     for(int j=0;j< min(pre.size(), curr.size()) ; j++){
        //         if(pre[j] != curr[j]){
        //             graph[pre[j]].push_back(curr[j]);
        //             inDegree[curr[j]]++;
        //             break;
        //         }
        //     }

        //     // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
        //     //     j++;
        //     // }
        //     // if(j<pre.size() && j==curr.size()) return "";
        //     // if(j<curr.size() && j<pre.size()){
        //     //     graph[pre[j]].push_back(curr[j]);
        //     //     inDegree[curr[j]]++;
        //     //     // if(inDegree.count(pre[j]) == 0){
        //     //     //     inDegree[pre[j]]=0;
        //     //     // }
        //     // }
        // }

        // // Do Topological Sorting
        // queue<char> qu;
        // cout<<" push in Queue ";
        // for(auto d: inDegree){
        //     cout<<d.first <<" "<<d.second<<" ";
        //     if(d.second == 0){
        //         qu.push(d.first);
                
        //     }
        // }
        // cout<<qu.size()<<" queue size ";

        // string ans = "";
        // while(!qu.empty()){
        //     int sz = qu.size();
        //     for(int i=0;i<sz;i++){
        //         char ch = qu.front(); qu.pop();
        //         ans += ch;
        //         for(auto end : graph[ch]){
        //             inDegree[end]--;
        //             if(inDegree[end] == 0){
        //                 qu.push(end);
        //             }
        //         }
        //     }
        // }

        // if(ans.size() == inDegree.size()){
        //     return ans;
        // }
        // return "";

    }
};
```

## Attempt 6 · 2023-04-29 15:23 IST · Wrong Answer · C++

[submission 941480942](https://leetcode.com/submissions/detail/941480942/) · tests 125/127

Failing input:

```text
["wrt","wrtkj"]
```

Expected:

```text
"jkrtw"
```

Your output:

```text
""
```

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {

        unordered_map<char, int> indegree;
        for(auto word : words){
            for(auto ch : word)
                indegree[ch] =0;
        }
        unordered_map<char, vector<char>> adj;
        // create a graph between chars
        for(int i=1;i<words.size();i++){
            // compare dict[i-] & dict[i]
            string s1 = words[i-1], s2 = words[i];
            int len = min(s1.size(),s2.size());
            bool flag = false;
            for(int j=0;j<len;j++){
                // build graph
                // store indegrees
                if(s1[j] != s2[j]){
                    adj[s1[j]].push_back(s2[j]);
                    indegree[s2[j]]++;
                    flag=true;
                    break;
                }
            }
            if(!flag && s1.size() != s2.size()){
                return "";
            }
        }
        queue<char> qu;
        // fill initial nodes with indegree 0
        for(auto &it : indegree){
            if(it.second == 0)
                qu.push(it.first);
        }
        // apply toposort
        string ans="";
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                char node = qu.front(); qu.pop();
                ans += node;
                for(auto &it: adj[node]){
                    indegree[it]--;
                    if(indegree[it]==0) qu.push(it);
                }
            }
        }
        if(ans.size() != indegree.size())
            return "";
        return ans;

        // map<char, vector<char>> graph;
        // map<char, int> inDegree;

        // for(auto word : words){
        //     for(auto ch : word){
        //         inDegree[ch]=0;
        //     }
        // }

        // // Build Graph
        // for(int i=1;i<words.size();i++){
        //     string pre = words[i-1];
        //     string curr = words[i];
        //     int j = 0;

        //     // OPTIMIZE this 

        //     if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
        //         return "";
        //     }
        //     for(int j=0;j< min(pre.size(), curr.size()) ; j++){
        //         if(pre[j] != curr[j]){
        //             graph[pre[j]].push_back(curr[j]);
        //             inDegree[curr[j]]++;
        //             break;
        //         }
        //     }

        //     // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
        //     //     j++;
        //     // }
        //     // if(j<pre.size() && j==curr.size()) return "";
        //     // if(j<curr.size() && j<pre.size()){
        //     //     graph[pre[j]].push_back(curr[j]);
        //     //     inDegree[curr[j]]++;
        //     //     // if(inDegree.count(pre[j]) == 0){
        //     //     //     inDegree[pre[j]]=0;
        //     //     // }
        //     // }
        // }

        // // Do Topological Sorting
        // queue<char> qu;
        // cout<<" push in Queue ";
        // for(auto d: inDegree){
        //     cout<<d.first <<" "<<d.second<<" ";
        //     if(d.second == 0){
        //         qu.push(d.first);
                
        //     }
        // }
        // cout<<qu.size()<<" queue size ";

        // string ans = "";
        // while(!qu.empty()){
        //     int sz = qu.size();
        //     for(int i=0;i<sz;i++){
        //         char ch = qu.front(); qu.pop();
        //         ans += ch;
        //         for(auto end : graph[ch]){
        //             inDegree[end]--;
        //             if(inDegree[end] == 0){
        //                 qu.push(end);
        //             }
        //         }
        //     }
        // }

        // if(ans.size() == inDegree.size()){
        //     return ans;
        // }
        // return "";

    }
};
```

## Attempt 7 · 2023-04-29 15:24 IST · Accepted · C++

[submission 941481149](https://leetcode.com/submissions/detail/941481149/) · tests 127/127 · runtime 10 ms (beats 6.3%)

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {

        unordered_map<char, int> indegree;
        for(auto word : words){
            for(auto ch : word)
                indegree[ch] =0;
        }
        unordered_map<char, vector<char>> adj;
        // create a graph between chars
        for(int i=1;i<words.size();i++){
            // compare dict[i-] & dict[i]
            string s1 = words[i-1], s2 = words[i];
            int len = min(s1.size(),s2.size());
            bool flag = false;
            for(int j=0;j<len;j++){
                // build graph
                // store indegrees
                if(s1[j] != s2[j]){
                    adj[s1[j]].push_back(s2[j]);
                    indegree[s2[j]]++;
                    flag=true;
                    break;
                }
            }
            if(!flag && s1.size() > s2.size()){
                return "";
            }
        }
        queue<char> qu;
        // fill initial nodes with indegree 0
        for(auto &it : indegree){
            if(it.second == 0)
                qu.push(it.first);
        }
        // apply toposort
        string ans="";
        while(!qu.empty()){
            int sz = qu.size();
            while(sz--){
                char node = qu.front(); qu.pop();
                ans += node;
                for(auto &it: adj[node]){
                    indegree[it]--;
                    if(indegree[it]==0) qu.push(it);
                }
            }
        }
        if(ans.size() != indegree.size())
            return "";
        return ans;

        // map<char, vector<char>> graph;
        // map<char, int> inDegree;

        // for(auto word : words){
        //     for(auto ch : word){
        //         inDegree[ch]=0;
        //     }
        // }

        // // Build Graph
        // for(int i=1;i<words.size();i++){
        //     string pre = words[i-1];
        //     string curr = words[i];
        //     int j = 0;

        //     // OPTIMIZE this 

        //     if(pre.size()> curr.size() && pre.substr(0, curr.size()) == curr){
        //         return "";
        //     }
        //     for(int j=0;j< min(pre.size(), curr.size()) ; j++){
        //         if(pre[j] != curr[j]){
        //             graph[pre[j]].push_back(curr[j]);
        //             inDegree[curr[j]]++;
        //             break;
        //         }
        //     }

        //     // while(j<pre.size() && j<curr.size() && pre[j]==curr[j]){
        //     //     j++;
        //     // }
        //     // if(j<pre.size() && j==curr.size()) return "";
        //     // if(j<curr.size() && j<pre.size()){
        //     //     graph[pre[j]].push_back(curr[j]);
        //     //     inDegree[curr[j]]++;
        //     //     // if(inDegree.count(pre[j]) == 0){
        //     //     //     inDegree[pre[j]]=0;
        //     //     // }
        //     // }
        // }

        // // Do Topological Sorting
        // queue<char> qu;
        // cout<<" push in Queue ";
        // for(auto d: inDegree){
        //     cout<<d.first <<" "<<d.second<<" ";
        //     if(d.second == 0){
        //         qu.push(d.first);
                
        //     }
        // }
        // cout<<qu.size()<<" queue size ";

        // string ans = "";
        // while(!qu.empty()){
        //     int sz = qu.size();
        //     for(int i=0;i<sz;i++){
        //         char ch = qu.front(); qu.pop();
        //         ans += ch;
        //         for(auto end : graph[ch]){
        //             inDegree[end]--;
        //             if(inDegree[end] == 0){
        //                 qu.push(end);
        //             }
        //         }
        //     }
        // }

        // if(ans.size() == inDegree.size()){
        //     return ans;
        // }
        // return "";

    }
};
```

## Attempt 8 · 2023-10-20 20:12 IST · Wrong Answer · C++

[submission 1079969864](https://leetcode.com/submissions/detail/1079969864/) · tests 81/127

Failing input:

```text
["abc","ab"]
```

Expected:

```text
""
```

Your output:

```text
"cba"
```

```cpp
class Solution {
private:
    bool topoSort(int node, vector<int> adj[], vector<int>& vis, stack<int>& s, vector<int> isCharPresent, vector<int>& pathVisited) {
        vis[node] = 1;
        pathVisited.push_back(node);

        for (auto it:adj[node]) {
            if(!vis[it]) {
                if(topoSort(it, adj, vis, s, isCharPresent, pathVisited)) {
                    return true;
                }
            } else {
                if ((std::find(pathVisited.begin(), pathVisited.end(), it)) != pathVisited.end()) {
                    return true;
                }
            }
        }
        if(isCharPresent[node]) {
            s.push(node);
        }

        pathVisited.pop_back();
        return false;
    }

public:
    string alienOrder(vector<string>& words) {
        vector<int> adj[26];
        vector<int> isCharPresent(26, 0);
        vector<int> vis(26, 0);
        bool isCyclePresent = false;

        for (int i=0;i<words.size();i++) {
            for (auto it: words[i]) 
                isCharPresent[it-'a'] = 1;
        }

        for(int i=0; i<words.size()-1; i++) {
            string str1 = words[i];
            string str2 = words[i+1];
            int m = min(str1.size(), str2.size());
            for(int j=0; j<m; j++) {
                if(str1[j] != str2[j]) {
                    adj[str1[j]-'a'].push_back(str2[j]-'a');
                    break;
                }
            }
        }

        stack<int> s;
        vector<int> pathVisited;
        for (int i=0 ;i<26 ;i++) {
            if(!vis[i]) {
                isCyclePresent = topoSort(i, adj, vis, s, isCharPresent, pathVisited);
                if(isCyclePresent)
                    break;
            }
        }

        string ans = "";
        while(!s.empty()) {
            int it = s.top();
            s.pop();
            char c = (char)(it + 'a');
            ans = ans + c;
        }
        return ans;
    }
};
```

## Attempt 9 · 2023-10-20 20:19 IST · Wrong Answer · C++

[submission 1079974102](https://leetcode.com/submissions/detail/1079974102/) · tests 84/127

Failing input:

```text
["z","z"]
```

Expected:

```text
"z"
```

Your output:

```text
""
```

```cpp
class Solution {
private:
    bool topoSort(int node, vector<int> adj[], vector<int>& vis, stack<int>& s, vector<int> isCharPresent, vector<int>& pathVisited) {
        vis[node] = 1;
        pathVisited.push_back(node);

        for (auto it:adj[node]) {
            if(!vis[it]) {
                if(topoSort(it, adj, vis, s, isCharPresent, pathVisited)) {
                    return true;
                }
            } else {
                if ((std::find(pathVisited.begin(), pathVisited.end(), it)) != pathVisited.end()) {
                    return true;
                }
            }
        }
        if(isCharPresent[node]) {
            s.push(node);
        }

        pathVisited.pop_back();
        return false;
    }

public:
    string alienOrder(vector<string>& words) {
        vector<int> adj[26];
        vector<int> isCharPresent(26, 0);
        vector<int> vis(26, 0);
        bool isCyclePresent = false;

        for (int i=0;i<words.size();i++) {
            for (auto it: words[i]) 
                isCharPresent[it-'a'] = 1;
        }

        for(int i=0; i<words.size()-1; i++) {
            string str1 = words[i];
            string str2 = words[i+1];
            int m = min(str1.size(), str2.size());
            for(int j=0; j<m; j++) {
                if(str1[j] != str2[j]) {
                    adj[str1[j]-'a'].push_back(str2[j]-'a');
                    break;
                }
                if(j==m-1) {
                    return "";
                }
            }
        }

        stack<int> s;
        vector<int> pathVisited;
        for (int i=0 ;i<26 ;i++) {
            if(!vis[i]) {
                isCyclePresent = topoSort(i, adj, vis, s, isCharPresent, pathVisited);
                if(isCyclePresent)
                    break;
            }
        }

        string ans = "";
        while(!s.empty()) {
            int it = s.top();
            s.pop();
            char c = (char)(it + 'a');
            ans = ans + c;
        }
        return ans;
    }
};
```

## Attempt 10 · 2023-10-20 21:57 IST · Wrong Answer · C++

[submission 1080029994](https://leetcode.com/submissions/detail/1080029994/) · tests 125/127

Failing input:

```text
["wrt","wrtkj"]
```

Expected:

```text
"jkrtw"
```

Your output:

```text
""
```

```cpp
class Solution {
private:

    bool topoSort(vector<int> adj[], vector<int> isCharPresent, vector<int>& ans) {
        int n = 26;
        vector<int> inDegree(26,0);
        for (int i=0;i<n;i++) {
            for(auto it:adj[i]) {
                inDegree[it]++;
            }
        }

        queue<int> q;
        int count = 0;
        for(int i=0;i<26;i++) {
            if(isCharPresent[i]) {
                count++;
                if(inDegree[i] == 0) {
                    q.push(i);
                    // char ch = ((char)i+'a');
                    // cout<<ch<< " ";
                }
            }
        }

        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            ans.push_back(curr);
            for(auto it: adj[curr]) {
                inDegree[it]--;
                if(inDegree[it] == 0) {
                    q.push(it);
                };
            }
        }
        cout<<ans.size()<<endl;
        if(count == ans.size()) {
            return false;
        }
        return true;
    }
    

public:
    string alienOrder(vector<string>& words) {
        int n = words.size();
        vector<int> isCharPresent(26,0);
        for(int i=0; i<n; i++) {
           for (auto it: words[i]) {
               isCharPresent[it-'a'] = 1;
           }
        }

        vector<int> adj[26];
        for (int i=0 ; i<n-1; i++) {
            string str1=words[i];
            string str2=words[i+1];
            int m = min(str1.size(), str2.size());
            for(int j=0; j<m; j++) {
                if(str1[j]!=str2[j]) {
                    adj[str1[j]-'a'].push_back(str2[j]-'a');
                    break;
                }
                if(j==m-1 && str1.size() != str2.size()) return "";
            }
        }
        vector<int> ans;
        if(topoSort(adj, isCharPresent, ans)) {
            return "";
        }
        string result = "";
        for (auto it:ans) {
            char c = it + 'a';
            result = result + c;
        }
        return result;
    }
};
```

## Attempt 11 · 2023-10-20 22:01 IST · Accepted · C++

[submission 1080032283](https://leetcode.com/submissions/detail/1080032283/) · tests 127/127 · runtime 6 ms (beats 8.2%)

```cpp
class Solution {
private:

    bool topoSort(vector<int> adj[], vector<int> isCharPresent, vector<int>& ans) {
        int n = 26;
        vector<int> inDegree(26,0);
        for (int i=0;i<n;i++) {
            for(auto it:adj[i]) {
                inDegree[it]++;
            }
        }

        queue<int> q;
        int count = 0;
        for(int i=0;i<26;i++) {
            if(isCharPresent[i]) {
                count++;
                if(inDegree[i] == 0) {
                    q.push(i);
                    // char ch = ((char)i+'a');
                    // cout<<ch<< " ";
                }
            }
        }

        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            ans.push_back(curr);
            for(auto it: adj[curr]) {
                inDegree[it]--;
                if(inDegree[it] == 0) {
                    q.push(it);
                };
            }
        }
        cout<<ans.size()<<endl;
        if(count == ans.size()) {
            return false;
        }
        return true;
    }
    

public:
    string alienOrder(vector<string>& words) {
        int n = words.size();
        vector<int> isCharPresent(26,0);
        for(int i=0; i<n; i++) {
           for (auto it: words[i]) {
               isCharPresent[it-'a'] = 1;
           }
        }

        vector<int> adj[26];
        for (int i=0 ; i<n-1; i++) {
            string str1=words[i];
            string str2=words[i+1];
            int m = min(str1.size(), str2.size());
            for(int j=0; j<m; j++) {
                if(str1[j]!=str2[j]) {
                    adj[str1[j]-'a'].push_back(str2[j]-'a');
                    break;
                }
                if(j==m-1 && str1.size() > str2.size()) return "";
            }
        }
        vector<int> ans;
        if(topoSort(adj, isCharPresent, ans)) {
            return "";
        }
        string result = "";
        for (auto it:ans) {
            char c = it + 'a';
            result = result + c;
        }
        return result;
    }
};
```

## Attempt 12 · 2023-11-17 23:01 IST · Accepted · Python3

[submission 1100930154](https://leetcode.com/submissions/detail/1100930154/) · tests 127/127 · runtime 41 ms (beats 3.6%)

```python
class Solution:
    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])
```

## Attempt 13 · 2023-11-17 23:07 IST · Wrong Answer · Python3

[submission 1100933431](https://leetcode.com/submissions/detail/1100933431/) · tests 124/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)
                    in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()
            alien_order.append(c)
            for d in adj_list[c]:
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 14 · 2023-11-17 23:09 IST · Wrong Answer · Python3

[submission 1100934975](https://leetcode.com/submissions/detail/1100934975/) · tests 124/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)
                    in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()
            alien_order.append(c)
            for d in adj_list[c]:
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 15 · 2023-11-17 23:10 IST · Wrong Answer · Python3

[submission 1100935228](https://leetcode.com/submissions/detail/1100935228/) · tests 124/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)
                    in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()
            alien_order.append(c)
            for d in adj_list[c]:
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 16 · 2023-11-17 23:10 IST · Wrong Answer · Python3

[submission 1100935727](https://leetcode.com/submissions/detail/1100935727/) · tests 124/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)
                    in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()
            alien_order.append(c)
            for d in adj_list[c]:
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        print(alien_order, in_degree)
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 17 · 2023-11-17 23:12 IST · Wrong Answer · Python3

[submission 1100936608](https://leetcode.com/submissions/detail/1100936608/) · tests 124/127

Failing input:

```text
["ac","ab","zc","zb"]
```

Expected:

```text
"acbz"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)
                    in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()

            alien_order.append(c)
            print('adding', c)
            for d in adj_list[c]:
                print('visitng', d)
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        print(alien_order, in_degree)
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 18 · 2023-11-17 23:13 IST · Wrong Answer · Python3

[submission 1100937488](https://leetcode.com/submissions/detail/1100937488/) · tests 126/127

Failing input:

```text
["wrt","wrf","er","ett","rftt","te"]
```

Expected:

```text
"wertf"
```

Your output:

```text
""
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    if d not in adj_list[c]:
                        adj_list[c].add(d)
                        in_degree[d] +=1
                        break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()

            alien_order.append(c)
            print('adding', c)
            for d in adj_list[c]:
                print('visitng', d)
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        print(alien_order, in_degree)
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 19 · 2023-11-17 23:14 IST · Accepted · Python3

[submission 1100937709](https://leetcode.com/submissions/detail/1100937709/) · tests 127/127 · runtime 45 ms (beats 3.6%)

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    if d not in adj_list[c]:
                        adj_list[c].add(d)
                        in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()

            alien_order.append(c)
            print('adding', c)
            for d in adj_list[c]:
                print('visitng', d)
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        print(alien_order, in_degree)
        if len(alien_order) < len(in_degree):
            return ""

        return "".join(alien_order)
```

## Attempt 20 · 2023-11-28 22:20 IST · Wrong Answer · Python3

[submission 1108286839](https://leetcode.com/submissions/detail/1108286839/) · tests 57/127

Failing input:

```text
["z","x","a","zb","zx"]
```

Expected:

```text
""
```

Your output:

```text
"b"
```

```python
class Solution:
    def alienOrder1(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}

        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    adj_list[c].add(d)

                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        # print(adj_list)

        # topological sorting with cycle detection
        def dfs(c):
            if c in visited:
                return visited[c] 

            visited[c] =False
            for next_c in adj_list[c]:
                if not dfs(next_c): return False # cycle detected
            
            visited[c] = True
            result.append(c)
            return True

        result = []
        for c in set(char for word in words for char in word):
            if not dfs(c): return ""

        return "".join(result[::-1])

    def alienOrder(self, words: List[str]) -> str:
        adj_list = defaultdict(set)
        visited= {}
        in_degree = {char:0 for word in words for char in word}
        for first_word, second_word in zip(words, words[1:]):
            for c,d in zip(first_word, second_word):
                if c!=d:
                    if d not in adj_list[c]:
                        adj_list[c].add(d)
                        in_degree[d] +=1
                    break
            else:
                if len(first_word) > len(second_word):
                    return ""

        # run dfs to do topological sorting
        print(adj_list, in_degree)
        queue = deque([c for c in in_degree if in_degree[c] ==0])

        alien_order = []
        while queue:
            c = queue.popleft()

            alien_order.append(c)
            print('adding', c)
            for d in adj_list[c]:
                print('visitng', d)
                in_degree[d] -=1
                if in_degree[d] ==0:
                    queue.append(d)
        
        print(alien_order, in_degree)
        # if len(alien_order) < len(in_degree):
        #     return ""

        return "".join(alien_order)

    def alienOrder3(self, words: List[str]) -> str:
        # 1. create  adj list
        adjList= defaultdict(set)
        indegree = Counter({ch:0 for word in words for ch in word })
        for word1, word2 in zip(words, words[1:]):
            for c, d in zip(word1, word2):
                if c!=d:
                    if d not in adjList[c]:
                        adjList[c].add(d)
                        indegree[d] +=1

                    break

            else:
                if len(word1) > len(word2):
                    return ''

        #2. topological sorting
        # find all nodes with indegree 0 
        # cyclic graph
        queue = deque([ch for ch in indegree if indegree[ch]==0])

        output = []
        while queue:
            ch = queue.popleft()
            output.append(ch)

            for d in adjList[c]:
                indegree[d] -=1
                if indegree[d] ==0:
                    queue.append(d)

        return "".join(output)
```
