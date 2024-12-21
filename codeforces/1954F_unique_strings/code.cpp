#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;

ll fp(ll a, ll p) {
    if (!p) return 1;
    ll h = fp(a, p / 2);
    h = (h * h) % MOD;
    if (p % 2) h = (h * a) % MOD;
    return h;
}

ll inv(ll a) {
    return fp(a, MOD - 2);
}

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

vector<int> get_divisors(int N) {
    vector<int> divs;
    int i = 1;
    while (i * i <= N) {
        if (N % i == 0) {
            divs.push_back(i);
            if (i * i != N) divs.push_back(N / i);
        }
        i ++;
    }
    return divs;
}

void solve() {
    int N, C, K; cin >> N >> C >> K;
    vector<int> divs = get_divisors(N);
    
    // Keep track for how many numbers [1, N] each divisors corrisponds to.
    map<int, ll> gcds;
    for (int i = 1; i <= N; i ++) gcds[gcd(N, i)] ++;

    // Subtract from the total the unwanted configurations.
    // Always keep in mind Burnside's Lemma.
    ll all = 0;
    for (auto d : divs) {
        ll delta = (fp(2, d) * gcds[d]) % MOD;
        all = (all + delta) % MOD;
    }
    all = (all * inv(N)) % MOD;

    // Exclude all the configuration whose number of ones
    // is less than C or more than C + K.
    // The complexity of this is O(N * sum(d)), which is roughly O(N ^ 2).
    vector<ll> unwanted(N + 1);
    for (auto d : divs) {
        vector<ll> knapsack(N + 1);
        knapsack[0] = 1;
        for (int i = 0; i < d; i ++ ) {
            for (int j = N; j >= N / d; j --) {
                knapsack[j] = (knapsack[j] + knapsack[j - N / d]) % MOD;
            }
        }

        for (int i = 0; i < N + 1; i ++) knapsack[i] = (knapsack[i] * gcds[d]) % MOD;

        for (int j = 0; j <= N; j ++) {
            unwanted[j] = (unwanted[j] + knapsack[j]) % MOD;
        }
    }

    // I perform Burnside lemma on each configuration with i ones.
    // I can do this because these sets are closed under cyclic shift.
    for (int i = 0; i <= N; i ++) unwanted[i] = (unwanted[i] * inv(N)) % MOD;

    for (int i = 0; i < C; i ++) all = (all - unwanted[i] + MOD) % MOD;
    for (int i = C + K + 1; i <= N; i ++) all = (all - unwanted[i] + MOD) % MOD;

    // Exclude all the configurations whose number of ones is between
    // C and C + K and that don't have C ones in a row
    // The complexity of this is O(sum(d ^ 2)) <= O(N * sum(d)),
    // which is roughly O(N ^ 2).
    ll unwanted2 = 0;
    for (auto d : divs) {
        // Instead of counting each one (N / d) times 
        // and keeping the target range [C, C + K],
        // let's count each one 1 time and keep the target 
        // range [ceil(C / (N / d)), floor((C + K) / (N / d))] = [C_1, C_K_1].
        ll C_1 = (C + (N / d) - 1) / (N / d);
        ll C_K_1 = (C + K) / (N / d); // Upperbound o(d)
        // dp[i][j] : the number of binary strings of lenght i with 
        // no less than C_1 - j and no more than C_K_1 - j ones, 
        // that don't have C ones in a row
        vector<vector<ll>> dp(d, vector<ll>(d + 1));
        vector<ll> ps(2 * d); // ps[i + j] = sum (dp[i - z][j + z]) (z = 0, C - 1)
        for (int i = C_1; i <= C_K_1; i ++) dp[0][i] = 1;
        for (int i = C_1; i <= C_K_1; i ++) ps[i] = 1;
        for (int i = 1; i < d; i ++) {
            for (int j = d; j >= 0; j --) {
                
                // Place z [0, C - 1] ones and a zero.
                dp[i][j] = ps[i + j - 1];

                if (i - C >= 0 && j + C <= d) {
                    ps[i + j] = (ps[i + j] - dp[i - C][j + C] + MOD) % MOD;
                }
                ps[i + j] = (ps[i + j] + dp[i][j]) % MOD;
            }
        }

        ll res = 0;
        // Can't have all ones, because then there would be C ones in a row,
        // so there must be at least one zero. We use this information to prevent
        // having C ones in a row when considering wrapping around the string 
        // from the end to the beginning.
        for (int i = 0; i < min(C, d); i ++) {
            // Place i ones at the beginning, followed by a zero.
            // The end of the string must not end with C - i ones.
            ll curr = 0;
            for (int z = 0; z < C - i && d - i - 1 - z >= 0 && z + i <= d; z ++) {
                curr = (curr + dp[d - i - 1 - z][z + i]) % MOD;
            }
            res = (res + curr) % MOD;
        }

        res = (res * gcds[d]) % MOD;

        unwanted2 = (unwanted2 + res) % MOD;
    }

    // Since this set of the configurations counted in unwanted2 is closed 
    // under cyclic shift, Burnside's Lemma can be applied.
    unwanted2 = (unwanted2 * inv(N)) % MOD;

    all = (all - unwanted2 + MOD) % MOD;

    cout << all << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}
