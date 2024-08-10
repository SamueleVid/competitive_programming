#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250010;
int n, k, m, l = 0;
int t[MAXN];
bool v[MAXN];
vector<int> adj[MAXN];
set<int> adj_check[MAXN];
vector<int> adj_reverse[MAXN];
vector<int> scc_adj[MAXN];

vector<int> post_ordering;
int inverse_post_ordering[MAXN]{-1};
int scc[MAXN];

void dfs(int u) {
    v[u] = 1;
    for (auto x : adj[u]) if (!v[x]) dfs(x);
    post_ordering.push_back(u);
}

void dfs_kosaraju(int u) {
    v[u] = 1;
    scc[u] = l;
    for (auto x : adj_reverse[u]) if (!v[x]) dfs_kosaraju(x);
}

void dfs_scc(int u) {
    v[u] = 1;
    for (auto x : scc_adj[u]) if (!v[x]) dfs_scc(x);
    post_ordering.push_back(u);
}

void dfs_dag(int u, int limit) {
    v[u] = 1;
    for (auto x : scc_adj[u]) if (inverse_post_ordering[x] <= limit && !v[x]) dfs_dag(x, limit);
}

void kosaraju() {
    // get post ordering.
    fill(v,v+k+1,0);
    for (int i=1;i<=k;i++) if (!v[i]) dfs(i);
    fill(v,v+k+1,0);

    // map every node to its scc. l is the number of sccs.
    reverse(post_ordering.begin(), post_ordering.end());
    for (auto u : post_ordering) {
        if (v[u]) continue;
        dfs_kosaraju(u);
        l ++;
    }

    // create the adj list of sccs without edge repetition.
    set<pair<int,int>>edges;
    for (int i=1;i<=k;i++) {
        for (auto x : adj[i]) {
            if (!edges.count({scc[i],scc[x]}) && scc[i] != scc[x]) {
                scc_adj[scc[i]].push_back(scc[x]);
                edges.insert({scc[i],scc[x]});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> k;
    for (int i=0;i<n;i++) cin >> t[i];
    cin >> m;
    for (int i=0;i<m;i++) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj_check[a].insert(b);
        adj_reverse[b].push_back(a);
    }

    kosaraju();

    // toposort
    post_ordering.clear();
    fill(v,v+l,0);
    dfs_scc(scc[t[0]]);
    fill(v,v+l,0);
    reverse(post_ordering.begin(), post_ordering.end());

    for (int i=0;i<post_ordering.size();i++) inverse_post_ordering[post_ordering[i]] = i;
    int score = 2;
    for (int i=1;i<n;i++) {
        if (adj_check[t[i-1]].count(t[i])) {
            score += 2;
            continue;
        }
        if (scc[t[i-1]] == scc[t[i]]) {
            score ++;
            continue;
        }
        // this node could have been visited in the last dfs.
        v[scc[t[i-1]]] = 0;
        // if scc[t[i]] comes before scc[t[i-1]] in the toposort then it's not reachable.
        if (inverse_post_ordering[scc[t[i]]] < inverse_post_ordering[scc[t[i-1]]]) break;
        // don't visit sccs after scc[t[i]] in the toposort as it is useless and would become O(n^2).
        dfs_dag(scc[t[i-1]], inverse_post_ordering[scc[t[i]]]);

        if (v[scc[t[i]]]) score ++;
        else break;
    }

    cout << score << '\n';
}
