#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;

    if ((n*m)%4!=0) {
        cout << -1 << '\n';
        return 0;
    }
    
    int res[n][m];
    int counter = 0;

    if (n%2==0 && m%2==0) {

        for (int i=0;i<n;i+=2) {
            for (int j=0;j<m;j+=2) {
                res[i][j] = counter;
                res[i+1][j] = counter;
                res[i][j+1] = counter;
                res[i+1][j+1] = counter;
                counter ++;
            }
        }
    }

    else if (n%4 == 0) {

        for (int i=0;i<n;i+=4) {
            for (int j=0;j<m;j++) {
                res[i][j] = counter;
                res[i+1][j] = counter;
                res[i+2][j] = counter;
                res[i+3][j] = counter;
                counter ++;
            }
        }
    }

    else if (m%4 == 0) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j+=4) {
                res[i][j] = counter;
                res[i][j+1] = counter;
                res[i][j+2] = counter;
                res[i][j+3] = counter;
                counter ++;
            }
        }
    }
    
    cout << counter << '\n';
    for (int i=0;i<n;i++) {
        for (int j=0;j<m;j++) {
            cout << res[i][j] << " ";
        }
        cout << '\n';
    }
}
