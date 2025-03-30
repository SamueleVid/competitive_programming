#include <bits/stdc++.h>
using namespace std;

bool possible = true;

// la dfs serve per rilevare possibili cicli
void dfs(bool sx, int nodo, vector<bool> &v_sx, vector<bool> &v_dx, vector<vector<int>> &adj_sx, vector<vector<int>> &adj_dx, int p) {
    if (sx) {
        if (v_sx[nodo]) {
            possible = false;
            return;
        }
        v_sx[nodo] = 1;

        for (auto x : adj_sx[nodo]) {
            if (x == p) continue;
            dfs(0, x, v_sx, v_dx, adj_sx, adj_dx, nodo);
        }
    }
    else {
        if (v_dx[nodo]) {
            possible = false;
            return;
        }
        v_dx[nodo] = 1;

        for (auto x : adj_dx[nodo]) {
            if (x == p) continue;
            dfs(1, x, v_sx, v_dx, adj_sx, adj_dx, nodo);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, E;
    cin >> N >> M >> E;

    vector<vector<int>> adj_sx(N), adj_dx(M);

    for (int i = 0; i < E; ++i) {
        int a, b; cin >> a >> b;
        adj_sx[a].push_back(b);
        adj_dx[b].push_back(a);
    }

    vector<int> d_sx(N, 1), d_dx(M, 0);
    for (int i = 0; i < N; i ++) d_sx[i] = adj_sx[i].size();
    for (int i = 0; i < M; i ++) d_dx[i] = adj_dx[i].size();

    vector<int> counter_sx(N, 0), counter_dx(M, 0);

    // non è possibile se un nodo è vicino di più di due nodi con grado >= 2
    for (int i = 0; i < N; i ++) {
        int quanti_deg_two = 0;
        for (auto x : adj_sx[i]) {
            if (d_dx[x] >= 2) quanti_deg_two ++;
        }
        counter_sx[i] = quanti_deg_two;
       
        if (quanti_deg_two > 2) possible = false;
    }
    for (int i = 0; i < M; i ++) {
        int quanti_deg_two = 0;
        for (auto x : adj_dx[i]) {
            if (d_sx[x] >= 2) quanti_deg_two ++;
        }
        counter_dx[i] = quanti_deg_two;

        if (quanti_deg_two > 2) possible = false;
    }

    // non è possibile se sono presenti dei cicli
    vector<bool> v_sx(N, 0), v_dx(M, 0);
    for (int i = 0; i < N; i ++) {
        if (!v_sx[i]) dfs(1, i, v_sx, v_dx, adj_sx, adj_dx, -1);
    }
    for (int i = 0; i < M; i ++) {
        if (!v_dx[i]) dfs(0, i, v_sx, v_dx, adj_sx, adj_dx, -1);
    }

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    // piazzo le vari componenti piano piano
    vector<int> SX, DX;
    vector<bool> piazzato_sx(N), piazzato_dx(M);
    while (true) {
        int start = -1;
        bool sx = 1;
        for (int i = 0; i < N; i ++) {
            if (d_sx[i] >= 2 && counter_sx[i] == 1 && !piazzato_sx[i]) {
                start = i;
                break;
            }
        }
        if (start == -1) {
            sx = 0;
            for (int i = 0; i < M; i ++) {
                if (d_dx[i] >= 2 && counter_dx[i] == 1 && !piazzato_dx[i]) {
                    start = i;
                    break;
                }
            }
        }
        if (start == -1) break;

        while (start != -1) {
            int curr = start;
            start = -1;
            if (sx) {
                SX.push_back(curr);
                piazzato_sx[curr] = 1;
                for (auto i : adj_sx[curr]) {
                    if (piazzato_dx[i]) continue;
                    if (d_dx[i] == 1) {
                        DX.push_back(i);
                        piazzato_dx[i] = 1;
                    }
                    else start = i;
                }
            }
            else {
                DX.push_back(curr);
                piazzato_dx[curr] = 1;
                for (auto i : adj_dx[curr]) {
                    if (piazzato_sx[i]) continue;
                    if (d_sx[i] == 1) {
                        SX.push_back(i);
                        piazzato_sx[i] = 1;
                    }
                    else start = i;
                }
            }
            sx = !sx;
        }
    }
    for (int i = 0; i < N; i ++) {
        if (piazzato_sx[i]) continue;
        SX.push_back(i);
        piazzato_sx[i] = 1;
        for (auto x : adj_sx[i]) {
            DX.push_back(x);
            piazzato_dx[x] = 1;
        }
    }
    for (int i = 0; i < M; i ++) {
        if (piazzato_dx[i]) continue;
        DX.push_back(i);
        piazzato_dx[i] = 1;
        for (auto x : adj_dx[i]) {
            SX.push_back(x);
            piazzato_sx[x] = 1;
        }
    }

    for (auto x : SX) cout << x << " ";
    cout << '\n';
    for (auto x : DX) cout << x << " ";
    cout << '\n';
}
