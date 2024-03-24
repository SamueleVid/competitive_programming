#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40010;
const int SQRT = 200;
const int LOG = 17;
int n, q, tot = 0;
int a[MAXN], p[MAXN], depth[MAXN];
int v[MAXN]{0}; // this tells me if the current node has already been visited and therefore should be removed from f or added.
int f[MAXN]{0}; // frequency of weights
pair<int,int> orig[MAXN];
pair<int,int> pos[MAXN]; // first and second position of node in treearray
int binlift[LOG][MAXN];
vector<int> adj[MAXN];
vector<int> treearray;

void dfs(int u) {
    pos[u].first = treearray.size();
    treearray.push_back(u);
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        p[x] = u;
        depth[x] = depth[u] + 1;
        dfs(x);
    }
    pos[u].second = treearray.size();
    treearray.push_back(u);
}

void build_binlift() {
    for (int i=1;i<=n;i++) binlift[0][i] = p[i];
    for (int pw=1;pw<LOG;pw++) {
        for (int i=1;i<=n;i++) {
            binlift[pw][i] = binlift[pw-1][binlift[pw-1][i]];
        }
    }
}

int get_lca(int u, int v) {
    // depth[u] >= depth[v]
    if (depth[u] < depth[v]) swap(u,v);
    // depth[u] = depth[v]
    for (int pw=LOG-1;pw>=0;pw--) {
        if (depth[binlift[pw][u]] >= depth[v]) u = binlift[pw][u];
    }
    // if u or v is lca
    if (u == v) return u;

    // find child of lca with bsa
    for (int pw=LOG-1;pw>=0;pw--) {
        if (binlift[pw][u] != binlift[pw][v]) u = binlift[pw][u], v = binlift[pw][v];
    }
    return p[u];
}

struct query {
    int u, v, id;
};

bool comp(query &a, query &b) {
    if ((a.u / SQRT) != (b.u / SQRT)) return a.u < b.u;
    if ((a.u / SQRT) % 2) return a.v < b.v;
    return a.v > b.v;
}

void update(int x) {
    if (v[treearray[x]] == 1) v[treearray[x]] = -1;
    else v[treearray[x]] = 1;
            
    if (!f[a[treearray[x]]]) tot ++;
    f[a[treearray[x]]] += v[treearray[x]];
    if (!f[a[treearray[x]]]) tot --;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    for (int i=1;i<=n;i++) {
        int a; cin >> a;
        orig[i] = {a,i};
    }

    // index compression for frequency update O(n)
    sort(orig+1, orig+n+1);
    a[0] = 0; orig[0].first = -1;
    for (int i=1;i<=n;i++) {
        if (orig[i-1].first == orig[i].first) a[orig[i].second] = a[orig[i-1].second];
        else a[orig[i].second] = a[orig[i-1].second] + 1;
    }

    for (int i=0;i<n-1;i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    p[1] = 1; depth[1] = 0;
    dfs(1);
    build_binlift();

    vector<int>results(q);
    vector<query>queries(q);
    for (int i=0;i<q;i++) {
        int u, v; cin >> u >> v;
        // u comes before v in treearray
        if (pos[u].second > pos[v].second) swap(u,v);
        queries[i] = {pos[u].second,pos[v].first,i};
    }

    // mo sort
    sort(queries.begin(), queries.end(), comp);
    int curr_l = 0, curr_r = -1;

    for (auto [l, r, id] : queries) {
        while (curr_l > l) {
            curr_l --;
            update(curr_l);
        }
        while (curr_r < r) {
            curr_r ++;
            update(curr_r);
        }
        while (curr_l < l) {
            update(curr_l);
            curr_l ++;
        }
        while (curr_r > r) {
            update(curr_r);
            curr_r --;
        }

        int lca = get_lca(treearray[l],treearray[r]);

        results[id] = tot;

        // consider lca separately as it's not in the range [l,r]
        if (!f[a[lca]]) results[id] ++;
    }

    for (int i=0;i<q;i++) cout << results[i] << '\n';
}
