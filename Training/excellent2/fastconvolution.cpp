#include <bits/stdc++.h>
#define ll long long
#define m 1000000007
using namespace std;

// 0 elements 0 mod 3, 1 element 1 mod 3 (1), 1 element 2 mod 3 (5) for n=1
vector<ll>start {0,1,1};

vector<ll> conv(vector<ll>&a, vector<ll>&b) {
    vector<ll>res(3,0);
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            int k = i+j<3 ? i+j : i+j-3;
            res[k] += (a[i]*b[j])%m;
            res[k] %= m;
        }
    }
    return res;
}

vector<ll> f(ll n) {
    if (n == 1) return start;
    vector<ll> h = f(n/2);
    h = conv(h,h);
    if (n%2) h = conv(h,start);
    return h;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        cout << f(n)[0] << '\n';
    }
}
