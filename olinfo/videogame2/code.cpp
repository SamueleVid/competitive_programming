#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll MOD;
constexpr ll MAXV = 1e6 + 5;
ll fact[MAXV], inv[MAXV], inv_fact[MAXV];

ll fp(ll a, ll p) {
    if (!p) return 1;
    ll h = fp(a, p / 2);
    h = h * h % MOD;
    if (p % 2) h = h * a % MOD;
    return h;
}

void precalc() {
    fact[0] = 1;
    for (int i = 1; i < MAXV; i ++) fact[i] = fact[i - 1] * i % MOD;
    inv[1] = 1;
    for (int i = 2; i < MAXV; i ++) inv[i] = (MOD - (MOD / i)) * inv[MOD % i] % MOD;
    inv_fact[0] = 1;
    for (int i = 1; i < MAXV; i ++) inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
}

ll lagrange_interpolate(ll x, vector<ll> y) { // x [0, N]
    ll N = y.size() - 1;

    vector<ll> prefix(N + 1); // product [x - i, x - 0]
    prefix[0] = x;
    for (ll i = 1; i <= N; i ++) prefix[i] = prefix[i - 1] * (x - i) % MOD;

    vector<ll> suffix(N + 1); // product [x - N, x - i]
    suffix[N] = x - N;
    for (ll i = N - 1; i >= 0; i --) suffix[i] = suffix[i + 1] * (x - i) % MOD;
    
    ll res = 0;
    for (ll i = 0; i <= N; i ++) {
        // numerator
        ll l = (i > 0 ? prefix[i - 1] : 1) * (i < N ? suffix[i + 1] : 1) % MOD;
        // denumerator
        l = l * (MOD + (((N - i) % 2) ? -1 : 1) * (inv_fact[i] * inv_fact[N - i] % MOD)) % MOD;
        // multiply by y
        res = (res + l * y[i]) % MOD;
    }

    return res;
}

ll sum_of_kth_power(ll N, ll K) {
    vector<ll> y(K + 2);
    y[0] = 0;
    for (int i = 1; i < K + 2; i ++) {
        y[i] = (y[i - 1] + fp(i, K)) % MOD;
    }

    if (N < K + 2) return y[N];
    return lagrange_interpolate(N, y);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll N, K, MOD; cin >> N >> K >> MOD;
    :: MOD = MOD;
    N %= MOD;
    precalc();

    ll sum_i_k = sum_of_kth_power(N - 1, K);
    ll sum_i_k_plus_1 = sum_of_kth_power(N - 1, K + 1);

    ll res = fp(N, K);
    res = (res + (2 * N + 1) % MOD * sum_i_k) % MOD;
    res = (res - 2 * sum_i_k_plus_1 + 2 * MOD) % MOD;
    
    cout << res << '\n';
}
