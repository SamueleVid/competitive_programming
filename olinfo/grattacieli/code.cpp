#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e5 + 5;
vector<pair<int,int>> adj[MAXN];
int d[MAXN];
bool v[MAXN];

ll costruisci(int N, int M, vector<long long>& H, vector<int>& A,
vector<int>& B, vector<int>& C) {
    for (int i = 0; i < M; i ++) {
        adj[A[i] + 1].push_back({B[i] + 1, C[i]});
    }
    for (int i = 0; i < N; i ++) {
        adj[0].push_back({i + 1, H[i]});
    }

    fill(d, d + MAXN, 1e9);
    fill(v, v + MAXN, 0);
    d[0] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0,0});

    while (!pq.empty()) {
        auto [_, nodo] = pq.top(); pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;

        for (auto [u, w] : adj[nodo]) {
            if (d[nodo] + w < d[u]) {
                d[u] = d[nodo] + w;
                pq.push({-d[u], u});
            }
        }
    }

    ll res = 0;
    for (int i = 0; i < N + 1; i ++) res += d[i];

    return res;
}
