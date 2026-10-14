// ============================================================================
//  Hashing — reference solutions for Part 16 of the guide
//  All 38 problems, Tier 1 -> Tier 2 -> Tier 3, each with test cases.
//
//  Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part16-solutions.cpp && ./ref
//
//  Every solution lives in its own namespace so each class can be called
//  Solution, exactly as LeetCode expects. The //>>>BEGIN / //<<<END markers
//  delimit the code that is printed in Hashing-Solved-Questions.pdf, so the
//  book can never drift from the code that was actually tested.
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

// ----------------------------------------------------------------------- LC 1
namespace LC1 {
//>>>BEGIN LC1
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;              // value -> index
        for (int i = 0; i < (int)nums.size(); i++) {
            int need = target - nums[i];           // the complement question
            auto it = seen.find(need);
            if (it != seen.end()) return {it->second, i};
            seen[nums[i]] = i;                     // insert AFTER the lookup
        }
        return {};
    }
};
//<<<END LC1
}

// --------------------------------------------------------------------- LC 217
namespace LC217 {
//>>>BEGIN LC217
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int x : nums)
            if (!seen.insert(x).second) return true;   // insert says "already there"
        return false;
    }
};
//<<<END LC217
}

// --------------------------------------------------------------------- LC 242
namespace LC242 {
//>>>BEGIN LC242
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int cnt[26] = {0};                      // an array IS a hash map for 26 keys
        for (int i = 0; i < (int)s.size(); i++) {
            cnt[s[i] - 'a']++;
            cnt[t[i] - 'a']--;
        }
        for (int c : cnt) if (c != 0) return false;
        return true;
    }
};
//<<<END LC242
}

// --------------------------------------------------------------------- LC 383
namespace LC383 {
//>>>BEGIN LC383
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int cnt[26] = {0};
        for (char c : magazine) cnt[c - 'a']++;        // supply
        for (char c : ransomNote)
            if (--cnt[c - 'a'] < 0) return false;       // demand exceeds supply
        return true;
    }
};
//<<<END LC383
}

// --------------------------------------------------------------------- LC 387
namespace LC387 {
//>>>BEGIN LC387
class Solution {
public:
    int firstUniqChar(string s) {
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;                // pass 1: count
        for (int i = 0; i < (int)s.size(); i++)         // pass 2: first with count 1
            if (cnt[s[i] - 'a'] == 1) return i;
        return -1;
    }
};
//<<<END LC387
}

// --------------------------------------------------------------------- LC 205
namespace LC205 {
//>>>BEGIN LC205
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        // a BIJECTION needs two maps: s->t and t->s. 0 means "not mapped yet".
        char st[256] = {0}, ts[256] = {0};
        for (int i = 0; i < (int)s.size(); i++) {
            unsigned char a = s[i], b = t[i];
            if (st[a] == 0 && ts[b] == 0) { st[a] = b; ts[b] = a; }
            else if (st[a] != (char)b || ts[b] != (char)a) return false;
        }
        return true;
    }
};
//<<<END LC205
}

// --------------------------------------------------------------------- LC 290
namespace LC290 {
//>>>BEGIN LC290
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        vector<string> words;
        stringstream ss(s);
        for (string w; ss >> w;) words.push_back(w);
        if (words.size() != pattern.size()) return false;
        unordered_map<char, string> p2w;
        unordered_map<string, char> w2p;
        for (int i = 0; i < (int)words.size(); i++) {
            char p = pattern[i];
            const string& w = words[i];
            if (p2w.count(p) && p2w[p] != w) return false;   // p already means something else
            if (w2p.count(w) && w2p[w] != p) return false;   // w already belongs to another p
            p2w[p] = w; w2p[w] = p;
        }
        return true;
    }
};
//<<<END LC290
}

// --------------------------------------------------------------------- LC 349
namespace LC349 {
//>>>BEGIN LC349
class Solution {
public:
    vector<int> intersection(vector<int>& a, vector<int>& b) {
        unordered_set<int> inA(a.begin(), a.end());
        vector<int> res;
        for (int x : b)
            if (inA.erase(x)) res.push_back(x);   // erase returns 1 once, then 0
        return res;
    }
};
//<<<END LC349
}

// --------------------------------------------------------------------- LC 350
namespace LC350 {
//>>>BEGIN LC350
class Solution {
public:
    vector<int> intersect(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return intersect(b, a);   // count the smaller array
        unordered_map<int, int> cnt;
        for (int x : a) cnt[x]++;
        vector<int> res;
        for (int x : b) {
            auto it = cnt.find(x);
            if (it != cnt.end() && it->second > 0) { res.push_back(x); it->second--; }
        }
        return res;
    }
};
//<<<END LC350
}

// --------------------------------------------------------------------- LC 202
namespace LC202 {
//>>>BEGIN LC202
class Solution {
    int next(int n) {
        int s = 0;
        for (; n; n /= 10) s += (n % 10) * (n % 10);
        return s;
    }
public:
    bool isHappy(int n) {
        unordered_set<int> seen;                 // a repeat means we are in a cycle
        while (n != 1 && !seen.count(n)) {
            seen.insert(n);
            n = next(n);
        }
        return n == 1;
    }
};
//<<<END LC202
}

