# IV2 Platform Round: Progress

## Checklist
| Item | Day | Done |
|---|---|---|
| Intel + prep video notes (00 §6) | 1 | |
| Narrative Playbook | 1 | |
| Connectivity §1–19 | 1 | |
| QA §1–12 | 1 | |
| Scenarios S1, S2 aloud | 1 | |
| Generic A + B (28 Qs) | 1 | |
| Code review CR-1…CR-12 | 2 | |
| Scenarios S3–S6 aloud | 2 | |
| Generic C + D + E (22 Qs) | 2 | |
| Mock 1 | 2 | |
| Mock 2 | 2 | |
| WSL P1: booking, no double booking + idempotency (W2#1) | 3+ | |
| WSL P2–P3: bounded pool → supplier gateway capstone | 3+ | |
| WSL P4: cursor pagination (W8#2) | 3+ | |
| WSL P5–P7: webhooks · auth · outbox queue | 3+ | |
| Mock 3 (eve) | eve | |

## Mock scores (1–4)
| Mock | Date | Design | Connectivity | QA | Code review | Comms | Top 3 fixes |
|---|---|---|---|---|---|---|---|
| | | | | | | | |

## Weak spots (one line each)
- Length swings both ways: §4 was only the Say-it line (about 20 s). The Say-it line is the Kya beat, not the whole answer.
- Length: recites every point in the doc (§3 took about 3 min). Pick 5 points for 60 s and let the interviewer pull the rest.
- Vague words where a list is expected: "it should be resilient" → name timeout, retry, breaker, bulkhead, partial results.
- Recites the table attribute-by-attribute and runs past 60 s. Speak protocol-by-protocol (what, best at, catch) and finish on the trade-off.
- Skips the Keemat beat: no trade-off, metric or "what I'd standardise" at the end (Connectivity §1, §2). Also skips the Kahan beat (no Agoda example) in §2.
- Lists patterns instead of answering the question asked: §2 asked "when sync vs async" and never came back to it after the first sentence.
- Fillers: "uh" and "like" in most sentences; the closing line trails off. Pause silently instead, and end on a full sentence with "because".
- Says "matrices" for "metrics" (5+ times across §3 and its follow-up). Drill: MET-riks.
- Debugging questions: answers with guesses before data. Lead with "first I'd break the number down by …", then the ranked suspects, then prevention.
- Precision slips: L7 = application layer (not presentation); REST resources are nouns, HTTP methods are the verbs.

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
