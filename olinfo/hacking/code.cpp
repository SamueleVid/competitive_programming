#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<int>v(n);
    for (auto &x:v) cin >> x;

    // mi salvo un vettore di posizioni per ogni valore
    map<int,set<int>> m;
    for (int i=0;i<n;i++) {
        auto it = m.find(v[i]);
        if (it == m.end()) {
            m.insert({v[i],{i}});
        }
        else {
            it->second.insert(i);
        }
    }

    int res = 0;

    while (!m.empty()) {

        auto [value, s] = *m.begin();

        if (value > 0) {
            // non va bene che nodi visitati siano positivi
            cout << 0 << '\n';
            return 0;
        }

        while (!m.begin()->second.empty()) {

            res ++;

            int pos = *m.begin()->second.begin();

            m.begin()->second.erase(m.begin()->second.begin());
        
            int to_visit = value + 2;
            while (to_visit <= -value) {

                auto it = m.find(to_visit);
                if (it == m.end()) {
                    // se non trova  la roba

                    cout << 0 << '\n';
                    return 0;
                }

                // bsa upper bound

                auto pos_nuova = it->second.upper_bound(pos);

                if (pos_nuova == it->second.end()) {
                    // non trovato non c'è tutto visitato

                    cout << 0 << '\n';
                    return 0;
                }

                it->second.erase(pos_nuova);
                if (it->second.size() == 0) {
                    m.erase(it);
                }

                to_visit += 2;
                pos = *pos_nuova;
            }
            
        }

        m.erase(m.begin());
    }

    cout << res << endl;
}
