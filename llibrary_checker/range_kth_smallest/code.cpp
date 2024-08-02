#include <bits/stdc++.h>
using namespace std;

struct node{
    int v = 0;
    node* sx;
    node* dx;
};

int it = 0;
node arr[20000000];
node* newnode() {
    return arr+it++;
}

void build(node* nodo, int lb, int rb) {
    nodo->v = 0;
    if (rb-lb == 1) return;
    nodo->sx = newnode();
    nodo->dx = newnode();
    build(nodo->sx, lb, (lb+rb)/2);
    build(nodo->dx, (lb+rb)/2, rb);
}

node* update(node* nodo, int x, int k, int clb, int crb) {
    if (crb <= x || x < clb) return nodo;
    node* nodo1 = newnode();
    nodo1->v = nodo->v;

    if (crb - clb == 1) {
        nodo1->v += k;
        return nodo1;
    }
    
    nodo1->sx = update(nodo->sx, x, k, clb, (clb+crb)/2);
    nodo1->dx = update(nodo->dx, x, k, (clb+crb)/2, crb);
    nodo1->v = nodo1->sx->v + nodo1->dx->v;
    return nodo1;
}

int query(node* lnodo, node* rnodo, int clb, int crb, int a_sx, int k) {
    if (crb - clb == 1) return clb;
    int sx = rnodo->sx->v - lnodo->sx->v + a_sx;
    int dx = rnodo->dx->v - lnodo->dx->v + sx;
    if (sx >= k) return query(lnodo->sx, rnodo->sx, clb, (clb+crb)/2, a_sx, k);
    return query(lnodo->dx, rnodo->dx, (clb+crb)/2, crb, sx, k);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int>v(n);
    for (auto &x:v) cin >> x;

    vector<int>vsort = v;
    sort(vsort.begin(), vsort.end());
    map<int,int>m;
    for (int i=0;i<n;i++) m[vsort[i]] = i;

    // 0 è il root vuoto, così che la prefix sum è 1 based
    vector<node*>ptree;
    node* root = newnode();
    build(root, 0, n);
    ptree.push_back(root);

    for (int i=0;i<n;i++) {
        int id = m[v[i]];
        ptree.push_back(update(ptree.back(), id, 1, 0, n));
    }

    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        // r escluso e prefix 1 based
        int id = query(ptree[l],ptree[r],0,n,0,k+1);
        cout << vsort[id] << '\n';
    }
}
