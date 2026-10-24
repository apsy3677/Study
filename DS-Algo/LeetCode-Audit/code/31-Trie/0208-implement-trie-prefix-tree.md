# 208. Implement Trie (Prefix Tree)

[Problem](https://leetcode.com/problems/implement-trie-prefix-tree/) · Medium · Trie → Basic trie

LeetCode tags: hash-table, string, design, trie

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-05-04 16:35 IST · Accepted · C++

[submission 944313239](https://leetcode.com/submissions/detail/944313239/) · tests 16/16 · runtime 74 ms (beats 6.1%)

```cpp
namespace my{
    class TreeNode{
        private:
            bool end;
            vector<TreeNode*> child;
        public:
            TreeNode(){
                this->end = false;
                child.resize(26,NULL);
            }

            void setEnd(){
                this->end = true;
            }

            void setNode(char ch){
                child[ch-'a'] = new TreeNode();
            }

            bool isEnd(){
                return this->end;
            }

            bool isSet(char ch){
                return child[ch-'a'] != NULL;
            }

            TreeNode* getNode(char ch){
                return child[ch-'a'];
            }
    };
}

struct Node{
    vector<Node *> child;
    bool end = false;

    Node()
    {
        child.resize(26, NULL);
        end = false;
    }
    bool containsKey(char ch){
        return child[ch-'a'] != NULL;
    }
    void put(char ch){
        child[ch-'a'] = new Node();
    }
    Node* get(char ch){
        return child[ch-'a'];
    }
    void setEnd(){
        this->end = true;
    }
    bool isEnd(){
        return this->end;
    }
};

class Trie {
    Node * root;
public:
    Trie() {
        root = new Node();
        // root->
    }
    // O(N)  size of word
    void insert(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                node->put(word[i]);
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        node->setEnd();
    }
    
    bool search(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                return false;
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        return node->isEnd();
    }
    
    bool startsWith(string prefix) {
        Node * node = root;

        for(int i=0;i<prefix.size();i++){
            if(!node->containsKey(prefix[i])){
                return false;
            }
            // move to reference Trie
            node = node->get(prefix[i]);
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```

## Attempt 2 · 2023-05-04 16:38 IST · Accepted · C++

[submission 944314286](https://leetcode.com/submissions/detail/944314286/) · tests 16/16 · runtime 67 ms (beats 6.5%)

```cpp
struct Node{
    vector<Node *> child;
    bool end = false;

    Node()
    {
        child.resize(26, NULL);
        end = false;
    }
    bool containsKey(char ch){
        return child[ch-'a'] != NULL;
    }
    void put(char ch){
        child[ch-'a'] = new Node();
    }
    Node* get(char ch){
        return child[ch-'a'];
    }
    void setEnd(){
        this->end = true;
    }
    bool isEnd(){
        return this->end;
    }
};

class Trie {
    Node * root;
public:
    Trie() {
        root = new Node();
        // root->
    }
    // O(N)  size of word
    void insert(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                node->put(word[i]);
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        node->setEnd();
    }
    
    bool search(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                return false;
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        return node->isEnd();
    }
    
    bool startsWith(string prefix) {
        Node * node = root;

        for(int i=0;i<prefix.size();i++){
            if(!node->containsKey(prefix[i])){
                return false;
            }
            // move to reference Trie
            node = node->get(prefix[i]);
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
```
