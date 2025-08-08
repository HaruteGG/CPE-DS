#include <bits/stdc++.h>
using namespace std;
 
constexpr int M = 1E9 + 9;
constexpr int A = 998244353;
 
constexpr int N = 2e5 + 5;
 
int power[N];
 
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	power[0] = 1;
	for(int i = 1; i < N; i++) {
		power[i] = 1LL * power[i - 1] * A % M;
	}
	string n, h;
	cin >> n >> h;
	int sn = (int)n.size(), sh = (int)h.size();
	array<int, 26> n_freq = {};
	for(char c : n) {
		n_freq[c - 'a']++;
	}
	vector<int> hsh(sh);
	hsh[0] = h[0];
	for(int i = 1; i < sh; i++) {
		hsh[i] = (1LL * hsh[i - 1] * A + h[i]) % M;
	}
	auto get = [&](int i, int j) -> int {
		if(i == 0) return hsh[j];
		return ((hsh[j] - 1LL * hsh[i - 1] * power[j - i + 1]) % M + M) % M;
	};
	vector<int> matched;
	vector<array<int, 26>> pref(sh + 1);
	for(int i = 0; i < sh; i++) {
		pref[i + 1] = pref[i];
		pref[i + 1][h[i] - 'a']++;
		if(i >= sn - 1) {
			array<int, 26> diff = {};
			for(int j = 0; j < 26; j++) {
				diff[j] = pref[i + 1][j] - pref[i + 1 - sn][j];
			}
			if(diff == n_freq) {
				matched.push_back(get(i - sn + 1, i));
			}
		}
	}
	sort(matched.begin(), matched.end());
	int ans = 0;
	int last = -1;
	for(auto x : matched) {
		if(x == last) {
			continue;	
		}
		ans++;
		last = x;
	}
	cout << ans << '\n';
	return 0;
}
 
