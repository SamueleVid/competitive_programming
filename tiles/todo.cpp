#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, M; cin >> N >> M;

    int grid[2][M + 5];
    fill(grid[0], grid[0] + M + 5, 1);
    fill(grid[1], grid[1] + M + 5, 1);
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < M; j ++) {
            char c; cin >> c;
            if (c == '.') grid[i][j + 1] = 0;
            else grid[i][j + 1] = 1;
        }
    }

    vector<ll> A(M + 1), B(M + 1), C(M + 1);
    A[0] = 1; B[0] = 0; C[0] = 0;
    A[1] = 1; B[1] = 1; C[1] = 1;
    
    A[2] = 1;
    if (grid[0][1] + grid[1][1] + grid[0][2] + grid[1][2] == 1) A[2] = 2;
    if (grid[0][1] + grid[1][1] + grid[0][2] + grid[1][2] == 0) A[2] = 2;
    
    if (grid[0][1] + grid[1][1] + grid[0][2] == 0) B[2] = 2;
    else B[2] = 1;
    if (grid[0][1] + grid[1][1] + grid[1][2] == 0) C[2] = 2;
    else C[2] = 1;
    
    for (int i = 3; i <= M; i ++) {
        
        // B
        for (int a = 0; a < 1; a ++) {
            if (grid[0][i] == 1) {
                B[i] = A[i - 1];
                continue;
            }
            
            if (grid[0][i - 1] == 1 && grid[1][i - 1] == 1) B[i] = A[i - 2];
            if (grid[0][i - 1] == 1 && grid[1][i - 1] == 0) B[i] = C[i - 1];
            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 1) {
                B[i] += A[i - 2];
                if (grid[0][i - 2] == 0 && grid[1][i - 2] == 1) B[i] += A[i - 3];
                if (grid[0][i - 2] == 0 && grid[1][i - 2] == 0) B[i] += C[i - 2];
            }
            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 0) {
                B[i] = A[i - 2] + C[i - 1];
                if (grid[0][i - 2] == 0) B[i] += A[i - 3]; 
            }
        }


        // C
        for (int a = 0; a < 1; a ++) {
            if (grid[1][i] == 1) {
                C[i] = A[i - 1];
                continue;
            }
            
            if (grid[0][i - 1] == 1 && grid[1][i - 1] == 1) C[i] = A[i - 2];
            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 1) C[i] = B[i - 1];
            if (grid[0][i - 1] == 1 && grid[1][i - 1] == 0) {
                C[i] += A[i - 2];
                if (grid[0][i - 2] == 1 && grid[1][i - 2] == 0) C[i] += A[i - 3];
                if (grid[0][i - 2] == 0 && grid[1][i - 2] == 0) C[i] += B[i - 2];
            }
            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 0) {
                C[i] = A[i - 2] + B[i - 1];
                if (grid[1][i - 2] == 0) C[i] += A[i - 3]; 
            }
        }


        // A
        for (int a = 0; a < 1; a ++) {
            if (grid[0][i] == 1 && grid[1][i] == 1) {
                A[i] = A[i - 1];
                continue;
            }
            if (grid[0][i] == 0 && grid[1][i] == 1) {
                A[i] = B[i];
                continue;
            }
            if (grid[0][i] == 1 && grid[1][i] == 0) {
                A[i] = C[i];
                continue;
            }

            A[i] = A[i - 1];

            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 1) A[i] += A[i - 2];
            if (grid[0][i - 1] == 1 && grid[1][i - 1] == 0) A[i] += A[i - 2];

            if (grid[0][i - 1] == 0 && grid[1][i - 1] == 0) {
                A[i] += A[i - 2];
                if (grid[0][i - 2] == 1 && grid[1][i - 2] == 0) A[i] += A[i - 3]; 
                if (grid[0][i - 2] == 0 && grid[1][i - 2] == 1) A[i] += A[i - 3]; 
                if (grid[0][i - 2] == 0 && grid[1][i - 2] == 0) A[i] += B[i - 2] + C[i - 2]; 
            }
        }

        A[i] %= MOD; B[i] %= MOD; C[i] %= MOD;
    }

    cout << A[M] << '\n';
}
