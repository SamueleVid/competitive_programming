// taking inspiration from https://cp-algorithms.com/string/aho_corasick.html
#include <bits/stdc++.h>
using namespace std;

constexpr int ABC = 26;

struct node {
    int next_trie[ABC];
    int next_dfa[ABC];
    vector<int> words;
    int visited = 0;
    int suffix = -1;
    int p = -1;
    int pch = -1;

    node() {
        suffix = -1;
        p = -1;
        fill(next_trie, next_trie + ABC, -1);
        fill(next_dfa, next_dfa + ABC, -1);
    }
};

vector<node> trie;

int new_node() {
    trie.push_back(node());
    return trie.size() - 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string S; cin >> S;
    int K; cin >> K;
    vector<string> dict(K);
    for (int i = 0; i < K; i ++) cin >> dict[i];

    int root = new_node();
    trie[root].suffix = root;
    trie[root].p = root;
    for (int i = 0; i < K; i ++) {
        int curr = root;
        for (auto c : dict[i]) {
            if (trie[curr].next_trie[c - 'a'] == -1) {
                trie[curr].next_trie[c - 'a'] = new_node();
            }
            trie[trie[curr].next_trie[c - 'a']].pch = c - 'a';
            trie[trie[curr].next_trie[c - 'a']].p = curr;
            curr = trie[curr].next_trie[c - 'a'];
        }
        trie[curr].words.push_back(i);
    }

    // setting suffix edges and dfa edges
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int p_suff = trie[trie[u].p].suffix;

        // key feature of aho corasick, its dp recurrence for suffix edges
        if (trie[u].p == root) trie[u].suffix = root; // root e depth = 1
        else trie[u].suffix = trie[p_suff].next_dfa[trie[u].pch];

        if (u == root) {
            for (int i = 0; i < ABC; i ++) {
                if (trie[u].next_trie[i] != -1) {
                    trie[u].next_dfa[i] = trie[u].next_trie[i];
                }
                else trie[u].next_dfa[i] = u;
            }
        }
        else {
            for (int i = 0; i < ABC; i ++) {
                if (trie[u].next_trie[i] != -1) {
                    trie[u].next_dfa[i] = trie[u].next_trie[i];
                }
                else trie[u].next_dfa[i] = trie[trie[u].suffix].next_dfa[i];
            }
        }


        for (int i = 0; i < ABC; i ++) {
            if (trie[u].next_trie[i] != -1) { 
                q.push(trie[u].next_trie[i]);
            }
        }
    }

    // visiting S
    int curr = root;
    for (auto c : S) {
        curr = trie[curr].next_dfa[c - 'a'];
        trie[curr].visited ++;
    }

    // get nodes in bfs order
    vector<int> sorted_nodes;
    q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        sorted_nodes.push_back(u);

        for (int i = 0; i < ABC; i ++) {
            if (trie[u].next_trie[i] != -1) { 
                q.push(trie[u].next_trie[i]);
            }
        }
    }

    vector<int> res(K);

    reverse(sorted_nodes.begin(), sorted_nodes.end());
    for (auto u : sorted_nodes) {
        for (auto i : trie[u].words) {
            res[i] = trie[u].visited;
        }
        // if AB is visited, also B is visited. As |B| < |AB|,  
        // it has not yet been seen in this loop
        trie[trie[u].suffix].visited += trie[u].visited;
    }

    for (auto x : res) cout << (x ? "YES" : "NO") << '\n';
}
