#include <bits/stdc++.h>
#define cx complex<double>
using namespace std;

vector<cx> fft(vector<cx>pol, int n, bool ifft) {
    if (n == 1) return pol;
    
    vector<cx>pol_e(n/2), pol_o(n/2);
    for (int i=0;i<n;i++) {
        if (i%2) pol_o[(i-1)/2]=pol[i];
        else pol_e[i/2]=pol[i];
    }
    
    vector<cx>pts_e = fft(pol_e, n/2, ifft);
    vector<cx>pts_o = fft(pol_o, n/2, ifft);
    vector<cx>pts(n);
    
    cx k = ifft ? -1 : 1;
    cx u = exp(k*2i*(M_PI/n));
    cx x = 1;
    for (int i=0;i<n;i++) {
        int j = i<n/2 ? i : i-n/2;
        pts[i] = pts_e[j] + x*pts_o[j];
        x *= u;
    }

    return pts;
}

vector<int> convolution(vector<int>&a, vector<int>&b, int n, int m) {
    int size = 1<<(int)ceil(log2(n+m-1));
    
    vector<cx>a_pol(size),b_pol(size);
    for (int i=0;i<n;i++) a_pol[i]=a[i];
    for (int i=0;i<m;i++) b_pol[i]=b[i];
    
    vector<cx>a_pts = fft(a_pol, size, 0);
    vector<cx>b_pts = fft(b_pol, size, 0);
    
    vector<cx>c_pts(size);
    for (int i=0;i<size;i++) c_pts[i] = a_pts[i] * b_pts[i];

    vector<cx>c_pol = fft(c_pts, size, 1);
    
    vector<int>c(n+m-1);    
    for (int i=0;i<n+m-1;i++) c[i] = c_pol[i].real() / size + 0.5;
    
    return c;
} 

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int>a(n), b(m);
    for (auto &x:a) cin >> x;
    for (auto &x:b) cin >> x;
    
    reverse(b.begin(), b.end());
    
    vector<int> c = convolution(a,b,n,m);
    for (auto x : c) cout << x << " ";
}
