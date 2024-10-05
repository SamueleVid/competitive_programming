#include <bits/stdc++.h>
using namespace std;

vector<int> verifica(int N, vector<int> T) {
    vector<int> sx(N, 1e9), dx(N, -1e9);
    for (int i = 0; i < N; i ++) {
        sx[T[i]] = min(sx[T[i]], i);
        dx[T[i]] = max(dx[T[i]], i);
    }

    vector<int> res;
    int l = 0;
    int r = 0;
    bool started = false;
    for (int i = 0; i < N; i ++) {
        if (sx[i] == 1e9) continue;
        if (!started) {
            started = 1;
            l = sx[i];
            r = dx[i];
            for (int j = sx[i]; j <= dx[i]; j ++) {
                res.push_back(j);
                if (T[j] < res.size() - 1) return {};
            }
        }
        else {
            while (l > sx[i]) {
                l --;
                res.push_back(l);
                if (T[l] < res.size() - 1) return {};
            }
            while (r < dx[i]) {
                r ++;
                res.push_back(r);
                if (T[r] < res.size() - 1) return {};
            }
        }

    }
    return res;
}
