#include <bits/stdc++.h>
using namespace std;

bool is_x(int r, int c, int n, int m, vector<vector<bool>> &grid) {
    if (r < 0 || r >= n || c < 0 || c >= m) return 0;
    return grid[r][c];
}

bool placable(int r, int c, int n, int m, vector<vector<bool>> &grid) {
    
    // HORIZONTAL

    //
    // x x X
    //

    if (is_x(r,c-2,n,m,grid)&&is_x(r,c-1,n,m,grid)) return 0;
    
    // VERTICAL

    // x
    // x
    // X

    if (is_x(r-2,c,n,m,grid)&&is_x(r-1,c,n,m,grid)) return 0;

    // DIAG 1 

    // x . .
    // . x .
    // . . X

    if (is_x(r-2,c-2,n,m,grid)&&is_x(r-1,c-1,n,m,grid)) return 0;

    // DIAG 2

    // . . x
    // . x .
    // X . .

    if (is_x(r-1,c+1,n,m,grid)&&is_x(r-2,c+2,n,m,grid)) return 0;

    return 1;
}

int max_placed = 0;

void rec(int row, int col, int n, int m, int placed, int remaining, vector<vector<bool>> &grid, int libere_di_seguito) {
    if (n*m > 25 && libere_di_seguito >= 3) return;
    if (remaining+placed * 5 < max_placed * 2) return;
    if (col == m) return rec(row+1, 0, n, m, placed, remaining, grid, 0);
    if (row == n) {
        max_placed = max(placed, max_placed);
        return;
    }
    if (placable(row,col,n,m,grid)) {
        grid[row][col] = 1;
        rec(row, col+1, n, m, placed+1, remaining-1, grid, 0);
        grid[row][col] = 0;
    }
    rec(row, col+1, n, m, placed, remaining, grid, libere_di_seguito+1);
}

int gioca(int n, int m) {
    vector<vector<bool>> grid(n, vector<bool>(m,0));
    rec(0,0,n,m,0,n*m,grid,0);
    return max_placed;
}

int main() {
    int n, m; cin >> n >> m;
    if (m>n) swap(n,m);
    cout << gioca(n,m) << endl;
}
