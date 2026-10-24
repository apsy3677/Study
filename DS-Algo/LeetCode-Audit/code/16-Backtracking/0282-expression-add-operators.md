# 282. Expression Add Operators

[Problem](https://leetcode.com/problems/expression-add-operators/) · Hard · Backtracking → Operator insertion

LeetCode tags: math, string, backtracking

Attempts since Mar 2023: 5 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-12-05 04:26 IST · Accepted · Python3

[submission 1112486977](https://leetcode.com/submissions/detail/1112486977/) · tests 23/23 · runtime 550 ms (beats 9.7%)

```python
class Solution:
    def addOperators(self, num: str, target: int) -> List[str]:
        results = []

        def backtrack(idx, last_operand, current_result, expr):
            if idx == len(num):
                if current_result == target:
                    results.append(expr)
                return

            for end in range(idx + 1, len(num) + 1):
                current_num_str = num[idx:end]
                current_num = int(current_num_str)

                # Skip if the number has leading zeros
                if len(current_num_str) != len(str(current_num)):
                    continue

                if idx == 0:
                    # First number, so just take it without any operator
                    backtrack(end, current_num, current_num, current_num_str)
                else:
                    # Addition
                    backtrack(end, current_num, current_result + current_num, expr + "+" + current_num_str)
                    # Subtraction
                    backtrack(end, -current_num, current_result - current_num, expr + "-" + current_num_str)
                    # Multiplication
                    backtrack(end, last_operand * current_num, current_result - last_operand + (last_operand * current_num), expr + "*" + current_num_str)

        backtrack(0, 0, 0, "")
        return results
```

## Attempt 2 · 2023-12-05 04:26 IST · Accepted · Python3

[submission 1112487028](https://leetcode.com/submissions/detail/1112487028/) · tests 23/23 · runtime 548 ms (beats 9.8%)

```python
class Solution:
    def addOperators(self, num: str, target: int) -> List[str]:
        results = []

        def backtrack(idx, last_operand, current_result, expr):
            if idx == len(num):
                if current_result == target:
                    results.append(expr)
                return

            for end in range(idx + 1, len(num) + 1):
                current_num_str = num[idx:end]
                current_num = int(current_num_str)

                # Skip if the number has leading zeros
                if len(current_num_str) != len(str(current_num)):
                    continue

                if idx == 0:
                    # First number, so just take it without any operator
                    backtrack(end, current_num, current_num, current_num_str)
                else:
                    # Addition
                    backtrack(end, current_num, current_result + current_num, expr + "+" + current_num_str)
                    # Subtraction
                    backtrack(end, -current_num, current_result - current_num, expr + "-" + current_num_str)
                    # Multiplication
                    backtrack(end, last_operand * current_num, current_result - last_operand + (last_operand * current_num), expr + "*" + current_num_str)

        backtrack(0, 0, 0, "")
        return results
```

## Attempt 3 · 2023-12-05 04:30 IST · Accepted · Python3

[submission 1112488328](https://leetcode.com/submissions/detail/1112488328/) · tests 23/23 · runtime 561 ms (beats 9.4%)

```python
class Solution:
    def addOperators(self, num: str, target: int) -> List[str]:
        results = []

        def backtrack(idx, last_operand, current_result, expr):
            # if reached the end
            # base condition
            if idx == len(num):
                # when result is target
                if current_result == target:
                    results.append(expr)
                return

            # for all prefixes
            for end in range(idx + 1, len(num) + 1):
                current_num_str = num[idx:end]
                current_num = int(current_num_str)

                # Skip if the number has leading zeros
                if len(current_num_str) != len(str(current_num)):
                    continue

                # don;t add any operator
                if idx == 0:
                    # First number, so just take it without any operator
                    backtrack(end, current_num, current_num, current_num_str)

                # try all operations
                else:
                    # Addition
                    backtrack(end, current_num, current_result + current_num, expr + "+" + current_num_str)
                    # Subtraction
                    backtrack(end, -current_num, current_result - current_num, expr + "-" + current_num_str)
                    # Multiplication
                    # for multiplication (result + last) * current = to make it result + last*current
                    
                    backtrack(end, last_operand * current_num, current_result - last_operand + (last_operand * current_num), expr + "*" + current_num_str)

        backtrack(0, 0, 0, "")
        return results
```

## Attempt 4 · 2023-12-29 23:20 IST · Wrong Answer · Python3

[submission 1131581265](https://leetcode.com/submissions/detail/1131581265/) · tests 20/23

Failing input:

```text
"123456789"
45
```

Expected:

```text
["1*2*3*4*5-6-78+9","1*2*3*4+5+6-7+8+9","1*2*3+4+5+6+7+8+9","1*2*3+4+5-6*7+8*9","1*2*3+4-5*6+7*8+9","1*2*3+4-5*6-7+8*9","1*2*3-4*5+6*7+8+9","1*2*3-4*5-6+7*8+9","1*2*3-4*5-6-7+8*9","1*2*3-45+67+8+9","1*2*34+56-7-8*9","1*2*34-5+6-7-8-9","1*2+3*4-56+78+9","1*2+3+4+5*6+7+8-9","1*2+3+4-5+6*7+8-9","1*2+3+4-5-6+7*8-9","1*2+3+45+67-8*9","1*2+3-45+6+7+8*9","1*2+34+5-6-7+8+9","1*2+34+56-7*8+9","1*2+34-5+6+7 ... [1891 more chars]
```

Your output:

```text
["1+2+3+4+5+6+7+8+9","1+2+3+4+5-6*7+8*9","1+2+3+4-5*6+7*8+9","1+2+3+4-5*6-7+8*9","1+2+3+4*5*6-7-8+9","1+2+3-4*5+6*7+8+9","1+2+3-4*5-6+7*8+9","1+2+3-4*5-6-7+8*9","1+2+3*4+5+6*7-8-9","1+2+3*4*5+6+7-8+9","1+2+3*4*5+6-7*8*9","1+2+3-45+67+8+9","1+2+3*45-6-78-9","1+2-3+4*5+6*7-8-9","1+2-3-4+5*6*7-8-9","1+2-3-4-5*6+7+8*9","1+2-3*4+5*6+7+8+9","1+2-3*4-5+6*7+8+9","1+2-3*4-5-6+7*8+9","1+2-3*4-5-6-7+8*9","1+ ... [2291 more chars]
```

```python
class Solution:
    def addOperators(self, num: str, target: int) -> List[str]:
        '''
        backtracking dfs - implicit
        - choices are after each position you can insert a operator
        at each position - to get all possible substrings
        for i in range(start+1, len(nums)+1) -> to generate prefix strings from 0:1 to 0:len(nums)

        for first time you need some expression before you can add operator 
        like 1+ 12+ to do that - check idx ==0 and call back with those prefix strings

        thigns to take care of 
        - zero prefix numbers
        - calculation in multiplication - (result + last) * current = to make it result + last*current. result has -> result + last instead of result 
        - one argument - result and other for string expression , one more for last operand required for multiplication which has more priority 
        '''
        results = []

        def backtrack(idx, last_operand, current_result, expr):
            # if reached the end
            # base condition
            if idx == len(num):
                # when result is target
                if current_result == target:
                    results.append(expr)
                return

            # for all prefixes substrings 
            for end in range(idx + 1, len(num) + 1):
                
                # get number prefix
                current_num_str = num[idx:end]
                current_num = int(current_num_str)

                # Skip if the number has leading zeros
                if len(current_num_str) != len(str(current_num)):
                    continue

                # for first time, get initial number
                if idx == 0:
                    # First number, so just take it without any operator
                    backtrack(end, current_num, current_num, current_num_str)

                # try all operations
                else:
                    # Addition
                    # 
                    backtrack(end, current_num, current_result + current_num, expr + "+" + current_num_str)
                    # Subtraction
                    print(expr + "-" + current_num_str)
                    backtrack(end, -current_num, current_result - current_num, expr + "-" + current_num_str)
                    # Multiplication
                    # for multiplication (result + last) * current = to make it result + last*current

                    print(expr + "*" + current_num_str)
                    backtrack(end, last_operand * current_num, current_result - last_operand + (last_operand * current_num), expr + "*" + current_num_str)

        backtrack(0, 0, 0, "")
        return results


    def addOperators(self, num: str, target: int) -> List[str]:

        
        def backtrack(start, result, lastVal,  expr):
            # base condition
            if start == len(num):
                if result == target:
                    exprs.append(expr)       
                return 
                

            # prefixes
            for end in range(start+1, len(num)+1):
                val = int(num[start:end])
                val_str = num[start:end]

                if len(val_str) != len(str(val)):
                    continue

                if start ==0:
                    backtrack(end, val, val, val_str)
                else:
                    # addition
                    backtrack(end, result+val, val, expr+'+'+val_str) 
                    
                    # sub
                    backtrack(end, result-val, -val,  expr+'-'+val_str)
                    
                    # mul
                    backtrack(end, result-lastVal + val * lastVal, val, expr+'*'+val_str)

        exprs =[]  
        backtrack(0,0,0,'')
        return exprs
```

## Attempt 5 · 2023-12-29 23:21 IST · Accepted · Python3

[submission 1131582212](https://leetcode.com/submissions/detail/1131582212/) · tests 23/23 · runtime 443 ms (beats 39.1%)

```python
class Solution:
    def addOperators(self, num: str, target: int) -> List[str]:
        '''
        backtracking dfs - implicit
        - choices are after each position you can insert a operator
        at each position - to get all possible substrings
        for i in range(start+1, len(nums)+1) -> to generate prefix strings from 0:1 to 0:len(nums)

        for first time you need some expression before you can add operator 
        like 1+ 12+ to do that - check idx ==0 and call back with those prefix strings

        thigns to take care of 
        - zero prefix numbers
        - calculation in multiplication - (result + last) * current = to make it result + last*current. result has -> result + last instead of result 
        - one argument - result and other for string expression , one more for last operand required for multiplication which has more priority 
        '''
        results = []

        def backtrack(idx, last_operand, current_result, expr):
            # if reached the end
            # base condition
            if idx == len(num):
                # when result is target
                if current_result == target:
                    results.append(expr)
                return

            # for all prefixes substrings 
            for end in range(idx + 1, len(num) + 1):
                
                # get number prefix
                current_num_str = num[idx:end]
                current_num = int(current_num_str)

                # Skip if the number has leading zeros
                if len(current_num_str) != len(str(current_num)):
                    continue

                # for first time, get initial number
                if idx == 0:
                    # First number, so just take it without any operator
                    backtrack(end, current_num, current_num, current_num_str)

                # try all operations
                else:
                    # Addition
                    # 
                    backtrack(end, current_num, current_result + current_num, expr + "+" + current_num_str)
                    # Subtraction
                    print(expr + "-" + current_num_str)
                    backtrack(end, -current_num, current_result - current_num, expr + "-" + current_num_str)
                    # Multiplication
                    # for multiplication (result + last) * current = to make it result + last*current

                    print(expr + "*" + current_num_str)
                    backtrack(end, last_operand * current_num, current_result - last_operand + (last_operand * current_num), expr + "*" + current_num_str)

        backtrack(0, 0, 0, "")
        return results


    def addOperators(self, num: str, target: int) -> List[str]:

        
        def backtrack(start, result, lastVal,  expr):
            # base condition
            if start == len(num):
                if result == target:
                    exprs.append(expr)       
                return 
                

            # prefixes
            for end in range(start+1, len(num)+1):
                val = int(num[start:end])
                val_str = num[start:end]

                if len(val_str) != len(str(val)):
                    continue

                if start ==0:
                    backtrack(end, val, val, val_str)
                else:
                    # addition
                    backtrack(end, result+val, val, expr+'+'+val_str) 
                    
                    # sub
                    backtrack(end, result-val, -val,  expr+'-'+val_str)
                    
                    # mul
                    backtrack(end, result-lastVal + val * lastVal, lastVal * val , expr+'*'+val_str)

        exprs =[]  
        backtrack(0,0,0,'')
        return exprs
```
