#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, d; cin >> n >> d;
    vector<int> h(n),l(n);
    for (int i=0;i<n;i++) {
        cin >> h[i] >> l[i];
    }
    long long sum = 0;
    for (auto x : h) sum += x;
    vector<pair<int,int>> reach(n);
    for (int i=0;i<n;i++) reach[i] = {h[i]+l[i],i};
    sort(reach.begin(), reach.end());
    priority_queue<int> q;

    int res = 0;
    for (int i=0;i<n;i++) {
        int elem = reach[i].second;

        // se riesci ad uscire gg
        if (sum+l[elem] >= d) {
            res ++;
            sum -= h[elem];
            q.push(h[elem]);
            continue;
        }
        // se non riesci ad uscire
        // se riaggiungendo tra gli stronzi uno già uscito
        // riesco a far uscire elem con una somma finale più alta
        // allora lo faccio
        if (!q.empty() && q.top() > h[elem] && sum+q.top()+l[elem] >= d) {
            sum += q.top() - h[elem];
            q.pop();
            q.push(h[elem]);
            continue;
        }
        // se invece non è giusto allora prova a mettere in cima un'altro con reach minore e continua
    }

    cout << res << '\n';
}
