#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;

int solve(int N, vector<int> L, vector<int> W) {
    ll res = 0;

    // individual
    for (int i = 0; i < N; i ++) {
        ll w = W[i];
        ll h = L[i];
        ll horiz = ((h * (h + 1)) / 2) % MOD;
        ll vertic = ((w * (w + 1)) / 2) % MOD;
        ll curr = (horiz * vertic) % MOD;
        res = (res + curr) % MOD;
    }

    // invariante: decrescente second
    stack<pair<ll, ll>> s; // width, (height + 1) choose 2 
    ll curr_sum = 0;

    for (int i = 0; i < N; i ++) {
        ll w = W[i];
        ll new_h = L[i];
        ll sostituiti = 0;
        ll to_remove = 0;
        ll to_add = 0;
        while (!s.empty() && s.top().second > new_h) {
            ll d = ((s.top().second * (s.top().second + 1)) / 2) % MOD;
            d = (d * s.top().first) % MOD;
            to_remove = (to_remove + d) % MOD;
            sostituiti = (sostituiti + s.top().first) % MOD;
            s.pop();
        }

        if (sostituiti > 0) s.push({sostituiti, new_h});
        to_add = ((new_h * (new_h + 1)) / 2) % MOD;
        to_add = (to_add * sostituiti) % MOD;

        curr_sum = (curr_sum - to_remove + MOD) % MOD;
        curr_sum = (curr_sum + to_add) % MOD;

        ll d = (curr_sum * w) % MOD;
        res = (res + d) % MOD;

        ll nuovo = ((new_h * (new_h + 1)) / 2) % MOD;
        nuovo = (nuovo * w) % MOD;

        curr_sum = (curr_sum + nuovo) % MOD;
        s.push({w, new_h});
    }

    return res;
    
}

int main() {
    int N;
    cin >> N;

    vector<int> L(N), W(N);

    for(int &x: L) cin >> x;
    for(int &x: W) cin >> x;

    cout << solve(N, L, W) << "\n";
}
