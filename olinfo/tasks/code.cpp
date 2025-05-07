#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MAXN = 10000 + 5;
constexpr ll MAXC = 100 + 5;

ll sol[MAXN][MAXC];

vector<ll> adj[MAXN];
ll T[MAXN];

ll C;

void dfs(int u) {

    for (auto x : adj[u]) dfs(x);
    int children = adj[u].size();

    // how many children I have considered so far, C
    vector<vector<ll>> dp(children + 1, vector<ll>(C + 1, 1e18));

    dp[0][0] = 0;

    for (int k = 1; k <= children; k ++) {
        for (int c = 0; c <= C; c ++) {
            for (int a = 0; a <= c; a ++) {
                if (sol[ adj[u][k - 1] ][c - a] >= 1e18) continue;
                if (dp[k - 1][a] >= 1e18) continue;
                dp[k][c] = min(dp[k][c], max(dp[k - 1][a], sol[ adj[u][k - 1] ][c - a]));
            }
        }  
    }
    
    for (int c = 0; c <= C; c ++) {
        sol[u][c] = dp[children][c] + T[u];
        if (c - 1 >= 0) sol[u][c] = min(sol[u][c], dp[children][c - 1]);
        if (sol[u][c] >= 1e18) sol[u][c] = 1e18;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int N; cin >> N;
    cin >> C;
    int root = -1;
    for (int i = 0; i < N; i ++) {
        int p, t; cin >> p >> t;
        if (p == -1) root = i;
        else adj[p].push_back(i);
        T[i] = t;
    }

    dfs(root);

    cout << sol[root][C] << '\n';
}
