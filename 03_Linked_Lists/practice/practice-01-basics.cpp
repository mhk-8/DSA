// ============================================================
//  WEEK 1 PRACTICE FILE — build a linked list from scratch
//  Compile:  g++ -std=c++17 -o practice practice_week1.cpp
//  Run:      ./practice
//
//  Fill in each TODO. The tests at the bottom tell you if
//  you got it right. Do NOT look at the guide while coding —
//  look only after you're stuck for 10 minutes.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ---------- given to you: helpers ----------
ListNode* build(vector<int> v) {
    ListNode dummy(0);
    ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}

string dump(ListNode* h) {
    string s;
    while (h) { s += to_string(h->val); if (h->next) s += "->"; h = h->next; }
    return s.empty() ? "(empty)" : s;
}

int PASS = 0, FAIL = 0;
void check(const string& name, const string& got, const string& want) {
    if (got == want) { PASS++; cout << "  ok   " << name << "\n"; }
    else { FAIL++; cout << "  FAIL " << name << "  got: " << got << "   want: " << want << "\n"; }
}

// ============================================================
//  YOUR TURN
// ============================================================

// 1. Count the nodes.
int length(ListNode* head) {
    // TODO
    return 0;
}

// 2. Return true if `target` appears in the list.
bool contains(ListNode* head, int target) {
    // TODO
    return false;
}

// 3. Add a node with value `val` at the FRONT. Return the new head.
ListNode* insertFront(ListNode* head, int val) {
    // TODO
    return head;
}

// 4. Add a node with value `val` at the END. Return the head.
//    Careful: what if the list is empty?
ListNode* insertBack(ListNode* head, int val) {
    // TODO
    return head;
}

// 5. Insert `val` at 0-indexed position `pos`. Return the head.
//    Hint: use a dummy node.
ListNode* insertAt(ListNode* head, int pos, int val) {
    // TODO
    return head;
}

// 6. Delete the FIRST node whose value equals `val`. Return the head.
//    Careful: the head itself might be the one to delete.
ListNode* deleteValue(ListNode* head, int val) {
    // TODO
    return head;
}

// 7. Delete ALL nodes whose value equals `val`. Return the head.
ListNode* deleteAll(ListNode* head, int val) {
    // TODO
    return head;
}

// 8. Return the middle node (second middle if the length is even).
//    Use fast & slow pointers — no counting the length first.
ListNode* middle(ListNode* head) {
    // TODO
    return head;
}

// 9. Reverse the list. Return the new head. Iterative, O(1) space.
ListNode* reverse(ListNode* head) {
    // TODO
    return head;
}

// 10. Return the k-th node from the END (k=1 means the last node).
//     One pass, two pointers.
ListNode* kthFromEnd(ListNode* head, int k) {
    // TODO
    return head;
}

// ============================================================
//  TESTS — do not edit
// ============================================================
int main() {
    cout << "1. length\n";
    check("empty",  to_string(length(nullptr)),          "0");
    check("three",  to_string(length(build({1,2,3}))),   "3");

    cout << "2. contains\n";
    check("found",     contains(build({1,2,3}), 2) ? "yes" : "no", "yes");
    check("not found", contains(build({1,2,3}), 9) ? "yes" : "no", "no");
    check("empty",     contains(nullptr, 1)        ? "yes" : "no", "no");

    cout << "3. insertFront\n";
    check("normal", dump(insertFront(build({2,3}), 1)), "1->2->3");
    check("empty",  dump(insertFront(nullptr, 1)),      "1");

    cout << "4. insertBack\n";
    check("normal", dump(insertBack(build({1,2}), 3)), "1->2->3");
    check("empty",  dump(insertBack(nullptr, 1)),      "1");

    cout << "5. insertAt\n";
    check("pos 0",   dump(insertAt(build({1,2,3}), 0, 9)), "9->1->2->3");
    check("pos 2",   dump(insertAt(build({1,2,3}), 2, 9)), "1->2->9->3");
    check("pos end", dump(insertAt(build({1,2,3}), 3, 9)), "1->2->3->9");
    check("empty",   dump(insertAt(nullptr, 0, 9)),        "9");

    cout << "6. deleteValue\n";
    check("middle", dump(deleteValue(build({1,2,3}), 2)),   "1->3");
    check("head",   dump(deleteValue(build({1,2,3}), 1)),   "2->3");
    check("tail",   dump(deleteValue(build({1,2,3}), 3)),   "1->2");
    check("only",   dump(deleteValue(build({1}), 1)),       "(empty)");
    check("absent", dump(deleteValue(build({1,2}), 9)),     "1->2");

    cout << "7. deleteAll\n";
    check("scattered", dump(deleteAll(build({1,6,2,6,3,6}), 6)), "1->2->3");
    check("all gone",  dump(deleteAll(build({7,7,7}), 7)),       "(empty)");
    check("at head",   dump(deleteAll(build({6,6,1,2}), 6)),     "1->2");

    cout << "8. middle\n";
    check("odd",    to_string(middle(build({1,2,3,4,5}))->val), "3");
    check("even",   to_string(middle(build({1,2,3,4}))->val),   "3");
    check("single", to_string(middle(build({1}))->val),         "1");

    cout << "9. reverse\n";
    check("five",   dump(reverse(build({1,2,3,4,5}))), "5->4->3->2->1");
    check("single", dump(reverse(build({1}))),         "1");
    check("empty",  dump(reverse(nullptr)),            "(empty)");

    cout << "10. kthFromEnd\n";
    check("k=1", to_string(kthFromEnd(build({1,2,3,4,5}), 1)->val), "5");
    check("k=2", to_string(kthFromEnd(build({1,2,3,4,5}), 2)->val), "4");
    check("k=n", to_string(kthFromEnd(build({1,2,3,4,5}), 5)->val), "1");

    cout << "\n" << PASS << " passed, " << FAIL << " failed\n";
    if (FAIL == 0) cout << "All done. Move on to LeetCode 707, 876, 206, 203, 83.\n";
    return 0;
}
