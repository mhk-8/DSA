// ============================================================================
//  Searching & Sorting — reference solutions for Part 13 of the guide
//  All 38 problems, Tier 1 -> Tier 2 -> Tier 3, each with test cases.
//
//  Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part13-solutions.cpp && ./ref
//
//  Every solution lives in its own namespace so each class can be called
//  Solution, exactly as LeetCode expects. The //>>>BEGIN / //<<<END markers
//  delimit the code that is printed in Searching-and-Sorting-Solved-
//  Questions.pdf, so the book can never drift from the code that was tested.
//
//  Where a problem allows any answer order, the tests sort before comparing.
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
static void banner(const string& s) { cout << "\n== " << s << " ==\n"; }


// ============================================================================
//  TIER 1
// ============================================================================

// --------------------------------------------------------------------- LC 704
namespace LC704 {
//>>>BEGIN LC704
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = (int)nums.size() - 1;      // search space: [lo, hi], closed
        while (lo <= hi) {                          // non-empty while lo <= hi
            int mid = lo + (hi - lo) / 2;           // no overflow
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) lo = mid + 1;   // answer is strictly right of mid
            else hi = mid - 1;                      // answer is strictly left of mid
        }
        return -1;
    }
};
//<<<END LC704
}

// ---------------------------------------------------------------------- LC 35
namespace LC35 {
//>>>BEGIN LC35
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // lower_bound: the first index with nums[i] >= target
        int lo = 0, hi = nums.size();               // half-open [lo, hi); n is a valid answer
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < target) lo = mid + 1;   // mid is too small: discard it
            else hi = mid;                          // mid might be the answer: keep it
        }
        return lo;                                  // lo == hi: the boundary
    }
};
//<<<END LC35
}

// --------------------------------------------------------------------- LC 278
namespace LC278 {
static int g_firstBad = 1;
static bool isBadVersion(int v) { return v >= g_firstBad; }   // the judge's API
//>>>BEGIN LC278
class Solution {
public:
    int firstBadVersion(int n) {
        int lo = 1, hi = n;                         // the answer is in [lo, hi]
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;           // (lo + hi) / 2 overflows near 2^31
            if (isBadVersion(mid)) hi = mid;        // mid is bad: first bad is mid or earlier
            else lo = mid + 1;                      // mid is good: first bad is later
        }
        return lo;
    }
};
//<<<END LC278
}

// ---------------------------------------------------------------------- LC 69
namespace LC69 {
//>>>BEGIN LC69
class Solution {
public:
    int mySqrt(int x) {
        // the LAST r with r*r <= x
        long long lo = 0, hi = x;
        while (lo < hi) {
            long long mid = lo + (hi - lo + 1) / 2;  // round UP: lo = mid must make progress
            if (mid * mid <= x) lo = mid;            // mid works: answer is mid or larger
            else hi = mid - 1;
        }
        return (int)lo;
    }
};
//<<<END LC69
}

// ---------------------------------------------------------------------- LC 34
namespace LC34 {
//>>>BEGIN LC34
class Solution {
    // first index with a[i] >= x   (x+1 gives "first index > x")
    int lowerBound(const vector<int>& a, int x) {
        int lo = 0, hi = a.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] < x) lo = mid + 1; else hi = mid;
        }
        return lo;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = lowerBound(nums, target);
        if (first == (int)nums.size() || nums[first] != target) return {-1, -1};
        int last = lowerBound(nums, target + 1) - 1;   // one before the first bigger value
        return {first, last};
    }
};
//<<<END LC34
}

// --------------------------------------------------------------------- LC 367
namespace LC367 {
//>>>BEGIN LC367
class Solution {
public:
    bool isPerfectSquare(int num) {
        long long lo = 1, hi = num;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long sq = mid * mid;                // long long: 46341^2 > INT_MAX
            if (sq == num) return true;
            if (sq < num) lo = mid + 1; else hi = mid - 1;
        }
        return false;
    }
};
//<<<END LC367
}

// --------------------------------------------------------------------- LC 744
namespace LC744 {
//>>>BEGIN LC744
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        // upper_bound: the first letter strictly greater than target
        int lo = 0, hi = letters.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (letters[mid] <= target) lo = mid + 1; else hi = mid;
        }
        return letters[lo % letters.size()];        // none greater: wrap to the first
    }
};
//<<<END LC744
}

// --------------------------------------------------------------------- LC 852
namespace LC852 {
//>>>BEGIN LC852
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;            // mid < hi, so a[mid+1] exists
            if (a[mid] < a[mid + 1]) lo = mid + 1;   // still climbing: peak is to the right
            else hi = mid;                           // descending: peak is mid or left
        }
        return lo;
    }
};
//<<<END LC852
}

// ---------------------------------------------------------------------- LC 88
namespace LC88 {
//>>>BEGIN LC88
class Solution {
public:
    void merge(vector<int>& a, int m, vector<int>& b, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;     // fill from the BACK:
        while (j >= 0) {                             // nothing is overwritten unread
            if (i >= 0 && a[i] > b[j]) a[k--] = a[i--];
            else a[k--] = b[j--];
        }                                            // leftovers of a are already in place
    }
};
//<<<END LC88
}

