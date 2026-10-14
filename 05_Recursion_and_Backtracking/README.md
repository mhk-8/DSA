# Recursion & Backtracking

**Status:** Material ready — study not started
**Covers:** the call stack and the leap of faith, tracing and "what does this print?", the cost of a recursive function, the reduce-by-one and halving families, Tower of Hanoi and Josephus, divide and conquer (merge sort, quick sort, counting during the merge), the one backtracking template, subsets, combinations, permutations, N-Queens, Sudoku, word search, partitioning, and the bridge from recursion to memoization

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Recursion-and-Backtracking-Guide.pdf` | **51-page guide.** Recursion from zero (frames, winding and unwinding, stack overflow), the leap of faith and the three questions, tracing, the cost of recursion (recursion trees, the recurrences to know on sight), warm-ups and divide and conquer, the backtracking template, subsets, combinations, permutations, N-Queens / Sudoku / grids, partitioning and generation, recursion → memo, the 12 patterns, the approach framework, the 16-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 3-week plan. |
| `notes/Recursion-and-Backtracking-Solved-Questions.pdf` | **42-page solved-questions book.** All 38 problems from Part 16 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 36 test cases, all passing |
| `solutions/reference-part16-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 124 test cases, all passing (also clean under AddressSanitizer / UBSan) |

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
| 1 | Reduce by one | "handle one element, the rest is the same problem" | base case + one call on n − 1 |
| 2 | Halve the input | power, binary search, grammar rows | one call on n / 2, **stored** |
| 3 | Divide and conquer with a combine | sort, count pairs across halves, split an expression | two calls + a linear merge |
| 4 | Recurrence from the definition | Josephus, Hanoi, row n built from row n − 1 | write the formula as code |
| 5 | Pick / skip | subsets, subsequences, each element in or out | two calls per level, answer at leaves |
| 6 | Loop from `start` | combinations, sums to target | `for (i = start…)` + `dfs(i + 1)` |
| 7 | Permutations | arrangements, every order | `used[]` array, or swap into place |
| 8 | Duplicate skipping | repeated values, "no duplicate answers" | sort + `i > start && a[i] == a[i-1]` |
| 9 | Partition at every cut | split a string into valid pieces | `for (end = start…)` + `dfs(end + 1)` |
| 10 | Generation with validity counters | parentheses, case flips, IPs | only branch where the rule still holds |
| 11 | Constraint placement | queens, Sudoku, buckets, colouring | O(1) conflict arrays, set / clear |
| 12 | Grid path backtracking | word search, maze paths | mark → 4 directions → unmark |

Plus one modifier: **+ memo** whenever a counting recursion revisits the same state.

---

## The five rules

1. **Define what the function returns, then trust it** for smaller inputs. Do not trace.
2. Answer the three questions before writing code: **base case, recursive case, progress.**
3. **Every "do" has an "undo"**, in reverse order. State passed by value needs no undo.
4. **Read the constraints first:** n ≤ 10 → n!, n ≤ 20 → 2ⁿ, larger → memo or something else.
5. **Prune near the root:** sort, skip duplicates at the same depth, `break` on the bound, check validity when placing.

---

## The template worth memorising

```cpp
void dfs(<state>) {
    if (<complete>) { res.push_back(path); return; }
    for (<each choice>) {
        if (<invalid>) continue;
        <do>;   path.push_back(x);
        dfs(<next state>);
        path.pop_back();   <undo>;        // mirror image of <do>
    }
}
```

Subsets, combinations, permutations, N-Queens, Sudoku, palindrome partitioning
and word search are all this block with the five blanks filled differently —
state, goal, choices, validity, undo (guide Part 5.2).

---

## Progress

- [ ] Part 0–3 — the call stack, the leap of faith, tracing, the cost of recursion
- [ ] Practice file: TODOs 1–4 (`sumOfDigits`, `fastPower`, `isPalindrome`, `hanoi`)
- [ ] Part 4 — warm-ups, merge sort and quick sort written from a blank page
- [ ] Part 5 — the backtracking template
- [ ] Practice file: TODOs 5–6 (pick / skip: `subsets`, `countSubsequencesWithSum`)
- [ ] Practice file: TODOs 7–9 (`permutations`, `combinationSum`, `generateParenthesis`)
- [ ] Parts 6–10 — subsets, combinations, permutations, boards and grids, partitioning
- [ ] Practice file: TODO 10 (`totalNQueens`)
- [ ] Part 11 — recursion → memoization
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: Rat in a Maze, M-colouring, count inversions, sort a stack recursively, "what does this print?"

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 51 (N-Queens), LC 37 (Sudoku Solver), LC 79 (Word Search), LC 46/47
(Permutations), LC 39/40 (Combination Sum) and LC 131 (Palindrome
Partitioning)** are the most-asked backtracking questions in on-campus drives —
Amazon, Microsoft, Adobe, Samsung, Flipkart, TCS Digital, Infosys. Be able to
write each from a blank page and state its complexity.

For Indian **written rounds** specifically, also drill: "what does this print?"
on functions with work before and after the recursive call, Tower of Hanoi and
its 2ⁿ − 1 moves, merge sort and quick sort (stability and worst case), count
inversions, Rat in a Maze, and printing all subsequences of a string.

## Where this topic leads

Trees (Topic 06) is recursion on a shape you already know. Graph DFS (Topic 12)
is backtracking without the unmark. Every Dynamic Programming problem
(Topic 11) starts as a recursion from Part 11 of the guide — recursion first,
memo second, table third. Tries (Topic 14) are what make Word Search II fast.
Merge sort and quick sort return in Searching & Sorting (Topic 09).
