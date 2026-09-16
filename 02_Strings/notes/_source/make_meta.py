#!/usr/bin/env python3
"""Generate strings-solved.meta.json for build_solved_pdf.py."""
import json

P = lambda i, n, t, d, pat, prob, app, cx, trap: dict(
    id=i, num=n, title=t, difficulty=d, pattern=pat,
    problem=prob, approach=app, complexity=cx, trap=trap)

tier1 = [
P("LC344", 344, "Reverse String", "EASY", "Two pointers, converging",
  "Reverse a `vector<char>` in place. You must do it with O(1) extra memory — no second array, no `reverse` call.",
  "One index at each end, walking towards each other, swapping as they go.\n\nThe loop condition is `l < r`, not `l <= r`. At `l == r` you are looking at a single middle character, which is already in the right place; swapping it with itself is harmless but pointless, and `<` handles odd and even lengths with no special case at all.",
  "**O(n)** time — each character is touched once. **O(1)** extra space.",
  "Writing `while (l <= r)` is not wrong here, but the same habit breaks in problems where the middle element must be treated differently. Learn `l < r` as the default and deviate deliberately."),

P("LC125", 125, "Valid Palindrome", "EASY", "Two pointers with filtering",
  "A phrase is a palindrome if, after keeping only alphanumeric characters and lower-casing them, it reads the same forwards and backwards. Decide whether the given string qualifies.",
  "Do not build a cleaned copy — that is an extra O(n) allocation you do not need. Walk two pointers inwards and skip the characters you do not care about as you go.\n\nInside the main loop, advance `l` past non-alphanumerics and retreat `r` past them, then compare the two survivors case-insensitively.",
  "**O(n)** time — each index is visited at most once by either pointer. **O(1)** space.",
  "Both inner skip loops need `l < r` repeated in their conditions. Without it, an input like `\",,,,\"` sends `l` walking straight off the end of the string and you read out of bounds. This is the single most common failure on this problem."),

P("LC242", 242, "Valid Anagram", "EASY", "Frequency counting",
  "Return true if `t` is a rearrangement of `s`. Both consist of lowercase English letters.",
  "Guard the lengths first — different lengths can never be anagrams, and the guard is what makes the rest of the argument work.\n\nThen count up from `s` into a 26-slot array and count down from `t`. If any count goes negative, `t` has more of that letter than `s` had, so bail out immediately. If nothing goes negative and the sizes were equal, nothing can be left over either, so the answer is true.",
  "**O(n)** time, **O(26) = O(1)** space. Sorting both strings also works but is O(n log n).",
  "`int cnt[26];` without `= {0}` is filled with garbage. The code compiles, runs, and is wrong differently on every machine. Write `int cnt[26] = {0};` every single time — the `{0}` zeroes all 26 slots, not just the first."),

P("LC387", 387, "First Unique Character in a String", "EASY", "Frequency counting, two passes",
  "Return the index of the first character in `s` that appears exactly once, or −1 if there is none.",
  "Two passes. The first fills a 26-slot count array. The second walks the string **in order** and returns the index of the first character whose count is 1.\n\nThe second pass has to be over the string, not over the count array — the count array has lost all position information, and the question asks for the *first* such character.",
  "**O(n)** time (two linear passes), **O(1)** space.",
  "Scanning the 26-slot array instead of the string finds the alphabetically-smallest unique character, not the first one. On `\"loveleetcode\"` that returns the wrong index."),

P("LC383", 383, "Ransom Note", "EASY", "Frequency counting",
  "Can `ransomNote` be built using only the letters available in `magazine`, with each letter used at most as many times as it appears there?",
  "Exactly the second half of Valid Anagram, with the length guard removed. Count the magazine's letters up, then count the note's letters down, and fail the moment a count goes negative.\n\nNote the direction: you count the **supply** up and the **demand** down. Getting them the wrong way round answers a different question.",
  "**O(n + m)** time, **O(26) = O(1)** space.",
  "There is no size guard here, and there should not be — a short note from a long magazine is perfectly valid. Copying the guard across from LC 242 rejects every legitimate case."),

P("LC14", 14, "Longest Common Prefix", "EASY", "Vertical scan",
  "Find the longest string that is a prefix of every string in the array. Return `\"\"` if there is none.",
  "Scan **column by column** rather than string by string: take the i-th character of the first word and check it against the i-th character of every other word. The moment one word is too short or disagrees, the answer is everything before column i.\n\nThis stops as early as possible — the work is bounded by the length of the answer times the number of words, not by the total input.",
  "**O(S)** where S is the sum of all characters, and much better in practice. **O(1)** extra space.",
  "`strs[j][i]` when word j is shorter than i is undefined behaviour. The length check `i >= strs[j].size()` must come **first** in the `||`, because `||` short-circuits left to right."),

P("LC58", 58, "Length of Last Word", "EASY", "Reverse scan",
  "Return the length of the last word in a string, where a word is a maximal run of non-space characters. The string may have trailing spaces.",
  "Walk backwards from the end. First skip every trailing space, then count characters until you hit a space or run out of string.\n\nTwo loops, in that order. Scanning forwards and remembering the last word also works but touches every character; the backward scan touches only the trailing spaces plus the last word.",
  "**O(n)** worst case, **O(length of last word + trailing spaces)** in practice. **O(1)** space.",
  "Skipping the trailing spaces is a separate loop that must run *first*. Starting the count immediately on an input like `\"day \"` returns 0."),

P("LC28", 28, "Find the Index of the First Occurrence in a String", "EASY", "Naive pattern matching",
  "Return the index of the first occurrence of `needle` in `haystack`, or −1. By convention an empty needle matches at index 0.",
  "The naive scan: for every possible start position, compare characters until they disagree or the needle is exhausted.\n\nThe loop bound is `i + m <= n`, which stops before the needle could run past the end of the haystack. That single expression removes every bounds check from the inner loop.\n\nKMP (problem 29) gets this to O(n + m), and is worth mentioning — but for a single search on ordinary text the naive version is what an interviewer expects first.",
  "**O(n · m)** worst case, close to O(n) on ordinary text. **O(1)** space.",
  "The empty-needle case must return 0, not −1. And writing the loop as `i < n` rather than `i + m <= n` means the inner comparison reads past the end of the haystack on the last few positions."),

P("LC205", 205, "Isomorphic Strings", "EASY", "Character mapping, both directions",
  "Two strings are isomorphic if the characters of `s` can be replaced to get `t`, where every occurrence of a character maps to the same character, and **no two characters map to the same one**.",
  "Keep **two** maps, `s → t` and `t → s`, and require both to agree at every position.\n\nThe second map is what enforces the no-two-characters-collide rule. With only `s → t`, the pair `(\"ab\", \"aa\")` passes: `a → a` and `b → a` are individually consistent, but they collapse two characters into one, which the problem forbids.",
  "**O(n)** time, **O(128) = O(1)** space with fixed arrays.",
  "One map is not enough, and `(\"ab\", \"aa\")` is the counterexample that proves it. If you can only remember one thing about this problem, remember that it needs the mapping checked in both directions."),

P("LC392", 392, "Is Subsequence", "EASY", "One pointer per string",
  "Return true if `s` is a subsequence of `t` — that is, `s` can be obtained from `t` by deleting some characters without changing the order of the rest.",
  "One pointer into `s`, one scan across `t`. Whenever the current character of `t` matches the character `s` is waiting for, advance `s`'s pointer. At the end, `s` is a subsequence exactly when its pointer reached the end.\n\nGreedy is correct, and the exchange argument is worth saying out loud: matching the **earliest** possible position in `t` is never worse, because any later match leaves strictly fewer characters of `t` available for the rest of `s`.",
  "**O(n + m)** time, **O(1)** space.",
  "The follow-up — many `s` values against one fixed `t` — changes the answer completely: precompute, for each position of `t` and each letter, the next position of that letter, then each query is O(|s|). Interviewers ask this follow-up often."),

P("LC13", 13, "Roman to Integer", "EASY", "Parsing with a look-ahead rule",
  "Convert a Roman numeral in the range 1–3999 to an integer.",
  "Roman numerals are additive except for six subtractive pairs. Rather than special-casing those six, use the rule that generates them: **a symbol whose value is smaller than the one immediately after it is subtracted**, and every other symbol is added.\n\nSo walk left to right, look one character ahead, and choose the sign. No lookup of pairs needed.",
  "**O(n)** time, **O(1)** space (the value table has seven fixed entries).",
  "The look-ahead needs the bound `i + 1 < n`, or the last character reads past the end. And the comparison is strictly `<` — equal adjacent symbols like `\"II\"` must add, not subtract."),

P("LC12", 12, "Integer to Roman", "MEDIUM", "Greedy over a table",
  "Convert an integer in the range 1–3999 to its Roman numeral.",
  "Put the six subtractive forms — 900/CM, 400/CD, 90/XC, 40/XL, 9/IX, 4/IV — **into the value table** alongside the seven plain symbols, sorted descending. Then a plain greedy loop works: repeatedly subtract the largest value that fits and append its symbol.\n\nBuilding the table that way is the entire trick. With it, there are no special cases; without it, you need six of them.",
  "**O(1)** time — at most 13 table entries and a bounded number of repeats each. **O(1)** space.",
  "Greedy is only correct because the table includes the subtractive forms. Drop them and 4 renders as `\"IIII\"`, 9 as `\"VIIII\"`. The table construction *is* the proof of correctness."),

P("LC415", 415, "Add Strings", "EASY", "Digit arithmetic from the end",
  "Add two non-negative integers given as decimal strings, without converting them to an integer type and without using a big-integer library.",
  "Exactly how you add by hand: one index at the end of each string, walk left, add the two digits plus the carry, append the units digit of the sum and keep the tens as the new carry.\n\nAppend forwards and `reverse` once at the end. Inserting at the front instead shifts the whole string on every digit and turns an O(n) routine into O(n²).",
  "**O(max(n, m))** time, **O(max(n, m))** space for the result.",
  "The loop condition needs `|| carry` as a third clause. Without it, `\"99\" + \"1\"` produces `\"00\"` — both strings are exhausted while a carry is still outstanding, and it is silently dropped."),
]

