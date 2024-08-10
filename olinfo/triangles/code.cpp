#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 2e5+5;
ll out[MAXN];
ll not_triangles[MAXN];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll N, Q; cin >> N >> Q;

    for (int i = 1; i <= N; i ++) out[i] = N - i;
    for (int i = 1; i <= N; i ++) not_triangles[i] = (out[i] * (out[i] - 1)) / 2;
    ll tot_triples = (N * (N - 1) * (N - 2)) / 6;
    ll tot_not_triangles = 0;
    for (int i = 1; i <= N; i ++) tot_not_triangles += not_triangles[i];

    while (Q --) {
        int a, b; cin >> a >> b;

        tot_not_triangles -= not_triangles[a];
        tot_not_triangles -= not_triangles[b];

        out[b] ++;
        out[a] --;
        not_triangles[a] = (out[a] * (out[a] - 1)) / 2;
        not_triangles[b] = (out[b] * (out[b] - 1)) / 2;
        tot_not_triangles += not_triangles[a];
        tot_not_triangles += not_triangles[b];

        cout << tot_triples - tot_not_triangles << '\n';
    }
}
