// ============================================================================
//  01_Arrays / practice / practice-01-basics.cpp
//
//  Ten TODOs covering Parts 0-8 of Arrays-Guide.pdf. Fill in each function;
//  the tests at the bottom check your work and tell you which one is wrong.
//
//  Build and run:
//      g++ -std=c++17 -O2 -Wall practice-01-basics.cpp -o practice && ./practice
//
//  Before you touch a loop, write the invariant comment: what does each index
//  MEAN? ("w is the next write slot", "l is the start of the window", ...)
//  Rules: no std::sort unless a TODO says so, and keep the stated space bound.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------
// TODO 1 — findMax
// Return the largest element. Return INT_MIN if the array is empty.
// Part 2.5: do NOT initialise the running max to 0.
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
int findMax(const vector<int>& v) {
    // TODO
    return 0;
}

// ---------------------------------------------------------------------------
// TODO 2 — reverseInPlace
// Reverse the array in place. Do not use std::reverse, and do not allocate.
// Part 3.1: two pointers, opposite ends.
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
void reverseInPlace(vector<int>& v) {
    // TODO
}

// ---------------------------------------------------------------------------
// TODO 3 — removeValue
// Remove every occurrence of val in place. Return the new length k; the first
// k slots must hold the survivors in their original order.
// Part 3.2: the write index.
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
int removeValue(vector<int>& v, int val) {
    // TODO
    return 0;
}

// ---------------------------------------------------------------------------
// TODO 4 — moveZeroes
// Move every 0 to the end, keeping the order of the non-zero elements.
// Part 3.2. O(n) time, O(1) space.
// ---------------------------------------------------------------------------
void moveZeroes(vector<int>& v) {
    // TODO
}

// ---------------------------------------------------------------------------
// TODO 5 — prefixSums
// Return P of length n+1 with P[0] = 0 and P[i] = v[0] + ... + v[i-1],
// so that sum(v[i..j]) == P[j+1] - P[i].
// Part 5.1. Use long long. O(n) time.
// ---------------------------------------------------------------------------
vector<long long> prefixSums(const vector<int>& v) {
    // TODO
    return {};
}

// ---------------------------------------------------------------------------
// TODO 6 — firstOccurrence
// v is sorted ascending. Return the index of the FIRST occurrence of target,
// or -1 if it is absent. Must be O(log n) — no linear scan, no std::find.
// Part 6.2: binary search template 2.
// ---------------------------------------------------------------------------
int firstOccurrence(const vector<int>& v, int target) {
    // TODO
    return -1;
}

// ---------------------------------------------------------------------------
// TODO 7 — maxSumWindow
// Return the largest sum of k consecutive elements. Return 0 if n < k or k <= 0.
// Part 4.1: roll the window, do not re-add k elements each step.
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
int maxSumWindow(const vector<int>& v, int k) {
    // TODO
    return 0;
}

// ---------------------------------------------------------------------------
// TODO 8 — maxSubarraySum
// Kadane. Largest sum of any contiguous subarray. The array is non-empty and
// MAY BE ALL NEGATIVE — in that case the answer is the largest single element.
// Part 8.1. O(n) time, O(1) space.
// ---------------------------------------------------------------------------
int maxSubarraySum(const vector<int>& v) {
    // TODO
    return 0;
}

// ---------------------------------------------------------------------------
// TODO 9 — rotateRight
// Rotate the array right by k steps, in place. k may be larger than n, and n
// may be 0. Do not allocate a second array.
// Part 8.4: three reversals (feel free to call your own reverseInPlace on
// sub-ranges, or write a helper that reverses v[a..b]).
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
void rotateRight(vector<int>& v, int k) {
    // TODO
}

// ---------------------------------------------------------------------------
// TODO 10 — sortColors
// v holds only 0s, 1s and 2s. Sort it in ONE pass, in place, without sorting.
// Part 3.3: Dutch national flag, three pointers.
// O(n) time, O(1) space.
// ---------------------------------------------------------------------------
void sortColors(vector<int>& v) {
    // TODO
}

// ============================== TESTS =======================================
// Do not edit below this line.
static int g_pass = 0, g_fail = 0;
static string g_current;

template <class T>
static void check(const string& what, const T& got, const T& want) {
    if (got == want) { g_pass++; return; }
    g_fail++;
    cout << "  FAIL  " << g_current << " : " << what << "\n";
}
static string show(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += to_string(v[i]); }
    return s + "]";
}
static void checkVec(const string& what, vector<int> got, vector<int> want) {
    if (got == want) { g_pass++; return; }
    g_fail++;
    cout << "  FAIL  " << g_current << " : " << what
         << "  got " << show(got) << " want " << show(want) << "\n";
}

