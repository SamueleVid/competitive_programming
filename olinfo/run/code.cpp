#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll PW = (1<<20);

struct min_segment {
    vector<ll> seg;

    min_segment(int N, vector<ll> &v) {
        seg.assign(2 * PW, 1e18);
        for (int i = 0; i < N; i ++) seg[PW + i] = v[i];
        for (int i = PW - 1; i >= 1; i --) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    }

    ll query(int l, int r) {
        l += PW; r += PW;
        ll res = 1e18;
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

struct max_segment {
    vector<ll> seg;

    max_segment(int N, vector<ll> &v) {
        seg.assign(2 * PW, -1e18);
        for (int i = 0; i < N; i ++) seg[PW + i] = v[i];
        for (int i = PW - 1; i >= 1; i --) seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    }

    ll query(int l, int r) {
        l += PW; r += PW;
        ll res = -1e18;
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


int main() {
    int N; cin >> N;
    vector<ll> v(N);
    for (int i = 0; i < N; i ++) cin >> v[i];

    min_segment min_seg(N, v);
    max_segment max_seg(N, v);

    ll max_lunghezza = 1;
    for (int i = 0; i < N; i ++) {

        ll k = 0;
        for (ll p = PW; p >= 1; p /= 2) {
            if (k + i + p >= N) continue;
            if (min_seg.query(i, i + k + p) >= v[i]) k += p;
        }

        ll end = i + k;

        ll value = max_seg.query(i, end);

        k = 0;
        for (ll p = PW; p >= 1; p /= 2) {
            if (i + k + p <= end && max_seg.query(i + k + p, end) == value) k += p;
        }

        end = i + k;

        max_lunghezza = max(max_lunghezza, end - i + 1);
    }

    cout << max_lunghezza << '\n';
}
