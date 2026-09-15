# Arrays

**Status:** Material ready — study not started
**Covers:** What the memory actually looks like, the index discipline that kills off-by-one bugs, two pointers in all three shapes, both sliding-window flavours, prefix sums and difference arrays, the two binary-search templates plus binary search on the answer, hashing and index-as-hash, Kadane, intervals, and matrix manipulation

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Arrays-Guide.pdf` | **51-page guide.** Arrays from absolute zero (memory, the address formula, decay, out-of-bounds UB), C array vs `std::array` vs `vector`, the index mental model, two pointers, sliding windows, prefix sums, binary search, hashing and in-place marking, Kadane/intervals/matrices, the 14 patterns, the approach framework, the 14-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 4-week plan. |
| `notes/Arrays-Solved-Questions.pdf` | **41-page solved-questions book.** All 38 problems from Part 13 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file, plus the building blocks and the Indian-placement classics — 57 test cases, all passing |
| `solutions/reference-part13-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 129 test cases, all passing |

The markdown source for the guide and the metadata for the solved-questions
book live in `notes/_source/` — those are build inputs, not study material.
Read the PDFs.

Compile any C++ file here with:

```bash
g++ -std=c++17 -O2 -Wall -o out <file>.cpp && ./out
```

---

## The 14 patterns

| # | Pattern | Recognition signal | Core tool |
|---|---|---|---|
| 1 | Linear scan with state | "max/min/count as you go", Kadane, majority | one or two running variables |
| 2 | Two pointers — opposite ends | sorted + pair/triplet, or compare both ends | `l = 0, r = n-1`, move the losing end |
| 3 | Two pointers — write index | "in place", "return the new length" | `w` = next output slot |
| 4 | Partitioning (Dutch flag) | rearrange into 2 or 3 groups in one pass | `low`, `mid`, `high` |
| 5 | Fixed sliding window | "window of size k", "every k consecutive" | `sum += v[r] - v[r-k]` |
| 6 | Variable sliding window | longest/shortest contiguous satisfying X, **non-negative** | grow right, shrink left |
| 7 | Prefix sum | many range-sum queries, "sum of v[i..j]" | `P[j+1] - P[i]` |
| 8 | Prefix sum + hash map | "count/longest subarray with sum k", **negatives allowed** | look up `pre - k` |
| 9 | Difference array / sweep | many range updates, "how many overlap at once" | `+x` at `l`, `-x` at `r+1` |
| 10 | Binary search on a sorted array | sorted, "find / first / last / insert position" | the two templates |
| 11 | Binary search on the answer | "minimise the maximum", "smallest capacity such that" | `bool feasible(x)` |
| 12 | Hashing / frequency counting | membership, duplicates, counts, "return indices" | `cnt[26]` or `unordered_map` |
| 13 | Index-as-hash / in-place marking | values are `1..n` **and** O(1) space demanded | cyclic sort, sign bit, XOR |
| 14 | Matrix / grid index manipulation | rotate, spiral, transpose, zeroing | boundaries, transpose + reverse |

---

## The five rules

1. **Read the constraints before the statement.** `n <= 10^5` and a nested loop means you have already chosen wrong.
2. **Every index needs a sentence.** "`w` is the next write slot", "`l` is the start of the window". If you cannot finish the sentence, you are about to write a bug.
3. **Negatives plus a sum condition rules out a sliding window.** That is pattern 8, not pattern 6 — this single distinction is the most common wrong turn in the topic.
4. **Write `i + 1 < n`, never `i < n - 1`.** `v.size()` is unsigned, so `n - 1` on an empty vector is 18446744073709551615.
5. **Dry-run five inputs before submitting:** `[]`, `[x]`, all-equal, sorted both ways, answer at each end.

---

## The two templates worth memorising

```cpp
// binary search: EXACT value          // binary search: FIRST TRUE (the boundary)
int lo = 0, hi = n - 1;                int lo = 0, hi = n;      // hi = n, not n-1
while (lo <= hi) {                     while (lo < hi) {
    int m = lo + (hi - lo) / 2;            int m = lo + (hi - lo) / 2;
    if (v[m] == t) return m;               if (pred(m)) hi = m;   // m may be it — KEEP
    if (v[m] < t) lo = m + 1;              else         lo = m + 1;
    else          hi = m - 1;          }
}                                      return lo;
```

Never mix them: `while (lo <= hi)` with `hi = mid` loops forever, and
`while (lo < hi)` with `hi = mid - 1` skips the answer. Pick one and stick to it.

---

## Progress

- [ ] Part 0–2 — memory, the three array types, the index mental model
- [ ] Practice file: TODOs 1–5 (`findMax`, `reverseInPlace`, `removeValue`, `moveZeroes`, `prefixSums`)
- [ ] Part 3–4 — two pointers and both window flavours
- [ ] Practice file: TODOs 6–8 (`firstOccurrence`, `maxSumWindow`, `maxSubarraySum`)
- [ ] Part 5–7 — prefix sums, binary search, hashing and index-as-hash
- [ ] Practice file: TODOs 9–10 (`rotateRight`, `sortColors`)
- [ ] Part 8–12 — Kadane, intervals, matrices, the patterns, the bug catalogue
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The Indian-placement classics list in Part 13

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 53 (Maximum Subarray), LC 42 (Trapping Rain Water), LC 560 (Subarray Sum
Equals K), LC 15 (3Sum) and LC 33 (Search in Rotated Sorted Array)** are the
most-asked array questions in on-campus drives — Amazon, Microsoft, Adobe, TCS
Digital, Infosys, Cognizant. Be able to write all five from a blank page.

For Indian **written rounds** specifically, also drill: reverse and rotate an
array by `d`, second largest in one pass, union and intersection of two sorted
arrays, leaders of an array, equilibrium index, maximum circular subarray sum,
count inversions, the duplicate-and-missing pair, and printing a matrix in
spiral order. All of them are in Part 13 and implemented in
`solutions/reference-basics.cpp`.

## Where this topic leads

Everything. A hash table is an array (Topic 08), a heap is an array (Topic 07),
a stack is an array (Topic 04). The prefix-sum idea becomes the DP table in
Topic 11, binary search on the answer reappears in Topic 09 and Topic 10, and
the two-pointer scan over a sorted array is the merge step of merge sort. The
index discipline in Part 2 is the single thing that transfers to every other
topic in this repo.
