// ============================================================================
//  Stacks & Queues — Practice 01: the basics
//
//  Fill in the TODOs. Do NOT look at solutions/reference-basics.cpp until you
//  have made a real attempt at each one. The tests are self-checking:
//
//      g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
//  Every test prints "ok" or "FAIL". Against the empty stubs everything fails —
//  that is the point. Work down the list until they all pass.
//
//  Suggested order: 1-3 first (the mechanics), then 4-6 (monotonic), then
//  7-8 (recursion on a stack), then 9-10 (design).
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  TODO 1 — Reverse a string using a stack.
//  "hello" -> "olleh".   Use a stack; do not use std::reverse.
//  Hint: a stack reverses whatever passes through it. That is its whole nature.
// ============================================================================
string reverseString(string s) {
    // TODO
    return s;
}

// ============================================================================
//  TODO 2 — Balanced brackets, all three types: ()  []  {}
//  "([]{})" -> true      "([)]" -> false      "((" -> false      ")(" -> false
//  Remember the THREE checks: empty before popping, the partner comparison,
//  and empty at the end. Dropping any one of them is a wrong answer.
// ============================================================================
bool isBalanced(string s) {
    // TODO
    return false;
}

// ============================================================================
//  TODO 3 — Evaluate a postfix (reverse Polish) expression.
//  {"2","1","+","3","*"} -> 9        {"3","4","-"} -> -1
//  Tokens are integers or one of + - * / . Division truncates toward zero.
//  WATCH OUT: the first value you pop is the RIGHT operand.
// ============================================================================
int evalPostfix(vector<string>& tokens) {
    // TODO
    return 0;
}

// ============================================================================
//  TODO 4 — Next greater element to the right, for every index.
//  Return the VALUE, or -1 if there is none.
//  [2,1,2,4,3] -> [4,2,4,-1,-1]
//  Monotonic stack. Push indices; keep values decreasing bottom -> top.
// ============================================================================
vector<int> nextGreater(vector<int>& a) {
    // TODO
    return vector<int>(a.size(), -1);
}

// ============================================================================
//  TODO 5 — Previous smaller element to the left, for every index.
//  Return the VALUE, or -1 if there is none.
//  [4,5,2,10,8] -> [-1,4,-1,2,2]
//  Same loop as TODO 4, but you read the answer AFTER popping, from st.top().
// ============================================================================
vector<int> prevSmaller(vector<int>& a) {
    // TODO
    return vector<int>(a.size(), -1);
}

// ============================================================================
//  TODO 6 — Maximum of every window of size k.
//  a=[1,3,-1,-3,5,3,6,7], k=3 -> [3,3,5,5,6,7]
//  Monotonic DEQUE of indices. Three steps per index, in this order:
//     1. expire the front if it has slid out of the window
//     2. pop from the back while a[back] <= a[i]
//     3. push i, and once i >= k-1 record a[front]
// ============================================================================
vector<int> maxSlidingWindow(vector<int>& a, int k) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 7 — Insert x at the BOTTOM of a stack, using recursion only.
//  st = [1,2,3] (3 on top), insertAtBottom(st, 0) -> [0,1,2,3]
//  No second container. Hold the popped value in a local variable — the call
//  stack is your second container.
// ============================================================================
void insertAtBottom(stack<int>& st, int x) {
    // TODO
}

// ============================================================================
//  TODO 8 — Reverse a stack using recursion only (you may call TODO 7).
//  [1,2,3] with 3 on top -> [3,2,1] with 1 on top.
// ============================================================================
void reverseStack(stack<int>& st) {
    // TODO
}

// ============================================================================
//  TODO 9 — A stack that also answers getMin() in O(1).
//  Hint: a second, "shadow" stack whose top is always the minimum of everything
//  currently in the main stack. Push onto it on EVERY push, so the two stay the
//  same height and pop() is a single line.
// ============================================================================
class MinStack {
    // TODO: your data members
public:
    void push(int x) {
        // TODO
        (void)x;
    }
    void pop() {
        // TODO
    }
    int top() {
        // TODO
        return 0;
    }
    int getMin() {
        // TODO
        return 0;
    }
};

// ============================================================================
//  TODO 10 — A fixed-capacity queue on a circular array.
//  enqueue/dequeue return false when the queue is full/empty.
//  front() and rear() return -1 when empty.
//  Hint: store `front` and `count`; DERIVE the rear as (front + count) % cap.
//  Keeping a count is what removes the full-versus-empty ambiguity.
// ============================================================================
class CircularQueue {
    // TODO: your data members
public:
    CircularQueue(int k) {
        // TODO
        (void)k;
    }
    bool enqueue(int x) {
        // TODO
        (void)x;
        return false;
    }
    bool dequeue() {
        // TODO
        return false;
    }
    int front() {
        // TODO
        return -1;
    }
    int rear() {
        // TODO
        return -1;
    }
    bool isEmpty() {
        // TODO
        return true;
    }
    bool isFull() {
        // TODO
        return false;
    }
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
