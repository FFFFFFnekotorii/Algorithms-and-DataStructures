#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define     INF 1000000007
#define  BIGINF 1000000000000000
#define     LMT 1000000
#define   INPUT ios::sync_with_stdio(false); cin.tie(0);

#define     FST first
#define     SND second

#define MAXLOG2 31

template<int alphabet_size>
struct prefix_tree {
    vector<vector<int>> to;
    vector<ll> cnt;
    int last_free_id = 1;

    prefix_tree() {
        to.push_back(vector<int>(alphabet_size, -1));
        cnt.push_back(0);
    }

    void insert_all_prefixes(vector<int>& word) {
        int cur_id = 0;
        for (int c : word) {
            if (to[cur_id][c] == -1) {
                to[cur_id][c] = last_free_id++;
                to.push_back(vector<int>(alphabet_size, -1));
                cnt.push_back(0);
            }
            cur_id = to[cur_id][c];
            cnt[cur_id]++;
        }
    }

    void insert(vector<int>& word) {
        int cur_id = 0;
        for (int c : word) {
            if (to[cur_id][c] == -1) {
                to[cur_id][c] = last_free_id++;
                to.push_back(vector<int>(alphabet_size, -1));
                cnt.push_back(0);
            }
            cur_id = to[cur_id][c];
        }
        cnt[cur_id]++;
    }

    ll count_all_prefixes(vector<int>& word) {
        int cur_id = 0;
        ll res = 0;
        for (int c : word) {
            if (to[cur_id][c] == -1) {
                return res;
            }
            cur_id = to[cur_id][c];
            res += cnt[cur_id];
        }
        return res;
    }

    ll count(vector<int>& word) {
        int cur_id = 0;
        for (int c : word) {
            if (to[cur_id][c] == -1) {
                return 0;
            }
            cur_id = to[cur_id][c];
        }
        return cnt[cur_id];
    }
};

void solve() {

}

int main() {
    INPUT;

    ll t;

    t = 1;

    while (t--) {
        solve();
    }

    return 0;
}
