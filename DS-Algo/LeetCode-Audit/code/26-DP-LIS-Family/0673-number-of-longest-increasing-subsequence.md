# 673. Number of Longest Increasing Subsequence

[Problem](https://leetcode.com/problems/number-of-longest-increasing-subsequence/) · Medium · DP: LIS Family → LIS with counts

LeetCode tags: array, dynamic-programming, binary-indexed-tree, segment-tree, longest-increasing-subsequence

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-03 01:22 IST · Accepted · C++

[submission 926821178](https://leetcode.com/submissions/detail/926821178/) · tests 223/223 · runtime 172 ms (beats 5.1%)

```cpp
class Solution {
public:
    
    int findNumberOfLIS(vector<int>& nums) {
        const int n = nums.size();
        vector<int> lis(n,1);  // stores length of longest sequence till i-th position
        vector<int> count(n,1);  // stores count of longest sequence of length lis[i]
        int maxLen = 1;  // maximum length of lis
		
		// O(N^2) DP Solution
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    if(lis[j] + 1 > lis[i]){ // strictly increasing
                        lis[i] = lis[j] + 1;
                        count[i] = count[j];
                    } 
					 // this means there are more subsequences of same length ending at length lis[i]
					else if(lis[j]+1 == lis[i]){ 
                        count[i] += count[j];
                    }
                }
            }
            maxLen = max(maxLen,lis[i]);
        }
        
        int numOfLIS = 0;
        // count all the subseq of length maxLen
        for(int i=0;i<n;i++){
            if(lis[i]==maxLen)
                numOfLIS += count[i];
        }
            
        return numOfLIS;
    }
};
```
