#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 3e5 + 5;
constexpr int PW = 524288;
vector<pair<int, ll>> adj[MAXN];
vector<int> adj2[MAXN];
int h[MAXN];
ll d[MAXN];
bool v[MAXN];
pair<int, ll> tree[MAXN];
vector<int> treearray;
int inv_treearray[MAXN];
int subtree[MAXN];
int depth[MAXN];

struct segment {
    vector<int> seg;

    segment() {
        seg.assign(2 * PW, 0);
    }

    void update(int x, int d) {
        x ++; // 1 based per seg
        x += PW;
        while (x >= 1) {
            seg[x] += d;
            x /= 2;
        }
    }

    int query(int l, int r) {
        l ++; r ++; // 1 based per seg
        l += PW; r += PW;
        int res = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                res += seg[l];
                l ++;
            }
            if (r % 2 == 0) {
                res += seg[r];
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }

    int query2(int idx, int l, int r, int ql, int qr) {
        if (l >= qr) return 1e9;
        if (r <= qr && seg[idx] == r - l) return 1e9;
        if (r - l == 1) return l;
        
        int dx = query2(2 * idx + 1, (l + r) / 2, r, ql, qr);
        if (dx != 1e9) return dx;
        int sx = query2(2 * idx    , l, (l + r) / 2, ql, qr);
        return sx;
    }

    int muraglia(int l, int r) {
        l ++; r ++; // 1 based per seg
        return treearray[query2(1, 0, PW, l, r + 1) - 1]; // -1 ritorno 0 based
    }
};

segment seg;

void dijkstra(int N, int s) {
    fill(d, d + MAXN, 1e18);
    fill(v, v + MAXN, 0);
    d[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({-d[s], s});

    while (!pq.empty()) {
        auto [_, u] = pq.top(); pq.pop();
        if (v[u]) continue;
        v[u] = 1;
        for (auto [x, w] : adj[u]) {
            if (d[x] > d[u] + w) {
                d[x] = d[u] + w;
                pq.push({-d[x], x});
                tree[x] = {u, w};
            }
        }
    }
} 

void dfs_subtree(int u) {
    subtree[u] = 1;
    for (auto x : adj2[u]) {
        depth[x] = depth[u] + 1;
        dfs_subtree(x);
        subtree[u] += subtree[x];
    }
}

void dfs_hld(int u) {
    if (!adj[u].size()) return;
    
    // i guess i didn't want to sort the whole adj list
    int best_subtree = 0;
    for (int i = 0; i < adj2[u].size(); i ++) {
        if (subtree[adj2[u][i]] > subtree[adj2[u][best_subtree]]) best_subtree = i;
    }
    swap(adj[u][0], adj[u][best_subtree]);

    bool primo = 1;
    for (auto x : adj2[u]) {
        if (primo) {
            primo = 0;
            h[x] = h[u];
            dfs_hld(x);
            continue;
        }
        h[x] = x;
        dfs_hld(x);
    }
}

void dfs_treearray(int u) {
    treearray.push_back(u);
    inv_treearray[u] = treearray.size() - 1;

    for (auto x : adj2[u]) dfs_treearray(x);
}

void build_tree(int N) {
    for (int i = 0; i < N - 1; i ++) {
        adj2[tree[i].first].push_back(i);
    }

    fill(subtree, subtree + MAXN, 0);
    fill(depth, depth + MAXN, 0);
    fill(inv_treearray, inv_treearray + MAXN, 0);
    h[N - 1] = N - 1;
    
    dfs_subtree(N - 1);
    dfs_hld(N - 1);
    dfs_treearray(N - 1);
}

ll viaggia(int N, int M, vector<int> A, vector<int> B, vector<int> T, vector<int> V, vector<int> W) {

    fill(adj, adj + MAXN, vector<pair<int, ll>>());
    fill(adj2, adj2 + MAXN, vector<int>());
    fill(tree, tree + MAXN, pair<int, ll>());
    tree[N - 1] = {N - 1, 0};

    for (int i = 0; i < M; i ++) {
        adj[B[i]].push_back({A[i], T[i]});
    }

    dijkstra(N, N - 1);

    build_tree(N);

    ll res = 0;
    int curr = 0;
    vector<bool> used(N);
    while (used[N - 1] == 0) {
        if (used[curr]) {
            // sali a quello più alto non visitato con tutto il path tra curr e quello visitati
            int boss = h[curr];

            int nodi_in_mezzo = depth[curr] - depth[boss] + 1;
            int visitati_in_mezzo = seg.query(inv_treearray[boss], inv_treearray[curr]);

            if (visitati_in_mezzo == nodi_in_mezzo) {
                res += d[curr] - d[tree[boss].first];
                curr = tree[boss].first;
                continue;
            }
            else {
                int nuovo = seg.muraglia(inv_treearray[boss], inv_treearray[curr]);
                res += d[curr] - d[nuovo];
                curr = nuovo;
                continue;
            }
        }

        used[curr] = 1;
        if (curr == N - 1) break;
        seg.update(inv_treearray[curr], 1);
        if (V[curr] != -1) {
            res += W[curr];
            curr = V[curr];
            continue;
        }
        res += tree[curr].second;
        curr = tree[curr].first;
    }

    return res;
}
