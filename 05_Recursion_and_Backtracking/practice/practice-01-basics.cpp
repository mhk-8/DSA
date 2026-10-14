// ============================================================================
//  Recursion & Backtracking — Practice 01: the basics
//
//  Fill in the TODOs. Do NOT look at solutions/reference-basics.cpp until you
//  have made a real attempt at each one. The tests are self-checking:
//
//      g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
//  Every test prints "ok" or "FAIL". Against the empty stubs almost everything
//  fails — that is the point. Work down the list until they all pass.
//
//  Suggested order: 1-4 first (plain recursion: base case + one smaller call),
//  then 5-6 (pick / skip), then 7-9 (the backtracking template), then 10.
//
//  Before writing each one, answer the three questions from Part 1 out loud:
//    1. What is the smallest input, and what is its answer?   (base case)
//    2. If a smaller call already worked, how do I use it?    (recursive case)
//    3. Does every call move toward the base case?            (termination)
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  TODO 1 — Sum of the decimal digits of n (n >= 0), recursively. No loops.
//  1234 -> 10      7 -> 7      0 -> 0
//  Hint: n % 10 is the last digit; n / 10 is "the rest of the number".
// ============================================================================
int sumOfDigits(int n) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 2 — x raised to n (n >= 0) in O(log n) multiplications.
//  fastPower(2, 10) -> 1024
//  Hint: x^n = (x^(n/2))^2, times one extra x when n is odd.
//  Make exactly ONE recursive call and store it — calling power(x, n/2)
//  twice turns O(log n) back into O(n).
// ============================================================================
long long fastPower(long long x, int n) {
    // TODO
    return 0;
}

// ============================================================================
//  TODO 3 — Is s[l..r] a palindrome? Recursively, no loops.
//  ("racecar", 0, 6) -> true      ("abca", 0, 3) -> false
//  Hint: compare the outer pair, then trust recursion with the inside.
//  What is the base case when the inside has 0 or 1 characters left?
// ============================================================================
bool isPalindrome(const string& s, int l, int r) {
    // TODO
    return false;
}

// ============================================================================
//  TODO 4 — Tower of Hanoi. Move n discs from rod `from` to rod `to`, using
//  `via`. Append every move as {fromRod, toRod} to `moves`, in order.
//  hanoi(2, 1, 3, 2) -> {1,2} {1,3} {2,3}
//  Hint: three lines. Move n-1 out of the way, move the biggest, move the
//  n-1 back on top. Do not try to trace it — trust it.
// ============================================================================
void hanoi(int n, int from, int to, int via, vector<pair<int,int>>& moves) {
    // TODO
}

// ============================================================================
//  TODO 5 — All subsets of nums (any order).
//  [1,2,3] -> [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]
//  Use the PICK / SKIP form: at index i, either take nums[i] or don't.
//  Write a helper with the signature you want; this one just calls it.
// ============================================================================
vector<vector<int>> subsets(vector<int>& nums) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 6 — How many subsequences of a (all positive) add up to exactly k?
//  [1,2,1], k=2 -> 2   ({2} and {1,1})
//  Same pick / skip tree as TODO 5, but RETURN a count instead of building
//  lists: count(i, sum) = count(pick) + count(skip).
// ============================================================================
int countSubsequencesWithSum(vector<int>& a, int k) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 7 — All permutations of nums (distinct values, any order).
//  [1,2,3] -> 6 permutations
//  Use a `used` array. Choose, explore, UN-choose — undo BOTH the push and
//  the used[i] = true, or later branches see stale state.
// ============================================================================
vector<vector<int>> permutations(vector<int>& nums) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 8 — Combination Sum: every combination of candidates (each may be
//  reused any number of times) that adds up to target. No duplicate lists.
//  [2,3,6,7], 7 -> [2,2,3], [7]
//  Hint: a `start` index stops [2,3,2] appearing alongside [2,2,3].
//  Recurse with i (not i+1) because reuse is allowed. Sort first and
//  `break` as soon as a candidate exceeds what is left.
// ============================================================================
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 9 — Every valid string of n pairs of parentheses.
//  n=3 -> ((()))  (()())  (())()  ()(())  ()()()
//  Two rules decide which branches exist:
//    you may add '(' while open < n;   you may add ')' while close < open.
// ============================================================================
vector<string> generateParenthesis(int n) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 10 — N-Queens: how many ways to place n queens on an n x n board so
//  that no two attack each other?   n=4 -> 2,  n=8 -> 92
//  Place one queen per row. Track used columns and both diagonals:
//     cells on one diagonal share  r + c,
//     cells on the other share     r - c   (add n-1 to keep it >= 0).
// ============================================================================
int totalNQueens(int n) {
    // TODO
    return -1;
}

// ============================================================================
//  TESTS — do not edit below this line
// ============================================================================
static int pass_ = 0, fail_ = 0;
static string show(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += to_string(v[i]); }
    return s + "]";
}
static string show(const vector<vector<int>>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += show(v[i]); }
    return s + "]";
}
static string show(const vector<string>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += "\"" + v[i] + "\""; }
    return s + "]";
}
static string show(const vector<pair<int,int>>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) s += ",";
        s += to_string(v[i].first) + "->" + to_string(v[i].second);
    }
    return s + "]";
}
static void ck(const string& label, const string& got, const string& want) {
    if (got == want) { pass_++; cout << "ok   " << label << "\n"; }
    else { fail_++; cout << "FAIL " << label << "\n     got  " << got << "\n     want " << want << "\n"; }
}
static void ck(const string& l, long long g, long long w) { ck(l, to_string(g), to_string(w)); }
static void ck(const string& l, bool g, bool w) { ck(l, string(g ? "true" : "false"), string(w ? "true" : "false")); }
template <class T> static void ck(const string& l, const T& g, const T& w) { ck(l, show(g), show(w)); }
// answers may come out in any order: sort the inner lists, then the outer one
static vector<vector<int>> canon(vector<vector<int>> v) {
    for (auto& x : v) sort(x.begin(), x.end());
    sort(v.begin(), v.end());
    return v;
}
static vector<string> sorted(vector<string> v) { sort(v.begin(), v.end()); return v; }
static vector<vector<int>> sortedOuter(vector<vector<int>> v) { sort(v.begin(), v.end()); return v; }

