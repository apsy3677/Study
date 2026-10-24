# 22. Generate Parentheses

[Problem](https://leetcode.com/problems/generate-parentheses/) · Medium · Backtracking → Balanced generation

LeetCode tags: string, dynamic-programming, backtracking, bracket-sequences

Attempts since Mar 2023: 5 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-25 03:20 IST · Accepted · C++

[submission 921532455](https://leetcode.com/submissions/detail/921532455/) · tests 8/8 · runtime 11 ms (beats 7.0%)

```cpp
class Solution {
    vector<string> ans;
public:
    void generate(int n, int left, int right, string s){
        if(left ==n && right ==n){
            ans.push_back(s);
            cout<<s<< " ";
            return;
        }
        // char ch ='(';
        // s +=ch;
        if(left<n)
            generate(n, left+1,right,s+"(");
        // s.erase(s.end()-1);

        if(left>right){
            // ch = ')';
            // s += ch;
            generate(n, left,right+1,s+")");
            // s.erase(s.end()-1);
        }
    }
    vector<string> generateParenthesis(int n) {
        string s ="";
        generate(n,0,0,s);
        return ans;
    }
};
```

## Attempt 2 · 2023-03-25 03:25 IST · Accepted · C++

[submission 921533825](https://leetcode.com/submissions/detail/921533825/) · tests 8/8 · runtime 12 ms (beats 6.2%)

```cpp
class Solution {
    vector<string> ans;
public:
    void generate(int n, int left, int right, string &s){
        if(left ==n && right ==n){
            ans.push_back(s);
            cout<<s<< " ";
            return;
        }
        char ch ='(';
        
        if(left<n){
            s +=ch;
            generate(n, left+1,right,s);
            s.erase(s.end()-1);
        }
            

        if(left>right){
            ch = ')';
            s += ch;
            generate(n, left,right+1,s);
            s.erase(s.end()-1);
        }
    }
    vector<string> generateParenthesis(int n) {
        string s ="";
        generate(n,0,0,s);
        return ans;
    }
};
```

## Attempt 3 · 2023-05-20 14:35 IST · Accepted · C++

[submission 953806289](https://leetcode.com/submissions/detail/953806289/) · tests 8/8 · runtime 4 ms (beats 32.2%)

```cpp
class Solution {
    vector<string> ans;
public:
    void generate(int n, int left, int right, string &s){
        if(left ==n && right ==n){
            ans.push_back(s);
            cout<<s<< " ";
            return;
        }
        char ch ='(';
        
        if(left<n){
            s += ch;
            generate(n, left+1,right,s);
            s.erase(s.end()-1);
        }
            

        if(left>right){
            ch = ')';
            s += ch;
            generate(n, left,right+1,s);
            s.erase(s.end()-1);
        }
    }
    void f(int n, int l, int r, string s){
        if(l==0 && r==0){
            ans.push_back(s);
        }
        if(l>0){
            f(n, l-1, r, s + '(' );
        }
        if(r>0 && (n-l)> (n-r)){
            f(n, l, r-1, s+')');
        }
    }
    vector<string> generateParenthesis(int n) {
        string s ="";
        f(n, n,n,s);
        // generate(n,0,0,s);
        return ans;
    }
};
```

## Attempt 4 · 2023-05-20 14:36 IST · Accepted · C++

[submission 953806924](https://leetcode.com/submissions/detail/953806924/) · tests 8/8 · runtime 8 ms (beats 7.9%)

```cpp
class Solution {
    vector<string> ans;
public:
    void generate(int n, int left, int right, string &s){
        if(left ==n && right ==n){
            ans.push_back(s);
            cout<<s<< " ";
            return;
        }
        char ch ='(';
        
        if(left<n){
            s += ch;
            generate(n, left+1,right,s);
            s.erase(s.end()-1);
        }
            

        if(left>right){
            ch = ')';
            s += ch;
            generate(n, left,right+1,s);
            s.erase(s.end()-1);
        }
    }
    void f(int n, int l, int r, string s){
        if(l==0 && r==0){
            ans.push_back(s);
            return;
        }
        if(l>0){
            f(n, l-1, r, s + '(' );
        }
        if(r>0 && (n-l)> (n-r)){
            f(n, l, r-1, s+')');
        }
    }
    vector<string> generateParenthesis(int n) {
        string s ="";
        f(n, n,n,s);
        // generate(n,0,0,s);
        return ans;
    }
};
```

## Attempt 5 · 2023-05-20 14:43 IST · Accepted · C++

[submission 953809671](https://leetcode.com/submissions/detail/953809671/) · tests 8/8 · runtime 3 ms (beats 66.5%)

```cpp
class Solution {
    vector<string> ans;
public:
    void generate(int n, int left, int right, string &s){
        if(left ==n && right ==n){
            ans.push_back(s);
            // cout<<s<< " ";
            return;
        }
        char ch ='(';
        
        if(left<n){
            s += ch;
            generate(n, left+1,right,s);
            s.erase(s.end()-1);
        }
            

        if(left>right){
            ch = ')';
            s += ch;
            generate(n, left,right+1,s);
            s.erase(s.end()-1);
        }
    }
    void f(int n, int l, int r, string s){
        if(l==0 && r==0){
            ans.push_back(s);
            return;
        }
        if(l>0){
            f(n, l-1, r, s + '(' );
        }
        if(r>0 && (n-l)> (n-r)){
            f(n, l, r-1, s+')');
        }
    }
    vector<string> generateParenthesis(int n) {
        string s ="";
        // f(n, n,n,s);
        generate(n,0,0,s);
        return ans;
    }
};
```
