#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// LC 48 Rotate Image, 90 degrees clockwise, in place.
// Way 1: two mirror flips = one rotation. (i,j) -transpose-> (j,i) -reverse row-> (j, n-1-i) = clockwise target.
void rotateFlips(vector<vector<int>>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) swap(a[i][j], a[j][i]);   // 1. transpose: only j > i, or every pair swaps back
    for (auto& row : a) reverse(row.begin(), row.end());          // 2. mirror left-right
}

// Way 2: the spiral's walls. Ring by ring; each step moves 4 cells, one per side, with one temp.
void rotateRings(vector<vector<int>>& a) {
    int n = a.size();
    for (int top = 0, bot = n - 1; top < bot; top++, bot--)       // a ring: l = top, r = bot (square)
        for (int i = 0; i < bot - top; i++) {
            int tmp = a[top][top + i];                            // save the top cell
            a[top][top + i] = a[bot - i][top];                    // left   -> top
            a[bot - i][top] = a[bot][bot - i];                    // bottom -> left
            a[bot][bot - i] = a[top + i][bot];                    // right  -> bottom
            a[top + i][bot] = tmp;                                // top    -> right
        }
}

void show(vector<vector<int>>& a) {
    for (auto& row : a) { for (int x : row) cout << x << ' '; cout << '\n'; }
    cout << '\n';
}

int main() {
    vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, b = a;
    vector<vector<int>> c = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}, d = c;
    rotateFlips(a); show(a);       // 7 4 1 / 8 5 2 / 9 6 3
    rotateRings(b); show(b);
    rotateFlips(c); show(c);       // 13 9 5 1 / 14 10 6 2 / 15 11 7 3 / 16 12 8 4
    rotateRings(d); show(d);
}
