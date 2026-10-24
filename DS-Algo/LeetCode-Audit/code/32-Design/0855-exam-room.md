# 855. Exam Room

[Problem](https://leetcode.com/problems/exam-room/) · Medium · Design → Ordered set of seats

LeetCode tags: design, heap-priority-queue, ordered-set

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-03-30 23:14 IST · Accepted · C++

[submission 924960225](https://leetcode.com/submissions/detail/924960225/) · tests 126/126 · runtime 55 ms (beats 76.5%)

```cpp
// class ExamRoom {
// public:
//     int n;
//     set<int> seats;
//     map<int,int> seatMap;
//     ExamRoom(int _n) {
//         n = _n;
//     }
    
//     int seat() {
//         // find the largest gap, if multiple chose with lower index
//         // some sort of binary search required for finding empty gaps
//     }
    
//     void leave(int p) {
        
//     }
// };
struct IntV
{
    static int N;
    int l, r;
    IntV(int l, int r) : l(l), r(r) {}
    int getD() const
    {
        if(l == 0) return r;
        if(r == N - 1) return N - 1 - l;
        if(r < l) return -1;
        else return (r - l) / 2;
    }
    int getP() const
    {
        if(l == 0) return 0;
        if(r == N - 1) return N - 1;
        else return l + (r - l) / 2;
    }
    bool operator < (const IntV& a) const
    {
        int d1 = getD(), d2 = a.getD();
        if(d1 != d2) return d1 > d2;
        return l < a.l;
    }
};

int IntV :: N = 0;

class ExamRoom {
public:
    set<IntV> tab;
    map<int, int> l2r, r2l;
    
    ExamRoom(int N)
    {
        IntV :: N = N;
        tab.clear(); l2r.clear(); r2l.clear();
        tab.insert(IntV(0, N - 1));
        l2r[0] = N - 1;
        r2l[N - 1] = 0;
    }
    
    int seat()
    {
        IntV cur = *(tab.begin());
        tab.erase(tab.begin());
        
        int pos = cur.getP();
        tab.insert(IntV(cur.l, pos - 1));
        tab.insert(IntV(pos + 1, cur.r));
        l2r[cur.l] = pos - 1; r2l[pos - 1] = cur.l;
        l2r[pos + 1] = cur.r; r2l[cur.r] = pos + 1;
        return pos;
    }
    
    void leave(int p)
    {
        int l = r2l[p - 1], r = l2r[p + 1];
        tab.erase(IntV(l, p - 1));
        tab.erase(IntV(p + 1, r));
        tab.insert(IntV(l, r));
        l2r[l] = r; r2l[r] = l;
        r2l.erase(p - 1); l2r.erase(p + 1);
    }
};
/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */
```
