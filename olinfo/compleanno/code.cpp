// credit a fabrizio brioni e alla sua soluzione https://forum.olinfo.it/t/editorial-non-ufficiale-oii-2020/6450
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void aggiungi();
void copia();
void incolla();

constexpr int values = 9;
vector<ll> vals {2, 3, 4, 5, 7, 11, 13, 17, 19};
// non ho ancora capito perché il massimo primo è 19 tbh

unordered_map<ll, pair<ll, ll>> dp; // clicks, used value

ll rec(ll x) {
    if (dp.count(x)) return dp[x].first;

    pair<ll, ll> res = {1e18, 1e18};
    for (int i = 0; i < values; i ++) {
        pair<ll, ll> curr = {rec(x / vals[i]) + vals[i] + 1 + x % vals[i], vals[i]};
        res = min(res, curr);
    }

    dp[x] = res;
    return dp[x].first;
}

void auguri(ll N) {

    dp[0] = {0, 1e18};
    dp[1] = {1, 1e18};
    dp[2] = {2, 1e18};
    dp[3] = {3, 1e18};
    dp[4] = {4, 1e18};
    dp[5] = {5, 1e18};

    rec(N);

    // 1 copia 2 incolla 3 aggiungi
    vector<int> actions;

    while (N != 0) {
        for (int i = 0; i < N % dp[N].second; i ++) {
            actions.push_back(3);
        }
        if (dp[N].second != 1e18) {
            for (int i = 0; i < dp[N].second - 1; i ++) {
                actions.push_back(2);
            }
            actions.push_back(1);
        }
        N = N / dp[N].second;
    }

    reverse(actions.begin(), actions.end());
    for (auto x : actions) {
        if (x == 1) copia();
        if (x == 2) incolla();
        if (x == 3) aggiungi();
    }
}
