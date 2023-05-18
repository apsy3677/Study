// Tekion Interview


// Pointer to a BST and node N

// root, node 

// Find the next number lower then given node 

// Find the floor in BST

Node * findLowerNumber(Node * root, int n){

    if(!root) return NULL;
    return util(root, n-1);
}

Node * util(Node * root, int key){
    if(!root) return NULL;
    if(root->val == key) return root;

    if(root->val > key){
        return util(root->left, key);
    }
    Node *ans = util(root->right, key);
    
    return ans != NULL && ans->val <=key ? ans : root;
}

// Sorted Array 
// find given number k its frequency

// O(N) Linear traversal

// O(logN) Binary Search

// leftmost index of K 
// rightmost index of k

// rightmost-leftmost+1

int freq(vector<int> arr, int k){
    int n = arr.size();
    int left = lower_bound(arr.begin(), arr.end(), k) - arr.begin();

    if(left == n){
        // K is not present in array
        return 0;
    }

    int right = upper_bound(arr.begin(), arr.end(), k) - arr.begin();

    return right - left;
}

// Ludo game
// other ppl will get assigned system will assign

// Ensure that 

// if ppl played last game together, dont match 

//     2
// 1       3

