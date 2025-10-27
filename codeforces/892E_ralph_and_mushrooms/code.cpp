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
template<class G, class F> void ssc(G& g, F f) {
    int n = sz(g);
    val.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

vi topoSort(const vector<vi>& gr) {
    vi indeg(sz(gr)), q;
    for (auto& li : gr) for (int x : li) indeg[x]++;
    rep(i,0,sz(gr)) if (indeg[i] == 0) q.push_back(i);
    rep(j,0,sz(gr)) for (int x : gr[q[j]])
        if (--indeg[x] == 0) q.push_back(x);
    return q;
}

void solve() {
    int N, M; cin >> N >> M;
    vector<vi> adj(N);
    vector<vector<pair<ll, ll>>> adj_weight(N);
    for (int i = 0; i < M; i ++) {
        ll a, b, w; cin >> a >> b >> w;
        a --; b --;
        adj[a].push_back(b);
        adj_weight[a].push_back({b, w});
    }
    int s; cin >> s;
    s --;

    vi node_in_scc(N);
    ssc(adj, [&](vi &v){ });

    vector<ll> mushroom_scc(ncomps);
    vector<vector<pair<ll, ll>>> scc_adj(ncomps);
    rep(i, 0, N) {
        for (auto [x, w] : adj_weight[i]) {
            if (comp[i] == comp[x]) {
                ll k = (-1 + sqrt(1 + 8 * w)) / 2;
                mushroom_scc[comp[i]] += (k + 1) * w - k * (k + 1) * (k + 2) / 6;
            }
            else {
                scc_adj[comp[i]].push_back({comp[x], w});
            }
        }
    }

    vector<vi> scc_adj_simple(ncomps);
    rep(i,0,ncomps) for (auto [x, w] : scc_adj[i]) scc_adj_simple[i].push_back(x);

    vi topo = topoSort(scc_adj_simple);

    vector<ll> dp(ncomps);

    for (int i = ncomps - 1; i >= 0; i --) {
        int u = topo[i];
        for (auto [x, w] : scc_adj[u]) {
            dp[u] = max(dp[u], dp[x] + w);
        }
        dp[u] += mushroom_scc[u];
    }

    cout << dp[comp[s]] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int T = 1;
    // cin >> T;
    while (T --) solve();
}
