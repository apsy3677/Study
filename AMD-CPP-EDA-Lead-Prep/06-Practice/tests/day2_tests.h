// Tests for day2. Included at the end of day2.cpp (and solutions/day2_sol.cpp).
#pragma once
#include "../test.h"
using tst::ListArena;
using tst::NUL;

// ---------- P04 ----------
static void t_reverseKGroup() {
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2, 3, 4, 5}), 2)), (VI{2, 1, 4, 3, 5})); }
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2, 3, 4, 5}), 3)), (VI{3, 2, 1, 4, 5})); }
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2, 3, 4, 5}), 1)), (VI{1, 2, 3, 4, 5})); }
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2, 3, 4, 5}), 5)), (VI{5, 4, 3, 2, 1})); }
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2}), 3)), (VI{1, 2})); }
    { ListArena A; CHECK_EQ(tst::toVec(reverseKGroup(A.make({1, 2, 3, 4, 5, 6}), 2)), (VI{2, 1, 4, 3, 6, 5})); }
}
static void t_detectCycle() {
    { ListArena A; ListNode* h = A.make({3, 2, 0, -4}); tst::nth(h, 3)->next = tst::nth(h, 1);
      CHECK(detectCycle(h) == tst::nth(h, 1)); }
    { ListArena A; ListNode* h = A.make({1, 2}); tst::nth(h, 1)->next = h;
      CHECK(detectCycle(h) == h); }
    { ListArena A; ListNode* h = A.make({1}); h->next = h; CHECK(detectCycle(h) == h); }
    { ListArena A; ListNode* h = A.make({1, 2, 3}); CHECK(detectCycle(h) == nullptr); }
    CHECK(detectCycle(nullptr) == nullptr);
}
static void t_mergeTwoLists() {
    { ListArena A; CHECK_EQ(tst::toVec(mergeTwoLists(A.make({1, 2, 4}), A.make({1, 3, 4}))), (VI{1, 1, 2, 3, 4, 4})); }
    { ListArena A; CHECK_EQ(tst::toVec(mergeTwoLists(A.make({}), A.make({}))), (VI{})); }
    { ListArena A; CHECK_EQ(tst::toVec(mergeTwoLists(A.make({}), A.make({0}))), (VI{0})); }
    { ListArena A; CHECK_EQ(tst::toVec(mergeTwoLists(A.make({5}), A.make({1, 2, 3}))), (VI{1, 2, 3, 5})); }
}
static void t_isPalindromeList() {
    { ListArena A; CHECK(isPalindromeList(A.make({1, 2, 2, 1}))); }
    { ListArena A; CHECK(!isPalindromeList(A.make({1, 2}))); }
    { ListArena A; CHECK(isPalindromeList(A.make({1}))); }
    { ListArena A; CHECK(isPalindromeList(A.make({}))); }
    { ListArena A; CHECK(isPalindromeList(A.make({1, 2, 3, 2, 1}))); }
    { ListArena A; CHECK(!isPalindromeList(A.make({1, 2, 3, 1}))); }
}
static void t_rotateRight() {
    { ListArena A; CHECK_EQ(tst::toVec(rotateRight(A.make({1, 2, 3, 4, 5}), 2)), (VI{4, 5, 1, 2, 3})); }
    { ListArena A; CHECK_EQ(tst::toVec(rotateRight(A.make({0, 1, 2}), 4)), (VI{2, 0, 1})); }
    { ListArena A; CHECK_EQ(tst::toVec(rotateRight(A.make({}), 3)), (VI{})); }
    { ListArena A; CHECK_EQ(tst::toVec(rotateRight(A.make({1, 2}), 2)), (VI{1, 2})); }
    { ListArena A; CHECK_EQ(tst::toVec(rotateRight(A.make({1, 2, 3}), 0)), (VI{1, 2, 3})); }
}
static void t_removeNthFromEnd() {
    { ListArena A; CHECK_EQ(tst::toVec(removeNthFromEnd(A.make({1, 2, 3, 4, 5}), 2)), (VI{1, 2, 3, 5})); }
    { ListArena A; CHECK_EQ(tst::toVec(removeNthFromEnd(A.make({1}), 1)), (VI{})); }
    { ListArena A; CHECK_EQ(tst::toVec(removeNthFromEnd(A.make({1, 2}), 1)), (VI{1})); }
    { ListArena A; CHECK_EQ(tst::toVec(removeNthFromEnd(A.make({1, 2}), 2)), (VI{2})); }
}
static void t_addTwoNumbers() {
    auto run = [](const VI& x, const VI& y) {
        ListArena A; ListNode* r = addTwoNumbers(A.make(x), A.make(y));
        VI v = tst::toVec(r); tst::freeList(r); return v;
    };
    CHECK_EQ(run({2, 4, 3}, {5, 6, 4}), (VI{7, 0, 8}));
    CHECK_EQ(run({0}, {0}), (VI{0}));
    CHECK_EQ(run({9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9}), (VI{8, 9, 9, 9, 0, 0, 0, 1}));
}
static void t_deleteDuplicates() {
    { ListArena A; CHECK_EQ(tst::toVec(deleteDuplicates(A.make({1, 1, 2}))), (VI{1, 2})); }
    { ListArena A; CHECK_EQ(tst::toVec(deleteDuplicates(A.make({1, 1, 2, 3, 3}))), (VI{1, 2, 3})); }
    { ListArena A; CHECK_EQ(tst::toVec(deleteDuplicates(A.make({}))), (VI{})); }
    { ListArena A; CHECK_EQ(tst::toVec(deleteDuplicates(A.make({7, 7, 7}))), (VI{7})); }
}
static void t_sortList() {
    { ListArena A; CHECK_EQ(tst::toVec(sortList(A.make({4, 2, 1, 3}))), (VI{1, 2, 3, 4})); }
    { ListArena A; CHECK_EQ(tst::toVec(sortList(A.make({-1, 5, 3, 4, 0}))), (VI{-1, 0, 3, 4, 5})); }
    { ListArena A; CHECK_EQ(tst::toVec(sortList(A.make({}))), (VI{})); }
    { ListArena A; CHECK_EQ(tst::toVec(sortList(A.make({2, 1}))), (VI{1, 2})); }
}

