#include <bits/stdc++.h>

using namespace std;

int prim(int n, vector<vector<pair<int,int>>> &adj, vector<pair<int,int>> &p, vector<int> &depth) {
    int start = 0;
    vector<bool> v(n,0);
    priority_queue<tuple<int,int,int>> q;
    q.push({0,start,-1});
    int sum = 0;
    while (!q.empty()) {
        auto [peso, nodo, parent] = q.top(); q.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;
        p[nodo] = {parent,-peso};
        if (parent != -1) {
            depth[nodo] = depth[parent]+1;
        }
        sum += -peso;

        for (auto [u,w] : adj[nodo]) {
            if (v[u]) continue;
            q.push({-w,u,nodo});
        }
    }
    return sum;
}

int ancestor(int nodo, int k, vector<vector<int>> &bin_lift) {
    int pow = 0;
    while (k != 0) {
        if (k%2==1) {
            nodo = bin_lift[nodo][pow];
        }
        k/=2;
        pow++;
    }
    return nodo;
}

int lca(int n, int nodo1, int nodo2, vector<int>&depth, vector<vector<int>> &bin_lift) {

    if (depth[nodo1] < depth[nodo2]) swap(nodo1, nodo2);
    
    nodo1 = ancestor(nodo1, depth[nodo1]-depth[nodo2], bin_lift);

    if (nodo1 == nodo2) return nodo1;

	for (int i=(int)log2(depth[nodo1]);i>=0;i--) {
		if (bin_lift[nodo1][i] != bin_lift[nodo2][i]) {
			nodo1 = bin_lift[nodo1][i];
			nodo2 = bin_lift[nodo2][i];
		}
	}

    return bin_lift[nodo1][0];
}

int max_ancestor(int nodo, int k, vector<vector<int>> &bin_lift,vector<vector<int>> &max_path) {
    int pow = 0;
    int res = 0;
    while (k != 0) {
        if (k%2==1) {
            res = max(res, max_path[nodo][pow]);
            nodo = bin_lift[nodo][pow];
        }
        k/=2;
        pow++;
    }
    return res;
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, s; cin >> n >> s;
    vector<vector<pair<int,int>>> adj(s);
    vector<tuple<int,int,int>> fav(n);
    for (int i=0;i<n;i++) {
        int a, b, t; cin >> a >> b >> t;
        fav[i] = {a,b,t};
        adj[a].push_back({b,t});
        adj[b].push_back({a,t});
    }

    vector<pair<int,int>> p(s);
    vector<int> depth(s);
    depth[0]=0;
    int mst = prim(s,adj,p,depth);
    
    vector<vector<int>> bin_lift(s, vector<int>((int)ceil(log2(s)),-3));
    for (int j=0;j<(int)ceil(log2(s));j++) {
        for (int i=0;i<s;i++) {
            if (i == 0) {
                bin_lift[i][j]=i;
                continue;
            }
            if (j == 0) {
                bin_lift[i][j]=p[i].first;
                continue;
            }
            bin_lift[i][j] = bin_lift[ bin_lift[i][j-1] ][j-1];
        }
    }

    vector<vector<int>> max_path(s, vector<int>((int)ceil(log2(s)),-1));
    for (int j=0;j<(int)ceil(log2(s));j++) {
        for (int i=0;i<s;i++) {
            if (i == 0) {
                max_path[i][j]=0;
                continue;
            }
            if (j == 0) {
                max_path[i][j]=p[i].second;
                continue;
            }
            max_path[i][j] = max(
                max_path[i][j-1],
                max_path[bin_lift[i][j-1]][j-1]
            );
        }
    }

    for (int i=0;i<n;i++) {
        auto [a,b,c] = fav[i];
        int lca_node = lca(s,a,b,depth,bin_lift);
        int massimo = max(
            max_ancestor(a,depth[a]-depth[lca_node],bin_lift,max_path),
            max_ancestor(b,depth[b]-depth[lca_node],bin_lift,max_path));
        cout << mst - massimo + c << '\n';
    } 
}
