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
            
            ll hash_l = h[r-i];
            if (l > 0) hash_l = (hash_l - h[l-1] + m)%m;
            // lo porto alla stessa altezza
            hash_l = (hash_l * p[i])%m;

            ll hash_r = h[r];
            if (l+i > 0) hash_r = (hash_r - h[l+i-1] + m)%m;

            // [l,r-i) == [l+i,r]
            if (hash_r == hash_l) {
                cout << "YES" << '\n';
                goto yes;
            }
        }
        cout << "NO" << '\n';
        continue;

        yes: ;
    }
}
