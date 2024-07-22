#include <bits/stdc++.h>
using namespace std;
#define ll long long

void posiziona(int D, int T);

void budget(int B);

void irriga(int C, int N, vector<int>& X, vector<int>& P) {

    vector<pair<ll,ll>> ps(N);
    for (int i = 0; i < N; i ++) ps[i] = {X[i], P[i]};
    sort(ps.begin(), ps.end());

    vector<pair<ll,ll>> ranges;
    ll cost = C + ps[0].second;
    ranges.push_back({ps[0].first - ps[0].second, ps[0].first + ps[0].second});
    for (int i = 1; i < N; i ++) {

        ll sx = ps[i].first - ps[i].second;
        ll dx = ps[i].first + ps[i].second;

        ll new_sx = min(sx, ranges.back().first);
        ll new_dx = max(dx, ranges.back().second);

        ll prev_cost = (ranges.back().second - ranges.back().first) / 2;
        ll new_cost = (new_dx - new_sx) / 2;

        if (new_cost - prev_cost < (dx - sx) / 2 + C) {
            cost += new_cost - prev_cost;
            ranges.back().first = new_sx;
            ranges.back().second = new_dx;
        }
        else {
            cost += C + (dx - sx) / 2;
            ranges.push_back({sx, dx});
        }

        if (ranges.size() >= 2) {
            new_sx = min(ranges[ranges.size() - 1].first, ranges[ranges.size() - 2].first);
            new_dx = max(ranges[ranges.size() - 1].second, ranges[ranges.size() - 2].second);
        }
        while (ranges.size() >= 2 && (new_dx - new_sx) / 2 + C
        < (ranges[ranges.size() - 1].second - ranges[ranges.size() - 1].first) / 2
        + (ranges[ranges.size() - 2].second - ranges[ranges.size() - 2].first) / 2 + 2 * C
        ) {
            cost -= (ranges[ranges.size() - 1].second - ranges[ranges.size() - 1].first) / 2
            + (ranges[ranges.size() - 2].second - ranges[ranges.size() - 2].first) / 2 + 2 * C;
            cost += (new_dx - new_sx) / 2 + C;
            
            ranges.pop_back();
            ranges.back().first = new_sx;
            ranges.back().second = new_dx;
            
            if (ranges.size() >= 2) {
                new_sx = min(ranges[ranges.size() - 1].first, ranges[ranges.size() - 2].first);
                new_dx = max(ranges[ranges.size() - 1].second, ranges[ranges.size() - 2].second);
            }
        }
    }
    for (auto [a, b] : ranges) posiziona((a + b) / 2, (b - a) / 2);
    budget(cost);
}
