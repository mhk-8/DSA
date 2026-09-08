// ============================================================================
//  Stacks & Queues — reference answers to practice/practice-01-basics.cpp
//
//      g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
//  Same tests as the practice file, all passing. Read this AFTER you have made
//  a real attempt at the practice file yourself.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------- 1
// A stack reverses whatever passes through it — that is the entire solution.
string reverseString(string s) {
    stack<char> st;
    for (char c : s) st.push(c);
    string out;
    while (!st.empty()) { out += st.top(); st.pop(); }
    return out;
}

// ---------------------------------------------------------------------- 2
// Three checks: empty before popping, the partner comparison, empty at the end.
bool isBalanced(string s) {
    unordered_map<char, char> match{{')', '('}, {']', '['}, {'}', '{'}};
    stack<char> st;
    for (char c : s) {
        if (!match.count(c)) st.push(c);                      // an opener
        else if (st.empty() || st.top() != match[c]) return false;
        else st.pop();
    }
    return st.empty();
}

// ---------------------------------------------------------------------- 3
// Push operands; on an operator pop two. The FIRST pop is the RIGHT operand.
int evalPostfix(vector<string>& tokens) {
    stack<long long> st;
    for (const string& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            long long b = st.top(); st.pop();          // right
            long long a = st.top(); st.pop();          // left
            if      (t == "+") st.push(a + b);
            else if (t == "-") st.push(a - b);
            else if (t == "*") st.push(a * b);
            else               st.push(a / b);
        } else st.push(stoll(t));
    }
    return (int)st.top();
}

// ---------------------------------------------------------------------- 4
// Monotonic stack of indices, values decreasing bottom -> top.
// The answer is read AT the moment of the pop.
vector<int> nextGreater(vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) { res[st.top()] = a[i]; st.pop(); }
        st.push(i);
    }
    return res;
}

// ---------------------------------------------------------------------- 5
// Same loop, increasing stack, but the answer is read AFTER popping.
vector<int> prevSmaller(vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        res[i] = st.empty() ? -1 : a[st.top()];
        st.push(i);
    }
    return res;
}

// ---------------------------------------------------------------------- 6
// Monotonic deque of indices: expire the front, dominate from the back, push.
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();       // 1. expire
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();    // 2. dominate
        dq.push_back(i);                                              // 3. push
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

// ---------------------------------------------------------------------- 7
// The call stack is the second container: `t` lives in a stack frame.
void insertAtBottom(stack<int>& st, int x) {
    if (st.empty()) { st.push(x); return; }
    int t = st.top(); st.pop();
    insertAtBottom(st, x);
    st.push(t);                       // put it back on the way out
}

// ---------------------------------------------------------------------- 8
// Pop everything down to the bottom, then reinsert each value AT the bottom.
void reverseStack(stack<int>& st) {
    if (st.empty()) return;
    int t = st.top(); st.pop();
    reverseStack(st);
    insertAtBottom(st, t);
}

// ---------------------------------------------------------------------- 9
// Shadow stack: mins.top() is always the minimum of everything in st.
// Pushing unconditionally keeps the two the same height, so pop() is one line.
class MinStack {
    stack<int> st, mins;
public:
    void push(int x) {
        st.push(x);
        mins.push(mins.empty() ? x : min(x, mins.top()));
    }
    void pop()    { st.pop(); mins.pop(); }
    int  top()    { return st.top(); }
    int  getMin() { return mins.top(); }
};

// --------------------------------------------------------------------- 10
// front + count. The rear is DERIVED, so full and empty can never look alike.
class CircularQueue {
    vector<int> data;
    int cap, front_ = 0, count = 0;
public:
    CircularQueue(int k) : data(k), cap(k) {}

    bool enqueue(int x) {
        if (isFull()) return false;
        data[(front_ + count) % cap] = x;
        count++;
        return true;
    }
    bool dequeue() {
        if (isEmpty()) return false;
        front_ = (front_ + 1) % cap;
        count--;
        return true;
    }
    int  front()   { return isEmpty() ? -1 : data[front_]; }
    int  rear()    { return isEmpty() ? -1 : data[(front_ + count - 1) % cap]; }
    bool isEmpty() { return count == 0; }
    bool isFull()  { return count == cap; }
};

// ============================================================================
//  TESTS — do not edit below this line
// ============================================================================
static int pass_ = 0, fail_ = 0;
static string show(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += to_string(v[i]); }
    return s + "]";
}
static void ck(const string& label, const string& got, const string& want) {
    if (got == want) { pass_++; cout << "ok   " << label << "\n"; }
    else { fail_++; cout << "FAIL " << label << "  got " << got << "  want " << want << "\n"; }
}
static void ck(const string& l, int g, int w)  { ck(l, to_string(g), to_string(w)); }
static void ck(const string& l, bool g, bool w){ ck(l, string(g?"true":"false"), string(w?"true":"false")); }
static void ck(const string& l, const vector<int>& g, const vector<int>& w) { ck(l, show(g), show(w)); }
static vector<int> drain(stack<int> st) { vector<int> v; while (!st.empty()) { v.push_back(st.top()); st.pop(); } return v; }

