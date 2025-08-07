#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
struct matrix{
    vector<vector<long long>> m;
    friend matrix operator *(matrix a, matrix b) {
        matrix c;
        c.m = {{0, 0}, {0, 0}};
        for(int i=0; i<2; i++) {
            for(int j=0; j<2; j++) {
                for(int k=0; k<2; k++) {
                    c.m[i][j] = (c.m[i][j] + (a.m[i][k] * b.m[k][j]) % mod) % mod;
                }
            }
        }
        return c;
    };
};
matrix fast_pow(matrix a, int n) {
    if(n == 1) return a;
    if(n == 0) {
        matrix identity;
        identity.m = {{1, 0}, {0, 1}};
        return identity;
    }
    if(n % 2 == 0) {
        matrix tmp = fast_pow(a, n / 2);
        return tmp * tmp;
    }
    else {
        return a * fast_pow(a, n - 1);
    }
}
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    long long x[3], a, b, n;
    cin >> x[1] >> x[2] >> a >> b >> n;
    if(n <= 2) {
        cout << x[n] % mod << '\n';
        return 0;
    }
    matrix A;
    A.m = {{b, a}, {1, 0}};
    matrix ans = fast_pow(A, n - 2);
    cout << (ans.m[0][0] * x[2] % mod + ans.m[0][1] * x[1] % mod) % mod << '\n';
    return 0;
}
