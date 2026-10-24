# 658. Find K Closest Elements

[Problem](https://leetcode.com/problems/find-k-closest-elements/) · Medium · Binary Search → Window start search

LeetCode tags: array, two-pointers, binary-search, sliding-window, sorting, heap-priority-queue

Attempts since Mar 2023: 31 · accepted: 17 · failed before first AC: 0

## Attempt 1 · 2023-04-03 16:06 IST · Accepted · C++

[submission 927143513](https://leetcode.com/submissions/detail/927143513/) · tests 66/66 · runtime 81 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // making a min-heap of absolute difference and corresponding array value
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // store the difference one by one with the array value
        for (int i = 0; i < arr.size(); i++)
            pq.push({abs(arr[i] - x), arr[i]});

        vector<int> ans;

        // get the top of the heap i.e. the element with minimum absolute difference
        for (int i = 0; i < k; i++)
        {
            ans.push_back(pq.top().second);
            pq.pop(); // pop it k times
        }

        sort(ans.begin(), ans.end());
        return ans;
    }
};
```

## Attempt 2 · 2023-04-03 16:09 IST · Accepted · C++

[submission 927144670](https://leetcode.com/submissions/detail/927144670/) · tests 66/66 · runtime 118 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue<pair<int,int>> pq;
        
        for(int i=0;i<arr.size();i++)
            {pq.push({abs(arr[i]-x),arr[i]});
              if(pq.size()>k)
                  pq.pop();
            }
        vector<int> ans;
        while(pq.size()>0)
        {
            ans.push_back(pq.top().second);
            pq.pop();
        }
        sort(ans.begin(),ans.end());
        return ans;
        
        // // making a min-heap of absolute difference and corresponding array value
        // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // // store the difference one by one with the array value
        // for (int i = 0; i < arr.size(); i++)
        //     pq.push({abs(arr[i] - x), arr[i]});

        // vector<int> ans;

        // // get the top of the heap i.e. the element with minimum absolute difference
        // for (int i = 0; i < k; i++)
        // {
        //     ans.push_back(pq.top().second);
        //     pq.pop(); // pop it k times
        // }

        // sort(ans.begin(), ans.end());
        // return ans;
    }
};
```

## Attempt 3 · 2023-05-19 11:18 IST · Accepted · C++

