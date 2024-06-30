#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];
int P[MAXN], S[MAXN];
ll C[MAXN];
vector<int> tree_array;
int subtree[MAXN], h[MAXN], pos_in_array[MAXN];
ll block[MAXN], block_children[MAXN], unlock[MAXN];
ll ps_block[MAXN + 1], ps_block_children[MAXN + 1], ps_unlock[MAXN + 1];
// per ogni HLD dice il nodo (pos in tree_array) più alto non visitato (tutti sopra sono visitati)
// modo figo per togliere il logn da un possibile segment lazy muraglia :O
int visited[MAXN]; 
bool is_already_to_fix[MAXN]; 

void dfs(int u) {
    subtree[u] = 1;
    
    block[u] = S[u] ? C[u] : 0;
    block_children[u] = 0;
    unlock[u] = S[u] ? 0 : C[u];

    int children = 0;
    for (auto x : adj[u]) {
        if (x == P[u]) continue;

        dfs(x);
        block_children[u] += block[x];
        subtree[u] += subtree[x];
        children ++;
    }

    if (children > 0) block[u] = min(block[u], block_children[u]);
    
    sort(adj[u].begin(), adj[u].end(), [&](int i, int j){ return (subtree[i] > subtree[j]); });
}

void dfs_hld(int u) {
    tree_array.push_back(u);
    pos_in_array[u] = tree_array.size() - 1;

    bool first = true;
    for (auto x : adj[u]) {
        if (x == P[u]) continue;

        if (first) {
            // setto stesso hld
            h[x] = h[u];
            first = false;
        }
        else {
            // starto nuovo hld
            h[x] = x;
        }

        dfs_hld(x);
    }
}

void build(int N) {
    for (int i = 0; i < N; i ++) ps_block[i + 1] = ps_block[i] + block[tree_array[i]];
    for (int i = 0; i < N; i ++) ps_block_children[i + 1] = ps_block_children[i] + block_children[tree_array[i]];
    for (int i = 0; i < N; i ++) ps_unlock[i + 1] = ps_unlock[i] + unlock[tree_array[i]];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    for (int i = 0; i < N; i ++) cin >> P[i];
    for (int i = 0; i < N; i ++) cin >> C[i];
    for (int i = 0; i < N; i ++) cin >> S[i];

    int root = 0;
    for (int i = 0; i < N; i ++) if (P[i] == -1) root = i;
    
    for (int i = 0; i < N; i ++) {
        if (P[i] != -1) {
            adj[i].push_back(P[i]);
            adj[P[i]].push_back(i);
        }
    }

    dfs(root);
    h[root] = root;

    dfs_hld(root);

    build(N);

    for (int i = 0; i < N; i ++) visited[i] = pos_in_array[i];

    while (Q --) {
        int M; cin >> M;
        vector<int> A(M);
        for (int i = 0; i < M; i ++) cin >> A[i];

        // il ziopera
        if (M == 0) {
            cout << block[root] << '\n';
            continue;
        }

        vector<int> to_fix;
        ll res = 0;

        for (auto u : A) {
            int prev = -1;
            int x = u;

            while (x != -1 && visited[h[x]] <= pos_in_array[x]) {
                // limit the top of the hld to the highest not visited node in the hld
                int top = tree_array[visited[h[x]]];
                // cout << "x, top -> " << x << " " << top << '\n';
                
                // unlock
                res += ps_unlock[pos_in_array[x] + 1] - ps_unlock[pos_in_array[top]];

                // block children
                res += ps_block_children[pos_in_array[x] + 1] - ps_block_children[pos_in_array[top]];

                // unblock those who didn't need to be blocked
                res -= ps_block[pos_in_array[x] + 1] - ps_block[pos_in_array[top] + 1];

                if (prev != -1) res -= block[prev];

                // set visited
                visited[h[x]] = pos_in_array[x] + 1;
                if (!is_already_to_fix[h[x]]) {
                    to_fix.push_back(h[x]);
                    is_already_to_fix[h[x]] = 1;
                }

                // next iteration
                prev = top;
                x = P[top];
            }

            if (prev != root) res -= block[prev];
        }

        for (auto x : to_fix) {
            is_already_to_fix[x] = 0;
            visited[x] = pos_in_array[x];
        }

        cout << res << '\n';
    }
}