// --------------------------------------------------------------------- LC 219
namespace LC219 {
//>>>BEGIN LC219
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> last;            // value -> most recent index
        for (int i = 0; i < (int)nums.size(); i++) {
            auto it = last.find(nums[i]);
            if (it != last.end() && i - it->second <= k) return true;
            last[nums[i]] = i;                   // keep only the LATEST position
        }
        return false;
    }
};
//<<<END LC219
}

// -------------------------------------------------------------------- LC 1512
namespace LC1512 {
//>>>BEGIN LC1512
class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int pairs = 0;
        for (int x : nums) {
            pairs += cnt[x];        // x pairs with every earlier copy of itself
            cnt[x]++;
        }
        return pairs;
    }
};
//<<<END LC1512
}

// --------------------------------------------------------------------- LC 706
namespace LC706 {
//>>>BEGIN LC706
class MyHashMap {
    static const int B = 10007;                       // prime number of buckets
    vector<list<pair<int, int>>> buckets;             // separate chaining
    list<pair<int, int>>& bucket(int key) { return buckets[key % B]; }
public:
    MyHashMap() : buckets(B) {}
    void put(int key, int value) {
        for (auto& kv : bucket(key))
            if (kv.first == key) { kv.second = value; return; }   // overwrite
        bucket(key).push_back({key, value});
    }
    int get(int key) {
        for (auto& kv : bucket(key)) if (kv.first == key) return kv.second;
        return -1;
    }
    void remove(int key) {
        bucket(key).remove_if([key](const pair<int, int>& kv) { return kv.first == key; });
    }
};
//<<<END LC706
}

// ============================================================================
//  TIER 2
// ============================================================================

// ---------------------------------------------------------------------- LC 49
namespace LC49 {
//>>>BEGIN LC49
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            // signature: 26 counts, written out as a string key -> O(L) per word
            string key(26, 0);
            for (char c : s) key[c - 'a']++;
            groups[key].push_back(s);
        }
        vector<vector<string>> res;
        for (auto& [key, g] : groups) res.push_back(move(g));
        return res;
    }
};
//<<<END LC49
}

// --------------------------------------------------------------------- LC 128
namespace LC128 {
//>>>BEGIN LC128
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int best = 0;
        for (int x : s) {
            if (s.count(x - 1)) continue;        // not the START of a run: skip
            int len = 1;
            while (s.count(x + len)) len++;      // walk the run once, from its start
            best = max(best, len);
        }
        return best;
    }
};
//<<<END LC128
}

// --------------------------------------------------------------------- LC 560
namespace LC560 {
//>>>BEGIN LC560
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> seen{{0, 1}};    // prefix sum -> how many times; empty prefix
        int prefix = 0, count = 0;
        for (int x : nums) {
            prefix += x;
            // a subarray (j, i] sums to k  <=>  prefix[j] == prefix[i] - k
            auto it = seen.find(prefix - k);
            if (it != seen.end()) count += it->second;
            seen[prefix]++;
        }
        return count;
    }
};
//<<<END LC560
}

// --------------------------------------------------------------------- LC 525
namespace LC525 {
//>>>BEGIN LC525
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> first{{0, -1}};  // balance -> FIRST index it was seen
        int bal = 0, best = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            bal += nums[i] ? 1 : -1;             // 1 -> +1, 0 -> -1
            auto it = first.find(bal);
            if (it != first.end()) best = max(best, i - it->second);
            else first[bal] = i;                 // never overwrite: earliest = longest
        }
        return best;
    }
};
//<<<END LC525
}

// --------------------------------------------------------------------- LC 974
namespace LC974 {
//>>>BEGIN LC974
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> cnt(k, 0);                   // remainder -> count (array as map)
        cnt[0] = 1;
        int prefix = 0, res = 0;
        for (int x : nums) {
            prefix = ((prefix + x) % k + k) % k; // keep the remainder NON-negative
            res += cnt[prefix];                  // equal remainders -> divisible gap
            cnt[prefix]++;
        }
        return res;
    }
};
//<<<END LC974
}

// --------------------------------------------------------------------- LC 454
namespace LC454 {
//>>>BEGIN LC454
class Solution {
public:
    int fourSumCount(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d) {
        unordered_map<int, int> ab;              // every a+b, with multiplicity
        for (int x : a) for (int y : b) ab[x + y]++;
        int res = 0;
        for (int x : c)
            for (int y : d) {
                auto it = ab.find(-(x + y));     // meet in the middle
                if (it != ab.end()) res += it->second;
            }
        return res;
    }
};
//<<<END LC454
}

// ---------------------------------------------------------------------- LC 36
namespace LC36 {
//>>>BEGIN LC36
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row[9][9] = {}, col[9][9] = {}, box[9][9] = {};
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') continue;
                int d = board[r][c] - '1', b = (r / 3) * 3 + c / 3;
                if (row[r][d] || col[c][d] || box[b][d]) return false;   // seen before
                row[r][d] = col[c][d] = box[b][d] = true;
            }
        return true;
    }
};
//<<<END LC36
}

