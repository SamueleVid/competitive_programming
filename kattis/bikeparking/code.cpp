// credit editorial https://wiki.egoi2024.nl/en/tasks
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<int> X(N), Y(N);
    for (auto &x : X) cin >> x;
    for (auto &y : Y) cin >> y;

    // assegno più + 1 possibili
    int res = 0;
    stack<int> non_zero_x;
    for (int i = 0; i < N; i ++) {
        while (!non_zero_x.empty() && Y[i] > 0) {
            int x_pos = non_zero_x.top();
            int x_value = X[x_pos];

            int delta = min(x_value, Y[i]);
            Y[i] -= delta;
            X[x_pos] -= delta;
            res += delta;

            if (X[x_pos] == 0) non_zero_x.pop();
        }
        if (X[i] > 0) non_zero_x.push(i);
    }

    // metto più + 0 possibili
    for (int i = 0; i < N; i ++) {
        int delta = min(X[i], Y[i]);
        X[i] -= delta;
        Y[i] -= delta;
        res -= Y[i]; // quelli che vanno in - 1 :(
    }

    cout << res << '\n';
}
