#include <bits/stdc++.h>

using namespace std;

int boss(int n, vector<int>&link) {
    if (link[n] == n) return n;
    return link[n] = boss(link[n],link);
}

void merge(int n, int m, vector<int>&link, vector<int>&size, vector<int>&dx) {
    n = boss(n,link);
    m = boss(m,link);
    if (n == m) return;
    // n ha size maggiore
    if (size[n] < size[m]) swap(n,m);
    link[m]=n;
    size[n] += size[m];
    dx[n] = max(dx[n],dx[m]);
}

void Colora(int n, int q, vector <int> &a, vector <int> &b, vector <int> &c, vector <int> &murale){
    vector<bool> v(n,0);
    vector<int> link(n,0);
    for (int i=0;i<n;i++) link[i]=i;
    vector<int> size(n,1);
    vector<int> dx(n,0);
    for (int i=0;i<n;i++) dx[i]=i+1;

    for (int i=q-1;i>=0;i--) {
        int lb = a[i];
        int rb = b[i];
        int reference = lb;
        while (lb<=rb) {
            if (!v[lb]) {
                v[lb] = 1;
                murale[lb] = c[i];
            }
            merge(lb,reference,link,size,dx);
            lb = dx[boss(lb,link)];
            
        }
        if (a[i]-1 >= 0 && v[a[i]-1]) merge(reference,a[i]-1,link,size,dx);
        if (b[i]+1 < n && v[b[i]+1]) merge(reference,b[i]+1,link,size,dx);
    }
}
