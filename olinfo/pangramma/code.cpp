#include <bits/stdc++.h>

using namespace std;

const int mod = 46337;

int pow(int n, int k) {
    if (k == 0) return 1;
    if (k == 1) return n%mod;
    int res = pow(n,k/2)*pow(n,k/2);
    res %= mod;
    if (k%2) res *= n;
    res %= mod;
    return res;  
}

int conta(int n, int k, vector<int>&v) {

    vector<int>inv(mod);
    for (int i=1;i<mod;i++) inv[i] = pow(i,mod-2);

    vector<int> alfabeto_curr(k,0);
    int res = 0;
    int min_lunghezza = 1e9;
    int quante_lettere_mancano = k;
    int multiplier = 1;

    int lb = 0;
    for (int rb=0;rb<n;rb++) {

        if (alfabeto_curr[v[rb]]) {
            
            multiplier *= inv[alfabeto_curr[v[rb]]%mod];
            multiplier %= mod;
            multiplier *= (alfabeto_curr[v[rb]]+1)%mod;
            multiplier %= mod;    
        }
        else {
            quante_lettere_mancano --;
        }
        alfabeto_curr[v[rb]] ++;

        while (alfabeto_curr[v[lb]] > 1 && lb<=rb) {

            alfabeto_curr[v[lb]] --;
            if (alfabeto_curr[v[lb]]) {

                multiplier *= inv[(alfabeto_curr[v[lb]]+1)%mod];
                multiplier %= mod;
                multiplier *= alfabeto_curr[v[lb]]%mod;
                multiplier %= mod;    
            }
            else {
                quante_lettere_mancano ++;
            }
            lb ++;
        }

        if (quante_lettere_mancano) continue;
        if (rb-lb+1 > min_lunghezza) continue;
        if (rb-lb+1 < min_lunghezza) {

            min_lunghezza = rb-lb+1;
            res = 0;
        }
        
        res += multiplier%mod;
        res %= mod;
    }

    return res;
}
