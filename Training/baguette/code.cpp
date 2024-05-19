#include <bits/stdc++.h>
using namespace std;
const int abc = 26;

int affetta(int n, int k, string s) {
    vector<int>v(n);
    for (int i=0;i<n;i++) {
        v[i] = s[i]-'a';
    }
    int res = n;
    for (int l = 0; l < abc; l ++) {
        int curr_res = 0;
        for (int i=0;i<n;i++) {
            if (v[i] != l) {
                i += k-1;
                curr_res ++;
            }
        }
        res = min(res, curr_res);
    }
    return res;
}
