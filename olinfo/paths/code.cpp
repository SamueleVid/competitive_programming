#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9+7;

int boss(int a, vector<int>&link) {
    if (link[a] == a) return a;
    return link[a]=boss(link[a],link);
}

void join(int a, int b, vector<int>&link, vector<int>&size, vector<int>&top, vector<int> &depth) {
    int boss_a = boss(a,link);
    int boss_b = boss(b,link);
    if (boss_a == boss_b) return;
    if (size[boss_a] < size[boss_b]) swap(boss_a, boss_b);
    link[boss_b] = boss_a;
    size[boss_a] += size[boss_b];
    // setta il nodo più alto
    if (depth[top[boss_b]] < depth[top[boss_a]]) top[boss_a] = top[boss_b];
}

void dfs(int a, vector<vector<int>> &adj, int to_ignore, vector<int> &p, vector<int> &depth) {
    for (auto x : adj[a]) {
        if (x == to_ignore) continue;
        p[x] = a;
        depth[x] = depth[a]+1;
        dfs(x,adj,a,p,depth);
    }
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n;
    vector<vector<int>> adj(n+1);
    vector<pair<int,int>> edges(n-1);
    map<pair<int,int>,int> edges_to_id;
    for (int i=0;i<n-1;i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges[i] = {min(a,b),max(a,b)};
        edges_to_id.insert({{min(a,b),max(a,b)},i});
    }
    cin >> m;
    vector<pair<int,int>> ms(m);
    for (auto &[a,b] : ms) cin >> a >> b;

    // buildo dsu
    vector<int> link(n-1);
    for (int i=0;i<n-1;i++) link[i]=i;
    vector<int> size(n-1,1);
    vector<int> top(n-1);

    // buildo il parent tree e il depth
    vector<int> p(n+1);
    vector<int> depth(n+1,0);
    dfs(1,adj,-1,p,depth);

    // inizializzo il nodo più alto di ogni insieme
    for (int i=0;i<n-1;i++) {
        int nodo_1 = edges[i].first;
        int nodo_2 = edges[i].second;
        if (depth[nodo_1]<depth[nodo_2]) top[i] = nodo_1;
        else top[i] = nodo_2;
    }

    for (auto [a,b]:ms) {

        // gli id degli insiemi rispettivamente di b e di a
        int id_da_unire_a = -1;
        int id_da_unire_b = -1;

        // alzo i nodi verso l'alto così che stessa depth
        // pian piano unisco tra di loro i path salendo
        while (a != b) {
            if (depth[b]>depth[a]) {
                int id_arco = edges_to_id[{min(b,p[b]),max(b,p[b])}];
                if (id_da_unire_b == -1) id_da_unire_b = id_arco;
                else join(id_arco, id_da_unire_b, link, size, top, depth);
                // salgo al più alto dell'insieme per evitare di ricalcolare roba
                b = top[boss(id_arco,link)];
            }
            else {
                int id_arco = edges_to_id[{min(a,p[a]),max(a,p[a])}];
                if (id_da_unire_a == -1) id_da_unire_a = id_arco;
                join(id_arco, id_da_unire_a, link, size, top, depth);
                // salgo al più alto dell'insieme per evitare di ricalcolare roba
                a = top[boss(id_arco,link)];
            }
        }

        // se son saliti entrambi li unisco 
        if (id_da_unire_a != -1 && id_da_unire_b != -1) join(id_da_unire_a, id_da_unire_b, link, size, top, depth);
    }

    // conto numero di insiemi
    // ogni insieme ha due possibilità, o andare tutti verso una direzione o l'altra
    long long res = 1;
    vector<int> visited(n-1,0);
    for (int i=0;i<n-1;i++) {
        if (!visited[boss(i,link)]) {
            visited[boss(i,link)] = 1;
            res *= 2;
            res %= mod;
        }
    }
    cout << res << endl;
}
