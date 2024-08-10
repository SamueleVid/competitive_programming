#include <bits/stdc++.h>

using namespace std;

int main() {
    string a, b, c; cin >> a >> b >> c;
    int n1 = a.size();
    int n2 = b.size();
    int n3 = c.size();

    int pta, ptb, ptc;
    pta = ptb = ptc = 0;

    int leta, letb, letc;

    string sol = "";

    while (pta < n1 || ptb < n2 || ptc < n3) {
        leta = letb = letc = 1;
        char charac = a[pta];
        bool f = false;
        if (b[ptb] != charac) f = 1;
        if (c[ptc] != charac) f = 1;

        while (pta+1 < n1 && a[pta] == a[pta+1]) {
            pta ++;
            leta ++;
        }
        pta ++;
        while (ptb+1 < n2 && b[ptb] == b[ptb+1]) {
            ptb ++;
            letb ++;
        }
        ptb ++;
        while (ptc+1 < n3 && c[ptc] == c[ptc+1]) {
            ptc ++;
            letc ++;
        }
        ptc ++;

        vector<int>v{leta,letb,letc};
        sort(v.begin(), v.end());
        int coso = v[1];

        for (int i=0;i<coso;i++) sol += charac;

    }

    cout << sol << '\n';
}
