#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, Q; cin >> N >> Q;
    vector<int> stati(N, 1);
    vector<int> when(N, 0);
    // 0 : behind, 1 : ahead
    int last_reset = 0;
    int sol = 0;
    for (int q = 0; q < Q; q ++) {
        int x; cin >> x;
        if (x < 0) {
            stati[-x] = 1;
        }
        else {
            if (stati[x] == 0 && when[x] >= last_reset) {
                sol ++;
                last_reset = q;
            }
            stati[x] = 0;
            when[x] = q;
        }
    }
    cout << sol << '\n';
}
