// ============================================================================
//  01_Arrays / solutions / reference-part13-solutions.cpp
//
//  Verified reference solutions to all 38 problems in Part 13 of
//  Arrays-Guide.pdf, in Tier 1 (13) -> Tier 2 (15) -> Tier 3 (10) order.
//
//  This file is the SINGLE SOURCE OF TRUTH for Arrays-Solved-Questions.pdf:
//  the book extracts the code between the BEGIN/END markers below, so the
//  printed code is provably the code that passes the tests in main().
//
//  Build:  g++ -std=c++17 -O2 -Wall reference-part13-solutions.cpp -o ref && ./ref
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ------------------------------ test harness --------------------------------
static int g_pass = 0, g_fail = 0;

template <class T>
static void check(const string& what, const T& got, const T& want) {
    if (got == want) { g_pass++; return; }
    g_fail++;
    cout << "FAIL  " << what << "\n";
}
static void checkV(const string& what, vector<int> got, vector<int> want) {
    check(what, got, want);
}

// ============================== TIER 1 ======================================

namespace LC1 {
//>>>BEGIN LC1
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> seen;              // value -> its index
        for (int i = 0; i < (int)nums.size(); i++) {
            int need = target - nums[i];
            auto it = seen.find(need);
            if (it != seen.end()) return {it->second, i};
            seen[nums[i]] = i;                    // insert AFTER the lookup
        }
        return {};
    }
};
//<<<END LC1
}

namespace LC26 {
//>>>BEGIN LC26
class Solution {
public:
    int removeDuplicates(vector<int>& v) {
        int n = v.size();
        if (n == 0) return 0;
        int w = 1;                                 // v[0] is always kept
        for (int r = 1; r < n; r++)
            if (v[r] != v[w - 1]) v[w++] = v[r];   // compare with the last KEPT
        return w;
    }
};
//<<<END LC26
}

namespace LC27 {
//>>>BEGIN LC27
class Solution {
public:
    int removeElement(vector<int>& v, int val) {
        int w = 0;                                 // next write slot
        for (int r = 0; r < (int)v.size(); r++)
            if (v[r] != val) v[w++] = v[r];
        return w;                                  // w is also the new length
    }
};
//<<<END LC27
}

namespace LC283 {
//>>>BEGIN LC283
class Solution {
public:
    void moveZeroes(vector<int>& v) {
        int n = v.size(), w = 0;
        for (int r = 0; r < n; r++)
            if (v[r] != 0) v[w++] = v[r];          // pass 1: compact the non-zeros
        while (w < n) v[w++] = 0;                  // pass 2: zero-fill the tail
    }
};
//<<<END LC283
}

namespace LC88 {
//>>>BEGIN LC88
class Solution {
public:
    void merge(vector<int>& a, int m, vector<int>& b, int n) {
        int i = m - 1, j = n - 1, w = m + n - 1;   // fill from the BACK
        while (j >= 0) {
            if (i >= 0 && a[i] > b[j]) a[w--] = a[i--];
            else                       a[w--] = b[j--];
        }
    }
};
//<<<END LC88
}

namespace LC121 {
//>>>BEGIN LC121
class Solution {
public:
    int maxProfit(vector<int>& p) {
        int best = 0, lo = INT_MAX;
        for (int x : p) {
            lo   = min(lo, x);                     // cheapest day so far
            best = max(best, x - lo);              // sell today against it
        }
        return best;
    }
};
//<<<END LC121
}

namespace LC53 {
//>>>BEGIN LC53
class Solution {
public:
    int maxSubArray(vector<int>& v) {
        int best = v[0], cur = v[0];               // NOT 0 — all-negative input
        for (int i = 1; i < (int)v.size(); i++) {
            cur  = max(v[i], cur + v[i]);          // restart here, or extend
            best = max(best, cur);
        }
        return best;
    }
};
//<<<END LC53
}

namespace LC217 {
//>>>BEGIN LC217
class Solution {
public:
    bool containsDuplicate(vector<int>& v) {
        unordered_set<int> seen;
        for (int x : v)
            if (!seen.insert(x).second) return true;   // insert failed -> already in
        return false;
    }
};
//<<<END LC217
}

namespace LC169 {
//>>>BEGIN LC169
class Solution {
public:
    int majorityElement(vector<int>& v) {
        int cand = v[0], count = 0;                // Boyer-Moore vote
        for (int x : v) {
            if (count == 0) cand = x;
            count += (x == cand) ? 1 : -1;
        }
        return cand;      // a majority is guaranteed; otherwise verify in pass 2
    }
};
//<<<END LC169
}

