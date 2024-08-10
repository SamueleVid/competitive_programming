#include <bits/stdc++.h>

using namespace std;

long long somma(int l, int r);
long long subarray_massimo(int l, int r);
long long subarray_minimo(int l, int r);

pair<long long, long long> prefixsuffix(int l, int r, int n, long long submax, long long submin, long long sum) {
    int sq = sqrt(n);

    long long prefix = 0;
    long long suffix = 0;
    int k;
    if (submax > -submin) {
       k = -1;
        for (int pw = 1<<(int)ceil(log2(sq)); pw >= 1; pw /= 2) {
            if (l <= r - k - pw) {
                long long curr_submax = subarray_massimo(l, r - k - pw);
                if (curr_submax == submax) {
                    k += pw;
                }
            }
        }
        prefix = somma(l, r-k);
        suffix = sum - prefix + submax;
    }
    else {
        k = -1;
        for (int pw = 1<<(int)ceil(log2(sq)); pw >= 1; pw /= 2) {
            if (l <= r - k - pw) {
                long long curr_submin = subarray_minimo(l, r - k - pw);
                if (curr_submin == submin) {
                    k += pw;
                }
            }
        }
        prefix = somma(l, r-k) - submin;
        suffix = sum - prefix - submin;
    }

    return {prefix, suffix};
}

long long trova(int n) {
    long long curr_max = 0;
    long long curr=0;
    int sq = 338;

    for (int i=0;i<n;i+=sq) {
        // controllo coso in mezzo giusto per

        long long submax = subarray_massimo(i,min(i+sq-1, n-1));
        long long submin = subarray_minimo(i,min(i+sq-1, n-1));
        long long sum = somma(i,min(i+sq-1, n-1));
        auto [prefix, suffix] = prefixsuffix(i,min(i+sq-1,n-1),n,submax,submin,sum);

        curr_max = max(curr_max, submax);
        // max prefix 
        if (curr > 0) {
            curr_max = max(curr_max, curr + prefix);
        }
        
        curr += sum;
        // se minore di 0 taglia
        if (curr < 0) {
            curr = 0;
        }
        curr_max = max(curr_max, curr);

        if (curr < suffix) curr = suffix;
        curr_max = max(curr_max, curr);
    }

    return curr_max;
}
