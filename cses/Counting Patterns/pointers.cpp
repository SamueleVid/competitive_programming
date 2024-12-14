// taking inspiration from https://cp-algorithms.com/string/aho_corasick.html
#include <bits/stdc++.h>
using namespace std;

constexpr int ABC = 26;

struct node {
    node* next_trie[ABC];
    node* next_dfa[ABC];
    vector<int> words;
    int visited = 0;
    node* suffix;
    node* p;
    int pch = -1;

    node() {
        suffix = nullptr;
        p = nullptr;
        fill(next_trie, next_trie + ABC, nullptr);
        fill(next_dfa, next_dfa + ABC, nullptr);
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string S; cin >> S;
    int K; cin >> K;
    vector<string> dict(K);
    for (int i = 0; i < K; i ++) cin >> dict[i];

    node* root = new node;
    root->suffix = root;
    root->p = root;
    for (int i = 0; i < K; i ++) {
        node* curr = root;
        for (auto c : dict[i]) {
            if (!curr->next_trie[c - 'a']) {
                curr->next_trie[c - 'a'] = new node;
            }
            curr->next_trie[c - 'a']->pch = c - 'a';
            curr->next_trie[c - 'a']->p = curr;
            curr = curr->next_trie[c - 'a'];
        }
        curr->words.push_back(i);
    }

    // setting suffix edges and dfa edges
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* u = q.front(); q.pop();
        node* p_suff = u->p->suffix;

        // key feature of aho corasick, its dp recurrence for suffix edges
        if (u->p == root) u->suffix = root; // root e depth = 1
        else u->suffix = p_suff->next_dfa[u->pch]; 

        if (u == root) {
            for (int i = 0; i < ABC; i ++) {
                if (!u->next_trie[i]) {
                    u->next_dfa[i] = u;
                }
                else u->next_dfa[i] = u->next_trie[i];
            }
        }
        else {
            for (int i = 0; i < ABC; i ++) {
                if (!u->next_trie[i]) {
                    u->next_dfa[i] = u->suffix->next_dfa[i];;
                }
                else u->next_dfa[i] = u->next_trie[i];
            }
        }

        for (int i = 0; i < ABC; i ++) {
            if (u->next_trie[i]) { 
                q.push(u->next_trie[i]);
            }
        }
    }

    // visiting S
    node* curr = root;
    for (auto c : S) {
        curr = curr->next_dfa[c - 'a'];
        curr->visited ++;
    }

    // get nodes in bfs order
    vector<node*> sorted_nodes;
    q.push(root);
    while (!q.empty()) {
        node* u = q.front(); q.pop();
        sorted_nodes.push_back(u);

        for (int i = 0; i < ABC; i ++) {
            if (u->next_trie[i]) { 
                q.push(u->next_trie[i]);
            }
        }
    }

    vector<int> res(K);

    reverse(sorted_nodes.begin(), sorted_nodes.end());
    for (auto u : sorted_nodes) {
        for (auto i : u->words) {
            res[i] = u->visited;
        }
        // if AB is visited, also B is visited. As |B| < |AB|,  
        // it has not yet been seen in this loop
        u->suffix->visited += u->visited;
    }

    for (auto x : res) cout << x << '\n';
}
