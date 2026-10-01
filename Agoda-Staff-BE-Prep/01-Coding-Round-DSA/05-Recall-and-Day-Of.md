# One-Page Recall + Interview-Day Checklist

> Read this sheet the night before and 30 minutes before the call. No new problems on interview day.

## 1. Story → pattern (Agoda dresses up problems)

| If the story says… | Think | ID |
|---|---|---|
| formula / molecule / nested brackets with counts | recursive descent, `parseGroup(i&)` + `readCount` (default 1) | S1 |
| `k[...]`, reverse inside `( )`, remove k adjacent equal, backspace `#` | stack of (partial, count) · wormhole pairs · run stack · walk from the end | S3–S6 |
| next/largest greater on the right, nearest smaller, span | monotonic stack (who gets answered on a pop?) / suffix max | M1, M2 |
| "all left smaller and all right greater" | prefix max < x < suffix min | M3 |
| longest/shortest substring with a condition, "at most k" | window: grow right, shrink while invalid | W1–W4 |
| minimum capacity/speed/days, "maximize the minimum gap" | binary search on the answer + greedy check (upper mid for max) | B1–B3 |
| many queries "cost to make all equal to q" | sort + prefix sums + `lower_bound` | B4 |
| planes/monsters arriving, deadlines | sort by arrival; fail when `ceil(d/s) ≤ minute` | G1 |
| closest pairs, ranks of priorities | sort + adjacent · sort + unique + `lower_bound` | G2, G4 |
| repeatedly apply to the biggest | max-heap (stop early at 0) | G6 |
| cooldown between same tasks / no two adjacent equal | frequency frame `(maxF−1)(n+1)+ties` · even slots first | G8, G9 |
| bookings, rooms, capacity over time, range adds | sweep `+1/−1` map · heap of ends · difference array | I1–I5 |
| "can I reach the end" / "fewest jumps" | greedy farthest · BFS levels | J1, J2 |
| buy/sell with rules | state machine: cash/hold (+fee), buy1/sell1/buy2/sell2 | J5–J7 |
| palindromic substrings | expand 2n−1 centres (say O(n³) → O(n²); Manacher O(n)) | P1, P2 |
| cheapest route with ≤ k stops | Bellman-Ford k+1 rounds, **copy per round** | R1 |

## 2. Templates in 3 lines

```cpp
// first x that works                   // last x that works (maximize min)
while (lo < hi) { m = lo + (hi-lo)/2;    while (lo < hi) { m = lo + (hi-lo+1)/2;
  ok(m) ? hi = m : lo = m + 1; }           ok(m) ? lo = m : hi = m - 1; }

// window                               // next greater (indices, decreasing values)
for (r...) { add(r); while (bad()) remove(l++); best = max(best, r-l+1); }
while (!st.empty() && a[st.back()] < x) { ans[st.back()] = x; st.pop_back(); }

// two heaps for rooms                  // difference array
priority_queue<int, vector<int>, greater<>> freeRooms;   diff[l] += v; diff[r+1] -= v; partial_sum(...)
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> busy;
```

## 3. The trap list (say "let me check…" and check)
`<` vs `<=` (ties, touching intervals, landing at the shooting minute) · empty input · `size()-1` underflow · `int` overflow (sums, products, end times, `m*k`) · `INT_MAX` sentinels · upper mid when maximizing · stale index in the window (`abba`) · default count 1 / two-letter atoms · `map[]` insert while iterating · comparator with `<=` · formula on empty input (G8) · in-place relaxation (R1) · roll back rejected bookings (I4) · copy-paste symmetric code.

## 4. Talk track (one line per phase)
1. "Let me restate it and check the edge semantics…" (3–5 questions, one worked example)
2. "Brute force is ___ O(__); the repeated work is ___; with ___ it's O(__). The invariant is ___. OK to code?"
3. "Helper first: ___. Then the main loop." (Run once early.)
4. "Tests: the sample, then ___ because ___, ___ because ___." (All pass.)
5. "Complexity O(__). If this were a stream / a service / at Agoda's scale, I'd ___."

## 5. Interview-day checklist

**The evening before**
- [ ] Mock 6 done in the morning. Nothing new after 6 pm.
- [ ] Re-read Playbook §7 (your pre-Run checklist) and this page.
- [ ] Laptop charged, stable Wi-Fi (phone hotspot as backup), camera and mic tested, quiet room booked.
- [ ] Have your 45-second technical intro ready (Synopsys C++ systems + Microsoft OneDrive services; see `../00-Recruiter-Screen.md` §3b).
- [ ] Sleep 7+ hours. That's worth more than one more problem.

**60–30 minutes before**
- [ ] One easy warm-up from the AMD list (LC 20 or LC 739), typed blind in about 8 minutes, to get your fingers going.
- [ ] Open HackerRank once, choose C++, run a hello-world.
- [ ] Water, a notepad and pen (for drawing examples), close Slack/email/notifications.

**In the call**
- [ ] Say "I'll use C++" at the start.
- [ ] Every problem: restate → questions → example → approach + complexity → **nod** → code → **run early** → tests with reasons → follow-up.
- [ ] Clock: problem 1 done by about 30 min. Never past 32.
- [ ] Ask 2 questions at the end: "Which domain does this team own: inventory, pricing, booking or payments?" and "How do you test changes safely at Agoda's traffic?"

**Right after**
- [ ] Write both questions and your solutions into `PROGRESS.md` (useful for later rounds, and for the next candidate if you share).
