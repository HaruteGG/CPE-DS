#include <bits/stdc++.h>
using namespace std;
vector<long long> tree;
vector<long long> depot;
void build(int node, int start, int end) {
    if(start == end) {
        tree[node] = depot[start];
    }
    else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node],  tree[2 * node + 1]);
    }
}
int query(int node, int start, int end, long long shipp) {
    if(tree[node] < shipp) return 0;
    if(start == end) return start + 1;
    int mid = (start + end) / 2;
    int result = 0;
    if(tree[2 * node] >= shipp) {
        result = query(2 * node, start, mid, shipp);
    }
    if(result == 0 && tree[2 * node + 1] >= shipp) {
        result = query(2 * node + 1, mid + 1, end, shipp);
    }
    return result;
}
void update(int node, int start, int end, int idx, long long shipp) {
    if(start == end) {
        tree[node] -= shipp;
        return;
    }
    int mid = (start + end) / 2;
    if(start <= idx && idx <= mid) {
        update(2 * node, start, mid, idx, shipp);
    }
    else {
        update(2 * node + 1, mid + 1, end, idx, shipp);
    }
    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}
int main() {
    int n, m;
    cin >> n >> m;
    depot.resize(n);
    for(int i = 0; i < n; i++) cin >> depot[i];
    tree.resize(4 * n);
    build(1, 0, n - 1);
    for(int i = 0; i < m; i++) {
        long long shipp;
        cin >> shipp;
        int depot_idx = query(1, 0, n - 1, shipp);
        cout << depot_idx << " ";
        if(depot_idx != 0) {
            update(1, 0, n - 1, depot_idx - 1, shipp);
        }
    }
    return 0;
}
