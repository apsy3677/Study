# 560. Subarray Sum Equals K

[Problem](https://leetcode.com/problems/subarray-sum-equals-k/) · Medium · Prefix Sum & Difference Array → Prefix sum + hash map

LeetCode tags: array, hash-table, prefix-sum

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-05-22 11:21 IST · Accepted · C++

[submission 954905270](https://leetcode.com/submissions/detail/954905270/) · tests 93/93 · runtime 108 ms (beats 20.2%)

```cpp
class Solution {
public:
    int subarraySum(vector<int>& arr, int k) {
        int currSum = 0, ind =0;
        int ans =0;
        unordered_map<int, int> seen;
        seen[0] = 1;
        for(auto num : arr){
            currSum += num;

            if(seen.find(currSum-k) != seen.end()){
                ans += seen[currSum-k];
            }
            seen[currSum]++;
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-22 11:26 IST · Accepted · C++

[submission 954907802](https://leetcode.com/submissions/detail/954907802/) · tests 93/93 · runtime 98 ms (beats 20.4%)

```cpp
class Solution {
public:
    int subarraySum(vector<int>& arr, int k) {
        int currSum = 0, ind =0;
        int ans =0;
        unordered_map<int, int> seen;
        // seen[0] = 1; // it is base case if k matches the arr[i]
        for(auto num : arr){
            currSum += num;
            if(currSum == k) ans++;
            if(seen.find(currSum-k) != seen.end()){
                ans += seen[currSum-k];
            }
            seen[currSum]++;
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-12-05 00:30 IST · Accepted · Python3

[submission 1112379899](https://leetcode.com/submissions/detail/1112379899/) · tests 93/93 · runtime 282 ms (beats 5.9%)

```python
class Solution:
    def subarraySum1(self, nums: List[int], k: int) -> int:
        '''
        approach 1- find all subarrays using two loops. the first loop gives the end range and second the start range - that is find all subarrays ending in i , then i+1 and so on

        approach 2- if thre prefix sum at some position is x and at some position y 
        then there is a subarray only if there exists y-k prefix sum entry 
        and the count of that y-k will tell how many subarrays exists with that sum k


        '''
        count = 0
        for i in range(len(nums)):
            sum = 0
            for j in range(i, len(nums)):
                sum += nums[j]
                if sum == k:
                    count+=1
        
        return count

    def subarraySum(self, nums: List[int], k: int) -> int:
        '''
        prefix_sum_counter to keep track of prefixSums and count 
        '''
        prefixSum = 0
        prefix_sum_count = Counter({0:1})
        subarray_count =0
        for num in nums:
            prefixSum += num
            if (prefixSum - k) in prefix_sum_count:
                subarray_count += prefix_sum_count[prefixSum-k]
            prefix_sum_count[prefixSum] += 1    
        return subarray_count
```

## Attempt 4 · 2025-07-07 23:07 IST · Accepted · C++

[submission 1689878099](https://leetcode.com/submissions/detail/1689878099/) · tests 93/93 · runtime 33 ms (beats 90.5%)

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSums = {{0, 1}}; // Empty subarray with sum 0
        int sum = 0;
        int count = 0;
        
        for (int num : nums) {
            sum += num;
            
            // If (sum - k) exists in prefixSums, it means we have subarrays ending at current position with sum k
            if (prefixSums.count(sum - k)) {
                count += prefixSums[sum - k];
            }
            
            prefixSums[sum]++;
        }
        
        return count;
    }
};
```
