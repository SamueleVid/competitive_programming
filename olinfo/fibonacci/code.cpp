#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXM = 1e9 + 10;
map<pair<int, int>, ll> dp;
map<int, ll> res;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    dp[{1, 2}] = 1;
    
    for (auto [n, v] : dp) {
        auto [a, b] = n;
        if (b + b < MAXM) dp[{b, b + b}] += dp[{a, b}];
        if (a + b < MAXM) dp[{b, a + b}] += dp[{a, b}];
    }

    for (auto [n, v] : dp) {
        auto [a, b] = n;
        res[b] += v;
    }

    while (T --) {
        int M; cin >> M;
        cout << res[M] << '\n';
    }
}
