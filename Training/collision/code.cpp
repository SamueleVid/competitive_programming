#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<int> v(N);
    int total_xor = 0;
    for (int i = 0; i < N - 1; i ++) {
        v[i] = abs(rand());
        total_xor ^= v[i];
    }
    v[N - 1] = total_xor ^ K;

    vector<int> w = v;
    for (int pw = 30; pw >= 0; pw --) {
        for (int i = 0; i < N; i ++) {
            for (int j = i + 1; j < N; j ++) {
                if (rand() % 2) continue;
                int bit_i = (v[i] >> pw) & 2;
                int bit_j = (v[j] >> pw) & 2;
                v[i] ^= bit_i << pw;
                v[i] ^= bit_j << pw;
                v[j] ^= bit_j << pw;
                v[j] ^= bit_i << pw;
            }
        }
    }

    for (auto x : v) cout << x << " ";
    cout << '\n';
    for (auto x : w) cout << x << " ";
    cout << '\n';
}
