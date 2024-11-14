#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll A, B, K; cin >> A >> B >> K;
    ll a = A + B + K;

    ll zp = -1;
    for (ll d = 1; d * d <= a; d ++) {
        if (a % d != 0) continue;

        if (K >= d) zp = max(zp, d);
        if (A % d == 0) zp = max(zp, d);
        if (A % (a/d) == 0) zp = max(zp, (a/d));

        if (A % d + K >= d) zp = max(zp, d);
        if (A % (a/d) + K >= (a/d)) zp = max(zp, (a/d));
    }

    cout << zp << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
