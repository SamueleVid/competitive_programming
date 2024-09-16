#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e5 + 5;
int C[MAXN];
int P[MAXN];
vector<int> adj[MAXN];
int res = 1;
map<int, int> mappe[MAXN];
map<int, int> freq[MAXN];

void dfs(int u) {
    mappe[u][C[u]] = 1;
    freq[u][1] = 1; 
    for (auto x : adj[u]) {
        dfs(x);
        if (mappe[u].size() < mappe[x].size()) {
            swap(mappe[u], mappe[x]);
            swap(freq[u], freq[x]);
        }
        for (auto [a, b] : mappe[x]) {
            freq[u][mappe[u][a]] --;
            mappe[u][a] += b;
            freq[u][mappe[u][a]] ++;
        }
    }

    res = max(res, freq[u].rbegin()->second);
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;

    for (int i = 0; i < N; i ++) cin >> C[i];
    P[0] = -1;
    for (int i = 1; i < N; i ++) cin >> P[i];

    for (int i = 1; i < N; i ++) adj[P[i]].push_back(i);
    
    dfs(0);
    cout << res << '\n';
}