[submission 953154427](https://leetcode.com/submissions/detail/953154427/) · tests 66/66 · runtime 51 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int closestInd = idx;
        if(idx == n){
            closestInd = idx-1;
        }
        else{
            if(arr[closestInd] != x && closestInd >0){
                if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
                    closestInd = closestInd -1;
                }
            }
        }
        int left = closestInd-1;
        int right = closestInd +1;

        vector<int> ans;
        ans.push_back(arr[closestInd]);
        k--; // need to find k-1 elements more
        while(k--){
            if(left>=0 && right <n){
                if(abs(arr[left] - x) <= abs(arr[right] - x)){
                    ans.push_back(arr[left]);
                    left--;
                }
                else{
                    ans.push_back(arr[right++]);
                }
            }
            else if(left >=0){
                ans.push_back(arr[left]);
                left--;
            }
            else if(right <n){
                ans.push_back(arr[right]);
                right++;
            }
        }

        sort(ans.begin() , ans.end());
        return ans;
    }
};
```

## Attempt 4 · 2023-05-19 11:20 IST · Accepted · C++

[submission 953155460](https://leetcode.com/submissions/detail/953155460/) · tests 66/66 · runtime 68 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int closestInd = idx;
        if(idx == n){
            closestInd = idx-1;
        }
        else{
            if(arr[closestInd] != x && closestInd >0){
                if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
                    closestInd = closestInd -1;
                }
            }
        }
        int left = closestInd-1;
        int right = closestInd +1;

        // vector<int> ans;
        multiset<int> ans;
        ans.insert(arr[closestInd]);
        k--; // need to find k-1 elements more
        while(k--){
            if(left>=0 && right <n){
                if(abs(arr[left] - x) <= abs(arr[right] - x)){
                    ans.insert(arr[left]);
                    left--;
                }
                else{
                    ans.insert(arr[right++]);
                }
            }
            else if(left >=0){
                ans.insert(arr[left]);
                left--;
            }
            else if(right <n){
                ans.insert(arr[right]);
                right++;
            }
        }

        return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 5 · 2023-05-19 11:23 IST · Wrong Answer · C++

[submission 953157350](https://leetcode.com/submissions/detail/953157350/) · tests 16/66

Failing input:

```text
[0,0,1,2,3,3,4,7,7,8]
3
5
```

Expected:

```text
[3,3,4]
```

Your output:

```text
[3,4,7]
```

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        vector<int> res;
        int low =0;int high = arr.size()-1;
        int idx = n;
        bool found = false;
        while(low<=high) {
            int mid = low + ((high-low)>>1);
            if(arr[mid] == x) {
                idx = mid;
                high = mid-1;
                found = true;
            } else if(arr[mid] < x) {
                low = mid + 1;
            } else {
                if(!found) idx = mid;
                 high = mid-1;
            }
        }
        
        int l = idx-1;
        int r = idx+1;
        res.push_back(arr[idx]);
        k--;
        while(k--) {
            if(l>=0 && r < arr.size()) {
                if(abs(x-arr[l]) <= abs(x-arr[r])) {
                    res.push_back(arr[l]);
                    l--;
                } else {
                    res.push_back(arr[r]);
                    r++;
                }
            } else {
                if(l>=0) {
                    res.push_back(arr[l]);
                    l--;
                }
                
                if(r<arr.size()) {
                    res.push_back(arr[r]);
                    r++;
                }
            }
        }
        
        sort(res.begin(), res.end());
        return res;

        // int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        // int closestInd = idx;
        // if(idx == n){
        //     closestInd = idx-1;
        // }
        // else{
        //     if(arr[closestInd] != x && closestInd >0){
        //         if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
        //             closestInd = closestInd -1;
        //         }
        //     }
        // }
        // int left = closestInd-1;
        // int right = closestInd +1;

        // // vector<int> ans;
        // multiset<int> ans;
        // ans.insert(arr[closestInd]);
        // k--; // need to find k-1 elements more
        // while(k--){
        //     if(left>=0 && right <n){
        //         if(abs(arr[left] - x) <= abs(arr[right] - x)){
        //             ans.insert(arr[left]);
        //             left--;
        //         }
        //         else{
        //             ans.insert(arr[right++]);
        //         }
        //     }
        //     else if(left >=0){
        //         ans.insert(arr[left]);
        //         left--;
        //     }
        //     else if(right <n){
        //         ans.insert(arr[right]);
        //         right++;
        //     }
        // }

        // return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 6 · 2023-05-19 11:29 IST · Runtime Error · C++

[submission 953159880](https://leetcode.com/submissions/detail/953159880/) · tests 17/66

Failing input:

```text
[3,5,8,10]
2
15
```

Expected:

```text
[8,10]
```

Runtime error:

```text
=================================================================
==22==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000001420 at pc 0x00000034d8fb bp 0x7ffc93c4c4e0 sp 0x7ffc93c4c4d8
READ of size 4 at 0x602000001420 thread T0
    #2 0x7f1796afd082  (/lib/x86_64-linux-gnu/libc.so.6+0x24082)
