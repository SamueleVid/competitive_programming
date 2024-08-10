#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    vector<int>v(n);
    for (auto &x:v) cin >> x;
    vector<int> piu(n);
    for (int i=0;i<n;i++) piu[i] = v[i]+i;
    vector<int> meno(n);
    for (int i=0;i<n;i++) meno[i] = v[i]-i;
    
    int maxpiu=piu[0], minpiu=piu[0], maxmeno=meno[0], minmeno=meno[0];
    
    for (int i=1;i<n;i++) maxpiu = max(maxpiu, piu[i]);
    for (int i=1;i<n;i++) minpiu = min(minpiu, piu[i]);
    for (int i=1;i<n;i++) maxmeno = max(maxmeno, meno[i]);
    for (int i=1;i<n;i++) minmeno = min(minmeno, meno[i]);

    int sol1 = maxpiu - minpiu;
    int sol2 = maxmeno - minmeno;

    cout << max(sol1, sol2) << '\n';
}
