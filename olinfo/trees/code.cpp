#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 5e5 + 5;
const ll MOD = 1e9 + 7;
vector<int> adj[MAXN];
ll v[MAXN];

ll res = 0;

void dfs(int n, int prev) {
    v[n] = 1;
    for (auto u : adj[n]) {
        if (u == prev) continue;
        dfs(u, n);
        v[n] = (v[n] * (v[u] + 1)) % MOD;
    }
    res = (res + v[n]) % MOD;
}  

int count_sets(int N, vector<int> U, vector<int> V) {
    for (int i = 0; i < N - 1; i ++) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }

    res = 0;
    dfs(0, -1);
    return res;
}
