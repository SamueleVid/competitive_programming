#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e5 + 10;
const int PW = 131072;
const ll MAXPS = 1e14 + 10;
const int LOG = 48;
ll ps[MAXN];
int dp[MAXN];
ll seg[2 * PW]; 

void update(int x, ll d) {
    x += PW;
    while (x >= 1) {
        seg[x] = min(seg[x], d);
        x /= 2;
    }
}

int query(ll d) {
    int lb = 0, rb = PW;
    int x = 1;
    while (rb - lb > 1) {
        if (seg[2 * x] <= d) {
            x = 2 * x;
            rb = (lb + rb) / 2;
        }
        else {
            x = 2 * x + 1;
            lb = (lb + rb) / 2;
        }
    }
    return lb;
}

bool bsa(int N, int K, ll max_sum) {
    fill(dp, dp + MAXN, MAXN);
    fill(seg, seg + 2 * PW, MAXPS);

    dp[0] = 0;
    update(0, 0);
    for (int i = 0; i < N; i ++) {
        int min_dp = query(max_sum - ps[i + 1]);
        // esiste un j : ps[i + 1] - ps[j] <= max_sum
        if (seg[min_dp + PW] != MAXPS) {
            dp[i + 1] = min_dp + 1;
            update(dp[i + 1], -ps[i + 1]);
        }
    }
    return (dp[N] <= K);
}

ll stalkera(int N, int K, vector<int> S) {
    for (int i = 0; i < N; i ++) ps[i + 1] = ps[i] + S[i];
    
    ll max_sum = -MAXPS;
    for (ll pw = 1ll << LOG; pw >= 1; pw /= 2) {
        if (!bsa(N, K, max_sum + pw)) max_sum += pw;
    }
    max_sum ++;

    return max_sum;
}
