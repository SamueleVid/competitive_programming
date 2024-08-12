#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll X = 3;
constexpr ll MOD = (1ll << 31) - 1;

constexpr int MAXN = 2e5 + 5;
constexpr int PW = 262144;
ll pw[MAXN];

vector<ll> get_hash(string &v) {
    int n = v.size();
    vector<ll> hash_v(n + 1);
    for (int i = 0; i < n; i ++) {
        hash_v[i + 1] = (hash_v[i] + pw[i] * (v[i] - '0' + 1)) % MOD;
    }
    return hash_v;
}

bool alternating(int la, int ra, int lb, int rb, vector<ll> &hash_a, vector<ll> &hash_b) {
    // controlla se in parallelo le cifre sono solo ('0','1') o ('1','0') = (1,2) o (2,1)
    // la somma è 3 * X ^ (L - 1) + ... + 3 X ^ 2 + 3 X + 3
    // la somma è 3 * ( X ^ L - 1 ) / ( X - 1 ), con X = 3 : (3 ^ ( L + 1 ) - 3) / 2.
    ll a = (hash_a[ra] - hash_a[la] + MOD) % MOD;
    ll b = (hash_b[rb] - hash_b[lb] + MOD) % MOD;

    if (la > lb) b = (b * pw[la - lb]) % MOD;
    if (lb > la) a = (a * pw[lb - la]) % MOD;

    // a + b == (3 ^ (L + 1) - 3) / 2 <=> (a + b) * 2 == 3 ^ (L + 1) - 3
    ll left_side = ((a + b) * (X - 1)) % MOD;
    ll right_side = (pw[ra - la + 1] - X + MOD) % MOD;
    // e poi moltiplico a destra di pw[max(la, lb)] da traslare 
    // la somma geometrica allo stesso grado al left side
    right_side = (right_side * pw[max(la, lb)]) % MOD;
    return left_side == right_side;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    pw[0] = 1;
    for (int i = 1; i < MAXN; i ++) pw[i] = (pw[i - 1] * X) % MOD;

    int N; cin >> N;
    string A, B; cin >> A >> B;

    vector<ll> hash_a = get_hash(A);
    vector<ll> hash_b = get_hash(B);

    int Q; cin >> Q;
    while (Q --) {
        int x, y, l; cin >> x >> y >> l;

        int k = 0;
        for (int p = PW; p >= 1; p /= 2) {
            if (k + p > l) continue;
            if (alternating(x + k, x + k + p, y + k, y + k + p, hash_a, hash_b)) k += p;
        }

        if (k == l || A[x + k] == '0') cout << 1 << " ";
        else cout << 0 << " ";
    }
}
