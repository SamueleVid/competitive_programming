// credits:
// tourist's submission https://codeforces.com/contest/2021/submission/284591976
// errorgon's blog https://codeforces.com/blog/entry/98663
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

    // Save in dp[X] the slopes between the answers for K and K + 1 for the subgraph X.
    vector<multiset<ll>> dp(N);
    // Manually save for each component the result of K = 1.
    vector<ll> k_one(N);
    for (int i = 0; i < N; i ++) {
        if (wifi[i]) dp[i].insert(0);
        k_one[i] = 0;
    }
    for (auto [w, u, v] : edges) {
        if (d.same_group(u, v)) continue;
        // Loop invariant for dp: 
        // 1) dp[X] contains the slopes between K = i and K = i + 1,
        // for i = [0, i = local_P - 1], where local_P is the number
        // of wifi houses in the component X.
        // 2) dp[X] is convex.

        u = d.boss(u);
        v = d.boss(v);

        ll local_P_u = dp[u].size();
        ll local_P_v = dp[v].size();
        
        // Get the value for K = 0 for both components.
        ll k_zero_u = w * local_P_u;
        ll k_zero_v = w * local_P_v;

        // Get the answer for K = 1 for the resulting component.
        ll new_k_one = min(k_one[v] + k_zero_u, k_one[u] + k_zero_v);

        // Editing the slope between K = 0 and K = 1, which means changing the answer for
        // K = 0 for the convolution. DP stays convex as K_1 - K_0 <= K_2 - K_1. 
        // Using W as an upper bound for the latencies of the wifi houses for K = 1
        // and K = 2, and knowing that each server is always placed on top of a wifi house
        // (follows from the conjecture that the servers for K_i are a subset for K_i+1 
        // and that for K = P it's optimal to place the P servers on top of the P wifi houses) 
        // K_0 = W * P, K_1 <= W * (P - 1), K_2 <= W * (P - 2), from K_1 - K_0 <= K_2 - K_1
        // follows W * (P - 1) - W * P <= W * (P - 2) - W * (P - 1), W * P <= W * P.
        // This shows that DP stays convex.
        if (dp[u].size()) {
            dp[u].erase(dp[u].begin());
            dp[u].insert(k_one[u] - k_zero_u);
        }
        if (dp[v].size()) {
            dp[v].erase(dp[v].begin());
            dp[v].insert(k_one[v] - k_zero_v);
        }

        // errorgon's blog (https://codeforces.com/blog/entry/98663) describes how a
        // (min, +) convolution over two convex arrays A, B is equivalent of calculating
        // the Minkowski sum of the convex polygons defined by the points (i, A[i]) 
        // and (i, B[i]), which is ""well known"" as taking the union of their edges.
        // The Minkowski sum of two convex polygons produces another convex polygon, 
        // which mantains the loop invariance for dp. 
        // I used small-to-large to limit the complexity of taking this union over all
        // the subgraphs in O(NlogN). 
        multiset<ll> new_dp;
        if (dp[u].size() < dp[v].size()) swap(u, v);
        swap(dp[u], new_dp);
        for (auto x : dp[v]) new_dp.insert(x);

        d.merge(u, v);
        int b = d.boss(v);
        swap(dp[b], new_dp);
        k_one[b] = new_k_one;
    }

    multiset<ll> res = dp[d.boss(0)];
    // Ignore K = 0, so the first slope.
    res.erase(res.begin()); 
    ll curr = k_one[d.boss(0)];
    cout << curr << " ";
    for (auto x : res) {
        curr += x;
        cout << curr << " ";
    }
    for (int i = P; i < N; i ++) cout << 0 << " ";
    cout << '\n';

}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
