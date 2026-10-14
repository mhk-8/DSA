// ============================================================================
//  Hashing — reference answers to practice/practice-01-basics.cpp
//
//      g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
//  Same tests as the practice file, all passing. Read this AFTER you have made
//  a real attempt at the practice file yourself.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------- 1
class ChainedHashMap {
    vector<list<pair<int, int>>> buckets = vector<list<pair<int, int>>>(8);
    int count = 0;
    int idx(int key) const { int B = buckets.size(); return ((key % B) + B) % B; }
    void rehash() {
        vector<list<pair<int, int>>> old(buckets.size() * 2);
        swap(old, buckets);                          // buckets is now the bigger table
        for (auto& chain : old)
            for (auto& kv : chain) buckets[idx(kv.first)].push_back(kv);
    }
public:
    void put(int key, int value) {
        for (auto& kv : buckets[idx(key)])
            if (kv.first == key) { kv.second = value; return; }   // overwrite
        if (count + 1 > (int)buckets.size()) rehash();           // keep load factor <= 1
        buckets[idx(key)].push_back({key, value});
        count++;
    }
    int get(int key) {
        for (auto& kv : buckets[idx(key)]) if (kv.first == key) return kv.second;
        return -1;
    }
    bool erase(int key) {
        auto& chain = buckets[idx(key)];
        for (auto it = chain.begin(); it != chain.end(); ++it)
            if (it->first == key) { chain.erase(it); count--; return true; }
        return false;
    }
    int size() const { return count; }
    int bucketCount() const { return buckets.size(); }
};

// ---------------------------------------------------------------------- 2
class OpenAddressingSet {
    enum State { EMPTY, FULL, DELETED };
    static const int CAP = 64;
    int keys[CAP];
    State state[CAP];
    int home(int x) const { return ((x % CAP) + CAP) % CAP; }
public:
    OpenAddressingSet() { for (int i = 0; i < CAP; i++) state[i] = EMPTY; }
    bool contains(int x) {
        for (int i = home(x), steps = 0; steps < CAP; i = (i + 1) % CAP, steps++) {
            if (state[i] == EMPTY) return false;              // end of the chain
            if (state[i] == FULL && keys[i] == x) return true;
        }                                                     // DELETED: keep going
        return false;
    }
    bool insert(int x) {
        if (contains(x)) return false;
        for (int i = home(x), steps = 0; steps < CAP; i = (i + 1) % CAP, steps++)
            if (state[i] != FULL) { keys[i] = x; state[i] = FULL; return true; }   // reuse tombstones
        return false;                                         // table full
    }
    bool erase(int x) {
        for (int i = home(x), steps = 0; steps < CAP; i = (i + 1) % CAP, steps++) {
            if (state[i] == EMPTY) return false;
            if (state[i] == FULL && keys[i] == x) { state[i] = DELETED; return true; }
        }
        return false;
    }
};

// ---------------------------------------------------------------------- 3
vector<int> rabinKarp(const string& text, const string& pat) {
    const long long B = 131, M = 1000000007;
    int n = text.size(), m = pat.size();
    vector<int> res;
    if (m == 0 || m > n) return res;
    long long hp = 0, ht = 0, pw = 1;                 // pw = B^(m-1)
    for (int i = 0; i < m; i++) {
        hp = (hp * B + pat[i]) % M;
        ht = (ht * B + text[i]) % M;
        if (i) pw = pw * B % M;
    }
    for (int i = 0; ; i++) {                          // window text[i .. i+m-1]
        if (ht == hp && text.compare(i, m, pat) == 0) res.push_back(i);   // verify
        if (i + m == n) break;
        ht = (ht - text[i] * pw % M + M) % M;         // drop the left character
        ht = (ht * B + text[i + m]) % M;              // add the right character
    }
    return res;
}

// ---------------------------------------------------------------------- 4
string firstNonRepeatingStream(const string& s) {
    int cnt[256] = {0};
    queue<char> q;                                    // candidates, in arrival order
    string out;
    for (char c : s) {
        cnt[(unsigned char)c]++;
        q.push(c);
        while (!q.empty() && cnt[(unsigned char)q.front()] > 1) q.pop();
        out += q.empty() ? '#' : q.front();
    }
    return out;
}

// ---------------------------------------------------------------------- 5
vector<int> twoSum(vector<int>& a, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < (int)a.size(); i++) {
        auto it = seen.find(target - a[i]);
        if (it != seen.end()) return {it->second, i};
        seen[a[i]] = i;
    }
    return {};
}

// ---------------------------------------------------------------------- 6
vector<int> countDistinctInWindows(vector<int>& a, int k) {
    unordered_map<int, int> cnt;
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        cnt[a[i]]++;
        if (i >= k && --cnt[a[i - k]] == 0) cnt.erase(a[i - k]);   // ERASE at zero
        if (i >= k - 1) res.push_back(cnt.size());
    }
    return res;
}

// ---------------------------------------------------------------------- 7
int largestZeroSumSubarray(vector<int>& a) {
    unordered_map<long long, int> first{{0, -1}};
    long long prefix = 0;
    int best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        prefix += a[i];
        auto it = first.find(prefix);
        if (it != first.end()) best = max(best, i - it->second);
        else first[prefix] = i;                      // keep the EARLIEST index
    }
    return best;
}

// ---------------------------------------------------------------------- 8
int countSubarraysWithSum(vector<int>& a, int k) {
    unordered_map<long long, int> seen{{0, 1}};
    long long prefix = 0;
    int count = 0;
    for (int x : a) {
        prefix += x;
        auto it = seen.find(prefix - k);
        if (it != seen.end()) count += it->second;
        seen[prefix]++;
    }
    return count;
}

// ---------------------------------------------------------------------- 9
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (const string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& [k, g] : groups) res.push_back(g);
    return res;
}

// ---------------------------------------------------------------------- 10
int longestConsecutive(vector<int>& a) {
    unordered_set<int> s(a.begin(), a.end());
    int best = 0;
    for (int x : s) {
        if (s.count(x - 1)) continue;                // only start at the start of a run
        int len = 1;
        while (s.count(x + len)) len++;
        best = max(best, len);
    }
    return best;
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
