#include <bits/stdc++.h>
using namespace std;

struct dinic {
    vector<vector<int>> aug;
    vector<int> ptr;
    vector<int> lvl;
    int sz, s, t;
    
    dinic(vector<vector<int>> &adj, int s_, int t_, int sz_) {
        sz = sz_, s = s_, t = t_;
        aug.assign(sz, vector<int>(sz));
        ptr.resize(sz);
        lvl.resize(sz);
        
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
            for (int v = 0; v < sz; v ++) {
                if (lvl[v] != -1 || aug[u][v] == 0) continue;
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
        
        return (lvl[t] != -1);
    }
    
    int dfs_flow(int u, int curr_flow) {
        if (u == t) return curr_flow;

        for (int &v = ptr[u]; v < sz; v ++) {
            if (aug[u][v] == 0 || lvl[v] <= lvl[u]) continue;

            int flow = dfs_flow(v, min(curr_flow, aug[u][v]));
            if (flow == 0) continue;

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
            while (int curr_flow = dfs_flow(s, 1e9)) {
                flow += curr_flow;
            }
        }
        return flow;
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; i ++) {
        cin >> x[i] >> y[i];
    }
    
    map<int,int> rows, cols;
    for (int i = 0; i < N; i ++) {
        rows[x[i]] ++;
        cols[y[i]] ++;
    }
    
    vector<int> v_rows, v_cols;
    map<int,int> pos_row, pos_col;
    for (auto [x, r] : rows) {
        if (r % 3 != 0) {
            cout << "No" << '\n';
            return 0;
        }
    
        v_rows.push_back(r);
        pos_row[x] = v_rows.size() - 1;
    }
    for (auto [y, c] : cols) {
        if (c % 3 != 0) {
            cout << "No" << '\n';
            return 0;
        }
    
        v_cols.push_back(c);
        pos_col[y] = v_cols.size() - 1;
    }
    
    int sz = v_rows.size() + v_cols.size() + 2;
    vector<vector<int>> adj(sz, vector<int>(sz));
    int s = sz - 2;
    int t = sz - 1;
    for (int i = 0; i < v_rows.size(); i ++) {
        adj[s][i] = 2 * v_rows[i] / 3;
    }
    for (int i = 0; i < v_cols.size(); i ++) {
        adj[i + v_rows.size()][t] = 2 * v_cols[i] / 3;
    }
    for (int i = 0; i < N; i ++) {
        adj[pos_row[x[i]]][v_rows.size() + pos_col[y[i]]] = 1;
    }
    
    dinic max_matching(adj, s, t, sz);
    int flow = max_matching.get_flow();
    if (flow != 2 * N / 3) {
        cout << "No" << '\n';
        return 0;
    }

    cout << "Yes" << '\n';
    cout << N / 3 << '\n';
    for (int i = 0; i < N; i ++) {
        // se ha arco flow 0 è rosso. controllo flow guardando arco inverso
        if (max_matching.aug[v_rows.size() + pos_col[y[i]]][pos_row[x[i]]] == 0) {
            cout << x[i] << " " << y[i] << '\n';
        }
    }
}
