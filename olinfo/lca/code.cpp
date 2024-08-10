#include <bits/stdc++.h>

using namespace std;

struct subpath{
    long long sum, pref, suff, best;
};

vector<vector<int>>binlift;
vector<long long>ps;
vector<vector<int>>minarc;
vector<vector<subpath>>maxpath;
vector<pair<int,int>>p;
vector<int>depth;

subpath merge(subpath &a, subpath &b) {
    subpath res;
    res.sum = a.sum + b.sum;
    res.pref = max(a.pref, a.sum+b.pref);
    res.suff = max(b.suff, b.sum+a.suff);
    res.best = max(max(a.best,b.best), a.suff+b.pref);
    return res;
};

void dfs(int nodo, vector<vector<pair<int,int>>>&adj, int to_ignore) {
    for (auto [u,w] : adj[nodo]) {
        if (u == to_ignore) continue;
        p[u] = {nodo,w};
        ps[u] = ps[nodo]+w;
        depth[u] = depth[nodo]+1;
        dfs(u,adj,nodo);
    }
}

void inizia(int n, int t, int a[], int b[], int c[]) {
    binlift.assign(n, vector<int>((int)ceil(log2(n)),-1));
    minarc.assign(n, vector<int>((int)ceil(log2(n)),-1));
    maxpath.assign(n, vector<subpath>((int)ceil(log2(n))));
    p.resize(n);
    ps.resize(n);
    depth.resize(n);
    depth[0]=0;
    p[0]={-1,-1};
    ps[0]=0;

    vector<vector<pair<int,int>>>adj(n);
    for (int i=0;i<n;i++) {
        adj[a[i]].push_back({b[i],c[i]});
        adj[b[i]].push_back({a[i],c[i]});
    }

    dfs(0,adj,-1);

    for (int j=0;j<(int)ceil(log2(n));j++) {
        for (int i=0;i<n;i++) {
            if (i==0) {
                binlift[i][j]=0;
                continue;
            }
            if (j==0) {
                binlift[i][j]=p[i].first;
                continue;
            }
            binlift[i][j] = binlift[ binlift[i][j-1] ][j-1];
        }
    }

    for (int j=0;j<(int)ceil(log2(n));j++) {
        for (int i=0;i<n;i++) {
            if (i==0) {
                minarc[i][j]=1e9;
                continue;
            }
            if (j==0) {
                minarc[i][j]=p[i].second;
                continue;
            }
            minarc[i][j] = min(minarc[i][j-1], minarc[ binlift[i][j-1] ][j-1]);
        }
    }

    for (int j=0;j<(int)ceil(log2(n));j++) {
        for (int i=0;i<n;i++) {
            if (i==0) {
                maxpath[i][j]={0,0,0,0};
                continue;
            }
            if (j==0) {
                maxpath[i][j]={p[i].second,p[i].second,p[i].second,p[i].second};
                continue;
            }
            maxpath[i][j] = merge(
                maxpath[i][j-1],
                maxpath[ binlift[i][j-1] ][j-1]
            );
        }
    }
}

int ancestor(int u, int k) {
    for (int i=0;i<=log2(k);i++) {
        if (1<<i & k) u = binlift[u][i];
    }
    return u;
}

int min_path(int u, int k) {
    int minim = 1e9;
    for (int i=0;i<=log2(k);i++) {
        if (1<<i & k) {
            minim = min(minim, minarc[u][i]);
            u = binlift[u][i];
        }
    }
    return minim;
}

subpath max_path(int u, int k) {
    subpath res = {0,0,0,0};
    for (int i=0;i<=log2(k);i++) {
        if (1<<i & k) {
            res = merge(res, maxpath[u][i]);
            u = binlift[u][i];
        }
    }
    return res;
}

int lca(int u, int v) {
    // u è quello più in basso
    if (depth[u] < depth[v]) swap(u,v);
    u = ancestor(u,depth[u]-depth[v]);
    if (u == v) return u;
    for (int i=log2(depth[u]);i>=0;i--) {
        if (binlift[u][i] != binlift[v][i]) {
            u = binlift[u][i];
            v = binlift[v][i];
        }
    }
    return binlift[u][0];
}

long long distanza1(int u, int v) {
    int lcanode = lca(u,v);
    if (lcanode == u || lcanode == v) {
        // v è l'lca, u è in basso
        if (lcanode == u) swap(u,v);
        return depth[u]-depth[lcanode];
    }
    return (depth[u]-depth[lcanode])+(depth[v]-depth[lcanode]);
}

long long distanza2(int u, int v) {
    int lcanode = lca(u,v);
    if (lcanode == u || lcanode == v) {
        // v è l'lca, u è in basso
        if (lcanode == u) swap(u,v);
        return ps[u]-ps[lcanode];
    }
    return (ps[u]-ps[lcanode])+(ps[v]-ps[lcanode]);
}

long long minimo(int u, int v) {
    int lcanode = lca(u,v);
    if (lcanode == u || lcanode == v) {
        // v è l'lca, u è in basso
        if (lcanode == u) swap(u,v);
        return min_path(u,depth[u]-depth[lcanode]);
    }
    return min(
        min_path(u,depth[u]-depth[lcanode]),
        min_path(v,depth[v]-depth[lcanode])
    );
}

long long massimo(int u, int v) {
    int lcanode = lca(u,v);
    if (lcanode == u || lcanode == v) {
        // v è l'lca, u è in basso
        if (lcanode == u) swap(u,v);
        return max_path(u,depth[u]-depth[lcanode]).best;
    }
    subpath sx = max_path(u,depth[u]-depth[lcanode]);
    subpath dx = max_path(v,depth[v]-depth[lcanode]);
    return max(max(sx.best, dx.best), sx.suff+dx.suff);
}
