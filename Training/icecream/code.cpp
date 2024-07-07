#include <bits/stdc++.h>
using namespace std;

struct node {
    map<int, node*> next;
    map<int, int> max_index;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<string> strings(N);
    for (auto &x : strings) cin >> x;

    node* trie = new node;

    vector<int> res(N + 1);

    for (int i = N - 1; i >= 0; i --) {
        node* curr = trie;
        int min_value = N;
        for (auto c : strings[i]) {    
            if (!curr->next.count(c - 'a')) {
                curr->next[c - 'a'] = new node;
            }

            if (curr->max_index.count(c - 'a')) {
                min_value = min(min_value, curr->max_index[c - 'a']);
            }
            curr->max_index[c - 'a'] = max(curr->max_index[c - 'a'], i);
            curr = curr->next[c - 'a'];
        }
        res[i] ++;
        res[min_value] --;
    }

    int curr = 0;
    for (int i = 0; i < N; i ++) {
        curr += res[i];
        cout << curr << '\n';
    }
}
