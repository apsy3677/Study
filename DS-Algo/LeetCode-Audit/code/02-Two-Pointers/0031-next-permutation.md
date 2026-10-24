# 31. Next Permutation

[Problem](https://leetcode.com/problems/next-permutation/) · Medium · Two Pointers → Next permutation

LeetCode tags: array, two-pointers

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 1

## Attempt 1 · 2023-03-26 01:53 IST · Wrong Answer · C++

[submission 922060308](https://leetcode.com/submissions/detail/922060308/) · tests 141/265

Failing input:

```text
[1,3,2]
```

Expected:

```text
[2,1,3]
```

Your output:

```text
[3,1,2]
```

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n<=1) return;
        int i = n-1;
        for(i=n-1;i>0;i--){
            if(nums[i]< nums[i-1]) continue;
            // swap(nums[i], nums[i-1]);
            break;
        }
        if(i==0){
            // means sorted in descending order
            sort(nums.begin(), nums.end()); 
        }
        else{
            // if(i>=0 && i<n-1){
                swap(nums[i], nums[i-1]);
            // }
        }
    }
};
```

## Attempt 2 · 2023-03-26 02:10 IST · Accepted · C++

[submission 922066671](https://leetcode.com/submissions/detail/922066671/) · tests 265/265 · runtime 3 ms (beats 1.8%)

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n<=1) return;
        int i = n-2;
        
        while(i>=0 && nums[i]>=nums[i+1]) i--;

        if(i>=0){
            int j= n-1;
            while(nums[j] <= nums[i]) j--;
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin()+i+1, nums.end());
    }
};
```

## Attempt 3 · 2023-11-15 23:54 IST · Wrong Answer · Python

[submission 1099554668](https://leetcode.com/submissions/detail/1099554668/) · tests 261/266

Failing input:

```text
[1,2]
```

Expected:

```text
[2,1]
```

Your output:

```text
[1,2]
```

```python
class Solution(object):
    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: None Do not return anything, modify nums in-place instead.
        """

        i= len(nums) - 2
        while i>=0 and nums[i] >= nums[i+1]:
            i-=1

        if i>0:
            j = len(nums) -1 
            while nums[j] <= nums[i]:
                j-=1
            
            nums[j], nums[i] = nums[i] , nums[j]

        nums[i+1:] = nums[i+1:][::-1]
```

## Attempt 4 · 2023-12-30 21:42 IST · Accepted · Python3

[submission 1132312147](https://leetcode.com/submissions/detail/1132312147/) · tests 266/266 · runtime 46 ms (beats 0.2%)

```python
class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        '''
        since we want next greater number we have to look from least significat digit
        look for the digit that shold be replaced
        for a decreasing sequence, the only possible next permutation is reversing the digits 
        
        '''
        i = len(nums) - 2

        # skip duplicate, as we want find the first lower number
        while i >=0 and nums[i]>=nums[i+1]:
            i-=1

        # i now points to the small number just before non increasing seq

        # find j - the number just greater than i on right
        j = len(nums) - 1

        if i>=0:
            # skip duplicate or else it would be the same
            while j>=0 and nums[j]<=nums[i]:
                j-=1
            
            nums[i], nums[j] = nums[j], nums[i]
        
        # it handles the case where for the decreasing sequence as well 98761
        nums[i+1:] = nums[i+1:][::-1]

        return nums

    def nextPermutation(self, nums: List[int]) -> None:
        i = len(nums) -2
        while i>=0 and nums[i] >= nums[i+1]:
            i-=1

        j = len(nums) -1
        if i >=0:
        
            while j >=0 and nums[j] <= nums[i]:
                j-=1

            nums[i], nums[j] = nums[j], nums[i]

        # decreasing
        nums[i+1:] = nums[i+1:][::-1]
        return nums
```

## Attempt 5 · 2024-03-25 20:50 IST · Accepted · C++

[submission 1213568405](https://leetcode.com/submissions/detail/1213568405/) · tests 266/266 · runtime 3 ms (beats 1.8%)

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        if(n<=1) return;
        int i = n-2; // coz we compare 2 elements together
        
        while(i>=0 && nums[i]>=nums[i+1]) i--;

        if(i>=0){
            // replace the number a[i] with the number which
            // is just larger than itself among the numbers lying to its right section
            int j= n-1;
            while(nums[j] <= nums[i]) j--;
            // swap with the closest bigger element
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin()+i+1, nums.end());
    }
};
```
