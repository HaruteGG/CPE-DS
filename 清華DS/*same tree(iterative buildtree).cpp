#include<bits/stdc++.h>
using namespace std;
struct TreeNode {
    string val;
    TreeNode *left, *right;
    TreeNode(string x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* buildTree(vector<string>& preorder, vector<string>& inorder, map<string, int>& inorder_map){
    if(preorder.empty()) return nullptr;

    stack<TreeNode*> s; // use stack to save parent nodes
    TreeNode* root = new TreeNode(preorder[0]);
    s.push(root);
    int inorder_idx = 0;
    for(int i=1; i<preorder.size(); i++) {
        TreeNode* node_current = new TreeNode(preorder[i]);
        TreeNode* parent = s.top();
        
        if(parent->val != inorder[inorder_idx]) {
            parent->left = node_current;
        }else {
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
