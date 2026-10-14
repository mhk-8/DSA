// ============================================================================
//  Recursion & Backtracking — reference solutions for Part 16 of the guide
//  All 38 problems, Tier 1 -> Tier 2 -> Tier 3, each with test cases.
//
//  Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part16-solutions.cpp && ./ref
//
//  Every solution lives in its own namespace so each class can be called
//  Solution, exactly as LeetCode expects. The //>>>BEGIN / //<<<END markers
//  delimit the code that is printed in Recursion-and-Backtracking-Solved-
//  Questions.pdf, so the book can never drift from the code that was tested.
//
//  Backtracking problems return their answers in any order, so the tests sort
//  both the result and the expected answer before comparing.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------- test harness
static int g_pass = 0, g_fail = 0;

template <class T>
static string show(const T& v) { ostringstream o; o << v; return o.str(); }
static string show(bool b)     { return b ? "true" : "false"; }
static string show(double d)   { ostringstream o; o << fixed << setprecision(5) << d; return o.str(); }
static string show(const string& s) { return "\"" + s + "\""; }
template <class T>
static string show(const vector<T>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += show(v[i]); }
    return s + "]";
}

template <class A, class B>
static void check(const string& label, const A& got, const B& want) {
    if (show(got) == show(want)) { g_pass++; }
    else {
        g_fail++;
        cout << "  FAIL " << label << "\n       got  " << show(got)
             << "\n       want " << show(want) << "\n";
    }
}
template <class T>
static vector<T> sorted(vector<T> v) { sort(v.begin(), v.end()); return v; }
// sort every inner vector, then the outer one: makes subset/combination
// answers comparable no matter what order the recursion produced them in
static vector<vector<int>> canon(vector<vector<int>> v) {
    for (auto& x : v) sort(x.begin(), x.end());
    sort(v.begin(), v.end());
    return v;
}
static void banner(const string& s) { cout << "\n== " << s << " ==\n"; }

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
static ListNode* makeList(const vector<int>& v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
static vector<int> toVec(ListNode* h) { vector<int> v; for (; h; h = h->next) v.push_back(h->val); return v; }

// ============================================================================
//  TIER 1
// ============================================================================

// --------------------------------------------------------------------- LC 509
namespace LC509 {
//>>>BEGIN LC509
class Solution {
    int memo[31];
    int f(int n) {
        if (n <= 1) return n;                    // base cases: F(0)=0, F(1)=1
        if (memo[n] != -1) return memo[n];       // already solved once
        return memo[n] = f(n - 1) + f(n - 2);    // trust the two smaller calls
    }
public:
    int fib(int n) {
        fill(memo, memo + 31, -1);
        return f(n);
    }
};
//<<<END LC509
}

// --------------------------------------------------------------------- LC 344
namespace LC344 {
//>>>BEGIN LC344
class Solution {
    void rev(vector<char>& s, int l, int r) {
        if (l >= r) return;                      // 0 or 1 chars left: done
        swap(s[l], s[r]);                        // handle the outer pair
        rev(s, l + 1, r - 1);                    // trust recursion for the inside
    }
public:
    void reverseString(vector<char>& s) {
        rev(s, 0, (int)s.size() - 1);
    }
};
//<<<END LC344
}

// ---------------------------------------------------------------------- LC 50
namespace LC50 {
//>>>BEGIN LC50
class Solution {
    double power(double x, long long n) {        // n >= 0 here
        if (n == 0) return 1.0;
        double half = power(x, n / 2);           // ONE recursive call, reused
        return (n % 2 == 0) ? half * half : half * half * x;
    }
public:
    double myPow(double x, int n) {
        long long N = n;                         // -INT_MIN overflows an int
        if (N < 0) { x = 1.0 / x; N = -N; }
        return power(x, N);
    }
};
//<<<END LC50
}

// ---------------------------------------------------------------------- LC 21
namespace LC21 {
//>>>BEGIN LC21
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if (!a) return b;                        // one list exhausted:
        if (!b) return a;                        // the rest is the other list
        if (a->val <= b->val) {
            a->next = mergeTwoLists(a->next, b); // a wins this position
            return a;
        }
        b->next = mergeTwoLists(a, b->next);     // b wins this position
        return b;
    }
};
//<<<END LC21
}

// --------------------------------------------------------------------- LC 779
namespace LC779 {
//>>>BEGIN LC779
class Solution {
public:
    int kthGrammar(int n, int k) {
        if (n == 1) return 0;                    // row 1 is just "0"
        int parent = kthGrammar(n - 1, (k + 1) / 2);
        // 0 -> "01", 1 -> "10": an odd k is the LEFT child and copies its
        // parent; an even k is the RIGHT child and is the flip of its parent
        return (k % 2 == 1) ? parent : 1 - parent;
    }
};
//<<<END LC779
}

// -------------------------------------------------------------------- LC 1823
namespace LC1823 {
//>>>BEGIN LC1823
class Solution {
    // survivor's 0-indexed position among n people, counting k each time
    int josephus(int n, int k) {
        if (n == 1) return 0;                    // the last one standing
        // after the first removal the circle restarts k places later,
        // so shift the smaller answer forward by k and wrap around
        return (josephus(n - 1, k) + k) % n;
    }
public:
    int findTheWinner(int n, int k) {
        return josephus(n, k) + 1;               // the problem is 1-indexed
    }
};
//<<<END LC1823
}

// ---------------------------------------------------------------------- LC 78
namespace LC78 {
//>>>BEGIN LC78
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(const vector<int>& nums, int i) {
        if (i == (int)nums.size()) {             // decided for every element
            res.push_back(cur);
            return;
        }
        cur.push_back(nums[i]);                  // choice 1: PICK nums[i]
        dfs(nums, i + 1);
        cur.pop_back();                          // undo the choice
        dfs(nums, i + 1);                        // choice 2: SKIP nums[i]
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
        return res;
    }
};
//<<<END LC78
}

// ---------------------------------------------------------------------- LC 90
namespace LC90 {
//>>>BEGIN LC90
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(const vector<int>& nums, int start) {
        res.push_back(cur);                      // every node is a subset
        for (int i = start; i < (int)nums.size(); i++) {
            // same value at the same depth = same subtree: skip it
            if (i > start && nums[i] == nums[i - 1]) continue;
            cur.push_back(nums[i]);
            dfs(nums, i + 1);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());          // duplicates must be adjacent
        dfs(nums, 0);
        return res;
    }
};
//<<<END LC90
}

