// Standard starter file for solving a DSA problem locally.
// g++ -std=c++17 -O2 -Wall -o out competitive-template.cpp && ./out

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ---- list helpers ----
ListNode* build(vector<int> v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
void print(ListNode* h) {
    while (h) { cout << h->val; if (h->next) cout << "->"; h = h->next; }
    cout << "\n";
}

// ---- your solution ----
ListNode* solve(ListNode* head) {
    return head;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ListNode* l = build({1, 2, 3, 4, 5});
    print(solve(l));
    return 0;
}
