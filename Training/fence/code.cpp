#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<int> v(n);
    for (auto &x:v) cin >> x;
    
    int pos_max = 0;
    for (int i=0;i<n;i++) {
        if (v[i] >= v[pos_max]) pos_max = i;
    }
    
    unsigned long long res = 0;
    int curr = v[0];
    for (int i=1;i<=pos_max;i++) {
        res += curr;
        if (v[i] > curr) curr = v[i];
    }
    curr = v[n-1];
    for (int i=n-2;i>=pos_max;i--) {
        res += curr;
        if (v[i] > curr) curr = v[i];
    }
    
    cout << res << '\n';
}
