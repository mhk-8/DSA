// ============================================================================
//  Heaps & Priority Queues — reference solutions for Part 13 of the guide
//  All 38 problems, Tier 1 -> Tier 2 -> Tier 3, each with test cases.
//
//  Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part13-solutions.cpp && ./ref
//
//  Every solution lives in its own namespace so each class can be called
//  Solution, exactly as LeetCode expects. The //>>>BEGIN / //<<<END markers
//  delimit the code that is printed in Heaps-and-Priority-Queues-Solved-
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

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
static ListNode* makeList(const vector<int>& v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
static vector<int> toVec(ListNode* h) { vector<int> v; for (; h; h = h->next) v.push_back(h->val); return v; }

// ============================================================================
//  TIER 1
// ============================================================================

// -------------------------------------------------------------------- LC 1046
namespace LC1046 {
//>>>BEGIN LC1046
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq(stones.begin(), stones.end());   // max-heap, O(n) build
        while (pq.size() > 1) {
            int y = pq.top(); pq.pop();                         // heaviest
            int x = pq.top(); pq.pop();                         // second heaviest
            if (y != x) pq.push(y - x);                         // the remainder goes back
        }
        return pq.empty() ? 0 : pq.top();
    }
};
//<<<END LC1046
}

// --------------------------------------------------------------------- LC 703
namespace LC703 {
//>>>BEGIN LC703
class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;   // MIN-heap of the k largest
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.push(val);
        if ((int)pq.size() > k) pq.pop();                 // evict the smallest
        return pq.top();                                  // smallest of the top k
    }
};
//<<<END LC703
}

// --------------------------------------------------------------------- LC 215
namespace LC215 {
//>>>BEGIN LC215
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;   // min-heap, size <= k
        for (int x : nums) {
            pq.push(x);
            if ((int)pq.size() > k) pq.pop();
        }
        return pq.top();          // the weakest member of the top-k club
    }
};
//<<<END LC215
}

// --------------------------------------------------------------------- LC 347
namespace LC347 {
//>>>BEGIN LC347
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int x : nums) freq[x]++;
        // min-heap on frequency: the top is the LEAST frequent of the current k
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (auto& [val, f] : freq) {
            pq.push({f, val});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<int> res;
        while (!pq.empty()) { res.push_back(pq.top().second); pq.pop(); }
        return res;
    }
};
//<<<END LC347
}

// --------------------------------------------------------------------- LC 973
namespace LC973 {
//>>>BEGIN LC973
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // MAX-heap on squared distance: the top is the FARTHEST of the k kept
        priority_queue<pair<long long, int>> pq;
        for (int i = 0; i < (int)points.size(); i++) {
            long long x = points[i][0], y = points[i][1];
            pq.push({x * x + y * y, i});              // no sqrt needed
            if ((int)pq.size() > k) pq.pop();
        }
        vector<vector<int>> res;
        while (!pq.empty()) { res.push_back(points[pq.top().second]); pq.pop(); }
        return res;
    }
};
//<<<END LC973
}

// -------------------------------------------------------------------- LC 1337
namespace LC1337 {
//>>>BEGIN LC1337
class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        // max-heap of (soldiers, row): pair compares soldiers, then row index,
        // which is exactly the tie-break the problem asks for
        priority_queue<pair<int, int>> pq;
        for (int r = 0; r < (int)mat.size(); r++) {
            int soldiers = accumulate(mat[r].begin(), mat[r].end(), 0);
            pq.push({soldiers, r});
            if ((int)pq.size() > k) pq.pop();          // drop the strongest
        }
        vector<int> res(k);
        for (int i = k - 1; i >= 0; i--) { res[i] = pq.top().second; pq.pop(); }
        return res;                                    // weakest first
    }
};
//<<<END LC1337
}

// -------------------------------------------------------------------- LC 2558
namespace LC2558 {
//>>>BEGIN LC2558
class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> pq(gifts.begin(), gifts.end());
        while (k--) {
            int top = pq.top(); pq.pop();
            pq.push((int)sqrt((double)top));          // floor of the square root
        }
        long long sum = 0;
        while (!pq.empty()) { sum += pq.top(); pq.pop(); }
        return sum;
    }
};
//<<<END LC2558
}

// --------------------------------------------------------------------- LC 506
namespace LC506 {
//>>>BEGIN LC506
class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        priority_queue<pair<int, int>> pq;            // (score, athlete index)
        for (int i = 0; i < (int)score.size(); i++) pq.push({score[i], i});
        vector<string> res(score.size());
        const string medal[3] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        for (int place = 1; !pq.empty(); place++) {
            int i = pq.top().second; pq.pop();
            res[i] = place <= 3 ? medal[place - 1] : to_string(place);
        }
        return res;
    }
};
//<<<END LC506
}

// --------------------------------------------------------------------- LC 451
namespace LC451 {
//>>>BEGIN LC451
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> freq;
        for (char c : s) freq[c]++;
        priority_queue<pair<int, char>> pq;           // most frequent on top
        for (auto& [c, f] : freq) pq.push({f, c});
        string res;
        while (!pq.empty()) {
            auto [f, c] = pq.top(); pq.pop();
            res.append(f, c);                         // f copies of c
        }
        return res;
    }
};
//<<<END LC451
}

// --------------------------------------------------------------------- LC 692
namespace LC692 {
//>>>BEGIN LC692
class Solution {
    // "a < b" for a MIN-heap must mean "a is BETTER than b" — the heap keeps the
    // worst on top so it can be evicted. Better = higher count, then smaller word.
    struct Cmp {
        bool operator()(const pair<int, string>& a, const pair<int, string>& b) const {
            if (a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        }
    };
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> freq;
        for (auto& w : words) freq[w]++;
        priority_queue<pair<int, string>, vector<pair<int, string>>, Cmp> pq;
        for (auto& [w, f] : freq) {
            pq.push({f, w});
            if ((int)pq.size() > k) pq.pop();         // pops the WORST candidate
        }
        vector<string> res(k);
        for (int i = k - 1; i >= 0; i--) { res[i] = pq.top().second; pq.pop(); }
        return res;                                   // best first
    }
};
//<<<END LC692
}

