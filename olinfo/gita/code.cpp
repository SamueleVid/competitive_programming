#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>,
rb_tree_tag, tree_order_statistics_node_update> indexed_tree;

int dfs(int nodo, int to_ignore, vector<vector<int>>&adj, indexed_tree &s, vector<int> &d, vector<int>&c, int tipo) {
    
    int res;
    // vuole dolce
    if (tipo == 0) res = 0;
    // vuole salato
    else res = 1e9;

    int count = 0;
    for (auto u : adj[nodo]) {
        if (u == to_ignore) continue;
        count ++;
    }

    // è una foglia
    if (!count) {
        return *s.find_by_order(c[nodo]);
    }

    for (auto u : adj[nodo]) {
        if (u == to_ignore) continue;
        s.insert(d[u]);
        int curr = dfs(u,nodo,adj,s,d,c,(tipo+1)%2);
        s.erase(d[u]);
        if ((tipo==0 && curr > res) || (tipo==1 && curr < res)) {
            res = curr;
        }
    }
    return res;
}

int visita(int n, vector<int> &a, vector<int> &b, vector<int> &d,
vector<int> &c) {
    vector<vector<int>> adj(n);
    for (int i=0;i<n-1;i++) {
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }
    // prima fabio = dolci :>
    // poi giacomo = salato
    indexed_tree s;
    s.insert(d[0]);
    return dfs(0,-1,adj,s,d,c,0);

}