// ---------- P05 ----------
static void t_isValidParens() {
    CHECK(isValidParens("()"));
    CHECK(isValidParens("()[]{}"));
    CHECK(!isValidParens("(]"));
    CHECK(!isValidParens("([)]"));
    CHECK(isValidParens("{[]}"));
    CHECK(!isValidParens("("));
    CHECK(!isValidParens(")"));
    CHECK(isValidParens(""));
}
static void t_MinStack() {
    MinStack s;
    s.push(-2); s.push(0); s.push(-3);
    CHECK_EQ(s.getMin(), -3);
    s.pop();
    CHECK_EQ(s.top(), 0);
    CHECK_EQ(s.getMin(), -2);
    MinStack t;
    t.push(1); t.push(1); t.pop();
    CHECK_EQ(t.getMin(), 1);
    t.push(0); t.push(2);
    CHECK_EQ(t.getMin(), 0);
}
static void t_nextGreater() {
    CHECK_EQ(nextGreater({4, 5, 2, 25}), (VI{5, 25, 25, -1}));
    CHECK_EQ(nextGreater({13, 7, 6, 12}), (VI{-1, 12, 12, -1}));
    CHECK_EQ(nextGreater({}), (VI{}));
    CHECK_EQ(nextGreater({2, 2, 3}), (VI{3, 3, -1}));
}
static void t_largestRectangle() {
    CHECK_EQ(largestRectangle({2, 1, 5, 6, 2, 3}), 10);
    CHECK_EQ(largestRectangle({2, 4}), 4);
    CHECK_EQ(largestRectangle({}), 0);
    CHECK_EQ(largestRectangle({1, 1, 1, 1}), 4);
    CHECK_EQ(largestRectangle({6, 2, 5, 4, 5, 1, 6}), 12);
}
static void t_maxSlidingWindow() {
    CHECK_EQ(maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3), (VI{3, 3, 5, 5, 6, 7}));
    CHECK_EQ(maxSlidingWindow({1}, 1), (VI{1}));
    CHECK_EQ(maxSlidingWindow({9, 8, 7, 6}, 2), (VI{9, 8, 7}));
    CHECK_EQ(maxSlidingWindow({1, 3, 1, 2, 0, 5}, 3), (VI{3, 3, 2, 5}));
}

