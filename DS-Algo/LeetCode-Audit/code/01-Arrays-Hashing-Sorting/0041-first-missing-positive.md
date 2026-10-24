# 41. First Missing Positive

[Problem](https://leetcode.com/problems/first-missing-positive/) · Hard · Arrays, Hashing & Sorting → Cyclic sort

LeetCode tags: array, hash-table

Attempts since Mar 2023: 11 · accepted: 6 · failed before first AC: 3

## Attempt 1 · 2023-05-21 08:11 IST · Wrong Answer · C++

[submission 954217915](https://leetcode.com/submissions/detail/954217915/) · tests 164/175

Failing input:

```text
[1,1]
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
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        int validNums = 0;
        bool onePresent = false;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
            else{
                validNums++;
            }
        }
        if(!onePresent) return 1;
        if(validNums == N) return N+1;

        // for(auto num : arr) cout<<num<<" "; cout <<"::";

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            if(arr[abs(num)-1] > 0){
                arr[abs(num)-1] = -arr[abs(num)-1];
            }
        }

        // for(auto num : arr) cout<<num<<" ";
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-21 08:13 IST · Wrong Answer · C++

[submission 954220300](https://leetcode.com/submissions/detail/954220300/) · tests 172/175

Failing input:

```text
[1,3,3]
```

Expected:

```text
2
```

Your output:

```text
4
```

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        int validNums = 0;
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
            else{
                maxi = max(maxi, num);
                validNums++;
            }
        }
        if(!onePresent) return 1;
        if(validNums == N && maxi == N) return N+1;

        // for(auto num : arr) cout<<num<<" "; cout <<"::";

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            if(arr[abs(num)-1] > 0){
                arr[abs(num)-1] = -arr[abs(num)-1];
            }
        }

        // for(auto num : arr) cout<<num<<" ";
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-05-21 08:15 IST · Wrong Answer · C++

[submission 954222766](https://leetcode.com/submissions/detail/954222766/) · tests 164/175

Failing input:

```text
[1]
```

Expected:

```text
2
```

Your output:

```text
1
```

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        int validNums = 0;
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
            else{
                maxi = max(maxi, num);
                validNums++;
            }
        }
        if(!onePresent) return 1;
        // if(validNums == N && maxi == N) return N+1;

        // for(auto num : arr) cout<<num<<" "; cout <<"::";

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            if(arr[abs(num)-1] > 0){
                arr[abs(num)-1] = -arr[abs(num)-1];
            }
        }

        // for(auto num : arr) cout<<num<<" ";
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-05-21 08:16 IST · Accepted · C++

[submission 954223490](https://leetcode.com/submissions/detail/954223490/) · tests 175/175 · runtime 71 ms (beats 5.4%)

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        int validNums = 0;
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
            else{
                maxi = max(maxi, num);
                validNums++;
            }
        }
        if(!onePresent) return 1;
        // if(validNums == N && maxi == N) return N+1;

        // for(auto num : arr) cout<<num<<" "; cout <<"::";

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            if(arr[abs(num)-1] > 0){
                arr[abs(num)-1] = -arr[abs(num)-1];
            }
        }

        // for(auto num : arr) cout<<num<<" ";
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        ans++;
        return ans;
    }
};
```

## Attempt 5 · 2023-05-21 08:22 IST · Accepted · C++

[submission 954229515](https://leetcode.com/submissions/detail/954229515/) · tests 175/175 · runtime 60 ms (beats 11.3%)

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```

## Attempt 6 · 2023-05-21 08:25 IST · Accepted · C++

[submission 954231547](https://leetcode.com/submissions/detail/954231547/) · tests 175/175 · runtime 51 ms (beats 14.1%)

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& arr) {
        // check if 1 is present, valid numbers
        std::ios::sync_with_stdio(0); std::cin.tie(0);
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```

## Attempt 7 · 2023-05-24 09:08 IST · Wrong Answer · C++

[submission 956186716](https://leetcode.com/submissions/detail/956186716/) · tests 56/175

Failing input:

```text
[1]
```

Expected:

```text
2
```

Your output:

```text
1
```

```cpp
class Solution {
public:
    int cyclicSort(vector<int> &arr){
        int i=0;

        while(i<arr.size()){
            int correct = arr[i]-1;
            if(arr[i] <=0 || arr[i] >arr.size()){
                i++;
                continue;
            }
            if(arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        for(auto x : arr) cout<<x<<" ";
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                return i+1;
        }
        
        return arr.size();
    }
    int firstMissingPositive(vector<int>& arr) {
        return cyclicSort(arr);
        // check if 1 is present, valid numbers
        std::ios::sync_with_stdio(0); std::cin.tie(0);
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```

## Attempt 8 · 2023-05-24 09:09 IST · Runtime Error · C++

[submission 956187012](https://leetcode.com/submissions/detail/956187012/) · tests 61/175

Failing input:

```text
[2147483647,2147483646,2147483645,3,2,1,-1,0,-2147483648]
```

Expected:

```text
4
```

Runtime error:

```text
Line 7: Char 33: runtime error: signed integer overflow: -2147483648 - 1 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:16:33
```

```cpp
class Solution {
public:
    int cyclicSort(vector<int> &arr){
        int i=0;

        while(i<arr.size()){
            int correct = arr[i]-1;
            if(arr[i] <=0 || arr[i] >arr.size()){
                i++;
                continue;
            }
            if(arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        for(auto x : arr) cout<<x<<" ";
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                return i+1;
        }
        
        return arr.size()+1;
    }
    int firstMissingPositive(vector<int>& arr) {
        return cyclicSort(arr);
        // check if 1 is present, valid numbers
        std::ios::sync_with_stdio(0); std::cin.tie(0);
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```

## Attempt 9 · 2023-05-24 09:11 IST · Accepted · C++

[submission 956187648](https://leetcode.com/submissions/detail/956187648/) · tests 175/175 · runtime 373 ms (beats 5.1%)

```cpp
class Solution {
public:
    int cyclicSort(vector<int> &arr){
        int i=0;

        while(i<arr.size()){
            long correct = arr[i]-1L;
            if(arr[i] <=0 || arr[i] >arr.size()){
                i++;
                continue;
            }
            if(arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        for(auto x : arr) cout<<x<<" ";
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                return i+1;
        }
        
        return arr.size()+1;
    }
    int firstMissingPositive(vector<int>& arr) {
        return cyclicSort(arr);
        // check if 1 is present, valid numbers
        std::ios::sync_with_stdio(0); std::cin.tie(0);
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```

## Attempt 10 · 2023-05-24 09:17 IST · Accepted · C++

[submission 956190068](https://leetcode.com/submissions/detail/956190068/) · runtime 76 ms

_Code not returned by LeetCode._

## Attempt 11 · 2023-05-24 09:18 IST · Accepted · C++

[submission 956190757](https://leetcode.com/submissions/detail/956190757/) · tests 175/175 · runtime 65 ms (beats 7.5%)

```cpp
class Solution {
public:
    int cyclicSort(vector<int> &arr){
        int i=0;

        while(i<arr.size()){
            long correct = arr[i]-1L;
            if(arr[i]>0 && arr[i]<arr.size() && arr[i] != arr[correct]){
                swap(arr[i], arr[correct]);
            }
            else{
                i++;
            }
        }
        // for(auto x : arr) cout<<x<<" ";
        for(int i=0;i<arr.size();i++){
            if(arr[i] != i+1)
                return i+1;
        }
        
        return arr.size()+1; // all nums 1 to N are present
    }
    int firstMissingPositive(vector<int>& arr) {
        return cyclicSort(arr);
        // check if 1 is present, valid numbers
        std::ios::sync_with_stdio(0); std::cin.tie(0);
        int N = arr.size();
        bool onePresent = false;
        int maxi = 0;
        for(int &num : arr){
            if(num == 1) onePresent = true;
            if(num <= 0 || num >N){
                // update them to 1
                num = 1;
            }
        }
        if(!onePresent) return 1;

        // Do Hashing as all nums are positive 

        for(int &num : arr){
            // num is positive and arr[num-1] is also positve
            int key = abs(num) - 1;
            if(arr[key] > 0){
                arr[key] = -arr[key];
            }
        }
        
        int ans = 0;
        for(int &num : arr){
            ans++;
            if(num > 0){
                return ans;
            }
        }
        // if all nums are present from 1 to N 
        // ans = N+1
        // ans++;
        return N+1;
    }
};
```
