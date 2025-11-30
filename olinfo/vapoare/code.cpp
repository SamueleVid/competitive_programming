#include <bits/stdc++.h>
using namespace std;

struct Dsu {
    vector<int> p, sz;
    Dsu(int N) {
        p.resize(N);
        iota(p.begin(), p.end(), 0);
        sz.assign(N, 1);
    }

    int boss(int u) {
        if (p[u] == u) return u;
        return p[u] = boss(p[u]);
    }

    void merge(int u, int v) {
        u = boss(u);
        v = boss(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
    }
};

int main() {
    int N, K, T; cin >> N >> K >> T;
    vector<pair<int, pair<int,int>>> edges(K);
    for (int i = 0; i < K; i ++) {
        int u, v, w; cin >> u >> v >> w;
        u --; v --;
        edges[i] = {w, {u, v}};
    }
    vector<int> W(T);
    for (int i = 0; i < T; i ++) {
        cin >> W[i];
    }

    vector<pair<int, int>> w_sorted(T);
    for (int i = 0; i < T; i ++) {
        w_sorted[i] = {W[i], i};
    }

    sort(edges.rbegin(), edges.rend());
    sort(w_sorted.rbegin(), w_sorted.rend());
    
    vector<int> res(T);
    
    Dsu comps(N);
    int num_comps = N;

    int pt = 0;
    for (auto [w, uv] : edges) {
        auto [u, v] = uv;
        while (pt < T && w < w_sorted[pt].first) {
            res[w_sorted[pt].second] = num_comps;
            pt ++;
        }

        if (comps.boss(u) != comps.boss(v)) {
            num_comps --;
        }
        comps.merge(u, v);
    }

    while (pt < T) {
        res[w_sorted[pt].second] = num_comps;
        pt ++;
    }

    for (auto x : res) {
        cout << x << '\n';
    }

}