// ---------- P06 ----------
static void t_mergeIntervals() {
    CHECK_EQ(mergeIntervals({{1, 3}, {2, 6}, {8, 10}, {15, 18}}), (VVI{{1, 6}, {8, 10}, {15, 18}}));
    CHECK_EQ(mergeIntervals({{1, 4}, {4, 5}}), (VVI{{1, 5}}));
    CHECK_EQ(mergeIntervals({{1, 4}, {2, 3}}), (VVI{{1, 4}}));
    CHECK_EQ(mergeIntervals({{8, 10}, {1, 3}, {2, 6}}), (VVI{{1, 6}, {8, 10}}));
    CHECK_EQ(mergeIntervals({}), (VVI{}));
}
static void t_minMeetingRooms() {
    CHECK_EQ(minMeetingRooms({{0, 30}, {5, 10}, {15, 20}}), 2);
    CHECK_EQ(minMeetingRooms({{7, 10}, {2, 4}}), 1);
    CHECK_EQ(minMeetingRooms({{1, 5}, {5, 10}}), 1);
    CHECK_EQ(minMeetingRooms({{1, 10}, {2, 3}, {3, 4}, {4, 5}}), 2);
    CHECK_EQ(minMeetingRooms({}), 0);
    CHECK_EQ(minMeetingRooms({{1, 4}, {1, 4}, {1, 4}}), 3);
}
static void t_findKthLargest() {
    CHECK_EQ(findKthLargest({3, 2, 1, 5, 6, 4}, 2), 5);
    CHECK_EQ(findKthLargest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4), 4);
    CHECK_EQ(findKthLargest({1}, 1), 1);
}
static void t_mergeKLists() {
    { ListArena A; CHECK_EQ(tst::toVec(mergeKLists({A.make({1, 4, 5}), A.make({1, 3, 4}), A.make({2, 6})})), (VI{1, 1, 2, 3, 4, 4, 5, 6})); }
    { CHECK_EQ(tst::toVec(mergeKLists({})), (VI{})); }
    { CHECK_EQ(tst::toVec(mergeKLists({nullptr, nullptr})), (VI{})); }
}
static void t_MedianFinder() {
    MedianFinder m;
    m.addNum(1); m.addNum(2);
    CHECK_EQ(m.findMedian(), 1.5);
    m.addNum(3);
    CHECK_EQ(m.findMedian(), 2.0);
    m.addNum(4);
    CHECK_EQ(m.findMedian(), 2.5);
    MedianFinder n;
    n.addNum(-5); n.addNum(10); n.addNum(-20);
    CHECK_EQ(n.findMedian(), -5.0);
}
static void t_segmentsIntersect() {
    CHECK(segmentsIntersect({0, 0, 4, 0}, {2, -1, 2, 3}));     // H x V crossing
    CHECK(!segmentsIntersect({0, 0, 4, 0}, {5, -1, 5, 3}));    // V to the right
    CHECK(segmentsIntersect({0, 0, 4, 0}, {4, 0, 4, 5}));      // touching at an endpoint
    CHECK(segmentsIntersect({0, 0, 3, 0}, {2, 0, 5, 0}));      // collinear H overlap
    CHECK(!segmentsIntersect({0, 0, 1, 0}, {2, 0, 3, 0}));     // collinear H, disjoint
    CHECK(!segmentsIntersect({0, 0, 3, 0}, {0, 1, 3, 1}));     // parallel H, different y
    CHECK(segmentsIntersect({1, 5, 1, 2}, {1, 3, 1, 9}));      // collinear V, reversed endpoints
    CHECK(!segmentsIntersect({2, 1, 2, 3}, {0, 5, 4, 5}));     // H above V
    CHECK(segmentsIntersect({4, 0, 0, 0}, {2, 3, 2, -1}));     // reversed endpoints both
    CHECK(!segmentsIntersect({0, 0, 2, 0}, {3, 0, 3, 2}));     // V just past the H end
}
static void t_rectOverlapArea() {
    CHECK_EQ(rectOverlapArea({0, 0, 4, 4}, {2, 2, 6, 6}), 4LL);
    CHECK_EQ(rectOverlapArea({0, 0, 1, 1}, {2, 2, 3, 3}), 0LL);
    CHECK_EQ(rectOverlapArea({0, 0, 2, 2}, {2, 0, 4, 2}), 0LL);
    CHECK_EQ(rectOverlapArea({0, 0, 10, 10}, {2, 2, 3, 3}), 1LL);
    CHECK_EQ(rectOverlapArea({-3, -3, 3, 3}, {0, -10, 1, 10}), 6LL);
}
static void t_rectUnionArea() {
    CHECK_EQ(rectUnionArea({{0, 0, 2, 2}, {1, 1, 3, 3}}), 7LL);
    CHECK_EQ(rectUnionArea({{0, 0, 1, 1}, {2, 2, 3, 3}}), 2LL);
    CHECK_EQ(rectUnionArea({{0, 0, 2, 2}, {0, 0, 2, 2}}), 4LL);
    CHECK_EQ(rectUnionArea({{0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1}}), 6LL);
    CHECK_EQ(rectUnionArea({}), 0LL);
    CHECK_EQ(rectUnionArea({{0, 0, 1000000000, 1000000000}}), 1000000000000000000LL);
}

