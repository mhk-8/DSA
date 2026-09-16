// reference-part14-solutions.cpp
// -----------------------------------------------------------------------------
// All 38 problems from Part 14 of Strings-Guide.pdf, each in its own namespace
// so every class can be named `Solution` exactly as LeetCode expects.
//
// This file is the SINGLE SOURCE OF TRUTH for Strings-Solved-Questions.pdf:
// the code printed in the book is extracted verbatim from the marked blocks
// below, so the book can never drift from code that was actually tested.
//
//   g++ -std=c++17 -O2 -Wall -o ref reference-part14-solutions.cpp && ./ref
// -----------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

// ------------------------------- test harness --------------------------------
static int g_pass = 0, g_fail = 0;

static void check(bool ok, const string& what) {
    if (ok) { g_pass++; }
    else    { g_fail++; cout << "  FAIL  " << what << "\n"; }
}

template <class T>
static void eq(const T& got, const T& want, const string& what) {
    bool ok = (got == want);
    if (!ok) {
        cout << "  FAIL  " << what << "\n";
        g_fail++;
    } else g_pass++;
}

static void eqs(const string& got, const string& want, const string& what) {
    if (got == want) g_pass++;
    else { g_fail++; cout << "  FAIL  " << what
                          << "  got=\"" << got << "\" want=\"" << want << "\"\n"; }
}

static void eqi(long long got, long long want, const string& what) {
    if (got == want) g_pass++;
    else { g_fail++; cout << "  FAIL  " << what
                          << "  got=" << got << " want=" << want << "\n"; }
}

static void eqv(vector<int> got, vector<int> want, const string& what) {
    if (got == want) g_pass++;
    else { g_fail++; cout << "  FAIL  " << what << "\n"; }
}

// =============================================================================
// TIER 1 - FUNDAMENTALS
// =============================================================================

namespace LC344 {
//>>>BEGIN LC344
class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            swap(s[l], s[r]);
            l++;
            r--;
        }
    }
};
//<<<END LC344
}

namespace LC125 {
//>>>BEGIN LC125
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            // both guards repeat `l < r`, or a pure-punctuation string walks off
            while (l < r && !isalnum((unsigned char)s[l])) l++;
            while (l < r && !isalnum((unsigned char)s[r])) r--;
            if (tolower((unsigned char)s[l]) != tolower((unsigned char)s[r]))
                return false;
            l++;
            r--;
        }
        return true;
    }
};
//<<<END LC125
}

namespace LC242 {
//>>>BEGIN LC242
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int cnt[26] = {0};                       // {0} zeroes all 26 slots
        for (char c : s) cnt[c - 'a']++;
        for (char c : t)
            if (--cnt[c - 'a'] < 0) return false; // t has more of c than s did
        return true;                              // equal sizes => nothing left over
    }
};
//<<<END LC242
}

namespace LC387 {
//>>>BEGIN LC387
class Solution {
public:
    int firstUniqChar(string s) {
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;
        for (int i = 0; i < (int)s.size(); i++)
            if (cnt[s[i] - 'a'] == 1) return i;
        return -1;
    }
};
//<<<END LC387
}

namespace LC383 {
//>>>BEGIN LC383
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int cnt[26] = {0};
        for (char c : magazine) cnt[c - 'a']++;
        for (char c : ransomNote)
            if (--cnt[c - 'a'] < 0) return false;
        return true;
    }
};
//<<<END LC383
}

namespace LC14 {
//>>>BEGIN LC14
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        // vertical scan: column by column across every word
        for (int i = 0; i < (int)strs[0].size(); i++) {
            char c = strs[0][i];
            for (int j = 1; j < (int)strs.size(); j++)
                if (i >= (int)strs[j].size() || strs[j][i] != c)
                    return strs[0].substr(0, i);
        }
        return strs[0];
    }
};
//<<<END LC14
}

namespace LC58 {
//>>>BEGIN LC58
class Solution {
public:
    int lengthOfLastWord(string s) {
        int i = (int)s.size() - 1;
        while (i >= 0 && s[i] == ' ') i--;     // skip trailing spaces first
        int len = 0;
        while (i >= 0 && s[i] != ' ') { len++; i--; }
        return len;
    }
};
//<<<END LC58
}

namespace LC28 {
//>>>BEGIN LC28
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size(), m = needle.size();
        if (m == 0) return 0;
        for (int i = 0; i + m <= n; i++) {       // stop before running off the end
            int j = 0;
            while (j < m && haystack[i + j] == needle[j]) j++;
            if (j == m) return i;
        }
        return -1;
    }
};
//<<<END LC28
}

namespace LC205 {
//>>>BEGIN LC205
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) return false;
        int mapST[128], mapTS[128];
        memset(mapST, -1, sizeof(mapST));
        memset(mapTS, -1, sizeof(mapTS));
        for (int i = 0; i < (int)s.size(); i++) {
            unsigned char a = s[i], b = t[i];
            // one map is not enough: "ab" -> "aa" passes s->t but fails t->s
            if (mapST[a] == -1 && mapTS[b] == -1) {
                mapST[a] = b;
                mapTS[b] = a;
            } else if (mapST[a] != (int)b || mapTS[b] != (int)a) {
                return false;
            }
        }
        return true;
    }
};
//<<<END LC205
}

