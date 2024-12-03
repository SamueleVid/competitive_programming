#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    for (int i = 0; i < N; i ++) {
        string s; cin >> s;
        for (int j = 0; j < M; j ++) {
            A[i][j] = (s[j] == '0') ? 0 : 1;
        }
    }

    vector<vector<int>> B = A;

    // flipping a row or column doesn't change its errors.
    // since you fix a column by flipping rows and vice versa
    // fixing the errors (3 same elements) in one direction
    // mantains the same number of errors in the other direction
    // so just fix the errors in both directions indipendently.

    int dp[2][2], temp[2][2];

    // fix horizontally
    for (int a : {0, 1}) {
        for (int b : {0, 1}) {
            dp[a][b] = a + b;
        }
    }

    for (int j = 2; j < M; j ++) {
        
        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                temp[a][b] = 1e9;
            }
        }

        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                if (dp[a][b] == 1e9) continue;
                
                for (int c : {0, 1}) {
                    bool possible = true;
                    for (int i = 0; i < N; i ++) {
                        int new_a = B[i][j - 2] ^ a;
                        int new_b = B[i][j - 1] ^ b;
                        int new_c = B[i][j] ^ c;
                        if (new_a == new_b && new_b == new_c) {
                            possible = false;
                            break;
                        }
                    }
                    if (possible) {
                        temp[b][c] = min(temp[b][c], dp[a][b] + c);
                    }
                }

            }
        }

        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                dp[a][b] = temp[a][b];
            }
        }
    }

    int sol_horiz = 1e9;
    for (int a : {0, 1}) {
        for (int b : {0, 1}) {
            sol_horiz = min(sol_horiz, dp[a][b]);
        }
    }

    // fix vertically
    for (int a : {0, 1}) {
        for (int b : {0, 1}) {
            dp[a][b] = a + b;
        }
    }

    for (int i = 2; i < N; i ++) {
        
        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                temp[a][b] = 1e9;
            }
        }

        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                if (dp[a][b] == 1e9) continue;
                
                for (int c : {0, 1}) {
                    bool possible = true;
                    for (int j = 0; j < M; j ++) {
                        int new_a = B[i - 2][j] ^ a;
                        int new_b = B[i - 1][j] ^ b;
                        int new_c = B[i][j] ^ c;
                        if (new_a == new_b && new_b == new_c) {
                            possible = false;
                            break;
                        }
                    }
                    if (possible) {
                        temp[b][c] = min(temp[b][c], dp[a][b] + c);
                    }
                }

            }
        }

        for (int a : {0, 1}) {
            for (int b : {0, 1}) {
                dp[a][b] = temp[a][b];
            }
        }
    }

    int sol_vertic = 1e9;
    for (int a : {0, 1}) {
        for (int b : {0, 1}) {
            sol_vertic = min(sol_vertic, dp[a][b]);
        }
    }

    int sol = sol_horiz + sol_vertic;

    if (sol >= 1e9) sol = -1;
    cout << sol << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