namespace LC268 {
//>>>BEGIN LC268
class Solution {
public:
    int missingNumber(vector<int>& v) {
        int n = v.size(), res = n;                 // seed with n: index n has no v
        for (int i = 0; i < n; i++) res ^= i ^ v[i];
        return res;                                // every present pair cancels
    }
};
//<<<END LC268
}

namespace LC136 {
//>>>BEGIN LC136
class Solution {
public:
    int singleNumber(vector<int>& v) {
        int res = 0;
        for (int x : v) res ^= x;                  // x^x = 0, x^0 = x
        return res;
    }
};
//<<<END LC136
}

namespace LC66 {
//>>>BEGIN LC66
class Solution {
public:
    vector<int> plusOne(vector<int>& d) {
        for (int i = (int)d.size() - 1; i >= 0; i--) {
            if (d[i] < 9) { d[i]++; return d; }    // no carry -> done
            d[i] = 0;                              // 9 -> 0, carry continues
        }
        d.insert(d.begin(), 1);                    // all nines: 999 -> 1000
        return d;
    }
};
//<<<END LC66
}

namespace LC448 {
//>>>BEGIN LC448
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& v) {
        int n = v.size();
        for (int i = 0; i < n; i++) {
            int idx = abs(v[i]) - 1;               // abs: v[i] may be marked
            if (v[idx] > 0) v[idx] = -v[idx];      // mark "value idx+1 is present"
        }
        vector<int> res;
        for (int i = 0; i < n; i++) if (v[i] > 0) res.push_back(i + 1);
        return res;
    }
};
//<<<END LC448
}

// ============================== TIER 2 ======================================

namespace LC167 {
//>>>BEGIN LC167
class Solution {
public:
    vector<int> twoSum(vector<int>& v, int target) {
        int l = 0, r = (int)v.size() - 1;
        while (l < r) {
            int s = v[l] + v[r];
            if (s == target) return {l + 1, r + 1};   // this problem is 1-indexed
            if (s < target) l++;                      // need more -> raise the low end
            else            r--;                      // need less -> lower the high end
        }
        return {};
    }
};
//<<<END LC167
}

namespace LC15 {
//>>>BEGIN LC15
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& v) {
        sort(v.begin(), v.end());
        int n = v.size();
        vector<vector<int>> res;
        for (int i = 0; i + 2 < n; i++) {
            if (v[i] > 0) break;                        // sorted: no triple can reach 0
            if (i > 0 && v[i] == v[i - 1]) continue;    // skip duplicate FIRST element
            int l = i + 1, r = n - 1;
            while (l < r) {
                long long s = (long long)v[i] + v[l] + v[r];
                if (s == 0) {
                    res.push_back({v[i], v[l], v[r]});
                    l++; r--;
                    while (l < r && v[l] == v[l - 1]) l++;   // skip duplicate SECOND
                    while (l < r && v[r] == v[r + 1]) r--;   // skip duplicate THIRD
                } else if (s < 0) l++;
                else              r--;
            }
        }
        return res;
    }
};
//<<<END LC15
}

namespace LC11 {
//>>>BEGIN LC11
class Solution {
public:
    int maxArea(vector<int>& h) {
        int l = 0, r = (int)h.size() - 1, best = 0;
        while (l < r) {
            best = max(best, min(h[l], h[r]) * (r - l));
            if (h[l] < h[r]) l++;                   // move the SHORTER wall
            else             r--;                   // the taller one caps nothing
        }
        return best;
    }
};
//<<<END LC11
}

namespace LC42 {
//>>>BEGIN LC42
class Solution {
public:
    int trap(vector<int>& h) {
        int n = h.size();
        if (n == 0) return 0;
        int l = 0, r = n - 1, lmax = 0, rmax = 0, water = 0;
        while (l < r) {
            if (h[l] < h[r]) {                      // the left side is the limit
                lmax = max(lmax, h[l]);
                water += lmax - h[l];
                l++;
            } else {
                rmax = max(rmax, h[r]);
                water += rmax - h[r];
                r--;
            }
        }
        return water;
    }
};
//<<<END LC42
}

namespace LC75 {
//>>>BEGIN LC75
class Solution {
public:
    void sortColors(vector<int>& v) {
        int low = 0, mid = 0, high = (int)v.size() - 1;
        // [0,low) = 0s   [low,mid) = 1s   [mid,high] = unknown   (high,n) = 2s
        while (mid <= high) {
            if      (v[mid] == 0) swap(v[low++], v[mid++]);
            else if (v[mid] == 1) mid++;
            else                  swap(v[mid], v[high--]);  // mid does NOT advance
        }
    }
};
//<<<END LC75
}

