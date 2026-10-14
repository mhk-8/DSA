# Heaps & Priority Queues

**Status:** Material ready — study not started
**Covers:** the priority-queue idea, the heap inside an array, sift-up and sift-down by hand, O(n) build-heap and heap sort, `std::priority_queue` and its comparator rule, lazy deletion and `multiset`, top-K, k-way merge, two heaps, greedy and scheduling with a heap, the regret pattern, and Dijkstra

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Heaps-and-Priority-Queues-Guide.pdf` | **37-page guide.** Priority queues and heaps from zero (complete tree + heap property, the array index formulas), building a heap by hand (sift-up, sift-down, worked push / pop / build-heap traces, why heapify is O(n), heap sort), the STL (`priority_queue`, **the comparator trap**, functor / lambda / pair ordering, `make_heap`, lazy deletion, `multiset`), the mental model and the size-k rule, top-K, k-way merge, two heaps, greedy and scheduling, Dijkstra and minimax paths, the 12 patterns, the approach framework, the 14-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 3-week plan. |
| `notes/Heaps-and-Priority-Queues-Solved-Questions.pdf` | **41-page solved-questions book.** All 38 problems from Part 13 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. TODOs 1–6 build a heap by hand, without `std::priority_queue`. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 35 test cases, all passing |
| `solutions/reference-part13-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 115 test cases, all passing (also clean under AddressSanitizer / UBSan) |

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
| 1 | Repeatedly take the best | "each turn, take the largest/smallest and …" | pop, modify, push back |
| 2 | K-th / top-K with a bounded heap | "k-th largest", "top k", "k closest" | min-heap of size k for the largest |
| 3 | Top-K by frequency | "k most frequent" | counts → heap of `(freq, value)` |
| 4 | K-way merge | "merge k sorted", sorted matrix, smallest pairs | one head per list, push the successor |
| 5 | Two heaps | median, balance two halves | max-heap low half + min-heap high half |
| 6 | Sort + heap of available options | options unlock over time | pointer over sorted input + value heap |
| 7 | Greedy combine the two best | connect ropes, stones, Huffman | pop two, push the combination |
| 8 | Regret / exchange greedy | take as many as possible under a limit | accept all, evict the worst when the limit breaks |
| 9 | Cooldown / no-adjacent scheduling | task scheduler, reorganize string | heap of counts + a waiting queue |
| 10 | Event simulation | CPU, servers, meeting rooms | a clock that jumps + free / busy heaps |
| 11 | Dijkstra-style search | weighted shortest path, minimax path | min-heap of `(cost, state)` + stale skip |
| 12 | Heap with deletions | sliding window median, skyline | `multiset`, or lazy deletion |

---

## The five rules

1. **A heap answers one question cheaply: "what is the best right now?"** Use it when you ask that repeatedly while the set changes.
2. Decide **what one entry is** and **which way the heap points** before writing code — say it out loud.
3. **k largest → min-heap of size k. k smallest → max-heap of size k.** The top is the one to evict.
4. `cmp(a, b)` true means **a goes below b**. `priority_queue<int>` is a **max**-heap.
5. A heap cannot erase or update: **push a new entry and skip stale ones**, or use a `multiset`.

---

## The lines worth memorising

```cpp
// the comparator rule, and the two heaps you will write most
priority_queue<int> maxH;                                   // largest on top
priority_queue<int, vector<int>, greater<int>> minH;        // smallest on top

// k largest of a stream: a MIN-heap of size k, top = the k-th largest
for (int x : a) { minH.push(x); if ((int)minH.size() > k) minH.pop(); }

// build-heap is O(n): sift down every internal node, bottom-up
for (int i = n / 2 - 1; i >= 0; i--) siftDown(a, n, i);
```

---

## Progress

- [ ] Part 0–1 — the heap in an array, sift-up, sift-down, build-heap, heap sort
- [ ] Practice file: TODOs 1–6 (by hand: `isMaxHeap`, `siftUp`, `siftDown`, `MaxHeap`, `buildMaxHeap`, `heapSort`)
- [ ] Part 2–3 — `std::priority_queue`, the comparator rule, the size-k rule
- [ ] Practice file: TODOs 7–9 (`kthLargest`, `connectRopes`, `sortKSorted`)
- [ ] Part 4–5 — top-K and k-way merge
- [ ] Part 6 — two heaps; practice TODO 10 (`MedianFinder`)
- [ ] Part 7–8 — greedy, scheduling, the regret pattern, Dijkstra
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: is-array-a-heap, min-heap → max-heap, merge k sorted arrays, is a binary tree a heap, Huffman coding

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 295 (Median from Data Stream), LC 23 (Merge k Sorted Lists), LC 215 (Kth
Largest), LC 347 (Top K Frequent), LC 973 (K Closest Points), LC 621 (Task
Scheduler) and LC 743 (Network Delay Time)** are the most-asked heap questions in
on-campus drives — Amazon, Microsoft, Adobe, Flipkart, Walmart, Goldman Sachs.
Be able to write all of them cold.

For Indian **written rounds** specifically, also drill: implementing a heap on
an array, **"build a heap — what is the complexity?"** (O(n), with the
argument), heap sort and its stability, checking whether an array is a heap,
sorting a k-sorted array, minimum cost of ropes, and merge k sorted arrays.

## Where this topic leads

Dijkstra and Prim are the centre of Topic 12 (Graphs). The regret pattern
returns in Topic 10 (Greedy), where exchange arguments prove it correct. Heap
sort and quickselect belong to Topic 09 (Searching & Sorting). LRU and LFU
caches in Topic 15 are what you build when a heap is *not* enough.
