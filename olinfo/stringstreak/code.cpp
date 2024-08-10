#include <bits/stdc++.h>

using namespace std;

int main() {
    string s; cin >> s;
    int b; cin >> b;

    int res = 0;
    for (int l=0;l<26;l++) {
        char c = 'a'+l;
        deque<pair<int,int>>q; // end
        int lb = 0;
        int sum = 0;
        int max_len = 0;
        for (int rb=0;rb<s.size();rb++) {
            
            if ((rb == 0 || s[rb-1] == c) && s[rb] != c) {
                q.push_back({1,rb}); //metto 1 perché tanto dopo lo raddoppio e diventa 2
                sum += 1;
            }
            if (s[rb] != c) {
                q[q.size()-1].second = rb;
                sum -= q[q.size()-1].first;
                q[q.size()-1].first *= 2;
                sum += q[q.size()-1].first;
            }
            
            while (sum>b && lb<=rb) {
                
                if (s[lb] == c) {
                    lb ++;
                    continue;
                }
                
                if (lb == q[0].second) {
                    sum -= q[0].first;
                    q.pop_front();
                }
                else {
                    sum -= q[0].first;
                    q[0].first /= 2;
                    sum += q[0].first;
                }
                lb ++;
                
            }

            if (sum <= b && rb-lb+1 > max_len) max_len = rb-lb+1;
        }
        res = max(res, max_len);
    }

    cout << res << '\n';
}
