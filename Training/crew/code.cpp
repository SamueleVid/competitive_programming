#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    for (int k=0;k<n+1;k++) {
        cout << k << " ";
    }
    cout << '\n';

    for (int k=1;k<=n;k++) {
        cout << 0 << " ";
        for (int j=1;j<=n;j++) {
            cout << k*n+j << " ";
        }
        cout << '\n';
    }
    
    for (int k=1;k<=n;k++) {
        for (int j=0;j<n;j++) {
            cout << k << " ";
            for (int l=1;l<=n;l++) {
                cout << ((k-1)*l+j)%n + (l*n) + 1 << " ";
            }
            cout << '\n';
        }
    }
}
