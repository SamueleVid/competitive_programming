#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<string>v(13);
    for (int i=0;i<13;i++) {
        cin >> v[i];
    } 
    vector<vector<char>>sudoku(9,vector<char>(9,'.'));
    int real_i = 0;
    for (int i=0;i<13;i++) {
        
        if (v[i][1] == '-') continue;
        int real_j = 0;
        for (int j=0;j<13;j++) {
            if (v[i][j] == '|' || v[i][j] == '-' || v[i][j] == '+') continue;
            sudoku[real_i][real_j] = v[i][j];
            real_j ++;
        }
        real_i ++;
    }
    vector<int>nums(9,0);
    // rows
    for (int i=0;i<9;i++) {
        for (int k=0;k<9;k++) nums[k] = 0;
        for (int j=0;j<9;j++) {
            if (sudoku[i][j] != '.') {
                if (nums[sudoku[i][j] - '1'] != 0) {
                    cout << "GRESKA" << '\n';
                    return 0;
                }
                nums[sudoku[i][j] - '1'] ++;
            }
        }
    }
    // cols
    for (int i=0;i<9;i++) {
        for (int k=0;k<9;k++) nums[k] = 0;
        for (int j=0;j<9;j++) {
            if (sudoku[j][i] != '.') {
                if (nums[sudoku[j][i] - '1'] != 0) {
                    cout << "GRESKA" << '\n';
                    return 0;
                }
                nums[sudoku[j][i] - '1'] ++;
            }
        }
    }
    // quadranti
    for (int qi=0;qi<3;qi++) {
        for (int qj=0;qj<3;qj++) {
            for (int k=0;k<9;k++) nums[k] = 0;
            for (int i=qi*3;i<qi*3+3;i++) {
                for (int j=qj*3;j<qj*3+3;j++) {
                    if (sudoku[j][i] != '.') {
                        if (nums[sudoku[j][i] - '1'] != 0) {
                            cout << "GRESKA" << '\n';
                            return 0;
                        }
                        nums[sudoku[j][i] - '1'] ++;
                    }
                }
            }
        }
    }
    cout << "OK" << '\n';
}