namespace LC209 {
//>>>BEGIN LC209
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& v) {
        int n = v.size(), l = 0, best = INT_MAX;
        long long sum = 0;
        for (int r = 0; r < n; r++) {
            sum += v[r];
            while (sum >= target) {                 // valid -> record, then shrink
                best = min(best, r - l + 1);
                sum -= v[l++];
            }
        }
        return best == INT_MAX ? 0 : best;
    }
};
//<<<END LC209
}

namespace LC3 {
//>>>BEGIN LC3
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int cnt[128] = {0};
        int l = 0, best = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            cnt[(unsigned char)s[r]]++;
            while (cnt[(unsigned char)s[r]] > 1)    // only the new char can clash
                cnt[(unsigned char)s[l++]]--;
            best = max(best, r - l + 1);
        }
        return best;
    }
};
//<<<END LC3
}

namespace LC424 {
//>>>BEGIN LC424
class Solution {
public:
    int characterReplacement(string s, int k) {
        int cnt[26] = {0};
        int l = 0, maxCount = 0, best = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            maxCount = max(maxCount, ++cnt[s[r] - 'A']);
            // window is valid while (length - most frequent) <= k
            while ((r - l + 1) - maxCount > k) cnt[s[l++] - 'A']--;
            best = max(best, r - l + 1);
        }
        return best;
    }
};
//<<<END LC424
}

namespace LC560 {
//>>>BEGIN LC560
class Solution {
public:
    int subarraySum(vector<int>& v, int k) {
        unordered_map<long long,int> seen;
        seen[0] = 1;                                // the empty prefix — essential
        long long pre = 0;
        int count = 0;
        for (int x : v) {
            pre += x;
            auto it = seen.find(pre - k);           // look up BEFORE inserting
            if (it != seen.end()) count += it->second;
            seen[pre]++;
        }
        return count;
    }
};
//<<<END LC560
}

namespace LC238 {
//>>>BEGIN LC238
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& v) {
        int n = v.size();
        vector<int> res(n, 1);
        for (int i = 1; i < n; i++) res[i] = res[i - 1] * v[i - 1];   // left products
        int suf = 1;
        for (int i = n - 1; i >= 0; i--) {                            // right sweep
            res[i] *= suf;
            suf *= v[i];
        }
        return res;
    }
};
//<<<END LC238
}

namespace LC152 {
//>>>BEGIN LC152
class Solution {
public:
    int maxProduct(vector<int>& v) {
        int best = v[0], hi = v[0], lo = v[0];
        for (int i = 1; i < (int)v.size(); i++) {
            if (v[i] < 0) swap(hi, lo);             // a negative flips the roles
            hi = max(v[i], hi * v[i]);
            lo = min(v[i], lo * v[i]);
            best = max(best, hi);
        }
        return best;
    }
};
//<<<END LC152
}

namespace LC56 {
//>>>BEGIN LC56
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& iv) {
        sort(iv.begin(), iv.end());                 // by start, then by end
        vector<vector<int>> res;
        for (auto& cur : iv) {
            if (!res.empty() && cur[0] <= res.back()[1])
                res.back()[1] = max(res.back()[1], cur[1]);  // max: cur may be inside
            else
                res.push_back(cur);
        }
        return res;
    }
};
//<<<END LC56
}

namespace LC33 {
//>>>BEGIN LC33
class Solution {
public:
    int search(vector<int>& v, int target) {
        int lo = 0, hi = (int)v.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (v[mid] == target) return mid;
            if (v[lo] <= v[mid]) {                             // left half sorted
                if (v[lo] <= target && target < v[mid]) hi = mid - 1;
                else                                    lo = mid + 1;
            } else {                                           // right half sorted
                if (v[mid] < target && target <= v[hi]) lo = mid + 1;
                else                                    hi = mid - 1;
            }
        }
        return -1;
    }
};
//<<<END LC33
}

namespace LC153 {
//>>>BEGIN LC153
class Solution {
public:
    int findMin(vector<int>& v) {
        int lo = 0, hi = (int)v.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (v[mid] > v[hi]) lo = mid + 1;      // minimum is strictly right
            else                hi = mid;          // mid could BE the minimum
        }
        return v[lo];                              // compare with hi, never with lo
    }
};
//<<<END LC153
}

