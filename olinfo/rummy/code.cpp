#include <bits/stdc++.h>
using namespace std;
#define ll long long 

void solve() {
    int N; cin >> N;
    vector<ll> P(N + 2);
    for (int i = 0; i < N + 2; i ++) cin >> P[i];

    // Calcolo la doppia prefix sum su P. Una mossa produrrà questa queste differenze:
    // P:       +1 -2 +1
    // ps(P):   +1 -1  0
    // ps^2(P): +1  0  0
    // Si può arrivare a questa idea sapendo che con la prefix si "accorcia"
    // la lunghezza del subarray intaccato dalla mossa di uno finché non è
    // lungo un elemento. In questo modo, pensando nei termini della doppia
    // prefix, una mossa cambia solo un elemento, ovvero aumenta di uno quello
    // subito a sinistra. 
    vector<ll> ps(N + 2);
    ps[0] = P[0];
    for (int i = 1; i < N + 2; i ++) ps[i] = ps[i - 1] + P[i]; // ps(P)
    for (int i = 1; i < N + 2; i ++) ps[i] = ps[i - 1] + ps[i]; // ps^2(P)

    // Il problema chiede se è possibile rendere P non negativo, ovvero P[i] >= 0.
    // Per la prefix sum si ha che ps[i] >= ps[i - 1], mentre per la doppia 
    // prefix sum si dimostra facilmente che ps2[i] * i >= ps[i - 1] * (i + 1).
    // Dunque, in modo greedy, aumento i valori di ps2[i] da i = 1 fino a i = N - 1
    // in modo che rispettino la regola, per poi vedere se per il penultimo elemento,
    // che non può essere cambiato con la mossa (+1,0,0) sulla doppia prefix sum,
    // la regola regge.
    for (int i = 1; i < N; i ++) {
        ps[i] = max(ps[i], ps[i - 1] * (i + 1) / i);
    }
    if (ps[N] >= ps[N - 1] * (N + 1) / N) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    while (T --) solve();
}