// --------------------------------------------------------------------- LC 380
namespace LC380 {
//>>>BEGIN LC380
class RandomizedSet {
    vector<int> vals;                       // dense: random access by index
    unordered_map<int, int> pos;            // value -> its index in vals
public:
    bool insert(int val) {
        if (pos.count(val)) return false;
        pos[val] = vals.size();
        vals.push_back(val);
        return true;
    }
    bool remove(int val) {
        auto it = pos.find(val);
        if (it == pos.end()) return false;
        int i = it->second, last = vals.back();
        vals[i] = last;  pos[last] = i;     // move the last element into the hole
        vals.pop_back(); pos.erase(val);    // erase val LAST (it may equal `last`)
        return true;
    }
    int getRandom() { return vals[rand() % vals.size()]; }
};
//<<<END LC380
}

// --------------------------------------------------------------------- LC 146
namespace LC146 {
//>>>BEGIN LC146
class LRUCache {
    int cap;
    list<pair<int, int>> order;                                // front = most recent
    unordered_map<int, list<pair<int, int>>::iterator> where;  // key -> its list node
public:
    LRUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        auto it = where.find(key);
        if (it == where.end()) return -1;
        order.splice(order.begin(), order, it->second);  // move to front, O(1)
        return it->second->second;
    }
    void put(int key, int value) {
        auto it = where.find(key);
        if (it != where.end()) {
            it->second->second = value;
            order.splice(order.begin(), order, it->second);
            return;
        }
        if ((int)order.size() == cap) {                  // evict least recent
            where.erase(order.back().first);
            order.pop_back();
        }
        order.push_front({key, value});
        where[key] = order.begin();
    }
};
//<<<END LC146
}

// --------------------------------------------------------------------- LC 438
namespace LC438 {
//>>>BEGIN LC438
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n = s.size(), m = p.size();
        if (m > n) return res;
        int need[26] = {0}, have[26] = {0};
        for (char c : p) need[c - 'a']++;
        for (int i = 0; i < n; i++) {
            have[s[i] - 'a']++;                         // char enters the window
            if (i >= m) have[s[i - m] - 'a']--;         // char leaves the window
            if (i >= m - 1 && equal(need, need + 26, have)) res.push_back(i - m + 1);
        }
        return res;
    }
};
//<<<END LC438
}

// ----------------------------------------------------------------------- LC 3
namespace LC3 {
//>>>BEGIN LC3
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> last(256, -1);              // char -> last index seen
        int best = 0, left = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            unsigned char c = s[i];
            if (last[c] >= left) left = last[c] + 1;   // repeat INSIDE the window: jump
            last[c] = i;
            best = max(best, i - left + 1);
        }
        return best;
    }
};
//<<<END LC3
}

// --------------------------------------------------------------------- LC 523
namespace LC523 {
//>>>BEGIN LC523
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> first{{0, -1}};   // remainder -> earliest index
        int prefix = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            prefix = (prefix + nums[i]) % k;
            auto it = first.find(prefix);
            if (it != first.end()) {
                if (i - it->second >= 2) return true;   // length at least 2
            } else {
                first[prefix] = i;                      // keep the EARLIEST
            }
        }
        return false;
    }
};
//<<<END LC523
}

// -------------------------------------------------------------------- LC 1010
namespace LC1010 {
//>>>BEGIN LC1010
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        int cnt[60] = {0};
        int pairs = 0;
        for (int t : time) {
            int r = t % 60;
            pairs += cnt[(60 - r) % 60];    // the complement remainder; (60-0)%60 = 0
            cnt[r]++;
        }
        return pairs;
    }
};
//<<<END LC1010
}

// --------------------------------------------------------------------- LC 554
namespace LC554 {
//>>>BEGIN LC554
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> edges;      // x position -> rows with an edge there
        int most = 0;
        for (auto& row : wall) {
            int x = 0;
            for (int i = 0; i + 1 < (int)row.size(); i++) {   // skip the wall's right edge
                x += row[i];
                most = max(most, ++edges[x]);
            }
        }
        return (int)wall.size() - most;     // cut where the most edges line up
    }
};
//<<<END LC554
}

// --------------------------------------------------------------------- LC 187
namespace LC187 {
//>>>BEGIN LC187
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        // 4 letters -> 2 bits each; a 10-letter window fits in 20 bits exactly,
        // so this "hash" is PERFECT: no collisions possible
        auto code = [](char c) { return c == 'A' ? 0 : c == 'C' ? 1 : c == 'G' ? 2 : 3; };
        unordered_map<int, int> seen;
        vector<string> res;
        int h = 0, mask = (1 << 20) - 1;
        for (int i = 0; i < (int)s.size(); i++) {
            h = ((h << 2) | code(s[i])) & mask;     // roll: drop the oldest letter
            if (i >= 9 && ++seen[h] == 2)           // report on the SECOND sighting only
                res.push_back(s.substr(i - 9, 10));
        }
        return res;
    }
};
//<<<END LC187
}

// ============================================================================
//  TIER 3
// ============================================================================

