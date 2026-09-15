// ============================================================================
//  01_Arrays / solutions / reference-basics.cpp
//
//  Worked answers to practice-01-basics.cpp (TODO 1-10), plus the core
//  building blocks taught in Parts 0-8 of Arrays-Guide.pdf: the two binary
//  search templates, both window flavours, the at-most-K counting trick,
//  prefix sums in 1D and 2D, the difference array, and the Indian-placement
//  classics (union/intersection, leaders, equilibrium index, second largest).
//
//  Build:  g++ -std=c++17 -O2 -Wall reference-basics.cpp -o basics && ./basics
//  Open this only AFTER attempting the practice file.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ------------------------- TODO 1-10: the answers ---------------------------

int findMax(const vector<int>& v) {
    if (v.empty()) return INT_MIN;              // guard the empty case first
    int best = v[0];                            // seed from the data, never 0
    for (int i = 1; i < (int)v.size(); i++) best = max(best, v[i]);
    return best;
}

void reverseInPlace(vector<int>& v) {
    int l = 0, r = (int)v.size() - 1;
    while (l < r) swap(v[l++], v[r--]);         // two pointers, opposite ends
}

int removeValue(vector<int>& v, int val) {
    int w = 0;                                  // w = next write slot
    for (int r = 0; r < (int)v.size(); r++)     // v[0..w-1] is the finished answer
        if (v[r] != val) v[w++] = v[r];
    return w;
}

void moveZeroes(vector<int>& v) {
    int n = v.size(), w = 0;
    for (int r = 0; r < n; r++)
        if (v[r] != 0) v[w++] = v[r];           // pass 1: compact
    while (w < n) v[w++] = 0;                   // pass 2: zero the tail
}

vector<long long> prefixSums(const vector<int>& v) {
    int n = v.size();
    vector<long long> P(n + 1, 0);              // P[0] = 0 removes every special case
    for (int i = 0; i < n; i++) P[i + 1] = P[i] + v[i];
    return P;
}

int firstOccurrence(const vector<int>& v, int target) {
    int lo = 0, hi = v.size();                  // half-open: hi = n, not n-1
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] >= target) hi = mid;         // mid may be the answer — keep it
        else                  lo = mid + 1;
    }
    if (lo == (int)v.size() || v[lo] != target) return -1;
    return lo;
}

int maxSumWindow(const vector<int>& v, int k) {
    int n = v.size();
    if (k <= 0 || n < k) return 0;
    int sum = 0;
    for (int i = 0; i < k; i++) sum += v[i];
    int best = sum;
    for (int r = k; r < n; r++) {
        sum += v[r] - v[r - k];                 // v[r] enters, v[r-k] leaves
        best = max(best, sum);
    }
    return best;
}

int maxSubarraySum(const vector<int>& v) {
    int best = v[0], cur = v[0];                // NOT 0 — all-negative input
    for (int i = 1; i < (int)v.size(); i++) {
        cur  = max(v[i], cur + v[i]);
        best = max(best, cur);
    }
    return best;
}

void rotateRight(vector<int>& v, int k) {
    int n = v.size();
    if (n == 0) return;                         // guard before the modulo
    k %= n;
    reverse(v.begin(), v.end());
    reverse(v.begin(), v.begin() + k);
    reverse(v.begin() + k, v.end());
}

void sortColors(vector<int>& v) {
    int low = 0, mid = 0, high = (int)v.size() - 1;
    while (mid <= high) {
        if      (v[mid] == 0) swap(v[low++], v[mid++]);
        else if (v[mid] == 1) mid++;
        else                  swap(v[mid], v[high--]);   // mid stays put
    }
}

// --------------------------- building blocks --------------------------------

// Binary search template 1 — exact value, closed range.
int binarySearchExact(const vector<int>& v, int target) {
    int lo = 0, hi = (int)v.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] == target) return mid;
        if (v[mid] < target) lo = mid + 1;
        else                 hi = mid - 1;
    }
    return -1;
}

// Template 2 — first index with v[i] > x  (std::upper_bound).
int upperBoundIdx(const vector<int>& v, int x) {
    int lo = 0, hi = v.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (v[mid] > x) hi = mid;
        else            lo = mid + 1;
    }
    return lo;
}

