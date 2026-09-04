// ============================================================
//  LINKED LISTS - REFERENCE IMPLEMENTATIONS (all 12 patterns)
//  Companion to: ../notes/linked-lists-cpp-guide.md
//
//  Every function here is the exact template from the guide.
//  main() runs 66 test cases covering the edge cases that
//  actually break linked list code: empty list, single node,
//  two nodes, operation at head, operation at tail, k > length.
//
//  Compile:  g++ -std=c++17 -O2 -Wall -o out reference-all-patterns.cpp
//  Run:      ./out          -> expect "ALL TESTS PASSED"
// ============================================================

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// ---------- helpers ----------
ListNode* build(vector<int> v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
string dump(ListNode* h) {
    string s; while (h) { s += to_string(h->val); if (h->next) s += "->"; h = h->next; }
    return s.empty() ? "(empty)" : s;
}
int FAILS = 0;
void check(string name, string got, string want) {
    if (got != want) { FAILS++; cout << "FAIL " << name << " got=" << got << " want=" << want << "\n"; }
    else cout << "ok   " << name << " = " << got << "\n";
}

// ---------- Pattern 1 ----------
int length(ListNode* head) { int n=0; for (ListNode* c=head;c;c=c->next) n++; return n; }
bool contains(ListNode* head, int target) {
    for (ListNode* c = head; c; c = c->next) if (c->val == target) return true;
    return false;
}
ListNode* insertAt(ListNode* head, int pos, int val) {
    ListNode dummy(0); dummy.next = head; ListNode* prev = &dummy;
    for (int i = 0; i < pos && prev->next; i++) prev = prev->next;
    ListNode* node = new ListNode(val);
    node->next = prev->next; prev->next = node;
    return dummy.next;
}
ListNode* getTail(ListNode* head) { if (!head) return nullptr; while (head->next) head=head->next; return head; }

// ---------- Pattern 2 ----------
ListNode* middleNode(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while (fast && fast->next) { slow=slow->next; fast=fast->next->next; }
    return slow;
}
ListNode* firstMiddle(ListNode* head) {
    ListNode *slow=head,*fast=head->next;
    while (fast && fast->next) { slow=slow->next; fast=fast->next->next; }
    return slow;
}
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0); dummy.next=head;
    ListNode *slow=&dummy,*fast=&dummy;
    for (int i=0;i<n;i++) fast=fast->next;
    while (fast->next) { slow=slow->next; fast=fast->next; }
    slow->next = slow->next->next;
    return dummy.next;
}

// ---------- Pattern 3 ----------
ListNode* reverseList(ListNode* head) {
    ListNode* prev=nullptr;
    while (head) { ListNode* nxt=head->next; head->next=prev; prev=head; head=nxt; }
    return prev;
}
ListNode* reverseRec(ListNode* head) {
    if (!head || !head->next) return head;
    ListNode* newHead = reverseRec(head->next);
    head->next->next = head; head->next = nullptr;
    return newHead;
}
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0); dummy.next=head; ListNode* prev=&dummy;
    for (int i=1;i<left;i++) prev=prev->next;
    ListNode* curr=prev->next;
    for (int i=0;i<right-left;i++) {
        ListNode* nxt=curr->next;
        curr->next=nxt->next; nxt->next=prev->next; prev->next=nxt;
    }
    return dummy.next;
}
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* node=head;
    for (int i=0;i<k;i++) { if (!node) return head; node=node->next; }
    ListNode* prev = reverseKGroup(node,k);
    ListNode* curr = head;
    for (int i=0;i<k;i++) { ListNode* nxt=curr->next; curr->next=prev; prev=curr; curr=nxt; }
    return prev;
}

// ---------- Pattern 4 ----------
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0); dummy.next=head; ListNode* curr=&dummy;
    while (curr->next) {
        if (curr->next->val==val) curr->next=curr->next->next;
        else curr=curr->next;
    }
    return dummy.next;
}
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* curr=head;
    while (curr && curr->next) {
        if (curr->val==curr->next->val) curr->next=curr->next->next;
        else curr=curr->next;
    }
    return head;
}
ListNode* deleteAllDuplicates(ListNode* head) {
    ListNode dummy(0); dummy.next=head;
    ListNode* prev=&dummy; ListNode* curr=head;
    while (curr) {
        if (curr->next && curr->val==curr->next->val) {
            int dup=curr->val;
            while (curr && curr->val==dup) curr=curr->next;
            prev->next=curr;
        } else { prev=curr; curr=curr->next; }
    }
    return dummy.next;
}
void deleteNode(ListNode* node) { node->val=node->next->val; node->next=node->next->next; }

