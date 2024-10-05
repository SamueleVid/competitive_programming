#include <bits/stdc++.h>
using namespace std;

constexpr int PW = 2097152;

struct segment {
    vector<int> seg;

    segment() {
        seg.resize(2 * PW, 0);
    }
    segment(vector<int> &v, int N) {
        seg.resize(2 * PW, 0);
        for (int i = 0; i < N; i ++) seg[PW + i] = v[i];
        for (int i = PW - 1; i >= 1; i --) seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    }

    void update(int x, int d) {
        x += PW;
        seg[x] = d;
        x /= 2;
        while (x >= 1) {
            seg[x] = max(seg[2 * x], seg[2 * x + 1]);
            x /= 2;
        }
    }

    int query(int l, int r) {
        l += PW; r += PW;
        int res = 0;
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

int sbugiarda(int N, vector<int> H) {
    vector<int> sx(N), dx(N);
    segment seg_sx, seg_dx;
    vector<int> limit_sx(N), limit_dx(N);

    stack<int> s;
    for (int i = 0; i < N; i ++) {
        while (!s.empty() && H[s.top()] < H[i]) s.pop();
        if (s.empty()) limit_sx[i] = -1;
        else limit_sx[i] = s.top();
        s.push(i);
    }

    while (!s.empty()) s.pop();
    for (int i = N - 1; i >= 0; i --) {
        while (!s.empty() && H[s.top()] < H[i]) s.pop();
        if (s.empty()) limit_dx[i] = PW;
        else limit_dx[i] = s.top();
        s.push(i);
    }


    for (int i = 0; i < N; i ++) {
        int limit = limit_sx[i];
        sx[i] = 1 + seg_sx.query(limit + 1, i);
        seg_sx.update(i, sx[i]);
    }

    for (int i = N - 1; i >= 0; i --) {
        int limit = limit_dx[i];
        dx[i] = 1 + seg_dx.query(i, limit - 1);
        seg_dx.update(i, dx[i]);
    }

    vector<pair<int, int>> h_sorted(N);
    for (int i = 0; i < N; i ++) h_sorted[i] = {H[i], i};
    sort(h_sorted.begin(), h_sorted.end());

    vector<int> comp_H(N);
    int curr = 0;
    for (int i = 0; i < N; i ++) {
        if (i > 0 && h_sorted[i - 1].first != h_sorted[i].first) curr ++;
        comp_H[h_sorted[i].second] = curr;
    }

    vector<int> best_sx(N); // compressed height, best sx

    int res = 0;
    for (int i = 0; i < N; i ++) {
        // scelgo solo i come picco
        res = max(res, sx[i] + dx[i] - 1); 
        // scelgo i come picco destro e un altro con H uguale come picco sinsitro
        res = max(res, best_sx[comp_H[i]] + dx[i]);
        best_sx[comp_H[i]] = max(best_sx[comp_H[i]], sx[i]);
    }

    return res;
}
