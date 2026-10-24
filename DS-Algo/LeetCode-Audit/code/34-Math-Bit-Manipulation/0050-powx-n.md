# 50. Pow(x, n)

[Problem](https://leetcode.com/problems/powx-n/) · Medium · Math & Bit Manipulation → Fast power

LeetCode tags: math, recursion

Attempts since Mar 2023: 10 · accepted: 7 · failed before first AC: 0

## Attempt 1 · 2023-11-22 20:49 IST · Accepted · Python3

[submission 1104243702](https://leetcode.com/submissions/detail/1104243702/) · tests 306/306 · runtime 35 ms (beats 0.6%)

```python
class Solution:
    def myPow(self, x: float, n: int) -> float:
        
        if n <0:
            x = 1/x
            n = -n
        
        result = 1
        while n > 0:
            # print(bin(n)[2:])
            if n&1:
                print('least sig is 1')
                result *= x
            
            x*=x
            # print('next power', x)
            n>>=1

        return result
```

## Attempt 2 · 2023-11-22 20:49 IST · Accepted · Python3

[submission 1104243758](https://leetcode.com/submissions/detail/1104243758/) · tests 306/306 · runtime 30 ms (beats 0.6%)

```python
class Solution:
    def myPow(self, x: float, n: int) -> float:
        
        if n <0:
            x = 1/x
            n = -n
        
        result = 1
        while n > 0:
            # print(bin(n)[2:])
            if n&1:
                # print('least sig is 1')
                result *= x
            
            x*=x
            # print('next power', x)
            n>>=1

        return result
```

## Attempt 3 · 2023-12-04 21:37 IST · Accepted · Python3

[submission 1112265657](https://leetcode.com/submissions/detail/1112265657/) · tests 306/306 · runtime 46 ms (beats 0.6%)

```python
class Solution:
    def myPow(self, x: float, n: int) -> float:
        if n ==0:
            return 1
            
        if n<0:
            n = -n
            x = 1/x

        

        
        total = 0
        
        if n & 1:
            total = x* self.myPow(x*x, (n-1)//2)
        else:
            total = self.myPow(x*x, n//2)
        return total
```

## Attempt 4 · 2023-12-04 21:46 IST · Accepted · Python3

[submission 1112271277](https://leetcode.com/submissions/detail/1112271277/) · tests 306/306 · runtime 42 ms (beats 0.6%)

```python
class Solution:
    def myPow1(self, x: float, n: int) -> float:
        '''
        approach1 
        recursion approach
        base case when n==0: x^0 =1
        for odd x* pow(x*x, (n-1)//2) else pow(x*x, )
        Time - O(log n)
        space = O(log n )

        approach 2
        to do it without stack, iterative method

        '''
        if n ==0:
            return 1

        if n<0:
            n = -n
            x = 1/x
        
        total = 0
        
        if n & 1:
            total = x* self.myPow(x*x, (n-1)//2)
        else:
            total = self.myPow(x*x, n//2)
        return total 
            

    def myPow(self, x: float, n: int) -> float:
        '''
        n can be expressed in binary form 1011
        each x^2^3 * x^2^1 * x^2^0
        x^8 x^2 x^1
        doubling x everytime and including only those numbers for which binary exponent is 1
        '''
        while n <0:
            x = 1/x
            n = -n

        total = 1

        while n>0:
            if n &1:
                total *=x
            x*=x
            n= n>>1

        return total
```

## Attempt 5 · 2023-12-04 21:46 IST · Accepted · Python3

[submission 1112271484](https://leetcode.com/submissions/detail/1112271484/) · tests 306/306 · runtime 39 ms (beats 0.6%)

```python
class Solution:
    def myPow1(self, x: float, n: int) -> float:
        '''
        approach1 
        recursion approach
        base case when n==0: x^0 =1
        for odd x* pow(x*x, (n-1)//2) else pow(x*x, )
        Time - O(log n)
        space = O(log n )

        approach 2
        to do it without stack, iterative method

        '''
        if n ==0:
            return 1

        if n<0:
            n = -n
            x = 1/x
        
        total = 0
        
        if n & 1:
            total = x* self.myPow(x*x, (n-1)//2)
        else:
            total = self.myPow(x*x, n//2)
        return total 
            

    def myPow(self, x: float, n: int) -> float:
        '''
        n can be expressed in binary form 1011
        each x^2^3 * x^2^1 * x^2^0
        x^8 x^2 x^1
        doubling x everytime and including only those numbers for which binary exponent is 1
        '''
        if n <0:
            x = 1/x
            n = -n

        total = 1

        while n>0:
            if n &1:
                total *=x
            x*=x
            n= n>>1

        return total
```

## Attempt 6 · 2025-06-15 00:10 IST · Wrong Answer · C++

[submission 1664150999](https://leetcode.com/submissions/detail/1664150999/) · tests 281/307

Failing input:

```text
-2.00000
2
```

Expected:

```text
4.00000
```

Your output:

```text
-4.00000
```

```cpp
class Solution {
    double pow(double x, int n) {
        if (n==0) return 1;
        if (n==1) return x;

        double ans = pow(x, n/2) * pow(x, n/2);
        if (n &1) ans = ans*x;

        return ans;
    }
public:
    double myPow(double x, int n) {
        double a_x = abs(x);
        int a_n = abs(n);

        double ans = pow(a_x, a_n);
        if (x < 0) ans = ans * -1.0;

        if (n < 0) return 1.0/ans;
        
        return ans;
    }
};
```

## Attempt 7 · 2025-06-15 00:11 IST · Time Limit Exceeded · C++

[submission 1664151958](https://leetcode.com/submissions/detail/1664151958/) · tests 294/307

Failing input:

```text
0.00001
2147483647
```

Expected:

```text
0.00000
```

```cpp
class Solution {
    double pow(double x, int n) {
        if (n==0) return 1;
        if (n==1) return x;

        double ans = pow(x, n/2) * pow(x, n/2);
        if (n &1) ans = ans*x;

        return ans;
    }
public:
    double myPow(double x, int n) {
        double a_x = abs(x);
        int a_n = abs(n);

        double ans = pow(a_x, a_n);
        if (x < 0 & (n&1)) ans = ans * -1.0;

        if (n < 0) return 1.0/ans;

        return ans;
    }
};
```

## Attempt 8 · 2025-06-15 00:16 IST · Runtime Error · C++

[submission 1664155816](https://leetcode.com/submissions/detail/1664155816/) · tests 303/307

Failing input:

```text
1.00000
-2147483648
```

Expected:

```text
1.00000
```

Runtime error:

```text
Line 17: Char 23: runtime error: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:26:23
```

```cpp
class Solution {
    map < pair<double, int>, double> seen;
    double pow(double x, int n) {
        if (n==0) return 1;
        if (n==1) return x;
        if(seen.find({x,n}) != seen.end()) {
            return seen[{x,n}];
        }
        double ans = pow(x, n/2) * pow(x, n/2);
        if (n &1) ans = ans*x;

        return seen[{x,n}] = ans;
    }
public:
    double myPow(double x, int n) {
        double a_x = abs(x);
        int a_n = abs(n);

        double ans = pow(a_x, a_n);
        if (x < 0 && (n&1)) ans = ans * -1.0;

        if (n < 0) return 1.0/ans;

        return ans;
    }
};
```

## Attempt 9 · 2025-06-15 00:18 IST · Accepted · C++

[submission 1664157190](https://leetcode.com/submissions/detail/1664157190/) · tests 307/307 · runtime 4 ms (beats 1.0%)

```cpp
class Solution {
    map < pair<double, long long>, double> seen;
    double pow(double x, long long n) {
        if (n==0) return 1;
        if (n==1) return x;
        if(seen.find({x,n}) != seen.end()) {
            return seen[{x,n}];
        }
        double ans = pow(x, n/2) * pow(x, n/2);
        if (n &1) ans = ans*x;

        return seen[{x,n}] = ans;
    }
public:
    double myPow(double x, int n) {
        double a_x = abs(x);
        long long a_n = abs((long long)n);

        double ans = pow(a_x, a_n);
        if (x < 0 && (n&1)) ans = ans * -1.0;

        if (n < 0) return 1.0/ans;

        return ans;
    }
};
```

## Attempt 10 · 2025-06-15 00:52 IST · Accepted · C++

[submission 1664181690](https://leetcode.com/submissions/detail/1664181690/) · tests 307/307 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    map < pair<double, long long>, double> seen;
    double pow(double x, long long n) {
        if (n==0) return 1;
        if (n==1) return x;
        if(seen.find({x,n}) != seen.end()) {
            return seen[{x,n}];
        }
        double ans = pow(x, n/2) * pow(x, n/2);
        if (n &1) ans = ans*x;

        return seen[{x,n}] = ans;
    }
public:
    double myPow(double x, int n) {
        double a_x = abs(x);
        long long a_n = abs((long long)n);

        // double ans = pow(a_x, a_n);
        // if (x < 0 && (n&1)) ans = ans * -1.0;

        // if (n < 0) return 1.0/ans;

        // return ans;

        if (n==0) return 1.0;
        if (x == 0) return 0;
        if (n == 1) return x;

        if(n < 0) {
            // n = -n;
            x = 1.0/x;
        }

        double ans = 1.0;
        double curr_pow = x;

        while (a_n > 0) {
            if (a_n & 1) {
                ans = ans * curr_pow;
            }
            curr_pow *= curr_pow;
            a_n >>= 1;
        }
        return ans;
    }
};
```
