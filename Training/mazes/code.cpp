#include <bits/stdc++.h>
using namespace std;

const int LOG = 59;

vector<vector<char>> solve(long long K) {

    vector<vector<char>> res(2 * LOG + 3, vector<char>(2 * LOG + 1, '#')); 
    for (int i = 2; i < 2 * LOG + 3; i ++) {
        for (int j = 0; j < 2 * LOG + 1; j += 2) res[i][j] = '.';
    }
    for (int i = 0; i < 2 * LOG + 1; i ++) res[0][i] = '.';
    for (int i = 0; i < 2 * LOG + 1; i ++) res[2 * LOG + 2][i] = '.';


    int lunghezza = 2 * LOG;
    for (int i = 2; i < 2 * LOG + 3; i += 2) {
        for (int j = 0; j < lunghezza; j ++) res[i][j] = '.';
        lunghezza -= 2;
    }

    int pw = LOG;
    for (int i = 0; i < 2 * LOG + 1; i += 2) {
        if (K & (1ll << pw)) {
            res[1][i] = '.';
        }
        pw --;
    }

    return res;
}
