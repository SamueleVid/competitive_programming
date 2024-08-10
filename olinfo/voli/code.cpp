#include <bits/stdc++.h>

using namespace std;

long long dijkstra(int n, vector<vector<pair<int,int>>>&adj) {
    vector<long long>d(adj.size(),1e18);
    vector<bool>v(adj.size(),0);
    priority_queue<pair<long long, int>>pq;
    pq.push({0,0});
    d[0]=0;
    while (!pq.empty()) {
        auto [cost, nodo] = pq.top(); pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;
        for (auto [u,w] : adj[nodo]) {
            if (v[u]) continue;
            long long dist = d[nodo]+w;
            if (dist < d[u]) {
                d[u] = dist;
                pq.push({-d[u],u});
            }
        }
    }
    return d[n-1];
}

long long plan(int n, int m, int k, vector<int> a, vector<int> b,
vector<int> l, vector<int> c, vector<int> t) {
    int id = n;
    vector<vector<pair<int,int>>>adj;
    for (int i=0;i<n;i++) adj.push_back({});
    map<pair<int,int>,int> compress;
    for (int i=0;i<m;i++) {
        if (!compress.count({a[i],c[i]})) {
            compress[{a[i],c[i]}] = id;
            adj.push_back({});
            adj[id].push_back({a[i],0});
            adj[a[i]].push_back({id,t[c[i]]});
            id ++;

        }
        if (!compress.count({b[i],c[i]})) {
            compress[{b[i],c[i]}] = id;
            adj.push_back({});
            adj[id].push_back({b[i],0});
            adj[b[i]].push_back({id,t[c[i]]});
            id ++;
        }
        adj[ compress[{b[i],c[i]}] ].push_back({ compress[{a[i],c[i]}] ,l[i]});
        adj[ compress[{a[i],c[i]}] ].push_back({ compress[{b[i],c[i]}] ,l[i]});
    }

    return dijkstra(n,adj);
}
