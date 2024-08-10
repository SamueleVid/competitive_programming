#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr int MAXQ = 2e5 + 5;
constexpr int PW = 262144;

int sx[MAXN];
int dx[MAXN]; // se x viene tagliato allora dx[x] si salva
int start_queue[MAXN]; // start time for queue merge {i, dx[i]}
vector<array<int, 4>> queries; // {i, dx[i]}, [start, end);
int results[MAXQ];

struct union_find {
    // mi salvo quelli consecutivi crescenti in una DSU
    // si nota che quelli salvi sono la dimensione del segmento crescente fratto due
    int ans;

    vector<int> p, size;
    stack<array<int, 3>> last; // x, y, se erano stesso boss

    union_find(int N) {
        p.resize(N);
        for (int i = 0; i < N; i ++) p[i] = i;
        size.assign(N, 1);
        ans = 0;
    }

    int boss(int x) {
        while (p[x] != x) x = p[x];
        return x;
    }

    void merge(int x, int y) {
        x = boss(x);
        y = boss(y);

        // x è il più grosso
        if (size[x] < size[y]) swap(x, y);

        last.push({x, y, x == y});
        if (x == y) return;

        ans -= size[x] / 2;
        ans -= size[y] / 2;

        p[y] = x;
        size[x] += size[y]; 

        ans += size[x] / 2;
    }

    void rollback() {
        assert(last.size());
        auto [x, y, same_boss] = last.top(); last.pop();
        if (same_boss) return;

        ans -= size[x] / 2;

        size[x] -= size[y];
        p[y] = y;

        ans += size[x] / 2;
        ans += size[y] / 2;
    }
};

struct segment {
    // dynamic connectivity
    vector<vector<pair<int, int>>> seg;

    segment() {
        seg.resize(2 * PW);

        for (auto [x, y, start, end] : queries) {
            update(1, 0, PW, start, end, {x, y});
        }
    }

    void update(int idx, int l, int r, int lq, int rq, pair<int, int> q) {
        if (rq <= l || r <= lq) return;
        if (lq <= l && r <= rq) {
            seg[idx].push_back(q);
            return;
        }
        update(2 * idx,     l, (l + r) / 2, lq, rq, q);
        update(2 * idx + 1, (l + r) / 2, r, lq, rq, q);
    }

    void dfs(int idx, int l, int r, union_find &dsu) {
        for (auto [x, y] : seg[idx]) dsu.merge(x, y);

        if (r - l == 1) {
            results[l] = dsu.ans;
        }
        else {
            dfs(2 * idx,     l, (l + r) / 2, dsu);
            dfs(2 * idx + 1, (l + r) / 2, r, dsu);
        }

        for (auto [x, y] : seg[idx]) dsu.rollback();
    }

    void get_results(union_find &dsu) {
        dfs(1, 0, PW, dsu);
    }
};

void process_query(int i, int time) {
    if (start_queue[i] != -1) {
        queries.push_back({i, dx[i], start_queue[i], time});
        start_queue[i] = -1;
    }
    else {
        start_queue[i] = time;
    }
}

void init(int N, vector<int> &A) {
    for (int i = 0; i < N - 1; i ++) dx[i] = i + 1, sx[i + 1] = i;
    dx[N - 1] = 0, sx[0] = N - 1;

    fill(start_queue, start_queue + N, -1);
    for (int i = 0; i < N; i ++) {
        if (A[dx[i]] > A[i]) process_query(i, 0);
    }
}

void conclude(int N, int time) {
    for (int i = 0; i < N; i ++) {
        if (start_queue[i] != -1) process_query(i, time);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i ++) cin >> A[i];

    union_find dsu(N);
    init(N, A);

    for (int time = 1; time <= Q; time ++) {
        int X, C; cin >> X >> C;

        if ((A[X] > A[sx[X]]) != (C > A[sx[X]])) {
            process_query(sx[X], time);
        }
        if ((A[dx[X]] > A[X]) != (A[dx[X]] > C)) {
            process_query(X, time);
        }

        A[X] = C;
    }

    conclude(N, Q + 1);   

    segment seg;
    seg.get_results(dsu);

    for (int i = 0; i <= Q; i ++) cout << results[i] << " ";
    cout << '\n';
}
