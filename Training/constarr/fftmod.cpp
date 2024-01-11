#include <bits/stdc++.h>
#define ll long long
#define cx complex<double>
#define mod 1000000007
#define sqrtmod 31622
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

vector<ll> convolution(vector<ll>&a, vector<ll>&b, int n, int m) {
    int size = 1<<(int)ceil(log2(n+m-1));
    
    vector<cx>a_pol(size),b_pol(size);
    for (int i=0;i<n;i++) a_pol[i]=a[i];
    for (int i=0;i<m;i++) b_pol[i]=b[i];
    
    vector<cx>a_pts = fft(a_pol, size, 0);
    vector<cx>b_pts = fft(b_pol, size, 0);
    
    vector<cx>c_pts(size);
    for (int i=0;i<size;i++) c_pts[i] = a_pts[i] * b_pts[i];

    vector<cx>c_pol = fft(c_pts, size, 1);
    vector<ll>c(n+m-1);    
    for (int i=0;i<n+m-1;i++) c[i] = c_pol[i].real() / size + 0.5;
        
    return c;
}

vector<ll> convolution_mod(vector<ll>&a, vector<ll>&b, int n, int m) {
    // a = a_small + sqrtmod(a_large)
    vector<ll>a_small(n), a_large(n), b_small(m), b_large(m);
    for (int i=0;i<n;i++) {
        a_small[i] = a[i] % sqrtmod;
        a_large[i] = a[i] / sqrtmod;
    }
    for (int i=0;i<m;i++) {
        b_small[i] = b[i] % sqrtmod;
        b_large[i] = b[i] / sqrtmod;
    }
    // c = (a_s + (sqrtmod)a_l)*(b_s + (sqrtmod)b_l)  with "*" meaning convolution
    // c = a_s*b_s + sqrtmod(a_s*b_l) + sqrtmod(a_l*b_a) + sqrtmod^2(a_l * b_l)
    vector<ll>asbs = convolution(a_small, b_small, n, m);
    vector<ll>asbl = convolution(a_small, b_large, n, m);
    vector<ll>albs = convolution(a_large, b_small, n, m);
    vector<ll>albl = convolution(a_large, b_large, n, m);
    for (auto &x:asbs) x %= mod;
    for (auto &x:asbl) x %= mod;
    for (auto &x:albs) x %= mod;
    for (auto &x:albl) x %= mod;
    
    vector<ll>c(n+m-1,0);
    for (int i=0;i<n+m-1;i++) {
        c[i] += asbs[i];
        c[i] %= mod;
        c[i] += (sqrtmod * asbl[i]) % mod;
        c[i] %= mod;
        c[i] += (sqrtmod * albs[i]) % mod;
        c[i] %= mod;
        c[i] += (sqrtmod * sqrtmod * albl[i]) % mod;
        c[i] %= mod;
    }
    
    return c;
} 

vector<ll> merge(vector<ll>&a, vector<ll>&b, int m) {
    vector<ll>c = convolution_mod(a, b, m, m);
    vector<ll>res(m,0);
    for (int i=0;i<c.size();i++) {
        int j = i<m ? i : i-m;
        res[j] += c[i];
        res[j] %= mod;   
    }
    return res;
}

vector<ll> fastpow(vector<ll>&a, vector<ll>&start, ll n, int m) {
    if (n == 1) return start;
    vector<ll>res = fastpow(a,start,n/2,m);
    res = merge(res,res,m);
    if (n%2) res = merge(res,start,m);
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    ll n; cin >> n;
    int m; cin >> m;
    ll l, r; cin >> l >> r;
    int k; cin >> k;

    vector<ll>start(m,0);
    vector<ll>curr(m,0);

    for (int i=l;i<l+m&&i<=r;i++) {
        curr[i%m] = start[i%m] = ceil((double)(r-i+1)/m);
    }
    
    curr = fastpow(curr, start, n, m);
    
    cout << curr[k] << '\n';
}
