#include <bits/stdc++.h>

using namespace std;

int arrampicate(int n, string s) {
    // dir sx, boh, dx
    vector<int> prev_comps(3,0);
    prev_comps[1] = 1;
    vector<int> comps(3,0);
    comps[1] = 1;
    for (int i=0;i<n;i++) {
        if (s[i] == '<' || s[i] == '?') {
            comps[0] = max(comps[0], max(prev_comps[0],prev_comps[1]));
            comps[1] = max(comps[1], max(prev_comps[1],prev_comps[2]+1));
        }
        if (s[i] == '=') {
            comps[1] = prev_comps[1];
        }
        if (s[i] == '>' || s[i] == '?') {
            comps[2] = max(comps[2], max(prev_comps[2],prev_comps[1]));
            comps[1] = max(comps[1], max(prev_comps[1],prev_comps[0]+1));
        }   
        if (s[i] == '#') {
            int c = max(prev_comps[0],prev_comps[1]);
            c = max(c, prev_comps[2]);
            comps[1] = c + 1;
        }
        prev_comps = comps;
    }
    int c = max(prev_comps[0],prev_comps[1]);
    c = max(c, prev_comps[2]);
    return c;    

}

int main() {
    int n; cin >> n;
    string s; cin >> s;
    cout << arrampicate(n, s) << '\n';
}
