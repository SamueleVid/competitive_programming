#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int q; cin >> q;
    for (int qq=0;qq<q;qq++) {
        int a; cin >> a;

        int res1 = vector<int>{a,1,a+1,0}[a%4];

        int res2;
        if (a%2==0) res2 = (1 << (int)(log2(a)+1)) - 1;
        else res2 = a;

        cout << res1 << " " << res2 << "\n";
    }
}
