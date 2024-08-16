#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MOD = 1e9 + 7;
constexpr ll MAXN = 1e6 + 5; // 1e6 così il trinomiale funziona (N * 3)
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

ll fill_holes(int x, int b, int c) { 
    // x = numero di buchi
    ll res = 0;
    // si decide quante B assegnare ad ogni buco, tenendo conto che i possibili C sono:
    // 1) (B == C + 1), BCB...BCB
    // 2) (B == C - 1), CBC...CBC
    // 3) (B == C), BC...BC & CB...CB
    // nel caso in cui ad un buco si assegni 0 B, siamo costretti al caso 2) e inserire una C.
    // zero_b indica il numero di buchi dove vengono piazzate 0 B.
    for (int zero_b = 0; zero_b < x; zero_b ++) {
        int c_to_use = c - zero_b; // piazzo le C nei buchi
        if (c_to_use < 0) continue;
        
        int holes = x - zero_b;
        ll curr_res = 0; 
        
        // se non posso mettere almeno un B in ogni buco è impossibile
        if (holes > b) continue;

        // immaginando i buchi riempiti con le B, devo decidere se le C sono
        // +1, -1, 0 rispetto al numero di B. Inizialmente setto tutto a 0
        // tranne quelle necessarie (nel caso ci siano più/meno C_to_use di B).
        // ogni coppia di 0 può essere sostituita da un -1 e un 1.
        // L'importante è che la somma dei +1, -1, 0 sia C_to_use - B.
        
        // se non bastano gli spazi allora è impossibile piazzare le C. ci sarebbero uguali adiacenti.
        if (abs(c_to_use - b) > holes) continue;

        int plus_one = 0, zero = 0, minus_one = 0;
        if (c_to_use > b) plus_one = c_to_use - b;
        if (c_to_use < b) minus_one = b - c_to_use;

        zero = holes - plus_one - minus_one;
        while (zero >= 0) {
            // tutte le permutazioni di +1, 0, -1
            ll curr_sol = trinomial(plus_one, zero, minus_one);
            // fai x 2 per ogni 0 (BCBC, CBCB)
            curr_sol = (curr_sol * pw2[zero]) % MOD;

            curr_res = (curr_res + curr_sol) % MOD;

            zero -= 2;
            plus_one ++;
            minus_one ++;
        }

        // sbarre e palle : moltiplico curr_res per quanti modi posso distribuire le B nei buchi non zeri
        // considero B - holes così che peffozza ci sia un B per ogni buco
        curr_res = (curr_res * binomial((b - holes) + holes - 1, holes - 1)) % MOD;
        // molitplico curr_res per tutte le possibili scelte dei zero_b;
        curr_res = (curr_res * binomial(x, zero_b)) % MOD;

        res = (res + curr_res) % MOD;
    }
    // serve sbarre e palle con coefficenti binomiali negativi quando tutti zeri, quindi lo faccio a parte
    if (b == 0 && c == x) res = (res + 1) % MOD;

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
