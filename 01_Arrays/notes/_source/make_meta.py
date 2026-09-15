#!/usr/bin/env python3
"""Generate arrays-solved.meta.json for build_solved_pdf.py."""
import json, os

T = lambda *a: a  # readability helper: (id, num, title, difficulty, pattern, tier,
                  #                      problem, approach, complexity, trap)

PATTERNS = {'LC1': 'Pattern 12 — Hashing / complement lookup', 'LC26': 'Pattern 3 — Two pointers, write index', 'LC27': 'Pattern 3 — Two pointers, write index', 'LC283': 'Pattern 3 — Two pointers, write index', 'LC88': 'Pattern 2 — Two pointers, filling from the back', 'LC121': 'Pattern 1 — Linear scan with state', 'LC53': 'Pattern 1 — Kadane', 'LC217': 'Pattern 12 — Hashing / membership', 'LC169': 'Pattern 1 — Boyer–Moore vote', 'LC268': 'Pattern 13 — XOR parity', 'LC136': 'Pattern 13 — XOR parity', 'LC66': 'Pattern 1 — Linear scan with carry', 'LC448': 'Pattern 13 — In-place marking', 'LC167': 'Pattern 2 — Two pointers, opposite ends', 'LC15': 'Pattern 2 — Sort + two pointers', 'LC11': 'Pattern 2 — Two pointers, greedy move', 'LC42': 'Pattern 2 — Two pointers + running max', 'LC75': 'Pattern 4 — Dutch national flag', 'LC209': 'Pattern 6 — Variable window, shortest', 'LC3': 'Pattern 6 — Variable window, longest', 'LC424': 'Pattern 6 — Variable window + frequency', 'LC560': 'Pattern 8 — Prefix sum + hash map', 'LC238': 'Pattern 7 — Prefix/suffix sweep', 'LC152': 'Pattern 1 — Kadane with min and max', 'LC56': 'Pattern 9 — Interval sweep', 'LC33': 'Pattern 10 — Binary search, rotated', 'LC153': 'Pattern 10 — Binary search, rotated', 'LC34': 'Pattern 10 — Binary search, boundaries', 'LC41': 'Pattern 13 — Cyclic sort', 'LC287': 'Pattern 13 — Floyd cycle on an array', 'LC128': 'Pattern 12 — Hashing / set walk', 'LC73': 'Pattern 14 — Matrix, in-place markers', 'LC48': 'Pattern 14 — Matrix, transpose + reverse', 'LC54': 'Pattern 14 — Matrix, shrinking boundaries', 'LC189': 'Pattern 3 — In-place rearrangement', 'LC239': 'Pattern 6 — Monotonic deque window', 'LC4': 'Pattern 11 — Binary search on a partition', 'LC31': 'Pattern 3 — In-place index scan'}

