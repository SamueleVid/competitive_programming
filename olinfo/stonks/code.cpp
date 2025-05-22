#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, K; cin >> N >> K;
    vector<vector<double>> B(N, vector<double>(K));
    vector<vector<double>> S(N, vector<double>(K));

    for (int i = 0; i < N; i ++) {
        for (int k = 0; k < K; k ++) {
            cin >> B[i][k] >> S[i][k];
        }
    }

    double dp = 1;
    vector<double> max_ps(K, 1);
    for (int i = N - 1; i >= 0; i --) {
        for (int k = 0; k < K; k ++) {
            dp = max(dp, max_ps[k] / B[i][k]);
        }
        for (int k = 0; k < K; k ++) {
            max_ps[k] = max(max_ps[k], dp * S[i][k]);
        }
    }

    cout << fixed << setprecision(9) << dp << '\n';
}