// Binary search on the ANSWER: smallest speed that clears the piles within h hours.
bool canFinish(const vector<int>& piles, long long speed, int h) {
    long long hours = 0;
    for (int p : piles) hours += (p + speed - 1) / speed;   // ceiling division
    return hours <= h;
}
int minEatingSpeed(const vector<int>& piles, int h) {
    long long lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canFinish(piles, mid, h)) hi = mid;             // feasible -> go slower
        else                          lo = mid + 1;
    }
    return (int)lo;
}

// Shortest window with sum >= target (positive values only).
int minWindowLen(const vector<int>& v, int target) {
    int l = 0, best = INT_MAX;
    long long sum = 0;
    for (int r = 0; r < (int)v.size(); r++) {
        sum += v[r];
        while (sum >= target) { best = min(best, r - l + 1); sum -= v[l++]; }
    }
    return best == INT_MAX ? 0 : best;
}

// Longest window with at most K distinct values.
int longestAtMostKDistinct(const vector<int>& v, int K) {
    unordered_map<int,int> cnt;
    int l = 0, best = 0;
    for (int r = 0; r < (int)v.size(); r++) {
        cnt[v[r]]++;
        while ((int)cnt.size() > K)
            if (--cnt[v[l++]] == 0) cnt.erase(v[l - 1]);
        best = max(best, r - l + 1);
    }
    return best;
}

// Count subarrays with at most K distinct — the half of exactly(K) = atMost(K) - atMost(K-1).
long long countAtMostKDistinct(const vector<int>& v, int K) {
    unordered_map<int,int> cnt;
    long long res = 0;
    int l = 0;
    for (int r = 0; r < (int)v.size(); r++) {
        if (++cnt[v[r]] == 1) K--;
        while (K < 0) if (--cnt[v[l++]] == 0) K++;
        res += r - l + 1;                       // every subarray ending at r is valid
    }
    return res;
}

// Count subarrays summing to k — works with negative values.
int countSubarraysWithSum(const vector<int>& v, int k) {
    unordered_map<long long,int> seen;
    seen[0] = 1;                                // the empty prefix
    long long pre = 0;
    int count = 0;
    for (int x : v) {
        pre += x;
        auto it = seen.find(pre - k);
        if (it != seen.end()) count += it->second;
        seen[pre]++;
    }
    return count;
}

// Difference array: apply range updates in O(1) each, materialise once.
vector<long long> applyRangeUpdates(int n, const vector<array<int,3>>& ups) {
    vector<long long> diff(n + 1, 0);
    for (auto& u : ups) { diff[u[0]] += u[2]; diff[u[1] + 1] -= u[2]; }
    vector<long long> res(n, 0);
    long long run = 0;
    for (int i = 0; i < n; i++) { run += diff[i]; res[i] = run; }
    return res;
}

// 2D prefix sum, then an O(1) rectangle query (inclusion-exclusion).
vector<vector<long long>> build2D(const vector<vector<int>>& g) {
    int r = g.size(), c = g[0].size();
    vector<vector<long long>> P(r + 1, vector<long long>(c + 1, 0));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            P[i+1][j+1] = g[i][j] + P[i][j+1] + P[i+1][j] - P[i][j];
    return P;
}
long long query2D(const vector<vector<long long>>& P, int r1, int c1, int r2, int c2) {
    return P[r2+1][c2+1] - P[r1][c2+1] - P[r2+1][c1] + P[r1][c1];
}

// --------------------- Indian-placement classics ----------------------------

// Second largest DISTINCT value, one pass. INT_MIN if there is none.
int secondLargest(const vector<int>& v) {
    int a = INT_MIN, b = INT_MIN;               // a = largest, b = runner-up
    for (int x : v) {
        if (x > a)      { b = a; a = x; }
        else if (x > b && x < a) b = x;         // x < a keeps it DISTINCT
    }
    return b;
}

// Union of two sorted arrays, no duplicates.
vector<int> unionSorted(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int i = 0, j = 0;
    auto push = [&](int x) { if (res.empty() || res.back() != x) res.push_back(x); };
    while (i < (int)a.size() && j < (int)b.size()) {
        if      (a[i] < b[j]) push(a[i++]);
        else if (b[j] < a[i]) push(b[j++]);
        else { push(a[i++]); j++; }
    }
    while (i < (int)a.size()) push(a[i++]);
    while (j < (int)b.size()) push(b[j++]);
    return res;
}

