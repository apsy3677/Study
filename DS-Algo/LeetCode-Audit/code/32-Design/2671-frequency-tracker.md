# 2671. Frequency Tracker

[Problem](https://leetcode.com/problems/frequency-tracker/) · Medium · Design → Two hash maps

LeetCode tags: hash-table, design

Attempts since Mar 2023: 1 · accepted: 1 · failed before first AC: 0

## Attempt 1 · 2024-04-20 13:21 IST · Accepted · Java

[submission 1237161463](https://leetcode.com/submissions/detail/1237161463/) · tests 1118/1118 · runtime 47 ms (beats 20%)

```java
class FrequencyTracker {
    int[] freq;
    int[] count;

    public FrequencyTracker() {
        freq = new int[100001];
        count = new int[100001];
    }
    
    public void add(int number) {
        freq[count[number]]--;
        count[number]++;
        freq[count[number]]++;
    }
    
    public void deleteOne(int number) {
        if (count[number] > 0) {
            freq[count[number]]--;
            count[number]--;
            freq[count[number]]++;
        }
    }
    
    public boolean hasFrequency(int frequency) {
        return freq[frequency] >= 1;
    }
}
/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * FrequencyTracker obj = new FrequencyTracker();
 * obj.add(number);
 * obj.deleteOne(number);
 * boolean param_3 = obj.hasFrequency(frequency);
 */
```
