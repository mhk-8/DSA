// ============================================================================
//  Stacks & Queues — reference solutions for Part 11 of the guide
//  All 38 problems, Tier 1 -> Tier 2 -> Tier 3, each with test cases.
//
//  Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part11-solutions.cpp && ./ref
//
//  Every solution lives in its own namespace so each class can be called
//  Solution, exactly as LeetCode expects. The //>>>BEGIN / //<<<END markers
//  delimit the code that is printed in Stacks-and-Queues-Solved-Questions.pdf,
//  so the book can never drift from the code that was actually tested.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------- test harness
static int g_pass = 0, g_fail = 0;

template <class T>
static string show(const T& v) { ostringstream o; o << v; return o.str(); }
static string show(bool b)     { return b ? "true" : "false"; }
static string show(const vector<int>& v) {
    ostringstream o; o << "[";
    for (size_t i = 0; i < v.size(); i++) o << (i ? "," : "") << v[i];
    o << "]"; return o.str();
}
static string show(const string& s) { return "\"" + s + "\""; }

template <class A, class B>
static void check(const string& label, const A& got, const B& want) {
    if (show(got) == show(want)) { g_pass++; }
    else {
        g_fail++;
        cout << "  FAIL " << label << "  got " << show(got)
             << "  want " << show(want) << "\n";
    }
}
static void banner(const string& s) { cout << "\n== " << s << " ==\n"; }

// ============================================================================
//  TIER 1
// ============================================================================

// ---------------------------------------------------------------------- LC 20
namespace LC20 {
//>>>BEGIN LC20
class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> match{{')', '('}, {']', '['}, {'}', '{'}};
        stack<char> st;
        for (char c : s) {
            if (!match.count(c)) {              // an opening bracket
                st.push(c);
            } else {                            // a closing bracket
                if (st.empty() || st.top() != match[c]) return false;
                st.pop();
            }
        }
        return st.empty();                      // nothing may be left unclosed
    }
};
//<<<END LC20
}

// --------------------------------------------------------------------- LC 921
namespace LC921 {
//>>>BEGIN LC921
class Solution {
public:
    int minAddToMakeValid(string s) {
        int open = 0;        // unmatched '(' seen so far
        int need = 0;        // ')' that had nothing to match
        for (char c : s) {
            if (c == '(') open++;
            else if (open > 0) open--;          // this ')' matches an earlier '('
            else need++;                        // an orphan ')'
        }
        return open + need;
    }
};
//<<<END LC921
}

// --------------------------------------------------------------------- LC 155
namespace LC155 {
//>>>BEGIN LC155
class MinStack {
    stack<int> st;       // the real stack
    stack<int> mins;     // mins.top() == minimum of everything currently in st
public:
    MinStack() {}

    void push(int val) {
        st.push(val);
        mins.push(mins.empty() ? val : min(val, mins.top()));  // push ALWAYS
    }
    void pop()    { st.pop(); mins.pop(); }     // the two stay in lockstep
    int  top()    { return st.top(); }
    int  getMin() { return mins.top(); }
};
//<<<END LC155
}

// --------------------------------------------------------------------- LC 232
namespace LC232 {
//>>>BEGIN LC232
class MyQueue {
    stack<int> in;       // everything pushed goes here
    stack<int> out;      // everything popped comes from here, in reverse order

    void shift() {                              // only ever called when out is empty
        while (!in.empty()) { out.push(in.top()); in.pop(); }
    }
public:
    MyQueue() {}

    void push(int x) { in.push(x); }

    int pop() {
        peek();                                 // makes sure out is non-empty
        int v = out.top(); out.pop();
        return v;
    }
    int peek() {
        if (out.empty()) shift();               // LAZY refill — the whole point
        return out.top();
    }
    bool empty() { return in.empty() && out.empty(); }
};
//<<<END LC232
}

// --------------------------------------------------------------------- LC 225
namespace LC225 {
//>>>BEGIN LC225
class MyStack {
    queue<int> q;
public:
    MyStack() {}

    void push(int x) {
        q.push(x);
        // rotate every OTHER element to the back, so x ends up at the front
        for (int i = 1; i < (int)q.size(); i++) { q.push(q.front()); q.pop(); }
    }
    int  pop()   { int v = q.front(); q.pop(); return v; }
    int  top()   { return q.front(); }
    bool empty() { return q.empty(); }
};
//<<<END LC225
}

// --------------------------------------------------------------------- LC 622
namespace LC622 {
//>>>BEGIN LC622
class MyCircularQueue {
    vector<int> data;
    int cap, front_ = 0, count = 0;      // rear is DERIVED, never stored
public:
    MyCircularQueue(int k) : data(k), cap(k) {}

    bool enQueue(int value) {
        if (isFull()) return false;
        data[(front_ + count) % cap] = value;    // the rear slot
        count++;
        return true;
    }
    bool deQueue() {
        if (isEmpty()) return false;
        front_ = (front_ + 1) % cap;             // just walk the front forward
        count--;
        return true;
    }
    int  Front()  { return isEmpty() ? -1 : data[front_]; }
    int  Rear()   { return isEmpty() ? -1 : data[(front_ + count - 1) % cap]; }
    bool isEmpty(){ return count == 0; }
    bool isFull() { return count == cap; }
};
//<<<END LC622
}

