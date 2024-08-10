#include <bits/stdc++.h>

using namespace std;

long long fuggi(int n, int m, vector<int> a, vector<int> b, vector<int> t, vector<int> r) {
    vector<vector<tuple<int,int,int>>> adj(n);
    for (int i=0;i<m;i++) {
        adj[b[i]].emplace_back(a[i],t[i],r[i]);
    }
    vector<long long>dr(n,1e18);
    vector<long long>db(n,1e18);
    vector<long long>d(n,1e18);
    vector<bool>v(n,0);
    dr[n-1]=db[n-1]=d[n-1]=0;

    priority_queue<pair<long long,int>> q;
    q.push({-d[n-1],n-1});

    while (!q.empty()) {
        int nodo = q.top().second; q.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;

        for (auto [u,t,r] : adj[nodo]) {
            if (v[u]) continue;
            if (r) {
                if (dr[u] > d[nodo]+t) {
                    dr[u] = d[nodo]+t;
                    // il poliziotto sceglierà la strada più lunga tra quella minore di partenza
                    // e quella blu forzando il semaforo (-1)
                    long long dist = max(min(dr[u],db[u]),db[u]-1);
                    if (dist < d[u]) {
                        d[u] = dist;
                        q.push({-d[u],u});
                    }
                }
            }
            else {
                if (db[u] > d[nodo]+t) {
                    db[u] = d[nodo]+t;
                    long long dist;
                    // il poliziotto sceglierà la strada più lunga tra quella minore di partenza
                    // e quella blu forzando il semaforo (-1)
                    if (dr[u] != 1e18) dist = max(min(dr[u],db[u]),db[u]-1);
                    // se non esiste una strada rossa è inutile forzare la blu
                    // accendendo il semaforo
                    else dist = db[u];

                    if (dist < d[u]) {
                        d[u] = dist;
                        q.push({-d[u],u});
                    }
                }
            }
        }
    }

    return d[0];
}
