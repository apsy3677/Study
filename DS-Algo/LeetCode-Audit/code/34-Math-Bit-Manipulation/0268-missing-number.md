# 268. Missing Number

[Problem](https://leetcode.com/problems/missing-number/) · Easy · Math & Bit Manipulation → XOR / sum

LeetCode tags: array, hash-table, math, binary-search, bit-manipulation, sorting

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-05-20 18:07 IST · Accepted · C++

[submission 953893283](https://leetcode.com/submissions/detail/953893283/) · tests 122/122 · runtime 19 ms (beats 9.0%)

```cpp
class Solution {
public:
    int missingNumber(vector<int>& arr) {
        long sum = 0;
        for(auto x: arr){
            sum += x;
        }
        long n = arr.size();
        
        return n*(n+1)/2 - sum;
    }
};
```

## Attempt 2 · 2023-05-24 08:23 IST · Accepted · C++

[submission 956169851](https://leetcode.com/submissions/detail/956169851/) · tests 122/122 · runtime 15 ms (beats 10.9%)

```cpp
class Solution {
public:
    int Maths(vector<int>& arr){
        long sum = 0;
        for(auto x: arr){
            sum += x;
        }
        long n = arr.size();
        
        return n*(n+1)/2 - sum;
    }
    int missingNumber(vector<int>& arr) {
        return Maths(arr);
    }
};
```

## Attempt 3 · 2023-05-24 08:26 IST · Accepted · C++

[submission 956170954](https://leetcode.com/submissions/detail/956170954/) · tests 122/122 · runtime 29 ms (beats 6.4%)

```cpp
class Solution {
public:
    int Maths(vector<int>& arr){
        long sum = 0;
        for(auto x: arr){
            sum += x;
        }
        long n = arr.size();
        
        return n*(n+1)/2 - sum;
    }
    int cyclicSort(vector<int> arr){
        int i = 0;

        while(i<arr.size()){
            int correctIndex = arr[i]; // correct index for arr[i] element     
            if(correctIndex == arr.size()){
                i++;
                continue;
            }
            if(arr[i] != arr[correctIndex]){
                swap(arr[i], arr[correctIndex]);
            }
            else{
                i++;
            }
        }
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i) return i;
        }
        return arr.size();
    }
    int missingNumber(vector<int>& arr) {
        // return Maths(arr);
        return cyclicSort(arr);
    }
};
```

## Attempt 4 · 2023-05-24 08:28 IST · Accepted · C++

[submission 956171574](https://leetcode.com/submissions/detail/956171574/) · tests 122/122 · runtime 29 ms (beats 6.4%)

```cpp
class Solution {
public:
    int Maths(vector<int>& arr){
        long sum = 0;
        for(auto x: arr){
            sum += x;
        }
        long n = arr.size();
        
        return n*(n+1)/2 - sum;
    }
    int cyclicSort(vector<int> arr){
        int i = 0;

        while(i<arr.size()){
            int correctIndex = arr[i]; // correct index for arr[i] element     
            if(correctIndex != arr.size() && arr[i] != arr[correctIndex]){
                swap(arr[i], arr[correctIndex]);
            }
            else{
                i++;
            }
        }
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i) return i;
        }
        return arr.size();
    }
    int missingNumber(vector<int>& arr) {
        // return Maths(arr);
        return cyclicSort(arr);
    }
};
```

## Attempt 5 · 2023-05-24 08:30 IST · Accepted · C++

[submission 956172334](https://leetcode.com/submissions/detail/956172334/) · tests 122/122 · runtime 26 ms (beats 6.6%)

```cpp
class Solution {
public:
    int Maths(vector<int>& arr){
        long sum = 0;
        for(auto x: arr){
            sum += x;
        }
        long n = arr.size();
        
        return n*(n+1)/2 - sum;
    }
    int cyclicSort(vector<int> arr){
        int i = 0;

        while(i<arr.size()){
            int correctIndex = arr[i]; // correct index for arr[i] element     
            if(correctIndex < arr.size() && arr[i] != arr[correctIndex]){
                swap(arr[i], arr[correctIndex]);
            }
            else{
                i++;
            }
        }
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i) return i;
        }
        return arr.size();
    }
    int missingNumber(vector<int>& arr) {
        // return Maths(arr);
        return cyclicSort(arr);
    }
};
```
