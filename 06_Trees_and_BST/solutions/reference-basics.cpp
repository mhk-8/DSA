// ============================================================================
// Reference solutions for practice-01-basics.cpp.
// Read this only after you have genuinely attempted the practice file.
//
//   g++ -std=c++17 -O2 -Wall -o refb reference-basics.cpp && ./refb
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 1 — size. Identity for a count is 0; combine is addition, plus one for me.
int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// 2 — sum. Identity 0, combine is addition of my own value too.
int sumValues(TreeNode* root) {
    if (!root) return 0;
    return root->val + sumValues(root->left) + sumValues(root->right);
}

// 3 — height in nodes. Identity 0, combine is 1 + the deeper side.
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// 4 — leaves. A leaf has BOTH children null; a one-child node is not a leaf.
int countLeaves(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// 5 — maximum. Identity for max is INT_MIN, which is why an empty tree returns it.
int findMax(TreeNode* root) {
    if (!root) return INT_MIN;
    return max(root->val, max(findMax(root->left), findMax(root->right)));
}

// 6 — membership in a plain binary tree: both sides must be searched.
bool contains(TreeNode* root, int x) {
    if (!root) return false;
    if (root->val == x) return true;
    return contains(root->left, x) || contains(root->right, x);   // short-circuits
}

// 7 — inorder: left, NODE, right.
void inorder(TreeNode* root, vector<int>& out) {
    if (!root) return;
    inorder(root->left, out);
    out.push_back(root->val);
    inorder(root->right, out);
}

// 8 — level order. The whole trick is freezing the level width before the loop.
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> out;
    if (!root) return out;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        int sz = q.size();                 // the current level, frozen
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* n = q.front(); q.pop();
            level.push_back(n->val);
            if (n->left)  q.push(n->left);
            if (n->right) q.push(n->right);
        }
        out.push_back(level);
    }
    return out;
}

// 9 — mirror the tree. Swap the pointers, then recurse.
TreeNode* invert(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invert(root->left);
    invert(root->right);
    return root;
}

// 10 — BST validation by the range method. long, so INT_MIN/INT_MAX nodes are legal.
static bool validRange(TreeNode* n, long lo, long hi) {
    if (!n) return true;
    if (n->val <= lo || n->val >= hi) return false;
    return validRange(n->left, lo, n->val) && validRange(n->right, n->val, hi);
}
bool isBST(TreeNode* root) { return validRange(root, LONG_MIN, LONG_MAX); }

// ============================================================================
// ------------------------------ TESTS ---------------------------------------
// ============================================================================
const int NUL = INT_MIN;

TreeNode* build(vector<int> a) {
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
    return FAILS ? 1 : 0;
}
