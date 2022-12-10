#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
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
#define BIGINF 100000000700000
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define  INF64 1000000000000000003

//#define DEBUG

struct segment_tree_node {
    int lb, rb, ls;

    segment_tree_node() {
        lb = 0;
        rb = 0;
        ls = 0;
    }

    segment_tree_node(int lb0, int rb0) {
        lb = lb0;
        rb = rb0;
        ls = 0;
    }
};

struct segment_tree {
    const segment_tree_node neutral = segment_tree_node();
    vector<segment_tree_node> tree;

    static segment_tree_node combine(segment_tree_node a, segment_tree_node b) {
        segment_tree_node c;

        c.ls = a.ls + b.ls + min(a.lb, b.rb);

        c.lb = a.lb + b.lb - min(a.lb, b.rb);
        c.rb = a.rb + b.rb - min(a.lb, b.rb);

        return c;
    }

    void resize(int n) {
        tree.resize(n << 2);
    }

    void build(string& a) {
        build(0, 0, tree.size() >> 2, a);
    }

    void build(int v, int l, int r, string& a) {
        if (r - l == 1) {
            if (a[l] == ')') {
                tree[v] = segment_tree_node(0, 1);
            } else {
                tree[v] = segment_tree_node(1, 0);
            }
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
};

void solve() {
    int n, i, ql, qr, q;
    string s;
    segment_tree segtree;

    cin >> s;

    segtree.resize(s.size());
    segtree.build(s);

    for (cin >> q; q; q--) {
        cin >> ql >> qr;
        ql--;

        cout << 2 * segtree.get(ql, qr).ls << '\n';
    }
}

int main() {
    INPUT;

    int t;

    for (t = 1; t; t--) {
        solve();
    }

    return 0;
}
