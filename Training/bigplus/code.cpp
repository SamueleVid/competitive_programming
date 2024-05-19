#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int LOG = 30;

struct node {
    int m = 0;
    int lazy = 0;
    node* sx = nullptr;
    node* dx = nullptr;
};

node arr[10000000];
int it = 0;

node* new_nodo() {
    node* nodo = arr + it;
    nodo->m = 0;
    nodo->lazy = 0;
    nodo->sx = nullptr;
    nodo->dx = nullptr;
    it ++;
    return nodo;
}

void push_lazy(node* nodo, ll l, ll r) {
    if (!nodo->lazy) return;
    if (r-l == 1) {
        nodo->lazy = 0;
        return;
    }

    if (!nodo->sx) nodo->sx = new_nodo();
    if (!nodo->dx) nodo->dx = new_nodo();
    nodo->sx->m += nodo->lazy;
    nodo->dx->m += nodo->lazy;
    nodo->sx->lazy += nodo->lazy;
    nodo->dx->lazy += nodo->lazy;

    nodo->lazy = 0;
}

void update(ll nl, ll nr, ll ql, ll qr, node* nodo, int x) {
    push_lazy(nodo, nl, nr);
    if (qr <= nl || nr <= ql) {
        return;
    }
    
    if (ql <= nl && nr <= qr) {
        nodo->m += x;
        nodo->lazy += x;
        push_lazy(nodo, nl, nr);
        return;
    }
    
    if (!nodo->sx) nodo->sx = new_nodo();
    if (!nodo->dx) nodo->dx = new_nodo();
    update(nl, (nl+nr)/2, ql, qr, nodo->sx, x);
    update((nl+nr)/2, nr, ql, qr, nodo->dx, x);
    nodo->m = max(nodo->sx->m, nodo->dx->m);
}

int query(ll nl, ll nr, node* nodo, int x) {
    push_lazy(nodo, nl, nr);
    if (nr - nl == 1) return nl;
    if (!nodo->sx) nodo->sx = new_nodo();
    if (!nodo->dx) nodo->dx = new_nodo();
    if (nodo->sx->m >= x) return query(nl, (nl+nr)/2, nodo->sx, x);
    return query((nl+nr)/2, nr, nodo->dx, x);
}

pair<int,int> possible(ll s, ll f, int n, vector<pair<ll,ll>> &pts, ll r) {

    it = 0;
    node* seg = new_nodo();
    vector<int>ys_dupe, ys;
    // tutte le y dove potrebbe trovarsi il centro della croce
    for (auto [y, x] : pts) {
        if (0 <= y-r && y-r < s) ys_dupe.push_back(y-r);
        if (0 <= y && y < s) ys_dupe.push_back(y);
        if (0 <= y+r && y+r < s) ys_dupe.push_back(y+r);
    }
    ys_dupe.push_back(0); // considera sempre la possibilità di non usare gli N e metterlo sulla prima riga
    sort(ys_dupe.begin(), ys_dupe.end());
    for (int i = 0; i < ys_dupe.size(); i++) {
        if (i == 0 || ys_dupe[i] != ys_dupe[i-1]) ys.push_back(ys_dupe[i]);
    }

    int horiz_enter = 0, horiz_exit = 0, vertic_enter = 0, vertic_exit = 0;     
    int cy = -1, cx = -1;
    for (auto y : ys) {

        // aggiungi i segmenti orizzontali sulla stessa y
        while (horiz_enter < n && pts[horiz_enter].first <= y) {
            auto [curr_y, curr_x] = pts[horiz_enter];
            horiz_enter ++;
            update(0, s, max(0ll,curr_x-r), min(curr_x,s), seg, +1);
            update(0, s, max(0ll,curr_x+1), min(curr_x+r+1,s), seg, +1);
        }
        
        // rimuovi i segmenti orizzontali che si trovano sopra
        while (horiz_exit < n && pts[horiz_exit].first < y) {
            auto [curr_y, curr_x] = pts[horiz_exit];
            horiz_exit ++;
            update(0, s, max(0ll,curr_x-r), min(curr_x,s), seg, -1);
            update(0, s, max(0ll,curr_x+1), min(curr_x+r+1,s), seg, -1);
        }
        
        // aggiungi i segmenti verticali che si originano da sotto
        while (vertic_enter < n && pts[vertic_enter].first <= y+r) {
            auto [curr_y, curr_x] = pts[vertic_enter];
            vertic_enter ++;
            update(0, s, max(0ll,curr_x), min(curr_x+1,s), seg, +1);
        }

        // rimuovi i segmenti verticali che si originano da troppo sopra
        while (vertic_exit < n && pts[vertic_exit].first < y-r) {
            auto [curr_y, curr_x] = pts[vertic_exit];
            vertic_exit ++;
            update(0, s, max(0ll,curr_x), min(curr_x+1,s), seg, -1);
        }

        if (seg->m + f >= 4*r + 1) {
            cy = y;
            cx = query(0, s, seg, 4*r + 1 - f);
            break;            
        }
    }
    return {cy, cx};
}

array<int, 3> find_plus(int n, int s, int f, vector<int> y, vector<int> x) {

    vector<pair<ll,ll>>pts(n); // y, x per il sort
    for (int i = 0; i < n; i++) pts[i] = {y[i], x[i]};
    sort(pts.begin(), pts.end());
    int r = 0, cy = 0, cx = 0;
    for (ll pw = 1ll << LOG; pw > 0; pw /= 2) {

        auto [curr_cy, curr_cx] = possible(s, f, n, pts, r+pw);
        if (curr_cy != -1) {
            r += pw;
            cy = curr_cy;
            cx = curr_cx;
        }
    }    
    return {r, cy, cx};
}
