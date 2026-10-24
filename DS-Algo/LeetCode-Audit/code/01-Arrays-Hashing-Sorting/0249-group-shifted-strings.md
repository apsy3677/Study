# 249. Group Shifted Strings

[Problem](https://leetcode.com/problems/group-shifted-strings/) · Medium · Arrays, Hashing & Sorting → Canonical key

LeetCode tags: array, hash-table, string

Attempts since Mar 2023: 2 · accepted: 2 · failed before first AC: 0

## Attempt 1 · 2023-12-01 09:38 IST · Accepted · Python3

[submission 1109959184](https://leetcode.com/submissions/detail/1109959184/) · tests 25/25 · runtime 48 ms (beats 4.6%)

```python
class Solution:
    def groupStrings(self, strings: List[str]) -> List[List[str]]:
        
        # Create a hash value
        def get_hash(string: str):
            key = []
            for a, b in zip(string, string[1:]):
                key.append(chr((ord(b) - ord(a)) % 26 ))
            return ''.join(key)
        
        # Create a hash value (hash_key) for each string and append the string
        # to the list of hash values i.e. mapHashToList["cd"] = ["acf", "gil", "xzc"]
        groups = collections.defaultdict(list)
        for string in strings:
            hash_key = get_hash(string)
            groups[hash_key].append(string)
        
        # Return a list of all of the grouped strings
        return list(groups.values())
```

## Attempt 2 · 2023-12-04 21:00 IST · Accepted · Python3

[submission 1112242328](https://leetcode.com/submissions/detail/1112242328/) · tests 25/25 · runtime 62 ms (beats 4.6%)

```python
class Solution:
    def groupStrings(self, strings: List[str]) -> List[List[str]]:
        
        '''
        time complexity - for each string O(N), iterate over all chars O(k)
        '''
        # Create a hash value
        def get_hash(string: str):
            key = []

            # compare letter with next letter in a string
            for a, b in zip(string, string[1:]):
                print(a,b)

                # you can keep ord(b) - ord(a) as key but what about negative 
                # maybe you can use abs but what about if 1 and 1 are treated as 11 or two 1s
                # that is the reason you convert it into char
                # substract unicode code point value of a and b
                key.append(chr((ord(b) - ord(a)) % 26 + ord('a')))
                print((ord(b) - ord(a)), (ord(b) - ord(a)) % 26)
            print(key)
            return ''.join(key)
        
        # Create a hash value (hash_key) for each string and append the string
        # to the list of hash values i.e. mapHashToList["cd"] = ["acf", "gil", "xzc"]

        # create hash key to strings list
        groups = collections.defaultdict(list)

        # for each string
        for string in strings:

            # get hash
            hash_key = get_hash(string)

            # add to hashgroup
            groups[hash_key].append(string)
        
        # Return a list of all of the grouped strings
        return list(groups.values())
```
