#include<bits/stdc++.h>
using namespace std;
struct subproblem {
    int pre_s, pre_e, in_s, in_e, post_s, post_e;
};
bool solve() {
    int n;
    if(!(cin >> n)) return false;
    string d;
    getline(cin, d);
    
    if(n == 0) {
        for(int i=0; i<3; i++) getline(cin, d);
        return true;
    }
    
    vector<string> preorder(n), inorder(n), postorder(n);
    string line;
    
    getline(cin, line); 
    stringstream ss_pre(line);
    for(int i=0; i<n; i++) ss_pre >> preorder[i];

    getline(cin, line);
    stringstream ss_in(line);
    for(int i=0; i<n; i++) ss_in >> inorder[i];

    getline(cin, line);
    stringstream ss_post(line);
    for(int i=0; i<n; i++) ss_post >> postorder[i];

    map<string, int> inorder_map;
    for(int i=0; i<n; i++) inorder_map[inorder[i]] = i;

    stack<subproblem> s;
    s.push({0, n-1, 0, n-1, 0, n-1});

    while(!s.empty()) {
        subproblem p = s.top();
        s.pop();
        
        if(preorder[p.pre_s] != postorder[p.post_e]) {
            return false;
        }
        
        string root_val = preorder[p.pre_s];

        if(p.pre_s == p.pre_e) {
            if(root_val == inorder[p.in_s] && root_val == postorder[p.post_s]) {
                continue;
            } else {
                return false;
            }
        }
        if(inorder_map.find(root_val) == inorder_map.end()) {
            return false;
        }
        int in_root_idx = inorder_map.at(root_val);
        if(in_root_idx < p.in_s || in_root_idx > p.in_e) {
            return false;
        }

        int left_subtree_size = in_root_idx - p.in_s;
        int right_subtree_size = p.in_e - in_root_idx;
        
        if(right_subtree_size > 0) {
            s.push({
                p.pre_s + left_subtree_size + 1, p.pre_e, 
                in_root_idx + 1, p.in_e, 
                p.post_s + left_subtree_size , p.post_e - 1
            });
        }
        
        if(left_subtree_size > 0) {
            s.push({
                p.pre_s + 1, p.pre_s + left_subtree_size,
                p.in_s, in_root_idx - 1,
                p.post_s, p.post_s + left_subtree_size - 1
            });
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        if(solve()) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
    return 0;
}
