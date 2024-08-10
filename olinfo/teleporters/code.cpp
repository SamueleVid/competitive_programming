#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);s
    
    int n, m; cin >> n >> m;
    vector<pair<int,int>>v(n);
    for (auto &[a, b]:v) cin >> a >> b;
    
    // ogni nodo è composto da due parti:
    // una a sx 0 e una a dx 1
    //      / -> -> -> -> \
    // -> . . -> -> -> . . -> ->
    //        \  <- <-  /
    
    vector<vector<pair<int,int>>> adj(2, vector<pair<int,int>>(2000010,{-1,-1}));
    for (int i=0;i<n;i++) {
        adj[0][v[i].first] = {1,v[i].second};
        adj[0][v[i].second] = {1,v[i].first};
    }
    
    vector<int> tutti;
    for (auto [a, b]:v) {
        tutti.push_back(a);
        tutti.push_back(b);
    }
    
    sort(tutti.begin(), tutti.end());
    adj[1][0] = {0,tutti[0]};
    adj[1][tutti[2*n-1]] = {0,2000001};
    
    for (int i=0;i<2*n-1;i++) {
        adj[1][tutti[i]] = {0,tutti[i+1]};
    }
    
    vector<vector<bool>> visited(2,vector<bool>(2000010, 0));
    vector<int> components;
    int size_original = 0;
    
    int grafo = 1;
    int nodo = 0;
    while (nodo != 2000001) {
        if (grafo == 0) size_original ++;
        visited[grafo][nodo]=1;
        auto [a,b] = adj[grafo][nodo];
        grafo = a; nodo = b;
    }
        
    for (auto x:tutti) {
        if (!visited[0][x]) {
            int res = 0;
            int grafo = 0;
            int nodo = x;
            while (!visited[grafo][nodo]) {
                if (grafo == 0) res ++;
                visited[grafo][nodo]=1;
                auto [a,b] = adj[grafo][nodo];
                grafo = a; nodo = b;
            }
            components.push_back(res);
        }
        if (!visited[1][x]) {
            int res = 0;
            int grafo = 1;
            int nodo = x;
            while (!visited[grafo][nodo]) {
                if (grafo == 0) res ++;
                visited[grafo][nodo]=1;
                auto [a,b] = adj[grafo][nodo];
                grafo = a; nodo = b;
        }
            components.push_back(res);
        }
        
    }
        
    sort(components.begin(), components.end(), greater<int>());
    int old_m = m;
    for (int i=0;i<components.size()&&i<old_m;i++) {
        size_original += components[i]+2;
        m--;
    }
    
    if (m%2==0) {
        size_original += 2*m;
    }
    else {
        size_original += 2*(m-1)+1;
    }
    
    cout << size_original << '\n';
}
