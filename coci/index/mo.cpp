#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 262144;
constexpr int SQ = 512; 

struct segment {
    vector<ll> seg;
    segment() {
        seg.assign(2 * PW, 0);
    }
    
    // To cut in half the time I keep in mind the updates on 0 in this variable,
    // instead of updating the segtree in O(logN)
    ll zero = 0;

    void update(int x, ll d) {
        x += PW;
        while (x >= 1) {
            seg[x] += d;
            x /= 2;
        }
    }

    ll get_sol() {
        int idx = 1;
        int l = 0;
        int r = PW;
        ll d = 0;
        while (r - l > 1) {
            int m = (l + r) / 2;
            ll first_half = seg[2 * idx];
            if (l == 0) first_half += zero;
            int x = first_half + d - (m - 1);
            if (x == 0) return m - 1;
            if (x > 0) {
                d += first_half;
                idx = 2 * idx + 1;
                l = m;
            }
            else {
                idx = 2 * idx;
                r = m;
            }
        }
        return l - 1;        
    }
};

segment seg;

struct query {
    int l;
    int r;
    int q;

    bool operator<(query b) {
        if (l / SQ != b.l / SQ) {
            return l / SQ < b.l / SQ; 
        }
        if ((l / SQ) % 2) return r < b.r;
        else return r > b.r;
    }
};

void add(int x) {
    seg.zero ++;
    seg.update(x + 1, -1);
}

void remove(int x) {
    seg.zero --;
    seg.update(x + 1, 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<int> P(N);
    for (int i = 0; i < N; i ++) cin >> P[i];
    for (int i = 0; i < N; i ++) P[i] = min(P[i], N);
    
    vector<query> qs(Q);
    vector<int> res(Q);
    for (int i = 0; i < Q; i ++) {
        int l, r; cin >> l >> r;
        l --; r --;
        qs[i] = {l, r, i};
    }
    sort(qs.begin(), qs.end());

    int curr_l = 0, curr_r = -1;

    for (auto [l, r, q] : qs) {

        while (curr_r < r) {
            curr_r ++;
            add(P[curr_r]);
        }
        while (curr_r > r) {
            remove(P[curr_r]);
            curr_r --;
        }
        while (curr_l > l) {
            curr_l --;
            add(P[curr_l]);
        }
        while (curr_l < l) {
            remove(P[curr_l]);
            curr_l ++;
        }


        int sol = seg.get_sol();
        res[q] = sol;
    }

    for (auto x : res) cout << x << '\n';
}   
