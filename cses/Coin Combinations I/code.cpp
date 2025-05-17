#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int N, X; cin >> N >> X;

    vector<int> C(N);
    for (int i = 0; i < N; i ++) cin >> C[i];

    vector<int> dp(X + 1);
    dp[0] = 1;
    for (int i = 0; i <= X; i ++) {
        for (auto c : C) {
            if (i - c >= 0) dp[i] = (dp[i] + dp[i - c]) % MOD;
        }
    }

    // Iterando prima per il valore e poi per la moneta, conto anche l'ordine in cui arrivano le monete. 
    // Se penso di visualizzare con una sequenza le monete che aggiungo,
    // considerando C = {2, 3}, si nota facilmente che dp[0] = (), dp[2] = (2), dp[3] = (3) e dp[5] = dp[2] + dp[3], quindi (2,3) e (3,2). 

    cout << dp[X] << '\n';
}