// --------------------------------------------------------------------- LC 912
namespace LC912 {
//>>>BEGIN LC912
class Solution {
    // randomised quicksort with a THREE-WAY partition:
    //   a[lo..lt-1] < p,   a[lt..gt] == p,   a[gt+1..hi] > p
    void quickSort(vector<int>& a, int lo, int hi) {
        if (lo >= hi) return;
        int p = a[lo + rand() % (hi - lo + 1)];      // random pivot: no sorted-input worst case
        int lt = lo, i = lo, gt = hi;
        while (i <= gt) {
            if (a[i] < p) swap(a[lt++], a[i++]);
            else if (a[i] > p) swap(a[i], a[gt--]);  // do NOT advance i: new a[i] is unseen
            else i++;
        }
        quickSort(a, lo, lt - 1);                    // the == p block is already placed
        quickSort(a, gt + 1, hi);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};
//<<<END LC912
}

// ---------------------------------------------------------------------- LC 75
namespace LC75 {
//>>>BEGIN LC75
class Solution {
public:
    void sortColors(vector<int>& a) {
        // Dutch national flag: [0, lo) = 0s, [lo, i) = 1s, (hi, n-1] = 2s, [i, hi] unknown
        int lo = 0, i = 0, hi = (int)a.size() - 1;
        while (i <= hi) {
            if (a[i] == 0) swap(a[lo++], a[i++]);
            else if (a[i] == 2) swap(a[i], a[hi--]);   // i stays: the swapped-in value is new
            else i++;
        }
    }
};
//<<<END LC75
}

// -------------------------------------------------------------------- LC 1051
namespace LC1051 {
//>>>BEGIN LC1051
class Solution {
public:
    int heightChecker(vector<int>& heights) {
        int cnt[101] = {0};                          // counting sort: heights are 1..100
        for (int h : heights) cnt[h]++;
        int wrong = 0, h = 1;
        for (int x : heights) {
            while (cnt[h] == 0) h++;                 // next value in sorted order
            if (x != h) wrong++;
            cnt[h]--;
        }
        return wrong;
    }
};
//<<<END LC1051
}

// --------------------------------------------------------------------- LC 977
namespace LC977 {
//>>>BEGIN LC977
class Solution {
public:
    vector<int> sortedSquares(vector<int>& a) {
        int n = a.size(), l = 0, r = n - 1;
        vector<int> res(n);
        for (int k = n - 1; k >= 0; k--) {           // the LARGEST square is at an end
            if (abs(a[l]) > abs(a[r])) { res[k] = a[l] * a[l]; l++; }
            else { res[k] = a[r] * a[r]; r--; }
        }
        return res;
    }
};
//<<<END LC977
}

// ============================================================================
//  TIER 2
// ============================================================================

// ---------------------------------------------------------------------- LC 33
namespace LC33 {
//>>>BEGIN LC33
class Solution {
public:
    int search(vector<int>& a, int target) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] == target) return mid;
            if (a[lo] <= a[mid]) {                        // LEFT half [lo, mid] is sorted
                if (a[lo] <= target && target < a[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {                                      // RIGHT half [mid, hi] is sorted
                if (a[mid] < target && target <= a[hi]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return -1;
    }
};
//<<<END LC33
}

// --------------------------------------------------------------------- LC 153
namespace LC153 {
//>>>BEGIN LC153
class Solution {
public:
    int findMin(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] > a[hi]) lo = mid + 1;    // the drop is right of mid
            else hi = mid;                       // [mid, hi] is sorted: min is mid or left
        }
        return a[lo];
    }
};
//<<<END LC153
}

// --------------------------------------------------------------------- LC 162
namespace LC162 {
//>>>BEGIN LC162
class Solution {
public:
    int findPeakElement(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            // walking uphill always reaches a peak, because a[-1] = a[n] = -infinity
            if (a[mid] < a[mid + 1]) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};
//<<<END LC162
}

// ---------------------------------------------------------------------- LC 74
namespace LC74 {
//>>>BEGIN LC74
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& m, int target) {
        int R = m.size(), C = m[0].size();
        int lo = 0, hi = R * C - 1;                  // treat the matrix as ONE sorted array
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int v = m[mid / C][mid % C];             // index -> (row, col)
            if (v == target) return true;
            if (v < target) lo = mid + 1; else hi = mid - 1;
        }
        return false;
    }
};
//<<<END LC74
}

// --------------------------------------------------------------------- LC 240
namespace LC240 {
//>>>BEGIN LC240
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& m, int target) {
        // staircase from the TOP-RIGHT: left is smaller, down is larger
        int r = 0, c = (int)m[0].size() - 1;
        while (r < (int)m.size() && c >= 0) {
            if (m[r][c] == target) return true;
            if (m[r][c] > target) c--;               // whole column below is bigger: drop it
            else r++;                                // whole row to the left is smaller: drop it
        }
        return false;
    }
};
//<<<END LC240
}

// --------------------------------------------------------------------- LC 875
namespace LC875 {
//>>>BEGIN LC875
class Solution {
    long long hoursAt(const vector<int>& piles, int speed) {
        long long h = 0;
        for (int p : piles) h += (p + speed - 1) / speed;   // ceil(p / speed)
        return h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // binary search on the ANSWER: "speed k is fast enough" is monotone in k
        int lo = 1, hi = *max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hoursAt(piles, mid) <= h) hi = mid;      // fast enough: try slower
            else lo = mid + 1;
        }
        return lo;
    }
};
//<<<END LC875
}

