// SPOILERS: reference solutions for day2.cpp.
#include "../test.h"

// ===== P04 =====
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0, head);
    ListNode* groupPrev = &dummy;
    while (true) {
        ListNode* kth = groupPrev;
        for (int i = 0; i < k && kth; ++i) kth = kth->next;
        if (!kth) break;                                   // fewer than k left
        ListNode* groupNext = kth->next;
        ListNode* prev = groupNext;                        // reversed group's tail connects to groupNext
        ListNode* cur = groupPrev->next;
        while (cur != groupNext) { ListNode* nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
        ListNode* oldHead = groupPrev->next;               // becomes the group's tail
        groupPrev->next = kth;
        groupPrev = oldHead;
    }
    return dummy.next;
}

ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            ListNode* p = head;
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;
        }
    }
    return nullptr;
}

ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0); ListNode* t = &dummy;
    while (a && b) {
        if (a->val <= b->val) { t->next = a; a = a->next; } else { t->next = b; b = b->next; }
        t = t->next;
    }
    t->next = a ? a : b;
    return dummy.next;
}

static ListNode* reverseList(ListNode* h) {
    ListNode* prev = nullptr;
    while (h) { ListNode* n = h->next; h->next = prev; prev = h; h = n; }
    return prev;
}

bool isPalindromeList(ListNode* head) {
    if (!head || !head->next) return true;
    ListNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) { slow = slow->next; fast = fast->next->next; }  // slow = end of 1st half
    ListNode* second = reverseList(slow->next);
    bool ok = true;
    for (ListNode *p = head, *q = second; q; p = p->next, q = q->next)
        if (p->val != q->val) { ok = false; break; }
    slow->next = reverseList(second);                                                     // restore input
    return ok;
}

ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next) return head;
    int len = 1; ListNode* tail = head;
    while (tail->next) { tail = tail->next; ++len; }
    k %= len;
    if (k == 0) return head;
    tail->next = head;                                     // make it circular
    ListNode* newTail = head;
    for (int i = 0; i < len - k - 1; ++i) newTail = newTail->next;
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    return newHead;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);
    ListNode *fast = &dummy, *slow = &dummy;
    for (int i = 0; i <= n; ++i) fast = fast->next;        // gap of n+1
    while (fast) { fast = fast->next; slow = slow->next; }
    slow->next = slow->next->next;                          // (production: delete the removed node)
    return dummy.next;
}

ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
    ListNode dummy(0); ListNode* t = &dummy; int carry = 0;
    while (a || b || carry) {
        int s = carry + (a ? a->val : 0) + (b ? b->val : 0);
        carry = s / 10;
        t->next = new ListNode(s % 10); t = t->next;
        if (a) a = a->next;
        if (b) b = b->next;
    }
    return dummy.next;
}

ListNode* deleteDuplicates(ListNode* head) {
    for (ListNode* cur = head; cur && cur->next;) {
        if (cur->next->val == cur->val) cur->next = cur->next->next;
        else cur = cur->next;
    }
    return head;
}

ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode *slow = head, *fast = head->next;             // fast starts ahead: 2 nodes split 1|1
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    ListNode* right = slow->next; slow->next = nullptr;
    return mergeTwoLists(sortList(head), sortList(right));
}

// ===== P05 =====
bool isValidParens(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') { st.push(c); continue; }
        char want = c == ')' ? '(' : c == ']' ? '[' : '{';
        if (st.empty() || st.top() != want) return false;
        st.pop();
    }
    return st.empty();
}

class MinStack {
    vector<PII> s_;                                        // {value, min so far}
public:
    void push(int x) { s_.push_back({x, s_.empty() ? x : min(x, s_.back().second)}); }
    void pop() { s_.pop_back(); }
    int top() const { return s_.back().first; }
    int getMin() const { return s_.back().second; }
};

VI nextGreater(const VI& a) {
    VI res(a.size(), -1); stack<int> st;                   // indices, values decreasing
    for (int i = 0; i < (int)a.size(); ++i) {
        while (!st.empty() && a[st.top()] < a[i]) { res[st.top()] = a[i]; st.pop(); }
        st.push(i);
    }
    return res;
}

int largestRectangle(const VI& h) {
    stack<int> st; int best = 0, n = (int)h.size();
    for (int i = 0; i <= n; ++i) {
        int cur = (i == n) ? 0 : h[i];                     // sentinel flushes the stack
        while (!st.empty() && h[st.top()] > cur) {
            int height = h[st.top()]; st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            best = max(best, height * width);
        }
        st.push(i);
    }
    return best;
}

