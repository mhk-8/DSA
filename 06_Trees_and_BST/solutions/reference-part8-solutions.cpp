// ============================================================================
// Trees & BST — verified solutions for all 38 problems in Part 8 of the guide.
//
// Code between //>>>BEGIN X and //<<<END X markers is extracted verbatim into
// Trees-and-BST-Solved-Questions.pdf, so the printed code IS the tested code.
//
// Build:  g++ -std=c++17 -O2 -Wall -o ref reference-part8-solutions.cpp && ./ref
// ============================================================================
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Node with a next pointer, used by LC 116.
struct Node {
    int val;
    Node *left, *right, *next;
    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

// ---------- test helpers (not part of any solution) ----------
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

Node* buildN(vector<int> a) {                     // same, for the Node type (LC 116)
    if (a.empty() || a[0] == NUL) return nullptr;
    Node* root = new Node(a[0]);
    queue<Node*> q; q.push(root);
    size_t i = 1;
    while (!q.empty() && i < a.size()) {
        Node* cur = q.front(); q.pop();
        if (i < a.size() && a[i] != NUL) { cur->left  = new Node(a[i]); q.push(cur->left); }
        i++;
        if (i < a.size() && a[i] != NUL) { cur->right = new Node(a[i]); q.push(cur->right); }
        i++;
    }
    return root;
}

TreeNode* find(TreeNode* r, int v) {              // locate a node by value (for LCA tests)
    if (!r) return nullptr;
    if (r->val == v) return r;
    TreeNode* L = find(r->left, v);
    return L ? L : find(r->right, v);
}

string levelDump(TreeNode* r) {                   // canonical level-order string with nulls trimmed
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
string sortedVVDump(vector<vector<int>> v) {      // order-insensitive compare
    for (auto& r : v) sort(r.begin(), r.end());
    sort(v.begin(), v.end());
    return vvDump(v);
}

int FAILS = 0, OKS = 0;
void check(string name, string got, string want) {
    if (got != want) { FAILS++; cout << "FAIL " << name << "  got=" << got << "  want=" << want << "\n"; }
    else { OKS++; cout << "ok   " << name << "\n"; }
}
void check(string name, int got, int want) { check(name, to_string(got), to_string(want)); }
void check(string name, bool got, bool want) { check(name, string(got?"true":"false"), string(want?"true":"false")); }

// ============================================================================
// TIER 1 — Learn the mechanics
// ============================================================================

namespace LC94 {
//>>>BEGIN LC94
class Solution {
public:
    // Recursive — left, NODE, right.
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> out;
        dfs(root, out);
        return out;
    }
    void dfs(TreeNode* n, vector<int>& out) {
        if (!n) return;
        dfs(n->left, out);
        out.push_back(n->val);
        dfs(n->right, out);
    }

    // Iterative — the follow-up the interviewer always asks for.
    vector<int> inorderIterative(TreeNode* root) {
        vector<int> out;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            while (cur) { st.push(cur); cur = cur->left; }  // dive left, remembering the way back
            cur = st.top(); st.pop();
            out.push_back(cur->val);                         // visit
            cur = cur->right;                                // then go right
        }
        return out;
    }
};
//<<<END LC94
}

namespace LC144 {
//>>>BEGIN LC144
class Solution {
public:
    // Recursive — NODE, left, right.
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> out;
        dfs(root, out);
        return out;
    }
    void dfs(TreeNode* n, vector<int>& out) {
        if (!n) return;
        out.push_back(n->val);
        dfs(n->left, out);
        dfs(n->right, out);
    }

    // Iterative — push right first so left pops first.
    vector<int> preorderIterative(TreeNode* root) {
        vector<int> out;
        if (!root) return out;
        stack<TreeNode*> st; st.push(root);
        while (!st.empty()) {
            TreeNode* n = st.top(); st.pop();
            out.push_back(n->val);
            if (n->right) st.push(n->right);
            if (n->left)  st.push(n->left);
        }
        return out;
    }
};
//<<<END LC144
}

namespace LC145 {
//>>>BEGIN LC145
class Solution {
public:
    // Recursive — left, right, NODE.
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> out;
        dfs(root, out);
        return out;
    }
    void dfs(TreeNode* n, vector<int>& out) {
        if (!n) return;
        dfs(n->left, out);
        dfs(n->right, out);
        out.push_back(n->val);
    }

