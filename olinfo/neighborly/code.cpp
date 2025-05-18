#include <bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll MAXN = 1e6 + 5;
constexpr ll MAXS = 1e4 + 5;
constexpr ll ABC = 256 + 5;
constexpr ll LOGS = 14;
constexpr ll LOGN = 20;

struct segment{
    vector<ll> seg;
    
    segment() {
        seg.assign(2 * (1 << LOGN), 1e18);
    }
    
    void update(int x, ll d) {
        x += (1 << LOGN);
        while (x >= 1) {
            seg[x] = min(seg[x], d);
            x /= 2;
        }
    }
    
    ll query(int l, int r) {
        l += (1 << LOGN), r += (1 << LOGN);
        ll res = 1e18;
        while (l <= r) {
            if (l % 2 == 1) {
                res = min(res, seg[l]);
                l ++;
            }
            if (r % 2 == 0) {
                res = min(res, seg[r]);
                r --;
            }
            l /= 2; r /= 2;
        }
        return res;
    }
};

struct suffixarray {
    vector<vector<int>> sa;
    vector<int> s;
    int sz;

    suffixarray(string &s_) {
        for (auto c : s_) s.push_back(c + 1);
        s.push_back(0);
        sz = s.size();
        sa.assign(LOGS, vector<int>(sz));
    }

    vector<int> calc_suffix_array() {
        vector<pair<int, int>> to_compare(sz);
        for (int i = 0; i < sz; i ++) to_compare[i] = {s[i], i};
        sort(to_compare.begin(), to_compare.end());
        sa[0][to_compare[0].second] = 0;
        for (int i = 1; i < sz; i ++) {
            int diff = (to_compare[i].first > to_compare[i - 1].first) ? 1 : 0;
            sa[0][to_compare[i].second] = sa[0][to_compare[i - 1].second] + diff;
        }

        for (int p = 1; p < LOGS; p ++) {
            vector<pair<pair<int, int>, int>> to_compare(sz);
            for (int i = 0; i < sz; i ++) {
                int nxt = (i + (1 << (p - 1))) % (sz + 1);
                to_compare[i] = {{sa[p - 1][i], sa[p - 1][nxt]}, i};
            }
            sort(to_compare.begin(), to_compare.end());
            sa[p][to_compare[0].second] = 0;
            for (int i = 1; i < sz; i ++) {
                int diff = (to_compare[i].first > to_compare[i - 1].first) ? 1 : 0;
                sa[p][to_compare[i].second] = sa[p][to_compare[i - 1].second] + diff;
            }
        }

        vector<int> sol(sz - 1);
        for (int i = 0; i < sz - 1; i ++) sol[i] = sa[LOGS - 1][i] - 1;
        return sol;
    }
};

void subtask(string n, string s) {
    // N consists of a single character repeated multiple times.
    char same_char = n[0];
    int longest = 0;
    int curr = 0;
    for (auto c : s) {
        if (c == same_char) {
            curr ++;
            longest = max(longest, curr);
        }
        else curr = 0;
    }

    cout << (n.size() + longest - 1) / longest << '\n'; 
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    string n, s;
    getline(cin, n);
    getline(cin, s);
    
    ll N = n.size();
    ll S = s.size();

    bool flag = 1;
    char same_char = n[0];
    for (auto c : n) if (c != same_char) flag = 0;
    if (flag) {
        subtask(n, s);
        return 0;
    }
    
    // suffix array

    suffixarray sa(s);
    vector<int> sorted_suffix = sa.calc_suffix_array();

    vector<ll> inv_perm(S);
    for (int i = 0; i < S; i ++) inv_perm[sorted_suffix[i]] = i;

    // dp + segment

    segment seg;
    vector<ll> dp(N + 1, 1e18);
    dp[N] = 0;
    seg.update(N, dp[N]);
    for (int i = N - 1; i >= 0; i --) {

        int max_l = -1;
        int sx = 0;
        int dx = S - 1;
        // claimed that l is actually always small
        for (int l = 0; i + l < N; l ++) {
            int new_sx = sx - 1;

            for (int p = (1 << LOGS); p >= 1; p /= 2) {
                if (new_sx + p <= dx && (inv_perm[new_sx + p] + l >= S || (int)s[inv_perm[new_sx + p] + l] < (int)n[i + l])) new_sx += p;
            }
            new_sx ++;

            int new_dx = dx + 1;
            for (int p = (1 << LOGS); p >= 1; p /= 2) {
                if (new_dx - p >= sx && inv_perm[new_dx - p] + l < S && (int)s[inv_perm[new_dx - p] + l] > (int)n[i + l]) new_dx -= p;
            }
            new_dx --;

            if (new_sx > new_dx) break;
            if (inv_perm[new_sx] + l >= S) break;

            if (s[inv_perm[new_sx] + l] == n[i + l]) {
                max_l = l;
            }
            else break;

            sx = new_sx, dx = new_dx;
        }

        dp[i] = seg.query(i + 1, i + max_l + 1) + 1;
        seg.update(i, dp[i]);
    }

    cout << dp[0] << '\n';
}
