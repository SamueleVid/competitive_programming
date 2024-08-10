#include <bits/stdc++.h>

using namespace std;

int kg = 1000000;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    
    vector<vector<int>> p(m,vector<int>(n));
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            cin >> p[i][j];
        }
    }

    vector<int> sums(m);
    for (int i=0;i<m;i++) {
        int sum = 0;
        for (int j=0;j<n;j++) {
            sum += p[i][j];
        }
        sums[i] = sum;
    }

    vector<vector<double>> pkg(m, vector<double>(n));
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            pkg[i][j] = ((double)p[i][j] * kg) / sums[i];
        }
    }

    vector<int> res(n);
    for (int j=0;j<n;j++) {
        double tot = 0;
        for (int i=0;i<m;i++) {
            tot += pkg[i][j];
        }
        tot /= m;
        res[j] = tot;
    }

    for (auto x : res) cout << x << " ";
    cout << endl;
}