namespace LC392 {
//>>>BEGIN LC392
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, n = s.size();
        for (char c : t)
            if (i < n && s[i] == c) i++;   // greedy: match the earliest position
        return i == n;
    }
};
//<<<END LC392
}

namespace LC13 {
//>>>BEGIN LC13
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char,int> v{{'I',1},{'V',5},{'X',10},{'L',50},
                                  {'C',100},{'D',500},{'M',1000}};
        int n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            // a smaller value immediately before a larger one is subtracted
            if (i + 1 < n && v[s[i]] < v[s[i + 1]]) res -= v[s[i]];
            else                                    res += v[s[i]];
        }
        return res;
    }
};
//<<<END LC13
}

namespace LC12 {
//>>>BEGIN LC12
class Solution {
public:
    string intToRoman(int num) {
        // the six subtractive forms live in the table, so there are no special cases
        const int    val[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        const string sym[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        string res;
        for (int i = 0; i < 13; i++)
            while (num >= val[i]) { num -= val[i]; res += sym[i]; }
        return res;
    }
};
//<<<END LC12
}

namespace LC415 {
//>>>BEGIN LC415
class Solution {
public:
    string addStrings(string num1, string num2) {
        int i = (int)num1.size() - 1, j = (int)num2.size() - 1, carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry) {      // `|| carry` handles "99" + "1"
            int a = i >= 0 ? num1[i--] - '0' : 0;
            int b = j >= 0 ? num2[j--] - '0' : 0;
            int s = a + b + carry;
            res += char('0' + s % 10);
            carry = s / 10;
        }
        reverse(res.begin(), res.end());         // build forwards, reverse once
        return res;
    }
};
//<<<END LC415
}

// =============================================================================
// TIER 2 - THE CORE PATTERNS
// =============================================================================

namespace LC3 {
//>>>BEGIN LC3
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int cnt[128] = {0}, l = 0, best = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            cnt[(unsigned char)s[r]]++;
            // the arriving character is the only possible offender
            while (cnt[(unsigned char)s[r]] > 1) {
                cnt[(unsigned char)s[l]]--;
                l++;
            }
            best = max(best, r - l + 1);       // record AFTER shrinking: longest
        }
        return best;
    }
};
//<<<END LC3
}

namespace LC438 {
//>>>BEGIN LC438
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size(), k = p.size();
        vector<int> res;
        if (n < k) return res;
        int need[26] = {0}, win[26] = {0};
        for (char c : p) need[c - 'a']++;
        for (int r = 0; r < n; r++) {
            win[s[r] - 'a']++;
            if (r >= k) win[s[r - k] - 'a']--;             // the character leaving
            if (r >= k - 1 && memcmp(need, win, sizeof(need)) == 0)
                res.push_back(r - k + 1);                  // window's left end
        }
        return res;
    }
};
//<<<END LC438
}

namespace LC567 {
//>>>BEGIN LC567
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s2.size(), k = s1.size();
        if (n < k) return false;
        int need[26] = {0}, win[26] = {0};
        for (char c : s1) need[c - 'a']++;
        for (int r = 0; r < n; r++) {
            win[s2[r] - 'a']++;
            if (r >= k) win[s2[r - k] - 'a']--;
            if (r >= k - 1 && memcmp(need, win, sizeof(need)) == 0) return true;
        }
        return false;
    }
};
//<<<END LC567
}

namespace LC424 {
//>>>BEGIN LC424
class Solution {
public:
    int characterReplacement(string s, int k) {
        // LC 424's alphabet is UPPERCASE, so index by the raw character:
        // a 128-slot table is case-agnostic and costs nothing
        int cnt[128] = {0}, l = 0, maxFreq = 0, best = 0;
        for (int r = 0; r < (int)s.size(); r++) {
            maxFreq = max(maxFreq, ++cnt[(unsigned char)s[r]]);
            // a window of length L needs L - maxFreq replacements
            while ((r - l + 1) - maxFreq > k) {
                cnt[(unsigned char)s[l]]--;
                l++;
            }
            // maxFreq is deliberately never decreased: a stale value only makes
            // the test more permissive, and best is only ever set by a window
            // whose maxFreq was genuinely achieved
            best = max(best, r - l + 1);
        }
        return best;
    }
};
//<<<END LC424
}

namespace LC76 {
//>>>BEGIN LC76
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.size() < t.size()) return "";
        int need[128] = {0};
        for (char c : t) need[(unsigned char)c]++;
        int missing = t.size();                  // characters still owed
        int l = 0, bestL = 0, bestLen = INT_MAX;
        for (int r = 0; r < (int)s.size(); r++) {
            // post-decrement: only a character that was still needed counts
            if (need[(unsigned char)s[r]]-- > 0) missing--;
            while (missing == 0) {               // valid -> record, THEN shrink
                if (r - l + 1 < bestLen) { bestLen = r - l + 1; bestL = l; }
                if (++need[(unsigned char)s[l]] > 0) missing++;
                l++;
            }
        }
        return bestLen == INT_MAX ? "" : s.substr(bestL, bestLen);
    }
};
//<<<END LC76
}

namespace LC49 {
//>>>BEGIN LC49
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& w : strs) {
            string key = w;
            sort(key.begin(), key.end());   // canonical form: "eat","tea" -> "aet"
            groups[key].push_back(w);
        }
        vector<vector<string>> res;
        for (auto& kv : groups) res.push_back(move(kv.second));
        return res;
    }
};
//<<<END LC49
}

