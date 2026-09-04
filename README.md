# Claude DSA — Placement Preparation Workspace

**Owner:** Hari
**Language:** C++
**Goal:** On-campus placement preparation for MNCs
**Linked Claude project:** Leetcode

This folder is the permanent home for every study document, practice file, and
reference solution produced in the Leetcode project. Everything is filed by DSA
topic so material is easy to find months later.

---

## How this folder is organized

```
Claude DSA/
├── README.md                  <- you are here (master index)
├── 00_Foundations/            <- C++ basics, pointers, complexity, STL
├── 01_Arrays/
├── 02_Strings/
├── 03_Linked_Lists/           <- IN PROGRESS
├── 04_Stacks_and_Queues/
├── 05_Recursion_and_Backtracking/
├── 06_Trees_and_BST/
├── 07_Heaps_and_Priority_Queues/
├── 08_Hashing/
├── 09_Searching_and_Sorting/
├── 10_Greedy/
├── 11_Dynamic_Programming/
├── 12_Graphs/
├── 13_Bit_Manipulation/
├── 14_Tries/
├── 15_Design_and_LLD/
├── _Progress/                 <- problem log, weekly plan, revision tracker
└── _Templates/                <- reusable C++ scaffolding
```

Every topic folder has the same three subfolders:

| Subfolder | What goes in it |
|---|---|
| `notes/` | Concept guides — the theory, the patterns, the explanations |
| `practice/` | Skeleton `.cpp` files with TODOs and built-in tests you fill in yourself |
| `solutions/` | Verified reference implementations — every one compiles and passes its tests |

---

## Topic index

| # | Topic | Status | Notes | Practice | Solutions |
|---|---|---|---|---|---|
| 00 | [Foundations](00_Foundations/) | Not started | – | – | – |
| 01 | [Arrays](01_Arrays/) | Not started | – | – | – |
| 02 | [Strings](02_Strings/) | Not started | – | – | – |
| 03 | [Linked Lists](03_Linked_Lists/) | **In progress** | 1 | 1 | 1 |
| 04 | [Stacks & Queues](04_Stacks_and_Queues/) | Not started | – | – | – |
| 05 | [Recursion & Backtracking](05_Recursion_and_Backtracking/) | Not started | – | – | – |
| 06 | [Trees & BST](06_Trees_and_BST/) | Not started | – | – | – |
| 07 | [Heaps & Priority Queues](07_Heaps_and_Priority_Queues/) | Not started | – | – | – |
| 08 | [Hashing](08_Hashing/) | Not started | – | – | – |
| 09 | [Searching & Sorting](09_Searching_and_Sorting/) | Not started | – | – | – |
| 10 | [Greedy](10_Greedy/) | Not started | – | – | – |
| 11 | [Dynamic Programming](11_Dynamic_Programming/) | Not started | – | – | – |
| 12 | [Graphs](12_Graphs/) | Not started | – | – | – |
| 13 | [Bit Manipulation](13_Bit_Manipulation/) | Not started | – | – | – |
| 14 | [Tries](14_Tries/) | Not started | – | – | – |
| 15 | [Design & LLD](15_Design_and_LLD/) | Not started | – | – | – |

---

## File naming convention

| Kind | Pattern | Example |
|---|---|---|
| Concept guide | `<topic>-guide.md` | `linked-lists-cpp-guide.md` |
| Practice scaffold | `practice-<NN>-<subject>.cpp` | `practice-01-basics.cpp` |
| Reference solutions | `reference-<subject>.cpp` | `reference-all-patterns.cpp` |
| Single problem solution | `LC<number>-<slug>.cpp` | `LC206-reverse-linked-list.cpp` |

---

## How to compile and run anything here

```bash
g++ -std=c++17 -O2 -Wall -o out file.cpp && ./out
```

Practice files are self-checking — they print `ok` / `FAIL` per test case, so
you know immediately whether your implementation is correct.

---

## Standing instruction for Claude

Every document produced in the **Leetcode** Claude project is filed here
automatically, in the matching topic folder, following the conventions above.
The topic index in this README and the topic folder's own README are updated
at the same time. Nothing is left only in a chat.
