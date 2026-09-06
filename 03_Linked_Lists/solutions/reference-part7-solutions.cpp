// Verified solutions for all 33 problems in Part 7 of the linked list guide.
// Code between //>>>BEGIN X and //<<<END X markers is extracted into the PDF.
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// ---------- test helpers (not part of any solution) ----------
ListNode* build(vector<int> v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
string dump(ListNode* h) {
    string s; while (h) { s += to_string(h->val); if (h->next) s += "->"; h = h->next; }
    return s.empty() ? "(empty)" : s;
}
int FAILS = 0, OKS = 0;
void check(string name, string got, string want) {
    if (got != want) { FAILS++; cout << "FAIL " << name << "  got=" << got << "  want=" << want << "\n"; }
    else { OKS++; cout << "ok   " << name << "\n"; }
}

// ============================================================================
// TIER 1
// ============================================================================

//>>>BEGIN LC707
class MyLinkedList {
    struct Node {
        int val;
        Node* next;
        Node(int v) : val(v), next(nullptr) {}
    };
    Node* head;
    int size;
public:
    MyLinkedList() : head(nullptr), size(0) {}

    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* c = head;
        for (int i = 0; i < index; i++) c = c->next;
        return c->val;
    }

    void addAtHead(int val) {
        Node* n = new Node(val);
        n->next = head;
        head = n;
        size++;
    }

    void addAtTail(int val) {
        Node* n = new Node(val);
        if (!head) head = n;
        else {
            Node* c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        size++;
    }

    void addAtIndex(int index, int val) {
        if (index > size) return;              // index == size means append
        if (index <= 0) { addAtHead(val); return; }
        Node* c = head;
        for (int i = 0; i < index - 1; i++) c = c->next;   // stop BEFORE index
        Node* n = new Node(val);
        n->next = c->next;
        c->next = n;
        size++;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        if (index == 0) {
            Node* d = head; head = head->next; delete d; size--;
            return;
        }
        Node* c = head;
        for (int i = 0; i < index - 1; i++) c = c->next;
        Node* d = c->next;
        c->next = d->next;
        delete d;
        size--;
    }
};
//<<<END LC707

//>>>BEGIN LC876
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {      // order matters: && short-circuits
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;                      // second middle when length is even
}
//<<<END LC876

//>>>BEGIN LC206
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* nxt = head->next;   // 1. SAVE the rest
        head->next = prev;            // 2. flip this arrow
        prev = head;                  // 3. prev moves up
        head = nxt;                   // 4. curr moves up
    }
    return prev;                      // prev is the new head
}
//<<<END LC206

//>>>BEGIN LC203
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0);
    dummy.next = head;                // dummy => the head is not a special case
    ListNode* curr = &dummy;
    while (curr->next) {
        if (curr->next->val == val) curr->next = curr->next->next;  // do NOT advance
        else                        curr = curr->next;
    }
    return dummy.next;
}
//<<<END LC203

//>>>BEGIN LC83
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* curr = head;
    while (curr && curr->next) {
        if (curr->val == curr->next->val) curr->next = curr->next->next;
        else                              curr = curr->next;
    }
    return head;                      // head can never be deleted -> no dummy needed
}
//<<<END LC83

//>>>BEGIN LC21
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else                  { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;           // attach the non-empty remainder
    return dummy.next;
}
//<<<END LC21

//>>>BEGIN LC141
bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;   // compare ADDRESSES, not values
    }
    return false;                        // fast fell off => no cycle
}
//<<<END LC141

//>>>BEGIN LC160
ListNode* getIntersectionNode(ListNode* a, ListNode* b) {
    if (!a || !b) return nullptr;
    ListNode *p = a, *q = b;
    while (p != q) {
        p = p ? p->next : b;      // when p runs out, restart it on list b
        q = q ? q->next : a;      // when q runs out, restart it on list a
    }
    return p;                     // junction, or nullptr if they never meet
}
//<<<END LC160

//>>>BEGIN LC234
ListNode* reverseFor234(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) { ListNode* n = head->next; head->next = prev; prev = head; head = n; }
    return prev;
}

bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    ListNode *slow = head, *fast = head->next;      // first middle
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }

    ListNode* second = reverseFor234(slow->next);   // reverse the back half
    slow->next = nullptr;

    ListNode *p = head, *q = second;
    bool ok = true;
    while (p && q) {
        if (p->val != q->val) { ok = false; break; }
        p = p->next; q = q->next;
    }
    slow->next = reverseFor234(second);             // restore the input list
    return ok;
}
//<<<END LC234

//>>>BEGIN LC237
void deleteNode(ListNode* node) {
    node->val  = node->next->val;     // copy the successor's value into me
    node->next = node->next->next;    // then unlink the successor
}
//<<<END LC237

// ============================================================================
// TIER 2
// ============================================================================

//>>>BEGIN LC19
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode *slow = &dummy, *fast = &dummy;
    for (int i = 0; i < n; i++) fast = fast->next;      // open a gap of n
    while (fast->next) { slow = slow->next; fast = fast->next; }
    slow->next = slow->next->next;                      // slow sits BEFORE the target
    return dummy.next;
}
//<<<END LC19

//>>>BEGIN LC2
ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    int carry = 0;
    while (a || b || carry) {          // "|| carry" handles 999 + 1
        int sum = carry;
        if (a) { sum += a->val; a = a->next; }
        if (b) { sum += b->val; b = b->next; }
        carry = sum / 10;
        tail->next = new ListNode(sum % 10);
        tail = tail->next;
    }
    return dummy.next;
}
//<<<END LC2

//>>>BEGIN LC142
ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                 // phase 1: they meet inside the loop
            ListNode* p = head;             // phase 2: walk both one step at a time
            while (p != slow) { p = p->next; slow = slow->next; }
            return p;                       // meeting point == loop entrance
        }
    }
    return nullptr;
}
//<<<END LC142

//>>>BEGIN LC92
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    for (int i = 1; i < left; i++) prev = prev->next;   // node just before segment

    ListNode* curr = prev->next;
    for (int i = 0; i < right - left; i++) {   // head-insertion, right-left times
        ListNode* nxt = curr->next;
        curr->next = nxt->next;
        nxt->next  = prev->next;
        prev->next = nxt;
    }
    return dummy.next;
}
//<<<END LC92

//>>>BEGIN LC82
ListNode* deleteAllDuplicates(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    ListNode* curr = head;
    while (curr) {
        if (curr->next && curr->val == curr->next->val) {
            int dup = curr->val;
            while (curr && curr->val == dup) curr = curr->next;   // skip the whole run
            prev->next = curr;                                    // prev does NOT move
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return dummy.next;
}
//<<<END LC82

//>>>BEGIN LC24
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    while (prev->next && prev->next->next) {
        ListNode* a = prev->next;
        ListNode* b = a->next;
        a->next    = b->next;    // a jumps over b
        b->next    = a;          // b points back at a
        prev->next = b;          // prev adopts b
        prev = a;                // a is now the tail of the done part
    }
    return dummy.next;
}
//<<<END LC24

//>>>BEGIN LC61
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;

    int n = 1;
    ListNode* tail = head;
    while (tail->next) { tail = tail->next; n++; }

    k %= n;                          // k can be far larger than the length
    if (k == 0) return head;

    tail->next = head;               // close the ring
    ListNode* newTail = head;
    for (int i = 0; i < n - k - 1; i++) newTail = newTail->next;
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;         // reopen the ring
    return newHead;
}
//<<<END LC61

//>>>BEGIN LC86
ListNode* partitionList(ListNode* head, int x) {
    ListNode lessDummy(0), geDummy(0);           // two output lists
    ListNode *less = &lessDummy, *ge = &geDummy;
    while (head) {
        if (head->val < x) { less->next = head; less = less->next; }
        else               { ge->next   = head; ge   = ge->next;   }
        head = head->next;
    }
    ge->next   = nullptr;             // ESSENTIAL: without this you build a cycle
    less->next = geDummy.next;
    return lessDummy.next;
}
//<<<END LC86

