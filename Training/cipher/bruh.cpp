#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(a, b);
}

int lcm(int a, int b) {
    return a * b / gcd(max(a, b), min(a, b));
}

const int ABC = 26;

struct node {
    int fine = 1e9;
    map<int, node*> next;
    // dice che si può generare una key (perché ha appena finito di ciclare o è all'inizio)
    // carattere iniziale -> (index stringa, pos di quel carattere)
    map<int, vector<pair<int, int>>> to_generate; 
    map<int, bool> can_generate; 
};

void del(node* nodo) {
    for (auto [c, x] : nodo->next) del(x);
    delete nodo;
}

void generate(vector<string> &keys, int s, int idx, node* start) {
    // genera lettera successiva
    int size = keys[s].size();
    int x = keys[s][idx] - 'a';
    
    node* curr = start;

    if (!curr->next.count(x)) curr->next[x] = new node;
    curr = curr->next[x];
    curr->fine = min(curr->fine, s);

    int next_idx = (idx + 1 < size) ? (idx + 1) : 0;
    int next_x = keys[s][next_idx] - 'a';

    curr->to_generate[next_x].push_back({s, next_idx});
    curr->can_generate[next_x] = true;
}

void solve_normale(int N, int K, vector<string> &strings, vector<string> &keys) {
    node* trie = new node;
    for (int i = 0; i < K; i ++) {
        int x = keys[i][0] - 'a';
        trie->to_generate[x].push_back({i, 0});
        trie->can_generate[x] = true;
    }

    vector<pair<string, int>> strings2(N);
    for (int i = 0; i < N; i ++) strings2[i] = {strings[i], i};
    sort(strings2.rbegin(), strings2.rend());
    vector<int> res(N);

    for (int i = 0; i < N; i ++) {
        node* curr = trie;
        bool uscito = false;

        for (auto c : strings2[i].first) {
            int x = c - 'a';

            int next_char = -1;
            int min_val = ABC;

            for (auto [a, b] : curr->to_generate) {
                int val = (x + a) % ABC;
                if (val < min_val) {
                    int trovato = false;
                    for (auto [s, idx] : b) {
                        if (strings2[i].first.size() % keys[s].size() == 0) trovato = true;
                    }
                    if (!trovato) continue;
                    min_val = val;
                    next_char = a;
                } 
            }

            if (next_char == -1) {
                uscito = true;
                break;
            }
            
            vector<int> to_erase;

            for (auto [a, nodo] : curr->next) {
                if (a != next_char) {
                    del(nodo);
                    to_erase.push_back(a);
                    curr->can_generate[a] = true;
                }
            }
            
            for (auto a : to_erase) curr->next.erase(a);

            if (curr->to_generate.count(next_char) && curr->can_generate[next_char]) {
                for (auto [s, idx] : curr->to_generate[next_char]) {
                    generate(keys, s, idx, curr);
                }

                curr->can_generate[next_char] = false;
            }

            curr = curr->next[next_char];

        }

        if (uscito || curr->fine == 1e9) res[strings2[i].second] = -1;
        else res[strings2[i].second] = curr->fine + 1;
    }

    for (auto x : res) cout << x << '\n';    
}

