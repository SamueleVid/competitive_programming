#include <bits/stdc++.h>

using namespace std;

long long bfs(int n, long long k, vector<int> p, vector<int> f) {
    vector<pair<long long,long long>>quote_max(n);
    for (long long i=0;i<n;i++) {
        quote_max[i] = {-p[i],i};
    }
    sort(quote_max.begin(),quote_max.end());

    priority_queue<pair<long long,long long>> spendaccioni;
    long long best_guadagno = 0;
    long long soldi_spesi = 0;
    for (long long i=0;i<n;i++) {
        auto [quota,pos]=quote_max[i];
        quota *= -1;
        spendaccioni.push({f[pos],pos});
        soldi_spesi += f[pos];
        long long curr_input = quota * spendaccioni.size();
        long long curr_guad = curr_input - soldi_spesi;
        while (spendaccioni.size()) {
            auto [soldi, pos] = spendaccioni.top();
            long long soldi_spesi1 = soldi_spesi - soldi;
            long long curr_input1 = curr_input - quota;
            long long curr_guad1 = curr_input1 - soldi_spesi1;
            if (curr_guad1 > curr_guad || soldi_spesi > k) {
                spendaccioni.pop();
                soldi_spesi = soldi_spesi1;
                curr_input = curr_input1;
                curr_guad = curr_guad1;
                continue;
            }
            break;
        }
        best_guadagno = max(best_guadagno, curr_guad);
    }
    return best_guadagno;
}
