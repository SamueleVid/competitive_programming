#include <bits/stdc++.h>
using namespace std;
#define ll long long

pair<int,ll> max_dist(int n, vector<vector<pair<int,ll>>> &adj, int da_ignorare) {
    ll res = 0;
    int tipo_distante = n;
    for (auto [u,w] : adj[n]) {
        if (u == da_ignorare) continue;
        auto [tipo, risultato] = max_dist(u,adj,n);
        risultato += w;
        if (risultato > res) {
            tipo_distante = tipo;
            res = risultato;
        }
    }
    return {tipo_distante, res};
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, k; cin >> n >> k;
    ll sum = 0;
    vector<vector<pair<int,ll>>> adj(n+1);
    for (int i=0;i<n-1;i++) {
        int a, b; cin >> a >> b;
        ll c; cin >> c;
        sum += c;
        
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    if (k == 1) {
        cout << 2 * sum << '\n';
        return 0;
    }
    if (n == 2) {
        cout << sum << '\n';
        return 0;
    }  

    auto [tipo, dist] = max_dist(1,adj,-1);

    ll massimo = max_dist(tipo,adj,-1).second;

    cout << sum * 2 - massimo << '\n';
}
