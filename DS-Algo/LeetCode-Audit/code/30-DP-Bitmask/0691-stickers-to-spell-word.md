# 691. Stickers to Spell Word

[Problem](https://leetcode.com/problems/stickers-to-spell-word/) · Hard · DP: Bitmask → Memo over remaining letters

LeetCode tags: array, hash-table, string, dynamic-programming, backtracking, bit-manipulation, memoization, bitmask

Attempts since Mar 2023: 29 · accepted: 14 · failed before first AC: 4

## Attempt 1 · 2023-12-04 12:48 IST · Wrong Answer · Python3

[submission 1111997465](https://leetcode.com/submissions/detail/1111997465/) · tests 100/101

Failing input:

```text
["bring","plane","should","against","chick"]
"greatscore"
```

Expected:

```text
7
```

Your output:

```text
-1
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        queue = deque([(target,0)])
        visited = set(target)

        while queue:
            current, steps = queue.popleft()
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 2 · 2023-12-04 12:49 IST · Wrong Answer · Python3

[submission 1111998348](https://leetcode.com/submissions/detail/1111998348/) · tests 100/101

Failing input:

```text
["bring","plane","should","against","chick"]
"greatscore"
```

Expected:

```text
7
```

Your output:

```text
-1
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set(target)

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 3 · 2023-12-04 12:53 IST · Wrong Answer · Python3

[submission 1112000451](https://leetcode.com/submissions/detail/1112000451/) · tests 100/101

Failing input:

```text
["bring","plane","should","against","chick"]
"greatscore"
```

Expected:

```text
7
```

Your output:

```text
-1
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set(target)

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 4 · 2023-12-04 12:55 IST · Wrong Answer · Python3

[submission 1112001424](https://leetcode.com/submissions/detail/1112001424/) · tests 100/101

Failing input:

```text
["bring","plane","should","against","chick"]
"greatscore"
```

Expected:

```text
7
```

Your output:

```text
-1
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(''.join(sorted(target)), 0)])
        visited = set(''.join(sorted(target)))


        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 5 · 2023-12-04 12:56 IST · Accepted · Python3

[submission 1112001777](https://leetcode.com/submissions/detail/1112001777/) · tests 101/101 · runtime 951 ms (beats 31.3%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 6 · 2023-12-04 12:56 IST · Accepted · Python3

[submission 1112001890](https://leetcode.com/submissions/detail/1112001890/) · tests 101/101 · runtime 931 ms (beats 31.3%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 7 · 2023-12-22 00:43 IST · Accepted · Python3

[submission 1125331930](https://leetcode.com/submissions/detail/1125331930/) · tests 101/101 · runtime 856 ms (beats 31.5%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1
```

## Attempt 8 · 2023-12-22 02:53 IST · Output Limit Exceeded · Python3

[submission 1125395706](https://leetcode.com/submissions/detail/1125395706/) · tests 66/101

Failing input:

```text
["win","move","back","son","feet","street","sight","sing","earth","ship","quiet","special","sugar","guess","end","also","favor","create","fight","mix","hot","strange","hill","interest","correct","exercise","told","swim","good","door","farm","object","famous","insect","verb","particular","sheet","those","dry","protect","kept","roll","always","drive","agree","fruit","were","whole","wing","wind"]
"wo ... [7 more chars]
```

Expected:

```text
4
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 9 · 2023-12-22 02:54 IST · Accepted · Python3

[submission 1125395839](https://leetcode.com/submissions/detail/1125395839/) · tests 101/101 · runtime 2864 ms (beats 16.9%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 10 · 2023-12-22 02:54 IST · Output Limit Exceeded · Python3

[submission 1125395919](https://leetcode.com/submissions/detail/1125395919/) · tests 66/101

Failing input:

```text
["win","move","back","son","feet","street","sight","sing","earth","ship","quiet","special","sugar","guess","end","also","favor","create","fight","mix","hot","strange","hill","interest","correct","exercise","told","swim","good","door","farm","object","famous","insect","verb","particular","sheet","those","dry","protect","kept","roll","always","drive","agree","fruit","were","whole","wing","wind"]
"wo ... [7 more chars]
```

Expected:

```text
4
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 11 · 2023-12-22 02:54 IST · Output Limit Exceeded · Python3

[submission 1125396185](https://leetcode.com/submissions/detail/1125396185/) · tests 66/101

Failing input:

```text
["win","move","back","son","feet","street","sight","sing","earth","ship","quiet","special","sugar","guess","end","also","favor","create","fight","mix","hot","strange","hill","interest","correct","exercise","told","swim","good","door","farm","object","famous","insect","verb","particular","sheet","those","dry","protect","kept","roll","always","drive","agree","fruit","were","whole","wing","wind"]
"wo ... [7 more chars]
```

Expected:

```text
4
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 12 · 2023-12-22 02:54 IST · Accepted · Python3

[submission 1125396254](https://leetcode.com/submissions/detail/1125396254/) · tests 101/101 · runtime 2636 ms (beats 18.4%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 13 · 2023-12-22 02:55 IST · Accepted · Python3

[submission 1125396531](https://leetcode.com/submissions/detail/1125396531/) · tests 101/101 · runtime 828 ms (beats 31.5%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 14 · 2023-12-22 02:55 IST · Accepted · Python3

[submission 1125396563](https://leetcode.com/submissions/detail/1125396563/) · tests 101/101 · runtime 847 ms (beats 31.5%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1
```

## Attempt 15 · 2023-12-26 20:30 IST · Accepted · Python3

[submission 1128940457](https://leetcode.com/submissions/detail/1128940457/) · tests 101/101 · runtime 2781 ms (beats 18.0%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps
            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1
```

## Attempt 16 · 2024-01-03 22:37 IST · Accepted · Python3

[submission 1135829227](https://leetcode.com/submissions/detail/1135829227/) · tests 101/101 · runtime 246 ms (beats 46.1%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers5(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] > 0:  # Check if sticker can contribute to target
                    remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                    res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                    if res != -1:
                        min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        


    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 17 · 2024-01-24 02:11 IST · Wrong Answer · Python3

[submission 1154965626](https://leetcode.com/submissions/detail/1154965626/) · tests 7/101

Failing input:

```text
["with","example","science"]
"thehat"
```

Expected:

```text
3
```

Your output:

```text
2
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) for sticker in stickers]

        # return min number of stickers
        def count_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                print('applying sticker', sticker_counter, 'to target', target_counter)
                new_target_counter = target_counter - sticker_counter
                if target_counter == new_target_counter:
                    continue
                new_target = ''.join(new_target_counter.keys())
                
                
                res = count_stickers(new_target)
                if res != '-1':
                    min_stickers = min(min_stickers, 1+ res)

            return -1 if min_stickers == float('inf') else min_stickers

        return count_stickers(target)


            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 18 · 2024-01-24 02:22 IST · Time Limit Exceeded · Python3

[submission 1154972440](https://leetcode.com/submissions/detail/1154972440/) · tests 25/101

Failing input:

```text
["swim","love","father","shape","rich","multiply","new","fill","history"]
"operateform"
```

Expected:

```text
4
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 

        # return min number of stickers
        def count_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                # if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                #     continue
                remaining_target = target_counter - sticker_counter 
                if target_counter == remaining_target:
                    continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)

            return -1 if min_stickers == float('inf') else min_stickers

        return count_stickers(target)


            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 19 · 2024-01-24 02:23 IST · Time Limit Exceeded · Python3

[submission 1154972762](https://leetcode.com/submissions/detail/1154972762/) · tests 32/101

Failing input:

```text
["control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean"]
"stoodcrease"
```

Expected:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 

        # return min number of stickers
        def count_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)

            return -1 if min_stickers == float('inf') else min_stickers

        return count_stickers(target)


            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 20 · 2024-01-24 02:25 IST · Accepted · Python3

[submission 1154974248](https://leetcode.com/submissions/detail/1154974248/) · tests 101/101 · runtime 261 ms (beats 45.5%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)


            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 21 · 2024-01-24 02:31 IST · Accepted · Python3

[submission 1154977367](https://leetcode.com/submissions/detail/1154977367/) · tests 101/101 · runtime 3421 ms (beats 11.9%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 




            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 22 · 2024-02-03 02:25 IST · Wrong Answer · Python3

[submission 1164257844](https://leetcode.com/submissions/detail/1164257844/) · tests 32/101

Failing input:

```text
["travel","quotient","nose","wrote","any"]
"lastwest"
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def find_min_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            
            for sticker_counter in sticker_counters:
                if target[0] not in sticker_counter:
                    continue

                #apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.keys())

                stickers_count = find_min_stickers(remaining_target)
                if stickers_count != -1:
                    min_stickers = min(min_stickers, 1+ stickers_count)

            return min_stickers if min_stickers != float('inf') else -1
            
        return find_min_stickers(target) 



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 23 · 2024-02-03 02:26 IST · Wrong Answer · Python3

[submission 1164258554](https://leetcode.com/submissions/detail/1164258554/) · tests 31/101

Failing input:

```text
["travel","quotient","nose","wrote","any"]
"lastwest"
```

Expected:

```text
4
```

Your output:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def find_min_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            
            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue

                #apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.keys())

                stickers_count = find_min_stickers(remaining_target)
                if stickers_count != -1:
                    min_stickers = min(min_stickers, 1+ stickers_count)

            return min_stickers if min_stickers != float('inf') else -1
            
        return find_min_stickers(target) 



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 24 · 2024-02-03 02:27 IST · Time Limit Exceeded · Python3

[submission 1164259387](https://leetcode.com/submissions/detail/1164259387/) · tests 32/101

Failing input:

```text
["control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean"]
"stoodcrease"
```

Expected:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def find_min_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            
            for sticker_counter in sticker_counters:
                if target[0] not in sticker_counter:
                    continue

                #apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                stickers_count = find_min_stickers(remaining_target)
                if stickers_count != -1:
                    min_stickers = min(min_stickers, 1+ stickers_count)

            return min_stickers if min_stickers != float('inf') else -1
            
        return find_min_stickers(target) 



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 25 · 2024-02-03 02:29 IST · Time Limit Exceeded · Python3

[submission 1164260405](https://leetcode.com/submissions/detail/1164260405/) · tests 32/101

Failing input:

```text
["control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean"]
"stoodcrease"
```

Expected:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def find_min_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            
            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue

                #apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                stickers_count = find_min_stickers(remaining_target)
                if stickers_count != -1:
                    min_stickers = min(min_stickers, 1+ stickers_count)

            return min_stickers if min_stickers != float('inf') else -1
            
        return find_min_stickers(target) 



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 26 · 2024-02-03 02:30 IST · Time Limit Exceeded · Python3

[submission 1164260825](https://leetcode.com/submissions/detail/1164260825/) · tests 32/101

Failing input:

```text
["control","heart","interest","stream","sentence","soil","wonder","them","month","slip","table","miss","boat","speak","figure","no","perhaps","twenty","throw","rich","capital","save","method","store","meant","life","oil","string","song","food","am","who","fat","if","put","path","come","grow","box","great","word","object","stead","common","fresh","the","operate","where","road","mean"]
"stoodcrease"
```

Expected:

```text
3
```

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def find_min_stickers(target):
            if not target:
                return 0

            min_stickers = float('inf')
            target_counter = Counter(target)
            
            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue

                #apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                stickers_count = find_min_stickers(remaining_target)
                if stickers_count != -1:
                    min_stickers = min(min_stickers, 1+ stickers_count)

            return min_stickers if min_stickers != float('inf') else -1
            
        # return find_min_stickers(target) 

        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 27 · 2024-02-03 02:35 IST · Accepted · Python3

[submission 1164263323](https://leetcode.com/submissions/detail/1164263323/) · tests 101/101 · runtime 260 ms (beats 45.7%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        # return find_min_stickers(target) 
        memo= {"":0}
        def find_min_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)
            
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        # print(''.join(Counter(target).elements()))
        res = find_min_stickers(target)
        # print(memo)
        return res



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 28 · 2024-02-03 02:35 IST · Accepted · Python3

[submission 1164263373](https://leetcode.com/submissions/detail/1164263373/) · tests 101/101 · runtime 262 ms (beats 45.5%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        # return find_min_stickers(target) 
        memo= {"":0}
        def find_min_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)
            
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        # print(''.join(Counter(target).elements()))
        res = find_min_stickers(target)
        # print(memo)
        return res



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```

## Attempt 29 · 2024-02-03 02:39 IST · Accepted · Python3

[submission 1164265403](https://leetcode.com/submissions/detail/1164265403/) · tests 101/101 · runtime 251 ms (beats 46.1%)

```python
class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:

        """
        explore all the possible states - apply each sticker and then explore all possible states -> 
        for target "thehat", apply -> with, example, science and after applying each you will get new target -> add those new targets to the queue -> this will give all states after applying 1 sticker

        same way apply again all stickers to get states after 2 stickers

        maintain a queue of new states after applying all stickers
        start with target
        """

        # for each letter in current, 
        # remove all character common in current 
        def applySticker(current, sticker):
            remaining = list(current)
            for ch in sticker:
                if ch in remaining:
                    remaining.remove(ch)
            return ''.join(remaining)

        # with zero stickers applied this is the state
        queue = deque([(target,0)])
        visited = set({target})

        while queue:
            current, steps = queue.popleft()

            # final condition when currnet is total empty
            if not current:
                return steps


            for sticker in stickers:
                new_state = applySticker(current, sticker)
                if new_state not in visited:
                    # print(new_state, sticker)
                    # with 1 more sticker applied this is the new state
                    queue.append((new_state,steps+1))
                    visited.add(new_state)
        return -1


    def minStickers3(self, stickers: List[str], target: str) -> int:
        
        targetCounter = Counter(target)
        queue = deque([(targetCounter,0)])
        visited = set({tuple(targetCounter.items())})
        # print(visited)
        steps = 0


        def applySticker(stickerCounter, targetCounter):
            # print(targetCounter - stickerCounter )
            return targetCounter - stickerCounter 
        
        # filter letters in each sticker - to keep only ones which are present in target as well
        processedStickers = [Counter(sticker) & targetCounter for sticker in stickers]

        while queue:
            # print(queue.popleft())
            currentCounter, steps = queue.popleft()

            if not currentCounter:
                return steps

            for stickerCounter in processedStickers:
                new_state = applySticker(stickerCounter, currentCounter)
                new_state_tuple = tuple(new_state.items()) 
                if new_state_tuple not in visited:
                    queue.append((new_state, steps+1))
                    visited.add(new_state_tuple)
        return -1

    def minStickers(self, stickers: List[str], target: str) -> int:

        '''
        time complexity - 
        number of states = 2^target 
        for each state - apply each sticker (number of sticker * lenght of sticker)
        '''
        targetCounter = Counter(target)
        stickerCounters = [Counter(sticker) for sticker in stickers]

        queue = deque([(targetCounter, 0)])
        targetCounterTuple = tuple(targetCounter.items())
        visited = set({targetCounterTuple})

        # for each new state after applying sticker save it in queue
        while queue:
            newTargetCounter, steps = queue.popleft()

            if not newTargetCounter:
                return steps

            for stickerCounter in stickerCounters:
                # apply sticker
                newState = newTargetCounter - stickerCounter
                newStateTuple = tuple(newState.items())

                if newStateTuple not in visited:
                    queue.append((newState, steps+1))
                    visited.add(newStateTuple)

        return -1


    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]
        
        memo = {}
        memo[""] = 0
        
        def dp(remaining):
            # base condition
            if remaining in memo:
                return memo[remaining]
            
            remaining_counter = Counter(remaining)

            # set the infinity 
            # not possible initially
            min_stickers = float('inf')
            
            # for each sticker
            for sticker in sticker_counters:
                print('for', remaining, 'trying ', ''.join(sticker.elements()))
                if sticker[remaining[0]] == 0:  # Optimization: skip stickers that don't contain the first char of remaining
                    continue
                
                # Form the new remaining string after using the sticker
                new_remaining = remaining_counter - sticker
                
                # recursive dp part
                next_try = dp(''.join(new_remaining.elements()))
                print('next_try',next_try)

                # if possible
                if next_try != -1:

                    # find min_stickers from all stickers to get current target
                    min_stickers = min(min_stickers, 1 + next_try)
                    print(min_stickers)

            # update dp table
            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            print(memo)

            # return dp table
            return memo[remaining]
        
        return dp(target)

    # ver1 
    # backtracking or recursion without memoization
    def minStickers(self, stickers, target):
        '''
        M choices stickers
        L avg length of sticker
        for target length of N
        M^N * 

        so total time complexity is
        O(ML) - sticker initialization 
        total number of calls - total states in backtracking - M^N
        each call has additional cost of O(N+L)

        total - O(ML) + O(M^N * (N+L))

        space - O(ML) - for sticker
        recursion tree - O(N)
        result - 

        '''
        sticker_counters = [Counter(sticker) for sticker in stickers] # O(ML) 
        def find_min_stickers(target):
            if not target:
                return 0

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)

            return -1 if min_stickers == float('inf') else min_stickers

        return find_min_stickers(target)

    # ver2 
    # backtracking or recursion with memoization
    def minStickers4(self, stickers, target):
        '''
        1. create a memo table with base case
        2. check is string is in memo
        3. apply all choices -> get min result of all choices
        if the result is not possible with all choices, keep result = inf
        - if previously explore string and not possible to build target, save -1 in memoization and hence don't set min_stickers
        - if new, initially set inf and then after applying all cohices, check if 


        time 
        O(ML) - sticker initilaization
        total number of unique states - maximum upperlimit - all possible subsets - 2^n

        '''

        #1. base case
        memo = {"": 0}
        sticker_counters = [Counter(sticker) for sticker in stickers]

        def dp(target):
            # 2. if exists in memo
            if target in memo:
                return memo[target]

            target_counter = Counter(target)

            #3. set default result - impossible
            min_stickers = float('inf')

            # 
            for sticker_counter in sticker_counters:
                # If the sticker can't contribute a letter not in target, skip it
                if not sticker_counter[target[0]]:
                    continue

                remaining_target = target_counter - sticker_counter
                temp_stickers = dp(''.join(remaining_target.elements()))

                if temp_stickers != -1:
                    min_stickers = min(min_stickers, 1 + temp_stickers)

            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return dp(target)

    
        
    def minStickers(self, stickers, target):
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers] # O(ML) 
        memo = {"":0}
        # return min number of stickers
        def count_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                # print('applying sticker', sticker_counter, 'to target', target_counter)
                if sticker_counter[target[0]] == 0:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter 
                # if target_counter == remaining_target:
                #     continue
                res = count_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1+ res)
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        return count_stickers(target)

    def minStickers(self, stickers, target):
        queue = deque([(target,0)]) # state, stickets
        visited = set()
        visited.add(target)
        sticker_counters = [Counter(sticker) & Counter(target) for sticker in stickers]

        while queue:
            target, sticker_count = queue.popleft()
            if target == "":
                return sticker_count

            target_counter = Counter(target)
            for sticker_counter in sticker_counters:
                # apply sticker
                remaining_target_counter = target_counter - sticker_counter
                remaining_target = ''.join(remaining_target_counter.elements())

                if remaining_target not in visited:
                    queue.append((remaining_target, sticker_count+1))
                    visited.add(remaining_target)
        return -1 

class Solution:
    def minStickers(self, stickers: List[str], target: str) -> int:
        sticker_counters = [Counter(sticker) for sticker in stickers]

        # return find_min_stickers(target) 
        memo= {"":0}
        def find_min_stickers(target):
            if target in memo:
                return memo[target]

            target_counter = Counter(target)
            min_stickers = float('inf')

            for sticker_counter in sticker_counters:
                if target[0]  not in sticker_counter:  # Check if sticker can contribute to target
                    continue
                remaining_target = target_counter - sticker_counter # O(L) lenth of sticker 
                # if len(remaining_target) == len(target_counter):
                #     continue
                res = find_min_stickers(''.join(remaining_target.elements())) # O(N)
                if res != -1:
                    min_stickers = min(min_stickers, 1 + res)
            
            memo[target] = -1 if min_stickers == float('inf') else min_stickers
            return memo[target]

        # print(''.join(Counter(target).elements()))
        res = find_min_stickers(target)
        # print(memo)
        return res



            

    




# Example usage
# sol = Solution()
# print(sol.minStickers(["sticker1", "sticker2"], "target"))
```
