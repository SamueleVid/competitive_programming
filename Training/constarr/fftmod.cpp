#include <bits/stdc++.h>
#define ll long long
#define cx complex<double>
#define mod 1000000007
#define sqrtmod 31622
using namespace std;

vector<cx> fft(vector<cx>&pol, int n, bool ifft) {
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

vector<ll> convolution_mod(vector<ll>&a, vector<ll>&b, int n, int m) {
    int size = 1<<(int)ceil(log2(n+m-1));
    
    // a[i] = a_s[i] + (sqrtmod)(a_l[i])
    vector<cx>a_s(size),a_l(size),b_s(size),b_l(size);
    for (int i=0;i<n;i++) a_s[i]=(ll)(a[i] % sqrtmod);
    for (int i=0;i<n;i++) a_l[i]=(ll)(a[i] / sqrtmod);
    for (int i=0;i<m;i++) b_s[i]=(ll)(b[i] % sqrtmod);
    for (int i=0;i<m;i++) b_l[i]=(ll)(b[i] / sqrtmod);
    
    a_s = fft(a_s, size, 0);
    a_l = fft(a_l, size, 0);
    b_s = fft(b_s, size, 0);
    b_l = fft(b_l, size, 0);

    // c = (a_s + sqrtmod(a_l))*(b_s + sqrtmod(b_l)) with "*" meaning convolution
    // c = a_s*b_s + sqrtmod(a_s*b_l + a_l*b_s) + sqrtmod^2(a_l*b_l)
    vector<cx>c_ss(size),c_sl(size),c_ll(size);
    for (int i=0;i<size;i++) c_ss[i] = a_s[i] * b_s[i];
    for (int i=0;i<size;i++) c_sl[i] = a_s[i] * b_l[i] + a_l[i] * b_s[i];
    for (int i=0;i<size;i++) c_ll[i] = a_l[i] * b_l[i];

    c_ss = fft(c_ss, size, 1);
    c_sl = fft(c_sl, size, 1);
    c_ll = fft(c_ll, size, 1);
    
    for (int i=0;i<n+m-1;i++) c_ss[i] = c_ss[i].real() / size + 0.5;
    for (int i=0;i<n+m-1;i++) c_sl[i] = c_sl[i].real() / size + 0.5;
    for (int i=0;i<n+m-1;i++) c_ll[i] = c_ll[i].real() / size + 0.5;
        
    vector<ll>c(n+m-1,0);
    for (int i=0;i<n+m-1;i++) {
        c[i] += (ll)c_ss[i].real() % mod;
        c[i] %= mod;
        c[i] += (sqrtmod * ((ll)c_sl[i].real() % mod)) % mod;
        c[i] %= mod;
        c[i] += (sqrtmod * sqrtmod * ((ll)c_ll[i].real() % mod)) % mod;
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
