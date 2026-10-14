// ============================================================================
//  Recursion & Backtracking — reference answers to practice/practice-01-basics.cpp
//
//      g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
//  Same tests as the practice file, all passing. Read this AFTER you have made
//  a real attempt at the practice file yourself.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------- 1
// Base case: a single digit is its own sum. Otherwise: last digit + the rest.
int sumOfDigits(int n) {
    if (n < 10) return n;
    return n % 10 + sumOfDigits(n / 10);
}

// ---------------------------------------------------------------------- 2
// ONE recursive call, stored in `half`. Depth is log2(n).
long long fastPower(long long x, int n) {
    if (n == 0) return 1;
    long long half = fastPower(x, n / 2);
    return (n % 2 == 0) ? half * half : half * half * x;
}

// ---------------------------------------------------------------------- 3
// Base case covers both the empty middle (l > r) and the single char (l == r).
bool isPalindrome(const string& s, int l, int r) {
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return isPalindrome(s, l + 1, r - 1);
}

// ---------------------------------------------------------------------- 4
// 2^n - 1 moves. The leap of faith: hanoi(n-1, ...) just works.
void hanoi(int n, int from, int to, int via, vector<pair<int,int>>& moves) {
    if (n == 0) return;
    hanoi(n - 1, from, via, to, moves);     // park n-1 discs on the spare rod
    moves.push_back({from, to});            // move the biggest disc
    hanoi(n - 1, via, to, from, moves);     // bring the n-1 discs back on top
}

// ---------------------------------------------------------------------- 5
// Pick / skip. Each leaf of the tree (i == n) is one subset: 2^n leaves.
static void subsetsDfs(const vector<int>& a, int i, vector<int>& cur,
                       vector<vector<int>>& res) {
    if (i == (int)a.size()) { res.push_back(cur); return; }
    cur.push_back(a[i]);
    subsetsDfs(a, i + 1, cur, res);         // pick
    cur.pop_back();
    subsetsDfs(a, i + 1, cur, res);         // skip
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    subsetsDfs(nums, 0, cur, res);
    return res;
}

// ---------------------------------------------------------------------- 6
// Same tree as 5, but nothing is built: the function RETURNS a count.
// Since every value is positive, a sum above k can never come back down.
static int countDfs(const vector<int>& a, int i, int sum, int k) {
    if (sum > k) return 0;                   // prune (positive values only)
    if (i == (int)a.size()) return sum == k ? 1 : 0;
    return countDfs(a, i + 1, sum + a[i], k)     // pick
         + countDfs(a, i + 1, sum, k);           // skip
}
int countSubsequencesWithSum(vector<int>& a, int k) {
    return countDfs(a, 0, 0, k);
}

// ---------------------------------------------------------------------- 7
static void permDfs(const vector<int>& a, vector<bool>& used, vector<int>& cur,
                    vector<vector<int>>& res) {
    if (cur.size() == a.size()) { res.push_back(cur); return; }
    for (int i = 0; i < (int)a.size(); i++) {
        if (used[i]) continue;
        used[i] = true;  cur.push_back(a[i]);   // choose
        permDfs(a, used, cur, res);             // explore
        used[i] = false; cur.pop_back();        // un-choose
    }
}
vector<vector<int>> permutations(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(nums.size(), false);
    permDfs(nums, used, cur, res);
    return res;
}

// ---------------------------------------------------------------------- 8
static void combDfs(const vector<int>& c, int start, int remain, vector<int>& cur,
                    vector<vector<int>>& res) {
    if (remain == 0) { res.push_back(cur); return; }
    for (int i = start; i < (int)c.size(); i++) {
        if (c[i] > remain) break;                // sorted, so the rest are too big
        cur.push_back(c[i]);
        combDfs(c, i, remain - c[i], cur, res);  // i: the same number may repeat
        cur.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> cur;
    combDfs(candidates, 0, target, cur, res);
    return res;
}

// ---------------------------------------------------------------------- 9
static void parenDfs(int n, int open, int close, string& cur, vector<string>& res) {
    if ((int)cur.size() == 2 * n) { res.push_back(cur); return; }
    if (open < n)     { cur.push_back('('); parenDfs(n, open + 1, close, cur, res); cur.pop_back(); }
    if (close < open) { cur.push_back(')'); parenDfs(n, open, close + 1, cur, res); cur.pop_back(); }
}
vector<string> generateParenthesis(int n) {
    vector<string> res;
    string cur;
    parenDfs(n, 0, 0, cur, res);
    return res;
}

// ---------------------------------------------------------------------- 10
static int queens(int r, int n, vector<bool>& col, vector<bool>& d1, vector<bool>& d2) {
    if (r == n) return 1;
    int count = 0;
    for (int c = 0; c < n; c++) {
        if (col[c] || d1[r + c] || d2[r - c + n - 1]) continue;
        col[c] = d1[r + c] = d2[r - c + n - 1] = true;
        count += queens(r + 1, n, col, d1, d2);
        col[c] = d1[r + c] = d2[r - c + n - 1] = false;
    }
    return count;
}
int totalNQueens(int n) {
    vector<bool> col(n, false), d1(2 * n - 1, false), d2(2 * n - 1, false);
    return queens(0, n, col, d1, d2);
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
