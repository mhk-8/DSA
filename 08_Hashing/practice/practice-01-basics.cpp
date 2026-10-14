// ============================================================================
//  Hashing — Practice 01: the basics
//
//  Fill in the TODOs. Do NOT look at solutions/reference-basics.cpp until you
//  have made a real attempt at each one. The tests are self-checking:
//
//      g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
//  Every test prints "ok" or "FAIL". Against the empty stubs almost everything
//  fails — that is the point. Work down the list until they all pass.
//
//  Suggested order: 1-3 first, WITHOUT unordered_map / unordered_set — you are
//  building the hash table yourself. Then 4-10 with the STL.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ============================================================================
//  TODO 1 — A hash map from int to int, with SEPARATE CHAINING.
//  Start with 8 buckets. Each bucket is a list of (key, value) pairs.
//    bucket index:  ((key % B) + B) % B      (keeps negative keys valid)
//    put:   overwrite if the key exists in its bucket, else append
//    get:   the value, or -1 if absent
//    erase: true if something was removed
//  REHASH: when size() would exceed the number of buckets (load factor > 1),
//  double the buckets and re-insert every pair — positions change with B.
// ============================================================================
class ChainedHashMap {
    vector<list<pair<int, int>>> buckets = vector<list<pair<int, int>>>(8);
    int count = 0;
public:
    void put(int key, int value) {
        // TODO
    }
    int get(int key) {
        // TODO
        return -1;
    }
    bool erase(int key) {
        // TODO
        return false;
    }
    int size() const { return count; }
    int bucketCount() const { return buckets.size(); }
};

// ============================================================================
//  TODO 2 — A hash SET of ints with OPEN ADDRESSING and LINEAR PROBING.
//  64 slots, never resized (the tests insert only a few keys).
//  Each slot is EMPTY, FULL or DELETED (a "tombstone").
//    home slot:  ((x % 64) + 64) % 64, then try home+1, home+2, ... (wrap)
//    contains: probe until you find x (true) or an EMPTY slot (false).
//              DELETED slots do NOT stop the search.
//    erase:    find x and mark its slot DELETED — never EMPTY. (Why? An EMPTY
//              slot in the middle of a probe chain hides every key after it.)
//    insert:   false if x is present; otherwise store it in the first
//              DELETED-or-EMPTY slot on its probe path.
// ============================================================================
class OpenAddressingSet {
    enum State { EMPTY, FULL, DELETED };
    static const int CAP = 64;
    int keys[CAP];
    State state[CAP];
public:
    OpenAddressingSet() { for (int i = 0; i < CAP; i++) state[i] = EMPTY; }
    bool insert(int x) {
        // TODO
        return false;
    }
    bool contains(int x) {
        // TODO
        return false;
    }
    bool erase(int x) {
        // TODO
        return false;
    }
};

// ============================================================================
//  TODO 3 — Rabin-Karp: every index where `pat` occurs in `text`.
//  ("abracadabra", "abra") -> {0, 7}
//  Polynomial hash with base 31 (or 131) modulo 1e9+7, using long long.
//  Compute the pattern's hash and the first window's hash, then ROLL:
//      h = (h - text[i-m] * B^(m-1)) * B + text[i]      (all mod M, keep >= 0)
//  When the hashes match, compare the actual characters before reporting —
//  different strings can share a hash.
// ============================================================================
vector<int> rabinKarp(const string& text, const string& pat) {
    // TODO
    return {};
}

// ============================================================================
//  From here on, use unordered_map / unordered_set (or plain arrays).
// ============================================================================

// ============================================================================
//  TODO 4 — First non-repeating character in a STREAM (GfG classic).
//  After each character arrives, append the first character so far that has
//  appeared exactly once, or '#' if there is none.
//  "aabc" -> "a#bb"
//  Hint: counts in an array + a queue of candidates; pop while the front's
//  count is above 1.
// ============================================================================
string firstNonRepeatingStream(const string& s) {
    // TODO
    return "";
}