void solve_piccolo(int N, int K, vector<string> &strings, vector<string> &keys) {
    node* trie = new node;
    for (int i = 0; i < K; i ++) {
        int x = keys[i][0] - 'a';
        trie->to_generate[x].push_back({i, 0});
        trie->can_generate[x] = true;
    }

    vector<pair<string, int>> strings2(N);
    for (int i = 0; i < N; i ++) strings2[i] = {strings[i], i};
    sort(strings2.begin(), strings2.end());
    vector<int> res(N);

    for (int i = 0; i < N; i ++) {
        node* curr = trie;
        bool uscito = false;

        for (auto c : strings2[i].first) {
            int x = c - 'a';

            int next_char = -1;
            int min_val = ABC;

            for (auto [a, b] : curr->can_generate) {
                int val = (x + a) % ABC;
                if (val < min_val) {
                    min_val = val;
                    next_char = a;
                } 
            }

            if (next_char == -1) {
                uscito = true;
                break;
            }
            
            vector<int> to_erase;

            for (auto [a, b] : curr->next) {
                if (a != next_char) {
                    del(curr->next[a]);
                    to_erase.push_back(a);
                    curr->can_generate[a] = true;
                }
            }
            
            for (auto a : to_erase) curr->next.erase(a);

            if (curr->to_generate.count(next_char) && curr->can_generate[next_char]) {
                for (auto [s, idx] : curr->to_generate[next_char]) {
                    generate(keys, s, idx, curr);
                }

                curr->can_generate[next_char] = false;
            }

            curr = curr->next[next_char];

        }

        if (uscito || curr->fine == 1e9) res[strings2[i].second] = -1;
        else res[strings2[i].second] = curr->fine + 1;
    }

    for (auto x : res) cout << x << '\n';
}

struct node2 {
    int fine = 1e9;
    map<int,node2*> next;

    // carattere iniziale, stringa
    map<int, vector<int>> to_generate; 
};

int zp = 0;
const int MAX_SIZE = 1000000;
node2 arr[MAX_SIZE];
node2* new_node() {
    if (zp == MAX_SIZE) exit(-1);
    node2* nodo = arr + zp ++;
    nodo->fine = 1e9;
    nodo->next.clear();
    nodo->to_generate.clear();
    return nodo;
}

void generate2(vector<string> &keys, int i, node2* start) {
    // genera tutta la stringa  
    node2* curr = start;
    for (auto x : keys[i]) {
        if (!curr->next.count(x - 'a')) curr->next[x - 'a'] = new_node();
        curr = curr->next[x - 'a'];
        curr->fine = min(curr->fine, i);
    }
    curr->to_generate[keys[i][0] - 'a'].push_back(i);
}

void solve_grande(int N, int K, vector<string> &strings, vector<string> &keys) {
    node2* trie = new_node();
    for (int i = 0; i < K; i ++) {
        generate2(keys, i, trie);
    }

    int zp_prima = zp;

    for (int i = 0; i < N; i ++) {
        zp = zp_prima;
        node2* curr = trie;
        bool uscito = false;

        for (auto x : strings[i]) {

            bool trovato = false;
            for (int j = 0; j < ABC; j ++) {

                int character = (j - (x - 'a') + ABC) % ABC;
                
                if (curr->to_generate.count(character)) {
                    for (auto s : curr->to_generate[character]) {
                        generate2(keys, s, curr);
                    }
                }

                if (!curr->next.count(character)) continue;

                trovato = true;
                curr = curr->next[character];
                break;
            
            }
            if (trovato) continue;
            uscito = true;
        }

        if (uscito || curr->fine == 1e9) cout << -1 << '\n';
        else cout << curr->fine + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, K; cin >> N >> K;
    vector<string> keys(K), strings(N);
    for (int i = 0; i < K; i ++) cin >> keys[i];
    for (int i = 0; i < N; i ++) cin >> strings[i];

    int mcm = 1;
    for (int i = 0; i < K; i ++) mcm = lcm(mcm, keys[i].size());
    
    // se divide l'mcm divide tutti i keys
    bool sempre_divisibile = true;
    for (int i = 0; i < N; i ++) if (strings[i].size() % mcm != 0) sempre_divisibile = false;

    // per qualche motivo l'ultimo subtask funziona in questo modo :skull:
    if (!sempre_divisibile) {
        solve_normale(N, K, strings, keys);
        return 0;   
    }
    
    if (K <= 1e4) {
        solve_piccolo(N, K, strings, keys);
        return 0;
    }

    if (K > 1e4) {
        solve_grande(N, K, strings, keys);
        return 0;
    }
}