namespace LC5 {
//>>>BEGIN LC5
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n == 0) return "";
        int bestL = 0, bestLen = 1;
        auto expand = [&](int l, int r) {
            while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
            int len = r - l - 1;            // both overshot by one on exit
            if (len > bestLen) { bestLen = len; bestL = l + 1; }
        };
        for (int c = 0; c < n; c++) {
            expand(c, c);                   // odd-length centre
            expand(c, c + 1);               // even-length centre
        }
        return s.substr(bestL, bestLen);
    }
};
//<<<END LC5
}

namespace LC647 {
//>>>BEGIN LC647
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), total = 0;
        auto expand = [&](int l, int r) {
            while (l >= 0 && r < n && s[l] == s[r]) { total++; l--; r++; }
        };
        for (int c = 0; c < n; c++) {       // exactly 2n - 1 centres
            expand(c, c);
            expand(c, c + 1);
        }
        return total;
    }
};
//<<<END LC647
}

namespace LC680 {
//>>>BEGIN LC680
class Solution {
    bool isPalRange(const string& s, int l, int r) {
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    }
public:
    bool validPalindrome(string s) {
        int l = 0, r = (int)s.size() - 1;
        while (l < r) {
            if (s[l] != s[r])
                // the FIRST mismatch is the only place a deletion can help,
                // and there are exactly two candidates
                return isPalRange(s, l + 1, r) || isPalRange(s, l, r - 1);
            l++;
            r--;
        }
        return true;
    }
};
//<<<END LC680
}

namespace LC151 {
//>>>BEGIN LC151
class Solution {
public:
    string reverseWords(string s) {
        // operator>> skips arbitrary runs of whitespace, leading and trailing
        stringstream ss(s);
        vector<string> words;
        string w;
        while (ss >> w) words.push_back(w);
        string res;
        for (int i = (int)words.size() - 1; i >= 0; i--) {
            res += words[i];
            if (i) res += ' ';               // no trailing space
        }
        return res;
    }
};
//<<<END LC151
}

namespace LC443 {
//>>>BEGIN LC443
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), read = 0, write = 0;
        while (read < n) {
            char c = chars[read];
            int run = 0;
            while (read < n && chars[read] == c) { read++; run++; }
            chars[write++] = c;
            if (run > 1)
                for (char d : to_string(run))   // run can be multi-digit!
                    chars[write++] = d;
        }
        return write;                           // write never overtakes read
    }
};
//<<<END LC443
}

namespace LC8 {
//>>>BEGIN LC8
class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.size();
        while (i < n && s[i] == ' ') i++;                  // 1. leading spaces
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-'))         // 2. at most one sign
            sign = (s[i++] == '-') ? -1 : 1;
        int res = 0;
        while (i < n && isdigit((unsigned char)s[i])) {    // 3. digits
            int d = s[i++] - '0';
            // 4. clamp on EVERY digit - a 30-digit input overflows long long too
            if (res > (INT_MAX - d) / 10)
                return sign == 1 ? INT_MAX : INT_MIN;
            res = res * 10 + d;
        }
        return sign * res;                                 // 5. stop at non-digit
    }
};
//<<<END LC8
}

namespace LC165 {
//>>>BEGIN LC165
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0, j = 0, n = version1.size(), m = version2.size();
        while (i < n || j < m) {          // OR, not AND: a missing part is 0
            long a = 0, b = 0;
            while (i < n && version1[i] != '.') a = a * 10 + (version1[i++] - '0');
            while (j < m && version2[j] != '.') b = b * 10 + (version2[j++] - '0');
            if (a != b) return a < b ? -1 : 1;
            i++;                          // step over the '.', harmless past the end
            j++;
        }
        return 0;
    }
};
//<<<END LC165
}

namespace LC6 {
//>>>BEGIN LC6
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;        // otherwise cur walks out of range
        vector<string> rows(min<int>(numRows, s.size()));
        int cur = 0, dir = -1;             // first flip at row 0 makes dir = +1
        for (char c : s) {
            rows[cur] += c;
            if (cur == 0 || cur == numRows - 1) dir = -dir;
            cur += dir;
        }
        string res;
        for (const string& r : rows) res += r;
        return res;
    }
};
//<<<END LC6
}

namespace LC179 {
//>>>BEGIN LC179
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> v;
        for (int x : nums) v.push_back(to_string(x));
        // compare the two concatenations, not the two strings:
        // "9" must beat "34", and "3" must beat "30" ("330" > "303")
        sort(v.begin(), v.end(),
             [](const string& a, const string& b) { return a + b > b + a; });
        if (v[0] == "0") return "0";        // all zeros collapse to a single "0"
        string res;
        for (const string& s : v) res += s;
        return res;
    }
};
//<<<END LC179
}

// =============================================================================
// TIER 3 - ADVANCED: KMP, HASHING, DP
// =============================================================================

namespace LC214 {
//>>>BEGIN LC214
class Solution {
    vector<int> prefixFunction(const string& p) {
        int m = p.size();
        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];   // fall back to the
            if (p[i] == p[j]) j++;                         // next-longest border
            pi[i] = j;
        }
        return pi;
    }
public:
    string shortestPalindrome(string s) {
        if (s.empty()) return s;
        string rev(s.rbegin(), s.rend());
        // '#' must not occur in s, or a border can straddle the join
        string comb = s + '#' + rev;
        vector<int> pi = prefixFunction(comb);
        int k = pi.back();                 // longest palindromic PREFIX of s
        return rev.substr(0, s.size() - k) + s;
    }
};
//<<<END LC214
}

