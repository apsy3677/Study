# 120. Triangle

[Problem](https://leetcode.com/problems/triangle/) · Medium · DP: Grid / 2D → Triangle min path

LeetCode tags: array, dynamic-programming

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-12 18:01 IST · Accepted · C++

[submission 913799505](https://leetcode.com/submissions/detail/913799505/) · tests 44/44 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n= triangle[triangle.size()-1].size();
        vector<vector<int>> dp(200,vector<int>(200,INT_MAX));
        dp[0][0] = triangle[0][0];
        for(int i=1;i<triangle.size();i++){
            for(int j=0;j<triangle[i].size();j++){
                dp[i][j] = triangle[i][j] + 
                min( j>0 ? dp[i-1][j-1] : INT_MAX,
                    dp[i-1][j]);

            }
        }
        
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};
```

## Attempt 2 · 2023-04-02 10:07 IST · Accepted · C++

[submission 926374798](https://leetcode.com/submissions/detail/926374798/) · tests 44/44 · runtime 4 ms (beats 5.4%)

```cpp
class Solution {
public:
int minimumPathSumUtil(int i, int j, vector<vector<int> > &triangle,int n, 
vector<vector<int> > &dp) {
  
  
  
//   if(i==n-1) return triangle[i][j];
  if(i==n) return  0;
  if(dp[i][j]!=-1)
  return dp[i][j];
    
  int down = triangle[i][j]+minimumPathSumUtil(i+1,j,triangle,n,dp);
  int diagonal = triangle[i][j]+minimumPathSumUtil(i+1,j+1,triangle,n,dp);
  
  return dp[i][j] = min(down, diagonal);
  
}
    int minimumTotal(vector<vector<int>>& triangle) {
        int n= triangle[triangle.size()-1].size();
        vector<vector<int> > dp(n,vector<int>(n,-1));
        return minimumPathSumUtil(0,0,triangle,n,dp);
        
        // vector<vector<int>> dp(200,vector<int>(200,INT_MAX));
        dp[0][0] = triangle[0][0];
        for(int i=1;i<triangle.size();i++){
            for(int j=0;j<triangle[i].size();j++){
                dp[i][j] = triangle[i][j] + 
                min( j>0 ? dp[i-1][j-1] : INT_MAX,
                    dp[i-1][j]);

            }
        }
        
        return *min_element(dp[n-1].begin(), dp[n-1].end());
    }
};
```
