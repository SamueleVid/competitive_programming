// credit a lorenzo ferrari e alla sua soluzione https://github.com/lorenzo-ferrari/olinfo/blob/main/src/ois_keygen.cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int MAXK = 16;
int pw[MAXK];

struct tritset { // lmao capita? perché bi-tset e tri-tset xd
    int value;

    tritset() {
        // (0, 1, 2) = (non preso, preso, da non prendere)
        value = 0;
    }
    tritset(int v) { value = v; }

    int get_elem(int pos) {
        return (value / pw[pos]) % 3;
    }

    void update(int pos, int new_elem) {
        int curr_elem = get_elem(pos);
        value -= curr_elem * pw[pos];
        value += new_elem * pw[pos];
    }
};

void setup(int K, string &S, vector<tritset> &group) {
    bool to_ignore = false;
    bool inverse = false;

    for (auto x : S) {
        if (x == '&' || x == '^') continue;
        if (x == '(') {            
            group.push_back(tritset());
            inverse = false;
            to_ignore = false;
            continue;
        }
        if (x == ')') {
            // controlla che non si rompa da solo
            if (to_ignore) group.pop_back();
            continue;
        }
        if (x == '!') {
            inverse = true;
            continue;
        }

        int curr_elem = group.back().get_elem(x - 'a');

        if (!inverse) {
            if (curr_elem == 2) to_ignore = 1;
            else group.back().update(x - 'a', 1);
        }   
        else {
            if (curr_elem == 1) to_ignore = 1;
            else group.back().update(x - 'a', 2);
        }
        inverse = false;
    }
}

void solve() {
    int K; cin >> K;
    string S; cin >> S;

    vector<tritset> group;
    setup(K, S, group);

    bool sums[pw[K]];
    fill(sums, sums + pw[K], 0);

    for (int i = 0; i < group.size(); i ++) sums[group[i].value] ^= 1;

    int tot = 0;
    for (int s = 0; s < pw[K]; s ++) {
        // questo continue è fondamentale e fa fullare.
        if (!sums[s]) continue;
        tritset ts(s);
        int first_zero = -1;
        for (int i = 0; i < K; i ++) {
            if (ts.get_elem(i) == 0) {
                first_zero = i;
                // questo break velocizza un po'
                break;
            }
        }

        // i sums di tritset senza zeri contengono lo xor di tutti i subset
        if (first_zero == -1) tot += sums[s];
        else {
            // propaga il valore ai tritset avanti. 
            // essendo tutti gli elem < i non zero e cambiando il valore di
            // i ad un valore diverso da zero, si è assicurati che alla fine
            // raggiunga tutti i tritset che contiene s.
            ts.update(first_zero, 1);
            sums[ts.value] ^= sums[s];
            ts.update(first_zero, 2);
            sums[ts.value] ^= sums[s];
        }
    }

    cout << tot << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    pw[0] = 1;
    for (int i = 1; i < MAXK; i ++) pw[i] = pw[i - 1] * 3;
    int T; cin >> T;
    while (T--) solve();
}
