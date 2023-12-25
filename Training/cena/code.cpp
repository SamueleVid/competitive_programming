#include <bits/stdc++.h>

using namespace std;

long long conta(int n, int s[], int m, int p[]) {
    vector<vector<int>>pos_elems(100);
    for (int i=0;i<n;i++) pos_elems[s[i]].push_back(i);
    
    vector<int> pt(m,0);
    vector<pair<int,int>> saved;

    bool esci = false;
    for (;(pt[0]<pos_elems[p[0]].size()) && (!esci);pt[0]++) {
        
        for (int j=1;
            j<m
            && (
                // solo se va aggiornato
                pos_elems[p[j]][pt[j]] <= pos_elems[p[j-1]][pt[j-1]]
                // se non è il primo perché il primo è tutto rotto
                || pt[0] == 0
            )
            && !esci
            ;j++) {

            while (pos_elems[p[j]][pt[j]] <= pos_elems[p[j-1]][pt[j-1]]) {
                pt[j] ++;
                if (pt[j] >= pos_elems[p[j]].size()) {
                    esci = true;
                    break;
                }
            }
        }

        if (!esci) saved.push_back(
            {pos_elems[p[0]][pt[0]], pos_elems[p[m-1]][pt[m-1]]}
        );
    }

    long long res = 0;
    int esplorato = -1;
    for (auto [a,b] : saved) {
        res += (a-esplorato)*(n-b);
        esplorato = a;
    }
  
    return res;
}
