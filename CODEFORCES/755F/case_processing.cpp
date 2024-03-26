#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;
const int T = 176; // T = n/32T
int n, k;
int p[MAXN];
bool v[MAXN]{0};
bitset<MAXN> dp;
int used[MAXN];
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
    
    vector<pair<int,int>>v_small; // value, how many
    vector<int>v_big;
    v_small.push_back({groups[0],0});
    for (auto x : groups) {
        if (x < T) {
            if (v_small.back().first == x) v_small.back().second ++;
            else v_small.push_back({x,1});
        }
        else {
            v_big.push_back(x);
        }
    }
 
    // per x < T faccio knapsack per elementi distinti, quindi O(Tk)
    dp[0] = 1;
    for (auto [value, how_many] : v_small) {
        fill(used, used+k+1, 0);
        for (int i=value;i<=k;i++) {
            if (dp[i]) continue; // used[i] rimane zero
            if (dp[i-value] && used[i-value] < how_many) {
                dp[i] = 1;
                used[i] = used[i-value] + 1;
            }
        }
        if (dp[k]) break;
    }
 
    // per x >= T faccio knapsack con bitset. Al massimo ci sono n/T elementi >= T quindi O(nk/32T)
    for (auto x : v_big) {
        dp |= dp << x;
    }
 
    if (dp[k]) minim = k;
    else minim = min(k + 1, n);
 
    cout << minim << " " << maxim << '\n';   
}