// --------------------------------------------------------------------- LC 150
namespace LC150 {
//>>>BEGIN LC150
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<long long> st;
        for (const string& t : tokens) {
            if (t == "+" || t == "-" || t == "*" || t == "/") {
                long long b = st.top(); st.pop();      // RIGHT operand pops FIRST
                long long a = st.top(); st.pop();
                if      (t == "+") st.push(a + b);
                else if (t == "-") st.push(a - b);
                else if (t == "*") st.push(a * b);
                else               st.push(a / b);     // truncates toward zero
            } else {
                st.push(stoll(t));
            }
        }
        return (int)st.top();
    }
};
//<<<END LC150
}

// --------------------------------------------------------------------- LC 682
namespace LC682 {
//>>>BEGIN LC682
class Solution {
public:
    int calPoints(vector<string>& ops) {
        vector<int> st;                      // a vector so we can read st[n-2]
        for (const string& op : ops) {
            if (op == "C") {
                st.pop_back();                           // cancel the last score
            } else if (op == "D") {
                st.push_back(st.back() * 2);
            } else if (op == "+") {
                st.push_back(st[st.size() - 1] + st[st.size() - 2]);
            } else {
                st.push_back(stoi(op));
            }
        }
        return accumulate(st.begin(), st.end(), 0);
    }
};
//<<<END LC682
}

// -------------------------------------------------------------------- LC 1047
namespace LC1047 {
//>>>BEGIN LC1047
class Solution {
public:
    string removeDuplicates(string s) {
        string st;                          // the output string IS the stack
        for (char c : s) {
            if (!st.empty() && st.back() == c) st.pop_back();   // cancel the pair
            else st.push_back(c);
        }
        return st;
    }
};
//<<<END LC1047
}

// --------------------------------------------------------------------- LC 844
namespace LC844 {
//>>>BEGIN LC844
class Solution {
    string build(const string& s) {
        string st;
        for (char c : s) {
            if (c == '#') { if (!st.empty()) st.pop_back(); }   // guard the empty case
            else st.push_back(c);
        }
        return st;
    }
public:
    bool backspaceCompare(string s, string t) {
        return build(s) == build(t);
    }
};
//<<<END LC844
}

// --------------------------------------------------------------------- LC 496
namespace LC496 {
//>>>BEGIN LC496
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nxt;         // value -> its next greater value
        stack<int> st;                       // values, DECREASING bottom -> top
        for (int v : nums2) {
            while (!st.empty() && st.top() < v) { nxt[st.top()] = v; st.pop(); }
            st.push(v);
        }                                    // whatever is left has no next greater
        vector<int> res;
        for (int v : nums1) res.push_back(nxt.count(v) ? nxt[v] : -1);
        return res;
    }
};
//<<<END LC496
}

// --------------------------------------------------------------------- LC 739
namespace LC739 {
//>>>BEGIN LC739
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        int n = t.size();
        vector<int> res(n, 0);               // 0 = no warmer day ever comes
        stack<int> st;                       // INDICES, temperatures decreasing
        for (int i = 0; i < n; i++) {
            while (!st.empty() && t[st.top()] < t[i]) {
                res[st.top()] = i - st.top();          // the DISTANCE, not the value
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
};
//<<<END LC739
}

// --------------------------------------------------------------------- LC 933
namespace LC933 {
//>>>BEGIN LC933
class RecentCounter {
    queue<int> q;                            // ping times, oldest at the front
public:
    RecentCounter() {}

    int ping(int t) {
        q.push(t);
        while (q.front() < t - 3000) q.pop();   // drop everything now out of range
        return q.size();
    }
};
//<<<END LC933
}

// ============================================================================
//  TIER 2
// ============================================================================

// --------------------------------------------------------------------- LC 503
namespace LC503 {
//>>>BEGIN LC503
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& a) {
        int n = a.size();
        vector<int> res(n, -1);
        stack<int> st;                       // indices, values decreasing
        for (int i = 0; i < 2 * n; i++) {    // two laps around the circle
            int cur = a[i % n];
            while (!st.empty() && a[st.top()] < cur) { res[st.top()] = cur; st.pop(); }
            if (i < n) st.push(i);           // only push on the FIRST lap
        }
        return res;
    }
};
//<<<END LC503
}

// --------------------------------------------------------------------- LC 901
namespace LC901 {
//>>>BEGIN LC901
class StockSpanner {
    // Each entry is {price, span}. The stack is decreasing in price, and the
    // span of a popped entry is absorbed into the entry that swallowed it.
    stack<pair<int, int>> st;
public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;         // inherit the days it already covered
            st.pop();
        }
        st.push({price, span});
        return span;
    }
};
//<<<END LC901
}

// ---------------------------------------------------------------------- LC 84
namespace LC84 {
//>>>BEGIN LC84
class Solution {
public:
    int largestRectangleArea(vector<int>& h) {
        h.push_back(0);                      // sentinel: forces the stack to drain
        stack<int> st;                       // indices, heights INCREASING
        long long best = 0;
        for (int i = 0; i < (int)h.size(); i++) {
            while (!st.empty() && h[st.top()] > h[i]) {
                long long height = h[st.top()]; st.pop();
                // after the pop, st.top() is the previous SMALLER bar, which is
                // outside the rectangle -- hence the "- 1".
                int left = st.empty() ? -1 : st.top();
                best = max(best, height * (i - left - 1));
            }
            st.push(i);
        }
        h.pop_back();                        // leave the caller's vector as we found it
        return (int)best;
    }
};
//<<<END LC84
}

