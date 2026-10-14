// ============================================================================
//  Searching & Sorting — Practice 01: the basics
//
//  Fill in the TODOs. Do NOT look at solutions/reference-basics.cpp until you
//  have made a real attempt at each one. The tests are self-checking:
//
//      g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
//  Every test prints "ok" or "FAIL". Against the empty stubs almost everything
//  fails — that is the point. Work down the list until they all pass.
//
//  RULE: no std::sort, std::stable_sort, lower_bound or upper_bound anywhere in
//  your answers. These are the algorithms written rounds ask you to write.
//
//  Suggested order: 1-3 (the elementary sorts), 4-6 (divide and conquer),
//  7 (non-comparison), then 8-10 (binary search).
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  TODO 1 — Bubble sort, ascending, with the EARLY EXIT: if a whole pass makes
//  no swap, the array is sorted — stop. (That makes sorted input O(n).)
//  After pass i, the largest i+1 values are in their final places at the end.
// ============================================================================
void bubbleSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 2 — Selection sort: for each position i, find the minimum of a[i..n-1]
//  and swap it into position i. Exactly n-1 swaps at most — its one virtue.
// ============================================================================
void selectionSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 3 — Insertion sort: a[0..i-1] is sorted; take key = a[i] and shift the
//  larger elements one place right until key's slot is found.
//  Use `>` (not `>=`) when shifting, so equal elements keep their order (stable).
// ============================================================================
void insertionSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 4 — Merge sort, ascending, O(n log n). Write a helper
//  mergeSort(a, lo, hi, tmp) and merge two sorted halves with two pointers.
//  Use `<=` when taking from the left half, so the sort is stable.
// ============================================================================
void mergeSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 5 — Count inversions: pairs i < j with a[i] > a[j]. O(n log n).
//  {2,4,1,3,5} -> 3   ((2,1), (4,1), (4,3))
//  Hint: in merge sort's merge step, when you take an element from the RIGHT
//  half, every element still waiting in the left half is greater than it.
//  Return long long — n = 10^5 reverse-sorted gives about 5 * 10^9.
// ============================================================================
long long countInversions(vector<int> a) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 6 — Quick sort, ascending. Lomuto partition with the LAST element as
//  pivot is fine; a random pivot is better. Recurse on both sides of the pivot.
//  Partition invariant (Lomuto): a[lo..i-1] < pivot, a[i..j-1] >= pivot.
// ============================================================================
void quickSort(vector<int>& a) {
    // TODO
}

// ============================================================================
//  TODO 7 — Counting sort for values in 0..maxVal. O(n + maxVal), no compares.
//  {4,2,2,8,3,3,1}, maxVal 9 -> {1,2,2,3,3,4,8}
// ============================================================================
vector<int> countingSort(vector<int> a, int maxVal) {
    // TODO
    return a;
}

// ============================================================================
//  TODO 8 — How many times does x occur in the SORTED array a? O(log n).
//  Write lowerBound (first index with a[i] >= x) and upperBound (first index
//  with a[i] > x) yourself, half-open [lo, hi), and return the difference.
// ============================================================================
int countOccurrences(const vector<int>& a, int x) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 9 — Search a sorted array of DISTINCT values that was rotated
//  ({0,1,2,4,5,6,7} -> {4,5,6,7,0,1,2}). Return the index of target or -1.
//  O(log n). At every mid, ONE of the two halves is sorted — find out which,
//  then check whether target lies inside that sorted half.
// ============================================================================
int searchRotated(const vector<int>& a, int target) {
    // TODO
    return -2;
}

