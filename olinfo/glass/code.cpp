#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 5e5 + 5;
vector<int> adj[MAXN];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;       
    vector<int> C(N);
    for (int i = 0; i < N; i ++) cin >> C[i];

    for (int i = 0; i < M; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> v(N, -1);

    queue<int> q;
    vector<int> d(N, 1e7);
    for (int i = 0; i < N; i ++) {
        for (auto x : adj[i]) {
            if (C[i] != C[x]) {
                // se due vicini hanno un colore diverso me li salvo per far partire da lì la bfs multisource
                if (v[i] != -1 && v[i] != C[x]) {
                    // se ho già registrato un altro colore ancora allora ci sono tre nodi adiacenti di colori diversi
                    cout << 2 << '\n';
                    return 0;
                }
                if (v[x] != -1 && v[x] != C[i]) {
                    cout << 2 << '\n';
                    return 0;
                }
                if (v[i] == -1) q.push(i);
                if (v[x] == -1) q.push(x);
                v[i] = C[x];
                v[x] = C[i];
                d[i] = 1;
                d[x] = 1;
            }
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        
        for (auto x : adj[u]) {
            if (C[x] != C[u]) continue;
            // la bfs la faccio solo internamente ad ogni CC dello stesso colore
            if (v[x] == v[u]) continue;
            // se è già passato uno dello stesso colore allora non ci interessa
            if (v[x] != -1) {
                // è già passato qua uno di un colore diverso
                cout << d[x] + d[u] + 1 << '\n';
                return 0;
            }
            v[x] = v[u];
            d[x] = d[u] + 1;
            q.push(x);
        }
    }

    cout << -1 << '\n';
}
