#include <bits/stdc++.h>
using namespace std;

const int LOG = 15;

bool test(string T);

string repeat_ones(int k) {
    string res = "";
    for (int i = 0; i < k; i++) res += '1';
    return res;
}

string analizza(int N) {
    string res = "";

    int k = 0;
    for (int pw = 1 << LOG; pw >= 1; pw /= 2) {
        if (k + pw <= N && test(repeat_ones(k + pw))) k += pw;
    }
    int biggest_one = k;
    
    res += repeat_ones(biggest_one);
    
    int curr_ones = biggest_one;

    while (res.size() < N && curr_ones <= biggest_one) {

        if (test(res + '0')) {
            res += '0';
            curr_ones = 0;
        }
        else {
            res += '1';
            curr_ones ++;
        }
    }

    res = string(res.begin(), res.end() - curr_ones);
    
    while (test(res + '1')) res += '1';

    if (res.size() == N) return res;
    res = '0' + res;
    curr_ones = 0;

    while (res.size() < N) {

        if (test('0' + res)) {
            res = '0' + res;
            curr_ones = 0;
        }
        else {
            res = '1' + res;
            curr_ones ++;
        }
    }

    return res;
}
