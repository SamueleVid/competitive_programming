#include <bits/stdc++.h>
using namespace std;
#define ll long long

int alzati(int N, int M, int X[], int Y[]) {
    vector<bool> v(M);
    vector<ll> d(M,1e18);

    for (int i = 0; i < M; i ++) {
        // distanza dall'alto
        d[i] = min(Y[i], N - X[i] - 1);
    }
    
    // minimizza il massimo arco dal top-right
    for (int k = 0; k < M; k ++) {
        int minim = -1;
        for (int i = 0; i < M; i ++) if ((minim == -1 || d[i] < d[minim]) && !v[i]) minim = i;
        v[minim] = 1;
        
        for (int i = 0; i < M; i ++) {
            ll manhattan = (ll)abs(Y[minim] - Y[i]) + (ll)abs(X[minim] - X[i]);
            ll time = (manhattan - 1) / 2;
            if (X[i] == X[minim] || Y[i] == Y[minim]) time --;
            if (!v[i]) d[i] = min(d[i], max(d[minim], time));
        }
    }

    ll res = 1e18;
    for (int i = 0; i < M; i ++) {
        // distanza dal basso
        res = min(res, max(d[i], (ll)min(X[i], N - Y[i] - 1)));
    }

    return res - 1;
}
