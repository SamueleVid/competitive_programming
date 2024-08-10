#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
ll mod = 1e9+7;
ll invtwo = 500000004;
 
int main()  {
    ll n; cin >> n;
    ll tot = 0;
    for (ll i=1;i<=sqrt(n);i++) {
        ll s = (ll)(n/i)%mod;
        tot += ( s - i + 1 ) * i;
        tot %= mod;
        tot += ( ( s * (s+1) - i * (i+1)) % mod ) *invtwo;
        tot %= mod;
    }
    cout << tot << '\n';
}
