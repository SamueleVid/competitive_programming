#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000 + 5;
const int PW = 1024;

struct segment {
    vector<ll> seg;

    segment() {
        seg.assign(2 * PW, -1);
    }

    void update(int x, ll d) {
        x += PW;
        while (x >= 1) {
            seg[x] = max(seg[x], d);
            x /= 2;
        }
    }

    ll query(int l, int r) {
        l = max(l, 0);
    
        l += PW; r += PW;
        ll res = -1;
        while (l <= r) {
            if ((l % 2) == 1) {
                res = max(res, seg[l]);
                l ++;
            }
            if ((r % 2) == 0) {
                res = max(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};

map<ll, set<ll>> adj;
map<ll, int> repetitions;
map<ll, segment> segs;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;

    set<ll> l, lr;

    for (int i = 0; i < N; i ++) {
        ll L, R; cin >> L >> R;
        if (L == R) repetitions[L] ++;
        else adj[L].insert(R);
        l.insert(L);
        lr.insert(L);
        lr.insert(R);
    }
    
    vector<ll> nodes;
    for (auto x : lr) nodes.push_back(x);
    sort(nodes.rbegin(), nodes.rend());

    for (auto x : nodes) {
        for (int j = 0; j <= N; j ++) {
            segs[x].update(j, -1);
        }
    }
    
    for (auto x : nodes) {
        for (int j = 0; j <= N; j ++) {
            
            ll res = -1;
            if (j <= repetitions[x]) res = x;
            
            for (auto u : adj[x]) {
                res = max(res, segs[u].query(j - 1 - repetitions[x], j - 1));
            }
            
            segs[x].update(j, res);
        }
    }

    int Q; cin >> Q;
    while (Q --) {
        ll X; cin >> X;
        int U, V; cin >> U >> V;

        if (!l.count(X) && U == 0) {
            cout << X << " ";
            continue;
        }
        if (!l.count(X) && U != 0) {
            cout << -1 << " ";
            continue;
        }

        ll res = segs[X].query(U, V);

        cout << res << " ";
    }
}
