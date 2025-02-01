#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 1e5 + 5;
constexpr int PW = 131072;
constexpr int B = 30;

struct dsu {
    vector<int> p, size;
    stack<pair<int,int>> moves; // aggiungo dx a sx

    dsu() {
        p.resize(MAXN);
        iota(p.begin(), p.end(), 0);
        size.assign(MAXN, 1);
    }

    int boss(int u) {
        while (p[u] != u) u = p[u];
        return u;
    }

    bool same_comp(int u, int v) {
        return boss(v) == boss(v);
    }

    void merge(int u, int v) {
        int b_u = boss(u);
        int b_v = boss(v);
        
        if (size[b_u] < size[b_v]) {
            swap(b_u, b_v);
            swap(u, v);
        }

        p[b_v] = b_u;
        size[b_u] += size[b_v];
        moves.push({b_u, b_v});
    }

    void rollback() {
        auto [b_u, b_v] = moves.top(); moves.pop();

        p[b_v] = b_v;
        size[b_u] -= size[b_v];
    }
};

struct segment {
    vector<vector<pair<int, int>>> seg;

    segment() {
        seg.resize(2 * PW);
    }

    void update(int idx, int l, int r, int ql, int qr, pair<int, int> move) {
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            seg[idx].push_back(move);
            return;
        }

        update(idx * 2    , l, (l + r) / 2, ql, qr, move);
        update(idx * 2 + 1, (l + r) / 2, r, ql, qr, move);
    }

    void add_mossa(pair<int, int> move, int l, int r) {
        // r escluso
        update(1, 0, PW, l, r, move);
    }

    void dfs(int idx, int l, int r, ll &tot, dsu &comps, vector<ll> &sols) {
        
        ll delta = 0;
        for (auto [u, v] : seg[idx]) {

            int b_u = comps.boss(u);
            int b_v = comps.boss(v);
            ll c_u = comps.size[b_u];
            ll c_v = comps.size[b_v];

            delta -= c_u * (c_u - 1) / 2;
            delta -= c_v * (c_v - 1) / 2;

            delta += (c_u + c_v) * (c_u + c_v - 1) / 2;
            comps.merge(u, v);
        }
        tot += delta;

        if (r - l == 1) {
            if (l < sols.size()) sols[l] = tot;
        }
        else {
            dfs(2 * idx    , l, (l + r) / 2, tot, comps, sols);
            dfs(2 * idx + 1, (l + r) / 2, r, tot, comps, sols);
        }

        for (auto [u, v] : seg[idx]) {
            comps.rollback();
        }
        tot -= delta;
    }

    void calc_res(ll &tot, dsu &comps, vector<ll> &sols) {
        dfs(1, 0, PW, tot, comps, sols);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int N; cin >> N;

    // ho ottimizzato tutto così da fare un segment e una dsu per bit alla volta al posto
    // di tenerne 30 contemporaneamente per evitare MLE, still 30 map sono poche quindi non è un problema.
    map<pair<int, int>, int> when_added[B];

    for (int i = 0; i < N - 1; i ++) {
        int U, V, W; cin >> U >> V >> W;
        if (U > V) swap(U, V);

        for (int p = 0; p < B; p ++) {
            if (W & (1 << p)) {
                when_added[p][{U, V}] = 0;
            }
        }
    }

    int Q; cin >> Q;
    vector<vector<int>> queries(Q);

    for (int q = 0; q < Q; q ++) {
        int U, V, X; cin >> U >> V >> X;
        queries[q] = {U, V, X};
    }

    vector<ll> res(Q + 1);

    for (int p = 0; p < B; p ++) {

        dsu comps;
        segment seg;

        for (int q = 1; q <= Q; q ++) {
            int U = queries[q - 1][0];
            int V = queries[q - 1][1];
            int X = queries[q - 1][2];

            if (U > V) swap(U, V);
            
            if ((X & (1 << p)) && !when_added[p].count({U, V})) {
                // aggiungi arco

                when_added[p][{U, V}] = q;
                continue;
            }

            if (!(X & (1 << p)) && when_added[p].count({U, V})) {
                // togli arco

                seg.add_mossa({U, V}, when_added[p][{U, V}], q);
                when_added[p].erase({U, V});
                continue;
            }
        }

        // togli le ultime mosse rimaste
        for (auto [move, l] : when_added[p]) {
            seg.add_mossa(move, l, Q + 1);
        }
        when_added[p].clear();

        vector<ll> sols(Q + 1);
        ll tot = 0;
        seg.calc_res(tot, comps, sols);

        for (int q = 0; q <= Q; q ++) {
            res[q] += sols[q] << p;
        }
    }

    for (auto x : res) cout << x << " ";
}
