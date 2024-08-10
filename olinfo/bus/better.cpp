#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> adj;

int pianifica(int N, int L, vector<vector<int>> F) {
    for (int i = 0; i < N; i ++) {
        adj.push_back({});
    }
    for (auto l : F) {
        for (int i = 0; i < l.size(); i ++) {
            adj.push_back({});
            adj[l[i]].push_back({adj.size() - 1, 0});
            adj[adj.size() - 1].push_back({l[i], 1});
            if (i > 0) adj[adj.size() - 2].push_back({adj.size() - 1, 0});
        }
    }

    vector<int> d(adj.size(), 1e9);
    vector<bool> v(adj.size(), 0);

    d[0] = 0;
    priority_queue<pair<int,int>> pq;
    pq.push({0,0});
    while (!pq.empty()) {
        auto [_, nodo] = pq.top(); pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;

        for (auto [u, w] : adj[nodo]) {
            if (d[u] > d[nodo] + w) {
                d[u] = d[nodo] + w;
                pq.push({-d[u], u});
            }
        }
    }

    if (d[N - 1] == 1e9) return -1;
    return d[N - 1] - 1;
}