// ---------------------------------------------------------------------- LC 46
namespace LC46 {
//>>>BEGIN LC46
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used;
    void dfs(const vector<int>& nums) {
        if (cur.size() == nums.size()) {         // every slot filled
            res.push_back(cur);
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;               // already placed earlier
            used[i] = true;  cur.push_back(nums[i]);
            dfs(nums);
            used[i] = false; cur.pop_back();     // undo BOTH changes
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.assign(nums.size(), false);
        dfs(nums);
        return res;
    }
};
//<<<END LC46
}

// ---------------------------------------------------------------------- LC 77
namespace LC77 {
//>>>BEGIN LC77
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(int n, int k, int start) {
        if ((int)cur.size() == k) { res.push_back(cur); return; }
        int need = k - (int)cur.size();
        // pruning: there must be at least `need` numbers left in [i, n]
        for (int i = start; i <= n - need + 1; i++) {
            cur.push_back(i);
            dfs(n, k, i + 1);                    // i+1: each number used once
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        dfs(n, k, 1);
        return res;
    }
};
//<<<END LC77
}

// ---------------------------------------------------------------------- LC 39
namespace LC39 {
//>>>BEGIN LC39
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(const vector<int>& c, int start, int remain) {
        if (remain == 0) { res.push_back(cur); return; }
        for (int i = start; i < (int)c.size(); i++) {
            if (c[i] > remain) break;            // sorted: the rest are bigger too
            cur.push_back(c[i]);
            dfs(c, i, remain - c[i]);            // i, not i+1: reuse allowed
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return res;
    }
};
//<<<END LC39
}

