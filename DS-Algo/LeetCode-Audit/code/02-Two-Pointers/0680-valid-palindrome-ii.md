# 680. Valid Palindrome II

[Problem](https://leetcode.com/problems/valid-palindrome-ii/) · Easy · Two Pointers → Skip one character

LeetCode tags: two-pointers, string, greedy

Attempts since Mar 2023: 6 · accepted: 2 · failed before first AC: 4

## Attempt 1 · 2023-12-01 03:59 IST · Runtime Error · Python3

[submission 1109833874](https://leetcode.com/submissions/detail/1109833874/) · tests 0/469

Failing input:

```text
"aba"
```

Expected:

```text
true
```

Runtime error:

```text
NameError: name 'Solution' is not defined
    ret = Solution().validPalindrome(param_1)
Line 20 in _driver (Solution.py)
    _driver()
Line 31 in <module> (Solution.py)
```

_Code not returned by LeetCode._

## Attempt 2 · 2023-12-21 05:15 IST · Wrong Answer · Python3

[submission 1124638597](https://leetcode.com/submissions/detail/1124638597/) · tests 370/469

Failing input:

```text
"eccer"
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
    def validPalindrome(self, s: str) -> bool:
        '''
        the way to check palindrom is two pointer approach or recursion 
        run left and right pointer - if not same return False
        or if not same try deleting one character - either left or right

        time complexity - n/2 letter are checked and for one letter there are two calls each will iterate < N/2

        for k palindrom 
        - you can call checkPalin(l, r, k)
        and on each mismatch reduce k 
        '''
        def isValid(l, r, s):
            while l<r:
                if s[l] != s[r]:
                    return False
                l+=1
                r-=1
            return True

        l,r = 0, len(s)-1
        while l< r:
            if s[l]!= s[r]:
                # return is valid from both condition
                return isValid(l+1, r, s) or isValid(l, r-l, s)
            l+=1
            r-=1
        return True

    def validKPalindrome(self, s: str) -> bool:
        def checkPalin(l,r,k):
            if l>=r:
                return True

            if s[l]==s[r]:
                return checkPalin(l+1, r-1,k)
            else:
                if k<=0:
                    return False
                return checkPalin(l+1,r,k-1) or checkPalin(l, r-1,k-1)
            return True
        checkPalin(0,len(s)-1,k)
```

## Attempt 3 · 2023-12-21 05:15 IST · Wrong Answer · Python3

[submission 1124638629](https://leetcode.com/submissions/detail/1124638629/) · tests 370/469

Failing input:

```text
"eccer"
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
    def validPalindrome(self, s: str) -> bool:
        '''
        the way to check palindrom is two pointer approach or recursion 
        run left and right pointer - if not same return False
        or if not same try deleting one character - either left or right

        time complexity - n/2 letter are checked and for one letter there are two calls each will iterate < N/2

        for k palindrom 
        - you can call checkPalin(l, r, k)
        and on each mismatch reduce k 
        '''
        def isValid(l, r, s):
            while l<r:
                if s[l] != s[r]:
                    return False
                l+=1
                r-=1
            return True

        l,r = 0, len(s)-1
        while l< r:
            if s[l]!= s[r]:
                # return is valid from both condition
                return isValid(l+1, r, s) or isValid(l, r-l, s)
            l+=1
            r-=1
        return True

    def validKPalindrome(self, s: str) -> bool:
        def checkPalin(l,r,k):
            if l>=r:
                return True

            if s[l]==s[r]:
                return checkPalin(l+1, r-1,k)
            else:
                if k<=0:
                    return False
                return checkPalin(l+1,r,k-1) or checkPalin(l, r-1,k-1)
            return True
        checkPalin(0,len(s)-1,k)
```

## Attempt 4 · 2023-12-21 05:15 IST · Wrong Answer · Python3

[submission 1124638810](https://leetcode.com/submissions/detail/1124638810/) · tests 370/469

Failing input:

```text
"eccer"
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
    def validPalindrome(self, s: str) -> bool:
        '''
        the way to check palindrom is two pointer approach or recursion 
        run left and right pointer - if not same return False
        or if not same try deleting one character - either left or right

        time complexity - n/2 letter are checked and for one letter there are two calls each will iterate < N/2

        for k palindrom 
        - you can call checkPalin(l, r, k)
        and on each mismatch reduce k 
        '''
        def isValid(l, r, s):
            while l<r:
                if s[l] != s[r]:
                    return False
                l+=1
                r-=1
            return True

        l,r = 0, len(s)-1
        while l< r:
            if s[l]!= s[r]:
                # return is valid from both condition
                return isValid(l+1, r, s) or isValid(l, r-l, s)
            l+=1
            r-=1
        return True

    def validKPalindrome(self, s: str) -> bool:
        def checkPalin(l,r,k):
            if l>=r:
                return True

            if s[l]==s[r]:
                return checkPalin(l+1, r-1,k)
            else:
                if k<=0:
                    return False
                return checkPalin(l+1,r,k-1) or checkPalin(l, r-1,k-1)
            return True
        return checkPalin(0,len(s)-1,k)
```

## Attempt 5 · 2023-12-21 05:18 IST · Accepted · Python3

[submission 1124639635](https://leetcode.com/submissions/detail/1124639635/) · tests 469/469 · runtime 93 ms (beats 5.6%)

```python
class Solution:
    def validPalindrome(self, s: str) -> bool:
        '''
        the way to check palindrom is two pointer approach or recursion 
        run left and right pointer - if not same return False
        or if not same try deleting one character - either left or right

        time complexity - n/2 letter are checked and for one letter there are two calls each will iterate < N/2

        for k palindrom 
        - you can call checkPalin(l, r, k)
        and on each mismatch reduce k 
        '''
        def isValid(l, r, s):
            while l<r:
                if s[l] != s[r]:
                    return False
                l+=1
                r-=1
            return True

        l,r = 0, len(s)-1
        while l< r:
            if s[l]!= s[r]:
                # return is valid from both condition
                return isValid(l+1, r, s) or isValid(l, r-1, s)
            l+=1
            r-=1
        return True

    def validKPalindrome3(self, s: str) -> bool:
        def checkPalin(l,r,k):
            if l>=r:
                return True

            if s[l]==s[r]:
                return checkPalin(l+1, r-1,k)
            else:
                if k<=0:
                    return False
                return checkPalin(l+1,r,k-1) or checkPalin(l, r-1,k-1)
            return True
        return checkPalin(0,len(s)-1,k)
```

## Attempt 6 · 2025-06-14 12:11 IST · Accepted · C++

[submission 1663580515](https://leetcode.com/submissions/detail/1663580515/) · tests 477/477 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    bool validPalindrome(string s) {
       int left = 0, right = s.size()-1; 

       while (left <= right) {
            if(s[left] == s[right]) {
                left++, right--;
                continue;
            }
            // skip left
            int i= left+1, j= right; 
            bool pl = true;
            while (i<=j) {
                if (s[i] != s[j]) { pl = false; break;}
                i++, j--;
            }
            if (pl) return pl;
            // skip right
            pl = true;
            i= left, j= right-1; 
            while (i<=j) {
                if (s[i] != s[j]) { pl = false; break;}
                i++, j--;
            }
            if (pl) return pl;
            return false;
       }

       return true;
    }
};
```
