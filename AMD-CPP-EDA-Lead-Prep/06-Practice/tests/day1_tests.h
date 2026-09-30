// Tests for day1. Included at the end of day1.cpp (and solutions/day1_sol.cpp).
#pragma once
#include "../test.h"

static void t_twoSum() {
    CHECK_EQ(twoSum({2, 7, 11, 15}, 9), (VI{0, 1}));
    CHECK_EQ(twoSum({3, 2, 4}, 6), (VI{1, 2}));
    CHECK_EQ(twoSum({3, 3}, 6), (VI{0, 1}));
    CHECK_EQ(twoSum({-5, 10, 4, -1}, -6), (VI{0, 3}));
}
static void t_subarraySumK() {
    CHECK_EQ(subarraySumK({1, 1, 1}, 2), 2);
    CHECK_EQ(subarraySumK({1, 2, 3}, 3), 2);
    CHECK_EQ(subarraySumK({1, -1, 0}, 0), 3);
    CHECK_EQ(subarraySumK({3, 4, 7, 2, -3, 1, 4, 2}, 7), 4);
    CHECK_EQ(subarraySumK({}, 0), 0);
}
static void t_longestConsecutive() {
    CHECK_EQ(longestConsecutive({100, 4, 200, 1, 3, 2}), 4);
    CHECK_EQ(longestConsecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}), 9);
    CHECK_EQ(longestConsecutive({}), 0);
    CHECK_EQ(longestConsecutive({5, 5, 5}), 1);
}
static void t_maxSubArray() {
    CHECK_EQ(maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}), 6);
    CHECK_EQ(maxSubArray({-3, -1, -2}), -1);
    CHECK_EQ(maxSubArray({5}), 5);
}
static void t_spiralOrder() {
    CHECK_EQ(spiralOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), (VI{1, 2, 3, 6, 9, 8, 7, 4, 5}));
    CHECK_EQ(spiralOrder({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}), (VI{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}));
    CHECK_EQ(spiralOrder({{1, 2, 3}}), (VI{1, 2, 3}));
    CHECK_EQ(spiralOrder({{1}, {2}, {3}}), (VI{1, 2, 3}));
    CHECK_EQ(spiralOrder({}), (VI{}));
}
static void t_rotateImage() {
    VVI m{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    rotateImage(m);
    CHECK_EQ(m, (VVI{{7, 4, 1}, {8, 5, 2}, {9, 6, 3}}));
    VVI m2{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
    rotateImage(m2);
    CHECK_EQ(m2, (VVI{{15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11}}));
    VVI m3{{1}};
    rotateImage(m3);
    CHECK_EQ(m3, (VVI{{1}}));
}
static void t_maxProfit() {
    CHECK_EQ(maxProfit({7, 1, 5, 3, 6, 4}), 5);
    CHECK_EQ(maxProfit({7, 6, 4, 3, 1}), 0);
    CHECK_EQ(maxProfit({}), 0);
}
static void t_maxShortProfit() {
    CHECK_EQ(maxShortProfit({7, 1, 5, 3, 6, 4}), 6);
    CHECK_EQ(maxShortProfit({1, 2, 3, 4}), 0);
    CHECK_EQ(maxShortProfit({3, 8, 2, 9, 1}), 8);
    CHECK_EQ(maxShortProfit({5}), 0);
}
static void t_productExceptSelf() {
    CHECK_EQ(productExceptSelf({1, 2, 3, 4}), (VI{24, 12, 8, 6}));
    CHECK_EQ(productExceptSelf({-1, 1, 0, -3, 3}), (VI{0, 0, 9, 0, 0}));
}
static void t_myAtoi() {
    CHECK_EQ(myAtoi("42"), 42);
    CHECK_EQ(myAtoi("   -42"), -42);
    CHECK_EQ(myAtoi("4193 with words"), 4193);
    CHECK_EQ(myAtoi("words and 987"), 0);
    CHECK_EQ(myAtoi("-91283472332"), INT_MIN);
    CHECK_EQ(myAtoi("91283472332"), INT_MAX);
    CHECK_EQ(myAtoi("+-12"), 0);
    CHECK_EQ(myAtoi(""), 0);
    CHECK_EQ(myAtoi("   +0012a"), 12);
    CHECK_EQ(myAtoi("2147483648"), INT_MAX);
}
static void t_romanToInt() {
    CHECK_EQ(romanToInt("III"), 3);
    CHECK_EQ(romanToInt("LVIII"), 58);
    CHECK_EQ(romanToInt("MCMXCIV"), 1994);
    CHECK_EQ(romanToInt("XLIX"), 49);
}
static void t_reverseWords() {
    CHECK_EQ(reverseWords("the sky is blue"), string("blue is sky the"));
    CHECK_EQ(reverseWords("  hello world  "), string("world hello"));
    CHECK_EQ(reverseWords("a good   example"), string("example good a"));
    CHECK_EQ(reverseWords("   "), string(""));
}
static void t_threeSum() {
    auto r = threeSum({-1, 0, 1, 2, -1, -4});
    tst::sortAll(r);
    CHECK_EQ(r, (VVI{{-1, -1, 2}, {-1, 0, 1}}));
    auto r2 = threeSum({0, 0, 0, 0});
    tst::sortAll(r2);
    CHECK_EQ(r2, (VVI{{0, 0, 0}}));
    CHECK_EQ(threeSum({0, 1, 1}), (VVI{}));
    auto r3 = threeSum({-2, 0, 1, 1, 2});
    tst::sortAll(r3);
    CHECK_EQ(r3, (VVI{{-2, 0, 2}, {-2, 1, 1}}));
}
static void t_moveZeroes() {
    VI a{0, 1, 0, 3, 12};
    moveZeroes(a);
    CHECK_EQ(a, (VI{1, 3, 12, 0, 0}));
    VI b{0};
    moveZeroes(b);
    CHECK_EQ(b, (VI{0}));
}
static void t_trap() {
    CHECK_EQ(trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}), 6);
    CHECK_EQ(trap({4, 2, 0, 3, 2, 5}), 9);
    CHECK_EQ(trap({}), 0);
    CHECK_EQ(trap({3, 2, 1}), 0);
    CHECK_EQ(trap({5, 0, 5}), 5);
}
static void t_mergeSorted() {
    VI a{1, 2, 3, 0, 0, 0};
    mergeSorted(a, 3, {2, 5, 6}, 3);
    CHECK_EQ(a, (VI{1, 2, 2, 3, 5, 6}));
    VI b{0};
    mergeSorted(b, 0, {1}, 1);
    CHECK_EQ(b, (VI{1}));
    VI c{4, 5, 6, 0, 0, 0};
    mergeSorted(c, 3, {1, 2, 3}, 3);
    CHECK_EQ(c, (VI{1, 2, 3, 4, 5, 6}));
}
static void t_lengthOfLongestSubstring() {
    CHECK_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
    CHECK_EQ(lengthOfLongestSubstring("bbbbb"), 1);
    CHECK_EQ(lengthOfLongestSubstring("pwwkew"), 3);
    CHECK_EQ(lengthOfLongestSubstring(""), 0);
    CHECK_EQ(lengthOfLongestSubstring("abba"), 2);
    CHECK_EQ(lengthOfLongestSubstring("dvdf"), 3);
}
static void t_minWindow() {
    CHECK_EQ(minWindow("ADOBECODEBANC", "ABC"), string("BANC"));
    CHECK_EQ(minWindow("a", "a"), string("a"));
    CHECK_EQ(minWindow("a", "aa"), string(""));
    CHECK_EQ(minWindow("aaflslflsldkalskaaa", "aaa"), string("aaa"));
}
static void t_searchRange() {
    CHECK_EQ(searchRange({5, 7, 7, 8, 8, 10}, 8), (VI{3, 4}));
    CHECK_EQ(searchRange({5, 7, 7, 8, 8, 10}, 6), (VI{-1, -1}));
    CHECK_EQ(searchRange({}, 0), (VI{-1, -1}));
    CHECK_EQ(searchRange({2, 2, 2}, 2), (VI{0, 2}));
}
static void t_searchRotated() {
    CHECK_EQ(searchRotated({4, 5, 6, 7, 0, 1, 2}, 0), 4);
    CHECK_EQ(searchRotated({4, 5, 6, 7, 0, 1, 2}, 3), -1);
    CHECK_EQ(searchRotated({1}, 0), -1);
    CHECK_EQ(searchRotated({3, 1}, 1), 1);
    CHECK_EQ(searchRotated({5, 1, 3}, 5), 0);
    CHECK_EQ(searchRotated({1, 2, 3, 4, 5}, 4), 3);
}
static void t_minEatingSpeed() {
    CHECK_EQ(minEatingSpeed({3, 6, 7, 11}, 8), 4);
    CHECK_EQ(minEatingSpeed({30, 11, 23, 4, 20}, 5), 30);
    CHECK_EQ(minEatingSpeed({30, 11, 23, 4, 20}, 6), 23);
    CHECK_EQ(minEatingSpeed({1000000000}, 2), 500000000);
}

int main(int argc, char** argv) {
    if (argc > 1) tst::filter = argv[1];
    SECTION(t_twoSum);
    SECTION(t_subarraySumK);
    SECTION(t_longestConsecutive);
    SECTION(t_maxSubArray);
    SECTION(t_spiralOrder);
    SECTION(t_rotateImage);
    SECTION(t_maxProfit);
    SECTION(t_maxShortProfit);
    SECTION(t_productExceptSelf);
    SECTION(t_myAtoi);
    SECTION(t_romanToInt);
    SECTION(t_reverseWords);
    SECTION(t_threeSum);
    SECTION(t_moveZeroes);
    SECTION(t_trap);
    SECTION(t_mergeSorted);
    SECTION(t_lengthOfLongestSubstring);
    SECTION(t_minWindow);
    SECTION(t_searchRange);
    SECTION(t_searchRotated);
    SECTION(t_minEatingSpeed);
    return tst::summary("day1");
}
