#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    for (int i=0;i<n/2;i++) {
        cout << "1 0 1\n";
    }
    cout << n-(n/2) << " 0 1\n";
    for (int i=0;i<n-(n/2);i++) {
        cout << "1 1 0\n";
    }
    cout << n-n/2 << " 0 1\n";
}
