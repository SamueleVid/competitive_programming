#include <bits/stdc++.h>
using namespace std;

vector<long long>dijkstra(int start, vector<vector<pair<int,int>>>&adj, int n) {
    vector<long long>d(n,1e18);
    vector<bool>v(n);
    d[start] = 0;
    priority_queue<pair<long long, int>>pq;
    pq.push({0,start});

    while (!pq.empty()) {
        int nodo = pq.top().second; pq.pop();
        if (v[nodo]) continue;
        v[nodo] = 1;
        for (auto [u,w]:adj[nodo]) {
            if (v[u]) continue;
            long long dist = d[nodo]+w;
            if (dist < d[u]) {
                d[u] = dist;
                pq.push({-d[u],u});
            }
        }
    }

    return d;
}

void init(int n, int fake_n, vector<pair<long long, long long>>&v, vector<long long>&seg1, vector<long long>&seg2) {
    for (int i=0;i<n;i++) {
        seg1[i+fake_n]=v[i].first+v[i].second;
        seg2[i+fake_n]=2*v[i].first+v[i].second;
    }
    for (int i=fake_n-1;i>=1;i--) {
        seg1[i]=min(seg1[2*i],seg1[2*i+1]);
        seg2[i]=min(seg2[2*i],seg2[2*i+1]);
    }
}

long long minim(int fake_n, vector<long long>&seg, int l, int r) {
    l += fake_n;
    r += fake_n;
    long long res = 1e18;
    while (l<=r) {
        if (l%2==1) {
            res = min(res,seg[l]);
            l ++;
        }
        if (r%2==0) {
            res = min(res,seg[r]);
            r --;
        }
        l/=2;
        r/=2;
    }
    return res;
}

vector<long long> shorten(int n, int m, int q, vector<long long> k, vector<int> a, vector<int> b, vector<int> c) {
    vector<vector<pair<int,int>>>adj(n);
    for (int i=0;i<m;i++) {
        adj[a[i]].push_back({b[i],c[i]});
        adj[b[i]].push_back({a[i],c[i]});
    }
    
    vector<long long> dij0 = dijkstra(0,adj,n);
    vector<long long> dij1 = dijkstra(1,adj,n);
    vector<long long> dij2 = dijkstra(2,adj,n);

    // common, separate
    vector<pair<long long, long long>>v(n);
    for (int i=0;i<n;i++) {
        v[i] = {dij1[i],dij0[i]+dij2[i]};
    }
    sort(v.begin(), v.end());

    int fake_n = 1<<(int)ceil(log2(n));
    // seg1 = C+S, seg2 = 2*C+S
    vector<long long>seg1(2*fake_n,1e18), seg2(2*fake_n,1e18);
    init(n,fake_n,v,seg1,seg2);

    vector<long long>res;

    for (int j=0;j<q;j++) {
        long long i = -1;
        for (int pw=1<<(int)log2(n);pw>=1;pw/=2) {
            if (pw+i < n && v[i+pw].first <= k[j]) i+=pw;
        }
        i ++;
        long long res1 = minim(fake_n,seg1,0,i-1);
        long long res2 = minim(fake_n,seg2,i,n);

        res1 -= k[j];
        res2 -= 2*k[j];
        long long curr = min(res1,res2);
        curr = max(curr, 0ll);
        res.push_back(curr);
    }
    return res;
}
