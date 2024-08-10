#include <bits/stdc++.h>
#define ll long long
using namespace std;

void add(int x, int k, vector<int>&fw, int n) {
    while (x<=n) {
        fw[x] += k;
        x += x&-x;
    }
}

ll sum(int x, vector<int>&fw) {
    int s = 0;
    while (x>0) {
        s += fw[x];
        x -= x&-x;
    }
    return s;
}

bool comp(vector<int>&a, vector<int>&b) {
    return a[0] > b[0];
}

void solve() {
    int n; cin >> n;
    vector<ll>v(n);
    for (auto &x:v) cin >> x;
    
    vector<int>nums(n);
    for (int i=0;i<n;i++) {
        int id = n-i;
        for (int j=1;j<=n-i;j++) {
            if (v[i+j-1]%j) {
               id = j-1;
               break;
            }
        }
        nums[i]=id;
    }    
    
    int q; cin >> q;
    vector<vector<int>>queries(q);
    for (int i=0;i<q;i++) {
        int a,b; cin >> a >> b;
        queries[i]={a,b,i};
    }
    sort(queries.begin(), queries.end(),comp);
    vector<int>sols(q);
    
    vector<int>fw(n+1);
    
    int to_process=n-1;
    for (int i=0;i<q;i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        int id = queries[i][2];
        a --; b --;
        while (to_process >= a) {
            for (int j=to_process;j<to_process+nums[to_process];j++) {
                add(j+1,1,fw,n);
            }
            to_process --;
        }
        sols[id] = sum(b+1,fw);
    }
    
    for (auto x : sols) cout << x << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
