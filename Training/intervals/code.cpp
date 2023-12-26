#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<pair<int,int>> v; // start, tipo (-1, 1), id
    for (int i=0;i<n;i++) {
        int a, b; cin >> a >> b;
        v.push_back({a,b});
    }

    sort(v.begin(), v.end());

    vector<bool> visited(n,0);
    int days = 0;

    int pow_two = 1 << (int)(log2(n));

    for (int i=0;i<n;i++) {
        if (visited[i]) continue;
        days ++;
        int k = i;
        int end = v[k].first;
        while (v[k].first == end) {
            visited[k] = 1;
            end = v[k].second;
            k = k;
            for (int jump=pow_two;jump>=1;jump/=2) {
                if (k+jump < n && v[k+jump].first <= end && !(v[k+jump].first == end && visited[k+jump])) {
                    k+=jump; 
                }
            }
        }
    }

    cout << days << endl;
}
