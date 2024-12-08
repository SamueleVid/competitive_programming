#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct node {
    ll sum = 0;
    node* sx;
    node* dx;

    void copy_into(node* nodo) {
        nodo->sum = sum;
        nodo->sx = sx;
        nodo->dx = dx;
    }
};
constexpr int MAX_NODES = 1e7;
node arr[MAX_NODES];
int it = 0;

node* new_node() {
    return arr + it ++;
}

node* build(int l, int r) {
    if (r - l == 1) return new_node();
    node* nodo = new_node();
    nodo->sx = build(l, (r + l) / 2);
    nodo->dx = build((r + l) / 2, r);
    return nodo;
}

node* update(node* nodo, int l, int r, int x, ll d) {
    if (x < l || x >= r) return nodo;
    if (r - l == 1) {
        node* new_nodo = new_node();
        nodo->copy_into(new_nodo);
        new_nodo->sum += d;
        return new_nodo;
    }
    node* sx = update(nodo->sx, l, (l + r) / 2, x, d);
    node* dx = update(nodo->dx, (l + r) / 2, r, x, d);
    node* new_nodo = new_node();
    new_nodo->sx = sx;    
    new_nodo->dx = dx;
    new_nodo->sum = sx->sum + dx->sum;
    return new_nodo;
}

ll get_sol(node* prev_node, node* curr_node, int l, int r, ll d) {
    if (r - l == 1) return l - 1;
    int m = (l + r) / 2;
    ll first_half = (curr_node->sx->sum - prev_node->sx->sum);
    ll x = first_half + d - (m - 1);
    if (x == 0) return m - 1;
    if (x > 0) return get_sol(prev_node->dx, curr_node->dx, m, r, d + first_half);
    return get_sol(prev_node->sx, curr_node->sx, l, m, d);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<ll> P(N);
    for (int i = 0; i < N; i ++) cin >> P[i];
    for (int i = 0; i < N; i ++) P[i] = min(P[i], (ll)N);
    int SIZE = N + 5;

    vector<node*> segs(SIZE);
    segs[0] = build(0, SIZE);
    for (int i = 0; i < N; i ++) {
        node* curr = segs[i];
        node* curr_1 = update(curr, 0, SIZE, 0, 1);
        node* curr_2 = update(curr_1, 0, SIZE, P[i] + 1, -1);
        segs[i + 1] = curr_2;
    }

    while (Q --) {
        int l, r; cin >> l >> r;
        l --; r --;
        ll sol = get_sol(segs[l], segs[r + 1], 0, SIZE, 0);
        cout << sol << '\n';
    }
}   
