# Stacks & Queues

**Status:** Material ready — study not started
**Covers:** LIFO and FIFO, building all four containers by hand, the STL adapters, bracket matching, infix/postfix/prefix and the calculator family, string collapsing, the monotonic stack in full, the monotonic deque, BFS with a queue, and the design problems

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Stacks-and-Queues-Guide.pdf` | **47-page guide.** Both structures from zero, implementing them by hand (array stack, linked stack, circular queue, linked queue), the STL adapters, the one stack mental model, brackets and expressions, the monotonic stack in full, the monotonic deque, BFS, design problems, the 12 patterns, the approach framework, the 14-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 3-week plan. |
| `notes/Stacks-and-Queues-Solved-Questions.pdf` | **44-page solved-questions book.** All 38 problems from Part 11 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 44 test cases, all passing |
| `solutions/reference-part11-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 143 test cases, all passing |

The markdown source for the guide and the metadata for the solved-questions
book live in `notes/_source/` — those are build inputs, not study material.
Read the PDFs.

Compile any C++ file here with:

```bash
g++ -std=c++17 -O2 -Wall -o out <file>.cpp && ./out
```

---

## The 12 patterns

| # | Pattern | Recognition signal | Core tool |
|---|---|---|---|
| 1 | Bracket matching | parentheses, valid, balanced, nesting | push openers, pop on the closer |
| 2 | Expression evaluation | infix / postfix / prefix, calculator | operand stack, operator stack |
| 3 | String collapse | "remove adjacent", backspace, stars | the output string **is** the stack |
| 4 | Nested context save & restore | `k[...]`, parentheses, paths, call logs | push the state you are about to overwrite |
| 5 | Monotonic stack — next/prev greater/smaller | "next greater", "span", "how many days until" | indices + one comparison |
| 6 | Monotonic stack — area & contribution | histogram, rectangle, trapping water, sum over subarrays | `(i - prev) * (next - i)` |
| 7 | Monotonic deque | sliding window maximum / minimum | expire the front, dominate the back |
| 8 | Queue as a time window | "in the last X ms", moving average, streams | push, pop while the front is stale |
| 9 | BFS with a queue | shortest steps, level by level, spreading | freeze `q.size()` per level |
| 10 | Stack simulation | asteroids, validate sequences, baseball | push, pop while a collision rule holds |
| 11 | Design with an auxiliary structure | "all operations in O(1)" | a shadow stack, two stacks, a map of stacks |
| 12 | Recursion ↔ explicit stack | "do it iteratively", "no recursion" | write the call stack out by hand |

---

## The five rules

1. **Most recent → stack. Oldest → queue. Both ends → deque.**
2. Answer two questions before writing code: **what do I push, and when do I pop?**
3. **Push the index**, not the value — you cannot recover a position from a value.
4. Guard every access with `!st.empty() &&`, on the **left** of the `&&`.
5. A `while` inside a `for` is still **O(n)**: each element is pushed once and popped once. Say that sentence out loud in the interview.

---

## The eight lines worth memorising

```cpp
// next smaller AND previous smaller, for every index, in one pass
vector<int> nxt(n, n), prv(n, -1);
stack<int> st;                                   // increasing
for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.top()] > a[i]) { nxt[st.top()] = i; st.pop(); }
    prv[i] = st.empty() ? -1 : st.top();
    st.push(i);
}
// swap '>' for '<' to get next/previous GREATER
```

Largest Rectangle, Trapping Rain Water, Sum of Subarray Minimums, Daily
Temperatures, Stock Span and Next Greater Element are all this block plus a
formula. Learn it as one unit.

---

## Progress

- [ ] Part 0–1 — LIFO/FIFO, and implementing all four containers by hand
- [ ] Practice file: TODOs 1–3 (`reverseString`, `isBalanced`, `evalPostfix`)
- [ ] Practice file: TODOs 4–6 (the monotonic ones)
- [ ] Practice file: TODOs 7–10 (recursion on a stack, and the two designs)
- [ ] Part 2–3 — the mental model, brackets, infix/postfix/prefix, calculators
- [ ] Part 4 — the monotonic stack, all four variants
- [ ] Part 5 — BFS and the monotonic deque
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: two stacks in one array, sort a stack recursively, infix conversions

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 84 (Largest Rectangle in Histogram), LC 42 (Trapping Rain Water),
LC 239 (Sliding Window Maximum) and LC 227 (Basic Calculator II)** are the four
most-asked stack and queue questions in on-campus drives — Amazon, Microsoft,
Adobe, Goldman Sachs, TCS Digital, Infosys. Be able to write all four from a
blank page.

For Indian **written rounds** specifically, also drill: implementing a queue on
a circular array and explaining the full-versus-empty ambiguity, **two stacks in
one array**, sorting a stack using recursion only, infix → postfix → prefix
conversion by hand, and the stock span problem.

## Where this topic leads

The monotonic deque returns in sliding-window DP (Topic 11). The BFS queue is
the engine of Topic 12 Graphs. `priority_queue` in Topic 07 is the "queue" that
orders by value rather than by arrival. The recursion-to-stack conversion in
Part 2.4 is what makes iterative DFS possible, and it is the same conversion you
already used for iterative tree traversal in Topic 06.
