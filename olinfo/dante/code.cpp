#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int PW = 524288;

bool bsa(int k, int N, int K, vector<int> &ps) {
    for (int i = 0; i <= N - k; i ++) {
        if (ps[i + k] - ps[i] + K >= k) {
            return true;
        }
    }
    return false;
}

int rimembra(int N, int K, vector<int> V) {

    vector<int> ps(N + 1);
    for (int i = 0; i < N; i ++) ps[i + 1] = ps[i] + V[i];

    int k = 0;
    for (int p = PW; p >= 1; p /= 2) {
        if (k + p <= N && bsa(k + p, N, K, ps)) k += p;
    }

    return k;
}
