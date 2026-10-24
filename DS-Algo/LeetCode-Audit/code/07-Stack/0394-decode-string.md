# 394. Decode String

[Problem](https://leetcode.com/problems/decode-string/) · Medium · Stack → Nested decode stack

LeetCode tags: string, stack, recursion

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-09-13 00:11 IST · Wrong Answer · C++

[submission 1047747472](https://leetcode.com/submissions/detail/1047747472/) · tests 23/34

Failing input:

```text
"100[leetcode]"
```

Expected:

```text
"leetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcodeleetcod ... [402 more chars]
```

Your output:

```text
"leetcode"
```

```cpp
class Solution {
public:
    string decodeString(string str) {
        stack<char> record;
        string result="";
        string subStr = "";
        for (auto s:str) {
            if(s==']') {
                while(record.top() != '[') {
                    subStr = record.top() + subStr;
                    record.pop();
                }
                record.pop();
                int decimal = 1;
                int count = 0;
                while(!record.empty() && isNumber(record.top())) {
                    count = count + decimal*getInt(record.top());
                    record.pop();
                }
                while(count>0) {
                    for(auto c:subStr) {
                        record.push(c);
                    }
                    count--;
                }
                subStr="";
            } else {
                record.push(s);
            }
        }
        while(!record.empty()) {
            result = record.top() + result;
            record.pop();
        }
        return result;
    }

    bool isNumber(char ch) {
        return ch>='0' && ch<='9';
    }

    int getInt(char ch) {
        return ch - '0';
    }
};
```

## Attempt 2 · 2023-09-13 00:13 IST · Accepted · C++

[submission 1047748694](https://leetcode.com/submissions/detail/1047748694/) · tests 34/34 · runtime 6 ms (beats 0.8%)

```cpp
class Solution {
public:
    string decodeString(string str) {
        stack<char> record;
        string result="";
        string subStr = "";
        for (auto s:str) {
            if(s==']') {
                while(record.top() != '[') {
                    subStr = record.top() + subStr;
                    record.pop();
                }
                record.pop();
                int decimal = 1;
                int count = 0;
                while(!record.empty() && isNumber(record.top())) {
                    count = count + decimal*getInt(record.top());
                    decimal = decimal*10;
                    record.pop();
                }
                while(count>0) {
                    for(auto c:subStr) {
                        record.push(c);
                    }
                    count--;
                }
                subStr="";
            } else {
                record.push(s);
            }
        }
        while(!record.empty()) {
            result = record.top() + result;
            record.pop();
        }
        return result;
    }

    bool isNumber(char ch) {
        return ch>='0' && ch<='9';
    }

    int getInt(char ch) {
        return ch - '0';
    }
};
```
