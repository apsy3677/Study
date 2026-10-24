# 987. Vertical Order Traversal of a Binary Tree

[Problem](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/) · Hard · Binary Tree (BFS / Level Order) → Column ordering + sort

LeetCode tags: hash-table, tree, depth-first-search, breadth-first-search, sorting, binary-tree

Attempts since Mar 2023: 9 · accepted: 6 · failed before first AC: 0

## Attempt 1 · 2023-03-25 21:41 IST · Accepted · C++

[submission 921935272](https://leetcode.com/submissions/detail/921935272/) · tests 32/32 · runtime 4 ms (beats 21.7%)

```cpp
// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */
// class Solution {
// public:
//     void traverse (TreeNode* root, int row, int col, map<int, vector<pair<int,int>> > &vertical){
//         if(!root) return;

//         vertical[col].push_back({row,root->val});
//         traverse(root->left, row +1, col-1, vertical);
//         traverse(root->right, row +1, col+1, vertical);
//     }
//     static bool comp(pair<int, int> p, pair<int,int> q) {
//         if(p.first == q.first){
//             return q.second>p.second;
//         }
//         return p.first < q.first;
//     }
//     vector<vector<int>> verticalTraversal(TreeNode* root) {
//         vector<vector<int>> ans;
//         map<int, vector<pair<int,int>> > vertical;

//         traverse(root, 0, 0, vertical);

//         for(auto& [x, st] : vertical)
//         {
//             ans.push_back({});
//             for(auto& [y, val] : st) ans.back().push_back(val);
//         }

//         // for(auto col : vertical){
//         //     vector< pair<int,int> > arr(col.second);
//         //     sort(arr.begin(), arr.begin(), comp);
//         //     vector<int> view;
//         //     for(auto x : arr){
//         //         view.push_back(x.second);
//         //     }
//         //     ans.push_back(view);
//         // }
//         return ans;
//     }
// };

class Solution {
    public:
        vector<vector<int>> verticalTraversal(TreeNode* root) 
        {
            map<int, multiset<pair<int, int>>> mp; // [x][y, val]
            traverse(root, 0, 0, mp);
            vector<vector<int>> res;
            for(auto& [x, st] : mp)
            {
                res.push_back({});
                for(auto& [y, val] : st) res.back().push_back(val);
            }
            return res;
        }
        
    protected:
        void traverse(TreeNode* node, int x, int y,  map<int, multiset<pair<int, int>>>& mp)
        {
            if(!node) return;
            mp[x].insert({y, node->val});
            traverse(node->left, x-1, y+1, mp);
            traverse(node->right, x+1, y+1, mp);
        }
};
```

## Attempt 2 · 2023-03-25 21:53 IST · Wrong Answer · C++

[submission 921941189](https://leetcode.com/submissions/detail/921941189/) · tests 12/32

Failing input:

```text
[1,2,3,4,6,5,7]
```

Expected:

```text
[[4],[2],[1,5,6],[3],[7]]
```

Your output:

```text
[[4],[2],[1,6,5],[3],[7]]
```

```cpp
// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */
static bool comp(const pair<int, int> p, const pair<int,int> q) {
        // if(p)
        return 0;
        return p.second > q.second;
        
    }
class Solution {
public:
    void traverse (TreeNode* root, int row, int col, map<int, vector<pair<int,int>> > &vertical){
        if(!root) return;

        vertical[col].push_back({row,root->val});
        traverse(root->left, row +1, col-1, vertical);
        traverse(root->right, row +1, col+1, vertical);
    }
    // static bool comp(const pair<int, int> p, const pair<int,int> q) {
    //     // if(p)
    //     return 0;
    //     return p.second > q.second;
        
    // }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> ans;
        map<int, vector<pair<int,int>> > vertical;

        traverse(root, 0, 0, vertical);

        // for(auto& [x, st] : vertical)
        // {
        //     ans.push_back({});
        //     for(auto& [y, val] : st) ans.back().push_back(val);
        // }

        for(auto col : vertical){
            vector< pair<int,int> > arr(col.second);
            sort(arr.begin(), arr.begin(), greater<>());
            cout<<"::"; for(auto x : arr) cout<<x.second<<"|"<<x.first<<" "; cout<<"::";
            vector<int> view;
            for(auto x : arr){
                view.push_back(x.second);
            }
            ans.push_back(view);
        }
        return ans;
    }
};

// class Solution {
//     public:
//         vector<vector<int>> verticalTraversal(TreeNode* root) 
//         {
//             map<int, multiset<pair<int, int>>> mp; // [x][y, val]
//             traverse(root, 0, 0, mp);
//             vector<vector<int>> res;
//             for(auto& [x, st] : mp)
//             {
//                 res.push_back({});
//                 for(auto& [y, val] : st) res.back().push_back(val);
//             }
//             return res;
//         }
        
//     protected:
//         void traverse(TreeNode* node, int x, int y,  map<int, multiset<pair<int, int>>>& mp)
//         {
//             if(!node) return;
//             mp[x].insert({y, node->val});
//             traverse(node->left, x-1, y+1, mp);
//             traverse(node->right, x+1, y+1, mp);
//         }
// };
```

## Attempt 3 · 2023-03-25 21:58 IST · Wrong Answer · C++

[submission 921944131](https://leetcode.com/submissions/detail/921944131/) · tests 14/32

Failing input:

```text
[3,1,4,0,2,2]
```

Expected:

```text
[[0],[1],[3,2,2],[4]]
```

Your output:

```text
[[0],[1],[2,2,3],[4]]
```

```cpp
// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
//  * };
//  */
static bool comp1(const pair<int, int> p, const pair<int,int> q) {
        // if(p)
        // return 0;
        return p.second < q.second;
        
    }
class Solution {
public:
    void traverse (TreeNode* root, int row, int col, map<int, vector<pair<int,int>> > &vertical){
        if(!root) return;

        vertical[col].push_back({row,root->val});
        traverse(root->left, row +1, col-1, vertical);
        traverse(root->right, row +1, col+1, vertical);
    }
    // static bool comp(const pair<int, int> p, const pair<int,int> q) {
    //     // if(p)
    //     return 0;
    //     return p.second > q.second;
        
    // }
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> ans;
        map<int, vector<pair<int,int>> > vertical;

        traverse(root, 0, 0, vertical);

        // for(auto& [x, st] : vertical)
        // {
        //     ans.push_back({});
        //     for(auto& [y, val] : st) ans.back().push_back(val);
        // }

        for(auto col : vertical){
            vector< pair<int,int> > arr(col.second);
            sort(arr.begin(), arr.begin(), comp1);
            cout<<"::"; for(auto x : arr) cout<<x.second<<"|"<<x.first<<" "; cout<<"::";
            vector<int> view;
            for(auto x : arr){
                view.push_back(x.second);
            }
            ans.push_back(view);
        }
        for(int i=0;i<ans.size();i++){
            sort(ans[i].begin(), ans[i].end());
        }
        return ans;
    }
};

// class Solution {
//     public:
//         vector<vector<int>> verticalTraversal(TreeNode* root) 
//         {
//             map<int, multiset<pair<int, int>>> mp; // [x][y, val]
//             traverse(root, 0, 0, mp);
//             vector<vector<int>> res;
//             for(auto& [x, st] : mp)
//             {
//                 res.push_back({});
//                 for(auto& [y, val] : st) res.back().push_back(val);
//             }
//             return res;
//         }
        
//     protected:
//         void traverse(TreeNode* node, int x, int y,  map<int, multiset<pair<int, int>>>& mp)
//         {
//             if(!node) return;
//             mp[x].insert({y, node->val});
//             traverse(node->left, x-1, y+1, mp);
//             traverse(node->right, x+1, y+1, mp);
//         }
// };
```

## Attempt 4 · 2023-11-15 23:10 IST · Accepted · Python3

[submission 1099525947](https://leetcode.com/submissions/detail/1099525947/) · tests 34/34 · runtime 45 ms (beats 1.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []

        columnTable = defaultdict(list)
        min_col = max_col = 0

        def dfs(node, row, col):
            if node is not None:
                nonlocal min_col, max_col

                columnTable[col].append((row, node.val))
                min_col = min(min_col, col)
                max_col = max(max_col, col)

                dfs(node.left, row+1, col-1)
                dfs(node.right, row+1, col+1)

        dfs(root, 0,0)

        ret = []
        for col in range(min_col, max_col+1):
            ret.append([val for row, val in sorted(columnTable[col])])
        
        return ret
```

## Attempt 5 · 2023-11-21 23:49 IST · Wrong Answer · Python3

[submission 1103647758](https://leetcode.com/submissions/detail/1103647758/) · tests 14/34

Failing input:

```text
[3,1,4,0,2,2]
```

Expected:

```text
[[0],[1],[3,2,2],[4]]
```

Your output:

```text
[[0],[1],[2,2,3],[4]]
```

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        queue = deque([(root,0,0)])

        columnNodes = defaultdict(list)
        minCol = math.inf
        maxCol= -math.inf
        while queue:
            node, col, row = queue.popleft()
            columnNodes[col].append((node.val))
            
            minCol = min(minCol, col)
            maxCol = max(maxCol, col)

            if node.left:
                queue.append((node.left, col-1, row+1))
            
            if node.right:
                queue.append((node.right, col+1, row+1))


        result = []
        for col in range(minCol, maxCol+1):
            result.append([val for val in sorted(columnNodes[col])])
        return result
```

## Attempt 6 · 2023-12-05 04:03 IST · Accepted · Python3

[submission 1112478686](https://leetcode.com/submissions/detail/1112478686/) · tests 34/34 · runtime 41 ms (beats 1.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        '''
        the time complexity is dictated by k lists of N/k size which needs to be sorted 
        which is O(n log N/k)

        we have to do the column ordering, row ordering and then value ordering
        in the previous problem, we did the column ordering using min max and row ordering was taken care by the traversal from left to right
         but here we have to do the col and then (row, val) sorting
        '''
        queue = deque([(root,0,0)])

        columnNodes = defaultdict(list)
        minCol = math.inf
        maxCol= -math.inf
        while queue:
            node, col, row = queue.popleft()
            columnNodes[col].append((row,node.val))
            
            minCol = min(minCol, col)
            maxCol = max(maxCol, col)

            if node.right:
                queue.append((node.right, col+1, row+1))
            
            if node.left:
                queue.append((node.left, col-1, row+1))


        result = []
        for col in range(minCol, maxCol+1):
            result.append([val for _, val in sorted(columnNodes[col])])
        return result
```

## Attempt 7 · 2023-12-30 06:51 IST · Accepted · Python3

[submission 1131815366](https://leetcode.com/submissions/detail/1131815366/) · tests 34/34 · runtime 83 ms (beats 1.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        '''
        the time complexity is dictated by k lists of N/k size which needs to be sorted 
        which is O(n log N/k)

        we have to do the column ordering, row ordering and then value ordering
        in the previous problem, we did the column ordering using min max and row ordering was taken care by the traversal from left to right
         but here we have to do the col and then (row, val) sorting
        '''
        queue = deque([(root,0,0)])

        columnNodes = defaultdict(list)
        minCol = math.inf
        maxCol= -math.inf
        while queue:
            node, col, row = queue.popleft()
            columnNodes[col].append((row,node.val))
            
            minCol = min(minCol, col)
            maxCol = max(maxCol, col)

           
            if node.left:
                queue.append((node.left, col-1, row+1))

            if node.right:
                queue.append((node.right, col+1, row+1))
            

        result = []
        for col in range(minCol, maxCol+1):
            result.append([val for _, val in sorted(columnNodes[col])])
        return result
```

## Attempt 8 · 2023-12-30 06:56 IST · Accepted · Python3

[submission 1131817380](https://leetcode.com/submissions/detail/1131817380/) · tests 34/34 · runtime 74 ms (beats 1.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        '''
        the time complexity is dictated by k lists of N/k size which needs to be sorted 
        which is O(n log N/k)

        time complexity - width * N/width log N/width
        if width = N that is when tree is skewed with each node having only left child
        time complexity = N 
         
        we have to do the column ordering, row ordering and then value ordering
        in the previous problem, we did the column ordering using min max and row ordering was taken care by the traversal from left to right
         but here we have to do the col and then (row, val) sorting


        '''

        queue = deque([(root,0,0)])

        columnNodes = defaultdict(list)
        minCol = math.inf
        maxCol= -math.inf
        while queue:
            node, col, row = queue.popleft()
            columnNodes[col].append((row,node.val))
            
            minCol = min(minCol, col)
            maxCol = max(maxCol, col)

            if node.right:
                queue.append((node.right, col+1, row+1))
            
            if node.left:
                queue.append((node.left, col-1, row+1))


        result = []
        for col in range(minCol, maxCol+1):
            result.append([val for _, val in sorted(columnNodes[col])])
        return result
```

## Attempt 9 · 2023-12-30 06:57 IST · Accepted · Python3

[submission 1131817657](https://leetcode.com/submissions/detail/1131817657/) · tests 34/34 · runtime 75 ms (beats 1.1%)

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        '''
        the time complexity is dictated by k lists of N/k size which needs to be sorted 
        which is O(n log N/k)

        time complexity - width * N/width log N/width
        if width = N that is when tree is skewed with each node having only left child
        time complexity = N 
         
        we have to do the column ordering, row ordering and then value ordering
        in the previous problem, we did the column ordering using min max and row ordering was taken care by the traversal from left to right
         but here we have to do the col and then (row, val) sorting


        '''

        queue = deque([(root,0,0)])

        columnNodes = defaultdict(list)
        minCol = math.inf
        maxCol= -math.inf
        while queue:
            node, col, row = queue.popleft()
            columnNodes[col].append((row,node.val))
            
            minCol = min(minCol, col)
            maxCol = max(maxCol, col)

            if node.right:
                queue.append((node.right, col+1, row+1))
            
            if node.left:
                queue.append((node.left, col-1, row+1))


        result = []
        for col in range(minCol, maxCol+1):
            result.append([val for _, val in sorted(columnNodes[col])])
        return result
```
