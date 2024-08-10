#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, R, T, L; cin >> N >> R >> T >> L;
    vector<int> X(N + 2);
    for (int i = 1; i <= N; i ++) cin >> X[i];
    X[0] = 0;
    X[N + 1] = L;
    
    int dp[R + 1][N + 2];
    for (int i = 0; i <= R; i ++) {
        for (int j = 0; j < N + 2; j ++) {
            dp[i][j] = 1e9;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i < N + 2; i ++) {
        int strada = X[i] - X[i - 1];
        int time = 0;

        if ((dp[0][i - 1] / T) % 2) {
            time += T - (dp[0][i - 1] % T);
        }

        dp[0][i] = dp[0][i - 1] + strada + time;
    }
    for (int j = 1; j <= R; j ++) {
        for (int i = 1; i < N + 2; i ++) {
            int strada = X[i] - X[i - 1];
            int time = 0;
            
            if ((dp[j][i - 1] / T) % 2 == 1) {
                time += T - (dp[j][i - 1] % T);
            }
            
            dp[j][i] = dp[j][i - 1] + strada + time;
            dp[j][i] = min(dp[j][i], dp[j - 1][i - 1] + strada);
        }
    }

    int res = dp[0][N + 1];
    for (int i = 1; i <= R; i ++) res = min(res, dp[i][N + 1]);
    cout << res << '\n';
}
