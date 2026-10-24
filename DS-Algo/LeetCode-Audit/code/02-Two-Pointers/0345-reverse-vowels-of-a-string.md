# 345. Reverse Vowels of a String

[Problem](https://leetcode.com/problems/reverse-vowels-of-a-string/) · Easy · Two Pointers → Opposite ends

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-08-19 00:14 IST · Wrong Answer · C++

[submission 1025125409](https://leetcode.com/submissions/detail/1025125409/) · tests 394/480

Failing input:

```text
"Live on evasions? No, I save no evil."
```

Expected:

```text
"Live on evasIons? No, i save no evil."
```

Your output:

```text
"Live on evasoons? Ni, I save no evil."
```

```cpp

#include <vector>
class Solution {
public:
    string reverseVowels(string s) {
        int start = 0, end =s.size()-1;
        while(start<end) {
            char sc = s[start];
            char ec = s[end];
            if(!isVowel(sc))
                start++;
            if(!isVowel(ec))
                end--;
            if(isVowel(sc) && isVowel(ec)) {
                char t = s[start];
                s[start] = s[end];
                s[end] = t;
                start++;
                end--;
            }
        }
        return s;
    }

    bool isVowel(char c) {
        return c == 'a'|| c=='e'|| c=='i'|| c=='o'|| c=='u'
        || c=='A'|| c=='E'|| c=='i'|| c=='O'|| c=='U';
    }
};
```

## Attempt 2 · 2023-08-19 00:15 IST · Accepted · C++

[submission 1025126413](https://leetcode.com/submissions/detail/1025126413/) · tests 480/480 · runtime 3 ms (beats 32.3%)

```cpp

#include <vector>
class Solution {
public:
    string reverseVowels(string s) {
        int start = 0, end =s.size()-1;
        while(start<end) {
            char sc = s[start];
            char ec = s[end];
            if(!isVowel(sc))
                start++;
            if(!isVowel(ec))
                end--;
            if(isVowel(sc) && isVowel(ec)) {
                char t = s[start];
                s[start] = s[end];
                s[end] = t;
                start++;
                end--;
            }
        }
        return s;
    }

    bool isVowel(char c) {
        return c == 'a'|| c=='e'|| c=='i'|| c=='o'|| c=='u'
        || c=='A'|| c=='E'|| c=='I'|| c=='O'|| c=='U';
    }
};
```
