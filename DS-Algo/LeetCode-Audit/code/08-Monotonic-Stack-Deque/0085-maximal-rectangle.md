# 85. Maximal Rectangle

[Problem](https://leetcode.com/problems/maximal-rectangle/) · Hard · Monotonic Stack / Deque → Histogram per row

LeetCode tags: array, dynamic-programming, stack, matrix, monotonic-stack

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-04-01 22:26 IST · Accepted · C++

[submission 926074412](https://leetcode.com/submissions/detail/926074412/) · tests 74/74 · runtime 44 ms (beats 7.0%)

```cpp
class Solution {
public:
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
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans=0;
        vector<int> heights(m,0);

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j] == '1')
                    heights[j]++;
                else heights[j]=0; 
            }
            ans = max(ans, largestRectangleArea(heights));
        }

        return ans;
    }
};
```
