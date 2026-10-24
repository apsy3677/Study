# 381. Insert Delete GetRandom O(1) - Duplicates allowed

[Problem](https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/) · Hard · Design → Array + index map

LeetCode tags: array, hash-table, math, design, randomized

Attempts since Mar 2023: 2 · accepted: 0 · failed before first AC: 2

## Attempt 1 · 2023-04-26 16:38 IST · Wrong Answer · C++

[submission 940016332](https://leetcode.com/submissions/detail/940016332/) · tests 20/32

Failing input:

```text
["RandomizedCollection","insert","insert","insert","insert","insert","remove","remove","remove","remove"]
[[],[4],[3],[4],[2],[4],[4],[3],[4],[4]]
```

Expected:

```text
[null,true,true,false,true,false,true,true,true,true]
```

Your output:

```text
[null,true,true,false,true,false,true,true,false,false]
```

```cpp
class RandomizedCollection {
    multiset<int> set;
    unordered_map<int, int> map;
public:
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        set.insert(val);
        if(map.count(val) == 0){
            map[val]++;
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if(map.count(val) != 0){
            set.erase(set.find(val));
            map[val]--;
            if(map[val] == 0){
                map.erase(val);
            }
            return true;
        }
        return false;
    }
    
    int getRandom() {
        // Returns a random element from the current multiset of elements. The probability of each element being returned is linearly related to the number of the same values the multiset contains.
        int ans  = 0;
        int n = set.size();
        int random = rand()%n;
        auto it = set.begin();
        std::advance(it,random);
        return *it;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```

## Attempt 2 · 2023-04-26 16:45 IST · Time Limit Exceeded · C++

[submission 940018807](https://leetcode.com/submissions/detail/940018807/) · tests 27/32

Failing input:

```text
["RandomizedCollection","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert","insert ... [154267 more chars]
```

Expected:

```text
[null,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true ... [48868 more chars]
```

```cpp
class RandomizedCollection {
    multiset<int> set;
    unordered_map<int, int> map;
public:
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        set.insert(val);
        if(map.count(val) == 0){
            map[val]++;
            return true;
        }
        map[val]++;
        return false;
    }
    
    bool remove(int val) {
        cout<<" Remove "<<val<<"||";
        cout<<" Set :: ";
        for(auto it : set) cout<<it<<" ";
        cout<<" Map :: ";
        for(auto [it,cnt] : map) cout<<it<<"|"<<cnt<<" ";
        if(map.find(val) != map.end()){
            set.erase(set.find(val));
            map[val]--;
            if(map[val] == 0){
                map.erase(val);
            }
            return true;
        }
        return false;
    }
    
    int getRandom() {
        // Returns a random element from the current multiset of elements. The probability of each element being returned is linearly related to the number of the same values the multiset contains.
        int ans  = 0;
        int n = set.size();
        int random = rand()%n;
        auto it = set.begin();
        std::advance(it,random);
        return *it;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
```
