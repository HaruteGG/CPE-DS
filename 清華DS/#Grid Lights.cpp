#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	vector<int> row_click(n), col_click(n);
	for(int i=0; i<q; i++) {
		int r, c;
		cin >> r >> c;
		row_click[r-1]++;
		col_click[c-1]++;
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(j != 0) cout << " ";
			if((row_click[i] + col_click[j]) % 2 == 0) {
				cout << 0; 
			}else {
				cout << 1;
			}
		}
		cout << "\n";
	}
	return 0;
}
