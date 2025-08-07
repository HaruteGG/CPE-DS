#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int p1 = 31, p2 = 37;
const int m1 = 1e9 + 7, m2 = 1e9 + 9;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string N, H;
    cin >> N >> H;
    int n = N.size();
    int h = H.size();
    if(h < n) return 0;
    set<pair<ll, ll>> sn;
    ll p1_pow = 1, p2_pow = 1;
    for(int i = 0; i < n - 1; i++) {
        p1_pow = (p1_pow * p1) % m1;
        p2_pow = (p2_pow * p2) % m2;
    }
    vector<int> n_freq(26, 0);
    for(auto c : N) n_freq[c - 'a']++;
    vector<int> h_freq(26, 0);
    ll h1 = 0, h2 = 0;
    for(int i = 0; i < n; i++) {
        h_freq[H[i] - 'a']++;
        h1 = (h1 * p1 + (H[i] - 'a' + 1)) % m1;
        h2 = (h2 * p2 + (H[i] - 'a' + 1)) % m2;
    }
    if(n_freq == h_freq) {
        sn.insert({h1, h2});
    }
    for(int i = n; i < h; i++) {
        h_freq[H[i - n] - 'a']--;
        ll old_c_val = (H[i - n] - 'a' + 1);
        h1 = (h1 - old_c_val * p1_pow) % m1;
        h1 = (h1 + m1) % m1; 
        h2 = (h2 - old_c_val * p2_pow) % m2;
        h2 = (h2 + m2) % m2;
        h_freq[H[i] - 'a']++;
        ll new_c_val = (H[i] - 'a' + 1);
        h1 = (h1 * p1 + new_c_val) % m1;
        h2 = (h2 * p2 + new_c_val) % m2;
        if(h_freq == n_freq) {
            sn.insert({h1, h2});
        }
    }
    cout << sn.size() << "\n";
    return 0;
}
