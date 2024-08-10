#include <bits/stdc++.h>
using namespace std;
const int ALPHA = 26;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    string S; cin >> S;
    int dp[N][ALPHA];
    for (int i = 0; i < ALPHA; i ++) dp[0][i] = 1;
    dp[0][S[0] - 'a'] = 0;
    for (int i = 1; i < N; i ++) for (int j = 0; j < ALPHA; j ++) dp[i][j] = 1e9;

    int graph[N][ALPHA];

    for (int i = 1; i < N; i ++) {
        for (int j = 0; j < ALPHA; j ++) {
            for (int z = 0; z <= j; z ++) {
                int v = dp[i - 1][z] + (j == S[i] - 'a' ? 0 : 1);
                if (v < dp[i][j]) {
                    dp[i][j] = v;
                    graph[i][j] = z;
                }
            }
        }
    }

    int res = 1e9;
    int idx = 0;
    for (int i = 0; i < ALPHA; i ++) {
        if (dp[N - 1][i] < res) {
            res = dp[N - 1][i];
            idx = i;
        }
    }

    vector<pair<int,char>> path;
    for (int i = N - 1; i >= 0; i --) {
        if (S[i] - 'a' != idx) path.push_back({i, 'a' + idx});
        idx = graph[i][idx];
    }
    reverse(path.begin(), path.end());

    cout << res << '\n';
    for (auto [i, c] : path) cout << i << " " << c << '\n';
}
