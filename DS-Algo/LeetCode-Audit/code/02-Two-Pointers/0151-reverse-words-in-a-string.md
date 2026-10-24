# 151. Reverse Words in a String

[Problem](https://leetcode.com/problems/reverse-words-in-a-string/) · Medium · Two Pointers → Reverse words

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-08-23 19:33 IST · Accepted · C++

[submission 1029596542](https://leetcode.com/submissions/detail/1029596542/) · tests 58/58 · runtime 7 ms (beats 13.4%)

```cpp
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int j=0;
        vector<string> words;
        string str = "";
        while(j<n) {
            if(isCharOrDigit(s[j])) {
                str = str + s[j];
            
            } else {
                if(str != "") {
                    words.push_back(str);
                    str="";
                }
            }
            j++;
        }
        if(str != "") {
            words.push_back(str);
        }
        return finalReverseWords(words);
    }

    bool isCharOrDigit(char c) {
        return (c >= 'a' && c<= 'z') ||
            (c >= 'A' && c<= 'Z') ||
            (c >= '0' && c<= '9');
    }

    string finalReverseWords(vector<string> words) {
        int n = words.size();
        if(n==0) {
            return "";
        }
        string str = words[n-1];
        for(int i=n-2; i>=0 ;i--) {
            str = str +  " " + words[i];
        }
        return str;
    }
};
```
