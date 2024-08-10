#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node{
    ll v=0;
    ll lazy=0;
    node* sx;
    node* dx;
};  
int it=0;
node arr[4000000];
node* newnode() { return arr+it++; }

void build(node* nodo, int l, int r) {
    if (r-l==1) return;
    nodo->sx = newnode();
    nodo->dx = newnode();
    build(nodo->sx, l, (l+r)/2);
    build(nodo->dx, (l+r)/2, r);
}

void push_lazy(node* nodo, int l, int r) {
    if (nodo->lazy == 0) return;
    nodo->v += (r-l)*nodo->lazy;
    if (r-l>1) {
        nodo->sx->lazy += nodo->lazy;
        nodo->dx->lazy += nodo->lazy;
    }
    nodo->lazy = 0;
}

void update(node* nodo, int l, int r, int ql, int qr, int k) {
    push_lazy(nodo,l,r);
    
    if (qr<=l || r<=ql) return;

    if (ql<=l && r<=qr) {
        nodo->lazy += k;
        push_lazy(nodo,l,r);
        return;
    }
    
    update(nodo->sx, l, (l+r)/2, ql, qr, k);
    update(nodo->dx, (l+r)/2, r, ql, qr, k);
    nodo->v = nodo->sx->v + nodo->dx->v;
    return;
}

ll sum(node* nodo, int l, int r, int ql, int qr) {
    if (qr<=l || r<=ql) return 0;

    push_lazy(nodo,l,r);

    if (ql<=l && r<=qr) {
        return nodo->v;
    }

    ll res = 0;
    res += sum(nodo->sx, l, (l+r)/2, ql, qr);
    res += sum(nodo->dx, (l+r)/2, r, ql, qr);
    return res;
}

bool comp(vector<int>&a, vector<int>&b) {
    return a[0] > b[0];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n,q; cin >> n >> q;
    vector<int>v(n);
    for (auto &x:v) cin >> x;
 
    node* seg = newnode();
    build(seg, 0, n);
 
    vector<vector<int>>queries(q);
    for (int i=0;i<q;i++) {
        int a,b; cin >> a >> b;
        queries[i]={a,b,i};
    }
    vector<ll>sol(q);
 
    sort(queries.begin(), queries.end(), comp);
 
    stack<int>minq;
 
    int to_process = n-1;
    for (auto query:queries) {
        int a = query[0];
        int b = query[1];
        int id = query[2];
        a --;
        b --;
        while (to_process >= a) {
            while (!minq.empty() && v[to_process] > v[minq.top()]) {   
                
                int l = minq.top();
                minq.pop();
                int r = n;
                if (!minq.empty()) r = minq.top();
                update(seg, 0, n, l, r, v[to_process]-v[l]);
            }
            minq.push(to_process);
            to_process --;
        }
        sol[id] = sum(seg, 0, n, a, b+1);
    }
 
    for (auto x : sol) cout << x << '\n';
}
