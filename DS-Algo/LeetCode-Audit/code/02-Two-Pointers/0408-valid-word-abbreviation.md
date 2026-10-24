# 408. Valid Word Abbreviation

[Problem](https://leetcode.com/problems/valid-word-abbreviation/) · Easy · Two Pointers → Two-pointer parse

LeetCode tags: two-pointers, string

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-11-09 04:00 IST · Accepted · Python3

[submission 1094782340](https://leetcode.com/submissions/detail/1094782340/) · tests 323/323 · runtime 35 ms (beats 0.4%)

```python
class Solution:
    def validWordAbbreviation(self, word: str, abbr: str) -> bool:
        word_idx = 0
        abbr_idx = 0

        word_length = len(word)
        abbr_length = len(abbr)

        while word_idx < word_length and abbr_idx < abbr_length:
            if abbr[abbr_idx] == word[word_idx]:
                abbr_idx +=1
                word_idx +=1
            elif abbr[abbr_idx].isdigit():
                if abbr[abbr_idx] =='0':
                    return False
                num_start = abbr_idx
                while abbr_idx < abbr_length and abbr[abbr_idx].isdigit():
                    abbr_idx +=1

                number = int(abbr[num_start:abbr_idx])
                word_idx += number
                print(abbr_idx, word_idx)
            else:
                return False

        return word_idx == word_length and abbr_idx == abbr_length
```

## Attempt 2 · 2024-01-12 21:51 IST · Accepted · Python3

[submission 1144355158](https://leetcode.com/submissions/detail/1144355158/) · tests 323/323 · runtime 40 ms (beats 0.4%)

```python
class Solution:
    def validWordAbbreviation(self, word: str, abbr: str) -> bool:
        word_idx = 0
        abbr_idx = 0

        word_length = len(word)
        abbr_length = len(abbr)

        # 1. run for min(abbr, word)
        # min of the two - if abbr has reached end then end or if word has reached end then end
        while word_idx < word_length and abbr_idx < abbr_length:
            if abbr[abbr_idx] == word[word_idx]:
                abbr_idx +=1
                word_idx +=1
            # 2. handle digit other than zero prefix
            elif abbr[abbr_idx].isdigit():
                #edge case 1
                if abbr[abbr_idx] =='0':
                    return False

                # 3. create number by saving current index and iterating abbr as long as digits
                # num_start = abbr_idx
                # while abbr_idx < abbr_length and abbr[abbr_idx].isdigit():
                #     abbr_idx +=1

                current_num = 0
                while abbr_idx < abbr_length and abbr[abbr_idx].isdigit():
                    current_num = current_num * 10 + int(abbr[abbr_idx])
                    abbr_idx+=1

                # get number 
                number =current_num# int(abbr[num_start:abbr_idx])

                #4. increase word idx 
                word_idx += number
                print(abbr_idx, word_idx)
            else:
                #5. if any other character return false
                return False

        # success when both have reached the end successfully without returning false in between
        return word_idx == word_length and abbr_idx == abbr_length
```
