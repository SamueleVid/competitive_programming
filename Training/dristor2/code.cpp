#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+7;

int rec(int i, vector<vector<int>>&v, int n, int m, int usati, vector<vector<int>>&dp, int total) {
    if (i == m) {
        if (usati == total) return 1;
        return 0;
    };
    if (dp[i][usati] != -1) return dp[i][usati];
    int sol = rec(i+1,v,n,m,usati,dp,total);
    for (int j=0;j<n;j++) {
        if (!(usati & (1<<j)) && v[j][i]) {
            usati ^= 1<<j;
            sol += rec(i+1,v,n,m,usati,dp,total);
            sol %= mod;
            usati ^= 1<<j;
        }
    }
    dp[i][usati] = sol;
    return sol;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m,0));
    for (int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            cin >> v[i][j];
        }
    }
    int total = 0;
    for (int i=n-1;i>=0;i--) {
        total*=2;
        for (int j=0;j<m;j++) {
            if (v[i][j]) {
                total ++;
                break;
            }
        }
    }

    vector<vector<int>> dp(m, vector<int>(1<<n,-1));
    cout << rec(0,v,n,m,0,dp,total) << '\n';
}
