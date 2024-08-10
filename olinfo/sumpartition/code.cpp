#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int PW = 262144;

// seg[PW + j] = k indica che esistono a_1 < a_2 <... a_k e b_1 < b_2 < ... b_k = j tali che psa[a_i] = psb[b_i].
int seg[2 * PW];
void update(int x, int v) {
    x += PW;
    while (x >= 1) {
        seg[x] = max(seg[x],v);
        x /= 2;
    }
}
int query(int x) {
    int lb = PW;
    int rb = x + PW;
    int res = 0;
    while (lb <= rb) {
        if (lb % 2 == 1) {
            res = max(res, seg[lb]);
            lb ++;
        }
        if (rb % 2 == 0) {
            res = max(res, seg[rb]);
            rb --;
        }
        lb /= 2; rb /= 2;
    }
    return res;
}
int muraglia(int v) {
    int x = 1;
    int lb = 0, rb = PW;
    while (rb - lb > 1) {
        if (seg[2 * x] >= v) {
            x = 2 * x;
            rb = (lb + rb) / 2;
        }
        else {
            x = 2 * x + 1;
            lb = (lb + rb) / 2;
        }
    }
    return lb;
}

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<ll> a(n), b(m), psa(n + 1), psb(m + 1);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    for (int i = 0; i < n; i ++) psa[i + 1] = psa[i] + a[i];
    for (int i = 0; i < m; i ++) psb[i + 1] = psb[i] + b[i];

    vector<int>b_to_a(m + 1); // mutabile nel tempo, serve per ritorvare l'a precedente di una determinata iterazione di i
    vector<int>a_to_b(n + 1); // fisso ma non induttivo: collega psa[i] = psb[a_to_b[i]]
    vector<int>a_to_prev_a(n + 1); // ci da la soluzione degli a percorrendo il grafo al contrario
    for (int i = 1; i <= n; i ++) {
        int j = 1;
        for (int pw = PW; pw >= 1; pw /= 2) {
            if (j + pw <= m && psb[j + pw] <= psa[i]) j += pw;
        }
        if (psa[i] == psb[j]) {
            a_to_b[i] = j;
            int da_sovrascrivere = seg[PW + j];
            int max_prev = query(j - 1);
            update(j, max_prev + 1);
            int prev_i = muraglia(max_prev);
            if (da_sovrascrivere < seg[PW + j]) b_to_a[j] = i;
            a_to_prev_a[i] = b_to_a[prev_i];
        }
    }

    if (psa[n] != psb[m] || seg[PW + m] < k) {
        cout << -1 << '\n';
        return 0;
    }

    vector<int> res_a(k - 1), res_b(k - 1);
    int curr = n;
    for (int i = k - 2; i >= 0; i --) {
        curr = a_to_prev_a[curr];
        res_a[i] = curr;
        res_b[i] = a_to_b[curr];
    }

    for (int i = 0; i < k - 1; i ++) cout << res_a[i] << " ";
    cout << '\n';
    for (int i = 0; i < k - 1; i ++) cout << res_b[i] << " ";
    cout << '\n';
}
