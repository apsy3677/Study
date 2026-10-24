# 415. Add Strings

[Problem](https://leetcode.com/problems/add-strings/) · Easy · Strings & Simulation → Digit addition

LeetCode tags: math, string, simulation

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-22 01:31 IST · Accepted · Python3

[submission 1103708182](https://leetcode.com/submissions/detail/1103708182/) · tests 317/317 · runtime 51 ms (beats 8.3%)

```python
class Solution:
    def addStrings(self, num1: str, num2: str) -> str:

        n = max(len(num1), len(num2))
        num1 = num1.zfill(n)
        num2 = num2.zfill(n)
        
        i = n -1
        result = []
        carry = 0

        while i >= 0:
            rem = (carry + int(num1[i]) + int(num2[i])) % 10
            carry = (carry + int(num1[i]) + int(num2[i])) // 10
            # print(rem,carry, i)
            result.append(str(rem))
            i-=1
            
        if carry>0:
            result.append(str(carry))

        return ''.join(result[::-1])
```

## Attempt 2 · 2023-12-05 02:28 IST · Runtime Error · Python3

[submission 1112439668](https://leetcode.com/submissions/detail/1112439668/) · tests 0/317

Failing input:

```text
"11"
"123"
```

Expected:

```text
"134"
```

Runtime error:

```text
TypeError: sequence item 0: expected str instance, int found
    return ''.join(result[::-1])
Line 31 in addStrings (Solution.py)
    ret = Solution().addStrings(param_1, param_2)
Line 57 in _driver (Solution.py)
    _driver()
Line 68 in <module> (Solution.py)
```

```python
class Solution:
    def addStrings(self, num1: str, num2: str) -> str:
            

        # zfill to max to match length
        n = max(len(num1), len(num2))
        num1 = num1.zfill(n)
        num2 = num2.zfill(n)
        
        i = n -1
        result = []
        carry = 0

        #for max length(which is same now)
        while i >= 0:
            # use ord or int to change string to number
            rem = (carry + int(num1[i]) + int(num2[i])) % 10
            carry = (carry + int(num1[i]) + int(num2[i])) // 10
            print(rem,carry, i)

            # conver to string and add
            result.append(rem)
            i-=1
        
        # add carry after last digit if any
        if carry:
            result.append(carry)
        print(result)

        # reverseresult because we started from least sign digit
        return ''.join(result[::-1])
```

## Attempt 3 · 2023-12-05 02:28 IST · Runtime Error · Python3

[submission 1112439723](https://leetcode.com/submissions/detail/1112439723/) · tests 6/317

Failing input:

```text
"1"
"9"
```

Expected:

```text
"10"
```

Runtime error:

```text
TypeError: sequence item 0: expected str instance, int found
    return ''.join(result[::-1])
Line 31 in addStrings (Solution.py)
    ret = Solution().addStrings(param_1, param_2)
Line 57 in _driver (Solution.py)
    _driver()
Line 68 in <module> (Solution.py)
```

```python
class Solution:
    def addStrings(self, num1: str, num2: str) -> str:


        # zfill to max to match length
        n = max(len(num1), len(num2))
        num1 = num1.zfill(n)
        num2 = num2.zfill(n)
        
        i = n -1
        result = []
        carry = 0

        #for max length(which is same now)
        while i >= 0:
            # use ord or int to change string to number
            rem = (carry + int(num1[i]) + int(num2[i])) % 10
            carry = (carry + int(num1[i]) + int(num2[i])) // 10
            print(rem,carry, i)

            # conver to string and add
            result.append(str(rem))
            i-=1
        
        # add carry after last digit if any
        if carry:
            result.append(carry)
        print(result)

        # reverseresult because we started from least sign digit
        return ''.join(result[::-1])
```

## Attempt 4 · 2023-12-05 02:28 IST · Accepted · Python3

[submission 1112439779](https://leetcode.com/submissions/detail/1112439779/) · tests 317/317 · runtime 67 ms (beats 8.3%)

```python
class Solution:
    def addStrings(self, num1: str, num2: str) -> str:


        # zfill to max to match length
        n = max(len(num1), len(num2))
        num1 = num1.zfill(n)
        num2 = num2.zfill(n)
        
        i = n -1
        result = []
        carry = 0

        #for max length(which is same now)
        while i >= 0:
            # use ord or int to change string to number
            rem = (carry + int(num1[i]) + int(num2[i])) % 10
            carry = (carry + int(num1[i]) + int(num2[i])) // 10
            print(rem,carry, i)

            # conver to string and add
            result.append(str(rem))
            i-=1
        
        # add carry after last digit if any
        if carry:
            result.append(str(carry))
        print(result)

        # reverseresult because we started from least sign digit
        return ''.join(result[::-1])
```

## Attempt 5 · 2024-01-22 01:07 IST · Accepted · Python3

[submission 1152910148](https://leetcode.com/submissions/detail/1152910148/) · tests 317/317 · runtime 47 ms (beats 8.3%)

```python
class Solution:
    def addStrings(self, num1: str, num2: str) -> str:


        # zfill to max to match length
        n = max(len(num1), len(num2))
        num1 = num1.zfill(n)
        num2 = num2.zfill(n)
        
        i = n -1
        result = []
        carry = 0

        #for max length(which is same now)
        while i >= 0:
            # use ord or int to change string to number
            rem = (carry + int(num1[i]) + int(num2[i])) % 10
            carry = (carry + int(num1[i]) + int(num2[i])) // 10
            print(rem,carry, i)

            # conver to string and add
            result.append(str(rem))
            i-=1
        
        # add carry after last digit if any
        if carry:
            result.append(str(carry))
        print(result)

        # reverseresult because we started from least sign digit
        return ''.join(result[::-1])


    def addStrings(self, num1: str, num2: str) -> str:
        carry = 0
        result = []
        p1 = len(num1) -1
        p2=  len(num2) -1
        while p1>=0 or p2>=0:
            x1 = ord(num1[p1]) - ord('0') if p1>=0 else 0
            x2 = ord(num2[p2]) - ord('0') if p2>=0 else 0
            val = (x1 + x2 + carry) % 10
            carry = (x1 + x2 + carry)//10
            result.append(str(val))

            p1 -=1
            p2 -=1

        if carry:
            result.append(str(carry))

        return "".join(result[::-1])
```
