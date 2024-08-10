#include <bits/stdc++.h>

using namespace std;

int pianifica(int n, int l, vector<vector<int>> f) {
    vector<vector<pair<int,int>>> node_to_f(n); //n -> lista e indice

    for (int i=0;i<l;i++) {
        for (int j=0;j<f[i].size();j++) {
            node_to_f[f[i][j]].push_back({i,j});
        }
    }

    // non si puo con adj list, perché non dipende dal nodo ma dalla pos nella roba
    // quanto cambi fermata, puoi decidere per quale posizione nella lista del 3 essere piazzato.
    // una volta presa una fermata, puoi decidere se cambiare linea o proseguire

    vector<vector<bool>> v(l);
    for (int i=0;i<l;i++) {
        v[i].assign(f[i].size(),0);
    }
    
    priority_queue<tuple<int,int,int>> q;
    
    vector<vector<int>> d(l);
    for (int i=0;i<l;i++) {
        d[i].assign(f[i].size(),1e9);
    }

    for (int i=0;i<l;i++) {
        for (int j=0;j<f[i].size();j++) {
            if (f[i][j] == 0) {
                d[i][j] = 0;
                q.push({d[i][j],i,j});
            }
        }
    }

    while (!q.empty()) {
        auto [peso, line, index] = q.top(); q.pop();

        if (v[line][index]) continue;
        v[line][index] = 1;

        if (f[line][index] == n-1) {
            return -peso;
        }

        if (index+1 < f[line].size()) {
            if (!v[line][index+1]) {
            if (d[line][index+1] > d[line][index]) {
                    d[line][index+1] = d[line][index];
                    q.push({peso,line,index+1});
                }
            }
        }

        for (auto [u_line, u_index] : node_to_f[f[line][index]]) {

            if (v[u_line][u_index]) continue;
            if (d[u_line][u_index] > d[line][index] + 1) {
                d[u_line][u_index] = d[line][index] + 1;
                q.push({-d[u_line][u_index],u_line,u_index});
            }
            node_to_f[f[line][index]].clear();
        }
    }
    return -1;
}