    // Iterative — do preorder as node,right,left then reverse it.
    vector<int> postorderIterative(TreeNode* root) {
        vector<int> out;
        if (!root) return out;
        stack<TreeNode*> st; st.push(root);
        while (!st.empty()) {
            TreeNode* n = st.top(); st.pop();
            out.push_back(n->val);
            if (n->left)  st.push(n->left);
            if (n->right) st.push(n->right);
        }
        reverse(out.begin(), out.end());
        return out;
    }
};
//<<<END LC145
}

namespace LC102 {
//>>>BEGIN LC102
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> out;
        if (!root) return out;
        queue<TreeNode*> q; q.push(root);
        while (!q.empty()) {
            int sz = q.size();                 // freeze the level width BEFORE pushing children
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
};
//<<<END LC102
}

namespace LC104 {
//>>>BEGIN LC104
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;                                          // empty tree: depth 0
        return 1 + max(maxDepth(root->left), maxDepth(root->right));  // me + the deeper child
    }
};
//<<<END LC104
}

namespace LC111 {
//>>>BEGIN LC111
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        // A missing child is NOT a path of length 0 — it is no path at all,
        // so a node with one child must take the depth of the child it has.
        if (!root->left)  return 1 + minDepth(root->right);
        if (!root->right) return 1 + minDepth(root->left);
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }

    // BFS alternative: stop at the first leaf dequeued. Faster on wide, deep trees.
    int minDepthBFS(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q; q.push(root);
        int depth = 1;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* n = q.front(); q.pop();
                if (!n->left && !n->right) return depth;
                if (n->left)  q.push(n->left);
                if (n->right) q.push(n->right);
            }
            depth++;
        }
        return depth;
    }
};
//<<<END LC111
}

namespace LC226 {
//>>>BEGIN LC226
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);   // swap the pointers, not the values
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
//<<<END LC226
}

namespace LC100 {
//>>>BEGIN LC100
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;      // both empty  -> equal
        if (!p || !q) return false;     // exactly one -> unequal
        return p->val == q->val
            && isSameTree(p->left,  q->left)
            && isSameTree(p->right, q->right);
    }
};
//<<<END LC100
}

namespace LC101 {
//>>>BEGIN LC101
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return !root || mirror(root->left, root->right);
    }
    bool mirror(TreeNode* a, TreeNode* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->val == b->val
            && mirror(a->left,  b->right)   // note the crossed pairing
            && mirror(a->right, b->left);
    }
};
//<<<END LC101
}

namespace LC112 {
//>>>BEGIN LC112
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;                                  // no node, no path
        targetSum -= root->val;
        if (!root->left && !root->right) return targetSum == 0;   // decide AT THE LEAF
        return hasPathSum(root->left,  targetSum)
            || hasPathSum(root->right, targetSum);
    }
};
//<<<END LC112
}

namespace LC543 {
//>>>BEGIN LC543
class Solution {
    int best = 0;
    int depth(TreeNode* n) {
        if (!n) return 0;
        int L = depth(n->left);
        int R = depth(n->right);
        best = max(best, L + R);       // RECORD: longest path that bends at n (in edges)
        return 1 + max(L, R);          // RETURN: what my parent actually needs
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        best = 0;
        depth(root);
        return best;
    }
};
//<<<END LC543
}

namespace LC110 {
//>>>BEGIN LC110
class Solution {
    // Returns the height, or -1 meaning "already unbalanced somewhere below".
    int h(TreeNode* n) {
        if (!n) return 0;
        int L = h(n->left);  if (L == -1) return -1;
        int R = h(n->right); if (R == -1) return -1;
        if (abs(L - R) > 1) return -1;
        return 1 + max(L, R);
    }
public:
    bool isBalanced(TreeNode* root) { return h(root) != -1; }
};
//<<<END LC110
}

// ============================================================================
// TIER 2 — The placement core
// ============================================================================

namespace LC700 {
//>>>BEGIN LC700
class Solution {
public:
    // Iterative: O(h) time, O(1) space. The recursive version is equally accepted.
    TreeNode* searchBST(TreeNode* root, int val) {
        while (root && root->val != val)
            root = val < root->val ? root->left : root->right;
        return root;                     // nullptr if the key is absent
    }
};
//<<<END LC700
}

namespace LC701 {
//>>>BEGIN LC701
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) return new TreeNode(val);          // the empty slot where val belongs
        if (val < root->val) root->left  = insertIntoBST(root->left,  val);
        else                 root->right = insertIntoBST(root->right, val);
        return root;                                   // reassign-from-return-value idiom
    }
};
//<<<END LC701
}

