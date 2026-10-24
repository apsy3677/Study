# 2215. Find the Difference of Two Arrays

[Problem](https://leetcode.com/problems/find-the-difference-of-two-arrays/) · Easy · Arrays, Hashing & Sorting → Sets

LeetCode tags: array, hash-table

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-09-08 16:49 IST · Accepted · C++

[submission 1043842772](https://leetcode.com/submissions/detail/1043842772/) · tests 202/202 · runtime 470 ms (beats 5.0%)

```cpp
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        set<int> count1, count2;
        for (int i=0;i<nums1.size();i++) {
            count1.insert(nums1[i]);
        }

        for (int i=0;i<nums2.size();i++) {
            count2.insert(nums2[i]);
        }
        vector<vector<int>> result;
        set<int> dist1, dist2;
        for(int i=0;i<nums1.size();i++) {
            if(std::find(count2.begin(), count2.end(), nums1[i]) == count2.end()) {
                dist1.insert(nums1[i]);
            }
        }
        for (int i=0; i<nums2.size(); i++) {
            if(std::find(count1.begin(), count1.end(), nums2[i]) == count1.end()) {
                dist2.insert(nums2[i]);
            }
        }
        vector<int> vc1, vc2;
        vc1.assign(dist1.begin(), dist1.end());
        vc2.assign(dist2.begin(), dist2.end());
        result.push_back(vc1);
        result.push_back(vc2);
        return result;
    }
};
```
