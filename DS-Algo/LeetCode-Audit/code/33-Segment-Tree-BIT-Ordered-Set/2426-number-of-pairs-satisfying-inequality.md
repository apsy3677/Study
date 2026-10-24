# 2426. Number of Pairs Satisfying Inequality

[Problem](https://leetcode.com/problems/number-of-pairs-satisfying-inequality/) · Hard · Segment Tree / BIT / Ordered Set → BIT / merge-sort counting

LeetCode tags: array, binary-search, divide-and-conquer, binary-indexed-tree, segment-tree, merge-sort, ordered-set

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-24 14:31 IST · Accepted · C++

[submission 921202242](https://leetcode.com/submissions/detail/921202242/) · tests 61/61 · runtime 394 ms (beats 23.8%)

```cpp
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        long long ans =0;
        if(nums1.size() <=1){
            return 0;
        }
        vector<int> arr(nums1.size());
        for(int i=0;i<nums1.size();i++){
            arr[i] = nums1[i] - nums2[i];
        }

        mergesort(ans, 0, nums1.size() -1, arr, diff);

        return ans;
    }

    void countAndMerge (long long &ans, int low, int mid, int high, vector<int> &arr, int diff){
        int l= low, r= mid+1;

        while(l<= mid && r<=high){
            if(arr[l] <= arr[r]+diff){
                ans += (high - r +1); // arr[l] will be smaller for rest of elemnts + diff as well which is high to r
                l++;
            }
            else{
                r++;
            }
        }
        sort(arr.begin() + low, arr.begin() +high +1);
    }

    void mergesort(long long &ans, int low, int high, vector<int> &arr, int diff){
        if(low >= high){
            return;
        }
        int mid = low + (high-low)/2;

        mergesort(ans, low, mid, arr, diff);
        mergesort(ans, mid+1, high, arr, diff);

        countAndMerge(ans, low, mid, high, arr, diff);
    }
};
```