// ---------------------------------------------------------------------- LC 41
namespace LC41 {
//>>>BEGIN LC41
class Solution {
public:
    int firstMissingPositive(vector<int>& a) {
        int n = a.size();
        // the array is its own hash table: value v belongs at index v-1
        for (int i = 0; i < n; i++)
            while (a[i] >= 1 && a[i] <= n && a[a[i] - 1] != a[i])
                swap(a[i], a[a[i] - 1]);            // send a[i] home
        for (int i = 0; i < n; i++)
            if (a[i] != i + 1) return i + 1;        // first slot with the wrong owner
        return n + 1;
    }
};
//<<<END LC41
}

// ---------------------------------------------------------------------- LC 76
namespace LC76 {
//>>>BEGIN LC76
class Solution {
public:
    string minWindow(string s, string t) {
        int need[128] = {0};
        for (char c : t) need[(int)c]++;
        int missing = t.size();             // characters of t still not covered
        int bestL = 0, bestLen = INT_MAX, left = 0;
        for (int right = 0; right < (int)s.size(); right++) {
            if (need[(int)s[right]]-- > 0) missing--;          // a useful character
            while (missing == 0) {                             // valid: try to shrink
                if (right - left + 1 < bestLen) { bestLen = right - left + 1; bestL = left; }
                if (++need[(int)s[left]] > 0) missing++;       // dropped a needed char
                left++;
            }
        }
        return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
    }
};
//<<<END LC76
}

// ---------------------------------------------------------------------- LC 30
namespace LC30 {
//>>>BEGIN LC30
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int w = words[0].size(), k = words.size(), n = s.size();
        unordered_map<string, int> need;
        for (auto& x : words) need[x]++;
        for (int off = 0; off < w; off++) {           // w separate word-aligned grids
            unordered_map<string, int> have;
            int left = off, used = 0;
            for (int right = off; right + w <= n; right += w) {
                string word = s.substr(right, w);
                if (!need.count(word)) { have.clear(); used = 0; left = right + w; continue; }
                have[word]++; used++;
                while (have[word] > need[word]) {     // too many copies: shrink
                    have[s.substr(left, w)]--; used--; left += w;
                }
                if (used == k) res.push_back(left);
            }
        }
        return res;
    }
};
//<<<END LC30
}

// --------------------------------------------------------------------- LC 149
namespace LC149 {
//>>>BEGIN LC149
class Solution {
public:
    int maxPoints(vector<vector<int>>& p) {
        int n = p.size(), best = min(n, 1);
        for (int i = 0; i < n; i++) {
            map<pair<int, int>, int> slopes;          // reduced (dy, dx) -> count
            for (int j = i + 1; j < n; j++) {
                int dy = p[j][1] - p[i][1], dx = p[j][0] - p[i][0];
                int g = gcd(dy, dx);                  // exact slope, no doubles
                dy /= g; dx /= g;
                if (dx < 0 || (dx == 0 && dy < 0)) { dx = -dx; dy = -dy; }   // one sign form
                best = max(best, ++slopes[{dy, dx}] + 1);   // +1 for point i itself
            }
        }
        return best;
    }
};
//<<<END LC149
}

// --------------------------------------------------------------------- LC 460
namespace LC460 {
//>>>BEGIN LC460
class LFUCache {
    struct Entry { int value, freq; list<int>::iterator it; };
    int cap, minFreq = 0;
    unordered_map<int, Entry> data;              // key -> value, freq, place in its list
    unordered_map<int, list<int>> byFreq;        // freq -> keys, most recent at front
    void touch(int key) {                        // bump a key's frequency by one
        Entry& e = data[key];
        byFreq[e.freq].erase(e.it);
        if (byFreq[e.freq].empty()) {
            byFreq.erase(e.freq);
            if (minFreq == e.freq) minFreq++;
        }
        byFreq[++e.freq].push_front(key);
        e.it = byFreq[e.freq].begin();
    }
public:
    LFUCache(int capacity) : cap(capacity) {}
    int get(int key) {
        if (!data.count(key)) return -1;
        touch(key); return data[key].value;
    }
    void put(int key, int value) {
        if (cap == 0) return;
        if (data.count(key)) { data[key].value = value; touch(key); return; }
        if ((int)data.size() == cap) {           // evict: lowest freq, then least recent
            int victim = byFreq[minFreq].back();
            byFreq[minFreq].pop_back();
            if (byFreq[minFreq].empty()) byFreq.erase(minFreq);
            data.erase(victim);
        }
        byFreq[1].push_front(key);
        data[key] = {value, 1, byFreq[1].begin()};
        minFreq = 1;                             // a new key always has the lowest freq
    }
};
//<<<END LC460
}

// -------------------------------------------------------------------- LC 1074
namespace LC1074 {
//>>>BEGIN LC1074
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& m, int target) {
        int R = m.size(), C = m[0].size(), res = 0;
        for (int top = 0; top < R; top++) {
            vector<int> colSum(C, 0);                 // column sums of rows top..bottom
            for (int bottom = top; bottom < R; bottom++) {
                for (int c = 0; c < C; c++) colSum[c] += m[bottom][c];
                // now it is LC 560 on a 1-D array
                unordered_map<int, int> seen{{0, 1}};
                int prefix = 0;
                for (int c = 0; c < C; c++) {
                    prefix += colSum[c];
                    auto it = seen.find(prefix - target);
                    if (it != seen.end()) res += it->second;
                    seen[prefix]++;
                }
            }
        }
        return res;
    }
};
//<<<END LC1074
}

