# IV2 Platform Round: Progress

**IV2: Wed 21 Oct 2026, 08:00.** Micro-labs (System Design/Micro-Labs-Plan.md) were paused on 18 Oct; prep is now drills with Claude (attempt first → feedback → retry).

## Plan to the round (updated Sun 18 Oct, 16:00)
| When | Do | Why |
|---|---|---|
| **Sun evening** (after a real break) | **Scenario S1** run by Claude as the interviewer (45 min) → **CR-2** supplier fan-out (20 min) | The narrative is most of the hour and hasn't been practised yet; CR-2 reuses connectivity §4–§7 |
| **Mon evening** (~1.5 h) | **QA**: 03 §1, §7, §8 → the 06 section C questions in batches of 4 (45 min) · **CR-3** retry helper (15 min) | QA is a graded attribute, still untouched |
| **Tue morning** | **Scenario S2** (hotel booking + payment; reuses today's saga) · 06 sections B and E rapid-fire in batches | The second most likely narrative |
| **Tue afternoon** | **Mock 1**, full 60 min, then a debrief | Never cut this |
| **Tue evening** | 08-Recall-Day-Of.md, the booking "sandwich" picture, the traffic-light code-review method. Sleep early | |
| **Wed 06:30** | 10 min: draw the sandwich + the review tiers; read the recall sheet | |

If time slips, cut in this order: CR-3 → 06 section E → S2 (talk through its key instead). Never cut S1 or Mock 1.

## Checklist
| Item | Day | Done |
|---|---|---|
| Intel + prep video notes (00 §6) | 1 | ✔ read 17 Oct (video notes not filled) |
| Narrative Playbook | 1 | ✔ read 17 Oct |
| Connectivity §1–19 | 1 | ~ §1–§7 drilled aloud; 02a See-it pages for §1, §3–§7; §8–§19 skimmed |
| QA §1–12 | 1 | |
| Scenarios S1, S2 aloud | 1 | |
| Generic A + B (28 Qs) | 1 | ? self-practised on the night of 17 Oct (results not reported) |
| Code review CR-1…CR-12 | 2 | ~ §1–§2 method + CR-1 twice (7 → 16 of 22) |
| Booking flow: concurrency, idempotency, saga | 2 | ✔ 18 Oct (see the session log) |
| Scenarios S3–S6 aloud | 2 | skip unless time |
| Generic C + D + E (22 Qs) | 2 | |
| Mock 1 | Tue | |
| Mock 2 | — | skip |
| WSL micro-labs 1–4 | — | paused 18 Oct (didn't fit the time left) |
| Mock 3 (eve) | — | skip |

## Mock scores (1–4)
| Mock | Date | Design | Connectivity | QA | Code review | Comms | Top 3 fixes |
|---|---|---|---|---|---|---|---|
| S2 scenario (compressed) | 2026-10-20 | 3 | 2 | — | — | 2 | (1) after an ambiguous timeout never void or retry blind: keep the auth, PENDING + 202, look up by our ref; (2) answer the asked question first, then fix; (3) clarifying questions + cost maths before any design |
| S1 scenario (practice) | 2026-10-18 | 2 | 2 | 2 | — | 2 | (1) do the cost maths aloud after clarifying (3,000 searches/s × 2 suppliers = 6,000 paid calls/s); (2) answer the asked question in the first sentence; (3) walk boxes → arrows → API field by field |

## What works for learning (from the 17–18 Oct sessions)
- Follow **one concrete example through real table rows** (inventory, bookings and idempotency_keys changing phase by phase); pictures of two users side by side; then short pseudocode. This is what made the booking flow click.
- Attempt first, then feedback, then retry: CR-1 went from 7 to 16 of 22 on the retake.
- Ask questions in **small batches**, not one per message, in long sessions.
- **Finish each scenario fully before the next** (20 Oct): fixed diagram + fixed code + the numbers + a 3-question check. Rushed gap drills (grade → next) didn't stick. Present scenarios exactly as in 05-Scenarios.md.

## Weak spots (one line each)
- Length swings both ways: §4 was only the Say-it line (about 20 s). The Say-it line is the Kya beat, not the whole answer.
- Length: recites every point in the doc (§3 took about 3 min). Pick 5 points for 60 s and let the interviewer pull the rest.
- Vague words where a list is expected: "it should be resilient" → name timeout, retry, breaker, bulkhead, partial results.
- Recites the table attribute-by-attribute and runs past 60 s. Speak protocol-by-protocol (what, best at, catch) and finish on the trade-off.
- Skips the Keemat beat: no trade-off, metric or "what I'd standardise" at the end (Connectivity §1, §2). Also skips the Kahan beat (no Agoda example) in §2.
- Lists patterns instead of answering the question asked: §2 asked "when sync vs async" and never came back to it after the first sentence.
- Answers around a direct question: asked "does a transaction alone stop it? supplier call inside?", the first reply gave a business flow and said neither yes nor no. Start with "No, because …".
- Fillers: "uh" and "like" in most sentences; the closing line trails off. Pause silently instead, and end on a full sentence with "because".
- Says "matrices" for "metrics" (5+ times across §3 and its follow-up). Drill: MET-riks.
- Debugging questions: answers with guesses before data. Lead with "first I'd break the number down by …", then the ranked suspects, then prevention.
- Code review: reads the flow line by line but doesn't interrogate each line. Ask five questions per line: who controls this input, what if it fails or is null, what if two run at once, what if it's slow, what does it print or store.
- Code review: ends without a ranked summary. Finish with "about N issues, these 4 block the merge, the rest are follow-ups".
- Scenarios: no numbers turned into cost. After clarifying, say the maths aloud (QPS × suppliers × cost per call, look-to-book) and let it drive the cache and refresh design.
- Scenarios: jumps between topics; no signposting. Say the plan ("boxes, then arrows, then the APIs, then testing") and close each part with a one-line summary.
- Precision slips: L7 = application layer (not presentation); REST resources are nouns, HTTP methods are the verbs; a 5–8 Dec stay is 3 nights, not 4.

## Session log
| Date | What | Notes |
|---|---|---|
| 2026-10-17 | Connectivity §1 aloud (Protocols) | Partial. Good mechanics for REST/gRPC; missed GraphQL weaknesses (N+1, caching, query cost) and the Staff line; about 2 min long |
| 2026-10-17 | Connectivity §1 retry | ✔ Good structure, about 75 s. Still missed N+1; the closing line trailed off with no reason given; heavy "uh/like" fillers |
| 2026-10-17 | Connectivity §2 aloud (Sync vs async) | Partial. Good mechanics for the 5 patterns; turned into a list with no Agoda example and no Staff line (availability multiplies across sync hops). Mixed up SSE and WebSocket; no queue-vs-stream distinction; skipped the L4 follow-up |
| 2026-10-17 | L4 vs L7 explained; §2 follow-up (30 s supplier confirm) | L4/L7 was a concept gap (now in §19). Follow-up partial: said async but not 202 + status resource, Idempotency-Key, or authorise-then-capture |
| 2026-10-17 | §2 follow-up retry | ✔ Complete. Say status codes digit by digit; "void / release the hold", not "avoid" |
| 2026-10-17 | Connectivity §3 aloud (Supplier integration) | ✔ Content (best so far, has the trade-off and metrics) but about 3 min. Coalescing is to save supplier calls, not the DB; missed channel-manager push (ARI), delta/ETag, token-bucket budget; "resilient" left vague |
| 2026-10-17 | §3 follow-up (supplier spend doubled, flat traffic) | Partial. Right instincts (cache hits, duplicate calls) but unstructured; missed attributing calls by caller, retry storms, deploy correlation, and the prevention line (budget alert) |
| 2026-10-17 | Connectivity §4 aloud (Timeouts) | Partial. Correct anchor + cascade, but about 20 s: no connect/read split, no min(own, remaining − margin), no Agoda example, no product-decision line. §3 60-s redo still pending |
| 2026-10-17 | 02a See-it pages; learning diagnosis | Pseudocode + C++ analogies for §1, §3–§7. Diagnosis: a mechanism gap (never built timeouts/pools/breakers) plus a recall gap (rereading); English isn't the main issue. Little's Law explained (threads = rate × time held) |
| 2026-10-18 | Code review §1 order recalled | Partial. Missed the Performance lens entirely (per-call client, N+1, no pagination, sequential loop); concurrency placed too late; skipped §2 comment labels |
| 2026-10-18 | CR-1 (booking service) | About 7/22. Found: SQL injection (unsure how), API key, per-call DB conn + HttpClient, check-then-act race, if/else → strategy + DI. **Major misses:** card number logged, IDOR on getBookings ("looks okay"), no pagination, no timeouts. No intent line, no labels, no prioritised opening |
| 2026-10-18 | Interview method for code review | Traffic-light tags typed on each line (RED money/data/security, YELLOW production, BLUE team); the five-finger questions per line; about 13 min: intent → tag pass → ranked summary → fix the top 2–3 → follow-ups. Say "I'm a C++ engineer; I'll sketch in Java-like pseudocode". Four fix shapes: PreparedStatement, conditional UPDATE, strategy interface + map, injected pool/client with timeouts |
| 2026-10-18 | CR-1 retake (interview form) | About 16/22, all 4 major misses fixed, and found the supplier-before-save orphan with a PENDING-status fix. Still missing: the prioritised summary at the end (it trailed off with "that's pretty much it"), idempotency key, price tampering, the shared cache list, rs.next() ("it is okay"). Said the card is "shown to the user"; it's printed to logs |
| 2026-10-18 | CR-1 ranked summary | ✔ The order was right (blockers → reliability → design). Add the count up front and "I'd block the merge on the first four" at the end |
| 2026-10-18 | Follow-up: does a transaction stop double booking? supplier call inside? | Partial on the first try (described a business flow instead of answering). Then taught: a plain SELECT doesn't lock → conditional UPDATE + row count; never hold a DB transaction across remote calls; the saga "sandwich" (T1 → payment + supplier → T2, compensate on failure, a reconciler for PENDING); Case A (supplier owns inventory) vs Case B (we own it); one inventory row per night; FOR UPDATE SKIP LOCKED for per-unit rows |
| 2026-10-18 | Booking flow traced through real tables | Idempotency-key claim via PRIMARY KEY / UNIQUE; the booking row vs the inventory rows; supplier_ref; "key = DONE + stored response" for replays; failure-by-phase table. Check questions: Q1 ✔, Q2 ✘ (3 nights, not 4), Q3 ✔ (add a 202 reply, and don't compensate before the outcome is known) |
| 2026-10-18 | Scenario S1 (flight aggregator), interviewer-run, ~35 min | 2/2/2/–/2. Good: split search/booking, SPOF, cache keyed by route+date with TTL + background refresh + lazy fill + telemetry to tune TTLs, partial results, timeouts, pagination, no card in the API, store the supplier ref, PENDING status, fake slow suppliers for tests. Missed: cost maths, sync fan-out per search, dedupe key/cheapest, breaker/bulkhead/budget, inbound rate limiting (bots), stampede, price + raw card from the client, "OK" → 201 + bookingId, auth, async/outbox, observability. **Concept gap: thought the server can generate the idempotency key; it must come from the client (one per checkout attempt, resent on retry).** Skipped the cache question until asked twice |
| 2026-10-19 | Quiz batches 1–3 (S1/S2, connectivity, code review) after rereading S1/S2 | B1: 3/5 (mixed up the search cache key and the dedupe key; dual write answered as a saga → taught the outbox, polling relay vs Debezium CDC, at-least-once delivery + idempotent consumer = effectively once). B2: 0 fully right, 4 partial (missed bulkhead, the retry gates "safe + temporary", cursor stability, webhook dedupe/ack-fast/ordering; RED blockers named as vague categories). B3: much better: bulkhead via Little's Law ✔, outbox ✔; still partial on the ambiguous supplier timeout (look up by our ref first), writing the cursor condition, a definitive out-of-order rule, and saying "same transaction" for the outbox write |
| 2026-10-19 | QA taught (03 §1, §7, §8) + quiz | Memory model: a 3-floor pyramid, with the middle floor holding 3 rooms (real DB / stubbed supplier / supplier contract); load+chaos and production outside. Quiz: Q1 ✔ unit for cheapest/dedupe; Q2 ~ (missing the asserts: one booking row, identical reply, supplier called once, 422 on a different body); Q3 ~ (stored fixtures only test us; add a nightly job against the supplier sandbox); Q4 ~ (fault injection right; say why untested: thresholds/wiring, and assert breaker opens, calls stop, fast fallback, half-open recovery) |
| 2026-10-19 | CR-2 (supplier fan-out), timed, ~6 min | About 4.5/10. Found: per-call client → injected gateway, timeouts/breaker/bulkhead/safe retries, early `return emptyList()` → partial results, no cache (cost). **Major miss: the sequential loop (latency = sum of 12).** Also missed the `(int)(a − b)` comparator, dedupe, currency, pagination, the silent catch. No intent line, no per-line tags, no ranked summary, no fix sketched; never interrogated the sort line |
| 2026-10-19 | CR-2 retry (full review again) | About 8/10 on content: opened with an intent line, sequential fan-out first, gateway duties, cache, dedupe, cap, logged partial results, the comparator explained with 10.30 vs 10.70, currency + taxes. Still: about 4 min against the 90 s asked, no count up front or "these block the merge", no fix sketched, trailed off ("that's all from like that these"), per-call timeouts but no overall deadline. Asked: what is the intent line; are the traffic-light tags said aloud (no: say blocker / should-fix / nit) |
| 2026-10-19 | Code-review delivery taught + CR-2 in 4 beats | Taught Kya → Kitne → Kaunse → Kaise (intent, count, blockers one sentence each, fix sketch); the summary is the opening, not the ending; rank by "what breaks, for whom". Rep: ✔ structure, about 75 s, the 4 blockers right and in order, one sentence each. Missing: the total count, "one overall deadline" in the fix, the Kaise line (offer to sketch); follow-ups dropped logging + cache; "timeout for resilient APIs" is vague |
| 2026-10-19 | CR-3 (retry helper), 18:44–18:49 | About 3/9. Found: retrying without knowing if it's safe (but never said "a POST can book 5 times" or the idempotency key), no timeout on `requests.post`, the catch-all handled badly. **Major misses: status code never checked (a 500 body returned as success); module-level `requests.post` = a new connection per call; fixed 1 s sleep with no backoff/jitter/Retry-After.** Also missed: no overall deadline, `return None` hides failure, no logging. Process: read the code aloud again, no Kitne count, no Kaise sketch, ended "these are the things I can find" |
| 2026-10-19 | Own trigger list (RED/YELLOW/BLUE) → 04b-Code-Review-Triggers.md | Good RED instincts (SQL concat, wrong sort, authZ from the token, races). Gaps: secrets, PII in logs, client price, POST retry is RED (not YELLOW); pools/per-call clients are YELLOW (not BLUE); missed status check, pagination, N+1, silent catch. Asked: is printf/format safe vs concat? No: any string building is injection; only parameters are safe |
| 2026-10-20 | Generic review model → 3 Hindi phrases (04b top) | Said the trigger tables weren't generic. Now 9 words: RED *Galat, Leak, Do Baar*; YELLOW *Dheema, Toota, Mehenga*; BLUE *Jodo, Jaancho, Samjho*. CR-11 transfer test still pending (do it before S2) |
| 2026-10-20 | Recall of the 9 boxes + CR-11 (unseen; transfer test) | Recall: about 5–6 of 9; dropped **Leak** (security) again and Toota (failure handling); put "runs twice" in YELLOW (it's RED). CR-11: about 3/7. Found: config file read + new ObjectMapper per call → load once and inject, the connection → a pool, `.get("rates")` can throw. **Missed: `hotelId` concatenated into the URL path (path injection, the Leak box), no timeouts (infinite by default), streams/connection never closed, no status check, no supplier auth.** Intent + "5 to 6 issues" ✔; no ranked blockers, no Kaise; read the code aloud again |
| 2026-10-20 | CR-11 retry (4 beats) | About 5.5/7: path injection with the `../admin` example ✔, timeout ✔, NPE ✔, per-call mapper/config ✔, testability unprompted ✔. Still missed: streams/connection never closed, supplier auth; "error handling" vague (say "check the status code"). Delivery: opened the blockers with the NPE, not the Leak; scanned aloud mid-answer ("checking if there are other blockers"); no "X block the merge", no Kaise; about 90 s; ended "that's pretty much it" |
| 2026-10-20 | Scenario S2 (booking + payment), compressed, 12:48–13:08 | 3/2/–/–/2. Good: authorise → PENDING → supplier → capture/void, idempotency key, outbox for the email, a reconciler. Missed: no clarifying questions about the system (volume, PSP/supplier idempotency, auth-hold window, supplier lookup by our ref) and no cost maths; didn't answer "what does the user see" (jumped to the fix); ambiguous timeout: offered "void + tell them to retry" (wrong: the supplier may have booked) and "charge and say pending" (keep the auth, don't capture), didn't pick one; no "look up by our ref first", no 202; the toll road on each arrow and the API were never reached |
| 2026-10-20 | Taught: authorise/capture/void; 2PC vs saga; orchestration vs choreography; pivot step + quiz | Q1 ~ (used "pivot" as a verb; the pivot is the supplier confirm, the point of no return: undo-able steps like authorise go before it, must-finish steps like capture after). Q2 ✔ (reconciler reads the status + checks the supplier; say "by our ref"). Q3 ✔ content but about 40 s for a one-sentence answer; said "logs" for "locks" |
| 2026-10-20 | S3 gap drill (channel-manager ARI push) | ✘ on time: 3 min went on restating the prompt and the maths; 1 of the 4 gaps (cache staleness) and no ordering fix. Good clarifying questions (QPS, retries, timeouts). **Maths slips: 20k/s × 86,400 ≈ 1.7 B per *day* (said "per second"); 20k is already updates, i.e. 2 requests/s of 10k each (multiplied by 10k again → "trillions").** Missed: sync 10k-row write → timeouts → whole-batch retry storm (202 + queue), per-key ordering/versions, shared Basic auth + no authZ per hotel, no rate limit or batch cap |
| 2026-10-20 | S4 gap drill (nightly content sync, 10 req/s) | ~ Found: checkpoint/resume, timeouts, a queue + retry for failed pages, batching. **Maths wrong: 2M / 100 = 20,000 requests (said 200,000 then 2,000) → 2,000 s ≈ 33 min at 10 req/s, so the 9 h is OUR slowness (2M row-by-row inserts), not the supplier.** **Main fix was backwards: "make calls parallel" is exactly what gets us banned; missed the client-side token bucket (about 8/s) + 429/Retry-After.** Missed: SQL injection from supplier data (the Leak box on the code), INSERT → upsert per page, delta sync (`updatedSince`), offset pagination on a changing list (skips/dupes). Used "asynchronous" for "sequential" |
| 2026-10-18 | Quiz Q1–Q2 (transactions, unique constraint) | Q1 ✔ (add "a plain SELECT doesn't lock" + the row-count check). Q2 ✔ (add: without a constraint, the second insert does NOT fail; you'd get two rows). Asked a good production question: who owns the rollback, code or DB |
