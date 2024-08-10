#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll m = 1e9+7;

int find(vector<int>&link, int n) {
    if (link[n] == n) return n;
    return link[n] = find(link,link[n]);
}

void merge(vector<int>&link, vector<int>&size, int a, int b) {
    int a1 = find(link, a);
    int b1 = find(link, b);
    if (size[b1] > size[a1]) swap(a1,b1);
    link[b1]=a1;
    size[a1] += size[b1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int r, c, n; cin >> r >> c >> n;
    map<int, int>row,col,diag1,diag2;
    //diag1 = rr - cc, diag2 = rr + cc
    int x,y;
    vector<int>link(n);
    for (int i=0;i<n;i++) link[i]=i;
    vector<int>size(n,1);
    for (int i=0;i<n;i++) {
        int rr, cc; cin >> rr >> cc;

        if (row.count(rr)) merge(link,size,i,row[rr]);
        else row[rr]=i;
        if (col.count(cc)) merge(link,size,i,col[cc]);
        else col[cc]=i;
        if (diag1.count(rr-cc)) merge(link,size,i,diag1[rr-cc]);
        else diag1[rr-cc]=i;
        if (diag2.count(rr+cc)) merge(link,size,i,diag2[rr+cc]);
        else diag2[rr+cc]=i;
    }

    ll res = 1;
    vector<int>v(n);
    for (int i=0;i<n;i++) {
        int k = find(link,i);
        if (v[k]) continue;
        v[k] = 1;
        res *= 2;
        res %= m;
    }

    cout << res << '\n';
}
