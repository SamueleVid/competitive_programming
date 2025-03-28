#include <bits/stdc++.h>
using namespace std;

struct dinic {
    vector<vector<int>> aug;
    vector<int> ptr;
    vector<int> lvl;
    int sz, s, t;

    dinic(vector<vector<int>> &adj, int sz_, int s_, int t_) {
        sz = sz_, s = s_, t = t_;
        aug.assign(sz, vector<int>(sz));
        ptr.assign(sz, 0);
        lvl.resize(sz, 0);

        for (int i = 0; i < sz; i ++) {
            for (int j = 0; j < sz; j ++) {
                aug[i][j] = adj[i][j];
            }
        }
    }

    bool bfs_set_lvl() {
        fill(lvl.begin(), lvl.end(), -1);
        lvl[s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            
            for (int x = 0; x < sz; x ++) {
                if (lvl[x] != -1 || aug[u][x] == 0) continue;
                lvl[x] = lvl[u] + 1;
                q.push(x);
            }
        }

        return lvl[t] != -1;
    }

    int dfs_flow(int u, int curr_flow) {
        if (u == t) return curr_flow;

        for (int &x = ptr[u]; x < sz; x ++) {
            if (lvl[x] != lvl[u] + 1 || aug[u][x] == 0) continue;
            
            int flow = dfs_flow(x, min(curr_flow, aug[u][x]));
            if (flow == 0) continue;

            aug[u][x] -= flow;
            aug[x][u] += flow;

            return flow;
        }
        return 0;
    }

    int get_flow() {
        int flow = 0;
        while (bfs_set_lvl()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int curr_flow = dfs_flow(s, 1e9)) {
                flow += curr_flow;
            }
        }
        return flow;
    }

    vector<vector<int>> get_flow_adj(int N, vector<vector<int>> &adj) {
        get_flow();

        // Keep only the edges chosen by the max matching
        vector<vector<int>> new_adj(N, vector<int>(N));
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                if (aug[N + j][i] && adj[i][j]) new_adj[i][j] = 1;
            }
        }

        return new_adj;
    }
    
};

void dfs(int u, int N, vector<vector<int>> &adj, vector<bool> &v) {
    if (v[u]) return;
    v[u] = 1;
    for (int i = 0; i < N; i ++) {
        if (adj[u][i]) dfs(i, N, adj, v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<int> D(N);
    for (int i = 0; i < N; i ++) cin >> D[i];

    vector<vector<int>> C(N, vector<int>(N));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            cin >> C[i][j];
        }
    }

    vector<vector<int>> can_reach(N, vector<int>(N));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            if (D[i] > D[j]) continue;
            if (C[i][j] <= D[j] - D[i]) can_reach[i][j] = 1;
        }
    }

    // I'm interested in counting the minimum number of chains I need to cover the graph. (<=> max antichain)
    // I try to cut the least amount of edges so that only chains remain (each node has max outdegree and indegree of one),
    // the claim is that by cutting the least amount of edges (and obtaining a set of chains) I also obtain the minimum 
    // number of chains that cover the graph.
    // To do so I construct a maxflow/mincut problem that limit the flow of each indegree and outdegree to one.

    int sz = 2 * N + 2;
    int s = 2 * N, t = 2 * N + 1;
    vector<vector<int>> adj_flow(sz, vector<int>(sz));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            if (can_reach[i][j]) {
                adj_flow[i][N + j] = 1;
            }
        }
    }
    for (int i = 0; i < N; i ++) {
        adj_flow[s][i] = 1;
        adj_flow[N + i][t] = 1;
        // I don't count edges from a node to itself.
        adj_flow[i][N + i] = 0;
    }

    dinic form_chains(adj_flow, sz, s, t);
    vector<vector<int>> chains = form_chains.get_flow_adj(N, can_reach);

    // Make it undirected for easier CC counting.
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            if (chains[i][j] == 1) chains[j][i] = 1; 
        }
    }

    // Now that I have all distinct chains, I just need to count them. 
    int comps = 0;
    vector<bool> v(N);
    for (int i = 0; i < N; i ++) {
        if (!v[i]) {
            comps ++;
            dfs(i, N, chains, v);
        }
    }

    cout << comps << '\n';
}
