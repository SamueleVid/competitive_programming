#include <bits/stdc++.h>

using namespace std;

void dfs(int nodo, int n, vector<int> &l, vector<int> &visited, vector<int> &elems) {
    if (visited[nodo]) return;
    visited[nodo] = 1;
    elems.push_back(nodo);
    for (auto x : l) {
        if (nodo-x>=0) dfs(nodo-x, n, l, visited, elems);
        if (nodo+x<n) dfs(nodo+x, n, l, visited, elems);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; cin >> n >> m;
    vector<int> v(n), l(m);
    for (auto &x:v) cin >> x;
    for (auto &x:l) cin >> x;

    vector<int> sol(n,-1);
    vector<int> visited(n,0);
    for (int i=0;i<n;i++) {
        vector<int> elems;
        dfs(i,n,l,visited,elems);

        vector<int> values;
        for (auto x : elems) values.push_back(v[x]);
        
        sort(elems.begin(), elems.end());
        sort(values.begin(), values.end());

        for (int i=0;i<elems.size();i++) {
            sol[elems[i]] = values[i];
        }
    }

    for (auto x : sol) cout << x << " ";
    cout << '\n';
}
