#include <bits/stdc++.h>

using namespace std;

void brucia(int N, vector<int> &M, vector<int> &B, vector<long long> &T) {

    // inizializza T
    for (auto &x:T) x = -1;
    T[0] = 0;

    // inizializza s
    set<pair<int,int>>s;
    for (int i=1;i<N;i++) {
        s.emplace(M[i],i);
    }
    // se lo 0 va a destra lo metto a sx dei suoi uguali,
    // se lo 0 va a sx lo metto a destra dei suoi uguali
    // l'idea è semplicemente fare in modo che partendo da 0 andando a sx o a dx riesce
    // a raggiungere tutti gli altri con stesso M
    int index_zero = 0;
    if (M[0] > B[0]) index_zero = N;
    
    // se guarda a sx entrerà in questa pq.
    // l'idea è che per prendere un elemento sfruttanndo candele che guardano a sinistra
    // è ottimale utilizare la candela che è già più a sinistra.
    priority_queue<pair<int,int>> sx;
    // Stesso discorso a destra
    priority_queue<pair<int,int>> dx;
    
    // va a sx [    ]o
    if (M[0] > B[0]) sx.push({M[0],index_zero});
    // va a dx o[    ]
    else dx.push({M[0],index_zero});

    while (!sx.empty() || !dx.empty()) {
        while (!dx.empty()) {
            auto [value, elem] = dx.top(); dx.pop();
            // Se 0 gestisci la differenza tra il valore falso, per ordinarli, e il valore vero.
            int fake_elem = elem;
            if (fake_elem == N) elem = 0;

            auto it = s.lower_bound({M[elem],fake_elem});
            // non ha trovato niente ed è andato alla fine.
            // Gurdando a destra non troverà nessuno da aggiungere (non c'è niente a destra).
            if (it == s.end()) continue;

            while (it != s.end() && it->first <= B[elem]) {
                // inserisco M a sx o a dx in base all'orientamento
                if (M[it->second] > B[it->second]) {
                    // Metto - così che sia ordinato per minore, sx è ordinato per quelli più a sx
                    sx.push({-M[it->second], it->second});
                }
                // Lascio + così che sia ordinato per maggiore, dx è ordinato per quelli più a dx
                else dx.push({M[it->second], it->second});
                
                // Aggiorno T
                T[it->second] = T[elem]+M[it->second]-M[elem];
                
                // Segno la copia che poi verrà eliminata
                auto copy = it;

                // incremento ora, perché poi se è uguale a s.end() fermerà il programma.
                it ++;

                // elimino l'elemento. 
                // Devo eliminarlo dopo aver aggiornato it.
                s.erase(copy);
            }    
        }

        if (!sx.empty()) {

            auto [value, elem] = sx.top(); sx.pop();
            // Se 0 gestisci la differenza tra il valore falso, per ordinarli, e il valore vero.
            int fake_elem = elem;
            if (fake_elem == N) elem = 0;

            auto it = s.upper_bound({M[elem],fake_elem});
            // M[elem] è minore della più piccola altra M salvata in s.
            // Guardando a sinistra non troverà nulla (non c'è niente a sinistra).
            if (it == s.begin()) break;
            
            // Decremento così entro nel range degli elementi che tocca la candela.
            it --;

            // Segna se it precedentemente era s.begin(). In caso positivo ferma il loop
            bool prima_era_begin = false;

            while (!prima_era_begin && (it)->first >= B[elem]) {
                // se prima era begin, adesso it è ancora più a sinistra di begin,
                // fuori dal set. Quindi la ricerca finisce si esce dal loop.

                // inserisco M a sx o a dx in base all'orientamento
                if (M[it->second] > B[it->second]) {
                    // Metto - così che sia ordinato per minore, sx è ordinato per quelli più a sx
                    sx.push({-M[it->second], it->second});
                }
                // Lascio + così che sia ordinato per maggiore, dx è ordinato per quelli più a dx
                else dx.push({M[it->second], it->second});
                
                // Aggiorno T
                T[it->second] = T[elem]+M[elem]-M[it->second];
                
                // Segno la copia che poi verrà eliminata
                auto copy = it;
                
                // aggiorno prima_era_begin
                prima_era_begin = (it == s.begin());
                
                // decremento it
                it --;
                
                // elimino l'elemento. 
                // Devo eliminarlo dopo aver aggiornato it.
                s.erase(copy);
            }
        }
    }
}
