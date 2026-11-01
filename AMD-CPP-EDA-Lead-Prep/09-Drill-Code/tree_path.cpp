#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode { int val; TreeNode *left = nullptr, *right = nullptr; TreeNode(int v) : val(v) {} };

// LC 236 LCA: each node asks both children "did you find p or q below you?"
TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;      // 1. empty, or I am one of them -> report myself
    TreeNode* L = lca(root->left, p, q);                   // 2. ask both children
    TreeNode* R = lca(root->right, p, q);
    if (L && R) return root;                               // 3. one on each side -> I'm the meeting point
    return L ? L : R;                                      // 4. pass up whatever was found
}

// Root-to-target path by backtracking. path by reference: found -> return true and stop popping.
bool pathTo(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) {
    if (!root) return false;
    path.push_back(root);                                  // 1. step in
    if (root == target) return true;                       // 2. found -> keep the path
    if (pathTo(root->left, target, path) || pathTo(root->right, target, path)) return true;   // 3. found below
    path.pop_back();                                       // 4. dead end -> step back out
    return false;
}

// Prefix way: two root paths, cut the common prefix, keep the LCA once.
vector<int> pathCommonPrefix(TreeNode* root, TreeNode* a, TreeNode* b) {
    vector<TreeNode*> pa, pb;
    pathTo(root, a, pa); pathTo(root, b, pb);              // 3 5 6  |  3 5 2 4
    int i = 0;
    while (i < (int)pa.size() && i < (int)pb.size() && pa[i] == pb[i]) i++;   // common = 3 5 -> i = 2, LCA = pa[i-1]
    vector<int> out;
    for (int j = (int)pa.size() - 1; j >= i - 1; j--) out.push_back(pa[j]->val);   // a up to the LCA: 6 5
    for (int j = i; j < (int)pb.size(); j++) out.push_back(pb[j]->val);             // down to b: 2 4
    return out;
}

// LCA way: paths from the LCA, first one reversed, LCA once.
vector<int> pathViaLca(TreeNode* root, TreeNode* a, TreeNode* b) {
    TreeNode* m = lca(root, a, b);
    vector<TreeNode*> pa, pb;
    pathTo(m, a, pa); pathTo(m, b, pb);                    // 5 6  |  5 2 4
    vector<int> out;
    for (int j = (int)pa.size() - 1; j >= 0; j--) out.push_back(pa[j]->val);   // 6 5
    for (int j = 1; j < (int)pb.size(); j++) out.push_back(pb[j]->val);        // skip the LCA: 2 4
    return out;
}

int main() {
    vector<TreeNode*> n(9);
    for (int v : {3, 5, 1, 6, 2, 0, 8, 7, 4}) n[v] = new TreeNode(v);
    n[3]->left = n[5]; n[3]->right = n[1];
    n[5]->left = n[6]; n[5]->right = n[2];
    n[1]->left = n[0]; n[1]->right = n[8];
    n[2]->left = n[7]; n[2]->right = n[4];

    cout << "LCA(5,1)=" << lca(n[3], n[5], n[1])->val << " LCA(5,4)=" << lca(n[3], n[5], n[4])->val
         << " LCA(6,4)=" << lca(n[3], n[6], n[4])->val << '\n';                       // 3 5 5
    vector<pair<int,int>> qs = {{6, 4}, {7, 8}, {5, 4}, {4, 5}, {6, 6}};
    for (auto [a, b] : qs) {
        cout << "path " << a << "->" << b << ":  prefix ";
        for (int v : pathCommonPrefix(n[3], n[a], n[b])) cout << v << ' ';
        cout << "|  via LCA ";
        for (int v : pathViaLca(n[3], n[a], n[b])) cout << v << ' ';
        cout << '\n';
    }
}