//>>>BEGIN LC328
ListNode* oddEvenList(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* odd  = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;              // remember where the evens start
    while (even && even->next) {
        odd->next  = even->next;  odd  = odd->next;
        even->next = odd->next;   even = even->next;
    }
    odd->next = evenHead;                   // stitch evens onto the odds
    return head;
}
//<<<END LC328

//>>>BEGIN LC143
void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    ListNode *slow = head, *fast = head->next;          // 1. find the first middle
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    ListNode* second = slow->next;
    slow->next = nullptr;                               // cut

    ListNode* prev = nullptr;                           // 2. reverse the back half
    while (second) {
        ListNode* nxt = second->next;
        second->next = prev;
        prev = second;
        second = nxt;
    }

    ListNode* first = head;                             // 3. weave the halves
    while (prev) {
        ListNode* n1 = first->next;
        ListNode* n2 = prev->next;
        first->next = prev;
        prev->next  = n1;
        first = n1;
        prev  = n2;
    }
}
//<<<END LC143

//>>>BEGIN LC148
ListNode* mergeForSort(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else                  { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;

    // split at the FIRST middle (fast starts one ahead) so both halves are non-empty
    ListNode *slow = head, *fast = head->next;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    ListNode* second = slow->next;
    slow->next = nullptr;                       // cut

    return mergeForSort(sortList(head), sortList(second));
}
//<<<END LC148

//>>>BEGIN LC138
class RandomNode {
public:
    int val;
    RandomNode* next;
    RandomNode* random;
    RandomNode(int v) : val(v), next(nullptr), random(nullptr) {}
};

// O(1) extra space: interleave copies, wire randoms, then unweave.
RandomNode* copyRandomList(RandomNode* head) {
    if (!head) return nullptr;

    // 1. A -> A' -> B -> B' -> ...
    for (RandomNode* c = head; c; c = c->next->next) {
        RandomNode* copy = new RandomNode(c->val);
        copy->next = c->next;
        c->next = copy;
    }
    // 2. the copy of X is always X->next
    for (RandomNode* c = head; c; c = c->next->next)
        if (c->random) c->next->random = c->random->next;

    // 3. separate the two interleaved lists
    RandomNode* newHead = head->next;
    for (RandomNode* c = head; c; c = c->next) {
        RandomNode* copy = c->next;
        c->next = copy->next;
        if (copy->next) copy->next = copy->next->next;
    }
    return newHead;
}
//<<<END LC138

//>>>BEGIN LC146
class LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };
    int cap;
    unordered_map<int, Node*> mp;
    Node *head, *tail;                 // head side = most recent, tail side = least

    void remove(Node* n) {             // sentinels mean no null checks are needed
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void insertFront(Node* n) {
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }
public:
    LRUCache(int capacity) : cap(capacity) {
        head = new Node(0, 0);         // dummy head and dummy tail
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!mp.count(key)) return -1;
        Node* n = mp[key];
        remove(n);
        insertFront(n);                // touching it makes it most recent
        return n->val;
    }

    void put(int key, int value) {
        if (mp.count(key)) {
            Node* n = mp[key];
            n->val = value;
            remove(n);
            insertFront(n);
            return;
        }
        if ((int)mp.size() == cap) {   // evict from the tail side
            Node* lru = tail->prev;
            remove(lru);
            mp.erase(lru->key);
            delete lru;
        }
        Node* n = new Node(key, value);
        mp[key] = n;
        insertFront(n);
    }
};
//<<<END LC146

// ============================================================================
// TIER 3
// ============================================================================

//>>>BEGIN LC25
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* node = head;
    for (int i = 0; i < k; i++) {        // are there k nodes left?
        if (!node) return head;          // fewer than k -> leave them as they are
        node = node->next;
    }
    // node points just past this group
    ListNode* prev = reverseKGroup(node, k);   // solve the rest first
    ListNode* curr = head;
    for (int i = 0; i < k; i++) {              // reverse this group onto prev
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}
//<<<END LC25