// --------------------------------------------------------------------- LC 992
namespace LC992 {
//>>>BEGIN LC992
class Solution {
    // number of subarrays with AT MOST k distinct values
    int atMost(const vector<int>& a, int k) {
        unordered_map<int, int> cnt;
        int left = 0, res = 0;
        for (int right = 0; right < (int)a.size(); right++) {
            if (cnt[a[right]]++ == 0) k--;            // a new distinct value
            while (k < 0) {
                if (--cnt[a[left]] == 0) k++;         // a value fully left the window
                left++;
            }
            res += right - left + 1;                  // every subarray ending at right
        }
        return res;
    }
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);   // exactly = atMost(k) - atMost(k-1)
    }
};
//<<<END LC992
}

// --------------------------------------------------------------------- LC 336
namespace LC336 {
//>>>BEGIN LC336
class Solution {
    bool isPal(const string& s, int l, int r) {
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> idx;               // reversed word -> its index
        for (int i = 0; i < (int)words.size(); i++)
            idx[string(words[i].rbegin(), words[i].rend())] = i;
        vector<vector<int>> res;
        for (int i = 0; i < (int)words.size(); i++) {
            const string& w = words[i];
            int L = w.size();
            for (int j = 0; j <= L; j++) {            // split w = w[0..j) + w[j..L)
                // left part is a palindrome: reverse(right) + w is a palindrome
                if (isPal(w, 0, j - 1)) {
                    auto it = idx.find(w.substr(j));
                    if (it != idx.end() && it->second != i) res.push_back({it->second, i});
                }
                // right part is a palindrome: w + reverse(left) is a palindrome
                if (j < L && isPal(w, j, L - 1)) {    // j < L avoids double counting
                    auto it = idx.find(w.substr(0, j));
                    if (it != idx.end() && it->second != i) res.push_back({i, it->second});
                }
            }
        }
        return res;
    }
};
//<<<END LC336
}

