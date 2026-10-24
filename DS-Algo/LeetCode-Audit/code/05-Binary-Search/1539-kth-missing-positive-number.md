# 1539. Kth Missing Positive Number

[Problem](https://leetcode.com/problems/kth-missing-positive-number/) · Easy · Binary Search → Missing-count search

LeetCode tags: array, binary-search

Attempts since Mar 2023: 8 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2024-01-07 01:23 IST · Accepted · Python3

[submission 1138854879](https://leetcode.com/submissions/detail/1138854879/) · tests 86/86 · runtime 45 ms (beats 17.1%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        if k < arr[0]:
            return k
        
        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        return arr[-1] + k
```

## Attempt 2 · 2024-01-07 02:31 IST · Accepted · Python3

[submission 1138894606](https://leetcode.com/submissions/detail/1138894606/) · tests 86/86 · runtime 58 ms (beats 16.6%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1
```

## Attempt 3 · 2024-01-26 07:52 IST · Accepted · Python3

[submission 1156988662](https://leetcode.com/submissions/detail/1156988662/) · tests 86/86 · runtime 51 ms (beats 17.0%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1  

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1

        while l <r:
            mid = (l+r)//2
            missing = arr[mid] - mid -1
            if k > missing:
                left = mid +1
            else:
                right = mid - 1

        return right+k+1

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = 0
        for i in range( len(arr)):
            
            missing_between = arr[i] - last - 1
            print(arr[i], last, missing_between,k)
            if k<=missing_between:
                return last +k
            k-=missing_between
            last = arr[i]

        return arr[-1] +k
```

## Attempt 4 · 2024-01-26 07:54 IST · Accepted · Python3

[submission 1156989236](https://leetcode.com/submissions/detail/1156989236/) · tests 86/86 · runtime 57 ms (beats 16.6%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1  

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1

        while l <r:
            mid = (l+r)//2
            missing = arr[mid] - mid -1
            if k > missing:
                left = mid +1
            else:
                right = mid - 1

        return right+k+1

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = 0
        for i in range( len(arr)):
            
            missing_between = arr[i] - last - 1
            # print(arr[i], last, missing_between,k)
            if k<=missing_between:
                return last +k
            k-=missing_between
            last = arr[i]

        return last +k
```

## Attempt 5 · 2024-02-06 12:22 IST · Wrong Answer · Python3

[submission 1167548075](https://leetcode.com/submissions/detail/1167548075/) · tests 13/86

Failing input:

```text
[1,2]
1
```

Expected:

```text
3
```

Your output:

```text
-1
```

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1  

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1

        while l <r:
            mid = (l+r)//2
            missing = arr[mid] - mid -1
            if k > missing:
                left = mid +1
            else:
                right = mid - 1

        return right+k+1

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = 0
        for i in range( len(arr)):
            missing_between = arr[i] - last - 1
            # print(arr[i], last, missing_between,k)
            if k<=missing_between:
                return last +k
            k-=missing_between
            last = arr[i]

        return last +k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1
        missing_at = lambda i: arr[i] - i - 1
        while l <= r:
            mid = (l+r)//2
            missing = missing_at(mid)
            if k > missing:
                l = mid +1
            else:
                r = mid - 1

        remaining_k = k - missing_at(l-1)
        return arr[l-1] + remaining_k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = -1
        missing =0
        for num in arr:
            if num - last >1:
                missing += num - last - 1
            
            if k - missing <=0:
                return last + abs(k-missing)
            last = num
        
        return last + k
```

## Attempt 6 · 2024-02-10 17:50 IST · Accepted · Python3

[submission 1171383966](https://leetcode.com/submissions/detail/1171383966/) · tests 86/86 · runtime 45 ms (beats 17.1%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1  

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1

        while l <r:
            mid = (l+r)//2
            missing = arr[mid] - mid -1
            if k > missing:
                left = mid +1
            else:
                right = mid - 1

        return right+k+1

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = 0
        for i in range( len(arr)):
            missing_between = arr[i] - last - 1
            # print(arr[i], last, missing_between,k)
            if k<=missing_between:
                return last +k
            k-=missing_between
            last = arr[i]

        return last +k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1
        
        # missing num - i - 1
        missing_at = lambda i: arr[i] - i - 1

        # find the index where l has missing <= k
        while l <= r:
            mid = (l+r)//2
            missing = missing_at(mid)
            print(mid,l,r, missing)
            if k > missing:
                l = mid +1
            else:
                r = mid - 1
            
        print(l,r)
        remaining_k = k - missing_at(l-1)
        return arr[l-1] + remaining_k

    def findKthPositive8(self, arr: List[int], k: int) -> int:
        if k < arr[0]:
            return k

        last = 0

        for i in range(len(arr)):
            curr_missing = arr[i] - last - 1
            print(arr[i], curr_missing, k)
            if k <= curr_missing:
                return last+k
            k -= curr_missing
            last = arr[i]
        return last +k 

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr)  -1
        missing_at = lambda indx: arr[indx] - indx -1

        while l< r:
            mid = (l+r)//2
            # print(arr[mid])

            if k > missing_at(mid):
                l = mid + 1
            else:
                r = mid 

        print(l)
        if l == len(arr)-1 and missing_at(l) <k:
            l = l+1

        # print(missing_at(l-1))
        # print(l)
        remaining_k = k - missing_at(l-1)
        return arr[l-1] + remaining_k
```

## Attempt 7 · 2024-02-11 00:14 IST · Accepted · Python3

[submission 1171653463](https://leetcode.com/submissions/detail/1171653463/) · tests 86/86 · runtime 54 ms (beats 16.9%)

```python
class Solution:
    def findKthPositive(self, arr: List[int], k: int) -> int:
        '''
        keep on decreasing k 
        change it to -> from current number, find the kth missing number
        and when k lies between current missing range -> return last +k
        '''
        # 1. for less than first number
        if k < arr[0]:
            return k

        last = 0
        for i in range(len(arr)):
            curr_missing = arr[i] - last -1
            if k<= curr_missing:
                return last + k
            k -= curr_missing
            last = arr[i]
            
        # 3. after last
        return arr[-1] + k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        left = 0
        right = len(arr) -1

        while left <= right:
            mid = (left + right) //2

            if k > arr[mid] - mid - 1:
                left = mid +1
            else:
                right = mid - 1

        # at last left will be one more than right 
        # right will point to the last number after which you have to find missing
        # missing till right = nums[right] - right - 1 
        # after nums[right] this many missing number = k - (missing till right) 
        # nums[right] + k - (nums[right] - right - 1) = k + right + 1
        return right + k +1  

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1

        while l <r:
            mid = (l+r)//2
            missing = arr[mid] - mid -1
            if k > missing:
                left = mid +1
            else:
                right = mid - 1

        return right+k+1

    def findKthPositive(self, arr: List[int], k: int) -> int:
        last = 0
        for i in range( len(arr)):
            missing_between = arr[i] - last - 1
            # print(arr[i], last, missing_between,k)
            if k<=missing_between:
                return last +k
            k-=missing_between
            last = arr[i]

        return last +k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr) -1
        
        # missing num - i - 1
        missing_at = lambda i: arr[i] - i - 1

        # find the index where l has missing <= k
        while l <= r:
            mid = (l+r)//2
            missing = missing_at(mid)
            print(mid,l,r, missing)
            if k > missing:
                l = mid +1
            else:
                r = mid - 1
            
        print(l,r)
        remaining_k = k - missing_at(l-1)
        return arr[l-1] + remaining_k

    def findKthPositive8(self, arr: List[int], k: int) -> int:
        if k < arr[0]:
            return k

        last = 0

        for i in range(len(arr)):
            curr_missing = arr[i] - last - 1
            print(arr[i], curr_missing, k)
            if k <= curr_missing:
                return last+k
            k -= curr_missing
            last = arr[i]
        return last +k 

    def findKthPositive(self, arr: List[int], k: int) -> int:
        l = 0
        r = len(arr)  -1
        missing_at = lambda indx: arr[indx] - indx -1

        while l< r:
            mid = (l+r)//2
            # print(arr[mid])

            if missing_at(mid) < k:
                l = mid + 1
            else:
                r = mid 

        print(r)
        if l == len(arr)-1 and missing_at(l) <k:
            l = l+1

        # print(missing_at(l-1))
        # print(l)
        remaining_k = k - missing_at(l-1)
        return arr[l-1] + remaining_k

    def findKthPositive(self, arr: List[int], k: int) -> int:
        missing_at = lambda indx : arr[indx] - indx - 1

        l = 0
        r = len(arr)

        while l < r:
            mid = (l+r)//2

            if missing_at(mid) < k:
                l = mid +1
            else:
                r = mid
        
        return arr[l-1] + k - missing_at(l-1)
```

## Attempt 8 · 2025-07-08 16:27 IST · Accepted · C++

[submission 1690679643](https://leetcode.com/submissions/detail/1690679643/) · tests 87/87 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int l = 0, r = arr.size()-1;
        int x = 1; // as numbers start from 1.
        while(l<=r) {
            int mid = l + (r-l)/2;
            int miss = arr[mid] - x -mid;
            if (miss < k) {
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        return k + r + x;
    }
};
```
