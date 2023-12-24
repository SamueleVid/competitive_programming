#include <bits/stdc++.h>

using namespace std;

int arrampicate(int n, string s) {
    // dirs: -1 sx, 0 boh, 1 dx
    // index: 0 sx, 1 dx 
    int comps[2];
    comps[0] = comps[1] = 1;
    int dir[2];
    dir[0] = dir[1] = 0;
    int comps_new[2];
    comps_new[0] = comps_new[1] = 1;
    int dir_new[2];
    dir_new[0] = dir_new[1] = 0;

    for (int i=0;i<n;i++) {
        for (int j=0;j<2;j++) {
            if (s[i] == '#' || (s[i] == '>' && dir[j] == -1) || (s[i] == '<' && dir[j] == 1)) {
                comps_new[j] ++;
                dir_new[j] = 0;
                continue;
            }
            if (dir[j] == 0 && (s[i] == '<' || s[i] == '>')) {
                if (s[i] == '>') dir_new[j] = 1;
                else dir_new[j] = -1;
                continue;
            }
            if (s[i] == '?') {
                // vedi che risultato avrebbe se mettessi < o > a i 2 risultati precedenti
                int compssx, compsdx;
                compssx = comps[0]; compsdx = comps[1];
                int dir0, dir1;
                dir0 = dir[0]; dir1 = dir[1];
                if ((j == 0 && dir0 == 1) || (j == 1 && dir0 == -1)) {
                    compssx ++;
                    dir0 = 0;
                }
                else {
                    if (j == 0) dir0 = -1;
                    else dir0 = 1;
                }

                if ((j == 0 && dir1 == 1) || (j == 1 && dir1 == -1)) {
                    compsdx ++;
                    dir1 = 0;
                }
                else {
                    if (j == 0) dir1 = -1;
                    else dir1 = 1;
                }

                if (compssx > compsdx) {
                    comps_new[j] = compssx;
                    dir_new[j] = dir0;
                    continue;
                }
                if (compsdx > compssx) {
                    comps_new[j] = compsdx;
                    dir_new[j] = dir1;
                    continue;
                }
                // se non è 0 ha più probabilità di cambiare e aggiungere comps
                if (dir0 != 0) {
                    comps_new[j] = compssx;
                    dir_new[j] = dir0; 
                    continue;
                }
                comps_new[j] = compsdx;
                dir_new[j] = dir1; 

            }
        }
        if (dir_new[0] == dir_new[1]) {
            comps_new[0] = max(comps_new[0], comps_new[1]);
            comps_new[1] = max(comps_new[0], comps_new[1]);
        }
        dir[0] = dir_new[0];
        dir[1] = dir_new[1];
        comps[0] = comps_new[0];
        comps[1] = comps_new[1];
        
    }
    return max(comps[0],comps[1]);
}

int main() {
    int n; cin >> n;
    string s; cin >> s;
    cout << arrampicate(n, s) << '\n';
}  
