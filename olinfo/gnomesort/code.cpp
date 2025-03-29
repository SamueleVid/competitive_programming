#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; i ++) cin >> P[i];

    vector<int> check = P;
    bool flag = 1;
    for (int i = 0; i < N; i ++) {
        if (check[check[i]] != i) {
            flag = 0;
        }
        swap(check[check[i]], check[i]);
    }
    if (!flag) {
        cout << "NO" << '\n';
        return 0;
    }
    cout << "YES" << '\n';

    vector<vector<int>> moves;
    for (int i = 0; i < N; i ++) {
        if (P[i] == i) continue;
        int altro = P[i];
        vector<int> curr_moves;
        // for some reason if I don't stop the for loop at "altro" it results in both WA and TLE.
        for (int j = i; j < altro; j ++) {
            if (P[j] != j && P[j] <= altro) {
                curr_moves.push_back(j);
                curr_moves.push_back(P[j]);
                altro = P[j];
                swap(P[j], P[P[j]]);
            }
        }

        moves.push_back(curr_moves);
    }

    cout << moves.size() << '\n';
    for (auto y : moves) {
        cout << y.size() << " ";
        for (auto x : y) cout << x << " ";
        cout << '\n';
    }

}
