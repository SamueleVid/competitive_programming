#include <bits/stdc++.h>
using namespace std;

int Gira(int N, int* freccia) { 
    vector<int> v(N); // 0 verso dx e 1 verso sx
    for (int i = 0; i < N; i ++) v[i] = freccia[i];

    vector<vector<int>> dp(N + 2, {(int)1e6, (int)1e6}), prev(N + 2, {(int)1e6, (int)1e6});
    // dp[quante freccie puntano a destra][direzione dell'ultima freccia]

    // lo start possiamo considerarlo quando hai 0 frecce che puntano a dx e l'ultima punta a sx. il resto è infinito = impossibile
    dp[0][1] = 0;

    for (int i = 0; i < N; i ++) {
        swap(dp, prev);
        for (int j = 0; j < N + 2; j ++) dp[j] = {(int)1e6, (int)1e6};

        for (int j = 0; j < N + 2; j ++) {

            // aggiungo -> 
            if (j > 0 && prev[j - 1][0] != 1e6) dp[j][0] = min(dp[j][0], prev[j - 1][0] + (v[i] == 0 ? 0 : 1));
            // continuo una streak di frecce a destra
            if (j == 1 && prev[j - 1][1] != 1e6) dp[j][0] = min(dp[j][0], prev[j - 1][1] + (v[i] == 0 ? 0 : 1));
            // dopo aver raggiunto 0 frecce a destra (con streak di frecce a sx) ricomincio una streak puntando a destra
            
            // aggiungo <-
            if (j < N + 1 && prev[j + 1][0] != 1e6) dp[j][1] = min(dp[j][1], prev[j + 1][0] + (v[i] == 1 ? 0 : 1));
            // decido di interrompere la streak di frecce a destra
            if (j < N + 1 && prev[j + 1][1] != 1e6) dp[j][1] = min(dp[j][1], prev[j + 1][1] + (v[i] == 1 ? 0 : 1));
            // continuo la streak di frecce a sinistra
        }
    }

    // deve finire con 0 frecce che puntano verso destra e l'ultima freccia punta a sx
    return dp[0][1];
}
