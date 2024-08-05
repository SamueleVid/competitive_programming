#include <bits/stdc++.h>
using namespace std;

void solve() {
    int K; cin >> K;
    string S; cin >> S;
    vector<int> group;
    for (auto x : S) {
        if (x == '(') {
            group.push_back(0);
            continue;
        }
        if (x == '&' || x == ')' || x == '^') continue;
        group.back() |= 1 << (x - 'a');
    }
    
    // "counting subsets" section from handbook
    bool sums[1 << K];
    fill(sums, sums + (1 << K), 0);
    for (auto x : group) sums[x] ^= 1;
    
    for (int i = 0; i < K; i ++) {
        for (int j = 0; j < (1 << K); j ++) {
            if (j & (1 << i)) sums[j] ^= sums[j ^ (1 << i)];
        }
    }

    int tot = 0;
    for (int i = 0; i < (1 << K); i ++) {
        tot += sums[i];
    }
    
    cout << tot << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
