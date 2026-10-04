// DAY 2: Linked lists, Stack/Monotonic, Heaps/Intervals/Geometry, Trees/BST, LRU
// Patterns: 02-Patterns/P04, P05, P06, P07, P12.
// Build: g++ -std=c++20 -O1 -g -fsanitize=address,undefined day2.cpp -o day2 && ./day2 [filter]
// ★ = do first. Target: 10–15 min each.
//
// LINKED LISTS: the tests own every node. RELINK ONLY; don't `delete` nodes you remove
// (say in the interview that production code would free or recycle them).
#include "test.h"

// ===== P04 Linked lists =====
// ★ P04-2  Reverse nodes in groups of k; a leftover group (< k nodes) stays as is.
ListNode* reverseKGroup(ListNode* head, int k) {
    return head;
}
// P04-3  Node where the cycle begins, or nullptr.
ListNode* detectCycle(ListNode* head) {
    return nullptr;
}
// ★ P04-4  Merge two sorted lists by relinking (no new nodes).
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    return nullptr;
}
// P04-5  O(n) time, O(1) extra space. (Bonus: restore the list before returning.)
bool isPalindromeList(ListNode* head) {
    return false;
}
// ★ P04-6  Rotate right by k.
ListNode* rotateRight(ListNode* head, int k) {
    return head;
}
// P04-7  Remove the n-th node from the end (n is valid).
ListNode* removeNthFromEnd(ListNode* head, int n) {
    return head;
}
// P04-8  Digits stored in reverse order; return a NEW list (allocate with new; the tests free it).
ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
    return nullptr;
}
// ★ P04-9  Sorted list: keep one copy of each value.
ListNode* deleteDuplicates(ListNode* head) {
    return head;
}
// P04-10  Sort in O(n log n).
ListNode* sortList(ListNode* head) {
    return head;
}

// ===== P05 Stacks =====
// ★ P05-1
bool isValidParens(const string& s) {
    return false;
}
// P05-2  All operations O(1).
class MinStack {
public:
    void push(int x) {}
    void pop() {}
    int top() const { return 0; }
    int getMin() const { return 0; }
};
// ★ P05-3  Next greater VALUE to the right for each element, else -1.
VI nextGreater(const VI& a) {
    return {};
}
// P05-4  Largest rectangle in a histogram.
int largestRectangle(const VI& h) {
    return 0;
}
// P05-5  Max of each window of size k.
VI maxSlidingWindow(const VI& a, int k) {
    return {};
}

// ===== P06 Heaps, intervals, geometry =====
// ★ P06-1  Merge overlapping intervals (touching [1,4],[4,5] DO merge). Output sorted by start.
VVI mergeIntervals(VVI iv) {
    return {};
}
// ★ P06-2  Min rooms; meetings are half-open [start, end): one ending at t frees a room for one starting at t.
int minMeetingRooms(vector<PII> m) {
    return 0;
}
// P06-3  k-th largest element.
int findKthLargest(VI a, int k) {
    return 0;
}
// P06-4  Merge k sorted lists (relink only).
ListNode* mergeKLists(vector<ListNode*> lists) {
    return nullptr;
}
// P06-5  Running median.
class MedianFinder {
public:
    void addNum(int x) {}
    double findMedian() const { return 0.0; }
};
// ★ P06-7  (Cadence R1) Axis-parallel segments (endpoints in any order). Touching counts as intersecting.
bool segmentsIntersect(Seg a, Seg b) {
    return false;
}
// P06-8a  Overlap area of two rectangles (0 if they only touch or are disjoint).
ll rectOverlapArea(Rect a, Rect b) {
    return 0;
}
// P06-8b  Area covered by the union of rectangles (n <= 200).
ll rectUnionArea(const vector<Rect>& rs) {
    return 0;
}

// ===== P07 Trees =====
// P07-2  Diameter in EDGES.
int diameter(TreeNode* root) {
    return 0;
}
// ★ P07-3  Height-balanced? O(n).
bool isBalanced(TreeNode* root) {
    return false;
}
// ★ P07-4  LCA (both values exist, values are unique).
TreeNode* lca(TreeNode* root, int a, int b) {
    return nullptr;
}
// ★ P07-5  (Cadence R1) Values on the path from a to b, inclusive. {} if either is missing.
VI pathBetween(TreeNode* root, int a, int b) {
    return {};
}
// ★ P07-6  Strict BST (no duplicates).
bool isValidBST(TreeNode* root) {
    return false;
}
// P07-7  k-th smallest (1-based) in a BST.
int kthSmallest(TreeNode* root, int k) {
    return 0;
}
// P07-8  Any format you like; deserialize(serialize(t)) must rebuild the same tree.
string serialize(TreeNode* root) {
    return "";
}
TreeNode* deserialize(const string& s) {
    return nullptr;
}
// P07-9  Build from preorder + inorder (distinct values).
TreeNode* buildTree(const VI& pre, const VI& in) {
    return nullptr;
}
// P07-10  Mirror the tree in place; return the root.
TreeNode* invertTree(TreeNode* root) {
    return root;
}

// ===== P12 Design =====
// ★ P12-1  LRU cache: O(1) get/put. get returns -1 if missing.
class LRUCache {
public:
    explicit LRUCache(int capacity) {}
    int get(int key) { return -1; }
    void put(int key, int value) {}
};

// ===== MM03 The flip (contribution technique) =====
// ★ MM03-1  Sum of min(subarray) over all subarrays (LC 907, without the modulo).
//   Suggested order: walls by walking (O(n^2)) → change the walk to jumps (O(n)) → optionally a stack.
long long sumSubarrayMins(const VI& a) {
    return 0;
}
// ★ MM03-2  Sum of (max - min) over all subarrays (LC 2104). Values may be negative.
long long subArrayRanges(const VI& a) {
    return 0;
}

#include "tests/day2_tests.h"