// ---------------------------------------------------------------------- LC 42
namespace LC42 {
//>>>BEGIN LC42
class Solution {
public:
    // Two pointers: O(n) time, O(1) space. Move whichever side has the smaller
    // running maximum, because that side's water level is already decided.
    int trap(vector<int>& a) {
        int l = 0, r = (int)a.size() - 1, lMax = 0, rMax = 0, water = 0;
        while (l < r) {
            if (a[l] < a[r]) {
                lMax = max(lMax, a[l]);
                water += lMax - a[l];
                l++;
            } else {
                rMax = max(rMax, a[r]);
                water += rMax - a[r];
                r--;
            }
        }
        return water;
    }

    // The monotonic-stack version: fills water in horizontal layers instead.
    int trapStack(vector<int>& a) {
        stack<int> st;                       // indices, heights decreasing
        int water = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            while (!st.empty() && a[st.top()] < a[i]) {
                int floorIdx = st.top(); st.pop();
                if (st.empty()) break;                  // no left wall -> no puddle
                int width  = i - st.top() - 1;
                int height = min(a[st.top()], a[i]) - a[floorIdx];
                water += width * height;
            }
            st.push(i);
        }
        return water;
    }
};
//<<<END LC42
}

// --------------------------------------------------------------------- LC 239
namespace LC239 {
//>>>BEGIN LC239
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        deque<int> dq;                       // INDICES, values decreasing
        vector<int> res;
        for (int i = 0; i < (int)a.size(); i++) {
            // 1. expire the front if it has slid out of the window
            if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            // 2. anything smaller that arrived earlier can never win again
            while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
            // 3. this index is a candidate
            dq.push_back(i);
            if (i >= k - 1) res.push_back(a[dq.front()]);   // front is the maximum
        }
        return res;
    }
};
//<<<END LC239
}

// ---------------------------------------------------------------------- LC 71
namespace LC71 {
//>>>BEGIN LC71
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;                   // the canonical directory components
        stringstream ss(path);
        string part;
        while (getline(ss, part, '/')) {
            if (part.empty() || part == ".") continue;       // "//" and "/./"
            if (part == "..") { if (!st.empty()) st.pop_back(); }   // go up, if we can
            else st.push_back(part);
        }
        string res;
        for (const string& d : st) res += "/" + d;
        return res.empty() ? "/" : res;      // the root is a special case
    }
};
//<<<END LC71
}

// --------------------------------------------------------------------- LC 394
namespace LC394 {
//>>>BEGIN LC394
class Solution {
public:
    string decodeString(string s) {
        stack<int> counts;                   // repeat counts waiting for their ']'
        stack<string> parts;                 // text built before each '['
        string cur;
        int k = 0;
        for (char c : s) {
            if (isdigit(c)) {
                k = k * 10 + (c - '0');      // counts can be multi-digit: 100[a]
            } else if (c == '[') {
                counts.push(k);              // save the context we are overwriting
                parts.push(cur);
                k = 0; cur.clear();
            } else if (c == ']') {
                string inner = cur;
                cur = parts.top(); parts.pop();          // restore the outer text
                int rep = counts.top(); counts.pop();
                while (rep--) cur += inner;
            } else {
                cur += c;
            }
        }
        return cur;
    }
};
//<<<END LC394
}

// --------------------------------------------------------------------- LC 227
namespace LC227 {
//>>>BEGIN LC227
class Solution {
public:
    int calculate(string s) {
        stack<long long> st;
        long long num = 0;
        char op = '+';                       // the operator BEFORE the current number
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (isdigit(c)) num = num * 10 + (c - '0');
            // flush on any operator, and on the last character whatever it is
            if ((!isdigit(c) && c != ' ') || i + 1 == (int)s.size()) {
                if      (op == '+') st.push(num);
                else if (op == '-') st.push(-num);       // subtraction = a negative term
                else if (op == '*') { long long t = st.top(); st.pop(); st.push(t * num); }
                else                { long long t = st.top(); st.pop(); st.push(t / num); }
                op = c; num = 0;
            }
        }
        long long sum = 0;
        while (!st.empty()) { sum += st.top(); st.pop(); }
        return (int)sum;
    }
};
//<<<END LC227
}

// --------------------------------------------------------------------- LC 946
namespace LC946 {
//>>>BEGIN LC946
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> st;
        size_t j = 0;                        // how much of popped we have matched
        for (int v : pushed) {
            st.push(v);
            // pop greedily for as long as the top is what must come out next
            while (!st.empty() && j < popped.size() && st.top() == popped[j]) {
                st.pop(); j++;
            }
        }
        return st.empty();                   // everything came out in the right order
    }
};
//<<<END LC946
}

// --------------------------------------------------------------------- LC 402
namespace LC402 {
//>>>BEGIN LC402
class Solution {
public:
    string removeKdigits(string num, int k) {
        string st;                           // an INCREASING stack of digits
        for (char c : num) {
            // a bigger digit in front of a smaller one is always worth removing
            while (k > 0 && !st.empty() && st.back() > c) { st.pop_back(); k--; }
            st.push_back(c);
        }
        while (k-- > 0 && !st.empty()) st.pop_back();   // digits already increasing
        int i = 0;
        while (i < (int)st.size() && st[i] == '0') i++; // strip leading zeros
        string res = st.substr(i);
        return res.empty() ? "0" : res;
    }
};
//<<<END LC402
}