VI maxSlidingWindow(const VI& a, int k) {
    deque<int> dq; VI res;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// ===== P06 =====
VVI mergeIntervals(VVI iv) {
    sort(iv.begin(), iv.end());
    VVI res;
    for (auto& cur : iv) {
        if (!res.empty() && cur[0] <= res.back()[1]) res.back()[1] = max(res.back()[1], cur[1]);
        else res.push_back(cur);
    }
    return res;
}

int minMeetingRooms(vector<PII> m) {
    sort(m.begin(), m.end());
    priority_queue<int, VI, greater<int>> ends;             // min-heap of end times
    int best = 0;
    for (auto [s, e] : m) {
        while (!ends.empty() && ends.top() <= s) ends.pop(); // half-open: end == start frees the room
        ends.push(e);
        best = max(best, (int)ends.size());
    }
    return best;
}

int findKthLargest(VI a, int k) {
    priority_queue<int, VI, greater<int>> minh;
    for (int x : a) { minh.push(x); if ((int)minh.size() > k) minh.pop(); }
    return minh.top();
    // alternative O(n) avg: nth_element(a.begin(), a.begin() + k - 1, a.end(), greater<int>()); return a[k-1];
}

ListNode* mergeKLists(vector<ListNode*> lists) {
    auto cmp = [](ListNode* x, ListNode* y) { return x->val > y->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    for (auto* l : lists) if (l) pq.push(l);
    ListNode dummy(0); ListNode* t = &dummy;
    while (!pq.empty()) {
        ListNode* n = pq.top(); pq.pop();
        t->next = n; t = n;
        if (n->next) pq.push(n->next);
    }
    t->next = nullptr;
    return dummy.next;
}

class MedianFinder {
    priority_queue<int> lo_;                                // max-heap: lower half
    priority_queue<int, VI, greater<int>> hi_;              // min-heap: upper half
public:
    void addNum(int x) {
        lo_.push(x);
        hi_.push(lo_.top()); lo_.pop();
        if (hi_.size() > lo_.size()) { lo_.push(hi_.top()); hi_.pop(); }
    }
    double findMedian() const {
        return lo_.size() > hi_.size() ? lo_.top() : (lo_.top() + (double)hi_.top()) / 2.0;
    }
};

bool segmentsIntersect(Seg a, Seg b) {
    auto norm = [](Seg& s) { if (s.x1 > s.x2) swap(s.x1, s.x2); if (s.y1 > s.y2) swap(s.y1, s.y2); };
    norm(a); norm(b);
    auto overlap = [](int l1, int r1, int l2, int r2) { return max(l1, l2) <= min(r1, r2); };
    // for axis-parallel segments, the bounding boxes intersecting is exactly the condition
    return overlap(a.x1, a.x2, b.x1, b.x2) && overlap(a.y1, a.y2, b.y1, b.y2);
}

ll rectOverlapArea(Rect a, Rect b) {
    ll w = max(0, min(a.x2, b.x2) - max(a.x1, b.x1));
    ll h = max(0, min(a.y2, b.y2) - max(a.y1, b.y1));
    return w * h;
}

ll rectUnionArea(const vector<Rect>& rs) {
    VI xs, ys;
    for (auto& r : rs) { xs.push_back(r.x1); xs.push_back(r.x2); ys.push_back(r.y1); ys.push_back(r.y2); }
    sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());
    auto ix = [&](int x) { return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()); };
    auto iy = [&](int y) { return (int)(lower_bound(ys.begin(), ys.end(), y) - ys.begin()); };
    vector<vector<char>> cov(xs.size(), vector<char>(ys.size(), 0));
    for (auto& r : rs)
        for (int i = ix(r.x1); i < ix(r.x2); ++i)
            for (int j = iy(r.y1); j < iy(r.y2); ++j) cov[i][j] = 1;
    ll area = 0;
    for (size_t i = 0; i + 1 < xs.size(); ++i)
        for (size_t j = 0; j + 1 < ys.size(); ++j)
            if (cov[i][j]) area += (ll)(xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
    return area;
    // At scale: sweep over x + segment tree over y (cover count, covered length): O(n log n).
}

// ===== P07 =====
static int depthAndDiameter(TreeNode* n, int& best) {
    if (!n) return 0;
    int L = depthAndDiameter(n->left, best), R = depthAndDiameter(n->right, best);
    best = max(best, L + R);
    return 1 + max(L, R);
}
int diameter(TreeNode* root) { int best = 0; depthAndDiameter(root, best); return best; }

static int balancedHeight(TreeNode* n) {                   // -1 means "unbalanced"
    if (!n) return 0;
    int L = balancedHeight(n->left); if (L < 0) return -1;
    int R = balancedHeight(n->right); if (R < 0) return -1;
    if (abs(L - R) > 1) return -1;
    return 1 + max(L, R);
}
bool isBalanced(TreeNode* root) { return balancedHeight(root) >= 0; }

TreeNode* lca(TreeNode* root, int a, int b) {
    if (!root || root->val == a || root->val == b) return root;
    TreeNode* L = lca(root->left, a, b);
    TreeNode* R = lca(root->right, a, b);
    if (L && R) return root;
    return L ? L : R;
}

static bool rootPath(TreeNode* n, int target, VI& path) {
    if (!n) return false;
    path.push_back(n->val);
    if (n->val == target) return true;
    if (rootPath(n->left, target, path) || rootPath(n->right, target, path)) return true;
    path.pop_back();                                        // backtrack
    return false;
}
VI pathBetween(TreeNode* root, int a, int b) {
    VI pa, pb;
    if (!rootPath(root, a, pa) || !rootPath(root, b, pb)) return {};
    size_t i = 0;                                           // length of the common prefix
    while (i < pa.size() && i < pb.size() && pa[i] == pb[i]) ++i;
    VI res(pa.rbegin(), pa.rend() - (i - 1));               // a ... up to LCA (pa[i-1])
    res.insert(res.end(), pb.begin() + i, pb.end());        // below LCA ... b
    return res;
}

static bool validBST(TreeNode* n, ll lo, ll hi) {
    if (!n) return true;
    if (n->val <= lo || n->val >= hi) return false;
    return validBST(n->left, lo, n->val) && validBST(n->right, n->val, hi);
}
bool isValidBST(TreeNode* root) { return validBST(root, LLONG_MIN, LLONG_MAX); }

int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> st; TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur = cur->left; }
        cur = st.top(); st.pop();
        if (--k == 0) return cur->val;
        cur = cur->right;
    }
    return -1;
}

