#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define m 666013

using namespace std;

vector<vector<ll>> matrixprod(vector<vector<ll>>&a, vector<vector<ll>>&b, int r, int c, int k) {
    vector<vector<ll>>res(r,vector<ll>(c,0));
    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            for (int z=0;z<k;z++) {
                res[i][j] += (a[i][z] * b[z][j])%m;
                res[i][j] %= m;
            }
        }
    }
    return res;
}

vector<vector<ll>> matrixexp(vector<vector<ll>>&a, int k, ll n) {
    if (n == 1) return a;
    vector<vector<ll>>h = matrixexp(a,k,n/2);
    h = matrixprod(h,h,k,k,k);
    if (n%2) h = matrixprod(h,a,k,k,k);
    return h;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, k; cin >> n >> k;

    vector<vector<ll>>matrix = {{0, 1},{n-1, n-2}};
    vector<vector<ll>>start = {{0},{1}};

    vector<vector<ll>> exped = matrixexp(matrix,2,k-1);

    vector<vector<ll>> end = matrixprod(exped, start, 2, 1, 2);

    cout << ((n-1)*end[0][0])%m << '\n';
}
