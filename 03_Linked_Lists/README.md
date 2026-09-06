# Linked Lists

**Status:** In progress — Module 1 complete (pointers → nodes → traversal)
**Covers:** Pointers, dummy nodes, fast/slow pointers, reversal, merging, cycles, rearrangement, LRU design

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Linked-Lists-Guide.pdf` | **36-page guide.** Pointers from zero, the 12 problem patterns, the approach framework, the 8-bug catalogue, the curated LeetCode list, a 4-week plan. |
| `notes/Linked-Lists-Solved-Questions.pdf` | **38-page solved-questions book.** All 33 problems from Part 7 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-all-patterns.cpp` | Every template from the guide, compiled and verified — 66 test cases, all passing |
| `solutions/reference-part7-solutions.cpp` | Source of truth for the PDF — all 33 solutions plus a test harness, 79 test cases, all passing |

The markdown source for the guide lives in `notes/_source/` — that is the build
input, not study material. Read the PDFs.

Compile any C++ file here with:

```bash
g++ -std=c++17 -O2 -Wall -o out <file>.cpp && ./out
```

---

## The 12 patterns

| # | Pattern | Recognition signal | Core tool |
|---|---|---|---|
| 1 | Traversal & basic ops | "print", "count", "insert at position" | the walk loop |
| 2 | Fast & slow pointers | "middle", "n-th from end", "palindrome" | two pointers |
| 3 | Reversal | "reverse", "in groups of k" | prev/curr/next |
| 4 | Deletion | "remove", "duplicates" | dummy node |
| 5 | Merge & sort | "two sorted lists", "sort the list" | dummy + merge |
| 6 | Cycle detection | "does it loop", "where does it start" | Floyd's algorithm |
| 7 | Intersection | "where do two lists meet" | length diff / switching |
| 8 | Rearrangement | "reorder", "partition", "rotate" | split + reverse + merge |
| 9 | Arithmetic | "add two numbers", "digits" | carry propagation |
| 10 | Copy / hashing | "random pointer", "deep copy" | hash map or interleaving |
| 11 | Recursion | "solve recursively" | recursion + call stack |
| 12 | Design | "LRU cache", "flatten multilevel" | doubly linked + map |

---

## The three rules

1. **Save `next` before you overwrite it.**
2. **Check for `nullptr` before you dereference.**
3. **Cut every tail you create.**

---

## Progress

- [x] Module 1 — Pointers, nodes, traversal
- [ ] Practice file: `length`, `contains`, `insertFront`
- [ ] Practice file: remaining 7 TODOs
- [ ] Module 2 — Dummy node, fast/slow, reversal
- [ ] Module 3 — The 12 patterns in depth
- [ ] Tier 1 problems (10)  — solutions in the PDF
- [ ] Tier 2 problems (13) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the PDF. Reading the solution before struggling with
the problem teaches you nothing. After you solve one, still read the
*Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LeetCode 146 (LRU Cache)** is asked more than any other linked list question
in on-campus drives — Amazon, Microsoft, Adobe, Flipkart, Uber. Be able to
write it from a blank page.
