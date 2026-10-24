# 68. Text Justification

[Problem](https://leetcode.com/problems/text-justification/) · Hard · Strings & Simulation → Simulation

LeetCode tags: array, string, simulation

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-03-21 10:48 IST · Accepted · C++

[submission 919260300](https://leetcode.com/submissions/detail/919260300/) · tests 27/27 · runtime 5 ms (beats 0.5%)

```cpp
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        
        // traverse all words
        // find words with their size less than maxWidth and no of words should have equal amount of spaces in between
        // pick words and try to check if they can be left & right aligned properly.

        int wordsTaken=0, i=0;
        int n = words.size();
        vector<string> ans;
        while(i<n){

            // find wordcount that can fit in maxWidth
            
            int j=i;
            wordsTaken=0;
            int spaces=0, line =0;
            string s = "";
            for(;j<n;j++){
                
                if(line + words[j].size() + (j-i) > maxWidth){
                    break;
                }
                line += words[j].size();
                wordsTaken++;
                spaces = (maxWidth - line);
            }
            // spaces equal
            // if cant be, then more spaces on left words
            // divide btwn words
            // abc   def
            
            if(wordsTaken == 1){
                s = words[i];
                if(s.size() < maxWidth)
                    s.append(maxWidth - s.size(), ' ');
                i=j;
            }
            else{
                int extra = spaces % (wordsTaken -1);
                // spaces = spaces/(wordsTaken -1);
                if(j==n){
                    for(;i<j;i++){
                        s += words[i];
                        if(s.size() < maxWidth)
                            s.append(1, ' ');
                    }
                    if(s.size() < maxWidth)
                        s.append(maxWidth - s.size(), ' ');
                }
                else{
                    
                    for(;i<j;i++){
                        s += words[i];
                        
                        int sp = spaces/(wordsTaken -1) + (extra >0 ? 1 : 0);
                        extra--;
                        if(s.size() < maxWidth)
                            s.append(sp, ' ');
                    }
                    if(s.size() < maxWidth)
                        s.append(maxWidth - s.size(), ' ');
                }
                
            }

            ans.push_back(s);
            // increment i properly
            i = j;

        }
        return ans;
    }
};
```

## Attempt 2 · 2023-03-22 21:06 IST · Accepted · C++

[submission 920196506](https://leetcode.com/submissions/detail/920196506/) · tests 27/27 · runtime 0 ms (beats 100%)

```cpp
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        
        // traverse all words
        // find words with their size less than maxWidth and no of words should have equal amount of spaces in between
        // pick words and try to check if they can be left & right aligned properly.

        int wordsTaken=0, i=0;
        int n = words.size();
        vector<string> ans;
        while(i<n){

            // find wordcount that can fit in maxWidth
            
            int j=i;
            wordsTaken=0;
            int spaces=0, line =0;
            string s = "";
            for(;j<n;j++){
                
                if(line + words[j].size() + (j-i) > maxWidth){
                    break;
                }
                line += words[j].size();
                wordsTaken++;
                spaces = (maxWidth - line);
            }
            // spaces equal
            // if cant be, then more spaces on left words
            // divide btwn words
            // abc   def
            
            if(wordsTaken == 1){
                s = words[i];
                if(s.size() < maxWidth)
                    s.append(maxWidth - s.size(), ' ');
                i=j;
            }
            else{
                int extra = spaces % (wordsTaken -1);
                // spaces = spaces/(wordsTaken -1);
                if(j==n){
                    for(;i<j;i++){
                        s += words[i];
                        if(s.size() < maxWidth)
                            s.append(1, ' ');
                    }
                    if(s.size() < maxWidth)
                        s.append(maxWidth - s.size(), ' ');
                }
                else{
                    
                    for(;i<j;i++){
                        s += words[i];
                        
                        int sp = spaces/(wordsTaken -1) + (extra >0 ? 1 : 0);
                        extra--;
                        if(s.size() < maxWidth)
                            s.append(sp, ' ');
                    }
                    if(s.size() < maxWidth)
                        s.append(maxWidth - s.size(), ' ');
                }
                
            }

            ans.push_back(s);
            // increment i properly
            i = j;

        }
        return ans;
    }
};
```