namespace LC450 {
//>>>BEGIN LC450
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        if      (key < root->val) root->left  = deleteNode(root->left,  key);
        else if (key > root->val) root->right = deleteNode(root->right, key);
        else {
            // found it — three cases
            if (!root->left)  return root->right;   // leaf, or only a right child
            if (!root->right) return root->left;    // only a left child
            TreeNode* succ = root->right;           // two children: inorder successor
            while (succ->left) succ = succ->left;   // = smallest value in the right subtree
            root->val = succ->val;                  // copy its value up
            root->right = deleteNode(root->right, succ->val);   // then delete the successor
        }
        return root;
    }
};
//<<<END LC450
}

namespace LC98 {
//>>>BEGIN LC98
class Solution {
    // Every node must lie strictly inside the open interval (lo, hi).
    // Going left tightens hi; going right tightens lo.
    bool valid(TreeNode* n, long lo, long hi) {
        if (!n) return true;
        if (n->val <= lo || n->val >= hi) return false;
        return valid(n->left, lo, n->val) && valid(n->right, n->val, hi);
    }
public:
    bool isValidBST(TreeNode* root) {
        return valid(root, LONG_MIN, LONG_MAX);   // long, because a node may hold INT_MIN/INT_MAX
    }
};
//<<<END LC98
}

namespace LC230 {
//>>>BEGIN LC230
class Solution {
    int k_ = 0, ans_ = -1;
    void inorder(TreeNode* n) {
        if (!n || k_ == 0) return;                       // stop as soon as we have the answer
        inorder(n->left);
        if (k_ == 0) return;
        if (--k_ == 0) { ans_ = n->val; return; }
        inorder(n->right);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        k_ = k; ans_ = -1;
        inorder(root);                                   // inorder of a BST is sorted order
        return ans_;
    }
};
//<<<END LC230
}

namespace LC235 {
//>>>BEGIN LC235
class Solution {
public:
    // In a BST the values tell you which way to go — no searching needed. O(h), O(1).
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            if (p->val < root->val && q->val < root->val)      root = root->left;
            else if (p->val > root->val && q->val > root->val) root = root->right;
            else return root;          // the split point (or one of p/q itself)
        }
        return nullptr;
    }
};
//<<<END LC235
}

namespace LC236 {
//>>>BEGIN LC236
class Solution {
public:
    // Read the return value as "a target I found below me, or the answer".
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;
        TreeNode* L = lowestCommonAncestor(root->left,  p, q);
        TreeNode* R = lowestCommonAncestor(root->right, p, q);
        if (L && R) return root;       // p and q are on opposite sides -> this is the LCA
        return L ? L : R;              // both on one side -> pass the find upward
    }
};
//<<<END LC236
}

namespace LC108 {
//>>>BEGIN LC108
class Solution {
    TreeNode* build(vector<int>& a, int lo, int hi) {
        if (lo > hi) return nullptr;
        int mid = lo + (hi - lo) / 2;        // the middle becomes the root -> balanced
        TreeNode* n = new TreeNode(a[mid]);
        n->left  = build(a, lo, mid - 1);
        n->right = build(a, mid + 1, hi);
        return n;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build(nums, 0, (int)nums.size() - 1);
    }
};
//<<<END LC108
}

namespace LC105 {
//>>>BEGIN LC105
class Solution {
    unordered_map<int,int> pos;    // value -> its index in inorder, so the split is O(1)
    int pre = 0;
    TreeNode* build(vector<int>& preorder, int lo, int hi) {
        if (lo > hi) return nullptr;
        int rootVal = preorder[pre++];       // preorder gives the root...
        TreeNode* n = new TreeNode(rootVal);
        int mid = pos[rootVal];              // ...inorder says where it splits
        n->left  = build(preorder, lo, mid - 1);
        n->right = build(preorder, mid + 1, hi);
        return n;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pos.clear(); pre = 0;
        for (int i = 0; i < (int)inorder.size(); i++) pos[inorder[i]] = i;
        return build(preorder, 0, (int)inorder.size() - 1);
    }
};
//<<<END LC105
}

namespace LC106 {
//>>>BEGIN LC106
class Solution {
    unordered_map<int,int> pos;
    int post = 0;
    TreeNode* build(vector<int>& postorder, int lo, int hi) {
        if (lo > hi) return nullptr;
        int rootVal = postorder[post--];     // read postorder BACKWARDS
        TreeNode* n = new TreeNode(rootVal);
        int mid = pos[rootVal];
        n->right = build(postorder, mid + 1, hi);   // RIGHT subtree first — it sits nearer the end
        n->left  = build(postorder, lo, mid - 1);
        return n;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        pos.clear();
        post = (int)postorder.size() - 1;
        for (int i = 0; i < (int)inorder.size(); i++) pos[inorder[i]] = i;
        return build(postorder, 0, (int)inorder.size() - 1);
    }
};
//<<<END LC106
}