namespace LC34 {
//>>>BEGIN LC34
class Solution {
public:
    vector<int> searchRange(vector<int>& v, int target) {
        int lo = lower(v, target);                    // first index >= target
        if (lo == (int)v.size() || v[lo] != target) return {-1, -1};
        return {lo, lower(v, target + 1) - 1};        // first > target, minus one
    }
private:
    int lower(vector<int>& v, int x) {                // binary search template 2
        int lo = 0, hi = v.size();                    // hi = n: "not found" is valid
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (v[mid] >= x) hi = mid;
            else             lo = mid + 1;
        }
        return lo;
    }
};
//<<<END LC34
}

// ============================== TIER 3 ======================================

namespace LC41 {
//>>>BEGIN LC41
class Solution {
public:
    int firstMissingPositive(vector<int>& v) {
        int n = v.size();
        for (int i = 0; i < n; i++)
            // send v[i] to its home slot v[i]-1 until the one at i belongs there
            while (v[i] > 0 && v[i] <= n && v[v[i] - 1] != v[i])
                swap(v[i], v[v[i] - 1]);       // compare VALUES, not v[i] != i+1
        for (int i = 0; i < n; i++)
            if (v[i] != i + 1) return i + 1;   // first slot holding the wrong value
        return n + 1;
    }
};
//<<<END LC41
}

namespace LC287 {
//>>>BEGIN LC287
class Solution {
public:
    int findDuplicate(vector<int>& v) {
        int slow = v[0], fast = v[0];
        do {                                   // phase 1: find a meeting point
            slow = v[slow];
            fast = v[v[fast]];
        } while (slow != fast);
        slow = v[0];                           // phase 2: find the cycle entrance
        while (slow != fast) {
            slow = v[slow];
            fast = v[fast];                    // both one step now
        }
        return slow;
    }
};
//<<<END LC287
}

namespace LC128 {
//>>>BEGIN LC128
class Solution {
public:
    int longestConsecutive(vector<int>& v) {
        unordered_set<int> s(v.begin(), v.end());
        int best = 0;
        for (int x : s) {
            if (s.count(x - 1)) continue;      // only walk from a sequence START
            int len = 1;
            while (s.count(x + len)) len++;    // keeps the whole loop O(n)
            best = max(best, len);
        }
        return best;
    }
};
//<<<END LC128
}

namespace LC73 {
//>>>BEGIN LC73
class Solution {
public:
    void setZeroes(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        bool firstCol = false;
        for (int i = 0; i < m; i++) {          // pass 1: record into row 0 / col 0
            if (g[i][0] == 0) firstCol = true;
            for (int j = 1; j < n; j++)
                if (g[i][j] == 0) { g[i][0] = 0; g[0][j] = 0; }
        }
        for (int i = m - 1; i >= 0; i--) {     // pass 2: BACKWARDS, markers last
            for (int j = n - 1; j >= 1; j--)
                if (g[i][0] == 0 || g[0][j] == 0) g[i][j] = 0;
            if (firstCol) g[i][0] = 0;
        }
    }
};
//<<<END LC73
}

namespace LC48 {
//>>>BEGIN LC48
class Solution {
public:
    void rotate(vector<vector<int>>& g) {
        int n = g.size();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)    // j = i+1: upper triangle only
                swap(g[i][j], g[j][i]);        // transpose
        for (auto& row : g) reverse(row.begin(), row.end());
    }
};
//<<<END LC48
}

namespace LC54 {
//>>>BEGIN LC54
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& g) {
        vector<int> res;
        if (g.empty() || g[0].empty()) return res;
        int top = 0, bot = g.size() - 1, left = 0, right = g[0].size() - 1;
        while (top <= bot && left <= right) {
            for (int j = left; j <= right; j++) res.push_back(g[top][j]);
            top++;
            for (int i = top; i <= bot; i++)   res.push_back(g[i][right]);
            right--;
            if (top <= bot) {                              // guard: one row left
                for (int j = right; j >= left; j--) res.push_back(g[bot][j]);
                bot--;
            }
            if (left <= right) {                           // guard: one column left
                for (int i = bot; i >= top; i--) res.push_back(g[i][left]);
                left++;
            }
        }
        return res;
    }
};
//<<<END LC54
}

namespace LC189 {
//>>>BEGIN LC189
class Solution {
public:
    void rotate(vector<int>& v, int k) {
        int n = v.size();
        if (n == 0) return;
        k %= n;                                        // k can exceed n
        reverse(v.begin(), v.end());
        reverse(v.begin(), v.begin() + k);
        reverse(v.begin() + k, v.end());
    }
};
//<<<END LC189
}

