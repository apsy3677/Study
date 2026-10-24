# 996. Number of Squareful Arrays

[Problem](https://leetcode.com/problems/number-of-squareful-arrays/) · Hard · Backtracking → Permutations with pruning

LeetCode tags: array, hash-table, math, dynamic-programming, backtracking, bit-manipulation, bitmask

Attempts since Mar 2023: 7 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-12-30 02:45 IST · Accepted · Python3

[submission 1131708431](https://leetcode.com/submissions/detail/1131708431/) · tests 76/76 · runtime 69 ms (beats 9.2%)

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    print(nums,i, start, seen)
                    continue
                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)
```

## Attempt 2 · 2023-12-30 02:45 IST · Accepted · Python3

[submission 1131708471](https://leetcode.com/submissions/detail/1131708471/) · tests 76/76 · runtime 37 ms (beats 10.9%)

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue
                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)
```

## Attempt 3 · 2023-12-30 02:48 IST · Accepted · Python3

[submission 1131709849](https://leetcode.com/submissions/detail/1131709849/) · tests 76/76 · runtime 65 ms (beats 9.2%)

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue
                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                # start is the fix part 
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)
```

## Attempt 4 · 2024-02-10 21:42 IST · Wrong Answer · Python3

[submission 1171531678](https://leetcode.com/submissions/detail/1171531678/) · tests 41/76

Failing input:

```text
[1,17,8]
```

Expected:

```text
2
```

Your output:

```text
1
```

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue

                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                # start is the fix part 
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)


    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isSquareful(num):
            return int(num **0.5)**2 == num


        def perm(start):
            if start == len(nums):
                return 1

            count =0
            seen = set()
            for i in range(start, len(nums)):
                # swap to get a permutation
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                
                nums[start], nums[i] = nums[i], nums[start]
                if start ==0 or isSquareful(nums[start]+nums[start-1]):
                    count += perm(start+1)
                nums[start], nums[i] = nums[i], nums[start]
            return count
        return perm(0)

    def numSquarefulPerms(self, nums: List[int]) -> int:
        def perm(start):
            if start == len(nums):
                print(nums)

            seen = set()
            for i in range(start, len(nums)):
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                nums[i], nums[start] = nums[start], nums[i]
                if i>0 and isPerfect(nums[start]+nums[start]-1):
                    perm(start+1)
                nums[i], nums[start] = nums[start], nums[i]

        perm(0)
        return -1

    def numSquarefulPerms(self, nums: List[int]) -> int:
        is_squareful = lambda x: (x**0.5)**2 == x

        def perm(start):
            if start == len(nums):
                return 1
            
            seen = set()
            count = 0
            for indx in range(start, len(nums)):
                if nums[indx] in seen:
                    continue
                nums[start], nums[indx] = nums[indx], nums[start]
                if (indx==0 or is_squareful(nums[indx]+nums[indx-1])):
                    count += perm(start+1)
                nums[start], nums[indx] = nums[indx], nums[start]
                seen.add(nums[indx])

            return count
        return perm(0)
```

## Attempt 5 · 2024-02-10 21:43 IST · Wrong Answer · Python3

[submission 1171532446](https://leetcode.com/submissions/detail/1171532446/) · tests 41/76

Failing input:

```text
[2,3,1]
```

Expected:

```text
0
```

Your output:

```text
1
```

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue

                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                # start is the fix part 
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)


    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isSquareful(num):
            return int(num **0.5)**2 == num


        def perm(start):
            if start == len(nums):
                return 1

            count =0
            seen = set()
            for i in range(start, len(nums)):
                # swap to get a permutation
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                
                nums[start], nums[i] = nums[i], nums[start]
                if start ==0 or isSquareful(nums[start]+nums[start-1]):
                    count += perm(start+1)
                nums[start], nums[i] = nums[i], nums[start]
            return count
        return perm(0)

    def numSquarefulPerms(self, nums: List[int]) -> int:
        def perm(start):
            if start == len(nums):
                print(nums)

            seen = set()
            for i in range(start, len(nums)):
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                nums[i], nums[start] = nums[start], nums[i]
                if i>0 and isPerfect(nums[start]+nums[start]-1):
                    perm(start+1)
                nums[i], nums[start] = nums[start], nums[i]

        perm(0)
        return -1

    def numSquarefulPerms(self, nums: List[int]) -> int:
        is_squareful = lambda x: (x**0.5)**2 == x

        def perm(start):
            if start == len(nums):
                return 1
            
            seen = set()
            count = 0
            for indx in range(start, len(nums)):
                if nums[indx] in seen:
                    continue
                nums[start], nums[indx] = nums[indx], nums[start]
                if (start==0 or is_squareful(nums[indx]+nums[indx-1])):
                    count += perm(start+1)
                nums[start], nums[indx] = nums[indx], nums[start]
                seen.add(nums[indx])

            return count
        return perm(0)
```

## Attempt 6 · 2024-02-10 21:46 IST · Wrong Answer · Python3

[submission 1171534270](https://leetcode.com/submissions/detail/1171534270/) · tests 49/76

Failing input:

```text
[65,44,5,11]
```

Expected:

```text
0
```

Your output:

```text
4
```

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue

                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                # start is the fix part 
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)


    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isSquareful(num):
            return int(num **0.5)**2 == num


        def perm(start):
            if start == len(nums):
                return 1

            count =0
            seen = set()
            for i in range(start, len(nums)):
                # swap to get a permutation
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                
                nums[start], nums[i] = nums[i], nums[start]
                if start ==0 or isSquareful(nums[start]+nums[start-1]):
                    count += perm(start+1)
                nums[start], nums[i] = nums[i], nums[start]
            return count
        return perm(0)

    def numSquarefulPerms(self, nums: List[int]) -> int:
        def perm(start):
            if start == len(nums):
                print(nums)

            seen = set()
            for i in range(start, len(nums)):
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                nums[i], nums[start] = nums[start], nums[i]
                if i>0 and isPerfect(nums[start]+nums[start]-1):
                    perm(start+1)
                nums[i], nums[start] = nums[start], nums[i]

        perm(0)
        return -1

    def numSquarefulPerms(self, nums: List[int]) -> int:
        is_squareful = lambda x: (x**0.5)**2 == x

        def perm(start):
            if start == len(nums):
                return 1
            
            seen = set()
            count = 0
            for indx in range(start, len(nums)):
                if nums[indx] in seen:
                    continue
                nums[start], nums[indx] = nums[indx], nums[start]
                if (start==0 or is_squareful(nums[start]+nums[start-1])):
                    count += perm(start+1)
                nums[start], nums[indx] = nums[indx], nums[start]
                seen.add(nums[indx])

            return count
        return perm(0)
```

## Attempt 7 · 2024-02-10 21:47 IST · Accepted · Python3

[submission 1171534805](https://leetcode.com/submissions/detail/1171534805/) · tests 76/76 · runtime 31 ms (beats 10.9%)

```python
class Solution:
    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isPerfectSquare(num):
            # print(num, int(num**0.5)**2 == num)
            return int(num**0.5)**2 == num

        
        def perm(start):
            # print(start)
            if len(nums) == start:
                # print(nums)
                return 1
            count = 0

            seen = set()
            for i in range(start, len(nums)):
                # at the start postion- check if you have seen this digit before
                if nums[i] in seen:
                    # print(nums,i, start, seen)
                    continue

                seen.add(nums[i])

                # 123 -> 213 -> start will be 
                nums[start], nums[i] = nums[i], nums[start]
                
                # fix one element at a time and swap from next onwards
                # start is the fix part 
                if start == 0 or isPerfectSquare(nums[start]+nums[start-1]):
                    count +=perm(start+1)
                
                nums[start], nums[i] = nums[i], nums[start]
            # print(count)
            return count

        return perm(0)


    def numSquarefulPerms(self, nums: List[int]) -> int:
        def isSquareful(num):
            return int(num **0.5)**2 == num


        def perm(start):
            if start == len(nums):
                return 1

            count =0
            seen = set()
            for i in range(start, len(nums)):
                # swap to get a permutation
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                
                nums[start], nums[i] = nums[i], nums[start]
                if start ==0 or isSquareful(nums[start]+nums[start-1]):
                    count += perm(start+1)
                nums[start], nums[i] = nums[i], nums[start]
            return count
        return perm(0)

    def numSquarefulPerms(self, nums: List[int]) -> int:
        def perm(start):
            if start == len(nums):
                print(nums)

            seen = set()
            for i in range(start, len(nums)):
                if nums[i] in seen:
                    continue
                seen.add(nums[i])
                nums[i], nums[start] = nums[start], nums[i]
                if i>0 and isPerfect(nums[start]+nums[start]-1):
                    perm(start+1)
                nums[i], nums[start] = nums[start], nums[i]

        perm(0)
        return -1

    def numSquarefulPerms(self, nums: List[int]) -> int:
        is_squareful = lambda x: int(x**0.5)**2 == x

        def perm(start):
            if start == len(nums):
                return 1
            
            seen = set()
            count = 0
            for indx in range(start, len(nums)):
                if nums[indx] in seen:
                    continue
                nums[start], nums[indx] = nums[indx], nums[start]
                if (start==0 or is_squareful(nums[start]+nums[start-1])):
                    count += perm(start+1)
                nums[start], nums[indx] = nums[indx], nums[start]
                seen.add(nums[indx])

            return count
        return perm(0)
```
