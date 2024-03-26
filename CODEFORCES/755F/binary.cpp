#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000010;
int n, k;
int p[MAXN];
bool v[MAXN]{0};
bitset<MAXN> dp;
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
    vector<pair<int,int>>v; // value, how many
    v.push_back({groups[0],0});
    for (auto x : groups) {
        if (v.back().first == x) v.back().second ++;
        else v.push_back({x,1});
    }
 
    // si dimostra che è O(sqrtn * n)
    dp[0] = 1;
    for (auto [value, how_many] : v) {
        // lo duplichi ogni volta e piano piano togli : o -> o o -> o o o o -> ...
        for (int pw = 1; pw <= how_many; pw *= 2) {
            dp |= dp << (value * pw);
            how_many -= pw;
        }
        // quello che rimane è minore della duplicazione successiva in quanto è uscito dal loop,
        // quindi si overlappa un pezzo però conclude il tutto
        dp |= dp << (value * how_many);
    }
 
    if (dp[k]) minim = k;
    else minim = min(k + 1, n);
 
    cout << minim << " " << maxim << '\n';   
}
