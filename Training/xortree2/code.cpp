#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int PW = 65536;
const int LOG = 29;
vector<pair<int,int>> adj[MAXN];
int p[MAXN], prefix_xor[MAXN];
bool interesting[MAXN];
int start[MAXN];
int ans[PW];

void dfs(int u) {
    for (auto [v, w] : adj[u]) {
        if (v == p[u]) continue;
        p[v] = u;
        prefix_xor[v] = prefix_xor[u] ^ w;
        dfs(v);
    }
}

struct query {
    int x, start, end; // [start, end)
};

struct node {
    node* next[2] = {nullptr, nullptr};
    int quanti[2] = {0, 0};
};
int it = 0;
node arr[2000000];
node* new_node() {
    node* nodo = arr + it;
    nodo->next[0] = nullptr;
    nodo->next[1] = nullptr;
    nodo->quanti[0] = 0;
    nodo->quanti[1] = 0;
    it ++;
    return nodo;
}
stack<int> maxes;
stack<int> added;

void update_max(int x, node* trie) {
    node* curr = trie;
    int make_xor_bigger = 0;
    for (int pw = LOG; pw >= 0; pw --) {
        int bit = (x >> pw) & 1;
        int other_bit = bit ^ 1;
        if (curr->quanti[other_bit]) {
            make_xor_bigger += other_bit << pw;
            curr = curr->next[other_bit];
        }
        else {
            make_xor_bigger += bit << pw;
            curr = curr->next[bit];
        }
    }
    
    int prev_max = (maxes.empty()) ? 0 : maxes.top();
    maxes.push(max(prev_max, make_xor_bigger ^ x));
}

void add(int x, node* trie) {
    node* curr = trie;
    for (int pw = LOG; pw >= 0; pw --) {
        int bit = (x >> pw) & 1;
        if (!curr->next[bit]) curr->next[bit] = new_node();
        curr->quanti[bit] ++;
        curr = curr->next[bit];
    }

    added.push(x);
    update_max(x, trie);
}

void go_back(node* trie) {
    maxes.pop();
    int x = added.top(); added.pop();

    node* curr = trie;
    for (int pw = LOG; pw >= 0; pw --) {
        int bit = (x >> pw) & 1;
        if (!curr->next[bit]) curr->next[bit] = new_node();
        curr->quanti[bit] --;
        curr = curr->next[bit];
    }
}

vector<int> seg[2 * PW];

void update(int i, int lb, int rb, int qlb, int qrb, int x) {
    // salvo i range di azione delle query in un segment che simboleggia il tempo delle query.
    // in questo modo spezzo i range in modo da creare una gerarchia ad albero 
    // (che costruisco e decido che sia in logn) così da permettere gli add e go_back del trie.
    if (rb <= qlb || qrb <= lb) return;
    if (qlb <= lb && rb <= qrb) {
        seg[i].push_back(x);
        return;
    }
    update(2 * i,     lb, (lb + rb) / 2, qlb, qrb, x);
    update(2 * i + 1, (lb + rb) / 2, rb, qlb, qrb, x);
}

void dfs_seg(int i, int lb, int rb, node* trie) {
    // visita elementi nel range di tempo [lb, rb)
    for (auto x : seg[i]) add(x, trie);

    // se il tempo è lb stampa la soluzione per la query in quel tempo
    if (rb - lb == 1) {
        ans[lb] = maxes.empty() ? 0 : maxes.top();
    }
    else {
        // vedi figli
        dfs_seg(2 * i,     lb, (lb + rb) / 2, trie);
        dfs_seg(2 * i + 1, (lb + rb) / 2, rb, trie);
    }

    for (auto x : seg[i]) {
        go_back(trie);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;

    bool flag = true;

    for (int i = 0; i < N - 1; i ++) {
        int u, v, w; cin >> u >> v >> w;
        if (w != 0 && w != 1) flag = false;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    p[1] = -1, prefix_xor[1] = 0;
    dfs(1);

    fill(interesting, interesting + MAXN, 0);
    fill(start, start + MAXN, -1);
    vector<query> queries;

    for (int i = 0; i < Q; i ++) {
        int p; cin >> p;
        int x = prefix_xor[p];
        if (interesting[p]) {
            interesting[p] = 0;
            queries.push_back({x, start[p], i});
            start[p] = -1;
        }
        else {
            interesting[p] = 1;
            start[p] = i;
        }
    }
    for (int p = 1; p <= N; p ++) {
        int x = prefix_xor[p];
        if (start[p] != -1) {
            queries.push_back({x, start[p], Q});
        }
    }

    for (auto [x, start, end] : queries) update(1, 0, PW, start, end, x);
    
    node* trie = new_node();

    dfs_seg(1, 0, PW, trie);

    for (int i = 0; i < Q; i ++) {
        cout << ans[i] << '\n';
    }
}
