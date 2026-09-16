// practice-01-basics.cpp  —  Strings, Module 1
// -----------------------------------------------------------------------------
// Fill in the ten TODOs. Do NOT look at solutions/reference-basics.cpp until
// you have tried each one for at least fifteen minutes.
//
//   g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
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
    // TODO
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
    // TODO
    return false;
}

// =============================================================================
// TODO 3 — isAnagram
// True if t is a rearrangement of s. Lowercase letters only.
// Pattern: frequency counting. O(n) time, O(26) space.
// Hint: count up from s, count down from t, and bail out the moment a count
//       goes negative. Guard the sizes first. REMEMBER TO INITIALISE THE ARRAY.
// =============================================================================
bool isAnagram(const string& s, const string& t) {
    // TODO
    return false;
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
    // TODO
    return 0;
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
    // TODO
    return "";
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
    // TODO
    return 0;
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
    // TODO
    return "";
}

// =============================================================================
// TODO 8 — countPalindromicSubstrings
// Count every palindromic substring of s, counting different positions of the
// same text separately.  "aaa" -> 6   ("a","a","a","aa","aa","aaa")
// Pattern: expand around centre — the same loop as TODO 7, counting instead.
// =============================================================================
int countPalindromicSubstrings(const string& s) {
    // TODO
    return 0;
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
    // TODO
    return vector<int>(p.size(), 0);
}

int strStrKMP(const string& txt, const string& pat) {
    // TODO
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
    // TODO
    return 0;
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
    cout << "Strings — practice 01 — basics\n";
    cout << "==============================\n";

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

    cout << "==============================\n";
    cout << "passed: " << g_pass << "   failed: " << g_fail << "\n";
    if (g_fail == 0) {
        cout << "ALL TESTS PASSED — every TODO is done.\n";
    } else {
        cout << "still to do: ";
        for (int t : g_failedTodos) cout << t << " ";
        cout << "\n";
    }
    return g_fail != 0;
}
