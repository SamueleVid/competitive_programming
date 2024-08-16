#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;
const int MAXN = 100 + 3;
ll dp[4][MAXN][MAXN][MAXN]; // prev, a, b, c

ll rec(int prev, int a, int b, int c) {
    vector<int> v = {a, b, c};
    sort(v.begin(), v.end());
    if (v[2] > v[1] + v[2] + 1) return 0;
    if (dp[prev][a][b][c] != -1) return dp[prev][a][b][c];

    ll res = 0;
    if (prev != 0 && a > 0) res += rec(0, a - 1, b, c), res %= MOD;
    if (prev != 1 && b > 0) res += rec(1, a, b - 1, c), res %= MOD;
    if (prev != 2 && c > 0) res += rec(2, a, b, c - 1), res %= MOD;

    dp[prev][a][b][c] = res;
    return res;
}

int c_zero(int A, int B) {
    if (A < 0 || B < 0) return 0;
    if (A == B) {
        return 2;
    }
    if (max(A, B) == min(A, B) + 1) {
        return 1;
    }
    return 0;
}

void solve() {
    int A, B, C; cin >> A >> B >> C;

    if (C == 0) {
        cout << c_zero(A, B) << '\n';
        return;
    }
 
    for (int i = 0; i <= 3; i ++) {
        for (int a = 0; a <= A; a ++) {
            for (int b = 0; b <= B; b ++) {
                for (int c = 0; c <= C; c ++) {
                    dp[i][a][b][c] = -1;
                }
            }
        }
    }

    for (int i = 0; i <= 3; i ++) dp[i][0][0][0] = 1;

    cout << rec(3, A, B, C) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
