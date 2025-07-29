#include<bits/stdc++.h>
using namespace std;
vector<int> segment_tree;
int segment_tree_range;

void build_segment_tree(int root_idx, int current_L, int current_R) {
    if(current_L == current_R) {
        segment_tree[root_idx] = 0;
        return;
    }
    int mid = current_L + (current_R - current_L) / 2;
    build_segment_tree(2 * root_idx, current_L, mid);
    build_segment_tree(2 * root_idx + 1, mid + 1, current_R);
    segment_tree[root_idx] = segment_tree[2 * root_idx] + segment_tree[2 * root_idx + 1];
}
void update_segment_tree(int root_idx, int current_L, int current_R, int target_idx, int val) {
    if(current_L == current_R) {
        segment_tree[root_idx] = val;
        return;
    }
    int mid = current_L + (current_R - current_L) / 2;
    if(target_idx <= mid) {
        update_segment_tree(2 * root_idx, current_L, mid, target_idx, val);
    }
    else {
        update_segment_tree(2 * root_idx + 1, mid + 1, current_R, target_idx, val);
    }
    segment_tree[root_idx] = segment_tree[2 * root_idx] + segment_tree[2 * root_idx + 1];
}

int query_segment_tree(int root_idx, int current_L, int current_R, int query_L, int query_R) {
    if(query_L <= current_L && current_R <= query_R) {
        return segment_tree[root_idx];
    }
    if(current_R < query_L || current_L > query_R) {
        return 0;
    }
    int mid = current_L + (current_R - current_L) / 2;
    return query_segment_tree(2 * root_idx, current_L, mid, query_L, query_R) + 
            query_segment_tree(2 * root_idx + 1, mid + 1, current_R, query_L, query_R);
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    
    vector<int> arr(n);
    vector<vector<pair<int, int>>> queries(n);
    segment_tree_range = n;
    segment_tree.resize(4 * n);
    build_segment_tree(1, 0, segment_tree_range - 1);

    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    for(int i=0; i<q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries[b].push_back({a, i});
    }

    map<int, int> last_index;
    vector<int> solution(q, -1);
    for(int i=0; i<n; i++) {
        int val = arr[i];
        if(last_index.count(val) > 0) {
            update_segment_tree(1, 0, segment_tree_range - 1, last_index[val], 0);
        }
        last_index[val] = i;
        update_segment_tree(1, 0, segment_tree_range - 1, i, 1);
        for(auto &qr : queries[i]) {
            int query_left = qr.first;
            int query_idx = qr.second;
            solution[query_idx] = query_segment_tree(1, 0, segment_tree_range - 1, query_left, i);
        }
    }
    for(auto &ans : solution) {
        cout << ans << "\n";
    }
}