P = [
# ------------------------------- TIER 1 -------------------------------------
T("LC1", "LC 1", "Two Sum", "Easy", "Hash map", 1,
  "Given an array and a `target`, return the indices of the two numbers that add up to `target`. Exactly one answer exists.",
  "Brute force checks all pairs in O(n²). Instead, walk once and ask *what would complete this element*: for `nums[i]` the partner is `target - nums[i]`. Keep every value seen so far in a hash map from value to index, so the question is answered in O(1).",
  "O(n) time · O(n) space",
  "Look up **before** you insert the current element, otherwise an element pairs with itself when `target` is exactly `2 * nums[i]`. Do not sort — sorting destroys the indices you were asked to return."),

T("LC26", "LC 26", "Remove Duplicates from Sorted Array", "Easy", "Write index", 1,
  "The array is sorted. Remove duplicates in place so each value appears once, and return the new length `k`. The first `k` slots must hold the answer.",
  "Write index: `w` is the next output slot, so `v[0..w-1]` is the finished answer. Since the array is sorted, duplicates are adjacent, so a new element is worth keeping exactly when it differs from the last one **kept**.",
  "O(n) time · O(1) space",
  "Compare `v[r]` with `v[w-1]` — the last *accepted* value — not with `v[r-1]`. Seed `w = 1` and guard the empty array, since `v[w-1]` would read `v[-1]`."),

T("LC27", "LC 27", "Remove Element", "Easy", "Write index", 1,
  "Remove every occurrence of `val` in place and return the new length. The order of the remaining elements does not matter.",
  "The same write-index skeleton with a different keep-test. Everything that is not `val` is copied forward to `v[w]` and `w` advances; everything else is simply skipped.",
  "O(n) time · O(1) space",
  "`w` is both the next write slot and the final length — that is not a coincidence, it is the loop invariant `v[0..w-1]` is finished. Do not try to `erase()` inside the loop; that is O(n) per call and invalidates iterators."),

T("LC283", "LC 283", "Move Zeroes", "Easy", "Write index", 1,
  "Move all zeroes to the end while keeping the relative order of the non-zero elements. In place.",
  "Two passes over the same array: compact all non-zeroes to the front with a write index, then fill the tail from `w` to `n-1` with zeroes. A one-pass variant swaps `v[w++]` with `v[r]` instead.",
  "O(n) time · O(1) space",
  "The order of the non-zeroes must be **preserved**, so you cannot swap from the end. The swap version works because `w <= r` always, so you never overwrite an unread element."),

T("LC88", "LC 88", "Merge Sorted Array", "Easy", "Two pointers from the back", 1,
  "`a` has length `m + n` with its first `m` slots used; `b` has `n` elements. Merge `b` into `a` in place, keeping it sorted.",
  "Merging front to back would overwrite unread elements of `a`. Fill from the **back** instead: compare the two largest remaining values and write the bigger one into `a[w]`, moving `w` leftwards. The free space is always exactly where you are writing.",
  "O(m + n) time · O(1) space",
  "Loop `while (j >= 0)`, not until both run out: if `a` empties first the remainder of `b` must still be copied, but if `b` empties first the rest of `a` is already in place. The `i >= 0 &&` guard must come first in the comparison."),

T("LC121", "LC 121", "Best Time to Buy and Sell Stock", "Easy", "Scan with state", 1,
  "One buy and one sell, and the buy must come first. Maximise the profit, or return 0.",
  "For each day, the best possible sale today is *today's price minus the cheapest price seen so far*. Carry the running minimum and the running best profit in two variables.",
  "O(n) time · O(1) space",
  "Update the minimum *before* computing today's profit and the same-day trade contributes 0, which is harmless. Initialise `best = 0`, not `INT_MIN` — a falling market must return 0, not a negative profit. This is Kadane over the day-to-day differences, and saying so is a good interview remark."),

T("LC53", "LC 53", "Maximum Subarray", "Medium", "Kadane", 1,
  "Find the contiguous subarray with the largest sum and return that sum.",
  "Kadane. At each index the best subarray ending here either extends the previous one or starts fresh at this element: `cur = max(v[i], cur + v[i])`. Track the best `cur` ever seen.",
  "O(n) time · O(1) space",
  "**Initialise `best` and `cur` from `v[0]`, never from 0.** With 0 an all-negative array wrongly returns 0; the hidden test is `[-3,-1,-2]`, whose answer is `-1`. To report the indices too, record `start` whenever `cur` restarts."),

T("LC217", "LC 217", "Contains Duplicate", "Easy", "Hash set", 1,
  "Return true if any value appears at least twice.",
  "Insert each value into an `unordered_set`; `insert` returns a pair whose `.second` is false when the value was already present, so one pass and one lookup per element suffices.",
  "O(n) time · O(n) space",
  "Sorting and scanning adjacent pairs also works but is O(n log n) — know both and be able to state the trade: the hash set buys time with memory. Reading `mp[x]` on a map would *insert* a zero; the set's `insert` return value avoids two lookups."),

T("LC169", "LC 169", "Majority Element", "Easy", "Boyer–Moore", 1,
  "One element appears more than `n/2` times. Find it in O(1) space.",
  "Boyer–Moore voting: hold a candidate and a counter. A matching element increments, a different one decrements, and a counter of zero adopts the next element as the new candidate. The true majority cannot be fully cancelled because it outnumbers everything else combined.",
  "O(n) time · O(1) space",
  "The algorithm is only valid **because a majority is guaranteed**. If the problem does not promise one, add a second pass to count the candidate and verify it exceeds `n/2`. The `n/3` variant needs two candidates and always needs that verification pass."),

T("LC268", "LC 268", "Missing Number", "Easy", "XOR", 1,
  "The array holds `n` distinct numbers from the range `0..n`. Return the one that is missing.",
  "XOR every index `0..n-1` and every value together, seeded with `n`. Each number that *is* present appears once as a value and once as an index and cancels itself, so only the missing one survives.",
  "O(n) time · O(1) space",
  "The sum formula `n*(n+1)/2 - sum` is easier to explain but **overflows** for large `n`; XOR never can. Offering both, and naming the overflow difference, is exactly the comparison interviewers are listening for."),

T("LC136", "LC 136", "Single Number", "Easy", "XOR", 1,
  "Every element appears twice except one. Find it, in O(1) space.",
  "XOR the whole array. Because `x ^ x == 0` and `x ^ 0 == x`, and XOR is commutative and associative, every pair annihilates regardless of position and the loner is what remains.",
  "O(n) time · O(1) space",
  "A hash map works but costs O(n) space, which the problem forbids. For the variant where two numbers appear once (LC 260), XOR everything to get `a^b`, isolate the lowest set bit with `x & -x`, and split the array on that bit."),

T("LC66", "LC 66", "Plus One", "Easy", "Digit carry", 1,
  "A non-negative integer is stored as an array of digits, most significant first. Add one and return the digit array.",
  "Walk from the last digit backwards. Anything below 9 can absorb the increment and you return immediately; a 9 becomes 0 and the carry continues left. If the loop finishes, every digit was a 9, so prepend a 1.",
  "O(n) time · O(1) extra space (O(n) only in the all-nines case)",
  "The all-nines case is the whole problem: `999` must become `1000`, which is *longer* than the input. Do not convert to `int` or `long long` — the array can hold hundreds of digits, which is precisely why the problem is phrased this way."),

T("LC448", "LC 448", "Find All Numbers Disappeared in an Array", "Easy", "In-place marking", 1,
  "An array of length `n` holds values in `1..n`, some appearing twice. Return every value in `1..n` that does not appear, in O(1) extra space.",
  "Use the sign bit as a 'seen' flag. For each element, negate the value sitting at index `|v[i]| - 1`. After one pass every slot still holding a positive number corresponds to a value that was never visited.",
  "O(n) time · O(1) extra space (the output does not count)",
  "**`abs(v[i])` is mandatory** — by the time you reach index `i`, `v[i]` may itself already have been flipped negative, and a negative index is undefined behaviour. Swapping the final test to `v[i] < 0` solves LC 442 (find all duplicates) with the same code."),

# ------------------------------- TIER 2 -------------------------------------
T("LC167", "LC 167", "Two Sum II — Input Array Is Sorted", "Medium", "Two pointers, opposite ends", 2,
  "The array is sorted ascending. Return the **1-indexed** positions of the two values summing to `target`.",
  "Start at both ends. If the sum is too small only the left pointer can help, because `v[r]` is already the largest available partner for `v[l]`; if it is too large, only the right pointer can. Each step discards exactly one candidate and never discards a solution.",
  "O(n) time · O(1) space",
  "This problem is **1-indexed** — return `{l+1, r+1}`. Use `while (l < r)`, not `<=`, since the two elements must be distinct. Being able to state *why* discarding an end is safe is the actual interview question."),

T("LC15", "LC 15", "3Sum", "Medium", "Sort + two pointers", 2,
  "Return all unique triplets summing to zero. No duplicate triplets in the output.",
  "Sort, then fix the first element `v[i]` and run the opposite-ends two-pointer scan over the rest looking for `-v[i]`. Sorting is what makes both the two-pointer move and the duplicate-skipping possible.",
  "O(n²) time · O(1) extra space beyond the output",
  "There are **three** de-duplication points, and each compares against the element just left behind: `v[i] == v[i-1]` for the first, and `v[l] == v[l-1]` / `v[r] == v[r+1]` after recording a hit. Sum into a `long long`; three `int`s near the limits can overflow. `if (v[i] > 0) break;` is a free early exit on sorted input."),

T("LC11", "LC 11", "Container With Most Water", "Medium", "Two pointers, greedy move", 2,
  "Each element is a vertical wall height. Choose two walls so the water they hold — `min(height) * distance` — is maximised.",
  "Start at the widest pair and always move the **shorter** wall inward. Moving the taller one cannot help: the width strictly shrinks while the height stays capped by the shorter wall, so no better area can appear.",
  "O(n) time · O(1) space",
  "The greedy exchange argument above is the whole answer — an interviewer will ask you to justify discarding the shorter wall. When the two heights are equal, either move is safe. Note that this problem ignores the walls in between, unlike Trapping Rain Water."),

T("LC42", "LC 42", "Trapping Rain Water", "Hard", "Two pointers + running max", 2,
  "Given an elevation map, compute how much rain water is trapped between the bars.",
  "Water above bar `i` is `min(maxLeft, maxRight) - h[i]`. Two pointers let you compute that without precomputing both arrays: whichever side is currently shorter is the limiting one, so its running max is already final and you can settle that column and step inward.",
  "O(n) time · O(1) space",
  "Add `lmax - h[l]` *after* updating `lmax`, so the contribution is never negative. The prefix/suffix-array version (O(n) space) and the monotonic-stack version are both acceptable — know at least two and say which you are writing and why."),

T("LC75", "LC 75", "Sort Colors", "Medium", "Dutch national flag", 2,
  "Sort an array of 0s, 1s and 2s in one pass, in place, without a library sort.",
  "Three pointers maintaining four regions: `[0,low)` all 0s, `[low,mid)` all 1s, `[mid,high]` unknown, `(high,n)` all 2s. A 0 swaps to `low` and both advance, a 1 just advances `mid`, a 2 swaps to `high` and `high` shrinks.",
  "O(n) time · one pass, O(1) space",
  "**`mid` must not advance after swapping with `high`** — the value that came back is from the unexamined region and has to be inspected next iteration. After swapping with `low` the incoming value is a known 1, so advancing is safe. Loop `while (mid <= high)`, inclusive, since `high` is still unknown."),

T("LC209", "LC 209", "Minimum Size Subarray Sum", "Medium", "Shortest variable window", 2,
  "All values are positive. Find the length of the shortest contiguous subarray whose sum is at least `target`, or 0 if none exists.",
  "Variable window, minimising flavour: grow on the right, and **while the window is valid**, record the length and then shrink from the left to hunt for something shorter.",
  "O(n) time · O(1) space — each index enters and leaves the window once",
  "For a *shortest* answer the recording happens **inside** the shrink loop; for a *longest* answer it happens after it. Return 0, not `INT_MAX`, when nothing qualifies. The window is only valid here because the values are positive — with negatives this needs prefix sums."),

T("LC3", "LC 3", "Longest Substring Without Repeating Characters", "Medium", "Longest variable window", 2,
  "Find the length of the longest substring containing no repeated character.",
  "Variable window with a 128-entry frequency table. After adding `s[r]`, the only character that can possibly have a count above 1 is `s[r]` itself, so shrink from the left until its count drops back to 1, then record `r - l + 1`.",
  "O(n) time · O(1) space (the table is a fixed 128 entries)",
  "Testing only `cnt[s[r]] > 1` rather than rescanning the table is what keeps this O(n). Cast to `unsigned char` before indexing: plain `char` is signed, so a byte above 127 would index negatively."),

T("LC424", "LC 424", "Longest Repeating Character Replacement", "Medium", "Window + frequency", 2,
  "You may change at most `k` characters. Find the longest substring that can be made of a single repeated letter.",
  "A window is valid when `(length) - (count of its most frequent letter) <= k`, since that difference is exactly how many characters you would have to replace. Grow on the right, shrink while invalid.",
  "O(n) time · O(1) space (26 counters)",
  "`maxCount` is kept as a running maximum and never decreased. That looks wrong but is not: a stale, too-large `maxCount` can only keep the window from shrinking, and a window shorter than the best already found can never improve the answer. If that argument feels shaky, recompute the max over 26 entries — still fast, and obviously correct."),

T("LC560", "LC 560", "Subarray Sum Equals K", "Medium", "Prefix + hash map", 2,
  "Count the contiguous subarrays whose sum is exactly `k`. Values may be **negative**.",
  "`sum(i..j) == k` is the same as `P[j+1] - P[i] == k`, i.e. `P[i] == P[j+1] - k`. Scan once keeping a map from each prefix value to how many times it has occurred; at each step add the count of `pre - k`.",
  "O(n) time · O(n) space",
  "**Seed the map with `seen[0] = 1`** — the empty prefix — or every subarray starting at index 0 is missed; test with `v = [3], k = 3`. Look up before inserting. A sliding window is *wrong* here because negatives break the monotonicity that justifies shrinking."),

T("LC238", "LC 238", "Product of Array Except Self", "Medium", "Prefix/suffix sweep", 2,
  "Return an array where `res[i]` is the product of every element except `v[i]`. No division, O(1) extra space beyond the output.",
  "Two sweeps. The forward pass leaves 'product of everything to my left' in `res`. The backward pass multiplies in 'product of everything to my right', carried in a single running variable.",
  "O(n) time · O(1) extra space (the output array is not counted)",
  "Division is banned precisely because of zeros — one zero makes the quotient undefined and two zeros make every answer zero. The left-then-right double sweep is a pattern in its own right; the same shape solves Trapping Rain Water and Candy."),

T("LC152", "LC 152", "Maximum Product Subarray", "Medium", "Kadane with min and max", 2,
  "Find the contiguous subarray with the largest **product**.",
  "Kadane's structure, but a large negative times a negative becomes a large positive — so carry both the running maximum and the running minimum ending here, and swap their roles whenever the current element is negative.",
  "O(n) time · O(1) space",
  "Swap **before** the two updates, not after. Zeros need no special case: both running values collapse to 0 and the next element restarts the run. Initialise all three variables from `v[0]`, as in LC 53."),

T("LC56", "LC 56", "Merge Intervals", "Medium", "Sort + sweep", 2,
  "Merge all overlapping intervals and return the non-overlapping set covering the same span.",
  "Sort by start. Sweep left to right: if the current interval starts at or before the end of the last kept one, extend that one; otherwise push the current interval as a new block.",
  "O(n log n) time (dominated by the sort), O(1) extra space beyond the output",
  "Extend with `max(res.back()[1], cur[1])`, never plain assignment — `[1,10]` followed by `[2,3]` must stay `[1,10]`. Use `<=` so touching intervals like `[1,4]` and `[4,5]` merge, unless the statement says otherwise. For 'keep the most non-overlapping intervals', sort by **end** instead."),

T("LC33", "LC 33", "Search in Rotated Sorted Array", "Medium", "Binary search", 2,
  "A sorted array of distinct values was rotated at an unknown pivot. Find `target` in O(log n), or return −1.",
  "At every split at least one half is still properly sorted. Detect which by comparing `v[lo]` with `v[mid]`, then test whether the target lies inside that sorted half's range: if it does, search there; otherwise search the other half.",
  "O(log n) time · O(1) space",
  "`v[lo] <= v[mid]` needs the `<=`: when only two elements remain, `mid == lo` and the one-element left half is trivially sorted. With duplicates (LC 81) the test can be uninformative — `[3,3,3,1,3]` — and the fix, `hi--`, degrades the worst case to O(n). Say that out loud when asked."),

T("LC153", "LC 153", "Find Minimum in Rotated Sorted Array", "Medium", "Binary search", 2,
  "Return the smallest element of a rotated sorted array of distinct values, in O(log n).",
  "There is no target, so compare against the right end. If `v[mid] > v[hi]` the rotation point — and therefore the minimum — is strictly to the right; otherwise `mid` is itself a candidate and the search continues left with `hi = mid`.",
  "O(log n) time · O(1) space",
  "**Compare with `v[hi]`, never with `v[lo]`.** Comparing against the left end fails on an unrotated array like `[1,2,3]`. This is the `while (lo < hi)` template, so `hi = mid` (not `mid-1`) and the answer is `v[lo]` after the loop."),

T("LC34", "LC 34", "Find First and Last Position of Element", "Medium", "lower/upper bound", 2,
  "Return the first and last index of `target` in a sorted array, or `{-1,-1}`.",
  "Two boundary searches with one helper. `lower(x)` is the first index with `v[i] >= x`; the first occurrence is `lower(target)` and the last is `lower(target + 1) - 1`, since the first index greater than `target` is one past the final occurrence.",
  "O(log n) time · O(1) space",
  "The helper's `hi` starts at `n`, not `n-1`, because 'not present, belongs at the end' is a legitimate answer. Check both `lo == n` and `v[lo] != target` before trusting the result. `lower(target+1)` is `upper_bound` without writing a second function."),

# ------------------------------- TIER 3 -------------------------------------
T("LC41", "LC 41", "First Missing Positive", "Hard", "Cyclic sort", 3,
  "Find the smallest missing **positive** integer, in O(n) time and O(1) space",
  "The answer must lie in `1..n+1`, so only values in `1..n` matter and each has a natural home: value `x` belongs at index `x-1`. Keep swapping elements into their homes, then scan for the first index whose value is wrong — that index plus one is the answer.",
  "O(n) time · O(1) space",
  "The nested `while` is **not** O(n²): every successful swap places one value permanently, so there are at most `n` swaps overall — have that argument ready, it is always the follow-up. The loop test must be `v[v[i]-1] != v[i]`, comparing values; writing `v[i] != i+1` instead loops forever on duplicates."),

T("LC287", "LC 287", "Find the Duplicate Number", "Medium", "Floyd cycle on an array", 3,
  "An array of `n+1` values in `1..n` has exactly one repeated value. Find it without modifying the array and in O(1) space.",
  "Read `v[i]` as 'the next index' and the array becomes a linked list. Two arrows landing on the same node means a cycle, and its entrance is the duplicate. Floyd: advance slow by one and fast by two until they meet, then restart one at index 0 and step both by one — they meet at the entrance.",
  "O(n) time · O(1) space, input untouched",
  "The two constraints together — read-only *and* O(1) space — are what rule out sorting, a hash set, and negation marking. Phase 2 must restart from `v[0]` and move **both** pointers one step at a time; that is the part people misremember."),

T("LC128", "LC 128", "Longest Consecutive Sequence", "Medium", "Hash set", 3,
  "Find the length of the longest run of consecutive integers in an unsorted array. O(n) required.",
  "Put everything in a hash set. For each value, only start counting if `x-1` is absent — that makes `x` the start of its run — then walk `x+1, x+2, …` upward while the set contains them.",
  "O(n) time · O(n) space",
  "The `if (s.count(x-1)) continue;` guard is what keeps this linear: the inner walk only ever runs from a run's smallest element, so across the whole loop each element is visited at most once. Without it the same run is re-walked from every member and you are back to O(n²). Sorting solves it too, but at O(n log n), which the problem forbids."),

T("LC73", "LC 73", "Set Matrix Zeroes", "Medium", "Markers in row 0 / column 0", 3,
  "If a cell is 0, set its entire row and column to 0 — in place, using O(1) extra space.",
  "Zeroing as you go is wrong because written zeroes are indistinguishable from original ones. Use the first row and first column as the marker buffers, plus one boolean for the first column itself (since `g[0][0]` would otherwise have to record two different facts).",
  "O(m·n) time · O(1) space",
  "The second pass must run **backwards**, bottom-right to top-left, so the markers are consumed last. Going forwards destroys the marker row before you have finished reading it. The O(m+n) version with two `vector<bool>`s is much easier — write that first, then optimise if asked."),

T("LC48", "LC 48", "Rotate Image", "Medium", "Transpose + reverse", 3,
  "Rotate an `n × n` matrix by 90° clockwise, in place.",
  "Transpose (reflect across the main diagonal), then reverse each row. Transposing turns rows into columns and the row reversal puts them in the right order, which together is exactly a clockwise quarter turn.",
  "O(n²) time · O(1) space",
  "**`j` must start at `i + 1`.** Starting at 0 swaps every pair twice and leaves the matrix unchanged — the classic silent failure here. For anticlockwise, transpose and then reverse the *order of the rows* instead."),

T("LC54", "LC 54", "Spiral Matrix", "Medium", "Four shrinking boundaries", 3,
  "Return all elements of an `m × n` matrix in spiral order.",
  "Hold four boundaries — `top`, `bot`, `left`, `right` — and peel one ring per iteration: left-to-right along the top, top-to-bottom down the right, right-to-left along the bottom, bottom-to-top up the left, shrinking the relevant boundary after each leg.",
  "O(m·n) time · O(1) extra space beyond the output",
  "**The two `if` guards before the bottom and left legs are the whole difficulty.** Without them a single remaining row or column is traversed twice and you emit duplicates. Test on `[[1,2,3]]` and `[[1],[2],[3]]` — those two inputs catch every buggy version of this."),

T("LC189", "LC 189", "Rotate Array", "Medium", "Three reversals", 3,
  "Rotate the array right by `k` steps, in place with O(1) extra space.",
  "Reverse the whole array, then reverse the first `k` elements, then reverse the remaining `n - k`. The full reversal puts the last `k` elements at the front but backwards, and the two partial reversals repair the order of each block.",
  "O(n) time · O(1) space",
  "**`k %= n` first** — `k` is routinely larger than `n` in the tests, and `v.begin() + k` past the end is undefined behaviour. Guard `n == 0` before the modulo, since `% 0` crashes. The same triple reversal rotates a string."),

T("LC239", "LC 239", "Sliding Window Maximum", "Hard", "Monotonic deque", 3,
  "Return the maximum of every window of size `k` as it slides across the array.",
  "Keep a deque of **indices** whose values are strictly decreasing. Before pushing `i`, pop from the back every index whose value is no greater than `v[i]` — those can never be a maximum again while `i` is in the window. Pop from the front when an index falls out of range; the front is then always the answer.",
  "O(n) time · O(k) space — each index is pushed once and popped once",
  "Store **indices, not values**, or you cannot tell when an entry has expired. Do the expiry pop (`dq.front() <= i - k`) before reading the answer, and only start recording once `i >= k - 1`."),

T("LC4", "LC 4", "Median of Two Sorted Arrays", "Hard", "Binary search on a partition", 3,
  "Find the median of two sorted arrays in O(log(m+n)).",
  "Do not merge. Binary search *how many* elements of the combined left half come from the shorter array; that count fixes the number taken from the other. The split is correct when `L1 <= R2 && L2 <= R1`, and the median then comes from the four boundary values.",
  "O(log(min(m, n))) time · O(1) space",
  "Always binary search the **shorter** array, or the derived index can fall outside the other array. Use `INT_MIN`/`INT_MAX` as sentinels when a partition is empty at either end — that is what removes every special case. `half = (m+n+1)/2` with the `+1` makes the odd-length case fall out as `max(L1, L2)`."),

T("LC31", "LC 31", "Next Permutation", "Medium", "Index scan from the right", 3,
  "Rearrange the array into the next lexicographically greater permutation, in place. If none exists, sort it ascending.",
  "Scan from the right for the first index `i` with `v[i] < v[i+1]` — the pivot. Everything after it is non-increasing and therefore already maximal. Swap the pivot with the rightmost value greater than it, then reverse the tail, which turns the largest arrangement of that suffix into the smallest.",
  "O(n) time · O(1) space",
  "The tail reversal is what makes the result the *next* permutation rather than merely a greater one. When no pivot exists (`i < 0`) the whole array is descending, and the unconditional final reverse already produces the ascending answer — so it must sit outside the `if`."),
]

