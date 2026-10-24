# 212. Word Search II

[Problem](https://leetcode.com/problems/word-search-ii/) · Hard · Trie → Trie + grid backtracking

LeetCode tags: array, string, backtracking, trie, matrix

Attempts since Mar 2023: 18 · accepted: 5 · failed before first AC: 0

## Attempt 1 · 2023-03-27 01:43 IST · Accepted · C++

[submission 922641891](https://leetcode.com/submissions/detail/922641891/) · tests 65/65 · runtime 379 ms (beats 33.3%)

```cpp
class Solution {
    struct TrieNode {
        TrieNode *children[26];
        string word;

        TrieNode() : word("") {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words) {
        TrieNode *root = buildTrie(words);
        vector<string> result;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, i, j, root, result);
            }
        }
        return result;
    }

    /** Inserts a word into the trie. */
    TrieNode *buildTrie(vector<string> &words) {
        TrieNode *root = new TrieNode();
        for (int j = 0; j < words.size(); j++) {
            string word = words[j];
            TrieNode *curr = root;
            for (int i = 0; i < word.length(); i++) {
                char c = word[i] - 'a';
                if (curr->children[c] == nullptr) {
                    curr->children[c] = new TrieNode();
                }
                curr = curr->children[c];
            }
            curr->word = word;
        }
        return root;
    }

    void dfs(vector<vector<char>> &board, int i, int j, TrieNode *p, vector<string> &result) {
        char c = board[i][j];
        if (c == '#' || !p->children[c - 'a']) return;
        p = p->children[c - 'a'];
        if (p->word.size() > 0) {
            result.push_back(p->word);
            p->word = "";
        }

        board[i][j] = '#';
        if (i > 0) dfs(board, i - 1, j, p, result);
        if (j > 0) dfs(board, i, j - 1, p, result);
        if (i < board.size() - 1) dfs(board, i + 1, j, p, result);
        if (j < board[0].size() - 1) dfs(board, i, j + 1, p, result);
        board[i][j] = c;
    }
};
```

## Attempt 2 · 2023-12-30 02:11 IST · Time Limit Exceeded · Python3

[submission 1131690819](https://leetcode.com/submissions/detail/1131690819/) · tests 63/65

Failing input:

```text
[["m","b","c","d","e","f","g","h","i","j","k","l"],["n","a","a","a","a","a","a","a","a","a","a","a"],["o","a","a","a","a","a","a","a","a","a","a","a"],["p","a","a","a","a","a","a","a","a","a","a","a"],["q","a","a","a","a","a","a","a","a","a","a","a"],["r","a","a","a","a","a","a","a","a","a","a","a"],["s","a","a","a","a","a","a","a","a","a","a","a"],["t","a","a","a","a","a","a","a","a","a","a","a"] ... [8991 more chars]
```

Expected:

```text
["mbaaaaaaaa","mnaaaaaaaa","bcaaaaaaaa","baaaaaaaaa","cdaaaaaaaa","caaaaaaaaa","cbaaaaaaaa","deaaaaaaaa","daaaaaaaaa","dcaaaaaaaa","efaaaaaaaa","eaaaaaaaaa","edaaaaaaaa","fgaaaaaaaa","faaaaaaaaa","feaaaaaaaa","ghaaaaaaaa","gaaaaaaaaa","gfaaaaaaaa","hiaaaaaaaa","haaaaaaaaa","hgaaaaaaaa","ijaaaaaaaa","iaaaaaaaaa","ihaaaaaaaa","jkaaaaaaaa","jaaaaaaaaa","jiaaaaaaaa","klaaaaaaaa","kaaaaaaaaa","kjaaaaaa ... [498 more chars]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''

            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result
```

## Attempt 3 · 2023-12-30 02:16 IST · Time Limit Exceeded · Python3

[submission 1131693426](https://leetcode.com/submissions/detail/1131693426/) · tests 63/65

Failing input:

```text
[["m","b","c","d","e","f","g","h","i","j","k","l"],["n","a","a","a","a","a","a","a","a","a","a","a"],["o","a","a","a","a","a","a","a","a","a","a","a"],["p","a","a","a","a","a","a","a","a","a","a","a"],["q","a","a","a","a","a","a","a","a","a","a","a"],["r","a","a","a","a","a","a","a","a","a","a","a"],["s","a","a","a","a","a","a","a","a","a","a","a"],["t","a","a","a","a","a","a","a","a","a","a","a"] ... [8991 more chars]
```

Expected:

```text
["mbaaaaaaaa","mnaaaaaaaa","bcaaaaaaaa","baaaaaaaaa","cdaaaaaaaa","caaaaaaaaa","cbaaaaaaaa","deaaaaaaaa","daaaaaaaaa","dcaaaaaaaa","efaaaaaaaa","eaaaaaaaaa","edaaaaaaaa","fgaaaaaaaa","faaaaaaaaa","feaaaaaaaa","ghaaaaaaaa","gaaaaaaaaa","gfaaaaaaaa","hiaaaaaaaa","haaaaaaaaa","hgaaaaaaaa","ijaaaaaaaa","iaaaaaaaaa","ihaaaaaaaa","jkaaaaaaaa","jaaaaaaaaa","jiaaaaaaaa","klaaaaaaaa","kaaaaaaaaa","kjaaaaaa ... [498 more chars]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''

            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result
```

## Attempt 4 · 2024-01-16 10:29 IST · Wrong Answer · Python3

[submission 1147501144](https://leetcode.com/submissions/detail/1147501144/) · tests 6/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oaa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in trie:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word
        
        result = set()
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.add(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return list(result)
```

## Attempt 5 · 2024-01-16 10:30 IST · Wrong Answer · Python3

[submission 1147501258](https://leetcode.com/submissions/detail/1147501258/) · tests 6/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oaa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in trie:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word
        
        result = set()
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.add(next_node[WORD_KEY])
                # next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return list(result)
```

## Attempt 6 · 2024-01-16 10:31 IST · Accepted · Python3

[submission 1147502205](https://leetcode.com/submissions/detail/1147502205/) · tests 65/65 · runtime 5091 ms (beats 43.7%)

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = set()
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.add(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return list(result)
```

## Attempt 7 · 2024-01-16 10:31 IST · Accepted · Python3

[submission 1147502515](https://leetcode.com/submissions/detail/1147502515/) · tests 65/65 · runtime 5229 ms (beats 41.5%)

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result
```

## Attempt 8 · 2024-01-27 02:10 IST · Wrong Answer · Python3

[submission 1157747996](https://leetcode.com/submissions/detail/1157747996/) · tests 32/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oa","oa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for r in range(len(board)):
            for c in range(len(board[0])):
                visited = set()
                for word in words:
                    if search(r,c, word, 0):
                        results.append(word)

        return results
```

## Attempt 9 · 2024-01-27 02:11 IST · Wrong Answer · Python3

[submission 1157748687](https://leetcode.com/submissions/detail/1157748687/) · tests 36/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oa","oa","oaa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    visited = set()
                    if search(r,c, word, 0):
                        results.append(word)

        return results
```

## Attempt 10 · 2024-01-27 02:12 IST · Wrong Answer · Python3

[submission 1157749014](https://leetcode.com/submissions/detail/1157749014/) · tests 32/65

Failing input:

```text
[["a"]]
["b"]
```

Expected:

```text
[]
```

Your output:

```text
["b"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    visited = set()
                    if search(r,c, word, 0):
                        results.append(word)

        return results
                
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result
```

## Attempt 11 · 2024-01-27 02:12 IST · Wrong Answer · Python3

[submission 1157749411](https://leetcode.com/submissions/detail/1157749411/) · tests 36/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oa","oa","oaa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    visited = set()
                    if search(r,c, word, 0):
                        results.append(word)

        return results
```

## Attempt 12 · 2024-01-27 02:13 IST · Wrong Answer · Python3

[submission 1157749556](https://leetcode.com/submissions/detail/1157749556/) · tests 36/65

Failing input:

```text
[["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
["oa","oaa"]
```

Expected:

```text
["oa","oaa"]
```

Your output:

```text
["oa","oa","oaa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    visited = set()
                    if search(r,c, word, 0):
                        results.append(word)

        return results
```

## Attempt 13 · 2024-01-27 02:16 IST · Wrong Answer · Python3

[submission 1157751358](https://leetcode.com/submissions/detail/1157751358/) · tests 44/65

Failing input:

```text
[["a","b","c"],["a","e","d"],["a","f","g"]]
["abcdefg","gfedcbaaa","eaabcdgfa","befa","dgc","ade"]
```

Expected:

```text
["abcdefg","befa","eaabcdgfa","gfedcbaaa"]
```

Your output:

```text
["abcdefg","gfedcbaaa","befa"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if search(r,c, word, 0) and not found:
                        results.append(word)
                        found = True

        return results
```

## Attempt 14 · 2024-01-27 02:24 IST · Time Limit Exceeded · Python3

[submission 1157755766](https://leetcode.com/submissions/detail/1157755766/) · tests 42/65

Failing input:

```text
[["b","a","b","a","b","a","b","a","b","a"],["a","b","a","b","a","b","a","b","a","b"],["b","a","b","a","b","a","b","a","b","a"],["a","b","a","b","a","b","a","b","a","b"],["b","a","b","a","b","a","b","a","b","a"],["a","b","a","b","a","b","a","b","a","b"],["b","a","b","a","b","a","b","a","b","a"],["a","b","a","b","a","b","a","b","a","b"],["b","a","b","a","b","a","b","a","b","a"],["a","b","a","b","a", ... [8811 more chars]
```

Expected:

```text
["ababababab"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        this is a backtracking solution 
        if you add a cell to visited after all choices have been explored in the backtrack 
        remove it from visited 
        '''
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True
            visited.remove((r,c))

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            # print('truing', word)
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if not found and search(r,c, word, 0):
                        results.append(word)
                        found = True

        return results
```

## Attempt 15 · 2024-01-27 02:34 IST · Wrong Answer · Python3

[submission 1157761029](https://leetcode.com/submissions/detail/1157761029/) · tests 64/65

Failing input:

```text
[["e","e","c","d","b","b","c","b","c","d","e"],["c","e","e","a","d","d","e","c","c","c","b"],["b","e","a","c","d","a","a","b","c","d","c"],["e","d","e","d","c","c","e","b","d","e","e"],["b","b","b","a","b","d","b","b","b","a","a"],["e","e","b","e","c","c","a","b","e","e","c"],["b","a","b","c","b","d","a","d","c","d","a"],["d","b","a","e","a","c","e","a","d","e","c"]]
["aeceecbee"]
```

Expected:

```text
["aeceecbee"]
```

Your output:

```text
[]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    # ver 1 
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        this is a backtracking solution 
        if you add a cell to visited after all choices have been explored in the backtrack 
        remove it from visited 

        1. either use visited or stick to overwriting the cell temporarily
        '''
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True
            visited.remove((r,c))

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            # print('truing', word)
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if not found and search(r,c, word, 0):
                        results.append(word)
                        found = True

        return results

    # ver 2 with trie
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # build trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        # find words
        result = []
        def dfs(r,c, node):
            if (r,c) in visited:
                return

            # found complete word
            if '$' in node:
                result.append(node['$'])
                node.pop('$')
            
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in node):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                dfs(nr,nc,node[board[r][c]])
            visited.remove((r,c))
                

        # for each cell
        for r in range(len(board)):
            for c in range(len(board[0])):
                visited = set()
                dfs(r,c, trie)

        return result
```

## Attempt 16 · 2024-01-27 02:37 IST · Accepted · Python3

[submission 1157762230](https://leetcode.com/submissions/detail/1157762230/) · tests 65/65 · runtime 6720 ms (beats 16.6%)

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    # ver 1 
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        this is a backtracking solution 
        if you add a cell to visited after all choices have been explored in the backtrack 
        remove it from visited 

        1. either use visited or stick to overwriting the cell temporarily
        '''
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True
            visited.remove((r,c))

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            # print('truing', word)
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if not found and search(r,c, word, 0):
                        results.append(word)
                        found = True

        return results

    # ver 2 with trie
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # build trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        # find words
        result = []
        def dfs(r,c, node):
            if (r,c) in visited:
                return
            
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in node):
                return

            next_node = node[board[r][c]]
            # found complete word
            if '$' in next_node:
                result.append(next_node['$'])
                next_node.pop('$')

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                dfs(nr,nc,next_node)
            visited.remove((r,c))
                

        # for each cell
        for r in range(len(board)):
            for c in range(len(board[0])):
                visited = set()
                dfs(r,c, trie)

        return result
```

## Attempt 17 · 2024-02-11 11:43 IST · Wrong Answer · Python3

[submission 1172054310](https://leetcode.com/submissions/detail/1172054310/) · tests 55/65

Failing input:

```text
[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]
["oath","pea","eat","rain","hklf", "hf"]
```

Expected:

```text
["oath","eat","hklf","hf"]
```

Your output:

```text
["oath","eat","hf"]
```

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    # ver 1 
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        this is a backtracking solution 
        if you add a cell to visited after all choices have been explored in the backtrack 
        remove it from visited 

        1. either use visited or stick to overwriting the cell temporarily
        '''
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True
            visited.remove((r,c))

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            # print('truing', word)
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if not found and search(r,c, word, 0):
                        results.append(word)
                        found = True

        return results

    # ver 2 with trie
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        # find words
        result = []
        def dfs(r,c, node):
            if (r,c) in visited:
                return
            
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in node):
                return
            print(board[r][c], node)

            # in grid you test here if you reached at end of the word
            # get next node and check if end
            next_node = node[board[r][c]]
            # found complete word
            if '$' in next_node:
                result.append(next_node['$'])
                # remove this from the node if you don't wan tto find the same word again in the next
                next_node.pop('$')

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                dfs(nr,nc,next_node)

            # important to backtrack in grid so you can try other choices
            visited.remove((r,c))
                

        # for each cell
        for r in range(len(board)):
            for c in range(len(board[0])):
                # 1. reset visited set
                visited = set()
                dfs(r,c, trie)

        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie
        trie = {}
        result = []
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        def dfs(r,c, node):
            if (r,c) in visited:
                return
            
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c]  in node):
                return

            visited.add((r,c))
            next_node = node[board[r][c]]
            
            if '$' in next_node:
                result.append(next_node['$'])
                next_node.pop('$')

            for nr,nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                dfs(nr,nc,next_node)

        visited = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                visited.clear()
                dfs(r,c, trie)

        return result
```

## Attempt 18 · 2024-02-11 11:44 IST · Accepted · Python3

[submission 1172054968](https://leetcode.com/submissions/detail/1172054968/) · tests 65/65 · runtime 6419 ms (beats 20.3%)

```python
class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        approach 1 - for each cell, for each word, run. a dfs and check 
        for each dfs call increase the index and then check word[indx] == new cell
        time complexity - for each cell there are 4 choices and it runs for each letter in word - 4^l
        for each cell, for each word 
        m*n*k*4^l

        approach2 - use trie to do search optimization    
        trie is good for prefix searches
        m*n*3^L

        '''

        # 1. create a trie from list of words

        # end of the word symbol
        word_key = '$'
        
        # trie dictionary
        # trie and try
        # {'t':{'r':{'i':{'e':{'$':'trie'}},'y':{'$':'try'}}}}
        trie= {}
        for word in words:
            # start at the root
            node = trie
            for letter in word:
                # if letter is not present, add it with {}
                # update the node to point to this
                node = node.setdefault(letter, {})
            # set $ as whole word
            node[word_key] = word

        print(trie)

        rowNum = len(board)
        colNum = len(board[0])

        matchedWords =[]

        def backtracking(row, col, parent):
             # is valid
            if not(0<=row<rowNum and 0<=col<colNum and board[row][col] in parent):
                return

            letter = board[row][col]
            currNode = parent[letter]
            print(currNode)
            
            # is solution
            word_match = currNode.pop(word_key, False)
            print(word_match)
            if word_match:
                matchedWords.append(word_match)

            # add path
            board[row][col] ='#'
            
            # neibors
            for nr,nc in [(row,col+1),(row+1,col),(row,col-1),(row-1 ,col)]:
                backtracking(nr,nc, currNode)

            # backtrack
            board[row][col] = letter

        for row in range(rowNum):
            for col in range(colNum):
                # starting from each of the cells
                if board[row][col] in trie:
                    backtracking(row, col, trie)

        return matchedWords 

    def findWords3(self, board: List[List[str]], words: List[str]) -> List:
        # for each cell, for each word call dfs
        def dfs(r,c, word, idx):
            print(idx, len(word))
            if idx == len(word) -1:
                print('found end of the word')
                return True

            temp = board[r][c]
            board[r][c] ='#'
            for nr,nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                # valid move 
                if 0<=nr<len(board) and 0<=nc<len(board[0]) and idx < len(word) -1 and word[idx+1] == board[nr][nc]:
                    print('inside',nr,nc,word)
                    if dfs(nr,nc,word, idx+1):
                        return True
            board[r][c] = temp
            
            return False

        result = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                for word in words:
                    if word[0] == board[r][c]:
                        print('calling', word, r,c)
                        if dfs(r,c,word, 0):
                            result.add(word)
        return list(result)


    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # create a trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                node = node.setdefault(letter, {})
            node['$'] = word

        result = []
        # backtrack

        def backtrack(r,c, parent_node):
            '''
            1. validate outside the loop 
            2. add parent_node as argument and the get the next_node where the next character might be there 
            3. move this word from the trie by deleting the end of word symbol 
            this guarantees same word is not searched again or atleast returned

            '''
            # validate
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in parent_node):
                return

            letter = board[r][c]

            # get childnode for this letter 
            next_node = parent_node[letter]

            # if this is the end node - end of a word
            word_match = next_node.pop('$', False)
            if word_match:
                result.append(word_match)
                
            # mark as visited
            board[r][c] = '#'
            
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node)
            
            # backtrack set it back
            board[r][c] = letter

        for r in range(len(board)):
            for c in range(len(board[0])):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        M = len(board)
        N = len(board[0])

        def backtrack(r,c,idx, word):
            if idx == len(word) -1:
                return True

            if board[r][c] != word[idx]:
                return

            letter = board[r][c]
            board[r][c] ='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if 0<=nr<M and 0<=nc<N:
                    if backtrack(nr,nc,idx+1, word):
                        return True
            board[r][c] = letter

            return False
        
        result = []
        for i in range(M):
            for j in range(N):
                for word in words:
                    if backtrack(i,j, 0, word):
                        result.append(word)


        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie solution
        trie = {}
        WORD_KEY = '$'
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node[WORD_KEY] = word

        result = set()

        # 2. backtrack in the grid 
        # to avoid visiting again - set to '#' and in backtrack set it back
        def backtrack(r,c, node):
            

            # check all valid conditions here
            # if invalid return
            if not ( 0<=r<M and 0<=c<N and board[r][c]  in node):
                return 

            letter = board[r][c]

            # valid cell check next node in trie
            node = node[letter]
            if WORD_KEY in node:
                result.add(node[WORD_KEY])
                # optimization do a pop here to make sure same word not searched agian

                # return # will fail for bat and bats - it will end for bat and will never find bats
            
            board[r][c] = '#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc, node)
            
            board[r][c] = letter

        M = len(board)
        N = len(board[0])
        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        return list(result)

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        trie = {}
        # build trie from words
        WORD_KEY = '$'
        for word in words:
            node = trie
            for ch in word:
                if ch not in node:
                    node[ch] = {}
                node = node[ch]
            node[WORD_KEY] = word

        # print(trie)
        result = []
        M = len(board)
        N = len(board[0])
        def backtrack(r,c,node):
            if not (0<=r<M and 0<=c<N and board[r][c] in node):
                return 

            letter = board[r][c]
            next_node = node[letter]
            if WORD_KEY in next_node:
                result.append(next_node[WORD_KEY])
                next_node.pop(WORD_KEY)

            board[r][c]='#'
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                backtrack(nr,nc,next_node) 
            board[r][c] = letter

        for r in range(M):
            for c in range(N):
                if board[r][c] in trie:
                    backtrack(r,c,trie)
        
        return result

    # ver 1 
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        '''
        this is a backtracking solution 
        if you add a cell to visited after all choices have been explored in the backtrack 
        remove it from visited 

        1. either use visited or stick to overwriting the cell temporarily
        '''
        def search(r,c,word, idx):
            if (r,c) in visited:
                return

            if idx == len(word):
                return True
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] == word[idx]):
                return

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                if search(nr,nc,word, idx+1):
                    return True
            visited.remove((r,c))

            return False
            
        results = []
        
        for word in words:
            visited = set()
            found = False
            # print('truing', word)
            for r in range(len(board)):
                for c in range(len(board[0])):            
                    if not found and search(r,c, word, 0):
                        results.append(word)
                        found = True

        return results

    # ver 2 with trie
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie
        trie = {}
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        # find words
        result = []
        def dfs(r,c, node):
            if (r,c) in visited:
                return
            
            if not(0<=r<len(board) and 0<=c<len(board[0]) and board[r][c] in node):
                return
            print(board[r][c], node)

            # in grid you test here if you reached at end of the word
            # get next node and check if end
            next_node = node[board[r][c]]
            # found complete word
            if '$' in next_node:
                result.append(next_node['$'])
                # remove this from the node if you don't wan tto find the same word again in the next
                next_node.pop('$')

            visited.add((r,c))
            for nr, nc in [(r,c+1),(r+1,c),(r,c-1),(r-1,c)]:
                dfs(nr,nc,next_node)

            # important to backtrack in grid so you can try other choices
            visited.remove((r,c))
                

        # for each cell
        for r in range(len(board)):
            for c in range(len(board[0])):
                # 1. reset visited set
                visited = set()
                dfs(r,c, trie)

        return result

    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        # 1. build trie
        trie = {}
        result = []
        for word in words:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = word
        
        def dfs(r,c, node):
            if (r,c) in visited:
                return
            
            if not (0<=r<len(board) and 0<=c<len(board[0]) and board[r][c]  in node):
                return

            visited.add((r,c))
            next_node = node[board[r][c]]
            
            if '$' in next_node:
                result.append(next_node['$'])
                next_node.pop('$')

            for nr,nc in [(r+1,c),(r-1,c),(r,c+1),(r,c-1)]:
                dfs(nr,nc,next_node)

            # backtrack
            visited.remove((r,c))

        visited = set()
        for r in range(len(board)):
            for c in range(len(board[0])):
                visited.clear()
                dfs(r,c, trie)

        return result
```
