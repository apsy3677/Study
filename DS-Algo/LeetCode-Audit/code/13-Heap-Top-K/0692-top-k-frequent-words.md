# 692. Top K Frequent Words

[Problem](https://leetcode.com/problems/top-k-frequent-words/) · Medium · Heap / Top-K → Top-K with heap

LeetCode tags: array, hash-table, string, trie, sorting, heap-priority-queue, bucket-sort, counting

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2024-01-28 02:51 IST · Wrong Answer · Python3

[submission 1158610943](https://leetcode.com/submissions/detail/1158610943/) · tests 31/110

Failing input:

```text
["i","love","leetcode","i","love","coding"]
1
```

Expected:

```text
["i"]
```

Your output:

```text
["love"]
```

```python
class Solution:
    def topKFrequent(self, words: List[str], k: int) -> List[str]:
        freq = Counter(words)
        min_heap = []

        for word in freq.keys():
            heapq.heappush(min_heap, (freq[word] , word))
            if len(min_heap) > k:
                heapq.heappop(min_heap)
                
        return [word for _, word in sorted(min_heap, key = lambda x: (-x[0],x[1]))]
```