tier2 = [
P("LC3", 3, "Longest Substring Without Repeating Characters", "MEDIUM", "Variable window, longest",
  "Find the length of the longest substring of `s` containing no repeated character.",
  "The universal window template. A character enters at `r` and increments its count. The window is illegal exactly when that character's count reaches 2 — and checking only the arriving character is enough, because the window was valid before it arrived. Shrink from the left until it is valid again, then record the length.\n\nBecause this is a **longest** problem, the recording happens *after* the shrink loop, where the window is guaranteed valid.\n\nThe nested `while` is not a second O(n) factor: `l` only ever increases, and it can increase at most n times over the whole run.",
  "**O(n)** time — at most 2n pointer moves. **O(min(n, Σ))** space.",
  "`\"dvdf\"` is the case that catches the jump variant. If you move `l` straight to `last[s[r]] + 1` without a `max`, an old occurrence drags `l` backwards and the answer comes out as 2 instead of 3."),

P("LC438", 438, "Find All Anagrams in a String", "MEDIUM", "Fixed window + count table",
  "Return the start indices of every substring of `s` that is an anagram of `p`.",
  "A fixed-size window of width `|p|`. There is no shrink loop at all — one character enters and one leaves on every step.\n\nMaintain a 26-slot count of the window and compare it against the count of `p`. `memcmp` on 26 ints is a handful of instructions, so the comparison is genuinely constant time.\n\nThe three index facts, and they are the same three in every fixed window: the character leaving is `s[r - k]`, the window is full from `r == k - 1` onwards, and the window's left end is `r - k + 1`.",
  "**O(n · 26) = O(n)** time, **O(26) = O(1)** space.",
  "Guard `n < k` before you start, or the very first `r >= k - 1` check reads a window that was never filled. And the character leaving is `s[r - k]` — off by one there gives answers that are right on some inputs and wrong on others."),

P("LC567", 567, "Permutation in String", "MEDIUM", "Fixed window + count table",
  "Return true if `s2` contains any permutation of `s1` as a substring.",
  "Identical to LC 438 in every respect except the answer: instead of collecting the start indices, return true at the first match.\n\nRecognising that these two problems are the same code is worth more than solving either one. If an interviewer asks both, say so.",
  "**O(n · 26) = O(n)** time, **O(26) = O(1)** space.",
  "\"Permutation\" and \"anagram\" mean the same thing here. Some candidates reach for a permutation-generating routine, which is O(k!) and will not finish. The question is about multiset equality, nothing more."),

P("LC424", 424, "Longest Repeating Character Replacement", "MEDIUM", "Window with `len − maxFreq ≤ k`",
  "You may change at most `k` characters of `s` to any other uppercase letter. Find the length of the longest substring that can be made to contain a single repeated letter.",
  "The validity test is the whole problem: a window of length L whose most frequent character occurs `maxFreq` times needs exactly `L − maxFreq` replacements. So the window is legal while `(r − l + 1) − maxFreq <= k`.\n\n`maxFreq` is deliberately **never decreased** when the window shrinks, so it can be stale — larger than the true maximum of the current window. This is still correct, and the argument is worth rehearsing: a stale `maxFreq` only makes the test more permissive, so the window never shrinks when it should not; and `best` can only be updated by a window whose `maxFreq` was genuinely achieved, because `best` grows only when the window does.",
  "**O(n)** time, **O(26) = O(1)** space.",
  "The alphabet here is **uppercase**, so `c - 'a'` indexes out of bounds with a negative subscript. Either use `c - 'A'` or index a 128-slot table by the raw character, which is case-agnostic and costs nothing."),

P("LC76", 76, "Minimum Window Substring", "HARD", "Shrink-while-valid window",
  "Find the shortest substring of `s` containing every character of `t`, including duplicates. Return `\"\"` if none exists.",
  "This is the template with the `while` condition flipped: shrink **while the window is valid**, recording the answer inside that loop, because that is where the shortest windows live.\n\nRead `need[c]` as a signed debt. Positive means \"still owed\", zero or negative means \"satisfied, with surplus\". Testing `need[c]-- > 0` checks the value *before* decrementing, so `missing` drops only for a character that was genuinely still needed — a fourth `'a'` when only three were required does not count. On the way out, `++need[l] > 0` raises `missing` only when removing that character actually breaks validity.\n\nStore `bestL` and `bestLen` and call `substr` exactly once at the end.",
  "**O(n + m)** time, **O(128) = O(1)** space.",
  "Duplicates in `t` are the case that separates working code from nearly-working code. `t = \"AABC\"` requires two `A`s, and any solution that tracks a set of distinct characters rather than counts will accept a window with only one."),

P("LC49", 49, "Group Anagrams", "MEDIUM", "Canonical signature",
  "Group the strings in an array so that anagrams of each other end up in the same group. The order of groups and of strings within a group does not matter.",
  "Map every word to a **canonical form** — a value that is identical for all members of its group — and use it as a hash-map key. The sorted word is the obvious choice: `\"eat\"`, `\"tea\"` and `\"ate\"` all sort to `\"aet\"`.\n\nThe alternative signature is the 26-slot count rendered as a string, which is O(k) per word instead of O(k log k). Say both; write the sorted one, because it is four lines shorter and words are usually short.",
  "**O(n · k log k)** time for n words of length k. **O(n · k)** space.",
  "If you use the count-vector signature, the separators are essential: `\"#1#0#...\"`, not `\"10...\"`. Without them, counts of 1 and 12 produce the same digit string as counts of 11 and 2, and unrelated words collide."),

P("LC5", 5, "Longest Palindromic Substring", "MEDIUM", "Expand around centre",
  "Return the longest palindromic substring of `s`.",
  "A string of length n has exactly **2n − 1 centres** — n sitting on a character (odd-length palindromes) and n − 1 sitting between two characters (even-length). Every palindromic substring has exactly one centre, so enumerating centres enumerates palindromes with no duplication.\n\nFor each centre, expand outwards while the characters match, and keep the longest span seen.\n\nThis beats the O(n²)-space DP table on space while matching it on time. Manacher's algorithm gets it to O(n); naming it is worth credit, writing it under time pressure usually is not.",
  "**O(n²)** time, **O(1)** extra space.",
  "When the expand loop exits, `l` and `r` have each overshot by one. The length is therefore `r - l - 1` and the start is `l + 1`. Writing `r - l + 1` — correct for an inclusive range, wrong here — is the most common error on this problem."),

P("LC647", 647, "Palindromic Substrings", "MEDIUM", "Expand around centre",
  "Count every palindromic substring of `s`. Substrings with the same text but different positions count separately.",
  "The same 2n − 1 centres as LC 5, counting instead of measuring: every successful expansion step *is* one more palindromic substring, so increment a counter inside the expand loop.\n\nBeing able to write LC 5 and LC 647 as the same loop with a different body is the point of doing both.",
  "**O(n²)** time, **O(1)** space.",
  "Increment the counter **inside** the `while`, before expanding further — each successful match is its own palindrome. Counting once per centre after the loop counts only the longest one and undercounts badly."),

P("LC680", 680, "Valid Palindrome II", "EASY", "First mismatch, two tries",
  "Return true if `s` can be made a palindrome by deleting **at most one** character.",
  "You do not need to try deleting each character in turn. Walk two pointers inwards as normal; the **first** mismatch is the only place a deletion could ever help, and there are exactly two candidates — drop the left character or drop the right one.\n\nSo on the first mismatch, check whether either of the two remaining ranges is a plain palindrome, and return the OR. If the pointers meet without any mismatch, the string was already a palindrome.\n\nThat argument — one decision point, two branches — is what makes this O(n) rather than O(n²), and it is what the interviewer is listening for.",
  "**O(n)** time — the helper runs at most twice. **O(1)** space.",
  "Take the range-based helper `isPalRange(s, l, r)` rather than building substrings. `isPal(s.substr(l+1, r-l))` is correct but allocates, and it makes the index arithmetic much easier to get wrong."),

P("LC151", 151, "Reverse Words in a String", "MEDIUM", "Tokenise, or three reversals",
  "Reverse the order of the words in a string. Words are separated by one or more spaces; leading and trailing spaces must be removed and inner runs collapsed to a single space.",
  "`stringstream`'s `operator>>` handles every whitespace rule for free: it skips arbitrary runs, leading and trailing. Read the words into a vector, then join them in reverse with single spaces.\n\nThe O(1)-space follow-up is worth knowing: reverse the whole string, then reverse each word in place, then squeeze out the extra spaces with a read/write pointer. Three passes, no extra container. Offer it after the simple version works.",
  "**O(n)** time, **O(n)** space for the words (**O(1)** extra for the three-reversal version).",
  "The trailing space. Appending `word + ' '` for every word leaves one at the end, and the judge checks for it. Append the separator only when the word is not the last one."),

P("LC443", 443, "String Compression", "MEDIUM", "Read/write pointer",
  "Compress a `vector<char>` in place: each run of repeated characters becomes the character followed by the run length, with the length omitted when it is 1. Return the new length.",
  "The read/write pattern. `read` scans a whole run, `write` emits the character and — when the run is longer than 1 — its digits.\n\nThe invariant that makes this safe is that `write` never overtakes `read`: a run of length k is replaced by at most `1 + digits(k)` characters, which is ≤ k for every k ≥ 1. Say that sentence when asked why in-place is legal here.",
  "**O(n)** time, **O(1)** extra space.",
  "The run length can be **multi-digit**. `chars[write++] = run + '0'` looks right and breaks on any run of 10 or more. Convert with `to_string(run)` and write the digits one at a time."),

P("LC8", 8, "String to Integer (atoi)", "MEDIUM", "Parsing, case enumeration",
  "Implement `atoi`: skip leading spaces, read an optional sign, read digits until a non-digit, and clamp the result to the 32-bit signed range.",
  "There is no algorithm here — only five steps that must happen in exactly this order: skip spaces, read at most one sign, accumulate digits, clamp, stop at the first non-digit.\n\nClamp **inside** the digit loop, not after it. A 30-digit input overflows a 64-bit integer long before the loop ends, so the overflow test has to run on every digit. The clean form is `if (res > (INT_MAX - d) / 10) return ...` which never overflows at all.",
  "**O(n)** time, **O(1)** space.",
  "The range is asymmetric: `INT_MIN` is −2147483648 while `INT_MAX` is 2147483647, so the negative side allows one more. Clamping the magnitude at `INT_MAX` and then negating gets `\"-2147483648\"` wrong."),

P("LC165", 165, "Compare Version Numbers", "MEDIUM", "Parallel parsing",
  "Compare two dot-separated version strings. Return −1, 0 or 1. Leading zeros in a part are insignificant, and a missing trailing part is treated as zero — so `\"1.0\"` and `\"1.0.0\"` are equal.",
  "Parse both strings in lockstep, one part at a time, comparing the parsed integers as you go. Because a missing part parses as 0, the two rules fall out for free without any padding or splitting.\n\nThe loop condition is `while (i < n || j < m)` — **or**, not and. Once one string is exhausted, its remaining parts are 0 and the comparison must keep going against the other's.",
  "**O(n + m)** time, **O(1)** space.",
  "Comparing the strings lexicographically fails on `\"1.2\"` versus `\"1.10\"`, because `'2' > '1'` as characters while 2 < 10 as numbers. The comparison must be numeric, part by part."),

P("LC6", 6, "Zigzag Conversion", "MEDIUM", "Row simulation",
  "Write the string in a zigzag across `numRows` rows, then read it off row by row.",
  "Do not compute geometry. Simulate: keep a current row and a direction that flips whenever you touch the top or bottom row, appending each character to its row's buffer. Concatenate the rows at the end.\n\nInitialising `dir = -1` so that the flip at row 0 makes it `+1` avoids an extra branch before the loop.",
  "**O(n)** time, **O(n)** space for the row buffers.",
  "`numRows == 1` must be special-cased. With one row, row 0 is also the last row, the direction flips on every character, and the row index walks straight out of range."),

P("LC179", 179, "Largest Number", "MEDIUM", "Custom comparator `a+b > b+a`",
  "Arrange the given non-negative integers so that their concatenation is the largest possible number, and return it as a string.",
  "Sort with a comparator that compares the two **concatenations**, not the two strings: `a` comes before `b` when `a + b > b + a`.\n\nThat is what makes `\"9\"` beat `\"34\"` (`\"934\" > \"349\"`) and `\"3\"` beat `\"30\"` (`\"330\" > \"303\"`). Comparing the strings directly, or comparing the numbers, gets both of those backwards.\n\nThis comparator is a genuine strict weak ordering — it behaves like comparing the infinite repetitions of each string — which is what makes `sort` legal rather than undefined behaviour. Interviewers do ask why.",
  "**O(n · k log n)** time for n numbers of k digits. **O(n · k)** space.",
  "All-zero input. `{0, 0}` concatenates to `\"00\"`, and the expected answer is `\"0\"`. One guard — if the first element after sorting is `\"0\"`, return `\"0\"` — handles every such case."),
]

