# 1868. Product of Two Run-Length Encoded Arrays

[Problem](https://leetcode.com/problems/product-of-two-run-length-encoded-arrays/) · Medium · Two Pointers → Two-pointer merge

LeetCode tags: array, two-pointers

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-01-05 23:30 IST · Accepted · Python3

[submission 1137834234](https://leetcode.com/submissions/detail/1137834234/) · tests 52/52 · runtime 2084 ms (beats 5.9%)

```python
class Solution:
    def findRLEArray(self, encoded1: List[List[int]], encoded2: List[List[int]]) -> List[List[int]]:
        p1 = 0
        p2 = 0
        result = []

        while p1< len(encoded1) and p2< len(encoded2):
            val1, freq1 =  encoded1[p1]
            val2, freq2 =  encoded2[p2]

            product = val1 * val2

            freq = min(freq1, freq2)

            if result and result[-1][0] == product:
                result[-1][1]+=freq
            else:
                result.append([product, freq])

            encoded1[p1][1] -=freq
            encoded2[p2][1] -=freq

            if encoded1[p1][1] ==0:
                p1+=1
            if encoded2[p2][1]==0:
                p2+=1

        return result
```
