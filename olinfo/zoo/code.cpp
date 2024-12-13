#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 131072;
constexpr int MAXN = 1e5 + 5;
vector<int> adj[MAXN];

struct segment {
    vector<ll> seg;
    segment() {
        seg.assign(2 * PW, 0);
    }

    void update(int x, ll d) {
        x += PW;
        while (x >= 1) {
            seg[x] += d;
            x /= 2;
        }
    }

    int query(int l, int r) {
        l += PW; r += PW;
        ll res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res += seg[l];
                l ++;
            }
            if (r % 2 == 0) {
                res += seg[r];
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};

vector<ll> dijkstra(int N, int s) {
    vector<ll> d(N, 1e18);
    vector<bool> v(N);
    priority_queue<pair<ll, int>> pq;
    d[s] = 0;
    pq.push({-d[s], s});

    while (!pq.empty()) {
        auto [_, u] = pq.top(); pq.pop();
        if (v[u]) continue;
        v[u] = 1;
        for (auto x : adj[u]) {
            if (d[x] > d[u] + 1) {
                d[x] = d[u] + 1;
                pq.push({-d[x], x});
            }
        }
    }
  
    return d;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<ll> d_0 = dijkstra(N, 0);
    vector<ll> d_f = dijkstra(N, N - 1);
    ll D = d_0[N - 1];
    
    ll res = 0;
    segment seg;

    vector<pair<ll, int>> delta(N);
    for (int i = 0; i < N; i ++) delta[i] = {d_0[i] - d_f[i], i};
    sort(delta.begin(), delta.end());

    // count for every A, B that d_0[A] + d_f[B] + 1 <= d_0[B] + d_f[A] + 1,
    // d_0[A] - d_f[A] <= d_0[B]- d_f[B], delta[A] <= delta[B]
    // all elements such that d_0[A] + d_f[B] + 1 >= D,
    // d_0[A] >= D - d_f[B] - 1
    for (int i = 0; i < N; i ++) {
        auto [_, B] = delta[i];
        res += seg.query(D - d_f[B] - 1, N + 1); // count all valid A
        seg.update(d_0[B], 1);
    }
    
    // remove the edges that are already present in the graph, that have 
    // been counted as they doesn't decrese the distance from 0 to N - 1.
    res -= M;
    cout << res << '\n';
}
