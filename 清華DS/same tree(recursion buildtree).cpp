#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    string val;
    TreeNode *left, *right;
    TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* build(vector<string>& preorder, int pre_start, int pre_end, vector<string>& inorder, int in_start, int in_end, map<string, int>& inorder_map){
    if(pre_start > pre_end || in_start > in_end) return nullptr;
    string root_val = preorder[pre_start];
    TreeNode* root = new TreeNode(root_val);
    int in_root_index = inorder_map.at(root_val);
    int left_subtree_size = in_root_index - in_start;
    root->left = build(preorder, pre_start + 1, pre_start + left_subtree_size, inorder, in_start, in_root_index - 1, inorder_map);
    root->right = build(preorder, pre_start + left_subtree_size + 1, pre_end, inorder, in_root_index + 1, in_end, inorder_map);
    return root;
}
TreeNode* buildTree(vector<string>& preorder, vector<string>& inorder, map<string, int>& inorder_map) {
    if(preorder.empty() || inorder.empty()) return nullptr;
    return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inorder_map);
}
void getPostorderTraversal(TreeNode* root, vector<string>& result) {
    if(root == nullptr) return;
    getPostorderTraversal(root->left, result);
    getPostorderTraversal(root->right, result);
    result.push_back(root->val);
}
void deleteTree(TreeNode* root) {
    if(root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
vector<string> readline() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string s;
    vector<string> result;
    while(ss >> s) {
        result.push_back(s);
    }
    return result;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    string dummy;
    getline(cin, dummy);
    while(t--) {
        int m;
        cin >> m;
        getline(cin, dummy);
        if(m == 0) {
            string empty_line;
            getline(cin, empty_line);
            getline(cin, empty_line);
            getline(cin, empty_line);
            cout << "yes\n";
            continue;
        }
        vector<string> preorder = readline();
        vector<string> inorder = readline();
        vector<string> postorder = readline();
        map<string, int> inorder_map;
        for(int i=0; i<m; i++) {
            inorder_map[inorder[i]] = i;
        }
        TreeNode* root = buildTree(preorder, inorder, inorder_map);
        vector<string> re_postorder;
        getPostorderTraversal(root, re_postorder);
        if(re_postorder == postorder) {
            cout << "yes\n";
        } else{
            cout << "no\n";
        }
        deleteTree(root);
    }
    return 0;
}