// -------------------------------------------------------------------- LC 1011
namespace LC1011 {
//>>>BEGIN LC1011
class Solution {
    int daysNeeded(const vector<int>& w, int cap) {
        int days = 1, load = 0;
        for (int x : w) {
            if (load + x > cap) { days++; load = 0; }    // greedy: start a new day
            load += x;
        }
        return days;
    }
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int lo = *max_element(weights.begin(), weights.end());   // must carry the heaviest
        int hi = accumulate(weights.begin(), weights.end(), 0);  // everything in one day
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (daysNeeded(weights, mid) <= days) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
//<<<END LC1011
}

// --------------------------------------------------------------------- LC 540
namespace LC540 {
//>>>BEGIN LC540
class Solution {
public:
    int singleNonDuplicate(vector<int>& a) {
        // before the single element pairs start at EVEN indices; after it, at odd ones
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mid % 2 == 1) mid--;                 // look at the pair starting at even mid
            if (a[mid] == a[mid + 1]) lo = mid + 2;  // pair intact: single is to the right
            else hi = mid;                           // pair broken: single is mid or left
        }
        return a[lo];
    }
};
//<<<END LC540
}

// --------------------------------------------------------------------- LC 981
namespace LC981 {
//>>>BEGIN LC981
class TimeMap {
    // timestamps arrive strictly increasing, so each list is already sorted
    unordered_map<string, vector<pair<int, string>>> data;
public:
    void set(string key, string value, int timestamp) {
        data[key].push_back({timestamp, value});
    }
    string get(string key, int timestamp) {
        auto it = data.find(key);
        if (it == data.end()) return "";
        auto& v = it->second;
        // first entry with time > timestamp; the one before it is the answer
        auto ub = upper_bound(v.begin(), v.end(), timestamp,
                              [](int t, const pair<int, string>& e) { return t < e.first; });
        return ub == v.begin() ? "" : prev(ub)->second;
    }
};
//<<<END LC981
}

// ---------------------------------------------------------------------- LC 56
namespace LC56 {
//>>>BEGIN LC56
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& iv) {
        sort(iv.begin(), iv.end());                  // by start, then end
        vector<vector<int>> res;
        for (auto& cur : iv) {
            if (!res.empty() && cur[0] <= res.back()[1])
                res.back()[1] = max(res.back()[1], cur[1]);   // overlap: extend
            else
                res.push_back(cur);                            // gap: new interval
        }
        return res;
    }
};
//<<<END LC56
}

// --------------------------------------------------------------------- LC 179
namespace LC179 {
//>>>BEGIN LC179
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> s;
        for (int x : nums) s.push_back(to_string(x));
        // a goes first iff a+b > b+a  (a strict weak ordering, so sort is safe)
        sort(s.begin(), s.end(), [](const string& a, const string& b) { return a + b > b + a; });
        if (s[0] == "0") return "0";                 // all zeros
        string res;
        for (auto& x : s) res += x;
        return res;
    }
};
//<<<END LC179
}

// --------------------------------------------------------------------- LC 215
namespace LC215 {
//>>>BEGIN LC215
class Solution {
public:
    int findKthLargest(vector<int>& a, int k) {
        int target = (int)a.size() - k;              // its index in ascending order
        int lo = 0, hi = (int)a.size() - 1;
        while (true) {                               // QUICKSELECT: recurse into one side only
            int p = a[lo + rand() % (hi - lo + 1)];
            int lt = lo, i = lo, gt = hi;            // three-way partition around p
            while (i <= gt) {
                if (a[i] < p) swap(a[lt++], a[i++]);
                else if (a[i] > p) swap(a[i], a[gt--]);
                else i++;
            }
            if (target < lt) hi = lt - 1;            // answer is in the < p block
            else if (target > gt) lo = gt + 1;       // answer is in the > p block
            else return p;                           // inside the == p block
        }
    }
};
//<<<END LC215
}

// -------------------------------------------------------------------- LC 1482
namespace LC1482 {
//>>>BEGIN LC1482
class Solution {
    int bouquetsBy(const vector<int>& bloom, int day, int k) {
        int made = 0, run = 0;
        for (int b : bloom) {
            run = (b <= day) ? run + 1 : 0;          // adjacent bloomed flowers
            if (run == k) { made++; run = 0; }
        }
        return made;
    }
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if ((long long)m * k > (long long)bloomDay.size()) return -1;   // never enough flowers
        int lo = *min_element(bloomDay.begin(), bloomDay.end());
        int hi = *max_element(bloomDay.begin(), bloomDay.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (bouquetsBy(bloomDay, mid, k) >= m) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
//<<<END LC1482
}

// --------------------------------------------------------------------- LC 274
namespace LC274 {
//>>>BEGIN LC274
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> cnt(n + 1, 0);                   // counting sort, capped at n
        for (int c : citations) cnt[min(c, n)]++;
        int atLeast = 0;                             // papers with >= h citations
        for (int h = n; h >= 0; h--) {
            atLeast += cnt[h];
            if (atLeast >= h) return h;              // the largest h that works
        }
        return 0;
    }
};
//<<<END LC274
}

// ---------------------------------------------------------------------- LC 81
namespace LC81 {
//>>>BEGIN LC81
class Solution {
public:
    bool search(vector<int>& a, int target) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] == target) return true;
            if (a[lo] == a[mid] && a[mid] == a[hi]) { lo++; hi--; continue; }  // can't tell: shrink
            if (a[lo] <= a[mid]) {
                if (a[lo] <= target && target < a[mid]) hi = mid - 1; else lo = mid + 1;
            } else {
                if (a[mid] < target && target <= a[hi]) lo = mid + 1; else hi = mid - 1;
            }
        }
        return false;
    }
};
//<<<END LC81
}

