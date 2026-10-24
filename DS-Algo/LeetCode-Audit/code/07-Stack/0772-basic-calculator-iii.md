# 772. Basic Calculator III

[Problem](https://leetcode.com/problems/basic-calculator-iii/) · Hard · Stack → Expression parsing with parentheses

LeetCode tags: math, string, stack, recursion

Attempts since Mar 2023: 10 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-04-01 18:11 IST · Accepted · C++

[submission 925892098](https://leetcode.com/submissions/detail/925892098/) · tests 79/79 · runtime 5 ms (beats 33.8%)

```cpp
class Solution {
    int DFS(queue<char> &Q)
    {
        long long int num =0, sum=0, prev=0;
        char prevop = '+';
        while(!Q.empty())
        {
            char c = Q.front(); Q.pop();
            if(isdigit(static_cast<unsigned char>(c)))
                num = num*10 + c-'0';
            else if(c=='(')
                num = DFS(Q);
            else
            {
                switch(prevop)
                {
                    case '+':
                        sum+=prev;
                        prev = num;
                        break;
                    case '-':
                        sum+=prev;
                        prev = -num;
                        break;
                    case '*':
                        prev*=num;
                        break;
                    case '/':
                        prev/=num;
                        break;
                }
                prevop = c;
                num = 0;
                if(c==')')
                    break;
            }
        }
        return sum+prev;
    }
public:
    int calculate(string s) {
        queue<char> Q;
        int l = s.length();
        for(int i=0; i<l; i++)
        {
            if(isspace(static_cast<unsigned char>(s[i]) ))
                continue;
            Q.push(s[i]);
        }
        Q.push(' ');
        return DFS(Q);
    }
};
```

## Attempt 2 · 2023-12-30 04:12 IST · Wrong Answer · Python3

[submission 1131749449](https://leetcode.com/submissions/detail/1131749449/) · tests 25/79

Failing input:

```text
"2*(5+5*2)/3+(6/2+8)"
```

Expected:

```text
21
```

Your output:

```text
9
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand += operand*10 + int(ch)

            if ch in '+-/*' or len(s)-1 == i:
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            if ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            elif ch == ')':
                curr = 0
                while type(stack[-1]) == int:
                    curr += stack.pop()
                last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 3 · 2023-12-30 04:12 IST · Wrong Answer · Python3

[submission 1131749772](https://leetcode.com/submissions/detail/1131749772/) · tests 28/79

Failing input:

```text
"2*(5+5*2)/3+(6/2+8)"
```

Expected:

```text
21
```

Your output:

```text
9
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            if ch in '+-/*' or len(s)-1 == i:
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            if ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            elif ch == ')':
                curr = 0
                while type(stack[-1]) == int:
                    curr += stack.pop()
                last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 4 · 2023-12-30 04:14 IST · Wrong Answer · Python3

[submission 1131750265](https://leetcode.com/submissions/detail/1131750265/) · tests 28/79

Failing input:

```text
"2*(5+5*2)/3+(6/2+8)"
```

Expected:

```text
21
```

Your output:

```text
9
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            if ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            elif ch == ')':
                curr = 0
                while type(stack[-1]) == int:
                    curr += stack.pop()
                last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 5 · 2023-12-30 04:16 IST · Accepted · Python3

[submission 1131751327](https://leetcode.com/submissions/detail/1131751327/) · tests 79/79 · runtime 85 ms (beats 5.7%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            else:
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            
                if ch == ')':
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 6 · 2023-12-30 04:18 IST · Wrong Answer · Python3

[submission 1131752384](https://leetcode.com/submissions/detail/1131752384/) · tests 23/79

Failing input:

```text
"2*(5+5*2)/3+(6/2+8)"
```

Expected:

```text
21
```

Your output:

```text
9
```

```python
class Solution1:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@' # run one more time 
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            else:
            # always check last operator not the current character
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))

                # reset operand and set last_operator 
                operand = 0
                last_op = ch
            
                if ch == ')':
                    # correctly set the operator and operand
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)


class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            if ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            elif ch == ')':
                operand = 0
                while type(stack[-1]) == int:
                    operand += stack.pop()
                last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 7 · 2023-12-30 04:19 IST · Wrong Answer · Python3

[submission 1131752416](https://leetcode.com/submissions/detail/1131752416/) · tests 23/79

Failing input:

```text
"2*(5+5*2)/3+(6/2+8)"
```

Expected:

```text
21
```

Your output:

```text
9
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@' # run one more time 
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            else:
            # always check last operator not the current character
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))

                # reset operand and set last_operator 
                operand = 0
                last_op = ch
            
                if ch == ')':
                    # correctly set the operator and operand
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)


class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@'
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))
                operand = 0
                last_op = ch
            if ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            elif ch == ')':
                operand = 0
                while type(stack[-1]) == int:
                    operand += stack.pop()
                last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 8 · 2023-12-30 04:19 IST · Accepted · Python3

[submission 1131752448](https://leetcode.com/submissions/detail/1131752448/) · tests 79/79 · runtime 48 ms (beats 5.7%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@' # run one more time 
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # add operator and 
                stack.append(last_op)
                last_op = '+'
            else:
            # always check last operator not the current character
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))

                # reset operand and set last_operator 
                operand = 0
                last_op = ch
            
                if ch == ')':
                    # correctly set the operator and operand
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 9 · 2024-02-09 20:01 IST · Accepted · Python3

[submission 1170664443](https://leetcode.com/submissions/detail/1170664443/) · tests 79/79 · runtime 37 ms (beats 5.7%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@' # run one more time 
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # push the operator 
                stack.append(last_op)
                last_op = '+'
            else:
            # always check last operator not the current character
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))

                # reset operand and set last_operator 
                operand = 0
                last_op = ch
            
                if ch == ')':
                    # correctly set the operator and operand
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)
```

## Attempt 10 · 2024-02-09 21:15 IST · Accepted · Python3

[submission 1170716534](https://leetcode.com/submissions/detail/1170716534/) · tests 79/79 · runtime 49 ms (beats 5.7%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        we process items when we get a operator and evaluate the last operator
        1+2-3 when we get - we decide what to do with +2 
        ebcause of the reason that that - could be a * and would get priority 
        
        the stack approach where we have operators like */ are says that 
        if you have + - - push the 
        '''
        operand = 0
        last_op = '+'
        stack = []
        s+='@' # run one more time 
        for i, ch in enumerate(s):
            if ch.isdigit():
                operand = operand*10 + int(ch)

            elif ch == '(':
                # push the operator 
                stack.append(last_op)
                last_op = '+'
            else:
            # always check last operator not the current character
            #if ch in '+-/*' or ch =='@':
                if last_op == '+':
                    stack.append(operand)
                elif last_op =='-':
                    stack.append(-operand)
                elif last_op == '*':
                    stack.append(stack.pop()*operand)
                elif last_op == '/':
                    stack.append(int(stack.pop()/operand))

                # reset operand and set last_operator 
                operand = 0
                last_op = ch
            
                if ch == ')':
                    # correctly set the operator and operand
                    while type(stack[-1]) == int:
                        operand += stack.pop()
                    last_op = stack.pop()
                
        # print(stack)
        return sum(stack)

class Solution:
    def calculate2(self, s: str) -> int:
        
        def calc(s):
            num = 0
            op = '+'
            res = 0
            stack=[]
            i=0
            
            while i<len(s):
                
                l = s[i]
                if l.isdigit():
                    num = num * 10 + int(l)
                
                if l in '+-/*' :
                    if op =='+':
                        stack.append(num)
                    if op =='-':
                        stack.append(-num)
                    if op =='*':
                        stack.append(stack.pop()* num)
                    if op =='/':
                        stack.append(int(stack.pop()/ num))
                    op=l
                    num=0
                
                if l =='(':
                    closing_pos, sum1 = calc(s[i+1:])
                    num = sum1
                    i+=closing_pos
                    
                if l ==')':
                    return (i+1, sum(stack))
                i+=1
                 
            return sum(stack)
        
        return calc(s+'+')
    
    def calculate(self, s: str) -> int:
        
        def calc(s):
            num = 0
            op = '+'
            res = 0
            lastNumber = 0
            i=0
            
            while i<len(s):
                
                l = s[i]
                if l.isdigit():
                    num = num * 10 + int(l)
                
                if l in '+-/*' or l ==')':
                    if op in '+-':
                        res += lastNumber
                        lastNumber = -num if op=='-' else num
                    if op =='*':
                        lastNumber = lastNumber * num
                    if op =='/':
                        lastNumber = int(lastNumber / num)
                    op=l
                    num=0
                    
                if l =='(':
                    closing_pos, sum1 = calc(s[i+1:])
                    num = sum1
                    i+=closing_pos
                    
                if l ==')':
                    return (i+1, res+lastNumber)
                i+=1
                 
            return res+lastNumber
        
        return calc(s+'+')


class Solution:
    def calculate(self, s: str) -> int:
        stack = []
        result = last_num = cur_num = 0
        last_op = '+'
        s += '+'
        for c in s:
            if c.isdigit():
                cur_num = cur_num * 10 + int(c)
            if c == '(':
                stack.append(result)
                stack.append(last_num)
                stack.append(last_op)
                result = last_num = 0
                last_op = '+'
            elif c in '+-*/)':
                if last_op == '+':
                    result += last_num
                    last_num = cur_num
                elif last_op == '-':
                    result += last_num
                    last_num = -cur_num
                elif last_op == '*':
                    last_num *= cur_num
                else:
                    last_num = int(last_num / cur_num)
                print(last_num, result, cur_num)
                if c == ')':
                    cur_num = result + last_num
                    last_op = stack.pop()
                    last_num = stack.pop()
                    result = stack.pop()
                else:
                    last_op = c
                    cur_num = 0
        return result + last_num

    def calculate(self, s: str) -> int:
        '''
        if you get + - as previous add last expression to result 
        don't calculate current - hold it in last_num because if next is a multiplication you first want to
        do multiplication/division before adding to the result
        2+3*4
        '''
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s+'+'
        stack = []
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch =='(':
                stack.append(result)
                stack.append(last_num)
                stack.append(last_op)
                last_op = '+'
                last_num = result = 0
            elif ch in '+-*/' or ch==')':
                if last_op =='+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result += last_num
                    last_num = -curr_num
                elif last_op == '*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num / curr_num)
                
                
                if ch == ')':
                    cur_num = result + last_num
                    last_op = stack.pop()
                    last_num = stack.pop()
                    result = stack.pop()
                else:
                    last_op = ch
                    curr_num = 0
                
            indx+=1

        return result  + last_num

    #class Solution:
    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        indx = 0
        last_num = 0
        result = 0
        s = s + '+'  # Append '+' to ensure the last operation is processed
        stack = []
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch == '(':
                # Save the current state before going into a parenthesis
                stack.append((result, last_num, last_op))
                last_op = '+'
                result, last_num = 0, 0  # Reset for new expression inside parentheses
            elif ch in '+-*/' or ch == ')':
                # Process the last operation before updating last_op
                if last_op == '+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result += last_num
                    last_num = -curr_num
                elif last_op == '*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num / curr_num)
                
                if ch == ')':
                    # Process the closing parenthesis
                    curr_num = result + last_num  # Finalize inner expression result
                    result, last_num, last_op = stack.pop()  # Restore the state
                    #curr_num = temp  # The result of the inner expression becomes the current number for the outer level
                else:
                    last_op = ch
                    curr_num = 0  # Reset current number after processing operation
                
            indx += 1

        return result + last_num  # Ensure last_num is included in the final result
```