int main() {
    cout << "--- TODO 1: sumOfDigits ---\n";
    ck("digits 1234", (long long)sumOfDigits(1234), 10LL);
    ck("digits 7",    (long long)sumOfDigits(7),     7LL);
    ck("digits 0",    (long long)sumOfDigits(0),     0LL);
    ck("digits 9999", (long long)sumOfDigits(9999), 36LL);

    cout << "--- TODO 2: fastPower ---\n";
    ck("2^10",  fastPower(2, 10), 1024LL);
    ck("3^0",   fastPower(3, 0),  1LL);
    ck("5^3",   fastPower(5, 3),  125LL);
    ck("2^62",  fastPower(2, 62), 4611686018427387904LL);
    ck("-2^5",  fastPower(-2, 5), -32LL);

    cout << "--- TODO 3: isPalindrome ---\n";
    ck("pal racecar", isPalindrome("racecar", 0, 6), true);
    ck("pal abba",    isPalindrome("abba", 0, 3),    true);
    ck("pal abca",    isPalindrome("abca", 0, 3),    false);
    ck("pal a",       isPalindrome("a", 0, 0),       true);
    ck("pal empty",   isPalindrome("", 0, -1),       true);

    cout << "--- TODO 4: hanoi ---\n";
    { vector<pair<int,int>> m; hanoi(1, 1, 3, 2, m);
      ck("hanoi 1", m, vector<pair<int,int>>{{1,3}}); }
    { vector<pair<int,int>> m; hanoi(2, 1, 3, 2, m);
      ck("hanoi 2", m, vector<pair<int,int>>{{1,2},{1,3},{2,3}}); }
    { vector<pair<int,int>> m; hanoi(3, 1, 3, 2, m);
      ck("hanoi 3", m, vector<pair<int,int>>{{1,3},{1,2},{3,2},{1,3},{2,1},{2,3},{1,3}}); }
    { vector<pair<int,int>> m; hanoi(10, 1, 3, 2, m);
      ck("hanoi 10 count", (long long)m.size(), 1023LL); }

    cout << "--- TODO 5: subsets ---\n";
    { vector<int> a{1,2,3};
      ck("subsets 123", canon(subsets(a)), canon({{},{1},{2},{3},{1,2},{1,3},{2,3},{1,2,3}})); }
    { vector<int> a{};
      ck("subsets empty", canon(subsets(a)), canon({{}})); }

    cout << "--- TODO 6: countSubsequencesWithSum ---\n";
    { vector<int> a{1,2,1};     ck("subseq sum 2", (long long)countSubsequencesWithSum(a, 2), 2LL); }
    { vector<int> a{1,2,3,4,5}; ck("subseq sum 5", (long long)countSubsequencesWithSum(a, 5), 3LL); }
    { vector<int> a{3};         ck("subseq none",  (long long)countSubsequencesWithSum(a, 1), 0LL); }

    cout << "--- TODO 7: permutations ---\n";
    { vector<int> a{1,2,3};
      ck("perms 123", sortedOuter(permutations(a)),
         vector<vector<int>>{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}); }
    { vector<int> a{7};
      ck("perms 7", permutations(a), vector<vector<int>>{{7}}); }

    cout << "--- TODO 8: combinationSum ---\n";
    { vector<int> c{2,3,6,7};
      ck("combsum 7", canon(combinationSum(c, 7)), canon({{2,2,3},{7}})); }
    { vector<int> c{2,3,5};
      ck("combsum 8", canon(combinationSum(c, 8)), canon({{2,2,2,2},{2,3,3},{3,5}})); }
    { vector<int> c{2};
      ck("combsum none", canon(combinationSum(c, 1)), canon({})); }

    cout << "--- TODO 9: generateParenthesis ---\n";
    ck("parens 1", sorted(generateParenthesis(1)), vector<string>{"()"});
    ck("parens 3", sorted(generateParenthesis(3)),
       vector<string>{"((()))","(()())","(())()","()(())","()()()"});
    ck("parens 4 count", (long long)generateParenthesis(4).size(), 14LL);

    cout << "--- TODO 10: totalNQueens ---\n";
    ck("queens 1", (long long)totalNQueens(1), 1LL);
    ck("queens 2", (long long)totalNQueens(2), 0LL);
    ck("queens 4", (long long)totalNQueens(4), 2LL);
    ck("queens 6", (long long)totalNQueens(6), 4LL);
    ck("queens 8", (long long)totalNQueens(8), 92LL);

    cout << "\n----------------------------------------\n";
    cout << pass_ << " passed, " << fail_ << " failed\n";
    if (fail_ == 0) cout << "All tests pass. Move on to the problem list in Part 16.\n";
    return fail_ == 0 ? 0 : 1;
}
