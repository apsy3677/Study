# 1804. Implement Trie II (Prefix Tree)

[Problem](https://leetcode.com/problems/implement-trie-ii-prefix-tree/) · Medium · Trie → Trie with counts

LeetCode tags: hash-table, string, design, trie

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-05-04 17:08 IST · Accepted · C++

[submission 944324967](https://leetcode.com/submissions/detail/944324967/) · tests 78/78 · runtime 209 ms (beats 6.1%)

```cpp
struct Node{
    vector<Node *> child;
    bool end = false;
    int cp =0;
    int ew =0;

    Node()
    {
        child.resize(26, NULL);
        end = false;
        cp = 0;
        ew = 0;
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
    int getEndWith(){
        return this->ew;
    }
    int getCP(){
        return this->cp;
    }
    void incEnd(){
        this->ew++;
    }
    void incPrefix(){
        this->cp++;
    }
    void decEnd(){
        this->ew--;
    }
    void decPrefix(){
        this->cp--;
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
            node->incPrefix();
        }
        node->incEnd();
    }
    
    int countWordsEqualTo(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                return 0;
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        return node->getEndWith();
    }
    
    int countWordsStartingWith(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                return 0;
            }
            // move to reference Trie
            node = node->get(word[i]);
        }
        return node->getCP();
    }
    
    void erase(string word) {
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(node->containsKey(word[i])){
                node = node->get(word[i]);
                node->decPrefix();
            }
            else {
                return;
            }
        }
        node->decEnd();
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */
```
