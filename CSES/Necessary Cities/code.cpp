#include <bits/stdc++.h>
 
using namespace std;
 
void dfs(int n, int p, int t, vector<vector<int>>&adj, vector<int>&open, vector<int>&low, vector<int>&city) {
    open[n] = low[n] = t++;
 
    bool pushed = 0;
    int children = 0;
    for (int x : adj[n]) {
        if (x == p) continue;
        if (open[x] == -1) {
            children ++;
            dfs(x,n,t,adj,open,low,city);
            low[n] = min(low[n],low[x]);
            if (low[x] >= open[n] && !pushed && p != -1) {
                pushed = 1;
                city.push_back(n);
            }
        }
        else {
            low[n] = min(low[n],open[x]);
        }
    }
    if (p == -1 && children > 1) city.push_back(n);
}   
 
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n+1);
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int>city;
    vector<int> open(n+1,-1),low(n+1);
 
    dfs(1,-1,0,adj,open,low,city);
 
    cout << city.size() << '\n';
    for (auto x:city) cout << x << " ";
    cout << '\n';
}
