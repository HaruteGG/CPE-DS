#include<bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    set<int> s;
    int n, L;
    cin >> n >> L;
    s.insert(0);
    s.insert(L);
    vector<int> pos(n);
    for(int i=0; i<n; i++) {
        int poss, ord;
        cin >> poss >> ord;
        pos[ord-1] = poss;
    }
    long long ans = 0;
    for(int i=0; i<n; i++) {
        ans += (*s.upper_bound(pos[i]) - *(prev(s.upper_bound(pos[i]))));
        s.insert(pos[i]);
    }
    cout << ans;
    return 0;
}
