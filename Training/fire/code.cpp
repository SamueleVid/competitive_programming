#include <bits/stdc++.h>
using namespace std;

int fiamme(int nodo, vector<vector<int>> &adj, int da_ignorare, vector<int>&res, vector<int>&mass, vector<int>&sec_mass) {
    int count = 0;
    for (auto x : adj[nodo]) {
        if (x != da_ignorare) {
            count ++;
        }
    }
    if (count < 1) {
        res[nodo] = 1;
        return 1;
    }
    int tot = 0;
    int massimo = 0;
    int second_massimo = 0;
    vector<pair<int,int>> results;
    for (auto x : adj[nodo]) {
        if (x != da_ignorare) {
            int curr;
            curr = fiamme(x, adj, nodo,res,mass,sec_mass);
            results.push_back({curr,x});
            tot += curr;
        }
    }
    
    sort(results.begin(), results.end(), greater<pair<int,int>>());

    massimo = results[0].first;
    mass[nodo] = results[0].second;
    if (count > 1) sec_mass[nodo] = results[1].second;
    
    res[nodo] = tot - massimo + 1;

    return tot - massimo + 1;

}

void get_values(int nodo, vector<vector<int>> &adj, int da_ignorare, vector<int>&res, vector<int> &old_res, vector<int>&mass, vector<int>&sec_mass) {
    // trova il valore di prev
    
    int prev = 0;
    if (da_ignorare != -1) {
        
        // faccio finta che la ricerca fosse partita dal nodo precedente
        prev = res[da_ignorare];

        // se il massimo del precedente era nodo, quando da nodo vai a precedente, nodo non viene contato in quanto
        // il "da ignorare", quindi quello ignorato perché il maggiore è il secondo maggiore del precedente 
        if (mass[da_ignorare] == nodo) {
            if (sec_mass[da_ignorare] != -1) {
                // noto che prendo l'old_res, ovvero quando il secondo massimo parte dal nodo precedente 
                // (potrebbe essere anche il precedente del precedente nell'attraversamento originale)
                prev -= old_res[sec_mass[da_ignorare]];
            }
        }
        // se invece il massimo del precedente non era il nodo, semplicemente attraversiamo da nodo al precedente,
        // quindi non contando nodo, e si va verso il suo massimo. Va quindi tolto il risultato di nodo
        else {
            prev -= old_res[nodo];
        }

        // mi salvo il risultato in old_res, che salva il risultato del precedente se fosse partito da nodo
        old_res[da_ignorare] = prev;
    }

    
    int massimo = 0;
    if (mass[nodo] != -1) massimo = old_res[mass[nodo]]; // ricrea massimo

    res[nodo] += massimo; // ricrea tot pt1
    res[nodo] += prev; // ricrea tot pt2
    
    // ora res[nodo] rappresenta il risultato se avessimo chiamato la prima funzione nella posizione iniziale nodo

    res[nodo] -= max(prev, massimo); // togli il massimo tra quello che c'era già e prev

    vector<pair<int,int>> results;
    if (prev != -1) results.push_back({prev,da_ignorare});
    if (mass[nodo] != -1) results.push_back({old_res[mass[nodo]],mass[nodo]});
    if (sec_mass[nodo] != -1) results.push_back({old_res[sec_mass[nodo]],sec_mass[nodo]});
    
    sort(results.begin(), results.end(), greater<pair<int,int>>());

    // risalvo i nuovi massimo e secondo massimo tenendo conto del ramo che parte dal precedente
    if (results.size() > 0) mass[nodo] = results[0].second;
    if (results.size() > 1) sec_mass[nodo] = results[1].second;

    for (auto x : adj[nodo]) {
        if (x != da_ignorare) {
            // mi salvo il valore di quando x parte da adesso
            int temp = old_res[x];
            get_values(x, adj, nodo,res,old_res,mass,sec_mass);
            // la funzione avrà cambiato il valore di old_res[x] come quando parte dai suoi nodi successivi,
            // ma quando considero i prossimi nodi partenti da nodo, l'unico modo per arrivare da un nodo
            // j e x entrambi adiacenti a nodo è proprio partendo da nodo, quindi mi risalvo old_res[x]
            // come se partisse da nodo
            old_res[x] = temp;       
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);    
    int N; cin >> N;
    vector<vector<int>> adj(N, vector<int>());

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> res(N,-1);
    vector<int> mass(N,-1);
    vector<int> sec_mass(N,-1);
    vector<int> old_res(N,-1);

    fiamme(0, adj, -1, res, mass, sec_mass);

    old_res = res;
    
    get_values(0, adj, -1, res, old_res, mass, sec_mass);

    for (int i=0;i<N;i++) cout << res[i] << " ";
    cout << endl;
}
