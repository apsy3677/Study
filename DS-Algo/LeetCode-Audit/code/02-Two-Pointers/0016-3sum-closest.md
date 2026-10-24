# 16. 3Sum Closest

[Problem](https://leetcode.com/problems/3sum-closest/) · Medium · Two Pointers → Sort + two pointers

LeetCode tags: array, two-pointers, sorting

Attempts since Mar 2023: 8 · accepted: 3 · failed before first AC: 5

## Attempt 1 · 2023-05-21 11:52 IST · Wrong Answer · C++

[submission 954337717](https://leetcode.com/submissions/detail/954337717/) · tests 47/99

Failing input:

```text
[1,1,1,0]
-100
```

Expected:

```text
2
```

Your output:

```text
3
```

```cpp
class Solution {
    int twoSum(vector<int>& arr, int sum, int index){
        int left =index +1 , right = arr.size() -1;
        int closestDiff = INT_MAX;
        int closest = INT_MIN;
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - sum);
            if( diff < closestDiff){
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                left++;
            }
            else if(arr[left] + arr[right] < sum) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0, closest = INT_MIN;
        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            if(i==0 || arr[i-1] != arr[i])
                closest = max(twoSum(arr, sum, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 2 · 2023-05-21 11:58 IST · Wrong Answer · C++

[submission 954340859](https://leetcode.com/submissions/detail/954340859/) · tests 65/99

Failing input:

```text
[-23,-67,32,21,-65,46,73,42,93,9,-61,-79,-51,61,-15,49,92,-34,50,1,26,-12,68,-97,-17,51,-55,75,-56,-95,-70,-42,91,-18,-64,20,33,-20,19,61,-89,81,-73,82,-23,-65,51,-88,15,-48,24,34,0,-24,37,22,28,-67,-25,-61,-57,-74,65,50,-66,24,99,80,44,85,20,-4,-9,-81,87,-82,-100,51,-83,9,-31,37,23,-61,53,-14,-51,88,56,27,42,-52,-97,37,36,-59,-45,95,46,-1,-100,-38,66,44,27,-97,12,-43,84,-53,93,18,-40,-38,34,85,53 ... [162 more chars]
```

Expected:

```text
-87
```

Your output:

```text
-86
```

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int sum, int index){
        int left =index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - sum);
            if( diff < closestDiff){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                left++; right--;
            }
            else if(arr[left] + arr[right] < sum) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0, closest = INT_MIN;
        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            
            closest = max(twoSum(arr, target, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 3 · 2023-05-21 12:02 IST · Wrong Answer · C++

[submission 954342495](https://leetcode.com/submissions/detail/954342495/) · tests 63/99

Failing input:

```text
[0,3,97,102,200]
300
```

Expected:

```text
300
```

Your output:

```text
302
```

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int target, int index){
        int left =index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) ){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                left++; 
                // right--;
            }
            else if(arr[left] + arr[right] < target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0, closest = INT_MIN;
        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            
            closest = max(twoSum(arr, target, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 4 · 2023-05-21 12:03 IST · Wrong Answer · C++

[submission 954342980](https://leetcode.com/submissions/detail/954342980/) · tests 67/99

Failing input:

```text
[833,736,953,-584,-448,207,128,-445,126,248,871,860,333,-899,463,488,-50,-331,903,575,265,162,-733,648,678,549,579,-172,-897,562,-503,-508,858,259,-347,-162,-505,-694,300,-40,-147,383,-221,-28,-699,36,-229,960,317,-585,879,406,2,409,-393,-934,67,71,-312,787,161,514,865,60,555,843,-725,-966,-352,862,821,803,-835,-635,476,-704,-78,393,212,767,-833,543,923,-993,274,-839,389,447,741,999,-87,599,-349,- ... [333 more chars]
```

Expected:

```text
-2960
```

Your output:

```text
-1599
```

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int target, int index){
        int left =index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) ){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                left++; 
                right--;
            }
            else if(arr[left] + arr[right] + arr[index]< target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0, closest = INT_MIN;
        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            
            closest = max(twoSum(arr, target, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 5 · 2023-05-22 15:10 IST · Wrong Answer · C++

[submission 955015460](https://leetcode.com/submissions/detail/955015460/) · tests 96/99

Failing input:

```text
[0,3,97,102,200]
300
```

Expected:

```text
300
```

Your output:

```text
302
```

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int target, int index){
        int left = index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) ){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                // left++; 
                // right--;
            }
            if(arr[left] + arr[right] + arr[index] < target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0, closest1 = INT_MIN;
        closestDiff = INT_MAX;
        closest = INT_MIN;

        for(int i=0;i<arr.size();i++){
            int sum = totalSum - arr[i];
            closest1 = max(twoSum(arr, target, i), closest1);
        }
        return {closest1};
    }
};
```

## Attempt 6 · 2023-05-22 15:14 IST · Accepted · C++

[submission 955017863](https://leetcode.com/submissions/detail/955017863/) · tests 99/99 · runtime 384 ms (beats 5.2%)

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int target, int index){
        int left = index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) || diff ==0){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                // left++; 
                // right--;
            }
            if(arr[left] + arr[right] + arr[index] < target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0;
        closestDiff = INT_MAX;
        closest = INT_MIN;

        for(int i=0;i<arr.size();i++){
            closest = max(twoSum(arr, target, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 7 · 2023-05-22 15:15 IST · Accepted · C++

[submission 955018008](https://leetcode.com/submissions/detail/955018008/) · tests 99/99 · runtime 308 ms (beats 5.3%)

```cpp
class Solution {
    int closestDiff = INT_MAX;
    int closest = INT_MIN;
    int twoSum(vector<int>& arr, int target, int index){
        int left = index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) ){
                cout<<diff<<":"<<closestDiff<<" :: ";
                cout<<arr[index]<<" "<<arr[left] <<" "<<arr[right]<<" || ";
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
                // left++; 
                // right--;
            }
            if(arr[left] + arr[right] + arr[index] < target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int totalSum = 0;
        closestDiff = INT_MAX;
        closest = INT_MIN;

        for(int i=0;i<arr.size();i++){
            closest = max(twoSum(arr, target, i), closest);
        }
        return {closest};
    }
};
```

## Attempt 8 · 2023-05-22 15:19 IST · Accepted · C++

[submission 955019848](https://leetcode.com/submissions/detail/955019848/) · tests 99/99 · runtime 84 ms (beats 6.0%)

```cpp
class Solution {
    
    int twoSum(vector<int>& arr, int target, int index, int& closest, int &closestDiff){
        int left = index +1 , right = arr.size() -1;
        
        while(left <right){
            int diff = abs(arr[left] + arr[right] + arr[index] - target);
            if( diff < abs(closestDiff) ){
                closestDiff = diff;
                closest = arr[left] + arr[index] + arr[right];
            }
            if(arr[left] + arr[right] + arr[index] < target) left++;
            else right--;
        }
        return closest;
    }
public:
    int threeSumClosest(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int closestDiff = INT_MAX;
        int closest = INT_MIN;
        int totalSum = 0;
        closestDiff = INT_MAX;
        closest = INT_MIN;

        for(int i=0;i<arr.size();i++){
            twoSum(arr, target, i, closest, closestDiff);
        }
        return closest;
    }
};
```