// ============================================================================
//  TIER 3
// ============================================================================

// ----------------------------------------------------------------------- LC 4
namespace LC4 {
//>>>BEGIN LC4
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return findMedianSortedArrays(b, a);  // search the SHORTER
        int m = a.size(), n = b.size(), half = (m + n + 1) / 2;
        int lo = 0, hi = m;                          // i = how many of a go to the left half
        while (lo <= hi) {
            int i = lo + (hi - lo) / 2, j = half - i;
            int aL = i ? a[i - 1] : INT_MIN, aR = i < m ? a[i] : INT_MAX;
            int bL = j ? b[j - 1] : INT_MIN, bR = j < n ? b[j] : INT_MAX;
            if (aL <= bR && bL <= aR) {              // a valid split: left <= right
                if ((m + n) % 2) return max(aL, bL);
                return (max(aL, bL) + (double)min(aR, bR)) / 2.0;
            }
            if (aL > bR) hi = i - 1;                 // took too many from a
            else lo = i + 1;                         // took too few from a
        }
        return 0.0;                                  // unreachable for valid input
    }
};
//<<<END LC4
}

// --------------------------------------------------------------------- LC 410
namespace LC410 {
//>>>BEGIN LC410
class Solution {
    int piecesNeeded(const vector<int>& a, long long cap) {   // greedy: fill each piece
        int pieces = 1;
        long long sum = 0;
        for (int x : a) {
            if (sum + x > cap) { pieces++; sum = 0; }
            sum += x;
        }
        return pieces;
    }
public:
    int splitArray(vector<int>& nums, int k) {
        // minimise the maximum: "largest sum <= cap is achievable" is monotone in cap
        long long lo = *max_element(nums.begin(), nums.end());
        long long hi = accumulate(nums.begin(), nums.end(), 0LL);
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (piecesNeeded(nums, mid) <= k) hi = mid;
            else lo = mid + 1;
        }
        return (int)lo;
    }
};
//<<<END LC410
}

// --------------------------------------------------------------------- LC 154
namespace LC154 {
//>>>BEGIN LC154
class Solution {
public:
    int findMin(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (a[mid] > a[hi]) lo = mid + 1;
            else if (a[mid] < a[hi]) hi = mid;
            else hi--;              // equal: cannot tell which side; a[hi] has a twin at mid
        }
        return a[lo];
    }
};
//<<<END LC154
}

// --------------------------------------------------------------------- LC 315
namespace LC315 {
//>>>BEGIN LC315
class Solution {
    vector<int> cnt, idx, tmp;
    void sortCount(const vector<int>& a, int lo, int hi) {   // sorts idx[lo..hi] by value
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        sortCount(a, lo, mid);
        sortCount(a, mid + 1, hi);
        int i = lo, j = mid + 1, k = lo;
        while (i <= mid) {
            // every right-half element already taken is smaller AND was to the right
            while (j <= hi && a[idx[j]] < a[idx[i]]) tmp[k++] = idx[j++];
            cnt[idx[i]] += j - (mid + 1);
            tmp[k++] = idx[i++];
        }
        while (j <= hi) tmp[k++] = idx[j++];
        for (k = lo; k <= hi; k++) idx[k] = tmp[k];
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        cnt.assign(n, 0); tmp.assign(n, 0); idx.resize(n);
        iota(idx.begin(), idx.end(), 0);              // sort INDICES, so answers stay attached
        sortCount(nums, 0, n - 1);
        return cnt;
    }
};
//<<<END LC315
}

// --------------------------------------------------------------------- LC 327
namespace LC327 {
//>>>BEGIN LC327
class Solution {
    vector<long long> tmp;
    // counts pairs i < j in P[lo..hi] with lower <= P[j] - P[i] <= upper, and sorts P
    int sortCount(vector<long long>& P, int lo, int hi, int lower, int upper) {
        if (lo >= hi) return 0;
        int mid = lo + (hi - lo) / 2;
        int res = sortCount(P, lo, mid, lower, upper) + sortCount(P, mid + 1, hi, lower, upper);
        int a = mid + 1, b = mid + 1;                // a window in the sorted right half
        for (int i = lo; i <= mid; i++) {
            while (a <= hi && P[a] - P[i] < lower) a++;
            while (b <= hi && P[b] - P[i] <= upper) b++;
            res += b - a;                            // right-half sums in [lower, upper]
        }
        merge(P.begin() + lo, P.begin() + mid + 1, P.begin() + mid + 1,
              P.begin() + hi + 1, tmp.begin() + lo);
        copy(tmp.begin() + lo, tmp.begin() + hi + 1, P.begin() + lo);
        return res;
    }
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long long> P(n + 1, 0);               // prefix sums; range sum = P[j] - P[i]
        for (int i = 0; i < n; i++) P[i + 1] = P[i] + nums[i];
        tmp.assign(n + 1, 0);
        return sortCount(P, 0, n, lower, upper);
    }
};
//<<<END LC327
}

