# P09: Recursion & Backtracking

> Striver: `Recursion.pdf` · Priority for AMD R1: **low–medium** (1 problem at most). Know the template cold, then move on.

---

## Card: "choose → explore → un-choose"
| | |
|---|---|
| **Hook** | You walk a **decision tree**. At each level you pick one option, recurse, and then **undo** the pick so the next sibling starts clean. |
| **Triggers** | "all subsets / permutations / combinations", "generate all valid …", N-Queens, Sudoku, word search, n ≤ ~20 |
| **Invariant** | On entering `bt(i)`, `path` contains exactly the choices made for positions `< i`. |
| **Traps** | Forgetting to undo (pop / unmark). Copying `path` at every call (pass by reference). Duplicates → sort + skip `if (i > start && a[i] == a[i-1]) continue;`. No pruning → TLE. |

```cpp
vector<vector<int>> res; vector<int> path;
function<void(int)> bt = [&](int start) {
    res.push_back(path);                          // subsets: record every node
    for (int i = start; i < n; ++i) {
        if (i > start && a[i] == a[i-1]) continue; // skip dups (a sorted)
        path.push_back(a[i]);                      // choose
        bt(i + 1);                                 // explore (i, not i+1, if reuse allowed)
        path.pop_back();                           // un-choose
    }
};
bt(0);
```
| Variant | Change |
|---|---|
| Permutations | loop over all i with a `used[]` array (or swap-based) |
| Combination sum (reuse allowed) | recurse with `i`, prune when `remaining < 0` (sort first → `break`) |
| N-Queens | cols / diag (`r+c`) / anti-diag (`r−c+n`) boolean arrays |
| Word search on a grid | mark the cell `'#'`, recurse in 4 directions, restore |
| Bitmask alternative for subsets | `for mask in 0..2ⁿ−1` |

## Problems (hint ladders)
### P09-1 · Subsets II (LC 90) ★
<details><summary>Approach check</summary>Sort + skip duplicates at the same depth. O(2ⁿ·n).</details>

### P09-2 · Permutations (LC 46) ★
<details><summary>Approach check</summary>used[] + path; or swap a[i] with a[start]. n!·n.</details>

### P09-3 · Combination Sum (LC 39) ★
<details><summary>Approach check</summary>Recurse with the same i (reuse), sorted with an early break.</details>

### P09-4 · Word Search (LC 79) ★
<details><summary>Approach check</summary>DFS from each cell with in-place marking; O(RC·4^L). Prune by checking the char counts first.</details>

### P09-5 · N-Queens (LC 51) ★
<details><summary>Approach check</summary>Row by row; three occupancy arrays; O(n!).</details>

## Recall check
1. Where does the "un-choose" go and why? 2. Duplicate-skipping condition. 3. Reuse vs no-reuse: which index do you recurse with?