// ---------------------------------------------------------------------- LC 23
namespace LC23 {
//>>>BEGIN LC23
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);  // min-heap
        for (ListNode* h : lists) if (h) pq.push(h);  // one head per list
        ListNode dummy(0), *tail = &dummy;
        while (!pq.empty()) {
            ListNode* node = pq.top(); pq.pop();      // smallest head overall
            tail->next = node; tail = node;
            if (node->next) pq.push(node->next);      // its successor replaces it
        }
        return dummy.next;
    }
};
//<<<END LC23
}

// --------------------------------------------------------------------- LC 378
namespace LC378 {
//>>>BEGIN LC378
class Solution {
public:
    int kthSmallest(vector<vector<int>>& m, int k) {
        int n = m.size();
        // (value, row, col); every row is a sorted list -> k-way merge
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        for (int r = 0; r < min(n, k); r++) pq.push({m[r][0], r, 0});
        while (--k) {                                 // pop k-1 times
            auto [v, r, c] = pq.top(); pq.pop();
            if (c + 1 < n) pq.push({m[r][c + 1], r, c + 1});
        }
        return get<0>(pq.top());
    }
};
//<<<END LC378
}

// -------------------------------------------------------------------- LC 1962
namespace LC1962 {
//>>>BEGIN LC1962
class Solution {
public:
    int minStoneSum(vector<int>& piles, int k) {
        priority_queue<int> pq(piles.begin(), piles.end());
        int total = accumulate(piles.begin(), piles.end(), 0);
        while (k--) {
            int top = pq.top(); pq.pop();
            int removed = top / 2;                    // floor(top / 2) stones go
            total -= removed;
            pq.push(top - removed);
        }
        return total;
    }
};
//<<<END LC1962
}

// ============================================================================
//  TIER 2
// ============================================================================

// --------------------------------------------------------------------- LC 295
namespace LC295 {
//>>>BEGIN LC295
class MedianFinder {
    priority_queue<int> lo;                               // max-heap: smaller half
    priority_queue<int, vector<int>, greater<int>> hi;    // min-heap: larger half
    // invariant: every lo <= every hi, and lo.size() == hi.size() or one more
public:
    void addNum(int num) {
        lo.push(num);                         // 1. always enter through lo
        hi.push(lo.top()); lo.pop();          // 2. hand lo's largest to hi (fixes order)
        if (hi.size() > lo.size()) {          // 3. rebalance sizes
            lo.push(hi.top()); hi.pop();
        }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + (double)hi.top()) / 2.0;
    }
};
//<<<END LC295
}

// --------------------------------------------------------------------- LC 621
namespace LC621 {
//>>>BEGIN LC621
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int cnt[26] = {0};
        for (char t : tasks) cnt[t - 'A']++;
        priority_queue<int> ready;                    // remaining counts, largest first
        for (int c : cnt) if (c) ready.push(c);
        queue<pair<int, int>> cooling;                // (remaining count, time it is free)
        int time = 0;
        while (!ready.empty() || !cooling.empty()) {
            time++;
            if (!ready.empty()) {                     // run the most-remaining task
                int left = ready.top() - 1; ready.pop();
                if (left) cooling.push({left, time + n});
            }                                         // else: this slot is idle
            if (!cooling.empty() && cooling.front().second == time) {
                ready.push(cooling.front().first);    // cooldown over
                cooling.pop();
            }
        }
        return time;
    }
};
//<<<END LC621
}

// --------------------------------------------------------------------- LC 767
namespace LC767 {
//>>>BEGIN LC767
class Solution {
public:
    string reorganizeString(string s) {
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < 26; i++) if (cnt[i]) pq.push({cnt[i], char('a' + i)});
        string res;
        while (pq.size() >= 2) {                      // place the two most frequent
            auto [f1, c1] = pq.top(); pq.pop();
            auto [f2, c2] = pq.top(); pq.pop();
            res += c1; res += c2;                     // different letters: always safe
            if (--f1) pq.push({f1, c1});
            if (--f2) pq.push({f2, c2});
        }
        if (!pq.empty()) {                            // one letter left over
            if (pq.top().first > 1) return "";        // it would have to repeat
            res += pq.top().second;
        }
        return res;
    }
};
//<<<END LC767
}

// -------------------------------------------------------------------- LC 1642
namespace LC1642 {
//>>>BEGIN LC1642
class Solution {
public:
    int furthestBuilding(vector<int>& h, int bricks, int ladders) {
        // min-heap of the climbs currently covered by ladders
        priority_queue<int, vector<int>, greater<int>> ladderClimbs;
        for (int i = 0; i + 1 < (int)h.size(); i++) {
            int climb = h[i + 1] - h[i];
            if (climb <= 0) continue;
            ladderClimbs.push(climb);                 // tentatively use a ladder
            if ((int)ladderClimbs.size() > ladders) { // one ladder too many:
                bricks -= ladderClimbs.top();         // pay the SMALLEST climb in bricks
                ladderClimbs.pop();
            }
            if (bricks < 0) return i;                 // cannot reach building i+1
        }
        return (int)h.size() - 1;
    }
};
//<<<END LC1642
}

