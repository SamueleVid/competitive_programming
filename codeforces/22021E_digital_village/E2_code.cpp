// credit: tourist's submission https://codeforces.com/contest/2021/submission/284583097
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct dsu {
    vector<int> p;
    vector<int> size;

    dsu(int N) {
        size.assign(N, 1);
        p.resize(N);
        iota(p.begin(), p.end(), 0);
    }

    int boss(int u) {
        if (p[u] == u) return u;
        return p[u] = boss(p[u]);
    }

    void merge(int a, int b) {
        a = boss(a);
        b = boss(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        p[b] = a;
        size[a] += size[b];
    }

    bool same_group(int a, int b) {
        return (boss(a) == boss(b));
    }
};

void solve() {
    int N, M, P; cin >> N >> M >> P;
    vector<bool> wifi(N);
    for (int i = 0; i < P; i ++) {
        int u; cin >> u;
        wifi[u - 1] = 1;
    }
    
    vector<array<int, 3>> edges(M); // weight, u, v
    for (int i = 0; i < M; i ++) {
        int u, v, w; cin >> u >> v >> w;
        u --; v --;
        edges[i] = {w, u, v};        
    }

    sort(edges.begin(), edges.end());
    dsu d(N);

    // In dp[i][j] I save the solution for K = j considering the subgraph defined
    // by the connected component of the DSU with root i.
    // Obviously j <= number of wifi nodes in the component.
    vector<vector<ll>> dp(N);
    for (int i = 0; i < N; i ++) {
        // Of course if there is a house that needs wifi 
        // the number of server needed is 1, otherwise 0.
        // If there is 1 house that needs wifi and 1 server, for K = 1 the answer is 0.
        // The latency consumed by 0 houses is trivially 0. 
        dp[i].assign(wifi[i] ? 2 : 1, 0);
    }
    for (auto [w, u, v] : edges) {
        if (d.same_group(u, v)) continue;
        // I merge the solutions of the two subgraphs
        // temp.size() - 1 is the number of wifi houses and possible servers in the new subgraph 

        u = d.boss(u);
        v = d.boss(v);
        vector<ll> new_dp(dp[u].size() + dp[v].size() - 1, 1e18);
        for (int i = 0; i < dp[u].size(); i ++) {
            for (int j = 0; j < dp[v].size(); j ++) {
                // Merge the K = i solution of U's subgraph and
                // the K = j solution of V's subgraph

                if (i == 0 && j == 0) new_dp[0] = 0;
                
                // If there are server only on one of the subgraphs (wlog i = 0, j > 0),
                // all the wifi houses on U's subgraph must be linked to V's servers.
                // To do so they must go through the edge (U, V) of weight W.
                // Since the edges are processed in order of weight, W is greater than
                // all the other weights in U's and V's subgraph edges, so the latency 
                // of each wifi house in U's subgraph is W. 
                if (i == 0 && j > 0) 
                    new_dp[j] = min(new_dp[j], dp[v][j] + w * (ll)(dp[u].size() - 1));
                if (i > 0 && j == 0) 
                    new_dp[i] = min(new_dp[i], dp[u][i] + w * (ll)(dp[v].size() - 1));
                
                // Since going through the edge (U, V) of weight W is never optimal,
                // beacuse its latency is greater then all the other edges, all the
                // wifi houses in the bigger subgraph are connected to the same servers
                // they were connected to in their smaller subgraphs.
                if (i > 0 && j > 0) 
                    new_dp[i + j] = min(new_dp[i + j], dp[u][i] + dp[v][j]);
            }
        }

        d.merge(u, v);
        int b = d.boss(v);
        swap(dp[b], new_dp);
    }

    vector<ll> res = dp[d.boss(0)];

    for (int i = 1; i <= N; i ++) {
        cout << (i < P ? res[i] : 0) << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
