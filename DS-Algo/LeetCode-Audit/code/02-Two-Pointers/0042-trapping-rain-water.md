# 42. Trapping Rain Water

[Problem](https://leetcode.com/problems/trapping-rain-water/) · Hard · Two Pointers → Two pointers / prefix max

LeetCode tags: array, two-pointers, dynamic-programming, stack, monotonic-stack

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-21 23:36 IST · Accepted · C++

[submission 919668793](https://leetcode.com/submissions/detail/919668793/) · tests 322/322 · runtime 21 ms (beats 4.7%)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // find local minima & maxima index
        
        int n =height.size();
        if(n == 0)
            return 0;
        vector<int> left(n), right(n);
        left[0] = 0;
        right[n-1] =0;

        for(int i=1;i<n;i++){
            left[i] = max(height[i-1], left[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            right[i] = max(height[i+1],right[i+1]);
        }
        int ans =0;
        for(int i=0;i<n;i++){
            int maxx = min(left[i],right[i]) - height[i];
            ans +=  maxx <= 0 ? 0 : maxx;
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-21 23:39 IST · Accepted · C++

[submission 919670634](https://leetcode.com/submissions/detail/919670634/) · tests 322/322 · runtime 13 ms (beats 4.7%)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // find local minima & maxima index
        
        int n =height.size();
        if(n == 0)
            return 0;
        vector<int> left(n), right(n);
        left[0] = height[0];
        right[n-1] =height[n-1];

        for(int i=1;i<n;i++){
            left[i] = max(height[i], left[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            right[i] = max(height[i],right[i+1]);
        }
        int ans =0;
        for(int i=0;i<n;i++){
            int maxx = min(left[i],right[i]) - height[i];
            ans +=  maxx <= 0 ? 0 : maxx;
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-22 00:05 IST · Accepted · C++

[submission 919686936](https://leetcode.com/submissions/detail/919686936/) · tests 322/322 · runtime 12 ms (beats 4.7%)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // find local minima & maxima index
        
        int n =height.size();
        if(n == 0)
            return 0;

        // using stack
        stack<int> st;
        int ans =0;
        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>height[st.top()]){
                int top = st.top();
                st.pop();
                if(st.empty()){
                    break;
                }
                int dis = i - st.top() -1;
                int b_h = min(height[i],height[st.top()]) - height[top];
                ans += dis*b_h;
            }
            st.push(i);
        }
        return ans;
        vector<int> left(n), right(n);
        left[0] = height[0];
        right[n-1] =height[n-1];

        for(int i=1;i<n;i++){
            left[i] = max(height[i], left[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            right[i] = max(height[i],right[i+1]);
        }
        
        for(int i=0;i<n;i++){
            int maxx = min(left[i],right[i]) - height[i];
            ans +=  maxx <= 0 ? 0 : maxx;
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-03-22 00:11 IST · Accepted · C++

[submission 919690241](https://leetcode.com/submissions/detail/919690241/) · tests 322/322 · runtime 17 ms (beats 4.7%)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // find local minima & maxima index
        
        int n =height.size();
        int ans =0;
        if(n == 0)
            return 0;

        // using 2 pointers
        int left =0, right = n-1, l_max = 0, r_max=0;

        while(left<right){
            if(height[left] < height[right]){
                // we can get max prof
                l_max = max(l_max, height[left]);
                ans += l_max - height[left];
                left++;
            }
            else{
                r_max = max(r_max, height[right]);
                ans += r_max - height[right];
                right--;
            }
        }
        return ans;

        // using stack
        stack<int> st;
        
        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>height[st.top()]){
                int top = st.top();
                st.pop();
                if(st.empty()){
                    break;
                }
                int dis = i - st.top() -1;
                int b_h = min(height[i],height[st.top()]) - height[top];
                ans += dis*b_h;
            }
            st.push(i);
        }
        return ans;

        // DP Solution
        // vector<int> left(n), right(n);
        // left[0] = height[0];
        // right[n-1] =height[n-1];

        // for(int i=1;i<n;i++){
        //     left[i] = max(height[i], left[i-1]);
        // }
        // for(int i=n-2;i>=0;i--){
        //     right[i] = max(height[i],right[i+1]);
        // }
        
        // for(int i=0;i<n;i++){
        //     int maxx = min(left[i],right[i]) - height[i];
        //     ans +=  maxx <= 0 ? 0 : maxx;
        // }
        // return ans;
    }
};
```

## Attempt 5 · 2023-03-22 22:08 IST · Accepted · C++

[submission 920228993](https://leetcode.com/submissions/detail/920228993/) · tests 322/322 · runtime 11 ms (beats 4.7%)

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        // find local minima & maxima index
        
        int n =height.size();
        int ans =0;
        if(n == 0)
            return 0;

        // using 2 pointers
        int left =0, right = n-1, l_max = 0, r_max=0;

        while(left<right){
            if(height[left] < height[right]){
                // we can get max prof
                l_max = max(l_max, height[left]);
                ans += l_max - height[left];
                left++;
            }
            else{
                r_max = max(r_max, height[right]);
                ans += r_max - height[right];
                right--;
            }
        }
        return ans;

        // using stack
        stack<int> st;
        
        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>height[st.top()]){
                int top = st.top();
                st.pop();
                if(st.empty()){
                    break;
                }
                int dis = i - st.top() -1;
                int b_h = min(height[i],height[st.top()]) - height[top];
                ans += dis*b_h;
            }
            st.push(i);
        }
        return ans;

        // DP Solution
        // vector<int> left(n), right(n);
        // left[0] = height[0];
        // right[n-1] =height[n-1];

        // for(int i=1;i<n;i++){
        //     left[i] = max(height[i], left[i-1]);
        // }
        // for(int i=n-2;i>=0;i--){
        //     right[i] = max(height[i],right[i+1]);
        // }
        
        // for(int i=0;i<n;i++){
        //     int maxx = min(left[i],right[i]) - height[i];
        //     ans +=  maxx <= 0 ? 0 : maxx;
        // }
        // return ans;
    }
};
```
