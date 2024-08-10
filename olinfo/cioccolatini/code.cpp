#include <bits/stdc++.h>
using namespace std;

vector<vector<int>>adj;
vector<int>p,h,dim,depth,treearray,pos_in_array;

void dfs(int u) {
    dim[u] = 1;
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        depth[x] = depth[u] + 1;
        p[x] = u;
        dfs(x);
        dim[u] += dim[x];
    }
    sort(adj[u].begin(), adj[u].end(), [&](int i, int j){return dim[i] > dim[j];});
}

void dfs_hld(int u) {
    treearray.push_back(u);
    pos_in_array[u] = treearray.size() - 1;
    bool first = true;
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        if (first) {
            // hld
            h[x] = h[u];
            first = false;
        }
        else {
            // not hld
            h[x] = x;
        }
        dfs_hld(x);
    }
}

int fake_n; vector<int>seg;
void build(int n, vector<int>&c) {
    fake_n = 1 << (int)ceil(log2(n));
    seg.assign(2*fake_n,0);
    for (int i=0;i<n;i++) seg[fake_n+pos_in_array[i]]=c[i];
    for (int i=fake_n-1;i>0;i--) seg[i] = max(seg[2*i],seg[2*i+1]); 
}

int query(int lb, int rb) {
    lb += fake_n;
    rb += fake_n;
    int res = 0;
    while (lb <= rb) {
        if ((lb%2)==1) {
            res = max(res, seg[lb]);
            lb ++;
        }
        if ((rb%2)==0) {
            res = max(res, seg[rb]);
            rb --;
        }
        lb /= 2; rb /= 2;
    }
    return res;
}

vector<int> raccogli(int n, int q, vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &l, vector<int> &t){
    // adj list
    adj.resize(n);
    for (int i=0;i<n-1;i++) {
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }

    // root in 0
    p.resize(n); dim.resize(n); depth.resize(n);
    depth[0] = 0; 
    p[0] = -1;
    dfs(0);

    // treearray and hld
    pos_in_array.resize(n);  h.resize(n); 
    h[0] = 0;
    dfs_hld(0);

    // build segtree
    vector<int>results;
    build(n,c);

    for (int i=0;i<q;i++) {
        int a = l[i]; int b = t[i];
        vector<pair<int,int>>to_skip;
        to_skip.push_back({-1,-1});
        to_skip.push_back({n,n});

        // binliftare sopra e aggiungere gli archi in to_skip
        while (h[a] != h[b]) {
            // h[a] è più in basso in h[b]
            if (depth[h[a]] < depth[h[b]]) swap(a,b);
            to_skip.push_back({pos_in_array[h[a]], pos_in_array[a]});
            a = p[h[a]];
        }
        // stessa testa, quello più in alto è l'lca
        // b è l'lca
        if (depth[a] < depth[b]) swap(a,b);
        to_skip.push_back({pos_in_array[b], pos_in_array[a]});

        // sorto
        sort(to_skip.begin(), to_skip.end());

        // trovo il massimo tra le zone non da skippare con il segment
        int res = 0;
        for (int i=0;i<to_skip.size()-1;i++) {
            int start = to_skip[i].second + 1;
            int end = to_skip[i+1].first - 1;
            int curr_res = query(start, end);
            res = max(res, curr_res);
        }

        results.push_back(res);
    }

    return results;
}
