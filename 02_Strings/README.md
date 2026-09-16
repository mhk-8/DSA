# Strings

**Status:** Material ready — study not started
**Covers:** Characters and ASCII, the full `std::string` toolkit, frequency counting, two pointers, the universal sliding-window template, palindromes and expand-around-centre, parsing and tokenising, KMP and the prefix function, rolling hashes, and the two-string DP grid

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Strings-Guide.pdf` | **59-page guide.** Characters from zero, the whole `std::string` API with its costs, the mental model, frequency counting in full, the three two-pointer shapes, the sliding window in full, palindromes in full, parsing and building, KMP and rolling hashes, two-string DP, the 14 patterns, the approach framework, the 18-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 3-week plan and a quick-reference card. |
| `notes/Strings-Solved-Questions.pdf` | **43-page solved-questions book.** All 38 problems from Part 14 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 54 test cases, all passing |
| `solutions/reference-part14-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 216 test cases, all passing |

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
| 1 | Two pointers, converging | palindrome, reverse, mirror, "from both ends" | `l = 0, r = n-1; while (l < r)` |
| 2 | Read / write pointer | "in place", "O(1) extra space", remove, compress | `if (keep) s[write++] = s[read]` |
| 3 | Frequency counting | anagram, permutation, "same characters" | `int cnt[26]` / `cnt[128]` |
| 4 | Canonical signature | group, bucket, "which of these are equivalent" | sorted string, or a `#`-joined count key |
| 5 | Fixed-size window | "of length k", "all anagrams of p" | add `s[r]`, remove `s[r-k]` |
| 6 | Variable window — longest | "longest substring such that …" | `while (invalid) shrink;` record **after** |
| 7 | Variable window — shortest | "minimum window containing …" | `while (valid) { record; shrink; }` |
| 8 | Expand around centre | palindromic substring, "count palindromes" | 2n−1 centres, expand both ways |
| 9 | String as a stack | "remove adjacent", backspace, collapse | `out.back()`, `out.pop_back()` |
| 10 | Parsing & tokenising | atoi, version, words, calculator, path | `stringstream`, index walk, case list |
| 11 | Character mapping | isomorphic, word pattern, "one-to-one" | **two** maps, both directions |
| 12 | Prefix function (KMP) | "find the pattern", period, border | `pi[i]` = longest proper border |
| 13 | Rolling hash | fixed-width windows, binary search on length | polynomial hash, `(x % M + M) % M` |
| 14 | Two-string DP grid | two strings + transform / align / match | `(n+1) × (m+1)` table |

---

## The five rules

1. **Contiguous → window. Gaps allowed → DP.** "Substring" and "subsequence" are different problems; confusing them has cost more interviews than any algorithm.
2. Store **`int n = s.size()`** at the top of every function. `size()` is unsigned, and `s.size() - 1` on an empty string is 18446744073709551615.
3. **Always initialise** the frequency array: `int cnt[26] = {0};`.
4. **`s += c`, never `s = s + c`.** The second one is O(n²) and invisible in a code review.
5. A `while` inside a `for` is still **O(n)**: the left pointer only moves forward, at most n times in total. Say that sentence out loud in the interview.

---

## The seven lines worth memorising

```cpp
// the universal sliding window
int l = 0;
for (int r = 0; r < n; r++) {
    add(s[r]);                            // 1. what does entering do?
    while (invalid()) { remove(s[l]); l++; }   // 2. what makes it illegal?
    best = max(best, r - l + 1);          // 3. longest -> record AFTER the while
}
```

LC 3, LC 424, LC 340, LC 904, LC 438, LC 567 and LC 76 are all this block with
a different `invalid()` and the record moved. Learn it as one unit.

And the twelve lines beside it:

```cpp
// prefix function — pi[i] = longest proper prefix of p[0..i] that is also a suffix
vector<int> pi(m, 0);
for (int i = 1; i < m; i++) {
    int j = pi[i - 1];
    while (j > 0 && p[i] != p[j]) j = pi[j - 1];   // fall back, NOT j--
    if (p[i] == p[j]) j++;
    pi[i] = j;
}
// smallest period = n - pi[n-1];   longest border = pi[n-1]
```

That one array answers LC 28, LC 214, LC 459 and LC 1392.

---

## Progress

- [ ] Part 0–1 — characters, ASCII, and the whole `std::string` toolkit with its costs
- [ ] Practice file: TODOs 1–3 (`reverseString`, `isPalindromeFiltered`, `isAnagram`)
- [ ] Part 2–4 — the mental model, frequency counting, the three two-pointer shapes
- [ ] Practice file: TODOs 4–5 (`compress`, `addStrings`)
- [ ] Part 5 — the sliding window, all three flavours
- [ ] Practice file: TODO 6 (`lengthOfLongestSubstring`)
- [ ] Part 6 — palindromes, expand around centre
- [ ] Practice file: TODOs 7–8 (`longestPalindrome`, `countPalindromicSubstrings`)
- [ ] Part 7 — parsing, tokenising and building
- [ ] Part 8 — KMP and rolling hashes
- [ ] Practice file: TODO 9 (`prefixFunction`, `strStrKMP`)
- [ ] Part 9 — the two-string DP grid
- [ ] Practice file: TODO 10 (`editDistance`)
- [ ] Tier 1 problems (13) — solutions in the PDF
- [ ] Tier 2 problems (15) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only classics: rotations, permutations, stream of characters, run-length coding

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the solved-questions book. Reading the solution before
struggling with the problem teaches you nothing. After you solve one, still read
the *Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 3 (Longest Substring Without Repeating Characters), LC 5 (Longest
Palindromic Substring), LC 49 (Group Anagrams), LC 76 (Minimum Window Substring)
and LC 438 (Find All Anagrams)** are the five most-asked string questions in
on-campus drives — Amazon, Microsoft, Adobe, Goldman Sachs, TCS Digital,
Infosys. Be able to write all five from a blank page.

For Indian **written rounds** specifically, also drill: checking whether two
strings are rotations of each other, printing all permutations of a string, the
first non-repeating character **in a stream**, removing duplicates in place,
run-length encoding and decoding, and converting a sentence to camelCase.

## Where this topic leads

The frequency tables here are the entry point to Topic 08 Hashing, and the
rolling hash in Part 8.6 is a preview of it. The prefix function is what makes
Topic 14 Tries feel familiar. The two-string grid in Part 9 *is* one of the
standard shapes in Topic 11 Dynamic Programming. The sliding window reappears in
Topic 01 Arrays, and the string-as-a-stack pattern in Part 2.7 is the same idea
as Topic 04 Stacks & Queues.
