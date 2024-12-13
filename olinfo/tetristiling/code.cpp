#include <bits/stdc++.h>
using namespace std;

int q_q[4][4] = {
    {1, 1, 1, 2},
    {4, 1, 2, 2},
    {4, 4, 3, 2},
    {4, 3, 3, 3}
};
int q_q_max = 4;

int c_c[5][5] = {
    {1, 2, 2, 2, 3},
    {1, 1, 2, 3, 3},
    {1, 6, 0, 3, 4},
    {6, 6, 5, 4, 4},
    {6, 5, 5, 5, 4}
};
int c_c_max = 6;

int s_s[7][7] = {
    {1, 2, 2, 2, 3, 3, 3},
    {1, 1, 2, 4, 4, 3, 5},
    {1, 7, 4, 4, 6, 5, 5},
    {8, 7, 7, 0, 6, 6, 5},
    {8, 8, 7, 9, 9, 6, 10},
    {8, 11, 9, 9, 12, 10, 10},
    {11, 11, 11, 12, 12, 12, 10}
};
int s_s_max = 12;

int d_d[10][10] = {
    {1, 1, 1, 2, 3, 3, 4, 4, 4, 5},
    {6, 1, 7, 2, 2, 3, 3, 4, 5, 5},
    {6, 6, 7, 7, 2, 8, 8, 9, 9, 5},
    {10, 6, 7, 11, 8, 8, 12, 13, 9, 9},
    {10, 10, 14, 11, 11, 12, 12, 13, 13, 16},
    {10, 14, 14, 14, 11, 12, 15, 13, 16, 16},
    {17, 17, 18, 18, 19, 19, 15, 15, 20, 16},
    {21, 17, 17, 18, 18, 19, 19, 15, 20, 20},
    {21, 21, 22, 23, 23, 24, 24, 25, 25, 20},
    {21, 22, 22, 22, 23, 23, 24, 24, 25, 25}
};
int d_d_max = 25;

int q_c[4][5] = {
    {1, 2, 2, 2, 3},
    {1, 1, 2, 3, 3},
    {1, 4, 4, 5, 3},
    {4, 4, 5, 5, 5}
};
int q_c_max = 5;

int q_s[4][7] = {
    {1, 2, 2, 2, 3, 3, 3},
    {1, 1, 2, 4, 4, 3, 5},
    {1, 6, 4, 4, 7, 5, 5},
    {6, 6, 6, 7, 7, 7, 5}
};
int q_s_max = 7;

int q_d[4][10] = {
    {1, 1, 2, 2, 3, 3, 4, 4, 4, 5},
    {6, 1, 1, 2, 2, 3, 3, 4, 5, 5},
    {6, 6, 7, 8, 8, 9, 9, 10, 10, 5},
    {6, 7, 7, 7, 8, 8, 9, 9, 10, 10}
};
int q_d_max = 10;

int sei_sei[6][6] = {
    {1, 1, 2, 2, 2, 3},
    {4, 1, 1, 2, 3, 3},
    {4, 4, 5, 5, 6, 3},
    {4, 5, 5, 6, 6, 7},
    {0, 8, 0, 6, 7, 7},
    {8, 8, 8, 0, 0, 7}
};
int sei_sei_max = 8;

constexpr int MAXN = 1e3 + 5;
int grid[MAXN][MAXN];

void z_mod_q(int N) {
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            grid[i][j] = (
                q_q[i % 4][j % 4] 
                + ((i / 4) * (N / 4) + (j / 4)) * q_q_max
            );
        }
    }

    cout << N * N / 4 << '\n';
}

