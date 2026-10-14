// ============================================================================
//  Heaps & Priority Queues — Practice 01: the basics
//
//  Fill in the TODOs. Do NOT look at solutions/reference-basics.cpp until you
//  have made a real attempt at each one. The tests are self-checking:
//
//      g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
//  Every test prints "ok" or "FAIL". Against the empty stubs almost everything
//  fails — that is the point. Work down the list until they all pass.
//
//  Suggested order: 1-6 first, WITHOUT std::priority_queue — you are building
//  the heap yourself, on a plain vector. Then 7-10 with the STL.
//
//  The three index formulas, for a 0-indexed array:
//      parent(i) = (i - 1) / 2      left(i) = 2*i + 1      right(i) = 2*i + 2
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  TODO 1 — Is the array a valid MAX-heap?
//  {90,15,10,7,12,2} -> true      {9,15,10,7,12,11} -> false
//  Hint: every non-root i must satisfy a[parent(i)] >= a[i]. One loop.
// ============================================================================
bool isMaxHeap(const vector<int>& a) {
    // TODO
    return false;
}

// ============================================================================
//  TODO 2 — siftUp: the element at index i may be bigger than its parent.
//  Swap it upward until the heap property holds again.
//  {10,5,8,2,12}, i=4 -> {12,10,8,2,5}
//  This is what push() does after appending at the end.
// ============================================================================
void siftUp(vector<int>& a, int i) {
    // TODO
}

// ============================================================================
//  TODO 3 — siftDown: the element at index i may be smaller than a child.
//  Swap it with its LARGER child until the heap property holds again.
//  Only indices < n are part of the heap (heap sort needs this).
//  {1,9,8,5,6}, n=5, i=0 -> {9,6,8,5,1}
//  Careful: the right child may not exist. Check both children against n.
// ============================================================================
void siftDown(vector<int>& a, int n, int i) {
    // TODO
}

// ============================================================================
//  TODO 4 — A max-heap class, on a vector, using TODO 2 and TODO 3.
//    push: append, then siftUp the last index.
//    pop:  move the LAST element to the root, shrink, then siftDown the root.
//    top:  a[0].
//  Do not use std::priority_queue or std::push_heap here.
// ============================================================================
class MaxHeap {
    vector<int> a;
public:
    void push(int x) {
        // TODO
    }
    void pop() {
        // TODO
    }
    int top() const {
        // TODO
        return -1;
    }
    int size() const { return a.size(); }
    bool empty() const { return a.empty(); }
};

