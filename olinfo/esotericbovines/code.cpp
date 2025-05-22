#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> a(N), b(N);
    for (int i = 0; i < N; i ++) cin >> a[i];
    for (int i = 0; i < N; i ++) cin >> b[i];

    vector<pair<vector<ll>, vector<ll>>> groups;
    groups.push_back({a, b});

    for (int p = 59; p >= 0; p --) {

        ll L = 0; 
        for (auto g : groups) {
            ll x_1 = 0, y_1 = 0;
            ll x_2 = 0, y_2 = 0;
            for (auto x : g.first) {
                if (x & (1ll << p)) x_2 ++;
                else x_1 ++;
            }
            for (auto y : g.second) {
                if (y & (1ll << p)) y_2 ++;
                else y_1 ++;
            }
            L += x_1 * y_1 + x_2 * y_2;
        }

        vector<pair<vector<ll>, vector<ll>>> groups_new;
        for (auto g : groups) {
            vector<ll> x_1, x_2, y_1, y_2;
            for (auto x : g.first) {
                if (x & (1ll << p)) x_2.push_back(x);
                else x_1.push_back(x);
            }
            for (auto y : g.second) {
                if (y & (1ll << p)) y_2.push_back(y);
                else y_1.push_back(y);
            }
            if (L >= K) {
                if (!x_1.empty() && !y_1.empty()) groups_new.push_back({x_1, y_1});
                if (!x_2.empty() && !y_2.empty()) groups_new.push_back({x_2, y_2});
            }
            else {
                if (!x_1.empty() && !y_2.empty()) groups_new.push_back({x_1, y_2});
                if (!x_2.empty() && !y_1.empty()) groups_new.push_back({x_2, y_1});
            }
        }
        if (L < K) K -= L;

        swap(groups, groups_new);
    }

    cout << (groups[0].first[0] ^ groups[0].second[0]) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