// --------------------------------------------------------------------- LC 856
namespace LC856 {
//>>>BEGIN LC856
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);                          // the score of the current (outermost) level
        for (char c : s) {
            if (c == '(') {
                st.push(0);                  // open a new, empty level
            } else {
                int inner = st.top(); st.pop();
                int add = inner ? 2 * inner : 1;     // "()" scores 1, "(A)" scores 2A
                st.top() += add;                     // fold into the enclosing level
            }
        }
        return st.top();
    }
};
//<<<END LC856
}

// -------------------------------------------------------------------- LC 1249
namespace LC1249 {
//>>>BEGIN LC1249
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> open;                     // INDICES of '(' still unmatched
        vector<bool> drop(s.size(), false);
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') open.push(i);
            else if (s[i] == ')') {
                if (open.empty()) drop[i] = true;    // an orphan ')'
                else open.pop();
            }
        }
        while (!open.empty()) { drop[open.top()] = true; open.pop(); }  // orphan '('
        string res;
        for (int i = 0; i < (int)s.size(); i++) if (!drop[i]) res += s[i];
        return res;
    }
};
//<<<END LC1249
}

// ---------------------------------------------------------------------- LC 32
namespace LC32 {
//>>>BEGIN LC32
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);                         // sentinel: the base of the current run
        int best = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();                    // try to match it
                if (st.empty()) st.push(i);  // no match: i becomes the new base
                else best = max(best, i - st.top());   // length from the base to here
            }
        }
        return best;
    }
};
//<<<END LC32
}

// --------------------------------------------------------------------- LC 735
namespace LC735 {
//>>>BEGIN LC735
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;                      // the survivors so far
        for (int a : asteroids) {
            bool alive = true;
            // a collision happens only when a right-mover is on the stack and
            // the incoming asteroid moves left
            while (alive && a < 0 && !st.empty() && st.back() > 0) {
                if (st.back() < -a)      st.pop_back();      // the stack one explodes
                else if (st.back() == -a){ st.pop_back(); alive = false; }  // both do
                else                      alive = false;     // the incoming one does
            }
            if (alive) st.push_back(a);
        }
        return st;
    }
};
//<<<END LC735
}

// --------------------------------------------------------------------- LC 994
namespace LC994 {
//>>>BEGIN LC994
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), fresh = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) q.push({i, j});   // MULTI-source: every rotten one
                else if (grid[i][j] == 1) fresh++;
            }
        if (fresh == 0) return 0;                      // nothing to rot
        int minutes = 0;
        int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
        while (!q.empty() && fresh > 0) {
            int sz = q.size();                         // FREEZE the level width
            for (int s = 0; s < sz; s++) {
                auto [r, c] = q.front(); q.pop();
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                    if (grid[nr][nc] != 1) continue;
                    grid[nr][nc] = 2;                  // mark on push, not on pop
                    fresh--;
                    q.push({nr, nc});
                }
            }
            minutes++;                                 // one full level = one minute
        }
        return fresh == 0 ? minutes : -1;
    }
};
//<<<END LC994
}

// ============================================================================
//  TIER 3
// ============================================================================

// ---------------------------------------------------------------------- LC 85
namespace LC85 {
//>>>BEGIN LC85
class Solution {
    // exactly LC 84, reused unchanged
    int largestRectangleArea(vector<int>& h) {
        h.push_back(0);
        stack<int> st;
        long long best = 0;
        for (int i = 0; i < (int)h.size(); i++) {
            while (!st.empty() && h[st.top()] > h[i]) {
                long long height = h[st.top()]; st.pop();
                int left = st.empty() ? -1 : st.top();
                best = max(best, height * (i - left - 1));
            }
            st.push(i);
        }
        h.pop_back();
        return (int)best;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix[0].size(), best = 0;
        vector<int> heights(n, 0);
        for (const auto& row : matrix) {
            for (int c = 0; c < n; c++)
                heights[c] = (row[c] == '1') ? heights[c] + 1 : 0;  // running histogram
            best = max(best, largestRectangleArea(heights));
        }
        return best;
    }
};
//<<<END LC85
}

// --------------------------------------------------------------------- LC 224
namespace LC224 {
//>>>BEGIN LC224
class Solution {
public:
    int calculate(string s) {
        stack<int> st;                 // alternating: result, sign, result, sign, ...
        int result = 0, sign = 1, num = 0;
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '+') {
                result += sign * num; num = 0; sign =  1;
            } else if (c == '-') {
                result += sign * num; num = 0; sign = -1;
            } else if (c == '(') {
                st.push(result);       // save the context we are about to overwrite
                st.push(sign);
                result = 0; sign = 1;
            } else if (c == ')') {
                result += sign * num; num = 0;
                result *= st.top(); st.pop();       // the sign in front of the '('
                result += st.top(); st.pop();       // the result before the '('
                sign = 1;
            }
        }
        return result + sign * num;    // flush the trailing number
    }
};
//<<<END LC224
}

