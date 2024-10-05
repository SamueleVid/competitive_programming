#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 3e5 + 5;
vector<int> adj[MAXN];
int p[MAXN], depth[MAXN], max_depth[MAXN], subtree[MAXN];
ll res_alto[MAXN], res_basso[MAXN];

void dfs(int u) {
    subtree[u] = 1;
    for (auto x : adj[u]) {
        depth[x] = depth[u] + 1;
        max_depth[x] = depth[x];
        dfs(x);
        max_depth[u] = max(max_depth[u], max_depth[x]);
        subtree[u] += subtree[x];
    }
}

void dfs_res(int u) {
    res_alto[max_depth[u]] += 1;
    res_basso[depth[u]] += 1;

    for (auto x : adj[u]) dfs_res(x);
}

int pota(int N, vector<int> P) {
    for (int i = 0; i < N; i ++) p[i] = P[i];
    for (int i = 1; i < N; i ++) adj[p[i]].push_back(i);
    depth[0] = 0; max_depth[0] = 0;
    dfs(0);

    fill(res_alto, res_alto + MAXN, 0);
    fill(res_basso, res_basso + MAXN, 0);

    dfs_res(0);

    vector<ll> ps_res_alto(N + 1);
    vector<ll> ps_res_basso(N + 1);
    ps_res_alto[0] = res_alto[0];
    for (int i = 1; i <= N; i ++) {
        ps_res_alto[i] = ps_res_alto[i - 1] + res_alto[i - 1];
    }
    ps_res_basso[N] = res_basso[N];
    for (int i = N - 1; i >= 0; i --) {
        ps_res_basso[i] = ps_res_basso[i + 1] + res_basso[i + 1];
    }
    
    ll res = 1e9;
    for (int i = 0; i <= N; i ++) {
        res = min(res, ps_res_alto[i] + ps_res_basso[i]);
    }

    return res;
}