// --------------------------------------------------------------------- LC 719
namespace LC719 {
//>>>BEGIN LC719
class Solution {
    long long pairsWithin(const vector<int>& a, int d) {   // pairs with distance <= d
        long long count = 0;
        for (int i = 0, j = 0; i < (int)a.size(); i++) {
            while (a[i] - a[j] > d) j++;             // two pointers on the sorted array
            count += i - j;
        }
        return count;
    }
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int lo = 0, hi = nums.back() - nums.front();
        while (lo < hi) {                            // the smallest d with >= k pairs within d
            int mid = lo + (hi - lo) / 2;
            if (pairsWithin(nums, mid) >= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
//<<<END LC719
}

// --------------------------------------------------------------------- LC 668
namespace LC668 {
//>>>BEGIN LC668
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int lo = 1, hi = m * n;
        while (lo < hi) {                            // smallest x with >= k entries <= x
            int mid = lo + (hi - lo) / 2;
            long long count = 0;
            for (int i = 1; i <= m; i++) count += min(mid / i, n);   // row i: i, 2i, ..., ni
            if (count >= k) hi = mid; else lo = mid + 1;
        }
        return lo;                                   // always a value in the table
    }
};
//<<<END LC668
}

// --------------------------------------------------------------------- LC 164
namespace LC164 {
//>>>BEGIN LC164
class Solution {
public:
    int maximumGap(vector<int>& a) {
        int n = a.size();
        if (n < 2) return 0;
        int mn = *min_element(a.begin(), a.end()), mx = *max_element(a.begin(), a.end());
        if (mn == mx) return 0;
        // n-1 gaps share (mx - mn): the max gap >= ceil((mx-mn)/(n-1)) = bucket width,
        // so it is never INSIDE a bucket — only between consecutive non-empty buckets
        int width = max(1, (mx - mn) / (n - 1));
        int nb = (mx - mn) / width + 1;
        vector<int> bMin(nb, INT_MAX), bMax(nb, INT_MIN);
        for (int x : a) {
            int b = (x - mn) / width;
            bMin[b] = min(bMin[b], x);
            bMax[b] = max(bMax[b], x);
        }
        int best = 0, prevMax = mn;
        for (int b = 0; b < nb; b++) {
            if (bMin[b] == INT_MAX) continue;        // empty bucket
            best = max(best, bMin[b] - prevMax);
            prevMax = bMax[b];
        }
        return best;
    }
};
//<<<END LC164
}

// -------------------------------------------------------------------- LC 1095
namespace LC1095 {
class MountainArray {                                // the judge's interface
    vector<int> v;
public:
    int calls = 0;
    MountainArray(vector<int> a) : v(a) {}
    int get(int i) { calls++; return v[i]; }
    int length() { return v.size(); }
};
//>>>BEGIN LC1095
class Solution {
public:
    int findInMountainArray(int target, MountainArray& m) {
        int n = m.length();
        int lo = 0, hi = n - 1;                      // 1. find the peak
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (m.get(mid) < m.get(mid + 1)) lo = mid + 1; else hi = mid;
        }
        int peak = lo;
        lo = 0, hi = peak;                           // 2. ascending side: the SMALLER index wins
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2, v = m.get(mid);
            if (v == target) return mid;
            if (v < target) lo = mid + 1; else hi = mid - 1;
        }
        lo = peak + 1, hi = n - 1;                   // 3. descending side: comparisons flip
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2, v = m.get(mid);
            if (v == target) return mid;
            if (v > target) lo = mid + 1; else hi = mid - 1;
        }
        return -1;
    }
};
//<<<END LC1095
}

// -------------------------------------------------------------------- LC 1802
namespace LC1802 {
//>>>BEGIN LC1802
class Solution {
    // minimum total of `len` cells descending by 1 from just below `top`, floor 1
    long long side(long long top, long long len) {
        if (top - 1 >= len)                          // top-1, top-2, ..., top-len
            return (top - 1 + top - len) * len / 2;
        long long sloped = top - 1;                  // top-1, ..., 1, then 1s
        return sloped * (sloped + 1) / 2 + (len - sloped);
    }
public:
    int maxValue(int n, int index, int maxSum) {
        int lo = 1, hi = maxSum;
        while (lo < hi) {                            // the LARGEST peak that fits
            int mid = lo + (hi - lo + 1) / 2;        // round up: lo = mid must progress
            long long total = mid + side(mid, index) + side(mid, n - 1 - index);
            if (total <= maxSum) lo = mid; else hi = mid - 1;
        }
        return lo;
    }
};
//<<<END LC1802
}

// ============================================================================
//  TESTS
// ============================================================================
static bool isPeak(const vector<int>& a, int i) {
    long long l = i > 0 ? a[i - 1] : LLONG_MIN, r = i + 1 < (int)a.size() ? a[i + 1] : LLONG_MIN;
    return a[i] > l && a[i] > r;
}

