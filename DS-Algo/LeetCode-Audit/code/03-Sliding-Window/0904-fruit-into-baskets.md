# 904. Fruit Into Baskets

[Problem](https://leetcode.com/problems/fruit-into-baskets/) · Medium · Sliding Window → At most 2 distinct

LeetCode tags: array, hash-table, sliding-window

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-02-10 14:37 IST · Accepted · Python3

[submission 1171274364](https://leetcode.com/submissions/detail/1171274364/) · tests 91/91 · runtime 782 ms (beats 5.1%)

```python
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        l = 0 
        r = 0
        
        type_count = Counter()
        max_fruits = float('-inf')
        while r < len(fruits):
            # add to window
            type_count[fruits[r]] +=1

            while len(type_count) > 2:
                type_count[fruits[l]] -= 1
                if type_count[fruits[l]] ==0:
                    del type_count[fruits[l]]
                l+=1
            # print(r, type_count)
            # valid
            max_fruits = max(max_fruits, r-l+1)
            r+=1
        return max_fruits
```
