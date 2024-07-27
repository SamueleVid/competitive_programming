#include <bits/stdc++.h>
using namespace std;

typedef enum {
    OK,
    RISOLTO,
    IMPOSSIBILE
} stato_t;

typedef struct {
    int domino1;
    int domino2;
} coppia_t;

const int PW = 8388608; 

int seg[2 * PW];
int lazy[2 * PW];

void build(vector<int> &v, int N) {
    for (int i = 0; i < N; i ++) seg[i + PW] = v[i];
    for (int i = N; i < PW; i ++) seg[i + PW] = 1e9;
    for (int i = PW - 1; i > 0; i --) seg[i] = min(seg[2 * i], seg[2 * i + 1]);
    for (int i = 0; i < 2 * PW; i ++) lazy[i] = 0;
}

void update(int idx, int l, int r, int ql, int qr, int d) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        seg[idx] += d;
        lazy[idx] += d;
        return;
    }
    seg[2 * idx    ] += lazy[idx];
    seg[2 * idx + 1] += lazy[idx];
    lazy[2 * idx    ] += lazy[idx];
    lazy[2 * idx + 1] += lazy[idx];
    lazy[idx] = 0;
    update(2 * idx,     l, (l + r) / 2, ql, qr, d);
    update(2 * idx + 1, (l + r) / 2, r, ql, qr, d);
    seg[idx] = min(seg[2 * idx], seg[2 * idx + 1]);
}

stato_t correggi(int N, int h[], coppia_t* scambio) {
    vector<int> dipende(N);
    int primo = N;
    int ultimo = -1;
    priority_queue<pair<int, int>> pq;
    vector<vector<int>> raggruppa_per_h(1001);
    pq.push({0, -1});
    for (int i = 0; i < N; i ++) {
        while (!pq.empty() && -pq.top().first < i) {
            pq.pop();
        }
        if (pq.size() == 0) {
            primo = min(primo, i);
            ultimo = max(ultimo, i);
        }
        dipende[i] = pq.size();
        raggruppa_per_h[h[i]].push_back(i);
        pq.push({-(i + h[i] - 1), i});
    }

    if (primo == N) return OK;

    build(dipende, N);
    
    for (int i = max(0, ultimo - 1000); i < primo; i ++) {
        for (int alt = ultimo - i; alt <= 1000; alt ++) {
            for (auto j : raggruppa_per_h[alt]) {
                update(1, 0, PW, min(N, i + h[i]), min(N, i + h[j]), 1);
                update(1, 0, PW, min(N, j + h[i]), min(N, j + h[j]), -1);

                if (seg[1] > 0) {
                    scambio->domino1 = i;
                    scambio->domino2 = j;
                    return RISOLTO;
                }

                update(1, 0, PW, min(N, i + h[i]), min(N, i + h[j]), -1);
                update(1, 0, PW, min(N, j + h[i]), min(N, j + h[j]), 1);
            }
        }
    }

    return IMPOSSIBILE;
}
