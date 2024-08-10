#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
struct node {
    ll v = 0;
    node* sx;
    node* dx;
};
 
node arr[10000000];
ll pt = 0;
node* nn() {
    node* newnodo = arr+pt++;
    newnodo->v = 0;
    return newnodo;
}
 
void add(node* nodo, ll x, ll k, ll clb, ll crb) {
    
    if (x<clb || crb<=x) return;
    if (clb == x && crb == x+1) {
        nodo->v += k;
        return;
    }
    if (!nodo->sx) nodo->sx = nn();
    add(nodo->sx,x,k,clb,(clb+crb)/2);
    if (!nodo->dx) nodo->dx = nn();
    add(nodo->dx,x,k,(clb+crb)/2,crb);
    nodo->v = nodo->sx->v + nodo->dx->v; 
}
 
ll query(node* nodo, ll lb, ll rb, ll clb, ll crb) {
    if (rb<=clb || crb<=lb) return 0;
    if (lb<=clb && crb<=rb) return nodo->v;
    ll res = 0;
    if (nodo->sx) res += query(nodo->sx,lb,rb,clb,(clb+crb)/2);
    if (nodo->dx) res += query(nodo->dx,lb,rb,(clb+crb)/2,crb);
    return res;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ll n, q; cin >> n >> q;
    vector<ll>curr_sal(n+1);
    node* root = nn();
    for (ll i=1;i<=n;i++) {
        ll x; cin >> x;
        curr_sal[i] = x;
        add(root,x,1,1,1e9+1);
    }
    while (q--) {
        char c; cin >> c;
        ll a, b; cin >> a >> b;
        if (c == '!') {
            add(root,curr_sal[a],-1,1,1e9+1);
            curr_sal[a] = b;
            add(root,curr_sal[a],1,1,1e9+1);
        }
        else {
            cout << query(root,a,b+1,1,1e9+1) << '\n'; 
        }
    }
}
