// reference-basics.cpp  —  Strings, Module 1 reference answers
// -----------------------------------------------------------------------------
// Worked answers to every TODO in practice/practice-01-basics.cpp, with the
// same test harness. All tests pass.
//
//   g++ -std=c++17 -O2 -Wall -o ref reference-basics.cpp && ./ref
//
// Read these only AFTER you have attempted the practice file yourself.
//
// The tests are self-checking: each prints ok or FAIL and the summary at the
// end tells you how many are still outstanding. With the empty stubs below,
// almost everything fails — that is expected. Work down the list in order.
//
// Suggested order (matches the 3-week plan in the guide):
//   Week 1 day 1  -> TODO 1, 2, 3
//   Week 1 day 5  -> TODO 4, 5
//   Week 2 day 8  -> TODO 6
//   Week 2 day 12 -> TODO 7, 8
//   Week 3 day 15 -> TODO 9
//   Week 3 day 18 -> TODO 10
// -----------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// TODO 1 — reverseString
// Reverse the characters of s IN PLACE. O(n) time, O(1) extra space.
// Pattern: two pointers converging from both ends.
// Hint: while (l < r) { swap; l++; r--; }   — why `<` and not `<=`?
// =============================================================================
void reverseString(string& s) {
    int l = 0, r = (int)s.size() - 1;
    // `<` not `<=`: at l == r there is one character, equal to itself
    while (l < r) {
        swap(s[l], s[r]);
        l++;
        r--;
    }
}

// =============================================================================
// TODO 2 — isPalindromeFiltered
// True if s reads the same both ways, considering only alphanumeric characters
// and ignoring case.  "A man, a plan, a canal: Panama" -> true
// Pattern: two pointers with filtering.
// Hint: the inner skip loops each need `l < r` in their condition too, or a
//       string of pure punctuation walks off the end.
// =============================================================================
bool isPalindromeFiltered(const string& s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        // both skip loops repeat `l < r`, or ",,,," walks off the end
        while (l < r && !isalnum((unsigned char)s[l])) l++;
        while (l < r && !isalnum((unsigned char)s[r])) r--;
        if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r]))
            return false;
        l++;
        r--;
    }
    return true;
}

// =============================================================================
// TODO 3 — isAnagram
// True if t is a rearrangement of s. Lowercase letters only.
// Pattern: frequency counting. O(n) time, O(26) space.
// Hint: count up from s, count down from t, and bail out the moment a count
//       goes negative. Guard the sizes first. REMEMBER TO INITIALISE THE ARRAY.
// =============================================================================
bool isAnagram(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    int cnt[26] = {0};                        // {0} zeroes all 26
    for (char c : s) cnt[c - 'a']++;
    for (char c : t)
        if (--cnt[c - 'a'] < 0) return false; // t has more of c than s did
    return true;                              // equal sizes => none left over
}

// =============================================================================
// TODO 4 — compress
// Run-length compress the vector IN PLACE. Each run becomes its character
// followed by the run length, with the length omitted when it is 1.
// Return the new length; characters past it are ignored.
//   {'a','a','b','b','c','c','c'} -> {'a','2','b','2','c','3'}, return 6
//   twelve 'a's                   -> {'a','1','2'},             return 3
// Pattern: read/write pointers. O(n) time, O(1) extra space.
// Hint: the run length can have MORE THAN ONE DIGIT.
// =============================================================================
int compress(vector<char>& chars) {
    int n = chars.size(), read = 0, write = 0;
    while (read < n) {
        char c = chars[read];
        int run = 0;
        while (read < n && chars[read] == c) { read++; run++; }
        chars[write++] = c;
        if (run > 1)
            for (char d : to_string(run))     // a run of 12 writes '1','2'
                chars[write++] = d;
    }
    return write;                             // write never overtakes read
}

