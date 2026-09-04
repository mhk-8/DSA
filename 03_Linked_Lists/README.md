# Linked Lists

**Status:** In progress — Module 1 complete (pointers → nodes → traversal)
**Covers:** Pointers, dummy nodes, fast/slow pointers, reversal, merging, cycles, rearrangement, LRU design

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/linked-lists-cpp-guide.md` | The full guide — pointers from zero, 12 problem patterns, approach framework, bug catalogue, curated LeetCode list, 4-week plan |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-all-patterns.cpp` | Every template from the guide, compiled and verified — 66 test cases, all passing |

Compile anything here with:

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
- [ ] Tier 1 problems (10)
- [ ] Tier 2 problems (13)
- [ ] Tier 3 problems (10)

## Must-know for placements

**LeetCode 146 (LRU Cache)** is asked more than any other linked list question
in on-campus drives — Amazon, Microsoft, Adobe, Flipkart, Uber. Be able to
write it from a blank page.
