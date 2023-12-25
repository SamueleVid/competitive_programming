#include <bits/stdc++.h>

using namespace std;

long long sum(int a, vector<long long>&fw) {
    long long res = 0;
    while (a>0) {
        res += fw[a];
        a -= a&-a;
    }
    return res;
}

void add(int a, int k, vector<long long>&fw) {
    while (a<fw.size()) {
        fw[a] += k;
        a += a&-a;
    }
}

int dfs(int nodo, vector<int>&tta, vector<int>&dim, vector<vector<int>>&adj) {
    int d = 1;
    for (auto x : adj[nodo]) {
        d += dfs(x,tta,dim,adj);
    }
    dim.push_back(d);
    tta.push_back(nodo);

    return d;
}

void dfs_sol(int nodo, vector<vector<int>>&adj, vector<vector<pair<int,int>>>&queries, vector<vector<pair<int,int>>>&v, vector<int>&tta, vector<int>&dim, vector<long long>&fw, vector<int>&inverse_tta, vector<long long>&res) {

    for (auto [b,c]:v[nodo]) {
        int id = inverse_tta[b]+1;
        add(id,c,fw);
        add(id+dim[id-1],-c,fw);
    }

    for (auto [b,i]:queries[nodo]) {
        int id = inverse_tta[b]+1;
        long long val = sum(id,fw);
        res[i] = val;
    }

    for (auto u : adj[nodo]) {
        dfs_sol(u,adj,queries,v,tta,dim,fw,inverse_tta,res);
    }

    for (auto [b,c]:v[nodo]) {
        int id = inverse_tta[b]+1;
        add(id,-c,fw);
        add(id+dim[id-1],c,fw);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<int>pa(n+1);
    for (int i=2;i<=n;i++) cin >> pa[i];
    int m; cin >> m;
    vector<int>pb(m+1);
    for (int i=2;i<=m;i++) cin >> pb[i];

    int k; cin >> k;
    vector<vector<pair<int,int>>>v(n+1);
    for (int i=0;i<k;i++) {
        int a,b,c; cin >> a >> b >> c;
        v[a].push_back({b,c});
    }

    vector<vector<int>> adja(n+1);
    for (int i=2;i<=n;i++) {
        adja[pa[i]].push_back(i);
    }
    vector<vector<int>> adjb(m+1);
    for (int i=2;i<=m;i++) {
        adjb[pb[i]].push_back(i);
    }

    // travel tree array + dimensione del sotto albero
    
    vector<int>tta,dim;
    dfs(1,tta,dim,adjb);
    reverse(tta.begin(), tta.end());
    reverse(dim.begin(), dim.end());

    // array che punta alla posizione nella tta dato un nodo

    vector<int> inverse_tta(m+1);
    for (int i=0;i<m;i++) inverse_tta[tta[i]]=i;

    // grafo che punta alla posizione della query a dx data quella a dx

    int q; cin >> q;
    vector<vector<pair<int,int>>>queries(n+1);
    for (int i=0;i<q;i++) {
        int a,b; cin >> a >> b;
        queries[a].push_back({b,i});
    }
    vector<long long>res(q);

    // fenwick tree che rappresenta la tta, ma 1 based

    vector<long long> fw(m+1,0);

    dfs_sol(1,adja,queries,v,tta,dim,fw,inverse_tta,res);

    for (auto x : res) cout << x << "\n";
}