// --------------------------------------------------------------------- LC 907
namespace LC907 {
//>>>BEGIN LC907
class Solution {
public:
    int sumSubarrayMins(vector<int>& a) {
        const long long MOD = 1000000007LL;
        int n = a.size();
        vector<int> prev(n, -1), next(n, n);
        stack<int> st;
        // STRICT on the left, NON-STRICT on the right: among equal values exactly
        // one is treated as the owner, so no subarray is counted twice.
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()] >= a[i]) { next[st.top()] = i; st.pop(); }
            prev[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        long long total = 0;
        for (int i = 0; i < n; i++) {
            long long left  = i - prev[i];      // choices of start
            long long right = next[i] - i;      // choices of end
            total = (total + (long long)a[i] % MOD * (left * right % MOD)) % MOD;
        }
        return (int)total;
    }
};
//<<<END LC907
}

// --------------------------------------------------------------------- LC 456
namespace LC456 {
//>>>BEGIN LC456
class Solution {
public:
    bool find132pattern(vector<int>& a) {
        // Scan RIGHT to LEFT. "third" is the largest value we have already
        // popped, so it is guaranteed to have a bigger value to its right.
        stack<int> st;                        // decreasing bottom -> top
        int third = INT_MIN;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            if (a[i] < third) return true;    // a[i] < third < the popper: 1-3-2 found
            while (!st.empty() && st.top() < a[i]) { third = st.top(); st.pop(); }
            st.push(a[i]);
        }
        return false;
    }
};
//<<<END LC456
}

// --------------------------------------------------------------------- LC 316
namespace LC316 {
//>>>BEGIN LC316
class Solution {
public:
    string removeDuplicateLetters(string s) {
        int last[26] = {0};
        for (int i = 0; i < (int)s.size(); i++) last[s[i] - 'a'] = i;  // final position
        bool used[26] = {false};
        string st;                            // an INCREASING stack of letters
        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (used[c - 'a']) continue;      // already placed, and placement is final
            // drop a bigger letter only if it is guaranteed to reappear later
            while (!st.empty() && st.back() > c && last[st.back() - 'a'] > i) {
                used[st.back() - 'a'] = false;
                st.pop_back();
            }
            st.push_back(c);
            used[c - 'a'] = true;
        }
        return st;
    }
};
//<<<END LC316
}

// -------------------------------------------------------------------- LC 1019
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
namespace LC1019 {
using ::ListNode;
//>>>BEGIN LC1019
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> a;                        // copy to a vector first -- do not
        for (ListNode* p = head; p; p = p->next) a.push_back(p->val);  // fight pointers
        vector<int> res(a.size(), 0);         // 0 = no greater node ahead
        stack<int> st;                        // indices, values decreasing
        for (int i = 0; i < (int)a.size(); i++) {
            while (!st.empty() && a[st.top()] < a[i]) { res[st.top()] = a[i]; st.pop(); }
            st.push(i);
        }
        return res;
    }
};
//<<<END LC1019
}

// --------------------------------------------------------------------- LC 636
namespace LC636 {
//>>>BEGIN LC636
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        stack<int> st;                        // function ids currently on the call stack
        int prev = 0;                         // the timestamp we last accounted for
        for (const string& log : logs) {
            int p1 = log.find(':'), p2 = log.rfind(':');
            int id       = stoi(log.substr(0, p1));
            string type  = log.substr(p1 + 1, p2 - p1 - 1);
            int ts       = stoi(log.substr(p2 + 1));
            if (type == "start") {
                if (!st.empty()) res[st.top()] += ts - prev;   // credit the caller
                st.push(id);
                prev = ts;
            } else {
                res[st.top()] += ts - prev + 1;   // "end" is INCLUSIVE of its own unit
                st.pop();
                prev = ts + 1;
            }
        }
        return res;
    }
};
//<<<END LC636
}

// --------------------------------------------------------------------- LC 895
namespace LC895 {
//>>>BEGIN LC895
class FreqStack {
    unordered_map<int, int> freq;             // value -> how many copies are in
    unordered_map<int, vector<int>> group;    // frequency level -> stack of values
    int maxFreq = 0;
public:
    FreqStack() {}

    void push(int val) {
        int f = ++freq[val];
        maxFreq = max(maxFreq, f);
        group[f].push_back(val);              // one stack PER frequency level
    }
    int pop() {
        int val = group[maxFreq].back();      // most recent among the most frequent
        group[maxFreq].pop_back();
        freq[val]--;
        if (group[maxFreq].empty()) maxFreq--;
        return val;
    }
};
//<<<END LC895
}

// --------------------------------------------------------------------- LC 862
namespace LC862 {
//>>>BEGIN LC862
class Solution {
public:
    int shortestSubarray(vector<int>& a, int k) {
        int n = a.size();
        vector<long long> p(n + 1, 0);                      // prefix sums
        for (int i = 0; i < n; i++) p[i + 1] = p[i] + a[i];
        deque<int> dq;                        // indices into p, values INCREASING
        int best = n + 1;
        for (int i = 0; i <= n; i++) {
            // any front that already satisfies the sum gives a candidate, and it
            // can never be beaten by a later i, so pop it
            while (!dq.empty() && p[i] - p[dq.front()] >= k) {
                best = min(best, i - dq.front());
                dq.pop_front();
            }
            // a prefix that is >= the incoming one is useless: it is both larger
            // and further left, so it can never win
            while (!dq.empty() && p[dq.back()] >= p[i]) dq.pop_back();
            dq.push_back(i);
        }
        return best == n + 1 ? -1 : best;
    }
};
//<<<END LC862
}

