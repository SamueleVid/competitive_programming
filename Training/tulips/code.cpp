#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<ll>v(n);
    for (auto &x:v) cin >> x;
    
    vector<vector<ll>>dp(k,vector<ll>(n,0));
    
    dp[0][0]=v[0];
    for (int i=0;i<n;i++) {
        dp[0][i] = min(dp[0][i-1],v[i]);
    }
    
    for (int j=1;j<k;j++) {
        vector<ll>maxim(n,0);
        stack<pair<int,ll>>s;
        for (int i=j;i<n;i++) {
            
            maxim[i] = dp[j-1][i-1];
                
            while (!s.empty() && v[s.top().first] >= v[i]) {
                int x = s.top().first; s.pop();
                maxim[i] = max(maxim[i],maxim[x]);
            }        
            
            if (s.empty() || s.top().second < maxim[i]+v[i]) s.push({i,maxim[i]+v[i]});
            
            dp[j][i] = s.top().second;
        }
    }
    
    cout << dp[k-1][n-1] << '\n';
}
