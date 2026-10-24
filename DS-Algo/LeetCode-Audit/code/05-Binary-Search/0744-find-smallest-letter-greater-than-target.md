# 744. Find Smallest Letter Greater Than Target

[Problem](https://leetcode.com/problems/find-smallest-letter-greater-than-target/) · Easy · Binary Search → Upper bound

LeetCode tags: array, binary-search

Attempts since Mar 2023: 3 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-22 12:57 IST · Accepted · C++

[submission 954953476](https://leetcode.com/submissions/detail/954953476/) · tests 167/167 · runtime 11 ms (beats 0.2%)

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& arr, char target) {
        int low = 0, high = arr.size()-1;
        int ans = -1;
        while(low <= high){
            int mid = low + (high- low)/2;
            char ch = arr[mid];
            if(ch > target){
                ans = mid;
                high = mid -1;
            }else{
                low = mid +1;
            }
        }
        return ans ==-1 ? arr[0] : arr[ans];
    }
};
```

## Attempt 2 · 2023-05-22 13:06 IST · Runtime Error · C++

[submission 954958167](https://leetcode.com/submissions/detail/954958167/) · tests 5/167

Failing input:

```text
["c","f","j"]
"j"
```

Expected:

```text
"c"
```

Runtime error:

```text
Line 66: Char 12: runtime error: index -66 out of bounds for type 'std::string [256]' (_Serializer_.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior _Serializer_.cpp:75:12
```

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& arr, char target) {
        int low = 0, high = arr.size()-1;
        int ans = -1;
         if(target > arr[high]) return arr[0]; // also correct
        while(low <= high){
            int mid = low + (high- low)/2;
            char ch = arr[mid];
            if(ch > target){
                ans = mid;
                high = mid -1;
            }else{
                low = mid +1;
            }
        }
        return arr[low];
    }
};
```

## Attempt 3 · 2023-05-22 13:07 IST · Accepted · C++

[submission 954958311](https://leetcode.com/submissions/detail/954958311/) · tests 167/167 · runtime 21 ms (beats 0.2%)

```cpp
class Solution {
public:
    char nextGreatestLetter(vector<char>& arr, char target) {
        int low = 0, high = arr.size()-1;
        int ans = -1;
        if(target >= arr[high]) return arr[0]; // also correct
        while(low <= high){
            int mid = low + (high- low)/2;
            char ch = arr[mid];
            if(ch > target){
                ans = mid;
                high = mid -1;
            }else{
                low = mid +1;
            }
        }
        return arr[low];
    }
};
```
