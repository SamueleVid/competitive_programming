#include <bits/stdc++.h>
using namespace std;
#define ll long long

void add(vector<int> S, long long X);

bool compare(int i, int j);

void make_all_equal(int N, int Q_add, int Q_compare) {
    
    for (int i = 1; i <= log2(N); i ++) {
        if (N > 256) {
            // altrimenti la differenza diventa maggiore di 2^20, ma solo se 
            // N > 256 e ci sono abbastanza passaggi da far alzare la diff di tanto
            vector<int> alza_bassi;
            for (int i = 0; i < N / 2; i ++) alza_bassi.push_back(i);
            add(alza_bassi, 1 << 20);
        }

        // splitto in casi da due [(A), (B)], A != B, abbasso la differenza
        // (alzando il minore) con una BSA,
        // poi quando A = B (e C = D) considero [(A, B), (C, D)] con divide and conquer.
        vector<int> S;
        for (int j = 0; j < N; j += (1 << i)) {
            for (int k = j; k < j + (1 << (i - 1)); k ++) {
                S.push_back(k);
            }
        }
        for (ll pw = 1ll << 20; pw > 0; pw /= 2) {
            add(S, pw);
        }

        // necessario cuz capitano casi del tipo [(A), (A + 1)] da fixare
        vector<int> to_add;
        for (int j = 0; j < N; j += (1 << i)) {
            S.clear();
            for (int k = j; k < j + (1 << (i - 1)); k ++) {
                S.push_back(k);
            }

            if (!compare(j + (1 << (i - 1)) - 1, j + (1 << (i - 1)))) {
                for (auto x : S) to_add.push_back(x);
            }
        }
        add(to_add, 1);
    }

    return;
}
