#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct merge_sort_tree {
public:
    //建merge_sort_tree
    merge_sort_tree() : n(0) {}
    explicit merge_sort_tree(const vector<T>& val) : n(val.size()), tree(val.size() * 2) {
        for(int i=0; i<n; i++) {
            tree[n + i] = {val[i]};
        }
        for(int i=n - 1; i >= 0; i--) {
            merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(), tree[2 * i + 1].end(), back_inserter(tree[i]));
        }
    }
    //查詢
    int count_less(int l, int r, T x) const {
        int ans = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                ans += lower_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
                l++;
            }
            if(r & 1) {
                r--;
                ans += lower_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
            }
        }
        return ans;
    }
    int count_less_equal(int l, int r, T x) const {
        int ans = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                ans += upper_bound(tree[l].begin(), tree[l].end(), x) - tree[l].begin();
                l++;
            }
            if(r & 1) {
                r--;
                ans += upper_bound(tree[r].begin(), tree[r].end(), x) - tree[r].begin();
            }
        }
        return ans;
    }
    int count_greater(int l, int r, T x) const {
        return r - l - count_less_equal(l, r, x);
    }
    int count_greater_equal(int l, int r, T x) const {
        return r - l - count_less(l, r, x);
    }
 
private:
    int n;
    vector<vector<T>> tree;
};
 
 
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for(int i=0; i<n; i++) {
        cin >> arr[i];
    }
    merge_sort_tree<int> tree(arr);
    for(int i=0; i<q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        int ans = tree.count_less(l, r + 1, x);
        cout << ans << "\n";
    }
}