// -------------------------------------------------------------------- LC 1834
namespace LC1834 {
//>>>BEGIN LC1834
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(),
             [&](int a, int b) { return tasks[a][0] < tasks[b][0]; });   // by arrival
        // available tasks: shortest processing time, then smallest index
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> order;
        long long time = 0;
        int i = 0;
        while ((int)order.size() < n) {
            if (pq.empty() && time < tasks[idx[i]][0])
                time = tasks[idx[i]][0];              // CPU idle: jump ahead
            while (i < n && tasks[idx[i]][0] <= time) {
                pq.push({tasks[idx[i]][1], idx[i]});
                i++;
            }
            auto [proc, id] = pq.top(); pq.pop();
            time += proc;
            order.push_back(id);
        }
        return order;
    }
};
//<<<END LC1834
}

// --------------------------------------------------------------------- LC 373
namespace LC373 {
//>>>BEGIN LC373
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& a, vector<int>& b, int k) {
        // (sum, i, j). Row i is the sorted list a[i]+b[0], a[i]+b[1], ...
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        for (int i = 0; i < (int)a.size() && i < k; i++) pq.push({a[i] + b[0], i, 0});
        vector<vector<int>> res;
        while (k-- && !pq.empty()) {
            auto [s, i, j] = pq.top(); pq.pop();
            res.push_back({a[i], b[j]});
            if (j + 1 < (int)b.size()) pq.push({a[i] + b[j + 1], i, j + 1});  // next in row i
        }
        return res;
    }
};
//<<<END LC373
}

// --------------------------------------------------------------------- LC 355
namespace LC355 {
//>>>BEGIN LC355
class Twitter {
    int clock = 0;
    unordered_map<int, vector<pair<int, int>>> tweets;   // user -> (time, tweetId)
    unordered_map<int, unordered_set<int>> follows;
public:
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({clock++, tweetId});
    }
    vector<int> getNewsFeed(int userId) {
        // k-way merge of each followee's tweet list, newest first
        priority_queue<tuple<int, int, int>> pq;          // (time, user, index)
        follows[userId].insert(userId);                   // see your own tweets
        for (int u : follows[userId]) {
            auto& t = tweets[u];
            if (!t.empty()) pq.push({t.back().first, u, (int)t.size() - 1});
        }
        vector<int> feed;
        while (!pq.empty() && feed.size() < 10) {
            auto [time, u, i] = pq.top(); pq.pop();
            feed.push_back(tweets[u][i].second);
            if (i > 0) pq.push({tweets[u][i - 1].first, u, i - 1});
        }
        return feed;
    }
    void follow(int a, int b)   { follows[a].insert(b); }
    void unfollow(int a, int b) { if (a != b) follows[a].erase(b); }
};
//<<<END LC355
}

// --------------------------------------------------------------------- LC 264
namespace LC264 {
//>>>BEGIN LC264
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        pq.push(1);
        long long cur = 1;
        for (int i = 0; i < n; i++) {
            cur = pq.top(); pq.pop();
            while (!pq.empty() && pq.top() == cur) pq.pop();   // drop duplicates
            for (int f : {2, 3, 5}) pq.push(cur * f);           // generate successors
        }
        return (int)cur;
    }
};
//<<<END LC264
}

// --------------------------------------------------------------------- LC 658
namespace LC658 {
//>>>BEGIN LC658
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        // max-heap on (distance, value): the top is the WORST of the k kept,
        // and a larger value loses a distance tie, as the problem requires
        priority_queue<pair<int, int>> pq;
        for (int v : arr) {
            pq.push({abs(v - x), v});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<int> res;
        while (!pq.empty()) { res.push_back(pq.top().second); pq.pop(); }
        sort(res.begin(), res.end());
        return res;
    }
};
//<<<END LC658
}

// --------------------------------------------------------------------- LC 846
namespace LC846 {
//>>>BEGIN LC846
class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize) return false;
        unordered_map<int, int> cnt;
        for (int c : hand) cnt[c]++;
        priority_queue<int, vector<int>, greater<int>> pq;   // distinct values
        for (auto& [v, c] : cnt) pq.push(v);
        while (!pq.empty()) {
            int first = pq.top();                    // smallest card MUST start a group
            for (int v = first; v < first + groupSize; v++) {
                if (cnt[v] == 0) return false;       // a gap in the run
                if (--cnt[v] == 0) {
                    // a value can only run out if it is the current minimum;
                    // otherwise a smaller value is left with no way to finish
                    if (v != pq.top()) return false;
                    pq.pop();
                }
            }
        }
        return true;
    }
};
//<<<END LC846
}

// --------------------------------------------------------------------- LC 743
namespace LC743 {
//>>>BEGIN LC743
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n + 1);           // u -> (v, w)
        for (auto& t : times) adj[t[0]].push_back({t[1], t[2]});
        vector<int> dist(n + 1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;  // (dist, node)
        dist[k] = 0;
        pq.push({0, k});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;                       // stale entry: skip
            for (auto [v, w] : adj[u])
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
        }
        int best = *max_element(dist.begin() + 1, dist.end());
        return best == INT_MAX ? -1 : best;
    }
};
//<<<END LC743
}

// -------------------------------------------------------------------- LC 1353
namespace LC1353 {
//>>>BEGIN LC1353
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());                  // by start day
        priority_queue<int, vector<int>, greater<int>> ends; // open events' end days
        int i = 0, n = events.size(), day = 0, attended = 0;
        while (i < n || !ends.empty()) {
            if (ends.empty()) day = max(day, events[i][0]);  // skip idle days
            while (i < n && events[i][0] <= day) ends.push(events[i++][1]);
            ends.pop();                                      // attend the one ending first
            attended++;
            day++;
            while (!ends.empty() && ends.top() < day) ends.pop();   // expired
        }
        return attended;
    }
};
//<<<END LC1353
}

