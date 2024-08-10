#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
stack<int> get_node[MAXN];
vector<pair<int, int>> edges;
bool impossibile = false;

void piazza(int nodo, int value) {
    // places all the stuff up to value
    for (int i = 1; i <= value; i ++) {
        if (get_node[i].empty()) {
            impossibile = true;
            return;
        }
        int new_node = get_node[i].top();
        edges.push_back({nodo, new_node});
        get_node[i].pop();

        piazza(new_node, i - 1);
    }
}

variant<bool, vector<pair<int, int>>> find_numbering(int N, vector<int> A) {
    int max_value = 0;
    for (int i = 0; i < N; i ++) {
        get_node[A[i]].push(i);
        max_value = max(max_value, A[i]);
    }

    // the strategy is this:
    // 1   1   1   1   1   1   1   1
    // |   |   |   |   |   |   |   |
    // 3 - 4 - 4 - 4 - 4 - 3 - 3 - 3 - 2 - 2 - 2 - 1   1 - 1    1 - 1    1 - 1
    // |   |   |   |   |
    // 2   2   2   2   2
    // |   |   |   |   |   
    // 1   1   1   1   1   

    for (int i = 1; i <= max_value; i ++) if (get_node[i].size() % 2) return false;

    // piazzo i primi 2 massimi
    int curr_node = get_node[max_value].top(); get_node[max_value].pop();
    piazza(curr_node, max_value - 1);

    // spammo i return false anche se non servono idc
    if (get_node[max_value].empty()) return false;

    int new_node = get_node[max_value].top();
    edges.push_back({curr_node, new_node});
    get_node[max_value].pop();
    curr_node = new_node;
    piazza(curr_node, max_value - 2);

    for (int curr_value = max_value; curr_value > 1; curr_value -= 1) {

        if (curr_value < max_value) {
            if (get_node[curr_value].empty()) return false;
            new_node = get_node[curr_value].top();
            edges.push_back({curr_node, new_node});
            get_node[curr_value].pop();
            curr_node = new_node;
            piazza(curr_node, curr_value - 2);
            if (impossibile) return false;
        }
        
        while (!get_node[curr_value].empty()) {
            // sempre di due in due idc

            new_node = get_node[curr_value].top();
            edges.push_back({curr_node, new_node});
            get_node[curr_value].pop();
            curr_node = new_node;
            piazza(curr_node, curr_value - 2);
            if (impossibile) return false;

            if (get_node[curr_value].empty()) return false;
            new_node = get_node[curr_value].top();
            edges.push_back({curr_node, new_node});
            get_node[curr_value].pop();
            curr_node = new_node;
            piazza(curr_node, curr_value - 2);
            if (impossibile) return false;
        }
    }

    if (A[curr_node] != 1) {

        // piazzo ultimo uno
        if (get_node[1].empty()) return false;
        new_node = get_node[1].top();
        edges.push_back({curr_node, new_node});
        get_node[1].pop();
        curr_node = new_node;
    }

    while (!get_node[1].empty()) {

        curr_node = get_node[1].top();
        get_node[1].pop();

        if (get_node[1].empty()) return false;
        new_node = get_node[1].top();
        get_node[1].pop();

        edges.push_back({curr_node, new_node});
    }

    return edges;
}