// ============================================================================
//  TODO 10 — Aggressive cows (GfG / SPOJ classic). Place `cows` cows in the
//  stalls (positions, unsorted) to MAXIMISE the minimum distance between any
//  two cows. Return that distance.   {1,2,4,8,9}, 3 cows -> 3
//  Binary search on the ANSWER d: "can I place all cows at least d apart?"
//  is true for small d and false for large d. Check it greedily after sorting.
//  (Sorting the stalls with your own mergeSort keeps the no-std::sort rule.)
// ============================================================================
int aggressiveCows(vector<int> stalls, int cows) {
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
static void ck(const string& label, const string& got, const string& want) {
    if (got == want) { pass_++; cout << "ok   " << label << "\n"; }
    else { fail_++; cout << "FAIL " << label << "\n     got  " << got << "\n     want " << want << "\n"; }
}
static void ck(const string& l, long long g, long long w) { ck(l, to_string(g), to_string(w)); }
static void ck(const string& l, const vector<int>& g, const vector<int>& w) { ck(l, show(g), show(w)); }
static vector<int> srt(vector<int> v) { sort(v.begin(), v.end()); return v; }

// every sort is checked on the same inputs, including the awkward ones
static void checkSort(const string& name, void (*f)(vector<int>&)) {
    vector<vector<int>> cases{{5,2,9,1,5,6}, {}, {7}, {1,2,3,4,5}, {5,4,3,2,1},
                              {3,3,3}, {-2,7,0,-9,4,4,1}, {2,1}};
    for (size_t i = 0; i < cases.size(); i++) {
        vector<int> v = cases[i];
        f(v);
        ck(name + " case " + to_string(i), v, srt(cases[i]));
    }
}

int main() {
    cout << "--- TODO 1: bubbleSort ---\n";     checkSort("bubble", bubbleSort);
    cout << "--- TODO 2: selectionSort ---\n";  checkSort("selection", selectionSort);
    cout << "--- TODO 3: insertionSort ---\n";  checkSort("insertion", insertionSort);
    cout << "--- TODO 4: mergeSort ---\n";      checkSort("merge", mergeSort);

    cout << "--- TODO 5: countInversions ---\n";
    { vector<int> a{2,4,1,3,5}; ck("inv a", countInversions(a), 3LL); }
    { vector<int> a{5,4,3,2,1}; ck("inv b", countInversions(a), 10LL); }
    { vector<int> a{1,2,3};     ck("inv c", countInversions(a), 0LL); }
    { vector<int> a{2,2,1};     ck("inv d", countInversions(a), 2LL); }   // equal values are NOT inversions

    cout << "--- TODO 6: quickSort ---\n";      checkSort("quick", quickSort);

    cout << "--- TODO 7: countingSort ---\n";
    { vector<int> a{4,2,2,8,3,3,1}; ck("count a", countingSort(a, 9), vector<int>{1,2,2,3,3,4,8}); }
    { vector<int> a{0,0,0};         ck("count b", countingSort(a, 0), vector<int>{0,0,0}); }
    { vector<int> a{};              ck("count c", countingSort(a, 5), vector<int>{}); }

    cout << "--- TODO 8: countOccurrences ---\n";
    { vector<int> a{1,1,2,2,2,2,3}; ck("occ a", (long long)countOccurrences(a, 2), 4LL); }
    { vector<int> a{1,1,2,2,2,2,3}; ck("occ b", (long long)countOccurrences(a, 4), 0LL); }
    { vector<int> a{1,1,2,2,2,2,3}; ck("occ c", (long long)countOccurrences(a, 0), 0LL); }
    { vector<int> a{5};             ck("occ d", (long long)countOccurrences(a, 5), 1LL); }
    { vector<int> a{};              ck("occ e", (long long)countOccurrences(a, 5), 0LL); }

    cout << "--- TODO 9: searchRotated ---\n";
    { vector<int> a{4,5,6,7,0,1,2}; ck("rot a", (long long)searchRotated(a, 0), 4LL); }
    { vector<int> a{4,5,6,7,0,1,2}; ck("rot b", (long long)searchRotated(a, 3), -1LL); }
    { vector<int> a{4,5,6,7,0,1,2}; ck("rot c", (long long)searchRotated(a, 7), 3LL); }
    { vector<int> a{1};             ck("rot d", (long long)searchRotated(a, 1), 0LL); }
    { vector<int> a{3,1};           ck("rot e", (long long)searchRotated(a, 1), 1LL); }

    cout << "--- TODO 10: aggressiveCows ---\n";
    { vector<int> a{1,2,4,8,9};     ck("cows a", (long long)aggressiveCows(a, 3), 3LL); }
    { vector<int> a{10,1,2,7,5};    ck("cows b", (long long)aggressiveCows(a, 3), 4LL); }
    { vector<int> a{2,12,11,3,26,7}; ck("cows c", (long long)aggressiveCows(a, 5), 1LL); }
    { vector<int> a{0,1000000000};  ck("cows d", (long long)aggressiveCows(a, 2), 1000000000LL); }

    cout << "\n----------------------------------------\n";
    cout << pass_ << " passed, " << fail_ << " failed\n";
    if (fail_ == 0) cout << "All tests pass. Move on to the problem list in Part 13.\n";
    return fail_ == 0 ? 0 : 1;
}
