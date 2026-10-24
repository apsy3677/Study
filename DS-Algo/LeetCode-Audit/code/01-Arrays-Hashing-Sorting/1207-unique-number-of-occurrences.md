# 1207. Unique Number of Occurrences

[Problem](https://leetcode.com/problems/unique-number-of-occurrences/) · Easy · Arrays, Hashing & Sorting → Counting

LeetCode tags: array, hash-table

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-08 23:04 IST · Accepted · C++

[submission 1044102868](https://leetcode.com/submissions/detail/1044102868/) · tests 67/67 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        map<int, int> count;
        map<int, int>::iterator it;
        for(int i=0;i<arr.size();i++) {
            it = count.find(arr[i]);
            if(it == count.end()) {
                count.insert(pair<int,int>(arr[i], 1));
            } else {
                it->second = it->second + 1;
            }
        }
        set<int> unique;
        it=count.begin();
        while(it != count.end()) {
            unique.insert(it->second);
            it++;
        }
        return unique.size() == count.size();
    }
};
```
