# 1202. Smallest String With Swaps

[Problem](https://leetcode.com/problems/smallest-string-with-swaps/) · Medium · Graph: Union-Find → Components + sort

LeetCode tags: array, hash-table, string, depth-first-search, breadth-first-search, union-find, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-25 01:56 IST · Accepted · C++

[submission 921506988](https://leetcode.com/submissions/detail/921506988/) · tests 36/36 · runtime 307 ms (beats 5.0%)

```cpp
// class Solution {
// public:
//     string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
//         int n = s.size();
//         vector<vector<int>> graph(n+1);

//         for(auto pair : pairs){
//             graph[pair[0]].push_back(pair[1]);
//             graph[pair[1]].push_back(pair[0]);
//         }
//             cout<<"graph ";

//         for(auto x : graph){
//             for(auto c: x){
//                 cout<<c<<" | ";
//             }
//         }
//         vector<bool> visited(n, false);
//         for(int i=0;i<n;i++){
//             if(!visited[i]){
//                 vector<int> indexes;
//                 vector<char> chars;
//                 // Populate these indexes
//                 dfs(s, i, graph, indexes, chars, visited);

//                 sort(indexes.begin(), indexes.end());
//                 sort(chars.begin(), chars.end());

//                 // replace them in string
//                 for(int idx = 0;idx<chars.size();i++){
//                     s[indexes[idx]] = chars[idx];
//                 }
//             }
//         }
//         return s;
//     }

//     void dfs(string &s, int i, vector<vector<int>> &graph, vector<int> &indexes, vector<char> &chars, vector<bool> &visited){
//         if(i<0 || i>= graph.size()) return;
//         indexes.push_back(i);
//         chars.push_back(s[i]);
//         visited[i] = true;
//         cout<<" i "<<i<<"::";
//         for(auto next: graph[i]){
//             cout<<" child "<<next<< " - ";
//             if(!visited[next]){
                
//                 cout<<" child dfs"<<next<< " ";
//                 dfs(s, next,graph,indexes,chars,visited);
//             }
//         }
//         return;
//     }
// };

class Solution {
public:
    // Maximum number of vertices
    static const int N = 100001;
    vector<int> adj[N];
    bool visited[N];
    
    void DFS(string& s, int vertex, vector<char>& characters, vector<int>& indices) {
        // Add the character and index to the list
        characters.push_back(s[vertex]);
        indices.push_back(vertex);
        
        visited[vertex] = true;
        
        // Traverse the adjacents
        for (int adjacent : adj[vertex]) {
            if (!visited[adjacent]) {
                DFS(s, adjacent, characters, indices);
            }
        }
    }
    
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        // Build the adjacency list
        for (vector<int> edge : pairs) {
            int source = edge[0];
            int destination = edge[1];
            
            // Undirected edge
            adj[source].push_back(destination);
            adj[destination].push_back(source);
        }
        
        for (int vertex = 0; vertex < s.size(); vertex++) {
            // If not covered in the DFS yet
            if (!visited[vertex]) {
                vector<char> characters;
                vector<int> indices;
                
                DFS(s, vertex, characters, indices);
                // Sort the list of characters and indices
                sort(characters.begin(), characters.end());
                sort(indices.begin(), indices.end());

                // Store the sorted characters corresponding to the index
                for (int index = 0; index < characters.size(); index++) {
                    s[indices[index]] = characters[index];
                }
            }
        }
        
        return s;
    }
};
```
