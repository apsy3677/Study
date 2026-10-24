# 339. Nested List Weight Sum

[Problem](https://leetcode.com/problems/nested-list-weight-sum/) · Medium · Binary Tree (DFS & Recursion) → Recursive depth sum

LeetCode tags: depth-first-search, breadth-first-search

Attempts since Mar 2023: 5 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-11-10 05:30 IST · Runtime Error · Python3

[submission 1095575429](https://leetcode.com/submissions/detail/1095575429/) · tests 0/25

Failing input:

```text
[[1,1],2,[1,1]]
```

Expected:

```text
10
```

Runtime error:

```text
TypeError: None is not valid value for the expected return type integer
    raise TypeError(str(ret) + " is not valid value for the expected return type integer");
Line 79 in _driver (Solution.py)
    _driver()
Line 86 in <module> (Solution.py)
During handling of the above exception, another exception occurred:
TypeError: '<' not supported between instances of 'int' and 'NoneType'
Line 14 in _seri ... [165 more chars]
```

```python
# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def __init__(self, value=None):
#        """
#        If value is not specified, initializes an empty list.
#        Otherwise initializes a single integer equal to value.
#        """
#
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def add(self, elem):
#        """
#        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
#        :rtype void
#        """
#
#    def setInteger(self, value):
#        """
#        Set this NestedInteger to hold a single integer equal to value.
#        :rtype void
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """

class Solution:
    def depthSum(self, nestedList: List[NestedInteger]) -> int:

        def dfs(nested_list, depth):
            result = 0
            for ele in nested_list:
                if ele.isInteger():
                    result += ele.getInteger() * depth
                else:
                    result += dfs(ele.getList(), depth+1)
            return result
```

## Attempt 2 · 2023-12-01 03:11 IST · Accepted · Python3

[submission 1109816286](https://leetcode.com/submissions/detail/1109816286/) · tests 25/25 · runtime 39 ms (beats 0.0%)

```python
class Solution:
    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        queue = deque(nestedList)

        depth = 1
        total = 0

        while len(queue) > 0:
            for i in range(len(queue)):
                nested = queue.popleft()
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:
                    queue.extend(nested.getList())
                    print(queue)
            depth += 1

        return total
```

## Attempt 3 · 2023-12-04 11:33 IST · Runtime Error · Python3

[submission 1111956734](https://leetcode.com/submissions/detail/1111956734/) · tests 0/25

Failing input:

```text
[[1,1],2,[1,1]]
```

Expected:

```text
10
```

Runtime error:

```text
TypeError: 'int' object is not callable
    total += depth(nested.getList(), depth+1)
Line 49 in dfs (Solution.py)
    dfs(nestedList, 1)
Line 53 in depthSum (Solution.py)
    ret = Solution().depthSum(param_1)
Line 72 in _driver (Solution.py)
    _driver()
Line 83 in <module> (Solution.py)
```

```python
class Solution:
    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        '''
        time complexity - queue will have nesting level + elements 

        BFS - process level by level - by adding all element sto the queue 
        DFS. - easy to keep track of depth
        for nested in nested_list:
            dfs(nested, depth+1)

        space complexity- 
        BFS has worst when all elements are at same level - [1,2,3,4,5]
        DFS has worst when nesting is to the full [[[[[1]]]]] - that many dfs calls on stack as nesting

        '''
        queue = deque(nestedList)

        # dpeth for first level is 1
        depth = 1
        total = 0

        while queue:

            # process this level first 
            # so that you can multiply all values with same depth value
            # other way is to save dpeth with each list in queue
            for i in range(len(queue)):
                nested = queue.popleft()

                # if integer - easy multiply and add
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:

                    # if another list - extend queue to add all element of this list
                    queue.extend(nested.getList())
                    print(queue)
            depth += 1

        return total

    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        def dfs(nested_list, depth):
            total = 0
            for nested in nested_list:
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:
                    total += depth(nested.getList(), depth+1)
            return total 


        dfs(nestedList, 1)
```

## Attempt 4 · 2023-12-04 11:33 IST · Runtime Error · Python3

[submission 1111956828](https://leetcode.com/submissions/detail/1111956828/) · tests 0/25

Failing input:

```text
[[1,1],2,[1,1]]
```

Expected:

```text
10
```

Runtime error:

```text
TypeError: 'int' object is not callable
    total += depth(nested.getList(), depth+1)
Line 49 in dfs (Solution.py)
    return dfs(nestedList, 1)
Line 53 in depthSum (Solution.py)
    ret = Solution().depthSum(param_1)
Line 72 in _driver (Solution.py)
    _driver()
Line 83 in <module> (Solution.py)
```

```python
class Solution:
    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        '''
        time complexity - queue will have nesting level + elements 

        BFS - process level by level - by adding all element sto the queue 
        DFS. - easy to keep track of depth
        for nested in nested_list:
            dfs(nested, depth+1)

        space complexity- 
        BFS has worst when all elements are at same level - [1,2,3,4,5]
        DFS has worst when nesting is to the full [[[[[1]]]]] - that many dfs calls on stack as nesting

        '''
        queue = deque(nestedList)

        # dpeth for first level is 1
        depth = 1
        total = 0

        while queue:

            # process this level first 
            # so that you can multiply all values with same depth value
            # other way is to save dpeth with each list in queue
            for i in range(len(queue)):
                nested = queue.popleft()

                # if integer - easy multiply and add
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:

                    # if another list - extend queue to add all element of this list
                    queue.extend(nested.getList())
                    print(queue)
            depth += 1

        return total

    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        def dfs(nested_list, depth):
            total = 0
            for nested in nested_list:
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:
                    total += depth(nested.getList(), depth+1)
            return total 


        return dfs(nestedList, 1)
```

## Attempt 5 · 2023-12-04 11:34 IST · Accepted · Python3

[submission 1111957079](https://leetcode.com/submissions/detail/1111957079/) · tests 25/25 · runtime 36 ms (beats 0.0%)

```python
class Solution:
    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        '''
        time complexity - queue will have nesting level + elements 

        BFS - process level by level - by adding all element sto the queue 
        DFS. - easy to keep track of depth
        for nested in nested_list:
            dfs(nested, depth+1)

        space complexity- 
        BFS has worst when all elements are at same level - [1,2,3,4,5]
        DFS has worst when nesting is to the full [[[[[1]]]]] - that many dfs calls on stack as nesting

        '''
        queue = deque(nestedList)

        # dpeth for first level is 1
        depth = 1
        total = 0

        while queue:

            # process this level first 
            # so that you can multiply all values with same depth value
            # other way is to save dpeth with each list in queue
            for i in range(len(queue)):
                nested = queue.popleft()

                # if integer - easy multiply and add
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:

                    # if another list - extend queue to add all element of this list
                    queue.extend(nested.getList())
                    print(queue)
            depth += 1

        return total

    def depthSum(self, nestedList: List[NestedInteger]) -> int:
        def dfs(nested_list, depth):
            total = 0
            for nested in nested_list:
                if nested.isInteger():
                    total += nested.getInteger() * depth
                else:
                    total += dfs(nested.getList(), depth+1)
            return total 


        return dfs(nestedList, 1)
```
