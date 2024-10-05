#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 1048576;

ll alleggerisci(int N, int M, vector<int> V, vector<int> L, vector<int> R, vector<ll> K) {
    // se due intervalli distinti necessitano rispettiamente di X e Y palloncini aggiunti, 
    // allora X + Y è un lowerbound della soluzione.
    // trovo il sottoinsieme di intervalli distinti che richiede più pallincini, ovvero il
    // lowerbound più alto trovabile con questo metodo, che per culo coincide con la soluzione lol

    vector<ll> ps(N + 1);
    for (int i = 0; i < N; i ++) {
        ps[i + 1] = ps[i] + V[i];
    }
    
    vector<ll> value(M);
    for (int i = 0; i < M; i ++) {
        value[i] = (ps[R[i] + 1] - ps[L[i]]) - K[i];
    }

    vector<pair<int, int>> sorted(M);
    for (int i = 0; i < M; i ++) {
        sorted[i] = {L[i], i};
    }
    sort(sorted.begin(), sorted.end());

    vector<ll> prefix_max(M + 1);
    vector<ll> dp(M);
    for (int i = M - 1; i >= 0; i --) {
        int idx = sorted[i].second;

        int k = -1;
        for (int p = PW; p >= 1; p /= 2) {
            if (p + k < M && L[sorted[p + k].second] <= R[idx]) k += p;
        }
        k ++;
        
        ll best_dp = prefix_max[k];
        dp[i] = value[idx] + best_dp;
        prefix_max[i] = max(prefix_max[i + 1], dp[i]);
    }

    ll res = 0;
    for (int i = 0; i < M; i ++) res = max(res, dp[i]);
    return res;
}
