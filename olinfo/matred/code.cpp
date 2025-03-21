#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int N, M; cin >> N >> M;

    ll grid[N][M];

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < M; j ++) cin >> grid[i][j];
    }

    // check se possibile
    vector<ll> a(3), b(3);
    int k = 0;
    for (int i = 0; i < N; i ++) {
        k = ( 3 - (i % 3) ) % 3;
        for (int j = 0; j < M; j ++) {
            a[k] += grid[i][j];
            k = (k + 1 < 3) ? k + 1 : 0;
        }
    }
    k = 0;
    for (int i = 0; i < N; i ++) {
        k = i % 3;
        for (int j = M - 1; j >= 0; j --) {
            b[k] += grid[i][j];
            k = (k + 1 < 3) ? k + 1 : 0;
        }
    }
    if (a[0] != a[1] || a[1] != a[2] || a[0] != a[2]) {
        cout << "NO" << '\n';
        return 0;

    }
    if (b[0] != b[1] || b[1] != b[2] || b[0] != b[2]) {
        cout << "NO" << '\n';
        return 0;
    }

    vector<vector<int>> mosse;
    for (int j = 0; j < M - 3; j ++) {
        for (int i = 0; i < N - 2; i ++) {
            for (auto k : {1, 2}) {
                if (grid[i + k][j] < grid[i][j]) {
                    int d = grid[i][j] - grid[i + k][j];
                    grid[i + k][j] += d;
                    grid[i + k][j + 1] += d;
                    grid[i + k][j + 2] += d;
                    mosse.push_back({j, i + k, j + 2, i + k, d});
                }
            }
            int a = grid[i][j];
            grid[i][j] -= a;
            grid[i + 1][j] -= a;
            grid[i + 2][j] -= a;
            mosse.push_back({j, i, j, i + 2, -a});
        }
        for (int i = N - 2; i < N; i ++) {
            for (auto k : {1, 2}) {
                if (grid[i][j + k] < grid[i][j]) {
                    int d = grid[i][j] - grid[i][j + k];
                    grid[N - 3][j + k] += d;
                    grid[N - 2][j + k] += d;
                    grid[N - 1][j + k] += d;
                    mosse.push_back({j + k, N - 3, j + k, N - 1, d});
                }
            }
            int a = grid[i][j];
            grid[i][j] -= a;
            grid[i][j + 1] -= a;
            grid[i][j + 2] -= a;
            mosse.push_back({j, i, j + 2, i, -a});
        }
    }

    for (int j = M - 3; j < M; j ++) {
        for (int i = 0; i < N - 3; i ++) {
            int minim = min(grid[i + 1][j], grid[i + 2][j]);
            if (grid[i][j] > minim) {
                int d = grid[i][j] - minim;
                grid[i + 1][j] += d;
                grid[i + 2][j] += d;
                grid[i + 3][j] += d;
                mosse.push_back({j, i + 1, j, i + 3, d});
            }
            int a = grid[i][j];
            grid[i][j] -= a;
            grid[i + 1][j] -= a;
            grid[i + 2][j] -= a;
            mosse.push_back({j, i, j, i + 2, -a});
        }
    }

    ll mass = 0;
    for (int j = M - 3; j < M; j ++) {
        mass = max(mass, grid[N - 3][j]);
    }

    for (int j = M - 3; j < M; j ++) {
        if (grid[N - 3][j] < mass) {
            int d = mass - grid[N - 3][j];
            grid[N - 3][j] += d;
            grid[N - 2][j] += d;
            grid[N - 1][j] += d;
            mosse.push_back({j, N - 3, j, N - 1, d});
        }
    }

    for (int i = N - 3; i < N; i ++) {
        int a = grid[i][M - 3];
        grid[i][M - 3] -= a;
        grid[i][M - 2] -= a;
        grid[i][M - 1] -= a;
        mosse.push_back({M - 3, i, M - 1, i, -a});
    }

    if (mosse.size() > N * M * 2) {
        cout << "NO" << '\n';
        return 0;
    }

    cout << "YES" << '\n';
    cout << mosse.size() << '\n';
    for (auto x : mosse) {
        cout << x[1] + 1 << " " << x[0] + 1 << " " << x[3] + 1 << " " << x[2] + 1 << " " << x[4] << '\n';
    }
}