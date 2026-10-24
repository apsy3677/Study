# 605. Can Place Flowers

[Problem](https://leetcode.com/problems/can-place-flowers/) · Easy · Greedy → Greedy placement

LeetCode tags: array, greedy

Attempts since Mar 2023: 3 · accepted: 1 · failed before first AC: 2

## Attempt 1 · 2023-08-18 22:50 IST · Time Limit Exceeded · C++

[submission 1025052295](https://leetcode.com/submissions/detail/1025052295/) · tests 84/127

Failing input:

```text
[1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1 ... [1109 more chars]
```

Expected:

```text
false
```

```cpp
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int maxFlowers = maxFlowersPlacement(flowerbed, 0);
        return maxFlowers>=n;
    }

    int maxFlowersPlacement(vector<int>& flowerbed, int index) {
        int n = flowerbed.size(), include, exclude;
        if (n==1) {
            return flowerbed[0] == 0? 1:0;
        } else if(index == 0 && n>1) {
            if(flowerbed[index] == 0 && flowerbed[index+1] == 0) {
                flowerbed[index] = 1;
                include = 1 + maxFlowersPlacement(flowerbed, index+1);
                flowerbed[index] = 0;
            }
            exclude = maxFlowersPlacement(flowerbed, index+1);
        } else if(index == n-1 && n>1) {
            if(flowerbed[index] == 0 && flowerbed[index-1] == 0) {
                return 1;
            }
            return 0;
        } else {
            if(flowerbed[index] == 0 && flowerbed[index+1] == 0 && flowerbed[index-1] == 0) {
                flowerbed[index] = 1;
                include = 1 + maxFlowersPlacement(flowerbed, index+1);
                flowerbed[index] = 0;
            }
            exclude = maxFlowersPlacement(flowerbed, index+1);
        }
        return include>exclude?include:exclude;
    }
};
```

## Attempt 2 · 2023-08-18 23:15 IST · Wrong Answer · C++

[submission 1025074175](https://leetcode.com/submissions/detail/1025074175/) · tests 102/127

Failing input:

```text
[1,0,0,0,0,0,1]
2
```

Expected:

```text
true
```

Your output:

```text
false
```

```cpp
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int include = flowerbed[0]^1;
        int exclude = 0;
        int length = flowerbed.size();
        int temp;

        for (int i = 1; i<length; i++) {
            temp = exclude;
            exclude = maxValue(include, exclude);
            include = (flowerbed[i]^1) + temp;
        }

        return maxValue(include, exclude) >= n;
    }

    bool maxValue(int a, int b) {
        return a>b?a:b;
    }
};
```

## Attempt 3 · 2023-08-18 23:51 IST · Accepted · C++

[submission 1025106754](https://leetcode.com/submissions/detail/1025106754/) · tests 127/127 · runtime 13 ms (beats 2.9%)

```cpp
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count =0;
        int length = flowerbed.size();
        for (int i = 0; i<length; i++) {
            int leftPlace = i==0 || flowerbed[i-1] == 0;
            int rightPlace = i==length-1 || flowerbed[i+1] == 0;

            if (leftPlace && rightPlace && flowerbed[i] == 0) {
                flowerbed[i] = 1;
                count++;
            }
        }

        return count >= n;
    }
};
```
