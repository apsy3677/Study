# 2463. Minimum Total Distance Traveled

[Problem](https://leetcode.com/problems/minimum-total-distance-traveled/) · Hard · DP: Partition / Interval (MCM) → Sorted assignment DP

LeetCode tags: array, dynamic-programming, sorting

Attempts since Mar 2023: 4 · accepted: 1 · failed before first AC: 3

## Attempt 1 · 2024-10-31 18:49 IST · Time Limit Exceeded · C++

[submission 1439060005](https://leetcode.com/submissions/detail/1439060005/) · tests 5/40

Failing input:

```text
[9486709,305615257,214323605,282129380,763907021,-662831631,628054452,-132239126,50488558,381544523,-656107497,810414334,421675516,-304916551,571202823,478460906,-972398628,325714139,-86452967,660743346]
[[-755430217,18],[382914340,2],[977509386,4],[94299927,9],[32194684,16],[-371001457,2],[-426296769,13],[-284404215,8],[-421288725,0],[-893030428,2],[291827872,17],[-766616824,8],[-730172656,17],[- ... [87 more chars]
```

Expected:

```text
925405949
```

```cpp
class Solution {
public:

    long long f(int robotIdx, vector<int>robot, vector<vector<int>> &factory, long long dis) {
        long long ans = INT_MAX;
        int robotPos = robot[robotIdx];

        if (robotIdx == robot.size() - 1){
            // fill one robot with min Dis

            for (auto &fac : factory) {
                // chose factory if limit is not reached.
                int facPos = fac[0];
                int limit = fac[1];
                if (limit<=0) continue;
                ans = min(ans, (long long)abs(robotPos - facPos));
            }
            return ans + dis;
        }
        // int dist = 0;
        for (auto &fac : factory) {
            // chose factory if limit is not reached.
            int facPos = fac[0];
            int &limit = fac[1];
            if (limit<=0) continue;

            // call for other robots
            fac[1]--;
            ans = min(ans, f(robotIdx + 1, robot, factory, dis + abs(robotPos - facPos) ) );
            fac[1]++;
        }
        return ans;
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        long long minDis = INT_MAX;
        return f(0, robot, factory, 0);
    }
};
```

## Attempt 2 · 2024-10-31 20:54 IST · Wrong Answer · C++

[submission 1439134519](https://leetcode.com/submissions/detail/1439134519/) · tests 19/40

Failing input:

```text
[79215383,708490359,-779179404,713376652,-368850098,573013032,195489859,121470584,916616893,327266713,950673412,410723622,538863648,170740409,753199490]
[[-284344805,4],[349360740,6],[-360820857,2],[-493544411,13],[-28182860,4],[-117519725,13],[-294274103,9]]
```

Expected:

```text
5121930465
```

Your output:

```text
4052915948
```

```cpp
class Solution {
public:
    // Memoization map to store the minimum distance for specific robot and factory states.
    unordered_map<string, long long> memo;

    // Helper function to generate a unique key for memoization.
    string makeKey(int robotIdx, int factoryIdx, int limit) {
        return to_string(robotIdx) + "," + to_string(factoryIdx) + "," + to_string(limit);
    }
    long long f(int robotIdx, vector<int>robot, vector<vector<int>> &factory) {
        if (robotIdx == robot.size()){
            return 0; // all robots assigned
        }
        long long ans = LLONG_MAX;
        int robotPos = robot[robotIdx];

        // int dist = 0;
        int facIdx = -1;
        for (auto &fac : factory) {
            facIdx++;

            // chose factory if limit is not reached.
            int facPos = fac[0];
            int &limit = fac[1];
            if (limit<=0) continue;

            string key = makeKey(robotIdx, facIdx, limit);

            if(memo.count(key)>0) {
                ans = min(ans, memo[key]);
                continue;
            }

            // call for other robots
            fac[1]--;
            long long dist = abs(robotPos - facPos) + f(robotIdx + 1, robot, factory );
            fac[1]++;

            memo[key] = dist;
            ans = min(ans,  dist);

        }
        return ans;
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sort robots and factories by position to optimize matching
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        return f(0, robot, factory);
    }
};

// #include <vector>
// #include <algorithm>
// #include <cmath>
// #include <climits>
// #include <unordered_map>

// using namespace std;

// class Solution {
// public:
//     // Memoization map to store the minimum distance for specific robot and factory states.
//     unordered_map<string, long long> memo;

//     // Helper function to generate a unique key for memoization.
//     string makeKey(int robotIdx, int factoryIdx, int limit) {
//         return to_string(robotIdx) + "," + to_string(factoryIdx) + "," + to_string(limit);
//     }

//     long long f(int robotIdx, vector<int>& robot, vector<vector<int>>& factory) {
//         if (robotIdx == robot.size()) return 0;  // All robots are assigned
        
//         long long ans = LLONG_MAX;
//         int robotPos = robot[robotIdx];

//         // Go through each factory starting from the first available factory
//         for (int j = 0; j < factory.size(); ++j) {
//             int facPos = factory[j][0];
//             int& limit = factory[j][1];

//             if (limit > 0) {  // Only consider if factory has remaining limit
//                 // Generate key for current robot-factory configuration
//                 string key = makeKey(robotIdx, j, limit);
                
//                 // Check if the result for this state is already memoized
//                 if (memo.count(key) > 0) {
//                     ans = min(ans, memo[key]);
//                     continue;
//                 }

//                 // Use this factory, decrement limit, and calculate distance
//                 limit--;
//                 long long dist = abs(robotPos - facPos) + f(robotIdx + 1, robot, factory);
//                 limit++;  // Restore limit for other calls (backtrack)

//                 // Store the result in memo
//                 memo[key] = dist;

//                 // Update the minimum distance answer
//                 ans = min(ans, dist);
//             }
//         }

//         return ans;
//     }

//     long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
//         // Sort robots and factories by their positions to optimize pairing
//         sort(robot.begin(), robot.end());
//         sort(factory.begin(), factory.end());

//         return f(0, robot, factory);
//     }
// };
```

## Attempt 3 · 2024-10-31 21:05 IST · Time Limit Exceeded · C++

[submission 1439141610](https://leetcode.com/submissions/detail/1439141610/) · tests 5/40

Failing input:

```text
[9486709,305615257,214323605,282129380,763907021,-662831631,628054452,-132239126,50488558,381544523,-656107497,810414334,421675516,-304916551,571202823,478460906,-972398628,325714139,-86452967,660743346]
[[-755430217,18],[382914340,2],[977509386,4],[94299927,9],[32194684,16],[-371001457,2],[-426296769,13],[-284404215,8],[-421288725,0],[-893030428,2],[291827872,17],[-766616824,8],[-730172656,17],[- ... [87 more chars]
```

Expected:

```text
925405949
```

```cpp
// class Solution {
// public:
//     // Memoization map to store the minimum distance for specific robot and factory states.
//     unordered_map<string, long long> memo;

//     // Helper function to generate a unique key for memoization.
//     string makeKey(int robotIdx, vector<vector<int>>& factory) {
//         string key = to_string(robotIdx) + "#";
//         for (const auto& fac : factory) {
//             key += to_string(fac[1]) + ",";  // Include current limit of each factory
//         }
//         return key;
//     }
//     long long f(int robotIdx, vector<int>robot, vector<vector<int>> &factory) {
//         if (robotIdx == robot.size()){
//             return 0; // all robots assigned
//         }
//         long long ans = LLONG_MAX;
//         int robotPos = robot[robotIdx];

//         // int dist = 0;
//         int facIdx = -1;
//         for (auto &fac : factory) {
//             facIdx++;

//             // chose factory if limit is not reached.
//             int facPos = fac[0];
//             int &limit = fac[1];
//             if (limit<=0) continue;

//             string key = makeKey(robotIdx, factory);

//             if(memo.count(key)>0) {
//                 ans = min(ans, memo[key]);
//                 continue;
//             }

//             // call for other robots
//             fac[1]--;
//             long long dist = abs(robotPos - facPos) + f(robotIdx + 1, robot, factory );
//             fac[1]++;

//             memo[key] = dist;
//             ans = min(ans,  dist);

//         }
//         return ans;
//     }

//     long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
//         // Sort robots and factories by position to optimize matching
//         sort(robot.begin(), robot.end());
//         sort(factory.begin(), factory.end());
//         return f(0, robot, factory);
//     }
// };

class Solution {
public:
    unordered_map<string, long long> memo;

    // Helper function to generate a unique key for memoization by encoding factory limits directly.
    string makeKey(int robotIdx, const vector<vector<int>>& factory) {
        string key = to_string(robotIdx) + "#";
        for (const auto& fac : factory) {
            key += to_string(fac[1]) + ",";  // Include current limit of each factory
        }
        return key;
    }

    long long f(int robotIdx, vector<int>& robot, vector<vector<int>>& factory) {
        if (robotIdx == robot.size()) {
            return 0;  // All robots are assigned
        }

        long long ans = LLONG_MAX;
        int robotPos = robot[robotIdx];

        // Generate a unique key based on the current robot index and factory limits
        string key = makeKey(robotIdx, factory);
        if (memo.count(key) > 0) {
            return memo[key];
        }

        // Try assigning the current robot to each factory
        for (int j = 0; j < factory.size(); ++j) {
            int facPos = factory[j][0];
            int& limit = factory[j][1];

            if (limit <= 0) continue;  // Skip if factory limit is reached

            // Temporarily assign the robot to this factory
            limit--;
            long long dist = abs(robotPos - facPos) + f(robotIdx + 1, robot, factory);
            limit++;  // Restore factory's limit after backtracking

            // Update minimum distance answer
            ans = min(ans, dist);
        }

        // Memoize the result for the current state
        memo[key] = ans;
        return ans;
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sort robots and factories by position to optimize pairing
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        return f(0, robot, factory);
    }
};
```

## Attempt 4 · 2024-10-31 21:13 IST · Accepted · C++

[submission 1439146279](https://leetcode.com/submissions/detail/1439146279/) · tests 40/40 · runtime 32 ms (beats 45.8%)

```cpp
// class Solution {
// public:
//     // Memoization map to store the minimum distance for specific robot and factory states.
//     unordered_map<string, long long> memo;

//     // Helper function to generate a unique key for memoization.
//     string makeKey(int robotIdx, vector<vector<int>>& factory) {
//         string key = to_string(robotIdx) + "#";
//         for (const auto& fac : factory) {
//             key += to_string(fac[1]) + ",";  // Include current limit of each factory
//         }
//         return key;
//     }
//     long long f(int robotIdx, vector<int>robot, vector<vector<int>> &factory) {
//         if (robotIdx == robot.size()){
//             return 0; // all robots assigned
//         }
//         long long ans = LLONG_MAX;
//         int robotPos = robot[robotIdx];

//         // int dist = 0;
//         int facIdx = -1;
//         for (auto &fac : factory) {
//             facIdx++;

//             // chose factory if limit is not reached.
//             int facPos = fac[0];
//             int &limit = fac[1];
//             if (limit<=0) continue;

//             string key = makeKey(robotIdx, factory);

//             if(memo.count(key)>0) {
//                 ans = min(ans, memo[key]);
//                 continue;
//             }

//             // call for other robots
//             fac[1]--;
//             long long dist = abs(robotPos - facPos) + f(robotIdx + 1, robot, factory );
//             fac[1]++;

//             memo[key] = dist;
//             ans = min(ans,  dist);

//         }
//         return ans;
//     }

//     long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
//         // Sort robots and factories by position to optimize matching
//         sort(robot.begin(), robot.end());
//         sort(factory.begin(), factory.end());
//         return f(0, robot, factory);
//     }
// };

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int R = robot.size();
        int F = factory.size();

        // Sort both robots and factories by position
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Initialize DP table with large values
        vector<vector<long long>> dp(R + 1, vector<long long>(F + 1, LLONG_MAX));
        dp[0][0] = 0;  // No cost for assigning 0 robots to 0 factories

        for (int j = 1; j <= F; ++j) {
            for (int i = 0; i <= R; ++i) {
                dp[i][j] = dp[i][j - 1];  // Option to skip this factory

                // Consider using the `j-1` factory for `k` robots
                long long totalDistance = 0;
                for (int k = 1; k <= min(factory[j - 1][1], i); ++k) {
                    totalDistance += abs(robot[i - k] - factory[j - 1][0]);
                    if (dp[i - k][j - 1] != LLONG_MAX) {
                        dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + totalDistance);
                    }
                }
            }
        }
        return dp[R][F];
    }
};
```
