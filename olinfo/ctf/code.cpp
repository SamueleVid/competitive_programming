#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sp " "
#define nl '\n'

ll rec(ll N) {
    if (N == 1) return 1;
    return (rec(N / 2) + N % 2) * 2 - 1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int Q; cin >> Q; 
    while (Q --) {
        ll N; cin >> N;
        cout << rec(N) << nl;
    }
}
