#include <bits/stdc++.h>
using namespace std;
#define ll long long
mt19937_64 real_rand;
constexpr int MAXARR = 1e7 + 5;

struct node {
    ll cnt = 1;
    ll Y;
    node* sx = nullptr;
    node* dx = nullptr;
    ll info = -2;
};

node arr[MAXARR];
int it = 0;
node* get_new_node() {
    return arr + it ++;
}

struct treap {

    node* root;
    treap(int N) {
        vector<int> v(N);
        iota(v.begin(), v.end(), 0);

        root = build(0, N, v);
    }

    node* build(int l, int r, vector<int> &v) {
        if (l >= r) return nullptr;
        node* nodo = get_new_node();
        nodo->Y = real_rand();
        nodo->info = v[(l + r) / 2];
        nodo->sx = build(l, (l + r) / 2, v);
        nodo->dx = build((l + r) / 2 + 1, r, v);

        upd_cnt(nodo);
        heapify(nodo);
        return nodo;
    }

    void heapify(node* treap) {
        if (!treap) return;
        node* max_prior = treap;
        if (treap->sx && treap->sx->Y > max_prior->Y) {
            max_prior = treap->sx;
        }
        if (treap->dx && treap->dx->Y > max_prior->Y) {
            max_prior = treap->dx;
        }
        if (treap->Y != max_prior->Y) {
            swap(treap->Y, max_prior->Y);
            heapify(max_prior);
        }
    }

    ll cnt(node* treap) {
        return treap ? treap->cnt : 0;
    }

    void upd_cnt(node* treap) {
        treap->cnt = cnt(treap->sx) + cnt(treap->dx) + 1;
    }

    void split(node* treap, ll X, node* &L, node* &R) {
        if (!treap) {
            L = nullptr;
            R = nullptr;
            return;
        }
        if (cnt(treap->sx) >= X) {
            split(treap->sx, X, L, treap->sx);
            R = treap;
        }
        else {
            split(treap->dx, X - cnt(treap->sx) - 1, treap->dx, R);
            L = treap;
        }
        upd_cnt(treap);
    }

    void merge(node* treap_L, node* treap_R, node* &res) {
        if (!treap_L) {
            res = treap_R;
            return;
        }
        if (!treap_R) {
            res = treap_L;
            return;
        }
        if (treap_L->Y > treap_R->Y) {
            merge(treap_L->dx, treap_R, treap_L->dx);
            res = treap_L;
        }
        else {
            merge(treap_L, treap_R->sx, treap_R->sx);
            res = treap_R;
        }
        upd_cnt(res);
    }

    node* search(node* treap, ll X) {
        if (!treap) return nullptr;
        if (cnt(treap->sx) == X) return treap;
        if (cnt(treap->sx) > X) return search(treap->sx, X);
        if (cnt(treap->sx) < X) return search(treap->dx, X - cnt(treap->sx) - 1);
        return nullptr;

    }

    void sposta(node* &treap, ll a, ll b) {
        node* L; node* M; node* R;
        split(treap, a, L, M);
        split(M, 1, M, R);
        merge(L, R, treap);

        split(treap, b, L, R);
        merge(L, M, treap);
        merge(treap, R, treap);
    }

    // void output(node* treap) {
    //     if (!treap) return;
    //     output(treap->sx);
    //     cout << treap->info << " ";
    //     output(treap->dx);
    // }
};

int main()  {
    ios_base::sync_with_stdio(0); cin.tie(0);
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int N, M; cin >> N >> M;
    treap t(N);

    while (M --) {
        char q; cin >> q;

        if (q == 'c') {
            int x; cin >> x;
            node* nodo = t.search(t.root, x);
            cout << nodo->info << " ";
        }
        else {
            int a, b; cin >> a >> b;
            t.sposta(t.root, a, b);
        }
    }
}
