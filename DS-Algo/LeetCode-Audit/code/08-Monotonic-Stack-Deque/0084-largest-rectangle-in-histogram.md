# 84. Largest Rectangle in Histogram

[Problem](https://leetcode.com/problems/largest-rectangle-in-histogram/) · Hard · Monotonic Stack / Deque → Histogram

LeetCode tags: array, stack, monotonic-stack, range-minimum-maximum-query

Attempts since Mar 2023: 4 · accepted: 4 · failed before first AC: 0

## Attempt 1 · 2023-04-01 21:39 IST · Accepted · C++

[submission 926048181](https://leetcode.com/submissions/detail/926048181/) · tests 98/98 · runtime 204 ms (beats 5.4%)

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n,0), right(n,0);
        stack<int> st; // keeps the indexes for elemets which are are in strictcly increasing order i.e. monotonic stack
        // left pass to calculate left index for i which is smaller then ith element
        for(int i =0;i<n;i++){
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if(st.empty()) left[i] = 0;
            else left[i] = st.top()+1;
            st.push(i);
        }

        while(!st.empty()) st.pop();

        for(int i=n-1;i>=0;i--){
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if(st.empty()) right[i] = n-1;
            else right[i] = st.top()-1;
            st.push(i);
        }
        int ans =0;
        for(int i=0;i<n;i++){
            ans = max(ans, heights[i]*(right[i]-left[i]+1));
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-01 22:08 IST · Accepted · C++

[submission 926064062](https://leetcode.com/submissions/detail/926064062/) · tests 98/98 · runtime 164 ms (beats 5.4%)

```cpp
class Solution {
public:
    int solveWithExtraSpace(vector<int>& heights){
        int n = heights.size();
        vector<int> left(n,0), right(n,0);
        stack<int> st; // keeps the indexes for elemets which are are in strictcly increasing order i.e. monotonic stack
        // left pass to calculate left index for i which is smaller then ith element
        for(int i =0;i<n;i++){
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if(st.empty()) left[i] = 0;
            else left[i] = st.top()+1;
            st.push(i);
        }

        while(!st.empty()) st.pop();

        for(int i=n-1;i>=0;i--){
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if(st.empty()) right[i] = n-1;
            else right[i] = st.top()-1;
            st.push(i);
        }
        int ans =0;
        for(int i=0;i<n;i++){
            ans = max(ans, heights[i]*(right[i]-left[i]+1));
        }
        return ans;
    }
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int n = heights.size();
        int ans =0;
        for(int i=0;i<n;i++){
            while(!st.empty() && heights[st.top()] >= heights[i]){
                int height = heights[st.top()];
                st.pop();// pop this
                int width = st.empty() ? i : i - st.top() -1; // excluding both the elemnts i & st.top as they are smaller for current height height
                ans = max(ans, height*width);
            }
            st.push(i);
        }
        while(!st.empty()){
                int height = heights[st.top()];
                st.pop();// pop this
                int width = st.empty() ? n : n - st.top() -1; // excluding both the elemnts i & st.top as they are smaller for current height height
                ans = max(ans, height*width);
            }
        return ans;
    }
};
```

## Attempt 3 · 2023-12-29 08:34 IST · Accepted · Python3

[submission 1131038362](https://leetcode.com/submissions/detail/1131038362/) · tests 98/98 · runtime 1353 ms (beats 5.1%)

```python
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        '''
        stack will contain heights as long as you havent found the smaller height
        monotonic increasing stack
        once you find the smaller height than the top of the stack - its is time to calculate area

        '''
        # sentinel 
        stack = [-1]
        max_area = 0 
        for i in range( len(heights)):
            # if smaller height comes
            
            while stack[-1] !=-1 and heights[i] < heights[stack[-1]]:
                
                # current smaller one becomes the right boundary 
                # and below the top becomes the left boundary
                # the top item at stack creates a rectangle to right till the right boundary
                
                right = i
                height = heights[stack.pop()]
                left = stack[-1]
                width = right - left - 1

                max_area = max(max_area, height*width)

            stack.append(i)

        # print(stack)
        # a increasing sequence
        while stack[-1]!=-1:
            height = heights[stack.pop()]
            width = len(heights) - stack[-1] -1

            max_area= max(max_area, height*width)

        return max_area
```

## Attempt 4 · 2023-12-29 08:38 IST · Accepted · Python3

[submission 1131040251](https://leetcode.com/submissions/detail/1131040251/) · tests 98/98 · runtime 702 ms (beats 5.1%)

```python
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        '''
        stack will contain heights as long as you havent found the smaller height
        monotonic increasing stack
        once you find the smaller height than the top of the stack - its is time to calculate area

        '''
        # sentinel 
        stack = [-1]
        max_area = 0 
        for i in range( len(heights)):
            # if smaller height comes
            
            while stack[-1] !=-1 and heights[i] < heights[stack[-1]]:
                
                # current smaller one becomes the right boundary 
                # and below the top becomes the left boundary
                # the top item at stack creates a rectangle to right till the right boundary
                # you need left to be one below the stack top 
                right = i
                height = heights[stack.pop()]
                left = stack[-1]
                width = right - left - 1

                max_area = max(max_area, height*width)

            stack.append(i)

        # print(stack)
        # a increasing sequence
        while stack[-1]!=-1:
            height = heights[stack.pop()]
            width = len(heights) - stack[-1] -1

            max_area= max(max_area, height*width)

        return max_area
```
