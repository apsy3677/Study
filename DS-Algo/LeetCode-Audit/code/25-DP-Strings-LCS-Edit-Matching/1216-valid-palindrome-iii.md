# 1216. Valid Palindrome III

[Problem](https://leetcode.com/problems/valid-palindrome-iii/) · Hard · DP: Strings (LCS, Edit, Matching) → Via longest palindromic subsequence

LeetCode tags: string, dynamic-programming

Attempts since Mar 2023: 11 · accepted: 2 · failed before first AC: 7

## Attempt 1 · 2023-11-28 07:26 IST · Wrong Answer · Python3

[submission 1107822796](https://leetcode.com/submissions/detail/1107822796/) · tests 25/51

Failing input:

```text
"bacabaaa"
2
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
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r):
            count=0
            while l<r:
                if s[l]!=s[r]:
                    if count > k:
                        return False
                    count +=1
                    return checkPalin(l+1, r) or  checkPalin(l, r-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1)
```

## Attempt 2 · 2023-11-28 07:27 IST · Wrong Answer · Python3

[submission 1107823219](https://leetcode.com/submissions/detail/1107823219/) · tests 39/51

Failing input:

```text
"bacabaaa"
2
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
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    if k<0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 3 · 2023-11-28 07:36 IST · Wrong Answer · Python3

[submission 1107826698](https://leetcode.com/submissions/detail/1107826698/) · tests 33/51

Failing input:

```text
"bacabaaa"
2
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
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    if k<0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                else:
                    checkPalin(l+1, r-1,k-1) 

                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 4 · 2023-11-28 07:58 IST · Wrong Answer · Python3

[submission 1107835804](https://leetcode.com/submissions/detail/1107835804/) · tests 39/51

Failing input:

```text
"bacabaaa"
2
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
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    print('checking', s[l], s[r])
                    if k<0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 5 · 2023-11-28 07:59 IST · Wrong Answer · Python3

[submission 1107836174](https://leetcode.com/submissions/detail/1107836174/) · tests 39/51

Failing input:

```text
"bacabaaa"
2
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
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    print('checking', s[l], s[r])
                    print(k)
                    if k<0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 6 · 2023-11-28 07:59 IST · Output Limit Exceeded · Python3

[submission 1107836433](https://leetcode.com/submissions/detail/1107836433/) · tests 44/51

Failing input:

```text
"fcgihcgeadfehgiabegbiahbeadbiafgcfchbcacedbificicihibaeehbffeidiaiighceegbfdggggcfaiibefbgeegbcgeadcfdfegfghebcfceiabiagehhibiheddbcgdebdcfegaiahibcfhheggbheebfdahgcfcahafecfehgcgdabbghddeadecidicchfgicbdbecibddfcgbiadiffcifiggigdeedbiiihfgehhdegcaffaggiidiifgfigfiaiicadceefbhicfhbcachacaeiefdcchegfbifhaeafdehicfgbecahidgdagigbhiffhcccdhfdbd"
216
```

Expected:

```text
true
```

```python
class Solution:
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 7 · 2023-11-28 07:59 IST · Time Limit Exceeded · Python3

[submission 1107836532](https://leetcode.com/submissions/detail/1107836532/) · tests 44/51

Failing input:

```text
"fcgihcgeadfehgiabegbiahbeadbiafgcfchbcacedbificicihibaeehbffeidiaiighceegbfdggggcfaiibefbgeegbcgeadcfdfegfghebcfceiabiagehhibiheddbcgdebdcfegaiahibcfhheggbheebfdahgcfcahafecfehgcgdabbghddeadecidicchfgicbdbecibddfcgbiadiffcifiggigdeedbiiihfgehhdegcaffaggiidiifgfigfiaiicadceefbhicfhbcachacaeiefdcchegfbifhaeafdehicfgbecahidgdagigbhiffhcccdhfdbd"
216
```

Expected:

```text
true
```

```python
class Solution:
    def isValidPalindrome(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    #print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)
```

## Attempt 8 · 2023-11-28 08:15 IST · Accepted · Python3

[submission 1107843502](https://leetcode.com/submissions/detail/1107843502/) · tests 51/51 · runtime 402 ms (beats 36.3%)

```python
class Solution:
    def isValidPalindrome1(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    #print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)

    def isValidPalindrome(self, s: str, k: int) -> bool:
        memo ={}

        def dp(i,j):
            # base case
            if i>=j:
                return 0

            # check memo
            if (i,j) in memo:
                return memo[(i,j)]

            # recursion with memo
            if s[i] == s[j]:
                memo[(i,j)] = dp(i+1, j-1)
            else:
                memo[(i,j)] = 1+ min(dp(i+1, j), dp(i, j-1))

            return memo[(i,j)]

        return dp(0,len(s)-1) <=k
```

## Attempt 9 · 2023-12-05 04:14 IST · Runtime Error · Python3

[submission 1112482563](https://leetcode.com/submissions/detail/1112482563/) · tests 0/51

Failing input:

```text
"abcdeca"
2
```

Expected:

```text
true
```

Runtime error:

```text
IndentationError: unexpected indent
    memo ={}
Line 23  (Solution.py)
```

```python
class Solution:
    def isValidPalindrome1(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    #print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)

    def isValidPalindrome(self, s: str, k: int) -> bool:
      '''
      table of number of removals required to make string i to j a palindrom
      memo table has number of removals
      if two characters are not same from left and right we add 1 and call min(left, right)
      '''
        memo ={}

        def dp(i,j):
            # base case
            if i>=j:
                return 0

            # check memo
            if (i,j) in memo:
                return memo[(i,j)]

            # recursion with memo
            if s[i] == s[j]:
                memo[(i,j)] = dp(i+1, j-1)
            else:
                memo[(i,j)] = 1+ min(dp(i+1, j), dp(i, j-1))

            return memo[(i,j)]

        return dp(0,len(s)-1) <=k
```

## Attempt 10 · 2023-12-05 04:14 IST · Accepted · Python3

[submission 1112482609](https://leetcode.com/submissions/detail/1112482609/) · tests 51/51 · runtime 400 ms (beats 36.3%)

```python
class Solution:
    def isValidPalindrome1(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    #print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)

    def isValidPalindrome(self, s: str, k: int) -> bool:
        '''
        table of number of removals required to make string i to j a palindrom
        memo table has number of removals
        if two characters are not same from left and right we add 1 and call min(left, right)
        '''
        memo ={}

        def dp(i,j):
            # base case
            if i>=j:
                return 0

            # check memo
            if (i,j) in memo:
                return memo[(i,j)]

            # recursion with memo
            if s[i] == s[j]:
                memo[(i,j)] = dp(i+1, j-1)
            else:
                memo[(i,j)] = 1+ min(dp(i+1, j), dp(i, j-1))

            return memo[(i,j)]

        return dp(0,len(s)-1) <=k
```

## Attempt 11 · 2024-01-05 11:59 IST · Time Limit Exceeded · Python3

[submission 1137358441](https://leetcode.com/submissions/detail/1137358441/) · tests 44/51

Failing input:

```text
"fcgihcgeadfehgiabegbiahbeadbiafgcfchbcacedbificicihibaeehbffeidiaiighceegbfdggggcfaiibefbgeegbcgeadcfdfegfghebcfceiabiagehhibiheddbcgdebdcfegaiahibcfhheggbheebfdahgcfcahafecfehgcgdabbghddeadecidicchfgicbdbecibddfcgbiadiffcifiggigdeedbiiihfgehhdegcaffaggiidiifgfigfiaiicadceefbhicfhbcachacaeiefdcchegfbifhaeafdehicfgbecahidgdagigbhiffhcccdhfdbd"
216
```

Expected:

```text
true
```

```python
class Solution:
    def isValidPalindrome1(self, s: str, k: int) -> bool:
        
        def checkPalin(l, r,k):
            while l<r:
                if s[l]!=s[r]:
                    #print('checking', s[l], s[r])
                    if k<=0:
                        return False
                    return checkPalin(l+1, r,k-1) or  checkPalin(l, r-1,k-1)
                l+=1
                r-=1
            return True

        return checkPalin(0,len(s)-1,k)

    def isValidPalindrome(self, s: str, k: int) -> bool:
        '''
        table of number of removals required to make string i to j a palindrom
        memo table has number of removals
        if two characters are not same from left and right we add 1 and call min(left, right)
        '''
        memo ={}

        def dp(i,j):
            # base case
            if i>=j:
                return 0

            # check memo
            if (i,j) in memo:
                return memo[(i,j)]

            # recursion with memo
            if s[i] == s[j]:
                memo[(i,j)] = dp(i+1, j-1)
            else:
                memo[(i,j)] = 1+ min(dp(i+1, j), dp(i, j-1))

            return memo[(i,j)]

        return dp(0,len(s)-1) <=k

    def isValidPalindrome(self, s: str, k: int) -> bool:
        def checkPalin(l, r,k):
            if l>=r:
                return True

            if s[l]!=s[r]:
                if k<=0: return False
                return checkPalin(l+1, r,k-1) or checkPalin(l, r-1,k-1)
            else:
                return checkPalin(l+1, r-1, k)

        return checkPalin(0, len(s)-1,k)
```