// ---------------------------------------------------------------------- LC 17
namespace LC17 {
//>>>BEGIN LC17
class Solution {
    const vector<string> keys{"", "", "abc", "def", "ghi",
                              "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string cur;
    void dfs(const string& digits, int i) {
        if (i == (int)digits.size()) { res.push_back(cur); return; }
        for (char ch : keys[digits[i] - '0']) {  // one branch per letter
            cur.push_back(ch);
            dfs(digits, i + 1);
            cur.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};           // NOT {""}
        dfs(digits, 0);
        return res;
    }
};
//<<<END LC17
}

// ---------------------------------------------------------------------- LC 22
namespace LC22 {
//>>>BEGIN LC22
class Solution {
    vector<string> res;
    string cur;
    void dfs(int n, int open, int close) {
        if ((int)cur.size() == 2 * n) { res.push_back(cur); return; }
        if (open < n) {                          // an opener is still available
            cur.push_back('(');
            dfs(n, open + 1, close);
            cur.pop_back();
        }
        if (close < open) {                      // only close what is open
            cur.push_back(')');
            dfs(n, open, close + 1);
            cur.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        dfs(n, 0, 0);
        return res;
    }
};
//<<<END LC22
}

// ============================================================================
//  TIER 2
// ============================================================================

// ---------------------------------------------------------------------- LC 40
namespace LC40 {
//>>>BEGIN LC40
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(const vector<int>& c, int start, int remain) {
        if (remain == 0) { res.push_back(cur); return; }
        for (int i = start; i < (int)c.size(); i++) {
            if (i > start && c[i] == c[i - 1]) continue;  // duplicate branch
            if (c[i] > remain) break;                     // sorted: prune
            cur.push_back(c[i]);
            dfs(c, i + 1, remain - c[i]);                 // i+1: use once
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return res;
    }
};
//<<<END LC40
}

// --------------------------------------------------------------------- LC 216
namespace LC216 {
//>>>BEGIN LC216
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    void dfs(int k, int start, int remain) {
        if ((int)cur.size() == k) {
            if (remain == 0) res.push_back(cur);
            return;                              // k numbers used: stop either way
        }
        for (int d = start; d <= 9; d++) {
            if (d > remain) break;               // digits only grow from here
            cur.push_back(d);
            dfs(k, d + 1, remain - d);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        dfs(k, 1, n);
        return res;
    }
};
//<<<END LC216
}

// ---------------------------------------------------------------------- LC 47
namespace LC47 {
//>>>BEGIN LC47
class Solution {
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used;
    void dfs(const vector<int>& a) {
        if (cur.size() == a.size()) { res.push_back(cur); return; }
        for (int i = 0; i < (int)a.size(); i++) {
            if (used[i]) continue;
            // equal values must be placed in left-to-right order; if the
            // previous twin is NOT used, this branch repeats an earlier one
            if (i > 0 && a[i] == a[i - 1] && !used[i - 1]) continue;
            used[i] = true;  cur.push_back(a[i]);
            dfs(a);
            used[i] = false; cur.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        used.assign(nums.size(), false);
        dfs(nums);
        return res;
    }
};
//<<<END LC47
}

// --------------------------------------------------------------------- LC 131
namespace LC131 {
//>>>BEGIN LC131
class Solution {
    vector<vector<string>> res;
    vector<string> cur;
    bool isPal(const string& s, int l, int r) {
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    }
    void dfs(const string& s, int start) {
        if (start == (int)s.size()) { res.push_back(cur); return; }
        for (int end = start; end < (int)s.size(); end++) {
            if (!isPal(s, start, end)) continue;      // this cut is illegal
            cur.push_back(s.substr(start, end - start + 1));
            dfs(s, end + 1);                          // partition the rest
            cur.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        dfs(s, 0);
        return res;
    }
};
//<<<END LC131
}

// ---------------------------------------------------------------------- LC 79
namespace LC79 {
//>>>BEGIN LC79
class Solution {
    bool dfs(vector<vector<char>>& b, const string& w, int i, int r, int c) {
        if (i == (int)w.size()) return true;          // matched every letter
        if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size())
            return false;
        if (b[r][c] != w[i]) return false;
        char saved = b[r][c];
        b[r][c] = '#';                                // mark: in the current path
        bool found = dfs(b, w, i + 1, r + 1, c) || dfs(b, w, i + 1, r - 1, c) ||
                     dfs(b, w, i + 1, r, c + 1) || dfs(b, w, i + 1, r, c - 1);
        b[r][c] = saved;                              // unmark on the way back
        return found;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int r = 0; r < (int)board.size(); r++)
            for (int c = 0; c < (int)board[0].size(); c++)
                if (dfs(board, word, 0, r, c)) return true;
        return false;
    }
};
//<<<END LC79
}

// ---------------------------------------------------------------------- LC 51
namespace LC51 {
//>>>BEGIN LC51
class Solution {
    vector<vector<string>> res;
    vector<string> board;
    vector<bool> col, diag, anti;    // diag: r+c,  anti: r-c+n-1
    void place(int r, int n) {
        if (r == n) { res.push_back(board); return; }
        for (int c = 0; c < n; c++) {
            if (col[c] || diag[r + c] || anti[r - c + n - 1]) continue;
            col[c] = diag[r + c] = anti[r - c + n - 1] = true;
            board[r][c] = 'Q';
            place(r + 1, n);                          // one queen per row
            board[r][c] = '.';
            col[c] = diag[r + c] = anti[r - c + n - 1] = false;
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        board.assign(n, string(n, '.'));
        col.assign(n, false);
        diag.assign(2 * n - 1, false);
        anti.assign(2 * n - 1, false);
        place(0, n);
        return res;
    }
};
//<<<END LC51
}

// ---------------------------------------------------------------------- LC 52
namespace LC52 {
//>>>BEGIN LC52
class Solution {
    // the three bitmasks are passed BY VALUE, so there is nothing to undo
    int place(int n, int r, int cols, int d1, int d2) {
        if (r == n) return 1;                         // a full valid board
        int count = 0;
        for (int c = 0; c < n; c++) {
            int a = r + c, b = r - c + n - 1;
            if ((cols >> c & 1) || (d1 >> a & 1) || (d2 >> b & 1)) continue;
            count += place(n, r + 1, cols | 1 << c, d1 | 1 << a, d2 | 1 << b);
        }
        return count;
    }
public:
    int totalNQueens(int n) {
        return place(n, 0, 0, 0, 0);
    }
};
//<<<END LC52
}

// ---------------------------------------------------------------------- LC 37
namespace LC37 {
//>>>BEGIN LC37
class Solution {
    bool row[9][10], col[9][10], box[9][10];
    vector<pair<int, int>> blanks;
    bool solve(vector<vector<char>>& b, int idx) {
        if (idx == (int)blanks.size()) return true;   // every blank filled
        auto [r, c] = blanks[idx];
        int bx = (r / 3) * 3 + c / 3;
        for (int d = 1; d <= 9; d++) {
            if (row[r][d] || col[c][d] || box[bx][d]) continue;
            row[r][d] = col[c][d] = box[bx][d] = true;
            b[r][c] = '0' + d;
            if (solve(b, idx + 1)) return true;       // stop at the FIRST solution
            row[r][d] = col[c][d] = box[bx][d] = false;
            b[r][c] = '.';
        }
        return false;                                 // no digit fits: backtrack
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        memset(box, 0, sizeof box);
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') { blanks.push_back({r, c}); continue; }
                int d = board[r][c] - '0';
                row[r][d] = col[c][d] = box[(r / 3) * 3 + c / 3][d] = true;
            }
        solve(board, 0);
    }
};
//<<<END LC37
}

// ---------------------------------------------------------------------- LC 93
namespace LC93 {
//>>>BEGIN LC93
class Solution {
    vector<string> res;
    vector<string> parts;
    void dfs(const string& s, int start) {
        int left = (int)s.size() - start, slots = 4 - (int)parts.size();
        if (left < slots || left > 3 * slots) return;  // cannot fit: prune
        if (slots == 0) {
            res.push_back(parts[0] + "." + parts[1] + "." + parts[2] + "." + parts[3]);
            return;
        }
        for (int len = 1; len <= 3 && start + len <= (int)s.size(); len++) {
            string seg = s.substr(start, len);
            if (len > 1 && seg[0] == '0') break;       // no leading zeros
            if (stoi(seg) > 255) break;
            parts.push_back(seg);
            dfs(s, start + len);
            parts.pop_back();
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0);
        return res;
    }
};
//<<<END LC93
}

// --------------------------------------------------------------------- LC 784
namespace LC784 {
//>>>BEGIN LC784
class Solution {
    vector<string> res;
    void dfs(string& s, int i) {
        if (i == (int)s.size()) { res.push_back(s); return; }
        dfs(s, i + 1);                                // branch 1: keep s[i] as is
        if (isalpha(s[i])) {                          // digits have ONE branch
            s[i] ^= 32;                               // flip case: 'a' <-> 'A'
            dfs(s, i + 1);                            // branch 2: flipped
            s[i] ^= 32;                               // undo
        }
    }
public:
    vector<string> letterCasePermutation(string s) {
        dfs(s, 0);
        return res;
    }
};
//<<<END LC784
}

// --------------------------------------------------------------------- LC 912
namespace LC912 {
//>>>BEGIN LC912
class Solution {
    vector<int> tmp;
    void mergeSort(vector<int>& a, int lo, int hi) {   // sorts a[lo..hi]
        if (lo >= hi) return;                          // 0 or 1 element
        int mid = lo + (hi - lo) / 2;
        mergeSort(a, lo, mid);                         // trust: left half sorted
        mergeSort(a, mid + 1, hi);                     // trust: right half sorted
        int i = lo, j = mid + 1, k = lo;               // now merge the two
        while (i <= mid && j <= hi) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i <= mid) tmp[k++] = a[i++];
        while (j <= hi)  tmp[k++] = a[j++];
        for (k = lo; k <= hi; k++) a[k] = tmp[k];
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize(nums.size());                       // one buffer, reused
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};
//<<<END LC912
}

// ---------------------------------------------------------------------- LC 60
namespace LC60 {
//>>>BEGIN LC60
class Solution {
    // pick the first digit, then recurse on the remaining digits with k shrunk
    string build(vector<int>& digits, int k, const vector<int>& fact) {
        int n = digits.size();
        if (n == 0) return "";
        int block = fact[n - 1];                       // perms per leading digit
        int idx = k / block;                           // which block k falls in
        int d = digits[idx];
        digits.erase(digits.begin() + idx);
        return char('0' + d) + build(digits, k % block, fact);
    }
public:
    string getPermutation(int n, int k) {
        vector<int> fact(n + 1, 1), digits;
        for (int i = 1; i <= n; i++) { fact[i] = fact[i - 1] * i; digits.push_back(i); }
        return build(digits, k - 1, fact);             // k-1: switch to 0-indexed
    }
};
//<<<END LC60
}

// --------------------------------------------------------------------- LC 241
namespace LC241 {
//>>>BEGIN LC241
class Solution {
    map<pair<int, int>, vector<int>> memo;
    vector<int> solve(const string& e, int lo, int hi) {   // e[lo..hi]
        if (memo.count({lo, hi})) return memo[{lo, hi}];
        vector<int> res;
        for (int i = lo; i <= hi; i++) {
            char op = e[i];
            if (op != '+' && op != '-' && op != '*') continue;
            // split at this operator: it is the LAST one evaluated
            vector<int> L = solve(e, lo, i - 1), R = solve(e, i + 1, hi);
            for (int a : L)
                for (int b : R)
                    res.push_back(op == '+' ? a + b : op == '-' ? a - b : a * b);
        }
        if (res.empty()) res.push_back(stoi(e.substr(lo, hi - lo + 1)));  // a number
        return memo[{lo, hi}] = res;
    }
public:
    vector<int> diffWaysToCompute(string expression) {
        return solve(expression, 0, (int)expression.size() - 1);
    }
};
//<<<END LC241
}

// --------------------------------------------------------------------- LC 494
namespace LC494 {
//>>>BEGIN LC494
class Solution {
    int total;
    vector<vector<int>> memo;          // memo[i][sum + total]
    int ways(const vector<int>& a, int i, int sum, int target) {
        if (i == (int)a.size()) return sum == target ? 1 : 0;
        int& m = memo[i][sum + total];
        if (m != -1) return m;
        return m = ways(a, i + 1, sum + a[i], target)    // put '+'
                 + ways(a, i + 1, sum - a[i], target);   // put '-'
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        total = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > total) return 0;
        memo.assign(nums.size(), vector<int>(2 * total + 1, -1));
        return ways(nums, 0, 0, target);
    }
};
//<<<END LC494
}

// -------------------------------------------------------------------- LC 1239
namespace LC1239 {
//>>>BEGIN LC1239
class Solution {
    vector<int> masks;                 // one bitmask per usable word
    int dfs(int i, int used) {
        if (i == (int)masks.size()) return __builtin_popcount(used);
        int best = dfs(i + 1, used);                     // skip word i
        if ((used & masks[i]) == 0)                      // no shared letter
            best = max(best, dfs(i + 1, used | masks[i]));   // take word i
        return best;
    }
public:
    int maxLength(vector<string>& arr) {
        for (const string& w : arr) {
            int m = 0;
            bool ok = true;
            for (char c : w) {
                if (m >> (c - 'a') & 1) { ok = false; break; }  // repeats itself
                m |= 1 << (c - 'a');
            }
            if (ok) masks.push_back(m);
        }
        return dfs(0, 0);
    }
};
//<<<END LC1239
}

// ============================================================================
//  TIER 3
// ============================================================================

// --------------------------------------------------------------------- LC 698
namespace LC698 {
//>>>BEGIN LC698
class Solution {
    vector<int> bucket;
    int side;
    bool dfs(const vector<int>& a, int i) {
        if (i == (int)a.size()) return true;             // every number placed
        for (int b = 0; b < (int)bucket.size(); b++) {
            if (bucket[b] + a[i] > side) continue;
            // two buckets with the same fill are interchangeable: try one
            if (b > 0 && bucket[b] == bucket[b - 1]) continue;
            bucket[b] += a[i];
            if (dfs(a, i + 1)) return true;
            bucket[b] -= a[i];
            if (bucket[b] == 0) break;                   // empty bucket failed:
        }                                                // every empty one will
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k) return false;
        side = sum / k;
        sort(nums.rbegin(), nums.rend());                // big numbers fail fast
        if (nums[0] > side) return false;
        bucket.assign(k, 0);
        return dfs(nums, 0);
    }
};
//<<<END LC698
}