// =============================================================================
// TODO 5 — addStrings
// Add two non-negative integers given as strings, without converting them to
// a numeric type.  "99" + "1" -> "100"
// Pattern: one pointer per string, walking from the END.
// Hint: the loop condition needs `|| carry`, or you lose the final digit.
//       Build the answer forwards and reverse once at the end.
// =============================================================================
string addStrings(const string& a, const string& b) {
    int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
    string res;
    while (i >= 0 || j >= 0 || carry) {       // `|| carry` gives "99"+"1"="100"
        int x = i >= 0 ? a[i--] - '0' : 0;
        int y = j >= 0 ? b[j--] - '0' : 0;
        int s = x + y + carry;
        res += char('0' + s % 10);
        carry = s / 10;
    }
    reverse(res.begin(), res.end());          // build forwards, reverse once
    return res;
}

// =============================================================================
// TODO 6 — lengthOfLongestSubstring
// Length of the longest substring of s with no repeated character.
//   "abcabcbb" -> 3 ("abc")      "bbbbb" -> 1      "pwwkew" -> 3 ("wke")
// Pattern: variable-size sliding window, longest.
// Hint: the four questions. What does a character entering do? What makes the
//       window illegal? What does a character leaving undo? Where do I record?
//       (For "longest", you record AFTER the shrink loop.)
// =============================================================================
int lengthOfLongestSubstring(const string& s) {
    int cnt[128] = {0}, l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        cnt[(unsigned char)s[r]]++;                 // 1. character enters
        while (cnt[(unsigned char)s[r]] > 1) {      // 2. invalid: it repeats
            cnt[(unsigned char)s[l]]--;             // 3. character leaves
            l++;
        }
        best = max(best, r - l + 1);                // 4. longest -> record after
    }
    return best;
}

// =============================================================================
// TODO 7 — longestPalindrome
// Return the longest palindromic SUBSTRING of s (any one, if tied).
// Pattern: expand around centre. O(n^2) time, O(1) space.
// Hint: there are 2n-1 centres — n on a character, n-1 between two.
//       When the expand loop exits, l and r have each overshot by one, so the
//       length is r - l - 1 and the start is l + 1.
// =============================================================================
string longestPalindrome(const string& s) {
    int n = s.size();
    if (n == 0) return "";
    int bestL = 0, bestLen = 1;
    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
        int len = r - l - 1;                  // both overshot by one on exit
        if (len > bestLen) { bestLen = len; bestL = l + 1; }
    };
    for (int c = 0; c < n; c++) {             // 2n - 1 centres
        expand(c, c);                         // odd
        expand(c, c + 1);                     // even
    }
    return s.substr(bestL, bestLen);
}

// =============================================================================
// TODO 8 — countPalindromicSubstrings
// Count every palindromic substring of s, counting different positions of the
// same text separately.  "aaa" -> 6   ("a","a","a","aa","aa","aaa")
// Pattern: expand around centre — the same loop as TODO 7, counting instead.
// =============================================================================
int countPalindromicSubstrings(const string& s) {
    int n = s.size(), total = 0;
    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { total++; l--; r++; }
    };
    for (int c = 0; c < n; c++) {
        expand(c, c);
        expand(c, c + 1);
    }
    return total;
}

// =============================================================================
// TODO 9 — prefixFunction and strStrKMP
// (a) prefixFunction(p)[i] = the length of the longest PROPER prefix of
//     p[0..i] that is also a suffix of p[0..i].
//       "ababaca" -> {0,0,1,2,3,0,1}
// (b) strStrKMP(txt, pat) = the index of the first occurrence of pat in txt,
//     or -1. Return 0 for an empty pattern. Use the prefix function; O(n+m).
// Hint: the fallback is `j = pi[j-1]`, NOT `j--`. The search loop has the same
//       shape as the build loop.
// =============================================================================
vector<int> prefixFunction(const string& p) {
    int m = p.size();
    vector<int> pi(m, 0);                     // pi[0] is always 0
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && p[i] != p[j]) j = pi[j - 1];   // next-longest border,
        if (p[i] == p[j]) j++;                         // NOT j--
        pi[i] = j;
    }
    return pi;
}