namespace LC103 {
//>>>BEGIN LC103
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> out;
        if (!root) return out;
        queue<TreeNode*> q; q.push(root);
        bool leftToRight = true;
        while (!q.empty()) {
            int sz = q.size();
            vector<int> level(sz);
            for (int i = 0; i < sz; i++) {
                TreeNode* n = q.front(); q.pop();
                // write straight into the right slot instead of reversing afterwards
                level[leftToRight ? i : sz - 1 - i] = n->val;
                if (n->left)  q.push(n->left);
                if (n->right) q.push(n->right);
            }
            out.push_back(level);
            leftToRight = !leftToRight;
        }
        return out;
    }
};
//<<<END LC103
}

namespace LC199 {
//>>>BEGIN LC199
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> out;
        if (!root) return out;
        queue<TreeNode*> q; q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* n = q.front(); q.pop();
                if (i == sz - 1) out.push_back(n->val);   // last node of the level
                if (n->left)  q.push(n->left);
                if (n->right) q.push(n->right);
            }
        }
        return out;
    }
};
//<<<END LC199
}

namespace LC113 {
//>>>BEGIN LC113
class Solution {
    vector<vector<int>> out;
    vector<int> path;
    void dfs(TreeNode* n, int target) {
        if (!n) return;
        path.push_back(n->val);
        target -= n->val;
        if (!n->left && !n->right && target == 0) out.push_back(path);  // record AT THE LEAF
        dfs(n->left,  target);
        dfs(n->right, target);
        path.pop_back();                                                // BACKTRACK
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        out.clear(); path.clear();
        dfs(root, targetSum);
        return out;
    }
};
//<<<END LC113
}

namespace LC129 {
//>>>BEGIN LC129
class Solution {
    int total = 0;
    void dfs(TreeNode* n, int cur) {
        if (!n) return;
        cur = cur * 10 + n->val;                        // build the number on the way down
        if (!n->left && !n->right) { total += cur; return; }
        dfs(n->left, cur);
        dfs(n->right, cur);
    }
public:
    int sumNumbers(TreeNode* root) {
        total = 0;
        dfs(root, 0);
        return total;
    }
};
//<<<END LC129
}

namespace LC114 {
//>>>BEGIN LC114
class Solution {
public:
    // O(1) extra space: splice the left subtree in between the node and its right subtree.
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode* pred = cur->left;
                while (pred->right) pred = pred->right;   // rightmost node of the left subtree
                pred->right = cur->right;                 // old right tail hangs off it
                cur->right  = cur->left;                  // left subtree moves across
                cur->left   = nullptr;                    // and cut
            }
            cur = cur->right;
        }
    }
};
//<<<END LC114
}

namespace LC116 {
//>>>BEGIN LC116
class Solution {
public:
    // Perfect tree, O(1) extra space: use the level you have already linked
    // to walk across and link the level below it.
    Node* connect(Node* root) {
        Node* leftmost = root;
        while (leftmost && leftmost->left) {
            for (Node* n = leftmost; n; n = n->next) {
                n->left->next = n->right;                          // within the same parent
                if (n->next) n->right->next = n->next->left;       // across two parents
            }
            leftmost = leftmost->left;
        }
        return root;
    }
};
//<<<END LC116
}

// ============================================================================
// TIER 3 — Harder, but they do appear
// ============================================================================

namespace LC124 {
//>>>BEGIN LC124
class Solution {
    int best = INT_MIN;
    int gain(TreeNode* n) {
        if (!n) return 0;
        int L = max(0, gain(n->left));       // a negative branch is worth dropping entirely
        int R = max(0, gain(n->right));
        best = max(best, n->val + L + R);    // RECORD: the path that bends at n
        return n->val + max(L, R);           // RETURN: a straight path the parent can extend
    }
public:
    int maxPathSum(TreeNode* root) {
        best = INT_MIN;
        gain(root);
        return best;
    }
};
//<<<END LC124
}

