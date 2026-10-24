# 1071. Greatest Common Divisor of Strings

[Problem](https://leetcode.com/problems/greatest-common-divisor-of-strings/) · Easy · Math & Bit Manipulation → GCD

LeetCode tags: math, string, euclidean-algorithm, greatest-common-divisor

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-08-18 00:46 IST · Wrong Answer · C++

[submission 1024263520](https://leetcode.com/submissions/detail/1024263520/) · tests 77/123

Failing input:

```text
"ABABABAB"
"ABAB"
```

Expected:

```text
"ABAB"
```

Your output:

```text
"AB"
```

```cpp
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int n=str1.size();
        int m=str2.size();
        int hcf = getHcf(n,m);
        cout<<"HCF: "<<hcf<<endl;
        string result = "";
        string temp = "";
        for(int i = 1; i <= hcf; i++) {
            temp = temp + str1[i-1];
            if(hcf%i==0) {
                cout<<"i: "<<i<<endl;
                string x = getString(temp, n/i);
                string y = getString(temp, m/i);
                cout<<"x:"<<x<<" y:"<<y<<endl;
                if(x==str1 && y == str2) {
                    result = temp;
                    break;
                }
            }
        }
        return result;
    }

    string getString(string temp, int times) {
        string result = "";
        for (int i =0;i<times;i++) {
            result = result+temp;
        }
        return result;
    }

    int getHcf(int n, int m) {
        if(n>m) {
            if(n%m==0) {
                return m;
            } else {
                return getHcf(m, n%m);
            }
        } else {
            if(m%n==0) {
                return n;
            } else {
                return getHcf(n, m%n);
            }
        }
    }
};
```

## Attempt 2 · 2023-08-18 00:46 IST · Accepted · C++

[submission 1024263824](https://leetcode.com/submissions/detail/1024263824/) · tests 123/123 · runtime 95 ms (beats 5.1%)

```cpp
class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int n=str1.size();
        int m=str2.size();
        int hcf = getHcf(n,m);
        cout<<"HCF: "<<hcf<<endl;
        string result = "";
        string temp = "";
        for(int i = 1; i <= hcf; i++) {
            temp = temp + str1[i-1];
            if(hcf%i==0) {
                cout<<"i: "<<i<<endl;
                string x = getString(temp, n/i);
                string y = getString(temp, m/i);
                cout<<"x:"<<x<<" y:"<<y<<endl;
                if(x==str1 && y == str2) {
                    result = temp;
                }
            }
        }
        return result;
    }

    string getString(string temp, int times) {
        string result = "";
        for (int i =0;i<times;i++) {
            result = result+temp;
        }
        return result;
    }

    int getHcf(int n, int m) {
        if(n>m) {
            if(n%m==0) {
                return m;
            } else {
                return getHcf(m, n%m);
            }
        } else {
            if(m%n==0) {
                return n;
            } else {
                return getHcf(n, m%n);
            }
        }
    }
};
```
