#include <bits/stdc++.h>

using namespace std;

struct info{
    int first;
    int last;
    long long sum;
    int l;
    int r;
};

bool operator==(info &a, info &b) {
    return (a.first == b.first
            && a.last == b.last
            && a.sum == b.sum);
}

void maxinit(vector<int>&segtree, vector<int>&v, int n) {
    for (int i=0;i<n;i++) segtree[n+i] = v[i];
    for (int i=n-1;i>=1;i--) segtree[i] = max(segtree[2*i], segtree[2*i+1]);
}

void maxupdate(int i, int value, vector<int>&segtree, int n) {
    i += n;
    segtree[i] = value;
    i /= 2;
    while (i >= 1) {
        segtree[i] = max(segtree[2*i], segtree[2*i+1]);
        i /= 2;
    }
}

int maxquery(int l, int r, vector<int>&segtree, int n) {
    l += n;
    r += n;
    int res = 0;
    while (l <= r) {
        if (l%2==1) {
            res = max(res, segtree[l]);
            l ++;
        }
        if (r%2==0) {
            res = max(res, segtree[r]);
            r --;
        }
        l /= 2;
        r /= 2;
    }
    return res;
}

int first_max(int l, int r, int l1, int r1, int i, int a, vector<int>&maxsegtree, int n) {
    if (maxsegtree[i] <= a) return n;
    if (l1 > r || r1 < l) return n;
    if (i >= n) return l1;
    
    int dx = first_max(l, r, (l1+r1)/2+1, r1, 2*i+1, a, maxsegtree, n);
    if (dx != n) return dx;
    int sx = first_max(l, r, l1, (l1+r1)/2, 2*i, a, maxsegtree, n);
    return sx;
}

long long query_sum(int l, int r, int rb, int i,vector<info>&segtree) {
    long long res = 0;

    while (l<=r) {
        int mid = (l+r)/2;

        if (mid < rb) {
            // vado a dx e sx è sicuro che rimane uguale, quindi lo aggiungo
            res += segtree[i].sum - segtree[2*i+1].sum;
            l = mid+1;
            i = 2*i+1;
        }
        if (rb < mid) {
            r = mid-1;
            i = 2*i;
        }
        if (mid == rb) {
            // tutto il coso sx è giusto e lo aggiungo (va bene anche segtree[2*i].sum)
            res += segtree[2*i].sum;
            break;
        }
    }
    return res;
}

int pos_to_i(int l, int r, int n) {
    l += n;
    r += n;
    return l / (1 << int(log2(r - l + 1)));
}

info merge(info &a, info &b, vector<info>&segtree, vector<int>&maxsegtree, int n) {
    if (a.first <= b.first) {
        return {b.first, b.last, b.sum, a.l, b.r};
    }
    if (a.last > b.first) {
        return {a.first, b.last, a.sum + b.sum, a.l, b.r};
    }
    // find the closest index to the end of the range whose value is greater than b.first 
    // questo sotto si può cambiare
    int rb = first_max(a.l, a.r, 0, n-1, 1, b.first, maxsegtree, n);
    long long sum = query_sum(a.l, a.r, rb, pos_to_i(a.l,a.r,n), segtree);
    return {a.first, b.last, sum+b.sum, a.l, b.r};
}

void init(vector<info>&segtree, vector<int>&v, vector<int>&maxsegtree, int n) {
    for (int i=0;i<n;i++) segtree[n+i] = {v[i],v[i],v[i],i,i};
    for (int i=n-1;i>=1;i--) {
        segtree[i] = merge(segtree[2*i], segtree[2*i+1], segtree, maxsegtree, n);
    }
}

void update(int i, int value, vector<info>&segtree, vector<int>&maxsegtree, int n) {
    i += n;
    segtree[i] = {value, value, value, i-n, i-n};
    int prev = i;
    i /= 2;
    while (i>=1) {
        info vecchio = segtree[i];
        segtree[i] = merge(segtree[2*i], segtree[2*i+1], segtree, maxsegtree, n);
        // constant time upgrade
        if (vecchio == segtree[i]) return;
        int prev = i;
        i /= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, q; cin >> n >> q;
    vector<int>v(n),p(q),s(q);
    for (auto &x:v) cin >> x;
    for (int i=0;i<q;i++) cin >> p[i] >> s[i];

    int n1 = 1<<(int)ceil(log2(n));
    vector<int>v1(n1);
    for (int i=0;i<n;i++) v1[i]=v[i];

    vector<int> maxsegtree(2*n1,0);
    maxinit(maxsegtree,v1,n1);

    vector<info> segtree(2*n1,{0,0,0});
    init(segtree,v1,maxsegtree,n1);

    for (int i=0;i<q;i++) {
        v[p[i]] = s[i];
        maxupdate(p[i],s[i],maxsegtree,n1);
        update(p[i],s[i],segtree,maxsegtree,n1);

        cout << segtree[1].sum << '\n';
    }
}
