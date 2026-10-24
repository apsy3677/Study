# 273. Integer to English Words

[Problem](https://leetcode.com/problems/integer-to-english-words/) · Hard · Strings & Simulation → Chunked conversion

LeetCode tags: math, string, recursion

Attempts since Mar 2023: 8 · accepted: 2 · failed before first AC: 6

## Attempt 1 · 2024-01-12 20:50 IST · Wrong Answer · Python3

[submission 1144310777](https://leetcode.com/submissions/detail/1144310777/) · tests 545/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Your output:

```text
""
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 

            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)

        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 2 · 2024-01-12 20:51 IST · Wrong Answer · Python3

[submission 1144311146](https://leetcode.com/submissions/detail/1144311146/) · tests 545/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Your output:

```text
""
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 

            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 3 · 2024-01-12 20:52 IST · Wrong Answer · Python3

[submission 1144312194](https://leetcode.com/submissions/detail/1144312194/) · tests 545/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Your output:

```text
""
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 
            print(hundred, rest)
            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 4 · 2024-01-12 20:53 IST · Runtime Error · Python3

[submission 1144312872](https://leetcode.com/submissions/detail/1144312872/) · tests 24/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Runtime error:

```text
TypeError: can only concatenate str (not "NoneType") to str
    ^^^^^^^^^^^^^^^^^^^^^^^^^^
    result += three(remainder)
Line 88 in numberToWords (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().numberToWords(param_1)
Line 110 in _driver (Solution.py)
    _driver()
Line 121 in <module> (Solution.py)
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 
            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <=20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 5 · 2024-01-12 20:53 IST · Wrong Answer · Python3

[submission 1144313027](https://leetcode.com/submissions/detail/1144313027/) · tests 545/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Your output:

```text
""
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 
            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 6 · 2024-01-12 20:54 IST · Wrong Answer · Python3

[submission 1144313140](https://leetcode.com/submissions/detail/1144313140/) · tests 545/601

Failing input:

```text
20
```

Expected:

```text
"Twenty"
```

Your output:

```text
""
```

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 
            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            print(num)
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ''

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 7 · 2024-01-12 20:54 IST · Accepted · Python3

[submission 1144313417](https://leetcode.com/submissions/detail/1144313417/) · tests 601/601 · runtime 34 ms (beats 1.5%)

```python
class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0:
            return "Zero"

        def one(num):
            switcher = {
                1: 'One',
                2: 'Two',
                3: 'Three',
                4: 'Four',
                5: 'Five',
                6: 'Six',
                7: 'Seven',
                8: 'Eight',
                9: 'Nine'
            }
            return switcher.get(num)

        def two_less_20(num):
            switcher = {
                10: 'Ten',
                11: 'Eleven',
                12: 'Twelve',
                13: 'Thirteen',
                14: 'Fourteen',
                15: 'Fifteen',
                16: 'Sixteen',
                17: 'Seventeen',
                18: 'Eighteen',
                19: 'Nineteen'
            }
            return switcher.get(num)

        def ten(num):
            switcher = {
                2: 'Twenty',
                3: 'Thirty',
                4: 'Forty',
                5: 'Fifty',
                6: 'Sixty',
                7: 'Seventy',
                8: 'Eighty',
                9: 'Ninety'
            }
            return switcher.get(num)

        def three(num):
            hundred = num //100
            rest = num - hundred * 100 
            if hundred and rest:
                return one(hundred) + " Hundred " + two(rest)
            elif not hundred and rest:
                return two(rest)
            elif hundred and not rest:
                return one(hundred) +" Hundred"

        def two(num):
            print(num)
            if not num:
                return ''
            elif num < 10:
                return one(num)
            elif num <20:
                return two_less_20(num)
            else:
                tenner = num // 10
                rest = num - tenner*10
                return ten(tenner) + " " + one(rest) if rest else ten(tenner)

        # return ''
        billions = num // pow(10,9)
        millions = (num - billions * pow(10,9)) // pow(10,6)
        thousands = (num - billions * pow(10,9) - millions * pow(10,6)) //1000
        remainder = (num - billions * pow(10,9) - millions * pow(10,6) - thousands * 1000)
        print(remainder)
        result = ''
        if billions:
            result += " " if result else ''
            result += three(billions) +' Billion'
        if millions:
            result += " " if result else ''
            result += three(millions) +' Million'
        if thousands:
            result += " " if result else ''
            result += three(thousands) +' Thousand'
        if remainder:
            result += " " if result else ''
            result += three(remainder) 

        return result
```

## Attempt 8 · 2024-02-09 21:35 IST · Accepted · Python3

[submission 1170730755](https://leetcode.com/submissions/detail/1170730755/) · runtime 29 ms

_Code not returned by LeetCode._
