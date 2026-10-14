// ============================================================================
//  Searching & Sorting — reference answers to practice/practice-01-basics.cpp
//
//      g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
//  Same tests as the practice file, all passing. Read this AFTER you have made
//  a real attempt at the practice file yourself.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------- 1
void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int pass = 0; pass + 1 < n; pass++) {
        bool swapped = false;
        for (int j = 0; j + 1 < n - pass; j++)       // the last `pass` are already final
            if (a[j] > a[j + 1]) { swap(a[j], a[j + 1]); swapped = true; }
        if (!swapped) return;                        // early exit: already sorted
    }
}

// ---------------------------------------------------------------------- 2
void selectionSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i + 1 < n; i++) {
        int mn = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[mn]) mn = j;
        swap(a[i], a[mn]);                           // one swap per position
    }
}

// ---------------------------------------------------------------------- 3
void insertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }   // '>' keeps it stable
        a[j + 1] = key;
    }
}

// ---------------------------------------------------------------------- 4 and 5
// One merge routine serves both: it sorts, and counts cross inversions.
static long long mergeCount(vector<int>& a, int lo, int hi, vector<int>& tmp) {
    if (lo >= hi) return 0;
    int mid = lo + (hi - lo) / 2;
    long long inv = mergeCount(a, lo, mid, tmp) + mergeCount(a, mid + 1, hi, tmp);
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];         // '<=' : stable, and equal is not inverted
        else { inv += mid - i + 1; tmp[k++] = a[j++]; }   // a[i..mid] all exceed a[j]
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= hi)  tmp[k++] = a[j++];
    for (k = lo; k <= hi; k++) a[k] = tmp[k];
    return inv;
}
void mergeSort(vector<int>& a) {
    vector<int> tmp(a.size());
    mergeCount(a, 0, (int)a.size() - 1, tmp);
}
long long countInversions(vector<int> a) {
    vector<int> tmp(a.size());
    return mergeCount(a, 0, (int)a.size() - 1, tmp);
}

// ---------------------------------------------------------------------- 6
static void quickSortRange(vector<int>& a, int lo, int hi) {
    if (lo >= hi) return;
    swap(a[lo + rand() % (hi - lo + 1)], a[hi]);     // random pivot, moved to the end
    int pivot = a[hi], i = lo;
    for (int j = lo; j < hi; j++)                    // Lomuto: a[lo..i-1] < pivot
        if (a[j] < pivot) swap(a[i++], a[j]);
    swap(a[i], a[hi]);                               // pivot to its final index i
    quickSortRange(a, lo, i - 1);
    quickSortRange(a, i + 1, hi);
}
void quickSort(vector<int>& a) { quickSortRange(a, 0, (int)a.size() - 1); }

// ---------------------------------------------------------------------- 7
vector<int> countingSort(vector<int> a, int maxVal) {
    vector<int> cnt(maxVal + 1, 0);
    for (int x : a) cnt[x]++;
    vector<int> out;
    out.reserve(a.size());
    for (int v = 0; v <= maxVal; v++) out.insert(out.end(), cnt[v], v);
    return out;
}

// ---------------------------------------------------------------------- 8
static int lowerB(const vector<int>& a, int x) {     // first index with a[i] >= x
    int lo = 0, hi = a.size();
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (a[mid] < x) lo = mid + 1; else hi = mid; }
    return lo;
}
static int upperB(const vector<int>& a, int x) {     // first index with a[i] > x
    int lo = 0, hi = a.size();
    while (lo < hi) { int mid = lo + (hi - lo) / 2; if (a[mid] <= x) lo = mid + 1; else hi = mid; }
    return lo;
}
int countOccurrences(const vector<int>& a, int x) { return upperB(a, x) - lowerB(a, x); }

// ---------------------------------------------------------------------- 9
int searchRotated(const vector<int>& a, int target) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[lo] <= a[mid]) {                       // left half sorted
            if (a[lo] <= target && target < a[mid]) hi = mid - 1; else lo = mid + 1;
        } else {                                     // right half sorted
            if (a[mid] < target && target <= a[hi]) lo = mid + 1; else hi = mid - 1;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------- 10
static bool canPlace(const vector<int>& s, int cows, int d) {
    int placed = 1, last = s[0];                     // greedy: first cow in the first stall
    for (int i = 1; i < (int)s.size(); i++)
        if (s[i] - last >= d) { placed++; last = s[i]; if (placed == cows) return true; }
    return placed >= cows;
}
int aggressiveCows(vector<int> stalls, int cows) {
    mergeSort(stalls);
    int lo = 1, hi = stalls.back() - stalls.front();  // the LARGEST d that is feasible
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;             // round up: lo = mid must progress
        if (canPlace(stalls, cows, mid)) lo = mid; else hi = mid - 1;
    }
    return lo;
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
