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
├── 04_Stacks_and_Queues/       <- MATERIAL READY
├── 05_Recursion_and_Backtracking/
├── 06_Trees_and_BST/           <- MATERIAL READY
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
| 03 | [Linked Lists](03_Linked_Lists/) | **In progress** | 2 PDFs | 1 | 2 |
| 04 | [Stacks & Queues](04_Stacks_and_Queues/) | **Material ready** | 2 PDFs | 1 | 2 |
| 05 | [Recursion & Backtracking](05_Recursion_and_Backtracking/) | Not started | – | – | – |
| 06 | [Trees & BST](06_Trees_and_BST/) | **Material ready** | 2 PDFs | 1 | 2 |
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

> **Notes and solved-questions files are always PDFs.** Markdown is a build
> input only; it lives in `notes/_source/` and is never the deliverable.

| Kind | Pattern | Example |
|---|---|---|
| Concept guide | `<Topic>-Guide.pdf` | `Linked-Lists-Guide.pdf` |
| Solved questions | `<Topic>-Solved-Questions.pdf` | `Linked-Lists-Solved-Questions.pdf` |
| Markdown source | `notes/_source/<topic>-guide.md` | `notes/_source/linked-lists-cpp-guide.md` |
| Practice scaffold | `practice-<NN>-<subject>.cpp` | `practice-01-basics.cpp` |
| Reference solutions | `reference-<subject>.cpp` | `reference-all-patterns.cpp` |
| Single problem solution | `LC<number>-<slug>.cpp` | `LC206-reverse-linked-list.cpp` |

---

## Building a notes PDF

`_Templates/md_to_pdf.py` converts any notes markdown into a styled PDF matching
the house design — cover page, auto table of contents, syntax-highlighted code,
formatted tables, callout boxes, page numbers.

```bash
python3 _Templates/md_to_pdf.py <input.md> <Output.pdf> [--patterns N] [--problems N]
```

Needs `markdown`, `pygments` and `playwright` (with chromium).

## Building a solved-questions PDF

`_Templates/build_solved_pdf.py` builds a `<Topic>-Solved-Questions.pdf` from a
metadata JSON file plus a compiled-and-tested `.cpp`. The printed code is
extracted verbatim from the marked blocks in that `.cpp`, so the book can never
drift from the code that was actually tested.

```bash
python3 _Templates/build_solved_pdf.py <meta.json> <Output.pdf>
```

The metadata file lives in the topic's `notes/_source/` folder; see
`06_Trees_and_BST/notes/_source/trees-and-bst-solved.meta.json` for the shape.
Wrap each solution in the source file with `//>>>BEGIN LC123` … `//<<<END LC123`.

---

## How to compile and run anything here

```bash
g++ -std=c++17 -O2 -Wall -o out file.cpp && ./out
```

Practice files are self-checking — they print `ok` / `FAIL` per test case, so
you know immediately whether your implementation is correct.

---

## Version control

This folder is a git repo pushed to `github.com/mhk-8/DSA`.

`.gitignore` is set up so that **documents are tracked and build output is not**:

| Tracked | Ignored |
|---|---|
| `.md` `.pdf` `.cpp` `.h` `.txt` `.py` `.png` `.svg` | `.o` `.obj` `.exe` `.out` `.dll` and friends |
| every notes / practice / solutions file | extensionless binaries (`out`, `prac`, `ref`) |
| `_Progress/` and `_Templates/` | `build/` `bin/` `.vscode/` `.idea/` |
| | `desktop.ini` `Thumbs.db` `~$*` (OneDrive/Office noise) |
| | `input.txt` `output.txt` (competitive-programming scratch) |

The extensionless-binary rule matters because `g++ -o out file.cpp` produces a
file called `out` with no extension, which no `*.something` pattern can catch.
If you ever need to commit an extensionless file on purpose:

```bash
git add -f <filename>
```

Everyday flow:

```bash
git status              # should show only real changes, never binaries
git add -A
git commit -m "Linked lists: solved questions PDF"
git push
```

---

## Standing instruction for Claude

Every document produced in the **Leetcode** Claude project is filed here
automatically, in the matching topic folder, following the conventions above.
The topic index in this README and the topic folder's own README are updated
at the same time. Nothing is left only in a chat.