tier3 = [
P("LC214", 214, "Shortest Palindrome", "HARD", "KMP on `s + '#' + rev(s)`",
  "Prepend the fewest possible characters to `s` to make it a palindrome, and return the result.",
  "The characters you prepend are forced: whatever follows the **longest palindromic prefix** of `s` has to be mirrored onto the front. So the problem reduces to finding that prefix.\n\nNow the transformation. The longest palindromic prefix of `s` is the longest prefix of `s` that is also a suffix of `reverse(s)` — which is exactly what the prefix function computes on the concatenation `s + '#' + reverse(s)`. Its last entry is the answer's length.\n\nThat is the whole solution: one prefix function, one `substr`, one concatenation.",
  "**O(n)** time, **O(n)** space.",
  "The `'#'` separator is load-bearing. Without a character that cannot appear in `s`, the border can straddle the join and report a length greater than `s.size()`, producing garbage on inputs like `\"aaaa\"`."),

P("LC459", 459, "Repeated Substring Pattern", "EASY", "Prefix function, period test",
  "Return true if `s` can be built by taking some proper substring of it and repeating it two or more times.",
  "`n - pi[n-1]` is the **smallest period** of the string — the shortest block that, repeated, generates it (possibly with a partial copy at the end). The string is a whole number of repetitions exactly when that period divides `n` evenly and the border is non-empty.\n\nTwo conditions, one line: `pi[n-1] > 0 && n % (n - pi[n-1]) == 0`.\n\nThe well-known one-liner `(s + s).substr(1, 2n - 2).find(s) != npos` is correct and cute, and it is O(n²) with `find`. Mention it, write the prefix-function version.",
  "**O(n)** time, **O(n)** space for the prefix array.",
  "The `pi[n-1] > 0` guard is not decoration. Without it, a string with no border at all gives a period equal to n, which divides n, and every string returns true."),

P("LC1392", 1392, "Longest Happy Prefix", "HARD", "Prefix function, directly",
  "Return the longest prefix of `s` that is also a suffix of `s`, excluding `s` itself.",
  "This problem *is* the definition of the prefix function's last entry. Build `pi` and return `s.substr(0, pi[n-1])`.\n\nIt is labelled Hard only because it assumes you know KMP. If you can write `prefixFunction` from memory, this is a three-line solution — which is the best possible argument for memorising those twelve lines outright.",
  "**O(n)** time, **O(n)** space.",
  "The word **proper** matters: the whole string is trivially both a prefix and a suffix of itself and does not count. The prefix function already excludes it by construction, which is why this works without any extra check."),

P("LC187", 187, "Repeated DNA Sequences", "MEDIUM", "Fixed window + rolling bitmask",
  "Find every 10-letter-long substring that occurs more than once in a DNA string over the alphabet `A`, `C`, `G`, `T`.",
  "Four letters need 2 bits each, so a 10-letter window packs into exactly **20 bits**. Roll it forward with a shift, an OR and a mask — O(1) per step — and this is not a hash at all but a perfect encoding, so there are no collisions to verify.\n\nCount each code in a hash map and emit the substring the moment its count reaches 2. Testing `== 2` rather than `>= 2` is what keeps duplicates out of the output without a second pass.",
  "**O(n)** time, **O(n)** space for the map.",
  "A generic polynomial rolling hash works too, but then a hash match is only a *candidate* and you must verify it with a real string comparison. The 2-bit packing sidesteps that entirely — say why when you choose it."),

P("LC516", 516, "Longest Palindromic Subsequence", "MEDIUM", "Interval DP",
  "Find the length of the longest palindromic **subsequence** of `s` — characters keep their order but gaps are allowed.",
  "`dp[i][j]` is the answer for the range `s[i..j]`. If the two ends match they can both be used, giving `dp[i+1][j-1] + 2`. If they do not, one of them must be discarded, so take the better of `dp[i+1][j]` and `dp[i][j-1]`.\n\nThere is an elegant alternative: **LPS(s) = LCS(s, reverse(s))**. It is a one-liner given the LCS routine from problem 34, and it is a satisfying thing to point out even if you then write the direct version.",
  "**O(n²)** time, **O(n²)** space (reducible to O(n)).",
  "`dp[i][j]` depends on `dp[i+1][j-1]` — a *larger* `i`. So `i` must **descend** and `j` ascend. A plain row-major fill reads uninitialised cells and returns plausible-looking nonsense."),

P("LC1143", 1143, "Longest Common Subsequence", "MEDIUM", "Two-string DP grid",
  "Return the length of the longest subsequence common to both strings.",
  "The canonical two-string grid. `dp[i][j]` is the answer for the first `i` characters of one string and the first `j` of the other — `i` and `j` are **counts**, not indices, which is what makes `dp[0][j]` a meaningful base case.\n\nIf the last characters match they can be paired: take the diagonal plus one. If not, one of them has to be dropped: try both and keep the better.\n\nLCS is the parent of a whole family. Minimum deletions to make two strings equal is `n + m − 2·LCS`; the shortest common supersequence is `n + m − LCS`; the longest common *substring* is the same grid with the mismatch case resetting to 0 and the answer taken from the maximum cell rather than the corner.",
  "**O(n · m)** time, **O(n · m)** space — reducible to **O(m)** with two rolling rows.",
  "Because `i` and `j` are counts, the characters being compared are `a[i-1]` and `b[j-1]`. Writing `a[i] == b[j]` reads one character too far and silently shifts the whole table."),

P("LC72", 72, "Edit Distance", "MEDIUM", "Two-string DP grid",
  "Find the minimum number of single-character insertions, deletions or replacements needed to turn `word1` into `word2`.",
  "The same grid as LCS with a different recurrence. When the characters match there is nothing to pay — take the diagonal. When they differ, pay 1 and take the best of three neighbours.\n\nLearn the three by what they mean, not by position: the diagonal is *replace*, the cell above is *delete from word1*, the cell to the left is *insert into word1*.\n\nThe base cases are the part people skip: `dp[i][0] = i` because turning an i-character string into the empty string costs i deletions, and `dp[0][j] = j` symmetrically.",
  "**O(n · m)** time, **O(n · m)** space — reducible to **O(m)**.",
  "Zero-initialising the table and omitting the two base-case loops produces an answer that is correct on most sample inputs and wrong whenever one string is a prefix of the other. Always write those two loops first."),

P("LC10", 10, "Regular Expression Matching", "HARD", "DP, `*` binds to `p[j-2]`",
  "Implement matching for `.` (any single character) and `*` (zero or more of the **preceding** element), where the match must cover the entire input string.",
  "`*` is never standalone — it always binds to the character before it, so `p[j-1] == '*'` must be read together with `p[j-2]`.\n\nTwo cases. Zero occurrences: skip both pattern characters, `dp[i][j] = dp[i][j-2]`. One more occurrence: only if `p[j-2]` matches `s[i-1]`, in which case `dp[i-1][j]` — consume a text character and keep the `*` available.\n\nThe base row matters: patterns like `\"a*b*c*\"` match the empty string, which is what the `j` loop starting at 2 sets up.",
  "**O(n · m)** time, **O(n · m)** space.",
  "The zero-occurrence case skips **two** pattern characters, not one. `dp[i][j-1]` is the wildcard rule from LC 44 and is wrong here — the two problems look nearly identical and this is the line that differs."),

P("LC44", 44, "Wildcard Matching", "HARD", "DP, `*` standalone",
  "Implement matching for `?` (exactly one character) and `*` (any sequence, including empty), covering the entire input string.",
  "Here `*` is independent of what precedes it, which makes the recurrence simpler than LC 10's. Two options joined by an OR: `dp[i-1][j]` — the `*` swallows `s[i-1]` and remains available — or `dp[i][j-1]` — the `*` matches nothing and we move past it.\n\nThe base row is the run of leading `*`s: `dp[0][j]` is true only while every pattern character so far has been a `*`.\n\nThere is also a well-known greedy two-pointer solution in O(1) space that backtracks to the last `*`. It is faster but much harder to defend under pressure; write the DP and mention the greedy.",
  "**O(n · m)** time, **O(n · m)** space.",
  "Stating the difference from LC 10 crisply is half the interview: in LC 44, `*` is standalone and consumes text via `dp[i-1][j]`; in LC 10, `*` is glued to `p[j-2]` and zero-occurrences skips two via `dp[i][j-2]`."),

P("LC97", 97, "Interleaving String", "MEDIUM", "DP, index `c[i+j-1]`",
  "Return true if `s3` is formed by interleaving `s1` and `s2`, preserving the relative order within each.",
  "`dp[i][j]` asks whether the first `i` characters of `s1` and the first `j` of `s2` can interleave to form the first `i + j` of `s3`. The cell is reachable if either the previous cell up supplies `s1[i-1]` or the previous cell left supplies `s2[j-1]`, matching `s3[i+j-1]`.\n\nThat index is the whole problem: having consumed `i + j` characters, the one being placed is number `i + j` of `s3`, which lives at index `i + j - 1`.\n\nGreedy fails, and the reason is worth stating: when `s1[i-1]` and `s2[j-1]` are both equal to the next character of `s3`, there is no local information that says which to take.",
  "**O(n · m)** time, **O(n · m)** space — reducible to **O(m)**.",
  "The length guard `n + m == s3.size()` must come first. Without it the table is filled against a string of the wrong length and the index `i + j - 1` reads out of bounds."),
]

