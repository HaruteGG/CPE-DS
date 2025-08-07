#include<bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> parent;
    vector<int> sz;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        sz.assign(n, 1);
    }
    int find(int a) {
        if(parent[a] == a) return a;
        return parent[a] = find(parent[a]);
    }
    void unite(int a, int b) {
        int roota = find(a);
        int rootb = find(b);
        if(roota != rootb) {
            if(sz[roota] < sz[rootb]) {
                swap(roota, rootb);
            }
            parent[rootb] = roota;
            sz[roota] += sz[rootb];
        }
    }
};
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    DSU dsu(26);
    int ans = 0;
    for(int i = 0; i < n/2; i++) {
        int c1 = s[i] - 'a';
        int c2 = s[n - i - 1] - 'a';
        int root1 = dsu.find(c1);
        int root2 = dsu.find(c2);
        if(root1 != root2) {
            dsu.unite(root1, root2);
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
