#include <bits/stdc++.h>
using namespace std;
#pragma optimize("Ofast");
#define ll long long

constexpr ll MAXN = 2 * 1e5;
constexpr ll PW = (1ll << 20);

struct elem {
    ll a, b, c;

    bool operator<(elem b) {
        return a < b.a;
    }
};

struct segment {
    vector<ll> seg;
    vector<ll> lazy;
    segment() {
        seg.assign(2 * PW, 0);
        lazy.assign(2 * PW, 0);
    }

    void push_lazy(int idx, int l, int r) {
        seg[idx] += lazy[idx];
        if (r - l > 1) {
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    void update(int idx, int l, int r, int ql, int qr, ll x) {
        push_lazy(idx, l, r);
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            lazy[idx] += x;
            push_lazy(idx, l, r);
            return;
        }

        update(2 * idx    , l, (l + r) / 2, ql, qr, x);
        update(2 * idx + 1, (l + r) / 2, r, ql, qr, x);
        seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
    }

    void add(int l, int r, ll x) {
        update(1, 0, PW, l, r, x);
    }

    ll query(int idx, int l, int r, int ql, int qr) {
        push_lazy(idx, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) {
            return seg[idx];
        }

        ll res = 0;
        res = max(res, query(2 * idx    , l, (l + r) / 2, ql, qr));
        res = max(res, query(2 * idx + 1, (l + r) / 2, r, ql, qr));
        
        return res;
    }

    ll get_min_X(int pos_kth_elem) {
        return query(1, 0, PW, 0, pos_kth_elem + 1);
    }
};  

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, K; cin >> N >> K;
    vector<elem> enemy(N);
    for (int i = 0; i < N; i ++) {
        cin >> enemy[i].a >> enemy[i].b >> enemy[i].c;
    }
    
    sort(enemy.begin(), enemy.end());
    vector<pair<int, int>> sorted_b(N);
    for (int i = 0; i < N; i ++) sorted_b[i] = {enemy[i].b, i};
    sort(sorted_b.begin(), sorted_b.end());
    
    segment seg;
    set<int> kth_pos;

    ll min_sum = 1e18;
    for (auto [Y, idx] : sorted_b) {
      
        seg.add(idx, idx + 1, enemy[idx].a);
        seg.add(idx + 1, PW, -enemy[idx].c);

        kth_pos.insert(idx);
        if (kth_pos.size() > K) kth_pos.erase(*kth_pos.rbegin());

        // what is the min X to slay the Kth available enemy (sorted by a_i) ?
        if (kth_pos.size() == K) {
            min_sum = min(min_sum, Y + seg.get_min_X(*kth_pos.rbegin()));
        }
    }

    cout << min_sum << '\n';
}
