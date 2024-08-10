#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    long long m, l; cin >> m >> l;
    vector<long long>check_points(n);
    for (auto &x:check_points) cin >> x;
    
    vector<pair<long long,int>>sweepline;
    sweepline.push_back({0,0});
    sweepline.push_back({l+1,0});
    for (auto x : check_points) {
        sweepline.push_back({max(x-m,(long long)0),1});
        sweepline.push_back({min(x+m+1,l+1),-1});
    }

    sort(sweepline.begin(), sweepline.end());

    int minim = 1e9;
    int curr = 0;
    for (int i=0;i<sweepline.size()-1;i++) {
        auto [pos_sx, add_sx] = sweepline[i];
        auto [pos_dx, add_dx] = sweepline[i+1];

        curr += add_sx;
        if ((pos_dx - pos_sx) == 0) continue;

        minim = min(minim, curr);
    }

    cout << minim << '\n';
}
