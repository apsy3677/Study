# 65. Valid Number

[Problem](https://leetcode.com/problems/valid-number/) · Hard · Strings & Simulation → Parsing / state machine

LeetCode tags: string

Attempts since Mar 2023: 7 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-11-23 03:24 IST · Accepted · Python3

[submission 1104464385](https://leetcode.com/submissions/detail/1104464385/) · tests 1493/1493 · runtime 52 ms (beats 3.8%)

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                seenDigit = False
            else:
                return False
            
        return seenDigit
```

## Attempt 2 · 2023-12-04 12:03 IST · Accepted · Python3

[submission 1111973554](https://leetcode.com/submissions/detail/1111973554/) · tests 1493/1493 · runtime 38 ms (beats 3.8%)

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        '.' -> seen_dot and seen_exp 232e3.4 - invalid 


        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                seenDigit = False
            else:
                return False
            
        return seenDigit
```

## Attempt 3 · 2024-01-01 09:19 IST · Wrong Answer · Python3

[submission 1133405320](https://leetcode.com/submissions/detail/1133405320/) · tests 1443/1494

Failing input:

```text
"0e"
```

Expected:

```text
false
```

Your output:

```text
true
```

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        te2e3+.4 -> invalid - all invalid conditions 
        
        '.' -> seen_dot and seen_exp 232e3.4 - invalid .343 is valid
        '+-' -> if i>0 previous has to be Ee - 232e3+.4
        eE -> seen_exp or not seen_digit -> invalid also, set seen_digit to False - 
        evertyhing else -> invalid

        simplified - other than check dot and dot comes only once
        for dot -> no exponent before 
        for exponent -> atleast digit before
        +- -> expo should be before this
        . -> e -> digit
        + -> e
        -/.ed
        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):

            # if digit
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            
            
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                # reset seenDigit
                # seenDigit = False
            
            # everything else is invalid
            else:
                return False
            
        # only digits is valid
        return seenDigit
```

## Attempt 4 · 2024-02-02 09:15 IST · Accepted · Python3

[submission 1163545671](https://leetcode.com/submissions/detail/1163545671/) · tests 1494/1494 · runtime 34 ms (beats 3.8%)

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        te2e3+.4 -> invalid - all invalid conditions 
        
        '.' -> seen_dot and seen_exp 232e3.4 - invalid .343 is valid
        '+-' -> if i>0 previous has to be Ee - 232e3+.4
        eE -> seen_exp or not seen_digit -> invalid also, set seen_digit to False - 
        evertyhing else -> invalid

        simplified - other than check dot and dot comes only once
        for dot -> no exponent before 
        for exponent -> atleast digit before
        +- -> expo should be before this
        . -> e -> digit
        + -> e
        -/.ed
        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):

            # if digit
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            
            
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                # reset seenDigit
                seenDigit = False
            
            # everything else is invalid
            else:
                return False
            
        # only digits is valid
        return seenDigit
```

## Attempt 5 · 2024-02-10 00:51 IST · Wrong Answer · Python3

[submission 1170889769](https://leetcode.com/submissions/detail/1170889769/) · tests 1073/1494

Failing input:

```text
".1"
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        te2e3+.4 -> invalid - all invalid conditions 
        
        '.' -> seen_dot and seen_exp 232e3.4 - invalid .343 is valid
        '+-' -> if i>0 previous has to be Ee - 232e3+.4
        eE -> seen_exp or not seen_digit -> invalid also, set seen_digit to False - 
        evertyhing else -> invalid

        simplified - other than check dot and dot comes only once
        for dot -> no exponent before 
        for exponent -> atleast digit before
        +- -> expo should be before this
        . -> e -> digit
        + -> e
        -/.ed
        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):

            # if digit
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            
            
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                # reset seenDigit
                seenDigit = False
            
            # everything else is invalid
            else:
                return False
            
        # only digits is valid
        return seenDigit

    def isNumber(self, s: str) -> bool:
        seen_digit = False
        seen_dot = False
        seen_expo = False
        seen_sign = False

        for letter_indx, letter in enumerate(s):
            if letter.isdigit():
                seen_digit = True

            elif letter in '+-':
                if letter_indx >0 and s[letter_indx-1] not in 'eE':
                    return False
            
            elif letter =='.':
                if seen_dot or not seen_expo:
                    return False

            elif letter.lower() =='e':
                if seen_expo or not seen_digit:
                    return False

            else:
                return False

        return seen_digit
```

## Attempt 6 · 2024-02-10 00:52 IST · Wrong Answer · Python3

[submission 1170890107](https://leetcode.com/submissions/detail/1170890107/) · tests 1115/1494

Failing input:

```text
".1"
```

Expected:

```text
true
```

Your output:

```text
false
```

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        te2e3+.4 -> invalid - all invalid conditions 
        
        '.' -> seen_dot and seen_exp 232e3.4 - invalid .343 is valid
        '+-' -> if i>0 previous has to be Ee - 232e3+.4
        eE -> seen_exp or not seen_digit -> invalid also, set seen_digit to False - 
        evertyhing else -> invalid

        simplified - other than check dot and dot comes only once
        for dot -> no exponent before 
        for exponent -> atleast digit before
        +- -> expo should be before this
        . -> e -> digit
        + -> e
        -/.ed
        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):

            # if digit
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            
            
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                # reset seenDigit
                seenDigit = False
            
            # everything else is invalid
            else:
                return False
            
        # only digits is valid
        return seenDigit

    def isNumber(self, s: str) -> bool:
        seen_digit = False
        seen_dot = False
        seen_expo = False
        seen_sign = False

        for letter_indx, letter in enumerate(s):
            if letter.isdigit():
                seen_digit = True

            elif letter in '+-':
                if letter_indx >0 and s[letter_indx-1] not in 'eE':
                    return False
            
            elif letter =='.':
                if seen_dot or not seen_expo:
                    return False
                seen_dot = True

            elif letter.lower() =='e':
                if seen_expo or not seen_digit:
                    return False
                seen_digit = False
                seen_expo = True

            else:
                return False

        return seen_digit
```

## Attempt 7 · 2024-02-10 00:52 IST · Accepted · Python3

[submission 1170890636](https://leetcode.com/submissions/detail/1170890636/) · tests 1494/1494 · runtime 34 ms (beats 3.8%)

```python
class Solution:
    def isNumber(self, s: str) -> bool:
        '''
        te2e3+.4 -> invalid - all invalid conditions 
        
        '.' -> seen_dot and seen_exp 232e3.4 - invalid .343 is valid
        '+-' -> if i>0 previous has to be Ee - 232e3+.4
        eE -> seen_exp or not seen_digit -> invalid also, set seen_digit to False - 
        evertyhing else -> invalid

        simplified - other than check dot and dot comes only once
        for dot -> no exponent before 
        for exponent -> atleast digit before
        +- -> expo should be before this
        . -> e -> digit
        + -> e
        -/.ed
        '''
        seenExp = False
        seenDigit = False
        seenDecimal = False
        seenSign = False

        for i, l in enumerate(s):

            # if digit
            if l.isdigit():
                seenDigit = True

            elif l=='.':
                if seenDecimal or seenExp:
                    return False
                seenDecimal = True
                # seenDigit =False

            elif l in '+-':
                if i>0 and s[i-1] not in 'eE':
                    return False
            
            
            elif l in 'eE':
                if seenExp or not seenDigit:
                    return False
                seenExp= True
                # reset seenDigit
                seenDigit = False
            
            # everything else is invalid
            else:
                return False
            
        # only digits is valid
        return seenDigit

    def isNumber(self, s: str) -> bool:
        seen_digit = False
        seen_dot = False
        seen_expo = False
        seen_sign = False

        for letter_indx, letter in enumerate(s):
            if letter.isdigit():
                seen_digit = True

            elif letter in '+-':
                if letter_indx >0 and s[letter_indx-1] not in 'eE':
                    return False
            
            elif letter =='.':
                if seen_dot or  seen_expo:
                    return False
                seen_dot = True

            elif letter.lower() =='e':
                if seen_expo or not seen_digit:
                    return False
                seen_digit = False
                seen_expo = True

            else:
                return False

        return seen_digit
```
