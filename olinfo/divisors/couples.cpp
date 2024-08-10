#include <bits/stdc++.h>

using namespace std;

long long compute(long long n) {
    long long tot = 0;
    for (long long i=1;i<=sqrt(n);i++) {
        long long s = (long long)(n/i);
        tot += ( s - i + 1 );
        tot += ( s - i );
    }
    return tot;
}