// ---------- Pattern 5 ----------
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0); ListNode* tail=&dummy;
    while (a&&b) {
        if (a->val<=b->val) { tail->next=a; a=a->next; }
        else { tail->next=b; b=b->next; }
        tail=tail->next;
    }
    tail->next = a?a:b;
    return dummy.next;
}
ListNode* sortList(ListNode* head) {
    if (!head||!head->next) return head;
    ListNode *slow=head,*fast=head->next;
    while (fast&&fast->next) { slow=slow->next; fast=fast->next->next; }
    ListNode* second=slow->next; slow->next=nullptr;
    return mergeTwoLists(sortList(head), sortList(second));
}
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    int n=lists.size();
    while (n>1) {
        int half=(n+1)/2;
        for (int i=0;i<n/2;i++) lists[i]=mergeTwoLists(lists[i],lists[i+half]);
        n=half;
    }
    return lists[0];
}

// ---------- Pattern 6 ----------
bool hasCycle(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while (fast&&fast->next) { slow=slow->next; fast=fast->next->next; if (slow==fast) return true; }
    return false;
}
ListNode* detectCycle(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while (fast&&fast->next) {
        slow=slow->next; fast=fast->next->next;
        if (slow==fast) { ListNode* p=head; while (p!=slow) { p=p->next; slow=slow->next; } return p; }
    }
    return nullptr;
}
int cycleLength(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while (fast&&fast->next) {
        slow=slow->next; fast=fast->next->next;
        if (slow==fast) { int len=1; for (ListNode* p=slow->next;p!=slow;p=p->next) len++; return len; }
    }
    return 0;
}

// ---------- Pattern 7 ----------
ListNode* getIntersectionNode(ListNode* a, ListNode* b) {
    if (!a||!b) return nullptr;
    ListNode *p=a,*q=b;
    while (p!=q) { p = p?p->next:b; q = q?q->next:a; }
    return p;
}
ListNode* getIntersectionByLength(ListNode* a, ListNode* b) {
    int la=length(a), lb=length(b);
    while (la>lb) { a=a->next; la--; }
    while (lb>la) { b=b->next; lb--; }
    while (a!=b) { a=a->next; b=b->next; }
    return a;
}

// ---------- Pattern 8 ----------
void reorderList(ListNode* head) {
    if (!head||!head->next) return;
    ListNode *slow=head,*fast=head->next;
    while (fast&&fast->next) { slow=slow->next; fast=fast->next->next; }
    ListNode* second=slow->next; slow->next=nullptr;
    ListNode* prev=nullptr;
    while (second) { ListNode* nxt=second->next; second->next=prev; prev=second; second=nxt; }
    ListNode* first=head;
    while (prev) {
        ListNode* n1=first->next; ListNode* n2=prev->next;
        first->next=prev; prev->next=n1;
        first=n1; prev=n2;
    }
}
ListNode* oddEvenList(ListNode* head) {
    if (!head||!head->next) return head;
    ListNode* odd=head; ListNode* even=head->next; ListNode* evenHead=even;
    while (even&&even->next) {
        odd->next=even->next; odd=odd->next;
        even->next=odd->next; even=even->next;
    }
    odd->next=evenHead;
    return head;
}
ListNode* partitionList(ListNode* head, int x) {
    ListNode lessDummy(0), geDummy(0);
    ListNode *less=&lessDummy, *ge=&geDummy;
    while (head) {
        if (head->val<x) { less->next=head; less=less->next; }
        else { ge->next=head; ge=ge->next; }
        head=head->next;
    }
    ge->next=nullptr; less->next=geDummy.next;
    return lessDummy.next;
}
ListNode* rotateRight(ListNode* head, int k) {
    if (!head||!head->next||k==0) return head;
    int n=1; ListNode* tail=head;
    while (tail->next) { tail=tail->next; n++; }
    k%=n; if (k==0) return head;
    tail->next=head;
    ListNode* newTail=head;
    for (int i=0;i<n-k-1;i++) newTail=newTail->next;
    ListNode* newHead=newTail->next; newTail->next=nullptr;
    return newHead;
}
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0); dummy.next=head; ListNode* prev=&dummy;
    while (prev->next && prev->next->next) {
        ListNode* a=prev->next; ListNode* b=a->next;
        a->next=b->next; b->next=a; prev->next=b;
        prev=a;
    }
    return dummy.next;
}

