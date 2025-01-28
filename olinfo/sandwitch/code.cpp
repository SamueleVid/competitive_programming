#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll PW = 524288;

struct segment {
    vector<ll> seg;
    segment() {
        seg.assign(2 * PW, -1e18);
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

int bsa(vector<pair<ll, int>> &order, ll trg) {
    ll k = -1;
    for (ll p = PW; p >= 1; p /= 2) {
        if (p + k < order.size() && order[p + k].first < trg) k += p;
    }
    k ++;
    return k;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i ++) cin >> A[i];

    vector<ll> ps(N + 1);
    for (int i = 0; i < N; i ++) ps[i + 1] = ps[i] + A[i];
    vector<ll> dp(N + 1);

    vector<pair<ll, int>> order;
    
    for (int i = 0; i <= N; i ++) {
        order.push_back({ps[i], i});
    }
    sort(order.begin(), order.end());

    vector<int> inv_order(N + 1);
    for (int i = 0; i < N; i ++) inv_order[order[i].second] = i;

    segment seg;
    seg.update(bsa(order, ps[N]), 0);
    
    for (int i = N - 1; i >= 0; i --) {
        // an interval [i, k] is positive if [0, k] - [0, i) is positive. so if [0, k] >= [0, i) + 1
        int lb = bsa(order, ps[i] + 1);
        ll res = seg.query(lb, PW - 1);
        if (res == -1e18) continue;
        dp[i] = res + 1;
        seg.update(inv_order[i], dp[i]);
        // I'm saving the result on the number before i (inv_order is shifted by 1 because of the shift on ps),
        // so that next time, when I find [i', k'], I'll see this result on k' insted of k'+1 and it's linked to
        // the ps[k'] >= ps[i'] + 1 found in order.
    }

    cout << dp[0] << '\n';
}
