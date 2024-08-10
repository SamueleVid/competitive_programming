#include <bits/stdc++.h>
using namespace std;

int sign(long long x) {
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

long long revenue(int n, int k, vector<long long> v) {
    vector<pair<long long,int>> abs_sorted(n);
    for (int i=0;i<n;i++) abs_sorted[i] = {abs(v[i]),sign(v[i])};
    sort(abs_sorted.begin(), abs_sorted.end());
    
    int m = -k;
    for (auto x:v) m+=sign(x);
    
    long long max_height = 0;
    long long height = 0;
    long long before = 0;
    int how_many = 0;
    for (auto [a,b] : abs_sorted) {
        
        if (before != a) {

            m -= how_many;
            height += m*(a-before);
            max_height = max(max_height, height);

            how_many = 0;
            before = a;
        }
        how_many += b;
    }
    
    return max_height;    
}
