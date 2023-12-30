#include <bits/stdc++.h>
#define ll long long
using namespace std;

bool can(vector<ll>&v, vector<ll>&ps, ll n, ll target, ll c) {
    ll ub = ps[n] + n*c;
    ll k=-1;
    for (ll i=1l<<(ll)log2(n);i>=1;i/=2) {
        if (k+i<n && v[k+i]<=c) k+=i;
    }
    k += 1;
    ll lb = k;
    lb += ps[n]-ps[k];
    lb -= (n-k)*c;
    return (lb <= target && target <= ub);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, k; cin >> n >> k;
    vector<ll>v(n);
    for (auto &x:v) cin >> x;
    
    ll target = k*n;
    
    sort(v.begin(), v.end());
    vector<ll>ps(n+1,0);
    for (int i=0;i<n;i++) ps[i+1]=ps[i]+v[i];    
    
    ll res = -1;
    for (ll i=1ll<<(ll)log2(1e9);i>=1;i/=2) {
        if (!can(v,ps,n,target,res+i)) res += i;
    }
    res ++;
    
    cout << res << '\n';
}