//>>>BEGIN LC23
ListNode* mergeTwoForK(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a && b) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else                  { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

// Pairwise merging: k -> k/2 -> k/4 -> 1.  O(N log k) time, O(1) extra space.
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int n = lists.size();
    while (n > 1) {
        int half = (n + 1) / 2;
        for (int i = 0; i < n / 2; i++)
            lists[i] = mergeTwoForK(lists[i], lists[i + half]);
        n = half;
    }
    return lists[0];
}
//<<<END LC23

//>>>BEGIN LC445
// Digits stored MOST significant first, and we may not reverse the input.
// Stacks give us reverse access; building by prepending gives the right order.
ListNode* addTwoNumbersII(ListNode* a, ListNode* b) {
    stack<int> sa, sb;
    for (; a; a = a->next) sa.push(a->val);
    for (; b; b = b->next) sb.push(b->val);

    ListNode* head = nullptr;
    int carry = 0;
    while (!sa.empty() || !sb.empty() || carry) {
        int sum = carry;
        if (!sa.empty()) { sum += sa.top(); sa.pop(); }
        if (!sb.empty()) { sum += sb.top(); sb.pop(); }
        carry = sum / 10;
        head = new ListNode(sum % 10, head);   // prepend
    }
    return head;
}
//<<<END LC445

//>>>BEGIN LC430
class MultiNode {
public:
    int val;
    MultiNode *prev, *next, *child;
    MultiNode(int v) : val(v), prev(nullptr), next(nullptr), child(nullptr) {}
};

MultiNode* flatten(MultiNode* head) {
    for (MultiNode* curr = head; curr; curr = curr->next) {
        if (!curr->child) continue;

        MultiNode* nxt   = curr->next;      // remember what came after
        MultiNode* child = curr->child;

        curr->child = nullptr;              // splice the child chain in
        curr->next  = child;
        child->prev = curr;

        MultiNode* tail = child;            // walk to the end of the child chain
        while (tail->next) tail = tail->next;

        tail->next = nxt;                   // reattach the remainder
        if (nxt) nxt->prev = tail;
        // the loop continues INTO the child chain, so nested children are handled
    }
    return head;
}
//<<<END LC430

//>>>BEGIN LC147
ListNode* insertionSortList(ListNode* head) {
    ListNode dummy(0);                       // sorted part hangs off the dummy
    while (head) {
        ListNode* nxt = head->next;          // save before we relink head

        ListNode* p = &dummy;                // find the insertion point
        while (p->next && p->next->val < head->val) p = p->next;

        head->next = p->next;                // splice head in after p
        p->next = head;

        head = nxt;
    }
    return dummy.next;
}
//<<<END LC147

//>>>BEGIN LC1721
ListNode* swapNodes(ListNode* head, int k) {
    ListNode* first = head;
    for (int i = 1; i < k; i++) first = first->next;   // k-th from the start

    ListNode* second = head;                            // k-th from the end
    for (ListNode* p = first; p->next; p = p->next) second = second->next;

    swap(first->val, second->val);   // swapping values is allowed here
    return head;
}
//<<<END LC1721

//>>>BEGIN LC109
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// The middle of a sorted list is the root of a height-balanced BST.
TreeNode* sortedListToBST(ListNode* head) {
    if (!head) return nullptr;
    if (!head->next) return new TreeNode(head->val);

    ListNode *slow = head, *fast = head, *prev = nullptr;
    while (fast && fast->next) {          // prev tracks the node before slow
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = nullptr;                 // cut the left half free

    TreeNode* root = new TreeNode(slow->val);
    root->left  = sortedListToBST(head);
    root->right = sortedListToBST(slow->next);
    return root;
}
//<<<END LC109

//>>>BEGIN LC725
// n nodes into k parts: the first (n % k) parts get one extra node.
vector<ListNode*> splitListToParts(ListNode* head, int k) {
    int n = 0;
    for (ListNode* c = head; c; c = c->next) n++;

    int size = n / k, extra = n % k;
    vector<ListNode*> res(k, nullptr);

    ListNode* curr = head;
    for (int i = 0; i < k && curr; i++) {
        res[i] = curr;
        int len = size + (i < extra ? 1 : 0);
        for (int j = 1; j < len; j++) curr = curr->next;   // walk to this part's tail
        ListNode* nxt = curr->next;
        curr->next = nullptr;                              // cut
        curr = nxt;
    }
    return res;
}
//<<<END LC725

//>>>BEGIN LC622
// A ring buffer. Storing head + count (instead of head + tail) avoids the
// classic "is it full or empty?" ambiguity entirely.
class MyCircularQueue {
    vector<int> q;
    int head, count, cap;
public:
    MyCircularQueue(int k) : q(k), head(0), count(0), cap(k) {}

    bool enQueue(int value) {
        if (isFull()) return false;
        q[(head + count) % cap] = value;
        count++;
        return true;
    }
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % cap;
        count--;
        return true;
    }
    int Front()   { return isEmpty() ? -1 : q[head]; }
    int Rear()    { return isEmpty() ? -1 : q[(head + count - 1) % cap]; }
    bool isEmpty(){ return count == 0; }
    bool isFull() { return count == cap; }
};
//<<<END LC622

