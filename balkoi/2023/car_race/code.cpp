#include <bits/stdc++.h>
using namespace std;
#define ll long long
#pragma GCC optimize("Os")

constexpr ll MAXN = 1e6 + 6;
constexpr ll PW = 1 << 21; // smallest 2^k >= 2 * MAXN
vector<int> adj[MAXN];

int depth[MAXN];
vector<int> euler_tour; // size 2 * N - 1
int leftmost_pos_in_et[MAXN];
int rightmost_pos_in_et[MAXN];

vector<int> depth_to_cars[MAXN];

void info_tree_dfs(int u) {
    euler_tour.push_back(u);
    leftmost_pos_in_et[u] = euler_tour.size() - 1;
    for (auto x : adj[u]) {
        depth[x] = depth[u] + 1;
        info_tree_dfs(x);
        euler_tour.push_back(u);
    }
    rightmost_pos_in_et[u] = euler_tour.size() - 1;
}

struct segment {
    // for calculating LCA using Euler Tour
    vector<int> seg;

    segment() {
        seg.assign(2 * PW, -1);
    }

    void build(vector<int> &v) {
        for (int i = 0; i < v.size(); i ++) seg[PW + i] = v[i];
        for (int i = PW - 1; i > 0; i --) seg[i] = merge(seg[2 * i], seg[2 * i + 1]);
    }

    int query(int l, int r) {
        l += PW;
        r += PW;

        ll res = -1;
        while (l <= r) {
            if (l % 2 == 1) {
                res = merge(res, seg[l]);
                l ++;
            }
            if (r % 2 == 0) {
                res = merge(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }

        return res;
    }

    int merge(int a, int b) {
        if (a == -1) return b;
        if (b == -1) return a;

        if (depth[a] < depth[b]) return a;
        else return b;
    }
};

segment seg_for_lca;

// I tried using Binary Lifting for LCA in O(NlogN), but it resulted in TLE.
// I tried using RMQ for LCA in O(1), but it resulted in MLE.
int lca(int a, int b) {
    return seg_for_lca.query(rightmost_pos_in_et[a], leftmost_pos_in_et[b]);
}

struct dsu {
    // to get the uppermost lca calculated for a specific node
    vector<int> p, sz;
    dsu(int N) {
        p.resize(N);
        iota(p.begin(), p.end(), 0);
        sz.assign(N, 1);
    }

    int boss(int u) {
        if (p[u] != u) return p[u] = boss(p[u]);
        return u;
    }

    void merge(int a, int b) {
        a = boss(a);
        b = boss(b);
        if (a == b) return;

        if (sz[a] < sz[b]) swap(a, b);

        p[b] = a;
        sz[a] += sz[b];
    }
};

void dfs_check_crash(int u, vector<vector<int>> &adj, vector<int> &is_there_car) {
    int how_many_cars = 0;
    for (auto x : adj[u]) {
        dfs_check_crash(x, adj, is_there_car);
        how_many_cars += is_there_car[x];
    }
    if (how_many_cars >= 2) is_there_car[u] = 0; // they crashed
    if (how_many_cars == 1) is_there_car[u] = 1; // signal that there is a car
    // if (how_many_cars == 0) stay the same
    return;
}

void dfs_find_winner_cars(int u, vector<vector<int>> &adj, vector<int> &is_there_car, vector<int> &win) {
    if (is_there_car[u] == 0) return; // here no cars have passed so this leads to nowhere

    if (adj[u].size() == 0) win.push_back(u); // if u this is a leaf then decompress[u] is the starting pos of a car
    for (auto x : adj[u]) {
        dfs_find_winner_cars(x, adj, is_there_car, win);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N; cin >> N;
    for (int i = 1; i < N; i ++) {
        int p; cin >> p;
        adj[p].push_back(i);
    }
    vector<int> car(N);
    for (int i = 0; i < N; i ++) cin >> car[i];

    depth[0] = 0;
    info_tree_dfs(0);

    seg_for_lca.build(euler_tour);
    
    for (int i = 0; i < N; i ++) {
        if (car[i]) depth_to_cars[depth[i]].push_back(i);
    }

    vector<int> res(N);    

    for (int d = 0; d < N; d ++) {
        // if two cars have different depth than they are indipendent
        if (!depth_to_cars[d].size()) continue;

        // sort the cars by euler tour position so that you only need to check O(N) LCAs
        // imagine drawing the tree as a planar graph: you only need to check the LCAS between two "consecutive" nodes.
        vector<pair<int, int>> car_sorted;
        for (auto x : depth_to_cars[d]) car_sorted.push_back({leftmost_pos_in_et[x], x});
        sort(car_sorted.begin(), car_sorted.end());

        int k = car_sorted.size();

        // compress the nodes so that I can use the DSU and it's easier to build a second tree for later use
        map<int, int> compress;
        vector<int> decompress(2 * k + 5);
        for (int i = 0; i < k; i ++) {
            decompress[i] = car_sorted[i].second;
            compress[decompress[i]] = i;
        }
        int next_k = k;

        dsu groups(k);
        vector<int> lca_of_group(k);
        for (int i = 0; i < k; i ++) lca_of_group[i] = i;
        
        // we calculate all the lcas between each consecutive nodes
        vector<pair<int, int>> lcas;
        for (int i = 0; i < k - 1; i ++) {
            lcas.push_back({-depth[lca(decompress[i], decompress[i + 1])], i});
        }
        sort(lcas.begin(), lcas.end());
 
        // the parent values for the new tree
        vector<int> p(2 * k + 5, -1);

        for (auto [_, consec_nodes] : lcas) {
            int a = consec_nodes, b = consec_nodes + 1;

            int l = lca(decompress[a], decompress[b]);
            int l_id;

            if (!compress.count(l)) {
                l_id = next_k ++;
                compress[l] = l_id;
                decompress[l_id] = l;
            }
            else {
                l_id = compress[l];
            }

            // update the parents on the new tree
            p[lca_of_group[groups.boss(a)]] = l_id;
            p[lca_of_group[groups.boss(b)]] = l_id;

            // set the lca of the new group
            groups.merge(a, b);
            lca_of_group[groups.boss(a)] = l_id;
        }

        // add the node 0 so that I can always start the dfs on the new tree at the real root
        if (!compress.count(0)) {
            compress[0] = next_k;
            decompress[next_k] = 0;
            p[lca_of_group[groups.boss(0)]] = compress[0];
            next_k ++;
        }

        // build the new tree
        p[compress[0]] = -1;
        vector<vector<int>> small_adj(next_k);
        for (int i = 0; i < next_k; i ++) {
            if (p[i] != -1) small_adj[p[i]].push_back(i);
        }

        // find the nodes where a car has passed by        
        vector<int> is_there_car(next_k);
        for (int i = 0; i < k; i ++) is_there_car[i] = 1;

        dfs_check_crash(compress[0], small_adj, is_there_car);
        is_there_car[compress[0]] = 1;

        // go down these nodes to find the winner cars
        vector<int> win;
        dfs_find_winner_cars(compress[0], small_adj, is_there_car, win);

        for (auto x : win) res[decompress[x]] = 1;
    }

    for (int i = 0; i < N; i ++) {
        if (!res[i]) cout << -1 << " ";
        else cout << depth[i] << " ";
    }
    cout << '\n';
}
