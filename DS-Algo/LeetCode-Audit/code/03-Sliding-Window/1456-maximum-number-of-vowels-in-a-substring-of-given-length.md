# 1456. Maximum Number of Vowels in a Substring of Given Length

[Problem](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/) · Medium · Sliding Window → Fixed window

LeetCode tags: string, sliding-window

Attempts since Mar 2023: 6 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-08-25 22:35 IST · Accepted · C++

[submission 1031591862](https://leetcode.com/submissions/detail/1031591862/) · tests 106/106 · runtime 348 ms (beats 5.3%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount = 0, i, n=s.length();
        for (i=0;i<k;i++) {  // abc i iidef
            if(isVowel(s[i])) {
                currCount++; // 0
            }
        }
        maxCount = currCount; // 0
        for(;i<n;i++) {      // ab cii i def
            if(isVowel(s[i-k]) && isVowel(s[i])) {
            } else if (isVowel(s[i-k])) {
                currCount--;
            } else if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
        }
        return maxCount;
    }

    bool isVowel(char c) {
        vector<char> vowels{'a', 'e', 'i', 'o', 'u'};
        return  find(vowels.begin(), vowels.end(), c) != vowels.end();
    }
};
```

## Attempt 2 · 2023-08-25 22:37 IST · Accepted · C++

[submission 1031593106](https://leetcode.com/submissions/detail/1031593106/) · tests 106/106 · runtime 23 ms (beats 5.3%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount = 0, i, n=s.length();
        for (i=0;i<k;i++) {  // abc i iidef
            if(isVowel(s[i])) {
                currCount++; // 0
            }
        }
        maxCount = currCount; // 0
        for(;i<n;i++) {      // ab cii i def
            if(isVowel(s[i-k]) && isVowel(s[i])) {
            } else if (isVowel(s[i-k])) {
                currCount--;
            } else if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
        }
        return maxCount;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
```

## Attempt 3 · 2023-08-25 22:38 IST · Accepted · C++

[submission 1031593690](https://leetcode.com/submissions/detail/1031593690/) · tests 106/106 · runtime 21 ms (beats 5.3%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount, i, n=s.length();
        for (i=0;i<k;i++) {  // abc i iidef
            if(isVowel(s[i])) {
                currCount++; // 0
            }
        }
        maxCount = currCount; // 0
        for(;i<n;i++) {      // ab cii i def
            if(isVowel(s[i-k]) && isVowel(s[i])) {
            } else if (isVowel(s[i-k])) {
                currCount--;
            } else if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
        }
        return maxCount;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
```

## Attempt 4 · 2023-08-25 22:40 IST · Accepted · C++

[submission 1031595683](https://leetcode.com/submissions/detail/1031595683/) · tests 106/106 · runtime 19 ms (beats 6.2%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount, i=0, n=s.length();
        while(i<k) {  // abc i iidef
            if(isVowel(s[i])) {
                currCount++; // 0
            }
            i++;
        }
        maxCount = currCount; // 0
        while(i<n) {      // ab cii i def
            if(isVowel(s[i-k]) && isVowel(s[i])) {
            } else if (isVowel(s[i-k])) {
                currCount--;
            } else if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
            i++;
        }
        return maxCount;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
```

## Attempt 5 · 2023-08-25 22:41 IST · Accepted · C++

[submission 1031596595](https://leetcode.com/submissions/detail/1031596595/) · tests 106/106 · runtime 23 ms (beats 5.3%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount, i=0, n=s.length();
        while(i<k) {  // abc i iidef
            if(isVowel(s[i])) {
                currCount++; // 0
            }
            i++;
        }
        maxCount = currCount; // 0
        while(i<n) {      // ab cii i def
            if (isVowel(s[i-k])) {
                currCount--;
            } 
            if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
            i++;
        }
        return maxCount;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
```

## Attempt 6 · 2023-08-25 22:43 IST · Accepted · C++

[submission 1031598078](https://leetcode.com/submissions/detail/1031598078/) · tests 106/106 · runtime 24 ms (beats 5.3%)

```cpp
class Solution {
public:
    int maxVowels(string s, int k) {
        int currCount=0, maxCount=0, i=0, n=s.length();
        while(i<n) {      // ab cii i def
            if (i>=k && isVowel(s[i-k])) {
                currCount--;
            } 
            if (isVowel(s[i])) {
                currCount++; // 2
            } 
            if(currCount>maxCount) {
                maxCount=currCount; // 2
            }
            i++;
        }
        return maxCount;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
```
