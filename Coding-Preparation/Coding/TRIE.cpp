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