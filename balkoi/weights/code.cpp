#include <bits/stdc++.h>
using namespace std;
#define ll long long
#pragma GCC optimize("Ofast")

constexpr ll MOD = 998244353;
constexpr ll MAXN = 4e5 + 5;
constexpr ll PW = 1 << 20;

struct llbig {
    // k * 2 ^ ex
    ll k = 0;
    ll ex = 0;

    llbig(ll _k = 0, ll _ex = 0) {
        k = _k; ex = _ex;
    }

    bool operator<(llbig &b) {
        if (k == 0) return 0 < 1;
        if (b.k == 0) return 1 < 0;
        return ex + log2(k) < b.ex + log2(b.k);
    }

    ll fp(ll a, ll p) {
        if (!p) return 1;
        ll h = fp(a, p / 2);
        h = (h * h) % MOD;
        if (p % 2) h = (h * a) % MOD;
        return h;
    }

    ll get_value() {
        ll exponential = fp(2, ex);
        return (k * exponential) % MOD;
    }
};


struct segment {
    vector<llbig> seg;

    segment() {
        seg.resize(2 * PW);
    }

    void update(int x, llbig d) {
        x += PW;
        seg[x] = d;
        x /= 2;
        while (x >= 1) {
            seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
            x /= 2;
        }
    }

    llbig query(int l, int r) {
        l += PW; r += PW;
        llbig res(0);
        while (l <= r) {
            if (l % 2 == 1) {
                res = merge(res, seg[l]);
                l ++;
            }
            if (r % 2 == 0) {
                res = merge(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }

    llbig merge(llbig a, llbig b) {
        return (a < b) ? b : a;
    }
};
segment seg_euler_tour;

vector<int> adj[MAXN];
int depth[MAXN];
vector<int> euler_tour;
int l_pos_et[MAXN];
int r_pos_et[MAXN];

void dfs(int u) {
    l_pos_et[u] = euler_tour.size();
    euler_tour.push_back(u);
    for (auto x : adj[u]) {
        depth[x] = depth[u] + 1;
        dfs(x);
    }
    r_pos_et[u] = euler_tour.size();
    euler_tour.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; i ++) {
        char c; int u; 
        for (int k = 0; k < 2; k ++) {
            cin >> c >> u;
            u --;
            if (c == 'W') u += N;
            adj[i].push_back(u);
        }
    }

    vector<ll> weight(N + 1);
    for (int i = 0; i < N + 1; i ++) {
        ll w; cin >> weight[i];
    }

    depth[0] = 0;
    dfs(0);
    for (int i = 0; i < N + 1; i ++) {
        seg_euler_tour.update(l_pos_et[N + i], llbig(weight[i], depth[N + i]));
    }

    while (Q --) {
        int op; cin >> op;
        
        if (op == 1) {
            ll k, w; cin >> k >> w; 
            k --;
            
            weight[k] = w;
            seg_euler_tour.update(l_pos_et[N + k], llbig(weight[k], depth[N + k]));
        }
        else {
            ll s; cin >> s;
            s --;
            
            llbig res = seg_euler_tour.query(l_pos_et[s], r_pos_et[s]);
            res.ex -= depth[s];
            cout << res.get_value() << '\n';
        }
    }
}
