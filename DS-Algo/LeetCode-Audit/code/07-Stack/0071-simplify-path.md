# 71. Simplify Path

[Problem](https://leetcode.com/problems/simplify-path/) · Medium · Stack → Path stack

LeetCode tags: string, stack

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-11-23 03:52 IST · Accepted · Python3

[submission 1104475468](https://leetcode.com/submissions/detail/1104475468/) · tests 258/258 · runtime 39 ms (beats 5.2%)

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        stack = []
        for segment in path.split('/'):
            if segment =='..':
                if len(stack): stack.pop()
            elif segment =='.' or not segment:
                continue
            else:
                stack.append(segment)
            
        final_str ='/' +'/'.join(stack)
        return final_str
```

## Attempt 2 · 2023-12-04 12:00 IST · Accepted · Python3

[submission 1111972039](https://leetcode.com/submissions/detail/1111972039/) · tests 258/258 · runtime 44 ms (beats 5.2%)

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        '''
        absolute path 
        starts with /

        split path on / and check for valid characters like . .. and empty like between //
        put it on stack to handle parents .. in case of nesting is long
        '''
        stack = []
        #1. split on /
        for segment in path.split('/'):

            #2. handle .. with pop if stack
            # if parent and stack has something
            # like /../ will have empty stack
            if segment =='..':
                if len(stack): stack.pop()
            
            #3. ignore . and blank
            # for . and blank - don't do anything
            elif segment =='.' or not segment:
                continue
            
            #4. append rest onto stack
            # rest all push to stack
            else:
                stack.append(segment)
            
        # prefix with / and join with /
        final_str ='/' +'/'.join(stack)
        return final_str
```

## Attempt 3 · 2023-12-04 12:02 IST · Accepted · Python3

[submission 1111972681](https://leetcode.com/submissions/detail/1111972681/) · tests 258/258 · runtime 39 ms (beats 5.2%)

```python
class Solution:
    def simplifyPath(self, path: str) -> str:
        '''
        absolute path 
        starts with /

        split path on / and check for valid characters like . .. and empty like between //
        put it on stack to handle parents .. in case of nesting is long


        time O(n) to split and O(n) to process
        space O(n) to save split result and O(n) for stack
        '''
        stack = []
        #1. split on /
        for segment in path.split('/'):

            #2. handle .. with pop if stack
            # if parent and stack has something
            # like /../ will have empty stack
            if segment =='..':
                if len(stack): stack.pop()
            
            #3. ignore . and blank
            # for . and blank - don't do anything
            elif segment =='.' or not segment:
                continue
            
            #4. append rest onto stack
            # rest all push to stack
            else:
                stack.append(segment)
            
        # prefix with / and join with /
        final_str ='/' +'/'.join(stack)
        return final_str
```
