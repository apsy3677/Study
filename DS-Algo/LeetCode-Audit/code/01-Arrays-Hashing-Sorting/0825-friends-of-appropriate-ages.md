# 825. Friends Of Appropriate Ages

[Problem](https://leetcode.com/problems/friends-of-appropriate-ages/) · Medium · Arrays, Hashing & Sorting → Count buckets

LeetCode tags: array, two-pointers, binary-search, sorting

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-12-04 00:23 IST · Accepted · Python3

[submission 1111670027](https://leetcode.com/submissions/detail/1111670027/) · tests 89/89 · runtime 312 ms (beats 5.7%)

```python
class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        #function numFriendRequests(ages):
        age_count = Counter(ages)
        total_requests = 0

        for age_x in age_count:
            for age_y in age_count:
                if age_y > 0.5 * age_x + 7 and age_y <= age_x:
                    if age_y <= 100 or age_x >= 100:
                        total_requests += age_count[age_x] * (age_count[age_y] - (age_x == age_y))

        return total_requests
```

## Attempt 2 · 2024-01-25 23:13 IST · Accepted · Python3

[submission 1156696705](https://leetcode.com/submissions/detail/1156696705/) · tests 89/89 · runtime 293 ms (beats 6.2%)

```python
class Solution:
    def numFriendRequests(self, ages: List[int]) -> int:
        #function numFriendRequests(ages):
        '''
        when you do calculation for same ages you need to substract rquest to themselves
        a smart trick is to do calculation as
        count(x) * ( count(y) - (x == y))
        so when x and y are same - substract request to themselves = - count(x)
        else count(x) * count(y)

        '''
        age_count = Counter(ages)
        total_requests = 0

        for age_x in age_count:
            for age_y in age_count:
                if age_y > 0.5 * age_x + 7 and age_y <= age_x and (age_y <= 100 or age_x >= 100):
                        total_requests += age_count[age_x] * (age_count[age_y] - (age_x == age_y))

        return total_requests
```
