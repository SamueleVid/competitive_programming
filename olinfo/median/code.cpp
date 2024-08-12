#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 5e4 + 5;
constexpr int PW = 65536;

vector<pair<int, int>> adj[MAXN];
int subtree[MAXN];
bool removed[MAXN];

map<int, int> weights, idx_comp;
int inv_idx_comp[MAXN];

struct segment {
    vector<int> seg;
    int size;
    
    segment(int size_) {
        size = size_;
        seg.assign(2 * size, 0);
    }

    void update(int x, int d) {
        x += size;
        while (x >= 1) {
            seg[x] += d;
            x /= 2;
        }
    }

    int query(int r) {
        int l = size;
        r += size;
        int res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res += seg[l];
                l ++;
            }
            if (r % 2 == 0){
                res += seg[r];
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }

    void dfs_empty(int idx, int l, int r) {
        if (seg[idx] == 0) return;
        seg[idx] = 0;
        if (r - l == 1) return;
        dfs_empty(2 * idx,     l, (l + r) / 2);
        dfs_empty(2 * idx + 1, (l + r) / 2, r);
    }
    
    void empty() {
        dfs_empty(1, 0, size);
    }
};

void get_subtrees(int u, int p) {
    subtree[u] = 1;
    for (auto [v, w] : adj[u]) {
        if (v == p || removed[v]) continue;
        get_subtrees(v, u);
        subtree[u] += subtree[v];
    }
}

int get_centroid(int u, int p, int trg) {
    for (auto [v, w] : adj[u]) {
        if (v == p || removed[v]) continue;
        if (subtree[v] >= trg) {
            return get_centroid(v, u, trg);
        }
    }
    return u;
}

ll dfs(int u, int p, int prev_w, int flag, array<int, 2> &curr_values, segment &seg, int k) {
    prev_w = (prev_w <= k) ? 0 : 1;
    curr_values[prev_w] ++;

    ll res = 0;
    if (flag == 0) {
        int spare_zeros = curr_values[0] - curr_values[1];
        // zeri avanzati che possono aiutare altri path ad arrivare ad avere 0 di median
        res = seg.query(spare_zeros + PW);    
        for (auto [v, w] : adj[u]) {
            if (v == p || removed[v]) continue;
            res += dfs(v, u, w, flag, curr_values, seg, k);
        }
    }
    if (flag == 1) {
        // zero necessari perché il median sia zero
        int necessary_zeros = curr_values[1] - curr_values[0];
        seg.update(necessary_zeros + PW, 1);    

        for (auto [v, w] : adj[u]) {
            if (v == p || removed[v]) continue;
            dfs(v, u, w, flag, curr_values, seg, k);
        }
    }

    curr_values[prev_w] --;
    return res;
}

ll centroid_decomp(int root, int k, segment &seg) {
    get_subtrees(root, -1);
    int c = get_centroid(root, -1, subtree[root] / 2);

    seg.empty();
    seg.update(0 + PW, 1); // path vuoto
    array<int, 2> curr_values; // nel path c->u 0 : edges <= k, 1 : edges > k 
    curr_values[0] = 0; curr_values[1] = 0;
    ll res = 0;
    for (auto [v, w] : adj[c]) {
        /* flags:
        0: conta i median <= k nei paths c->u e nei path dai figli precedenti a u
        1: aggiungi i path c->u ai path dei figli precedenti
        */
        if (removed[v]) continue;
        res += dfs(v, c, w, 0, curr_values, seg, k);
        dfs(v, c, w, 1, curr_values, seg, k);
    } 

    removed[c] = 1;
    for (auto [v, w] : adj[c]) {
        if (removed[v]) continue;
        res += centroid_decomp(v, k, seg);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, K; cin >> N >> K;
    for (int i = 0; i < N - 1; i ++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        weights[w] ++;
    }

    int size_comp = 0;
    for (auto [w, _] : weights) {
        idx_comp[w] = size_comp;
        inv_idx_comp[size_comp] = w;
        size_comp ++;
    }

    /*
    La sol è k + 1 con k il massimo numero tale che
    i medians con valore <= k sono meno di K
    */

    segment seg(2 * PW); // faccio + PW per evitare numeri negativi

    int k = -1;
    for (int pw = PW; pw >= 1; pw /= 2) {
        if (pw + k >= size_comp) continue;
        fill(removed, removed + MAXN, 0);

        int medians = centroid_decomp(1, inv_idx_comp[pw + k], seg);
        if (medians < K) k += pw;
    }
    cout << inv_idx_comp[k + 1] << '\n';
}
