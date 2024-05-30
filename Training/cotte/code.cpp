#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1e6+10;
const int LOG = 20;
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
    q.push_back(MAXM);
    for (int i = 1; i <= M; i ++) {
        
        for (int f = adj[i].size() - 1; f >= 0; f --) {
            int k = q.size() - 1;
            for (int pw = 1 << LOG; pw >= 1; pw /= 2) {
                if (k - pw >= 0 && q[k - pw] >= adj[i][f]) k -= pw;
            }
            q[k] = adj[i][f];
        }

        if (q.back() != MAXM) {
            q.push_back(MAXM);
        }
    }

    cout << 2 * (q.size() - 1) << '\n';
}
