#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 1048576;

struct segment {
    vector<ll> seg;

    segment() {
        seg.assign(2 * PW, 0);
    }

    void update(int x, ll d) {
        x += PW;
        seg[x] = d;
        x /= 2;
        while (x >= 1) {
            seg[x] = max(seg[2 * x], seg[2 * x + 1]);
            x /= 2;
        }
    }

    ll query(int l, int r) {
        l += PW; r += PW;
        ll res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res = max(res, seg[l]);
                l ++;
            }
            if (r % 2 == 0) {
                res = max(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};
segment seg;

ll alleggerisci(int N, int M, vector<int> V, vector<int> L, vector<int> R, vector<ll> K) {
    // se due intervalli distinti necessitano rispettiamente di X e Y palloncini aggiunti, 
    // allora X + Y è un lowerbound della soluzione.
    // trovo il sottoinsieme di intervalli distinti che richiede più pallincini, ovvero il
    // lowerbound più alto trovabile con questo metodo, che per culo coincide con la soluzione lol

    vector<ll> ps(N + 1);
    for (int i = 0; i < N; i ++) {
        ps[i + 1] = ps[i] + V[i];
    }
    
    vector<ll> value(M);
    for (int i = 0; i < M; i ++) {
        value[i] = (ps[R[i] + 1] - ps[L[i]]) - K[i];
    }

    vector<pair<int, int>> sorted(M);
    for (int i = 0; i < M; i ++) {
        sorted[i] = {L[i], i};
    }
    sort(sorted.begin(), sorted.end());

    vector<ll> dp(M);
    for (int i = M - 1; i >= 0; i --) {
        int idx = sorted[i].second;

        int k = -1;
        for (int p = PW; p >= 1; p /= 2) {
            if (p + k < M && L[sorted[p + k].second] <= R[idx]) k += p;
        }
        k ++;
        
        ll best_dp = seg.query(k, M - 1);
        dp[i] = value[idx] + best_dp;
        seg.update(i, dp[i]);
    }

    ll res = 0;
    for (int i = 0; i < M; i ++) res = max(res, dp[i]);
    return res;
}