// ---------- P07 ----------
static const VI kTree = {3, 5, 1, 6, 2, 0, 8, NUL, NUL, 7, 4};
static void t_diameter() {
    auto run = [](const VI& v) { TreeNode* t = tst::makeTree(v); int d = diameter(t); tst::freeTree(t); return d; };
    CHECK_EQ(run({1, 2, 3, 4, 5}), 3);
    CHECK_EQ(run({1, 2}), 1);
    CHECK_EQ(run({}), 0);
    CHECK_EQ(run({1, 2, NUL, 3, 4, 5, NUL, NUL, 6}), 4);
}
static void t_isBalanced() {
    auto run = [](const VI& v) { TreeNode* t = tst::makeTree(v); bool b = isBalanced(t); tst::freeTree(t); return b; };
    CHECK(run({3, 9, 20, NUL, NUL, 15, 7}));
    CHECK(!run({1, 2, 2, 3, 3, NUL, NUL, 4, 4}));
    CHECK(run({}));
    CHECK(!run({1, NUL, 2, NUL, 3}));
}
static void t_lca() {
    TreeNode* t = tst::makeTree(kTree);
    auto val = [](TreeNode* n) { return n ? n->val : -999; };
    CHECK_EQ(val(lca(t, 5, 1)), 3);
    CHECK_EQ(val(lca(t, 5, 4)), 5);
    CHECK_EQ(val(lca(t, 7, 8)), 3);
    CHECK_EQ(val(lca(t, 6, 4)), 5);
    CHECK_EQ(val(lca(t, 7, 4)), 2);
    tst::freeTree(t);
}
static void t_pathBetween() {
    TreeNode* t = tst::makeTree(kTree);
    CHECK_EQ(pathBetween(t, 7, 8), (VI{7, 2, 5, 3, 1, 8}));
    CHECK_EQ(pathBetween(t, 5, 4), (VI{5, 2, 4}));
    CHECK_EQ(pathBetween(t, 4, 6), (VI{4, 2, 5, 6}));
    CHECK_EQ(pathBetween(t, 6, 6), (VI{6}));
    CHECK_EQ(pathBetween(t, 6, 99), (VI{}));
    tst::freeTree(t);
}
static void t_isValidBST() {
    auto run = [](const VI& v) { TreeNode* t = tst::makeTree(v); bool b = isValidBST(t); tst::freeTree(t); return b; };
    CHECK(run({2, 1, 3}));
    CHECK(!run({5, 1, 4, NUL, NUL, 3, 6}));
    CHECK(!run({5, 4, 6, NUL, NUL, 3, 7}));        // grandchild violates the root bound
    CHECK(run({2147483647}));
    CHECK(!run({1, 1}));
    CHECK(run({}));
}
static void t_kthSmallest() {
    auto run = [](const VI& v, int k) { TreeNode* t = tst::makeTree(v); int r = kthSmallest(t, k); tst::freeTree(t); return r; };
    CHECK_EQ(run({3, 1, 4, NUL, 2}, 1), 1);
    CHECK_EQ(run({5, 3, 6, 2, 4, NUL, NUL, 1}, 3), 3);
    CHECK_EQ(run({5, 3, 6, 2, 4, NUL, NUL, 1}, 6), 6);
}
static void t_serialize() {
    for (const VI& v : {VI{1, 2, 3, NUL, NUL, 4, 5}, VI{}, VI{-1, -2, NUL, -3}, VI{10, NUL, 20, NUL, 30}}) {
        TreeNode* t = tst::makeTree(v);
        TreeNode* r = deserialize(serialize(t));
        CHECK_EQ(tst::preorder(r), tst::preorder(t));
        CHECK_EQ(tst::inorder(r), tst::inorder(t));
        tst::freeTree(t); tst::freeTree(r);
    }
}
static void t_buildTree() {
    TreeNode* r = buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
    CHECK_EQ(tst::preorder(r), (VI{3, 9, 20, 15, 7}));
    CHECK_EQ(tst::inorder(r), (VI{9, 3, 15, 20, 7}));
    CHECK(r && r->right && r->right->val == 20);
    tst::freeTree(r);
    TreeNode* e = buildTree({}, {});
    CHECK(e == nullptr);
}
static void t_invertTree() {
    TreeNode* t = tst::makeTree({4, 2, 7, 1, 3, 6, 9});
    t = invertTree(t);
    CHECK_EQ(tst::inorder(t), (VI{9, 7, 6, 4, 3, 2, 1}));
    CHECK(t && t->left && t->left->val == 7);
    tst::freeTree(t);
    CHECK(invertTree(nullptr) == nullptr);
}

