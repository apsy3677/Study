# 211. Design Add and Search Words Data Structure

[Problem](https://leetcode.com/problems/design-add-and-search-words-data-structure/) · Medium · Trie → Wildcard DFS

LeetCode tags: string, depth-first-search, design, trie

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2023-12-31 08:40 IST · Accepted · Python3

[submission 1132671929](https://leetcode.com/submissions/detail/1132671929/) · tests 29/29 · runtime 2221 ms (beats 5.0%)

```python
class WordDictionary:

    def __init__(self):
        self.trie = {}

    def addWord(self, word: str) -> None:
        node = self.trie
        for letter in word:
            if letter not in node:
                node[letter] = {}
            node = node[letter]
        node['$'] = True

    def search(self, word: str) -> bool:
        def dfs(j, node):
            for i in range(j, len(word)):
                letter = word[i]
                if letter == '.':
                    for child in node:
                        if child != '$' and dfs(i + 1, node[child]):
                            return True
                    return False
                else:
                    if letter not in node:
                        return False
                    node = node[letter]
            return '$' in node

        return dfs(0, self.trie)
```
