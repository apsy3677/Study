#include <iostream>
#include <vector>
using namespace std;

// LC 54 Spiral Matrix: 4 walls, 4 moves per lap; the box can collapse after moves 1-2 -> check before going back.
vector<int> spiralOrder(vector<vector<int>>& a) {
    vector<int> out;
    int top = 0, bot = (int)a.size() - 1, l = 0, r = (int)a[0].size() - 1;
    while (top <= bot && l <= r) {
        for (int c = l; c <= r; c++) out.push_back(a[top][c]);              // 1. top row  ->
        top++;
        for (int i = top; i <= bot; i++) out.push_back(a[i][r]);            // 2. right col down
        r--;
        if (top <= bot) { for (int c = r; c >= l; c--) out.push_back(a[bot][c]); bot--; }   // 3. bottom row <- (a row left?)
        if (l <= r)     { for (int i = bot; i >= top; i--) out.push_back(a[i][l]); l++; }   // 4. left col up  (a col left?)
    }
    return out;
}

int main() {
    vector<vector<vector<int>>> tests = {
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}},   // 1 2 3 4 8 12 11 10 9 5 6 7
        {{1, 2, 3}},                                     // single row
        {{1}, {2}, {3}},                                 // single column
        {{1}},
        {{1, 2}, {3, 4}, {5, 6}},                        // 1 2 4 6 5 3
    };
    for (auto& m : tests) {
        for (int x : spiralOrder(m)) cout << x << ' ';
        cout << '\n';
    }
}
