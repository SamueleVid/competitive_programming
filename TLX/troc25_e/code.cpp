#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll M = 998244353;
const int MAXN = 100010;
int n, q;
ll a[MAXN];
vector<int> adj[MAXN];
int p[MAXN];

struct block {
    ll sum = 0;
    ll lazy = 0;
    int degree = 0;
};

block* block_children[MAXN];
block* block_siblings[MAXN];

void dfs(int u) {
    block* curr_block = new block;
    block_children[u] = curr_block;

    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        
        curr_block->sum = (curr_block->sum + a[x]) % M;
        block_siblings[x] = curr_block;
        curr_block->degree ++;
        p[x] = u;
        
        dfs(x);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i=1;i<=n;i++) cin >> a[i];
    for (int i=0;i<n-1;i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    block_siblings[1] = new block;
    block_siblings[1]->sum = a[1];
    p[1] = -1;
    dfs(1);

    cin >> q;
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            ll value = (a[x] + block_siblings[x]->lazy) % M;

            block_children[x]->lazy += value;
            block_children[x]->lazy %= M;
            block_children[x]->sum += (value * block_children[x]->degree) % M;
            block_children[x]->sum % M;

            if (p[x] != -1) {
                a[p[x]] += value;
                a[p[x]] %= M;
                block_siblings[p[x]]->sum += value;
                block_siblings[p[x]]->sum %= M;
            }

        } else {
            ll res = 0;

            res += block_children[x]->sum;
            res %= M;

            if (p[x] != -1) {
                ll value_parent = (a[p[x]] + block_siblings[p[x]]->lazy) % M;
                res += value_parent;
                res %= M;
            }
            
            cout << res << '\n';
        }
    }
}
