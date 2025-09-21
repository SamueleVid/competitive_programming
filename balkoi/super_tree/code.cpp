// this code shares the same idea as the other one in this directory, but it runs for all bits parellel.
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#define ll long long

constexpr ll MOD = 1e9 + 7;
constexpr ll BITS = 60;
constexpr ll MAXN = 1e6 + 5;

vector<int> adj[MAXN];
int p[MAXN];
ll f[MAXN]; // this is equivalent to bool blocked[BITS][MAXN] in the other code
ll pows[BITS];
ll pows_mod[BITS];

void dfs_init(int u, vector<ll> &a) {

    f[u] = f[p[u]] & a[u];

    for (auto x : adj[u]) {
        dfs_init(x, a);
    }
}

void dfs(int u, vector<ll> &a, ll &super_power, ll &sum_f, ll &sum_f_squared) {

    ll new_f = f[p[u]] & a[u];
    ll old_f = f[u];
    if (new_f == old_f) return;

    new_f = new_f % MOD;
    old_f = old_f % MOD;

    ll diff = (new_f - old_f + MOD) % MOD;
    ll sum_minus_curr = (sum_f - old_f + MOD) % MOD;
    ll to_add = (diff * sum_minus_curr) % MOD;

    super_power = (super_power + to_add) % MOD;

    sum_f = (sum_f - old_f + MOD) % MOD;
    sum_f_squared = (sum_f_squared - ((old_f * old_f) % MOD) + MOD) % MOD;

    f[u] = f[p[u]] & a[u];
    
    sum_f = (sum_f + new_f) % MOD;
    sum_f_squared = (sum_f_squared + new_f * new_f) % MOD;

    for (auto x : adj[u]) {
        dfs(x, a, super_power, sum_f, sum_f_squared);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    
    p[0] = 0;
    for (int i = 1; i < N; i ++) cin >> p[i];
    
    vector<ll> a(N);
    for (int i = 0; i < N; i ++) cin >> a[i];

    for (int i = 1; i < N; i ++) {
        adj[p[i]].push_back(i);
    }

    pows[0] = 1;
    for (int p = 1; p < BITS; p ++) pows[p] = pows[p - 1] * 2;
    for (int p = 0; p < BITS; p ++) pows_mod[p] = pows[p] % MOD;

    f[0] = a[0];
    dfs_init(0, a);

    ll super_power = 0;
    ll sum_f = 0;
    ll sum_f_squared = 0;
    for (int i = 0; i < N; i ++) {
        ll curr_f = f[i] % MOD;
        super_power = (super_power + sum_f * curr_f) % MOD;
        sum_f = (sum_f + curr_f) % MOD;
        sum_f_squared = (sum_f_squared + curr_f * curr_f) % MOD;
    }
    ll power = (2 * super_power + sum_f_squared) % MOD;

    cout << power << " " << super_power << '\n';

    while (Q --) {
        ll u, x; cin >> u >> x;
        // it is sufficient to block only the node u
        a[u] &= x;

        // dfs is called at most BITS * MAXN times, as it is the maximum numbers of bits to "block" from the roof
        dfs(u, a, super_power, sum_f, sum_f_squared);

        power = (2 * super_power + sum_f_squared) % MOD;

        cout << power << " " << super_power << '\n';
    }
}
