// credit a lorenzo ferrari e alla sua soluzione https://github.com/lorenzo-ferrari/olinfo/blob/main/src/iiot_cipher.cpp
#include <bits/stdc++.h>
using namespace std;

const int ABC = 26;

struct node {
    int end = 1e9;
    node* next[26];

    node() {
        fill(next, next + ABC, nullptr);
    }
};

struct trie {
    node* root;
    
    trie() {
        root = new node;
    }

    void insert(string &s, int i) {
        node* curr = root;
        for (auto character : s) {
            int x = character - 'a';
            if (!curr->next[x]) curr->next[x] = new node;
            curr = curr->next[x];
        }
        curr->end = min(i, curr->end);
    }

    int search(string &s, int d) {
        node* curr = root;
        for (int i = 0; i < d; i ++) {
            int x = s[i] - 'a';

            for (int cip = 0; cip < ABC; cip ++) {
                int rev = (cip - x + ABC) % ABC;
                if (!curr->next[rev]) continue;

                curr = curr->next[rev];
                break;
            }
        }
        return curr->end;
    }
};

string cipher(string &s, string &k) {
    string res = "";
    for (int i = 0; i < s.size(); i ++) {
        res += (char) (((s[i] - 'a') + (k[i % k.size()] - 'a')) % ABC + 'a');
    }
    return res;
}

bool sostituisco(string &s, string &key1, int idx1, string &key2, int idx2) {
    string cipher1 = cipher(s, key1);
    string cipher2 = cipher(s, key2);
    if (cipher1 == cipher2) return idx1 < idx2;
    return cipher1 < cipher2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, K; cin >> N >> K;
    vector<string> keys(K), strings(N);
    for (int i = 0; i < K; i ++) cin >> keys[i];
    for (int i = 0; i < N; i ++) cin >> strings[i];

    map<int, trie> tries; // length of string, trie

    for (int i = 0; i < K; i ++) {
        int size = keys[i].size();
        tries[size].insert(keys[i], i);
    }

    // strings * divisors * length string = (N) * (N ^ (1/3)) * (TOT_LEN / N) = TOT_LEN * N ^ (1/3) = 2.33e7
    for (int i = 0; i < N; i ++) {
        int size = strings[i].size();

        int ans = 1e9;
        // se due chiavi hanno la stessa dimensione di ciclo è easy da confrontare, vedi fino alla lunghezza della chiave
        // N * size < TOT_LEN quindi chilling
        for (int d = 1; d <= size; d ++) {
            if (size % d || !tries.count(d)) continue;

            int fine = tries[d].search(strings[i], d);
            if (ans == 1e9 || sostituisco(strings[i], keys[fine], fine, keys[ans], ans)) {
                ans = fine;
            }
        }

        cout << ((ans == 1e9) ? -1 : ans + 1) << '\n';
    }
}
