#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e5 + 5;
constexpr int SQ = 300;
constexpr int LOG = 18;
constexpr int MAXV = 1e6 + 5;
constexpr int PW = 131072;
constexpr int PRIMES = 78499;
int N;

bool sieve[MAXV];
int inv_primes[MAXV];
vector<int> primes;
int primes_freq[PRIMES];

vector<int> adj[MAXN];
int v[MAXN];
int p[MAXN], depth[MAXN];
int binlift[LOG][MAXN];

vector<int> treearray;
pair<int, int> inv_treearray[MAXN];
bool visitato[MAXN];

struct segment {
    vector<int> seg;

    segment() {
        seg.assign(2 * PW, 0);
    }

    void update(int x, int d) {
        x += PW;
        while (x >= 1) {
            seg[x] += d;
            x /= 2;
        }
    }

    int first_zero() {
        int i = 1;
        int l = 0;
        int r = PW;
        while (r - l > 1) {
            // se a sinistra non è tutto riempito (c'è uno zero)
            if (seg[2 * i] < (l + r) / 2 - l) {
                r = (l + r) / 2;
                i = 2 * i;
            }
            else {
                l = (l + r) / 2;
                i = 2 * i + 1;
            }
        }
        return l;
    }
};

segment seg;

void build_sieve() {
    fill(sieve, sieve + MAXV, 1);
    for (int i = 2; i < MAXV; i ++) {
        if (sieve[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < MAXV; j += i) {
                sieve[j] = 0;
            }
        }
    }
    for (int i = 0; i < primes.size(); i ++) inv_primes[primes[i]] = i;
}

void dfs(int u) {
    treearray.push_back(u);
    inv_treearray[u].first = treearray.size() - 1;
    for (auto x : adj[u]) {
        if (x == p[u]) continue;
        depth[x] = depth[u] + 1;
        p[x] = u;
        dfs(x);
    }
    treearray.push_back(u);
    inv_treearray[u].second = treearray.size() - 1;
}

void build_tree() {
    p[1] = 0; depth[1] = 0;
    dfs(1);

    for (int i = 1; i <= N; i ++) binlift[0][i] = p[i];
    for (int pw = 1; pw < LOG; pw ++) {
        for (int i = 1; i <= N; i ++) {
            binlift[pw][i] = binlift[pw - 1][binlift[pw - 1][i]];
        }
    }
}

int lca(int a, int b) {
    // a deve essere più in basso
    if (depth[a] < depth[b]) swap(a, b);
    // salgo a fino a b
    for (int pw = LOG - 1; pw >= 0; pw --) {
        if (depth[binlift[pw][a]] >= depth[b]) a = binlift[pw][a];
    }
    // uno dei due è l'lca
    if (a == b) return a;
    // salgo finché sono diversi
    for (int pw = LOG - 1; pw >= 0; pw --) {
        if (binlift[pw][a] != binlift[pw][b]) {
            a = binlift[pw][a];
            b = binlift[pw][b];
        }
    }
    // quello subito sopra (così sono uguali) è l'lca
    return p[a];
}

bool mo_sort(pair<int, int> &a, pair<int, int> &b) {
    // if (a.first / SQ != b.first / SQ) return a < b;
    // if ((a.first / SQ) % 2) return a.second < b.second;
    if ((a.first >> 9) != (b.first >> 9)) return a < b;
    if ((a.first >> 9) & 1) return a.second < b.second;
    return a.second > b.second;
}

bool comp(pair<pair<int,int>, int> &a, pair<pair<int,int>, int> &b) {
    return mo_sort(a.first, b.first);
}

void update_mo(int idx) {
    int nodo = treearray[idx];
    int num = v[nodo];

    if (!visitato[nodo]) {
        if (sieve[num]) primes_freq[inv_primes[num]] ++;
        if (sieve[num] && primes_freq[inv_primes[num]] == 1) {
            seg.update(inv_primes[num], 1);
        }
        visitato[treearray[idx]] = 1;
    }
    else {
        if (sieve[num]) primes_freq[inv_primes[num]] --;
        if (sieve[num] && primes_freq[inv_primes[num]] == 0) {
            seg.update(inv_primes[num], -1);
        }
        visitato[treearray[idx]] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i ++) cin >> v[i];
    for (int i = 0; i < N - 1; i ++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    build_sieve();
    build_tree();

    int Q; cin >> Q;
    vector<pair<pair<int,int>, int>> queries(Q);
    vector<int> res(Q);
    for (int i = 0; i < Q; i ++) {
        int a, b; cin >> a >> b;
        int pos_a_start = inv_treearray[a].first;
        int pos_a_end = inv_treearray[a].second;
        int pos_b_start = inv_treearray[b].first;
        int pos_b_end = inv_treearray[b].second;
        pair<int, int> range = min(make_pair(pos_a_end, pos_b_start), make_pair(pos_b_end, pos_a_start));
        queries[i] = {range, i};
    }

    sort(queries.begin(), queries.end(), comp);

    int sx = 0;
    int dx = -1;
    fill(visitato, visitato + MAXN, 0);
    fill(primes_freq, primes_freq, 0);
    for (auto [q, i] : queries) {

        auto [pos_a, pos_b] = q;
        int a = treearray[pos_a];
        int b = treearray[pos_b];

        while (sx < pos_a) {
            update_mo(sx);
            sx ++;
        }
        while (sx > pos_a) {
            sx --;
            update_mo(sx);
        }

        while (dx < pos_b) {
            dx ++;
            update_mo(dx);
        }
        while (dx > pos_b) {
            update_mo(dx);
            dx --;
        }

        int l = lca(a, b);
        int pos_l = inv_treearray[l].first;
        
        // includo l'lca
        update_mo(pos_l);

        res[i] = primes[seg.first_zero()];

        // tolgo l'lca
        update_mo(pos_l);
    }

    for (auto x : res) cout << x << '\n';
}
