#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct pt {
    ll x;
    ll y;

    ll norm() {
        return x * x + y * y;
    }

    bool half() {
        return y > 0 || (y == 0 && x < 0);
    }

    pt operator-(pt b) {
        return {x - b.x, y - b.y};
    }
};

ll cross(pt a, pt b) {
    return a.x * b.y - a.y * b.x;
}

bool same_line(pt &a, pt &b) {
    return (cross(a, b) == 0) && (a.half() == b.half());
}

bool polar(pt &a, pt &b)  {
    // polar sort
    if (a.half() != b.half()) return a.half() > b.half(); // se l'angolo è > 180 si rompe, distinguo due metà
    return cross(a, b) < 0; // a è a sinistra di b (angolo verso destra -> angolo negativo -> seno negativo)
}

bool sweep(pt &a, pt &b)  {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool comp1(pair<pt, int> &a, pair<pt, int> &b) {
    return polar(a.first, b.first);
}

bool comp2(pair<pt, int> &a, pair<pt, int> &b) {
    return sweep(a.first, b.first);
}

vector<int> trovacerchi(int N, vector<int> X, vector<int> Y) {
    // letteralmente convex hull dei centri
    // solo che se due centri sono sulla stessa semiretta (partente da 0)
    // mi tengo quello più lontano

    vector<pt> pts(N);
    for (int i = 0; i < N; i ++) pts[i] = {X[i], Y[i]};

    vector<pair<pt, int>> duplicati(N);
    vector<pair<pt, int>> v;
    for (int i = 0; i < N; i ++) duplicati[i] = {pts[i], i};

    // polar sorto per togliere punti appartenenti a stessa semiretta
    sort(duplicati.begin(), duplicati.end(), comp1);

    for (int i = 0; i < N; i ++) {

        if (v.empty() || !same_line(duplicati[i].first, v.back().first)) {
            v.push_back(duplicati[i]);
        }
        else if (same_line(duplicati[i].first, v.back().first)) {
            if (duplicati[i].first.norm() > v.back().first.norm()) {
                v.pop_back();
                v.push_back(duplicati[i]);
            }
        }
    }
    
    // sweepline sorto per convex hull
    sort(v.begin(), v.end(), comp2);
    
    vector<pt> ch;
    vector<int> ch_res_top, ch_res_bot;

    ch.push_back(v[0].first);
    ch_res_top.push_back(v[0].second);
    if (v.size() > 1) {
        ch.push_back(v[1].first);
        ch_res_top.push_back(v[1].second);
    }
    for (int i = 2; i < v.size(); i ++) {
        pt p = v[i].first;

        while (ch.size() >= 2 && cross(p - ch[ch.size() - 2], ch[ch.size() - 1] - ch[ch.size() - 2]) <= 0) {
            ch.pop_back();
            ch_res_top.pop_back();
        }
        ch.push_back(p);
        ch_res_top.push_back(v[i].second);
    }

    ch.clear();

    ch.push_back(v[v.size() - 1].first);
    ch_res_bot.push_back(v[v.size() - 1].second);
    if (v.size() > 1) {
        ch.push_back(v[v.size() - 2].first);
        ch_res_bot.push_back(v[v.size() - 2].second);
    }
    for (int i = v.size() - 3; i >= 0; i --) {
        pt p = v[i].first;

        while (ch.size() >= 2 && cross(p - ch[ch.size() - 2], ch[ch.size() - 1] - ch[ch.size() - 2]) <= 0) {
            ch.pop_back();
            ch_res_bot.pop_back();
        }
        ch.push_back(p);
        ch_res_bot.push_back(v[i].second);
    }
    
    vector<bool> used(N);
    vector<int> res;
    for (auto x : ch_res_top) {
        if (used[x]) continue;
        used[x] = 1;
        res.push_back(x);
    }
    for (auto x : ch_res_bot) {
        if (used[x]) continue;
        used[x] = 1;
        res.push_back(x);
    }

    return res;
}
