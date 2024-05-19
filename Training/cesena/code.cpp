#include <bits/stdc++.h>
using namespace std;

int visita(int N, int M, int K, vector<int> S, vector<int> A,
vector<int> B, vector<int> T) {
    vector<vector<pair<int,int>>>adj(N);
    for (int i=0;i<M;i++) {
        adj[A[i]].push_back({B[i],T[i]});
        adj[B[i]].push_back({A[i],T[i]});
    }

    vector<int>d(N,0);
    vector<bool>v(N);
    priority_queue<pair<int,int>>pq;
    pq.push({K,0});
    d[0] = K;
    while (!pq.empty()) {
        int nodo = pq.top().second; pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;
        for (auto [u, w] : adj[nodo]) {
            if (d[u] < min(d[nodo],w)) {
                d[u] = min(d[nodo],w);
                pq.push({d[u],u});
            }
        }
    }

    int res = 0;
    vector<int> quanti_cadono(K+1,0);
    for (auto x : S) quanti_cadono[d[x]]++;
    for (int i = 1; i <= K; i++) res = min(res + quanti_cadono[i], i);

    return res;
}
