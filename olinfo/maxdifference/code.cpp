#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll PW = 262144;

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
            lazy[2 * idx]     += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
    
    void update(int idx, int l, int r, int ql, int qr, ll d) {
        push_lazy(idx, l, r);
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) {
            lazy[idx] += d;
            push_lazy(idx, l, r);
            return;
        }
        update(2 * idx    , l, (l + r) / 2, ql, qr, d);
        update(2 * idx + 1, (l + r) / 2, r, ql, qr, d);
        seg[idx] = max(seg[2 * idx], seg[2 * idx + 1]);
    }
    
    void azzera(int idx, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) return;
        if (r - l > 1) {
            azzera(2 * idx    , l, (l+r)/2, ql, qr);
            azzera(2 * idx + 1, (l+r)/2, r, ql, qr);
        }

        seg[idx] = 0;
        lazy[idx] = 0;
    }

    ll maxim() {
        return seg[1];
    }
};

segment seg; // max[i, j] - min[i, j] + dp[j + 1]

void solve() {
    
    int N; cin >> N;
    vector<ll> A(N);
    for (int i = 0; i < N; i ++) cin >> A[i];
    
    stack<array<ll, 3>> minstack, maxstack; // min/max, start, end
    minstack.push({(ll)-1e18,N,N});
    maxstack.push({(ll)1e18,N,N});
    
    vector<ll> dp(N + 1, 0);
    
    for (int i = N - 1; i >= 0; i --) {
        seg.update(1, 0, PW, i, i + 1, dp[i + 1]);

        int last = i;
        while (!minstack.empty() && A[i] < minstack.top()[0]) {
            seg.update(1, 0, PW, minstack.top()[1], minstack.top()[2] + 1, +minstack.top()[0]);

            last = minstack.top()[2];
            minstack.pop();
        }
        minstack.push({A[i], i, last});
        seg.update(1, 0, PW, minstack.top()[1], minstack.top()[2] + 1, -minstack.top()[0]);

        last = i;
        while (!maxstack.empty() && A[i] > maxstack.top()[0]) {
            seg.update(1, 0, PW, maxstack.top()[1], maxstack.top()[2] + 1, -maxstack.top()[0]);

            last = maxstack.top()[2];
            maxstack.pop();
        }
        maxstack.push({A[i], i, last});
        seg.update(1, 0, PW, maxstack.top()[1], maxstack.top()[2] + 1, maxstack.top()[0]);

        dp[i] = seg.maxim();
    }

    cout << dp[0] << '\n';

    seg.azzera(1, 0, PW, 0, N + 2);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
}
