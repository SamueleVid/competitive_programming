#include <bits/stdc++.h>
#include "disegno.h"
using namespace std;
const int INF = 2e9;

bool operator<(const Point &i, const Point &j) {
    if (i.x == j.x) return (i.y < j.y);
    return (i.x < j.x);
}

struct node{
    node* up = nullptr;
    node* right = nullptr;
    int x, y;
};

struct trie{
    vector<trie*> next;
    Point pt;
    bool is_move = false;
    
    void vectorize_moves(vector<Point>&res) {
        if (!is_move) return;
        res.push_back(pt);
        for (auto m : next) m->vectorize_moves(res);
    }
};

bool errore = false;
node* mock_node = new node;
trie* mock_trie = new trie;
pair<array<node*, 3>, trie*> chiudi() {
    errore = true;
    return {{mock_node,mock_node,mock_node},mock_trie};
}

// top-left, top-right, bottom-right
pair<array<node*, 3>, trie*> ziopera(node* nodo, Point bounds) {
    if (errore) return chiudi();

    if (!nodo->right || !nodo->up) return chiudi();
    node* dx = nodo->right;
    node* up = nodo->up;
    while (!up->right && up->up) up = up->up;
    while (!dx->up && dx->right) dx = dx->right;

    node* top_left = up;
    node* bottom_right = dx;

    while (dx->up && dx->y < top_left->y) dx = dx->up;
    while (up->right && up->x < bottom_right->x) up = up->right;
    if (dx != up || dx->x > bounds.x || dx->y > bounds.y) return chiudi();

    node* dot = dx;
    trie* top_moves = new trie;

    while (dot->x < bounds.x && dot->y < bounds.y) {
        if (errore) return chiudi();

        trie* temp = new trie;
        temp->next.push_back(top_moves);
        temp->pt = {dot->x, dot->y};
        temp->is_move = true;
        top_moves = temp;

        auto [top_results, moves_top] = ziopera(top_left, {dot->x, INF});
        auto [right_results, moves_right] = ziopera(bottom_right, {INF, dot->y});
        auto [topright_results, moves_topright] = ziopera(dot, {right_results[1]->x, top_results[1]->y});

        top_moves->next.push_back(moves_top);
        top_moves->next.push_back(moves_right);
        top_moves->next.push_back(moves_topright);

        top_left = top_results[0];
        bottom_right = right_results[2];
        dot = topright_results[1];
    }

    if (bounds.x != INF && bounds.x != dot->x) return chiudi();  
    if (bounds.y != INF && bounds.y != dot->y) return chiudi();

    return {{top_left, dot, bottom_right}, top_moves};
}

vector<Point> draw(int n, int l, vector<Point> a, vector<Point> b) {
    
    int k = 0;
    map<Point, int>indexes;
    vector<Point>pts;
    for (auto pt : a) if (!indexes.count(pt)) pts.push_back(pt), indexes[pt] = k++;
    for (auto pt : b) if (!indexes.count(pt)) pts.push_back(pt), indexes[pt] = k++;
    pts.push_back({0,0}), indexes[{0,0}] = k++;
    pts.push_back({0,l}), indexes[{0,l}] = k++;
    pts.push_back({l,0}), indexes[{l,0}] = k++;
    pts.push_back({l,l}), indexes[{l,l}] = k++;
    
    vector<node*>nodes(k);
    for (int i = 0; i < k; i++) {
        nodes[i] = new node;
        nodes[i]->x = pts[i].x;
        nodes[i]->y = pts[i].y;
    }

    for (int i = 0; i < n; i++) {
        if (a[i].x == b[i].x) {
            // a[i].y < b[i].y
            nodes[indexes[a[i]]]->up = nodes[indexes[b[i]]];
        }
        else {
            // a[i].x < b[i].x
            nodes[indexes[a[i]]]->right = nodes[indexes[b[i]]];
        }
    }

    // inserisci bordi
    vector<pair<int,int>> zeros_x, zeros_y, l_x, l_y;
    for (int i = 0; i < k; i++) {
        if (pts[i].x == 0) zeros_x.push_back({pts[i].y, i});
        if (pts[i].y == 0) zeros_y.push_back({pts[i].x, i});
        if (pts[i].x == l) l_x.push_back({pts[i].y, i});
        if (pts[i].y == l) l_y.push_back({pts[i].x, i});
    }
    sort(zeros_x.begin(), zeros_x.end());
    sort(zeros_y.begin(), zeros_y.end());
    sort(l_x.begin(), l_x.end());
    sort(l_y.begin(), l_y.end());
    for (int i = 0; i < zeros_x.size() - 1; i++) {
        nodes[zeros_x[i].second]->up = nodes[zeros_x[i+1].second];
    }
    for (int i = 0; i < zeros_y.size() - 1; i++) {
        nodes[zeros_y[i].second]->right = nodes[zeros_y[i+1].second];
    }
    for (int i = 0; i < l_x.size() - 1; i++) {
        nodes[l_x[i].second]->up = nodes[l_x[i+1].second];
    }
    for (int i = 0; i < l_y.size() - 1; i++) {
        nodes[l_y[i].second]->right = nodes[l_y[i+1].second];
    }

    trie* moves = ziopera(nodes[indexes[{0,0}]], {l,l}).second;
    vector<Point> res;
    moves->vectorize_moves(res);
    
    return res;
}
