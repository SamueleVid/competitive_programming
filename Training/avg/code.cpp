#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ll n, k; cin >> n >> k;
    vector<ll>v(n);
    for (auto &x:v) cin >> x;
    ll somma = 0;
    for (int i=0;i<n;i++) {
        somma += v[i];
    }
    ll goal = k*n;
    if (somma == goal) {
        cout << 0 << '\n';
        return 0;
    }
    if (goal > somma) {
        cout << 1 << '\n';
        return 0;
    }
    sort(v.rbegin(), v.rend());
    for (int i=0;i<n;i++) {
        somma -= (v[i]-1);
        if (goal >= somma) {
            cout << i+1 << '\n';
            return 0;
        }
    }
    cout << n << '\n';
}
