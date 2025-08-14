#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<int> deg(n);
	for(int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
      	a--, b--;
		g[a].push_back(b);
		deg[b]++;
	}
	queue<int> que;
	for(int i=0; i < n; i++) {
		if(deg[i] == 0) que.push(i);
	}
	vector<int> ans;
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		ans.push_back(u);
		for(auto i : g[u]) {
			deg[i]--;
			if(deg[i] == 0) {
				que.push(i);
			}
		}
	}
	cout << (static_cast<int>(ans.size()) == n ? "YES" : "NO") << "\n";
	return 0;
}
