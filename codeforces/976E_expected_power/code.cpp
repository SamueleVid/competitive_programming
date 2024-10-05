#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;
ll fp(ll a, ll b) {
    if (!b) return 1;
    ll h = fp(a, b / 2);
    return h * h * ((b % 2) ? a : 1);
}
ll fp_mod(ll a, ll b) {
    if (!b) return 1;
    ll h = fp_mod(a, b / 2);
    return (((h * h) % MOD) * ((b % 2) ? a : 1)) % MOD;
}
ll inv(ll a) {
    return fp_mod(a, MOD - 2);
}

constexpr int BITS = 11;

void solve() {
    ll N; cin >> N;
    ll inv_1e4 = inv(1e4);

    vector<ll> A(N), P(N), inv_P(N);
    for (int i = 0; i < N; i ++) cin >> A[i];
    for (int i = 0; i < N; i ++) {
        ll p; cin >> p;
        P[i] = (p * inv_1e4) % MOD;
        inv_P[i] = (1 - P[i] + MOD) % MOD;
    }

    // linearity of E[X] e X = sum(b_i * 2^i) => I sum E[b_i] * 2^i, the expected value for every bit
    // for E[X^2], X^2 = sum(sum(b_i * b_j * 2^(i+j)))
    // E[X^2] = sum(sum( E[b_i * b_j] * 2^(i+j) ))
    // E[b_i * b_j] = P[b_i * b_j == 1]

    ll dp[BITS][BITS][2][2], temp[2][2];

    for (int b1 = 0; b1 < BITS; b1 ++) {
        for (int b2 = 0; b2 < BITS; b2 ++) {
            // initially the xor is 0.
            dp[b1][b2][0][0] = 1;
            dp[b1][b2][0][1] = 0;
            dp[b1][b2][1][0] = 0;
            dp[b1][b2][1][1] = 0;

            for (int a = 0; a < N; a ++) {
                bool bit_1 = A[a] & (1 << b1);
                bool bit_2 = A[a] & (1 << b2);

                for (auto i : {0, 1}) {
                    for (auto j : {0, 1}) {
                        // probability of having (b1)(b2) so that 
                        // xorring A[a] results in having (i)(j)
                        ll prob_xor = (dp[b1][b2][i ^ bit_1][j ^ bit_2] * P[a]) % MOD;
                        // probability of having the same (b1)(b2)
                        // as (i)(j) and not picking A[a]
                        ll prob_ignore = (dp[b1][b2][i][j] * inv_P[a]) % MOD;
                        temp[i][j] = (prob_xor + prob_ignore) % MOD;
                    }
                }
                swap(dp[b1][b2], temp);
            }
        }
    }

    ll E_X = 0;
    for (int b1 = 0; b1 < BITS; b1 ++) {
        for (int b2 = 0; b2 < BITS; b2 ++) {
            ll pw = fp_mod(2, b1 + b2);
            ll d = (dp[b1][b2][1][1] * pw) % MOD;
            E_X += d;
            E_X %= MOD;
        }
    }

    cout << E_X << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