string serialize(TreeNode* root) {
    string out;
    function<void(TreeNode*)> go = [&](TreeNode* n) {
        if (!n) { out += "#,"; return; }
        out += to_string(n->val) + ",";
        go(n->left); go(n->right);
    };
    go(root);
    return out;
}
TreeNode* deserialize(const string& s) {
    stringstream ss(s); string tok;
    function<TreeNode*()> go = [&]() -> TreeNode* {
        if (!getline(ss, tok, ',') || tok == "#") return nullptr;
        TreeNode* n = new TreeNode(stoi(tok));
        n->left = go(); n->right = go();
        return n;
    };
    return go();
}

TreeNode* buildTree(const VI& pre, const VI& in) {
    unordered_map<int, int> pos;
    for (int i = 0; i < (int)in.size(); ++i) pos[in[i]] = i;
    int p = 0;
    function<TreeNode*(int, int)> go = [&](int l, int r) -> TreeNode* {
        if (l > r) return nullptr;
        TreeNode* n = new TreeNode(pre[p++]);
        int m = pos[n->val];
        n->left = go(l, m - 1);
        n->right = go(m + 1, r);
        return n;
    };
    return go(0, (int)in.size() - 1);
}

TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left); invertTree(root->right);
    return root;
}

// ===== P12 =====
class LRUCache {
public:
    explicit LRUCache(int capacity) : cap_(capacity) {}
    int get(int key) {
        auto it = pos_.find(key);
        if (it == pos_.end()) return -1;
        order_.splice(order_.begin(), order_, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        if (cap_ <= 0) return;
        if (auto it = pos_.find(key); it != pos_.end()) {
            it->second->second = value;
            order_.splice(order_.begin(), order_, it->second);
            return;
        }
        if ((int)order_.size() == cap_) { pos_.erase(order_.back().first); order_.pop_back(); }
        order_.emplace_front(key, value);
        pos_[key] = order_.begin();
    }
private:
    int cap_;
    list<PII> order_;                                        // front = most recently used
    unordered_map<int, list<PII>::iterator> pos_;
};

// ===== MM03 =====
// Walls by "walk with jumps": left[i] = previous strictly smaller, right[i] = next smaller-or-equal.
long long sumSubarrayMins(const VI& a) {
    int n = (int)a.size(); VI left(n), right(n);
    for (int i = 0; i < n; ++i) { int L = i - 1; while (L >= 0 && a[L] >= a[i]) L = left[L]; left[i] = L; }
    for (int i = n - 1; i >= 0; --i) { int R = i + 1; while (R < n && a[R] > a[i]) R = right[R]; right[i] = R; }
    long long total = 0;
    for (int i = 0; i < n; ++i) total += (long long)a[i] * (i - left[i]) * (right[i] - i);
    return total;
}
static long long sumSubarrayMaxs(const VI& a) {                // same, comparisons flipped
    int n = (int)a.size(); VI left(n), right(n);
    for (int i = 0; i < n; ++i) { int L = i - 1; while (L >= 0 && a[L] <= a[i]) L = left[L]; left[i] = L; }
    for (int i = n - 1; i >= 0; --i) { int R = i + 1; while (R < n && a[R] < a[i]) R = right[R]; right[i] = R; }
    long long total = 0;
    for (int i = 0; i < n; ++i) total += (long long)a[i] * (i - left[i]) * (right[i] - i);
    return total;
}
long long subArrayRanges(const VI& a) { return sumSubarrayMaxs(a) - sumSubarrayMins(a); }

#include "../tests/day2_tests.h"