//>>>BEGIN LC460
// Evict the least-frequently-used; ties broken by least-recently-used.
// Three maps give O(1): key->{value,freq}, freq->list of keys (MRU at front),
// key->iterator into that list so erasing is O(1).
class LFUCache {
    int cap, minFreq;
    unordered_map<int, pair<int,int>> kv;               // key -> {value, freq}
    unordered_map<int, list<int>> freqList;             // freq -> keys, MRU first
    unordered_map<int, list<int>::iterator> pos;        // key  -> its iterator

    void touch(int key) {                 // bump a key's frequency by one
        int f = kv[key].second;
        freqList[f].erase(pos[key]);
        if (freqList[f].empty()) {
            freqList.erase(f);
            if (minFreq == f) minFreq++;  // that bucket is gone, min shifts up
        }
        int nf = f + 1;
        kv[key].second = nf;
        freqList[nf].push_front(key);
        pos[key] = freqList[nf].begin();
    }
public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key) {
        if (cap <= 0 || !kv.count(key)) return -1;
        touch(key);
        return kv[key].first;
    }

    void put(int key, int value) {
        if (cap <= 0) return;
        if (kv.count(key)) { kv[key].first = value; touch(key); return; }

        if ((int)kv.size() == cap) {              // evict LFU, then LRU within it
            int evict = freqList[minFreq].back(); // back = least recently used
            freqList[minFreq].pop_back();
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
            kv.erase(evict);
            pos.erase(evict);
        }
        kv[key] = {value, 1};
        freqList[1].push_front(key);
        pos[key] = freqList[1].begin();
        minFreq = 1;                              // the new key has frequency 1
    }
};
//<<<END LC460

// ============================================================================
// TESTS
// ============================================================================
string treeInorder(TreeNode* r) {
    if (!r) return "";
    string l = treeInorder(r->left), rr = treeInorder(r->right);
    string s = to_string(r->val);
    return (l.empty() ? "" : l + ",") + s + (rr.empty() ? "" : "," + rr);
}
int treeHeight(TreeNode* r) { return r ? 1 + max(treeHeight(r->left), treeHeight(r->right)) : 0; }
bool balanced(TreeNode* r) {
    if (!r) return true;
    return abs(treeHeight(r->left) - treeHeight(r->right)) <= 1 && balanced(r->left) && balanced(r->right);
}
string dumpMulti(MultiNode* h) {
    string s;
    while (h) { s += to_string(h->val); if (h->next) s += "->"; h = h->next; }
    return s;
}
bool multiPrevOk(MultiNode* h) {
    MultiNode* prev = nullptr;
    while (h) { if (h->prev != prev || h->child) return false; prev = h; h = h->next; }
    return true;
}

