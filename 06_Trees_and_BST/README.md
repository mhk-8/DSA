# Trees & BST

**Status:** Material ready — study not started
**Covers:** Recursion on trees, all four traversals (recursive + iterative), BFS by level, heights & diameters, root-to-leaf paths, LCA, tree construction, the full BST toolkit, serialisation, tree-as-a-graph, tree DP

---

## Files in this folder

| File | What it is |
|---|---|
| `notes/Trees-and-BST-Guide.pdf` | **40-page guide.** Trees from zero, the one recursion mental model, all traversals, the BST in full, the 14 problem patterns, the approach framework, the 12-bug catalogue, the complexity cheat sheet, the curated LeetCode list, a 4-week plan. |
| `notes/Trees-and-BST-Solved-Questions.pdf` | **45-page solved-questions book.** All 38 problems from Part 8 of the guide, in Tier 1 → 2 → 3 order, each with the problem statement, the approach, complexity, the full C++ solution and the mistake that most often breaks it. |
| `practice/practice-01-basics.cpp` | 10 TODOs with self-checking tests. Fill them in without looking at the guide. |
| `solutions/reference-basics.cpp` | Reference answers to the practice file — 29 test cases, all passing |
| `solutions/reference-part8-solutions.cpp` | Source of truth for the solved-questions PDF — all 38 solutions plus a test harness, 80 test cases, all passing |

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
| 1 | Traversal & collection | "return the traversal" | pre / in / post / level order |
| 2 | Aggregate over the tree | depth, size, sum, count | postorder fold |
| 3 | Return one thing, record another | diameter, balanced, max path sum | one postorder pass + a captured variable |
| 4 | Root-to-leaf paths | "path", "leaf", "path sum" | top-down DFS + backtracking |
| 5 | Level-order / BFS | "level", "row", "view", "width" | queue + frozen `q.size()` |
| 6 | Two-tree comparison | same, symmetric, subtree, invert | lockstep recursion on two nodes |
| 7 | Lowest common ancestor | "common ancestor" | the 4-line LCA; value compare in a BST |
| 8 | Construction from traversals | "build the tree from…" | preorder gives the root, inorder splits |
| 9 | BST operations | search / insert / delete / floor / ceil | compare and descend, O(h) |
| 10 | BST + inorder ordering | kth smallest, validate, recover | inorder of a BST is sorted |
| 11 | Serialisation & encoding | "serialize", "duplicate subtrees" | preorder with `#` null markers |
| 12 | Tree as a graph | "distance K", "burn the tree" | parent map + BFS + visited set |
| 13 | In-place restructuring | flatten, connect next pointers | linked-list pointer discipline |
| 14 | Counting / DP on trees | house robber III, unique BSTs | return a tuple of alternatives |

---

## The four rules

1. **Base case is `nullptr`**, and its return value is the identity of whatever you are combining (0 / −1 / `true` / `nullptr` / `INT_MIN`).
2. **Handle this node; trust the children.** Never trace more than one level deep.
3. If the parent needs a **different** number than the answer, **return** the parent's number and **record** the answer.
4. Say the complexity as **O(n) time, O(h) space — O(log n) balanced, O(n) skewed.**

---

## Progress

- [ ] Part 0–1 — trees from zero, the recursion mental model
- [ ] Practice file: TODOs 1–4 (`countNodes`, `sumValues`, `maxDepth`, `countLeaves`)
- [ ] Practice file: TODOs 5–10
- [ ] Part 2 — all four traversals, recursive **and** iterative
- [ ] Part 3 — the BST: search, insert, delete, validate
- [ ] Part 4 — the 14 patterns in depth
- [ ] Tier 1 problems (12) — solutions in the PDF
- [ ] Tier 2 problems (16) — solutions in the PDF
- [ ] Tier 3 problems (10) — solutions in the PDF
- [ ] The GfG-only views: top view, bottom view, boundary traversal

**How to use the PDF:** attempt the problem on LeetCode first, give it a real
try, and only then open the PDF. Reading the solution before struggling with
the problem teaches you nothing. After you solve one, still read the
*Watch out* box — it names the bug you probably almost made.

## Must-know for placements

**LC 236 (LCA of a Binary Tree), LC 98 (Validate BST), LC 105 (Construct from
Preorder & Inorder) and LC 450 (Delete Node in a BST)** are the four most-asked
tree questions in on-campus drives — Amazon, Microsoft, TCS Digital, Infosys,
Accenture, Wipro. Be able to write all four from a blank page.

For Indian **written rounds** specifically, also drill the four views — left,
right, **top**, **bottom** — and boundary traversal. LeetCode never asks for
top and bottom view; GfG and campus papers ask constantly. Both are a BFS
carrying a horizontal distance into a `map<int,int>`: keep the first node seen
at each distance for the top view, the last for the bottom view.
