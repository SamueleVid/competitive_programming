#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            C z = rt[j+k] * a[i+j+k];
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

vd conv(const vd& a, const vd &b) {
    if (a.empty() || b.empty()) return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,0,sz(b)) in[i].imag(b[i]);
    fft(in);
    for (C& x : in) x *= x;
    rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
    
    // questa modifica qua sotto è necessaria, altrimenti i valori dentro il polinomio crescono troppo e il codice rallenta
    rep(i, 0, sz(res)) {
        if (abs(res[i]) > 1e-6) res[i] = 1;
        else res[i] = 0;
    }
    return res;
}

vector<double> fastconv(vector<double> &a, int K) {
    if (K == 1) return a;
    vector<double> h = fastconv(a, K / 2);
    h = conv(h, h);
    if (K % 2) h = conv(h, a);
    return h;
}

void solve() {
    int N, K; cin >> N >> K;
    vi a(N); for (auto &x : a) cin >> x;

    vector<double> p(1001, 0);
    for (auto x : a) p[x] = 1;

    vector<double> res = {1};

    while (K > 0) {
        if (K % 2) res = conv(res, p);
        p = conv(p, p);
        K /= 2;
    }

    rep(i, 0, sz(res)) {
        if (abs(res[i]) > 1e-6) cout << i << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int T = 1;
    // cin >> T;
    while (T --) solve();
}