// -------------------------------------------------------------------- LC 1405
namespace LC1405 {
//>>>BEGIN LC1405
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        if (a) pq.push({a, 'a'});
        if (b) pq.push({b, 'b'});
        if (c) pq.push({c, 'c'});
        string s;
        while (!pq.empty()) {
            auto [f1, c1] = pq.top(); pq.pop();
            int n = s.size();
            if (n >= 2 && s[n - 1] == c1 && s[n - 2] == c1) {   // would make "ccc"
                if (pq.empty()) break;                          // nothing else to use
                auto [f2, c2] = pq.top(); pq.pop();             // use the runner-up once
                s += c2;
                if (--f2) pq.push({f2, c2});
                pq.push({f1, c1});                              // the leader waits
            } else {
                s += c1;
                if (--f1) pq.push({f1, c1});
            }
        }
        return s;
    }
};
//<<<END LC1405
}

// --------------------------------------------------------------------- LC 871
namespace LC871 {
//>>>BEGIN LC871
class Solution {
public:
    int minRefuelStops(int target, int fuel, vector<vector<int>>& stations) {
        priority_queue<int> passed;          // fuel of stations we drove past
        long long reach = fuel;
        int stops = 0, i = 0, n = stations.size();
        while (reach < target) {
            while (i < n && stations[i][0] <= reach) passed.push(stations[i++][1]);
            if (passed.empty()) return -1;   // stranded
            reach += passed.top();           // "retroactively" stop at the best one
            passed.pop();
            stops++;
        }
        return stops;
    }
};
//<<<END LC871
}

// -------------------------------------------------------------------- LC 1882
namespace LC1882 {
//>>>BEGIN LC1882
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        using T = tuple<long long, int, int>;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> freeQ;  // (weight, idx)
        priority_queue<T, vector<T>, greater<>> busy;               // (freeAt, weight, idx)
        for (int i = 0; i < (int)servers.size(); i++) freeQ.push({servers[i], i});
        vector<int> res(tasks.size());
        long long time = 0;
        for (int j = 0; j < (int)tasks.size(); j++) {
            time = max(time, (long long)j);          // task j arrives at second j
            if (freeQ.empty()) time = get<0>(busy.top());   // wait for the first release
            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [t, w, i] = busy.top(); busy.pop();
                freeQ.push({w, i});
            }
            auto [w, i] = freeQ.top(); freeQ.pop();
            res[j] = i;
            busy.push({time + tasks[j], w, i});
        }
        return res;
    }
};
//<<<END LC1882
}

// ============================================================================
//  TIER 3
// ============================================================================

// --------------------------------------------------------------------- LC 480
namespace LC480 {
//>>>BEGIN LC480
class Solution {
    // LC 295's two halves, but a window needs DELETION -> multisets,
    // the "heap you can erase from".  lo.size() == hi.size() or one more.
    multiset<int> lo, hi;
    void balance() {          // one move is enough: sizes drift by at most 2
        if (lo.size() > hi.size() + 1) { hi.insert(*lo.rbegin()); lo.erase(prev(lo.end())); }
        else if (lo.size() < hi.size()) { lo.insert(*hi.begin()); hi.erase(hi.begin()); }
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        for (int i = 0; i < (int)nums.size(); i++) {
            int x = nums[i];
            if (lo.empty() || x <= *lo.rbegin()) lo.insert(x); else hi.insert(x);
            if (i >= k) {                            // slide: erase ONE copy of the oldest
                int y = nums[i - k];
                auto it = lo.find(y);
                if (it != lo.end()) lo.erase(it); else hi.erase(hi.find(y));
            }
            balance();
            if (i >= k - 1)
                res.push_back(k % 2 ? *lo.rbegin() : ((double)*lo.rbegin() + *hi.begin()) / 2.0);
        }
        return res;
    }
};
//<<<END LC480
}

// --------------------------------------------------------------------- LC 502
namespace LC502 {
//>>>BEGIN LC502
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<pair<int, int>> proj(n);                    // (capital needed, profit)
        for (int i = 0; i < n; i++) proj[i] = {capital[i], profits[i]};
        sort(proj.begin(), proj.end());
        priority_queue<int> affordable;                    // profits we can start now
        int i = 0;
        while (k--) {
            while (i < n && proj[i].first <= w) affordable.push(proj[i++].second);
            if (affordable.empty()) break;                 // nothing affordable, ever
            w += affordable.top();                         // greedy: most profitable
            affordable.pop();
        }
        return w;
    }
};
//<<<END LC502
}

// --------------------------------------------------------------------- LC 630
namespace LC630 {
//>>>BEGIN LC630
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [](auto& a, auto& b) { return a[1] < b[1]; });   // earliest deadline first
        priority_queue<int> taken;                             // durations, longest on top
        int time = 0;
        for (auto& c : courses) {
            taken.push(c[0]);
            time += c[0];
            if (time > c[1]) {                 // deadline broken: drop the longest course
                time -= taken.top();           // (it may be the one just added)
                taken.pop();
            }
        }
        return taken.size();
    }
};
//<<<END LC630
}

// --------------------------------------------------------------------- LC 857
namespace LC857 {
//>>>BEGIN LC857
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        int n = quality.size();
        vector<pair<double, int>> w(n);                     // (wage/quality, quality)
        for (int i = 0; i < n; i++) w[i] = {(double)wage[i] / quality[i], quality[i]};
        sort(w.begin(), w.end());                           // by ratio, ascending
        priority_queue<int> pq;                             // qualities, largest on top
        long long qsum = 0;
        double best = 1e18;
        for (auto& [ratio, q] : w) {
            pq.push(q); qsum += q;
            if ((int)pq.size() > k) { qsum -= pq.top(); pq.pop(); }   // drop the heaviest
            // this worker has the highest ratio so far, so it sets everyone's pay rate
            if ((int)pq.size() == k) best = min(best, ratio * qsum);
        }
        return best;
    }
};
//<<<END LC857
}

