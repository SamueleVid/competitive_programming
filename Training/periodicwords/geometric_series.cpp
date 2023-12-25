#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;
    string s; cin >> s;

    const ll x = 29;
    const ll m = 1e9+7;
    vector<ll>p(n+1);
    p[0] = 1;
    for (int i=1;i<n+1;i++) p[i] = (p[i-1]*x)%m;

    vector<ll>h(n+1);
    h[0] = s[0] - 'a' + 1;
    for (int i=1;i<n+1;i++) h[i] = (h[i-1] + ((s[i] - 'a' + 1) * p[i])%m)%m;

    vector<vector<int>>divs(n+1);
    for (int i=1;i<n+1;i++) {
        for (int j=i+i;j<n+1;j+=i) {
            divs[j].push_back(i);
        }
    }

    int q; cin >> q;
    while (q-- > 0) {
        int l, r; cin >> l >> r;
        int lenght = r-l+1;
        ll hash = h[r];
        if (l > 0) hash = (hash - h[l-1] + m)%m; 
        for (int d=divs[lenght].size()-1;d>=0;d--) {
            int i = divs[lenght][d];
            ll hash_i = h[l+i-1];
            if (l > 0) hash_i = (hash_i - h[l-1] + m)%m;
            // al posto di dividere geom_series per (x^i - 1), moltiplico hash per x^i-1.
            // perché a=b/k sse ak=b.
            ll geom_series = p[lenght] - 1;
            if (geom_series < 0) geom_series += m;

            ll res = (hash_i * geom_series) % m;
            ll denom = p[i] - 1;
            if (denom < 0) denom += m;

            ll new_hash = (hash * denom) % m;

            if (res == new_hash) {
                cout << "YES" << '\n';
                goto yes;
            }
        }
        cout << "NO" << '\n';
        continue;

        yes: ;
    }
}
