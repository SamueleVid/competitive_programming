#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 131072;

struct segment {
    vector<ll> seg;
    
    segment(vector<ll> &v, int N) {
        seg.resize(2 * PW, 1e18);
        for (int i = 0; i < N; i ++) seg[PW + i] = v[i];
        for (int i = PW - 1; i > 0; i --) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
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

struct line {
    ll m, q;

    ll value(int x) {
        return m * x + q;
    }
};

ll find_intersection(line a, line b) {
    return ( (b.q - a.q) + (a.m - b.m) - 1 ) / (a.m - b.m);
}

ll get_value(deque<pair<line, ll>> &lines, int x) {
    int k = 0;
    for (int p = PW; p >= 1; p /= 2) {
        if (k + p < lines.size() && lines[k + p].second <= x) k += p;
    }
    return lines[k].first.value(x);
}

void add_line_at_beginning(deque<pair<line, ll>> &lines, line new_line) {
    // the y-intercept of new_line is lower than all of lines' functions

    // remove all the lines that never intersect (parallel) or intersect on the left of zero.
    while (!lines.empty() 
        && lines[0].first.m >= new_line.m) {
        lines.pop_front();
    }
    // remove all the lines that intersect after the second starting point, so that
    // they intersect with the second line or later and render the first line useless. 
    while (lines.size() >= 2 
        && find_intersection(new_line, lines[0].first) > lines[1].second) {
        lines.pop_front();
    }
    // shift the starting point of the first line further right, so that it matches with the
    // intersection with new_line.
    if (!lines.empty()) {
        line intersected = lines[0].first; lines.pop_front();
        lines.push_front({intersected, find_intersection(new_line, intersected)});
    }
    lines.push_front({new_line, 0});
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, Q; cin >> N >> M >> Q;
    vector<ll> S(N), T(N - 1);
    for (int i = 0; i < N; i ++) cin >> S[i];
    for (int i = 0; i < N - 1; i ++) cin >> T[i];

    segment seg(S, N);
    vector<ll> ps(N);
    for (int i = 0; i < N - 1; i ++) ps[i + 1] = ps[i] + T[i];

    // lines for convex_hull trick
    vector<line> top_lines(N), bot_lines(N);
    for (int i = 0; i < N; i ++) {
        top_lines[i] = {S[i], 2 * ps[i]};
        bot_lines[i] = {S[i], -2 * ps[i]};
    }

    vector<ll> w(Q);
    vector<ll> vertical(Q);
    vector<ll> around(Q);
    vector<array<ll, 4>> queries(Q);
    for (int i = 0; i < Q; i ++) {
        int A, B, C, D; cin >> A >> B >> C >> D;
        // A is lower than C
        if (A >= C) {
            swap(A, C);
            swap(B, D);
        }
        queries[i] = {A, B, C, D};

        // necessary vertical distance
        vertical[i] = ps[C] - ps[A];
        // nodes to circumnavigate 
        w[i] = min(D - B >= 0 ? D - B : D - B + M, B - D >= 0 ? B - D : B - D + M);
        // the optimal path to circumnavigate between A and C
        ll s = seg.query(A, C);
        around[i] = s * w[i];
    }

    deque<pair<line, ll>> lines;
    // calculate going_over
    vector<ll> going_over(Q);
    vector<pair<int, int>> sorted_c(Q);
    for (int i = 0; i < Q; i ++) {
        int C = queries[i][2];
        sorted_c[i] = {C, i};
    }
    sort(sorted_c.rbegin(), sorted_c.rend());
    
    int pt = N - 1;
    for (auto [c, i] : sorted_c) {
        while (pt >= c) {
            line new_line = top_lines[pt];
            pt --;
            add_line_at_beginning(lines, new_line);
        }
        going_over[i] = get_value(lines, w[i]) - 2 * ps[c];
    }

    lines.clear();
    // calculate going_under 
    // https://open.spotify.com/intl-it/track/3UygY7qW2cvG9Llkay6i1i?si=034d8740c0474193
    vector<ll> going_under(Q);
    vector<pair<int, int>> sorted_a(Q);
    for (int i = 0; i < Q; i ++) {
        int A = queries[i][0];
        sorted_a[i] = {A, i};
    }
    sort(sorted_a.begin(), sorted_a.end());

    pt = 0;
    for (auto [a, i] : sorted_a) {
        while (pt <= a) {
            line new_line = bot_lines[pt];
            pt ++;
            add_line_at_beginning(lines, new_line);
        }
        going_under[i] = get_value(lines, w[i]) + 2 * ps[a];
    }

    for (int i = 0; i < Q; i ++) {
        around[i] = min(around[i], going_over[i]);
        around[i] = min(around[i], going_under[i]);
    }

    for (int i = 0; i < Q; i ++) {
        cout << vertical[i] + around[i] << '\n';
    }
}
