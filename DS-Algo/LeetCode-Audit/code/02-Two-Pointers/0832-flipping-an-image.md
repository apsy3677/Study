# 832. Flipping an Image

[Problem](https://leetcode.com/problems/flipping-an-image/) · Easy · Two Pointers → Reverse + invert

LeetCode tags: array, two-pointers, bit-manipulation, matrix, simulation

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-24 12:14 IST · Accepted · C++

[submission 956272640](https://leetcode.com/submissions/detail/956272640/) · tests 82/82 · runtime 11 ms (beats 0.6%)

```cpp
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
        int rows = image.size();
        int cols = image[0].size();

        for(int row=0;row<rows;row++){
            for(int col = 0;col<cols/2;col++){
                swap(image[row][col], image[row][cols-col-1]);
            }
        }
        for(int row=0;row<rows;row++){
            for(int col = 0;col<cols;col++){
                image[row][col] = !image[row][col];
            }
        }
        return image;
    }
};
```
