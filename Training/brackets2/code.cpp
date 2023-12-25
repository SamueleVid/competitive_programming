#include <bits/stdc++.h>

using namespace std;

void rec(vector<int>&v, int n, int i, int sum, vector<char>&s, vector<vector<int>>&visited) {
    if (visited[i][sum]) return;
    visited[i][sum] = 1;
    if (i == n) {
        if (sum == 0) {
            for (int j=0;j<n;j++) for (int x=0;x<v[j];x++) cout << s[j];
            exit(0);
        }
        return;
    }
    if ((sum - v[i])>=0) {
        s.push_back(')');
        rec(v,n,i+1,sum-v[i],s,visited);
        s.pop_back();
    }
    s.push_back('(');
    rec(v,n,i+1,sum+v[i],s,visited);
    s.pop_back();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int>v(n);
    for (auto &x:v) cin >> x;
    vector<char>s;
    vector<vector<int>>visited(n+20,vector<int>(50000+20));
    rec(v,n,0,0,s,visited);
    cout << -1 << '\n';
}
