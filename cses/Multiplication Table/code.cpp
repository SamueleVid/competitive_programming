#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
 
ll f(ll x, ll n) {
    ll res = 0;
    for (ll i=1;i<=n;i++) {
        res += (ll)min(x,i*n)/i;
    }
    return res;
}
 
int main() {
    ll n; cin >> n;
    ll x = 1;
    for (ll pw=1ll<<(ll)log2(n*n);pw>=1;pw/=2) {
        if (x+pw <= n*n && f(x+pw-1, n) < (ll)(n*n)/2+1) {
            x += pw;
        }
    }
    cout << x << '\n';
}
