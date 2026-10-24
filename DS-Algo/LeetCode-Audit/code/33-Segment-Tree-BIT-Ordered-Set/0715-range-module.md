# 715. Range Module

[Problem](https://leetcode.com/problems/range-module/) · Hard · Segment Tree / BIT / Ordered Set → Interval map

LeetCode tags: design, segment-tree, ordered-set

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 1

## Attempt 1 · 2023-03-19 08:18 IST · Wrong Answer · C++

[submission 917810461](https://leetcode.com/submissions/detail/917810461/) · tests 24/54

Failing input:

```text
["RangeModule","addRange","removeRange","removeRange","addRange","removeRange","addRange","queryRange","queryRange","queryRange"]
[[],[6,8],[7,8],[8,9],[8,9],[1,3],[1,8],[2,4],[2,9],[4,6]]
```

Expected:

```text
[null,null,null,null,null,null,null,true,true,true]
```

Your output:

```text
[null,null,null,null,null,null,null,true,false,true]
```

```cpp
class RangeModule {
public:
    map<int,int> mp;
    RangeModule() {
        
    }
    
    map<int,int>::iterator f_it(int l){
        auto it = mp.lower_bound(l);
        if(it != mp.begin() && prev(it)->second >= l){
            it--;
        }
        return it;
    }
    void addRange(int left, int right) {
        // find the first iter for insertion in range

        auto it = f_it(left);

        // why < and = as both rights are exclusive
        while(it!= mp.end() && it->second <= right){
            left = min(left, it->first);
            right = max(right, it->second);

            mp.erase(it++);
        }

        // add all merged intervals
        mp.insert({left,right});
    }
    
    bool queryRange(int left, int right) {
        // query
        auto it = f_it(left);
        if(it == mp.end())  
            return false;
        
        return it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = f_it(left);

        vector<pair<int,int>> v;

        while(it != mp.end() && it->first < right){

            if(it->first < left){
                v.push_back({it->first, left});
            }
            if(it->second > right){
                v.push_back({right, it->second});
            }
            mp.erase(it++);
        }

        for(auto &p :v){
            mp.insert(p);
        }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
```

## Attempt 2 · 2023-03-19 08:28 IST · Accepted · C++

[submission 917819658](https://leetcode.com/submissions/detail/917819658/) · tests 54/54 · runtime 212 ms (beats 15.6%)

```cpp
// class RangeModule {
// public:
//     map<int,int> mp;
//     RangeModule() {
        
//     }
    
//     map<int,int>::iterator f_it(int l){
//         auto it = mp.lower_bound(l);
//         if(it != mp.begin() && prev(it)->second >= l){
//             it--;
//         }
//         return it;
//     }
//     void addRange(int left, int right) {
//         // find the first iter for insertion in range

//         auto it = f_it(left);

//         // why < and = as both rights are exclusive
//         while(it!= mp.end() && it->second <= right){
//             // left = min(left, it->first);
//             right = max(right, it->second);

//             mp.erase(it++);
//         }

//         // add all merged intervals
//         mp.insert({left,right});
//     }
    
//     bool queryRange(int left, int right) {
//         // query
//         auto it = f_it(left);
//         if(it == mp.end())  
//             return false;
        
//         return it->first <= left && it->second >= right;
//     }
    
//     void removeRange(int left, int right) {
//         auto it = f_it(left);

//         vector<pair<int,int>> v;

//         while(it != mp.end() && it->first < right){

//             if(it->first < left){
//                 v.push_back({it->first, left});
//             }
//             if(it->second > right){
//                 v.push_back({right, it->second});
//             }
//             mp.erase(it++);
//         }

//         for(auto &p :v){
//             mp.insert(p);
//         }
//     }
// };
class RangeModule {
public:
    RangeModule() {
        
    }
    
    inline map<int,int>::iterator first_iter(int left) {
        
        // get first overlaping interval
        auto it = mp.lower_bound(left);
        if (it != mp.begin() && prev(it)-> second >= left){
            --it;
        }
        return it;
    }
    
    void addRange(int left, int right) {
        
        auto it = first_iter(left);
        // remove all overlaping intervals
        // update left  <- leftmost left boundary removed
        //        right <- rightmost right boundary removed
        while(it != mp.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            mp.erase(it++);
        }
        // add back all the intervals
        mp.insert({left, right});
    }
    
    bool queryRange(int left, int right) {
        
        auto it = first_iter(left);
        if (it == mp.end()) return false;
        return it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        
        auto it = first_iter(left);
        // v used to collect possible intervals that has partial overlap with [left, right)
        vector<pair<int,int>> v;
        // remove all overlapping intervals
        while (it != mp.end() && it->first < right) {
            // collect partially overlapped intervals
            // and update its left right borders
            if (it->first < left) {
                v.push_back({it->first, left});
            }
            if (it->second > right) {
                v.push_back({right, it->second});
            }
            mp.erase(it++);
        }
        // insert back partial intervals
        for (auto& p: v) {
            mp.insert(p);
        }
    }
    
    map<int,int> mp; // [beg, end)
};
// /**
//  * Your RangeModule object will be instantiated and called as such:
//  * RangeModule* obj = new RangeModule();
//  * obj->addRange(left,right);
//  * bool param_2 = obj->queryRange(left,right);
//  * obj->removeRange(left,right);
//  */
```

## Attempt 3 · 2023-03-19 08:31 IST · Wrong Answer · C++

[submission 917821896](https://leetcode.com/submissions/detail/917821896/) · tests 26/54

Failing input:

```text
["RangeModule","addRange","addRange","addRange","queryRange","queryRange","queryRange","removeRange","queryRange"]
[[],[10,180],[150,200],[250,500],[50,100],[180,300],[600,1000],[50,150],[50,100]]
```

Expected:

```text
[null,null,null,null,true,false,false,null,false]
```

Your output:

```text
[null,null,null,null,false,false,false,null,false]
```

```cpp
class RangeModule {
public:
    map<int,int> mp;
    RangeModule() {
        
    }
    
    map<int,int>::iterator f_it(int l){
        auto it = mp.lower_bound(l);
        if(it != mp.begin() && prev(it)->second >= l){
            it--;
        }
        return it;
    }
    void addRange(int left, int right) {
        // find the first iter for insertion in range

        auto it = f_it(left);

        // why < and = as both rights are exclusive
        while(it!= mp.end() && it->first <= right){
            // left = min(left, it->first);
            right = max(right, it->second);

            mp.erase(it++);
        }

        // add all merged intervals
        mp.insert({left,right});
    }
    
    bool queryRange(int left, int right) {
        // query
        auto it = f_it(left);
        if(it == mp.end())  
            return false;
        
        return it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = f_it(left);

        vector<pair<int,int>> v;

        while(it != mp.end() && it->first < right){

            if(it->first < left){
                v.push_back({it->first, left});
            }
            if(it->second > right){
                v.push_back({right, it->second});
            }
            mp.erase(it++);
        }

        for(auto &p :v){
            mp.insert(p);
        }
    }
};
// class RangeModule {
// public:
//     RangeModule() {
        
//     }
    
//     inline map<int,int>::iterator first_iter(int left) {
        
//         // get first overlaping interval
//         auto it = mp.lower_bound(left);
//         if (it != mp.begin() && prev(it)-> second >= left){
//             --it;
//         }
//         return it;
//     }
    
//     void addRange(int left, int right) {
        
//         auto it = first_iter(left);
//         // remove all overlaping intervals
//         // update left  <- leftmost left boundary removed
//         //        right <- rightmost right boundary removed
//         while(it != mp.end() && it->first <= right) {
//             left = min(left, it->first);
//             right = max(right, it->second);
//             mp.erase(it++);
//         }
//         // add back all the intervals
//         mp.insert({left, right});
//     }
    
//     bool queryRange(int left, int right) {
        
//         auto it = first_iter(left);
//         if (it == mp.end()) return false;
//         return it->first <= left && it->second >= right;
//     }
    
//     void removeRange(int left, int right) {
        
//         auto it = first_iter(left);
//         // v used to collect possible intervals that has partial overlap with [left, right)
//         vector<pair<int,int>> v;
//         // remove all overlapping intervals
//         while (it != mp.end() && it->first < right) {
//             // collect partially overlapped intervals
//             // and update its left right borders
//             if (it->first < left) {
//                 v.push_back({it->first, left});
//             }
//             if (it->second > right) {
//                 v.push_back({right, it->second});
//             }
//             mp.erase(it++);
//         }
//         // insert back partial intervals
//         for (auto& p: v) {
//             mp.insert(p);
//         }
//     }
    
//     map<int,int> mp; // [beg, end)
// };
// /**
//  * Your RangeModule object will be instantiated and called as such:
//  * RangeModule* obj = new RangeModule();
//  * obj->addRange(left,right);
//  * bool param_2 = obj->queryRange(left,right);
//  * obj->removeRange(left,right);
//  */
```

## Attempt 4 · 2023-03-19 08:31 IST · Accepted · C++

[submission 917822373](https://leetcode.com/submissions/detail/917822373/) · tests 54/54 · runtime 216 ms (beats 15.6%)

```cpp
class RangeModule {
public:
    map<int,int> mp;
    RangeModule() {
        
    }
    
    map<int,int>::iterator f_it(int l){
        auto it = mp.lower_bound(l);
        if(it != mp.begin() && prev(it)->second >= l){
            it--;
        }
        return it;
    }
    void addRange(int left, int right) {
        // find the first iter for insertion in range

        auto it = f_it(left);

        // why < and = as both rights are exclusive
        while(it!= mp.end() && it->first <= right){
            left = min(left, it->first);
            right = max(right, it->second);

            mp.erase(it++);
        }

        // add all merged intervals
        mp.insert({left,right});
    }
    
    bool queryRange(int left, int right) {
        // query
        auto it = f_it(left);
        if(it == mp.end())  
            return false;
        
        return it->first <= left && it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = f_it(left);

        vector<pair<int,int>> v;

        while(it != mp.end() && it->first < right){

            if(it->first < left){
                v.push_back({it->first, left});
            }
            if(it->second > right){
                v.push_back({right, it->second});
            }
            mp.erase(it++);
        }

        for(auto &p :v){
            mp.insert(p);
        }
    }
};
// class RangeModule {
// public:
//     RangeModule() {
        
//     }
    
//     inline map<int,int>::iterator first_iter(int left) {
        
//         // get first overlaping interval
//         auto it = mp.lower_bound(left);
//         if (it != mp.begin() && prev(it)-> second >= left){
//             --it;
//         }
//         return it;
//     }
    
//     void addRange(int left, int right) {
        
//         auto it = first_iter(left);
//         // remove all overlaping intervals
//         // update left  <- leftmost left boundary removed
//         //        right <- rightmost right boundary removed
//         while(it != mp.end() && it->first <= right) {
//             left = min(left, it->first);
//             right = max(right, it->second);
//             mp.erase(it++);
//         }
//         // add back all the intervals
//         mp.insert({left, right});
//     }
    
//     bool queryRange(int left, int right) {
        
//         auto it = first_iter(left);
//         if (it == mp.end()) return false;
//         return it->first <= left && it->second >= right;
//     }
    
//     void removeRange(int left, int right) {
        
//         auto it = first_iter(left);
//         // v used to collect possible intervals that has partial overlap with [left, right)
//         vector<pair<int,int>> v;
//         // remove all overlapping intervals
//         while (it != mp.end() && it->first < right) {
//             // collect partially overlapped intervals
//             // and update its left right borders
//             if (it->first < left) {
//                 v.push_back({it->first, left});
//             }
//             if (it->second > right) {
//                 v.push_back({right, it->second});
//             }
//             mp.erase(it++);
//         }
//         // insert back partial intervals
//         for (auto& p: v) {
//             mp.insert(p);
//         }
//     }
    
//     map<int,int> mp; // [beg, end)
// };
// /**
//  * Your RangeModule object will be instantiated and called as such:
//  * RangeModule* obj = new RangeModule();
//  * obj->addRange(left,right);
//  * bool param_2 = obj->queryRange(left,right);
//  * obj->removeRange(left,right);
//  */
```
