#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode *buildTree(vector<int>& preorder, vector<int>& inorder, map<int, int>& inorder_map) {
    if(preorder.empty() || inorder.empty()) return nullptr;
    stack<TreeNode*> s;
    TreeNode* root = new TreeNode(preorder[0]);
    s.push(root);
    int inorder_idx = 0;
    for(int i=1; i<preorder.size(); i++) {
        TreeNode* node_current = new TreeNode(preorder[i]);
        TreeNode* parent = s.top();
        if(parent->val != inorder[inorder_idx]) {
            parent->left = node_current;
        } else {
            while(!s.empty() && s.top()->val == inorder[inorder_idx]) {
                parent = s.top();
                s.pop();
                inorder_idx++;
            }
            parent->right = node_current;
        }
        s.push(node_current);
    }
    return root;
}
void getPostorder(TreeNode* root, vector<int>& postorder) {
    if(root == nullptr) return;
    getPostorder(root->left, postorder);
    getPostorder(root->right, postorder);
    postorder.push_back(root->val);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> preorder(n), inorder(n);
    map<int, int> inorder_map;
    for(int i=0; i<n; i++) cin >> preorder[i];
    for(int i=0; i<n; i++) {
        cin >> inorder[i];
        inorder_map[inorder[i]] = i;
    }
    TreeNode* root = buildTree(preorder, inorder, inorder_map);
    vector<int> postorder;
    getPostorder(root, postorder);
    for(int i=0; i<postorder.size(); i++) {
        if(i == 0) cout << postorder[i];
        else cout << " " << postorder[i];
    }
}