namespace LC297 {
//>>>BEGIN LC297
class Codec {
public:
    // Preorder with explicit '#' null markers — the markers are what make it decodable.
    string serialize(TreeNode* root) {
        string s;
        ser(root, s);
        return s;
    }
    void ser(TreeNode* n, string& s) {
        if (!n) { s += "#,"; return; }
        s += to_string(n->val) + ",";
        ser(n->left, s);
        ser(n->right, s);
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return des(in);
    }
    TreeNode* des(istringstream& in) {
        string tok;
        if (!getline(in, tok, ',')) return nullptr;
        if (tok == "#") return nullptr;
        TreeNode* n = new TreeNode(stoi(tok));
        n->left  = des(in);        // the recursion consumes the stream in the same order
        n->right = des(in);
        return n;
    }
};
//<<<END LC297
}

namespace LC437 {
//>>>BEGIN LC437
class Solution {
    unordered_map<long long,int> cnt;      // prefix sum along the current path -> how many times seen
    int dfs(TreeNode* n, long long run, int target) {
        if (!n) return 0;
        run += n->val;
        int res = cnt.count(run - target) ? cnt[run - target] : 0;   // paths ending here
        cnt[run]++;
        res += dfs(n->left, run, target) + dfs(n->right, run, target);
        cnt[run]--;                        // BACKTRACK the map as well as the path
        return res;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        cnt.clear();
        cnt[0] = 1;                        // the empty prefix — a path starting at the root
        return dfs(root, 0, targetSum);
    }
};
//<<<END LC437
}

namespace LC572 {
//>>>BEGIN LC572
class Solution {
    bool same(TreeNode* a, TreeNode* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
    }
public:
    // O(n*m): try isSameTree at every node. The O(n+m) answer is to serialise
    // both trees with null markers and run a substring search — worth mentioning.
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) return !subRoot;
        if (same(root, subRoot)) return true;
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};
//<<<END LC572
}

namespace LC863 {
//>>>BEGIN LC863
class Solution {
    unordered_map<TreeNode*, TreeNode*> par;
    void mark(TreeNode* n, TreeNode* p) {
        if (!n) return;
        par[n] = p;
        mark(n->left, n);
        mark(n->right, n);
    }
public:
    // A tree has no upward edges, so build them, then it is an ordinary BFS on a graph.
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        par.clear();
        mark(root, nullptr);
        unordered_set<TreeNode*> seen;
        queue<TreeNode*> q; q.push(target); seen.insert(target);
        int d = 0;
        while (!q.empty()) {
            if (d == k) {
                vector<int> out;
                while (!q.empty()) { out.push_back(q.front()->val); q.pop(); }
                return out;
            }
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                TreeNode* n = q.front(); q.pop();
                for (TreeNode* nb : {n->left, n->right, par[n]})
                    if (nb && !seen.count(nb)) { seen.insert(nb); q.push(nb); }
            }
            d++;
        }
        return {};
    }
};
//<<<END LC863
}

namespace LC99 {
//>>>BEGIN LC99
class Solution {
    TreeNode *first = nullptr, *second = nullptr, *prev = nullptr;
    void scan(TreeNode* n) {
        if (!n) return;
        scan(n->left);
        // Exactly two nodes are swapped: that is one inversion if they are adjacent
        // in the inorder sequence, two inversions if they are not.
        if (prev && prev->val > n->val) {
            if (!first) first = prev;
            second = n;
        }
        prev = n;
        scan(n->right);
    }
public:
    void recoverTree(TreeNode* root) {
        first = second = prev = nullptr;
        scan(root);
        if (first && second) swap(first->val, second->val);
    }
};
//<<<END LC99
}

namespace LC337 {
//>>>BEGIN LC337
class Solution {
    // Returns {best if this node is skipped, best if this node is robbed}.
    pair<int,int> dfs(TreeNode* n) {
        if (!n) return {0, 0};
        auto L = dfs(n->left), R = dfs(n->right);
        int skip = max(L.first, L.second) + max(R.first, R.second);  // children free to choose
        int take = n->val + L.first + R.first;                       // children must be skipped
        return {skip, take};
    }
public:
    int rob(TreeNode* root) {
        auto r = dfs(root);
        return max(r.first, r.second);
    }
};
//<<<END LC337
}

namespace LC662 {
//>>>BEGIN LC662
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        unsigned long long best = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});
        while (!q.empty()) {
            int sz = q.size();
            unsigned long long first = q.front().second, last = first;
            for (int i = 0; i < sz; i++) {
                auto [n, idx] = q.front(); q.pop();
                idx -= first;                       // rebase each level so the index cannot blow up
                last = idx;
                if (n->left)  q.push({n->left,  idx * 2});
                if (n->right) q.push({n->right, idx * 2 + 1});
            }
            best = max(best, last + 1);
        }
        return (int)best;
    }
};
//<<<END LC662
}

