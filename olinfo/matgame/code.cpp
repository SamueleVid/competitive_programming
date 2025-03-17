// more material on Dinic's algorithm can be found at https://cp-algorithms.com/graph/dinic.html
#include <bits/stdc++.h>
using namespace std;

constexpr int PW = 1048576;
constexpr int MAXN = 1e3 + 5;
int arr[MAXN][MAXN];

struct dinic {
    vector<int> ptr;
    vector<vector<int>> aug;
    vector<int> lvl;
    int N;
    int sz;
    int s, t;

    dinic(int N_) {
        N = N_, s = 2 * N, t = 2 * N + 1;
        sz = 2 * N + 2;
        ptr.resize(sz); lvl.resize(sz);
        aug.assign(sz, vector<int>(sz));
    }

    void set_graph(int trg) {
        // I transform the 0/1 rook problem to a max matching of a bipartite graph.
        // (the bipartition is rows / columns)

        // I can easilly solve the max matching problem using dinic max flow algorithm,
        // which runs in O(E*sqrtV) on unit networks (the maximum flow passing through each node is 1)

        for (int i = 0; i < sz; i ++) {
            for (int j = 0; j < sz; j ++) {
                aug[i][j] = 0;
            }
        }

        for (int i = 0; i < N; i ++) {
            aug[s][i] = 1;
            aug[i + N][t] = 1;
        }

        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                aug[i][j + N] = 0;
                if (arr[i][j] >= trg) aug[i][j + N] = 1;
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
            for (int v = 0; v < 2 * N + 2; v ++) {
                if (aug[u][v] == 0 || lvl[v] != -1) continue;
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
        return (lvl[t] != -1);
    }

    int dfs_flow(int u, int curr_flow) {
        if (u == t) return curr_flow;

        for (int& v = ptr[u]; v < sz; v ++) {
            if (aug[u][v] == 0 || lvl[v] <= lvl[u]) continue;
            int flow = dfs_flow(v, min(curr_flow, aug[u][v]));
            if (flow == 0) {
                continue;
            }
            aug[u][v] -= flow;
            aug[v][u] += flow;
            return flow;
        }
        return 0;
    }

    int get_flow() {
        int flow = 0;
        while (bfs_set_lvl()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int new_flow = dfs_flow(s, 1e9)) {
                flow += new_flow;
            }
        }
        return flow;
    }
};

bool check_zeros_ones(int N, int trg, dinic &flow) {
    // I reduce the problem to the 0/1 case, changing 
    // to 0 the elements < trg and to 1 the elements >= trg.

    flow.set_graph(trg);   

    return flow.get_flow() == N;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            cin >> arr[i][j];
        }
    }

    vector<int> values;
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            values.push_back(arr[i][j]);
        }
    }
    sort(values.begin(), values.end());

    dinic flow(N);

    // Binaryseach the smallest move made
    int k = 0;
    for (int p = PW; p >= 1; p /= 2) {
        if (p + k < values.size() && check_zeros_ones(N, values[p + k], flow)) k += p;
    }

    cout << values[k] << '\n';
}
