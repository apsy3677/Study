// DAY 1: Arrays, Hashing, Prefix sums, Two pointers, Sliding window, Binary search
// Patterns: 02-Patterns/P01, P02, P03 (hints live there, in the <details> blocks).
//
// HOW TO USE
//   1. Pick a function. Say the approach + invariant + complexity OUT LOUD (or to Claude) first.
//   2. Replace the stub body. Time yourself (target 12-15 min each). ★ = do these first.
//   3. Build & run:  g++ -std=c++20 -O1 -g -fsanitize=address,undefined day1.cpp -o day1 && ./day1
//      Only one problem:  ./day1 trap       (runs the sections whose name contains "trap")
//   4. Log the time + your bug in PROGRESS.md. Compare with solutions/day1_sol.cpp only AFTER passing.
#include "test.h"

// ★ P01-1  Two Sum: indices {i, j} (i < j) with a[i] + a[j] == target. Exactly one answer.
VI twoSum(const VI& a, int target) {
    return {};
}

// ★ P01-2  Count subarrays with sum == k (negatives allowed).
int subarraySumK(const VI& a, int k) {
    return 0;
}

// P01-3  Longest run of consecutive integers (unsorted input) in O(n).
int longestConsecutive(const VI& a) {
    return 0;
}

// P01-4  Maximum subarray sum (non-empty).
int maxSubArray(const VI& a) {
    return 0;
}

// ★ P01-5  Spiral order of an m x n matrix.
VI spiralOrder(const VVI& m) {
    return {};
}

// ★ P01-6  Rotate an n x n matrix 90° clockwise, in place.
void rotateImage(VVI& m) {
}

// P01-7a  Max profit: buy on day i, sell on day j > i. 0 if no profit.
int maxProfit(const VI& p) {
    return 0;
}

// ★ P01-7b  AMD variant: SELL first on day i, BUY back on day j > i. Max of p[i]-p[j]; 0 if none.
int maxShortProfit(const VI& p) {
    return 0;
}

// P01-8  Product of array except self, no division.
VI productExceptSelf(const VI& a) {
    return {};
}

// P01-9a  atoi: skip leading spaces, optional +/-, digits until a non-digit, clamp to [INT_MIN, INT_MAX].
int myAtoi(const string& s) {
    return 0;
}

// P01-9b  Roman numeral to integer (valid input).
int romanToInt(const string& s) {
    return 0;
}

// P01-10  Reverse the order of words; single spaces between words, no leading/trailing spaces.
string reverseWords(const string& s) {
    return "";
}

// ★ P02-1  All unique triplets summing to 0 (any order inside/outside; tests sort them).
VVI threeSum(VI a) {
    return {};
}

// P02-2  Move all zeros to the end, keeping the order of the non-zeros. In place.
void moveZeroes(VI& a) {
}

// ★ P02-3  Trapping rain water.
int trap(const VI& h) {
    return 0;
}

// P02-4  Merge sorted b (n elems) into sorted a (m elems + n spare slots at the end). In place.
void mergeSorted(VI& a, int m, const VI& b, int n) {
}

// ★ P02-5  Length of the longest substring without repeating characters.
int lengthOfLongestSubstring(const string& s) {
    return 0;
}

// P02-6  Minimum window of s containing all chars of t (with multiplicity). "" if none.
string minWindow(const string& s, const string& t) {
    return "";
}

// P03-1  First and last index of x in sorted a; {-1, -1} if absent.
VI searchRange(const VI& a, int x) {
    return {-1, -1};
}

// ★ P03-2  Index of x in a rotated sorted array of distinct values; -1 if absent.
int searchRotated(const VI& a, int x) {
    return -1;
}

// ★ P03-4  Koko: minimum integer speed k to eat all piles within h hours.
int minEatingSpeed(const VI& piles, int h) {
    return 0;
}

#include "tests/day1_tests.h"
