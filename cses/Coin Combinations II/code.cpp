#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {
    int N, X; cin >> N >> X;

    vector<int> C(N);
    for (int i = 0; i < N; i ++) cin >> C[i];

    vector<int> dp(X + 1);
    dp[0] = 1;
    for (int i = 0; i < N; i ++) {
        // qua parto dall'inizio e non dalla fine, così posso utilizzare la stessa moneta più volte
        for (int j = C[i]; j <= X; j ++) {
            dp[j] = (dp[j] + dp[j - C[i]]) % MOD;
        }
    }

    // Calcolo dp iterando prima per le monete e poi per il valore, questo significa conto le monete senza ordine.
    // Se penso di visualizzare con una sequenza le monete che aggiungo, le monete dello stesso tipo formano sempre un blocco continuo.

    cout << dp[X] << '\n';
}
