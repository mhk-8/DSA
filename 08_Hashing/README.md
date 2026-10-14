# Hashing

**Status:** Material ready — study not started
**Covers:** how a hash table works inside (direct addressing, hash functions, collisions, load factor, rehashing), separate chaining and open addressing with tombstones by hand, `unordered_map` vs `map` and the `operator[]` trap, counting and signatures, complement lookups, prefix sums with a hash map, sliding windows, bijections, LRU / LFU / O(1) getRandom designs, rolling hashes, and the array as its own hash table

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Hashing-Guide.pdf` | **41-page guide.** Hashing from zero (direct addressing → hash function → collisions → load factor), building a table by hand (chaining with rehash, open addressing, why deletion needs tombstones, probing strategies, polynomial string hashes), the STL (the four containers, **the `operator[]` trap**, erasing while iterating, keys without `std::hash`, anti-hash tests, arrays as maps), the mental model (key / value / question; first vs last index vs count), counting and signatures, complement lookups, **prefix sums + hash map in full**, sliding windows, bijections, design problems (LRU, getRandom, LFU), rolling hashes and Rabin-Karp, the array as its own table, the 12 patterns, the approach framework, the 16-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 3-week plan. |
| `notes/Hashing-Solved-Questions.pdf` | **41-page solved-questions book.** All 38 problems from Part 16 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. TODOs 1–3 build hash tables by hand, without the STL. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 49 test cases, all passing |
| `solutions/reference-part16-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 143 test cases, all passing (also clean under AddressSanitizer / UBSan; the O(1) designs, Palindrome Pairs and the rolling-hash solution were also fuzzed against brute force) |

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
| 1 | Existence / duplicate check | "seen before", "duplicate", "unique" | `unordered_set`, `insert(x).second` |
| 2 | Frequency counting | "how many times", anagram, supply vs demand | count map or `int cnt[26]` |
| 3 | Complement lookup | "two values that add up / differ by k" | value → index; look up, then insert |
| 4 | Last / first position | "within distance k", "longest" | value → last index, or → first index |
| 5 | Signature grouping | "group", "same pattern" | a canonical key shared by equivalent items |
| 6 | Bijection | isomorphic, word pattern | two maps, one each direction |
| 7 | Prefix sum + hash map | "subarray with sum k", equal 0/1, divisible by k | `count[P − k]`, seeded with `{0: 1}` |
| 8 | Sliding window + map | "longest substring with …", anagrams of p | window contents in a map |
| 9 | Set-based run walking | "longest consecutive" | start only where `x − 1` is absent |
| 10 | Design with map + list / vector | LRU, LFU, O(1) getRandom | the map points into the second structure |
| 11 | Rolling hash | repeated substring, pattern search | polynomial hash, O(1) slide, verify |
| 12 | Array as hash table | values in 1 … n, O(1) extra space | cyclic placement or sign marking |

---

## The five rules

1. **Hashing trades memory for time.** If the brute force searches earlier elements, hash them.
2. **Choose the key, then the value** — presence, count, **first** index (longest) or **last** index (nearest).
3. **Look up, then insert.** That keeps pairs i < j and never pairs an element with itself.
4. **`[]` writes, `find` reads.** `m[x]` on a missing key inserts it.
5. **Subarray + sum → prefix sums + map, seeded with the empty prefix.** It handles negatives; a sliding window does not.

---

## The six lines worth memorising

```cpp
// count subarrays with sum k — works with negative numbers
unordered_map<long long, int> seen{{0, 1}};          // the empty prefix
long long prefix = 0; int count = 0;
for (int x : a) {
    prefix += x;
    auto it = seen.find(prefix - k);
    if (it != seen.end()) count += it->second;
    seen[prefix]++;
}
```

Subarray Sum Equals K, Contiguous Array, Subarray Sums Divisible by K,
Continuous Subarray Sum, the GfG largest-zero-sum subarray and the 2-D
submatrix version are all this block with a different key or value.

---

## Progress

- [ ] Part 0–1 — direct addressing, collisions, chaining, open addressing, tombstones
- [ ] Practice file: TODOs 1–3 (by hand: `ChainedHashMap`, `OpenAddressingSet`, `rabinKarp`)
- [ ] Part 2–3 — the STL, the `operator[]` trap, key / value / question
- [ ] Practice file: TODOs 4–6 (`firstNonRepeatingStream`, `twoSum`, `countDistinctInWindows`)
- [ ] Part 4–5 — counting, signatures, complements, longest consecutive
- [ ] Part 6 — prefix sums + hash map; practice TODOs 7–8
- [ ] Part 7–8 — sliding windows and bijections; practice TODOs 9–10
- [ ] Part 9–11 — LRU / getRandom / LFU, rolling hashes, the array as a table
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: largest zero-sum subarray, count distinct in every window, itinerary from tickets, array subset of another

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 1 (Two Sum), LC 49 (Group Anagrams), LC 560 (Subarray Sum Equals K),
LC 128 (Longest Consecutive Sequence), LC 3 (Longest Substring Without
Repeating Characters) and LC 146 (LRU Cache)** are the most-asked hashing
questions in on-campus drives — Amazon, Microsoft, Adobe, Flipkart, Paytm,
Goldman Sachs, TCS Digital, Infosys. Be able to write all six cold.

For Indian **written rounds** specifically, also drill: explaining chaining vs
open addressing and why deletion needs tombstones, the load factor and
rehashing, first non-repeating character in a stream, largest subarray with
0 sum, count distinct elements in every window, and count pairs with a given sum.

## Where this topic leads

The sliding window is shared with Strings (Topic 02). Graphs (Topic 12) keep
visited sets and adjacency in hash maps. Memoisation in Dynamic Programming
(Topic 11) is a hash map from state to answer. Tries (Topic 14) are the
alternative when keys are strings and prefixes matter. LRU and LFU return in
Design & LLD (Topic 15).
