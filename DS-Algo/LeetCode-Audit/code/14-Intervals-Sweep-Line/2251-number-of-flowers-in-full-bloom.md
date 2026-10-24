# 2251. Number of Flowers in Full Bloom

[Problem](https://leetcode.com/problems/number-of-flowers-in-full-bloom/) · Hard · Intervals & Sweep Line → Sweep line / binary search

LeetCode tags: array, hash-table, binary-search, sorting, prefix-sum, ordered-set

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2025-04-16 22:18 IST · Accepted · C++

[submission 1608729211](https://leetcode.com/submissions/detail/1608729211/) · tests 53/53 · runtime 107 ms (beats 17.6%)

```cpp
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        map<int,int> activeFlowers;

        for (auto flower : flowers) {
            int l = flower[0];
            int r = flower[1];

            activeFlowers[l]++;
            activeFlowers[r+1]--;
        }
        // Precompute the cumulative sum of active flowers
    int cumulative = 0;
    for (auto& [time, count] : activeFlowers) {
        cumulative += count;
        count = cumulative; // Update the map to store the cumulative sum
    }
        vector <int> ans;
        for (auto pos : people) {
            // find interval for person on pos
            int count = 0;
            auto itr = activeFlowers.lower_bound(pos);
            // if itr is end
            if (itr != activeFlowers.end()) {
                if (itr->first == pos) {
                    count = itr->second;
                } else {
                    if (itr != activeFlowers.begin()) {
                        itr--;
                        count = itr->second;
                    }
                }
            } else {
                itr--;
                count = itr->second;
            }
            ans.push_back(count);
        }

        return ans;
    }
};
```

## Attempt 2 · 2025-04-16 22:43 IST · Accepted · C++

[submission 1608755716](https://leetcode.com/submissions/detail/1608755716/) · tests 53/53 · runtime 102 ms (beats 19.2%)

```cpp
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        map<int,int> activeFlowers;

        for (auto flower : flowers) {
            int l = flower[0];
            int r = flower[1];

            activeFlowers[l]++;
            activeFlowers[r+1]--;
        }
        // Precompute the cumulative sum of active flowers
        int cumulative = 0;
        for (auto& [time, count] : activeFlowers) {
            cumulative += count;
            count = cumulative; // Update the map to store the cumulative sum
        }
        vector <int> ans;
        for (auto pos : people) {
            // find interval for person on pos
            int count = 0;
            auto itr = activeFlowers.lower_bound(pos);
            // if itr is end
            if (itr != activeFlowers.end()) {
                if (itr->first == pos) {
                    count = itr->second;
                } else {
                    if (itr != activeFlowers.begin()) {
                        itr--;
                        count = itr->second;
                    }
                }
            } else {
                itr--;
                count = itr->second;
            }
            ans.push_back(count);
        }

        return ans;
    }
};
```