namespace LC173 {
//>>>BEGIN LC173
class BSTIterator {
    stack<TreeNode*> st;
    void pushLeft(TreeNode* n) { while (n) { st.push(n); n = n->left; } }
public:
    // This is the iterative inorder traversal, paused between iterations.
    // Amortised O(1) per call, O(h) space.
    BSTIterator(TreeNode* root) { pushLeft(root); }

    int next() {
        TreeNode* n = st.top(); st.pop();
        pushLeft(n->right);
        return n->val;
    }

    bool hasNext() { return !st.empty(); }
};
//<<<END LC173
}

namespace LC1448 {
//>>>BEGIN LC1448
class Solution {
    int count = 0;
    // Top-down: carry the maximum seen on the path from the root down to here.
    void dfs(TreeNode* n, int mx) {
        if (!n) return;
        if (n->val >= mx) count++;
        mx = max(mx, n->val);
        dfs(n->left, mx);
        dfs(n->right, mx);
    }
public:
    int goodNodes(TreeNode* root) {
        count = 0;
        dfs(root, INT_MIN);
        return count;
    }
};
//<<<END LC1448
}

// ============================================================================
// TESTS — every solution above is exercised here.
// ============================================================================
string nextDump(Node* root) {          // level-by-level walk using only the next pointers
    string s;
    for (Node* lm = root; lm; lm = lm->left) {
        for (Node* n = lm; n; n = n->next) { s += to_string(n->val); if (n->next) s += ","; }
        s += "#";
    }
    return s;
}

