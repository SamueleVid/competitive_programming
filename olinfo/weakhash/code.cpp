#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e7 + 19;
ll inv[MOD];

int main() {

    inv[1] = 1;
    for (int i = 2; i < MOD; i ++) inv[i] = MOD - ((MOD / i) * inv[MOD % i]) % MOD;

    int N; cin >> N;
    ll H; cin >> H;
    // claiming that there aren't lots of new elements added, K, the method belows works up to 91 points.
    map<ll, ll> dp;
    map<ll, ll> new_dp;
    dp[1] = 1;
    for (int i = 0; i <= N / 2; i ++) {

        new_dp.clear();
        for (auto [a, b] : dp) {
            for (ll d = 1; d < 10; d ++) {
                new_dp[(a * d) % MOD] += b;
                new_dp[(a * d) % MOD] %= MOD;
            } 
        }
        swap(new_dp, dp);
    } 

    // for the full I decide to calculate until N / 2 (ceil and floor if odd) and merge the solutions.
    // I first have to put all the elements in these vectors as MOD log MOD is too big and K log MOD + MOD is way smaller.
    vector<ll> dp_1(MOD), dp_2(MOD);
    for (auto [a, b] : dp) dp_1[a] = b;
    for (auto [a, b] : new_dp) dp_2[a] = b;

    ll k = 0;
    if (N % 2 == 0) {
        for (ll i = 1; i < MOD; i ++) {
            k = (k + dp_2[i] * dp_2[(H * inv[i]) % MOD]) % MOD;
        }
    }
    else {
        for (ll i = 1; i < MOD; i ++) {
            k = (k + dp_1[i] * dp_2[(H * inv[i]) % MOD]) % MOD;
        }
    }
    
    cout << k << '\n';
}
