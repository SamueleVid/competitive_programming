#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct num {
    // primes has max 7 keys, as the 
    // inverse primorial of MAXV 1e6 is 7
    map<int,int> primes;
    ll value;
    
    void pulisci() {
        value = 1;

        vector<int> to_erase;
        for (auto &[p,k] : primes) {
            k %= 4;
            for (int j = 0; j < k; j ++) value *= p;
            if (!k) to_erase.push_back(p);
        }
        for (auto p : to_erase) primes.erase(p);
    }

    num(int n) {
        primes = {};
        // O(sqrtN)
        for (int i = 2; i * i <= n; i ++) {
            while (n % i == 0) {
                primes[i] ++;
                n /= i;
            }
        }
        if (n != 1) primes[n] ++;
        pulisci();
    }
    num(map<int,int> primes_) {
        primes = primes_;
    }
    num() {
        primes = {};
    }
    
    num operator*(num b) {
        num res(primes);
        for (auto &[p,k] : b.primes) {
            res.primes[p] += k;
        }
        res.pulisci();
        return res;
    }
    
    ll inv() {
        ll res = value;
        for (auto &[p,k] : primes) {
            if (k == 1) res *= p * p;
            if (k == 3) res /= p * p;
        }
        return res;
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N; cin >> N;
    vector<int> V(N);
    for (auto &x : V) cin >> x;
    
    vector<num> A(N);
    for (int i = 0; i < N; i ++) A[i] = num(V[i]);
    
    ll res = 0;
    map<ll, ll> m;
    m[(A[0] * A[1]).inv()] = 1;
    
    // O(N^2logN)
    for (int i = 2; i < N; i ++) {
        for (int j = i + 1; j < N; j ++) {
            res += m[(A[i] * A[j]).value];
        }
        for (int j = 0; j < i; j ++) {
            m[(A[i] * A[j]).inv()] ++;
        }
    }
	
    cout << res << '\n';
}
