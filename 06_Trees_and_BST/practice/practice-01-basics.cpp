// ============================================================================
// PRACTICE 01 — Tree basics
//
// Fill in each TODO. Every function has tests below; run the file and it tells
// you which ones pass. Do NOT look at solutions/reference-basics.cpp until you
// have genuinely tried.
//
//   g++ -std=c++17 -O2 -Wall -o prac practice-01-basics.cpp && ./prac
//
// Everything here follows the universal skeleton from Part 1 of the guide:
//
//     T solve(TreeNode* n) {
//         if (!n) return IDENTITY;                 // what is the answer for an empty tree?
//         T L = solve(n->left), R = solve(n->right);
//         return combine(L, R, n->val);
//     }
//
// Getting IDENTITY right is usually the whole problem.
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ============================================================================
// TODO 1 — countNodes: how many nodes are in the tree?
// Empty tree -> 0.
// ============================================================================
int countNodes(TreeNode* root) {
    // TODO
    return 0;
}

// ============================================================================
// TODO 2 — sumValues: the sum of every value in the tree.
// Empty tree -> 0.
// ============================================================================
int sumValues(TreeNode* root) {
    // TODO
    return 0;
}

// ============================================================================
// TODO 3 — maxDepth: number of NODES on the longest root-to-leaf path.
// Empty tree -> 0. A single node -> 1.
// ============================================================================
int maxDepth(TreeNode* root) {
    // TODO
    return 0;
}

// ============================================================================
// TODO 4 — countLeaves: how many nodes have NO children at all?
// Careful: a node with only a left child is NOT a leaf.
// Empty tree -> 0.
// ============================================================================
int countLeaves(TreeNode* root) {
    // TODO
    return 0;
}

// ============================================================================
// TODO 5 — findMax: the largest value in the tree.
// Empty tree -> INT_MIN (that is the identity element for max).
// ============================================================================
int findMax(TreeNode* root) {
    // TODO
    return INT_MIN;
}

// ============================================================================
// TODO 6 — contains: is value x anywhere in the tree?
// This is a plain binary tree, not a BST — you must check both sides.
// ============================================================================
bool contains(TreeNode* root, int x) {
    // TODO
    return false;
}

// ============================================================================
// TODO 7 — inorder: append the values to `out` in left-NODE-right order.
// ============================================================================
void inorder(TreeNode* root, vector<int>& out) {
    // TODO
}

// ============================================================================
// TODO 8 — levelOrder: one inner vector per level, top to bottom,
// left to right within each level. Empty tree -> empty vector.
// Hint: BFS with a queue, and freeze q.size() BEFORE the inner loop.
// ============================================================================
vector<vector<int>> levelOrder(TreeNode* root) {
    // TODO
    return {};
}

// ============================================================================
// TODO 9 — invert: mirror the tree in place and return the root.
// Swap the child POINTERS, not the values.
// ============================================================================
TreeNode* invert(TreeNode* root) {
    // TODO
    return root;
}

// ============================================================================
// TODO 10 — isBST: is this a valid binary search tree?
// Remember: the rule is about the WHOLE subtree, not just the two children.
// Hint: pass down the open interval (lo, hi) each subtree is allowed to use.
// ============================================================================
bool isBST(TreeNode* root) {
    // TODO
    return false;
}

// ============================================================================
// ------------------------------ TESTS ---------------------------------------
// Nothing below this line needs changing.
// ============================================================================
const int NUL = INT_MIN;

