#include <bits/stdc++.h>

using namespace std;

int get_num(char porta) {
    if (porta == 'P') return 1;
    if (porta == 'C') return 2;
    if (porta == 'Z') return 4;
    if (porta == 'N') return 8;
    return 42069;
}

void dfs(int nodo, int value, vector<vector<bool>>&v, vector<vector<pair<int,int>>>&graph) {
    if (v[nodo][value]) return;
    v[nodo][value] = 1;
    for (auto [m,w] : graph[nodo]) {
        dfs(m,value|w,v,graph);
    }
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<char>> murii(n, vector<char>(m-1)); 
    vector<vector<char>> muri_(n-1, vector<char>(m)); 
    for (auto &x:murii) for (auto &y:x) cin >> y;
    for (auto &x:muri_) for (auto &y:x) cin >> y;
    int q; cin >> q;

    vector<vector<pair<int,int>>>graph(n*m);

    for (int i=0;i<n;i++) {
        for (int j=0;j<m-1;j++) {
            char porta = murii[i][j];
            int num = get_num(porta);
            graph[m*i+j].push_back({m*i+j+1,num});
            graph[m*i+j+1].push_back({m*i+j,num});
        }
    }
    
    for (int i=0;i<n-1;i++) {
        for (int j=0;j<m;j++) {
            char porta = muri_[i][j];
            int num = get_num(porta);
            graph[m*i+j].push_back({m*(i+1)+j,num});
            graph[m*(i+1)+j].push_back({m*i+j,num});
        }
    }

    for (int qq=0;qq<q;qq++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        a--;b--;c--;d--;

        vector<vector<bool>>v(n*m,vector<bool>(16,false));

        dfs(a*m+b,0,v,graph);

        int res = 16;
        for (int i=0;i<16;i++) {
            if (!v[c*m+d][i]) continue;
            int curr = 0;
            if (i&1) curr ++;
            if (i&2) curr ++;
            if (i&4) curr ++;
            if (i&8) curr ++;
            res = min(res,  curr);
        }
        cout << res << '\n';
    }
}
