# Searching & Sorting

**Status:** Material ready — study not started
**Covers:** binary search without off-by-one bugs (closed vs half-open, first true, last true), lower and upper bound, peaks, rotated arrays, 2-D search, binary search on the answer, k-th by counting, median of two sorted arrays, bubble / selection / insertion sort traced by hand, merge sort and counting during the merge, quicksort, partitioning and quickselect, counting / radix / bucket sort, comparators and stability, and sorting as a first step

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Searching-and-Sorting-Guide.pdf` | **35-page guide.** Searching and sorting from zero, binary search done right (**the invariant**, the three templates, why `lo = mid` needs round-up, lower / upper bound and the STL, an off-by-one checklist), binary search beyond sorted arrays (monotone predicates, peaks, rotated arrays, 2-D, **binary search on the answer** with the recipe and a table of six problems, k-th by counting, median of two arrays, real-valued search), the elementary sorts with real traces, merge sort and counting during the merge, quicksort with a Lomuto trace, the Dutch flag, quickselect, the Ω(n log n) bound, counting / radix / bucket sort, comparators and **strict weak ordering**, sorting as a first step, the 12 patterns, the approach framework, the 16-bug catalogue, the all-sorts complexity table, the curated LeetCode list, a 3-week plan. |
| `notes/Searching-and-Sorting-Solved-Questions.pdf` | **41-page solved-questions book.** All 38 problems from Part 13 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests: bubble, selection, insertion, merge sort, count inversions, quicksort, counting sort (no `std::sort` allowed), then count occurrences, rotated search, aggressive cows. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 61 test cases, all passing |
| `solutions/reference-part13-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 150 test cases, all passing (also clean under AddressSanitizer / UBSan, and 16 of the solutions fuzzed against brute force) |

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
| 1 | Exact binary search | "find x in a sorted array" | closed `[lo, hi]`, `lo <= hi` |
| 2 | Boundary search | first / last occurrence, insert position, count | half-open `[lo, hi)`, first true |
| 3 | Monotone predicate | first bad version, sqrt | name the predicate, then the template |
| 4 | Peak / slope search | mountain, bitonic | compare `a[mid]` with `a[mid + 1]` |
| 5 | Rotated array search | "rotated sorted array" | one half is always sorted |
| 6 | 2-D matrix search | sorted rows / columns | flatten the index, or the top-right staircase |
| 7 | Binary search on the answer | "minimise the max", "maximise the min" | bounds + greedy feasibility check |
| 8 | k-th by counting | k-th smallest in an implied set | binary search the value, count ≤ v |
| 9 | Partitioning | sort colours, k-th largest | Lomuto / Dutch flag / quickselect |
| 10 | Merge sort with counting | inversions, count smaller after self | count cross pairs while merging |
| 11 | Non-comparison sort | small value range, maximum gap | counting / radix / bucket |
| 12 | Sort, then scan | intervals, two pointers, custom order | `sort` + comparator, then one pass |

---

## The five rules

1. **Binary search needs a monotone predicate, not a sorted array.** Name the predicate first.
2. **Say what `lo` and `hi` mean** — closed or half-open — and make every update keep that meaning.
3. **`lo = mid` → round mid up.** `mid = lo + (hi − lo) / 2` always.
4. **"Minimise the maximum" / "maximise the minimum" → binary search on the answer** with a greedy check.
5. **Comparators are strict (`<`, never `<=`)**, and `std::sort` is not stable.

---

## The template worth memorising

```cpp
// the FIRST index where P becomes true (lower_bound is P(i) = a[i] >= x)
int lo = 0, hi = n;                     // half-open; n means "never true"
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (P(mid)) hi = mid; else lo = mid + 1;
}
return lo;
```

lower_bound, upper_bound, First Bad Version, peaks, minimum of a rotated array,
Koko, Ship Packages, Split Array and every "k-th by counting" problem are this
block with a different predicate.

---

## Progress

- [ ] Part 0–1 — binary search: the invariant, three templates, lower / upper bound
- [ ] Practice file: TODO 8 (`countOccurrences`, by hand)
- [ ] Part 2 — predicates, peaks, rotated arrays, 2-D; practice TODO 9 (`searchRotated`)
- [ ] Part 2.5 — binary search on the answer; practice TODO 10 (`aggressiveCows`)
- [ ] Part 3 — bubble, selection, insertion; practice TODOs 1–3
- [ ] Part 4–5 — merge sort, inversions, quicksort, partitioning; practice TODOs 4–6
- [ ] Part 6–8 — counting / radix / bucket, comparators, sorting first; practice TODO 7
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: allocate minimum pages, aggressive cows, floor and ceil, rotation count, minimum platforms, merge without extra space

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 33 (Search in Rotated Sorted Array), LC 153 (Find Minimum in Rotated
Sorted Array), LC 34 (First and Last Position), LC 875 (Koko Eating Bananas),
LC 1011 (Ship Packages), LC 56 (Merge Intervals) and LC 75 (Sort Colors)** are
the most-asked searching and sorting questions in on-campus drives — Amazon,
Microsoft, Adobe, Flipkart, Walmart, Goldman Sachs, TCS Digital, Infosys.

For Indian **written rounds** specifically, also drill: writing and tracing
bubble / selection / insertion sort, the stable / in-place / best / worst table,
merge sort and quicksort with the quicksort worst case, count inversions,
**allocate minimum pages**, **aggressive cows**, and sort 0s, 1s and 2s.

## Where this topic leads

Heap sort and the k-th element continue in Topic 07 (Heaps). Sorting first is
the backbone of Topic 10 (Greedy). Binary search pairs with DP in Topic 11
(Longest Increasing Subsequence in O(n log n) is a `lower_bound` on a tails
array). Merge sort with counting generalises to Fenwick and segment trees.
