# P07: Binary Trees & BST

> Practice file: `06-Practice/day2.cpp` · Striver: `Trees-BT-BST.pdf`
> AMD/EDA reports: **path between two nodes via LCA (your Cadence R1)**, height-balanced check, mirror/invert BST, BST degrading on sorted input → AVL/RB tree, level order.

---

## Card A: Every tree recursion = "what do I ask my children, what do I tell my parent?"
| | |
|---|---|
| **Hook** | You are a node. You **receive** from your children (postorder = bottom-up) and/or **pass down** constraints (preorder = top-down). Decide which before coding. |
| **Bottom-up (postorder)** | height, diameter, balanced, max path sum, LCA, subtree sums. *"Return what the parent needs; update a global answer on the side."* |
| **Top-down (preorder)** | validate BST (pass `[lo, hi]`), path sums from the root, depth labelling, right view by depth. |
| **Traps** | Mixing "return value" with "global best" (diameter: return the height, update the diameter). Null handling. Recursion depth on skewed trees (10⁵ → iterative). `INT_MIN`/`INT_MAX` as bounds when nodes can hold those values → use `long long` or pointers. |

```cpp
// bottom-up template: returns height, updates the answer
int dfs(TreeNode* n, int& best) {
    if (!n) return 0;
    int L = dfs(n->left, best), R = dfs(n->right, best);
    best = max(best, L + R);          // e.g., diameter in edges
    return 1 + max(L, R);
}
```
**Balanced check trick:** return `-1` as "unbalanced" to short-circuit, giving O(n) instead of O(n²).

## Card B: Traversals you must type blind
- Recursive pre/in/post: trivial.
- **Iterative inorder**: go left pushing; pop, visit, go right (see the toolkit).
- **Level order**: queue + `size` snapshot per level. Right view = last of each level; zig-zag = reverse alternate levels.
- **Morris** (O(1) space inorder): mention as a follow-up only.

## Card C: LCA = "the first node where the two searches split"
```cpp
TreeNode* lca(TreeNode* r, int a, int b) {
    if (!r || r->val == a || r->val == b) return r;
    TreeNode* L = lca(r->left, a, b); TreeNode* R = lca(r->right, a, b);
    if (L && R) return r;             // split here
    return L ? L : R;
}
```
**Caveat:** this assumes both values exist. If one may be missing, verify with a `find` (or return a found-count) before trusting the answer.
**BST LCA:** walk from the root. If both are smaller go left, if both are larger go right, else the current node.
**Path between a and b** = path(lca → a) reversed + path(lca → b) without repeating the LCA. `findPath` is a DFS with push/pop backtracking.
Your Cadence code had a bug to learn from: `findPathHelper(root->left) || findPathHelper(root->left)` searched left **twice**. It must be `left || right`. Classic pressure bug: re-read the recursive calls.

## Card D: BST = "inorder is sorted"
| Task | Idea |
|---|---|
| Validate | pass `(lo, hi)` down; or inorder and check strictly increasing with a `prev` pointer |
| k-th smallest | iterative inorder, stop at the k-th pop. With frequent queries: augment nodes with subtree sizes → O(h) |
| Insert/delete | delete with 2 children: replace with the inorder successor (min of the right subtree) |
| Floor/ceil | walk down and remember the last candidate |
| **Degenerates on sorted input** | height = n → O(n) ops. Fix: **self-balancing** (AVL: strict \|bf\| ≤ 1, faster lookups, more rotations; **Red-Black**: looser, cheaper inserts; `std::map` uses RB) or a skip list, or shuffle the input if it's offline |

## Card E: Construct & serialize
- Build from preorder + inorder: preorder[0] is the root; find it in inorder (hash map index) to split the sizes. O(n).
- Serialize: preorder with `#` for null; deserialize with a queue/index. (Level order also works.)

---

## Problems (hint ladders)

### P07-1 · Maximum Depth / Level Order (LC 104/102) ★★ (warm-up) · `levelOrder` is in the toolkit; write `maxDepth` both recursively and with BFS.

### P07-2 · Diameter of Binary Tree (LC 543) ★★ · `diameter`
<details><summary>Hint</summary>The longest path through a node = left height + right height. What does the recursion return vs update?</details>

### P07-3 · Balanced Binary Tree (LC 110) ★★★ · `isBalanced`
<details><summary>Hint</summary>Computing height separately at every node is O(n²). Can one pass return both the height and "balanced?"</details>
<details><summary>Approach check</summary>Return −1 if a subtree is unbalanced or |L−R| > 1, else the height. O(n).</details>

### P07-4 · LCA of a Binary Tree (LC 236) ★★★ · `lca`
<details><summary>Approach check</summary>Card C. O(n). Discuss: BST version O(h). Many queries → binary lifting (O(log n) per query) or Euler tour + RMQ.</details>

### P07-5 · Print the path between two nodes (Cadence R1) ★★★ · `pathBetween`
Return the node values along the path from a to b (inclusive). Empty if either is missing.
<details><summary>Hint 1</summary>Break it into LCA + two root-to-node paths.</details>
<details><summary>Hint 2</summary>Alternatively: root→a path and root→b path, strip the common prefix (keeping the last common node = the LCA).</details>
<details><summary>Approach check</summary>O(n). Edge cases: a == b, a is an ancestor of b, a missing. (The root-paths version is simpler to get right under pressure.)</details>

### P07-6 · Validate BST (LC 98) ★★★ · `isValidBST`
<details><summary>Hint</summary>Checking only `left < node < right` locally is wrong. Why? (Think of a grandchild.)</details>
<details><summary>Approach check</summary>Pass bounds as long long / nullable pointers; strict inequalities. O(n).</details>

### P07-7 · K-th Smallest in BST (LC 230) ★★ · `kthSmallest`
<details><summary>Approach check</summary>Iterative inorder, count pops. Follow-up: frequent inserts + queries → size-augmented tree (order-statistic tree; `__gnu_pbds` in GCC).</details>

### P07-8 · Serialize / Deserialize (LC 297) ★ · `serialize`, `deserialize`
<details><summary>Approach check</summary>Preorder with "#" nulls separated by ','. Deserialize recursively with an index into the token list.</details>

### P07-9 · Construct from Preorder + Inorder (LC 105) ★ · `buildTree`
<details><summary>Approach check</summary>Hash map value→inorder index; recursive with (preIdx, inL, inR). O(n).</details>

### P07-10 · Invert / Mirror a tree (LC 226, AMD "reverse a BST") ★★ · `invertTree`
<details><summary>Approach check</summary>Swap the children recursively (or BFS). Note: a mirrored BST is a BST with **descending** order.</details>

### P07-11 · Binary Tree Maximum Path Sum (LC 124) ★ (stretch)
<details><summary>Hint</summary>Return the best *downward* path; update the global with node + max(0,L) + max(0,R).</details>

---

## Recall check
1. Bottom-up vs top-down: one example each. 2. LCA code from memory, and its caveat. 3. Why does a local-only BST check fail?
4. AVL vs Red-Black: which does `std::map` use, and why? 5. Balanced check in O(n): the trick.
