#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <bitset>
#include <random>

#include <chrono>
#include <cassert>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define    INF 1000000007
#define  INF64 1000000000000000003LL
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

struct segment_tree_node {
    ll val;

    segment_tree_node() {
        val = 0;
    }

    segment_tree_node(ll val0) {
        val = val0;
    }
};

struct segment_tree {
    const segment_tree_node neutral = segment_tree_node();
    vector<segment_tree_node> tree;

    segment_tree_node combine(segment_tree_node a, segment_tree_node b) {
        segment_tree_node c;

        c.val = a.val + b.val;

        return c;
    }

    void resize(int n) {
        tree.resize(n << 2);
    }

    void build(vector<ll>& a) {
        build(0, 0, tree.size() >> 2, a);
    }

    void build(int v, int l, int r, vector<ll>& a) {
        if (r - l == 1) {
            tree[v].val = a[l];
            return;
        }
        int m = (l + r) / 2;

        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);

        tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
    }

    segment_tree_node get(int v, int l, int r, int ql, int qr) {
        if (r <= ql || qr <= l) {
            return neutral;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        int m = (l + r) / 2;

        return combine(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
    }

    segment_tree_node get(int ql, int qr) {
        return get(0, 0, tree.size() >> 2, ql, qr);
    }

    void update(int v, int l, int r, int ind, ll val) {
        if (r - l == 1) {
            tree[v].val = val;
            return;
        }
        int m = (l + r) / 2;
        if (ind < m) {
            update(2 * v + 1, l, m, ind, val);
        } else {
            update(2 * v + 2, m, r, ind, val);
        }

        tree[v] = combine(tree[2 * v + 1], tree[2 * v + 2]);
    }

    void update(int ind, ll val) {
        update(0, 0, tree.size() >> 2, ind, val);
    }
};

void solve() {
    ll lb, rb, i, n, q, cur_r;
    vector<ll> a, ans;
    map<ll, ll> prev_ind;
    vector<tuple<ll, ll, ll>> s;
    segment_tree segtree;

    cin >> n;

    a.resize(n);

    for (i = 0; i < n; i++) {
        cin >> a[i];
        prev_ind[a[i]] = -1;
    }

    cin >> q;

    s.resize(q);
    ans.resize(q);

    for (i = 0; i < q; i++) {
        cin >> lb >> rb;
        lb--;

        s[i] = tuple<ll, ll, ll>(rb, lb, i);
    }

    sort(s.begin(), s.end());

    segtree.resize(n);
    cur_r = 0;

    for (i = 0; i < q; i++) {
        while (cur_r < get<0>(s[i])) {
            if (prev_ind[a[cur_r]] != -1) {
                segtree.update(prev_ind[a[cur_r]], 0);
            }
            prev_ind[a[cur_r]] = cur_r;
            segtree.update(cur_r, 1);
            cur_r++;
        }
        /*
        for (ll j = 0; j < n; j++) {
            cout << segtree.get(j, j + 1).val << ' ';
        }
        cout << '\n';
        */
        ans[get<2>(s[i])] = segtree.get(get<1>(s[i]), get<0>(s[i])).val;
    }

    for (i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
 
    #ifndef LOCAL
        INPUT;
    #endif
	
    int t;
 
    for (t = 1; t; t--) {
        solve();
    }
 
    #ifdef LOCAL
        cerr << '\n';
        system("pause");
    #endif
 
    return 0;
}
