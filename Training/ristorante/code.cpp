#include <bits/stdc++.h>
using namespace std;

int pick_in_order(int N, vector<int> &first, vector<int> &second, vector<int> &third) {
    map<int,int>m;
    int res = 0;
    int x = 0, y = 0, z = 0;
    
    while (x < N && !m[first[x]]) m[first[x]] ++, x ++;
    while (y < N && !m[second[y]]) m[second[y]] ++, y ++;
    while (z < N && !m[third[z]]) m[third[z]] ++, z ++;

    res = x + y + z;
    while (x > 0) {
        x --;
        m[first[x]] --;
        while (y < N && !m[second[y]]) m[second[y]] ++, y ++;
        while (z < N && !m[third[z]]) m[third[z]] ++, z ++;
        res = max(res, x + y + z);
    }

    return res;
}

int conta(int N, vector<int> &A, vector<int> &P, vector<int> &D) {
    int res = 0;
    
    res = max(res, pick_in_order(N, A, P, D));
    res = max(res, pick_in_order(N, A, D, P));
    res = max(res, pick_in_order(N, P, A, D));
    res = max(res, pick_in_order(N, P, D, A));
    res = max(res, pick_in_order(N, D, A, P));
    res = max(res, pick_in_order(N, D, P, A));

    return sum;
}
