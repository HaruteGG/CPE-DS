#include <bits/stdc++.h>
using namespace std;
struct mycompare {
    bool operator()(const pair<long long, long long> &a, const pair<long long, long long> &b) {
        if(a.first == b.first) {
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};
int main() {
    ios:: sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, mycompare> v;
    while(t--) {
        int n;
        cin >> n;
        if(n == 1) {
            long long p, q;
            cin >> p >> q;
            v.push({p, q});
        }
        else if(n == 2) {
            pair<long long, long long> vtop = v.top();
            cout << vtop.first << " " << vtop.second << "\n";
            v.pop();
        }
        else {
            long long size = v.size();
            cout << size << "\n";
        }
    }
    return 0;
}
