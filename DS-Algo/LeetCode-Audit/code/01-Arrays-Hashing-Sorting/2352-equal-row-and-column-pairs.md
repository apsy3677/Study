# 2352. Equal Row and Column Pairs

[Problem](https://leetcode.com/problems/equal-row-and-column-pairs/) · Medium · Arrays, Hashing & Sorting → Row hash count

LeetCode tags: array, hash-table, matrix, simulation

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-09 00:19 IST · Accepted · C++

[submission 1044163612](https://leetcode.com/submissions/detail/1044163612/) · tests 78/78 · runtime 68 ms (beats 34.8%)

```cpp
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        map<vector<int>, int> count;
        for(auto i: grid) {
            count[i]++;
        }
        int n=grid.size(), result=0;
        for(int j=0;j<n;j++) {
            vector<int> c;
            for(int i=0;i<n;i++) {
                c.push_back(grid[i][j]);
            }
            if(count.find(c)!=count.end()) {
                result = result + count[c];
            }
        }
        return result;
    }
};
```
