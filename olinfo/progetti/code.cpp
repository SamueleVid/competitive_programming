#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
#pragma GCC optimize("Ofast")
using namespace std;

vector<vector<ll>> matrixprod(vector<vector<ll>>&a, vector<vector<ll>>&b, int r, int c, int k) {
    vector<vector<ll>>res(r,vector<ll>(c,0));
    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            for (int z=0;z<k;z++) {
                res[i][j] += (a[i][z] * b[z][j])%mod;
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

vector<vector<ll>> matrixexp(vector<vector<ll>>&a, int k, int n) {
    if (n == 0) exit(-1);
    if (n == 1) return a;
    vector<vector<ll>>h = matrixexp(a,k,n/2);
    h = matrixprod(h,h,k,k,k);
    if (n%2) h = matrixprod(h,a,k,k,k);
    return h;
}

int progetti(int n, int k) {
    vector<vector<ll>> start(k,vector<ll>(1,0));
    start[k-1][0]=1;
    
    vector<vector<ll>> m(k,vector<ll>(k,0));
    for (int i=0;i<k-1;i++) {
        m[i][i+1]=1;
    }
    for (int i=0;i<k;i++) m[k-1][i]=1;

    vector<vector<ll>> exp = matrixexp(m,k,n-1);
    vector<vector<ll>> end = matrixprod(exp, start, k, 1, k);

    ll res = 0;
    for (int i=0;i<k;i++) {
        res += end[i][0];
        res %= mod;
    }

    return res;
}