void u_mod_q(int N) {
    if (N == 1) {
        cout << 0 << '\n';
        return;
    }

    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            grid[i][j] = c_c[i][j];
        }
    }

    for (int i = 5; i < N; i ++) {
        for (int j = 0; j < 5; j ++) {
            grid[i][j] = (
                q_c[(i - 5) % 4][j] 
                + c_c_max 
                + ((i - 5) / 4) * q_c_max
            );
        }
    }

    for (int i = 0; i < 5; i ++) {
        for (int j = 5; j < N; j ++) {
            grid[i][j] = (
                q_c[(j - 5) % 4][i] 
                + c_c_max 
                + ((N - 5) / 4 + (j - 5) / 4) * q_c_max
            );
        }
    }

    for (int i = 5; i < N; i ++) {
        for (int j = 5; j < N; j ++) {
            grid[i][j] = (
                q_q[(i - 5) % 4][(j - 5) % 4] 
                + c_c_max
                + ((N - 5) / 4 + (N - 5) / 4) * q_c_max
                + (((i - 5) / 4) * ((N - 5) / 4) + ((j - 5) / 4)) * q_q_max
            );
        }
    }

    cout << (N * N - 1) / 4 << '\n';
}

void d_mod_q(int N) {
    if (N == 2) {
        cout << 0 << '\n';
        return;
    }
    if (N == 6) {
        for (int i = 0; i < 6; i ++) {
            for (int j = 0; j < 6; j ++) {
                grid[i][j] = sei_sei[i][j];
            }
        }
        cout << sei_sei_max << '\n';

        return;
    }

    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            grid[i][j] = d_d[i][j];
        }
    }

    for (int i = 10; i < N; i ++) {
        for (int j = 0; j < 10; j ++) {
            grid[i][j] = (
                q_d[(i - 10) % 4][j] 
                + d_d_max
                + ((i - 10) / 4) * q_d_max
            );
        }
    }

    for (int i = 0; i < 10; i ++) {
        for (int j = 10; j < N; j ++) {
            grid[i][j] = (
                q_d[(j - 10) % 4][i] 
                + d_d_max
                + ((N - 10) / 4 + (j - 10) / 4) * q_d_max
            );
        }
    }

    for (int i = 10; i < N; i ++) {
        for (int j = 10; j < N; j ++) {
            grid[i][j] = (
                q_q[(i - 10) % 4][(j - 10) % 4] 
                + d_d_max
                + ((N - 10) / 4 + (N - 10) / 4) * q_d_max
                + (((i - 10) / 4) * ((N - 10) / 4) + ((j - 10) / 4)) * q_q_max
            );
        }
    }

    cout << N * N / 4 << '\n';
}

void t_mod_q(int N) {
    if (N == 3) {
        cout << 1 << '\n';
        grid[0][0] = 1;
        grid[0][1] = 1;
        grid[0][2] = 1;
        grid[1][1] = 1;
        
        return;
    }

    for (int i = 0; i < 7; i ++) {
        for (int j = 0; j < 7; j ++) {
            grid[i][j] = s_s[i][j];
        }
    }

    for (int i = 7; i < N; i ++) {
        for (int j = 0; j < 7; j ++) {
            grid[i][j] = (
                q_s[(i - 7) % 4][j] 
                + s_s_max
                + ((i - 7) / 4) * q_s_max
            );
        }
    }

    for (int i = 0; i < 7; i ++) {
        for (int j = 7; j < N; j ++) {
            grid[i][j] = (
                q_s[(j - 7) % 4][i] 
                + s_s_max
                + ((N - 7) / 4 + (j - 7) / 4) * q_s_max
            );
        }
    }

    for (int i = 7; i < N; i ++) {
        for (int j = 7; j < N; j ++) {
            grid[i][j] = (
                q_q[(i - 7) % 4][(j - 7) % 4] 
                + s_s_max
                + ((N - 7) / 4 + (N - 7) / 4) * q_s_max
                + (((i - 7) / 4) * ((N - 7) / 4) + ((j - 7) / 4)) * q_q_max
            );
        }
    }

    cout << (N * N - 1) / 4 << '\n';
}

int main() {
    int N; cin >> N;

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            grid[i][j] = 0;
        }
    }

    if (N % 4 == 0) z_mod_q(N);
    if (N % 4 == 1) u_mod_q(N);
    if (N % 4 == 2) d_mod_q(N);
    if (N % 4 == 3) t_mod_q(N);

    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}
