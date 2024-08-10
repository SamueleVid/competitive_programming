#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q; cin >> n >> q;
    vector<int> pos_to_car(n);
    vector<int> car_to_pos(n+1);
    vector<int> overtaken(n+1,0);
    for (int i=0;i<n;i++) {
        int a; cin >> a;
        pos_to_car[i]=a;
        car_to_pos[a]=i;
    }

    priority_queue<pair<int,int>> pq; // overtakings, macchina

    int last = 0;
    int last_car = 0;

    for (int i=0;i<q;i++) {
        int car_a; cin >> car_a;
        int pos = car_to_pos[car_a];
        int car_b = pos_to_car[pos-1];
        
        pos_to_car[pos] = car_b;
        pos_to_car[pos-1] = car_a;

        car_to_pos[car_a] = pos-1;
        car_to_pos[car_b] = pos;

        overtaken[car_b] ++;

        if (overtaken[car_b] == last && last_car > car_b) last_car = car_b;
        if (overtaken[car_b] > last) {
            last = overtaken[car_b];
            last_car = car_b;
        }
        
        cout << last_car << endl;
    }
}
