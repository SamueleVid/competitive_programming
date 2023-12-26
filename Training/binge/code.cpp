#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> m >> n;

    vector<int> e(n);
    vector<int> l(n);
    for (int i=0;i<n;i++) {
        cin >> e[i] >> l[i];
    }

    long long days = 1;
    int curr_hour = 0;

    for (int i=0;i<n;i++) {
        
        int ep_possibili_oggi = (m-curr_hour)/l[i];
        int visti_oggi = min(e[i], ep_possibili_oggi);
        curr_hour += visti_oggi*l[i];
        e[i] -= visti_oggi;
        
        if (!e[i]) continue;
        int quanti_al_giorno = m/l[i];
        int giorni_completi = e[i]/quanti_al_giorno;
        days += giorni_completi;
        
        e[i] -= giorni_completi*quanti_al_giorno;
        if (!e[i]) {
            curr_hour = quanti_al_giorno*l[i];
            continue;
        }

        curr_hour = e[i]*l[i];

        days ++;        
    }
    
    cout << days << " " << m-curr_hour << endl;
}
