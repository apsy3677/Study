# 373. Find K Pairs with Smallest Sums

[Problem](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/) · Medium · Heap / Top-K → K-way heap

LeetCode tags: array, heap-priority-queue

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2024-03-25 18:07 IST · Wrong Answer · C++

[submission 1213449195](https://leetcode.com/submissions/detail/1213449195/) · tests 6/30

Failing input:

```text
[1,2,4,5,6]
[3,5,7,9]
20
```

Expected:

```text
[[1,3],[2,3],[1,5],[2,5],[4,3],[1,7],[5,3],[2,7],[4,5],[6,3],[1,9],[5,5],[2,9],[4,7],[6,5],[5,7],[4,9],[6,7],[5,9],[6,9]]
```

Your output:

```text
[[1,3],[2,3],[1,5],[1,5],[2,5],[2,5],[4,3],[1,5],[2,5],[1,7],[1,7],[1,7],[1,7],[1,7],[1,7],[5,3],[1,5],[2,5],[1,7],[1,7]]
```

```cpp
class Solution {
    typedef vector<int> node;
public:
    vector<vector<int>> kSmallestPairs(vector<int>& arr1, vector<int>& arr2, int k) {
        priority_queue<node, vector<node>, greater<node> > pq;
        vector<vector<int>> ans;
        int idx=0;
        for(auto num : arr1){
            pq.push({num + arr2[0], idx++, 0});
        }
        while(!pq.empty() && k>0){
            if (pq.empty()) break; // not required coz k <= n1*n2
            auto arr = pq.top(); pq.pop();
            ans.push_back({arr1[arr[1]],  arr2[arr[2]]});
            k--;
            if(arr[2] + 1 < arr2.size()){
                for(int i=0;i<arr1.size();i++){
                    pq.push({arr1[i] + arr2[arr[2]+1], i, arr[2]+1});
                }
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2024-03-25 18:15 IST · Accepted · C++

[submission 1213454011](https://leetcode.com/submissions/detail/1213454011/) · tests 30/30 · runtime 342 ms (beats 5.0%)

```cpp
class Solution {
    typedef vector<int> node;
public:
    vector<vector<int>> kSmallestPairs(vector<int>& arr1, vector<int>& arr2, int k) {
        priority_queue<node, vector<node>, greater<node> > pq;
        vector<vector<int>> ans;
        int idx=0;
        for(auto num : arr1){
            pq.push({num + arr2[0], idx++, 0});
        }
        while(!pq.empty() && k>0){
            if (pq.empty()) break; // not required coz k <= n1*n2
            auto arr = pq.top(); pq.pop();
            ans.push_back({arr1[arr[1]],  arr2[arr[2]]});
            k--;
            if(arr[2] + 1 < arr2.size()){
                pq.push({arr1[arr[1]] + arr2[arr[2]+1], arr[1], arr[2]+1});
            }
        }
        return ans;
    }
};
```