// Intersection of two sorted arrays, no duplicates.
vector<int> intersectSorted(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int i = 0, j = 0;
    while (i < (int)a.size() && j < (int)b.size()) {
        if      (a[i] < b[j]) i++;
        else if (b[j] < a[i]) j++;
        else {
            if (res.empty() || res.back() != a[i]) res.push_back(a[i]);
            i++; j++;
        }
    }
    return res;
}

// Leaders: every element greater than all elements to its right. Scan RIGHT to LEFT.
vector<int> leaders(const vector<int>& v) {
    vector<int> res;
    int mx = INT_MIN;
    for (int i = (int)v.size() - 1; i >= 0; i--)
        if (v[i] > mx) { mx = v[i]; res.push_back(v[i]); }
    reverse(res.begin(), res.end());
    return res;
}

// Equilibrium index: left sum == right sum. -1 if none.
int equilibriumIndex(const vector<int>& v) {
    long long total = accumulate(v.begin(), v.end(), 0LL);   // 0LL, not 0
    long long left = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        if (left == total - left - v[i]) return i;
        left += v[i];
    }
    return -1;
}

// Maximum circular subarray sum. Kadane twice.
int maxCircularSum(const vector<int>& v) {
    int total = 0, curMax = v[0], bestMax = v[0], curMin = v[0], bestMin = v[0];
    for (int i = 0; i < (int)v.size(); i++) {
        total += v[i];
        if (i) {
            curMax = max(v[i], curMax + v[i]); bestMax = max(bestMax, curMax);
            curMin = min(v[i], curMin + v[i]); bestMin = min(bestMin, curMin);
        }
    }
    if (bestMax < 0) return bestMax;            // all negative: wrapping is illegal
    return max(bestMax, total - bestMin);
}

// ================================ TESTS =====================================
static int g_pass = 0, g_fail = 0;
template <class T>
static void check(const string& what, const T& got, const T& want) {
    if (got == want) { g_pass++; return; }
    g_fail++;
    cout << "FAIL  " << what << "\n";
}