// --------------------------------------------------------------------- LC 980
namespace LC980 {
//>>>BEGIN LC980
class Solution {
    int R, C, toVisit;
    int dfs(vector<vector<int>>& g, int r, int c, int left) {
        if (r < 0 || c < 0 || r >= R || c >= C || g[r][c] == -1) return 0;
        if (g[r][c] == 2) return left == 0 ? 1 : 0;      // end: was EVERY cell used?
        g[r][c] = -1;                                    // block it for this path
        int paths = dfs(g, r + 1, c, left - 1) + dfs(g, r - 1, c, left - 1)
                  + dfs(g, r, c + 1, left - 1) + dfs(g, r, c - 1, left - 1);
        g[r][c] = 0;                                     // unblock
        return paths;
    }
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        R = grid.size(); C = grid[0].size();
        int sr = 0, sc = 0, empty = 0;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == 0) empty++;
                if (grid[r][c] == 1) { sr = r; sc = c; }
            }
        // moves needed: every empty cell, plus the final step onto the end
        return dfs(grid, sr, sc, empty + 1);
    }
};
//<<<END LC980
}

// -------------------------------------------------------------------- LC 1079
namespace LC1079 {
//>>>BEGIN LC1079
class Solution {
    int cnt[26] = {0};
    int dfs() {
        int total = 0;
        for (int c = 0; c < 26; c++) {       // branch on DISTINCT letters only,
            if (cnt[c] == 0) continue;       // so duplicates never double-count
            cnt[c]--;
            total += 1 + dfs();              // this sequence + all its extensions
            cnt[c]++;
        }
        return total;
    }
public:
    int numTilePossibilities(string tiles) {
        for (char ch : tiles) cnt[ch - 'A']++;
        return dfs();
    }
};
//<<<END LC1079
}

