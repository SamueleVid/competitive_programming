#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250000 + 5;
const int LOG = 20;
const int MAXV = 250000 + 5;
int N;

vector<int> adj[MAXN];
int v[MAXN];
int p[MAXN], depth[MAXN];
int binlift[LOG][MAXN];

struct node {
    int v;
    node* sx;
    node* dx;

    node() {
        v = 0;
        sx = nullptr;
        dx = nullptr;
    }

    node* copia() {
        node* new_nodo = new node;
        new_nodo->v = v;
        new_nodo->sx = sx;
        new_nodo->dx = dx;
        return new_nodo;
    }
};

struct persistent_segtree {
    vector<node*> versions;
    int size;

    persistent_segtree(int size_) {
        size = size_;
        versions.resize(MAXN);
        versions[0] = build(0, size);
    }

    node* build(int l, int r) {
        node* nodo = new node;
        if (r - l == 1) return nodo;
        nodo->sx = build(l, (l + r) / 2);
        nodo->dx = build((l + r) / 2, r);
        return nodo;
    }

    node* update(node* nodo, int l, int r, int x) {
        if (r <= x || l > x) return nodo;
        node* new_nodo = nodo->copia();
        if (r - l == 1) {
            new_nodo->v ++;
            return new_nodo;
        }
        node* sx = update(new_nodo->sx, l, (l + r) / 2, x);
        node* dx = update(new_nodo->dx, (l + r) / 2, r, x);
        new_nodo->sx = sx;
        new_nodo->dx = dx;
        new_nodo->v = new_nodo->sx->v + new_nodo->dx->v;
        return new_nodo;
    }

    void add(int prev_version, int new_version, int x) {
        node* new_nodo = update(versions[prev_version], 0, size, x);
        versions[new_version] = new_nodo;
    }

    int query(node* p_lca, node* lca, node* a, node* b, int l, int r, int k) {
        if (r - l == 1) return l;

        int a_dx = a->dx->v + b->dx->v - p_lca->dx->v - lca->dx->v;

        if (a_dx >= k) {
            return query(p_lca->dx, lca->dx, a->dx, b->dx, (l + r) / 2, r, k);
        }
        return query(p_lca->sx, lca->sx, a->sx, b->sx, l, (l + r) / 2, k - a_dx);
    }

    int find_kth_biggest(int p_lca, int lca, int a, int b, int k) {
        return query(versions[p_lca], versions[lca], versions[a], versions[b], 0, size, k);
    }
};

void dfs(int u) {
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        depth[x] = depth[u] + 1;
        p[x] = u;
        dfs(x);
    }
}

void build_tree() {
    p[1] = 0; depth[1] = 0; depth[0] = -1; // for lca

    dfs(1);

    for (int i = 1; i <= N; i ++) binlift[0][i] = p[i];
    for (int pw = 1; pw < LOG; pw ++) {
        for (int i = 1; i <= N; i ++) {
            binlift[pw][i] = binlift[pw - 1][binlift[pw - 1][i]];
        }
    }
}

void dfs_seg(int u, persistent_segtree &seg) {
    seg.add(p[u], u, v[u]);

    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        dfs_seg(x, seg);
    }
}

int lca(int a, int b) {
    // a deve essere più in basso
    if (depth[a] < depth[b]) swap(a, b);
    // salgo a fino a b
    for (int pw = LOG - 1; pw >= 0; pw --) {
        if (depth[binlift[pw][a]] >= depth[b]) a = binlift[pw][a];
    }
    // uno dei due è l'lca
    if (a == b) return a;
    // salgo finché sono diversi
    for (int pw = LOG - 1; pw >= 0; pw --) {
        if (binlift[pw][a] != binlift[pw][b]) {
            a = binlift[pw][a];
            b = binlift[pw][b];
        }
    }
    // quello subito sopra (così sono uguali) è l'lca
    return p[a];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i ++) cin >> v[i];
    for (int i = 1; i <= N - 1; i ++) {
        int p; cin >> p;
        adj[i + 1].push_back(p);
        adj[p].push_back(i + 1);
    }

    build_tree();
    persistent_segtree seg(MAXV);
    dfs_seg(1, seg);

    int Q; cin >> Q;
    while (Q --) {
        int a, b, k; cin >> a >> b >> k;

        int l = lca(a, b);

        int sol = seg.find_kth_biggest(p[l], l, a, b, k);
        cout << sol << '\n';
    }
}
