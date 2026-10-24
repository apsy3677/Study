# 849. Maximize Distance to Closest Person

[Problem](https://leetcode.com/problems/maximize-distance-to-closest-person/) · Medium · Arrays, Hashing & Sorting → Gap scan

LeetCode tags: array

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-23 13:44 IST · Accepted · C++

[submission 955655556](https://leetcode.com/submissions/detail/955655556/) · tests 81/81 · runtime 21 ms (beats 5.9%)

```cpp
class Solution {
public:
    void print(vector<int> & arr){
        for(auto x : arr) cout<<x<<" "; cout<<endl;
    }
    int maxDistToClosest(vector<int>& seats) {
        vector<int> seated, vacant;
        int n = seats.size();
        for(int i=0;i<n;i++){
            if(seats[i]){
                seated.push_back(i);
            }
            else{
                vacant.push_back(i);
            }
        }
        // cout<<seated.size()<<" "<<vacant.size()<<" --- ";
        // print(seated); print(vacant);
        int low = 0, high = vacant.size();
        int ans = 0;
        for(auto seat : vacant){
            int upper = upper_bound(seated.begin(), seated.end(), seat) - seated.begin();
            int lower_, upper_ =0;
            upper_ = upper == seated.size() ? 1e9 : abs(seated[upper]-seat);
            upper--;
            // cout<<seat<<" :: "<< upper+1<<"|"<<upper<<" ||| ";
            lower_ = upper <0 ? 1e9 : abs( seated[upper]-seat);
            ans = max(ans, min(lower_, upper_));
            // cout<<upper_<<" "<<lower_<<" :: ans "<<ans<<endl;

        }
        return ans;
    }
};
```

## Attempt 2 · 2023-05-23 13:46 IST · Accepted · C++

[submission 955656576](https://leetcode.com/submissions/detail/955656576/) · tests 81/81 · runtime 11 ms (beats 6.5%)

```cpp
class Solution {
public:
    void print(vector<int> & arr){
        for(auto x : arr) cout<<x<<" "; cout<<endl;
    }
    int maxDistToClosest(vector<int>& seats) {
        vector<int> seated, vacant;
        int n = seats.size();
        for(int i=0;i<n;i++){
            if(seats[i]){
                seated.push_back(i);
            }
            else{
                vacant.push_back(i);
            }
        }
        int low = 0, high = vacant.size();
        int ans = 0;
        for(auto seat : vacant){
            int upper = upper_bound(seated.begin(), seated.end(), seat) - seated.begin();
            int lower_, upper_ = 0;
            upper_ = upper == seated.size() ? 1e9 : abs(seated[upper]-seat);
            upper--;
            lower_ = upper <0 ? 1e9 : abs( seated[upper]-seat);
            ans = max(ans, min(lower_, upper_));

        }
        return ans;
    }
};
```