namespace LC459 {
//>>>BEGIN LC459
class Solution {
    vector<int> prefixFunction(const string& p) {
        int m = p.size();
        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) j = pi[j - 1];
            if (p[i] == p[j]) j++;
            pi[i] = j;
        }
        return pi;
    }
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        vector<int> pi = prefixFunction(s);
        int period = n - pi[n - 1];        // the smallest period of s
        return pi[n - 1] > 0 && n % period == 0;
    }
};
//<<<END LC459
}

namespace LC1392 {
//>>>BEGIN LC1392
class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> pi(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j]) j = pi[j - 1];
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        // the answer IS the definition of the prefix function's last entry:
        // the longest proper prefix that is also a suffix
        return s.substr(0, pi[n - 1]);
    }
};
//<<<END LC1392
}

namespace LC187 {
//>>>BEGIN LC187
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        vector<string> res;
        if (n < 10) return res;
        int code[128] = {0};
        code['A'] = 0; code['C'] = 1; code['G'] = 2; code['T'] = 3;
        // 10 characters over a 4-letter alphabet pack into 20 bits exactly,
        // so this "hash" is a perfect encoding - no collisions to verify
        int mask = (1 << 20) - 1, h = 0;
        unordered_map<int,int> seen;
        for (int i = 0; i < n; i++) {
            h = ((h << 2) | code[(unsigned char)s[i]]) & mask;   // roll in O(1)
            if (i >= 9 && ++seen[h] == 2) res.push_back(s.substr(i - 9, 10));
        }
        return res;
    }
};
//<<<END LC187
}

namespace LC516 {
//>>>BEGIN LC516
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // dp[i][j] depends on dp[i+1][j-1], so i must DESCEND and j ascend
        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++)
                dp[i][j] = (s[i] == s[j]) ? dp[i + 1][j - 1] + 2
                                          : max(dp[i + 1][j], dp[i][j - 1]);
        }
        return dp[0][n - 1];
    }
};
//<<<END LC516
}

namespace LC1143 {
//>>>BEGIN LC1143
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        // dp[i][j] = LCS of the first i chars of text1 and first j of text2
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                // i and j are COUNTS, so the characters are at i-1 and j-1
                dp[i][j] = (text1[i - 1] == text2[j - 1])
                         ? dp[i - 1][j - 1] + 1
                         : max(dp[i - 1][j], dp[i][j - 1]);
        return dp[n][m];
    }
};
//<<<END LC1143
}

namespace LC72 {
//>>>BEGIN LC72
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++) dp[i][0] = i;   // delete everything
        for (int j = 0; j <= m; j++) dp[0][j] = j;   // insert everything
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                dp[i][j] = (word1[i - 1] == word2[j - 1])
                         ? dp[i - 1][j - 1]
                         : 1 + min({dp[i - 1][j - 1],   // replace
                                    dp[i - 1][j],       // delete from word1
                                    dp[i][j - 1]});     // insert into word1
        return dp[n][m];
    }
};
//<<<END LC72
}

namespace LC10 {
//>>>BEGIN LC10
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for (int j = 2; j <= m; j++)              // "a*b*c*" can match empty
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == '*') {
                    // '*' binds to p[j-2], so zero occurrences skips TWO
                    dp[i][j] = dp[i][j - 2];
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1])
                        dp[i][j] = dp[i][j] || dp[i - 1][j];   // one more of it
                } else {
                    dp[i][j] = dp[i - 1][j - 1] &&
                               (p[j - 1] == '.' || p[j - 1] == s[i - 1]);
                }
            }
        return dp[n][m];
    }
};
//<<<END LC10
}

namespace LC44 {
//>>>BEGIN LC44
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for (int j = 1; j <= m; j++)              // only leading '*'s match empty
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == '*')
                    // here '*' stands alone: swallow s[i-1], or match nothing
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else
                    dp[i][j] = dp[i - 1][j - 1] &&
                               (p[j - 1] == '?' || p[j - 1] == s[i - 1]);
            }
        return dp[n][m];
    }
};
//<<<END LC44
}

namespace LC97 {
//>>>BEGIN LC97
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if (n + m != (int)s3.size()) return false;      // the guard that matters
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++) {
                // having consumed i + j characters, the next one is s3[i+j-1]
                if (i && dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) dp[i][j] = true;
                if (j && dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]) dp[i][j] = true;
            }
        return dp[n][m];
    }
};
//<<<END LC97
}

// =============================================================================
// TESTS
// =============================================================================

static vector<string> sorted(vector<string> v) { sort(v.begin(), v.end()); return v; }

static vector<vector<string>> canon(vector<vector<string>> g) {
    for (auto& v : g) sort(v.begin(), v.end());
    sort(g.begin(), g.end());
    return g;
}

