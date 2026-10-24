# 38. Count and Say

[Problem](https://leetcode.com/problems/count-and-say/) · Medium · Strings & Simulation → Simulation

LeetCode tags: string

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-12-11 04:04 IST · Runtime Error · Python3

[submission 1116767756](https://leetcode.com/submissions/detail/1116767756/) · tests 0/30

Failing input:

```text
1
```

Expected:

```text
"1"
```

Runtime error:

```text
TypeError: Solution.countAndSay() takes 1 positional argument but 2 were given
    ret = Solution().countAndSay(param_1)
Line 53 in _driver (Solution.py)
    _driver()
Line 64 in <module> (Solution.py)
```

```python
class Solution:
    def countAndSay(n):
        """
        conservative time compleixty is 2^n
        since in the worst case a sequence can double in length from prev to next when all the digits are unique - to describe each digit you need 2 digits in new sequence
        """

        # base condition
        if n == 1:
            return "1"
        
        prev_term = "1"

        # generate seq from next till n
        for i in range(2, n + 1):
            current_term = ""
            count = 1

            # in the previous term, compare next and previous digit because if two digits are same you reduce it from 11 -> two 1 and if different 12-> 11 12
            for j in range(1, len(prev_term)):
                if prev_term[j] == prev_term[j - 1]:
                    count += 1
                else:
                    # for previous ter add it to current term
                    current_term += str(count) + prev_term[j - 1]
                    # reset count for new term
                    count = 1

            # finally for the last
            current_term += str(count) + prev_term[-1]
            prev_term = current_term
        
        return prev_term
```

## Attempt 2 · 2023-12-11 04:05 IST · Accepted · Python3

[submission 1116767903](https://leetcode.com/submissions/detail/1116767903/) · tests 30/30 · runtime 43 ms (beats 18.8%)

```python
class Solution:
    def countAndSay(self,n):
        """
        conservative time compleixty is 2^n
        since in the worst case a sequence can double in length from prev to next when all the digits are unique - to describe each digit you need 2 digits in new sequence
        """

        # base condition
        if n == 1:
            return "1"
        
        prev_term = "1"

        # generate seq from next till n
        for i in range(2, n + 1):
            current_term = ""
            count = 1

            # in the previous term, compare next and previous digit because if two digits are same you reduce it from 11 -> two 1 and if different 12-> 11 12
            for j in range(1, len(prev_term)):
                if prev_term[j] == prev_term[j - 1]:
                    count += 1
                else:
                    # for previous ter add it to current term
                    current_term += str(count) + prev_term[j - 1]
                    # reset count for new term
                    count = 1

            # finally for the last
            current_term += str(count) + prev_term[-1]
            prev_term = current_term
        
        return prev_term
```

## Attempt 3 · 2024-01-02 03:35 IST · Accepted · Python3

[submission 1134094340](https://leetcode.com/submissions/detail/1134094340/) · tests 30/30 · runtime 54 ms (beats 18.8%)

```python
class Solution1:
    def countAndSay(self,n):
        """
        conservative time compleixty is 2^n
        since in the worst case a sequence can double in length from prev to next when all the digits are unique - to describe each digit you need 2 digits in new sequence
        """

        # base condition
        if n == 1:
            return "1"
        
        prev_term = "1"

        # generate seq from next till n
        for i in range(2, n + 1):
            current_term = ""
            count = 1

            # in the previous term, compare next and previous digit because if two digits are same you reduce it from 11 -> two 1 and if different 12-> 11 12
            print(i, prev_term,'---', current_term)
            for j in range(1, len(prev_term)):
                # print(prev_term, count)
                # in case if there are 112 or 11 - keep count in count 
                # then 
                if prev_term[j] == prev_term[j - 1]:
                    count += 1
                else:
                    # for previous ter add it to current term
                    current_term += str(count) + prev_term[j - 1]
                    # reset count for new term
                    count = 1

            # finally for the last
            current_term += str(count) + prev_term[-1]
            prev_term = current_term
        
        return prev_term

class Solution:
    def countAndSay(self,n):
        prev_term = "1"

        for seq_idx in range(2, n+1):
            
            #
            count = 1
            current_term= ""
            for num_idx in range(1, len(prev_term)):
                if prev_term[num_idx-1] == prev_term[num_idx]:
                    count += 1
                else:
                    current_term += str(count) + prev_term[num_idx - 1]
                    count = 1

            current_term += str(count) + prev_term[-1]
            prev_term = current_term
        return prev_term
```
