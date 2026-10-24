# 1186. Maximum Subarray Sum with One Deletion

[Problem](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/) · Medium · DP: 1D / Linear → Kadane with state

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 6 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-11-30 10:42 IST · Output Limit Exceeded · Python3

[submission 1109334699](https://leetcode.com/submissions/detail/1109334699/) · tests 34/36

Failing input:

```text
[2160,3455,3986,-1303,-4444,3651,-2842,-3747,2600,727,-134,-3919,-1748,-3589,-914,-3675,-2080,287,2402,9,1668,-1181,4102,2749,-4792,1447,-758,4721,748,-1733,4750,-1419,-4480,2207,-1470,713,-156,-2093,358,3069,4792,-4025,1882,577,3548,2795,-738,-4059,1984,-4033,2082,-455,1508,-589,-394,-2019,4504,-2137,1402,-2255,3980,651,1998,-3819,-4208,-1617,706,745,4564,1203,4998,-4643,-2184,231,1130,-3039,-948 ... [263557 more chars]
```

Expected:

```text
961792
```

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum
```

## Attempt 2 · 2023-11-30 10:43 IST · Accepted · Python3

[submission 1109334926](https://leetcode.com/submissions/detail/1109334926/) · tests 36/36 · runtime 229 ms (beats 5.0%)

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            #print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum
```

## Attempt 3 · 2024-01-24 00:15 IST · Wrong Answer · Python3

[submission 1154882252](https://leetcode.com/submissions/detail/1154882252/) · tests 13/36

Failing input:

```text
[1,-2,0,3]
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            #print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum

    def maximumSum(self, nums: List[int]) -> int:
        max_with_deletion = 0
        max_end_here = max_so_far = nums[0]

        for i in range(1, len(nums)):
            temp = max_end_here
            max_end_here = max(max_end_here + nums[i] , nums[i])
            max_with_deletion = max(max_with_deletion + nums[i], max_end_here)
            max_so_far = max(max_with_deletion, max_end_here, max_so_far)

        return max_so_far
```

## Attempt 4 · 2024-01-24 00:16 IST · Accepted · Python3

[submission 1154883219](https://leetcode.com/submissions/detail/1154883219/) · tests 36/36 · runtime 186 ms (beats 5.0%)

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            #print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum

    def maximumSum(self, nums: List[int]) -> int:
        max_with_deletion = 0 # delete first element
        max_end_here = max_so_far = nums[0]

        for i in range(1, len(nums)):
            temp = max_end_here
            max_end_here = max(max_end_here + nums[i] , nums[i])
            max_with_deletion = max(max_with_deletion + nums[i], temp)
            max_so_far = max(max_with_deletion, max_end_here, max_so_far)

        return max_so_far
```

## Attempt 5 · 2024-01-24 00:16 IST · Accepted · Python3

[submission 1154883274](https://leetcode.com/submissions/detail/1154883274/) · tests 36/36 · runtime 189 ms (beats 5.0%)

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            #print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum

    def maximumSum(self, nums: List[int]) -> int:
        max_with_deletion = 0 # delete first element
        max_end_here = max_so_far = nums[0]

        for i in range(1, len(nums)):
            temp = max_end_here
            max_end_here = max(max_end_here + nums[i] , nums[i])
            max_with_deletion = max(max_with_deletion + nums[i], temp)
            max_so_far = max(max_with_deletion, max_end_here, max_so_far)

        return max_so_far
```

## Attempt 6 · 2024-02-10 22:46 IST · Accepted · Python3

[submission 1171581598](https://leetcode.com/submissions/detail/1171581598/) · tests 36/36 · runtime 267 ms (beats 5.0%)

```python
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0:
            return 0

        noDeletion = [0] * n
        oneDeletion = [0] * n

        noDeletion[0], oneDeletion[0] = nums[0], nums[0]
        maxSum = nums[0]

        for i in range(1, n):
            noDeletion[i] = max(noDeletion[i-1] + nums[i], nums[i])
            oneDeletion[i] = max(oneDeletion[i-1] + nums[i], noDeletion[i-1], nums[i])
            #print(noDeletion, oneDeletion)
            maxSum = max(maxSum, oneDeletion[i])

        return maxSum

    def maximumSum(self, nums: List[int]) -> int:
        max_with_deletion = 0 # delete first element
        max_end_here = max_so_far = nums[0]

        for i in range(1, len(nums)):
            temp = max_end_here
            max_end_here = max(max_end_here + nums[i] , nums[i])
            max_with_deletion = max(max_with_deletion + nums[i], temp)
            max_so_far = max(max_with_deletion, max_end_here, max_so_far)

        return max_so_far

    def maximumSum(self, nums: List[int]) -> int:
        max_ends_here = max_so_far = nums[0]
        max_with_deletion = 0
        for indx in range(1, len(nums)):
            print('num', nums[indx])
            tmp = max_ends_here
            max_ends_here = max(max_ends_here+nums[indx], nums[indx])
            max_with_deletion = max(max_with_deletion + nums[indx], tmp)
            max_so_far = max(max_with_deletion, max_so_far, max_ends_here)
            print(max_ends_here)
        return max_so_far
```
