#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<ll> X(N), R(N);
    for (auto &x : X) cin >> x;
    for (auto &x : R) cin >> x;
    
    vector<pair<ll,int>> v;
    for (int i = 0; i < N; i ++) {
        v.push_back({X[i] - R[i], i});
        v.push_back({X[i] + R[i], i});
    }

    sort(v.begin(), v.end());
    vector<ll> xs;
    for (auto [x, i] : v) {
        if (xs.empty() || xs.back() != x) xs.push_back(x);
    }

    // mi salvo l'altezza corrente = maggiore tra quelli attivi
    set<pair<ll,int>> active;
    
    int it = 0;
    ll prev_x = -1;
    ll area = 0;
    for (auto x : xs) {

        ll height = 0;
        if (!active.empty()) height = -active.begin()->first;
        area += (x - prev_x) * height;;

        while (it < v.size() && v[it].first <= x) {
            if (active.count({-2*R[v[it].second], v[it].second})) {
                active.erase({-2*R[v[it].second], v[it].second});
            }
            else {
                active.insert({-2*R[v[it].second], v[it].second});
            }
            it ++;
        }

        prev_x = x;
    }

    cout << area << '\n';
}
