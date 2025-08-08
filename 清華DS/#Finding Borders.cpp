#include<bits/stdc++.h>
using namespace std;
const int A = 999999937;
const int M = 1e9+7;
const int N = 1e6+5;
int power[N];
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string s;
    cin >> s;
    power[0] = 1;
    for(int i = 1; i < N; i++) {
        power[i] = 1LL * power[i - 1] * A % M;
    }
    int n = (int)s.size();
    vector<int> hsh(n);
    hsh[0] = s[0];
    for(int i = 1; i < n; i++) {
        hsh[i] = (1LL * hsh[i - 1] * A + s[i]) % M;
    }
    auto get = [&](int i, int j) -> int {
        if(i == 0) return hsh[j];
        return ((hsh[j] - 1LL * hsh[i - 1] * power[j - i + 1]) % M + M) % M;
    };
    vector<int> ans;
    for(int i = 1; i < n; i++) {
        if(get(0, i - 1) == get(n - i, n - 1)) {
            ans.push_back(i);
        }
    }

    for(auto x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
    return 0;
}
