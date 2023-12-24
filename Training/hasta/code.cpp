#include <bits/stdc++.h>

using namespace std;

struct node{
    int value = 0;
    node* sx = nullptr;
    node* dx = nullptr;
};

vector<node*>segs;

node arr[10000000];
int pt = -1;

node* newnode() {
    pt ++;
    node* nodo = arr+pt;
    nodo->value = 0;
    return nodo;
}

node* build(int l, int r) {
    node* nodo = newnode();
    if (r-l==1) return nodo;
    nodo->sx = build(l,(l+r)/2);
    nodo->dx = build((l+r)/2,r);
    return nodo;
} 

node* update(node* prev, int l, int r, int x, int k) {
    if (x<l || x>=r) return prev;
    node* nodo = newnode();
    
    nodo->value = prev->value;
    nodo->sx = prev->sx;
    nodo->dx = prev->dx;

    if (r-l==1) {
        nodo->value += k;
        return nodo;
    }

    nodo->sx = update(nodo->sx, l, (l+r)/2, x, k);
    nodo->dx = update(nodo->dx, (l+r)/2, r, x, k);
    nodo->value = nodo->sx->value + nodo->dx->value;
    return nodo;
}

int query(node* nodo, int l, int r, int orig_l, int orig_r) {
    if (r <= orig_l || orig_r <= l) return 0;
    if (orig_l <= l && r <= orig_r) return nodo->value;
    int res = 0;
    res += query(nodo->sx, l, (l+r)/2, orig_l, orig_r);
    res += query(nodo->dx, (l+r)/2, r, orig_l, orig_r);
    return res;
}

int n;

void inizia(int n, int k, int v[],int r[]) {
    ::n = n;
    vector<int>rimanenti(k,0);
    for (int i=0;i<k;i++) rimanenti[i]=r[i];
    vector<vector<int>>pos(k);
    vector<int>sx(k,-2);
    vector<int>dx(k,-1);

    segs.resize(n+1);
    segs[0] = build(0,n);

    for (int i=0;i<n;i++) {
        pos[v[i]].push_back(i);
        rimanenti[v[i]] --;

        vector<node*> curr_segs;
        curr_segs.push_back(segs[i]);
        if (sx[v[i]] >= 0) curr_segs.push_back(update(curr_segs.back(), 0, n, pos[v[i]][sx[v[i]]], r[v[i]]));
        if (dx[v[i]] >= 0) curr_segs.push_back(update(curr_segs.back(), 0, n, pos[v[i]][dx[v[i]]], -r[v[i]]));

        if (rimanenti[v[i]] <= 0) {
            sx[v[i]] ++;
            dx[v[i]] ++;
        }

        if (sx[v[i]] >= 0) curr_segs.push_back(update(curr_segs.back(), 0, n, pos[v[i]][sx[v[i]]], -r[v[i]]));
        if (dx[v[i]] >= 0) curr_segs.push_back(update(curr_segs.back(), 0, n, pos[v[i]][dx[v[i]]], r[v[i]]));

        segs[i+1] = curr_segs.back();
    }
}

int istiga(int i,int j) {
    int sol = query(segs[j+1],0,n,i,j+1);
    return sol;
}