// ============================================================================
//  TODO 5 — Two Sum: indices {i, j}, i < j, with a[i] + a[j] == target,
//  or {} if none. One pass with a value -> index map.
//  Look up the complement BEFORE inserting the current element.
// ============================================================================
vector<int> twoSum(vector<int>& a, int target) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 6 — Number of distinct values in every window of size k.
//  {1,2,1,3,4,2,3}, k=4 -> {3,4,4,3}
//  Keep a value -> count map for the window. When a count drops to 0,
//  ERASE the key — otherwise map.size() over-counts.
// ============================================================================
vector<int> countDistinctInWindows(vector<int>& a, int k) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 7 — Length of the longest subarray with sum 0 (GfG classic).
//  {15,-2,2,-8,1,7,10,23} -> 5   (the subarray -2,2,-8,1,7)
//  Two equal prefix sums enclose a zero-sum subarray. Store the FIRST index
//  of every prefix sum, and remember the empty prefix: sum 0 at index -1.
// ============================================================================
int largestZeroSumSubarray(vector<int>& a) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 8 — How many subarrays sum to exactly k? Values may be negative.
//  {10,2,-2,-20,10}, k=-10 -> 3
//  prefix-sum -> count map, seeded with {0: 1}. At each position add
//  count[prefix - k] to the answer, THEN record the current prefix.
// ============================================================================
int countSubarraysWithSum(vector<int>& a, int k) {
    // TODO
    return -1;
}

// ============================================================================
//  TODO 9 — Group the anagrams together (any order).
//  {"eat","tea","tan","ate","nat","bat"} -> {{eat,tea,ate},{tan,nat},{bat}}
//  The key is a SIGNATURE every anagram shares: the sorted word works.
// ============================================================================
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    // TODO
    return {};
}

