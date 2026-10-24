# 224. Basic Calculator

[Problem](https://leetcode.com/problems/basic-calculator/) · Hard · Stack → Expression parsing with sign stack

LeetCode tags: math, string, stack, recursion

Attempts since Mar 2023: 9 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-12-30 03:40 IST · Accepted · Python3

[submission 1131734995](https://leetcode.com/submissions/detail/1131734995/) · tests 45/45 · runtime 54 ms (beats 32.1%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand
```

## Attempt 2 · 2024-02-09 21:26 IST · Wrong Answer · Python3

[submission 1170724697](https://leetcode.com/submissions/detail/1170724697/) · tests 26/45

Failing input:

```text
"1-(     -2)"
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
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                
                last_op = ch
                curr_num = 0  # Reset current number after processing operation
                
            # indx += 1

        return result  # Ensure last_num is included in the final result
```

## Attempt 3 · 2024-02-09 21:29 IST · Accepted · Python3

[submission 1170726441](https://leetcode.com/submissions/detail/1170726441/) · tests 45/45 · runtime 59 ms (beats 29.0%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
                    
            # indx += 1

        return result  # Ensure last_num is included in the final result
```

## Attempt 4 · 2024-02-10 20:48 IST · Wrong Answer · Python3

[submission 1171494279](https://leetcode.com/submissions/detail/1171494279/) · tests 23/45

Failing input:

```text
"1-(     -2)"
```

Expected:

```text
3
```

Your output:

```text
-3
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
         
        return result  # Ensure last_num is included in the final result

    def calculate(self, s: str) -> int:
        curr_num = 0
        stack =[]
        result = 0
        last_op = '+'
        s += '+'
        # print('s')
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)

            elif ch == '(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            if ch in '+-)':
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result -= curr_num
                
                if ch ==')':
                    curr_num, last_op = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
        return result
```

## Attempt 5 · 2024-02-10 20:49 IST · Accepted · Python3

[submission 1171495083](https://leetcode.com/submissions/detail/1171495083/) · tests 45/45 · runtime 62 ms (beats 26.5%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
         
        return result  # Ensure last_num is included in the final result

    def calculate5(self, s: str) -> int:
        curr_num = 0
        stack =[]
        result = 0
        last_op = '+'
        s += '+'
        # print('s')
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)

            elif ch == '(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            if ch in '+-)':
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result -= curr_num
                
                if ch ==')':
                    curr_num, last_op = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
        return result
```

## Attempt 6 · 2024-02-10 20:50 IST · Accepted · Python3

[submission 1171495883](https://leetcode.com/submissions/detail/1171495883/) · tests 45/45 · runtime 45 ms (beats 38.1%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
         
        return result  # Ensure last_num is included in the final result

    def calculate5(self, s: str) -> int:
        curr_num = 0
        stack =[]
        result = 0
        last_op = '+'
        s += '+'
        # print('s')
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)

            elif ch == '(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            if ch in '+-)':
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result -= curr_num
                
                if ch ==')':
                    curr_num, last_op = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
        return result
```

## Attempt 7 · 2024-02-10 20:50 IST · Wrong Answer · Python3

[submission 1171495955](https://leetcode.com/submissions/detail/1171495955/) · tests 23/45

Failing input:

```text
"1-(     -2)"
```

Expected:

```text
3
```

Your output:

```text
-3
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
         
        return result  # Ensure last_num is included in the final result

    def calculate(self, s: str) -> int:
        curr_num = 0
        stack =[]
        result = 0
        last_op = '+'
        s += '+'
        # print('s')
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)

            elif ch == '(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            if ch in '+-)':
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result -= curr_num
                
                if ch ==')':
                    curr_num, last_op = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
        return result
```

## Attempt 8 · 2024-02-10 20:53 IST · Accepted · Python3

[submission 1171498199](https://leetcode.com/submissions/detail/1171498199/) · tests 45/45 · runtime 62 ms (beats 26.5%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        immediately do the calculation since no *or /
        when you see the operator, evalute the last expression that is 
        result += sign * operand

        when you see a ( - put the result and isgn on to the stack
        and when you see a ) pop the sign multiply with current result and then add the old result

        time complexity - O(N)

        '''
        stack = []
        operand = 0
        res = 0
        sign = 1


        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            # if + like in 1-2[+]3 evaluate last expression
            elif ch == '+':
                res += sign * operand
                sign = 1
                operand = 0
            elif ch == '-':
                res += sign * operand
                sign = -1
                operand = 0

            # for a new opening 
            # 1-2+3-(4-5)
            # (4-5) will be the evaluated later
            # and - and result = 1-2+3 will be pushed on the stack
            elif ch == '(':
                # push the result on to stack
                stack.append(res)
                stack.append(sign)

                sign = 1
                res = 0

            # for a closing bracket
            # evaluate 4-5 
            # multiply by sign from stack
            # add the old result
            # reset operand
            elif ch == ')':
                res += sign * operand
                res *= stack.pop()
                res += stack.pop()
                operand = 0

        return res + sign* operand

    def calculate1(self, s: str) -> int:
        
        stack = []
        operand = 0
        result = 0
        sign = 1
        last_number=0
        for i, ch in enumerate(s):

            # if digit, make a number
            if ch.isdigit():
                operand = operand * 10 + int(ch)

            elif ch =='+':
                result += last_number
                last_number = operand* sign
                sign = 1
                operand = 0
            elif ch =='-':
                result += last_number
                last_number = operand* sign
                sign = -1
                operand = 0
            elif ch =='*':
                last_number = last_number * operand
                sign = 1
                operand = 0
            elif ch =='(':
                stack.append(result)
                stack.append(last_number)
                stack.append(sign)
                # operand = 0
                sign = 1
                result = 0
            elif ch ==')':
                result += last_number
                last_number = result * stack.pop()  # sign
                result = stack.pop()  # previous result
                last_number += stack.pop()  # previous last_number
                result = 0

        return last_number

    def calculate(self, s: str) -> int:
        stack = []
        num = 0
        result = 0
        sign = 1 # 1 for +
        for l in s:
            if l.isdigit():
                num = num * 10 + int(l)

            elif l in '+-':
                result += sign* num
                sign = -1 if l =='-' else 1
                num = 0

            elif l == '(':
                # add to stack
                stack.append(result) 
                stack.append(sign)
                
                # reset
                result = 0
                num = 0
                sign = 1
            elif l ==')':
                result += sign*num
                
                # add previous result
                result *= stack.pop()
                result += stack.pop()

                #reset
                num = 0
                sign = 1

        return result + sign*num
        
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            elif ch in '+-)' :
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result += -1* curr_num
                if ch ==')':
                    curr_num = result
                    result, last_op =  stack.pop()
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
         
        return result  # Ensure last_num is included in the final result

    def calculate(self, s: str) -> int:
        curr_num = 0
        stack =[]
        result = 0
        last_op = '+'
        s += '+'
        # print('s')
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)

            elif ch == '(':
                stack.append((result, last_op))
                result = 0
                last_op = '+'
            if ch in '+-)':
                if last_op == '+':
                    result += curr_num
                elif last_op == '-':
                    result -= curr_num
                
                if ch ==')':
                    curr_num = result
                    result, last_op = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
        return result
```

## Attempt 9 · 2024-02-19 15:46 IST · Accepted · C++

[submission 1179746617](https://leetcode.com/submissions/detail/1179746617/) · tests 46/46 · runtime 10 ms (beats 9.6%)

```cpp
class Solution {
public:
    int calculate(string s) {
        int result = 0;
        int currentNumber = 0;
        int sign = 1;
        stack<int> st;

        for (char c : s) {
            if (isdigit(c)) {
                currentNumber = currentNumber * 10 + (c - '0');
            } else if (c == '+' || c == '-') {
                result += sign * currentNumber;
                currentNumber = 0;
                sign = (c == '+') ? 1 : -1;
            } else if (c == '(') {
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;
            } else if (c == ')') {
                result += sign * currentNumber;
                currentNumber = 0;
                result *= st.top(); st.pop();
                result += st.top(); st.pop();
            }
        }
        result += sign * currentNumber;

        return result;
    }
};
```
