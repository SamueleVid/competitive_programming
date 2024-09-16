#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll N, X; cin >> N >> X;
    vector<ll> V(N);
    for (int i = 0; i < N; i ++) cin >> V[i];

    vector<ll> ps(N + 1);
    for (int i = 0; i < N; i ++) ps[i + 1] = ps[i] + V[i];

    ll res = 0;
    map<ll, ll> m;
    m[0] = 1;
    for (int i = 0; i < N; i ++) {
        // X + Y = PS[i + 1], search all Ys
        ll Y = ps[i + 1] - X;
        res += m[Y];
        m[ps[i + 1]] ++;
    }

    cout << res << '\n';
}
