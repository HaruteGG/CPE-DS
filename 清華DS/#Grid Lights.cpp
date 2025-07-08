#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> row_click(n, 0);
    vector<int> col_click(n, 0);
    vector<vector<int>> light(n, vector<int>(n, 0));
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        row_click[a-1]++;
        col_click[b-1]++;
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(row_click[i] % 2 == 0 && col_click[j] % 2 == 0) {
                light[i][j] = 0;
            }else if(row_click[i] % 2 == 1 && col_click[j] % 2 == 0) {
                light[i][j] = 1;
            }else if(row_click[i] % 2 == 0 && col_click[j] % 2 == 1) {
                light[i][j] = 1;
            }else {
                light[i][j] = 0;
            }
            cout << light[i][j];
            if(j < n-1) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}
