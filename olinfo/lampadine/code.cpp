#include <bits/stdc++.h>
using namespace std;

vector<int> disconnect(vector<int> L);
void series(vector<int> G);

void study(int N) {

    vector<int>gruppo;
    for (int i=0;i<N;i++) gruppo.push_back(i);
    vector<vector<int>>gruppi;
    gruppi.push_back(gruppo);

    for (int i=1<<(int)log2(N);i>=1;i/=2) {
        
        vector<int>to_discon;
        vector<int>elem_to_group(N,-1);
        for (auto g : gruppi) {
            for (int j=0;j<g.size()&&j<i;j++) {
                to_discon.push_back(g[j]);
            }
        }

        vector<int> check = disconnect(to_discon);
        vector<vector<int>>new_gruppi;
        for (auto x : gruppi) {
            vector<int>controlla(N,0);
            for (auto elem : x) controlla[elem]=1;
            vector<int>g1;
            vector<int>g2;
            for (int j=0;j<N;j++) {
                if (controlla[j]) {
                    if (check[j]) g1.push_back(j);
                    else g2.push_back(j);
                }
            }
            if (g1.size()) new_gruppi.push_back(g1);
            if (g2.size()) new_gruppi.push_back(g2);
        }
        gruppi=new_gruppi;
    }

    for (auto x : gruppi) series(x);
}
