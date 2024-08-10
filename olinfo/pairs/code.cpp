#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int PW = 262144;
const int MAX_M = 80;

struct pt {
    int x, y, z;
};

bool operator<(const pt &a, const pt &b) {
    if (a.z != b.z) return a.z < b.z;
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int seg[2 * PW];
ll query(int x) {
    int lb = PW;
    int rb = PW + x;

    ll res = 0;
    while (lb <= rb) {
        if (lb % 2 == 1) res += seg[lb], lb ++;
        if (rb % 2 == 0) res += seg[rb], rb --;
        lb /= 2, rb /= 2;
    }

    return res;
}
void update(int x, int d) {
    x += PW;
    while (x > 0) seg[x] += d, x /= 2;
}

int cubo[2 * MAX_M][2 * MAX_M][MAX_M];

ll one_dimention(int B, int N, int D, int M, vector<pt>&pts) {
    sort(pts.begin(), pts.end());
    ll res = 0;
    int lb = 0;
    for (int rb = 0; rb < N; rb ++) {
        while (pts[rb].x - pts[lb].x > D) lb ++;
        res += rb - lb;
    }

    return res;
}

ll two_dimentions(int B, int N, int D, int M, vector<pt>&pts) {
    vector<pt> diag_pts(N);
    for (int i = 0; i < N; i ++) {
        diag_pts[i].y = pts[i].y - pts[i].x + M;
        diag_pts[i].x = pts[i].y + pts[i].x;
    }
    sort(diag_pts.begin(), diag_pts.end());

    ll res = 0;
    int lb = 0;
    for (int rb = 0; rb < N; rb ++) {
        while (diag_pts[rb].x - diag_pts[lb].x > D) {
            int up = max(diag_pts[lb].y - D, 1);
            int dn = min(diag_pts[lb].y + D, 2 * M);
            update(up, -1);
            update(dn + 1, 1);
            lb ++;
        }

        res += query(diag_pts[rb].y);

        int up = max(diag_pts[rb].y - D, 1);
        int dn = min(diag_pts[rb].y + D, 2 * M);
        update(up, 1);
        update(dn+1, -1);
    }

    return res;
}

ll three_dimentions(int B, int N, int D, int M, vector<pt>&pts) {
    vector<pt> diag_pts(N);
    for (int i = 0; i < N; i ++) {
        diag_pts[i].y = pts[i].y - pts[i].x + M;
        diag_pts[i].x = pts[i].y + pts[i].x;
        diag_pts[i].z = pts[i].z;
    }

    for (auto [x, y, z] : diag_pts) {
        for (int d = D; d >= 0 && z - D + d >= 1; d --) {
            int up = max(y - d, 1);
            int dn = min(y + d, 2 * M);
            int sx = max(x - d, 1);
            int dx = min(x + d, 2 * M);
            cubo[sx][up][z - D + d] ++;
            cubo[dx + 1][up][z - D + d] --;
            cubo[sx][dn + 1][z - D + d] --;
            cubo[dx + 1][dn + 1][z - D + d] ++;
        }
        for (int d = D - 1; d >= 0 && z + D - d <= M; d --) {
            int up = max(y - d, 1);
            int dn = min(y + d, 2 * M);
            int sx = max(x - d, 1);
            int dx = min(x + d, 2 * M);
            cubo[sx][up][z + D - d] ++;
            cubo[dx + 1][up][z + D - d] --;
            cubo[sx][dn + 1][z + D - d] --;
            cubo[dx + 1][dn + 1][z + D - d] ++;
        }
    }

    for (int z = 1; z <= M; z ++) {
        for (int y = 1; y <= 2 * M; y ++) {
            for (int x = 1; x <= 2 * M; x ++) {
                cubo[x + 1][y][z] += cubo[x][y][z];
            }
        }
    }
    for (int z = 1; z <= M; z ++) {
        for (int y = 1; y <= 2 * M; y ++) {
            for (int x = 1; x <= 2 * M; x ++) {
                cubo[x][y + 1][z] += cubo[x][y][z];
            }
        }
    }

    ll res = 0;
    for (auto [x, y, z] : diag_pts) {
        res += cubo[x][y][z] - 1;
    }

    return res / 2;
}

int main() {

    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int B, N, D, M;
    cin >> B >> N >> D >> M;
    vector<pt> pts(N);
    if (B == 1) {
        for (int i = 0; i < N; i ++) cin >> pts[i].x;
        cout << one_dimention(B,N,D,M,pts) << '\n';
    }
    if (B == 2) {
        for (int i = 0; i < N; i ++) cin >> pts[i].x >> pts[i].y;
        cout << two_dimentions(B,N,D,M,pts) << '\n';
    }
    if (B == 3) {
        for (int i = 0; i < N; i ++) cin >> pts[i].x >> pts[i].y >> pts[i].z;
        cout << three_dimentions(B,N,D,M,pts) << '\n';
    }
}
