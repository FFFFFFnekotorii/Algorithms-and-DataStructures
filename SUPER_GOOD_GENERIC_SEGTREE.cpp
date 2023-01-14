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

//#define DEBUG
//#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    #define cout cerr
#endif

struct segment_tree_node_minmax {

    ll min_val, max_val, min_ind, max_ind;

    segment_tree_node_minmax() {
        min_val = INF;
        max_val = -INF;
        min_ind = -1;
        max_ind = -1;
    }

    segment_tree_node_minmax(ll ind0, ll val0) {
        min_val = val0;
        max_val = val0;
        min_ind = ind0;
        max_ind = ind0;
    }

    segment_tree_node_minmax operator|(segment_tree_node_minmax other) {
        segment_tree_node_minmax res;

        if (min_val < other.min_val) {
            res.min_val = min_val;
            res.min_ind = min_ind;
        } else {
            res.min_val = other.min_val;
            res.min_ind = other.min_ind;
        }

        if (max_val < other.max_val) {
            res.max_val = other.max_val;
            res.max_ind = other.max_ind;
        } else {
            res.max_val = max_val;
            res.max_ind = max_ind;
        }

        return res;
    }

    void operator+=(ll delta) {
        min_val += delta;
        max_val += delta;
    }

    void operator=(ll new_val) {
        min_val = new_val;
        max_val = new_val;
    }

};

struct segment_tree_node_sum {

    ll val;

    segment_tree_node_sum() {
        val = 0;
    }

    segment_tree_node_sum(ll ind0, ll val0) {
        val = val0;
    }

    segment_tree_node_sum operator|(segment_tree_node_sum other) {
        segment_tree_node_sum res;

        res.val = val + other.val;

        return res;
    }

    void operator+=(ll delta) {
        val += delta;
    }

    void operator=(ll new_val) {
        val = new_val;
    }

};

template<typename segment_tree_node>
struct segment_tree {
    const segment_tree_node neutral = segment_tree_node();
    vector<segment_tree_node> tree;

    void resize(ll n) {
        tree.resize(n << 2);
    }

    void build(vector<ll>& a) {
        build(0, 0, tree.size() >> 2, a);
    }

    void build(ll v, ll l, ll r, vector<ll>& a) {
        if (r - l == 1) {
            tree[v] = segment_tree_node(l, a[l]);
            return;
        }
        ll m = (l + r) / 2;

        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    segment_tree_node get(ll v, ll l, ll r, ll ql, ll qr) {
        if (r <= ql || qr <= l) {
            return neutral;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        ll m = (l + r) / 2;

        return get(2 * v + 1, l, m, ql, qr) | get(2 * v + 2, m, r, ql, qr);
    }

    segment_tree_node get(ll ql, ll qr) {
        return get(0, 0, tree.size() >> 2, ql, qr);
    }

    void add(ll v, ll l, ll r, ll ind, ll delta) {
        if (r - l == 1) {
            tree[v] += delta;
            return ;
        }
        ll m = (l + r) / 2;

        if (ind < m) {
            add(2 * v + 1, l, m, ind, delta);
        } else {
            add(2 * v + 2, m, r, ind, delta);
        }

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    void add(ll ind, ll delta) {
        add(0, 0, tree.size() >> 2, ind, delta);
    }

    void update(ll v, ll l, ll r, ll ind, ll new_val) {
        if (r - l == 1) {
            tree[v] = new_val;
            return ;
        }
        ll m = (l + r) / 2;

        if (ind < m) {
            update(2 * v + 1, l, m, ind, new_val);
        } else {
            update(2 * v + 2, m, r, ind, new_val);
        }

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    void update(ll ind, ll new_val) {
        update(0, 0, tree.size() >> 2, ind, new_val);
    }
};

void solve() {

    ll n, i, m, ans, x, val;
    vector<ll> a, p;
    segment_tree<segment_tree_node_minmax> st;
    segment_tree<segment_tree_node_sum> st_add;

    cin >> n >> m;
    m--;

    a.resize(n);
    p.resize(n);
    st.resize(n);
    st_add.resize(n);

    for (i = 0; i < n; i++) {
        cin >> a[i];
    }

    p[0] = a[0];
    for (i = 1; i < n; i++) {
        p[i] = p[i - 1] + a[i];
    }

    st.build(a);

    ans = 0;

    for (i = m - 1; -1 < i; i--) {

        while (p[i] + st_add.get(0, i + 1).val < p[m] + st_add.get(0, m + 1).val) {
            x = st.get(i + 1, m + 1).max_ind;
            st.update(x, -a[x]);

            st_add.add(x, -2 * a[x]);

            a[x] = -a[x];

            ans += 1;
        }
    }

    for (i = m + 1; i < n; i++) {

        while (p[i] + st_add.get(0, i + 1).val < p[m] + st_add.get(0, m + 1).val) {
            x = st.get(m + 1, i + 1).min_ind;
            st.update(x, -a[x]);

            st_add.add(x, -2 * a[x]);

            a[x] = -a[x];

            ans += 1;
        }
    }

    cout << ans << '\n';
}

int main() {

    #ifdef ONLINE_JUDGE
        INPUT;
    #endif

    int t;

    for (cin >> t; t; t--) {
        solve();
    }

    #ifndef ONLINE_JUDGE
        cerr << '\n';
        system("pause");
    #endif

    return 0;
}
