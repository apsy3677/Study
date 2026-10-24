# 528. Random Pick with Weight

[Problem](https://leetcode.com/problems/random-pick-with-weight/) · Medium · Prefix Sum & Difference Array → Prefix sum + binary search

LeetCode tags: array, math, binary-search, prefix-sum, randomized

Attempts since Mar 2023: 6 · accepted: 4 · failed before first AC: 1

## Attempt 1 · 2023-03-24 18:55 IST · Wrong Answer · C++

[submission 921302854](https://leetcode.com/submissions/detail/921302854/) · tests 19/57

Failing input:

```text
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pic ... [149627 more chars]
```

Expected:

```text
[null,1,2,3,3,1,3,3,1,0,1,1,1,3,3,1,1,1,1,3,1,1,1,0,3,0,3,1,1,0,3,1,2,1,1,1,1,1,1,1,0,1,1,3,1,3,3,3,1,1,0,1,3,1,1,3,3,3,1,3,3,3,0,1,1,1,3,1,0,1,3,2,1,1,1,1,1,1,1,3,1,0,3,3,1,2,1,1,0,1,1,1,1,1,1,1,3,0,1,3,0,3,3,0,3,3,1,0,3,3,1,1,1,1,1,0,1,1,1,1,0,3,1,3,1,1,3,0,3,0,1,1,1,1,0,3,1,1,3,3,0,2,2,1,1,1,3,1,1,3,3,3,1,3,3,1,0,3,2,1,3,2,1,1,1,2,1,0,0,1,1,1,1,3,1,3,3,3,1,1,3,1,3,3,1,1,1,1,1,1,1,0,1,3,3,3,1,1, ... [19606 more chars]
```

Your output:

```text
[null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [19606 more chars]
```

```cpp
class Solution {
    vector<int> prefixSum;
    int totalSum;
public:
    Solution(vector<int>& w) {
        int prev =0;
         for(int i=0;i<w.size();i++){
             prefixSum.push_back(prev+w[i]);
             prev = w[i];
             totalSum += w[i];
         }
    }
    
    int pickIndex() {
        float randNum = (float) rand()/ RAND_MAX;

        float target = randNum*totalSum;

        return lower_bound(prefixSum.begin(), prefixSum.end(), target) - prefixSum.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```

## Attempt 2 · 2023-03-24 18:59 IST · Accepted · C++

[submission 921304705](https://leetcode.com/submissions/detail/921304705/) · tests 57/57 · runtime 89 ms (beats 12.2%)

```cpp
class Solution {
    vector<int> prefixSum;
    int totalSum;
public:
    Solution(vector<int>& w) {
        int prev =0;
        totalSum =0;
         for(int i=0;i<w.size();i++){
             prefixSum.push_back(prev + w[i]);
             prev += w[i];
             totalSum += w[i]; 
         }
          
    }
    
    int pickIndex() {
        float randNum = (float) rand()/ RAND_MAX;

        float target = randNum*totalSum;

        return lower_bound(prefixSum.begin(), prefixSum.end(), target) - prefixSum.begin();
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```

## Attempt 3 · 2023-11-21 00:40 IST · Accepted · Python3

[submission 1102932083](https://leetcode.com/submissions/detail/1102932083/) · tests 57/57 · runtime 164 ms (beats 19.9%)

```python
class Solution:

    def __init__(self, w: List[int]):
        self.prefix_sums = []
        prefix_sum = 0
        for weight in w:
            prefix_sum += weight
            self.prefix_sums.append(prefix_sum)
        self.total_sum = prefix_sum
        print(self.prefix_sums)

    def pickIndex(self) -> int:
        target = random.random() * self.total_sum
        
        l, r = 0, len(self.prefix_sums) - 1
        while l < r:
            mid = (l+r)//2
            if self.prefix_sums[mid] < target:
                l = mid +1
            else:
                r = mid
        return l


# Your Solution object will be instantiated and called as such:
# obj = Solution(w)
# param_1 = obj.pickIndex()
```

## Attempt 4 · 2024-01-02 03:09 IST · Accepted · Python3

[submission 1134082231](https://leetcode.com/submissions/detail/1134082231/) · tests 57/57 · runtime 136 ms (beats 20.9%)

```python
class Solution1:

    def __init__(self, w: List[int]):

        '''
        cumulative sum maps the weights to range
        and ranges corresponds to the prob distribution
        take example of weights 1 4 3
        indexes as per weights 0 1 1 1 1 2 2 2
        if you map it to weights 1 5 8 
        if you change it to ranges -> [0] [1 2 3 4] [5,6,7]
        '''
        self.prefix_sums = []
        prefix_sum = 0
        for weight in w:
            prefix_sum += weight
            self.prefix_sums.append(prefix_sum)
        self.total_sum = prefix_sum
        print(self.prefix_sums)

    def pickIndex(self) -> int:
        # random.random() gives a fraction in range of 0 inclusive to 1 exclusive
        target = random.random() * self.total_sum
        
        # either do a linear search in O(n) or do a Log(n) search since prefixsums are always sorted in non decreasing order
        # find just number just greater than target
        # target = 5 and lets say seq is [3,6] 
        l, r = 0, len(self.prefix_sums) - 1
        while l < r:
            mid = (l+r)//2
            if self.prefix_sums[mid] < target:
                l = mid +1
            else:
                r = mid
        return l


class Solution:

    def __init__(self, w: List[int]):

        '''
        cumulative sum maps the weights to range
        and ranges corresponds to the prob distribution
        take example of weights 1 4 3
        indexes as per weights 0 1 1 1 1 2 2 2

        if you map it to weights 1 5 8 
        if you change it to ranges -> [0] [1 2 3 4] [5,6,7]
        '''
        prefixSum = 0
        self.prefixSums = []
        for weight in w:
            prefixSum += weight
            self.prefixSums.append(prefixSum)
        self.total_weight = prefixSum


    def pickIndex(self) -> int:
        target = random.random() * self.total_weight

        # linear search
        # for i, prefixSum in enumerate(self.prefixSums):
        #     if target < prefixSum:
        #         return i

        # binary search
        l = 0
        r = len(self.prefixSums)

        while l < r:
            mid = (l+r)//2

            if target <= self.prefixSums[mid] :
                r = mid 
            else:
                l = mid +1
        return l

       

# Your Solution object will be instantiated and called as such:
# obj = Solution(w)
# param_1 = obj.pickIndex()
```

## Attempt 5 · 2025-06-14 11:27 IST · Wrong Answer · C++

[submission 1663543314](https://leetcode.com/submissions/detail/1663543314/) · tests 19/57

Failing input:

```text
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex","pic ... [149627 more chars]
```

Expected:

```text
[null,1,2,3,3,1,3,3,1,0,1,1,1,3,3,1,1,1,1,3,1,1,1,0,3,0,3,1,1,0,3,1,2,1,1,1,1,1,1,1,0,1,1,3,1,3,3,3,1,1,0,1,3,1,1,3,3,3,1,3,3,3,0,1,1,1,3,1,0,1,3,2,1,1,1,1,1,1,1,3,1,0,3,3,1,2,1,1,0,1,1,1,1,1,1,1,3,0,1,3,0,3,3,0,3,3,1,0,3,3,1,1,1,1,1,0,1,1,1,1,0,3,1,3,1,1,3,0,3,0,1,1,1,1,0,3,1,1,3,3,0,2,2,1,1,1,3,1,1,3,3,3,1,3,3,1,0,3,2,1,3,2,1,1,1,2,1,0,0,1,1,1,1,3,1,3,3,3,1,1,3,1,3,3,1,1,1,1,1,1,1,0,1,3,3,3,1,1, ... [19606 more chars]
```

Your output:

```text
[null,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, ... [19606 more chars]
```

```cpp
#include <bits/stdc++.h>
class Solution {
    vector<int> pre;
    int sum = 0;
public:
    Solution(vector<int>& w) {
        int prev = 0;
        for(auto &weight : w) {
            pre.push_back(prev + weight);
            prev += weight;
        }
        sum = prev;
    }
    
    int pickIndex() {
        // generate a random number 
        srand(time(0));
        int rand = std::rand()%sum;
        int high = upper_bound(pre.begin(), pre.end(), rand) - pre.begin();

        if (high == 0) {
            return 0;
        }
        high--;
        return high;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```

## Attempt 6 · 2025-06-14 11:38 IST · Accepted · C++

[submission 1663551792](https://leetcode.com/submissions/detail/1663551792/) · tests 57/57 · runtime 21 ms (beats 40.2%)

```cpp
#include <bits/stdc++.h>
class Solution {
    vector<int> pre;
    int sum = 0;
public:
    Solution(vector<int>& w) {
        int prev = 0;
        for(auto &weight : w) {
            pre.push_back(prev + weight);
            prev += weight;
        }
        sum = prev;
        srand(time(0));
    }
    
    int pickIndex() {
        // generate a random number 
        int rand = std::rand()%sum;
        int high = upper_bound(pre.begin(), pre.end(), rand) - pre.begin();

        return high;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
```
