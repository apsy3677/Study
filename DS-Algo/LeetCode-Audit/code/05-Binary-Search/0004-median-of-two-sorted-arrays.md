# 4. Median of Two Sorted Arrays

[Problem](https://leetcode.com/problems/median-of-two-sorted-arrays/) · Hard · Binary Search → Partition search

LeetCode tags: array, binary-search, divide-and-conquer

Attempts since Mar 2023: 5 · accepted: 3 · failed before first AC: 2

## Attempt 1 · 2023-05-04 14:20 IST · Wrong Answer · C++

[submission 944262345](https://leetcode.com/submissions/detail/944262345/) · tests 1680/2094

Failing input:

```text
[3,4]
[1,2]
```

Expected:

```text
2.50000
```

Your output:

```text
0.00000
```

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0, high = n1;
        while(low <= high){
            int cut1 = (low + high)/2;
            int cut2 = (n1+n2+1)/2 - cut1;

            int l1 = cut1 == 0 ? INT_MIN : nums1[cut1 -1];
            int l2 = cut2 == 0 ? INT_MIN : nums2[cut2 -1];

            int r1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int r2 = cut2 == n2 ? INT_MAX : nums2[cut2];

            if(l1 <= r2 && l2 <=r1){
                if(((n1 + n2) & 1) == 0){
                    return (max(l1,l2) + min(r1,r2))/2.0;
                }
                else{
                    return max(l1,l2);
                }
            }
            else if(l1 > r1){
                high = cut1 -1;
            }
            else{
                low = cut1 + 1;
            }

        }
        return 0.0;
    }
    
};
```

## Attempt 2 · 2023-05-04 14:21 IST · Wrong Answer · C++

[submission 944262653](https://leetcode.com/submissions/detail/944262653/) · tests 1680/2094

Failing input:

```text
[3,4]
[1,2]
```

Expected:

```text
2.50000
```

Your output:

```text
0.00000
```

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0, high = n1;
        while(low <= high){
            int cut1 = (low + high)/2;
            int cut2 = (n1+n2+1)/2 - cut1;

            int l1 = cut1 == 0 ? INT_MIN : nums1[cut1 -1];
            int l2 = cut2 == 0 ? INT_MIN : nums2[cut2 -1];

            int r1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int r2 = cut2 == n2 ? INT_MAX : nums2[cut2];

            if(l1 <= r2 && l2 <=r1){
                if(((n1 + n2) & 1) == 0){
                    return (max(l1,l2) + min(r1,r2))/2.0;
                }
                else{
                    return max(l1,l2);
                }
            }
            else if(l1 > r1){
                high = cut1 -1;
            }
            else{
                low = cut1 + 1;
            }

        }
        return 0.0;
    }
    
};
```

## Attempt 3 · 2023-05-04 14:28 IST · Accepted · C++

[submission 944265436](https://leetcode.com/submissions/detail/944265436/) · tests 2094/2094 · runtime 48 ms (beats 5.9%)

```cpp
class Solution {
public:
    double f(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if(m>n) return f(nums2, nums1);
        int low=0,high=m,medianPos=((m+n)+1)/2;
        while(low<=high) {
            int cut1 = (low+high)>>1;
            int cut2 = medianPos - cut1;
            
            int l1 = (cut1 == 0)? INT_MIN:nums1[cut1-1];
            int l2 = (cut2 == 0)? INT_MIN:nums2[cut2-1];
            int r1 = (cut1 == m)? INT_MAX:nums1[cut1];
            int r2 = (cut2 == n)? INT_MAX:nums2[cut2];
            
            if(l1<=r2 && l2<=r1) {
                if((m+n)%2 != 0)
                    return max(l1,l2);
                else 
                    return (max(l1,l2)+min(r1,r2))/2.0;
            }
            else if(l1>r2) high = cut1-1;
            else low = cut1+1;
        }
        return 0.0;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // return f(nums1,nums2);
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0, high = n1;
        while(low <= high){
            int cut1 = (low + high)/2;
            int cut2 = (n1+n2+1)/2 - cut1;

            int l1 = cut1 == 0 ? INT_MIN : nums1[cut1 -1];
            int l2 = cut2 == 0 ? INT_MIN : nums2[cut2 -1];

            int r1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int r2 = cut2 == n2 ? INT_MAX : nums2[cut2];

            if(l1 <= r2 && l2 <=r1){
                if(((n1 + n2) & 1) == 0){
                    return (max(l1,l2) + min(r1,r2))/2.0;
                }
                else{
                    return max(l1,l2);
                }
            }
            else if(l1 > r2){
                high = cut1 -1;
            }
            else{
                low = cut1 + 1;
            }

        }
        return 0.0;
    }
    
};
```

## Attempt 4 · 2023-05-04 14:31 IST · Accepted · C++

[submission 944266663](https://leetcode.com/submissions/detail/944266663/) · tests 2094/2094 · runtime 60 ms (beats 5.9%)

```cpp
class Solution {
public:
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);
        int n1 = nums1.size();
        int n2 = nums2.size();
        int low = 0, high = n1; // at mininum we can chose 0 elements and at max we can chose n1 elements from first array
        while(low <= high){
            int cut1 = (low + high)/2;
            int cut2 = (n1+n2+1)/2 - cut1;

            int l1 = cut1 == 0 ? INT_MIN : nums1[cut1 -1];
            int l2 = cut2 == 0 ? INT_MIN : nums2[cut2 -1];

            int r1 = cut1 == n1 ? INT_MAX : nums1[cut1];
            int r2 = cut2 == n2 ? INT_MAX : nums2[cut2];

            if(l1 <= r2 && l2 <=r1){
                if(((n1 + n2) & 1) == 0){
                    return (max(l1,l2) + min(r1,r2))/2.0;
                }
                else{
                    return max(l1,l2);
                }
            }
            else if(l1 > r2){
                high = cut1 -1;
            }
            else{
                low = cut1 + 1;
            }

        }
        return 0.0;
    }
    
};
```

## Attempt 5 · 2025-03-23 15:48 IST · Accepted · C++

[submission 1583197806](https://leetcode.com/submissions/detail/1583197806/) · tests 2096/2096 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array for binary search efficiency
        if (nums1.size() > nums2.size()) 
            return findMedianSortedArrays(nums2, nums1);

        int size1 = nums1.size(); // Size of the first array
        int size2 = nums2.size(); // Size of the second array
        int left = 0, right = size1; // Binary search range for partitioning nums1

        while (left <= right) {
            // Partition indices for nums1 and nums2
            int partition1 = (left + right) / 2;
            int partition2 = (size1 + size2 + 1) / 2 - partition1;

            // Left and right elements around the partition in nums1
            int left1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
            int right1 = (partition1 == size1) ? INT_MAX : nums1[partition1];

            // Left and right elements around the partition in nums2
            int left2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
            int right2 = (partition2 == size2) ? INT_MAX : nums2[partition2];

            // Check if the partitions are valid
            if (left1 <= right2 && left2 <= right1) {
                // If total number of elements is even
                if ((size1 + size2) % 2 == 0) {
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                } 
                // If total number of elements is odd
                else {
                    return max(left1, left2);
                }
            } 
            // If left1 is greater than right2, move the partition in nums1 to the left
            else if (left1 > right2) {
                right = partition1 - 1;
            } 
            else {
                left = partition1 + 1;
            }
        }

        // If no valid partition is found (should not happen for valid inputs)
        return 0.0;
    }
};
```
