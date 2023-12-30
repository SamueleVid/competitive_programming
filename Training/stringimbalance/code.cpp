#include <bits/stdc++.h>
#define ll long long
#define abc 26
using namespace std;

void solve() {
    int q; cin >> q;
    vector<int> letters(2*abc,0);
    
    while (q--) {
        int f; cin >> f;
        char c; cin >> c;
        int k; cin >> k;    
        if (c >= 'a') letters[c-'a'] += f;
        else letters[c-'A'+abc] += f;
        
        vector<int> copy = letters;
        sort(copy.begin(), copy.end());
        
        ll res = 0;
        ll sum = 0;
        for (int i=0;i<2*abc;i++) {
            if (copy[i]<=k) {
               copy[2*abc-1] += copy[i];
               k -= copy[i]; 
            }
            else {
                res += (copy[i] - k) * sum;
                sum += copy[i] - k;
                copy[2*abc-1] += k;
                k = 0;                    
            }            
        }
        
        cout << res << '\n';       
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
