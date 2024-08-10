#include <bits/stdc++.h>
#define ll long long

using namespace std;

struct point{
    ll x,y;
};

bool compy(point &a, point &b) {
    return a.y>b.y;
}

void init_segtree(vector<ll>&dx_segtree, vector<ll>&sx_segtree, vector<ll>&dx_v, vector<ll>&sx_v, int n, int n_pw) {
    for (int i=0;i<n;i++) {
        dx_segtree[n_pw+i] = dx_v[i];
        sx_segtree[n_pw+i] = sx_v[i];
    }
    for (int i=n_pw-1;i>=1;i--) {
        dx_segtree[i] = min(dx_segtree[2*i], dx_segtree[2*i+1]);
        sx_segtree[i] = max(sx_segtree[2*i], sx_segtree[2*i+1]);
    }
}

ll query_segtree(vector<ll>&dx_segtree, vector<ll>&sx_segtree, int l, int r, int n, int grid) {
    // l rappresenta il muro alto e r il muro basso.
    // Bisogna trovare i limiti destri e sinistri INTERNI, dunque quelli da l+1 a r-1 inclusi.
    // Una volta trovati sx e dx bisogna considerare la larghezza INTERNA, quindi (dx-1) - (sx+1) + 1 = dx-sx-1
    l ++; r --;
    l += n; r += n;
    // Inizializzo i sx e dx con la massima base, perché nel caso l'altezza sia zero allora non ci sono
    // muri che delimitano il sx e dx e allora la base è massima.
    ll max_sx = 0;
    ll min_dx = grid+1;
    while (l<=r) {
        if (l%2==1) {
            max_sx = max(max_sx, sx_segtree[l]);
            min_dx = min(min_dx, dx_segtree[l]);
            l ++;
        }
        if (r%2==0) {
            max_sx = max(max_sx, sx_segtree[r]);
            min_dx = min(min_dx, dx_segtree[r]);
            r --;
        }
        l /= 2;
        r /= 2;
    }
    // chiaramente se è negativo (cioé quando i muri di dx e sx coincidono con il topo)
    // allora spazio in mezzo è zero
    return max(0ll, min_dx - max_sx - 1);
}

