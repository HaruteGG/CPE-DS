#include<bits/stdc++.h>
using namespace std;
const int A = 998244353;
const int N = 5005;
const int mod = 1e9 + 7;
int power[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    power[0] = 1;
    for(int i = 1; i < N; i++) {
        power[i] = 1LL * power[i - 1] * A % mod;
    }
    int n, q;
    cin >> n >> q;
    vector<int> hsh(n);
    vector<int> sz(n);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sz[i] = (int) s.size();
        for(char c : s) {
            hsh[i] = (1LL * hsh[i] * A + c) % mod;
        }
    }
    while(q--) {
        char type;
        int i, j;
        cin >> type >> i >> j;
        i--, j--;
        if(type == 'E') {
            if(hsh[i] == hsh[j] && sz[i] == sz[j]) {
                cout << "Y\n";
            }
            else {
                cout << "N\n";
            }
        }
        else {
            hsh[i] = (1LL * hsh[i] * power[sz[j]] + hsh[j]) % mod;
            sz[i] += sz[j];
        }
    }
    return 0;
}
