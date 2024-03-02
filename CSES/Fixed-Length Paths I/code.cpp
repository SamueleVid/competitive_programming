#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 200001;
int n, k;
vector<int> adj[MAXN];
int subtree[MAXN];

ll ans = 0;
int cnt[MAXN]{1};
int max_depth;
bool removed[MAXN];

void set_size(int u, int p) {
    subtree[u] = 1;
    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        set_size(v, u);
        subtree[u] += subtree[v];
    }
}

int get_centroid(int u, int p, int target) {
    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (subtree[v] >= target) return get_centroid(v, u, target);
    }
    return u;
}

void get_cnt(int u, int p, int depth, int updating) {
    if (depth > k) return;
    max_depth = max(depth, max_depth);
    
    if (updating) cnt[depth] ++;
    else ans += cnt[k-depth];

    for (auto v : adj[u]) {
        if (v == p || removed[v]) continue;
        get_cnt(v, u, depth + 1, updating);
    }
}

void centroid_decomp(int u) {
    set_size(u,-1);
    int c = get_centroid(u, -1, subtree[u] >> 1);
    removed[c] = true;
    max_depth = 0;

    for (auto v : adj[c]) {
        if (removed[v]) continue;
        get_cnt(v, c, 1, false);
        get_cnt(v, c, 1, true);
    }
    fill(cnt + 1, cnt + max_depth + 1, 0);
    
    for (auto v : adj[c]) {
        if (removed[v]) continue;
        centroid_decomp(v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    centroid_decomp(1);
    cout << ans << '\n';
}
