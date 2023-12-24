#include <bits/stdc++.h>
 
using namespace std;
 
const int mod = 1e9+7;
 
void dfs(int n, vector<vector<int>>&adj, vector<int>&v, vector<int>&toposort) {
    if (v[n] == 1) {
        cout << "IMPOSSIBLE" << '\n';
        exit(0);
    }
    if (v[n] == 2) return;
    v[n] = 1;
    for (auto x : adj[n]) dfs(x,adj,v,toposort);
    v[n]=2;
    toposort.push_back(n);
 
}
 
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n+1);
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
    }
    vector<int>v(n+1,0);
    vector<int>toposort;
    for (int i=1;i<=n;i++) dfs(i,adj,v,toposort);
    reverse(toposort.begin(), toposort.end());
    vector<long long>dp(n+1,0);
    dp[1]=1;
    for (auto i : toposort) {
        for (auto x : adj[i]) {
            dp[x] += dp[i];
            dp[x] %= mod;
        }
    }
    cout << dp[n] << '\n';
}