namespace LC239 {
//>>>BEGIN LC239
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& v, int k) {
        deque<int> dq;                                 // INDICES, values decreasing
        vector<int> res;
        for (int i = 0; i < (int)v.size(); i++) {
            if (!dq.empty() && dq.front() <= i - k) dq.pop_front();   // expired
            while (!dq.empty() && v[dq.back()] <= v[i]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) res.push_back(v[dq.front()]);
        }
        return res;
    }
};
//<<<END LC239
}

namespace LC4 {
//>>>BEGIN LC4
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return findMedianSortedArrays(b, a);  // search shorter
        int m = a.size(), n = b.size(), half = (m + n + 1) / 2;
        int lo = 0, hi = m;
        while (lo <= hi) {
            int i = lo + (hi - lo) / 2;            // take i from a, j from b
            int j = half - i;
            int L1 = (i == 0) ? INT_MIN : a[i - 1];
            int R1 = (i == m) ? INT_MAX : a[i];
            int L2 = (j == 0) ? INT_MIN : b[j - 1];
            int R2 = (j == n) ? INT_MAX : b[j];
            if (L1 > R2)      hi = i - 1;          // took too many from a
            else if (L2 > R1) lo = i + 1;          // took too few from a
            else {
                if ((m + n) % 2) return L1 > L2 ? L1 : L2;
                int left  = L1 > L2 ? L1 : L2;
                int right = R1 < R2 ? R1 : R2;
                return (left + right) / 2.0;
            }
        }
        return 0.0;
    }
};
//<<<END LC4
}

namespace LC31 {
//>>>BEGIN LC31
class Solution {
public:
    void nextPermutation(vector<int>& v) {
        int n = v.size(), i = n - 2;
        while (i >= 0 && v[i] >= v[i + 1]) i--;        // 1. rightmost rise v[i]<v[i+1]
        if (i >= 0) {
            int j = n - 1;
            while (v[j] <= v[i]) j--;                  // 2. rightmost value > v[i]
            swap(v[i], v[j]);
        }
        reverse(v.begin() + i + 1, v.end());           // 3. the tail is descending
    }
};
//<<<END LC31
}