// --------------------------------------------------------------------- LC 526
namespace LC526 {
//>>>BEGIN LC526
class Solution {
    vector<bool> used;
    int dfs(int n, int pos) {
        if (pos == 0) return 1;              // filled positions n..1
        int count = 0;
        for (int v = 1; v <= n; v++) {
            if (used[v] || (v % pos != 0 && pos % v != 0)) continue;
            used[v] = true;
            count += dfs(n, pos - 1);
            used[v] = false;
        }
        return count;
    }
public:
    int countArrangement(int n) {
        used.assign(n + 1, false);
        // fill from position n DOWN: large positions have few divisors,
        // so the tree is pruned near the root where pruning is worth most
        return dfs(n, n);
    }
};
//<<<END LC526
}

// --------------------------------------------------------------------- LC 140
namespace LC140 {
//>>>BEGIN LC140
class Solution {
    unordered_set<string> dict;
    unordered_map<int, vector<string>> memo;    // start -> sentences for s[start..]
    vector<string> dfs(const string& s, int start) {
        if (memo.count(start)) return memo[start];
        vector<string> res;
        if (start == (int)s.size()) { res.push_back(""); return res; }
        for (int end = start + 1; end <= (int)s.size(); end++) {
            string word = s.substr(start, end - start);
            if (!dict.count(word)) continue;
            for (const string& rest : dfs(s, end))
                res.push_back(rest.empty() ? word : word + " " + rest);
        }
        return memo[start] = res;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        dict.insert(wordDict.begin(), wordDict.end());
        return dfs(s, 0);
    }
};
//<<<END LC140
}

// --------------------------------------------------------------------- LC 301
namespace LC301 {
//>>>BEGIN LC301
class Solution {
    unordered_set<string> res;
    string cur;
    // l, r: how many '(' and ')' we STILL have to delete; open: balance so far
    void dfs(const string& s, int i, int l, int r, int open) {
        if (i == (int)s.size()) {
            if (l == 0 && r == 0 && open == 0) res.insert(cur);
            return;
        }
        char c = s[i];
        if (c == '(' && l > 0) dfs(s, i + 1, l - 1, r, open);    // delete it
        if (c == ')' && r > 0) dfs(s, i + 1, l, r - 1, open);    // delete it
        cur.push_back(c);                                        // keep it
        if (c != '(' && c != ')')  dfs(s, i + 1, l, r, open);
        else if (c == '(')         dfs(s, i + 1, l, r, open + 1);
        else if (open > 0)         dfs(s, i + 1, l, r, open - 1);
        cur.pop_back();
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0;                    // the MINIMUM deletions, counted first
        for (char c : s) {
            if (c == '(') l++;
            else if (c == ')') { if (l > 0) l--; else r++; }
        }
        dfs(s, 0, l, r, 0);
        return vector<string>(res.begin(), res.end());
    }
};
//<<<END LC301
}

// --------------------------------------------------------------------- LC 282
namespace LC282 {
//>>>BEGIN LC282
class Solution {
    vector<string> res;
    // val: value of expr so far; last: the last multiplicative term in it
    void dfs(const string& num, int target, int pos, string expr,
             long long val, long long last) {
        if (pos == (int)num.size()) {
            if (val == target) res.push_back(expr);
            return;
        }
        for (int len = 1; pos + len <= (int)num.size(); len++) {
            if (len > 1 && num[pos] == '0') break;           // no "05"
            string s = num.substr(pos, len);
            long long x = stoll(s);
            if (pos == 0) { dfs(num, target, len, s, x, x); continue; }
            dfs(num, target, pos + len, expr + "+" + s, val + x,  x);
            dfs(num, target, pos + len, expr + "-" + s, val - x, -x);
            // '*' binds tighter: take back `last`, then add last * x
            dfs(num, target, pos + len, expr + "*" + s,
                val - last + last * x, last * x);
        }
    }
public:
    vector<string> addOperators(string num, int target) {
        dfs(num, target, 0, "", 0, 0);
        return res;
    }
};
//<<<END LC282
}

// -------------------------------------------------------------------- LC 1255
namespace LC1255 {
//>>>BEGIN LC1255
class Solution {
    int cnt[26] = {0};
    int dfs(const vector<string>& w, const vector<int>& score, int i) {
        if (i == (int)w.size()) return 0;
        int best = dfs(w, score, i + 1);                 // skip word i
        int gain = 0;
        bool ok = true;
        for (char c : w[i]) {                            // try to take word i
            if (--cnt[c - 'a'] < 0) ok = false;
            gain += score[c - 'a'];
        }
        if (ok) best = max(best, gain + dfs(w, score, i + 1));
        for (char c : w[i]) cnt[c - 'a']++;              // undo, ok or not
        return best;
    }
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        for (char c : letters) cnt[c - 'a']++;
        return dfs(words, score, 0);
    }
};
//<<<END LC1255
}

// --------------------------------------------------------------------- LC 212
namespace LC212 {
//>>>BEGIN LC212
class Solution {
    struct Node {
        Node* next[26] = {nullptr};
        string word;                          // non-empty at the end of a word
    };
    vector<string> res;
    void dfs(vector<vector<char>>& b, int r, int c, Node* node) {
        if (r < 0 || c < 0 || r >= (int)b.size() || c >= (int)b[0].size()) return;
        char ch = b[r][c];
        if (ch == '#' || !node->next[ch - 'a']) return;  // used, or no word goes here
        node = node->next[ch - 'a'];
        if (!node->word.empty()) {
            res.push_back(node->word);
            node->word.clear();               // report each word only once
        }
        b[r][c] = '#';
        dfs(b, r + 1, c, node); dfs(b, r - 1, c, node);
        dfs(b, r, c + 1, node); dfs(b, r, c - 1, node);
        b[r][c] = ch;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Node* root = new Node();
        for (const string& w : words) {       // all words share ONE trie
            Node* cur = root;
            for (char ch : w) {
                if (!cur->next[ch - 'a']) cur->next[ch - 'a'] = new Node();
                cur = cur->next[ch - 'a'];
            }
            cur->word = w;
        }
        for (int r = 0; r < (int)board.size(); r++)
            for (int c = 0; c < (int)board[0].size(); c++)
                dfs(board, r, c, root);
        return res;
    }
};
//<<<END LC212
}

