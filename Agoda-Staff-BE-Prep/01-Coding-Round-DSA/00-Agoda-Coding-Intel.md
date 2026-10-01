# Agoda IV1 Coding Round: Intel (researched 1 Oct 2026)

> **Method** (same as the AMD prep's `00-Intel`): (1) what your recruiter told you, (2) Agoda candidate reports from 2025–26, read directly on LeetCode Discuss, (3) the LeetCode **Agoda company tag** (frequency + recency, via DSAPrep and CodingKaro), (4) **your own interview history** in this repo.
> Every claim is tagged with its source, so you can judge its weight. "Our ID" maps to the practice files (`practice/agoda_dayN.cpp`) and to `03-Problem-Bank.md`.

---

## 1. Ground truth: what Eve sent you

| Round | Content |
|---|---|
| **IV1 Coding** | **2 problems on HackerRank.** Practise LeetCode **medium–difficult**. ← this folder |
| IV2 Platform | System design, connectivity, QA, code review |
| IV3 Architecture | Low- and high-level design |
| IV4 | Overall technical + culture fit |

**IV1 rubric (Agoda's own words, condensed):**
1. **Understanding the problem:** structured approach. Clarify requirements, discuss possible solutions, choose the most efficient one, and explain your reasoning.
2. **Coding efficiency:** clean, working code written confidently. Show **advanced features and syntax of your language**. Debug efficiently.
3. **Testing:** a wide range of conditions, and you must **justify your choice of test scenarios**.
4. **Communication:** clear and concise, a smooth conversation with **minimal prompting**, and **proactively introduce new topics or ideas**.

Two of the four areas (testing and communication) aren't about the algorithm at all. The playbook (`01-Live-Round-Playbook.md`) is built around this.

---

## 2. What the round looks like (from reports)

- **60 minutes, live, HackerRank CodePair.** The interviewer is usually a **Staff/Senior engineer from the Bangkok office**. *(LC 7274226 Gurugram, LC 7551684 Gurugram, LC 7082771)*
- **You must run the code and pass all test cases live.** One report says: *"You were expected to code, run, and pass all test cases live."* *(LC 7237792)*
- It may **start with a short resume chat** (*"you seem to have worked on a lot of things…"*), which leaves less coding time. *(LC 7551684, Gurugram Staff, Feb 2026)*
- **Typical mix:** one medium plus one easy-to-medium, often a **"variant of"** a known problem, dressed in a travel or business story (airplanes, molecules, priorities, bookings).
- **Pace that earns "Strong Hire":** both problems done in about 35 minutes, then a chat. *(LC 7199643)*
- Some loops use an **OA** instead of, or before, the live round: HackerRank, 75–110 minutes, **1 DSA + 1 REST/HTTP task** ("plain vanilla HTTP client basics, call an endpoint, parse JSON"). Your recruiter described a live 2-problem round. If an OA shows up instead, we'll prep the HTTP part with the Platform round. *(LC 7237792, 6859065, 7380748, 7565801)*

---

## 3. Reported questions, 2025–26 (and one older Gurgaon report)

| When | Role, location | Round | Questions | Our ID |
|---|---|---|---|---|
| Oct 2025 | **SSE Backend, Gurugram.** The candidate's prep-guide link was named `…prepguide-be-shp-ic3…`, so this is **the same [SHP] backend track as yours** | R1 live, 1 h, Staff engineer from Bangkok | (1) **Variation of LC 1921 Eliminate Maximum Number of Monsters, "imagine airplanes instead of monsters"** (greedy). (2) **Molecule weight:** atoms C=12, H=1, O=8; `CH4`=16, `H(CH4)2`=33 (stack) | **G1, S1** |
| Feb 2026 | **Staff, Gurugram** | R1 (opened with a resume chat) | (1) **variant of "largest greater number on the right side"**. (2) **largest substring with distinct characters** | **M1, W1** |
| Dec 2025 | Senior/Staff MLE | R1 | **Variation of LC 726 Number of Atoms**, i.e. molecule weight from fixed atom weights. *"Got the base test cases down but was failing on some"* | **S1, S2** |
| Aug 2025 | Staff, Bangkok | HackerRank, 3 questions, 1 h | **pairs with minimum absolute difference**; **count palindromic substrings** (*"passed all test cases but could not optimize"*); **binary search very similar to Koko eating bananas**. Feedback: *"Strong coding skills"* | **G2, G3, P1, B1–B3** |
| Jul 2025 | Staff Backend, Bangkok | OA: 1 LC hard + 1 HTTP-client API. **R2 live:** 2 questions | **variation of Stock Buy/Sell**; **a DP similar to Jump Game** | **J5–J7, J1–J4** |
| 2026 | Staff, Bangkok (**selected**) | R1 | **monotonic stack, nearest smaller element**; **ranks of every element in an array of priorities** (higher number = higher rank) | **M2, G4** |
| Feb 2026 | SSE Backend, Bangkok | OA: medium graph/tree + HTTP request/response. **R2 live:** | **binary search/sorting variation**; **Jump Game variant (DP)** | **B\*, J\*** |
| 2025 | SSE, Bangkok relocation | OA: **binary search "maximum of minimum"** + call an endpoint and parse JSON. **Live:** | **monotonic stack, like next greater element**; **backspace string compare** | **B3, M1, S6** |
| Nov 2025 | Staff SE | OA (1 DSA + 1 REST API for book management) | **Minimum Operations to Make All Array Elements Equal** (LC 2602), per CodingKaro's summary; the post's text was in images | **B4** |
| Jul 2025 | SE IC1 (contract) | OA | **lexicographically smallest task queue** (swap 1↔2, 2↔3); **discount coupons** (halve a price, several coupons per item) | **G7, G6** |
| (Glassdoor) | Staff, India | coding | **how many airplanes can be shot down before any lands**; **all pivot elements in an unsorted array** | **G1, M3** |
| Aug 2021 | Senior Backend, Gurgaon | screening | first unique character; **task scheduler** (n = 2); delete characters to make a fancy string | **G8** |

## 4. The LeetCode Agoda tag (DSAPrep, last updated Aug 2026: 86 questions)

- **Difficulty:** 34% easy, 61% medium, 5% hard.
- **Patterns:** Array 68% · String 28% · Hash table 25% · **Sorting 23%** · DP 20% · Two pointers 20% · **Stack 15%** · Greedy 13% · Sliding window 10% · Math 8%.
- **Asked in the last 3 months:** 1011 Capacity to Ship (B1) · **1921 Eliminate Monsters (G1)** · **1209 Remove Adjacent Duplicates II (S5)** · **3893 Max Team Size with Overlapping Intervals (I1)** · 78 Subsets · **726 Number of Atoms (S1/S2)**.
- **Last 6 months:** 1200 Min Abs Difference (G2) · 1331 Rank Transform (G4) · 394 Decode String (S3) · 322 Coin Change · 75 Sort Colors · 55 Jump Game (J1).
- **Older:** 1636 freq sort (G5) · 496/739 next greater/daily temps · 844 backspace (S6) · 724 pivot index · 1011/875/1283 binary search (B\*) · 1190 reverse parens (S4) · 713 product < K (W4) · 120 triangle (J8) · 300 LIS · 1048 string chain (P5) · 767 reorganize (G9) · 380 RandomizedSet (H1) · 239 sliding window max · 3 · 15 · 121 · 198 · 63 · 46 · 12.

## 5. What this means: priorities for 3 days

| Rank | Family | Evidence | Where |
|---|---|---|---|
| 1 | **Stack parsing** (nested formulas, decode, reverse in parens, adjacent removal) | Molecule weight asked **twice** in 3 months, plus 3 tag problems | Day 1, S |
| 2 | **Monotonic stack variants** (next greater/smaller, circular, spans) | 3 live-round reports | Day 1, M |
| 3 | **Binary search on the answer** (min capacity, max-of-min, queries) | 3–4 reports + tag | Day 2, B |
| 4 | **Greedy + sorting** (deadlines, adjacent pairs, ranks, heaps) | Airplanes asked twice; pairs, ranks; 2 OA problems | Day 2, G |
| 5 | **Jump Game / Stock DP** | 3 reports (Staff and SSE, Bangkok) | Day 3, J |
| 6 | **Sliding window** (distinct chars, at most k) | Gurugram Staff 2026 + tag | Day 1, W |
| 7 | **Palindromes / string DP** | 1 report (the "couldn't optimize" one) + tag | Day 3, P |
| 8 | Intervals and bookings, hash design, routes | Tag (3893, 380) + travel domain | Day 2 I, Day 3 H/R |

**Not seen in Agoda's live rounds:** linked lists, tree-heavy problems, hard graph theory, heavy DP. Unlike the AMD prep, **don't spend time on linked lists**. Keep trees and graphs at "can do BFS/DFS cleanly" (only one OA mentioned a graph/tree question).

**Twists are the norm.** "Variant of" appears in most reports, so learn the *mechanism* (invariant + template), not the answer. The story will be dressed up.

## 6. Why people failed (from the same reports)
- **Didn't optimize.** Brute-force palindromes passed the tests, but the optimization wasn't there (Aug 2025). → Always state the better complexity, even if you code the simple one first.
- **Failed hidden tests** on the molecule problem (Dec 2025). → Multi-digit counts, two-letter atoms, nesting, a `)` with no count, long long. Test matrix: Playbook §4.
- **Lost 25 minutes misunderstanding the problem** (Gurugram Staff, R2). → Restate and run one example before solving.
- **Later rounds** reject on platform/connectivity and on values/culture, not on DSA. Those come later.

## 7. Your own history: what to fix (from this repo)

| Evidence | Pattern | Fix in this plan |
|---|---|---|
| `Interviews-2023/Uber-Feedback.txt`: *"Don't miss edge cases"*, *"Code readability should be better"*, *"Naming convention and clarity in code"* | Exactly 2 of Agoda's 4 rubric areas (testing, clean code) | Every stub asks you to **write your own tests before coding**. Playbook §4 (test matrix) and §6 (naming). |
| `Interviews-2023/Google-R2.txt` (Meeting Rooms III): `priorty_queue`, `pq.top.second`, `int maxi = 0 ans =0`, unbalanced `(` | Typos under pressure. On HackerRank each typo costs a compile cycle and looks careless. | Compile the skeleton early. Run the 60-second pre-Run checklist (Playbook §7). **I5 is that exact problem: a rematch.** |
| `I-2025/Cadence-R1.txt` (path between nodes): `findPathHelper(root->left…) \|\| findPathHelper(root->left…)` (left twice), `reurn`, `grater` | Copy-paste symmetry bug that a dry run would catch | "Symmetric code" item on the checklist. Dry-run one case before pressing Run. |
| CodeChef 1974, Codeforces 1693, Striver sheet 2023 | **Algorithmic ceiling isn't the risk.** Rust, speed, narration and test discipline are. | Timed practice + mocks scored on Agoda's 4 areas. Avoid CP habits (macros, `#define int long long`, one-letter names): they read badly at Staff level. |

---

## Sources
- [LC Discuss: Agoda SSE Backend, Gurugram, reject (Oct 2025): airplanes + molecule weight](https://leetcode.com/discuss/post/7274226/)
- [LC Discuss: Agoda Staff Engineer, Gurugram (Feb 2026): next greater variant + distinct substring](https://leetcode.com/discuss/post/7551684/)
- [LC Discuss: Agoda Senior/Staff MLE (Dec 2025): Number of Atoms variant](https://leetcode.com/discuss/post/7482642/)
- [LC Discuss: Agoda Staff, Bangkok (Jul–Aug 2025): min abs diff pairs, palindromic substrings, Koko-like](https://leetcode.com/discuss/post/7082771/)
- [LC Discuss: Agoda Staff Backend (Jul 2025): stock variant + Jump Game DP; "run and pass all tests live"](https://leetcode.com/discuss/post/7237792/)
- [LC Discuss: Agoda Staff, Bangkok, selected (2026): nearest smaller + ranks](https://leetcode.com/discuss/post/7755434/)
- [LC Discuss: Agoda SSE Backend, Bangkok (Feb 2026): binary search/sorting + Jump Game variant](https://leetcode.com/discuss/post/7565801/)
- [LC Discuss: Agoda SSE (2025): max-of-min binary search, next greater, backspace compare](https://leetcode.com/discuss/post/6859065/)
- [LC Discuss: Agoda Staff SE OA (Nov 2025)](https://leetcode.com/discuss/post/7380748/) and the [CodingKaro Agoda summary](https://www.codingkaro.in/jobs-internships/leetcode-interview-experience/Agoda)
- [LC Discuss: Agoda SE IC1 OA (Jul 2025): task queue + coupons](https://leetcode.com/discuss/post/7007178/)
- [LC Discuss: Agoda full-stack, Bangkok: both problems in 35 min, "Strong Hire"](https://leetcode.com/discuss/post/7199643/)
- [LC Discuss: Agoda Staff (2025): 2 LC medium](https://leetcode.com/discuss/post/6344830/)
- [LC Discuss: Agoda Senior Backend, Gurgaon (Aug 2021)](https://leetcode.com/discuss/post/1410711/)
- [Glassdoor: Agoda interview review (airplanes, pivot elements)](https://www.glassdoor.co.in/Interview/Agoda-Interview-E461386-RVW94645241.htm) (known only from a search-engine summary; Glassdoor blocks direct reading)
- [DSAPrep: Agoda coding interview questions (86 questions, tag recency)](https://www.dsaprep.dev/blog/agoda-coding-interview-questions)
- [LeetCode 3893: Maximum Team Size with Overlapping Intervals (problem summary)](https://leetcode.doocs.org/en/lc/3893)
- Your notes: `Interviews-2023/Uber-Feedback.txt`, `Interviews-2023/Google-R2.txt`, `I-2025/Cadence-R1.txt`