meta = {
    "title": "Arrays",
    "subtitle": ("Every problem from Part 13 of the Arrays guide, in order, with a worked C++ "
                 "solution, the approach behind it, and the mistake that most often breaks it."),
    "kicker": "Data Structures & Algorithms · C++",
    "source_cpp": "../../solutions/reference-part13-solutions.cpp",
    "stats": [["38", "Problems"], ["3", "Tiers"], ["14", "Patterns"], ["129", "Tests passing"]],
    "footer": ("Prepared for <b>Hari</b> &middot; on-campus placement preparation<br>"
               "Companion to <b>Arrays-Guide.pdf</b> &middot; code verified against "
               "<b>reference-part13-solutions.cpp</b><br>"
               "Every solution in this document was compiled with <b>g++ -std=c++17 -O2 -Wall</b> "
               "and passes its test cases."),
    "tiers": [
        {"name": "Tier 1 — Foundations",
         "blurb": ("Thirteen problems that build the index discipline everything else needs: the "
                   "write pointer, the hash map, the running-state scan, XOR, and in-place marking. "
                   "All O(n), nearly all one pass. Do every one of these before moving on."),
         "problems": []},
        {"name": "Tier 2 — The placement core",
         "blurb": ("Fifteen problems, each the home ground of a named pattern: opposite-ends two "
                   "pointers, the Dutch flag, both flavours of sliding window, prefix sums with a "
                   "hash map, the prefix/suffix double sweep, interval sweeping and the three "
                   "binary-search shapes. This is the tier that decides your placement result."),
         "problems": []},
        {"name": "Tier 3 — Harder, but they do appear",
         "blurb": ("Ten problems where the naive answer is easy and the required one is not: O(1) "
                   "space when you wanted a hash set, read-only when you wanted to sort, one pass "
                   "when you wanted two. Cyclic sort, Floyd on an array, in-place matrix markers, "
                   "the monotonic deque, and binary search on a partition."),
         "problems": []},
    ],
}

for r in P:
    meta["tiers"][r[5] - 1]["problems"].append({
        "id": r[0],
        "num": int(r[1].split()[1]),
        "title": r[2],
        "difficulty": r[3].upper(),
        "pattern": PATTERNS[r[0]],
        "problem": r[6],
        "approach": r[7],
        "complexity": r[8],
        "trap": r[9],
    })

out = os.path.join(os.path.dirname(os.path.abspath(__file__)), "arrays-solved.meta.json")
with open(out, "w", encoding="utf-8") as f:
    json.dump(meta, f, indent=1, ensure_ascii=False)
print("wrote", out, "—", sum(len(t["problems"]) for t in meta["tiers"]), "problems")
