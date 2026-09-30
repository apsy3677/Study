// test.h: a tiny test harness + the shared problem types for the practice files.
// You don't need to edit this file.
#pragma once
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <chrono>
#include <climits>
#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using VI = vector<int>;
using VVI = vector<vector<int>>;
using VS = vector<string>;
using PII = pair<int, int>;

// ---------------- shared problem types ----------------
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(int v) : val(v) {}
};

struct Seg { int x1, y1, x2, y2; };     // axis-parallel segment, endpoints in any order
struct Rect { int x1, y1, x2, y2; };    // x1 < x2, y1 < y2 (lower-left, upper-right)

// ---------------- helpers for tests ----------------
namespace tst {
inline int passed = 0, failed = 0;
inline string filter;                    // run only sections whose name contains this

template <class T> string show(const T& v);
template <class A, class B> string show(const pair<A, B>& p);
template <class T> string show(const vector<T>& v);
template <class T> string show(const optional<T>& v);
inline string show(const string& s) { return "\"" + s + "\""; }
inline string show(const char* s) { return show(string(s)); }
inline string show(bool b) { return b ? "true" : "false"; }

template <class T> string show(const T& v) { ostringstream os; os << v; return os.str(); }
template <class A, class B> string show(const pair<A, B>& p) { return "(" + show(p.first) + ", " + show(p.second) + ")"; }
template <class T> string show(const vector<T>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); ++i) { if (i) s += ", "; s += show(v[i]); if (i >= 40) { s += ", ..."; break; } }
    return s + "]";
}
template <class T> string show(const optional<T>& v) { return v ? show(*v) : string("nullopt"); }

inline void section(const char* name, void (*fn)()) {
    if (!filter.empty() && string(name).find(filter) == string::npos) return;
    cout << "-- " << name << "\n";
    int p0 = passed, f0 = failed;
    fn();
    int p = passed - p0, f = failed - f0;
    cout << (f == 0 ? "   [PASS] " : "   [FAIL] ") << name << "  " << p << "/" << (p + f) << endl;  // flush: sanitizers may _exit
}

inline int summary(const char* file) {
    cout << "\n==== " << file << ": " << passed << " passed, " << failed << " failed ====" << endl;
    return failed == 0 ? 0 : 1;
}

// linked-list helpers
inline ListNode* makeList(const VI& v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
inline VI toVec(ListNode* h, size_t limit = 100000) {
    VI v; while (h && v.size() < limit) { v.push_back(h->val); h = h->next; }
    return v;
}
inline void freeList(ListNode* h, size_t limit = 100000) {
    while (h && limit--) { ListNode* n = h->next; delete h; h = n; }
}
// Owns every node it creates, so tests stay leak-free even if your code relinks/drops nodes.
// (That's why the list problems say: relink only, don't delete nodes you remove.)
struct ListArena {
    vector<ListNode*> nodes;
    ListNode* make(const VI& v) {
        ListNode dummy(0); ListNode* t = &dummy;
        for (int x : v) { t->next = new ListNode(x); nodes.push_back(t->next); t = t->next; }
        return dummy.next;
    }
    ~ListArena() { for (auto* n : nodes) delete n; }
};
inline ListNode* nth(ListNode* h, int i) { while (h && i--) h = h->next; return h; }

// tree helpers: level-order with NUL as "no node" (LeetCode style)
constexpr int NUL = INT_MIN;
inline TreeNode* makeTree(const VI& v) {
    if (v.empty() || v[0] == NUL) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q; q.push(root); size_t i = 1;
    while (!q.empty() && i < v.size()) {
        TreeNode* n = q.front(); q.pop();
        if (i < v.size() && v[i] != NUL) { n->left = new TreeNode(v[i]); q.push(n->left); } ++i;
        if (i < v.size() && v[i] != NUL) { n->right = new TreeNode(v[i]); q.push(n->right); } ++i;
    }
    return root;
}
inline void freeTree(TreeNode* r) { if (!r) return; freeTree(r->left); freeTree(r->right); delete r; }
inline VI inorder(TreeNode* r) { VI out; function<void(TreeNode*)> go = [&](TreeNode* n) { if (!n) return; go(n->left); out.push_back(n->val); go(n->right); }; go(r); return out; }
inline VI preorder(TreeNode* r) { VI out; function<void(TreeNode*)> go = [&](TreeNode* n) { if (!n) return; out.push_back(n->val); go(n->left); go(n->right); }; go(r); return out; }
inline TreeNode* findNode(TreeNode* r, int v) { if (!r) return nullptr; if (r->val == v) return r; if (auto* L = findNode(r->left, v)) return L; return findNode(r->right, v); }

template <class T> void sortAll(vector<vector<T>>& v) { for (auto& x : v) sort(x.begin(), x.end()); sort(v.begin(), v.end()); }

// object that counts constructions/destructions (for smart pointer / vector / pool tests)
struct Counted {
    static inline int alive = 0, copies = 0, moves = 0;
    int v;
    explicit Counted(int x = 0) : v(x) { ++alive; }
    Counted(const Counted& o) : v(o.v) { ++alive; ++copies; }
    Counted(Counted&& o) noexcept : v(o.v) { ++alive; ++moves; }
    Counted& operator=(const Counted& o) { v = o.v; ++copies; return *this; }
    Counted& operator=(Counted&& o) noexcept { v = o.v; ++moves; return *this; }
    ~Counted() { --alive; }
    static void reset() { alive = copies = moves = 0; }
};
}  // namespace tst

#define CHECK(cond)                                                                   \
    do {                                                                              \
        if (cond) ++tst::passed;                                                      \
        else { ++tst::failed; std::cout << "   FAIL line " << __LINE__ << ": " #cond "\n"; } \
    } while (0)

#define CHECK_EQ(actual, expected)                                                    \
    do {                                                                              \
        auto&& a_ = (actual);                                                         \
        auto&& e_ = (expected);                                                       \
        if (a_ == e_) ++tst::passed;                                                  \
        else {                                                                        \
            ++tst::failed;                                                            \
            std::cout << "   FAIL line " << __LINE__ << ": " #actual "\n"             \
                      << "        got:      " << tst::show(a_) << "\n"                \
                      << "        expected: " << tst::show(e_) << "\n";              \
        }                                                                             \
    } while (0)

#define SECTION(fn) tst::section(#fn, fn)
