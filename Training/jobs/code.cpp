// credit a andrea coato (acoatoitgs) e alla sua soluzione
#include <bits/stdc++.h>
using namespace std;
#define ll long long

// letteralmente numero a caso, funziona fare greedy fino a M - K e poi DP NK per gli ultimi K
constexpr int K = 3600;

vector<ll> get_knapsack(int N, int M, vector<int> &T, vector<int> &P) {

    vector<ll> dp(K);
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < M; j ++) {
            if (j + T[i] >= K) break;
            dp[j + T[i]] = max(dp[j + T[i]], dp[j] + P[i]);
        }
    }

    return dp;
}

bool comp(pair<ll, ll> &a, pair<ll, ll> &b) {
    // P_i / T_i < P_j / T_j 
    return a.first * b.second < b.first * a.second;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    vector<int> T(N), P(N);
    for (auto &x : T) cin >> x;
    for (auto &x : P) cin >> x;

    vector<pair<ll, ll>> values(N);
    for (int i = 0; i < N; i ++) values[i] = {P[i], T[i]};
    sort(values.rbegin(), values.rend(), comp);

    vector<ll> dp = get_knapsack(N, M, T, P);

    if (M < K) {
        cout << dp[M] << '\n';
        return 0;
    }

    ll tot = 0;
    auto [p, t] = values[0];
    ll quante_volte = (M - K + t) / t;
    ll spostamento = quante_volte * t;
    tot += quante_volte * p;

    if (M - spostamento >= K) exit(-1);
    cout << tot + dp[M - spostamento] << '\n';
    
}
