#include <bits/stdc++.h>

using namespace std;

long long riciclo(int n, int m, vector<int> t, vector<int> p) {
    vector<long long> trackoni(31,0);
    for (int i=0;i<31;i++) {
        for (int j=0;j<n;j++) {
            trackoni[i] += (t[j]&(1<<i));
        }
    }  

    long long tot = 0;
    for (int i=0;i<31;i++) {
        for (int j=0;j<=i && j<m;j++) {
            long long da_togliere = min((long long)p[j],trackoni[i]/(1<<j));
            tot += da_togliere;
            p[j] -= da_togliere;
            trackoni[i] -= da_togliere*(1<<j);
        }
    }

    return tot;
}
