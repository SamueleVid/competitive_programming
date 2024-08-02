#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;
const int HALF_N = 500010;
int n, k, better_k;
int p[MAXN];
bool v[MAXN]{0};
bool dp[HALF_N]{0};
int used[HALF_N];
vector<int>groups;
 
void dfs(int u) {
    if (v[u]) return;
    v[u] = true;
    groups.back() ++;
    dfs(p[u]);
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    better_k = min(k,n-k);
    for (int i=1;i<=n;i++) cin >> p[i];
    for (int i=1;i<=n;i++) if (!v[i]) groups.push_back(0), dfs(i);
 
    int minim, maxim;
    
    // massimo : prendi più possibile le coppie pari, quando finiscono prendi i residui dispari singolarmente
    int odd = 0;
    for (auto x : groups) odd += x - (x % 2);
    if (odd >= 2*k) maxim = 2*k;
    else maxim = min(odd + (k - odd/2), n);
 
    // minimo : controlla se esiste un sottoinsieme di gruppi che sommati fanno esattamente k, altrimenti k + 1
    sort(groups.begin(), groups.end());
    vector<pair<int,int>>v; // value, how many
    v.push_back({groups[0],0});
    for (auto x : groups) {
        if (v.back().first == x) v.back().second ++;
        else v.push_back({x,1});
    }

    // sqrt(n) elementi distinti
    dp[0] = 1;
    for (auto [value, how_many] : v) {
        fill(used, used+better_k+1, 0);
        for (int i=value;i<=better_k;i++) {
            if (dp[i]) continue; // used[i] remains 0, no "value" are needed to cover dp[i] as it's been already covered by previous values
            if (dp[i-value] && used[i-value] < how_many) {
                dp[i] = 1;
                used[i] = used[i-value] + 1;
            }
        }
    }
 
    if (dp[better_k]) minim = k;
    else minim = min(k + 1, n);
 
    cout << minim << " " << maxim << '\n';   
}
