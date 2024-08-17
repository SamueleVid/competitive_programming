#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;
constexpr ll MAXN = 1e6 + 5; // 1e6 così il multinomiale funziona (N * 4)
ll fact[MAXN], invfact[MAXN], pw2[MAXN];

ll fp(ll n, ll p) {
    if (!p) return 1;
    ll h = fp(n, p / 2);
    h = (h * h) % MOD;
    if (p % 2) h = (h * n) % MOD;
    return h;
}

void precalc() {
    fact[0] = 1; invfact[0] = 1; pw2[0] = 1;
    for (int i = 1; i < MAXN; i ++) fact[i] = (fact[i - 1] * i) % MOD;
    for (int i = 1; i < MAXN; i ++) invfact[i] = fp(fact[i], MOD - 2);
    for (int i = 1; i < MAXN; i ++) pw2[i] = (pw2[i - 1] * 2) % MOD;
}

ll binomial(ll n, ll k) {
    // n! / (k! (n - k)!)
    ll res = fact[n];
    res = (res * invfact[k]) % MOD;
    res = (res * invfact[n - k]) % MOD;
    return res;
}

ll trinomial(ll n1, ll n2, ll n3) {
    // (n1 + n2 + n3)! / (n1! n2! n3!)
    ll res = fact[n1 + n2 + n3];
    res = (res * invfact[n1]) % MOD;
    res = (res * invfact[n2]) % MOD;
    res = (res * invfact[n3]) % MOD;
    return res;
}

ll fill_holes(int holes, int b, int c) { 
    // Devo contare quanti modi ho per riempire i buchi utilizzando le B e le C a disposizione
    // senza piazzarne due uguali adiacenti.
    if (holes == 0 && b == 0 && c == 0) return 1;
    ll res = 0;

    // Una volta deciso dove piazzare le B nei buchi, la scelta delle C è limitata a 3 possibilità:
    // 1. (C == B + 1), CBC...CBC 
    // 2. (B == C), BC...BC & CB...CB
    // 3. (C == B - 1), BCB...BCB
    // L'idea è di partire dal numero di buchi in cui questi casi si avverano, poi permutare i vari casi
    // con un trinomiale e infine usare sbarre e palle per piazzare le B nei buchi (sapendo che nei casi 2
    // e 3 è necessaria la presenza di B, mentre nel caso 1 può esserci anche una C da sola)
    // Inoltre tengo presente il fatto che per i casi di tipo 2 ci sono due possibilità e dunque
    // devo moltiplicare il tutto per 2 ^ zero. 
    // Sapendo che posso scambiare due casi 2 con un caso 1 e un caso 3,
    // in O(holes) controllo tutti i casi possibili.

    int plus_one = 0, zero = 0, minus_one = 0;

    // se ho tante / poche C, sono costretto a partire con alcuni casi di tipo 1 o 2. 
    if (c > b) plus_one = c - b;
    if (c < b) minus_one = b - c;
    zero = holes - plus_one - minus_one;

    while (zero >= 0) {
        // condizione per far funzionare il binomiale
        if (b >= minus_one + zero & holes > 0) {
            // tutte le permutazioni di +1, 0, -1
            ll curr_res = trinomial(plus_one, zero, minus_one);
            // stars and bars: piazzo i B, sapendo che deve essercene almeno 1 per ogni zero e minus_one
            curr_res = (curr_res * binomial((b - zero - minus_one) + holes - 1, holes - 1)) % MOD;
            // ho due possibilità per ogni zero (BCBCBC, CBCBCB)
            curr_res = (curr_res * pw2[zero]) % MOD;

            res = (res + curr_res) % MOD;
        }

        zero -= 2;
        plus_one ++;
        minus_one ++;
    }

    return res;
}

void solve() {
    int A, B, C; cin >> A >> B >> C;

    ll res = 0;
    // _ A _ A ... A _ A _
    res = (res + fill_holes(A + 1, B, C)) % MOD;
    // A _ A ... A _ A
    res = (res + fill_holes(A - 1, B, C)) % MOD;
    // _ A _ A ... A _ A  +  A _ A ... A _ A _
    res = (res + 2 * fill_holes(A, B, C)) % MOD;

    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;

    precalc();
    while (T --) solve();
}