int main() {
    // ---------------- Tier 1 ----------------
    {
        LC94::Solution s;
        TreeNode* t = build({1, NUL, 2, 3});
        check("94 inorder recursive", vecDump(s.inorderTraversal(t)), "[1,3,2]");
        check("94 inorder iterative", vecDump(s.inorderIterative(t)), "[1,3,2]");
        check("94 empty", vecDump(s.inorderTraversal(nullptr)), "[]");
    }
    {
        LC144::Solution s;
        TreeNode* t = build({1, NUL, 2, 3});
        check("144 preorder recursive", vecDump(s.preorderTraversal(t)), "[1,2,3]");
        check("144 preorder iterative", vecDump(s.preorderIterative(t)), "[1,2,3]");
    }
    {
        LC145::Solution s;
        TreeNode* t = build({1, NUL, 2, 3});
        check("145 postorder recursive", vecDump(s.postorderTraversal(t)), "[3,2,1]");
        check("145 postorder iterative", vecDump(s.postorderIterative(t)), "[3,2,1]");
    }
    {
        LC102::Solution s;
        check("102 level order", vvDump(s.levelOrder(build({3,9,20,NUL,NUL,15,7}))),
              "[[3],[9,20],[15,7]]");
        check("102 empty", vvDump(s.levelOrder(nullptr)), "[]");
    }
    {
        LC104::Solution s;
        check("104 max depth", s.maxDepth(build({3,9,20,NUL,NUL,15,7})), 3);
        check("104 empty", s.maxDepth(nullptr), 0);
        check("104 skewed", s.maxDepth(build({1,NUL,2,NUL,3})), 3);
    }
    {
        LC111::Solution s;
        check("111 min depth", s.minDepth(build({3,9,20,NUL,NUL,15,7})), 2);
        check("111 one child chain", s.minDepth(build({2,NUL,3,NUL,4})), 3);
        check("111 bfs variant", s.minDepthBFS(build({2,NUL,3,NUL,4})), 3);
        check("111 empty", s.minDepth(nullptr), 0);
    }
    {
        LC226::Solution s;
        check("226 invert", levelDump(s.invertTree(build({4,2,7,1,3,6,9}))), "[4,7,2,9,6,3,1]");
        check("226 empty", levelDump(s.invertTree(nullptr)), "[]");
    }
    {
        LC100::Solution s;
        check("100 same", s.isSameTree(build({1,2,3}), build({1,2,3})), true);
        check("100 different shape", s.isSameTree(build({1,2}), build({1,NUL,2})), false);
        check("100 both empty", s.isSameTree(nullptr, nullptr), true);
    }
    {
        LC101::Solution s;
        check("101 symmetric", s.isSymmetric(build({1,2,2,3,4,4,3})), true);
        check("101 not symmetric", s.isSymmetric(build({1,2,2,NUL,3,NUL,3})), false);
    }
    {
        LC112::Solution s;
        TreeNode* t = build({5,4,8,11,NUL,13,4,7,2,NUL,NUL,NUL,1});
        check("112 has path", s.hasPathSum(t, 22), true);
        check("112 no path", s.hasPathSum(t, 100), false);
        check("112 empty", s.hasPathSum(nullptr, 0), false);
    }
    {
        LC543::Solution s;
        check("543 diameter", s.diameterOfBinaryTree(build({1,2,3,4,5})), 3);
        check("543 two nodes", s.diameterOfBinaryTree(build({1,2})), 1);
    }
    {
        LC110::Solution s;
        check("110 balanced", s.isBalanced(build({3,9,20,NUL,NUL,15,7})), true);
        check("110 unbalanced", s.isBalanced(build({1,2,2,3,3,NUL,NUL,4,4})), false);
        check("110 empty", s.isBalanced(nullptr), true);
    }

    // ---------------- Tier 2 ----------------
    {
        LC700::Solution s;
        TreeNode* t = build({4,2,7,1,3});
        check("700 found", levelDump(s.searchBST(t, 2)), "[2,1,3]");
        check("700 absent", levelDump(s.searchBST(t, 5)), "[]");
    }
    {
        LC701::Solution s;
        check("701 insert", levelDump(s.insertIntoBST(build({4,2,7,1,3}), 5)), "[4,2,7,1,3,5]");
        check("701 into empty", levelDump(s.insertIntoBST(nullptr, 9)), "[9]");
    }
    {
        LC450::Solution s;
        check("450 delete two children",
              levelDump(s.deleteNode(build({5,3,6,2,4,NUL,7}), 3)), "[5,4,6,2,null,null,7]");
        check("450 delete leaf",
              levelDump(s.deleteNode(build({5,3,6,2,4,NUL,7}), 2)), "[5,3,6,null,4,null,7]");
        check("450 delete absent",
              levelDump(s.deleteNode(build({5,3,6,2,4,NUL,7}), 0)), "[5,3,6,2,4,null,7]");
    }
    {
        LC98::Solution s;
        check("98 valid", s.isValidBST(build({2,1,3})), true);
        check("98 grandchild violation", s.isValidBST(build({5,1,4,NUL,NUL,3,6})), false);
        check("98 INT_MAX node", s.isValidBST(build({2147483647})), true);
        check("98 equal values", s.isValidBST(build({2,2,2})), false);
    }
    {
        LC230::Solution s;
        TreeNode* t = build({5,3,6,2,4,NUL,NUL,1});
        check("230 k=3", s.kthSmallest(t, 3), 3);
        check("230 k=1", s.kthSmallest(t, 1), 1);
    }
    {
        LC235::Solution s;
        TreeNode* t = build({6,2,8,0,4,7,9,NUL,NUL,3,5});
        check("235 split", s.lowestCommonAncestor(t, find(t,2), find(t,8))->val, 6);
        check("235 ancestor is p", s.lowestCommonAncestor(t, find(t,2), find(t,4))->val, 2);
    }
    {
        LC236::Solution s;
        TreeNode* t = build({3,5,1,6,2,0,8,NUL,NUL,7,4});
        check("236 split", s.lowestCommonAncestor(t, find(t,5), find(t,1))->val, 3);
        check("236 ancestor is p", s.lowestCommonAncestor(t, find(t,5), find(t,4))->val, 5);
    }
    {
        LC108::Solution s;
        vector<int> a{-10,-3,0,5,9};
        check("108 sorted array to BST", levelDump(s.sortedArrayToBST(a)),
              "[0,-10,5,null,-3,null,9]");
    }
    {
        LC105::Solution s;
        vector<int> pre{3,9,20,15,7}, in{9,3,15,20,7};
        check("105 pre+in", levelDump(s.buildTree(pre, in)), "[3,9,20,null,null,15,7]");
    }
    {
        LC106::Solution s;
        vector<int> in{9,3,15,20,7}, post{9,15,7,20,3};
        check("106 in+post", levelDump(s.buildTree(in, post)), "[3,9,20,null,null,15,7]");
    }
    {
        LC103::Solution s;
        check("103 zigzag", vvDump(s.zigzagLevelOrder(build({3,9,20,NUL,NUL,15,7}))),
              "[[3],[20,9],[15,7]]");
    }
    {
        LC199::Solution s;
        check("199 right view", vecDump(s.rightSideView(build({1,2,3,NUL,5,NUL,4}))), "[1,3,4]");
        check("199 empty", vecDump(s.rightSideView(nullptr)), "[]");
    }
    {
        LC113::Solution s;
        TreeNode* t = build({5,4,8,11,NUL,13,4,7,2,NUL,NUL,5,1});
        check("113 path sum II", vvDump(s.pathSum(t, 22)), "[[5,4,11,2],[5,8,4,5]]");
        check("113 none", vvDump(s.pathSum(t, 1000)), "[]");
    }
    {
        LC129::Solution s;
        check("129 sum root to leaf", s.sumNumbers(build({1,2,3})), 25);
        check("129 bigger", s.sumNumbers(build({4,9,0,5,1})), 1026);
    }
    {
        LC114::Solution s;
        TreeNode* t = build({1,2,5,3,4,NUL,6});
        s.flatten(t);
        check("114 flatten", levelDump(t), "[1,null,2,null,3,null,4,null,5,null,6]");
    }
    {
        LC116::Solution s;
        Node* t = buildN({1,2,3,4,5,6,7});
        s.connect(t);
        check("116 next pointers", nextDump(t), "1#2,3#4,5,6,7#");
    }

    // ---------------- Tier 3 ----------------
    {
        LC124::Solution s;
        check("124 max path sum", s.maxPathSum(build({-10,9,20,NUL,NUL,15,7})), 42);
        check("124 all negative", s.maxPathSum(build({-3})), -3);
        check("124 simple", s.maxPathSum(build({1,2,3})), 6);
    }
    {
        LC297::Codec c;
        TreeNode* t = build({1,2,3,NUL,NUL,4,5});
        check("297 round trip", levelDump(c.deserialize(c.serialize(t))), "[1,2,3,null,null,4,5]");
        check("297 empty", levelDump(c.deserialize(c.serialize(nullptr))), "[]");
    }
    {
        LC437::Solution s;
        TreeNode* t = build({10,5,-3,3,2,NUL,11,3,-2,NUL,1});
        check("437 path sum III", s.pathSum(t, 8), 3);
        check("437 empty", s.pathSum(nullptr, 0), 0);
    }
    {
        LC572::Solution s;
        check("572 is subtree", s.isSubtree(build({3,4,5,1,2}), build({4,1,2})), true);
        check("572 not subtree",
              s.isSubtree(build({3,4,5,1,2,NUL,NUL,NUL,NUL,0}), build({4,1,2})), false);
    }
    {
        LC863::Solution s;
        TreeNode* t = build({3,5,1,6,2,0,8,NUL,NUL,7,4});
        vector<int> got = s.distanceK(t, find(t,5), 2);
        sort(got.begin(), got.end());
        check("863 distance K", vecDump(got), "[1,4,7]");
        check("863 k=0", vecDump(s.distanceK(t, find(t,5), 0)), "[5]");
    }
    {
        LC99::Solution s;
        TreeNode* t = build({1,3,NUL,NUL,2});
        s.recoverTree(t);
        check("99 recover adjacent", levelDump(t), "[3,1,null,null,2]");
        TreeNode* u = build({3,1,4,NUL,NUL,2});
        s.recoverTree(u);
        check("99 recover distant", levelDump(u), "[2,1,4,null,null,3]");
    }
    {
        LC337::Solution s;
        check("337 house robber III", s.rob(build({3,2,3,NUL,3,NUL,1})), 7);
        check("337 second shape", s.rob(build({3,4,5,1,3,NUL,1})), 9);
    }
    {
        LC662::Solution s;
        check("662 max width", s.widthOfBinaryTree(build({1,3,2,5,3,NUL,9})), 4);
        check("662 single", s.widthOfBinaryTree(build({1})), 1);
    }
    {
        TreeNode* t = build({7,3,15,NUL,NUL,9,20});
        LC173::BSTIterator it(t);
        string s;
        while (it.hasNext()) { if (!s.empty()) s += ","; s += to_string(it.next()); }
        check("173 BST iterator", s, "3,7,9,15,20");
    }
    {
        LC1448::Solution s;
        check("1448 good nodes", s.goodNodes(build({3,1,4,3,NUL,1,5})), 4);
        check("1448 root only counts", s.goodNodes(build({3,3,NUL,4,2})), 3);
    }

    cout << "\n" << OKS << " passed, " << FAILS << " failed\n";
    return FAILS ? 1 : 0;
}
