#include <bits/stdc++.h>
 
using namespace std;
 
void dfs(int n, vector<int>&p, vector<vector<int>>&adj, vector<int>&depth, vector<int>&low, vector<int>&art) {
 
    int children = 0;
    bool contato = false;
    for (int x : adj[n]) {
        if (x == p[n] && !contato) {
            contato = true;
            continue;
        }
        if (depth[x] == -1) {
            children ++;
            
            p[x]=n;
            low[x]=depth[x]=depth[n]+1;
            
            dfs(x,p,adj,depth,low,art);
            
            low[n] = min(low[n],low[x]);
            
            if (low[x] >= depth[n] && p[n] != -1) {
                art[n]=1;
            }
        }
        else {
            low[n] = min(low[n],depth[x]);
        }
    }
    if (p[n] == -1 && children > 1) art[n]=1;
}   
 
int calc_lca(int a, int b, int n, vector<vector<int>>&binlift, vector<int>&depth) {
    if (depth[a] < depth[b]) swap(a,b);
    for (int pw=(int)ceil(log2(n))+10-1;pw>=0;pw--) {
        if (depth[binlift[a][pw]] >= depth[b]) {
            a = binlift[a][pw];
        }
    }
    if (a == b) return a;
    for (int pw=(int)ceil(log2(n))+10-1;pw>=0;pw--) {
        if (binlift[a][pw] != binlift[b][pw]) {
            a = binlift[a][pw];
            b = binlift[b][pw];
        }
    }
    return binlift[a][0];
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>>adj(n+1);
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> depth(n+1,-1),low(n+1),art(n+1,0), p(n+1);
    p[1]=-1;
    depth[1]=0;
    dfs(1,p,adj,depth,low,art);
 
    vector<vector<int>>binlift(n+1, vector<int>((int)ceil(log2(n))+10,1));
    for (int i=0;i<ceil(log2(n))+10;i++) {
        for (int j=1;j<=n;j++) {
            if (i==0) {
                if (j == 1) binlift[j][i]=1;
                else binlift[j][i] = p[j];
                continue;
            }
            binlift[j][i]=binlift[binlift[j][i-1]][i-1];
        }
    }
 
    while (q--) {
        int a, b, c; cin >> a >> b >> c;
 
        // aint no way succede davvero. Skill issue.
        if (a == c || b == c) {
            cout << "NO" << '\n';
            continue; 
        }
 
        if (a == b) {
            cout << "YES" << '\n';
            continue;
        }
 
        // could be removed and would still work
        if (!art[c]) {
            cout << "YES" << '\n';
            continue;
        }
 
        int lca = calc_lca(a,b,n,binlift,depth);
 
        int a1 = a, b1 = b;
        for (int pw=(int)ceil(log2(n))+10-1;pw>=0;pw--) {
            if (depth[binlift[a1][pw]] > max(depth[c],depth[lca])) {
                a1 = binlift[a1][pw];
            }
            if (depth[binlift[b1][pw]] > max(depth[c],depth[lca])) {
                b1 = binlift[b1][pw];
            }
        }
 
        if (a == b) {
            cout << "YES" << '\n';
            continue; 
        }
 
        // se c è in mezzo alle palle e non puoi sorvolarlo skillissue
        // a1 è il tentativo di andare da A all'LCA fermandosi in mezzo a C.
        // p[a1]==c controlla se si è fermato prima di C, a != lca controlla se
        // effettivamente a1 sta sotto l'LCA: un caso dove a=lca e p[a]=c darebbe come No,
        // mentre in realtà non servirebbe salire.
        if (p[a1] == c && low[a1] >= depth[c] && a != lca) {
            cout << "NO" << '\n';
            continue;
        }
        if (p[b1] == c && low[b1] >= depth[c] && b != lca) {
            cout << "NO" << '\n';
            continue;
        }
 
        cout << "YES" << '\n';
    }
}
