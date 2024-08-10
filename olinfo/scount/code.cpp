#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll mod = 1000000007;

pair<ll,ll> gcd_e(ll a, ll b) {
    if (b == 0) {
        return {1,0};
    }
    auto [x,y] = gcd_e(b,a%b);
    return {y,x-(a/b)*y};
}

ll inv(int x) {
    ll res = gcd_e(mod,x).second;
    res += mod;
    res %= mod;
    return res;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n; cin >> n;
    vector<int> v(n);
    for (auto &x:v) cin >> x;
    
    sort(v.begin(),v.end());
    
    vector<int> appare;
    
    int curr=v[0];
    int di_seguito=0;
    int mass_seguito = 0;
    
    for (auto x:v) {
        if (x == curr) {
            di_seguito++;
        }
        else {
            appare.push_back(di_seguito);
            curr = x;
            mass_seguito = max(mass_seguito, di_seguito);
            di_seguito = 1;
        }
    }
    appare.push_back(di_seguito);
    mass_seguito = max(mass_seguito, di_seguito);
    
    ll tot_res = 1; //conto già insieme vuoto
    
    sort(appare.begin(),appare.end(),greater<int>());
    vector<ll> bcoeff(mass_seguito+1,1);
    vector<ll> inv_dp(mass_seguito+1,-1);
    vector<ll> curr_i(mass_seguito+1,0);
    for (int i=1;i<mass_seguito+1;i++) {
        inv_dp[i] = inv(i);
    }
    
    for (int i=1;i<mass_seguito+1;i++) {
        ll curr_res = 0;
    
        for (auto x:appare) {
            if (x<i) break;
            if (curr_i[x]<i) {
            
                bcoeff[x] *= (x-i+1);
                bcoeff[x] %= mod;
                bcoeff[x] *= inv_dp[i];
                bcoeff[x] %= mod;
                curr_i[x] ++;
            }
            
            ll toadd = bcoeff[x]*curr_res;
            toadd %= mod;
            toadd += bcoeff[x];
            toadd %= mod;
            curr_res += toadd;
            curr_res %= mod;
        }
    
        tot_res += curr_res;
        tot_res %= mod;    
    }
    
    cout << tot_res << '\n';
}
