#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// LC 200 Number of Islands. Flood fill: every new unseen '1' = one new island; paint everything it touches.

// Way 1: recursive DFS + visited matrix, input untouched. Depth can reach m*n -> stack overflow on huge grids.
struct DfsSolution {
    int m, n;
    vector<vector<bool>> seen;
    void dfs(vector<vector<char>>& g, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || g[i][j] != '1' || seen[i][j]) return;  // 1. off grid / water / done
        seen[i][j] = true;                                                             // 2. mark before going on
        dfs(g, i + 1, j); dfs(g, i - 1, j); dfs(g, i, j + 1); dfs(g, i, j - 1);       // 3. the 4 neighbours
    }
    int numIslands(vector<vector<char>>& g) {
        m = g.size(); n = g[0].size();
        seen.assign(m, vector<bool>(n, false));
        int islands = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (g[i][j] == '1' && !seen[i][j]) { islands++; dfs(g, i, j); }      // new pour = new island
        return islands;
    }
};

// Way 2 (big grids): BFS with a queue on the heap, marking in place ('1' -> '0') -> no recursion, no visited matrix.
int numIslandsBfs(vector<vector<char>>& g) {
    int m = g.size(), n = g[0].size(), islands = 0;
    int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (g[i][j] != '1') continue;
            islands++;
            queue<pair<int,int>> q;
            q.push({i, j}); g[i][j] = '0';                              // mark when PUSHED, not when popped
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nc >= 0 && nr < m && nc < n && g[nr][nc] == '1') {
                        g[nr][nc] = '0';
                        q.push({nr, nc});
                    }
                }
            }
        }
    return islands;
}

int main(int argc, char** argv) {
    vector<vector<char>> g = {{'1','1','0','0','0'}, {'1','1','0','0','0'}, {'0','0','1','0','0'}, {'0','0','0','1','1'}};
    vector<vector<char>> g2 = g;
    DfsSolution s;
    cout << "example: dfs " << s.numIslands(g) << ", bfs " << numIslandsBfs(g2) << '\n';   // 3 3

    int N = 2000;                                                       // all-'1' 2000 x 2000 = 4M cells
    vector<vector<char>> big(N, vector<char>(N, '1'));
    if (argc > 1 && string(argv[1]) == "bigdfs") {
        cout << "recursive dfs on all-1 " << N << "x" << N << "..." << endl;
        cout << s.numIslands(big) << '\n';                              // snakes through every cell: depth ~4M
    } else {
        cout << "bfs on all-1 " << N << "x" << N << ": " << numIslandsBfs(big) << '\n';
    }
}