int main() {
    cout << "practice-01-basics\n------------------\n";

    g_current = "TODO 1 findMax";
    { check<int>("normal",   findMax({3,1,4,1,5}), 5);
      check<int>("negatives", findMax({-7,-2,-9}), -2);
      check<int>("single",   findMax({42}), 42);
      check<int>("empty",    findMax({}), INT_MIN); }

    g_current = "TODO 2 reverseInPlace";
    { vector<int> a{1,2,3,4};   reverseInPlace(a); checkVec("even", a, {4,3,2,1});
      vector<int> b{1,2,3};     reverseInPlace(b); checkVec("odd",  b, {3,2,1});
      vector<int> c{9};         reverseInPlace(c); checkVec("one",  c, {9});
      vector<int> d;            reverseInPlace(d); checkVec("empty", d, {}); }

    g_current = "TODO 3 removeValue";
    { vector<int> a{3,2,2,3};  int k = removeValue(a, 3);
      check<int>("len", k, 2);
      checkVec("kept", vector<int>(a.begin(), a.begin() + min<int>(k, a.size())), {2,2});
      vector<int> b{1,1,1};    check<int>("all removed", removeValue(b, 1), 0);
      vector<int> c{1,2,3};    check<int>("none removed", removeValue(c, 9), 3);
      vector<int> d;           check<int>("empty", removeValue(d, 1), 0); }

    g_current = "TODO 4 moveZeroes";
    { vector<int> a{0,1,0,3,12}; moveZeroes(a); checkVec("order kept", a, {1,3,12,0,0});
      vector<int> b{0,0};        moveZeroes(b); checkVec("all zero", b, {0,0});
      vector<int> c{1,2,3};      moveZeroes(c); checkVec("no zero", c, {1,2,3});
      vector<int> d;             moveZeroes(d); checkVec("empty", d, {}); }

    g_current = "TODO 5 prefixSums";
    { vector<long long> p = prefixSums({3,1,4,1,5});
      check<vector<long long>>("values", p, {0,3,4,8,9,14});
      if (p.size() == 6) check<long long>("range v[1..3]", p[4] - p[1], 6);
      check<vector<long long>>("empty", prefixSums({}), {0}); }

    g_current = "TODO 6 firstOccurrence";
    { vector<int> v{5,7,7,8,8,10};
      check<int>("first of run", firstOccurrence(v, 8), 3);
      check<int>("single",       firstOccurrence(v, 5), 0);
      check<int>("last",         firstOccurrence(v, 10), 5);
      check<int>("absent",       firstOccurrence(v, 6), -1);
      check<int>("past end",     firstOccurrence(v, 99), -1);
      check<int>("empty",        firstOccurrence({}, 1), -1); }

    g_current = "TODO 7 maxSumWindow";
    { check<int>("normal", maxSumWindow({2,1,5,1,3,2}, 3), 9);
      check<int>("k == n", maxSumWindow({1,2,3}, 3), 6);
      check<int>("k > n",  maxSumWindow({1,2}, 5), 0);
      check<int>("negatives", maxSumWindow({-1,-2,-3,-4}, 2), -3); }

    g_current = "TODO 8 maxSubarraySum";
    { check<int>("mixed",    maxSubarraySum({-2,1,-3,4,-1,2,1,-5,4}), 6);
      check<int>("all neg",  maxSubarraySum({-3,-1,-2}), -1);
      check<int>("all pos",  maxSubarraySum({1,2,3}), 6);
      check<int>("single",   maxSubarraySum({-5}), -5); }

    g_current = "TODO 9 rotateRight";
    { vector<int> a{1,2,3,4,5,6,7}; rotateRight(a, 3); checkVec("k=3", a, {5,6,7,1,2,3,4});
      vector<int> b{1,2};           rotateRight(b, 5); checkVec("k > n", b, {2,1});
      vector<int> c{1,2,3};         rotateRight(c, 0); checkVec("k=0", c, {1,2,3});
      vector<int> d;                rotateRight(d, 3); checkVec("empty", d, {}); }

    g_current = "TODO 10 sortColors";
    { vector<int> a{2,0,2,1,1,0}; sortColors(a); checkVec("mixed", a, {0,0,1,1,2,2});
      vector<int> b{2,0,1};       sortColors(b); checkVec("one each", b, {0,1,2});
      vector<int> c{1,1,1};       sortColors(c); checkVec("all same", c, {1,1,1});
      vector<int> d;              sortColors(d); checkVec("empty", d, {}); }

    cout << "------------------\n" << g_pass << " passed, " << g_fail << " failed.\n";
    if (g_fail == 0) cout << "ALL TESTS PASSED — well done.\n";
    else cout << "Keep going. Fix the first failing TODO, rebuild, repeat.\n";
    return g_fail == 0 ? 0 : 1;
}
