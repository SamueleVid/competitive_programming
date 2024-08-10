#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    vector<int> precalc;
    long long curr = 0;
    int i=0;
    while (true) {    
        curr = 2*curr + 1 + i+2;
	    if (curr > 1000000000) break;
        precalc.push_back(curr);
        i++;
    }

    int pos; cin >> pos;
    pos --;

    for (int i=precalc.size();i>=0;i--) {
        // immaginiamo precalc[i]
        // è formato da precalc[i-1], P, i + 2 S, precalc[i-1]
        int val;
        if (i > 0) val = precalc[i-1];
        else val = 0;
        
        if (pos < val) {
            continue;
        }
        pos -= val;
        if (pos == 0) {
            cout << "P" << endl;
            break;
        }
        if (pos < i + 3) {
            cout << "S" << endl;
            break;
        }
        pos -= i+3;
    }
}
