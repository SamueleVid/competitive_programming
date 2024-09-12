#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2e5 + 5;
constexpr int MAXNODE = 2e6 + 5;
constexpr int PW = 262144;
pair<int, int> match[MAXN];
int nodes = 0;
vector<int> adj[MAXNODE];
int info_medaglia[MAXNODE]; // -1 = no medaglia, altrimenti la query
int res[MAXN];
int curr[MAXN];

struct segment {
    vector<int> seg;

    segment() {
        seg.assign(2 * PW, 0);
    }

    void update(int x, int d) {
        x += PW;
        seg[x] = d;
        x /= 2;
        while (x >= 1) {
            seg[x] = max(seg[2 * x], seg[2 * x + 1]);
            x /= 2;
        }
    }

    int query() {
        int l = 0, r = PW, idx = 1;
        while (r - l > 1) {
            if (seg[2 * idx] == seg[1]) {
                r = (l + r) / 2;
                idx = 2 * idx;
                continue;
            }
            else {
                l = (l + r) / 2;
                idx = 2 * idx + 1;
                continue;
            }
        }
        return l;
    }
};

segment seg;

void dfs(int u, int last) {
    if (info_medaglia[u] == -1) return;
    int query = info_medaglia[u];
    
    int dist = last - query;

    curr[match[query].first] += dist; 

    seg.update(match[query].first, curr[match[query].first]);
    int holder = seg.query();
    res[holder] ++;

    for (auto x : adj[u]) {
        dfs(x, query);
    }

    curr[match[query].first] -= dist; 
    seg.update(match[query].first, curr[match[query].first]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < M; i ++) cin >> match[i].first >> match[i].second;

    fill(info_medaglia, info_medaglia + MAXNODE, -1);
    vector<int> last_node(N);
    for (int i = 0; i < N; i ++) {
        last_node[i] = nodes ++;
    }

    for (int i = 0; i < M; i ++) {
        auto [x, y] = match[i];
        int new_nodo_x = nodes ++;
        int new_nodo_y = nodes ++;
        int old_nodo_x = last_node[x];
        int old_nodo_y = last_node[y];

        adj[new_nodo_x].push_back(old_nodo_x);
        adj[new_nodo_x].push_back(old_nodo_y);
        info_medaglia[new_nodo_x] = i;
        
        last_node[x] = new_nodo_x;
        last_node[y] = new_nodo_y;
    }

    fill(res, res + MAXN, 0);
    fill(curr, curr + MAXN, 0);

    for (int i = 0; i < N; i ++) {
        dfs(last_node[i], M);
    }

    for (int i = 0; i < N; i ++) {
        cout << res[i] << " ";
    }
    cout << '\n';

}
