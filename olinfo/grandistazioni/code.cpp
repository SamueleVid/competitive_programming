#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 3e5 + 5;
vector<pair<int, ll>> adj[MAXN];
int h[MAXN];
ll d[MAXN];
bool v[MAXN];
pair<int, ll> tree[MAXN];

void dijkstra(int N, int s) {
    fill(d, d + MAXN, 1e18);
    fill(v, v + MAXN, 0);
    d[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({-d[s], s});

    while (!pq.empty()) {
        auto [_, u] = pq.top(); pq.pop();
        if (v[u]) continue;
        v[u] = 1;
        for (auto [x, w] : adj[u]) {
            if (d[x] > d[u] + w) {
                d[x] = d[u] + w;
                pq.push({-d[x], x});
                tree[x] = {u, w};
            }
        }
    }
} 

ll viaggia(int N, int M, vector<int> A, vector<int> B, vector<int> T, vector<int> V, vector<int> W) {

    fill(adj, adj + MAXN, vector<pair<int, ll>>());
    fill(tree, tree + MAXN, pair<int, ll>());
    tree[N - 1] = {N - 1, 0};

    for (int i = 0; i < M; i ++) {
        adj[B[i]].push_back({A[i], T[i]});
    }

    dijkstra(N, N - 1);

    ll res = 0;
    int curr = 0;
    vector<bool> used(N);
    vector<int> curr_path;
    while (curr != N - 1) {
        curr_path.push_back(curr);

        if (!used[curr] && V[curr] != -1) {
            used[curr] = 1;

            ll arcone = 0;
            int prox = V[curr];
            res += W[curr];
            int destination = tree[curr].first;

            for (int i = curr_path.size() - 1; i >= 0; i --) {
                auto nodo = curr_path[i];
                arcone += tree[nodo].second;
                tree[nodo] = {destination, arcone};
            }

            curr_path.clear();

            curr = prox;
            continue;
        }

        used[curr] = 1;
        res += tree[curr].second;
        curr = tree[curr].first;
    }

    return res;
}
