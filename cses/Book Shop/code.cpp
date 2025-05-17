#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_X = 1e5 + 5;

int main() {
    int N, X; cin >> N >> X;
    vector<int> h(N), s(N);
    for (int i = 0; i < N; i ++) cin >> h[i];
    for (int i = 0; i < N; i ++) cin >> s[i];

    // MODO 1: mi tengo KNAPSACK[quanti elementi ho visto][prezzo] = massimo numero di pagine per quel prezzo

    vector<vector<int>> knapsack_1(N + 1, vector<int>(X + 1));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j <= X; j ++) {
            if (j - h[i] < 0) knapsack_1[i + 1][j] = knapsack_1[i][j];
            else knapsack_1[i + 1][j] = max(knapsack_1[i][j], knapsack_1[i][j - h[i]] + s[i]);
        }
    }

    int res_1 = 0;
    for (int i = 0; i <= X; i ++) res_1 = max(res_1, knapsack_1[N][i]);

    // MODO 2: mi tengo knapsack_old[prezzo] e knapsack_new[prezzo] visto che ogni volta mi serve solo quello prima

    vector<int> knapsack_2(X + 1);
    vector<int> knapsack_2_old(X + 1);
    for (int i = 0; i < N; i ++) {
        fill(knapsack_2.begin(), knapsack_2.end(), 0);
        for (int j = 0; j <= X; j ++) {
            if (j - h[i] < 0) knapsack_2[j] = knapsack_2_old[j];
            else knapsack_2[j] = max(knapsack_2_old[j], knapsack_2_old[j - h[i]] + s[i]);
        }
        swap(knapsack_2, knapsack_2_old);
    }

    int res_2 = 0;
    for (int i = 0; i <= X; i ++) res_2 = max(res_2, knapsack_2_old[i]);

    // MODO 3 (quello swag): evito di usare più di un array iterando da destra verso sinistra (così quelli che piazzo verranno letti solo nell'iterazione successiva)

    vector<int> knapsack(X + 1);
    for (int i = 0; i < N; i ++) {
        for (int j = X; j >= h[i]; j --) {
            knapsack[j] = max(knapsack[j], knapsack[j - h[i]] + s[i]);
        }
    }

    // MODO 4 (problema diverso): dati dei pesi, devo vedere quali somme riesco a raggiungere. In questo caso devo usare un caso base,
    // ovvero knapsack[0] = 1, perché è raggiungibile. 

    // normalmente sarebbe così
    vector<int> knapsack_4(X + 1);
    knapsack_4[0] = 1;
    for (int i = 0; i < N; i ++) {
        // attenzione che se parto da sinistra, invece che da destra, aggiungo un numero infinito di h[i], anziché solo uno.
        // (0 -> h[i] -> 2 * h[i] -> 3 * h[i] -> ...)
        for (int j = X; j >= h[i]; j --) {
            if (knapsack_4[j - h[i]]) knapsack_4[j] = 1;
        }
    }

    // posso velocizzarlo con un bitset, togliendo un fattore 32
    bitset<MAX_X> knapsack_bitset_4;
    knapsack_bitset_4[0] = 1;
    for (int i = 0; i < N; i ++) {
        // shifto a destra di h[i] e lo OR-ro a quello originale  
        knapsack_bitset_4 |= (knapsack_bitset_4 >> h[i]);
    }

    // do il risultato del problema
    
    int res = 0;
    for (int i = 0; i <= X; i ++) res = max(res, knapsack[i]);
    // cout << res_1 << '\n';
    // cout << res_2 << '\n';
    cout << res << '\n';
}
