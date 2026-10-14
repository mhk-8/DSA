// ============================================================================
//  Heaps & Priority Queues — reference answers to practice/practice-01-basics.cpp
//
//      g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
//  Same tests as the practice file, all passing. Read this AFTER you have made
//  a real attempt at the practice file yourself.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------- 1
bool isMaxHeap(const vector<int>& a) {
    for (size_t i = 1; i < a.size(); i++)
        if (a[(i - 1) / 2] < a[i]) return false;     // a child beats its parent
    return true;
}

// ---------------------------------------------------------------------- 2
// Climb while bigger than the parent. At most log n swaps.
void siftUp(vector<int>& a, int i) {
    while (i > 0 && a[(i - 1) / 2] < a[i]) {
        swap(a[(i - 1) / 2], a[i]);
        i = (i - 1) / 2;
    }
}

// ---------------------------------------------------------------------- 3
// Sink while smaller than the LARGER child. Children only count if < n.
void siftDown(vector<int>& a, int n, int i) {
    while (true) {
        int largest = i, l = 2 * i + 1, r = 2 * i + 2;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest == i) return;                    // heap property holds
        swap(a[i], a[largest]);
        i = largest;
    }
}

// ---------------------------------------------------------------------- 4
class MaxHeap {
    vector<int> a;
public:
    void push(int x) {
        a.push_back(x);                              // the only free slot: the end
        siftUp(a, (int)a.size() - 1);
    }
    void pop() {
        a[0] = a.back();                             // the last leaf fills the hole
        a.pop_back();
        if (!a.empty()) siftDown(a, (int)a.size(), 0);
    }
    int top() const { return a[0]; }
    int size() const { return a.size(); }
    bool empty() const { return a.empty(); }
};

// ---------------------------------------------------------------------- 5
// O(n): most nodes are near the bottom and sift down only a level or two.
void buildMaxHeap(vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(a, n, i);
}

// ---------------------------------------------------------------------- 6
void heapSort(vector<int>& a) {
    buildMaxHeap(a);
    for (int end = (int)a.size() - 1; end > 0; end--) {
        swap(a[0], a[end]);                          // the max goes to its final slot
        siftDown(a, end, 0);                         // heap is now a[0..end-1]
    }
}

// ---------------------------------------------------------------------- 7
// A min-heap of the k largest seen so far: its top is the weakest of them.
int kthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int x : nums) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    return pq.top();
}

// ---------------------------------------------------------------------- 8
long long connectRopes(vector<int>& ropes) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(ropes.begin(), ropes.end());
    long long cost = 0;
    while (pq.size() > 1) {
        long long a = pq.top(); pq.pop();
        long long b = pq.top(); pq.pop();
        cost += a + b;
        pq.push(a + b);                              // the new rope can be joined again
    }
    return cost;
}

// ---------------------------------------------------------------------- 9
// The smallest remaining element is always within the next k+1 positions.
vector<int> sortKSorted(vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> out;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) { out.push_back(pq.top()); pq.pop(); }
    }
    while (!pq.empty()) { out.push_back(pq.top()); pq.pop(); }
    return out;
}

// ---------------------------------------------------------------------- 10
class MedianFinder {
    priority_queue<int> lo;                              // smaller half, max on top
    priority_queue<int, vector<int>, greater<int>> hi;   // larger half, min on top
public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top()); lo.pop();                     // keep every lo <= every hi
        if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + (double)hi.top()) / 2.0;
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
