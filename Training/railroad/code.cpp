#include <bits/stdc++.h>

using namespace std;

vector<long long> dijkstra(int start, int n, vector<vector<pair<int,int>>> &adj, vector<int> &p) {
    vector<long long> d(n, 1e18);
    vector<bool> v(n,0);
    priority_queue<pair<long long,int>> q;
    d[start] = 0;
    q.push({0,start});

    while (!q.empty()) {
        auto [peso, nodo] = q.top(); q.pop();

        if (v[nodo]) continue;
        v[nodo] = 1;

        for (auto [b, w] : adj[nodo]) {
            if (v[b]) continue;
            if (d[b] > d[nodo]+w) {
                d[b] = d[nodo]+w;
                p[b] = nodo;
                q.emplace(-d[b],b);
            }
        }
    }
    return d;
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<tuple<int,int,int>> edges(m);
    for (int i=0;i<m;i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].emplace_back(b,c);
        adj[b].emplace_back(a,c);
        
        edges[i] = {a,b,c};
    }
    
    vector<int> p(n);
    vector<long long> d_n1 = dijkstra(n-1, n, adj, p);
    vector<long long> d_0 = dijkstra(0, n, adj, p);

    long long sp = d_0[n-1];

    vector<bool> nodi_sp(n,0);
    int a = n-1;
    while (a != 0) {
        nodi_sp[a] = 1;
        a = p[a];
    }
    nodi_sp[0] = 1;

    long long res = 1e18;
    for (auto [a,b,c] : edges) {
        if (nodi_sp[a] && nodi_sp[b]) continue;
        long long coso_uno = d_0[a] + d_n1[b];
        long long coso_due = d_0[b] + d_n1[a];
        long long coso = min(coso_uno, coso_due);

        long long c_1 = sp-1-coso;
        if (c_1 > 0) res = min(res, c-c_1);
    }
    if (res == 1e18) res = -1;
    cout << res << '\n';
}
