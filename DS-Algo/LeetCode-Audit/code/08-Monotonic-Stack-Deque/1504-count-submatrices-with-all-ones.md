# 1504. Count Submatrices With All Ones

[Problem](https://leetcode.com/problems/count-submatrices-with-all-ones/) · Medium · Monotonic Stack / Deque → Histogram counting

LeetCode tags: array, dynamic-programming, stack, matrix, monotonic-stack

Attempts since Mar 2023: 3 · accepted: 3 · failed before first AC: 0

## Attempt 1 · 2023-04-01 18:48 IST · Accepted · C++

[submission 925907043](https://leetcode.com/submissions/detail/925907043/) · tests 73/73 · runtime 792 ms (beats 5.0%)

```cpp
class Solution {
public:
    int findMat(vector<vector<int>>& mat, int row, int col){
        int ans =0;
        int n = mat.size(), m = mat[0].size();
        int bound = m;

        for(int r=row;r<n;r++){
            for(int c=col;c<bound;c++){
                if(mat[r][c] ==1 ) ans+=1;
                else bound = c;
            }
        }

        return ans;
    }
    int numSubmat(vector<vector<int>>& mat) {
        int ans =0;
        int n = mat.size(), m = mat[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans += findMat(mat, i, j);
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-04-01 19:14 IST · Accepted · C++

[submission 925918463](https://leetcode.com/submissions/detail/925918463/) · tests 73/73 · runtime 164 ms (beats 9.4%)

```cpp
class Solution {
public:
    int findMat(vector<vector<int>>& mat, int row, int col){
        int ans =0;
        int n = mat.size(), m = mat[0].size();
        int bound = m;

        for(int r=row;r<n;r++){
            for(int c=col;c<bound;c++){
                if(mat[r][c] ==1 ) ans+=1;
                else bound = c;
            }
        }
        return ans;
    }
    int solve1D(vector<vector<int>>& mat, vector<int> &height){
        int ans =0, len =0;

        for(int i=0;i<height.size();i++){
            len = height[i]==0 ? 0 : len+1;
            ans += len;
        }
        return ans;
    }
    int numSubmat(vector<vector<int>>& mat) {
        int ans =0;
        int n = mat.size(), m = mat[0].size();

        // O(n*N*M*M)
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<m;j++){
        //         ans += findMat(mat, i, j);
        //     }
        // }

        // O(N*N*M)
        for(int i=0;i<n;i++){
            vector<int> height(m,1);
            for(int row=i;row<n;row++){
                for(int col=0;col<m;col++)
                    height[col] = height[col]&mat[row][col];
                ans += solve1D(mat, height);
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-04-01 23:13 IST · Accepted · C++

[submission 926100354](https://leetcode.com/submissions/detail/926100354/) · tests 73/73 · runtime 42 ms (beats 16.6%)

```cpp
class Solution {
public:
    int findMat(vector<vector<int>>& mat, int row, int col){
        int ans =0;
        int n = mat.size(), m = mat[0].size();
        int bound = m;

        for(int r=row;r<n;r++){
            for(int c=col;c<bound;c++){
                if(mat[r][c] ==1 ) ans+=1;
                else bound = c;
            }
        }
        return ans;
    }
    int solve1D(vector<vector<int>>& mat, vector<int> &height){
        int ans =0, len =0;

        for(int i=0;i<height.size();i++){
            len = height[i]==0 ? 0 : len+1;
            ans += len;
        }
        return ans;
    }
    int numSubmat(vector<vector<int>>& mat) {
        int ans =0;
        int n = mat.size(), m = mat[0].size();

        // O(N*N*M*M)
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<m;j++){
        //         ans += findMat(mat, i, j);
        //     }
        // }

        // O(N*N*M)
        // for(int i=0;i<n;i++){
        //     vector<int> height(m,1);
        //     for(int row=i;row<n;row++){
        //         for(int col=0;col<m;col++)
        //             height[col] = height[col]&mat[row][col];
        //         ans += solve1D(mat, height);
        //     }
        // }

        // O(N*M)
        vector<int> heights(m,0);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j] == 1)
                    heights[j]++;
                else heights[j]=0; 
            }
            ans += allSubMat(heights);
        }
        return ans;
    }
    int allSubMat(vector<int> & heights){
        int ans =0;
        int m = heights.size();
        vector<int> sum(m,0);
        stack<int> st;

        for(int i=0;i<m;i++){
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if(!st.empty()){
                int prevIdx = st.top();
                sum[i] = sum[prevIdx];
                sum[i] += (heights[i] * (i -prevIdx)); // prevIdx is left elemt which is smaller then heights[i]
            }
            else{
                sum[i] = (heights[i] * (i - 0 + 1)); // 0 is left index of smaller element
            }
            st.push(i);
        }

        for(auto s: sum) ans += s;
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
