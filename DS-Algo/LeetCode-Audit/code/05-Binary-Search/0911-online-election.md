# 911. Online Election

[Problem](https://leetcode.com/problems/online-election/) · Medium · Binary Search → Precompute + binary search

LeetCode tags: array, hash-table, binary-search, design

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-03-29 20:43 IST · Accepted · C++

[submission 1217404450](https://leetcode.com/submissions/detail/1217404450/) · tests 98/98 · runtime 227 ms (beats 5.2%)

```cpp
class TopVotedCandidate {
    vector<int> times;
    map<int, int> records;   

public:
    TopVotedCandidate(vector<int>& persons, vector<int>& times) {
        int n = persons.size();
        vector<pair<int, int>> timeToPersonVotes;
        this->times = times;
        for(int i=0;i<n;i++) {
            timeToPersonVotes.push_back({times[i], persons[i]});
        }
        sort(timeToPersonVotes.begin(), timeToPersonVotes.end());
        int lead = -1;
        map<int, int> count;  
        for(int i=0;i<n;i++) {
            count[timeToPersonVotes[i].second]++;
            if(count[timeToPersonVotes[i].second] >= count[lead]) {
                lead = timeToPersonVotes[i].second;
            }
            records[timeToPersonVotes[i].first] = lead;;
        } 
    }
    
    int q(int t) {
        return records[*--upper_bound(times.begin(), times.end(), t)];
    }
};

/**
 * Your TopVotedCandidate object will be instantiated and called as such:
 * TopVotedCandidate* obj = new TopVotedCandidate(persons, times);
 * int param_1 = obj->q(t);
 */
```
