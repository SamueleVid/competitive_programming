#include <bits/stdc++.h>

using namespace std;

int pulisci(int n, int m, vector<string> S) {
    vector<vector<int>> v(n,vector<int>(m));
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            char c = S[i][j];
            if (c=='0') v[i][j] = 0;
            else v[i][j] = 1;
        }
    }

    set<int> righe;
    set<int> cols;
    for (int i=0;i<n;i++) righe.insert(i);
    for (int i=0;i<m;i++) cols.insert(i);

    bool fatto = true;
    while (!righe.empty() && !cols.empty() && fatto) {
        // verticalmente
        fatto = false;
        auto it = righe.begin();
        while (it != righe.end()) {
            auto it2 = cols.begin();
            bool same = true;
            int value = v[*it][*it2];
            while (it2 != cols.end()) {

                if (v[*it][*it2] != value) {
                    same = false;
                    break;
                }
                it2 ++;
            }
            if (same) {
                righe.erase(it);
                fatto = true;
                break;
            }
            it ++;
        }
        if (fatto) continue;
    
        // oriz
        fatto = false;
        it = cols.begin();
        while (it != cols.end()) {
            auto it2 = righe.begin();
            bool same = true;
            int value = v[*it2][*it];
            while (it2 != righe.end()) {
                if (v[*it2][*it] != value) {
                    same = false;
                    break;
                }
                it2 ++;
            }
            if (same) {
                cols.erase(it);
                fatto = true;
                break;
            }
            it ++;
        }
    }

    return righe.size() * cols.size();
}
