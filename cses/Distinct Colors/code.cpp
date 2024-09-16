#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2e5 + 5;
int C[MAXN];
int P[MAXN];
int res[MAXN];
vector<int> adj[MAXN];
map<int, int> mappe[MAXN];

void dfs(int u, int p) {
    mappe[u][C[u]] = 1;

    for (auto x : adj[u]) {
        if (x == p) continue;
        dfs(x, u);
        if (mappe[u].size() < mappe[x].size()) swap(mappe[u], mappe[x]);
        for (auto [a, b] : mappe[x]) mappe[u][a] += b;
    }

    res[u] = mappe[u].size();
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;

    for (int i = 1; i <= N; i ++) cin >> C[i];

    for (int i = 0; i < N - 1; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, -1);
    for (int i = 1; i <= N; i ++) cout << res[i] << " ";
    cout << '\n';
}
