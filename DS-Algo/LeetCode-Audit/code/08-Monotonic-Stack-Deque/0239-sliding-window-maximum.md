# 239. Sliding Window Maximum

[Problem](https://leetcode.com/problems/sliding-window-maximum/) · Hard · Monotonic Stack / Deque → Monotonic deque

LeetCode tags: array, queue, sliding-window, heap-priority-queue, monotonic-queue, range-minimum-maximum-query

Attempts since Mar 2023: 13 · accepted: 7 · failed before first AC: 2

## Attempt 1 · 2023-05-07 11:00 IST · Wrong Answer · C++

[submission 945883294](https://leetcode.com/submissions/detail/945883294/) · tests 39/51

Failing input:

```text
[-7,-8,7,5,7,1,6,0]
4
```

Expected:

```text
[7,7,7,7,7]
```

Your output:

```text
[7,7,7,6,6]
```

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxi = INT_MIN; 
        multiset<int> st;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            maxi = max(maxi, arr[i]);
            st.insert(arr[i]);
        }
        ans.push_back(maxi);
        
        for(int i=k;i<arr.size();i++){
            st.erase(arr[i-k]);
            st.insert(arr[i]);
            ans.push_back(*(st.rbegin()));
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-07 11:09 IST · Time Limit Exceeded · C++

[submission 945886665](https://leetcode.com/submissions/detail/945886665/)

_Code not returned by LeetCode._

## Attempt 3 · 2023-05-07 11:09 IST · Accepted · C++

[submission 945886830](https://leetcode.com/submissions/detail/945886830/) · tests 51/51 · runtime 766 ms (beats 5.0%)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxi = INT_MIN; 
        multiset<int> st;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            maxi = max(maxi, arr[i]);
            st.insert(arr[i]);
        }
        ans.push_back(*(st.rbegin()));
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            
            st.insert(arr[i]);
            st.erase(st.find(arr[i-k]));
            // for(auto &it: st) cout<<it<<" "; cout<<"::";
            ans.push_back(*(st.rbegin()));
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-07 11:24 IST · Accepted · C++

[submission 945892624](https://leetcode.com/submissions/detail/945892624/) · tests 51/51 · runtime 334 ms (beats 7.9%)

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }
        while(!dq.empty() && ( arr[idx] > arr[dq.back()]) ){
            dq.pop_back();
        }
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            clean__(arr, dq, i, k);
            dq.push_back(i);
            if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[maxIdx]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-05-07 11:25 IST · Wrong Answer · C++

[submission 945893319](https://leetcode.com/submissions/detail/945893319/) · tests 30/51

Failing input:

```text
[1,3,1,2,0,5]
3
```

Expected:

```text
[3,3,2,5]
```

Your output:

```text
[3,3,1,5]
```

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }
        while(!dq.empty() && ( arr[idx] >= arr[dq.front()]) ){
            dq.pop_front();
        }
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            clean__(arr, dq, i, k);
            dq.push_back(i);
            if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[maxIdx]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-05-07 11:42 IST · Time Limit Exceeded · C++

[submission 945900791](https://leetcode.com/submissions/detail/945900791/) · tests 37/51

Failing input:

```text
[41,8467,6334,6500,9169,5724,1478,9358,6962,4464,5705,8145,3281,6827,9961,491,2995,1942,4827,5436,2391,4604,3902,153,292,2382,7421,8716,9718,9895,5447,1726,4771,1538,1869,9912,5667,6299,7035,9894,8703,3811,1322,333,7673,4664,5141,7711,8253,6868,5547,7644,2662,2757,37,2859,8723,9741,7529,778,2316,3035,2190,1842,288,106,9040,8942,9264,2648,7446,3805,5890,6729,4370,5350,5006,1101,4393,3548,9629,2623, ... [485845 more chars]
```

Expected:

```text
[9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,9999 ... [249606 more chars]
```

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        for(auto it : dq) cout<<it<<" "; cout<<":: ";

        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }
        // while(!dq.empty() && (idx-k >= dq.front() || arr[idx] > arr[dq.front()]) ){
        //     dq.pop_front();
        // }
        while(!dq.empty() && (arr[idx] > arr[dq.back()]) ){
            dq.pop_back();
        }
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[maxIdx]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```

## Attempt 7 · 2023-05-07 11:43 IST · Accepted · C++

[submission 945901078](https://leetcode.com/submissions/detail/945901078/) · tests 51/51 · runtime 325 ms (beats 8.4%)

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        // for(auto it : dq) cout<<it<<" "; cout<<":: ";

        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }
        // while(!dq.empty() && (idx-k >= dq.front() || arr[idx] > arr[dq.front()]) ){
        //     dq.pop_front();
        // }
        while(!dq.empty() && (arr[idx] > arr[dq.back()]) ){
            dq.pop_back();
        }
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            // cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[maxIdx]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            // cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```

## Attempt 8 · 2023-11-19 00:48 IST · Runtime Error · Python3

[submission 1101605330](https://leetcode.com/submissions/detail/1101605330/) · tests 0/51

Failing input:

```text
[1,3,-1,-3,5,3,6,7]
3
```

Expected:

```text
[3,3,5,5,6,7]
```

Runtime error:

```text
NameError: name 'dq' is not defined. Did you mean: 'eq'?
    res.append(nums[dq[0]])
Line 11 in maxSlidingWindow (Solution.py)
    ret = Solution().maxSlidingWindow(param_1, param_2)
Line 48 in _driver (Solution.py)
    _driver()
Line 59 in <module> (Solution.py)
```

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        queue = deque()
        res = []

        for i in range(k):
            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop()
            queue.append(i)

        res.append(nums[dq[0]])


        for i in range(k, len(nums)):
            if queue and queue[0] == i-k:
                queue.popleft()

            while queue and nums[i] >= nums[queue[-1]]:
                queue.pop()

            queue.append(i)
            res.append(nums[queue[0]])

        return res
```

## Attempt 9 · 2023-11-19 00:49 IST · Runtime Error · Python3

[submission 1101605417](https://leetcode.com/submissions/detail/1101605417/) · tests 0/51

Failing input:

```text
[1,3,-1,-3,5,3,6,7]
3
```

Expected:

```text
[3,3,5,5,6,7]
```

Runtime error:

```text
NameError: name 'queueu' is not defined. Did you mean: 'queue'?
    res.append(nums[queueu[0]])
Line 11 in maxSlidingWindow (Solution.py)
    ret = Solution().maxSlidingWindow(param_1, param_2)
Line 48 in _driver (Solution.py)
    _driver()
Line 59 in <module> (Solution.py)
```

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        queue = deque()
        res = []

        for i in range(k):
            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop()
            queue.append(i)

        res.append(nums[queueu[0]])


        for i in range(k, len(nums)):
            if queue and queue[0] == i-k:
                queue.popleft()

            while queue and nums[i] >= nums[queue[-1]]:
                queue.pop()

            queue.append(i)
            res.append(nums[queue[0]])

        return res
```

## Attempt 10 · 2023-11-19 00:49 IST · Accepted · Python3

[submission 1101605458](https://leetcode.com/submissions/detail/1101605458/) · tests 51/51 · runtime 1301 ms (beats 5.0%)

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        queue = deque()
        res = []

        for i in range(k):
            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop()
            queue.append(i)

        res.append(nums[queue[0]])


        for i in range(k, len(nums)):
            if queue and queue[0] == i-k:
                queue.popleft()

            while queue and nums[i] >= nums[queue[-1]]:
                queue.pop()

            queue.append(i)
            res.append(nums[queue[0]])

        return res
```

## Attempt 11 · 2024-02-11 07:41 IST · Accepted · Python3

[submission 1171858464](https://leetcode.com/submissions/detail/1171858464/) · tests 51/51 · runtime 1069 ms (beats 5.0%)

```python
class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        queue = deque()
        res = []

        for i in range(k):
            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop()
            queue.append(i)

        res.append(nums[queue[0]])


        for i in range(k, len(nums)):
            if queue and queue[0] == i-k:
                queue.popleft()

            while queue and nums[i] >= nums[queue[-1]]:
                queue.pop()

            queue.append(i)
            res.append(nums[queue[0]])

        return res

    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        # keep a deque where you insert from end 
        # start has the max element
        # yo only keep potential candidates 
        # you remove all smaller elmenets because they will never be max in this window

        queue = deque()
        result = []
        for i in range(k):
            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop() # pop from end
            
            queue.append(i)
        
        result.append(nums[queue[0]])
        # print('here')
        for i in range(k, len(nums)):
            if queue and queue[0] == i-k:
                queue.popleft() # pop from start

            while queue and nums[queue[-1]] <= nums[i]:
                queue.pop() # pop from end

            queue.append(i)

            result.append(nums[queue[0]])
        return result
```

## Attempt 12 · 2024-03-26 10:41 IST · Accepted · C++

[submission 1214099075](https://leetcode.com/submissions/detail/1214099075/) · tests 51/51 · runtime 198 ms (beats 9.3%)

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        // for(auto it : dq) cout<<it<<" "; cout<<":: ";

        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }
        // while(!dq.empty() && (idx-k >= dq.front() || arr[idx] > arr[dq.front()]) ){
        //     dq.pop_front();
        // }
        while(!dq.empty() && (arr[idx] > arr[dq.back()]) ){
            dq.pop_back();
        }
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            // cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            // if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[dq.front()]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            // cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```

## Attempt 13 · 2024-03-26 10:45 IST · Accepted · C++

[submission 1214102989](https://leetcode.com/submissions/detail/1214102989/) · tests 51/51 · runtime 172 ms (beats 9.5%)

```cpp
class Solution {
public:
    void clean__(vector<int> & arr, deque<int> &dq, int idx, int k){
        // remove all elements whose index is smaller than idx -k
        // for(auto it : dq) cout<<it<<" "; cout<<":: ";

        while(!dq.empty() && (idx-k >= dq.front()) ){
            dq.pop_front();
        }

        while(!dq.empty() && (arr[idx] > arr[dq.back()]) ){
            dq.pop_back();
        }
        // Both these while loops make sure that, dq.front() always points to 
        // the maximum element index.
    }
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        vector<int> ans;
        int maxIdx = 0; 
        deque<int> dq;
        if(k > arr.size()) return {};
        for(int i=0;i<k;i++){
            clean__(arr, dq, i, k);
            dq.push_back(i);
            // if(arr[i] > arr[maxIdx]) maxIdx = i;
        }
        ans.push_back(arr[dq.front()]);
        // for(auto &it: st) cout<<it<<" "; cout<<"::";
        for(int i=k;i<arr.size();i++){
            // cout<<"insert "<<arr[i]<<"|";
            clean__(arr, dq, i, k);
            dq.push_back(i);
            ans.push_back(arr[dq.front()]);
        }
        return ans;
    }
};
```
