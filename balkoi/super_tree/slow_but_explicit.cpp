// here I have explicitly split the tree in BITS different trees, and by looking at each new tree individually 
// the queries become "block this node and all of the below from the root".
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#define ll long long

constexpr ll MOD = 1e9 + 7;
constexpr ll BITS = 60;
constexpr ll MAXN = 1e6 + 5;

vector<int> adj[MAXN];
bool blocked[BITS][MAXN];
ll pows[BITS];
ll pows_mod[BITS];

void fix_mod(ll &x) {
    while (x < 0) x += MOD;
    while (x >= MOD) x -= MOD;
}

void dfs_init(int u, int b, vector<ll> &a, vector<ll> &f) {
    if (!blocked[b][u]) {
        f[u] = (f[u] + pows_mod[b]);
        fix_mod(f[u]);
    }
    for (auto x : adj[u]) {
        bool togli = (a[x] & pows[b]);
        if (blocked[b][u] || !togli) blocked[b][x] = 1;
        dfs_init(x, b, a, f);
    }
}

void dfs(int u, int b, vector<ll> &a, vector<ll> &f, ll &super_power, ll &sum_f, ll &sum_f_squared) {
  
    ll bit = pows_mod[b]; 
    ll sum_minus_curr = sum_f - f[u];
    fix_mod(sum_minus_curr);
    ll to_remove = (bit * sum_minus_curr) % MOD;
    super_power = super_power - to_remove;
    fix_mod(super_power);

    sum_f = sum_f - f[u];
    fix_mod(sum_f);
    sum_f_squared = sum_f_squared - ((f[u] * f[u]) % MOD);
    fix_mod(sum_f_squared);
    f[u] = f[u] - bit;
    fix_mod(f[u]);
    sum_f = sum_f + f[u];
    fix_mod(sum_f);
    sum_f_squared = (sum_f_squared + f[u] * f[u]) % MOD;

    blocked[b][u] = 1;

    for (auto x : adj[u]) {
        if (!blocked[b][x]) {
            dfs(x, b, a, f, super_power, sum_f, sum_f_squared);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<int> p(N);
    for (int i = 1; i < N; i ++) cin >> p[i];
    vector<ll> a(N);
    for (int i = 0; i < N; i ++) cin >> a[i];

    for (int i = 1; i < N; i ++) {
        adj[p[i]].push_back(i);
    }

    pows[0] = 1;
    for (int p = 1; p < BITS; p ++) pows[p] = pows[p - 1] * 2;
    for (int p = 0; p < BITS; p ++) pows_mod[p] = pows[p] % MOD;
    for (int b = 0; b < BITS; b ++) for (int i = 0; i < N; i ++) blocked[b][i] = 0;

    vector<ll> f(N);

    for (int b = 0; b < BITS; b ++) {
        bool togli = (a[0] & pows[b]);
        if (!togli) blocked[b][0] = 1;
        dfs_init(0, b, a, f);
    }

    ll super_power = 0;
    ll sum_f = 0;
    ll sum_f_squared = 0;
    for (int i = 0; i < N; i ++) {
        super_power = (super_power + sum_f * f[i]) % MOD;
        sum_f = (sum_f + f[i]) % MOD;
        sum_f_squared = (sum_f_squared + f[i] * f[i]) % MOD;
    }
    ll power = (2 * super_power + sum_f_squared) % MOD;

    cout << power << " " << super_power << '\n';

    while (Q --) {
        ll u, x; cin >> u >> x;
        a[u] &= x;

        return -1;

        for (int b = 0; b < BITS; b ++) {
            if (blocked[b][u]) continue;
            bool is_there_bit = (a[u] & pows[b]);
            if (is_there_bit) continue;
            dfs(u, b, a, f, super_power, sum_f, sum_f_squared);
        }

        power = (2 * super_power + sum_f_squared);
        fix_mod(power);

        cout << power << " " << super_power << '\n';
    }
}
