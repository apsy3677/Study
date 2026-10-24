# 2365. Task Scheduler II

[Problem](https://leetcode.com/problems/task-scheduler-ii/) · Medium · Arrays, Hashing & Sorting → Last-day map

LeetCode tags: array, hash-table, simulation

Attempts since Mar 2023: 1 · accepted: 0 · failed before first AC: 1

## Attempt 1 · 2024-01-26 04:12 IST · Time Limit Exceeded · Python3

[submission 1156893619](https://leetcode.com/submissions/detail/1156893619/) · tests 57/61

Failing input:

```text
[1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,100 ... [1099608 more chars]
```

Expected:

```text
10000000000
```

```python
class Solution:
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        last_completed = {}  # Dictionary to store the last completion day of each task type
        current_day = 0

        for task in tasks:
            print(task, last_completed)
            if task in last_completed:
                # Wait until the space constraint is satisfied
                while current_day - last_completed[task] <= space:
                    current_day += 1  # Take a break

            # Complete the task
            last_completed[task] = current_day
            current_day += 1  # Move to the next day

        return current_day

    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        last_completed = {}
        current_day = 0
        for task in tasks:
            if task in last_completed:
                # wait until space constraint
                while current_day - last_completed[task] <= space:
                    current_day+=1

            last_completed[task] = current_day
            current_day +=1
        return current_day

    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        current_day = 0
        last_completed = {}
        for task in tasks:
            if task in last_completed:
                while current_day - last_completed[task] <= space:
                    current_day +=1
            last_completed[task] = current_day
            current_day +=1

        return current_day
```
