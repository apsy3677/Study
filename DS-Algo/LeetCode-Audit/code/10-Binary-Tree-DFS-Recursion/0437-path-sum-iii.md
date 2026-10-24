# 437. Path Sum III

[Problem](https://leetcode.com/problems/path-sum-iii/) · Medium · Binary Tree (DFS & Recursion) → Prefix sum on tree paths

LeetCode tags: tree, depth-first-search, binary-tree

Attempts since Mar 2023: 7 · accepted: 3 · failed before first AC: 3

## Attempt 1 · 2023-05-20 16:58 IST · Runtime Error · C++

[submission 953866966](https://leetcode.com/submissions/detail/953866966/) · tests 126/128

Failing input:

```text
[1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null ... [15601 more chars]
```

Expected:

```text
0
```

Runtime error:

```text
Line 18: Char 18: runtime error: signed integer overflow: 2000000000 + 1000000000 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:27:18
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    unordered_map<int,int> hash;
    void paths(TreeNode* root, int targetSum, int curr_sum, int &count){
        if(!root) return;

        int ans =0;
        curr_sum += root->val;
        if(curr_sum == targetSum)
            count++;
        
        count += hash[curr_sum-targetSum];
        hash[curr_sum]++;
        paths(root->left, targetSum, curr_sum, count);
        paths(root->right, targetSum, curr_sum, count);
        hash[curr_sum]--;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        int currSum =0;
        int count =0;
        paths(root, targetSum, currSum, count);

        return count;
    }
};
```

## Attempt 2 · 2023-05-20 16:59 IST · Wrong Answer · C++

[submission 953867342](https://leetcode.com/submissions/detail/953867342/) · tests 127/128

Failing input:

```text
[1000000000,1000000000,null,294967296,null,1000000000,null,1000000000,null,1000000000]
0
```

Expected:

```text
0
```

Your output:

```text
1
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    unordered_map<int,int> hash;
    void paths(TreeNode* root, int targetSum, long curr_sum, int &count){
        if(!root) return;

        int ans =0;
        curr_sum += root->val;
        if(curr_sum == targetSum)
            count++;
        
        count += hash[curr_sum-targetSum];
        hash[curr_sum]++;
        paths(root->left, targetSum, curr_sum, count);
        paths(root->right, targetSum, curr_sum, count);
        hash[curr_sum]--;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        int currSum =0;
        int count =0;
        paths(root, targetSum, currSum, count);

        return count;
    }
};
```

## Attempt 3 · 2023-05-20 17:13 IST · Wrong Answer · C++

[submission 953872794](https://leetcode.com/submissions/detail/953872794/) · tests 122/128

Failing input:

```text
[1,-2,-3,1,3,-2,null,-1]
0
```

Expected:

```text
2
```

Your output:

```text
1
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
class Solution {
    unordered_map<int,int> hash;
    void paths(TreeNode* root, int targetSum, long curr_sum, int &count){
        if(!root) return;

        int ans =0;
        curr_sum += root->val;
        if(curr_sum == targetSum)
            count++;
        if(targetSum != 0)
            count +=  hash[curr_sum-targetSum];
        hash[curr_sum]++;
        paths(root->left, targetSum, curr_sum, count);
        paths(root->right, targetSum, curr_sum, count);
        hash[curr_sum]--;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        long currSum =0;
        int count =0;
        // hash[0] = 1;
        paths(root, targetSum, currSum, count);

        return count;
    }
};
// class Solution {
//     unordered_map<long, int> hashMap;
//     int count;
//     int target;
//     void find(TreeNode* root, long sum) {
//         if (root == 0) return;
//         sum += root->val;
//         int prefixSum = sum - target;
//         if (hashMap.count(prefixSum)) {
//             count += hashMap[prefixSum];
//         }
//         hashMap[sum]++;
//         find(root->left, sum);
//         find(root->right, sum);
//         hashMap[sum]--;
//     }
// public:
//     int pathSum(TreeNode* root, int targetSum) {
//         count = 0;
//         target = targetSum;
//         hashMap[0] = 1;
//         find(root, 0);
//         return count;
//     }
// };
```

## Attempt 4 · 2023-05-20 17:33 IST · Accepted · C++

[submission 953880080](https://leetcode.com/submissions/detail/953880080/) · tests 128/128 · runtime 29 ms (beats 8.5%)

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
class Solution {
    unordered_map<int,int> hash;
    void paths(TreeNode* root, int targetSum, long curr_sum, int &count){
        if(!root) return;

        int ans =0;
        curr_sum += root->val;
        if(curr_sum == targetSum || root->val == targetSum)
            count++;
        if(root->val == targetSum){

        }
        if(curr_sum != (curr_sum - targetSum))
            count +=  hash[curr_sum-targetSum];
        hash[curr_sum]++;
        paths(root->left, targetSum, curr_sum, count);
        paths(root->right, targetSum, curr_sum, count);
        // hash[curr_sum]--;
    }
public:
    int ans =0;
    int pathSum(TreeNode* root, int targetSum) {
        long currSum =0;
        pathSum1(root, targetSum, currSum);
        return ans;
        int count =0;
        // hash[0] = 1;
        paths(root, targetSum, currSum, count);

        return count;
    }

    void pathSum1(TreeNode* root, int targetSum, int currSum) {
        if(!root) return ;

        dfs(root, targetSum);
        pathSum1(root->left, targetSum, currSum);
        pathSum1(root->right, targetSum, currSum);

    }
    void dfs(TreeNode* root, long long targetSum){
        if(!root) return;

        if(root->val == targetSum) ans++;

        dfs(root->left, targetSum-root->val);
        dfs(root->right, targetSum-root->val);
    }
};
```

## Attempt 5 · 2023-05-20 17:42 IST · Accepted · C++

[submission 953883637](https://leetcode.com/submissions/detail/953883637/) · tests 128/128 · runtime 15 ms (beats 28.4%)

```cpp
// // /**
// //  * Definition for a binary tree node.
// //  * struct TreeNode {
// //  *     int val;
// //  *     TreeNode *left;
// //  *     TreeNode *right;
// //  *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
// //  *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// //  *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// //  * };
// //  */
class Solution1 {
    unordered_map<int,int> hash;
    void paths(TreeNode* root, int targetSum, long curr_sum, int &count){
        if(!root) return;

        int ans =0;
        curr_sum += root->val;
        if(curr_sum == targetSum || root->val == targetSum)
            count++;

        // if(curr_sum != (curr_sum - targetSum))
            count +=  hash[curr_sum-targetSum];
        hash[curr_sum]++;
        paths(root->left, targetSum, curr_sum, count);
        paths(root->right, targetSum, curr_sum, count);
        hash[curr_sum]--;
    }
public:
    int ans =0;
    int pathSum(TreeNode* root, int targetSum) {
        long currSum =0;
        // pathSum1(root, targetSum, currSum);
        // return ans;
        int count =0;
        // hash[0] = 1;
        paths(root, targetSum, currSum, count);

        return count;
    }

    void pathSum1(TreeNode* root, int targetSum, int currSum) {
        if(!root) return ;

        dfs(root, targetSum);
        pathSum1(root->left, targetSum, currSum);
        pathSum1(root->right, targetSum, currSum);

    }
    void dfs(TreeNode* root, long long targetSum){
        if(!root) return;

        if(root->val == targetSum) ans++;

        dfs(root->left, targetSum-root->val);
        dfs(root->right, targetSum-root->val);
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        ans = 0;
        _t = targetSum;
        pc[0] = 1;
        dfs(root, 0);
        return ans;
    }
    unordered_map<long long, int> pc; // prefix sum count
    int ans;
    int _t;

    void dfs(TreeNode *node, long long psum) {
        if (!node) return;
        psum += node->val;
        long long comp = psum - _t; // psum - ppsum == _t
        ans += pc[comp];
        pc[psum]++;
        dfs(node->left, psum);
        dfs(node->right, psum);
        pc[psum]--;
    }
};
```

## Attempt 6 · 2025-05-01 09:16 IST · Runtime Error · C++

[submission 1622443744](https://leetcode.com/submissions/detail/1622443744/) · tests 126/129

Failing input:

```text
[1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null,1000000000,null ... [15601 more chars]
```

Expected:

```text
0
```

Runtime error:

```text
Line 17: Char 20: runtime error: signed integer overflow: 2000000000 + 1000000000 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior prog_joined.cpp:26:20
```

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int pathSumUtil(TreeNode* root, int targetSum, int currentSum, 
                    unordered_map<long long, long long> & prefix) {
        if (!root) return 0;
        currentSum += root->val;
        int ans = prefix[currentSum - targetSum];
        //explore paths
        prefix[currentSum]++;
        int left = pathSumUtil(root->left, targetSum, currentSum, prefix);
        int right = pathSumUtil(root->right, targetSum, currentSum, prefix);

        prefix[currentSum]--;
        return ans + left + right;
    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, long long> prefix;
        prefix[0] = 1;
        return pathSumUtil(root, targetSum, 0, prefix);
    }
};
```

## Attempt 7 · 2025-05-01 09:18 IST · Accepted · C++

[submission 1622444693](https://leetcode.com/submissions/detail/1622444693/) · tests 129/129 · runtime 4 ms (beats 79.8%)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int pathSumUtil(TreeNode* root, int targetSum, long long int currentSum, 
                    unordered_map<long long, long long> & prefix) {
        if (!root) return 0;
        currentSum += root->val;
        int ans = prefix[currentSum - targetSum];
        //explore paths
        prefix[currentSum]++;
        int left = pathSumUtil(root->left, targetSum, currentSum, prefix);
        int right = pathSumUtil(root->right, targetSum, currentSum, prefix);

        prefix[currentSum]--;
        return ans + left + right;
    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, long long> prefix;
        prefix[0] = 1;
        return pathSumUtil(root, targetSum, 0, prefix);
    }
};
```
