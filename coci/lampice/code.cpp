#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    n++;
    m++;
    
    vector<vector<ull>>v(n,vector<ull>(m,0));

    mt19937_64 rand;

    for (int i=0;i<k;i++) {
        int a,b,c,d; cin >> a >> b >> c >> d;
        ull ziopera = rand();
        v[a][b] ^= ziopera;
        v[c][d] ^= ziopera;
    }
    
    vector<vector<ull>>ps(n,vector<ull>(m,0));
    ps[0][0] = v[0][0];
    for (int i=1;i<n;i++) ps[i][0] = ps[i-1][0] ^ v[i][0];
    for (int i=1;i<m;i++) ps[0][i] = ps[0][i-1] ^ v[0][i];
    for (int i=1;i<n;i++) {
        for (int j=1;j<m;j++) {
            ps[i][j] = v[i][j] ^ ps[i-1][j] ^ ps[i][j-1] ^ ps[i-1][j-1];
        }
    }

    long long res = 0;
    for (int up=0;up<n-1;up++) {
        for (int down=up+1;down<n;down++) {
            map<ull, long long>mpp;
            mpp[0]=1;
            queue<ull>q;
            for (int i=0;i<m;i++) {
                ull value = ps[down][i];
                if (up != 0) value ^= ps[up-1][i];

                if (i != 0) res += mpp[value];
                
                if (!q.empty()) {
                    mpp[q.front()]++;
                    q.pop();
                }
                q.push(value);
            }
        }
    }
    
    cout << res << '\n';
}