int main() {
    cout << "Strings - Part 14 reference solutions\n";
    cout << "=====================================\n";

    // ---------------------------- TIER 1 -------------------------------------
    {
        LC344::Solution s;
        vector<char> a{'h','e','l','l','o'};  s.reverseString(a);
        check(string(a.begin(), a.end()) == "olleh", "LC344 hello");
        vector<char> b{'a','b'};              s.reverseString(b);
        check(string(b.begin(), b.end()) == "ba", "LC344 ab");
        vector<char> c{'x'};                  s.reverseString(c);
        check(string(c.begin(), c.end()) == "x", "LC344 single");
        vector<char> d{};                     s.reverseString(d);
        check(d.empty(), "LC344 empty");
    }
    {
        LC125::Solution s;
        check(s.isPalindrome("A man, a plan, a canal: Panama"), "LC125 panama");
        check(!s.isPalindrome("race a car"), "LC125 race a car");
        check(s.isPalindrome(" "), "LC125 space only");
        check(s.isPalindrome(",,,,"), "LC125 punctuation only");
        check(s.isPalindrome(""), "LC125 empty");
        check(s.isPalindrome("0P") == false, "LC125 0P");
        check(s.isPalindrome("aa"), "LC125 aa");
    }
    {
        LC242::Solution s;
        check(s.isAnagram("anagram", "nagaram"), "LC242 anagram");
        check(!s.isAnagram("rat", "car"), "LC242 rat car");
        check(!s.isAnagram("a", "ab"), "LC242 length differs");
        check(s.isAnagram("", ""), "LC242 empty");
        check(!s.isAnagram("aacc", "ccac"), "LC242 aacc");
    }
    {
        LC387::Solution s;
        eqi(s.firstUniqChar("leetcode"), 0, "LC387 leetcode");
        eqi(s.firstUniqChar("loveleetcode"), 2, "LC387 loveleetcode");
        eqi(s.firstUniqChar("aabb"), -1, "LC387 none");
        eqi(s.firstUniqChar("z"), 0, "LC387 single");
    }
    {
        LC383::Solution s;
        check(!s.canConstruct("a", "b"), "LC383 a b");
        check(!s.canConstruct("aa", "ab"), "LC383 aa ab");
        check(s.canConstruct("aa", "aab"), "LC383 aa aab");
        check(s.canConstruct("", "x"), "LC383 empty note");
    }
    {
        LC14::Solution s;
        vector<string> a{"flower","flow","flight"};  eqs(s.longestCommonPrefix(a), "fl", "LC14 fl");
        vector<string> b{"dog","racecar","car"};     eqs(s.longestCommonPrefix(b), "", "LC14 none");
        vector<string> c{"abc"};                     eqs(s.longestCommonPrefix(c), "abc", "LC14 single");
        vector<string> d{"", "a"};                   eqs(s.longestCommonPrefix(d), "", "LC14 empty member");
        vector<string> e{"ab","ab"};                 eqs(s.longestCommonPrefix(e), "ab", "LC14 identical");
    }
    {
        LC58::Solution s;
        eqi(s.lengthOfLastWord("Hello World"), 5, "LC58 hello world");
        eqi(s.lengthOfLastWord("   fly me   to   the moon  "), 4, "LC58 moon");
        eqi(s.lengthOfLastWord("a"), 1, "LC58 single");
        eqi(s.lengthOfLastWord("day "), 3, "LC58 trailing space");
    }
    {
        LC28::Solution s;
        eqi(s.strStr("sadbutsad", "sad"), 0, "LC28 first");
        eqi(s.strStr("leetcode", "leeto"), -1, "LC28 absent");
        eqi(s.strStr("hello", ""), 0, "LC28 empty needle");
        eqi(s.strStr("aaaaa", "bba"), -1, "LC28 no match");
        eqi(s.strStr("mississippi", "issip"), 4, "LC28 issip");
        eqi(s.strStr("ab", "abc"), -1, "LC28 needle longer");
    }
    {
        LC205::Solution s;
        check(s.isIsomorphic("egg", "add"), "LC205 egg add");
        check(!s.isIsomorphic("foo", "bar"), "LC205 foo bar");
        check(s.isIsomorphic("paper", "title"), "LC205 paper title");
        check(!s.isIsomorphic("ab", "aa"), "LC205 ab aa (needs both maps)");
        check(!s.isIsomorphic("badc", "baba"), "LC205 badc baba");
        check(s.isIsomorphic("", ""), "LC205 empty");
    }
    {
        LC392::Solution s;
        check(s.isSubsequence("abc", "ahbgdc"), "LC392 abc");
        check(!s.isSubsequence("axc", "ahbgdc"), "LC392 axc");
        check(s.isSubsequence("", "anything"), "LC392 empty s");
        check(!s.isSubsequence("a", ""), "LC392 empty t");
    }
    {
        LC13::Solution s;
        eqi(s.romanToInt("III"), 3, "LC13 III");
        eqi(s.romanToInt("LVIII"), 58, "LC13 LVIII");
        eqi(s.romanToInt("MCMXCIV"), 1994, "LC13 MCMXCIV");
        eqi(s.romanToInt("IV"), 4, "LC13 IV");
        eqi(s.romanToInt("MMMCMXCIX"), 3999, "LC13 3999");
    }
    {
        LC12::Solution s;
        eqs(s.intToRoman(3), "III", "LC12 3");
        eqs(s.intToRoman(58), "LVIII", "LC12 58");
        eqs(s.intToRoman(1994), "MCMXCIV", "LC12 1994");
        eqs(s.intToRoman(4), "IV", "LC12 4");
        eqs(s.intToRoman(3999), "MMMCMXCIX", "LC12 3999");
        // round trip against LC13 for every value in range
        LC13::Solution r;
        bool all = true;
        for (int i = 1; i <= 3999; i++) if (r.romanToInt(s.intToRoman(i)) != i) all = false;
        check(all, "LC12/LC13 round trip 1..3999");
    }
    {
        LC415::Solution s;
        eqs(s.addStrings("11", "123"), "134", "LC415 11+123");
        eqs(s.addStrings("456", "77"), "533", "LC415 456+77");
        eqs(s.addStrings("0", "0"), "0", "LC415 0+0");
        eqs(s.addStrings("99", "1"), "100", "LC415 carry out");
        eqs(s.addStrings("999999999999999999", "1"), "1000000000000000000", "LC415 big");
    }

    // ---------------------------- TIER 2 -------------------------------------
    {
        LC3::Solution s;
        eqi(s.lengthOfLongestSubstring("abcabcbb"), 3, "LC3 abcabcbb");
        eqi(s.lengthOfLongestSubstring("bbbbb"), 1, "LC3 bbbbb");
        eqi(s.lengthOfLongestSubstring("pwwkew"), 3, "LC3 pwwkew");
        eqi(s.lengthOfLongestSubstring(""), 0, "LC3 empty");
        eqi(s.lengthOfLongestSubstring(" "), 1, "LC3 space");
        eqi(s.lengthOfLongestSubstring("dvdf"), 3, "LC3 dvdf (the jump case)");
        eqi(s.lengthOfLongestSubstring("abcdef"), 6, "LC3 all distinct");
    }
    {
        LC438::Solution s;
        eqv(s.findAnagrams("cbaebabacd", "abc"), {0, 6}, "LC438 cbaebabacd");
        eqv(s.findAnagrams("abab", "ab"), {0, 1, 2}, "LC438 abab");
        eqv(s.findAnagrams("a", "ab"), {}, "LC438 p longer");
        eqv(s.findAnagrams("aaaaa", "aa"), {0, 1, 2, 3}, "LC438 all same");
        eqv(s.findAnagrams("abc", "abc"), {0}, "LC438 exact");
    }
    {
        LC567::Solution s;
        check(s.checkInclusion("ab", "eidbaooo"), "LC567 present");
        check(!s.checkInclusion("ab", "eidboaoo"), "LC567 absent");
        check(!s.checkInclusion("abc", "ab"), "LC567 s1 longer");
        check(s.checkInclusion("a", "a"), "LC567 single");
        check(s.checkInclusion("adc", "dcda"), "LC567 adc dcda");
    }
    {
        LC424::Solution s;
        eqi(s.characterReplacement("ABAB", 2), 4, "LC424 ABAB k=2");
        eqi(s.characterReplacement("AABABBA", 1), 4, "LC424 AABABBA k=1");
        eqi(s.characterReplacement("AAAA", 0), 4, "LC424 all same k=0");
        eqi(s.characterReplacement("ABCDE", 0), 1, "LC424 all distinct k=0");
        eqi(s.characterReplacement("A", 5), 1, "LC424 k larger than n");
    }
    {
        LC76::Solution s;
        eqs(s.minWindow("ADOBECODEBANC", "ABC"), "BANC", "LC76 BANC");
        eqs(s.minWindow("a", "a"), "a", "LC76 single");
        eqs(s.minWindow("a", "aa"), "", "LC76 impossible");
        eqs(s.minWindow("ab", "b"), "b", "LC76 ab b");
        eqs(s.minWindow("aa", "aa"), "aa", "LC76 duplicates in t");
        eqs(s.minWindow("bba", "ab"), "ba", "LC76 bba ab");
        eqs(s.minWindow("", "a"), "", "LC76 empty s");
    }
    {
        LC49::Solution s;
        vector<string> in{"eat","tea","tan","ate","nat","bat"};
        auto got = canon(s.groupAnagrams(in));
        vector<vector<string>> want{{"ate","eat","tea"},{"bat"},{"nat","tan"}};
        check(got == canon(want), "LC49 classic");
        vector<string> in2{""};
        auto g2 = s.groupAnagrams(in2);
        check(g2.size() == 1 && g2[0].size() == 1, "LC49 empty string");
        vector<string> in3{"a"};
        auto g3 = s.groupAnagrams(in3);
        check(g3.size() == 1, "LC49 single");
    }
    {
        LC5::Solution s;
        string r1 = s.longestPalindrome("babad");
        check(r1 == "bab" || r1 == "aba", "LC5 babad");
        eqs(s.longestPalindrome("cbbd"), "bb", "LC5 cbbd (even)");
        eqs(s.longestPalindrome("a"), "a", "LC5 single");
        eqs(s.longestPalindrome("ac").size() == 1 ? "ok" : "no", "ok", "LC5 no palindrome > 1");
        eqs(s.longestPalindrome("aaaa"), "aaaa", "LC5 all same");
        eqs(s.longestPalindrome("forgeeksskeegfor"), "geeksskeeg", "LC5 geeksskeeg");
    }
    {
        LC647::Solution s;
        eqi(s.countSubstrings("abc"), 3, "LC647 abc");
        eqi(s.countSubstrings("aaa"), 6, "LC647 aaa");
        eqi(s.countSubstrings("a"), 1, "LC647 single");
        eqi(s.countSubstrings("abba"), 6, "LC647 abba");
    }
    {
        LC680::Solution s;
        check(s.validPalindrome("aba"), "LC680 already palindrome");
        check(s.validPalindrome("abca"), "LC680 abca");
        check(!s.validPalindrome("abc"), "LC680 abc");
        check(s.validPalindrome("deeee"), "LC680 deeee");
        check(s.validPalindrome("cbbcc"), "LC680 cbbcc");
        check(s.validPalindrome(""), "LC680 empty");
        check(s.validPalindrome("eceec"), "LC680 eceec");
    }
    {
        LC151::Solution s;
        eqs(s.reverseWords("the sky is blue"), "blue is sky the", "LC151 basic");
        eqs(s.reverseWords("  hello world  "), "world hello", "LC151 padding");
        eqs(s.reverseWords("a good   example"), "example good a", "LC151 inner runs");
        eqs(s.reverseWords("word"), "word", "LC151 single");
        eqs(s.reverseWords("   "), "", "LC151 spaces only");
    }
    {
        LC443::Solution s;
        vector<char> a{'a','a','b','b','c','c','c'};
        int n1 = s.compress(a);
        check(string(a.begin(), a.begin() + n1) == "a2b2c3", "LC443 a2b2c3");
        vector<char> b{'a'};
        check(s.compress(b) == 1 && b[0] == 'a', "LC443 single");
        vector<char> c(12, 'a');
        int n3 = s.compress(c);
        check(string(c.begin(), c.begin() + n3) == "a12", "LC443 multi-digit run");
        vector<char> d{'a','b','c'};
        int n4 = s.compress(d);
        check(string(d.begin(), d.begin() + n4) == "abc", "LC443 no runs");
    }
    {
        LC8::Solution s;
        eqi(s.myAtoi("42"), 42, "LC8 42");
        eqi(s.myAtoi("   -42"), -42, "LC8 -42 with spaces");
        eqi(s.myAtoi("4193 with words"), 4193, "LC8 trailing words");
        eqi(s.myAtoi("words and 987"), 0, "LC8 leading words");
        eqi(s.myAtoi("-91283472332"), INT_MIN, "LC8 clamp low");
        eqi(s.myAtoi("91283472332"), INT_MAX, "LC8 clamp high");
        eqi(s.myAtoi(""), 0, "LC8 empty");
        eqi(s.myAtoi("+-12"), 0, "LC8 double sign");
        eqi(s.myAtoi("00000-42a1234"), 0, "LC8 leading zeros then sign");
        eqi(s.myAtoi("2147483648"), INT_MAX, "LC8 one past max");
        eqi(s.myAtoi("-2147483648"), INT_MIN, "LC8 exact min");
        eqi(s.myAtoi("99999999999999999999999999999999"), INT_MAX, "LC8 30 digits");
    }
    {
        LC165::Solution s;
        eqi(s.compareVersion("1.01", "1.001"), 0, "LC165 leading zeros");
        eqi(s.compareVersion("1.0", "1.0.0"), 0, "LC165 missing part");
        eqi(s.compareVersion("0.1", "1.1"), -1, "LC165 less");
        eqi(s.compareVersion("1.2", "1.10"), -1, "LC165 numeric not lexicographic");
        eqi(s.compareVersion("1.0.1", "1"), 1, "LC165 greater");
        eqi(s.compareVersion("7.5.2.4", "7.5.3"), -1, "LC165 deep");
    }
    {
        LC6::Solution s;
        eqs(s.convert("PAYPALISHIRING", 3), "PAHNAPLSIIGYIR", "LC6 3 rows");
        eqs(s.convert("PAYPALISHIRING", 4), "PINALSIGYAHRPI", "LC6 4 rows");
        eqs(s.convert("A", 1), "A", "LC6 one row");
        eqs(s.convert("AB", 1), "AB", "LC6 one row two chars");
        eqs(s.convert("AB", 5), "AB", "LC6 more rows than chars");
    }
    {
        LC179::Solution s;
        vector<int> a{10, 2};             eqs(s.largestNumber(a), "210", "LC179 10 2");
        vector<int> b{3,30,34,5,9};       eqs(s.largestNumber(b), "9534330", "LC179 classic");
        vector<int> c{0, 0};              eqs(s.largestNumber(c), "0", "LC179 all zeros");
        vector<int> d{1};                 eqs(s.largestNumber(d), "1", "LC179 single");
        vector<int> e{34323, 3432};       eqs(s.largestNumber(e), "343234323", "LC179 prefix case");
    }

    // ---------------------------- TIER 3 -------------------------------------
    {
        LC214::Solution s;
        eqs(s.shortestPalindrome("aacecaaa"), "aaacecaaa", "LC214 aacecaaa");
        eqs(s.shortestPalindrome("abcd"), "dcbabcd", "LC214 abcd");
        eqs(s.shortestPalindrome(""), "", "LC214 empty");
        eqs(s.shortestPalindrome("a"), "a", "LC214 single");
        eqs(s.shortestPalindrome("aba"), "aba", "LC214 already palindrome");
        eqs(s.shortestPalindrome("aabba"), "abbaabba", "LC214 aabba");
    }
    {
        LC459::Solution s;
        check(s.repeatedSubstringPattern("abab"), "LC459 abab");
        check(!s.repeatedSubstringPattern("aba"), "LC459 aba");
        check(s.repeatedSubstringPattern("abcabcabcabc"), "LC459 abc x4");
        check(!s.repeatedSubstringPattern("a"), "LC459 single");
        check(s.repeatedSubstringPattern("aa"), "LC459 aa");
        check(!s.repeatedSubstringPattern("abaababaab") == false, "LC459 abaababaab");
    }
    {
        LC1392::Solution s;
        eqs(s.longestPrefix("level"), "l", "LC1392 level");
        eqs(s.longestPrefix("ababab"), "abab", "LC1392 ababab");
        eqs(s.longestPrefix("leetcodeleet"), "leet", "LC1392 leetcodeleet");
        eqs(s.longestPrefix("a"), "", "LC1392 single");
        eqs(s.longestPrefix("abcd"), "", "LC1392 no border");
    }
    {
        LC187::Solution s;
        eqv({(int)s.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT").size()},
            {2}, "LC187 count");
        auto r = sorted(s.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"));
        check(r == sorted({"AAAAACCCCC", "CCCCCAAAAA"}), "LC187 classic");
        auto r2 = s.findRepeatedDnaSequences("AAAAAAAAAAAAA");
        check(r2.size() == 1 && r2[0] == "AAAAAAAAAA", "LC187 no duplicates in output");
        check(s.findRepeatedDnaSequences("AAAAA").empty(), "LC187 too short");
        check(s.findRepeatedDnaSequences("AAAAACCCCC").empty(), "LC187 exactly 10");
    }
    {
        LC516::Solution s;
        eqi(s.longestPalindromeSubseq("bbbab"), 4, "LC516 bbbab");
        eqi(s.longestPalindromeSubseq("cbbd"), 2, "LC516 cbbd");
        eqi(s.longestPalindromeSubseq("a"), 1, "LC516 single");
        eqi(s.longestPalindromeSubseq("abcde"), 1, "LC516 all distinct");
        eqi(s.longestPalindromeSubseq("agbdba"), 5, "LC516 agbdba");
    }
    {
        LC1143::Solution s;
        eqi(s.longestCommonSubsequence("abcde", "ace"), 3, "LC1143 ace");
        eqi(s.longestCommonSubsequence("abc", "abc"), 3, "LC1143 identical");
        eqi(s.longestCommonSubsequence("abc", "def"), 0, "LC1143 disjoint");
        eqi(s.longestCommonSubsequence("", "abc"), 0, "LC1143 empty");
        eqi(s.longestCommonSubsequence("bsbininm", "jmjkbkjkv"), 1, "LC1143 tricky");
        // LPS(s) == LCS(s, reverse(s))
        LC516::Solution p;
        string t = "agbdba", rt(t.rbegin(), t.rend());
        eqi(s.longestCommonSubsequence(t, rt), p.longestPalindromeSubseq(t),
            "LC1143 LPS identity");
    }
    {
        LC72::Solution s;
        eqi(s.minDistance("horse", "ros"), 3, "LC72 horse ros");
        eqi(s.minDistance("intention", "execution"), 5, "LC72 intention");
        eqi(s.minDistance("", "abc"), 3, "LC72 empty source");
        eqi(s.minDistance("abc", ""), 3, "LC72 empty target");
        eqi(s.minDistance("", ""), 0, "LC72 both empty");
        eqi(s.minDistance("abc", "abc"), 0, "LC72 identical");
        eqi(s.minDistance("a", "ab"), 1, "LC72 prefix");
    }
    {
        LC10::Solution s;
        check(!s.isMatch("aa", "a"), "LC10 aa a");
        check(s.isMatch("aa", "a*"), "LC10 a*");
        check(s.isMatch("ab", ".*"), "LC10 .*");
        check(s.isMatch("aab", "c*a*b"), "LC10 c*a*b");
        check(!s.isMatch("mississippi", "mis*is*p*."), "LC10 mississippi");
        check(s.isMatch("", "a*"), "LC10 empty vs a*");
        check(s.isMatch("", ""), "LC10 both empty");
        check(!s.isMatch("a", ""), "LC10 empty pattern");
        check(s.isMatch("aaa", "ab*a*c*a"), "LC10 aaa");
    }
    {
        LC44::Solution s;
        check(!s.isMatch("aa", "a"), "LC44 aa a");
        check(s.isMatch("aa", "*"), "LC44 star");
        check(!s.isMatch("cb", "?a"), "LC44 cb ?a");
        check(s.isMatch("adceb", "*a*b"), "LC44 adceb");
        check(!s.isMatch("acdcb", "a*c?b"), "LC44 acdcb");
        check(s.isMatch("", "*"), "LC44 empty vs star");
        check(s.isMatch("", "***"), "LC44 empty vs stars");
        check(!s.isMatch("", "?"), "LC44 empty vs ?");
        check(s.isMatch("abc", "a?c"), "LC44 a?c");
    }
    {
        LC97::Solution s;
        check(s.isInterleave("aabcc", "dbbca", "aadbbcbcac"), "LC97 true case");
        check(!s.isInterleave("aabcc", "dbbca", "aadbbbaccc"), "LC97 false case");
        check(s.isInterleave("", "", ""), "LC97 all empty");
        check(!s.isInterleave("a", "", ""), "LC97 length guard");
        check(s.isInterleave("a", "b", "ab"), "LC97 ab");
        check(s.isInterleave("a", "b", "ba"), "LC97 ba");
        check(!s.isInterleave("abc", "def", "abcdefg"), "LC97 wrong length");
    }

    cout << "=====================================\n";
    cout << "passed: " << g_pass << "   failed: " << g_fail << "\n";
    if (g_fail == 0) cout << "ALL TESTS PASSED\n";
    return g_fail != 0;
}
