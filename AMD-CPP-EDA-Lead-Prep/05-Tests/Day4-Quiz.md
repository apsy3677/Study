# Day 4 Quiz: performance, Linux, OS, EDA design, leadership (20 min)
Grade 0–3 with [answers/Day4-Answers.md](answers/Day4-Answers.md). Max 60.

1. Your 5-step performance methodology in 30 seconds.
2. Your tool's runtime regressed 30% after a merge. What do you do, step by step?
3. What's the difference between `perf record` and `perf stat`? What is a flame graph showing?
4. A crash reproduces only in release builds. List 4 likely root-cause classes and your first 3 actions.
5. RSS grows steadily over a 10-hour run, but LeakSanitizer reports nothing. What's going on? How do you tell?
6. Explain NUMA and why it matters on AMD EPYC for a multithreaded EDA tool.
7. What is Amdahl's law? With 5% serial code, what's the max speedup on 128 cores?
8. Three sources of non-determinism in parallel EDA algorithms and a fix for each.
9. Describe the process memory layout from low to high addresses.
10. What happens on a page fault? Minor vs major.
11. `fork()` in a process with 8 threads: what's the danger?
12. Design: netlist DB for 100M cells: the three most important data-layout decisions and a memory estimate.
13. Design: how would you make a single-threaded router use 32 cores while keeping results deterministic?
14. What is a design checkpoint (Vivado DCP), and what engineering concerns does save/restore raise?
15. Multi-level cache design: inclusive vs exclusive, write-through vs write-back: one trade-off each.
16. Behavioral: "Tell me about a time you disagreed with a senior/architect." Give your STAR outline in 4 lines.
17. Behavioral: "How do you use AI tools in your day-to-day engineering?" (AMD asks this in 2025–26.)
18. "Why AMD, and why this role?" Give your 3-point answer.
19. "How do you mentor or grow engineers on your team?" Give two concrete mechanisms.
20. **(transfer)** The team's nightly QoR suite takes 14 hours and blocks releases. As the lead, what's your plan?
