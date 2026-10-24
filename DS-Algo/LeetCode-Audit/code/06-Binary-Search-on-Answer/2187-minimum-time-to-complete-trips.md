# 2187. Minimum Time to Complete Trips

[Problem](https://leetcode.com/problems/minimum-time-to-complete-trips/) · Medium · Binary Search on Answer → Minimise time

LeetCode tags: array, binary-search

Attempts since Mar 2023: 8 · accepted: 1 · failed before first AC: 5

## Attempt 1 · 2023-03-16 10:04 IST · Wrong Answer · C++

[submission 916049625](https://leetcode.com/submissions/detail/916049625/) · tests 86/124

Failing input:

```text
[35526,68271,53295,85312,98439,20401,12567,75537,13042,3015,17945,51706,8379,9020,68149,90591,69251,9417,78418,35804,36630,93100,14223,27099,65124,38701,93629,82300,78404,72046,35760,11057,60001,55960,96428,49527,87398,89804,45956,46031,48904,35592,66810,2777,75831,753,82438,19950,57812,24402,51134,20588,25909,80046,36073,71308,94062,89630,18090,93549,23207,66416,54285,76663,66441,79464,67201,9357 ... [16486 more chars]
```

Expected:

```text
34766088
```

Your output:

```text
867618159880
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totTrips) {
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.back();
        long long ans = INT_MAX;
        while(low <= high){
            long long mid = low + (high - low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid-1;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-16 10:08 IST · Wrong Answer · C++

[submission 916051318](https://leetcode.com/submissions/detail/916051318/) · tests 90/124

Failing input:

```text
[35526,68271,53295,85312,98439,20401,12567,75537,13042,3015,17945,51706,8379,9020,68149,90591,69251,9417,78418,35804,36630,93100,14223,27099,65124,38701,93629,82300,78404,72046,35760,11057,60001,55960,96428,49527,87398,89804,45956,46031,48904,35592,66810,2777,75831,753,82438,19950,57812,24402,51134,20588,25909,80046,36073,71308,94062,89630,18090,93549,23207,66416,54285,76663,66441,79464,67201,9357 ... [16486 more chars]
```

Expected:

```text
34766088
```

Your output:

```text
867618159880
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totTrips) {
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.back();
        long long ans = high;
        while(low < high){
            long long mid = low + (high - low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 3 · 2023-03-16 10:10 IST · Wrong Answer · C++

[submission 916051943](https://leetcode.com/submissions/detail/916051943/) · tests 90/124

Failing input:

```text
[35526,68271,53295,85312,98439,20401,12567,75537,13042,3015,17945,51706,8379,9020,68149,90591,69251,9417,78418,35804,36630,93100,14223,27099,65124,38701,93629,82300,78404,72046,35760,11057,60001,55960,96428,49527,87398,89804,45956,46031,48904,35592,66810,2777,75831,753,82438,19950,57812,24402,51134,20588,25909,80046,36073,71308,94062,89630,18090,93549,23207,66416,54285,76663,66441,79464,67201,9357 ... [16486 more chars]
```

Expected:

```text
34766088
```

Your output:

```text
867618159880
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totTrips) {
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.back();
        long long ans = high;
        while(low <= high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid-1;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 4 · 2023-03-16 10:13 IST · Wrong Answer · C++

[submission 916053208](https://leetcode.com/submissions/detail/916053208/) · tests 90/124

Failing input:

```text
[35526,68271,53295,85312,98439,20401,12567,75537,13042,3015,17945,51706,8379,9020,68149,90591,69251,9417,78418,35804,36630,93100,14223,27099,65124,38701,93629,82300,78404,72046,35760,11057,60001,55960,96428,49527,87398,89804,45956,46031,48904,35592,66810,2777,75831,753,82438,19950,57812,24402,51134,20588,25909,80046,36073,71308,94062,89630,18090,93549,23207,66416,54285,76663,66441,79464,67201,9357 ... [16486 more chars]
```

Expected:

```text
34766088
```

Your output:

```text
867618159880
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totTrips) {
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.back();
        long long ans = high;
        while(low <= high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid;
                if(low ==high) break;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 5 · 2023-03-16 10:14 IST · Wrong Answer · C++

[submission 916053597](https://leetcode.com/submissions/detail/916053597/) · tests 120/124

Failing input:

```text
[88690,69213]
90165
```

Expected:

```text
3505206180
```

Your output:

```text
6240590145
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totTrips) {
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.front();
        long long ans = high;
        while(low <= high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid;
                if(low ==high) break;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 6 · 2023-03-16 10:17 IST · Accepted · C++

[submission 916054851](https://leetcode.com/submissions/detail/916054851/) · tests 124/124 · runtime 416 ms (beats 5.2%)

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long maxTime = 0, minTime = 0, ansTime = 0, totTrips = totalTrips;
        int minVal = time[0];
        for(int i = 1; i < time.size(); i++)
            minVal = min(minVal, time[i]);
        maxTime = (long long) minVal * totalTrips;
        ansTime = maxTime;
        while (minTime <= maxTime){
            long long medTime = (minTime + maxTime)/2;
            long long totalTripsPossible = 0;
            for(int i = 0; i < time.size(); i++){
                if(time[i] == 0)
                    continue;
                totalTripsPossible += medTime/time[i];
            }
            if(totalTripsPossible >= totalTrips){
                //it is possible that with less time also we can make totalTrips
                ansTime = medTime;
                maxTime = medTime - 1;
            }else{
                minTime = medTime + 1;
            }
        }
        return ansTime;
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.front();
        long long ans = high;
        while(low < high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid;
                if(low == high) break;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 7 · 2023-03-16 10:18 IST · Wrong Answer · C++

[submission 916055160](https://leetcode.com/submissions/detail/916055160/) · tests 120/124

Failing input:

```text
[88690,69213]
90165
```

Expected:

```text
3505206180
```

Your output:

```text
6240590145
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long maxTime = 0, minTime = 0, ansTime = 0, totTrips = totalTrips;
        // int minVal = time[0];
        // for(int i = 1; i < time.size(); i++)
        //     minVal = min(minVal, time[i]);
        // maxTime = (long long) minVal * totalTrips;
        // ansTime = maxTime;
        // while (minTime <= maxTime){
        //     long long medTime = (minTime + maxTime)/2;
        //     long long totalTripsPossible = 0;
        //     for(int i = 0; i < time.size(); i++){
        //         if(time[i] == 0)
        //             continue;
        //         totalTripsPossible += medTime/time[i];
        //     }
        //     if(totalTripsPossible >= totalTrips){
        //         //it is possible that with less time also we can make totalTrips
        //         ansTime = medTime;
        //         maxTime = medTime - 1;
        //     }else{
        //         minTime = medTime + 1;
        //     }
        // }
        // return ansTime;
        long long low =1, high = totTrips;

        sort(time.begin(), time.end());
        high = high* time.front();
        long long ans = high;
        while(low < high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid;
                if(low == high) break;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```

## Attempt 8 · 2023-03-16 10:26 IST · Wrong Answer · C++

[submission 916058795](https://leetcode.com/submissions/detail/916058795/) · tests 120/124

Failing input:

```text
[88690,69213]
90165
```

Expected:

```text
3505206180
```

Your output:

```text
6240590145
```

```cpp
class Solution {
public:
    long long tripsInTime(int t, vector<int> &arr){

        long long ans =0;

        for(auto x: arr){
            if(x == 0) continue;
            ans += t/x;
        }
        return ans;
    }
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long maxTime = 0, minTime = 0, ansTime = 0, totTrips = totalTrips;
        // int minVal = time[0];
        // for(int i = 1; i < time.size(); i++)
        //     minVal = min(minVal, time[i]);
        // maxTime = (long long) minVal * totalTrips;
        // ansTime = maxTime;
        // while (minTime <= maxTime){
        //     long long medTime = (minTime + maxTime)/2;
        //     long long totalTripsPossible = 0;
        //     for(int i = 0; i < time.size(); i++){
        //         if(time[i] == 0)
        //             continue;
        //         totalTripsPossible += medTime/time[i];
        //     }
        //     if(totalTripsPossible >= totalTrips){
        //         //it is possible that with less time also we can make totalTrips
        //         ansTime = medTime;
        //         maxTime = medTime - 1;
        //     }else{
        //         minTime = medTime + 1;
        //     }
        // }
        // return ansTime;
        long long low =1, high;

        sort(time.begin(), time.end());
        high = totTrips* time.front();
        long long ans = high;
        while(low <= high){
            long long mid = (high + low)/2;

            long long trips = tripsInTime(mid, time);

            if(trips >= totTrips){
                ans = mid;
                high = mid -1;
                // if(low == high) break;
            }
            else{
               low = mid+1; 
            }
        }
        return ans;
    }
};
```
