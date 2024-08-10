// credit a lorenzo ferrari e alla sua soluzione https://github.com/lorenzo-ferrari/olinfo/blob/main/src/ois_boring.cpp 
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int M = 1e9 + 7;
const int MAXN = 1e5 + 5;
const int PW = 131072;
double lg[MAXN];

struct fx {
    ll b, c;                // b * x ^ c
    fx() : b(1), c(0) {}    // 1 * x ^ 0 default
    fx(ll _b, ll _c) : b(_b), c(_c) {}

    ll fastpow(ll n, ll m) {
        if (m == 0) return 1;
        ll h = fastpow(n, m / 2);
        h = (h * h) % M;
        if (m % 2) h = (h * n) % M;
        return h;
    }

    ll value(ll x) {
        return (b * fastpow(x, c)) % M;
    }
};

bool comp(int i, fx &a, fx &b) {
    return lg[a.b] + lg[i] * a.c < lg[b.b] + lg[i] * b.c;
}

// ""metodo di bisezione"" : indago sempre più a fondo l'intersezione settando come valore del segment la funzione maggiore
// nel punto medio del range. Andando a ritrovare la funzione maggiore per un punto, si risale il segment andando a riscoprire
// le scelte fatte in passato, pian piano sezionando nell'intersezione, e confrontare le funzioni segnate nel path O(logn)
// verso il root rispetto al punto della query per trovare il punto più alto. 
fx seg[2 * PW];

void update(int i, int lb, int rb, fx f) {
    // se sx != mid significa che c'è un'intersezione tra le due funzioni nella metà sinistra del range [lb, rb)
    bool sx = comp(lb, seg[i], f);
    bool mid = comp((lb + rb) / 2, seg[i], f);
    // questo comando ha due funzioni:
    // 1) settare in seg[i] la funzione più alta al punto medio del range [lb, rb)
    // 2) seleziono in f quella minore delle due, così da indagare nell'intersezione
    // (a sinistra se sx != mid, altrimenti a destra, anche se potrebbe non esserci nessuna intersezione)
    // e vedere quando quella minore diventa di nuovo maggiore nei nodi più bassi
    if (mid) swap(seg[i], f);

    if (rb - lb == 1) return;

    if (sx != mid) update(2 * i, lb, (lb + rb) / 2, f);
    else update(2 * i + 1, (lb + rb) / 2, rb, f);
}

void find_range(int i, int lb, int rb, int qlb, int qrb, fx f) {
    if (rb <= qlb || qrb <= lb) return;
    if (qlb <= lb && rb <= qrb) return update(i, lb, rb, f);
    find_range(2 * i    , lb, (lb + rb) / 2, qlb, qrb, f);
    find_range(2 * i + 1, (lb + rb) / 2, rb, qlb, qrb, f);
} 

int query(int x) {
    int i = PW + x;
    fx f;
    while (i >= 1) {
        if (comp(x, f, seg[i])) f = seg[i];
        i /= 2;
    }
    return f.value(x);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;

    for (int i = 1; i < MAXN; i ++) lg[i] = log(i);
    fill(seg, seg + 2 * PW, fx());

    for (int i = 1; i <= N; i ++) {
        int a; cin >> a;
        seg[i + PW] = {a, 0};
    }

    int Q; cin >> Q;
    while (Q --) {
        int t; cin >> t;
        if (t == 1) {
            int x; cin >> x;
            cout << query(x) << '\n';
        }
        else {
            int x, y, b, c; cin >> x >> y >> b >> c;
            find_range(1, 0, PW, x, y + 1, {b, c});
        }
    }
}
