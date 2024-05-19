#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll comunica(int n, int m, int k, int s, int e, vector<int> a, vector<int> b, vector<int> t, vector<int> d){
    ll mult = ((ll)k*((ll)k-1))/2;
    vector<vector<pair<int,ll>>>adj(n);
    for (int i=0;i<m;i++) {
        adj[a[i]].push_back({b[i], (ll)k*(ll)t[i]-mult*(ll)d[i]});
        adj[b[i]].push_back({a[i], (ll)k*(ll)t[i]-mult*(ll)d[i]});
    }

    vector<ll>dist(n,1e18);
    dist[s] = 0;
    vector<bool>v(n);
    priority_queue<pair<ll,int>>pq;
    pq.push({0,s});
    while (!pq.empty()) {
        auto [_, nodo] = pq.top(); pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;
        for (auto [u, w] : adj[nodo]) {
            ll new_d = dist[nodo] + w;
            if (dist[u] > new_d) {
                dist[u] = new_d;
                pq.push({-dist[u],u});
            }
        }
    }
  
    return dist[e];
}
