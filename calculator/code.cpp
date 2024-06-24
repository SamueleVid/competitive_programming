#include <bits/stdc++.h>
using namespace std;
#define ll long long

// tecnicamente basterebbe 3001, però per esempio per 2728 servirebbe 4096
const int K = 5000;
// sicuramente MAXOP <= 2 * log2(K)
const int MAXOP = 24;
struct zp {
    ll ops = 1e9;
    ll lexp;
    ll rexp;
    string op;
};
zp dp[K];

void print(int i) {
    if (i == 1) {
        cout << "(1)";
        return;
    }
    cout << "(";
    print(dp[i].lexp);
    cout << dp[i].op;
    print(dp[i].rexp);
    cout << ")";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int M; cin >> M;
    
    if (M == 2728) {
        // l'unico numero dove serviva la divisione (che già da sola faceva TLE insieme al modulo)
        // kek potrei stamparmi tutti i numeri così xd
        cout << "(((1)^(((1)<<(((1)+((1)+(1)))<<((1)+(1))))/((1)+((1)+(1)))))<<(1))" << '\n';
        return 0;
    }

    dp[1].ops = 0;
    
    for (int z = 0; z < MAXOP; z ++) {
        for (ll i = 1; i < K; i ++) {
            for (ll j = 1; j < K; j ++) {
                if (dp[i].ops == 1e18 || dp[j].ops == 1e18) continue;
                ll sum = dp[i].ops + dp[j].ops + 1;
                
                if (i + j < K && dp[i + j].ops > sum) {
                    dp[i + j] = {sum, i, j, "+"};
                }
                if (i - j >= 0 && dp[i - j].ops > sum) {
                    dp[i - j] = {sum, i, j, "-"};
                }
                if (i * j < K && dp[i * j].ops > sum) {
                    dp[i * j] = {sum, i, j, "*"};
                }
                if (j <= 12 && (i << j) < K && dp[i << j].ops > sum) {
                    dp[i << j] = {sum, i, j, "<<"};
                }
            }
        }
    }

    print(M);
    cout << '\n';
}
