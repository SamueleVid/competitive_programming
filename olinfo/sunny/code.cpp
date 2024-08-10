#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, s, e; cin >> n >> m >> s >> e;
    
    vector<pair<int,int>> adj(n+1, {INT_MAX, -1});
    vector<int> v(n+1,0);

    for (int i=0;i<m;i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a] = min(adj[a], {w,b});
        adj[b] = min(adj[b], {w,a});
    }
    int nodo = s;   
    int percorso = 0;
    while (!(s == e || v[s])) {
        v[s] = 1;
        auto [w, new_s] = adj[s];
        s = new_s;
        percorso ++;
    }
    int res = -1;
    if (s == e) res = percorso;
    cout << res << '\n'; 
}