// ---------- Pattern 9 ----------
ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
    ListNode dummy(0); ListNode* tail=&dummy; int carry=0;
    while (a||b||carry) {
        int sum=carry;
        if (a) { sum+=a->val; a=a->next; }
        if (b) { sum+=b->val; b=b->next; }
        carry=sum/10;
        tail->next=new ListNode(sum%10); tail=tail->next;
    }
    return dummy.next;
}
ListNode* addTwoNumbersForward(ListNode* a, ListNode* b) {
    stack<int> sa,sb;
    for (;a;a=a->next) sa.push(a->val);
    for (;b;b=b->next) sb.push(b->val);
    ListNode* head=nullptr; int carry=0;
    while (!sa.empty()||!sb.empty()||carry) {
        int sum=carry;
        if (!sa.empty()) { sum+=sa.top(); sa.pop(); }
        if (!sb.empty()) { sum+=sb.top(); sb.pop(); }
        carry=sum/10;
        head=new ListNode(sum%10, head);
    }
    return head;
}

// ---------- Pattern 10 ----------
struct RNode {
    int val; RNode* next; RNode* random;
    RNode(int v):val(v),next(nullptr),random(nullptr) {}
};
RNode* copyWithMap(RNode* head) {
    unordered_map<RNode*,RNode*> mp;
    for (RNode* c=head;c;c=c->next) mp[c]=new RNode(c->val);
    for (RNode* c=head;c;c=c->next) {
        mp[c]->next   = c->next   ? mp[c->next]   : nullptr;
        mp[c]->random = c->random ? mp[c->random] : nullptr;
    }
    return head?mp[head]:nullptr;
}
RNode* copyInterleave(RNode* head) {
    if (!head) return nullptr;
    for (RNode* c=head;c;c=c->next->next) {
        RNode* copy=new RNode(c->val);
        copy->next=c->next; c->next=copy;
    }
    for (RNode* c=head;c;c=c->next->next)
        if (c->random) c->next->random=c->random->next;
    RNode* newHead=head->next;
    for (RNode* c=head;c;c=c->next) {
        RNode* copy=c->next;
        c->next=copy->next;
        if (copy->next) copy->next=copy->next->next;
    }
    return newHead;
}

// ---------- Pattern 11 ----------
ListNode* mergeRec(ListNode* a, ListNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->val<=b->val) { a->next=mergeRec(a->next,b); return a; }
    else { b->next=mergeRec(a,b->next); return b; }
}
ListNode* removeRec(ListNode* head, int val) {
    if (!head) return nullptr;
    head->next=removeRec(head->next,val);
    return head->val==val ? head->next : head;
}
bool isPalindrome(ListNode* head) {
    if (!head||!head->next) return true;
    ListNode *slow=head,*fast=head->next;
    while (fast&&fast->next) { slow=slow->next; fast=fast->next->next; }
    ListNode* second=reverseList(slow->next);
    slow->next=nullptr;
    ListNode *p=head,*q=second;
    bool ok=true;
    while (p&&q) { if (p->val!=q->val) { ok=false; break; } p=p->next; q=q->next; }
    slow->next=reverseList(second);   // restore
    return ok;
}

// ---------- Pattern 12 ----------
class LRUCache {
    struct Node {
        int key,val; Node *prev,*next;
        Node(int k,int v):key(k),val(v),prev(nullptr),next(nullptr) {}
    };
    int cap;
    unordered_map<int,Node*> mp;
    Node *head,*tail;
    void remove(Node* n) { n->prev->next=n->next; n->next->prev=n->prev; }
    void insertFront(Node* n) {
        n->next=head->next; n->prev=head;
        head->next->prev=n; head->next=n;
    }
public:
    LRUCache(int capacity):cap(capacity) {
        head=new Node(0,0); tail=new Node(0,0);
        head->next=tail; tail->prev=head;
    }
    int get(int key) {
        if (!mp.count(key)) return -1;
        Node* n=mp[key]; remove(n); insertFront(n);
        return n->val;
    }
    void put(int key,int value) {
        if (mp.count(key)) { Node* n=mp[key]; n->val=value; remove(n); insertFront(n); return; }
        if ((int)mp.size()==cap) {
            Node* lru=tail->prev; remove(lru); mp.erase(lru->key); delete lru;
        }
        Node* n=new Node(key,value); mp[key]=n; insertFront(n);
    }
};