int strStrKMP(const string& txt, const string& pat) {
    if (pat.empty()) return 0;
    vector<int> pi = prefixFunction(pat);
    int j = 0, m = pat.size();
    for (int i = 0; i < (int)txt.size(); i++) {        // same shape as the build
        while (j > 0 && txt[i] != pat[j]) j = pi[j - 1];
        if (txt[i] == pat[j]) j++;
        if (j == m) return i - j + 1;
    }
    return -1;
}

// =============================================================================
// TODO 10 — editDistance
// Minimum number of single-character insertions, deletions or replacements to
// turn a into b.  "horse" -> "ros" is 3.
// Pattern: two-string DP grid, (n+1) x (m+1).
// Hint: dp[i][j] covers the FIRST i characters of a and first j of b, so the
//       characters you compare are a[i-1] and b[j-1]. Do not forget the base
//       cases dp[i][0] = i and dp[0][j] = j.
// =============================================================================
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;         // delete everything
    for (int j = 0; j <= m; j++) dp[0][j] = j;         // insert everything
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            // i and j are COUNTS, so compare a[i-1] and b[j-1]
            dp[i][j] = (a[i - 1] == b[j - 1])
                     ? dp[i - 1][j - 1]
                     : 1 + min({dp[i - 1][j - 1],      // replace
                                dp[i - 1][j],          // delete from a
                                dp[i][j - 1]});        // insert into a
    return dp[n][m];
}

// =============================================================================
// ============================ TESTS — do not edit ============================
// =============================================================================
static int g_pass = 0, g_fail = 0;
static set<int> g_failedTodos;

static void T(int todo, bool ok, const string& what) {
    if (ok) { g_pass++; cout << "  ok    "; }
    else    { g_fail++; g_failedTodos.insert(todo); cout << "  FAIL  "; }
    cout << "[" << todo << "] " << what << "\n";
}

