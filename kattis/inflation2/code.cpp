#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    vector<ll> p(N);
    for (ll i = 0; i < N; i ++) cin >> p[i];
    
    map<ll, ll> m;
    for (auto x : p) m[x] ++;

    ll inflat = 0;
    ll sum = 0;
    for (auto [a, b] : m) sum += a * b;
    
    ll Q; cin >> Q;
    while (Q --) {
        string q; cin >> q;
        if (q == "INFLATION") {
            ll d; cin >> d;
            inflat += d;
            sum += d * N;
        }
        else {
            ll x, y; cin >> x >> y;
            ll real_x = x - inflat, real_y = y - inflat;
            ll d = m[real_x];
            sum -= real_x * d;
            sum += real_y * d;
            m[real_y] += d;
            m[real_x] -= d;
        }

        cout << sum << '\n';
    }
}
