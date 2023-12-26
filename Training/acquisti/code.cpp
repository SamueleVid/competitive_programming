#include <bits/stdc++.h>

using namespace std;

vector<long long>calcola(int t, int m, vector<long long> s, vector<long long>p) {
    vector<long long> ps_quanti(t);
    ps_quanti[0] = s[0];
    for (int i=1;i<t;i++) ps_quanti[i] = ps_quanti[i-1]+s[i];
    vector<long long> ps_peso(t);
    ps_peso[0] = 0;
    for (int i=1;i<t;i++) ps_peso[i] = ps_peso[i-1]+s[i]*i;

    vector<long long>res(m,0);

    for (int i=0;i<m;i++) {
        long long value = p[i];
        int k=-1;
        // trova quella subito minore
        for (int j = 1<<(int)(log2(t));j>=1;j/=2) {
            if (j+k < t && ps_peso[j+k]<value) k += j;
        }
        // l'indice di quella che devo upgradare
        k ++;
        if (k == t) {
            res[i] = ps_quanti[k-1];
            continue;
        }
        long long quanto_manca;
        long long quanti_ce_ne_stanno;
        if (k == 0) {
            quanto_manca = value;
            quanti_ce_ne_stanno = s[k];
        }
        else {
            res[i] += ps_quanti[k-1];
            quanto_manca = value - ps_peso[k-1];
            quanti_ce_ne_stanno = min(s[k],quanto_manca/k);
        } 
        res[i] += quanti_ce_ne_stanno;
    }
    return res;
}
