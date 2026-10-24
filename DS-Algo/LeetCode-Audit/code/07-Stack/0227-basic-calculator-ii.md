# 227. Basic Calculator II

[Problem](https://leetcode.com/problems/basic-calculator-ii/) · Medium · Stack → Expression parsing

LeetCode tags: math, string, stack

Attempts since Mar 2023: 9 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-04-01 18:21 IST · Accepted · C++

[submission 925895733](https://leetcode.com/submissions/detail/925895733/) · tests 110/110 · runtime 25 ms (beats 7.3%)

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

## Attempt 2 · 2023-12-21 05:03 IST · Wrong Answer · Python3

[submission 1124633796](https://leetcode.com/submissions/detail/1124633796/) · tests 49/111

Failing input:

```text
"42"
```

Expected:

```text
42
```

Your output:

```text
6
```

```python
class Solution:
    def calculate3(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result

        '''


        op = '+'
        num = 0
        lastNum = 0
        result = 0

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    result += lastNum
                    lastNum = num
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get + at index 1, you check the last operator +4, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation


        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                print('current char', c)
                print('operator',operator, current_number)
                if operator =='+':
                    stack.append(current_number)
                elif operator=='-':
                    stack.append(-current_number)
                elif operator =='*':
                    stack.append(stack.pop()* current_number)
                elif operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate(self, s: str) -> int:
        lastNum = 0
        op = '+'

        current = 0
        result=0

        for i, ch in enumerate(s):
            if ch.isdigit():
                current += int(ch)

            if ch in '+-/*' or i == len(s) -1:
                # for the last digit if operator before that was a +
                if op == '+':
                    result += lastNum
                    lastNum = current
                elif op == '-':
                    result += lastNum
                    lastNum = -current
                elif op =='*':
                    lastNum = lastNum * current
                elif op =='/':
                    lastNum = int(lastNum/current)
                op  = ch
                current = 0
        
        return result + lastNum
```

## Attempt 3 · 2023-12-21 05:03 IST · Accepted · Python3

[submission 1124633974](https://leetcode.com/submissions/detail/1124633974/) · tests 111/111 · runtime 97 ms (beats 11.7%)

```python
class Solution:
    def calculate3(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result

        '''


        op = '+'
        num = 0
        lastNum = 0
        result = 0

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    result += lastNum
                    lastNum = num
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get + at index 1, you check the last operator +4, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation


        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                print('current char', c)
                print('operator',operator, current_number)
                if operator =='+':
                    stack.append(current_number)
                elif operator=='-':
                    stack.append(-current_number)
                elif operator =='*':
                    stack.append(stack.pop()* current_number)
                elif operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate(self, s: str) -> int:
        lastNum = 0
        op = '+'

        current = 0
        result=0

        for i, ch in enumerate(s):
            if ch.isdigit():
                current = current*10 + int(ch)

            if ch in '+-/*' or i == len(s) -1:
                # for the last digit if operator before that was a +
                if op == '+':
                    result += lastNum
                    lastNum = current
                elif op == '-':
                    result += lastNum
                    lastNum = -current
                elif op =='*':
                    lastNum = lastNum * current
                elif op =='/':
                    lastNum = int(lastNum/current)
                op  = ch
                current = 0
        
        return result + lastNum
```

## Attempt 4 · 2024-01-02 01:30 IST · Accepted · Python3

[submission 1134032496](https://leetcode.com/submissions/detail/1134032496/) · tests 111/111 · runtime 104 ms (beats 10.1%)

```python
class Solution:
    def calculate3(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result

        '''


        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    result += lastNum
                    lastNum = num
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate(self, s: str) -> int:
        lastNum = 0
        op = '+'

        current = 0
        result=0

        for i, ch in enumerate(s):
            if ch.isdigit():
                current = current*10 + int(ch)

            if ch in '+-/*' or i == len(s) -1:
                # for the last digit if operator before that was a +
                if op == '+':
                    result += lastNum
                    lastNum = current
                elif op == '-':
                    result += lastNum
                    lastNum = -current
                elif op =='*':
                    lastNum = lastNum * current
                elif op =='/':
                    lastNum = int(lastNum/current)
                op  = ch
                current = 0
        
        return result + lastNum
```

## Attempt 5 · 2024-01-03 02:28 IST · Accepted · Python3

[submission 1135009242](https://leetcode.com/submissions/detail/1135009242/) · tests 111/111 · runtime 209 ms (beats 5.1%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result


        on multiply and division - update lastnum - with current * lastnum
        it takes priority so you multiple last and current immediately

        but for + -> update result and lastNum
        for */ -> update lastNum
        '''
        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    print(l, 'adding result', result, lastNum, num)
                    result += lastNum
                    lastNum = num
                    print(l, 'adding result', result, lastNum, num)
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate(self, s: str) -> int:
        # using the stack delay the operation for sum and substract
        # by adding numbers to stack
        # perform high precedence operations immediately / * -
        # and push result onto stack 
        stack = [] 
        num = 0
        last_op = '+'
        for i,c in enumerate(s):
            if c.isdigit():
                num = num * 10 + int(c)

            if c in '+-/*' or i ==len(s)-1:

                # low precedence
                # push on the stack
                if last_op == '+':
                    stack.append(num)
                if last_op == '-':
                    stack.append(-num)

                # higher precendence 
                # evaluate and push result
                if last_op == '*':
                    stack.append(stack.pop() * num)

                if last_op == '/':
                    stack.append( int(stack.pop() / num))

                last_op = c
                num = 0

        return sum(stack)

    def calculate(self, s: str) -> int:
        last_num = 0
        result = 0
        num = 0
        last_operator = '+'

        for idx, letter in enumerate(s):
            if letter.isdigit():
                num = num * 10 + int(letter)

            if letter in '+-/*' or idx == len(s) -1:

                # low precedence 
                # calculate last num and update last_num delay
                if last_operator == '+':
                    result += last_num
                    last_num = num
                if last_operator == '-':
                    result += last_num
                    last_num = -num

                if last_operator == '*':
                    last_num *= num

                if last_operator == '/':
                    last_num = int(last_num / num)

                last_operator = letter
                num = 0
        return result + last_num
```

## Attempt 6 · 2024-02-10 20:57 IST · Wrong Answer · Python3

[submission 1171501061](https://leetcode.com/submissions/detail/1171501061/) · tests 80/111

Failing input:

```text
"0-2147483647"
```

Expected:

```text
-2147483647
```

Your output:

```text
2147483647
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result


        on multiply and division - update lastnum - with current * lastnum
        it takes priority so you multiple last and current immediately

        but for + -> update result and lastNum
        for */ -> update lastNum
        '''
        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    print(l, 'adding result', result, lastNum, num)
                    result += lastNum
                    lastNum = num
                    print(l, 'adding result', result, lastNum, num)
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate5(self, s: str) -> int:
        # using the stack delay the operation for sum and substract
        # by adding numbers to stack
        # perform high precedence operations immediately / * -
        # and push result onto stack 
        stack = [] 
        num = 0
        last_op = '+'
        for i,c in enumerate(s):
            if c.isdigit():
                num = num * 10 + int(c)

            if c in '+-/*' or i ==len(s)-1:

                # low precedence
                # push on the stack
                if last_op == '+':
                    stack.append(num)
                if last_op == '-':
                    stack.append(-num)

                # higher precendence 
                # evaluate and push result
                if last_op == '*':
                    stack.append(stack.pop() * num)

                if last_op == '/':
                    stack.append( int(stack.pop() / num))

                last_op = c
                num = 0

        return sum(stack)

    def calculate3(self, s: str) -> int:
        last_num = 0
        result = 0
        num = 0
        last_operator = '+'

        for idx, letter in enumerate(s):
            if letter.isdigit():
                num = num * 10 + int(letter)

            if letter in '+-/*' or idx == len(s) -1:

                # low precedence 
                # calculate last num and update last_num delay
                if last_operator == '+':
                    result += last_num
                    last_num = num
                if last_operator == '-':
                    result += last_num
                    last_num = -num

                if last_operator == '*':
                    last_num *= num

                if last_operator == '/':
                    last_num = int(last_num / num)

                last_operator = letter
                num = 0
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
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-*/':
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
                
                last_op = ch
                curr_num = 0
            
            indx+=1

        return result  + last_num

    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        result = 0
        last_num = 0
        s += '+'
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-/*':
                if last_op == '+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result -= last_num
                    last_num = curr_num
                elif last_op =='*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num/curr_num)
                
                last_op = ch
                curr_num = 0
        
        return result + last_num
```

## Attempt 7 · 2024-02-10 20:58 IST · Wrong Answer · Python3

[submission 1171501329](https://leetcode.com/submissions/detail/1171501329/) · tests 75/111

Failing input:

```text
"1-1"
```

Expected:

```text
0
```

Your output:

```text
-2
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result


        on multiply and division - update lastnum - with current * lastnum
        it takes priority so you multiple last and current immediately

        but for + -> update result and lastNum
        for */ -> update lastNum
        '''
        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    print(l, 'adding result', result, lastNum, num)
                    result += lastNum
                    lastNum = num
                    print(l, 'adding result', result, lastNum, num)
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate5(self, s: str) -> int:
        # using the stack delay the operation for sum and substract
        # by adding numbers to stack
        # perform high precedence operations immediately / * -
        # and push result onto stack 
        stack = [] 
        num = 0
        last_op = '+'
        for i,c in enumerate(s):
            if c.isdigit():
                num = num * 10 + int(c)

            if c in '+-/*' or i ==len(s)-1:

                # low precedence
                # push on the stack
                if last_op == '+':
                    stack.append(num)
                if last_op == '-':
                    stack.append(-num)

                # higher precendence 
                # evaluate and push result
                if last_op == '*':
                    stack.append(stack.pop() * num)

                if last_op == '/':
                    stack.append( int(stack.pop() / num))

                last_op = c
                num = 0

        return sum(stack)

    def calculate3(self, s: str) -> int:
        last_num = 0
        result = 0
        num = 0
        last_operator = '+'

        for idx, letter in enumerate(s):
            if letter.isdigit():
                num = num * 10 + int(letter)

            if letter in '+-/*' or idx == len(s) -1:

                # low precedence 
                # calculate last num and update last_num delay
                if last_operator == '+':
                    result += last_num
                    last_num = num
                if last_operator == '-':
                    result += last_num
                    last_num = -num

                if last_operator == '*':
                    last_num *= num

                if last_operator == '/':
                    last_num = int(last_num / num)

                last_operator = letter
                num = 0
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
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-*/':
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
                
                last_op = ch
                curr_num = 0
            
            indx+=1

        return result  + last_num

    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        result = 0
        last_num = 0
        s += '+'
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-/*':
                if last_op == '+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result -= last_num
                    last_num = -curr_num
                elif last_op =='*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num/curr_num)
                
                last_op = ch
                curr_num = 0
        
        return result + last_num
```

## Attempt 8 · 2024-02-10 20:58 IST · Wrong Answer · Python3

[submission 1171501514](https://leetcode.com/submissions/detail/1171501514/) · tests 87/111

Failing input:

```text
"1+1-1"
```

Expected:

```text
1
```

Your output:

```text
0
```

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result


        on multiply and division - update lastnum - with current * lastnum
        it takes priority so you multiple last and current immediately

        but for + -> update result and lastNum
        for */ -> update lastNum
        '''
        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    print(l, 'adding result', result, lastNum, num)
                    result += lastNum
                    lastNum = num
                    print(l, 'adding result', result, lastNum, num)
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate5(self, s: str) -> int:
        # using the stack delay the operation for sum and substract
        # by adding numbers to stack
        # perform high precedence operations immediately / * -
        # and push result onto stack 
        stack = [] 
        num = 0
        last_op = '+'
        for i,c in enumerate(s):
            if c.isdigit():
                num = num * 10 + int(c)

            if c in '+-/*' or i ==len(s)-1:

                # low precedence
                # push on the stack
                if last_op == '+':
                    stack.append(num)
                if last_op == '-':
                    stack.append(-num)

                # higher precendence 
                # evaluate and push result
                if last_op == '*':
                    stack.append(stack.pop() * num)

                if last_op == '/':
                    stack.append( int(stack.pop() / num))

                last_op = c
                num = 0

        return sum(stack)

    def calculate3(self, s: str) -> int:
        last_num = 0
        result = 0
        num = 0
        last_operator = '+'

        for idx, letter in enumerate(s):
            if letter.isdigit():
                num = num * 10 + int(letter)

            if letter in '+-/*' or idx == len(s) -1:

                # low precedence 
                # calculate last num and update last_num delay
                if last_operator == '+':
                    result += last_num
                    last_num = num
                if last_operator == '-':
                    result += last_num
                    last_num = -num

                if last_operator == '*':
                    last_num *= num

                if last_operator == '/':
                    last_num = int(last_num / num)

                last_operator = letter
                num = 0
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
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-*/':
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
                
                last_op = ch
                curr_num = 0
            
            indx+=1

        return result  + last_num

    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        result = 0
        last_num = 0
        s += '+'
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-/*':
                if last_op == '+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result = last_num
                    last_num = -curr_num
                elif last_op =='*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num/curr_num)
                
                last_op = ch
                curr_num = 0
        
        return result + last_num
```

## Attempt 9 · 2024-02-10 20:58 IST · Accepted · Python3

[submission 1171501578](https://leetcode.com/submissions/detail/1171501578/) · tests 111/111 · runtime 77 ms (beats 20.5%)

```python
class Solution:
    def calculate(self, s: str) -> int:
        '''
        in stack approach you process binary set of numbers 
        for a+b*c -> you process a+b

        now think of it as result which has +a 
        when you get * you add a to the result 
        so you keep result, lastnum and currentnum
        along with current num, you will also keep lastnum which will point to a when your current pointer is at *
        at that time op would be + and at that time you would add lastnum a to the result


        on multiply and division - update lastnum - with current * lastnum
        it takes priority so you multiple last and current immediately

        but for + -> update result and lastNum
        for */ -> update lastNum
        '''
        op = '+'
        num = 0
        lastNum = 0 # keep current numbers with + - operations into lastNum
        
        result = 0
        # result will have result of numbers before last num
        # last num will be number before current num
        # when you get + - as last op -> you calculate the result +- last num
        # and assign current num as last num

        #1 . for each letter 
        for i, l in enumerate(s):
            if l.isdigit():
                num = num *10 + ord(l) - ord('0')

            if l in '+-/*' or len(s)-1 ==i:
                if op=='+': 
                    print(l, 'adding result', result, lastNum, num)
                    result += lastNum
                    lastNum = num
                    print(l, 'adding result', result, lastNum, num)
                if op=='-': 
                    result += lastNum
                    lastNum = -num
                if op=='*': 
                    lastNum = lastNum * num
                if op=='/': 
                    lastNum = int(lastNum/num)
                op = l
                num = 0
        return result + lastNum

    def calculate1(self, s: str) -> int:
        '''
        delay the operation when last operator was + -
        it assumes number as 4+3*5
        when the digits come -> you build current_number
        when operators comes -> you check last operator, that decides what to do with the current number
        liek when you get * at index 3, you check the last operator +3, so you decide to add it to stack
        when you get operator *, you check last operator which is + you decide to push 3 as well onto stack
        when you get 5 - you build number and also you go and check last operator, which is multiply, so you 


        because these are binary operators, you have to wait till you get both the numbers of the operation
        and then you perform the operation
        
        multiply and division has precendence and you perform thos operattions immediately
        '''

        last_operator = '+'
        current_number = 0
        stack=[] # keep track of numbers with sign + or -, so that it is easy to do final operation

        for i, c in enumerate(s):

            # build number when digits
            if c.isdigit():
                current_number = current_number * 10 + (ord(c) - ord('0'))
            

            # when you get operator or if its the last digit
            # check last operator and perform operation or delay and put it on stack
            if c in '+-/*' or i ==len(s)-1:
                # print('current char', c)
                # print('operator',operator, current_number)
                if last_operator =='+':
                    stack.append(current_number)
                elif last_operator=='-':
                    stack.append(-current_number)
                elif last_operator =='*':
                    stack.append(stack.pop()* current_number)
                elif last_operator =='/':
                    # based on the requirement do the int 
                    # if you do // for negative numbers, you will get lower digti like for -5//2 you will get -3
                    stack.append(int(stack.pop()/ current_number))
                print(stack)

                # reset number and set operator
                current_number = 0
                last_operator = c

        return sum(stack)

    def calculate2(self, s: str) -> int:
        '''
        lets work with two numbers at a time
        keep track of the operator in last_operator and numbers - last num in stack and current_num in variable
        when you get both the numbers
        - delay calculation for + - -> because if number is like 4+3*2 and you try to perform 4+3 it is incorrect
        - perform calculation if * or / because it takes priority accorindg to BODMAS rule of arithematic

        '''

        stack = []
        currentNum = 0
        last_operator = '+'

        #1. for each ch
        for i, l in enumerate(s):

            #2. build current number
            if l.isdigit():
                currentNum = currentNum * 10 + int(l)

            #3. if current char is a operator
            if l in '+-/*' or i == len(s)-1:
                if last_operator == '+':
                    stack.append(currentNum)
                elif last_operator == '-':
                    stack.append(-currentNum)
                elif last_operator =='*':
                    stack.append(stack.pop()*currentNum)
                elif last_operator =='/':
                    stack.append(int(stack.pop()/currentNum)) # this can cause issue with negative number 
                
                # 4. reset operator and number on next operator
                # this marks the end of current number and start of a new number
                last_operator = l
                currentNum = 0
            
        #5. return sum of stack
        return sum(stack)


    def calculate5(self, s: str) -> int:
        # using the stack delay the operation for sum and substract
        # by adding numbers to stack
        # perform high precedence operations immediately / * -
        # and push result onto stack 
        stack = [] 
        num = 0
        last_op = '+'
        for i,c in enumerate(s):
            if c.isdigit():
                num = num * 10 + int(c)

            if c in '+-/*' or i ==len(s)-1:

                # low precedence
                # push on the stack
                if last_op == '+':
                    stack.append(num)
                if last_op == '-':
                    stack.append(-num)

                # higher precendence 
                # evaluate and push result
                if last_op == '*':
                    stack.append(stack.pop() * num)

                if last_op == '/':
                    stack.append( int(stack.pop() / num))

                last_op = c
                num = 0

        return sum(stack)

    def calculate3(self, s: str) -> int:
        last_num = 0
        result = 0
        num = 0
        last_operator = '+'

        for idx, letter in enumerate(s):
            if letter.isdigit():
                num = num * 10 + int(letter)

            if letter in '+-/*' or idx == len(s) -1:

                # low precedence 
                # calculate last num and update last_num delay
                if last_operator == '+':
                    result += last_num
                    last_num = num
                if last_operator == '-':
                    result += last_num
                    last_num = -num

                if last_operator == '*':
                    last_num *= num

                if last_operator == '/':
                    last_num = int(last_num / num)

                last_operator = letter
                num = 0
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
        while indx < len(s):
            ch = s[indx]
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-*/':
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
                
                last_op = ch
                curr_num = 0
            
            indx+=1

        return result  + last_num

    def calculate(self, s: str) -> int:
        curr_num = 0
        last_op = '+'
        result = 0
        last_num = 0
        s += '+'
        for ch in s:
            if ch.isdigit():
                curr_num = curr_num * 10 + int(ch)
            elif ch in '+-/*':
                if last_op == '+':
                    result += last_num
                    last_num = curr_num
                elif last_op == '-':
                    result += last_num
                    last_num = -curr_num
                elif last_op =='*':
                    last_num *= curr_num
                elif last_op == '/':
                    last_num = int(last_num/curr_num)
                
                last_op = ch
                curr_num = 0
        
        return result + last_num
```
