#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,k; cin >> n >> k;
    vector<ll>v(n);
    for (auto &x:v) cin >> x;
    
    vector<map<int,ll>>dp_prev(k);  
    dp_prev[0][0]=0;
    for (int l=1;l<n;l++) {
        vector<map<int,ll>>dp_curr(k);  
        for (int i=0;i<k;i++) {
            for (auto [j,_] : dp_prev[i]) {
                if (i+1<k) dp_curr[i+1][l] = max(dp_prev[i][j]+v[j], dp_curr[i+1][l]);
                dp_curr[i][v[l]<v[j] ? l : j] = max(dp_prev[i][j], dp_curr[i][v[l]<v[j] ? l : j]);
            }
        }
        dp_prev = dp_curr;
    }
    
    ll res = -1e9;
    for (auto [i,_] : dp_prev[k-1]) res = max(res, dp_prev[k-1][i] + v[i]);
    cout << res << '\n';
}
