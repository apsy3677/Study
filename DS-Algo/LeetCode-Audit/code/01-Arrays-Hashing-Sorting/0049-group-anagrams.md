# 49. Group Anagrams

[Problem](https://leetcode.com/problems/group-anagrams/) · Medium · Arrays, Hashing & Sorting → Canonical key

LeetCode tags: array, hash-table, string, sorting

Attempts since Mar 2023: 4 · accepted: 2 · failed before first AC: 2

## Attempt 1 · 2023-03-21 09:22 IST · Compile Error · C++

[submission 919219818](https://leetcode.com/submissions/detail/919219818/)

Your output:

```text
{"compile_error": "Line 15: Char 5: error: non-void function does not return a value in all control paths [-Werror,-Wreturn-type]\n    }\n    ^"}
```

Compile error:

```text
Line 15: Char 5: error: non-void function does not return a value in all control paths [-Werror,-Wreturn-type]
    }
    ^
```

```cpp
class Solution {
public:
     
    bool checkAnagrams(string s, string t){
        bool ans = false;
        if(s.size() != t.size()){
            return ans;
        }
        map<char,int> s_map, t_map;

        for(int i=0;i<s.size();i++){

        }
        
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        if(strs.size() == 0){
            return ans;
        }
        vector<string> anagrams ;
        vector<bool> visited(strs.size(), false);

        for(int i=0;i<strs.size();i++){
            if(visited[i]){
                continue;
            }
            anagrams.resize(0);
            anagrams.push_back(strs[i]);
            visited[i] = true;
            for(int j= i+1;j<strs.size();i++){
                if(checkAnagrams(s[i], s[j])){

                    anagrams.push_back(s[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(anagrams);
        }

        return ans;
    }
};
```

## Attempt 2 · 2023-03-21 09:36 IST · Time Limit Exceeded · C++

[submission 919226157](https://leetcode.com/submissions/detail/919226157/) · tests 111/118

Failing input:

```text
["nozzle","punjabi","waterlogged","imprison","crux","numismatists","sultans","rambles","deprecating","aware","outfield","marlborough","guardrooms","roast","wattage","shortcuts","confidential","reprint","foxtrot","dispossession","floodgate","unfriendliest","semimonthlies","dwellers","walkways","wastrels","dippers","engrossing","undertakings","unforeseen","oscilloscopes","pioneers","geller","neglect ... [110884 more chars]
```

Expected:

```text
[["affabler"],["sorrowed"],["scarves"],["prolific"],["vetting"],["lauded"],["condemned"],["dickered"],["sharron"],["vancouver"],["attributively"],["suavity"],["shoeshines"],["liquids"],["bubbly"],["overcoat"],["birthplace"],["chatterley"],["heathen"],["slayings"],["potshots"],["impressionable"],["disenchants"],["termed"],["informants"],["effie"],["survivor"],["persians"],["satirize"],["moistened"] ... [130622 more chars]
```

```cpp
class Solution {
public:
    map<char,int> s_map, t_map;

    bool checkAnagrams(string &s, string &t){
        bool ans = false;
        if(s.size() != t.size()){
            return ans;
        }
        s_map.clear();
        t_map.clear();
        for(int i=0;i<s.size();i++){
            s_map[s[i]]++;
        }
        for(int i=0;i<s.size();i++){
            t_map[t[i]]++;
        }
        if(s_map.size() != t_map.size()){
            return ans;
        }
        auto it_s = s_map.begin(), it_t = t_map.begin();

        while(it_s != s_map.end() && it_t != t_map.end()){

            if(it_s -> first == it_t -> first && 
                it_s -> second == it_t -> second){

            }
            else{
                return ans;
            }

            it_s++;
            it_t++;
        }
        if(it_s != s_map.end() || it_t != t_map.end()){
            return ans;
        }

        return true;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        if(strs.size() == 0){
            return ans;
        }
        vector<string> anagrams ;
        vector<bool> visited(strs.size(), false);

        for(int i=0;i<strs.size();i++){
            if(visited[i]){
                continue;
            }
            anagrams.clear();
            anagrams.push_back(strs[i]);
            visited[i] = true;
            for(int j= i+1;j<strs.size();j++){
                if(!visited[j] && checkAnagrams(strs[i], strs[j])){

                    anagrams.push_back(strs[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(anagrams);
        }

        return ans;
    }
};
```

## Attempt 3 · 2023-03-21 09:45 IST · Accepted · C++

[submission 919230452](https://leetcode.com/submissions/detail/919230452/) · tests 118/118 · runtime 50 ms (beats 15.4%)

```cpp
class Solution {
public:
    map<char,int> s_map, t_map;

    bool checkAnagrams(string &s, string &t){
        bool ans = false;
        if(s.size() != t.size()){
            return ans;
        }
        s_map.clear();
        t_map.clear();
        for(int i=0;i<s.size();i++){
            s_map[s[i]]++;
        }
        for(int i=0;i<s.size();i++){
            t_map[t[i]]++;
        }
        if(s_map.size() != t_map.size()){
            return ans;
        }
        auto it_s = s_map.begin(), it_t = t_map.begin();

        while(it_s != s_map.end() && it_t != t_map.end()){

            if(it_s -> first == it_t -> first && 
                it_s -> second == it_t -> second){

            }
            else{
                return ans;
            }

            it_s++;
            it_t++;
        }
        if(it_s != s_map.end() || it_t != t_map.end()){
            return ans;
        }

        return true;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        if(strs.size() == 0){
            return ans;
        }
        vector<string> anagrams ;
        vector<bool> visited(strs.size(), false);

        map<string, vector<string>> groups;
        for(int i=0;i<strs.size();i++){
            string key = strs[i];
            sort(key.begin(), key.end());
            groups[key].push_back(strs[i]);
        }

        for(auto it : groups){
            ans.push_back(it.second);
        }

        return ans;

        for(int i=0;i<strs.size();i++){
            if(visited[i]){
                continue;
            }
            anagrams.clear();
            anagrams.push_back(strs[i]);
            visited[i] = true;
            for(int j= i+1;j<strs.size();j++){
                if(!visited[j] && checkAnagrams(strs[i], strs[j])){

                    anagrams.push_back(strs[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(anagrams);
        }

        return ans;
    }
};
```

## Attempt 4 · 2023-03-22 21:06 IST · Accepted · C++

[submission 920196438](https://leetcode.com/submissions/detail/920196438/) · tests 118/118 · runtime 36 ms (beats 17.7%)

```cpp
class Solution {
public:
    map<char,int> s_map, t_map;

    bool checkAnagrams(string &s, string &t){
        bool ans = false;
        if(s.size() != t.size()){
            return ans;
        }
        s_map.clear();
        t_map.clear();
        for(int i=0;i<s.size();i++){
            s_map[s[i]]++;
        }
        for(int i=0;i<s.size();i++){
            t_map[t[i]]++;
        }
        if(s_map.size() != t_map.size()){
            return ans;
        }
        auto it_s = s_map.begin(), it_t = t_map.begin();

        while(it_s != s_map.end() && it_t != t_map.end()){

            if(it_s -> first == it_t -> first && 
                it_s -> second == it_t -> second){

            }
            else{
                return ans;
            }

            it_s++;
            it_t++;
        }
        if(it_s != s_map.end() || it_t != t_map.end()){
            return ans;
        }

        return true;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        if(strs.size() == 0){
            return ans;
        }
        vector<string> anagrams ;
        vector<bool> visited(strs.size(), false);

        map<string, vector<string>> groups;
        for(int i=0;i<strs.size();i++){
            string key = strs[i];
            sort(key.begin(), key.end());
            groups[key].push_back(strs[i]);
        }

        for(auto it : groups){
            ans.push_back(it.second);
        }

        return ans;

        for(int i=0;i<strs.size();i++){
            if(visited[i]){
                continue;
            }
            anagrams.clear();
            anagrams.push_back(strs[i]);
            visited[i] = true;
            for(int j= i+1;j<strs.size();j++){
                if(!visited[j] && checkAnagrams(strs[i], strs[j])){

                    anagrams.push_back(strs[j]);
                    visited[j] = true;
                }
            }
            ans.push_back(anagrams);
        }

        return ans;
    }
};
```
