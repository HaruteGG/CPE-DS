#include<bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    multiset<long long> s;
    map<int, int> m;
    long long n;
    cin >> n;
    while(n--) {
        char c;
        cin >> c;
        long long x;
        if(c == 'I') {
            cin >> x;
            s.insert(x);
            m[x]++;
            cout << m.size() << '\n';
        } else if(c == 'D') {
            cin >> x;
            if(s.find(x) != s.end()) {
                s.erase(s.find(x));
                m[x]--;
                if(m[x] == 0) {
                    m.erase(x);
                }
            }
            cout << m.size() << '\n';
        } else if(c == 'C') {
            cin >> x;
            if(s.find(x) == s.end()) cout << "0\n";
            else cout << m[x] << '\n';
        } else if(c == 'L') {
            cin >> x;
            auto it = s.lower_bound(x);
            if(it == s.end()) cout << "-1\n";
            else cout << *it << '\n';
        } else if(c == 'U') {
            cin >> x;
            auto it = s.upper_bound(x);
            if(it == s.end()) cout << "-1\n";
            else cout << *it << '\n';
        }
    }
    return 0;
}
