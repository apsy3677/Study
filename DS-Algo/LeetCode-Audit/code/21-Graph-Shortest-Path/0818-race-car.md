# 818. Race Car

[Problem](https://leetcode.com/problems/race-car/) · Hard · Graph: Shortest Path → BFS over states

LeetCode tags: dynamic-programming, heuristic-search, a-search

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-24 00:58 IST · Accepted · C++

[submission 920921933](https://leetcode.com/submissions/detail/920921933/) · tests 55/55 · runtime 15 ms (beats 45.6%)

```cpp
class Solution {
public:
    int bfs(int pos, int speed, int target){
        if(pos == target){
            return 0;
        }
        
        // use A
        return min(bfs(pos+speed, speed*2, target), 
            bfs(pos, speed>0 ? -1: 1, target)) +1;
    }
    int racecar(int target) {
        // return bfs(0, 1, target);
        queue<pair<int,pair<int,int>>>q;
        q.push({0,{0,1}});
        set<pair<int,int>>vis;
        // vis.insert({0,0});
        while(!q.empty())
        {
        int mov=q.front().first;
        int pos=q.front().second.first;
        long long int speed=q.front().second.second;
        q.pop();
        if(pos==target)
            return mov;
        if(vis.find({pos,speed})!=vis.end())
            continue;
        else{
            vis.insert({pos,speed});
            q.push({mov+1,{pos+speed,speed*2}});

                if( pos+speed>target && speed>0 || pos+speed<target && speed<0)
                {
                    if(speed>0)
                    speed=-1;
                    else speed=1;
                    q.push({mov+1,{pos,speed}});
                }
            }
        }
    return -1;
    }
};
```
