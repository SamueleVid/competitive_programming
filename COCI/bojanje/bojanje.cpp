#include <bits/stdc++.h>
#define ll long long
#define m 1000000007
using namespace std;

ll fastpow(ll a, ll n) {
    if (n == 1) return a;
    ll h = fastpow(a,n/2);
    h *= h;
    h %= m;
    if (n%2) {
        h *= a;
        h %= m;
    }
    return h;
}

vector<vector<ll>> matrixprod(vector<vector<ll>>&a, vector<vector<ll>>&b, int r, int c, int k) {
    vector<vector<ll>>res(r,vector<ll>(c));
    for (int i=0;i<r;i++) {
        for (int j=0;j<c;j++) {
            for (int z=0;z<k;z++) {
                res[i][j] += (a[i][z] * b[z][j])%m;
                res[i][j] %= m;
            }
        }
    }
    return res;
}

vector<vector<ll>> matrixexp(vector<vector<ll>>&a, ll n, int k) {
    if (n == 1) return a;
    vector<vector<ll>> h = matrixexp(a,n/2,k);
    h = matrixprod(h,h,k,k,k);
    if (n%2) h = matrixprod(h,a,k,k,k);
    return h;
}

void generate(int last, int sum, vector<int>&curr, vector<vector<int>>&id_to_partition, int limit) {
    if (sum == limit) {
        id_to_partition.push_back(curr);
        return;
    }
    for (int i=last;i+sum<=limit;i++) {
        curr.push_back(i);
        generate(i,sum+i,curr,id_to_partition,limit);
        curr.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    ll t; cin >> t;
    int k; cin >> k;

    // precalcolo tutte le 42 partizioni di 10
    vector<vector<int>>id_to_partition;
    vector<int>curr;
    generate(1,0,curr,id_to_partition,n);
    int n_part = id_to_partition.size();
    map<vector<int>,int>partition_to_id;
    for (int i=0;i<n_part;i++) partition_to_id[id_to_partition[i]]=i;

    vector<vector<ll>>matrix(n_part,vector<ll>(n_part,0));
    
    for (int j=0;j<n_part;j++) {
        for (int k0=0;k0<id_to_partition[j].size();k0++) {
            for (int k1=0;k1<id_to_partition[j].size();k1++) {
                int casi = id_to_partition[j][k0]*id_to_partition[j][k1];
                vector<int>nuovo;
                for (int k2=0;k2<id_to_partition[j].size();k2++) {
                    int curr = id_to_partition[j][k2];
                    if (k2 == k0) curr ++;
                    if (k2 == k1) curr --;
                    if (curr != 0) nuovo.push_back(curr);
                }
                sort(nuovo.begin(), nuovo.end());
                int i = partition_to_id[nuovo];
                matrix[i][j] += casi;
            } 
        }
    }

    vector<int>start_pos;
    for (int i=0;i<n;i++) start_pos.push_back(1);
    vector<vector<ll>>start(n_part,vector<ll>(1,0));
    start[partition_to_id[start_pos]][0] = 1;

    vector<vector<ll>> exp = matrixexp(matrix, t, n_part);
    vector<vector<ll>> end = matrixprod(exp,start,n_part,1,n_part);

    ll tot = 0;
    ll fav = 0;
    for (int i=0;i<n_part;i++) {
        tot += end[i][0];
        tot %= m;
        int num_colori = id_to_partition[i].size();
        if (num_colori >= k) {
            fav += end[i][0];
            fav %= m;
        }
    }
    
    ll invtot = fastpow(tot, m-2);
    ll res = fav*invtot;
    res %= m;

    cout << res << '\n';
}