// ================================ TESTS =====================================
int main() {
    // ---------------- Tier 1 ----------------
    { LC1::Solution s;   vector<int> v{2,7,11,15};   checkV("LC1 basic", s.twoSum(v,9), {0,1});
                         vector<int> w{3,2,4};       checkV("LC1 mid",   s.twoSum(w,6), {1,2});
                         vector<int> x{3,3};         checkV("LC1 dup",   s.twoSum(x,6), {0,1}); }

    { LC26::Solution s;  vector<int> v{1,1,2};           check("LC26 a", s.removeDuplicates(v), 2);
                         checkV("LC26 a arr", {v[0],v[1]}, {1,2});
                         vector<int> w{0,0,1,1,1,2,2,3,3,4}; check("LC26 b", s.removeDuplicates(w), 5);
                         vector<int> e;                 check("LC26 empty", s.removeDuplicates(e), 0);
                         vector<int> o{7};              check("LC26 one", s.removeDuplicates(o), 1); }

    { LC27::Solution s;  vector<int> v{3,2,2,3};      check("LC27 a", s.removeElement(v,3), 2);
                         vector<int> w{0,1,2,2,3,0,4,2}; check("LC27 b", s.removeElement(w,2), 5);
                         vector<int> a{1,1,1};        check("LC27 all", s.removeElement(a,1), 0); }

    { LC283::Solution s; vector<int> v{0,1,0,3,12};   s.moveZeroes(v); checkV("LC283 a", v, {1,3,12,0,0});
                         vector<int> w{0};            s.moveZeroes(w); checkV("LC283 zero", w, {0});
                         vector<int> x{1,2,3};        s.moveZeroes(x); checkV("LC283 none", x, {1,2,3}); }

    { LC88::Solution s;  vector<int> a{1,2,3,0,0,0}, b{2,5,6};
                         s.merge(a,3,b,3); checkV("LC88 a", a, {1,2,2,3,5,6});
                         vector<int> c{0}, d{1}; s.merge(c,0,d,1); checkV("LC88 empty-a", c, {1});
                         vector<int> e{1}, f{};  s.merge(e,1,f,0); checkV("LC88 empty-b", e, {1}); }

    { LC121::Solution s; vector<int> v{7,1,5,3,6,4};  check("LC121 a", s.maxProfit(v), 5);
                         vector<int> w{7,6,4,3,1};    check("LC121 desc", s.maxProfit(w), 0);
                         vector<int> o{5};            check("LC121 one", s.maxProfit(o), 0); }

    { LC53::Solution s;  vector<int> v{-2,1,-3,4,-1,2,1,-5,4}; check("LC53 a", s.maxSubArray(v), 6);
                         vector<int> w{-3,-1,-2};     check("LC53 all-neg", s.maxSubArray(w), -1);
                         vector<int> o{1};            check("LC53 one", s.maxSubArray(o), 1);
                         vector<int> p{5,4,-1,7,8};   check("LC53 b", s.maxSubArray(p), 23); }

    { LC217::Solution s; vector<int> v{1,2,3,1};      check("LC217 yes", s.containsDuplicate(v), true);
                         vector<int> w{1,2,3,4};      check("LC217 no",  s.containsDuplicate(w), false);
                         vector<int> e;               check("LC217 empty", s.containsDuplicate(e), false); }

    { LC169::Solution s; vector<int> v{3,2,3};        check("LC169 a", s.majorityElement(v), 3);
                         vector<int> w{2,2,1,1,1,2,2};check("LC169 b", s.majorityElement(w), 2);
                         vector<int> o{1};            check("LC169 one", s.majorityElement(o), 1); }

    { LC268::Solution s; vector<int> v{3,0,1};        check("LC268 a", s.missingNumber(v), 2);
                         vector<int> w{0,1};          check("LC268 last", s.missingNumber(w), 2);
                         vector<int> x{1};            check("LC268 zero", s.missingNumber(x), 0);
                         vector<int> y{9,6,4,2,3,5,7,0,1}; check("LC268 b", s.missingNumber(y), 8); }

    { LC136::Solution s; vector<int> v{4,1,2,1,2};    check("LC136 a", s.singleNumber(v), 4);
                         vector<int> o{1};            check("LC136 one", s.singleNumber(o), 1); }

    { LC66::Solution s;  vector<int> v{1,2,3};  checkV("LC66 a", s.plusOne(v), {1,2,4});
                         vector<int> w{4,3,2,1}; checkV("LC66 b", s.plusOne(w), {4,3,2,2});
                         vector<int> x{9};      checkV("LC66 nine", s.plusOne(x), {1,0});
                         vector<int> y{9,9,9};  checkV("LC66 all9", s.plusOne(y), {1,0,0,0}); }

    { LC448::Solution s; vector<int> v{4,3,2,7,8,2,3,1}; checkV("LC448 a", s.findDisappearedNumbers(v), {5,6});
                         vector<int> w{1,1};             checkV("LC448 b", s.findDisappearedNumbers(w), {2});
                         vector<int> x{1,2,3};           checkV("LC448 none", s.findDisappearedNumbers(x), {}); }

    // ---------------- Tier 2 ----------------
    { LC167::Solution s; vector<int> v{2,7,11,15}; checkV("LC167 a", s.twoSum(v,9),  {1,2});
                         vector<int> w{2,3,4};     checkV("LC167 b", s.twoSum(w,6),  {1,3});
                         vector<int> x{-1,0};      checkV("LC167 neg", s.twoSum(x,-1), {1,2}); }

    { LC15::Solution s;  vector<int> v{-1,0,1,2,-1,-4};
                         vector<vector<int>> want{{-1,-1,2},{-1,0,1}};
                         check("LC15 a", s.threeSum(v), want);
                         vector<int> z{0,0,0,0};   vector<vector<int>> wz{{0,0,0}};
                         check("LC15 zeros", s.threeSum(z), wz);
                         vector<int> n{1,2,3};     vector<vector<int>> wn{};
                         check("LC15 none", s.threeSum(n), wn); }

    { LC11::Solution s;  vector<int> v{1,8,6,2,5,4,8,3,7}; check("LC11 a", s.maxArea(v), 49);
                         vector<int> w{1,1};               check("LC11 two", s.maxArea(w), 1); }

    { LC42::Solution s;  vector<int> v{0,1,0,2,1,0,1,3,2,1,2,1}; check("LC42 a", s.trap(v), 6);
                         vector<int> w{4,2,0,3,2,5};             check("LC42 b", s.trap(w), 9);
                         vector<int> e;                          check("LC42 empty", s.trap(e), 0);
                         vector<int> u{1,2,3};                   check("LC42 up", s.trap(u), 0); }

    { LC75::Solution s;  vector<int> v{2,0,2,1,1,0}; s.sortColors(v); checkV("LC75 a", v, {0,0,1,1,2,2});
                         vector<int> w{2,0,1};       s.sortColors(w); checkV("LC75 b", w, {0,1,2});
                         vector<int> o{0};           s.sortColors(o); checkV("LC75 one", o, {0});
                         vector<int> t{2,2,2,2};     s.sortColors(t); checkV("LC75 same", t, {2,2,2,2}); }

    { LC209::Solution s; vector<int> v{2,3,1,2,4,3}; check("LC209 a", s.minSubArrayLen(7,v), 2);
                         vector<int> w{1,4,4};       check("LC209 b", s.minSubArrayLen(4,w), 1);
                         vector<int> x{1,1,1,1,1,1,1,1}; check("LC209 none", s.minSubArrayLen(11,x), 0); }

    { LC3::Solution s;   check("LC3 a", s.lengthOfLongestSubstring("abcabcbb"), 3);
                         check("LC3 same", s.lengthOfLongestSubstring("bbbbb"), 1);
                         check("LC3 c", s.lengthOfLongestSubstring("pwwkew"), 3);
                         check("LC3 empty", s.lengthOfLongestSubstring(""), 0); }

    { LC424::Solution s; check("LC424 a", s.characterReplacement("ABAB", 2), 4);
                         check("LC424 b", s.characterReplacement("AABABBA", 1), 4);
                         check("LC424 zero", s.characterReplacement("ABCDE", 0), 1); }

    { LC560::Solution s; vector<int> v{1,1,1};   check("LC560 a", s.subarraySum(v,2), 2);
                         vector<int> w{1,2,3};   check("LC560 b", s.subarraySum(w,3), 2);
                         vector<int> x{3};       check("LC560 start", s.subarraySum(x,3), 1);
                         vector<int> y{1,-1,0};  check("LC560 neg", s.subarraySum(y,0), 3); }

    { LC238::Solution s; vector<int> v{1,2,3,4};   checkV("LC238 a", s.productExceptSelf(v), {24,12,8,6});
                         vector<int> w{-1,1,0,-3,3}; checkV("LC238 zero", s.productExceptSelf(w), {0,0,9,0,0}); }

    { LC152::Solution s; vector<int> v{2,3,-2,4};  check("LC152 a", s.maxProduct(v), 6);
                         vector<int> w{-2,0,-1};   check("LC152 b", s.maxProduct(w), 0);
                         vector<int> x{-2,3,-4};   check("LC152 c", s.maxProduct(x), 24);
                         vector<int> o{-3};        check("LC152 one", s.maxProduct(o), -3); }

    { LC56::Solution s;  vector<vector<int>> v{{1,3},{2,6},{8,10},{15,18}};
                         vector<vector<int>> w{{1,6},{8,10},{15,18}};
                         check("LC56 a", s.merge(v), w);
                         vector<vector<int>> t{{1,4},{4,5}}, tw{{1,5}};
                         check("LC56 touch", s.merge(t), tw);
                         vector<vector<int>> c{{1,10},{2,3}}, cw{{1,10}};
                         check("LC56 contained", s.merge(c), cw); }

    { LC33::Solution s;  vector<int> v{4,5,6,7,0,1,2}; check("LC33 a", s.search(v,0), 4);
                         check("LC33 miss", s.search(v,3), -1);
                         check("LC33 first", s.search(v,4), 0);
                         vector<int> o{1};             check("LC33 one", s.search(o,1), 0);
                         vector<int> t{3,1};           check("LC33 two", s.search(t,1), 1); }

    { LC153::Solution s; vector<int> v{3,4,5,1,2};   check("LC153 a", s.findMin(v), 1);
                         vector<int> w{4,5,6,7,0,1,2}; check("LC153 b", s.findMin(w), 0);
                         vector<int> x{11,13,15,17}; check("LC153 unrotated", s.findMin(x), 11);
                         vector<int> o{1};           check("LC153 one", s.findMin(o), 1); }

    { LC34::Solution s;  vector<int> v{5,7,7,8,8,10}; checkV("LC34 a", s.searchRange(v,8), {3,4});
                         checkV("LC34 miss", s.searchRange(v,6), {-1,-1});
                         vector<int> e;                checkV("LC34 empty", s.searchRange(e,0), {-1,-1});
                         vector<int> s1{1};            checkV("LC34 one", s.searchRange(s1,1), {0,0}); }

    // ---------------- Tier 3 ----------------
    { LC41::Solution s;  vector<int> v{1,2,0};       check("LC41 a", s.firstMissingPositive(v), 3);
                         vector<int> w{3,4,-1,1};    check("LC41 b", s.firstMissingPositive(w), 2);
                         vector<int> x{7,8,9,11,12}; check("LC41 c", s.firstMissingPositive(x), 1);
                         vector<int> d{1,1};         check("LC41 dup", s.firstMissingPositive(d), 2); }

    { LC287::Solution s; vector<int> v{1,3,4,2,2};   check("LC287 a", s.findDuplicate(v), 2);
                         vector<int> w{3,1,3,4,2};   check("LC287 b", s.findDuplicate(w), 3);
                         vector<int> x{2,2,2,2,2};   check("LC287 all", s.findDuplicate(x), 2); }

    { LC128::Solution s; vector<int> v{100,4,200,1,3,2}; check("LC128 a", s.longestConsecutive(v), 4);
                         vector<int> w{0,3,7,2,5,8,4,6,0,1}; check("LC128 b", s.longestConsecutive(w), 9);
                         vector<int> e;                check("LC128 empty", s.longestConsecutive(e), 0); }

    { LC73::Solution s;  vector<vector<int>> g{{1,1,1},{1,0,1},{1,1,1}};
                         vector<vector<int>> w{{1,0,1},{0,0,0},{1,0,1}};
                         s.setZeroes(g); check("LC73 a", g, w);
                         vector<vector<int>> h{{0,1,2,0},{3,4,5,2},{1,3,1,5}};
                         vector<vector<int>> i{{0,0,0,0},{0,4,5,0},{0,3,1,0}};
                         s.setZeroes(h); check("LC73 b", h, i); }

    { LC48::Solution s;  vector<vector<int>> g{{1,2,3},{4,5,6},{7,8,9}};
                         vector<vector<int>> w{{7,4,1},{8,5,2},{9,6,3}};
                         s.rotate(g); check("LC48 a", g, w);
                         vector<vector<int>> o{{1}}, ow{{1}}; s.rotate(o); check("LC48 one", o, ow); }

    { LC54::Solution s;  vector<vector<int>> g{{1,2,3},{4,5,6},{7,8,9}};
                         checkV("LC54 a", s.spiralOrder(g), {1,2,3,6,9,8,7,4,5});
                         vector<vector<int>> r{{1,2,3}};
                         checkV("LC54 row", s.spiralOrder(r), {1,2,3});
                         vector<vector<int>> c{{1},{2},{3}};
                         checkV("LC54 col", s.spiralOrder(c), {1,2,3});
                         vector<vector<int>> b{{1,2,3,4},{5,6,7,8},{9,10,11,12}};
                         checkV("LC54 b", s.spiralOrder(b), {1,2,3,4,8,12,11,10,9,5,6,7}); }

    { LC189::Solution s; vector<int> v{1,2,3,4,5,6,7}; s.rotate(v,3); checkV("LC189 a", v, {5,6,7,1,2,3,4});
                         vector<int> w{-1,-100,3,99};  s.rotate(w,2); checkV("LC189 b", w, {3,99,-1,-100});
                         vector<int> x{1,2};           s.rotate(x,5); checkV("LC189 big-k", x, {2,1});
                         vector<int> o{1};             s.rotate(o,0); checkV("LC189 one", o, {1}); }

    { LC239::Solution s; vector<int> v{1,3,-1,-3,5,3,6,7};
                         checkV("LC239 a", s.maxSlidingWindow(v,3), {3,3,5,5,6,7});
                         vector<int> o{1};  checkV("LC239 one", s.maxSlidingWindow(o,1), {1});
                         vector<int> d{9,8,7,6}; checkV("LC239 desc", s.maxSlidingWindow(d,2), {9,8,7}); }

    { LC4::Solution s;   vector<int> a{1,3}, b{2};      check("LC4 odd",  s.findMedianSortedArrays(a,b), 2.0);
                         vector<int> c{1,2}, d{3,4};    check("LC4 even", s.findMedianSortedArrays(c,d), 2.5);
                         vector<int> e{}, f{1};         check("LC4 empty", s.findMedianSortedArrays(e,f), 1.0);
                         vector<int> g{1,2,3,4}, h{5};  check("LC4 skew", s.findMedianSortedArrays(g,h), 3.0); }

    { LC31::Solution s;  vector<int> v{1,2,3}; s.nextPermutation(v); checkV("LC31 a", v, {1,3,2});
                         vector<int> w{3,2,1}; s.nextPermutation(w); checkV("LC31 wrap", w, {1,2,3});
                         vector<int> x{1,1,5}; s.nextPermutation(x); checkV("LC31 dup", x, {1,5,1});
                         vector<int> y{1,3,2}; s.nextPermutation(y); checkV("LC31 b", y, {2,1,3});
                         vector<int> o{1};     s.nextPermutation(o); checkV("LC31 one", o, {1}); }

    cout << "\n" << g_pass << " passed, " << g_fail << " failed.\n";
    if (g_fail == 0) cout << "ALL TESTS PASSED\n";
    return g_fail == 0 ? 0 : 1;
}
