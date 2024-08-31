#include <bits/stdc++.h>
using namespace std;
#define ll long long

int dist(int x, int y, int N) {
    return min((y - x + 2 * N) % (2 * N), (x - y + 2 * N) % (2 * N));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M, Q; cin >> N >> M >> Q;
    vector<int> ks(M);
    for (int i = 0; i < M; i ++) cin >> ks[i];
    set<int> teleports;
    for (int i = 0; i < M; i ++) teleports.insert(ks[i]);
    for (int i = 0; i < M; i ++) teleports.insert(ks[i] + N);


    for (int q = 0; q < Q; q ++) {
        int x, y; cin >> x >> y;
        auto it = teleports.lower_bound(x);
        int sx, dx;
        if (it == teleports.end()) dx = *teleports.begin();
        else dx = *it;
        if (it == teleports.begin()) sx = *teleports.rbegin();
        else {
            it --;
            sx = *it;
        }

        int direct = dist(x, y, N);
        int from_sx = dist(x, sx, N) + dist((sx + N) % (2 * N), y, N) + 1;
        int from_dx = dist(x, dx, N) + dist((dx + N) % (2 * N), y, N) + 1;
        
        int res = min(direct, from_sx);
        res = min(res, from_dx);

        cout << res << '\n';
    }

}
