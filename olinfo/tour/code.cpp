// credit https://weoi.org/wp-content/uploads/2023/07/WEOI-2023-Problemset-Editorial.pdf
#include <bits/stdc++.h>
using namespace std;

variant<bool, vector<int>> find_tour(int N, vector<int> A) {
	
    for (int i = 1; i < N - 1; i ++) if (A[i] <= 2) return false;
    if (A[0] != 2 || A[N - 1] != 2) return false;

    int k = 0;
    vector<int> type(N); // < v >
    for (int i = 0; i < N; i ++) {
        if (A[i] == k + 2) {
            type[i] = 0;
            k += 2;
            continue;
        }
        if (A[i] == k + 1) {
            type[i] = 1;
            k += 0;
            continue;
        }
        if (A[i] == k) {
            type[i] = 2;
            k -= 2;
            continue;
        }
        return false;
    }
    
    if (k != 0) return false;
    
    vector<int> res;
    res.push_back(0);
    queue<int> q;
    for (int i = 1; i < N - 1; i ++) {
        if (type[i] == 0) {
            q.push(i);
        }
        if (type[i] == 1) {
            res.push_back(i);
        }
        if (type[i] == 2) {
            res.push_back(i);
            if (q.empty()) return false;
            res.push_back(q.front()); q.pop();
        }
    }
    res.push_back(N - 1);
    
    return res;
}
