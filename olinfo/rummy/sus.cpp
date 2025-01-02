#include <bits/stdc++.h>
using namespace std;
#define ll long long 

ll prova(int N, ll start, vector<ll> P) {
    // fissando la prima mossa cerco di rendere tutti più piccoli possibili,
    // ma validi, così da avere a destra il valore più alto che posso.
    P[1] -= 2 * start;
    P[2] += start;
    for (int i = 1; i < N; i ++) {
        if (P[i] < 0) {
            // ne rubo da destra
            P[i + 1] -= -2 * P[i];
            P[i + 2] += -P[i];
        }
        if (P[i] > 0) {
            // ne passo un po' a destra
            P[i + 1] += P[i] / 2;
        }
    }
    return P[N];
}

ll prova_generalized(int N, vector<ll> P) {
    for (int i = 1; i < N; i ++) {
        // sempre P[i] < 0 in quanto S molto grande.
        P[i + 1] -= -2 * P[i];
        P[i + 2] += -P[i];        
    }
    return P[N];
}

void solve() {
    int N; cin >> N;
    vector<ll> P(N + 2);
    for (int i = 0; i < N + 2; i ++) cin >> P[i];

    // Empiricamente si vede che il coefficiente di S, con S grande, è sempre N + 1.
    // Dunque (a - (N + 1) * S) = prova(N, S, P) con S molto grande.
    // Calcolandolo in questo modo non fa overflow.
    ll a = prova_generalized(N, P);

    // Sapendo che all'aumentare di S il risultato diminuisce di (N + 1), 
    // torno indietro fino a quando il risultato dovrebbe essere non negativo.
    ll start = 1e9;
    ll step = (-(a - (N + 1) * start) + (N + 1) - 1) / (N + 1);

    // Se serve un numero negativo di mosse allora è impossibile.
    if (start - step < 0) {
        cout << "NO" << '\n';
        return;
    }

    // Questo invece lo calcolo legit, perché potrebbe non rispettare la regola.
    ll riprovo = prova(N, start - step, P);
    if (riprovo >= 0) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