// -------------------------------------------------------------------- LC 1383
namespace LC1383 {
//>>>BEGIN LC1383
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> eng(n);                         // (efficiency, speed)
        for (int i = 0; i < n; i++) eng[i] = {efficiency[i], speed[i]};
        sort(eng.rbegin(), eng.rend());                        // efficiency, descending
        priority_queue<int, vector<int>, greater<int>> speeds; // min-heap of chosen speeds
        long long sum = 0, best = 0;
        for (auto& [e, s] : eng) {
            speeds.push(s); sum += s;
            if ((int)speeds.size() > k) { sum -= speeds.top(); speeds.pop(); }
            best = max(best, sum * e);         // e is the minimum efficiency of the team
        }
        return best % 1000000007;              // modulo only AFTER maximising
    }
};
//<<<END LC1383
}

// --------------------------------------------------------------------- LC 632
namespace LC632 {
//>>>BEGIN LC632
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // one pointer per list; the heap gives the current minimum, and we
        // track the current maximum by hand
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        int curMax = INT_MIN;
        for (int i = 0; i < (int)nums.size(); i++) {
            pq.push({nums[i][0], i, 0});
            curMax = max(curMax, nums[i][0]);
        }
        vector<int> best{get<0>(pq.top()), curMax};
        while (true) {
            auto [v, i, j] = pq.top(); pq.pop();
            if (curMax - v < best[1] - best[0]) best = {v, curMax};
            if (j + 1 == (int)nums[i].size()) break;      // a list ran out: done
            int nv = nums[i][j + 1];
            pq.push({nv, i, j + 1});
            curMax = max(curMax, nv);
        }
        return best;
    }
};
//<<<END LC632
}

// --------------------------------------------------------------------- LC 407
namespace LC407 {
//>>>BEGIN LC407
class Solution {
public:
    int trapRainWater(vector<vector<int>>& h) {
        int R = h.size(), C = h[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        vector<vector<bool>> seen(R, vector<bool>(C, false));
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                if (r == 0 || c == 0 || r == R - 1 || c == C - 1) {   // the outer wall
                    pq.push({h[r][c], r, c});
                    seen[r][c] = true;
                }
        int water = 0;
        int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (!pq.empty()) {
            auto [level, r, c] = pq.top(); pq.pop();   // lowest point of the wall
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= R || nc >= C || seen[nr][nc]) continue;
                seen[nr][nc] = true;
                water += max(0, level - h[nr][nc]);    // fills up to the wall's low point
                pq.push({max(level, h[nr][nc]), nr, nc});   // wall moves inward
            }
        }
        return water;
    }
};
//<<<END LC407
}

// --------------------------------------------------------------------- LC 778
namespace LC778 {
//>>>BEGIN LC778
class Solution {
public:
    int swimInWater(vector<vector<int>>& g) {
        int n = g.size();
        // Dijkstra where a path's cost is its MAXIMUM cell, not its sum
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        vector<vector<bool>> seen(n, vector<bool>(n, false));
        pq.push({g[0][0], 0, 0});
        seen[0][0] = true;
        int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
        while (true) {
            auto [t, r, c] = pq.top(); pq.pop();
            if (r == n - 1 && c == n - 1) return t;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nc < 0 || nr >= n || nc >= n || seen[nr][nc]) continue;
                seen[nr][nc] = true;
                pq.push({max(t, g[nr][nc]), nr, nc});
            }
        }
    }
};
//<<<END LC778
}

// -------------------------------------------------------------------- LC 1675
namespace LC1675 {
//>>>BEGIN LC1675
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        // make every number as LARGE as it can be (odd -> doubled once);
        // from then on the only legal move is halving an even number
        priority_queue<int> pq;
        int mn = INT_MAX;
        for (int x : nums) {
            if (x % 2) x *= 2;
            pq.push(x);
            mn = min(mn, x);
        }
        int best = INT_MAX;
        while (true) {
            int mx = pq.top(); pq.pop();
            best = min(best, mx - mn);
            if (mx % 2) break;              // the max is odd: it can never shrink
            mx /= 2;                         // shrink the max, the only useful move
            mn = min(mn, mx);
            pq.push(mx);
        }
        return best;
    }
};
//<<<END LC1675
}

// --------------------------------------------------------------------- LC 218
namespace LC218 {
//>>>BEGIN LC218
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& b) {   // b sorted by left edge
        vector<vector<int>> res;
        priority_queue<pair<int, int>> live;                    // (height, right edge)
        int i = 0, n = b.size();
        while (i < n || !live.empty()) {
            int x;
            if (live.empty() || (i < n && b[i][0] <= live.top().second)) {
                x = b[i][0];                                    // next event: a left edge
                while (i < n && b[i][0] == x) { live.push({b[i][2], b[i][1]}); i++; }
            } else {
                x = live.top().second;                          // next event: tallest ends
                while (!live.empty() && live.top().second <= x) live.pop();  // lazy delete
            }
            int h = live.empty() ? 0 : live.top().first;
            if (res.empty() || res.back()[1] != h) res.push_back({x, h});
        }
        return res;
    }
};
//<<<END LC218
}

// ============================================================================
//  TESTS
// ============================================================================
static bool validNoAdjacent(const string& orig, const string& got) {
    if (got.size() != orig.size()) return false;
    string a = orig, b = got; sort(a.begin(), a.end()); sort(b.begin(), b.end());
    if (a != b) return false;
    for (size_t i = 1; i < got.size(); i++) if (got[i] == got[i - 1]) return false;
    return true;
}
static bool happy(const string& s, int a, int b, int c) {
    int cnt[3] = {0};
    for (size_t i = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
        if (i >= 2 && s[i] == s[i - 1] && s[i] == s[i - 2]) return false;
    }
    return cnt[0] <= a && cnt[1] <= b && cnt[2] <= c;
}

