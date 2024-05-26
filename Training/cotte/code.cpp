#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;

const int MAXM = 1e6+10;
vector<int>adj[MAXM];

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int M, F, C; cin >> M >> F >> C;

    for (int i = 0; i < C; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }
    for (int i = 1; i <= M; i ++) sort(adj[i].begin(), adj[i].end());

    vector<int> q;
    q.push_back(0);
    q.push_back(INF);
    for (int i = 1; i <= M; i ++) {
        
        int f = adj[i].size() - 1;
        int m = q.size() - 1;
        while (m >= 0 && f >= 0) {
            if (q[m - 1] < adj[i][f]) {
                q[m] = min(adj[i][f], q[m]);
                f --;
            }
            else {
                m --;
            }
        }

        if (q.back() != INF) q.push_back(INF);
    }

    cout << 2 * (q.size() - 2) << '\n';
}