pair<string,ll> solve(ll n, point topo, int g, vector<point>&gatti) {
    ll res = n+1;
    ll res1 = -1;
    
    // provo a far scappare il topo in tutte le direzioni. Se non riesce a scappare mi calcolo il tempo massimo
    // che riesce a perdere provando a scappare verso l'uscita, che non si riesce a calcolare con il metodo
    // successivo per il risultato CAUGHT

    // con sx, dx o up, down indico quando riuscirebbero a spostarsi dall'altra parte nel tempo che il topo
    // raggiunge il fondo. Se i gatti da ambo le parti non lasciano spazio al topo di scappare allora viene
    // sicuramente catturato. Si prova per tutte e 4 le direzioni.

    // nord
    ll dist_bordo = n-topo.y;
    ll sx = 1;
    ll dx = n;
    for (auto [x,y]:gatti) {
        if (y < topo.y) continue;
        if (x <= topo.x) sx = max(sx, x+dist_bordo+1);
        if (x >= topo.x) dx = min(dx, x-dist_bordo-1);
    }

    if (sx <= dx) res = min(res, dist_bordo);
    else res1 = max(res1, (dx-sx+2*dist_bordo+2)/2);

    // sud
    dist_bordo = topo.y-1;
    sx = 1;
    dx = n;
    for (auto [x,y]:gatti) {
        if (y > topo.y) continue;
        if (x <= topo.x) sx = max(sx, x+dist_bordo+1);
        if (x >= topo.x) dx = min(dx, x-dist_bordo-1);
    }

    if (sx <= dx) res = min(res, dist_bordo);
    else res1 = max(res1, (dx-sx+2*dist_bordo+2)/2);

    // est
    dist_bordo = n-topo.x;
    ll up = n;
    ll down = 1;
    for (auto [x,y]:gatti) {
        if (x < topo.x) continue;
        if (y <= topo.y) down = max(down, y+dist_bordo+1);
        if (y >= topo.y) up = min(up, y-dist_bordo-1);
    }

    if (down <= up) res = min(res, dist_bordo);
    else res1 = max(res1, (up-down+2*dist_bordo+2)/2);

    // ovest
    dist_bordo = topo.x-1;
    up = n;
    down = 1;
    for (auto [x,y]:gatti) {
        if (x > topo.x) continue;
        if (y <= topo.y) down = max(down, y+dist_bordo+1);
        if (y >= topo.y) up = min(up, y-dist_bordo-1);
    }

    if (down<=up) res = min(res, dist_bordo);
    else res1 = max(res1, (up-down+2*dist_bordo+2)/2);

    if (res != n+1) return {"ESCAPED",res};
    // ------------------------------------------------------

    // Ordino i gatti dal più alto al più basso
    sort(gatti.begin(), gatti.end(), compy);
    vector<ll> ys;
    vector<ll> min_dx;
    vector<ll> max_sx;
    ys.push_back(n+1);
    min_dx.push_back(n+1);
    max_sx.push_back(0);
    int size = 1;
    for (auto [x,y] : gatti) {
        if (y != ys[size-1]) {
            size ++;
            ys.push_back(y);
            min_dx.push_back(n+1);
            max_sx.push_back(0);
        }
        // Minimizzo lo spazio in mezzo, dove c'è il topo.
        // Se è sopra il topo (x coincide con topo.x) la distanza viene -1 negativa ma viene fixata.
        if (x >= topo.x) min_dx[size-1] = min(x,min_dx[size-1]);
        if (x <= topo.x) max_sx[size-1] = max(x,max_sx[size-1]);
    }
    if (0 != ys[size-1]) {
        size ++;
        ys.push_back(0);
        min_dx.push_back(n+1);
        max_sx.push_back(0);
    }

    // Inizializzo i segtree
    int size_pw = 1<<(int)ceil(log2(size));
    vector<ll> dx_segtree(2*size_pw), sx_segtree(2*size_pw);
    init_segtree(dx_segtree, sx_segtree, min_dx, max_sx, size, size_pw);

    int topo_index = 0;
    for (int i=0;ys[i]>=topo.y;i++) topo_index = i;
    topo_index ++;
    
    for (int i=0;ys[i]>topo.y;i++) {
        // faccio una BSA per trovare il limite basso con risultato maggiore
        int k = topo_index;
        for (int pw=1<<(int)log2(size);pw>=1;pw/=2) {
            if (pw+k >= size) continue;
            // All'alzarsi della base l'altezza diminuisce, la dovendo ragionare con meno gatti la base aumenta.
            // Il punto dove il minore dei due è maggiore e quando si intersecano.
            ll lenght = query_segtree(dx_segtree, sx_segtree, i, pw+k, size_pw, n);
            ll height = ys[i] - ys[pw+k] - 1;
            if (lenght > height) k += pw;
        }

        // Controllo per quello subito > e per quello subito <= 
        ll lato = 0;
        ll lenght, height;
        lenght = query_segtree(dx_segtree, sx_segtree, i, k, size_pw, n);
        height = ys[i] - ys[k] - 1;
        lato = max(lato, min(lenght, height));
        if (k+1 < size) {
            k ++;
            lenght = query_segtree(dx_segtree, sx_segtree, i, k, size_pw, n);
            height = ys[i] - ys[k] - 1;
            lato = max(lato, min(lenght, height));
        }

        ll sol = ceil(double(lato)/2);
        if (sol > res1) res1 = sol;
    }
    return {"CAUGHT",res1};
}

int main() {
    ios_base::sync_with_stdio(false);
    ll n; cin >> n;
    int t; cin >> t;
    for (int tt=0;tt<t;tt++) {
        point topo; cin >> topo.y >> topo.x;
        int g; cin >> g;
        vector<point>gatti(g);
        for (auto &[x,y]:gatti) cin >> y >> x;
        auto [res1, res2] = solve(n,topo,g,gatti);
        cout << res1 << " " << res2 << '\n';
    }
}
