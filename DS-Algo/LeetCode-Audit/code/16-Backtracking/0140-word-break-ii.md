# 140. Word Break II

[Problem](https://leetcode.com/problems/word-break-ii/) · Hard · Backtracking → Memoized segmentation

LeetCode tags: array, hash-table, string, dynamic-programming, backtracking, trie, memoization

Attempts since Mar 2023: 16 · accepted: 14 · failed before first AC: 0

## Attempt 1 · 2023-03-23 14:18 IST · Accepted · C++

[submission 920610898](https://leetcode.com/submissions/detail/920610898/) · tests 26/26 · runtime 0 ms (beats 100%)

```cpp
class Solution {
    vector<string> res;
public:

    bool WB(string s, vector<string>& wordDict, vector<string> path){
        if (s.empty()) {
            // String is empty, return true 
            string sen = "";
            int i=0;
            for(auto x: path){
                sen += x;
                if(i+1< path.size()){
                    sen += " ";
                }
                i++;
            }
            res.push_back(sen);
            return true;
        }
        
        // Check if this subproblem is evaluated
        // if (dp.count(s) == 1) {
        //     // The subproblem is already evaluated, returning previous
        //     // calculated solution
        //     return dp[s];
        // }
        
        // string is not empty, loop all words in dictionary
        for (string word: wordDict) {
            string left = s.substr(0, word.size());
            
            if(left == word ) {
                path.push_back(left);
                bool ans = WB(s.substr(word.size()), wordDict, path);
                path.pop_back();
                // return dp[s] = true;
            }
        }
        // dp[s] = false;
        return false;
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> dp;
        WB(s, wordDict, dp);
        return res;
    }
};
```

## Attempt 2 · 2023-11-18 21:48 IST · Accepted · Python3

[submission 1101500228](https://leetcode.com/submissions/detail/1101500228/) · tests 27/27 · runtime 41 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)
```

## Attempt 3 · 2023-12-27 21:06 IST · Wrong Answer · Python3

[submission 1129792195](https://leetcode.com/submissions/detail/1129792195/) · tests 23/27

Failing input:

```text
"abcd"
["a","abc","b","cd"]
```

Expected:

```text
["a b cd"]
```

Your output:

```text
[]
```

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        visited = set({0})
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))
                continue

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    # path.append(s[start:i])
                    # print(visited, i)
                    if i+1 not in visited:
                        queue.append((i, path + [s[start:i]]))
                        visited.add(i)

        return result
```

## Attempt 4 · 2023-12-27 21:06 IST · Accepted · Python3

[submission 1129792391](https://leetcode.com/submissions/detail/1129792391/) · tests 27/27 · runtime 41 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        visited = set({0})
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))
                continue

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    # path.append(s[start:i])
                    # print(visited, i)
                    # if i+1 not in visited:
                    queue.append((i, path + [s[start:i]]))
                    visited.add(i)

        return result
```

## Attempt 5 · 2023-12-27 21:07 IST · Wrong Answer · Python3

[submission 1129792787](https://leetcode.com/submissions/detail/1129792787/) · tests 18/27

Failing input:

```text
"catsanddog"
["cat","cats","and","sand","dog"]
```

Expected:

```text
["cats and dog","cat sand dog"]
```

Your output:

```text
["cat sand dog"]
```

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        visited = set({0})
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))
                continue

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    # path.append(s[start:i])
                    # print(visited, i)
                    if i not in visited:
                        queue.append((i, path + [s[start:i]]))
                        visited.add(i)

        return result
```

## Attempt 6 · 2023-12-27 21:08 IST · Accepted · Python3

[submission 1129793937](https://leetcode.com/submissions/detail/1129793937/) · tests 27/27 · runtime 32 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))
                # use continue here o that you end this path and explore more path
                # continue

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    # path.append(s[start:i])
                    # print(visited, i)
                    # if i not in visited:
                    queue.append((i, path + [s[start:i]]))
                        
        return result
```

## Attempt 7 · 2023-12-27 21:09 IST · Accepted · Python3

[submission 1129794153](https://leetcode.com/submissions/detail/1129794153/) · tests 27/27 · runtime 27 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result
```

## Attempt 8 · 2024-01-03 00:04 IST · Accepted · Python3

[submission 1134908980](https://leetcode.com/submissions/detail/1134908980/) · tests 27/27 · runtime 65 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        '''
        word_set = set(wordDict)
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)
```

## Attempt 9 · 2024-01-03 00:20 IST · Accepted · Python3

[submission 1134922385](https://leetcode.com/submissions/detail/1134922385/) · tests 27/27 · runtime 71 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        n^m * n + mk
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict)
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences
```

## Attempt 10 · 2024-01-03 00:20 IST · Accepted · Python3

[submission 1134922448](https://leetcode.com/submissions/detail/1134922448/) · tests 27/27 · runtime 67 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        n^m * n + mk
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict)
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences
```

## Attempt 11 · 2024-01-03 00:21 IST · Accepted · Python3

[submission 1134922708](https://leetcode.com/submissions/detail/1134922708/) · tests 27/27 · runtime 42 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        n^m * n + mk
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict)
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences
```

## Attempt 12 · 2024-01-26 00:50 IST · Accepted · Python3

[submission 1156779065](https://leetcode.com/submissions/detail/1156779065/) · tests 27/27 · runtime 41 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        - m is number of words
        k average length of word
        n - length of string s

        n^m * n + mk

        the number of substring - at each position either you parition it or you don't - 2^n
        
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict) 
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        # DFS function with backtracking
        def dfs(index, memo):
            if index in memo:
                return memo[index]

            if index == len(s):
                return [""]  # Return empty string for backtracking

            node = trie
            sentences = []
            for end in range(index, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]
                if '$' in node:
                    # Recursively call dfs for the rest of the string
                    for sentence in dfs(end + 1, memo):
                        # Add the current word to the sentence
                        word = s[index:end + 1]
                        if sentence:
                            sentences.append(word + " " + sentence)
                        else:
                            sentences.append(word)

            memo[index] = sentences
            return sentences

        # Call DFS and return the result
        return dfs(0, {})

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker
        memo={}
        def break_sentences(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                node = node[s[end]]

                if '$' in node:
                    for sentence in break_sentences(end+1):
                        word = s[start:end+1]
                        if sentence:
                            sentences.append(word + " "+ sentence)
                        else:
                            sentences.append(word)
            memo[start] = sentences
                    
            return memo[start]
        return break_sentences(0)
```

## Attempt 13 · 2024-01-27 03:18 IST · Accepted · Python3

[submission 1157782018](https://leetcode.com/submissions/detail/1157782018/) · tests 27/27 · runtime 38 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        - m is number of words
        k average length of word
        n - length of string s

        n^m * n + mk

        the number of substring - at each position either you parition it or you don't - 2^n
        
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict) 
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        # DFS function with backtracking
        def dfs(index, memo):
            if index in memo:
                return memo[index]

            if index == len(s):
                return [""]  # Return empty string for backtracking

            node = trie
            sentences = []
            for end in range(index, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]
                if '$' in node:
                    # Recursively call dfs for the rest of the string
                    for sentence in dfs(end + 1, memo):
                        # Add the current word to the sentence
                        word = s[index:end + 1]
                        if sentence:
                            sentences.append(word + " " + sentence)
                        else:
                            sentences.append(word)

            memo[index] = sentences
            return sentences

        # Call DFS and return the result
        return dfs(0, {})

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker
        memo={}
        def break_sentences(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                node = node[s[end]]

                if '$' in node:
                    for sentence in break_sentences(end+1):
                        word = s[start:end+1]
                        if sentence:
                            sentences.append(word + " "+ sentence)
                        else:
                            sentences.append(word)
            memo[start] = sentences
                    
            return memo[start]
        return break_sentences(0)

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker


        def segment(start):
            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                # go on looping as long as you have match 
                node= node[s[end]]

                # if found a word
                # call for rest of string
                if '$' in node:
                    word = s[start: end+1]
                    for subsentence in segment(end+1):
                        sentences.append(word+" "+subsentence if len(subsentence) else word)

            return sentences
        
        return segment(0)
```

## Attempt 14 · 2024-01-27 03:18 IST · Accepted · Python3

[submission 1157782336](https://leetcode.com/submissions/detail/1157782336/) · tests 27/27 · runtime 34 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        - m is number of words
        k average length of word
        n - length of string s

        n^m * n + mk

        the number of substring - at each position either you parition it or you don't - 2^n
        
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict) 
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        # DFS function with backtracking
        def dfs(index, memo):
            if index in memo:
                return memo[index]

            if index == len(s):
                return [""]  # Return empty string for backtracking

            node = trie
            sentences = []
            for end in range(index, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]
                if '$' in node:
                    # Recursively call dfs for the rest of the string
                    for sentence in dfs(end + 1, memo):
                        # Add the current word to the sentence
                        word = s[index:end + 1]
                        if sentence:
                            sentences.append(word + " " + sentence)
                        else:
                            sentences.append(word)

            memo[index] = sentences
            return sentences

        # Call DFS and return the result
        return dfs(0, {})

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker
        memo={}
        def break_sentences(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                node = node[s[end]]

                if '$' in node:
                    for sentence in break_sentences(end+1):
                        word = s[start:end+1]
                        if sentence:
                            sentences.append(word + " "+ sentence)
                        else:
                            sentences.append(word)
            memo[start] = sentences
                    
            return memo[start]
        return break_sentences(0)

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        @cache
        def segment(start):
            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                # go on looping as long as you have match 
                node= node[s[end]]

                # if found a word
                # call for rest of string
                if '$' in node:
                    word = s[start: end+1]
                    for subsentence in segment(end+1):
                        sentences.append(word+" "+subsentence if len(subsentence) else word)

            return sentences
        
        return segment(0)
```

## Attempt 15 · 2024-02-06 11:49 IST · Accepted · Python3

[submission 1167521775](https://leetcode.com/submissions/detail/1167521775/) · tests 27/27 · runtime 42 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        - m is number of words
        k average length of word
        n - length of string s

        n^m * n + mk

        the number of substring - at each position either you parition it or you don't - 2^n
        
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict) 
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        # DFS function with backtracking
        def dfs(index, memo):
            if index in memo:
                return memo[index]

            if index == len(s):
                return [""]  # Return empty string for backtracking

            node = trie
            sentences = []
            for end in range(index, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]
                if '$' in node:
                    # Recursively call dfs for the rest of the string
                    for sentence in dfs(end + 1, memo):
                        # Add the current word to the sentence
                        word = s[index:end + 1]
                        if sentence:
                            sentences.append(word + " " + sentence)
                        else:
                            sentences.append(word)

            memo[index] = sentences
            return sentences

        # Call DFS and return the result
        return dfs(0, {})

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker
        memo={}
        def break_sentences(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                node = node[s[end]]

                if '$' in node:
                    for sentence in break_sentences(end+1):
                        word = s[start:end+1]
                        if sentence:
                            sentences.append(word + " "+ sentence)
                        else:
                            sentences.append(word)
            memo[start] = sentences
                    
            return memo[start]
        return break_sentences(0)

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        @cache
        def segment(start):
            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for indx in range(start, len(s)):
                if s[indx] not in node:
                    break
                
                # go on looping as long as you have match 
                print('found ',s[indx],'in',node)
                node= node[s[indx]]


                # if found a word
                # call for rest of string
                if '$' in node:
                    word = s[start: indx+1]
                    for subsentence in segment(indx+1):
                        sentences.append(word+" "+subsentence if len(subsentence) else word)

            return sentences
        
        return segment(0)

    def wordBreak8(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    def wordBreak(self, s: str, wordDict: List[str] ) -> List[str]:
        """
        with memoization it would be n^2 * k number of setences 
        """
        # build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True

        # print(trie)
        # segment
        # return sentences
        memo = {}
        def segment(start:int) -> List[str]:
            if start == len(s):
                return [""]

            if start in memo:
                return memo[start]

            sentences = []
            node= trie
            for indx in range(start, len(s)):
                if s[indx] not in node:
                    break

                # check next char
                node = node[s[indx]]

                if '$' in node:
                    word = s[start: indx+1]
                    for subsentence in segment(indx+1):
                        sentences.append(word +" "+subsentence if len(subsentence) >0 else word)
            memo[start] = sentences
            return memo[start]

        return segment(0)
```

## Attempt 16 · 2024-02-06 11:56 IST · Accepted · Python3

[submission 1167527618](https://leetcode.com/submissions/detail/1167527618/) · tests 27/27 · runtime 35 ms (beats 0.3%)

```python
class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        
        words = set(wordDict)

        def dfs(startIndex):

            # base condition 
            if startIndex == len(s):
                return [""]

            sentences = []

            # child
            for endIndex in range(startIndex+1, len(s)+1):
                word = s[startIndex:endIndex]
                if word in words:
                    # sentences.append(word)
                    for subsentence in dfs(endIndex):
                         # Combine the current word with the result of the recursion
                        sentence = word + ("" if subsentence == "" else " " + subsentence)
                        sentences.append(sentence)

            return sentences
        
        return dfs(0)
        # print(sentences)


    def wordBreak3(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
    
        def dfs(start, path):
            if start == len(s):
                result.append(' '.join(path))
                return

            for end in range(start+1, len(s)+1):
                if s[start:end] in words:
                    path.append(s[start:end])
                    dfs(end, path)
                    path.pop()

        result = []
        dfs(0,[])
        return result

    def wordBreak1(self, s: str, wordDict: List[str]) -> List[str]:
        words = set(wordDict)
        
        queue = deque([(0,[])])
        # visited = set({0}) 
        # don't use visited here becaue you want to get all possible word breaks
        result = []
        while queue:
            start, path = queue.popleft()
            if start == len(s):
                result.append(' '.join(path))

            for i in range(start+1, len(s)+1):
                if s[start:i] in words:
                    queue.append((i, path + [s[start:i]]))
                        
        return result


    # ver 1
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        for a substring there could be multiple subsentences that can be
        create from this substring 
        dfs should return list of possible sentences

        - m is number of words
        k average length of word
        n - length of string s

        n^m * n + mk

        the number of substring - at each position either you parition it or you don't - 2^n
        
        extra n for substring op
        mk for set 
        space - shuold it be m or n ?

        '''
        word_set = set(wordDict) 
        def break_string(start):
            if start == len(s):
                return ['']

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                substring = s[start:end]

                # check if exists in vocabulary
                if substring in word_set:

                    # break remaining string
                    for subsentence in break_string(end):

                        # for each sentence from remaingin string
                        # combine this word and rest of words with space 
                        sentence = substring + (' ' + subsentence if len(subsentence) else '')
                        sentences.append(sentence)
            return sentences

        return break_string(0)

    #ver 2 
    # memoization solution
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    #ver 3
    # bfs
    def wordBreak6(self, s: str, wordDict: List[str]) -> List[str]:    
        sentences = []
        queue = deque([(0 , [])])
        # visited = set()
        word_set = set(wordDict)
        while queue:
            start, path = queue.popleft()

            # if start in visited:
            #     continue

            # visited.add(start)

            if start == len(s):
                sentences.append(' '.join(path))
                continue

            for end in range(start+1, len(s)+1):

                if s[start:end] in word_set:
                    queue.append((end, path + [s[start:end]]))
                    # seen.add(end)

        return sentences

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        # DFS function with backtracking
        def dfs(index, memo):
            if index in memo:
                return memo[index]

            if index == len(s):
                return [""]  # Return empty string for backtracking

            node = trie
            sentences = []
            for end in range(index, len(s)):
                char = s[end]
                if char not in node:
                    break
                node = node[char]
                if '$' in node:
                    # Recursively call dfs for the rest of the string
                    for sentence in dfs(end + 1, memo):
                        # Add the current word to the sentence
                        word = s[index:end + 1]
                        if sentence:
                            sentences.append(word + " " + sentence)
                        else:
                            sentences.append(word)

            memo[index] = sentences
            return sentences

        # Call DFS and return the result
        return dfs(0, {})

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker
        memo={}
        def break_sentences(start):
            if start in memo:
                return memo[start]

            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for end in range(start, len(s)):
                if s[end] not in node:
                    break
                
                node = node[s[end]]

                if '$' in node:
                    for sentence in break_sentences(end+1):
                        word = s[start:end+1]
                        if sentence:
                            sentences.append(word + " "+ sentence)
                        else:
                            sentences.append(word)
            memo[start] = sentences
                    
            return memo[start]
        return break_sentences(0)

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        # Build trie
        trie = {}
        for word in wordDict:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['$'] = True  # End of word marker

        @cache
        def segment(start):
            if start == len(s):
                return [""]

            node = trie
            sentences = []
            for indx in range(start, len(s)):
                if s[indx] not in node:
                    break
                
                # go on looping as long as you have match 
                print('found ',s[indx],'in',node)
                node= node[s[indx]]


                # if found a word
                # call for rest of string
                if '$' in node:
                    word = s[start: indx+1]
                    for subsentence in segment(indx+1):
                        sentences.append(word+" "+subsentence if len(subsentence) else word)

            return sentences
        
        return segment(0)

    def wordBreak8(self, s: str, wordDict: List[str]) -> List[str]:
        '''
        with memoization complexity n^*n
        '''
        memo = {}
        word_set = set(wordDict)
        def break_word(start):
            if start == len(s):
                return [""]
            
            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                # get curretn substring
                word = s[start:end]
            
                # check if exists in vocabulary
                if word in word_set:
                    rest_of_sentences = break_word(end)
                    # break remaining string
                    for sentence in rest_of_sentences:
                        sentences.append(word + (" "+sentence if len(sentence) else '' ))
                
            memo[start] = sentences
            return sentences

        return break_word(0)

    def wordBreak(self, s: str, wordDict: List[str] ) -> List[str]:
        """
        with memoization it would be n^2 * k number of setences 
        """
        # build trie
        trie = {}
        for word in wordDict:
            node = trie
            for letter in word:
                if letter not in node:
                    node[letter] = {}
                node = node[letter]
            node['$'] = True

        # print(trie)
        # segment
        # return sentences
        memo = {}
        def segment(start:int) -> List[str]:
            if start == len(s):
                return [""]

            if start in memo:
                return memo[start]

            sentences = []
            node= trie
            for indx in range(start, len(s)):
                if s[indx] not in node:
                    break

                # check next char
                node = node[s[indx]]

                if '$' in node:
                    word = s[start: indx+1]
                    for subsentence in segment(indx+1):
                        sentences.append(word +" "+subsentence if len(subsentence) >0 else word)
            memo[start] = sentences
            return memo[start]

        return segment(0)

    def wordBreak(self, s: str, wordDict: List[str] ) -> List[str]:
        words = set(wordDict)
        
        memo = {}
        def segment(start):
            if start == len(s):
                return [""]

            if start in memo:
                return memo[start]

            sentences = []
            for end in range(start+1, len(s)+1):
                word = s[start:end]
                if word in words:
                    for subsentence in segment(end):
                        sentences.append(word + " " + subsentence if len(subsentence) else word)
            memo[start] = sentences
            return sentences

        return segment(0)
```