TreeNode* build(vector<int> a) {                  // LeetCode level-order, NUL = null
    if (a.empty() || a[0] == NUL) return nullptr;
    TreeNode* root = new TreeNode(a[0]);
    queue<TreeNode*> q; q.push(root);
    size_t i = 1;
    while (!q.empty() && i < a.size()) {
        TreeNode* cur = q.front(); q.pop();
        if (i < a.size() && a[i] != NUL) { cur->left  = new TreeNode(a[i]); q.push(cur->left); }
        i++;
        if (i < a.size() && a[i] != NUL) { cur->right = new TreeNode(a[i]); q.push(cur->right); }
        i++;
    }
    return root;
}
string vecDump(const vector<int>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += to_string(v[i]); }
    return s + "]";
}
string vvDump(const vector<vector<int>>& v) {
    string s = "[";
    for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += vecDump(v[i]); }
    return s + "]";
}
string levelDump(TreeNode* r) {
    if (!r) return "[]";
    vector<string> out;
    queue<TreeNode*> q; q.push(r);
    while (!q.empty()) {
        TreeNode* n = q.front(); q.pop();
        if (!n) { out.push_back("null"); continue; }
        out.push_back(to_string(n->val));
        q.push(n->left); q.push(n->right);
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    string s = "[";
    for (size_t i = 0; i < out.size(); i++) { if (i) s += ","; s += out[i]; }
    return s + "]";
}
int FAILS = 0, OKS = 0;
void check(string name, string got, string want) {
    if (got != want) { FAILS++; cout << "FAIL " << name << "  got=" << got << "  want=" << want << "\n"; }
    else { OKS++; cout << "ok   " << name << "\n"; }
}
void check(string n, int g, int w) { check(n, to_string(g), to_string(w)); }
void check(string n, bool g, bool w) { check(n, string(g?"true":"false"), string(w?"true":"false")); }

int main() {
    // the lopsided test tree from Part 5, Step 1:
    //         5
    //       /   \        countNodes 6, sum 37, depth 4, leaves 2, max 11
    //      3     8
    //     /       \_
    //    1         9
    //               \_
    //                11
    TreeNode* T = build({5,3,8,1,NUL,NUL,9,NUL,NUL,NUL,11});

    check("1  countNodes lopsided", countNodes(T), 6);
    check("1  countNodes empty", countNodes(nullptr), 0);
    check("1  countNodes single", countNodes(build({7})), 1);

    check("2  sumValues lopsided", sumValues(T), 37);
    check("2  sumValues empty", sumValues(nullptr), 0);
    check("2  sumValues negatives", sumValues(build({-1,-2,-3})), -6);

    check("3  maxDepth lopsided", maxDepth(T), 4);
    check("3  maxDepth empty", maxDepth(nullptr), 0);
    check("3  maxDepth single", maxDepth(build({7})), 1);

    check("4  countLeaves lopsided", countLeaves(T), 2);
    check("4  countLeaves empty", countLeaves(nullptr), 0);
    check("4  countLeaves single", countLeaves(build({7})), 1);

    check("5  findMax lopsided", findMax(T), 11);
    check("5  findMax empty", findMax(nullptr), INT_MIN);
    check("5  findMax negatives", findMax(build({-5,-2,-9})), -2);

    check("6  contains present", contains(T, 9), true);
    check("6  contains deep", contains(T, 11), true);
    check("6  contains absent", contains(T, 4), false);
    check("6  contains empty", contains(nullptr, 1), false);

    { vector<int> out; inorder(T, out);
      check("7  inorder lopsided", vecDump(out), "[1,3,5,8,9,11]"); }
    { vector<int> out; inorder(nullptr, out);
      check("7  inorder empty", vecDump(out), "[]"); }

    check("8  levelOrder lopsided", vvDump(levelOrder(T)), "[[5],[3,8],[1,9],[11]]");
    check("8  levelOrder empty", vvDump(levelOrder(nullptr)), "[]");

    check("9  invert", levelDump(invert(build({4,2,7,1,3,6,9}))), "[4,7,2,9,6,3,1]");
    check("9  invert empty", levelDump(invert(nullptr)), "[]");

    check("10 isBST valid", isBST(build({8,3,10,1,6,NUL,14})), true);
    check("10 isBST grandchild violation", isBST(build({10,5,15,NUL,NUL,6,20})), false);
    check("10 isBST single", isBST(build({1})), true);
    check("10 isBST empty", isBST(nullptr), true);

    cout << "\n" << OKS << " passed, " << FAILS << " failed\n";
    if (FAILS == 0) cout << "All done. Move on to Module 2 — traversals and the BFS template.\n";
    return FAILS ? 1 : 0;
}