0x602000001420 is located 0 bytes to the right of 16-byte region [0x602000001410,0x60200000 ... [1533 more chars]
```

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        vector<int> res;
        int low =0;int high = arr.size()-1;
        int idx = n;
        bool found = false;
        while(low<=high) {
            int mid = low + ((high-low)>>1);
            if(arr[mid] == x) {
                idx = mid;
                high = mid-1;
                found = true;
            } else if(arr[mid] < x) {
                low = mid + 1;
            } else {
                if(!found) idx = mid;
                high = mid-1;
            }
        }
        cout<<idx<<" IND "<<arr[idx];
        if(idx == n){
            idx--;
        }
        else{
            if(idx>0 && abs(arr[idx-1] - x) <= abs(arr[idx] -x) )
                idx--;
        }
        int l = idx-1;
        int r = idx+1;
        res.push_back(arr[idx]);
        k--;
        while(k--) {
            if(l>=0 && r < arr.size()) {
                if(abs(x-arr[l]) <= abs(x-arr[r])) {
                    res.push_back(arr[l]);
                    l--;
                } else {
                    res.push_back(arr[r]);
                    r++;
                }
            } else {
                if(l>=0) {
                    res.push_back(arr[l]);
                    l--;
                }
                
                if(r<arr.size()) {
                    res.push_back(arr[r]);
                    r++;
                }
            }
        }
        
        sort(res.begin(), res.end());
        return res;

        // int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        // int closestInd = idx;
        // if(idx == n){
        //     closestInd = idx-1;
        // }
        // else{
        //     if(arr[closestInd] != x && closestInd >0){
        //         if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
        //             closestInd = closestInd -1;
        //         }
        //     }
        // }
        // int left = closestInd-1;
        // int right = closestInd +1;

        // // vector<int> ans;
        // multiset<int> ans;
        // ans.insert(arr[closestInd]);
        // k--; // need to find k-1 elements more
        // while(k--){
        //     if(left>=0 && right <n){
        //         if(abs(arr[left] - x) <= abs(arr[right] - x)){
        //             ans.insert(arr[left]);
        //             left--;
        //         }
        //         else{
        //             ans.insert(arr[right++]);
        //         }
        //     }
        //     else if(left >=0){
        //         ans.insert(arr[left]);
        //         left--;
        //     }
        //     else if(right <n){
        //         ans.insert(arr[right]);
        //         right++;
        //     }
        // }

        // return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 7 · 2023-05-19 11:29 IST · Accepted · C++

[submission 953160030](https://leetcode.com/submissions/detail/953160030/) · tests 66/66 · runtime 48 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        vector<int> res;
        int low =0;int high = arr.size()-1;
        int idx = n;
        bool found = false;
        while(low<=high) {
            int mid = low + ((high-low)>>1);
            if(arr[mid] == x) {
                idx = mid;
                high = mid-1;
                found = true;
            } else if(arr[mid] < x) {
                low = mid + 1;
            } else {
                if(!found) idx = mid;
                high = mid-1;
            }
        }
        // cout<<idx<<" IND "<<arr[idx];
        if(idx == n){
            idx--;
        }
        else{
            if(idx>0 && abs(arr[idx-1] - x) <= abs(arr[idx] -x) )
                idx--;
        }
        int l = idx-1;
        int r = idx+1;
        res.push_back(arr[idx]);
        k--;
        while(k--) {
            if(l>=0 && r < arr.size()) {
                if(abs(x-arr[l]) <= abs(x-arr[r])) {
                    res.push_back(arr[l]);
                    l--;
                } else {
                    res.push_back(arr[r]);
                    r++;
                }
            } else {
                if(l>=0) {
                    res.push_back(arr[l]);
                    l--;
                }
                
                if(r<arr.size()) {
                    res.push_back(arr[r]);
                    r++;
                }
            }
        }
        
        sort(res.begin(), res.end());
        return res;

        // int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        // int closestInd = idx;
        // if(idx == n){
        //     closestInd = idx-1;
        // }
        // else{
        //     if(arr[closestInd] != x && closestInd >0){
        //         if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
        //             closestInd = closestInd -1;
        //         }
        //     }
        // }
        // int left = closestInd-1;
        // int right = closestInd +1;

        // // vector<int> ans;
        // multiset<int> ans;
        // ans.insert(arr[closestInd]);
        // k--; // need to find k-1 elements more
        // while(k--){
        //     if(left>=0 && right <n){
        //         if(abs(arr[left] - x) <= abs(arr[right] - x)){
        //             ans.insert(arr[left]);
        //             left--;
        //         }
        //         else{
        //             ans.insert(arr[right++]);
        //         }
        //     }
        //     else if(left >=0){
        //         ans.insert(arr[left]);
        //         left--;
        //     }
        //     else if(right <n){
        //         ans.insert(arr[right]);
        //         right++;
        //     }
        // }

        // return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 8 · 2023-05-20 13:45 IST · Accepted · C++

[submission 953786455](https://leetcode.com/submissions/detail/953786455/) · tests 66/66 · runtime 36 ms (beats 7.0%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        vector<int> res;
        int low =0;int high = arr.size()-1;
        int idx = n;
        bool found = false;
        while(low<=high) {
            int mid = low + ((high-low)>>1);
            if(arr[mid] == x) {
                idx = mid;
                high = mid-1;
                found = true;
            } else if(arr[mid] < x) {
                low = mid + 1;
            } else {
                if(!found) idx = mid;
                high = mid-1;
            }
        }
        // cout<<idx<<" IND "<<arr[idx];
        if(idx == n){
            idx--;
        }
        else{
            if(idx>0 && abs(arr[idx-1] - x) <= abs(arr[idx] -x) )
                idx--;
        }
        int l = idx-1;
        int r = idx+1;
        res.push_back(arr[idx]);
        k--;
        while(k--) {
            if(l>=0 && r < arr.size()) {
                if(abs(x-arr[l]) <= abs(x-arr[r])) {
                    res.push_back(arr[l]);
                    l--;
                } else {
                    res.push_back(arr[r]);
                    r++;
                }
            } else {
                if(l>=0) {
                    res.push_back(arr[l]);
                    l--;
                }
                
                if(r<arr.size()) {
                    res.push_back(arr[r]);
                    r++;
                }
            }
        }
        
        sort(res.begin(), res.end());
        return res;

        // int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        // int closestInd = idx;
        // if(idx == n){
        //     closestInd = idx-1;
        // }
        // else{
        //     if(arr[closestInd] != x && closestInd >0){
        //         if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
        //             closestInd = closestInd -1;
        //         }
        //     }
        // }
        // int left = closestInd-1;
        // int right = closestInd +1;

        // // vector<int> ans;
        // multiset<int> ans;
        // ans.insert(arr[closestInd]);
        // k--; // need to find k-1 elements more
        // while(k--){
        //     if(left>=0 && right <n){
        //         if(abs(arr[left] - x) <= abs(arr[right] - x)){
        //             ans.insert(arr[left]);
        //             left--;
        //         }
        //         else{
        //             ans.insert(arr[right++]);
        //         }
        //     }
        //     else if(left >=0){
        //         ans.insert(arr[left]);
        //         left--;
        //     }
        //     else if(right <n){
        //         ans.insert(arr[right]);
        //         right++;
        //     }
        // }

        // return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 9 · 2023-05-20 13:45 IST · Compile Error · C++

[submission 953786698](https://leetcode.com/submissions/detail/953786698/)

Your output:

```text
{"compile_error": "Line 46: Char 16: error: no viable conversion from returned value of type 'multiset<int>' to function return type 'vector<int>'\n        return ans;\n               ^~~\n/usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_vector.h:550:7: note: candidate constructor not viable: no known conversion from 'multiset<int>' to 'const std::vector<int, std::allocato ... [1154 more chars]
```

Compile error:

```text
Line 46: Char 16: error: no viable conversion from returned value of type 'multiset<int>' to function return type 'vector<int>'
        return ans;
               ^~~
/usr/bin/../lib/gcc/x86_64-linux-gnu/9/../../../../include/c++/9/bits/stl_vector.h:550:7: note: candidate constructor not viable: no known conversion from 'multiset<int>' to 'const std::vector<int, std::allocator<int>> &' for 1st arg ... [1115 more chars]
```

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int closestInd = idx;
        if(idx == n){
            closestInd = idx-1;
        }
        else{
            if(arr[closestInd] != x && closestInd >0){
                if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
                    closestInd = closestInd -1;
                }
            }
        }
        int left = closestInd-1;
        int right = closestInd +1;

        // vector<int> ans;
        multiset<int> ans;
        ans.insert(arr[closestInd]);
        k--; // need to find k-1 elements more
        while(k--){
            if(left>=0 && right <n){
                if(abs(arr[left] - x) <= abs(arr[right] - x)){
                    ans.insert(arr[left]);
                    left--;
                }
                else{
                    ans.insert(arr[right++]);
                }
            }
            else if(left >=0){
                ans.insert(arr[left]);
                left--;
            }
            else if(right <n){
                ans.insert(arr[right]);
                right++;
            }
        }

        return vector<int>(ans.begin() , ans.end());
        return ans;
    }
};
```

## Attempt 10 · 2023-05-20 13:46 IST · Accepted · C++

[submission 953786794](https://leetcode.com/submissions/detail/953786794/) · tests 66/66 · runtime 84 ms (beats 5.4%)

```cpp
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int closestInd = idx;
        if(idx == n){
            closestInd = idx-1;
        }
        else{
            if(arr[closestInd] != x && closestInd >0){
                if(abs(x- arr[closestInd-1]) <= abs(x- arr[closestInd])){
                    closestInd = closestInd -1;
                }
            }
        }
        int left = closestInd-1;
        int right = closestInd +1;

        // vector<int> ans;
        multiset<int> ans;
        ans.insert(arr[closestInd]);
        k--; // need to find k-1 elements more
        while(k--){
            if(left>=0 && right <n){
                if(abs(arr[left] - x) <= abs(arr[right] - x)){
                    ans.insert(arr[left]);
                    left--;
                }
                else{
                    ans.insert(arr[right++]);
                }
            }
            else if(left >=0){
                ans.insert(arr[left]);
                left--;
            }
            else if(right <n){
                ans.insert(arr[right]);
                right++;
            }
        }

        return vector<int>(ans.begin() , ans.end());
        // return ans;
    }
};
```

## Attempt 11 · 2024-01-15 12:37 IST · Accepted · Python3

[submission 1146647786](https://leetcode.com/submissions/detail/1146647786/) · tests 69/69 · runtime 269 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])
```

## Attempt 12 · 2024-01-15 22:09 IST · Wrong Answer · Python3

[submission 1147028310](https://leetcode.com/submissions/detail/1147028310/) · tests 66/69

Failing input:

```text
[1]
1
1
```

Expected:

```text
[1]
```

Your output:

```text
[]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        # find elements between the window not including the window
        while right - left - 1<k:
            if right >= len(arr) or abs(arr[left]-x)<= abs(arr[right]-x):
                left -=1
            else:
                right +=1

        return arr[left+1:right]
```

## Attempt 13 · 2024-01-15 22:11 IST · Wrong Answer · Python3

[submission 1147029879](https://leetcode.com/submissions/detail/1147029879/) · tests 68/69

Failing input:

```text
[1,1]
1
1
```

Expected:

```text
[1]
```

Your output:

```text
[]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        print(left, right, closest)
        # find elements between the window not including the window
        while right - left - 1<k:
            if right >= len(arr) or abs(arr[left]-x)<= abs(arr[right]-x):
                left -=1
            else:
                right +=1

        return arr[left+1:right]
```

## Attempt 14 · 2024-01-15 22:16 IST · Accepted · Python3

[submission 1147034486](https://leetcode.com/submissions/detail/1147034486/) · tests 69/69 · runtime 231 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]
```

## Attempt 15 · 2024-01-15 22:20 IST · Accepted · Python3

[submission 1147037915](https://leetcode.com/submissions/detail/1147037915/) · tests 69/69 · runtime 226 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr

        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 16 · 2024-01-28 00:42 IST · Runtime Error · Python3

[submission 1158532712](https://leetcode.com/submissions/detail/1158532712/) · tests 6/69

Failing input:

```text
[-2,-1,1,2,3,4,5]
7
3
```

Expected:

```text
[-2,-1,1,2,3,4,5]
```

Runtime error:

```text
IndexError: list index out of range
                                                 ~~~^^^^^^^
    if left >=0 and abs(x - arr[left]) <= abs(x- arr[right]):
Line 146 in findClosestElements (Solution.py)
          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    ret = Solution().findClosestElements(param_1, param_2, param_3)
Line 208 in _driver (Solution.py)
    _driver()
Line 219 in  ... [22 more chars]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1 <k:
            if left >=0 and abs(x - arr[left]) <= abs(x- arr[right]):
                left -=1
            else:
                right +=1

        # print(left, right)
        return arr[left+1: right]
```

## Attempt 17 · 2024-02-07 00:43 IST · Wrong Answer · Python3

[submission 1168118751](https://leetcode.com/submissions/detail/1168118751/) · tests 48/69

Failing input:

```text
[1,2]
1
1
```

Expected:

```text
[1]
```

Your output:

```text
[]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) <= abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1 <k:
            if left < 0:
                right +=1
            if right >=len(arr) or abs(x - arr[left]) <= abs(x- arr[right]):
                left -=1
            else:
                right +=1

        print(left, right)
        return arr[left+1: right]
```

## Attempt 18 · 2024-02-07 00:43 IST · Wrong Answer · Python3

[submission 1168118838](https://leetcode.com/submissions/detail/1168118838/) · tests 45/69

Failing input:

```text
[1,2]
1
1
```

Expected:

```text
[1]
```

Your output:

```text
[]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1 <k:
            if left < 0:
                right +=1
            if right >=len(arr) or abs(x - arr[left]) <= abs(x- arr[right]):
                left -=1
            else:
                right +=1

        print(left, right)
        return arr[left+1: right]
```

## Attempt 19 · 2024-02-07 00:43 IST · Accepted · Python3

[submission 1168119142](https://leetcode.com/submissions/detail/1168119142/) · tests 69/69 · runtime 226 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1 <k:
            if left < 0:
                right +=1
            if right >=len(arr) or abs(x - arr[left]) <= abs(x- arr[right]):
                left -=1
            else:
                right +=1

        print(left, right)
        return arr[left+1: right]
```

## Attempt 20 · 2024-02-07 00:59 IST · Wrong Answer · Python3

[submission 1168130995](https://leetcode.com/submissions/detail/1168130995/) · tests 45/69

Failing input:

```text
[1,2]
1
1
```

Expected:

```text
[1]
```

Your output:

```text
[]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1 <k:
            if left < 0:
                right +=1
            if right >=len(arr) or abs(x - arr[left]) <= abs(x- arr[right]):
                left -=1
            else:
                right +=1

        print(left, right)
        return arr[left+1: right]
```

## Attempt 21 · 2024-02-07 01:00 IST · Wrong Answer · Python3

[submission 1168131478](https://leetcode.com/submissions/detail/1168131478/) · tests 51/69

Failing input:

```text
[1,2,2,2,5,5,5,8,9,9]
4
0
```

Expected:

```text
[1,2,2,2]
```

Your output:

```text
[2,2,5,5]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 22 · 2024-02-07 01:02 IST · Accepted · Python3

[submission 1168132889](https://leetcode.com/submissions/detail/1168132889/) · tests 69/69 · runtime 211 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements7(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 23 · 2024-02-07 01:02 IST · Accepted · Python3

[submission 1168133103](https://leetcode.com/submissions/detail/1168133103/) · tests 69/69 · runtime 224 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# bisect.bisect_left(arr, x)

        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements7(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 24 · 2024-02-07 01:03 IST · Wrong Answer · Python3

[submission 1168134202](https://leetcode.com/submissions/detail/1168134202/) · tests 51/69

Failing input:

```text
[1,2,2,2,5,5,5,8,9,9]
4
0
```

Expected:

```text
[1,2,2,2]
```

Your output:

```text
[2,2,5,5]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if arr[mid] <x:
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# bisect.bisect_left(arr, x)
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 25 · 2024-02-07 01:05 IST · Wrong Answer · Python3

[submission 1168135186](https://leetcode.com/submissions/detail/1168135186/) · tests 20/69

Failing input:

```text
[1,1,1,10,10,10]
1
9
```

Expected:

```text
[10]
```

Your output:

```text
[1]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    l = mid+1
                else:
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# bisect.bisect_left(arr, x)
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements3(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 26 · 2024-02-07 01:05 IST · Accepted · Python3

[submission 1168135240](https://leetcode.com/submissions/detail/1168135240/) · runtime 206 ms

_Code not returned by LeetCode._

## Attempt 27 · 2024-02-07 01:25 IST · Wrong Answer · Python3

[submission 1168149623](https://leetcode.com/submissions/detail/1168149623/) · tests 56/69

Failing input:

```text
[1,1,2,2,2,2,2,3,3]
3
3
```

Expected:

```text
[2,3,3]
```

Your output:

```text
[2,2,2]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                print('comparing', arr[mid], x)
                #if arr[mid] < x:
                if abs(arr[mid] - x) > abs(arr[mid+1] - x):
                    
                    # abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    l = mid+1
                else:
                    # this usally works without checking equals and returning the found value
                    # it keeps the leftt pointer on the matched value or if 
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# bisect.bisect_left(arr, x)
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements3(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 28 · 2024-02-07 01:41 IST · Accepted · Python3

[submission 1168160380](https://leetcode.com/submissions/detail/1168160380/) · tests 69/69 · runtime 208 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                print('comparing', arr[mid], x)

                # where a number would be inserted 
                # find the right position to insert x 
                # if number is present -here
                # if a number is not present the next position where it can be inserted
                if arr[mid] < x:
                    l = mid+1
                else:
                    # this usally works without checking equals and returning the found value
                    # it keeps the leftt pointer on the matched value or if 
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# 
        print(bisect.bisect_left(arr, x))
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1 < k:
            # if left <0: # left out of bound
            #     right +=1
            # elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
            #     left -=1
            # else:
            #     right +=1

            if left < 0 or (right < len(arr) and abs(arr[right] - x) < abs(arr[left] - x)):
                right += 1
            else:
                left -= 1



        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements3(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 29 · 2024-02-09 22:27 IST · Wrong Answer · Python3

[submission 1170772336](https://leetcode.com/submissions/detail/1170772336/) · tests 51/69

Failing input:

```text
[1,2,2,2,5,5,5,8,9,9]
4
0
```

Expected:

```text
[1,2,2,2]
```

Your output:

```text
[2,2,5,5]
```

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                print('comparing', arr[mid], x)

                # where a number would be inserted 
                # find the right position to insert x 
                # if number is present -here
                # if a number is not present the next position where it can be inserted
                if arr[mid] < x:
                    l = mid+1
                else:
                    # this usally works without checking equals and returning the found value
                    # it keeps the leftt pointer on the matched value or if 
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# 
        print(bisect.bisect_left(arr, x))
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1 < k:
            if left < 0 or (right < len(arr) and abs(arr[right] - x) < abs(arr[left] - x)):
                right += 1
            else:
                left -= 1

        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 30 · 2024-02-09 22:33 IST · Accepted · Python3

[submission 1170777129](https://leetcode.com/submissions/detail/1170777129/) · tests 69/69 · runtime 220 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                print('comparing', arr[mid], x)

                # where a number would be inserted 
                # find the right position to insert x 
                # if number is present -here
                # if a number is not present the next position where it can be inserted
                if arr[mid] < x:
                    l = mid+1
                else:
                    # this usally works without checking equals and returning the found value
                    # it keeps the leftt pointer on the matched value or if 
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# 
        closest = bisect.bisect_right(arr,x)
        print(bisect.bisect_left(arr, x))
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1 < k:
            if left < 0 or (right < len(arr) and abs(arr[right] - x) < abs(arr[left] - x)):
                right += 1
            else:
                left -= 1

        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements3(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```

## Attempt 31 · 2024-02-09 22:33 IST · Accepted · Python3

[submission 1170777298](https://leetcode.com/submissions/detail/1170777298/) · tests 69/69 · runtime 214 ms (beats 5.1%)

```python
class Solution:
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        
        # Helper function to find the index of the closest element to x
        def binarySearchClosest(arr, x):
            low, high = 0, len(arr) - 1
            while low < high:
                mid = low + (high - low) // 2
                if arr[mid] < x:
                    low = mid + 1
                else:
                    high = mid
            return low

        # Find the index of the closest element to x
        index = binarySearchClosest(arr, x)

        # Initialize two pointers
        left, right = index - 1, index

        print(left, right)

        # Find the k closest elements
        while right - left - 1 < k:
            print('here')
            if left == -1:
                right += 1
            elif right == len(arr) or abs(arr[left] - x) <= abs(arr[right] - x):
                left -= 1
            else:
                right += 1
            print(left, right)

        # Return the sorted k closest elements
        return (arr[left + 1:right])


    # ver1 - sort two times
    # first with difference target - num and then for result
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        arr.sort(key = lambda num: abs(x-num))
        # print(arr)
        return sorted(arr[:k])

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        if len(arr) == k:
            return arr
        closest = bisect.bisect_left(arr, x)
        
        left = closest- 1
        right = closest

        while right - left - 1<k:
            # Be careful to not go out of bounds
            if left < 0:  # Check if left is out of bounds - include right
                right += 1
            elif right >= len(arr) or abs(arr[left] - x) <= abs(arr[right] - x): # right is out of bound or left is closer - include left
                left -= 1
            else:
                right += 1
            

        return arr[left+1:right]

    #ver 2 
    # do a binary search to find the closest elemnt to x
    # then do a search around that to find either to the left or to the right
    def findClosestElements(self, arr: List[int], k: int, x: int) -> List[int]:
        # Base case
        # if len(arr) == k:
        #     return arr
        def binary_search(arr, x):
            l = 0
            r = len(arr) -1
            while l < r:
                mid = (l+r)//2

                print('comparing', arr[mid], x)

                # where a number would be inserted 
                # find the right position to insert x 
                # if number is present -here
                # if a number is not present the next position where it can be inserted
                if arr[mid] < x:
                    l = mid+1
                else:
                    # this usally works without checking equals and returning the found value
                    # it keeps the leftt pointer on the matched value or if 
                    r = mid
            return l


        # find closest 
        closest = binary_search(arr,x)# 
        closest = bisect.bisect_left(arr,x)
        print(bisect.bisect_left(arr, x))
        print(closest)
        # expand the window 
        left = closest -1
        right = closest

        # not inclusive
        while right - left - 1 < k:
            if left < 0 or (right < len(arr) and abs(arr[right] - x) < abs(arr[left] - x)):
                right += 1
            else:
                left -= 1

        return arr[left+1:right]

    def findClosestElements8(self, arr: List[int], k: int, x: int) -> List[int]:
        left = 0
        right = len(arr) -k

        while left < right:
            mid = (left+right)//2

            if abs(arr[mid] -x ) <= abs(arr[mid+k] -x):
                right = mid
            else:
                left = mid +1

        return arr[left:left+l]

    def findClosestElements3(self, arr: List[int], k: int, x: int) -> List[int]:    
        '''
        1. find the closet element to x in arr
        '''    
        def find_closest(arr, x):
            l = 0
            r = len(arr)-1

            while l < r:
                mid  = (l+r)//2

                if abs(x - arr[mid]) < abs(x- arr[mid+1]):
                    r = mid 
                else:
                    l = mid +1
            return l
        
        closest = find_closest(arr,x)
        print(closest)
        # return []
        left = closest - 1
        right = closest

        while right - left - 1<k:
            if left <0: # left out of bound
                right +=1
            elif right >=len(arr) or abs(arr[left] - x) <= abs(arr[right] - x) :
                left -=1
            else:
                right +=1


        return arr[left+1:right]
```