meta = {
  "title": "Strings",
  "subtitle": "All 38 problems from Part 14 of the Strings guide, worked in full — the problem, the approach, the complexity, the tested C++ solution, and the mistake that most often breaks it.",
  "kicker": "Data Structures & Algorithms · C++",
  "source_cpp": "reference-part14-solutions.cpp",
  "footer": "Prepared for <b>Hari</b> &middot; on-campus placement preparation<br>"
            "Every solution below is extracted verbatim from a file that compiles clean and passes 216 tests",
  "stats": [["38", "Problems"], ["14", "Patterns"], ["216", "Tests passing"], ["3", "Tiers"]],
  "tiers": [
    {"name": "Tier 1 · Fundamentals",
     "blurb": "Characters, counting and the basic two-pointer shapes. Do all thirteen of these "
              "before touching Tier 2 — everything later assumes this is automatic.",
     "problems": tier1},
    {"name": "Tier 2 · The core patterns",
     "blurb": "The tier that actually gets asked. LC 3, LC 5, LC 49, LC 76 and LC 438 are the five "
              "most-seen string questions in on-campus drives; be able to write all five from a blank page.",
     "problems": tier2},
    {"name": "Tier 3 · Advanced",
     "blurb": "KMP, hashing and the two-string DP grid. These are what separate a good on-campus "
              "result from a great one — and the prefix function repays memorising outright.",
     "problems": tier3},
  ],
}

json.dump(meta, open("strings-solved.meta.json", "w", encoding="utf-8"),
          indent=1, ensure_ascii=False)
n = sum(len(t["problems"]) for t in meta["tiers"])
print("wrote strings-solved.meta.json with", n, "problems")
