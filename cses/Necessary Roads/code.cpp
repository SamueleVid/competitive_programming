#include <bits/stdc++.h>
 
using namespace std;
 
void dfs(int n, int p, int t, vector<vector<int>>&adj, vector<int>&low, vector<int>&open, vector<pair<int,int>>&bridges) {
    open[n] = low[n] = t;
 
    for (auto x : adj[n]) {
        if (p == x) continue;
        if (open[x] == -1) {
            dfs(x,n,t+1,adj,low,open,bridges);
            low[n] = min(low[n],low[x]);
            if (low[x] > open[n]) {
                bridges.push_back({n,x});
            }  
        }
        else {
            low[n] = min(low[n],open[x]);
        }
    }
}
 
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n+1);
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int>low(n+1);
    vector<int>open(n+1,-1);
    vector<pair<int,int>>bridges;
 
    dfs(1,0,0,adj,low,open,bridges);
    cout << bridges.size() << '\n';
    for (auto [a,b] : bridges) cout << a << " " << b << '\n';