int main() {
    banner("Tier 1");
    {   LC1046::Solution s;
        vector<int> a{2,7,4,1,8,1}; check("LC1046 a", s.lastStoneWeight(a), 1);
        vector<int> b{1};           check("LC1046 b", s.lastStoneWeight(b), 1);
        vector<int> c{2,2};         check("LC1046 c", s.lastStoneWeight(c), 0);
    }
    {   vector<int> init{4,5,8,2};
        LC703::KthLargest kl(3, init);
        vector<int> got;
        for (int v : {3,5,10,9,4}) got.push_back(kl.add(v));
        check("LC703 a", got, vector<int>{4,5,5,8,8});
        vector<int> e{};
        LC703::KthLargest k2(1, e);
        check("LC703 b", k2.add(-3), -3);
        check("LC703 c", k2.add(-2), -2);
    }
    {   LC215::Solution s;
        vector<int> a{3,2,1,5,6,4};       check("LC215 a", s.findKthLargest(a, 2), 5);
        vector<int> b{3,2,3,1,2,4,5,5,6}; check("LC215 b", s.findKthLargest(b, 4), 4);
        vector<int> c{-1,-1};             check("LC215 c", s.findKthLargest(c, 2), -1);
    }
    {   LC347::Solution s;
        vector<int> a{1,1,1,2,2,3};  check("LC347 a", sorted(s.topKFrequent(a, 2)), vector<int>{1,2});
        vector<int> b{1};            check("LC347 b", s.topKFrequent(b, 1), vector<int>{1});
        vector<int> c{4,4,4,5,5,6,6,6,6}; check("LC347 c", sorted(s.topKFrequent(c, 2)), vector<int>{4,6});
    }
    {   LC973::Solution s;
        vector<vector<int>> a{{1,3},{-2,2}};
        check("LC973 a", s.kClosest(a, 1), vector<vector<int>>{{-2,2}});
        vector<vector<int>> b{{3,3},{5,-1},{-2,4}};
        check("LC973 b", sorted(s.kClosest(b, 2)), vector<vector<int>>{{-2,4},{3,3}});
    }
    {   LC1337::Solution s;
        vector<vector<int>> a{{1,1,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,1,0,0,0},{1,1,1,1,1}};
        check("LC1337 a", s.kWeakestRows(a, 3), vector<int>{2,0,3});
        vector<vector<int>> b{{1,0,0,0},{1,1,1,1},{1,0,0,0},{1,0,0,0}};
        check("LC1337 b", s.kWeakestRows(b, 2), vector<int>{0,2});
    }
    {   LC2558::Solution s;
        vector<int> a{25,64,9,4,100}; check("LC2558 a", s.pickGifts(a, 4), 29LL);
        vector<int> b{1,1,1,1};       check("LC2558 b", s.pickGifts(b, 4), 4LL);
    }
    {   LC506::Solution s;
        vector<int> a{5,4,3,2,1};
        check("LC506 a", s.findRelativeRanks(a),
              vector<string>{"Gold Medal","Silver Medal","Bronze Medal","4","5"});
        vector<int> b{10,3,8,9,4};
        check("LC506 b", s.findRelativeRanks(b),
              vector<string>{"Gold Medal","5","Bronze Medal","Silver Medal","4"});
    }
    {   LC451::Solution s;
        check("LC451 a", s.frequencySort("aaabbc"), string("aaabbc"));
        check("LC451 b", s.frequencySort("bcbaaa"), string("aaabbc"));
        string t = s.frequencySort("tree");
        check("LC451 c", t == "eetr" || t == "eert", true);
    }
    {   LC692::Solution s;
        vector<string> a{"i","love","leetcode","i","love","coding"};
        check("LC692 a", s.topKFrequent(a, 2), vector<string>{"i","love"});
        vector<string> b{"the","day","is","sunny","the","the","the","sunny","is","is"};
        check("LC692 b", s.topKFrequent(b, 4), vector<string>{"the","is","sunny","day"});
        vector<string> c{"b","a","c"};
        check("LC692 c", s.topKFrequent(c, 2), vector<string>{"a","b"});   // tie -> alphabetical
    }
    {   LC23::Solution s;
        vector<ListNode*> a{makeList({1,4,5}), makeList({1,3,4}), makeList({2,6})};
        check("LC23 a", toVec(s.mergeKLists(a)), vector<int>{1,1,2,3,4,4,5,6});
        vector<ListNode*> b{};
        check("LC23 b", toVec(s.mergeKLists(b)), vector<int>{});
        vector<ListNode*> c{nullptr};
        check("LC23 c", toVec(s.mergeKLists(c)), vector<int>{});
    }
    {   LC378::Solution s;
        vector<vector<int>> a{{1,5,9},{10,11,13},{12,13,15}};
        check("LC378 a", s.kthSmallest(a, 8), 13);
        check("LC378 b", s.kthSmallest(a, 1), 1);
        check("LC378 c", s.kthSmallest(a, 9), 15);
        vector<vector<int>> b{{-5}};
        check("LC378 d", s.kthSmallest(b, 1), -5);
    }
    {   LC1962::Solution s;
        vector<int> a{5,4,9};   check("LC1962 a", s.minStoneSum(a, 2), 12);
        vector<int> b{4,3,6,7}; check("LC1962 b", s.minStoneSum(b, 3), 12);
    }

    banner("Tier 2");
    {   LC295::MedianFinder m;
        m.addNum(1); m.addNum(2);
        check("LC295 a", m.findMedian(), 1.5);
        m.addNum(3);
        check("LC295 b", m.findMedian(), 2.0);
        LC295::MedianFinder m2;
        for (int x : {5, 15, 1, 3}) m2.addNum(x);
        check("LC295 c", m2.findMedian(), 4.0);
        m2.addNum(-10);
        check("LC295 d", m2.findMedian(), 3.0);
    }
    {   LC621::Solution s;
        vector<char> a{'A','A','A','B','B','B'};
        check("LC621 a", s.leastInterval(a, 2), 8);
        check("LC621 b", s.leastInterval(a, 0), 6);
        vector<char> c{'A','A','A','A','A','A','B','C','D','E','F','G'};
        check("LC621 c", s.leastInterval(c, 2), 16);
        vector<char> d{'A','C','A','B','D','B'};
        check("LC621 d", s.leastInterval(d, 1), 6);
    }
    {   LC767::Solution s;
        check("LC767 a", validNoAdjacent("aab", s.reorganizeString("aab")), true);
        check("LC767 b", s.reorganizeString("aaab"), string(""));
        check("LC767 c", validNoAdjacent("vvvlo", s.reorganizeString("vvvlo")), true);
        check("LC767 d", validNoAdjacent("a", s.reorganizeString("a")), true);
    }
    {   LC1642::Solution s;
        vector<int> a{4,2,7,6,9,14,12};        check("LC1642 a", s.furthestBuilding(a, 5, 1), 4);
        vector<int> b{4,12,2,7,3,18,20,3,19};  check("LC1642 b", s.furthestBuilding(b, 10, 2), 7);
        vector<int> c{14,3,19,3};              check("LC1642 c", s.furthestBuilding(c, 17, 0), 3);
    }
    {   LC1834::Solution s;
        vector<vector<int>> a{{1,2},{2,4},{3,2},{4,1}};
        check("LC1834 a", s.getOrder(a), vector<int>{0,2,3,1});
        vector<vector<int>> b{{7,10},{7,12},{7,5},{7,4},{7,2}};
        check("LC1834 b", s.getOrder(b), vector<int>{4,3,2,0,1});
    }
    {   LC373::Solution s;
        vector<int> a{1,7,11}, b{2,4,6};
        check("LC373 a", s.kSmallestPairs(a, b, 3), vector<vector<int>>{{1,2},{1,4},{1,6}});
        vector<int> c{1,1,2}, d{1,2,3};
        check("LC373 b", s.kSmallestPairs(c, d, 2), vector<vector<int>>{{1,1},{1,1}});
    }
    {   LC355::Twitter t;
        t.postTweet(1, 5);
        check("LC355 a", t.getNewsFeed(1), vector<int>{5});
        t.follow(1, 2);
        t.postTweet(2, 6);
        check("LC355 b", t.getNewsFeed(1), vector<int>{6,5});
        t.unfollow(1, 2);
        check("LC355 c", t.getNewsFeed(1), vector<int>{5});
        LC355::Twitter u;
        for (int i = 1; i <= 11; i++) u.postTweet(1, i);
        check("LC355 d", u.getNewsFeed(1), vector<int>{11,10,9,8,7,6,5,4,3,2});
    }
    {   LC264::Solution s;
        check("LC264 a", s.nthUglyNumber(10), 12);
        check("LC264 b", s.nthUglyNumber(1), 1);
        check("LC264 c", s.nthUglyNumber(1690), 2123366400);
    }
    {   LC658::Solution s;
        vector<int> a{1,2,3,4,5};
        check("LC658 a", s.findClosestElements(a, 4, 3),  vector<int>{1,2,3,4});
        check("LC658 b", s.findClosestElements(a, 4, -1), vector<int>{1,2,3,4});
        vector<int> b{1,1,2,3,4,5};
        check("LC658 c", s.findClosestElements(b, 4, -1), vector<int>{1,1,2,3});
        vector<int> c{1,3};
        check("LC658 d", s.findClosestElements(c, 1, 2), vector<int>{1});   // tie -> smaller
    }
    {   LC846::Solution s;
        vector<int> a{1,2,3,6,2,3,4,7,8}; check("LC846 a", s.isNStraightHand(a, 3), true);
        vector<int> b{1,2,3,4,5};         check("LC846 b", s.isNStraightHand(b, 4), false);
        vector<int> c{1,1,2,2,3,3};       check("LC846 c", s.isNStraightHand(c, 3), true);
        vector<int> d{1,2,2,3,3,4};       check("LC846 d", s.isNStraightHand(d, 3), true);
        vector<int> e{1,1,2,3,3,4};       check("LC846 e", s.isNStraightHand(e, 3), false);
    }
    {   LC743::Solution s;
        vector<vector<int>> a{{2,1,1},{2,3,1},{3,4,1}};
        check("LC743 a", s.networkDelayTime(a, 4, 2), 2);
        vector<vector<int>> b{{1,2,1}};
        check("LC743 b", s.networkDelayTime(b, 2, 1), 1);
        check("LC743 c", s.networkDelayTime(b, 2, 2), -1);
        vector<vector<int>> c{{1,2,4},{1,3,1},{3,2,1}};
        check("LC743 d", s.networkDelayTime(c, 3, 1), 2);   // the indirect route is shorter
    }
    {   LC1353::Solution s;
        vector<vector<int>> a{{1,2},{2,3},{3,4}};          check("LC1353 a", s.maxEvents(a), 3);
        vector<vector<int>> b{{1,2},{2,3},{3,4},{1,2}};    check("LC1353 b", s.maxEvents(b), 4);
        vector<vector<int>> c{{1,4},{4,4},{2,2},{3,4},{1,1}}; check("LC1353 c", s.maxEvents(c), 4);
        vector<vector<int>> d{{1,1},{1,1},{1,1}};          check("LC1353 d", s.maxEvents(d), 1);
    }
    {   LC1405::Solution s;
        string a = s.longestDiverseString(1, 1, 7);
        check("LC1405 a len", (int)a.size(), 8);   check("LC1405 a ok", happy(a, 1, 1, 7), true);
        string b = s.longestDiverseString(7, 1, 0);
        check("LC1405 b len", (int)b.size(), 5);   check("LC1405 b ok", happy(b, 7, 1, 0), true);
        string c = s.longestDiverseString(2, 2, 1);
        check("LC1405 c len", (int)c.size(), 5);   check("LC1405 c ok", happy(c, 2, 2, 1), true);
    }
    {   LC871::Solution s;
        vector<vector<int>> a{};
        check("LC871 a", s.minRefuelStops(1, 1, a), 0);
        vector<vector<int>> b{{10,100}};
        check("LC871 b", s.minRefuelStops(100, 1, b), -1);
        vector<vector<int>> c{{10,60},{20,30},{30,30},{60,40}};
        check("LC871 c", s.minRefuelStops(100, 10, c), 2);
    }
    {   LC1882::Solution s;
        vector<int> sv{3,3,2}, tk{1,2,3,2,1,2};
        check("LC1882 a", s.assignTasks(sv, tk), vector<int>{2,2,0,2,1,2});
        vector<int> sv2{5,1,4,3,2}, tk2{2,1,2,4,5,2,1};
        check("LC1882 b", s.assignTasks(sv2, tk2), vector<int>{1,4,1,4,1,3,2});
    }

    banner("Tier 3");
    {   LC480::Solution s;
        vector<int> a{1,3,-1,-3,5,3,6,7};
        check("LC480 a", s.medianSlidingWindow(a, 3), vector<double>{1,-1,-1,3,5,6});
        LC480::Solution t;
        vector<int> b{1,2,3,4,2,3,1,4,2};
        check("LC480 b", t.medianSlidingWindow(b, 3), vector<double>{2,3,3,3,2,3,2});
        LC480::Solution u;
        vector<int> c{2147483647,2147483647};
        check("LC480 c", u.medianSlidingWindow(c, 2), vector<double>{2147483647.0});
        LC480::Solution v;
        vector<int> d{5,5,5,5,1,1};
        check("LC480 d", v.medianSlidingWindow(d, 2), vector<double>{5,5,5,3,1});
    }
    {   LC502::Solution s;
        vector<int> p{1,2,3}, c{0,1,1};  check("LC502 a", s.findMaximizedCapital(2, 0, p, c), 4);
        vector<int> c2{0,1,2};           check("LC502 b", s.findMaximizedCapital(3, 0, p, c2), 6);
        vector<int> c3{1,1,1};           check("LC502 c", s.findMaximizedCapital(2, 0, p, c3), 0);
    }
    {   LC630::Solution s;
        vector<vector<int>> a{{100,200},{200,1300},{1000,1250},{2000,3200}};
        check("LC630 a", s.scheduleCourse(a), 3);
        vector<vector<int>> b{{1,2}};          check("LC630 b", s.scheduleCourse(b), 1);
        vector<vector<int>> c{{3,2},{4,3}};    check("LC630 c", s.scheduleCourse(c), 0);
    }
    {   LC857::Solution s;
        vector<int> q{10,20,5}, w{70,50,30};
        check("LC857 a", s.mincostToHireWorkers(q, w, 2), 105.0);
        vector<int> q2{3,1,10,10,1}, w2{4,8,2,2,7};
        check("LC857 b", s.mincostToHireWorkers(q2, w2, 3), 30.66667);
    }
    {   LC1383::Solution s;
        vector<int> sp{2,10,3,1,5,8}, ef{5,4,3,9,7,2};
        check("LC1383 a", s.maxPerformance(6, sp, ef, 2), 60);
        check("LC1383 b", s.maxPerformance(6, sp, ef, 3), 68);
        check("LC1383 c", s.maxPerformance(6, sp, ef, 4), 72);
    }
    {   LC632::Solution s;
        vector<vector<int>> a{{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
        check("LC632 a", s.smallestRange(a), vector<int>{20,24});
        vector<vector<int>> b{{1,2,3},{1,2,3},{1,2,3}};
        check("LC632 b", s.smallestRange(b), vector<int>{1,1});
    }
    {   LC407::Solution s;
        vector<vector<int>> a{{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
        check("LC407 a", s.trapRainWater(a), 4);
        vector<vector<int>> b{{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}};
        check("LC407 b", s.trapRainWater(b), 10);
    }
    {   LC778::Solution s;
        vector<vector<int>> a{{0,2},{1,3}};
        check("LC778 a", s.swimInWater(a), 3);
        vector<vector<int>> b{{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}};
        check("LC778 b", s.swimInWater(b), 16);
    }
    {   LC1675::Solution s;
        vector<int> a{1,2,3,4};    check("LC1675 a", s.minimumDeviation(a), 1);
        vector<int> b{4,1,5,20,3}; check("LC1675 b", s.minimumDeviation(b), 3);
        vector<int> c{2,10,8};     check("LC1675 c", s.minimumDeviation(c), 3);
    }
    {   LC218::Solution s;
        vector<vector<int>> a{{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
        check("LC218 a", s.getSkyline(a),
              vector<vector<int>>{{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}});
        vector<vector<int>> b{{0,2,3},{2,5,3}};
        check("LC218 b", s.getSkyline(b), vector<vector<int>>{{0,3},{5,0}});
    }

    cout << "\n----------------------------------------\n";
    cout << g_pass << " passed, " << g_fail << " failed\n";
    return g_fail == 0 ? 0 : 1;
}
