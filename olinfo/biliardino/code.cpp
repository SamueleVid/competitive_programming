#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N;
constexpr int PW = 1048576;
vector<ll> T;
vector<ll> dp;

struct segment {
    vector<ll> seg;

    segment() {
        seg.assign(2 * PW, 1e9);
        for (int i = 0; i < N; i ++) seg[PW + i] = T[i];
        for (int i = PW - 1; i > 0; i --) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }

    ll query(int idx, int l, int r, int ql, int qr, int trg) {
        if (qr <= l || r <= ql) return N;
        if (seg[idx] >= trg) return N;
        if (r - l == 1) return l;
         
        ll sx = query(2 * idx    , l, (l + r) / 2, ql, qr, trg);
        if (sx != N) return sx;
        ll dx = query(2 * idx + 1, (l + r) / 2, r, ql, qr, trg);
        return dx;
    }
    
    ll muraglia(int l, int r, int trg) {
        return query(1, 0, PW, l, r, trg);
    }

    ll query_min(int l, int r) {
        l += PW;
        r += PW;
        ll res = 1e9;
        while (l <= r) {
            if (l % 2 == 1) {
                res = min(res, seg[l]);
                l ++;
            }
            if (r % 2 == 0) {
                res = min(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};
segment seg;

ll calc_time(ll pos, ll start_time) {
    ll next_player = seg.muraglia(pos, N, start_time);
    return (next_player - pos) * start_time + dp[next_player];
}

void inizia(int N, int T[]) {
    ::N = N;
    ::T.resize(N);
    for (int i = 0; i < N; i ++) ::T[i] = T[i];
    
    seg = segment();

    dp.resize(N + 1);
    dp[N] = 0;
    for (int i = N - 1; i >= 0; i --) dp[i] = calc_time(i, T[i]);
}

ll passaggio(int L, int R) {
    return dp[L] - calc_time(R, seg.query_min(L, R));
}