// ---------- P12 ----------
static void t_LRUCache() {
    LRUCache c(2);
    c.put(1, 1); c.put(2, 2);
    CHECK_EQ(c.get(1), 1);
    c.put(3, 3);                          // evicts 2
    CHECK_EQ(c.get(2), -1);
    c.put(4, 4);                          // evicts 1
    CHECK_EQ(c.get(1), -1);
    CHECK_EQ(c.get(3), 3);
    CHECK_EQ(c.get(4), 4);

    LRUCache d(2);
    d.put(1, 1); d.put(2, 2); d.put(1, 10);   // update moves 1 to the front
    d.put(3, 3);                              // evicts 2
    CHECK_EQ(d.get(1), 10);
    CHECK_EQ(d.get(2), -1);

    LRUCache e(1);
    e.put(1, 1); e.put(2, 2);
    CHECK_EQ(e.get(1), -1);
    CHECK_EQ(e.get(2), 2);
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_reverseKGroup);
    SECTION(t_detectCycle);
    SECTION(t_mergeTwoLists);
    SECTION(t_isPalindromeList);
    SECTION(t_rotateRight);
    SECTION(t_removeNthFromEnd);
    SECTION(t_addTwoNumbers);
    SECTION(t_deleteDuplicates);
    SECTION(t_sortList);
    SECTION(t_isValidParens);
    SECTION(t_MinStack);
    SECTION(t_nextGreater);
    SECTION(t_largestRectangle);
    SECTION(t_maxSlidingWindow);
    SECTION(t_mergeIntervals);
    SECTION(t_minMeetingRooms);
    SECTION(t_findKthLargest);
    SECTION(t_mergeKLists);
    SECTION(t_MedianFinder);
    SECTION(t_segmentsIntersect);
    SECTION(t_rectOverlapArea);
    SECTION(t_rectUnionArea);
    SECTION(t_diameter);
    SECTION(t_isBalanced);
    SECTION(t_lca);
    SECTION(t_pathBetween);
    SECTION(t_isValidBST);
    SECTION(t_kthSmallest);
    SECTION(t_serialize);
    SECTION(t_buildTree);
    SECTION(t_invertTree);
    SECTION(t_LRUCache);
    return tst::summary("day2");
}
