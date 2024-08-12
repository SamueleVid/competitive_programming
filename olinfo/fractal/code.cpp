#include <bits/stdc++.h>
using namespace std;
#define m 32749

vector<vector<int>> matrixprod(vector<vector<int>>&a, vector<vector<int>>&b, int r, int c, int k) {
    vector<vector<int>>res(r, vector<int>(c));
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            for (int z=0; z<k; z++) {
                res[i][j] += (a[i][z]*b[z][j])%m;
                res[i][j] %= m;
            }
        }
    }
    return res;
}

vector<vector<int>> matrixexp(vector<vector<int>>&a, int k, int n) {
    if (n == 1) return a;
    vector<vector<int>> h = matrixexp(a,k,n/2);
    h = matrixprod(h,h,k,k,k);
    if (n%2) h = matrixprod(h,a,k,k,k);
    return h;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    
    // V E
    vector<vector<int>>res(2,vector<int>(1));
    res[0][0] = 1;
    res[1][0] = 0;
    
    vector<vector<int>>matrix(2,vector<int>(2));
    matrix[0][0] = 3;
    matrix[1][0] = 3;
    matrix[0][1] = 2;
    matrix[1][1] = 3;
    
    if (n == 0) {
        cout << 1 << " " << 0 << '\n';
        return 0;
    }
    
    matrix = matrixexp(matrix,2,n);
    res = matrixprod(matrix,res,2,1,2);
    
    cout << res[0][0] << " " << res[1][0] << '\n';
}
