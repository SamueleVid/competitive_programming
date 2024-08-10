#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+7;;

struct edge {
    int a, b, c;
};

bool operator<(edge&a, edge&b) {
    return a.c < b.c;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<edge>v(m);
    for (auto &[a,b,c]:v) cin >> a >> b >> c;

    int res = 0;
    sort(v.begin(), v.end());
    map<int,int> prec;
    map<int,int> nuovi;
    int curr_c = -1;
    for (auto x : v) {
        if (x.c != curr_c) {
            prec.clear();
            if (x.c == curr_c+1) {
                prec = nuovi;
            }
            nuovi.clear();
            curr_c = x.c;
        }
        res += prec[x.a];
        res %= mod;
        res += prec[x.b];
        res %= mod;
        res ++;
        res %= mod;
        nuovi[x.a] += prec[x.b]+1;
        nuovi[x.a] %= mod;
        nuovi[x.b] += prec[x.a]+1;
        nuovi[x.b] %= mod;
    }

    cout << res << '\n';
}
