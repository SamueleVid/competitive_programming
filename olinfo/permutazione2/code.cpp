#include <bits/stdc++.h>
using namespace std;

bool chiedi(int K);
void stato();
void sposta();

int curr_prefix = -1;

void vai_avanti(int quanto, int N) {
    int limit = curr_prefix + quanto;
    while (curr_prefix < limit) {
        if (curr_prefix == -1) {
           curr_prefix ++;
           continue; 
        }
        curr_prefix ++;
        if (curr_prefix < N) sposta();
    }
}

void vai_indietro(int quanto, int N) {
    int limit = curr_prefix - quanto;
    while (curr_prefix > limit) {
        if (curr_prefix == 0) {
            curr_prefix --;
            continue;
        }
        if (curr_prefix < N) sposta();
        curr_prefix --;
    }
}

void controlla(vector<vector<int>> &possibili, vector<vector<int>> &new_possibili, int i, int N) {
    if (curr_prefix >= N) {
        new_possibili[2 * i] = possibili[i];
        return;
    }

    vector<int> sx, dx;
    for (auto x : possibili[i]) {
        if (chiedi(x)) sx.push_back(x);
        else dx.push_back(x);
    }

    new_possibili[2 * i] = sx;
    new_possibili[2 * i + 1] = dx;
}

void indovina_bsa(int N, int A, int B, int C, int H[]) { // binary search
    vector<vector<int>> possibili;
    vector<vector<int>> new_possibili;
    new_possibili.push_back({});
    for (int i = 0; i < N; i ++) new_possibili[0].push_back(i);
    int pw = 1 << (int)ceil(log2(N));

    bool vado_a_dx = true;
    for (int d = 1; d < pw; d *= 2) {
        swap(new_possibili, possibili);
        new_possibili.resize(2 * d);

        if (vado_a_dx) {
            for (int i = 0; i < d; i ++) {
                vai_avanti(pw / (d * 2), N);
                controlla(possibili, new_possibili, i, N);
                vai_avanti(pw / (d * 2), N);
            }
        }
        else {
            for (int i = d - 1; i >= 0; i --) {
                vai_indietro(pw / (d * 2), N);
                controlla(possibili, new_possibili, i, N);
                vai_indietro(pw / (d * 2), N);
            }
        }
        stato();
        vado_a_dx ^= 1;
    }

    for (int i = 0; i < N; i ++) H[i] = new_possibili[i][0];
}

constexpr int K = 45;

void indovina_sqrt(int N, int A, int B, int C, int H[]) { // sqrt tecnique
    vector<int> liberi;
    for (int i = 0; i < N; i ++) liberi.push_back(i);
    vector<set<int>> cosi;

    for (int i = 0; i < N - 1; i ++) {
        if ((i + 1) % K == 0) {
            vector<int> curr;
            set<int> da_aggiungere;
            for (auto x : liberi) {
                if (chiedi(x)) da_aggiungere.insert(x);
                else curr.push_back(x);
            }
            cosi.push_back(da_aggiungere);
            liberi = curr;
        }
        sposta(); // mi trovo in i + 1
    }
    set<int> da_aggiungere;
    for (auto x : liberi) da_aggiungere.insert(x);
    cosi.push_back(da_aggiungere);

    stato();
    sposta();
    for (int i = N - 2; i >= 0; i --) {
        if (cosi.back().size() == 1) {
            H[i + 1] = *cosi.back().begin();
            cosi.pop_back();
            if (i - 1 >= 0) sposta();
            continue;
        }

        int to_remove = -1;
        for (auto x : cosi.back()) {
            if (!chiedi(x)) {
                H[i + 1] = x;
                to_remove = x;
                break;
            }
        }
        cosi.back().erase(to_remove);
        
        if (i - 1 >= 0) sposta();
    }
    H[0] = *cosi.back().begin();
}

void indovina(int N, int A, int B, int C, int H[]) {
    if (B == 1) return indovina_sqrt(N, A, B, C, H);
    else return indovina_bsa(N, A, B, C, H);
}
