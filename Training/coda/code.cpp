#include <bits/stdc++.h>

using namespace std;

vector<int> cucina(int n, int k, int x, vector<int> h) {
    vector<int>v(x,0);
    for (int i=0;i<n;i++) {
        v[h[i]]++;
    }
    vector<int> sol(x,0);
    int q = 0;
    int zeri = 0;
    for (int i=x-1;i>=0;i--) {
        q = min(k,v[i]);
        if (q == 0) {
            zeri ++;
            if (i<x-1) sol[i] = sol[i+1];
            else sol[i] = 0;
        }
        else {
            if (i<x-1) {
                sol[i] = sol[i+1] + 1 + min(zeri,q-1);
                zeri -= min(zeri,q-1);
            }
            else sol[i] = 1;
            
        }
        zeri = min(zeri, k-q);
    }
    return sol;
}