// ============================================================================
//  TODO 5 — Turn an arbitrary array into a max-heap IN PLACE, in O(n).
//  Do not push elements one by one (that is O(n log n)).
//  Hint: leaves are already heaps. siftDown every internal node, from the
//  LAST internal node (n/2 - 1) back to the root.
// ============================================================================
void buildMaxHeap(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 6 — Heap sort, ascending, in place, O(n log n), O(1) extra space.
//  Build a max-heap. Then repeatedly swap the root (the max) with the last
//  element of the heap, shrink the heap by one, and siftDown the root.
// ============================================================================
void heapSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  From here on, use std::priority_queue.
// ============================================================================

// ============================================================================
//  TODO 7 — k-th largest element.  {3,2,1,5,6,4}, k=2 -> 5
//  Keep a MIN-heap of size k. Its top is the k-th largest.
//  (Yes, MIN-heap for the LARGEST elements. Work out why before coding.)
// ============================================================================
int kthLargest(vector<int>& nums, int k) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 8 — Connect ropes (GfG classic). Joining ropes of length a and b
//  costs a + b and produces a rope of length a + b. Join all ropes into one
//  at minimum total cost.   {4,3,2,6} -> 29
//  Greedy: always join the two SHORTEST ropes. Return long long.
// ============================================================================
long long connectRopes(vector<int>& ropes) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 9 — Sort a k-sorted array: every element is at most k positions away
//  from where it belongs.   {6,5,3,2,8,10,9}, k=3 -> {2,3,5,6,8,9,10}
//  Do it in O(n log k): a min-heap of size k+1 always contains the next
//  element of the sorted output.
// ============================================================================
vector<int> sortKSorted(vector<int>& a, int k) {
    // TODO
    return a;
}

// ============================================================================
//  TODO 10 — Running median. addNum adds a number; findMedian returns the
//  median of everything added so far.
//  Two heaps: a MAX-heap for the smaller half, a MIN-heap for the larger half.
//  Keep their sizes equal, or the max-heap one bigger.
// ============================================================================
class MedianFinder {
public:
    void addNum(int num) {
        // TODO
    }
    double findMedian() {
        // TODO
        return 0.0;
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
    else { fail_++; cout << "FAIL " << label << "\n     got  " << got << "\n     want " << want << "\n"; }
}
static void ck(const string& l, long long g, long long w) { ck(l, to_string(g), to_string(w)); }
static void ck(const string& l, bool g, bool w) { ck(l, string(g ? "true" : "false"), string(w ? "true" : "false")); }
static void ck(const string& l, double g, double w) {
    ostringstream a, b; a << fixed << setprecision(2) << g; b << fixed << setprecision(2) << w;
    ck(l, a.str(), b.str());
}
static void ck(const string& l, const vector<int>& g, const vector<int>& w) { ck(l, show(g), show(w)); }
// an independent checker, so TODO 5 can be tested even before TODO 1 is done
static bool heapOK(const vector<int>& a) {
    for (size_t i = 1; i < a.size(); i++) if (a[(i - 1) / 2] < a[i]) return false;
    return true;
}
static vector<int> srt(vector<int> v) { sort(v.begin(), v.end()); return v; }

int main() {
    cout << "--- TODO 1: isMaxHeap ---\n";
    ck("isMaxHeap yes",   isMaxHeap({90,15,10,7,12,2}), true);
    ck("isMaxHeap no",    isMaxHeap({9,15,10,7,12,11}), false);
    ck("isMaxHeap empty", isMaxHeap({}),                true);
    ck("isMaxHeap one",   isMaxHeap({4}),               true);
    ck("isMaxHeap equal", isMaxHeap({5,5,5}),           true);

    cout << "--- TODO 2: siftUp ---\n";
    { vector<int> a{10,5,8,2,12}; siftUp(a, 4);  ck("siftUp to root", a, vector<int>{12,10,8,2,5}); }
    { vector<int> a{10,5,8,2,3};  siftUp(a, 4);  ck("siftUp stays",   a, vector<int>{10,5,8,2,3}); }

    cout << "--- TODO 3: siftDown ---\n";
    { vector<int> a{1,9,8,5,6};   siftDown(a, 5, 0); ck("siftDown two levels", a, vector<int>{9,6,8,5,1}); }
    { vector<int> a{3,9,8,5,6};   siftDown(a, 2, 0); ck("siftDown respects n", a, vector<int>{9,3,8,5,6}); }
    { vector<int> a{9,4,7};       siftDown(a, 3, 0); ck("siftDown stays",      a, vector<int>{9,4,7}); }

    cout << "--- TODO 4: MaxHeap ---\n";
    { MaxHeap h;
      ck("MaxHeap empty", h.empty(), true);
      for (int x : {3,1,4,1,5,9,2,6}) h.push(x);
      ck("MaxHeap size", (long long)h.size(), 8LL);
      ck("MaxHeap top",  (long long)h.top(),  9LL);
      vector<int> out;
      while (!h.empty()) { out.push_back(h.top()); h.pop(); }
      ck("MaxHeap order", out, vector<int>{9,6,5,4,3,2,1,1}); }

    cout << "--- TODO 5: buildMaxHeap ---\n";
    { vector<int> a{1,3,5,4,6,13,10,9,8,15,17}; buildMaxHeap(a);
      ck("build is heap", heapOK(a), true);
      ck("build same values", srt(a), vector<int>{1,3,4,5,6,8,9,10,13,15,17});
      ck("build root", (long long)(a.empty() ? 0 : a[0]), 17LL); }
    { vector<int> a{}; buildMaxHeap(a); ck("build empty", heapOK(a), true); }

    cout << "--- TODO 6: heapSort ---\n";
    { vector<int> a{5,2,9,1,5,6}; heapSort(a); ck("heapSort a", a, vector<int>{1,2,5,5,6,9}); }
    { vector<int> a{3,-1,2};      heapSort(a); ck("heapSort b", a, vector<int>{-1,2,3}); }
    { vector<int> a{7};           heapSort(a); ck("heapSort one", a, vector<int>{7}); }

    cout << "--- TODO 7: kthLargest ---\n";
    { vector<int> a{3,2,1,5,6,4};       ck("kth 2", (long long)kthLargest(a, 2), 5LL); }
    { vector<int> a{3,2,3,1,2,4,5,5,6}; ck("kth 4", (long long)kthLargest(a, 4), 4LL); }
    { vector<int> a{7};                 ck("kth 1", (long long)kthLargest(a, 1), 7LL); }

    cout << "--- TODO 8: connectRopes ---\n";
    { vector<int> a{4,3,2,6};   ck("ropes a", connectRopes(a), 29LL); }
    { vector<int> a{1,2,3,4,5}; ck("ropes b", connectRopes(a), 33LL); }
    { vector<int> a{5};         ck("ropes one", connectRopes(a), 0LL); }

    cout << "--- TODO 9: sortKSorted ---\n";
    { vector<int> a{6,5,3,2,8,10,9}; ck("ksorted a", sortKSorted(a, 3), vector<int>{2,3,5,6,8,9,10}); }
    { vector<int> a{2,1,4,3,6,5};    ck("ksorted b", sortKSorted(a, 1), vector<int>{1,2,3,4,5,6}); }
    { vector<int> a{1,2,3};          ck("ksorted c", sortKSorted(a, 0), vector<int>{1,2,3}); }

    cout << "--- TODO 10: MedianFinder ---\n";
    { MedianFinder m;
      m.addNum(5);  ck("median 1", m.findMedian(), 5.0);
      m.addNum(15); ck("median 2", m.findMedian(), 10.0);
      m.addNum(1);  ck("median 3", m.findMedian(), 5.0);
      m.addNum(3);  ck("median 4", m.findMedian(), 4.0);
      m.addNum(-2); ck("median 5", m.findMedian(), 3.0); }

    cout << "\n----------------------------------------\n";
    cout << pass_ << " passed, " << fail_ << " failed\n";
    if (fail_ == 0) cout << "All tests pass. Move on to the problem list in Part 13.\n";
    return fail_ == 0 ? 0 : 1;
}
