#include <bits/stdc++.h>

using namespace std;

bool heights(int n, vector<int>z, vector<int>&h) {
    vector<int>h1(n);
    vector<int>h2(n);
    h1[n-1]=1e9;
    h2[0]=1e9;
    for (int i=0;i<n-1;i++) h1[i]=z[i];
    for (int i=0;i<n-1;i++) h2[i+1]=z[i];
    vector<int> hres(n);
    for (int i=0;i<n;i++) hres[i]=min(h1[i],h2[i]);
    for (int i=0;i<n-1;i++) {
        if (max(hres[i],hres[i+1])!=z[i]) return false;
    }
    h = hres;
    return true;
}
