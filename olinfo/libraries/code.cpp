#include <bits/stdc++.h>
using namespace std;
#define ll long long

void get_subtree(int u, vector<int> &p, vector<vector<int>> &adj, vector<ll> &A, vector<ll> &A_st) {
    if (A[u]) A_st[u] ++;

    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        p[x] = u;
        get_subtree(x, p, adj, A, A_st);
        A_st[u] += A_st[x];
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<vector<int>> adj(N);
    
    for (int i = 0; i < N - 1; i ++) {
        int U, V, W; cin >> U >> V >> W;
        adj[U].push_back(V);    
        adj[V].push_back(U);
    }

    vector<ll> A(N),B(N),C(N);
    int K; cin >> K;
    for (int i = 0; i < K; i ++) {
        int a; cin >> a;
        A[a] ++;
    }
    int L; cin >> L;
    for (int i = 0; i < L; i ++) {
        int b; cin >> b;
        B[b] ++;
    }
    int M; cin >> M;
    for (int i = 0; i < M; i ++) {
        int c; cin >> c;
        C[c] ++;
    }

    vector<int> p(N, -1);
    vector<ll> A_st(N), B_st(N), C_st(N);
    get_subtree(0, p, adj, A, A_st);
    get_subtree(0, p, adj, B, B_st);
    get_subtree(0, p, adj, C, C_st);
    
    vector<ll> res(N);

    for (int u = 0; u < N; u ++) {
        // --- triples where A != u, B != u, C != u

        // A coming from above
        for (auto x : adj[u]) {
            if (x == p[u]) continue;
            res[u] += (K - A_st[u]) * B_st[x] * (C_st[u] - C_st[x] - C[u]);
        }
        // B coming from above
        for (auto x : adj[u]) {
            if (x == p[u]) continue;
            res[u] += (L - B_st[u]) * A_st[x] * (C_st[u] - C_st[x] - C[u]);
        }
        // C coming from above
        for (auto x : adj[u]) {
            if (x == p[u]) continue;
            res[u] += (M - C_st[u]) * B_st[x] * (A_st[u] - A_st[x] - A[u]);
        }

        // A, B, C all coming from below
        ll BC = 0;
        for (auto x : adj[u]) {
            if (x == p[u]) continue;
            BC += B_st[x] * (C_st[u] - C_st[x] - C[u]);
        }
        for (auto x : adj[u]) {
            if (x == p[u]) continue;
            ll BC_no_x = BC;
            // remove all Bs counted in child x
            BC_no_x -= B_st[x] * (C_st[u] - C_st[x] - C[u]);
            // remove all Cs counted in child x
            BC_no_x -= C_st[x] * (B_st[u] - B_st[x] - B[u]);
            // fill the available space of child x with As
            res[u] += A_st[x] * BC_no_x;
        }

        // --- triples where A == u, B != u, C != u
        if (A[u]) {
            // B coming from above
            res[u] += (L - B_st[u]) * (C_st[u] - C[u]);
            // C coming from above
            res[u] += (M - C_st[u]) * (B_st[u] - B[u]);
            // B, C all coming from below
            for (auto x : adj[u]) {
                if (x == p[u]) continue;
                res[u] += B_st[x] * (C_st[u] - C_st[x] - C[u]);
            }
        }

        // --- triples where A != u, B == u, C != u
        if (B[u]) {
            // A coming from above
            res[u] += (K - A_st[u]) * (C_st[u] - C[u]);
            // C coming from above
            res[u] += (M - C_st[u]) * (A_st[u] - A[u]);
            // A, C all coming from below
            for (auto x : adj[u]) {
                if (x == p[u]) continue;
                res[u] += A_st[x] * (C_st[u] - C_st[x] - C[u]);
            }
        }

        // --- triples where A != u, B != u, C == u
        if (C[u]) {
            // B coming from above
            res[u] += (L - B_st[u]) * (A_st[u] - A[u]);
            // A coming from above
            res[u] += (K - A_st[u]) * (B_st[u] - B[u]);
            // B, A all coming from below
            for (auto x : adj[u]) {
                if (x == p[u]) continue;
                res[u] += B_st[x] * (A_st[u] - A_st[x] - A[u]);
            }            
        }

        // --- triples where A == u, B == u, C != u
        if (A[u] && B[u]) {
            res[u] += M - C[u];
        }

        // --- triples where A == u, B != u, C == u
        if (A[u] && C[u]) {
            res[u] += L - B[u];
        }

        // --- triples where A != u, B == u, C == u
        if (B[u] && C[u]) {
            res[u] += K - A[u];
        }

        // --- triples where A == u, B == u, C == u
        if (A[u] && B[u] && C[u]) {
            res[u] += 1;
        }
    }

    for (auto x : res) cout << x << " ";
    cout << '\n';
}
