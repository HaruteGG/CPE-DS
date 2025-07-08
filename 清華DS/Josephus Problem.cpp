#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;

    if (n <= 0) {
        return 0;
    }

    // 根據題目要求，每次數 2 個人
    int k = 2;

    vector<int> child;
    for(int i = 1; i <= n; i++) {
        child.push_back(i);
    }

    vector<int> ans;
    int current_pos = 0;

    // 迴圈直到所有人都被移除
    while(!child.empty()) {
        int size = child.size();
        // 計算下一個要移除的元素的索引
        // 從目前位置向前走 k-1 步，並用模運算處理環形邊界
        current_pos = (current_pos + k - 1) % size;

        // 記錄被移除的人
        ans.push_back(child[current_pos]);

        // 從圈中移除這個人
        child.erase(child.begin() + current_pos);
    }

    for(int i=0; i<ans.size(); i++) {
        cout << ans[i];
        if(i < ans.size() - 1) cout << " ";
    }
    cout << endl;
    return 0;
}
