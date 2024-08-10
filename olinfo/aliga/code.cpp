#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e5 + 1;
vector<int> adj[MAXN];
map<int, int> m[2 * MAXN];
int subtree[MAXN]; 
bool removed[MAXN];
ll res = 0;
int max_dist = 0;

void get_size(int u, int p, int d) {
    max_dist = max(max_dist, d);
    subtree[u] = 1;
    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        get_size(v, u, d + 1); 
        subtree[u] += subtree[v];
    }
}

int get_centroid(int u, int p, int target) {
    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (subtree[v] > target) return get_centroid(v, u, target);
    }
    return u;
}

void dfs(int u, int p, int flag, int d) {
    // flag: 0 adda, 1 updata, 2 cancella
    int x = 0;
    if (flag == 0) {
        while (x * u <= 2 * max_dist && x <= 2 * max_dist) {
            if (m[x].count(d - x * u)) res += m[x][d - x * u];
            x ++;
        }
    }
    if (flag == 1) {
        while (x * u <= 2 * max_dist && x <= 2 * max_dist) {
            m[x][-d + x * u] ++;
            x ++;
        }
    }
    if (flag == 2) {
        while (x * u <= 2 * max_dist && x <= 2 * max_dist) {
            m[x].clear();
            x ++;
        }
    }

    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        dfs(v, u, flag, d + 1);
    }
}

void centroid_decomp(int u) {
    max_dist = 0;
    get_size(u, -1, 0);
    int c = get_centroid(u, -1, subtree[u] / 2);
    
    int x = 0;
    while (x * c <= 2 * max_dist && x <= 2 * max_dist) {
        m[x][0 + x * c] ++;
        x ++;
    }

    for (auto v : adj[c]) {
        if (!removed[v]) {
            dfs(v, c, 0, 1);
            dfs(v, c, 1, 1);
        }
    }
    for (auto v : adj[c]) {
        if (!removed[v]) {
            dfs(v, c, 2, 1);
        }
    }

    x = 0;
    while (x * c <= 2 * max_dist && x <= 2 * max_dist) {
        m[x].clear();
        x ++;
    }

    removed[c] = 1;
    for (auto v : adj[c]) {
        if (!removed[v]) centroid_decomp(v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    for (int i = 0; i < N - 1; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    fill(removed, removed + MAXN, 0);
    centroid_decomp(0);

    cout << res << '\n';
}
