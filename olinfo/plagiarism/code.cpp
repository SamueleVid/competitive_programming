#include <bits/stdc++.h>

using namespace std;

struct nota {
    int d, p;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, v; cin >> n >> v;
    vector<nota>a(n);
    vector<nota>b(n);
    for (auto &[d,p]:a) cin >> d >> p;
    for (auto &[d,p]:b) cin >> d >> p;

    int lb;
    int rb;
    for (lb = 0;lb<n;lb++) {
        auto [d1, p1] = a[lb];
        auto [d2, p2] = b[lb];
        if (d1 == d2 && p1 == p2) continue;
        break;
    }
    for (rb = n-1;rb>=0;rb--) {
        auto [d1, p1] = a[rb];
        auto [d2, p2] = b[rb];
        if (d1 == d2 && p1 == p2) continue;
        break;
    }

    if (rb < lb) {
        cout << "SAME" << endl;
        return 0;
    }
    a = vector<nota>(a.begin()+lb, a.begin()+rb+1);
    b = vector<nota>(b.begin()+lb, b.begin()+rb+1);
    int l = a.size();

    int fai_al_contrario = false;

    int diff = a[0].p - b[0].p;
    for (int i=1;i<l;i++) {
        if (a[i].p-b[i].p != diff) {
            fai_al_contrario = true;
            break;
        }
    }
    if (fai_al_contrario) reverse(b.begin(), b.end());

    diff = a[0].p - b[0].p;
    for (int i=1;i<l;i++) {
        if (a[i].p-b[i].p != diff) {
            cout << "ORIGINAL " << l << endl;
            return 0;
        }
    }

    int ratio;
    if (a[0].d == b[0].d) {
        ratio = 1;
    }
    else {
        // a > b
        if (a[0].d < b[0].d) swap(a,b);
        if (b[0].d == 0) {
            cout << "ORIGINAL " << l << endl;
            return 0;
        }
        if (a[0].d%b[0].d != 0) {
            cout << "ORIGINAL " << l << endl;
            return 0;
        }
        ratio = a[0].d/b[0].d;
        // non è una potenza di due
        if (!(ratio != 0 && ((ratio & (ratio-1)) == 0))) {
            cout << "ORIGINAL " << l << endl;
            return 0;
        }
    }

    for (int i=1;i<l;i++) {
        if (ratio == 1) {
            if (a[i].d != b[i].d) {
                cout << "ORIGINAL " << l << endl;
                return 0;  
            }
        }
        else {
            if (b[i].d == 0) {
                if (a[i].d == 0) continue;
                cout << "ORIGINAL " << l << endl;
                return 0;
            }
            if (a[i].d%b[i].d != 0) {
                cout << "ORIGINAL " << l << endl;
                return 0;
            }
            if (a[i].d/b[i].d != ratio) {
                cout << "ORIGINAL " << l << endl;
                return 0;
            }
        }
        
    }

    cout << "TRANSFORMED " << l << endl;
}