int main() {
    cout << "===== TIER 1 =====\n";
    { MyLinkedList l;
      l.addAtHead(1); l.addAtTail(3); l.addAtIndex(1, 2);
      string r = to_string(l.get(1));           // 2
      l.deleteAtIndex(1);
      r += "," + to_string(l.get(1));           // 3
      r += "," + to_string(l.get(5));           // -1
      l.addAtIndex(0, 9);
      r += "," + to_string(l.get(0));           // 9
      check("LC707", r, "2,3,-1,9"); }

    check("LC876-odd",  to_string(middleNode(build({1,2,3,4,5}))->val), "3");
    check("LC876-even", to_string(middleNode(build({1,2,3,4,5,6}))->val), "4");
    check("LC876-one",  to_string(middleNode(build({1}))->val), "1");

    check("LC206",       dump(reverseList(build({1,2,3,4,5}))), "5->4->3->2->1");
    check("LC206-empty", dump(reverseList(nullptr)), "(empty)");
    check("LC206-one",   dump(reverseList(build({1}))), "1");

    check("LC203",      dump(removeElements(build({1,2,6,3,4,5,6}), 6)), "1->2->3->4->5");
    check("LC203-all",  dump(removeElements(build({7,7,7}), 7)), "(empty)");
    check("LC203-head", dump(removeElements(build({6,1,2}), 6)), "1->2");

    check("LC83",     dump(deleteDuplicates(build({1,1,2,3,3}))), "1->2->3");
    check("LC83-all", dump(deleteDuplicates(build({1,1,1}))), "1");

    check("LC21",       dump(mergeTwoLists(build({1,2,4}), build({1,3,4}))), "1->1->2->3->4->4");
    check("LC21-empty", dump(mergeTwoLists(nullptr, nullptr)), "(empty)");
    check("LC21-one",   dump(mergeTwoLists(nullptr, build({0}))), "0");

    { ListNode* l = build({3,2,0,-4}); l->next->next->next->next = l->next;
      check("LC141-yes", hasCycle(l) ? "1" : "0", "1"); }
    check("LC141-no",  hasCycle(build({1,2})) ? "1" : "0", "0");
    check("LC141-nil", hasCycle(nullptr) ? "1" : "0", "0");

    { ListNode* common = build({8,4,5});
      ListNode* a = build({4,1}); ListNode* t = a; while (t->next) t = t->next; t->next = common;
      ListNode* b = build({5,6,1}); t = b; while (t->next) t = t->next; t->next = common;
      check("LC160", to_string(getIntersectionNode(a,b)->val), "8"); }
    check("LC160-none", getIntersectionNode(build({1,2}), build({3,4})) == nullptr ? "null" : "x", "null");

    check("LC234-even", isPalindrome(build({1,2,2,1})) ? "1" : "0", "1");
    check("LC234-odd",  isPalindrome(build({1,2,3,2,1})) ? "1" : "0", "1");
    check("LC234-no",   isPalindrome(build({1,2})) ? "1" : "0", "0");
    check("LC234-one",  isPalindrome(build({1})) ? "1" : "0", "1");

    { ListNode* l = build({4,5,1,9}); deleteNode(l->next); check("LC237", dump(l), "4->1->9"); }

    cout << "===== TIER 2 =====\n";
    check("LC19",        dump(removeNthFromEnd(build({1,2,3,4,5}), 2)), "1->2->3->5");
    check("LC19-head",   dump(removeNthFromEnd(build({1,2}), 2)), "2");
    check("LC19-single", dump(removeNthFromEnd(build({1}), 1)), "(empty)");

    check("LC2",       dump(addTwoNumbers(build({2,4,3}), build({5,6,4}))), "7->0->8");
    check("LC2-carry", dump(addTwoNumbers(build({9,9,9}), build({1}))), "0->0->0->1");
    check("LC2-zero",  dump(addTwoNumbers(build({0}), build({0}))), "0");

    { ListNode* l = build({3,2,0,-4}); l->next->next->next->next = l->next;
      check("LC142", to_string(detectCycle(l)->val), "2"); }
    check("LC142-none", detectCycle(build({1,2})) == nullptr ? "null" : "x", "null");

    check("LC92",      dump(reverseBetween(build({1,2,3,4,5}), 2, 4)), "1->4->3->2->5");
    check("LC92-full", dump(reverseBetween(build({1,2,3,4,5}), 1, 5)), "5->4->3->2->1");
    check("LC92-same", dump(reverseBetween(build({5}), 1, 1)), "5");

    check("LC82",      dump(deleteAllDuplicates(build({1,2,3,3,4,4,5}))), "1->2->5");
    check("LC82-head", dump(deleteAllDuplicates(build({1,1,1,2,3}))), "2->3");
    check("LC82-all",  dump(deleteAllDuplicates(build({1,1,2,2}))), "(empty)");

    check("LC24",     dump(swapPairs(build({1,2,3,4}))), "2->1->4->3");
    check("LC24-odd", dump(swapPairs(build({1,2,3}))), "2->1->3");
    check("LC24-one", dump(swapPairs(build({1}))), "1");

    check("LC61",       dump(rotateRight(build({1,2,3,4,5}), 2)), "4->5->1->2->3");
    check("LC61-big-k", dump(rotateRight(build({0,1,2}), 4)), "2->0->1");
    check("LC61-k0",    dump(rotateRight(build({1,2}), 0)), "1->2");

    check("LC86",      dump(partitionList(build({1,4,3,2,5,2}), 3)), "1->2->2->4->3->5");
    check("LC86-none", dump(partitionList(build({2,1}), 2)), "1->2");

    check("LC328",      dump(oddEvenList(build({1,2,3,4,5}))), "1->3->5->2->4");
    check("LC328-even", dump(oddEvenList(build({2,1,3,5,6,4,7}))), "2->3->6->7->1->5->4");

    { ListNode* l = build({1,2,3,4});   reorderList(l); check("LC143-even", dump(l), "1->4->2->3"); }
    { ListNode* l = build({1,2,3,4,5}); reorderList(l); check("LC143-odd",  dump(l), "1->5->2->4->3"); }

    check("LC148",     dump(sortList(build({4,2,1,3}))), "1->2->3->4");
    check("LC148-neg", dump(sortList(build({-1,5,3,4,0}))), "-1->0->3->4->5");
    check("LC148-two", dump(sortList(build({2,1}))), "1->2");

    { RandomNode* a = new RandomNode(7); RandomNode* b = new RandomNode(13);
      RandomNode* c = new RandomNode(11);
      a->next = b; b->next = c;
      a->random = nullptr; b->random = a; c->random = a;
      RandomNode* cp = copyRandomList(a);
      string r = to_string(cp->val);
      r += "," + string(cp->random == nullptr ? "null" : "x");
      r += "," + to_string(cp->next->random->val);
      r += "," + string(cp->next->random == cp ? "deep" : "SHALLOW");
      r += "," + to_string(a->next->val);            // original must be restored
      check("LC138", r, "7,null,7,deep,13"); }

    { LRUCache c(2);
      c.put(1,1); c.put(2,2);
      string r = to_string(c.get(1));      // 1
      c.put(3,3);                           // evicts key 2
      r += "," + to_string(c.get(2));       // -1
      c.put(4,4);                           // evicts key 1
      r += "," + to_string(c.get(1));       // -1
      r += "," + to_string(c.get(3));       // 3
      r += "," + to_string(c.get(4));       // 4
      check("LC146", r, "1,-1,-1,3,4"); }

    cout << "===== TIER 3 =====\n";
    check("LC25-k2", dump(reverseKGroup(build({1,2,3,4,5}), 2)), "2->1->4->3->5");
    check("LC25-k3", dump(reverseKGroup(build({1,2,3,4,5}), 3)), "3->2->1->4->5");
    check("LC25-k1", dump(reverseKGroup(build({1,2,3}), 1)), "1->2->3");

    { vector<ListNode*> v = {build({1,4,5}), build({1,3,4}), build({2,6})};
      check("LC23", dump(mergeKLists(v)), "1->1->2->3->4->4->5->6"); }
    { vector<ListNode*> v; check("LC23-empty", dump(mergeKLists(v)), "(empty)"); }
    { vector<ListNode*> v = {nullptr}; check("LC23-nullonly", dump(mergeKLists(v)), "(empty)"); }

    check("LC445",       dump(addTwoNumbersII(build({7,2,4,3}), build({5,6,4}))), "7->8->0->7");
    check("LC445-carry", dump(addTwoNumbersII(build({9,9}), build({1}))), "1->0->0");

    { // 1-2-3-4-5-6, node 3 has child 7-8-9-10, node 8 has child 11-12
      vector<MultiNode*> n;
      for (int i = 1; i <= 12; i++) n.push_back(new MultiNode(i));
      auto link = [&](vector<int> ids) {
          for (size_t i = 0; i + 1 < ids.size(); i++) {
              n[ids[i]-1]->next = n[ids[i+1]-1];
              n[ids[i+1]-1]->prev = n[ids[i]-1];
          }
      };
      link({1,2,3,4,5,6}); link({7,8,9,10}); link({11,12});
      n[2]->child = n[6];      // 3 -> child 7
      n[7]->child = n[10];     // 8 -> child 11
      MultiNode* f = flatten(n[0]);
      check("LC430", dumpMulti(f), "1->2->3->7->8->11->12->9->10->4->5->6");
      check("LC430-prev", multiPrevOk(f) ? "ok" : "BROKEN", "ok"); }

    check("LC147",     dump(insertionSortList(build({4,2,1,3}))), "1->2->3->4");
    check("LC147-neg", dump(insertionSortList(build({-1,5,3,4,0}))), "-1->0->3->4->5");

    check("LC1721",     dump(swapNodes(build({1,2,3,4,5}), 2)), "1->4->3->2->5");
    check("LC1721-k1",  dump(swapNodes(build({1,2,3}), 1)), "3->2->1");
    check("LC1721-mid", dump(swapNodes(build({1,2,3}), 2)), "1->2->3");

    { TreeNode* r = sortedListToBST(build({-10,-3,0,5,9}));
      check("LC109-inorder",  treeInorder(r), "-10,-3,0,5,9");
      check("LC109-balanced", balanced(r) ? "yes" : "no", "yes"); }
    check("LC109-empty", sortedListToBST(nullptr) == nullptr ? "null" : "x", "null");

    { vector<ListNode*> p = splitListToParts(build({1,2,3}), 5);
      string r; for (auto x : p) r += dump(x) + "|";
      check("LC725-3in5", r, "1|2|3|(empty)|(empty)|"); }
    { vector<ListNode*> p = splitListToParts(build({1,2,3,4,5,6,7,8,9,10}), 3);
      string r; for (auto x : p) r += dump(x) + "|";
      check("LC725-10in3", r, "1->2->3->4|5->6->7|8->9->10|"); }

    { MyCircularQueue q(3);
      string r;
      r += q.enQueue(1) ? "T" : "F";      // T
      r += q.enQueue(2) ? "T" : "F";      // T
      r += q.enQueue(3) ? "T" : "F";      // T
      r += q.enQueue(4) ? "T" : "F";      // F (full)
      r += to_string(q.Rear());           // 3
      r += q.isFull() ? "T" : "F";        // T
      r += q.deQueue() ? "T" : "F";       // T
      r += q.enQueue(4) ? "T" : "F";      // T
      r += to_string(q.Rear());           // 4
      r += to_string(q.Front());          // 2
      check("LC622", r, "TTTF3TTT42"); }

    { LFUCache c(2);
      c.put(1,1); c.put(2,2);
      string r = to_string(c.get(1));      // 1   (freq: 1->2, 2->1)
      c.put(3,3);                           // evicts key 2 (lowest freq)
      r += "," + to_string(c.get(2));       // -1
      r += "," + to_string(c.get(3));       // 3
      c.put(4,4);                           // evicts key 1 (freq 2 vs 3's freq 2, LRU)
      r += "," + to_string(c.get(1));       // -1
      r += "," + to_string(c.get(3));       // 3
      r += "," + to_string(c.get(4));       // 4
      check("LC460", r, "1,-1,3,-1,3,4"); }
    { LFUCache c(0);
      c.put(1,1);
      check("LC460-cap0", to_string(c.get(1)), "-1"); }

    cout << "\n" << OKS << " passed, " << FAILS << " failed\n";
    cout << (FAILS == 0 ? "ALL TESTS PASSED\n" : "THERE ARE FAILURES\n");
    return FAILS;
}
