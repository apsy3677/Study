# 1101. The Earliest Moment When Everyone Become Friends

[Problem](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/) · Medium · Graph: Union-Find → Sort by time + DSU

LeetCode tags: array, union-find, sorting

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-24 19:27 IST · Accepted · C++

[submission 921317555](https://leetcode.com/submissions/detail/921317555/) · tests 67/67 · runtime 32 ms (beats 5.2%)

```cpp
class UnionFind {
public:
    UnionFind(int sz) : root(sz), rank(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

private:
    vector<int> root;
    vector<int> rank;
};

class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
        /// use union find and check if all of the elements are connected at which time      
        sort(logs.begin(), logs.end());
        UnionFind uf(n);
        int components = n;
        for(int i=0;i<logs.size();i++){
            int time = logs[i][0];
            int x = logs[i][1];
            int y = logs[i][2];

            
            if(uf.find(x) != uf.find(y)){
                uf.unionSet(x,y);
                components--;
            }
            

            if(components == 1){
                return time;
            }
        }
        return -1;
    }
};
```