// -------------------------------------------------------------------- LC 1044
namespace LC1044 {
//>>>BEGIN LC1044
class Solution {
    string s;
    // start of some substring of length L that appears twice, or -1
    int dupOfLength(int L) {
        typedef unsigned long long u64;               // arithmetic mod 2^64, for free
        const u64 B = 131;
        u64 h = 0, pw = 1;
        for (int i = 0; i < L; i++) { h = h * B + s[i]; pw *= B; }
        unordered_map<u64, vector<int>> seen{{h, {0}}};
        for (int i = L; i < (int)s.size(); i++) {
            h = h * B + s[i] - pw * s[i - L];         // roll: add right, drop left
            int st = i - L + 1;
            auto it = seen.find(h);
            if (it != seen.end())
                for (int j : it->second)              // equal hash: VERIFY the text
                    if (s.compare(j, L, s, st, L) == 0) return st;
            seen[h].push_back(st);
        }
        return -1;
    }
public:
    string longestDupSubstring(string str) {
        s = str;
        int lo = 1, hi = (int)s.size() - 1, bestStart = 0, bestLen = 0;
        while (lo <= hi) {                            // if length L repeats, so does L-1
            int mid = lo + (hi - lo) / 2;
            int st = dupOfLength(mid);
            if (st != -1) { bestStart = st; bestLen = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return s.substr(bestStart, bestLen);
    }
};
//<<<END LC1044
}

// --------------------------------------------------------------------- LC 381
namespace LC381 {
//>>>BEGIN LC381
class RandomizedCollection {
    vector<int> vals;
    unordered_map<int, unordered_set<int>> where;     // value -> every index holding it
public:
    bool insert(int val) {
        bool fresh = !where.count(val);
        where[val].insert(vals.size());
        vals.push_back(val);
        return fresh;
    }
    bool remove(int val) {
        auto it = where.find(val);
        if (it == where.end()) return false;
        int i = *it->second.begin();                  // any copy will do
        it->second.erase(i);
        int lastIdx = vals.size() - 1, last = vals[lastIdx];
        if (i != lastIdx) {                           // move the last element into the hole
            vals[i] = last;
            where[last].erase(lastIdx);
            where[last].insert(i);
        }
        vals.pop_back();
        if (where[val].empty()) where.erase(val);
        return true;
    }
    int getRandom() { return vals[rand() % vals.size()]; }
};
//<<<END LC381
}

// ============================================================================
//  TESTS
// ============================================================================
static vector<vector<string>> canonGroups(vector<vector<string>> g) {
    for (auto& x : g) sort(x.begin(), x.end());
    sort(g.begin(), g.end());
    return g;
}
static vector<vector<char>> board(const vector<string>& rows) {
    vector<vector<char>> b;
    for (auto& r : rows) b.push_back(vector<char>(r.begin(), r.end()));
    return b;
}

int main() {
    banner("Tier 1");
    {   LC1::Solution s;
        vector<int> a{2,7,11,15}; check("LC1 a", s.twoSum(a, 9), vector<int>{0,1});
        vector<int> b{3,2,4};     check("LC1 b", s.twoSum(b, 6), vector<int>{1,2});
        vector<int> c{3,3};       check("LC1 c", s.twoSum(c, 6), vector<int>{0,1});
    }
    {   LC217::Solution s;
        vector<int> a{1,2,3,1}; check("LC217 a", s.containsDuplicate(a), true);
        vector<int> b{1,2,3,4}; check("LC217 b", s.containsDuplicate(b), false);
    }
    {   LC242::Solution s;
        check("LC242 a", s.isAnagram("anagram", "nagaram"), true);
        check("LC242 b", s.isAnagram("rat", "car"), false);
        check("LC242 c", s.isAnagram("a", "ab"), false);
    }
    {   LC383::Solution s;
        check("LC383 a", s.canConstruct("a", "b"), false);
        check("LC383 b", s.canConstruct("aa", "ab"), false);
        check("LC383 c", s.canConstruct("aa", "aab"), true);
    }
    {   LC387::Solution s;
        check("LC387 a", s.firstUniqChar("leetcode"), 0);
        check("LC387 b", s.firstUniqChar("loveleetcode"), 2);
        check("LC387 c", s.firstUniqChar("aabb"), -1);
    }
    {   LC205::Solution s;
        check("LC205 a", s.isIsomorphic("egg", "add"), true);
        check("LC205 b", s.isIsomorphic("foo", "bar"), false);
        check("LC205 c", s.isIsomorphic("paper", "title"), true);
        check("LC205 d", s.isIsomorphic("badc", "baba"), false);   // needs the reverse map
    }
    {   LC290::Solution s;
        check("LC290 a", s.wordPattern("abba", "dog cat cat dog"), true);
        check("LC290 b", s.wordPattern("abba", "dog cat cat fish"), false);
        check("LC290 c", s.wordPattern("aaaa", "dog cat cat dog"), false);
        check("LC290 d", s.wordPattern("abba", "dog dog dog dog"), false);
        check("LC290 e", s.wordPattern("aaa", "aa aa aa aa"), false);
    }
    {   LC349::Solution s;
        vector<int> a{1,2,2,1}, b{2,2};       check("LC349 a", s.intersection(a, b), vector<int>{2});
        vector<int> c{4,9,5}, d{9,4,9,8,4};   check("LC349 b", sorted(s.intersection(c, d)), vector<int>{4,9});
    }
    {   LC350::Solution s;
        vector<int> a{1,2,2,1}, b{2,2};       check("LC350 a", s.intersect(a, b), vector<int>{2,2});
        vector<int> c{4,9,5}, d{9,4,9,8,4};   check("LC350 b", sorted(s.intersect(c, d)), vector<int>{4,9});
    }
    {   LC202::Solution s;
        check("LC202 a", s.isHappy(19), true);
        check("LC202 b", s.isHappy(2), false);
        check("LC202 c", s.isHappy(1), true);
    }
    {   LC219::Solution s;
        vector<int> a{1,2,3,1};     check("LC219 a", s.containsNearbyDuplicate(a, 3), true);
        vector<int> b{1,0,1,1};     check("LC219 b", s.containsNearbyDuplicate(b, 1), true);
        vector<int> c{1,2,3,1,2,3}; check("LC219 c", s.containsNearbyDuplicate(c, 2), false);
    }
    {   LC1512::Solution s;
        vector<int> a{1,2,3,1,1,3}; check("LC1512 a", s.numIdenticalPairs(a), 4);
        vector<int> b{1,1,1,1};     check("LC1512 b", s.numIdenticalPairs(b), 6);
        vector<int> c{1,2,3};       check("LC1512 c", s.numIdenticalPairs(c), 0);
    }
    {   LC706::MyHashMap m;
        m.put(1, 1); m.put(2, 2);
        check("LC706 a", m.get(1), 1);
        check("LC706 b", m.get(3), -1);
        m.put(2, 1);
        check("LC706 c", m.get(2), 1);
        m.remove(2);
        check("LC706 d", m.get(2), -1);
        m.put(0, 5); m.put(10007, 6);                 // same bucket: must chain
        check("LC706 e", m.get(0), 5);
        check("LC706 f", m.get(10007), 6);
        m.remove(0);
        check("LC706 g", m.get(10007), 6);
    }

    banner("Tier 2");
    {   LC49::Solution s;
        vector<string> a{"eat","tea","tan","ate","nat","bat"};
        check("LC49 a", canonGroups(s.groupAnagrams(a)),
              vector<vector<string>>{{"ate","eat","tea"},{"bat"},{"nat","tan"}});
        vector<string> b{""};
        check("LC49 b", s.groupAnagrams(b), vector<vector<string>>{{""}});
    }
    {   LC128::Solution s;
        vector<int> a{100,4,200,1,3,2};       check("LC128 a", s.longestConsecutive(a), 4);
        vector<int> b{0,3,7,2,5,8,4,6,0,1};   check("LC128 b", s.longestConsecutive(b), 9);
        vector<int> c{};                      check("LC128 c", s.longestConsecutive(c), 0);
        vector<int> d{1,2,0,1};               check("LC128 d", s.longestConsecutive(d), 3);
    }
    {   LC560::Solution s;
        vector<int> a{1,1,1};   check("LC560 a", s.subarraySum(a, 2), 2);
        vector<int> b{1,2,3};   check("LC560 b", s.subarraySum(b, 3), 2);
        vector<int> c{1,-1,0};  check("LC560 c", s.subarraySum(c, 0), 3);
    }
    {   LC525::Solution s;
        vector<int> a{0,1};                  check("LC525 a", s.findMaxLength(a), 2);
        vector<int> b{0,1,0};                check("LC525 b", s.findMaxLength(b), 2);
        vector<int> c{0,1,1,1,1,1,0,0,0};    check("LC525 c", s.findMaxLength(c), 6);
    }
    {   LC974::Solution s;
        vector<int> a{4,5,0,-2,-3,1}; check("LC974 a", s.subarraysDivByK(a, 5), 7);
        vector<int> b{5};             check("LC974 b", s.subarraysDivByK(b, 9), 0);
        vector<int> c{-1,2,9};        check("LC974 c", s.subarraysDivByK(c, 2), 2);
    }
    {   LC454::Solution s;
        vector<int> a{1,2}, b{-2,-1}, c{-1,2}, d{0,2};
        check("LC454 a", s.fourSumCount(a, b, c, d), 2);
        vector<int> z{0};
        check("LC454 b", s.fourSumCount(z, z, z, z), 1);
    }
    {   LC36::Solution s;
        vector<string> good{"53..7....","6..195...",".98....6.","8...6...3","4..8.3..1",
                            "7...2...6",".6....28.","...419..5","....8..79"};
        auto b1 = board(good);
        check("LC36 a", s.isValidSudoku(b1), true);
        vector<string> bad = good; bad[0][0] = '8';     // clashes with the 8 in its box
        auto b2 = board(bad);
        check("LC36 b", s.isValidSudoku(b2), false);
    }
    {   LC380::RandomizedSet r;
        check("LC380 a", r.insert(1), true);
        check("LC380 b", r.remove(2), false);
        check("LC380 c", r.insert(2), true);
        int g = r.getRandom();
        check("LC380 d", g == 1 || g == 2, true);
        check("LC380 e", r.remove(1), true);
        check("LC380 f", r.insert(2), false);
        check("LC380 g", r.getRandom(), 2);
        check("LC380 h", r.remove(2), true);       // removing the LAST element itself
        check("LC380 i", r.insert(7), true);
        check("LC380 j", r.getRandom(), 7);
    }
    {   LC146::LRUCache c(2);
        c.put(1, 1); c.put(2, 2);
        check("LC146 a", c.get(1), 1);
        c.put(3, 3);                                // evicts 2
        check("LC146 b", c.get(2), -1);
        c.put(4, 4);                                // evicts 1
        check("LC146 c", c.get(1), -1);
        check("LC146 d", c.get(3), 3);
        check("LC146 e", c.get(4), 4);
        {
            LC146::LRUCache d(2);
            d.put(2, 1); d.put(2, 2);               // update, not a new entry
            check("LC146 f", d.get(2), 2);
            d.put(1, 1); d.put(4, 1);               // evicts 2
            check("LC146 g", d.get(2), -1);
        }
    }
    {   LC438::Solution s;
        check("LC438 a", s.findAnagrams("cbaebabacd", "abc"), vector<int>{0,6});
        check("LC438 b", s.findAnagrams("abab", "ab"), vector<int>{0,1,2});
        check("LC438 c", s.findAnagrams("a", "ab"), vector<int>{});
    }
    {   LC3::Solution s;
        check("LC3 a", s.lengthOfLongestSubstring("abcabcbb"), 3);
        check("LC3 b", s.lengthOfLongestSubstring("bbbbb"), 1);
        check("LC3 c", s.lengthOfLongestSubstring("pwwkew"), 3);
        check("LC3 d", s.lengthOfLongestSubstring(""), 0);
        check("LC3 e", s.lengthOfLongestSubstring("abba"), 2);   // stale index must not jump back
    }
    {   LC523::Solution s;
        vector<int> a{23,2,4,6,7}; check("LC523 a", s.checkSubarraySum(a, 6), true);
        vector<int> b{23,2,6,4,7}; check("LC523 b", s.checkSubarraySum(b, 13), false);
        vector<int> c{23,2,4,6,6}; check("LC523 c", s.checkSubarraySum(c, 7), true);
        vector<int> d{0};          check("LC523 d", s.checkSubarraySum(d, 1), false);
        vector<int> e{5,0,0,0};    check("LC523 e", s.checkSubarraySum(e, 3), true);
    }
    {   LC1010::Solution s;
        vector<int> a{30,20,150,100,40}; check("LC1010 a", s.numPairsDivisibleBy60(a), 3);
        vector<int> b{60,60,60};         check("LC1010 b", s.numPairsDivisibleBy60(b), 3);
    }
    {   LC554::Solution s;
        vector<vector<int>> a{{1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1}};
        check("LC554 a", s.leastBricks(a), 2);
        vector<vector<int>> b{{1},{1},{1}};
        check("LC554 b", s.leastBricks(b), 3);
    }
    {   LC187::Solution s;
        check("LC187 a", sorted(s.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT")),
              vector<string>{"AAAAACCCCC","CCCCCAAAAA"});
        check("LC187 b", s.findRepeatedDnaSequences("AAAAAAAAAAAAA"), vector<string>{"AAAAAAAAAA"});
        check("LC187 c", s.findRepeatedDnaSequences("ACGT"), vector<string>{});
    }

    banner("Tier 3");
    {   LC41::Solution s;
        vector<int> a{1,2,0};          check("LC41 a", s.firstMissingPositive(a), 3);
        vector<int> b{3,4,-1,1};       check("LC41 b", s.firstMissingPositive(b), 2);
        vector<int> c{7,8,9,11,12};    check("LC41 c", s.firstMissingPositive(c), 1);
        vector<int> d{1,1};            check("LC41 d", s.firstMissingPositive(d), 2);
    }
    {   LC76::Solution s;
        check("LC76 a", s.minWindow("ADOBECODEBANC", "ABC"), string("BANC"));
        check("LC76 b", s.minWindow("a", "a"), string("a"));
        check("LC76 c", s.minWindow("a", "aa"), string(""));
    }
    {   LC30::Solution s;
        vector<string> a{"foo","bar"};
        check("LC30 a", sorted(s.findSubstring("barfoothefoobarman", a)), vector<int>{0,9});
        vector<string> b{"word","good","best","word"};
        check("LC30 b", s.findSubstring("wordgoodgoodgoodbestword", b), vector<int>{});
        vector<string> c{"bar","foo","the"};
        check("LC30 c", sorted(s.findSubstring("barfoofoobarthefoobarman", c)), vector<int>{6,9,12});
    }
    {   LC149::Solution s;
        vector<vector<int>> a{{1,1},{2,2},{3,3}};                    check("LC149 a", s.maxPoints(a), 3);
        vector<vector<int>> b{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};  check("LC149 b", s.maxPoints(b), 4);
        vector<vector<int>> c{{0,0}};                                check("LC149 c", s.maxPoints(c), 1);
        vector<vector<int>> d{{0,0},{0,5},{0,-3},{1,1}};             check("LC149 d", s.maxPoints(d), 3);
    }
    {   LC460::LFUCache c(2);
        c.put(1, 1); c.put(2, 2);
        check("LC460 a", c.get(1), 1);
        c.put(3, 3);                                   // evicts 2 (lowest freq)
        check("LC460 b", c.get(2), -1);
        check("LC460 c", c.get(3), 3);
        c.put(4, 4);                                   // 1 and 3 tie on freq: evict LRU = 1
        check("LC460 d", c.get(1), -1);
        check("LC460 e", c.get(3), 3);
        check("LC460 f", c.get(4), 4);
        LC460::LFUCache z(0);
        z.put(0, 0);
        check("LC460 g", z.get(0), -1);
    }
    {   LC1074::Solution s;
        vector<vector<int>> a{{0,1,0},{1,1,1},{0,1,0}}; check("LC1074 a", s.numSubmatrixSumTarget(a, 0), 4);
        vector<vector<int>> b{{1,-1},{-1,1}};           check("LC1074 b", s.numSubmatrixSumTarget(b, 0), 5);
        vector<vector<int>> c{{904}};                   check("LC1074 c", s.numSubmatrixSumTarget(c, 0), 0);
    }
    {   LC992::Solution s;
        vector<int> a{1,2,1,2,3}; check("LC992 a", s.subarraysWithKDistinct(a, 2), 7);
        vector<int> b{1,2,1,3,4}; check("LC992 b", s.subarraysWithKDistinct(b, 3), 3);
    }
    {   LC336::Solution s;
        vector<string> a{"abcd","dcba","lls","s","sssll"};
        check("LC336 a", sorted(s.palindromePairs(a)), vector<vector<int>>{{0,1},{1,0},{2,4},{3,2}});
        vector<string> b{"bat","tab","cat"};
        check("LC336 b", sorted(s.palindromePairs(b)), vector<vector<int>>{{0,1},{1,0}});
        vector<string> c{"a",""};
        check("LC336 c", sorted(s.palindromePairs(c)), vector<vector<int>>{{0,1},{1,0}});
    }
    {   LC1044::Solution s;
        check("LC1044 a", s.longestDupSubstring("banana"), string("ana"));
        check("LC1044 b", s.longestDupSubstring("abcd"), string(""));
        check("LC1044 c", s.longestDupSubstring("aa"), string("a"));
        check("LC1044 d", s.longestDupSubstring("aaaaa"), string("aaaa"));
    }
    {   LC381::RandomizedCollection r;
        check("LC381 a", r.insert(1), true);
        check("LC381 b", r.insert(1), false);
        check("LC381 c", r.insert(2), true);
        int g = r.getRandom();
        check("LC381 d", g == 1 || g == 2, true);
        check("LC381 e", r.remove(1), true);
        check("LC381 f", r.remove(1), true);
        check("LC381 g", r.remove(1), false);
        check("LC381 h", r.getRandom(), 2);
        check("LC381 i", r.insert(1), true);
        check("LC381 j", r.remove(2), true);
        check("LC381 k", r.getRandom(), 1);
    }

    cout << "\n----------------------------------------\n";
    cout << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}