// ============================================================================
//  TODO 10 — Length of the longest run of consecutive integers, in O(n).
//  {100,4,200,1,3,2} -> 4   (1,2,3,4)
//  Put everything in a set. Only start counting at x if x-1 is NOT in the
//  set — that is what keeps it O(n) instead of O(n^2).
// ============================================================================
int longestConsecutive(vector<int>& a) {
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
static string show(const vector<vector<string>>& g) {
    string s = "[";
    for (size_t i = 0; i < g.size(); i++) {
        if (i) s += ",";
        s += "[";
        for (size_t j = 0; j < g[i].size(); j++) { if (j) s += ","; s += "\"" + g[i][j] + "\""; }
        s += "]";
    }
    return s + "]";
}
static void ck(const string& label, const string& got, const string& want) {
    if (got == want) { pass_++; cout << "ok   " << label << "\n"; }
    else { fail_++; cout << "FAIL " << label << "\n     got  " << got << "\n     want " << want << "\n"; }
}
static void ck(const string& l, long long g, long long w) { ck(l, to_string(g), to_string(w)); }
static void ck(const string& l, bool g, bool w) { ck(l, string(g ? "true" : "false"), string(w ? "true" : "false")); }
static void ck(const string& l, const vector<int>& g, const vector<int>& w) { ck(l, show(g), show(w)); }
static void ck(const string& l, const vector<vector<string>>& g, const vector<vector<string>>& w) { ck(l, show(g), show(w)); }
static vector<vector<string>> canonGroups(vector<vector<string>> g) {
    for (auto& x : g) sort(x.begin(), x.end());
    sort(g.begin(), g.end());
    return g;
}

int main() {
    cout << "--- TODO 1: ChainedHashMap ---\n";
    { ChainedHashMap m;
      m.put(1, 10); m.put(2, 20); m.put(9, 90);          // 1 and 9 share a bucket at size 8
      ck("chain get 1",  (long long)m.get(1), 10LL);
      ck("chain get 9",  (long long)m.get(9), 90LL);
      ck("chain miss",   (long long)m.get(5), -1LL);
      m.put(1, 11);
      ck("chain overwrite", (long long)m.get(1), 11LL);
      ck("chain size",   (long long)m.size(), 3LL);
      ck("chain erase",  m.erase(9), true);
      ck("chain erase again", m.erase(9), false);
      ck("chain after erase", (long long)m.get(9), -1LL);
      ck("chain still 1", (long long)m.get(1), 11LL);
      for (int k = 100; k < 1100; k++) m.put(k, k * 2);  // forces several rehashes
      bool ok = true;
      for (int k = 100; k < 1100; k++) if (m.get(k) != k * 2) ok = false;
      ck("chain survives rehash", ok, true);
      ck("chain size big", (long long)m.size(), 1002LL);
      ck("chain load factor <= 1", m.bucketCount() >= m.size(), true); }

    cout << "--- TODO 2: OpenAddressingSet ---\n";
    { OpenAddressingSet s;                              // 64 slots, linear probing
      ck("open insert 5",  s.insert(5),  true);
      ck("open insert 69", s.insert(69), true);         // 69 % 64 == 5: collides
      ck("open insert 133",s.insert(133),true);         // collides again
      ck("open dup",       s.insert(69), false);
      ck("open has 133",   s.contains(133), true);
      ck("open erase 69",  s.erase(69), true);          // leaves a tombstone
      ck("open has 133 after erase", s.contains(133), true);   // must probe PAST it
      ck("open no 69",     s.contains(69), false);
      ck("open erase missing", s.erase(7), false);
      ck("open reinsert 69", s.insert(69), true);
      ck("open has 69",    s.contains(69), true);
      ck("open neg key",   s.insert(-3), true);
      ck("open has neg",   s.contains(-3), true); }

    cout << "--- TODO 3: rabinKarp ---\n";
    ck("rk a", rabinKarp("abracadabra", "abra"), vector<int>{0,7});
    ck("rk b", rabinKarp("aaaaa", "aa"),         vector<int>{0,1,2,3});
    ck("rk c", rabinKarp("hello", "xyz"),        vector<int>{});
    ck("rk d", rabinKarp("ab", "abc"),           vector<int>{});

    cout << "--- TODO 4: firstNonRepeatingStream ---\n";
    ck("stream a", firstNonRepeatingStream("aabc"), string("a#bb"));
    ck("stream b", firstNonRepeatingStream("zz"),   string("z#"));
    ck("stream c", firstNonRepeatingStream("abcabc"), string("aaabc#"));

    cout << "--- TODO 5: twoSum ---\n";
    { vector<int> a{2,7,11,15}; ck("twoSum a", twoSum(a, 9), vector<int>{0,1}); }
    { vector<int> a{3,3};       ck("twoSum b", twoSum(a, 6), vector<int>{0,1}); }
    { vector<int> a{1,2};       ck("twoSum none", twoSum(a, 7), vector<int>{}); }

    cout << "--- TODO 6: countDistinctInWindows ---\n";
    { vector<int> a{1,2,1,3,4,2,3}; ck("distinct a", countDistinctInWindows(a, 4), vector<int>{3,4,4,3}); }
    { vector<int> a{4,1,1};         ck("distinct b", countDistinctInWindows(a, 2), vector<int>{2,1}); }
    { vector<int> a{5,5,5};         ck("distinct c", countDistinctInWindows(a, 1), vector<int>{1,1,1}); }

    cout << "--- TODO 7: largestZeroSumSubarray ---\n";
    { vector<int> a{15,-2,2,-8,1,7,10,23}; ck("zero a", (long long)largestZeroSumSubarray(a), 5LL); }
    { vector<int> a{1,2,3};                ck("zero b", (long long)largestZeroSumSubarray(a), 0LL); }
    { vector<int> a{1,-1,3,-3};            ck("zero c", (long long)largestZeroSumSubarray(a), 4LL); }

    cout << "--- TODO 8: countSubarraysWithSum ---\n";
    { vector<int> a{10,2,-2,-20,10}; ck("sumk a", (long long)countSubarraysWithSum(a, -10), 3LL); }
    { vector<int> a{1,1,1};          ck("sumk b", (long long)countSubarraysWithSum(a, 2), 2LL); }
    { vector<int> a{0,0,0};          ck("sumk c", (long long)countSubarraysWithSum(a, 0), 6LL); }

    cout << "--- TODO 9: groupAnagrams ---\n";
    { vector<string> a{"eat","tea","tan","ate","nat","bat"};
      ck("groups a", canonGroups(groupAnagrams(a)),
         vector<vector<string>>{{"ate","eat","tea"},{"bat"},{"nat","tan"}}); }
    { vector<string> a{"a"}; ck("groups b", groupAnagrams(a), vector<vector<string>>{{"a"}}); }

    cout << "--- TODO 10: longestConsecutive ---\n";
    { vector<int> a{100,4,200,1,3,2};     ck("consec a", (long long)longestConsecutive(a), 4LL); }
    { vector<int> a{0,3,7,2,5,8,4,6,0,1}; ck("consec b", (long long)longestConsecutive(a), 9LL); }
    { vector<int> a{};                    ck("consec c", (long long)longestConsecutive(a), 0LL); }

    cout << "\n----------------------------------------\n";
    cout << pass_ << " passed, " << fail_ << " failed\n";
    if (fail_ == 0) cout << "All tests pass. Move on to the problem list in Part 16.\n";
    return fail_ == 0 ? 0 : 1;
}
