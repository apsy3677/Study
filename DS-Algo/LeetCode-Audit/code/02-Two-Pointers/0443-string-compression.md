# 443. String Compression

[Problem](https://leetcode.com/problems/string-compression/) · Medium · Two Pointers → Read/write pointers

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 7 · accepted: 2 · failed before first AC: 5

## Attempt 1 · 2023-08-24 00:08 IST · Wrong Answer · C++

[submission 1029848000](https://leetcode.com/submissions/detail/1029848000/) · tests 0/75

Failing input:

```text
["a","a","b","b","c","c","c"]
```

Expected:

```text
["a","2","b","2","c","3"]
```

Your output:

```text
["a","","",""]
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        int currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count == 1) {
                    newIndex++;
                } else {
                    compressDigit(chars, newIndex, count);
                }
                count = 1;
                currentChar = chars[i];
            }
        }
        if(count == 1) {
            newIndex++;
        } else {
            compressDigit(chars, newIndex, count);
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int &count) {
        
        while(count!=0) {
            newIndex++;
            int rem = count%10;
            count = count/10;
            chars[newIndex] = rem;
            cout<<rem<<" ";
        }
    }
};
```

## Attempt 2 · 2023-08-24 00:18 IST · Wrong Answer · C++

[submission 1029856921](https://leetcode.com/submissions/detail/1029856921/) · tests 33/75

Failing input:

```text
["a","a","a","b","b","a","a"]
```

Expected:

```text
["a","3","b","2","a","2"]
```

Your output:

```text
["a","3","a","2","b","2"]
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        int currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count != 1) {
                    compressDigit(chars, newIndex, count);
                }
                newIndex++;
                count = 1;
                currentChar = chars[i];
            }
        }
        if(count != 1) {
            compressDigit(chars, newIndex, count);
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int &count) {
        string str = "";
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
            cout<<rem<<" ";
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```

## Attempt 3 · 2023-08-24 00:24 IST · Wrong Answer · C++

[submission 1029861766](https://leetcode.com/submissions/detail/1029861766/) · tests 40/75

Failing input:

```text
["a","a","a","a","a","b"]
```

Expected:

```text
["a","5","b"]
```

Your output:

```text
["a","5","a"]
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        int currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count != 1) {
                    compressDigit(chars, newIndex, count, currentChar);
                }
                newIndex++;
                count = 1;
                currentChar = chars[i];
            }
        }
        if(count != 1) {
            compressDigit(chars, newIndex, count, currentChar);
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int count, char ch) {
        string str = "";
        chars[newIndex] = ch;
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
            cout<<rem<<" ";
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```

## Attempt 4 · 2023-08-24 00:29 IST · Wrong Answer · C++

[submission 1029865733](https://leetcode.com/submissions/detail/1029865733/) · tests 40/75

Failing input:

```text
["a","a","a","a","a","b"]
```

Expected:

```text
["a","5","b"]
```

Your output:

```text
["a","5","a"]
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        char currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count != 1) {
                    compressDigit(chars, newIndex, count, currentChar);
                }
                newIndex++;
                count = 1;
                currentChar = chars[i];
                cout<<currentChar<<" ";
            }
        }
        if(count != 1) {
            compressDigit(chars, newIndex, count, currentChar);
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int count, char ch) {
        string str = "";
        chars[newIndex] = ch;
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```

## Attempt 5 · 2023-08-24 00:32 IST · Wrong Answer · C++

[submission 1029868613](https://leetcode.com/submissions/detail/1029868613/) · tests 43/75

Failing input:

```text
["a","a","a","a","b","a"]
```

Expected:

```text
["a","4","b","a"]
```

Your output:

```text
["a","4","a","a"]
```

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        char currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count != 1) {
                    compressDigit(chars, newIndex, count, currentChar);
                }
                newIndex++;
                count = 1;
                currentChar = chars[i];
                cout<<currentChar<<" ";
            }
        }
        if(count != 1) {
            compressDigit(chars, newIndex, count, currentChar);
        } else {
            chars[newIndex] = currentChar;
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int count, char ch) {
        string str = "";
        chars[newIndex] = ch;
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```

## Attempt 6 · 2023-08-24 00:39 IST · Accepted · C++

[submission 1029873840](https://leetcode.com/submissions/detail/1029873840/) · tests 75/75 · runtime 8 ms (beats 2.3%)

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int newIndex = 0, currentIndex = 0, count = 1;
        char currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                if(count != 1) {
                    compressDigit(chars, newIndex, count, currentChar);
                } else {
                    chars[newIndex] = currentChar;
                }
                newIndex++;
                count = 1;
                currentChar = chars[i];
                cout<<currentChar<<" ";
            }
        }
        if(count != 1) {
            compressDigit(chars, newIndex, count, currentChar);
        } else {
            chars[newIndex] = currentChar;
        }
        return newIndex+1;
    }

    void compressDigit(vector<char>& chars, int &newIndex, int count, char ch) {
        string str = "";
        chars[newIndex] = ch;
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```

## Attempt 7 · 2023-08-24 00:46 IST · Accepted · C++

[submission 1029879136](https://leetcode.com/submissions/detail/1029879136/) · tests 75/75 · runtime 7 ms (beats 2.3%)

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), newIndex = 0, currentIndex = 0, count = 1;
        char currentChar = chars[0];
        for (int i=1;i<n;i++) {
            if(chars[i] == currentChar) {
                count++;
            } else {
                compressGroup(chars, newIndex, count, currentChar);
                newIndex++;
                count = 1;
                currentChar = chars[i];
            }
        }
        compressGroup(chars, newIndex, count, currentChar);
        return newIndex+1;
    }

    void compressGroup(vector<char>& chars, int &newIndex, int count, char ch) {
        if(count != 1) {
            compressDigit(chars, newIndex, count, ch);
        } else {
            chars[newIndex] = ch;
        }
    }

    void compressDigit(vector<char>& chars, int &newIndex, int count, char ch) {
        string str = "";
        chars[newIndex] = ch;
        while(count!=0) {
            char rem = '0' + count%10;
            count = count/10;
            str = str + rem;
        }
        for(int i=str.length()-1;i>=0;i--) {
            newIndex++;
            chars[newIndex] = str[i];
        }
    }
};
```
