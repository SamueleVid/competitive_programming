#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000000
#define MAXM 100000

typedef struct {
    int x, y;
} point;

point operator+(point &a, point &b) {
    return {a.x+b.x, a.y+b.y};
}

point operator-(point &a, point &b) {
    return {a.x-b.x, a.y-b.y};
}

void rotate(point &a, int nintys) {
    for (int i=0;i<nintys;i++) {
        int x = a.y;
        int y = -a.x;
        a = {x,y};
    }
}

point update_dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};

point passeggia(int n, int m, char p[], int s[], int e[]) {
    vector<point> prefix_pos(n+1);
    vector<int> prefix_dir(n+1);
    vector<int> prefix_x(n+1);
    prefix_pos[0] = {0,0};
    prefix_dir[0] = 0;
    prefix_x[0] = 0;

    for (int i=0;i<n;i++) {
        if (p[i]=='F') {
            prefix_pos[i+1] = prefix_pos[i] + update_dir[prefix_dir[i]];
            prefix_dir[i+1] = prefix_dir[i];
            prefix_x[i+1] = prefix_x[i];;
        }
        if (p[i]=='B') {
            prefix_pos[i+1] = prefix_pos[i] - update_dir[prefix_dir[i]];
            prefix_dir[i+1] = prefix_dir[i];
            prefix_x[i+1] = prefix_x[i];;
        }
        if (p[i]=='R') {
            prefix_dir[i+1] = (prefix_dir[i] + 3) % 4;
            prefix_pos[i+1] = prefix_pos[i];
            prefix_x[i+1] = prefix_x[i];;
        }
        if (p[i]=='L') {
            prefix_dir[i+1] = (prefix_dir[i] + 1) % 4;
            prefix_pos[i+1] = prefix_pos[i];
            prefix_x[i+1] = prefix_x[i];;
        }
        if (p[i]=='X') {
            prefix_dir[i+1] = prefix_dir[i];
            prefix_pos[i+1] = prefix_pos[i];
            prefix_x[i+1] = prefix_x[i]+1;
        }
    }

    point vec = {0,0};
    int dir = 0;

    for (int i=0;i<m;i++) {
        if (prefix_x[e[i]+1]-prefix_x[s[i]] > 0) {
            for (int j=s[i];j<=e[i];j++) {
                if (p[j]=='F') {
                    vec = vec + update_dir[dir];
                }
                if (p[j]=='B') {
                    vec = vec - update_dir[dir];
                }
                if (p[j]=='R') {
                    dir = (dir + 3) % 4;
                }
                if (p[j]=='L') {
                    dir = (dir + 1) % 4;
                }
                if (p[j]=='X') {
                    return vec;
                }
            }
        }
        else {
            // vettore differenza
            point curr_vec = prefix_pos[e[i]+1] - prefix_pos[s[i]];
            // differenza di rotazione iniz
            int curr_dir_start = prefix_dir[s[i]] - dir;
            // differenza di rotazione finale
            int curr_dir_end = prefix_dir[e[i]+1] - prefix_dir[s[i]];
            // modulando come si deve
            curr_dir_start = (curr_dir_start + 4) % 4;
            curr_dir_end = (curr_dir_end + 4) % 4;

            // ruoto il vettore differenza rispetto la differenza di rotazione iniz
            rotate(curr_vec, curr_dir_start);

            // aggiungo il vettore alla fine
            vec = vec + curr_vec;
            // aggiungo alla rotazione la differenza di rotazione
            dir += curr_dir_end;
            // modulo come si deve
            dir = (dir + 4)%4;
        }
    }
    return vec;
}

char P[MAXN+2];
int S[MAXM], E[MAXM];

int main() {
    FILE *fr, *fw;
    int N, M, i;

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d %d\n", &N, &M));
    assert(1 == fscanf(fr, "%s", P));
    for(i=0; i<M; i++)
        assert(2 == fscanf(fr, "%d %d", &S[i], &E[i]));

    point p = passeggia(N, M, P, S, E);
    fprintf(fw, "%d %d\n", p.x, p.y);
    fclose(fr);
    fclose(fw);
    return 0;
}
