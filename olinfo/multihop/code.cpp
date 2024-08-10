// credit a francesco vercellesi e alla sua soluzione https://github.com/franv314/competitive/blob/soluzioni/olinfo/WEOI/multihop/multihop.cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr int MAXN = 1e5 + 5;
constexpr int LOG = 18;
vector<int> adj[MAXN];
int p[MAXN];
int depth[MAXN];
int binlift[LOG][MAXN];

struct matrix {
    /*
    La matrice rappresenta il costo rispetto a m[la mossa per entrare nel path][la mossa per arrivare all'ultimo elemento del path]
    con 0 : utilizzare A (low power), e 1 : utilizzare B + C (low power)
    la figata è che mergiare due matrici è letteralmente come moltiplicarle ma con la somma e il minimo
    */
    ll m[2][2];

    matrix() {
        m[0][0] = 0;
        m[0][1] = 0;
        m[1][0] = 0;
        m[1][1] = 0;
    }
    matrix(ll a, ll b, ll c, ll d) {
        m[0][0] = a;
        m[0][1] = b;
        m[1][0] = c;
        m[1][1] = d;
    }

    bool is_identity() {
        return m[0][0] == 0 && m[0][1] == 0 && m[1][0] == 0 && m[1][1] == 0;
    }

    ll get_res() {
        return min(m[0][0], m[0][1]);
    }
};
matrix operator+(matrix &a, matrix &b) {
    // non riesco a costruire un elemento identità decente 😭
    if (a.is_identity()) return b;
    if (b.is_identity()) return a;

    matrix ans(1e18, 1e18, 1e18, 1e18);
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 2; j ++) {
            for (int k = 0; k < 2; k ++) {
                ans.m[i][j] = min(ans.m[i][j], a.m[i][k] + b.m[k][j]);
            }
        }
    }
    return ans;
}
matrix dp_up[LOG][MAXN];
matrix dp_dn[LOG][MAXN];

void dfs(int u) {
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        depth[x] = depth[u] + 1;   
        p[x] = u;
        dfs(x);
    }
}

matrix lca_dp(int a, int b) {
    assert(a != b);

    matrix ans_a;
    matrix ans_b;
    
    if (depth[a] > depth[b]) {
        for (int pw = LOG - 1; pw >= 0; pw --) {
            if (depth[binlift[pw][a]] >= depth[b]) {
                ans_a = ans_a + dp_up[pw][a];
                a = binlift[pw][a];
            }
        }
    }
    if (depth[b] > depth[a]) {
        for (int pw = LOG - 1; pw >= 0; pw --) {
            if (depth[binlift[pw][b]] >= depth[a]) {
                ans_b = dp_dn[pw][b] + ans_b;
                b = binlift[pw][b];
            }
        }
    }

    if (a == b) {
        return ans_a + ans_b;
    }

    for (int pw = LOG - 1; pw >= 0; pw --) {
        if (binlift[pw][a] != binlift[pw][b]) {
            ans_a = ans_a + dp_up[pw][a];
            ans_b = dp_dn[pw][b] + ans_b;
            
            a = binlift[pw][a];
            b = binlift[pw][b];
        }
    }

    ans_a = ans_a + dp_up[0][a];
    ans_b = dp_dn[0][b] + ans_b;

    return ans_a + ans_b;
}

void init(int N, int C, vector<int> A, vector<int> B, vector<int> U, vector<int> V) {
    for (int i = 0; i < N - 1; i ++) {
        adj[U[i]].push_back(V[i]);
        adj[V[i]].push_back(U[i]);
    }
    
    // creo N per sbuggare l'lca
    p[0] = N;
    p[N] = N;
    depth[0] = 0;
    depth[N] = -1;
    dfs(0);

    for (int i = 0; i <= N; i ++) {
        // qua spiega bene la situazione iniziale della matrice, autoesplicativo (figo che m[1][1] = C)
        binlift[0][i] = p[i];
        dp_up[0][i] = matrix(A[i], B[i] + C, A[i], C); // path parte da i arriva a binlift[j][i]
        if (i != 0) {
            dp_dn[0][i] = matrix(A[p[i]], B[p[i]] + C, A[p[i]], C); // path parte da binlift[j][i] e arriva a i
        }
    }
    for (int i = 1; i < LOG; i ++) {
        for (int j = 0; j <= N; j ++) {
            binlift[i][j] = binlift[i - 1][binlift[i - 1][j]];
            dp_up[i][j] = dp_up[i - 1][j] + dp_up[i - 1][binlift[i - 1][j]];
            dp_dn[i][j] = dp_dn[i - 1][binlift[i - 1][j]] + dp_dn[i - 1][j];
        }        
    }
}

ll query(int X, int Y) {
    matrix ans = lca_dp(X, Y);
    return ans.get_res();
}
