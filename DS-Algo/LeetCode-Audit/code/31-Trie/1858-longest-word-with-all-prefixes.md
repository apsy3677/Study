# 1858. Longest Word With All Prefixes

[Problem](https://leetcode.com/problems/longest-word-with-all-prefixes/) · Medium · Trie → Prefix check

LeetCode tags: array, string, depth-first-search, trie

Attempts since Mar 2023: 2 · accepted: 1 · failed before first AC: 1

## Attempt 1 · 2023-05-04 17:28 IST · Wrong Answer · C++

[submission 944331978](https://leetcode.com/submissions/detail/944331978/) · tests 9/68

Failing input:

```text
["x","y","l","k","w","b","f","z","t","n","j","r","q","a","h","v","g","m","u","o","p","d","i","c","s","e"]
```

Expected:

```text
"a"
```

Your output:

```text
"e"
```

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

class Trie{
    Node* root;
    public:
    Trie(){
        root = new Node();
    }
    void insert(string word){
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                node->put(word[i]);
            }
            // move to reference Trie
            node = node->get(word[i]);
            // node->incPrefix();
        }
        node->setEnd();
    }
    bool checkIfPrefixExists(string word){
        bool ret = true;
        Node * node = root;

        for(auto ch : word){
            if(!node->containsKey(ch)){
                return false;
            }
            node = node->get(ch);
            if(!node->isEnd()){
                return false;
            }
        }
        return ret;
    }

};

class Solution {
    
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for(auto &it : words){
            trie.insert(it);
        }
        string longest = "";

        for(auto &it : words){
            if(trie.checkIfPrefixExists(it)){
                longest = it;
            }
            else if(it.length() == longest.length() && it < longest){
                longest = it;
            }
        }

        return longest;
    }
};
```

## Attempt 2 · 2023-05-04 17:32 IST · Accepted · C++

[submission 944333566](https://leetcode.com/submissions/detail/944333566/) · tests 68/68 · runtime 241 ms (beats 5.9%)

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

class Trie{
    Node* root;
    public:
    Trie(){
        root = new Node();
    }
    void insert(string word){
        Node * node = root;

        for(int i=0;i<word.size();i++){
            if(!node->containsKey(word[i])){
                node->put(word[i]);
            }
            // move to reference Trie
            node = node->get(word[i]);
            // node->incPrefix();
        }
        node->setEnd();
    }
    bool checkIfPrefixExists(string word){
        bool ret = true;
        Node * node = root;

        for(auto ch : word){
            if(!node->containsKey(ch)){
                return false;
            }
            node = node->get(ch);
            ret = ret & node->isEnd();
        }
        return ret;
    }

};

class Solution {
    
public:
    string longestWord(vector<string>& words) {
        Trie trie;
        for(auto &it : words){
            trie.insert(it);
        }
        string longest = "";

        for(auto &it : words){
            if(trie.checkIfPrefixExists(it)){
                if(it.size() > longest.size()){
                    longest = it;
                }
                else if(it.length() == longest.length() && it < longest){
                    longest = it;
                }
            }
            
        }

        return longest;
    }
};
```
