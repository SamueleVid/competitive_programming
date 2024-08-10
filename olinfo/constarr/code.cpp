#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;

vector<ll> merge(vector<ll>&a, vector<ll>&b, int m) {
    vector<ll> res(m,0);
    for (int i=0;i<m;i++) {
        for (int j=0;j<m;j++) {
            int id = i+j<m ? i+j : i+j-m;
            res[id] += (a[i] * b[j])%mod;
            res[id] %= mod;
        }
    }
    return res;
}

vector<ll> fastpow(vector<ll>&a, vector<ll>&start, ll n, int m) {
    if (n == 1) return start;
    vector<ll> res = fastpow(a,start,n/2,m);
    res = merge(res,res,m);
    if (n%2) res = merge(res,start,m);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    ll n; cin >> n;
    int m; cin >> m;
    ll l, r; cin >> l >> r;
    int k; cin >> k;

    vector<ll> start(m,0);
    vector<ll> curr(m,0);

    for (int i=l;i<l+m&&i<=r;i++) {
        curr[i%m] = start[i%m] = ceil((double)(r-i+1)/m);
    }
    
    curr = fastpow(curr, start, n, m);
    
    cout << curr[k] << '\n';
}
