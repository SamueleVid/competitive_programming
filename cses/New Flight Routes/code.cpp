#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++ i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi val, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int j, G& g, F& f) {
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e,g,f));
    
    if (low == val[j]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont); cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

template<class G> int find_sink(G& g, vi& v, int u, vi& is_sink) {
    if (v[u]) return -1;
    v[u] = 1;
    if (is_sink[u]) return u;
    for (auto x : g[u]) {
        int r = find_sink(g, v, x, is_sink);
        if (r != -1) return r;
    }
    return -1;
}

void solve() {
    int N, M; cin >> N >> M;
    vector<vi> adj(N);
    for (int i = 0; i < M; i ++) {
        int a, b; cin >> a >> b;
        a --; b --;
        adj[a].push_back(b);
    }

    vi node_in_scc(N);
    scc(adj, [&](vi &v){ 
        node_in_scc[ncomps] = v[0];
    });

    if (ncomps == 1) {
        cout << 0 << '\n';
        return;
    }

    vector<vi> scc_adj(ncomps);
    rep(i, 0, N) {
        for (auto x : adj[i]) {
            if (comp[i] == comp[x]) continue;
            scc_adj[comp[i]].push_back(comp[x]);
        }
    }

    vi indeg(ncomps), outdeg(ncomps);
    rep(i, 0, ncomps) {
        for (auto x : scc_adj[i]) {
            indeg[x] ++;
            outdeg[i] ++;
        }
    }

    int random_sink, random_source;

    vi is_sink(ncomps), is_source(ncomps);
    rep(i, 0, ncomps) {
        if (indeg[i] == 0) {
            is_source[i] = 1;
            random_source = i;
        }
        if (outdeg[i] == 0) {
            is_sink[i] = 1;
            random_sink = i;
        }
    } 

    // trovo dei path che connettono source a sink
    vi ring_sink, ring_source, not_ring_sink, not_ring_source;
    vi v(ncomps);

    rep(i,0,ncomps) {
        if (!is_source[i]) continue;

        int c = find_sink(scc_adj, v, i, is_sink);
        if (c == -1) continue;

        is_source[i] = 0;
        is_sink[c] = 0;
        ring_source.push_back(i);
        ring_sink.push_back(c);
    }
    
    rep(i,0,ncomps) {
        if (is_sink[i]) not_ring_sink.push_back(i);
        if (is_source[i]) not_ring_source.push_back(i);
    }

    // Ho collegato seguendo un anello tutti i path, creando una grande scc.
    // per ogni source e sink non all'interno dell'anello, ogni path collega il source all'scc
    // dell'anello e ogni path collega l'scc dell'anello al sink. Quindi quelli posso collegarli greedy
    // è importante che "ogni" path li colleghi, così che i nodi o fanno parte del ring oppure a path collegati al ring
    vector<pii> edges;
    rep(i, 0, sz(ring_sink) - 1) {
        edges.push_back({ring_sink[i], ring_source[i + 1]});
    }
    edges.push_back({ring_sink[sz(ring_sink) - 1], ring_source[0]});

    while (sz(not_ring_sink) && sz(not_ring_source)) {
        if (not_ring_sink.back() != not_ring_source.back()) {
            edges.push_back({not_ring_sink.back(), not_ring_source.back()});
        }
        not_ring_sink.pop_back();
        not_ring_source.pop_back();
    }

    while (sz(not_ring_sink)) {
        if (not_ring_sink.back() != random_source) {
            edges.push_back({not_ring_sink.back(), random_source});
        }
        not_ring_sink.pop_back();
    }

    while (sz(not_ring_source)) {
        if (random_sink && not_ring_source.back()) {
            edges.push_back({random_sink, not_ring_source.back()});
        }
        not_ring_source.pop_back();
    }

    cout << sz(edges) << '\n';
    for (auto [a, b] : edges) {
        cout << node_in_scc[a] + 1 << " " << node_in_scc[b] + 1 << '\n';
    }
}   

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int T = 1;
    // cin >> T;
    while (T --) solve();
}
