#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 5;
vector<pair<int,int>> adj[MAXN];
// un arco indica che posso skippare un segmento in quanto già tolto
// adj[0] è prima di 0, quindi gli indici sono 1-based
// però gli archi sono 0 based lol
int dp[MAXN];

int conta(int N, vector<int> D) {  
    vector<int> prefix_xor(N + 1);
    for (int i = 0; i < N; i ++) prefix_xor[i + 1] = prefix_xor[i] ^ D[i];
    for (int i = 0; i < MAXN; i ++) adj[i].push_back({i, 0});
    
    for (int i = N - 1; i >= 0; i --) {
        for (auto [u1, w1] : adj[i + 1]) {
            for (auto [u2, w2] : adj[u1 + 1]) {
                if (u2 >= N) continue;
                if ((prefix_xor[u2 + 1] ^ prefix_xor[i]) == 0) {
                    // collego la fine di u2 a quello precedente di i
                    // magari ci sono due segmenti da tre consecutivi, allora li unisco in uno da sei
                    // altrimenti semplicemente lo collega all'elemento successivo di u2
                    for (auto [u3, w3] : adj[u2 + 1]) {
                        adj[i].push_back({u3, w1 + w2 + w3 + 3});
                    }
                }
            }
        }
    }

    // dag dp max dist
    fill(dp, dp + MAXN, 0);
    for (int i = 0; i <= N; i ++) {
        for (auto [v, w] : adj[i]) {
            dp[v + 1] = max(dp[v + 1], dp[i] + w);
        }
    }

    return dp[N + 1];
}
