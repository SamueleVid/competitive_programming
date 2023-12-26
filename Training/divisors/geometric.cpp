#include <bits/stdc++.h>

using namespace std;

long long compute(long long n) {
    long long tot = 0;
    long long sq = (long long)sqrt(n);
    for (long long i=1;i*i<=n;i++) {
        tot += n/i;
    }
    tot *= 2;
    tot -= sq*sq;
    return tot;
}