int main() {
    // Pattern 1
    check("length", to_string(length(build({1,2,3,4,5}))), "5");
    check("length-empty", to_string(length(nullptr)), "0");
    check("contains", contains(build({1,2,3}),2)?"1":"0", "1");
    check("insertAt-0", dump(insertAt(build({1,2,3}),0,9)), "9->1->2->3");
    check("insertAt-mid", dump(insertAt(build({1,2,3}),2,9)), "1->2->9->3");
    check("insertAt-end", dump(insertAt(build({1,2,3}),3,9)), "1->2->3->9");
    check("insertAt-empty", dump(insertAt(nullptr,0,9)), "9");
    check("getTail", to_string(getTail(build({1,2,3}))->val), "3");

    // Pattern 2
    check("middle-odd", to_string(middleNode(build({1,2,3,4,5}))->val), "3");
    check("middle-even", to_string(middleNode(build({1,2,3,4}))->val), "3");
    check("firstMiddle-even", to_string(firstMiddle(build({1,2,3,4}))->val), "2");
    check("firstMiddle-odd", to_string(firstMiddle(build({1,2,3,4,5}))->val), "3");
    check("removeNth-1", dump(removeNthFromEnd(build({1,2,3,4,5}),2)), "1->2->3->5");
    check("removeNth-head", dump(removeNthFromEnd(build({1,2}),2)), "2");
    check("removeNth-single", dump(removeNthFromEnd(build({1}),1)), "(empty)");

    // Pattern 3
    check("reverse", dump(reverseList(build({1,2,3,4,5}))), "5->4->3->2->1");
    check("reverse-empty", dump(reverseList(nullptr)), "(empty)");
    check("reverseRec", dump(reverseRec(build({1,2,3}))), "3->2->1");
    check("reverseBetween", dump(reverseBetween(build({1,2,3,4,5}),2,4)), "1->4->3->2->5");
    check("reverseBetween-head", dump(reverseBetween(build({1,2,3,4,5}),1,5)), "5->4->3->2->1");
    check("reverseBetween-same", dump(reverseBetween(build({1,2,3}),2,2)), "1->2->3");
    check("reverseK-2", dump(reverseKGroup(build({1,2,3,4,5}),2)), "2->1->4->3->5");
    check("reverseK-3", dump(reverseKGroup(build({1,2,3,4,5}),3)), "3->2->1->4->5");

    // Pattern 4
    check("removeElements", dump(removeElements(build({1,2,6,3,4,5,6}),6)), "1->2->3->4->5");
    check("removeElements-all", dump(removeElements(build({7,7,7}),7)), "(empty)");
    check("removeElements-head", dump(removeElements(build({6,1,2}),6)), "1->2");
    check("dedup-keep1", dump(deleteDuplicates(build({1,1,2,3,3}))), "1->2->3");
    check("dedup-all", dump(deleteAllDuplicates(build({1,2,3,3,4,4,5}))), "1->2->5");
    check("dedup-all-head", dump(deleteAllDuplicates(build({1,1,1,2,3}))), "2->3");
    { ListNode* l=build({4,5,1,9}); deleteNode(l->next); check("deleteNode", dump(l), "4->1->9"); }

    // Pattern 5
    check("merge2", dump(mergeTwoLists(build({1,2,4}),build({1,3,4}))), "1->1->2->3->4->4");
    check("merge2-empty", dump(mergeTwoLists(nullptr,build({1}))), "1");
    check("sortList", dump(sortList(build({4,2,1,3}))), "1->2->3->4");
    check("sortList-2", dump(sortList(build({2,1}))), "1->2");
    check("sortList-neg", dump(sortList(build({-1,5,3,4,0}))), "-1->0->3->4->5");
    { vector<ListNode*> v = {build({1,4,5}),build({1,3,4}),build({2,6})};
      check("mergeK", dump(mergeKLists(v)), "1->1->2->3->4->4->5->6"); }
    { vector<ListNode*> v = {build({1})};
      check("mergeK-1", dump(mergeKLists(v)), "1"); }

    // Pattern 6
    { ListNode* l=build({3,2,0,-4}); l->next->next->next->next = l->next;
      check("hasCycle", hasCycle(l)?"1":"0", "1");
      check("detectCycle", to_string(detectCycle(l)->val), "2");
      check("cycleLength", to_string(cycleLength(l)), "3"); }
    check("noCycle", hasCycle(build({1,2,3}))?"1":"0", "0");
    check("detectCycle-none", detectCycle(build({1,2,3}))==nullptr?"null":"x", "null");

    // Pattern 7
    { ListNode* common=build({8,4,5});
      ListNode* a=build({4,1}); getTail(a)->next=common;
      ListNode* b=build({5,6,1}); getTail(b)->next=common;
      check("intersect", to_string(getIntersectionNode(a,b)->val), "8");
      check("intersect-len", to_string(getIntersectionByLength(a,b)->val), "8"); }
    check("intersect-none", getIntersectionNode(build({1,2}),build({3,4}))==nullptr?"null":"x", "null");

    // Pattern 8
    { ListNode* l=build({1,2,3,4}); reorderList(l); check("reorder-even", dump(l), "1->4->2->3"); }
    { ListNode* l=build({1,2,3,4,5}); reorderList(l); check("reorder-odd", dump(l), "1->5->2->4->3"); }
    check("oddEven", dump(oddEvenList(build({1,2,3,4,5}))), "1->3->5->2->4");
    check("oddEven-even", dump(oddEvenList(build({2,1,3,5,6,4,7}))), "2->3->6->7->1->5->4");
    check("partition", dump(partitionList(build({1,4,3,2,5,2}),3)), "1->2->2->4->3->5");
    check("rotate", dump(rotateRight(build({1,2,3,4,5}),2)), "4->5->1->2->3");
    check("rotate-big-k", dump(rotateRight(build({1,2}),5)), "2->1");
    check("swapPairs", dump(swapPairs(build({1,2,3,4}))), "2->1->4->3");
    check("swapPairs-odd", dump(swapPairs(build({1,2,3}))), "2->1->3");

    // Pattern 9
    check("add-rev", dump(addTwoNumbers(build({2,4,3}),build({5,6,4}))), "7->0->8");
    check("add-carry", dump(addTwoNumbers(build({9,9,9}),build({1}))), "0->0->0->1");
    check("add-fwd", dump(addTwoNumbersForward(build({7,2,4,3}),build({5,6,4}))), "7->8->0->7");

    // Pattern 10
    { RNode* a=new RNode(1); RNode* b=new RNode(2); a->next=b;
      a->random=b; b->random=b;
      RNode* c=copyWithMap(a);
      check("copyMap", to_string(c->val)+","+to_string(c->random->val)+","+(c->random==c->next?"same":"diff"), "1,2,same");
      RNode* d=copyInterleave(a);
      check("copyInter", to_string(d->val)+","+to_string(d->next->val)+","+(d->random==d->next?"same":"diff"), "1,2,same");
      check("copyInter-restored", to_string(a->next->val), "2"); }

    // Pattern 11
    check("mergeRec", dump(mergeRec(build({1,3}),build({2,4}))), "1->2->3->4");
    check("removeRec", dump(removeRec(build({1,2,2,3}),2)), "1->3");
    check("palin-yes", isPalindrome(build({1,2,2,1}))?"1":"0", "1");
    check("palin-odd", isPalindrome(build({1,2,3,2,1}))?"1":"0", "1");
    check("palin-no", isPalindrome(build({1,2}))?"1":"0", "0");

    // Pattern 12
    { LRUCache c(2);
      c.put(1,1); c.put(2,2);
      string r = to_string(c.get(1));       // 1
      c.put(3,3);                            // evicts 2
      r += "," + to_string(c.get(2));        // -1
      c.put(4,4);                            // evicts 1
      r += "," + to_string(c.get(1));        // -1
      r += "," + to_string(c.get(3));        // 3
      r += "," + to_string(c.get(4));        // 4
      check("LRU", r, "1,-1,-1,3,4"); }

    cout << "\n" << (FAILS==0 ? "ALL TESTS PASSED" : to_string(FAILS)+" FAILURES") << "\n";
    return FAILS;
}
