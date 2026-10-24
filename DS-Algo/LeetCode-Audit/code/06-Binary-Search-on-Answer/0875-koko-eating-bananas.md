# 875. Koko Eating Bananas

[Problem](https://leetcode.com/problems/koko-eating-bananas/) · Medium · Binary Search on Answer → Minimise speed

LeetCode tags: array, binary-search

Attempts since Mar 2023: 12 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-04-28 18:59 IST · Accepted · C++

[submission 941106300](https://leetcode.com/submissions/detail/941106300/) · runtime 77 ms

_Code not returned by LeetCode._

## Attempt 2 · 2023-11-27 20:51 IST · Runtime Error · Python3

[submission 1107502795](https://leetcode.com/submissions/detail/1107502795/) · tests 18/126

Failing input:

```text
[312884470]
968709470
```

Expected:

```text
1
```

Runtime error:

```text
ZeroDivisionError: division by zero
    hoursNeeded += math.ceil(pile/k)
Line 9 in canEat (Solution.py)
    if canEat(mid):
Line 14 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 43 in _driver (Solution.py)
    _driver()
Line 54 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        left = sum(piles)//h
        right = max(piles)

        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 3 · 2023-11-27 20:51 IST · Runtime Error · Python3

[submission 1107503112](https://leetcode.com/submissions/detail/1107503112/) · tests 18/126

Failing input:

```text
[312884470]
968709470
```

Expected:

```text
1
```

Runtime error:

```text
ZeroDivisionError: division by zero
    hoursNeeded += math.ceil(pile/k)
Line 10 in canEat (Solution.py)
    if canEat(mid):
Line 15 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 44 in _driver (Solution.py)
    _driver()
Line 55 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = sum(piles)//h
        right = max(piles)

        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 4 · 2023-11-27 20:52 IST · Runtime Error · Python3

[submission 1107503649](https://leetcode.com/submissions/detail/1107503649/) · tests 18/126

Failing input:

```text
[312884470]
968709470
```

Expected:

```text
1
```

Runtime error:

```text
ZeroDivisionError: division by zero
    hoursNeeded += math.ceil(pile/k)
Line 10 in canEat (Solution.py)
    if canEat(mid):
Line 16 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 45 in _driver (Solution.py)
    _driver()
Line 56 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = sum(piles)//h
        right = max(piles)

        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 5 · 2023-11-27 20:54 IST · Runtime Error · Python3

[submission 1107504760](https://leetcode.com/submissions/detail/1107504760/) · tests 0/126

Failing input:

```text
[3,6,7,11]
8
```

Expected:

```text
4
```

Runtime error:

```text
NameError: name 'rigth' is not defined. Did you mean: 'right'?
    print(left, rigth)
Line 6 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 45 in _driver (Solution.py)
    _driver()
Line 56 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = sum(piles)//h
        right = max(piles)
        print(left, rigth)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 6 · 2023-11-27 20:54 IST · Runtime Error · Python3

[submission 1107504814](https://leetcode.com/submissions/detail/1107504814/) · tests 0/126

Failing input:

```text
[3,6,7,11]
8
```

Expected:

```text
4
```

Runtime error:

```text
TypeError: 'right' is an invalid keyword argument for print()
    print(left,         right = max(piles)
Line 6 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 46 in _driver (Solution.py)
    _driver()
Line 57 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = sum(piles)//h
        right = max(piles)
        print(left,         right = max(piles)
)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 7 · 2023-11-27 20:55 IST · Runtime Error · Python3

[submission 1107504873](https://leetcode.com/submissions/detail/1107504873/) · tests 18/126

Failing input:

```text
[312884470]
968709470
```

Expected:

```text
1
```

Runtime error:

```text
ZeroDivisionError: division by zero
    hoursNeeded += math.ceil(pile/k)
Line 10 in canEat (Solution.py)
    if canEat(mid):
Line 16 in minEatingSpeed (Solution.py)
    ret = Solution().minEatingSpeed(param_1, param_2)
Line 45 in _driver (Solution.py)
    _driver()
Line 56 in <module> (Solution.py)
```

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = sum(piles)//h
        right = max(piles)
        print(left, right)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 8 · 2023-11-27 20:55 IST · Accepted · Python3

[submission 1107505336](https://leetcode.com/submissions/detail/1107505336/) · tests 126/126 · runtime 354 ms (beats 5.0%)

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        print(piles, h)
        left = math.ceil(sum(piles)/h)
        right = max(piles)
        print(left, right)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 9 · 2023-11-27 20:55 IST · Accepted · Python3

[submission 1107505427](https://leetcode.com/submissions/detail/1107505427/) · tests 126/126 · runtime 392 ms (beats 5.0%)

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        #print(piles, h)
        left = math.ceil(sum(piles)/h)
        right = max(piles)
        #print(left, right)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 10 · 2024-02-10 23:43 IST · Accepted · Python3

[submission 1171628615](https://leetcode.com/submissions/detail/1171628615/) · tests 126/126 · runtime 271 ms (beats 5.0%)

```python
class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        #print(piles, h)
        left = math.ceil(sum(piles)/h)
        right = max(piles)+1
        #print(left, right)
        def canEat(k):
            hoursNeeded = 0
            for pile in piles:
                hoursNeeded += math.ceil(pile/k)
            return hoursNeeded <= h
                
        while left < right:
            mid = (left + right) //2
            print(mid)
            if canEat(mid):
                right = mid
            else:
                left = mid + 1
        return left
```

## Attempt 11 · 2025-03-22 19:05 IST · Accepted · C++

[submission 1582305528](https://leetcode.com/submissions/detail/1582305528/) · tests 126/126 · runtime 8 ms (beats 52.4%)

```cpp
class Solution {
public:
    bool could_eat(vector<int>&piles,int h,int speed)
    {
        for(int i=0;i<piles.size();i++)
        {
            if(piles[i]%speed==0)
            {
                h-=(piles[i]/speed);//(piles[i]/speed) units of time to finish pile
            }
            else
            {
                h-=(piles[i]/speed)+1;(piles[i]/speed); //units of time + 1 for remainder to finish pile
            }
            if(h<0)
            {
                return false;//time out....Guards return before could finish completing the current pile
            }
        }
        return true;//Guards didn't return wihtin time to catch
    }
    int minEatingSpeed(vector<int>&piles,int h) 
    {
        int left=1,right=INT_MIN;
        int ans = INT_MAX;
        for(auto j:piles)//with this maximum limit we could always complete piles within time
        {
            right=max(right,j);
        }
        while(left <= right)//Normal Binary Search to find Minimum Element for which could_eat_piles within time
        {
            int mid=(left+right)/2;
            if(could_eat(piles,h,mid))
            {
                ans = min(ans, mid);
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
        }
        return ans;
    }
};
```

## Attempt 12 · 2025-03-22 21:36 IST · Accepted · C++

[submission 1582420275](https://leetcode.com/submissions/detail/1582420275/) · tests 126/126 · runtime 9 ms (beats 42.1%)

```cpp
class Solution {
public:
    bool could_eat(vector<int>&piles,int h,int speed)
    {
        for(int i=0;i<piles.size();i++)
        {
            if(piles[i]%speed==0)
            {
                h-=(piles[i]/speed);//(piles[i]/speed) units of time to finish pile
            }
            else
            {
                h-=(piles[i]/speed)+1;(piles[i]/speed); //units of time + 1 for remainder to finish pile
            }
            if(h<0)
            {
                return false;//time out....Guards return before could finish completing the current pile
            }
        }
        return true;//Guards didn't return wihtin time to catch
    }
    int minEatingSpeed(vector<int>&piles,int h) 
    {
        int left=1,right=INT_MIN;
        int ans = INT_MAX;
        for(auto j:piles)//with this maximum limit we could always complete piles within time
        {
            right=max(right,j);
        }
        while(left <= right)//Normal Binary Search to find Minimum Element for which could_eat_piles within time
        {
            int mid=(left+right)/2;
            if(could_eat(piles,h,mid))
            {
                ans = min(ans, mid);
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
        }
        return ans;
    }
};
```
