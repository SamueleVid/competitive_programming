#include <bits/stdc++.h>
using namespace std;

int n, t, i;

int main() {

    assert(1 == scanf("%d", &t));
    for(i=0; i<t; i++) {
        assert(1 == scanf("%d", &n));

        int a;
        if (n%4 == 0) a = n;
        if (n%4 == 1) a = 1;
        if (n%4 == 2) a = n + 1;
        if (n%4 == 3) a = 0;

        int b = 0;

        for (int pw=1;pw<=n;pw*=2) {
            b ^= pw;
            a ^= pw;
        }
        cout << a + b << '\n';

    }
    return 0;
}
