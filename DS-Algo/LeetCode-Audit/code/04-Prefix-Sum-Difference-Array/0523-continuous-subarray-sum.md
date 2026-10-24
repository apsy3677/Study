# 523. Continuous Subarray Sum

[Problem](https://leetcode.com/problems/continuous-subarray-sum/) · Medium · Prefix Sum & Difference Array → Prefix mod + hash map

LeetCode tags: array, hash-table, math, prefix-sum, pigeonhole-principle

Attempts since Mar 2023: 11 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-24 08:13 IST · Accepted · Python3

[submission 1105195149](https://leetcode.com/submissions/detail/1105195149/) · tests 99/99 · runtime 920 ms (beats 5.2%)

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False
```

## Attempt 2 · 2024-01-28 06:58 IST · Wrong Answer · Python3

[submission 1158719599](https://leetcode.com/submissions/detail/1158719599/) · tests 70/99

Failing input:

```text
[5,0,0,0]
3
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
                else:
                    mod_counter[remainder] = i
        return False
```

## Attempt 3 · 2024-01-28 06:59 IST · Accepted · Python3

[submission 1158719802](https://leetcode.com/submissions/detail/1158719802/) · runtime 836 ms

_Code not returned by LeetCode._

## Attempt 4 · 2024-01-28 06:59 IST · Wrong Answer · Python3

[submission 1158719929](https://leetcode.com/submissions/detail/1158719929/) · tests 70/99

Failing input:

```text
[5,0,0,0]
3
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
                else:
                    mod_counter[remainder] = i
        return False
```

## Attempt 5 · 2024-01-28 07:02 IST · Output Limit Exceeded · Python3

[submission 1158721132](https://leetcode.com/submissions/detail/1158721132/) · tests 79/99

Failing input:

```text
[237,237,10,117,138,274,205,130,370,333,409,243,52,397,318,261,204,189,503,20,479,481,365,238,327,514,275,452,444,341,148,325,14,269,493,265,194,198,177,522,80,500,192,327,271,266,225,31,228,249,364,375,113,388,148,102,87,311,98,508,28,463,78,47,2,452,80,515,89,413,214,76,432,481,100,334,388,197,424,136,132,122,371,246,228,87,173,497,461,198,123,479,469,252,21,81,473,159,41,459,155,404,15,16,28,35 ... [3395 more chars]
```

Expected:

```text
false
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False
```

## Attempt 6 · 2024-01-28 07:03 IST · Accepted · Python3

[submission 1158721195](https://leetcode.com/submissions/detail/1158721195/) · tests 99/99 · runtime 807 ms (beats 5.2%)

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False
```

## Attempt 7 · 2024-02-04 10:18 IST · Wrong Answer · Python3

[submission 1165514876](https://leetcode.com/submissions/detail/1165514876/) · tests 84/99

Failing input:

```text
[2,4,3]
6
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        for start in range(len(nums)):
            sum = 0
            for indx in range(start, len(nums)):
                sum += nums[indx]
                if indx - start > 1 and sum % k == 0:
                    return True
        return False
```

## Attempt 8 · 2024-02-04 10:20 IST · Wrong Answer · Python3

[submission 1165515906](https://leetcode.com/submissions/detail/1165515906/) · tests 87/99

Failing input:

```text
[0]
1
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] >= 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False

    def checkSubarraySum1(self, nums: List[int], k: int) -> bool:
        for start in range(len(nums)):
            sum = 0
            for indx in range(start, len(nums)):
                sum += nums[indx]
                # print(sum)
                if indx - start >= 1 and sum % k == 0:
                    return True
        return False
```

## Attempt 9 · 2024-02-04 10:20 IST · Wrong Answer · Python3

[submission 1165516092](https://leetcode.com/submissions/detail/1165516092/) · tests 92/99

Failing input:

```text
[1,0]
2
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:0}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] >= 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False

    def checkSubarraySum1(self, nums: List[int], k: int) -> bool:
        for start in range(len(nums)):
            sum = 0
            for indx in range(start, len(nums)):
                sum += nums[indx]
                # print(sum)
                if indx - start >= 1 and sum % k == 0:
                    return True
        return False
```

## Attempt 10 · 2024-02-04 10:21 IST · Time Limit Exceeded · Python3

[submission 1165516402](https://leetcode.com/submissions/detail/1165516402/) · tests 94/99

Failing input:

```text
[1617,4991,12564,3903,8881,19078,8583,1717,1829,13921,15174,4107,10415,15481,7904,1991,19477,5030,160,14071,16761,14050,8658,13497,15733,5139,18214,9705,13974,6813,4110,3072,1789,1663,1614,1293,6646,18194,17468,5979,19177,3269,2801,9339,8020,5700,18023,6344,15187,1236,11412,9714,15314,14423,1026,5194,14786,1204,1067,10848,11445,7689,10208,928,10631,16237,11890,15187,13066,488,16048,17340,17055,185 ... [544096 more chars]
```

Expected:

```text
false
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:-1}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] > 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        for start in range(len(nums)):
            sum = 0
            for indx in range(start, len(nums)):
                sum += nums[indx]
                # print(sum)
                if indx - start >= 1 and sum % k == 0:
                    return True
        return False
```

## Attempt 11 · 2024-02-04 10:23 IST · Wrong Answer · Python3

[submission 1165517657](https://leetcode.com/submissions/detail/1165517657/) · tests 73/99

Failing input:

```text
[1,0]
2
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if k == 0:
            # Special handling when k is 0
            cum_sum = 0
            for num in nums:
                cum_sum += num
                if cum_sum == 0:
                    return True
            return False

        remainder_map = {0: -1}  # Initialize with remainder 0 at index -1
        cum_sum = 0
        for i, num in enumerate(nums):
            cum_sum += num
            remainder = cum_sum % k

            # don;t updat ethe value of the index 
            # so that difference is maximum possible
            if remainder in remainder_map:
                if i - remainder_map[remainder] > 1:
                    return True
            else:
                remainder_map[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        # mod of k will be same in the prefix sums
        prefixSum = 0
        prefixSums = []
        
        for num in nums:
            prefixSum += num
            prefixSums.append(prefixSum)

        mod_counter = {0: -1}
        for i, prefixSum in enumerate(prefixSums):
            remainder = prefixSum % k
            if remainder in mod_counter:
                if i - mod_counter[remainder] >1:
                    return True
            else:
                mod_counter[remainder] = i

        return False

    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        mod_counter = {0:0}
        prefix_sum = 0
        
        for i, num in enumerate(nums):
            prefix_sum += num
            remainder = prefix_sum%k
            # print(num, prefix_sum, remainder, mod_counter)
            print(num, prefix_sum, remainder, mod_counter)
            if remainder in mod_counter:
                if i - mod_counter[remainder] >= 1:
                    return True
            else:
                mod_counter[remainder] = i
        return False

    def checkSubarraySum1(self, nums: List[int], k: int) -> bool:
        for start in range(len(nums)):
            sum = 0
            for indx in range(start, len(nums)):
                sum += nums[indx]
                # print(sum)
                if indx - start >= 1 and sum % k == 0:
                    return True
        return False
```