// --------------------------------------------------------------------- LC 493
namespace LC493 {
//>>>BEGIN LC493
class Solution {
    vector<int> tmp;
    long long sortCount(vector<int>& a, int lo, int hi) {
        if (lo >= hi) return 0;
        int mid = lo + (hi - lo) / 2;
        long long cnt = sortCount(a, lo, mid) + sortCount(a, mid + 1, hi);
        // both halves are sorted now: count cross pairs with one sweep
        int j = mid + 1;
        for (int i = lo; i <= mid; i++) {
            while (j <= hi && (long long)a[i] > 2LL * a[j]) j++;
            cnt += j - (mid + 1);
        }
        // then the ordinary merge
        int i = lo, k = lo; j = mid + 1;
        while (i <= mid && j <= hi) tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
        while (i <= mid) tmp[k++] = a[i++];
        while (j <= hi)  tmp[k++] = a[j++];
        for (k = lo; k <= hi; k++) a[k] = tmp[k];
        return cnt;
    }
public:
    int reversePairs(vector<int>& nums) {
        tmp.resize(nums.size());
        return (int)sortCount(nums, 0, (int)nums.size() - 1);
    }
};
//<<<END LC493
}

// ============================================================================
//  TESTS
// ============================================================================
int main() {
    banner("Tier 1");
    {   LC509::Solution s;
        check("LC509 0", s.fib(0), 0);   check("LC509 1", s.fib(1), 1);
        check("LC509 2", s.fib(2), 1);   check("LC509 10", s.fib(10), 55);
        check("LC509 30", s.fib(30), 832040);
    }
    {   LC344::Solution s;
        vector<char> a{'h','e','l','l','o'}; s.reverseString(a);
        check("LC344 a", string(a.begin(), a.end()), string("olleh"));
        vector<char> b{'H','a','n','n','a','h'}; s.reverseString(b);
        check("LC344 b", string(b.begin(), b.end()), string("hannaH"));
        vector<char> c{'x'}; s.reverseString(c);
        check("LC344 c", string(c.begin(), c.end()), string("x"));
    }
    {   LC50::Solution s;
        check("LC50 a", s.myPow(2.0, 10), 1024.0);
        check("LC50 b", s.myPow(2.1, 3), 9.261);
        check("LC50 c", s.myPow(2.0, -2), 0.25);
        check("LC50 d", s.myPow(1.0, INT_MIN), 1.0);
        check("LC50 e", s.myPow(2.0, 0), 1.0);
    }
    {   LC21::Solution s;
        check("LC21 a", toVec(s.mergeTwoLists(makeList({1,2,4}), makeList({1,3,4}))), vector<int>{1,1,2,3,4,4});
        check("LC21 b", toVec(s.mergeTwoLists(makeList({}), makeList({}))), vector<int>{});
        check("LC21 c", toVec(s.mergeTwoLists(makeList({}), makeList({0}))), vector<int>{0});
    }
    {   LC779::Solution s;
        check("LC779 a", s.kthGrammar(1, 1), 0);
        check("LC779 b", s.kthGrammar(2, 1), 0);
        check("LC779 c", s.kthGrammar(2, 2), 1);
        check("LC779 d", s.kthGrammar(4, 5), 1);    // row 4 = 01101001
        check("LC779 e", s.kthGrammar(4, 8), 1);
        check("LC779 f", s.kthGrammar(4, 6), 0);
    }
    {   LC1823::Solution s;
        check("LC1823 a", s.findTheWinner(5, 2), 3);
        check("LC1823 b", s.findTheWinner(6, 5), 1);
        check("LC1823 c", s.findTheWinner(1, 3), 1);
    }
    {   LC78::Solution s; vector<int> a{1,2,3};
        check("LC78 a", canon(s.subsets(a)),
              canon({{},{1},{2},{3},{1,2},{1,3},{2,3},{1,2,3}}));
        LC78::Solution t; vector<int> b{0};
        check("LC78 b", canon(t.subsets(b)), canon({{},{0}}));
    }
    {   LC90::Solution s; vector<int> a{1,2,2};
        check("LC90 a", canon(s.subsetsWithDup(a)), canon({{},{1},{1,2},{1,2,2},{2},{2,2}}));
        LC90::Solution t; vector<int> b{4,4,4,1,4};
        check("LC90 b size", (int)t.subsetsWithDup(b).size(), 10);
    }
    {   LC46::Solution s; vector<int> a{1,2,3};
        check("LC46 a", sorted(s.permute(a)),
              sorted(vector<vector<int>>{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}));
        LC46::Solution t; vector<int> b{0,1};
        check("LC46 b", sorted(t.permute(b)), sorted(vector<vector<int>>{{0,1},{1,0}}));
    }
    {   LC77::Solution s;
        check("LC77 a", canon(s.combine(4, 2)), canon({{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}}));
        LC77::Solution t;
        check("LC77 b", canon(t.combine(1, 1)), canon({{1}}));
        LC77::Solution u;
        check("LC77 c size", (int)u.combine(10, 3).size(), 120);
    }
    {   LC39::Solution s; vector<int> a{2,3,6,7};
        check("LC39 a", canon(s.combinationSum(a, 7)), canon({{2,2,3},{7}}));
        LC39::Solution t; vector<int> b{2,3,5};
        check("LC39 b", canon(t.combinationSum(b, 8)), canon({{2,2,2,2},{2,3,3},{3,5}}));
        LC39::Solution u; vector<int> c{2};
        check("LC39 c", canon(u.combinationSum(c, 1)), canon({}));
    }
    {   LC17::Solution s;
        check("LC17 a", sorted(s.letterCombinations("23")),
              sorted(vector<string>{"ad","ae","af","bd","be","bf","cd","ce","cf"}));
        LC17::Solution t;
        check("LC17 b", t.letterCombinations(""), vector<string>{});
        LC17::Solution u;
        check("LC17 c", sorted(u.letterCombinations("2")), vector<string>{"a","b","c"});
    }
    {   LC22::Solution s;
        check("LC22 a", sorted(s.generateParenthesis(3)),
              sorted(vector<string>{"((()))","(()())","(())()","()(())","()()()"}));
        LC22::Solution t;
        check("LC22 b", t.generateParenthesis(1), vector<string>{"()"});
        LC22::Solution u;
        check("LC22 c size", (int)u.generateParenthesis(5).size(), 42);   // Catalan(5)
    }

    banner("Tier 2");
    {   LC40::Solution s; vector<int> a{10,1,2,7,6,1,5};
        check("LC40 a", canon(s.combinationSum2(a, 8)), canon({{1,1,6},{1,2,5},{1,7},{2,6}}));
        LC40::Solution t; vector<int> b{2,5,2,1,2};
        check("LC40 b", canon(t.combinationSum2(b, 5)), canon({{1,2,2},{5}}));
    }
    {   LC216::Solution s;
        check("LC216 a", canon(s.combinationSum3(3, 7)), canon({{1,2,4}}));
        LC216::Solution t;
        check("LC216 b", canon(t.combinationSum3(3, 9)), canon({{1,2,6},{1,3,5},{2,3,4}}));
        LC216::Solution u;
        check("LC216 c", canon(u.combinationSum3(4, 1)), canon({}));
    }
    {   LC47::Solution s; vector<int> a{1,1,2};
        check("LC47 a", sorted(s.permuteUnique(a)),
              sorted(vector<vector<int>>{{1,1,2},{1,2,1},{2,1,1}}));
        LC47::Solution t; vector<int> b{1,2,3};
        check("LC47 b size", (int)t.permuteUnique(b).size(), 6);
        LC47::Solution u; vector<int> c{2,2,1,1};
        check("LC47 c size", (int)u.permuteUnique(c).size(), 6);
    }
    {   LC131::Solution s;
        check("LC131 a", sorted(s.partition("aab")),
              sorted(vector<vector<string>>{{"a","a","b"},{"aa","b"}}));
        LC131::Solution t;
        check("LC131 b", t.partition("a"), vector<vector<string>>{{"a"}});
    }
    {   LC79::Solution s;
        vector<vector<char>> b{{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
        check("LC79 a", s.exist(b, "ABCCED"), true);
        check("LC79 b", s.exist(b, "SEE"),    true);
        check("LC79 c", s.exist(b, "ABCB"),   false);   // would reuse the B
        check("LC79 board restored", b[0][0] == 'A' && b[1][2] == 'C', true);
    }
    {   LC51::Solution s;
        check("LC51 a", sorted(s.solveNQueens(4)),
              sorted(vector<vector<string>>{{".Q..","...Q","Q...","..Q."},
                                            {"..Q.","Q...","...Q",".Q.."}}));
        LC51::Solution t;
        check("LC51 b", t.solveNQueens(1), vector<vector<string>>{{"Q"}});
        LC51::Solution u;
        check("LC51 c size", (int)u.solveNQueens(8).size(), 92);
    }
    {   LC52::Solution s;
        check("LC52 1", s.totalNQueens(1), 1);
        check("LC52 3", s.totalNQueens(3), 0);
        check("LC52 4", s.totalNQueens(4), 2);
        check("LC52 8", s.totalNQueens(8), 92);
    }
    {   LC37::Solution s;
        vector<string> in{"53..7....","6..195...",".98....6.","8...6...3","4..8.3..1",
                          "7...2...6",".6....28.","...419..5","....8..79"};
        vector<string> want{"534678912","672195348","198342567","859761423","426853791",
                            "713924856","961537284","287419635","345286179"};
        vector<vector<char>> b;
        for (auto& r : in) b.push_back(vector<char>(r.begin(), r.end()));
        s.solveSudoku(b);
        vector<string> got;
        for (auto& r : b) got.push_back(string(r.begin(), r.end()));
        check("LC37 a", got, want);
    }
    {   LC93::Solution s;
        check("LC93 a", sorted(s.restoreIpAddresses("25525511135")),
              sorted(vector<string>{"255.255.11.135","255.255.111.35"}));
        LC93::Solution t;
        check("LC93 b", t.restoreIpAddresses("0000"), vector<string>{"0.0.0.0"});
        LC93::Solution u;
        check("LC93 c", sorted(u.restoreIpAddresses("101023")),
              sorted(vector<string>{"1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"}));
        LC93::Solution v;
        check("LC93 d", v.restoreIpAddresses("1"), vector<string>{});
    }
    {   LC784::Solution s;
        check("LC784 a", sorted(s.letterCasePermutation("a1b2")),
              sorted(vector<string>{"a1b2","a1B2","A1b2","A1B2"}));
        LC784::Solution t;
        check("LC784 b", sorted(t.letterCasePermutation("3z4")), sorted(vector<string>{"3z4","3Z4"}));
        LC784::Solution u;
        check("LC784 c", u.letterCasePermutation("12"), vector<string>{"12"});
    }
    {   LC912::Solution s;
        vector<int> a{5,2,3,1};          check("LC912 a", s.sortArray(a), vector<int>{1,2,3,5});
        vector<int> b{5,1,1,2,0,0};      check("LC912 b", s.sortArray(b), vector<int>{0,0,1,1,2,5});
        LC912::Solution t;
        vector<int> c{-3};               check("LC912 c", t.sortArray(c), vector<int>{-3});
    }
    {   LC60::Solution s;
        check("LC60 a", s.getPermutation(3, 3), string("213"));
        check("LC60 b", s.getPermutation(4, 9), string("2314"));
        check("LC60 c", s.getPermutation(3, 1), string("123"));
        check("LC60 d", s.getPermutation(3, 6), string("321"));
    }
    {   LC241::Solution s;
        check("LC241 a", sorted(s.diffWaysToCompute("2-1-1")), vector<int>{0,2});
        LC241::Solution t;
        check("LC241 b", sorted(t.diffWaysToCompute("2*3-4*5")), vector<int>{-34,-14,-10,-10,10});
        LC241::Solution u;
        check("LC241 c", u.diffWaysToCompute("11"), vector<int>{11});
    }
    {   LC494::Solution s;
        vector<int> a{1,1,1,1,1};  check("LC494 a", s.findTargetSumWays(a, 3), 5);
        LC494::Solution t;
        vector<int> b{1};          check("LC494 b", t.findTargetSumWays(b, 1), 1);
        LC494::Solution u;
        vector<int> c{1};          check("LC494 c", u.findTargetSumWays(c, 2), 0);
        LC494::Solution v;
        vector<int> d{0,0,1};      check("LC494 d", v.findTargetSumWays(d, 1), 4);
    }
    {   LC1239::Solution s;
        vector<string> a{"un","iq","ue"};          check("LC1239 a", s.maxLength(a), 4);
        LC1239::Solution t;
        vector<string> b{"cha","r","act","ers"};   check("LC1239 b", t.maxLength(b), 6);
        LC1239::Solution u;
        vector<string> c{"abcdefghijklmnopqrstuvwxyz"}; check("LC1239 c", u.maxLength(c), 26);
        LC1239::Solution v;
        vector<string> d{"aa","bb"};               check("LC1239 d", v.maxLength(d), 0);
    }

    banner("Tier 3");
    {   LC212::Solution s;
        vector<vector<char>> b{{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
        vector<string> w{"oath","pea","eat","rain"};
        check("LC212 a", sorted(s.findWords(b, w)), vector<string>{"eat","oath"});
        LC212::Solution t;
        vector<vector<char>> b2{{'a','b'},{'c','d'}};
        vector<string> w2{"abcb"};
        check("LC212 b", t.findWords(b2, w2), vector<string>{});
        LC212::Solution u;
        vector<vector<char>> b3{{'a','a'}};
        vector<string> w3{"aaa"};
        check("LC212 c", u.findWords(b3, w3), vector<string>{});
    }
    {   LC140::Solution s;
        vector<string> d{"cat","cats","and","sand","dog"};
        check("LC140 a", sorted(s.wordBreak("catsanddog", d)),
              vector<string>{"cat sand dog","cats and dog"});
        LC140::Solution t;
        vector<string> d2{"apple","pen","applepen","pine","pineapple"};
        check("LC140 b", sorted(t.wordBreak("pineapplepenapple", d2)),
              vector<string>{"pine apple pen apple","pine applepen apple","pineapple pen apple"});
        LC140::Solution u;
        vector<string> d3{"cats","dog","sand","and","cat"};
        check("LC140 c", u.wordBreak("catsandog", d3), vector<string>{});
    }
    {   LC698::Solution s;
        vector<int> a{4,3,2,3,5,2,1};  check("LC698 a", s.canPartitionKSubsets(a, 4), true);
        LC698::Solution t;
        vector<int> b{1,2,3,4};        check("LC698 b", t.canPartitionKSubsets(b, 3), false);
        LC698::Solution u;
        vector<int> c{2,2,2,2,3,4,5};  check("LC698 c", u.canPartitionKSubsets(c, 4), false);
        LC698::Solution v;
        vector<int> d{1,1,1,1,2,2,2,2}; check("LC698 d", v.canPartitionKSubsets(d, 4), true);
    }
    {   LC301::Solution s;
        check("LC301 a", sorted(s.removeInvalidParentheses("()())()")),
              vector<string>{"(())()","()()()"});
        LC301::Solution t;
        check("LC301 b", sorted(t.removeInvalidParentheses("(a)())()")),
              vector<string>{"(a())()","(a)()()"});
        LC301::Solution u;
        check("LC301 c", u.removeInvalidParentheses(")("), vector<string>{""});
    }
    {   LC282::Solution s;
        check("LC282 a", sorted(s.addOperators("123", 6)), vector<string>{"1*2*3","1+2+3"});
        LC282::Solution t;
        check("LC282 b", sorted(t.addOperators("232", 8)), vector<string>{"2*3+2","2+3*2"});
        LC282::Solution u;
        check("LC282 c", u.addOperators("3456237490", 9191), vector<string>{});
        LC282::Solution v;
        check("LC282 d", sorted(v.addOperators("105", 5)), vector<string>{"1*0+5","10-5"});
    }
    {   LC1255::Solution s;
        vector<string> w{"dog","cat","dad","good"};
        vector<char> l{'a','a','c','d','d','d','g','o','o'};
        vector<int> sc{1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0};
        check("LC1255 a", s.maxScoreWords(w, l, sc), 23);
        LC1255::Solution t;
        vector<string> w2{"xxxz","ax","bx","cx"};
        vector<char> l2{'z','a','b','c','x','x','x'};
        vector<int> sc2(26, 0); sc2[0] = sc2[1] = sc2[2] = 4; sc2[23] = 5; sc2[25] = 10;
        check("LC1255 b", t.maxScoreWords(w2, l2, sc2), 27);
        LC1255::Solution u;
        vector<string> w3{"leetcode"};
        vector<char> l3{'l','e','t','c','o','d'};
        vector<int> sc3{0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0};
        check("LC1255 c", u.maxScoreWords(w3, l3, sc3), 0);
    }
    {   LC980::Solution s;
        vector<vector<int>> a{{1,0,0,0},{0,0,0,0},{0,0,2,-1}};  check("LC980 a", s.uniquePathsIII(a), 2);
        LC980::Solution t;
        vector<vector<int>> b{{1,0,0,0},{0,0,0,0},{0,0,0,2}};   check("LC980 b", t.uniquePathsIII(b), 4);
        LC980::Solution u;
        vector<vector<int>> c{{0,1},{2,0}};                     check("LC980 c", u.uniquePathsIII(c), 0);
    }
    {   LC1079::Solution s;  check("LC1079 a", s.numTilePossibilities("AAB"), 8);
        LC1079::Solution t;  check("LC1079 b", t.numTilePossibilities("AAABBC"), 188);
        LC1079::Solution u;  check("LC1079 c", u.numTilePossibilities("V"), 1);
    }
    {   LC526::Solution s;
        check("LC526 1", s.countArrangement(1), 1);
        check("LC526 2", s.countArrangement(2), 2);
        check("LC526 3", s.countArrangement(3), 3);
        check("LC526 6", s.countArrangement(6), 36);
    }
    {   LC493::Solution s;
        vector<int> a{1,3,2,3,1};  check("LC493 a", s.reversePairs(a), 2);
        LC493::Solution t;
        vector<int> b{2,4,3,5,1};  check("LC493 b", t.reversePairs(b), 3);
        LC493::Solution u;         // 2*a[j] overflows int without the cast
        vector<int> c{2147483647,2147483647,2147483647,2147483647,2147483647,2147483647};
        check("LC493 c", u.reversePairs(c), 0);
        LC493::Solution v;
        vector<int> d{-5,-5};      check("LC493 d", v.reversePairs(d), 1);
    }

    cout << "\n----------------------------------------\n";
    cout << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}
