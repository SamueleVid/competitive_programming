#include <bits/stdc++.h>
#define ll long long
#define cx complex<double long>
#define m 1000000007
#define root1 exp(2i*(M_PI/3))
#define root2 exp(4i*(M_PI/3))
#define inv3 333333336

using namespace std;

ll fp(ll n) {
    if (n==1) return 2;
    ll h = fp(n/2);
    h = (h*h)%m;
    if (n%2) h = (h*2)%m;
    return h;
}

ll solve(ll n) {
    int z = ((n%3)*2)%3;
    ll a = fp(n);
    // (x+1)^n for x = root1 and x = root2
    cx b1 = exp(2i*(M_PI*1*(n%6)/6));
    cx b2 = exp(2i*(M_PI*5*(n%6)/6));
    for (int i=0;i<3-z;i++) {
        b1 *= root1;
        b2 *= root2;
    }
    b1 += b1.real() > 0 ? 0.5 : -0.5;
    b2 += b2.real() > 0 ? 0.5 : -0.5;
    ll b = b1.real() + b2.real();
    ll res = (a + b)%m;
    res = (res * inv3)%m;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        cout << solve(n) << '\n';
    }
}
