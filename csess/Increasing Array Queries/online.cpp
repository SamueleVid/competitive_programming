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
node arr[16000000];
node* newnode() { return arr+it++; }
 
node* copy(node* nodo, int l, int r) {
    node* nodo1 = newnode();
    nodo1->v = nodo->v;
    nodo1->lazy = nodo->lazy;
    if (r-l>1) {
        nodo1->sx = nodo->sx;
        nodo1->dx = nodo->dx;
    }
    return nodo1;
}
 
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
        nodo->sx = copy(nodo->sx,l,(l+r)/2);
        nodo->sx->lazy += nodo->lazy;
        nodo->dx = copy(nodo->dx,(l+r)/2,r);
        nodo->dx->lazy += nodo->lazy;
    }
    nodo->lazy = 0;
}
 
node* update(node* nodo, int l, int r, int ql, int qr, int k) {
    push_lazy(nodo,l,r);
    
    if (qr<=l || r<=ql) return nodo;
 
    node* nodo1 = copy(nodo,l,r);
    if (ql<=l && r<=qr) {
        nodo1->lazy += k;
        push_lazy(nodo1,l,r);
        return nodo1;
    }
    
    nodo1->sx = update(nodo1->sx, l, (l+r)/2, ql, qr, k);
    nodo1->dx = update(nodo1->dx, (l+r)/2, r, ql, qr, k);
    nodo1->v = nodo1->sx->v + nodo1->dx->v;
    return nodo1;
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
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n,q; cin >> n >> q;
    vector<int>v(n);
    for (auto &x:v) cin >> x;
 
    vector<ll>ps(n+1);
    for (int i=0;i<n;i++) ps[i+1]=ps[i]+v[i];
 
    node* root = newnode();
    build(root, 0, n);
 
    vector<node*>ptree(n+1);
    ptree[n]=root;
 
    stack<int>minq;
 
    for (int i=n-1;i>=0;i--) {
        while (!minq.empty() && v[minq.top()] <= v[i]) {
            minq.pop();
        }
        int last = n;
        if (!minq.empty()) last = minq.top();
        minq.push(i);
    
        ptree[i] = update(ptree[last],0,n,i,last,v[i]);
    }
 
    while (q--) {
        int a,b; cin >> a >> b;
        ll newsum = sum(ptree[a-1],0,n,a-1,b);
        ll oldsum = ps[b]-ps[a-1];
 
        cout << newsum-oldsum << '\n';
    }
}