// -------------------------------------------------------------------- LC 1425
namespace LC1425 {
//>>>BEGIN LC1425
class Solution {
public:
    int constrainedSubsetSum(vector<int>& a, int k) {
        int n = a.size();
        vector<int> dp(n);                    // dp[i] = best sum of a subsequence ending at i
        deque<int> dq;                        // indices, dp values DECREASING
        int best = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (!dq.empty() && dq.front() < i - k) dq.pop_front();   // expire
            dp[i] = a[i] + (dq.empty() ? 0 : max(0, dp[dq.front()])); // best in the window
            best = max(best, dp[i]);
            while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();  // dominate
            dq.push_back(i);
        }
        return best;
    }
};
//<<<END LC1425
}

// ============================================================================
//  TESTS
// ============================================================================
int main() {
    // ------------------------------------------------------------------ TIER 1
    banner("Tier 1");
    {   LC20::Solution s;
        check("LC20 a",  s.isValid("()"),       true);
        check("LC20 b",  s.isValid("()[]{}"),   true);
        check("LC20 c",  s.isValid("(]"),       false);
        check("LC20 d",  s.isValid("([)]"),     false);
        check("LC20 e",  s.isValid("(("),       false);
        check("LC20 f",  s.isValid(")("),       false);
        check("LC20 g",  s.isValid(""),         true);
    }
    {   LC921::Solution s;
        check("LC921 a", s.minAddToMakeValid("())"),  1);
        check("LC921 b", s.minAddToMakeValid("((("),  3);
        check("LC921 c", s.minAddToMakeValid("()"),   0);
        check("LC921 d", s.minAddToMakeValid(")("),   2);
    }
    {   LC155::MinStack st;
        st.push(-2); st.push(0); st.push(-3);
        check("LC155 a", st.getMin(), -3);
        st.pop();
        check("LC155 b", st.top(),     0);
        check("LC155 c", st.getMin(), -2);
        st.push(-2);
        check("LC155 d", st.getMin(), -2);   // duplicate minimum
        st.pop();
        check("LC155 e", st.getMin(), -2);
    }
    {   LC232::MyQueue q;
        q.push(1); q.push(2);
        check("LC232 a", q.peek(),  1);
        check("LC232 b", q.pop(),   1);
        q.push(3);
        check("LC232 c", q.pop(),   2);
        check("LC232 d", q.pop(),   3);
        check("LC232 e", q.empty(), true);
    }
    {   LC225::MyStack st;
        st.push(1); st.push(2);
        check("LC225 a", st.top(),   2);
        check("LC225 b", st.pop(),   2);
        check("LC225 c", st.top(),   1);
        check("LC225 d", st.empty(), false);
        st.pop();
        check("LC225 e", st.empty(), true);
    }
    {   LC622::MyCircularQueue q(3);
        check("LC622 a", q.enQueue(1),  true);
        check("LC622 b", q.enQueue(2),  true);
        check("LC622 c", q.enQueue(3),  true);
        check("LC622 d", q.enQueue(4),  false);   // full
        check("LC622 e", q.Rear(),      3);
        check("LC622 f", q.isFull(),    true);
        check("LC622 g", q.deQueue(),   true);
        check("LC622 h", q.enQueue(4),  true);    // wraps around
        check("LC622 i", q.Rear(),      4);
        check("LC622 j", q.Front(),     2);
    }
    {   LC150::Solution s;
        vector<string> a{"2","1","+","3","*"};      check("LC150 a", s.evalRPN(a),  9);
        vector<string> b{"4","13","5","/","+"};     check("LC150 b", s.evalRPN(b),  6);
        vector<string> c{"3","4","-"};              check("LC150 c", s.evalRPN(c), -1);
        vector<string> d{"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
        check("LC150 d", s.evalRPN(d), 22);
    }
    {   LC682::Solution s;
        vector<string> a{"5","2","C","D","+"};                check("LC682 a", s.calPoints(a), 30);
        vector<string> b{"5","-2","4","C","D","9","+","+"};   check("LC682 b", s.calPoints(b), 27);
    }
    {   LC1047::Solution s;
        check("LC1047 a", s.removeDuplicates("abbaca"), string("ca"));
        check("LC1047 b", s.removeDuplicates("azxxzy"), string("ay"));
        check("LC1047 c", s.removeDuplicates("aa"),     string(""));
    }
    {   LC844::Solution s;
        check("LC844 a", s.backspaceCompare("ab#c", "ad#c"), true);
        check("LC844 b", s.backspaceCompare("ab##", "c#d#"), true);
        check("LC844 c", s.backspaceCompare("a#c",  "b"),    false);
        check("LC844 d", s.backspaceCompare("#####a", "a"),  true);
    }
    {   LC496::Solution s;
        vector<int> a{4,1,2}, b{1,3,4,2};
        check("LC496 a", s.nextGreaterElement(a, b), vector<int>{-1,3,-1});
        vector<int> c{2,4}, d{1,2,3,4};
        check("LC496 b", s.nextGreaterElement(c, d), vector<int>{3,-1});
    }
    {   LC739::Solution s;
        vector<int> a{73,74,75,71,69,72,76,73};
        check("LC739 a", s.dailyTemperatures(a), vector<int>{1,1,4,2,1,1,0,0});
        vector<int> b{30,40,50,60};
        check("LC739 b", s.dailyTemperatures(b), vector<int>{1,1,1,0});
        vector<int> c{30,60,90};
        check("LC739 c", s.dailyTemperatures(c), vector<int>{1,1,0});
    }
    {   LC933::RecentCounter r;
        check("LC933 a", r.ping(1),    1);
        check("LC933 b", r.ping(100),  2);
        check("LC933 c", r.ping(3001), 3);
        check("LC933 d", r.ping(3002), 3);
    }

    // ------------------------------------------------------------------ TIER 2
    banner("Tier 2");
    {   LC503::Solution s;
        vector<int> a{1,2,1};      check("LC503 a", s.nextGreaterElements(a), vector<int>{2,-1,2});
        vector<int> b{1,2,3,4,3};  check("LC503 b", s.nextGreaterElements(b), vector<int>{2,3,4,-1,4});
        vector<int> c{5,4,3,2,1};  check("LC503 c", s.nextGreaterElements(c), vector<int>{-1,5,5,5,5});
    }
    {   LC901::StockSpanner sp;
        vector<int> prices{100,80,60,70,60,75,85}, want{1,1,1,2,1,4,6}, got;
        for (int p : prices) got.push_back(sp.next(p));
        check("LC901 a", got, want);
    }
    {   LC84::Solution s;
        vector<int> a{2,1,5,6,2,3};  check("LC84 a", s.largestRectangleArea(a), 10);
        vector<int> b{2,4};          check("LC84 b", s.largestRectangleArea(b), 4);
        vector<int> c{1,2,3};        check("LC84 c", s.largestRectangleArea(c), 4);   // increasing
        vector<int> d{3,2,1};        check("LC84 d", s.largestRectangleArea(d), 4);   // decreasing
        vector<int> e{2,2,2};        check("LC84 e", s.largestRectangleArea(e), 6);   // all equal
        vector<int> f{5};            check("LC84 f", s.largestRectangleArea(f), 5);
    }
    {   LC42::Solution s;
        vector<int> a{0,1,0,2,1,0,1,3,2,1,2,1};
        check("LC42 a",  s.trap(a),      6);
        check("LC42 a'", s.trapStack(a), 6);
        vector<int> b{4,2,0,3,2,5};
        check("LC42 b",  s.trap(b),      9);
        check("LC42 b'", s.trapStack(b), 9);
        vector<int> c{1,2,3};
        check("LC42 c",  s.trap(c),      0);
        check("LC42 c'", s.trapStack(c), 0);
    }
    {   LC239::Solution s;
        vector<int> a{1,3,-1,-3,5,3,6,7};
        check("LC239 a", s.maxSlidingWindow(a, 3), vector<int>{3,3,5,5,6,7});
        vector<int> b{1};
        check("LC239 b", s.maxSlidingWindow(b, 1), vector<int>{1});
        vector<int> c{7,2,4};
        check("LC239 c", s.maxSlidingWindow(c, 2), vector<int>{7,4});
        vector<int> d{2,2,2,2};
        check("LC239 d", s.maxSlidingWindow(d, 2), vector<int>{2,2,2});
    }
    {   LC71::Solution s;
        check("LC71 a", s.simplifyPath("/home/"),          string("/home"));
        check("LC71 b", s.simplifyPath("/../"),            string("/"));
        check("LC71 c", s.simplifyPath("/home//foo/"),     string("/home/foo"));
        check("LC71 d", s.simplifyPath("/a/./b/../../c/"), string("/c"));
    }
    {   LC394::Solution s;
        check("LC394 a", s.decodeString("3[a]2[bc]"),      string("aaabcbc"));
        check("LC394 b", s.decodeString("3[a2[c]]"),       string("accaccacc"));
        check("LC394 c", s.decodeString("2[abc]3[cd]ef"),  string("abcabccdcdcdef"));
        check("LC394 d", s.decodeString("10[a]"),          string("aaaaaaaaaa"));
    }
    {   LC227::Solution s;
        check("LC227 a", s.calculate("3+2*2"),      7);
        check("LC227 b", s.calculate(" 3/2 "),      1);
        check("LC227 c", s.calculate(" 3+5 / 2 "),  5);
        check("LC227 d", s.calculate("1"),          1);
        check("LC227 e", s.calculate("100-2*3"),   94);
    }
    {   LC946::Solution s;
        vector<int> pu{1,2,3,4,5}, po1{4,5,3,2,1}, po2{4,3,5,1,2};
        check("LC946 a", s.validateStackSequences(pu, po1), true);
        check("LC946 b", s.validateStackSequences(pu, po2), false);
    }
    {   LC402::Solution s;
        check("LC402 a", s.removeKdigits("1432219", 3), string("1219"));
        check("LC402 b", s.removeKdigits("10200", 1),   string("200"));
        check("LC402 c", s.removeKdigits("10", 2),      string("0"));
        check("LC402 d", s.removeKdigits("112", 1),     string("11"));
    }
    {   LC856::Solution s;
        check("LC856 a", s.scoreOfParentheses("()"),       1);
        check("LC856 b", s.scoreOfParentheses("(())"),     2);
        check("LC856 c", s.scoreOfParentheses("()()"),     2);
        check("LC856 d", s.scoreOfParentheses("(()(()))"), 6);
    }
    {   LC1249::Solution s;
        check("LC1249 a", s.minRemoveToMakeValid("lee(t(c)o)de)"), string("lee(t(c)o)de"));
        check("LC1249 b", s.minRemoveToMakeValid("a)b(c)d"),       string("ab(c)d"));
        check("LC1249 c", s.minRemoveToMakeValid("))(("),          string(""));
    }
    {   LC32::Solution s;
        check("LC32 a", s.longestValidParentheses("(()"),      2);
        check("LC32 b", s.longestValidParentheses(")()())"),   4);
        check("LC32 c", s.longestValidParentheses(""),         0);
        check("LC32 d", s.longestValidParentheses("()(()"),    2);
        check("LC32 e", s.longestValidParentheses("()(())"),   6);
    }
    {   LC735::Solution s;
        vector<int> a{5,10,-5};   check("LC735 a", s.asteroidCollision(a), vector<int>{5,10});
        vector<int> b{8,-8};      check("LC735 b", s.asteroidCollision(b), vector<int>{});
        vector<int> c{10,2,-5};   check("LC735 c", s.asteroidCollision(c), vector<int>{10});
        vector<int> d{-2,-1,1,2}; check("LC735 d", s.asteroidCollision(d), vector<int>{-2,-1,1,2});
    }
    {   LC994::Solution s;
        vector<vector<int>> a{{2,1,1},{1,1,0},{0,1,1}};  check("LC994 a", s.orangesRotting(a),  4);
        vector<vector<int>> b{{2,1,1},{0,1,1},{1,0,1}};  check("LC994 b", s.orangesRotting(b), -1);
        vector<vector<int>> c{{0,2}};                    check("LC994 c", s.orangesRotting(c),  0);
    }

    // ------------------------------------------------------------------ TIER 3
    banner("Tier 3");
    {   LC85::Solution s;
        vector<vector<char>> m{{'1','0','1','0','0'},
                               {'1','0','1','1','1'},
                               {'1','1','1','1','1'},
                               {'1','0','0','1','0'}};
        check("LC85 a", s.maximalRectangle(m), 6);
        vector<vector<char>> n{{'0'}};   check("LC85 b", s.maximalRectangle(n), 0);
        vector<vector<char>> o{{'1'}};   check("LC85 c", s.maximalRectangle(o), 1);
    }
    {   LC224::Solution s;
        check("LC224 a", s.calculate("1 + 1"),                 2);
        check("LC224 b", s.calculate(" 2-1 + 2 "),             3);
        check("LC224 c", s.calculate("(1+(4+5+2)-3)+(6+8)"),  23);
        check("LC224 d", s.calculate("2-(5-6)"),               3);
    }
    {   LC907::Solution s;
        vector<int> a{3,1,2,4};        check("LC907 a", s.sumSubarrayMins(a),  17);
        vector<int> b{11,81,94,43,3};  check("LC907 b", s.sumSubarrayMins(b), 444);
        vector<int> c{2,2,2};          check("LC907 c", s.sumSubarrayMins(c),  12);  // duplicates
    }
    {   LC456::Solution s;
        vector<int> a{1,2,3,4};   check("LC456 a", s.find132pattern(a), false);
        vector<int> b{3,1,4,2};   check("LC456 b", s.find132pattern(b), true);
        vector<int> c{-1,3,2,0};  check("LC456 c", s.find132pattern(c), true);
    }
    {   LC316::Solution s;
        check("LC316 a", s.removeDuplicateLetters("bcabc"),    string("abc"));
        check("LC316 b", s.removeDuplicateLetters("cbacdcbc"), string("acdb"));
    }
    {   LC1019::Solution s;
        auto make = [](vector<int> v) {
            ListNode *head = nullptr, *tail = nullptr;
            for (int x : v) {
                ListNode* n = new ListNode(x);
                if (tail) tail->next = n; else head = n;
                tail = n;
            }
            return head;
        };
        check("LC1019 a", s.nextLargerNodes(make({2,1,5})),     vector<int>{5,5,0});
        check("LC1019 b", s.nextLargerNodes(make({2,7,4,3,5})), vector<int>{7,0,5,5,0});
    }
    {   LC636::Solution s;
        vector<string> a{"0:start:0","1:start:2","1:end:5","0:end:6"};
        check("LC636 a", s.exclusiveTime(2, a), vector<int>{3,4});
        vector<string> b{"0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"};
        check("LC636 b", s.exclusiveTime(1, b), vector<int>{8});
    }
    {   LC895::FreqStack fs;
        for (int x : {5,7,5,7,4,5}) fs.push(x);
        vector<int> got{fs.pop(), fs.pop(), fs.pop(), fs.pop()};
        check("LC895 a", got, vector<int>{5,7,5,4});
    }
    {   LC862::Solution s;
        vector<int> a{1};              check("LC862 a", s.shortestSubarray(a, 1),    1);
        vector<int> b{1,2};            check("LC862 b", s.shortestSubarray(b, 4),   -1);
        vector<int> c{2,-1,2};         check("LC862 c", s.shortestSubarray(c, 3),    3);
        vector<int> d{84,-37,32,40,95};check("LC862 d", s.shortestSubarray(d, 167),  3);
    }
    {   LC1425::Solution s;
        vector<int> a{10,2,-10,5,20};   check("LC1425 a", s.constrainedSubsetSum(a, 2), 37);
        vector<int> b{-1,-2,-3};        check("LC1425 b", s.constrainedSubsetSum(b, 1), -1);
        vector<int> c{10,-2,-10,-5,20}; check("LC1425 c", s.constrainedSubsetSum(c, 2), 23);
    }

    cout << "\n----------------------------------------\n";
    cout << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}