int main() {
    banner("Tier 1");
    {   LC704::Solution s;
        vector<int> a{-1,0,3,5,9,12};
        check("LC704 a", s.search(a, 9), 4);
        check("LC704 b", s.search(a, 2), -1);
        check("LC704 c", s.search(a, -1), 0);
        vector<int> b{5}; check("LC704 d", s.search(b, 5), 0);
    }
    {   LC35::Solution s;
        vector<int> a{1,3,5,6};
        check("LC35 a", s.searchInsert(a, 5), 2);
        check("LC35 b", s.searchInsert(a, 2), 1);
        check("LC35 c", s.searchInsert(a, 7), 4);
        check("LC35 d", s.searchInsert(a, 0), 0);
    }
    {   LC278::Solution s;
        LC278::g_firstBad = 4;          check("LC278 a", s.firstBadVersion(5), 4);
        LC278::g_firstBad = 1;          check("LC278 b", s.firstBadVersion(1), 1);
        LC278::g_firstBad = 1702766719; check("LC278 c", s.firstBadVersion(2126753390), 1702766719);
    }
    {   LC69::Solution s;
        check("LC69 a", s.mySqrt(4), 2);
        check("LC69 b", s.mySqrt(8), 2);
        check("LC69 c", s.mySqrt(0), 0);
        check("LC69 d", s.mySqrt(1), 1);
        check("LC69 e", s.mySqrt(2147395599), 46339);
        check("LC69 f", s.mySqrt(INT_MAX), 46340);
    }
    {   LC34::Solution s;
        vector<int> a{5,7,7,8,8,10};
        check("LC34 a", s.searchRange(a, 8), vector<int>{3,4});
        check("LC34 b", s.searchRange(a, 6), vector<int>{-1,-1});
        vector<int> e{};  check("LC34 c", s.searchRange(e, 0), vector<int>{-1,-1});
        vector<int> o{1}; check("LC34 d", s.searchRange(o, 1), vector<int>{0,0});
        vector<int> m{2,2,2}; check("LC34 e", s.searchRange(m, 2), vector<int>{0,2});
    }
    {   LC367::Solution s;
        check("LC367 a", s.isPerfectSquare(16), true);
        check("LC367 b", s.isPerfectSquare(14), false);
        check("LC367 c", s.isPerfectSquare(1), true);
        check("LC367 d", s.isPerfectSquare(808201), true);
        check("LC367 e", s.isPerfectSquare(INT_MAX), false);
    }
    {   LC744::Solution s;
        vector<char> a{'c','f','j'};
        check("LC744 a", string(1, s.nextGreatestLetter(a, 'a')), string("c"));
        check("LC744 b", string(1, s.nextGreatestLetter(a, 'c')), string("f"));
        check("LC744 c", string(1, s.nextGreatestLetter(a, 'z')), string("c"));
        vector<char> b{'x','x','y','y'};
        check("LC744 d", string(1, s.nextGreatestLetter(b, 'z')), string("x"));
    }
    {   LC852::Solution s;
        vector<int> a{0,1,0};       check("LC852 a", s.peakIndexInMountainArray(a), 1);
        vector<int> b{0,2,1,0};     check("LC852 b", s.peakIndexInMountainArray(b), 1);
        vector<int> c{0,10,5,2};    check("LC852 c", s.peakIndexInMountainArray(c), 1);
        vector<int> d{0,1,2,3,2};   check("LC852 d", s.peakIndexInMountainArray(d), 3);
    }
    {   LC88::Solution s;
        vector<int> a{1,2,3,0,0,0}, b{2,5,6}; s.merge(a, 3, b, 3);
        check("LC88 a", a, vector<int>{1,2,2,3,5,6});
        vector<int> c{0}, d{1}; s.merge(c, 0, d, 1);
        check("LC88 b", c, vector<int>{1});
        vector<int> e{4,5,6,0,0,0}, f{1,2,3}; s.merge(e, 3, f, 3);
        check("LC88 c", e, vector<int>{1,2,3,4,5,6});
    }
    {   LC912::Solution s;
        vector<int> a{5,2,3,1};       check("LC912 a", s.sortArray(a), vector<int>{1,2,3,5});
        vector<int> b{5,1,1,2,0,0};   check("LC912 b", s.sortArray(b), vector<int>{0,0,1,1,2,5});
        vector<int> c{2,2,2,2,1};     check("LC912 c", s.sortArray(c), vector<int>{1,2,2,2,2});
        vector<int> d{-3};            check("LC912 d", s.sortArray(d), vector<int>{-3});
    }
    {   LC75::Solution s;
        vector<int> a{2,0,2,1,1,0}; s.sortColors(a); check("LC75 a", a, vector<int>{0,0,1,1,2,2});
        vector<int> b{2,0,1};       s.sortColors(b); check("LC75 b", b, vector<int>{0,1,2});
        vector<int> c{0};           s.sortColors(c); check("LC75 c", c, vector<int>{0});
        vector<int> d{2,2,0,0};     s.sortColors(d); check("LC75 d", d, vector<int>{0,0,2,2});
    }
    {   LC1051::Solution s;
        vector<int> a{1,1,4,2,1,3}; check("LC1051 a", s.heightChecker(a), 3);
        vector<int> b{5,1,2,3,4};   check("LC1051 b", s.heightChecker(b), 5);
        vector<int> c{1,2,3,4,5};   check("LC1051 c", s.heightChecker(c), 0);
    }
    {   LC977::Solution s;
        vector<int> a{-4,-1,0,3,10};  check("LC977 a", s.sortedSquares(a), vector<int>{0,1,9,16,100});
        vector<int> b{-7,-3,2,3,11};  check("LC977 b", s.sortedSquares(b), vector<int>{4,9,9,49,121});
        vector<int> c{-5,-3,-1};      check("LC977 c", s.sortedSquares(c), vector<int>{1,9,25});
    }

    banner("Tier 2");
    {   LC33::Solution s;
        vector<int> a{4,5,6,7,0,1,2};
        check("LC33 a", s.search(a, 0), 4);
        check("LC33 b", s.search(a, 3), -1);
        check("LC33 c", s.search(a, 4), 0);
        vector<int> b{1};   check("LC33 d", s.search(b, 0), -1);
        vector<int> c{3,1}; check("LC33 e", s.search(c, 1), 1);
        vector<int> d{5,1,3}; check("LC33 f", s.search(d, 5), 0);
    }
    {   LC153::Solution s;
        vector<int> a{3,4,5,1,2};       check("LC153 a", s.findMin(a), 1);
        vector<int> b{4,5,6,7,0,1,2};   check("LC153 b", s.findMin(b), 0);
        vector<int> c{11,13,15,17};     check("LC153 c", s.findMin(c), 11);
        vector<int> d{2,1};             check("LC153 d", s.findMin(d), 1);
    }
    {   LC162::Solution s;
        vector<int> a{1,2,3,1};          check("LC162 a", s.findPeakElement(a), 2);
        vector<int> b{1,2,1,3,5,6,4};    check("LC162 b", isPeak(b, s.findPeakElement(b)), true);
        vector<int> c{1};                check("LC162 c", s.findPeakElement(c), 0);
        vector<int> d{3,2,1};            check("LC162 d", s.findPeakElement(d), 0);
    }
    {   LC74::Solution s;
        vector<vector<int>> m{{1,3,5,7},{10,11,16,20},{23,30,34,60}};
        check("LC74 a", s.searchMatrix(m, 3), true);
        check("LC74 b", s.searchMatrix(m, 13), false);
        check("LC74 c", s.searchMatrix(m, 60), true);
    }
    {   LC240::Solution s;
        vector<vector<int>> m{{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
        check("LC240 a", s.searchMatrix(m, 5), true);
        check("LC240 b", s.searchMatrix(m, 20), false);
        check("LC240 c", s.searchMatrix(m, 18), true);
    }
    {   LC875::Solution s;
        vector<int> a{3,6,7,11};          check("LC875 a", s.minEatingSpeed(a, 8), 4);
        vector<int> b{30,11,23,4,20};     check("LC875 b", s.minEatingSpeed(b, 5), 30);
        check("LC875 c", s.minEatingSpeed(b, 6), 23);
        vector<int> c{1000000000};        check("LC875 d", s.minEatingSpeed(c, 2), 500000000);
    }
    {   LC1011::Solution s;
        vector<int> a{1,2,3,4,5,6,7,8,9,10}; check("LC1011 a", s.shipWithinDays(a, 5), 15);
        vector<int> b{3,2,2,4,1,4};          check("LC1011 b", s.shipWithinDays(b, 3), 6);
        vector<int> c{1,2,3,1,1};            check("LC1011 c", s.shipWithinDays(c, 4), 3);
    }
    {   LC540::Solution s;
        vector<int> a{1,1,2,3,3,4,4,8,8};  check("LC540 a", s.singleNonDuplicate(a), 2);
        vector<int> b{3,3,7,7,10,11,11};   check("LC540 b", s.singleNonDuplicate(b), 10);
        vector<int> c{1};                  check("LC540 c", s.singleNonDuplicate(c), 1);
        vector<int> d{1,1,2};              check("LC540 d", s.singleNonDuplicate(d), 2);
    }
    {   LC981::TimeMap t;
        t.set("foo", "bar", 1);
        check("LC981 a", t.get("foo", 1), string("bar"));
        check("LC981 b", t.get("foo", 3), string("bar"));
        t.set("foo", "bar2", 4);
        check("LC981 c", t.get("foo", 4), string("bar2"));
        check("LC981 d", t.get("foo", 5), string("bar2"));
        check("LC981 e", t.get("foo", 0), string(""));
        check("LC981 f", t.get("nope", 9), string(""));
    }
    {   LC56::Solution s;
        vector<vector<int>> a{{1,3},{2,6},{8,10},{15,18}};
        check("LC56 a", s.merge(a), vector<vector<int>>{{1,6},{8,10},{15,18}});
        vector<vector<int>> b{{1,4},{4,5}};  check("LC56 b", s.merge(b), vector<vector<int>>{{1,5}});
        vector<vector<int>> c{{1,4},{2,3}};  check("LC56 c", s.merge(c), vector<vector<int>>{{1,4}});
        vector<vector<int>> d{{4,7},{1,4}};  check("LC56 d", s.merge(d), vector<vector<int>>{{1,7}});
    }
    {   LC179::Solution s;
        vector<int> a{10,2};          check("LC179 a", s.largestNumber(a), string("210"));
        vector<int> b{3,30,34,5,9};   check("LC179 b", s.largestNumber(b), string("9534330"));
        vector<int> c{0,0};           check("LC179 c", s.largestNumber(c), string("0"));
        vector<int> d{432,43243};     check("LC179 d", s.largestNumber(d), string("43243432"));
    }
    {   LC215::Solution s;
        vector<int> a{3,2,1,5,6,4};       check("LC215 a", s.findKthLargest(a, 2), 5);
        vector<int> b{3,2,3,1,2,4,5,5,6}; check("LC215 b", s.findKthLargest(b, 4), 4);
        vector<int> c{1};                 check("LC215 c", s.findKthLargest(c, 1), 1);
        vector<int> d{2,2,2,2};           check("LC215 d", s.findKthLargest(d, 2), 2);
    }
    {   LC1482::Solution s;
        vector<int> a{1,10,3,10,2};       check("LC1482 a", s.minDays(a, 3, 1), 3);
        check("LC1482 b", s.minDays(a, 3, 2), -1);
        vector<int> b{7,7,7,7,12,7,7};    check("LC1482 c", s.minDays(b, 2, 3), 12);
    }
    {   LC274::Solution s;
        vector<int> a{3,0,6,1,5}; check("LC274 a", s.hIndex(a), 3);
        vector<int> b{1,3,1};     check("LC274 b", s.hIndex(b), 1);
        vector<int> c{100};       check("LC274 c", s.hIndex(c), 1);
        vector<int> d{0};         check("LC274 d", s.hIndex(d), 0);
    }
    {   LC81::Solution s;
        vector<int> a{2,5,6,0,0,1,2};
        check("LC81 a", s.search(a, 0), true);
        check("LC81 b", s.search(a, 3), false);
        vector<int> b{1,0,1,1,1};   check("LC81 c", s.search(b, 0), true);
        vector<int> c{1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1};
        check("LC81 d", s.search(c, 13), true);
    }

    banner("Tier 3");
    {   LC4::Solution s;
        vector<int> a{1,3}, b{2};       check("LC4 a", s.findMedianSortedArrays(a, b), 2.0);
        vector<int> c{1,2}, d{3,4};     check("LC4 b", s.findMedianSortedArrays(c, d), 2.5);
        vector<int> e{}, f{1};          check("LC4 c", s.findMedianSortedArrays(e, f), 1.0);
        vector<int> g{0,0}, h{0,0};     check("LC4 d", s.findMedianSortedArrays(g, h), 0.0);
        vector<int> i{2}, j{};          check("LC4 e", s.findMedianSortedArrays(i, j), 2.0);
        vector<int> k{1,3,8,9,15}, l{7,11,18,19,21,25};
        check("LC4 f", s.findMedianSortedArrays(k, l), 11.0);
    }
    {   LC410::Solution s;
        vector<int> a{7,2,5,10,8}; check("LC410 a", s.splitArray(a, 2), 18);
        vector<int> b{1,2,3,4,5};  check("LC410 b", s.splitArray(b, 2), 9);
        vector<int> c{1,4,4};      check("LC410 c", s.splitArray(c, 3), 4);
    }
    {   LC154::Solution s;
        vector<int> a{1,3,5};         check("LC154 a", s.findMin(a), 1);
        vector<int> b{2,2,2,0,1};     check("LC154 b", s.findMin(b), 0);
        vector<int> c{3,3,1,3};       check("LC154 c", s.findMin(c), 1);
        vector<int> d{10,1,10,10,10}; check("LC154 d", s.findMin(d), 1);
    }
    {   LC315::Solution s;
        vector<int> a{5,2,6,1};  check("LC315 a", s.countSmaller(a), vector<int>{2,1,1,0});
        vector<int> b{-1};       check("LC315 b", s.countSmaller(b), vector<int>{0});
        vector<int> c{-1,-1};    check("LC315 c", s.countSmaller(c), vector<int>{0,0});
        vector<int> d{2,0,1};    check("LC315 d", s.countSmaller(d), vector<int>{2,0,0});
    }
    {   LC327::Solution s;
        vector<int> a{-2,5,-1};  check("LC327 a", s.countRangeSum(a, -2, 2), 3);
        vector<int> b{0};        check("LC327 b", s.countRangeSum(b, 0, 0), 1);
        vector<int> c{2147483647,-2147483648,-1,0}; check("LC327 c", s.countRangeSum(c, -1, 0), 4);
    }
    {   LC719::Solution s;
        vector<int> a{1,3,1}; check("LC719 a", s.smallestDistancePair(a, 1), 0);
        vector<int> b{1,1,1}; check("LC719 b", s.smallestDistancePair(b, 2), 0);
        vector<int> c{1,6,1}; check("LC719 c", s.smallestDistancePair(c, 3), 5);
    }
    {   LC668::Solution s;
        check("LC668 a", s.findKthNumber(3, 3, 5), 3);
        check("LC668 b", s.findKthNumber(2, 3, 6), 6);
        check("LC668 c", s.findKthNumber(1, 1, 1), 1);
    }
    {   LC164::Solution s;
        vector<int> a{3,6,9,1};      check("LC164 a", s.maximumGap(a), 3);
        vector<int> b{10};           check("LC164 b", s.maximumGap(b), 0);
        vector<int> c{1,10000000};   check("LC164 c", s.maximumGap(c), 9999999);
        vector<int> d{1,1,1,1};      check("LC164 d", s.maximumGap(d), 0);
    }
    {   LC1095::Solution s;
        LC1095::MountainArray a({1,2,3,4,5,3,1});
        check("LC1095 a", s.findInMountainArray(3, a), 2);
        LC1095::MountainArray b({0,1,2,4,2,1});
        check("LC1095 b", s.findInMountainArray(3, b), -1);
        LC1095::MountainArray c({1,5,2});
        check("LC1095 c", s.findInMountainArray(2, c), 2);
        check("LC1095 d calls <= 100", a.calls <= 100, true);
    }
    {   LC1802::Solution s;
        check("LC1802 a", s.maxValue(4, 2, 6), 2);
        check("LC1802 b", s.maxValue(6, 1, 10), 3);
        check("LC1802 c", s.maxValue(3, 2, 18), 7);
        check("LC1802 d", s.maxValue(1, 0, 1000000000), 1000000000);
    }

    cout << "\n----------------------------------------\n";
    cout << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}