int main() {
    check<int>("findMax",        findMax({3,1,4,1,5}), 5);
    check<int>("findMax neg",    findMax({-7,-2,-9}), -2);
    check<int>("findMax empty",  findMax({}), INT_MIN);

    { vector<int> a{1,2,3,4}; reverseInPlace(a); check<vector<int>>("reverse even", a, {4,3,2,1});
      vector<int> b{1,2,3};   reverseInPlace(b); check<vector<int>>("reverse odd",  b, {3,2,1});
      vector<int> c;          reverseInPlace(c); check<vector<int>>("reverse empty", c, {}); }

    { vector<int> a{3,2,2,3}; check<int>("removeValue len", removeValue(a,3), 2);
      check<vector<int>>("removeValue kept", vector<int>(a.begin(), a.begin()+2), {2,2});
      vector<int> b{1,1,1};   check<int>("removeValue all", removeValue(b,1), 0); }

    { vector<int> a{0,1,0,3,12}; moveZeroes(a); check<vector<int>>("moveZeroes", a, {1,3,12,0,0});
      vector<int> b{0,0};        moveZeroes(b); check<vector<int>>("moveZeroes all", b, {0,0}); }

    { auto p = prefixSums({3,1,4,1,5});
      check<vector<long long>>("prefixSums", p, {0,3,4,8,9,14});
      check<long long>("range query", p[4]-p[1], 6);
      check<vector<long long>>("prefixSums empty", prefixSums({}), {0}); }

    { vector<int> v{5,7,7,8,8,10};
      check<int>("firstOccurrence run", firstOccurrence(v,8), 3);
      check<int>("firstOccurrence miss", firstOccurrence(v,6), -1);
      check<int>("firstOccurrence empty", firstOccurrence({},1), -1);
      check<int>("binarySearchExact", binarySearchExact(v,10), 5);
      check<int>("binarySearchExact miss", binarySearchExact(v,6), -1);
      check<int>("upperBoundIdx", upperBoundIdx(v,8), 5);
      check<int>("upperBoundIdx past", upperBoundIdx(v,99), 6); }

    check<int>("maxSumWindow",     maxSumWindow({2,1,5,1,3,2},3), 9);
    check<int>("maxSumWindow k>n", maxSumWindow({1,2},5), 0);
    check<int>("maxSumWindow neg", maxSumWindow({-1,-2,-3,-4},2), -3);

    check<int>("kadane mixed",   maxSubarraySum({-2,1,-3,4,-1,2,1,-5,4}), 6);
    check<int>("kadane all neg", maxSubarraySum({-3,-1,-2}), -1);
    check<int>("kadane single",  maxSubarraySum({-5}), -5);

    { vector<int> a{1,2,3,4,5,6,7}; rotateRight(a,3); check<vector<int>>("rotate", a, {5,6,7,1,2,3,4});
      vector<int> b{1,2};           rotateRight(b,5); check<vector<int>>("rotate k>n", b, {2,1});
      vector<int> c;                rotateRight(c,3); check<vector<int>>("rotate empty", c, {}); }

    { vector<int> a{2,0,2,1,1,0}; sortColors(a); check<vector<int>>("sortColors", a, {0,0,1,1,2,2});
      vector<int> b{1,1,1};       sortColors(b); check<vector<int>>("sortColors same", b, {1,1,1}); }

    check<int>("minEatingSpeed",   minEatingSpeed({3,6,7,11}, 8), 4);
    check<int>("minEatingSpeed 2", minEatingSpeed({30,11,23,4,20}, 5), 30);

    check<int>("minWindowLen",      minWindowLen({2,3,1,2,4,3}, 7), 2);
    check<int>("minWindowLen none", minWindowLen({1,1,1}, 11), 0);

    check<int>("atMostKDistinct",   longestAtMostKDistinct({1,2,1,2,3}, 2), 4);
    check<long long>("countAtMostK", countAtMostKDistinct({1,2,1,2,3}, 2), 12LL);
    // exactly(2) = atMost(2) - atMost(1)
    check<long long>("exactlyK",
        countAtMostKDistinct({1,2,1,2,3}, 2) - countAtMostKDistinct({1,2,1,2,3}, 1), 7LL);

    check<int>("subarraySum",     countSubarraysWithSum({1,1,1}, 2), 2);
    check<int>("subarraySum neg", countSubarraysWithSum({1,-1,0}, 0), 3);
    check<int>("subarraySum at 0", countSubarraysWithSum({3}, 3), 1);

    { auto r = applyRangeUpdates(5, {{0,2,3},{1,4,2}});
      check<vector<long long>>("difference array", r, {3,5,5,2,2}); }

    { vector<vector<int>> g{{1,2,3},{4,5,6},{7,8,9}};
      auto P = build2D(g);
      check<long long>("2D whole",  query2D(P,0,0,2,2), 45LL);
      check<long long>("2D corner", query2D(P,1,1,2,2), 28LL);
      check<long long>("2D cell",   query2D(P,0,2,0,2), 3LL); }

    check<int>("secondLargest",      secondLargest({3,1,4,4,5}), 4);
    check<int>("secondLargest dups", secondLargest({7,7,7}), INT_MIN);

    check<vector<int>>("unionSorted",     unionSorted({1,2,2,5},{2,3,5}), {1,2,3,5});
    check<vector<int>>("intersectSorted", intersectSorted({1,2,2,5},{2,3,5}), {2,5});
    check<vector<int>>("intersect none",  intersectSorted({1,3},{2,4}), {});

    check<vector<int>>("leaders", leaders({16,17,4,3,5,2}), {17,5,2});
    check<int>("equilibrium",      equilibriumIndex({-7,1,5,2,-4,3,0}), 3);
    check<int>("equilibrium none", equilibriumIndex({1,2,3}), -1);

    check<int>("maxCircular wrap",  maxCircularSum({5,-3,5}), 10);
    check<int>("maxCircular plain", maxCircularSum({1,-2,3,-2}), 3);
    check<int>("maxCircular neg",   maxCircularSum({-3,-2,-3}), -2);

    cout << "\n" << g_pass << " passed, " << g_fail << " failed.\n";
    if (g_fail == 0) cout << "ALL TESTS PASSED\n";
    return g_fail == 0 ? 0 : 1;
}