int main() {
    cout << "Strings — reference answers — basics\n";
    cout << "======================================\n";

    // --- TODO 1 ---
    { string s = "hello";  reverseString(s);  T(1, s == "olleh", "reverse \"hello\""); }
    { string s = "ab";     reverseString(s);  T(1, s == "ba",    "reverse \"ab\""); }
    { string s = "x";      reverseString(s);  T(1, s == "x",     "reverse single char"); }
    { string s = "";       reverseString(s);  T(1, s == "",      "reverse empty"); }

    // --- TODO 2 ---
    T(2, isPalindromeFiltered("A man, a plan, a canal: Panama"), "\"A man, a plan...\"");
    T(2, !isPalindromeFiltered("race a car"),                    "\"race a car\"");
    T(2, isPalindromeFiltered(" "),                              "single space");
    T(2, isPalindromeFiltered(",,,,"),                           "punctuation only");
    T(2, isPalindromeFiltered(""),                               "empty");
    T(2, !isPalindromeFiltered("0P"),                            "\"0P\" (digit vs letter)");

    // --- TODO 3 ---
    T(3, isAnagram("anagram", "nagaram"), "anagram / nagaram");
    T(3, !isAnagram("rat", "car"),        "rat / car");
    T(3, !isAnagram("a", "ab"),           "different lengths");
    T(3, isAnagram("", ""),               "both empty");
    T(3, !isAnagram("aacc", "ccac"),      "aacc / ccac");

    // --- TODO 4 ---
    { vector<char> v{'a','a','b','b','c','c','c'};
      int n = compress(v);
      T(4, n == 6 && string(v.begin(), v.begin()+max(0,min(n,(int)v.size()))) == "a2b2c3", "a2b2c3"); }
    { vector<char> v{'a'};
      int n = compress(v);
      T(4, n == 1 && v[0] == 'a', "single char"); }
    { vector<char> v(12, 'a');
      int n = compress(v);
      T(4, n == 3 && string(v.begin(), v.begin()+max(0,min(n,(int)v.size()))) == "a12", "multi-digit run"); }
    { vector<char> v{'a','b','c'};
      int n = compress(v);
      T(4, n == 3 && string(v.begin(), v.begin()+max(0,min(n,(int)v.size()))) == "abc", "no runs"); }

    // --- TODO 5 ---
    T(5, addStrings("11", "123") == "134",   "11 + 123");
    T(5, addStrings("456", "77") == "533",   "456 + 77");
    T(5, addStrings("0", "0") == "0",        "0 + 0");
    T(5, addStrings("99", "1") == "100",     "99 + 1  (carry out)");
    T(5, addStrings("999999999999999999", "1") == "1000000000000000000", "18 digits + 1");

    // --- TODO 6 ---
    T(6, lengthOfLongestSubstring("abcabcbb") == 3, "abcabcbb -> 3");
    T(6, lengthOfLongestSubstring("bbbbb") == 1,    "bbbbb -> 1");
    T(6, lengthOfLongestSubstring("pwwkew") == 3,   "pwwkew -> 3");
    T(6, lengthOfLongestSubstring("") == 0,         "empty -> 0");
    T(6, lengthOfLongestSubstring("dvdf") == 3,     "dvdf -> 3  (the jump case)");
    T(6, lengthOfLongestSubstring("abcdef") == 6,   "all distinct");

    // --- TODO 7 ---
    { string r = longestPalindrome("babad"); T(7, r == "bab" || r == "aba", "babad"); }
    T(7, longestPalindrome("cbbd") == "bb",   "cbbd (even length)");
    T(7, longestPalindrome("a") == "a",       "single char");
    T(7, longestPalindrome("aaaa") == "aaaa", "all same");
    T(7, longestPalindrome("forgeeksskeegfor") == "geeksskeeg", "geeksskeeg");
    { string r = longestPalindrome("ac"); T(7, r.size() == 1, "no palindrome longer than 1"); }

    // --- TODO 8 ---
    T(8, countPalindromicSubstrings("abc") == 3,  "abc -> 3");
    T(8, countPalindromicSubstrings("aaa") == 6,  "aaa -> 6");
    T(8, countPalindromicSubstrings("a") == 1,    "single -> 1");
    T(8, countPalindromicSubstrings("abba") == 6, "abba -> 6");

    // --- TODO 9 ---
    T(9, (prefixFunction("ababaca") == vector<int>{0,0,1,2,3,0,1}), "pi(\"ababaca\")");
    T(9, (prefixFunction("aaaa") == vector<int>{0,1,2,3}),          "pi(\"aaaa\")");
    T(9, (prefixFunction("abcd") == vector<int>{0,0,0,0}),          "pi(\"abcd\")");
    T(9, strStrKMP("sadbutsad", "sad") == 0,        "first occurrence at 0");
    T(9, strStrKMP("leetcode", "leeto") == -1,      "absent");
    T(9, strStrKMP("mississippi", "issip") == 4,    "issip at 4");
    T(9, strStrKMP("hello", "") == 0,               "empty pattern");
    T(9, strStrKMP("aaaaab", "aaab") == 2,          "aaab at 2");

    // --- TODO 10 ---
    T(10, editDistance("horse", "ros") == 3,            "horse -> ros");
    T(10, editDistance("intention", "execution") == 5,  "intention -> execution");
    T(10, editDistance("", "abc") == 3,                 "empty source");
    T(10, editDistance("abc", "") == 3,                 "empty target");
    T(10, editDistance("abc", "abc") == 0,              "identical");
    T(10, editDistance("a", "ab") == 1,                 "prefix");

    cout << "======================================\n";
    cout << "passed: " << g_pass << "   failed: " << g_fail << "\n";
    if (g_fail == 0) {
        cout << "ALL TESTS PASSED — every TODO is done.\n";
    } else {
        cout << "BROKEN — reference answers should never fail: ";
        for (int t : g_failedTodos) cout << t << " ";
        cout << "\n";
    }
    return g_fail != 0;
}
