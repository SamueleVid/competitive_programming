#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+2;
int P[MAXN];
bool v[MAXN];
int dist[MAXN];
int group[MAXN];
int dim[MAXN];

void dfs(int u, int count, int g) {
    if (v[u]) {
        dim[g] = count;
        return;
    }
    v[u] = 1;
    dist[u] = count;
    group[u] = g;
    dfs(P[u], count + 1, g);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N; i ++) cin >> P[i];

    int g = 0;
    for (int i = 0; i < N; i ++) {
        if (!v[i]) {
            dfs(i, 0, g);
            g++;
        }
    }
    
    int Q; cin >> Q;
    while (Q --) {
        int a, b; cin >> a >> b;

        if (group[a] != group[b]) {
            cout << -1 << " ";
        }
        else {
            int res = abs(dist[b] - dist[a]);
            res = min(res, abs(dim[group[a]] - res));
            cout << res << " ";
        }
    }
}
