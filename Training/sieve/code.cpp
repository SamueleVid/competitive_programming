#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<int> V(N);
    for (auto &x : V) cin >> x;

    bool graph[N][N];
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < i; j ++) {
            graph[i][j] = ((V[i] % V[j]) == 0);
        }
        for (int j = i; j < N; j ++) {
            graph[i][j] = ((V[j] % V[i]) == 0);
        }
    }

    int res = 0;
    vector<bool> generator(N, 1);
    for (int i = 0; i < N; i ++) {
        if (generator[i]) {
            res ++;
            for (int j = i + 1; j < N; j ++) {
                if (graph[i][j]) generator[j] = 0;
            }
        }
    }

    for (int i = 0; i < N; i ++) {
        if (generator[i]) continue;
        vector<int> generated_by(N, 0);
        int generators = 0;
        for (int j = 0; j < N; j ++) {
            if (graph[j][i] && generator[j]) {
                generated_by[j] = 1;
                generators ++;
            }
        }

        vector<int> remains_alone;
        for (int j = 0; j < N; j ++) {
            bool generato_da_altri = false;
            for (int z = 0; z < N; z ++) {
                // se può essere generato da un generatore diverso da quelli di V[i] allora ignoro
                if (graph[j][z] && generator[z] && !generated_by[z]) generato_da_altri = true;
            }
            if (generato_da_altri) continue;
            // non deve essere generato da V[i]
            if (graph[j][i]) continue;

            remains_alone.push_back(j);
        }

        if (generators > remains_alone.size() + 1) {
            for (int j = 0; j < N; j ++) {
                if (generated_by[j]) generator[j] = 0;
            }
            generator[i] = 1;
            for (auto x : remains_alone) generator[x] = 1;
            res += remains_alone.size() + 1 - generators;
        }
    }

    cout << res << '\n';
}
