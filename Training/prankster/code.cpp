#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    vector<int>v(n+2);
    v[0]=0;
    for (int i=1;i<=n;i++) cin >> v[i];
    v[n+1]=0;
    vector<int>diff(n+1);
    for (int i=0;i<n+1;i++) diff[i]=v[i+1]-v[i];
    int pos=0;
    int neg=0;
    for (auto x : diff) {
        if (x>0) pos ++;
        if (x<0) neg ++;
    }
    cout << max(pos,neg) << '\n';
}
