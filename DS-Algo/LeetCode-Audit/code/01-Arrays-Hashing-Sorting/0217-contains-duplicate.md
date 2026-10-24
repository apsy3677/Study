# 217. Contains Duplicate

[Problem](https://leetcode.com/problems/contains-duplicate/) · Easy · Arrays, Hashing & Sorting → Hash set

LeetCode tags: array, hash-table, sorting

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2023-11-18 02:37 IST · Time Limit Exceeded · Python3

[submission 1101037724](https://leetcode.com/submissions/detail/1101037724/) · tests 65/75

Failing input:

```text
[-24500,-24499,-24498,-24497,-24496,-24495,-24494,-24493,-24492,-24491,-24490,-24489,-24488,-24487,-24486,-24485,-24484,-24483,-24482,-24481,-24480,-24479,-24478,-24477,-24476,-24475,-24474,-24473,-24472,-24471,-24470,-24469,-24468,-24467,-24466,-24465,-24464,-24463,-24462,-24461,-24460,-24459,-24458,-24457,-24456,-24455,-24454,-24453,-24452,-24451,-24450,-24449,-24448,-24447,-24446,-24445,-24444, ... [328885 more chars]
```

Expected:

```text
false
```

```python
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        for i in range(len(nums)):
            for j in range(0,i):
                if nums[i] == nums[j]: return True

        return False
```
