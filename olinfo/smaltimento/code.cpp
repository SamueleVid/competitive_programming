#include <bits/stdc++.h>

using namespace std;

long long smaltisci(int n, int m, vector<int> a, vector<vector<int>> b) {
    vector<vector<int>> adj_contrario(n);
    // punta da un coso alle procedure di cui fa parte
    for (int i=0;i<m;i++) {
        for (auto x : b[i]) {
            adj_contrario[x].push_back(i);
        }
    }
    
    vector<int > how_many(m,0);
    // dice quante sostanze rimangono da sbloccare per rendere una procedura possibile
    for (int i=0;i<m;i++) {
        how_many[i] = b[i].size();
    }

    // essenzialmente la distanza
    vector<long long> prize(n,1e15);
    // essenzialmente l'array visited
    vector<bool> used(n,0);
    priority_queue<pair<long long,int>> q;

    // aggiungo alla queue quelli già sbloccati perché non necessitano nessuna procedura
    for (int i=0;i<m;i++) {
        if (!how_many[i]) {
            prize[a[i]] = 1;
            q.push({-prize[a[i]],a[i]});
        }
    }
    while (!q.empty()) {
        auto [w, nodo] = q.top(); q.pop();

        if (used[nodo]) continue;
        used[nodo] = 1;

        for (auto proc : adj_contrario[nodo]) {
            if (used[a[proc]]) continue;
            // una volta sbloccata la procedura diventa dijkstra
            how_many[proc] --;
            if (!how_many[proc]) {
                // inizialmente conto il prezzo della sostanza ...
                long long prezzo = 1;
                // ... e poi aggiungo il prezzo delle sostanze per sbloccarla
                for (auto x : b[proc]) {
                    prezzo += prize[x];
                }
                // se è vantaggioso lo dijkstro nella queue
                if (prezzo < prize[a[proc]]) {
                    prize[a[proc]] = prezzo;
                    q.push({-prize[a[proc]],a[proc]});
                }
            } 
        }
    }

    return prize[0];
}
