#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct pt{
    ll x, y;

    ll cross(pt &b) {
        return x * b.y - y * b.x;
    }
    pt operator-(pt &b) {
        pt res = {x - b.x, y - b.y};
        return res;
    }
};

struct f {
    ll m, q;

    ll calc(ll x) {
        return m * x + q;
    }
};

ll intersec(f f1, f f2) {
    return (f1.q - f2.q + f2.m - f1.m - 1) / (f2.m - f1.m);
}

ll intersec_2(f f1, f f2) {
    return (f1.q - f2.q) / (f2.m - f1.m);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    
    vector<pt> v(N);
    for (int i = 0; i < N; i ++) {
        ll h; cin >> h;
        v[i] = {i, h};
    }

    // decrescente massimo
    vector<pair<f, int>> func;

    for (int i = 1; i < N; i ++) {
        ll m = v[i].y - v[i - 1].y;
        ll q = v[i].y - m * v[i].x;
        f new_func = {m, q};
        ll inizio = i - 1;
        while (!func.empty() &&
            func.back().first.calc(func.back().second) < new_func.calc(func.back().second)) {
            inizio = func.back().second;
            func.pop_back();
        }
        if (!func.empty()) inizio = min(inizio, intersec(func.back().first, new_func));
        func.push_back({new_func, inizio});
    }

    // crescente massimo
    vector<pair<f, int>> func_2;

    for (int i = N - 2; i >= 0; i --) {
        ll m = v[i + 1].y - v[i].y;
        ll q = v[i].y - m * v[i].x;
        f new_func = {m, q};
        ll inizio = i + 1;
        while (!func_2.empty() &&
            func_2.back().first.calc(func_2.back().second) < new_func.calc(func_2.back().second)) {
            inizio = func_2.back().second;
            func_2.pop_back();
        }
        if (!func_2.empty()) inizio = max(inizio, intersec_2(func_2.back().first, new_func));
        func_2.push_back({new_func, inizio});
    }
    
    vector<ll> res(N);

    int curr_func = 0;
    for (int i = 0; i < N; i ++) {
        while (func.size() > curr_func + 1 && func[curr_func + 1].second == i) {
            curr_func ++;
        }
        res[i] = func[curr_func].first.calc(i) - v[i].y;
    }

    curr_func = 0;
    for (int i = N - 1; i >= 0; i --) {
        while (func_2.size() > curr_func + 1 && func_2[curr_func + 1].second == i) {
            curr_func ++;
        }
        res[i] = max(res[i], func_2[curr_func].first.calc(i) - v[i].y);
    }

    for (auto x : res) cout << x << " ";
    cout << '\n';
}