int main() {
    cout << "--- TODO 1: reverseString ---\n";
    ck("reverse hello", reverseString("hello"), string("olleh"));
    ck("reverse empty", reverseString(""),      string(""));
    ck("reverse ab",    reverseString("ab"),    string("ba"));

    cout << "--- TODO 2: isBalanced ---\n";
    ck("balanced ([]{})",   isBalanced("([]{})"), true);
    ck("balanced ()[]{}",   isBalanced("()[]{}"), true);
    ck("balanced ([)]",     isBalanced("([)]"),   false);
    ck("balanced ((",       isBalanced("(("),     false);
    ck("balanced )(",       isBalanced(")("),     false);
    ck("balanced empty",    isBalanced(""),       true);

    cout << "--- TODO 3: evalPostfix ---\n";
    { vector<string> t{"2","1","+","3","*"};   ck("postfix 9",  evalPostfix(t),  9); }
    { vector<string> t{"3","4","-"};           ck("postfix -1", evalPostfix(t), -1); }
    { vector<string> t{"4","13","5","/","+"};  ck("postfix 6",  evalPostfix(t),  6); }

    cout << "--- TODO 4: nextGreater ---\n";
    { vector<int> a{2,1,2,4,3};  ck("nextGreater a", nextGreater(a), vector<int>{4,2,4,-1,-1}); }
    { vector<int> a{5,4,3};      ck("nextGreater b", nextGreater(a), vector<int>{-1,-1,-1}); }
    { vector<int> a{1,2,3};      ck("nextGreater c", nextGreater(a), vector<int>{2,3,-1}); }

    cout << "--- TODO 5: prevSmaller ---\n";
    { vector<int> a{4,5,2,10,8}; ck("prevSmaller a", prevSmaller(a), vector<int>{-1,4,-1,2,2}); }
    { vector<int> a{1,2,3};      ck("prevSmaller b", prevSmaller(a), vector<int>{-1,1,2}); }
    { vector<int> a{3,2,1};      ck("prevSmaller c", prevSmaller(a), vector<int>{-1,-1,-1}); }

    cout << "--- TODO 6: maxSlidingWindow ---\n";
    { vector<int> a{1,3,-1,-3,5,3,6,7}; ck("window a", maxSlidingWindow(a,3), vector<int>{3,3,5,5,6,7}); }
    { vector<int> a{7,2,4};             ck("window b", maxSlidingWindow(a,2), vector<int>{7,4}); }
    { vector<int> a{9};                 ck("window c", maxSlidingWindow(a,1), vector<int>{9}); }

    cout << "--- TODO 7: insertAtBottom ---\n";
    { stack<int> st; st.push(1); st.push(2); st.push(3); insertAtBottom(st, 0);
      ck("insertAtBottom", drain(st), vector<int>{3,2,1,0}); }
    { stack<int> st; insertAtBottom(st, 5);
      ck("insertAtBottom empty", drain(st), vector<int>{5}); }

    cout << "--- TODO 8: reverseStack ---\n";
    { stack<int> st; st.push(1); st.push(2); st.push(3); reverseStack(st);
      ck("reverseStack", drain(st), vector<int>{1,2,3}); }
    { stack<int> st; st.push(7); reverseStack(st);
      ck("reverseStack one", drain(st), vector<int>{7}); }

    cout << "--- TODO 9: MinStack ---\n";
    { MinStack m; m.push(-2); m.push(0); m.push(-3);
      ck("MinStack min1", m.getMin(), -3);
      m.pop();
      ck("MinStack top",  m.top(),     0);
      ck("MinStack min2", m.getMin(), -2);
      m.push(-2);
      ck("MinStack dup",  m.getMin(), -2);
      m.pop();
      ck("MinStack min3", m.getMin(), -2); }

    cout << "--- TODO 10: CircularQueue ---\n";
    { CircularQueue q(3);
      ck("CQ enq1", q.enqueue(1), true);
      ck("CQ enq2", q.enqueue(2), true);
      ck("CQ enq3", q.enqueue(3), true);
      ck("CQ full", q.enqueue(4), false);
      ck("CQ rear", q.rear(),     3);
      ck("CQ isFull", q.isFull(), true);
      ck("CQ deq",  q.dequeue(),  true);
      ck("CQ wrap", q.enqueue(4), true);
      ck("CQ rear2",q.rear(),     4);
      ck("CQ front",q.front(),    2);
      ck("CQ empty",q.isEmpty(),  false); }
    { CircularQueue q(1);
      ck("CQ1 empty", q.isEmpty(), true);
      ck("CQ1 front", q.front(),  -1);
      ck("CQ1 deq",   q.dequeue(), false); }

    cout << "\n----------------------------------------\n";
    cout << pass_ << " passed, " << fail_ << " failed\n";
    if (fail_ == 0) cout << "All tests pass. Move on to the problem list in Part 11.\n";
    return fail_ == 0 ? 0 : 1;
}
